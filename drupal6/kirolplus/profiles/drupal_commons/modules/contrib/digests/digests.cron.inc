<?php

/**
 * @file
 *   Cron tasks for the Activity Log Digests module.
 */

//============
// PROCESSING
//============

/**
 * Send digest emails.
 */
function _digests_cron() {
  $default_tz = variable_get('date_default_timezone', 0);
  $now = time();
  $send_time = gmmktime(variable_get('digests_send_time', 18), 0, 0);

  foreach (_digests_cron_get_users($default_tz, $now, $send_time) as $account) {
    $interval = isset($account->send_interval) ? $account->send_interval : 86400;
    $messages = _digests_cron_get_messages($account, $default_tz, $send_time, $interval);
    digests_send_message($account, $messages, $now, $interval);
  }
}

/**
 * Gets the users eligible to receive a digest email.
 *
 * @param $default_tz
 *   The site default timezone.
 * @param $now
 *   The current UNIX timestamp.
 * @param $send_time
 *   The UNIX timestamp after which emails can be sent.
 * @return
 *   An array of modified user account objects.
 */
function _digests_cron_get_users($default_tz = NULL, $now = NULL, $send_time = NULL) {
  if (!isset($default_tz)) {
    $default_tz = variable_get('date_default_timezone', 0);
  }
  if (!isset($now)) {
    $now = time();
  }
  if (!isset($send_time)) {
    $send_time = gmmktime(variable_get('digests_send_time', 18), 0, 0);
  }

  // Get users for whom it is after 6PM in their timezone but who have not had a digest sent for this interval.
  $default = $now > $send_time + $default_tz || $now < $send_time + $default_tz - 43200; // whether it's past send_time in the site's default timezone
  $query = "
    SELECT d.*, u.* /* We need the digests table first here, otherwise users with no digests row have uid = NULL in the results */
    FROM {users} u
    LEFT JOIN {digests} d
      ON u.uid = d.uid
    WHERE
      status = 1 AND (                                                  /* user is not blocked */
        send_interval IS NULL OR                                        /* user has not set their interval */
        send_interval = 86400                                           /* user's interval is daily */
        ". (date('w') == 0 ? 'OR send_interval = 604800' : '') ."       /* user's interval is weekly, and it's Sunday */
      ) AND
      %d > COALESCE(last_sent, created) + (COALESCE(send_interval, 86400) - 43200) /* it's been at least (interval - 12 hours) since the last digest email */
  ";
  if (variable_get('digests_local', 'local') == 'local') {
    $query .= "    AND (
        %d /* NOW */ > %d /* SEND */ + timezone OR      /* it's after send_time today */
        %d /* NOW */ < %d /* SEND */ + timezone - 43200 /* it's more than 12hrs before send_time today, i.e. less than 12hrs since send_time yesterday */
    ";
    if ($default) {
      $query .= "    OR timezone IS NULL /* the user has not set a timezone, fall back to the site default */\n    ";
    }
    $query .= "  )";
    if (variable_get('digests_limit', 250)) {
      $result = db_query_range($query, $now, $now, $send_time, $now, $send_time, 0, variable_get('digests_limit', 250));
    }
    else {
      $result = db_query($query, $now, $now, $send_time, $now, $send_time);
    }
  }
  elseif ($default) {
    if (variable_get('digests_limit', 250)) {
      $result = db_query_range($query, $now, 0, variable_get('digests_limit', 250));
    }
    else {
      $result = db_query($query, $now);
    }
  }

  $accounts = array();
  while ($account = db_fetch_object($result)) {
    if ($account = _digests_unpack_account($account)) {
      $accounts[] = $account;
    }
  }
  return $accounts;
}

/**
 * Unpacks a user account retrieved from the database by Digests.
 *
 * @param $account
 *   A user account object retrieved by a query like
 *   SELECT d.*, u.* FROM {users}  LEFT JOIN {digests} d ON u.uid = d.uid
 * @return
 *   The unpacked user account object if the account is valid and can receive
 *   digest emails; NULL otherwise.
 */
function _digests_unpack_account($account) {
  if (empty($account) || empty($account->uid) || !valid_email_address($account->mail)) {
    return;
  }
  $account = drupal_unpack($account);
  $account->roles = array();
  $account->roles[DRUPAL_AUTHENTICATED_RID] = 'authenticated user';
  $rresult = db_query('SELECT r.rid, r.name FROM {role} r INNER JOIN {users_roles} ur ON ur.rid = r.rid WHERE ur.uid = %d', $account->uid);
  while ($role = db_fetch_object($rresult)) {
    $account->roles[$role->rid] = $role->name;
  }
  if (!user_access('receive digests', $account)) {
    return;
  }
  return $account;
}

