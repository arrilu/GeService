<?php

/**
 * @file
 *   Administrative settings for the Activity Digests module.
 */

/**
 * Administrative options.
 */
function digests_admin($form_state) {
  $form = array();
  $form['digests_send_time'] = array(
    '#type' => 'select',
    '#title' => t('Send digests after'),
    '#description' => t('Select an hour of the day'),
    '#options' => _digests_get_hours(),
    '#default_value' => variable_get('digests_send_time', 18),
    '#required' => TRUE,
  );
  $form['digests_local'] = array(
    '#type' => 'radios',
    '#title' => t('Send digests'),
    '#default_value' => variable_get('digests_local', 'local'),
    '#options' => array(
      'local' => t("using users' local timezones"),
      'site' => t("using the site's timezone"),
    ),
    '#required' => TRUE,
  );
  $form['digests_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('The maximum number of users to which to send digests each time cron runs'),
    '#description' => t('Leave this field blank or enter 0 to process all users.'),
    '#default_value' => variable_get('digests_limit', 250),
    '#size' => 11,
    '#maxlength' => 15,
  );
  $form['logo'] = array(
    '#type' => 'fieldset',
    '#title' => t('Logo image'),
    '#description' => t('The logo to display at the top of digest emails.') .' '.
      t('Un-check "Use theme logo" and leave the "Logo path" blank if you do not want to display a logo in digest emails.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['logo']['digests_logo_use_theme'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use theme logo'),
    '#description' => t("If checked, the default theme's logo will be used."),
    '#default_value' => variable_get('digests_logo_use_theme', 1),
  );
  $form['logo']['digests_logo'] = array(
    '#type' => 'textfield',
    '#title' => t('Logo path'),
    '#description' => t('The path to your logo image from your Drupal root.'),
    '#default_value' => variable_get('digests_logo', ''),
  );
  if (module_exists('token')) {
    $form['token_help'] = array(
      '#title' => t('Replacement patterns'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['token_help']['global'] = array(
      '#title' => t('Global'),
      '#description' => t('You can use these tokens in the email header or footer.'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['token_help']['global']['help'] = array(
      '#value' => theme('token_help', 'global'),
    );
    $form['token_help']['user'] = array(
      '#title' => t('Recipient user'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['token_help']['user']['help'] = array(
      '#value' => theme('token_help', 'user'),
    );
  }
  $form['digests_header'] = array(
    '#type' => 'textarea',
    '#title' => t('Email header'),
    '#rows' => 2,
    '#default_value' => variable_get('digests_header', ''),
  );
  $form['digests_footer'] = array(
    '#type' => 'textarea',
    '#title' => t('Email footer'),
    '#rows' => 2,
    '#default_value' => variable_get('digests_footer', ''),
  );
  return system_settings_form($form);
}

/**
 * Validates the administrative options.
 */
function digests_admin_validate($form, $form_state) {
  $v = $form_state['values']['digests_limit'];
  if (!empty($v) && (!is_numeric($v) || $v < 0)) {
    form_set_error('digests_limit', t('The maximum number of users to which to send digests per cron run must be a positive integer.'));
  }
}

/**
 * Returns a list of the hours of the day formatted by the site's preference.
 */
function _digests_get_hours() {
  $range = range(0, 23);
  $date_format = variable_get('date_format_long', 'l, F j, Y - H:i');
  $hour_format = 'H'; // e.g. 00
  foreach (array('a', 'A', 'g', 'h') as $c) {
    if (strpos($date_format, $c) !== FALSE) {
      $hour_format = 'ga'; // e.g. 12am
      break;
    }
  }
  $options = array();
  foreach ($range as $num) {
    $options[$num] = date($hour_format, mktime($num, 0, 0));
  }
  return $options;
}

/**
 * Allows administrators to send digest emails immediately.
 */
function digests_admin_send($form_state) {
  $form = array();
  $form['info'] = array(
    '#value' => '<p>'. t('Note that users may not receive digests if there is no activity from the previous day or week to send them.') .'</p>',
  );
  $form['recipients'] = array(
    '#type' => 'textfield',
    '#title' => t('Send digests to'),
    '#description' => t('Type in the usernames of people to whom to send digest emails now.') .' '.
      t('If you leave this field blank, digest emails will be sent to all users with recent activity available.'),
    '#maxlength' => 1000,
    '#autocomplete_path' => 'digests/autocomplete',
  );
  $form['send'] = array(
    '#type' => 'submit',
    '#value' => t('Send digests now'),
  );
  return $form;
}

/**
 * Submits the "Send now" form.
 */
function digests_admin_send_submit($form, $form_state) {
  $recipients_string = $form_state['values']['recipients'];
  $recipients_names_final = array();
  if (!empty($recipients_string)) {
    $recipients_names_orig = explode(',', $recipients_string);
    foreach ($recipients_names_orig as $recipient_name) {
      $recipients_names_final[] = trim($recipient_name);
    }
  }

  module_load_include('inc', 'digests', 'digests.cron');
  $message_count = 0;
  $now = time();
  $recipients = _digests_now_get_users($recipients_names_final);
  foreach ($recipients as $account) {
    $interval = isset($account->send_interval) ? $account->send_interval : 86400;
    $messages = _digests_cron_get_messages(
      $account,
      variable_get('date_default_timezone', 0),
      gmmktime(variable_get('digests_send_time', 18), 0, 0),
      $interval,
      array('include today' => TRUE)
    );
    $message_count += count($messages);
    digests_send_message($account, $messages, $now, $interval, array('update last sent time' => FALSE));
  }

  if ($message_count === 0) {
    drupal_set_message(t('No digest emails sent. Make sure there is recent activity to send!'), 'warning');
  }
  elseif ($message_count === 1) {
    drupal_set_message(t('Sent a digest email to 1 user containing 1 activity.'));
  }
  else {
    drupal_set_message(format_plural(count($recipients),
      'Sent a digest email to 1 user containing @activities activities.',
      'Sent digest emails to @count users containing @activities activities.',
      array('@activities' => $message_count)
    ));
  }
}

/**
 * Gets the users eligible to receive a digest email.
 *
 * @param $usernames
 *   An array of users to retrieve. If empty, defaults to all users.
 * @return
 *   An array of modified user account objects.
 */
function _digests_now_get_users($usernames = array()) {
  $query = "
    SELECT d.*, u.* /* We need the digests table first here, otherwise users with no digests row have uid = NULL in the results */
    FROM {users} u
    LEFT JOIN {digests} d
      ON u.uid = d.uid
    WHERE
      status = 1
  ";
  if (!empty($usernames)) {
    $query .= "    AND name IN (". db_placeholders($usernames, 'text') .")";
    if (variable_get('digests_limit', 250)) {
      $result = db_query_range($query, $usernames, 0, variable_get('digests_limit', 250));
    }
    else {
      $result = db_query($query, $usernames);
    }
  }
  else {
    if (variable_get('digests_limit', 250)) {
      $result = db_query_range($query, 0, variable_get('digests_limit', 250));
    }
    else {
      $result = db_query($query);
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
 * Autocompletes multiple-username textfields.
 * Some awkwardness exists if a user has quotes or commas in their username.
 * Adapted from taxonomy.module.
 *
 * @param $string
 *   The list of names.
 */
function _digests_user_autocomplete($string = '') {
  $array = drupal_explode_tags($string);
  // The user enters a comma-separated list of names. We only autocomplete the last name.
  $search = trim(array_pop($array));
  $matches = array();
  if ($search != '') {
    $result = db_query_range("SELECT DISTINCT(name) FROM {users}
      WHERE status <> 0 AND uid <> 0 AND LOWER(name) LIKE LOWER('%s%%')
      ORDER BY name ASC", $search, 0, 10);
    $prefix = count($array) ? implode(', ', $array) .', ' : '';
    while ($account = db_fetch_object($result)) {
      $name = $account->name;
      // Commas and quotes in terms are special cases, so encode them.
      // Use strpos() to check if they exist first since str_replace() is costly.
      if (strpos($account->name, ',') !== FALSE || strpos($account->name, '"') !== FALSE) {
        $name = '"'. str_replace('"', '""', $account->name) .'"';
      }
      $matches[$prefix . $name] = check_plain($account->name);
    }
  }
  drupal_json($matches);
}