/**
 * Get the messages to be sent in a digest email to the designated user.
 *
 * @param $account
 *   A user account object retrieved by a query like
 *   SELECT d.*, u.* FROM {users}  LEFT JOIN {digests} d ON u.uid = d.uid
 * @param $default_tz
 *   The site default timezone.
 * @param $send_time
 *   The UNIX timestamp after which emails can be sent.
 * @param $interval
 *   The number of seconds representing the expected time between digest
 *   emails.
 * @param $options
 *   An associative array of options that determine how the function behaves.
 *   Includes the following keys:
 *   - include today: Whether to include activity from the current day
 * @return
 *   An array of activity message objects.
 */
function _digests_cron_get_messages($account, $default_tz = NULL, $send_time = NULL, $interval = NULL, $options = array()) {
  // For each selected user, collect all activity that has been updated between 6PM 2 days ago and 6PM yesterday
  if (!isset($default_tz)) {
    $default_tz = variable_get('date_default_timezone', 0);
  }
  if (!isset($send_time)) {
    $send_time = gmmktime(variable_get('digests_send_time', 18), 0, 0);
  }
  if (!isset($interval)) {
    $interval = isset($account->send_interval) ? $account->send_interval : 86400;
  }
  $options += array(
    'include today' => FALSE,
  );

  $account_tz = $default_tz;
  if (isset($account->timezone) && !is_null($account->timezone)) {
    $account_tz = $account->timezone;
  }
  $send_time_account = $send_time + $account_tz;
  $send_time_two_days_ago = $send_time_account - (86400 + $interval);
  $send_time_one_day_ago = $send_time_account - 86400;
  $args = array($account->uid, $send_time_two_days_ago);
  $query = "
    SELECT *
    FROM {activity_log_messages} m
    LEFT JOIN {activity_log_templates} t
      ON m.tid = t.tid
    WHERE
      display_type = 'email' AND
      stream_owner_type = 'user' AND
      stream_owner_id = %d AND
      last_updated > %d /* 2 days ago */ AND";
  if (!$options['include today']) {
    $query .= "
      last_updated < %d /* 1 day ago */ AND";
    $args[] = $send_time_one_day_ago;
  }
  $query .= " (
        viewer_id = %d /* account */ OR
        viewer_id = 0 /* everyone */ OR
        (viewer_id < 0 AND viewer_id <> -%d) /* everyone except account */
      ) AND
      t.pid NOT IN (
        SELECT pid FROM {activity_log_disabled_types} WHERE uid = %d
      )
    ORDER BY last_updated DESC";
  array_push($args, $account->uid, $account->uid, $account->uid);
  $mresult = db_query($query, $args);

  $messages = array();
  while ($record = db_fetch_object($mresult)) {
    $messages[] = $record;
  }
  return _digests_filter_messages_node_access($messages);
}

/**
 * Remove messages that the current user does not have access to view.
 *
 * @param $messages
 *   The set of messages from which to filter messages about restricted nodes.
 * @return
 *   An array of activity message objects that the user has permission to view.
 */
function _digests_filter_messages_node_access($messages) {
  if (empty($messages)) {
    return;
  }
  $aids = array();
  $aid_to_result_key_map = array();
  foreach ($messages as $key => $item) {
    if ($item->target_type == 'node') {
      $result_aids = array_filter(explode(',', $item->aids));
      $aids = array_merge($aids, $result_aids);
      foreach ($result_aids as $aid) {
        $aid_to_result_key_map[$aid] = $key;
      }
    }
  }
  if (empty($aids)) {
    return $messages;
  }
  $nids_result = db_query("SELECT aid, target_id AS nid FROM {activity_log_events} WHERE aid IN (". db_placeholders($aids) .")", $aids);
  $nids = array();
  while ($node = db_fetch_object($nids_result)) {
    $nids[$node->aid] = $node->nid;
  }
  // If we're not dealing with any nodes, we don't need to check node access.
  if (empty($nids)) {
    return $messages;
  }
  // Reduce the list of nids returned by the view to those which the user has permission to view.
  $nids_visible = array();
  $query_restricted = db_query(db_rewrite_sql("SELECT DISTINCT(n.nid) FROM {node} n WHERE n.nid IN (". db_placeholders($nids) .")"), array_values($nids));
  while ($result_restricted = db_fetch_object($query_restricted)) {
    $nids_visible[$result_restricted->nid] = $result_restricted->nid;
  }
  $nids_to_remove = array_diff($nids, $nids_visible); // preserves keys
  // Remove the activity from $messages that use events related to restricted nodes.
  $result_keys_to_remove = array();
  foreach ($nids_to_remove as $aid => $nid) {
    $key = $aid_to_result_key_map[$aid];
    $result_keys_to_remove[$key] = $key;
  }
  return array_diff_key($messages, $result_keys_to_remove);
}

/**
 * Send a digest email.
 *
 * @param $account
 *   A user account object retrieved by a query like
 *   SELECT d.*, u.* FROM {users}  LEFT JOIN {digests} d ON u.uid = d.uid
 * @param $messages
 *   An array of activity message objects.
 * @param $now
 *   The current UNIX timestamp.
 * @param $interval
 *   The number of seconds representing the expected time between digest
 *   emails.
 * @param $options
 *   An associative array of options affecting how this function behaves, with
 *   the following keys:
 *   - update last sent time: Whether to record in the database that a digest
 *     email was sent. This will affect when the next one gets sent during
 *     cron. Defaults to TRUE.
 *   - from: The email address from which the digest email should be sent.
 *     Defaults to the site's default email.
 */
function digests_send_message($account, $messages = array(), $now = NULL, $interval = NULL, $options = array()) {
  if (empty($messages)) {
    return;
  }
  if (!isset($now)) {
    $now = time();
  }
  if (!isset($interval)) {
    $interval = isset($account->send_interval) ? $account->send_interval : 86400;
  }
  $options += array(
    'update last sent time' => TRUE,
    'from' => variable_get('site_mail', ini_get('sendmail_from')),
  );

  $output = theme('digests_email', $account, $messages, $now);

  // Pass the rendered activity stream to the Mime Mail module for delivery
  if ($interval == 86400) {
    $subject = t('Your @site activity for @date', array(
      '@site' => variable_get('site_name', 'Drupal'),
      '@date' => date('l, F j', $now - $interval),
    ));
  }
  elseif ($interval == 604800) {
    $subject = t('Your @site activity for the week of @date', array(
      '@site' => variable_get('site_name', 'Drupal'),
      '@date' => date('F j', $now - $interval),
    ));
  }
  mimemail(
    $options['from'], //sender
    $account, // recipient
    $subject, // subject
    $output,  // HTML for body
    NULL,     // force plaintext only
    array(),  // headers
    NULL,     // custom plaintext version
    array(),  // attachments
    'digests' // mailkey
  );

  // Update the "last sent" time for each processed user
  if ($options['update last sent time']) {
    db_query("UPDATE {digests} SET last_sent = %d WHERE uid = %d", $now, $account->uid);
    if (db_affected_rows() <= 0) {
      $insert = (object) array(
        'uid' => $account->uid,
        'last_sent' => $now,
        'send_interval' => 86400,
      );
      drupal_write_record('digests', $insert);
    }
  }
}

/**
 * Preprocess the digest email template variables.
 */
function template_preprocess_digests_email(&$vars) {
  $output = '';
  $count = 0;
  foreach ($vars['messages'] as $message) {
    $count++;
    activity_log_record_unpack($message);
    $html_message = theme('activity_log_item', $message);
    $output .= '<tr><td class="digests-message" style="border-bottom:1px solid #f0f0f0;'. ($count === 1 ? ' border-top: 1px solid #f0f0f0; ' : ' ') .'padding-top:12px;padding-bottom:12px;">'. $html_message ."</td></tr>\n";
  }
  $vars['stream'] = $output;
  $account = $vars['account'];
  $vars['name'] = check_plain($account->name);
  $vars['name_link'] = l(check_plain($account->name), 'user/'. $account->uid);
  $now = $vars['now'];
  $vars['date_small'] = format_date($now, 'small');
  $vars['date_medium'] = format_date($now, 'medium');
  $vars['date_large'] = format_date($now, 'large');
  $vars['logo'] = _digests_get_logo();
  $header = variable_get('digests_header', '');
  $footer = variable_get('digests_footer', '');
  if (module_exists('token')) {
    $types = array('global' => NULL, 'user' => $account);
    $header = token_replace_multiple($header, $types);
    $footer = token_replace_multiple($footer, $types);
  }
  $vars['header'] = filter_xss_admin($header);
  $vars['footer'] = filter_xss_admin($footer);
  $vars['unsubscribe'] = t('<a href="!unsub">Edit your settings</a> to unsubscribe from activity emails from @site.', array(
    '!unsub' => url('user/'. $account->uid .'/edit', array('absolute' => TRUE)),
    '@site' => variable_get('site_name', 'Drupal'),
  ));
}

/**
 * Get the logo for the digest email.
 */
function _digests_get_logo() {
  $path = variable_get('digests_logo_use_theme', 1)
    ? theme_get_setting('logo')         // theme's logo
    : variable_get('digests_logo', ''); // custom path
  if ($path) {
    return theme(
      'image',
      url($path, array('absolute' => TRUE)),
      variable_get('site_name', 'Drupal'),
      variable_get('site_name', 'Drupal'),
      NULL,
      FALSE
    );
  }
}
