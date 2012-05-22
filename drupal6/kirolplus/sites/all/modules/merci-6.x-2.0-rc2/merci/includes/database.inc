<?php

/**
 * @file
 * MERCI - Managed Equipment Reservation Checkout and Inventory
 */

function merci_reservation_item_node_settings($vid) {
  if (!$vid) {
    return;
  }
  return db_fetch_array(db_query("SELECT merci_default_availability, merci_sub_type, merci_item_status FROM {merci_reservation_item_node} WHERE vid = %d", $vid));
}

function merci_bucket_node_settings($vid) {
  if (!$vid) {
    return;
  }
  return db_fetch_array(db_query("SELECT merci_late_fee_per_hour, merci_rate_per_hour, merci_fee_free_hours FROM {merci_bucket_node} WHERE vid = %d", $vid));
}

function merci_resource_node_settings($vid) {
  if (!$vid) {
    return;
  }
  return db_fetch_array(db_query("SELECT merci_late_fee_per_hour, merci_rate_per_hour, merci_fee_free_hours, merci_min_cancel_hours, merci_autocheckout, merci_autocheckin, merci_selfcheckout FROM {merci_resource_node} WHERE vid = %d", $vid));
}

function merci_is_item_reservable($item_nid, $type, $start, $end, $exclude_vid = NULL) {
  $items = merci_load_reservations_for_node_in_timespan($item_nid, $type, $start, $end, $exclude_vid);

  // If we are checking an item?
  if ($item_nid) {
   if (isset($items[$item_nid]) and count($items[$item_nid])) {
    return FALSE;
   }
   return TRUE;
  }

  // If we are checking a bucket
  $count = 0;
  foreach ($items as $item_nid => $reservations) {
    if (empty($reservations)) {
      $count++;
    }
  }
  $content_settings = merci_load_item_settings($type);
  return $count - $content_settings->merci_spare_items > 0 ? $count - $content_settings->merci_spare_items : FALSE;
}

function merci_taxonomy_node_delete_vocabulary($node, $vid) {

  if (empty($vid) or empty($node->vid)) {
    return;
  }
  db_query("DELETE FROM {term_node} WHERE vid = %d and tid IN (SELECT tid FROM {term_data} td WHERE td.vid = %d)", $node->vid, $vid);
}

function merci_taxonomy_node_save_terms($node, $tids) {

  if (empty($tids) or empty($node->vid)) {
    return;
  }

  foreach ($tids as $tid) {
    if ($tid) {
      $object = array('nid' => $node->nid, 'vid' => $node->vid, 'tid' => $tid);
      drupal_write_record('term_node', $object);
    }
  }
}

function merci_nodes_for_type_count($type) {
  return db_result(db_query("SELECT COUNT(nid) FROM {node} WHERE type = '%s'", $type));
}

function merci_node_type_update($info) {
  if (isset($info->old_type) && $info->type != $info->old_type) {
    db_query("UPDATE {merci_node_type} SET type = '%s' WHERE type = '%s'", $info->type, $info->old_type);
    cache_clear_all('merci_' . $info->type . '_data', 'cache');
    cache_clear_all('merci_content_type_info', 'cache');
  }
}

function merci_node_type_existing($type) {
  return db_result(db_query("SELECT type FROM {merci_node_type} WHERE type = '%s'", $type));
}

function merci_node_type_delete($info) {
  db_query("DELETE FROM {merci_node_type} WHERE type = '%s'", $info->type);
  variable_del('merci_type_setting_' . $info->type);
  cache_clear_all('merci_' . $info->type . '_data', 'cache');
  cache_clear_all('merci_content_type_info', 'cache');
}

function merci_reservation_status($node) {
  return db_result(db_query("SELECT merci_reservation_status FROM {merci_reservation} WHERE vid = %d", $node->vid));
}

function merci_reservation_items($node) {
  $items = db_query("SELECT m.did, m.merci_item_status, merci_placeholder_nid, pn.title AS placeholder_title, merci_item_nid, tn.title AS item_title, nt.type, nt.name FROM {merci_reservation_detail} m INNER JOIN {node} pn ON m.merci_placeholder_nid = pn.nid INNER JOIN {node_type} nt ON pn.type = nt.type LEFT JOIN {node} tn ON m.merci_item_nid = tn.nid WHERE m.vid = %d", $node->vid);

  $reservation_items = array();

  while ($item = db_fetch_array($items)) {
    $reservation_items[$item['did']] = $item;
  }
  return $reservation_items;
}

/**
 * merci_get_reservation_count($content_type[string])
 * returns total number of checked out items for content type.
 * @ $content_type resource to be counted
 */
function merci_get_reservation_count($content_type) {
  return db_result(db_query("SELECT COUNT(n.nid) as total FROM {node} n
    JOIN {merci_reservation_detail} mrin ON mrin.vid = n.vid
    JOIN {node} ctn ON mrin.merci_item_nid = ctn.nid
    WHERE ctn.type = '%s' and mrin.merci_item_status = %d", $content_type, MERCI_ITEM_STATUS_CHECKED_OUT));
}

function merci_delete_record($table, &$object, $update = array()) {
  // Standardize $update to an array.
  if (is_string($update)) {
    $update = array($update);
  }

  $schema = drupal_get_schema($table);
  if (empty($schema)) {
    return FALSE;
  }

  // Convert to an object if needed.
  if (is_array($object)) {
    $object = (object) $object;
    $array = TRUE;
  }
  else {
    $array = FALSE;
  }

  $fields = $values = array();


  // Build the SQL.
  $query = '';

  foreach ($update as $key) {
    $conditions[] = "$key = " . db_type_placeholder($schema['fields'][$key]['type']);
    $values[] = $object->$key;
  }

  $query = "DELETE FROM {" . $table . "} WHERE " . implode(' AND ', $conditions);

  // Execute the SQL.
  if (db_query($query, $values)) {

    $return = true;
  }
  else {
    $return = FALSE;
  }

  // If we began with an array, convert back so we don't surprise the caller.
  if ($array) {
    $object = (array) $object;
  }

  return $return;
}
/**
 * Returns totals for reporting.
 *
 * @param $type
 *   The bucket or resrouce node type.
 * @param $startdate
 *   TRUE to restrict to published items, FALSE otherwise.
 *
 * @return
 *   Total reservation number for that type betweent the start and end dates
 TODO NOT USER.
 */
function merci_reservation_totals($type, $startdate, $enddate) {
  $result = db_query("SELECT COUNT(nid) as total  FROM {node} WHERE type LIKE '%s' and status = 0 AND created > %d AND created < %d", $type, $startdate, $enddate);
  $reservationnode = db_fetch_object($result);
  return $reservationnode->total;
}
function merci_has_accessories($content_type) {
  if (empty($content_type)) {
    return;
  }
  return db_fetch_object(db_query("SELECT * FROM {vocabulary_node_types} WHERE type = '%s'", $content_type));
}

/**
 * Pass type as user/project and uid/nid
 * returns total hours
 */
function merci_total_usage($id, $type = 'user', $date = NULL) {

  // Determine CCK table and columns the date data is stored in.
  $field             = content_fields('field_merci_date');
  $db_info           = content_database_info($field);
  $table             = $db_info['table'];
  $column_start_date = $db_info['columns']['value']['column'];
  $column_end_date   = $db_info['columns']['value2']['column'];

  if ($type == 'project') {
    $result = db_query("SELECT $column_start_date AS field_merci_date_value, $column_end_date AS field_merci_date_value2 FROM {merci_reservation} mr JOIN node n ON n.vid = mr.vid JOIN og_ancestry og ON og.nid = n.nid JOIN {" . $table . "} ct ON n.vid = ct.vid WHERE group_nid = %d", $id);
  }
  else {
    if ($date) {
      $result = db_query("SELECT $column_start_date AS field_merci_date_value, $column_end_date AS field_merci_date_value2 FROM {merci_reservation} mr JOIN {node} n ON n.vid = mr.vid JOIN {" . $table . "} ct ON n.vid = ct.vid WHERE uid = %d AND $column_start_date > '%s'", $id, $date);
    }
    else {
      $result = db_query("SELECT $column_start_date AS field_merci_date_value, $column_end_date AS field_merci_date_value2 FROM {merci_reservation} mr JOIN {node} n ON n.vid = mr.vid JOIN {" . $table . "} ct ON n.vid = ct.vid WHERE uid = %d", $id);
    }
  }

  //add the reservation total minutes for each item in the reservation
  while ($reservationnode = db_fetch_object($result)) {

    $minutes = $minutes + ((strtotime($reservationnode->field_merci_date_value2) - strtotime($reservationnode->field_merci_date_value)));
  }

  return $minutes;
}

function merci_incomplete_reservations_for_item_nid($nid) {
  // Determine CCK table and columns the date data is stored in.
  $field           = content_fields('field_merci_date');
  $db_info         = content_database_info($field);
  $table           = $db_info['table'];
  $column_end_date = $db_info['columns']['value2']['column'];

  $time = gmdate('Y-m-d H:i:s');

  // Pull any incomplete reservations that use the item in question
  $reservations = db_query(db_rewrite_sql("SELECT n.nid, n.title FROM {node} n INNER JOIN {" . $table . "} ct ON ct.vid = n.vid INNER JOIN {merci_reservation_detail} md ON ct.vid = md.vid WHERE md.merci_item_nid = %d AND " . $column_end_date . " >= '%s' AND NOT (md.merci_item_status <= %d)"), $nid, $time, MERCI_ITEM_STATUS_AVAILABLE);

  $bad_reservations = array();
  while ($reservation = db_fetch_object($reservations)) {
    $bad_reservations[] = l($reservation->title, "node/$reservation->nid/edit", array('query' => drupal_get_destination()));
  }

  return $bad_reservations;

}

function merci_db_reservations_by_status_in_timespan($statuses = array(), $start = NULL, $end = NULL, $older = FALSE) {

  // Determine CCK table and columns the date data is stored in.
  $field             = content_fields('field_merci_date');
  $db_info           = content_database_info($field);
  $table             = $db_info['table'];
  $column_start_date = $db_info['columns']['value']['column'];
  $column_end_date   = $db_info['columns']['value2']['column'];

  $where = array();
  $args = array();

  if (!empty($statuses)) {
    $status_where = array();
    foreach ($statuses as $status) {
      $status_where[] = 'mr.merci_reservation_status = %d';
      $args[] = $status;
    }
    $where[] = '(' . implode(' OR ', $status_where) . ')';
  }

  if ($start) {
    $args[] = $start;
    $where[] = "$column_start_date <= '%s'";
  }
  if ($end) {
    $args[] = $end;
    // See if we are looking for reservations which have ended.
    if ($older and !$start) {
      $where[] = "$column_end_date < '%s'";
    } else {
      $where[] = "$column_end_date > '%s'";
    }
  }

  $where = count($where) ? 'WHERE ' . implode(' AND ', $where) : '';
  // Select reservation nodes where all reserved items and resources are autocheckout.
  $reservations = db_query("SELECT n.nid FROM {node} AS n
        INNER JOIN {" . $table . "} ct ON ct.vid = n.vid
        INNER JOIN {merci_reservation} AS mr ON n.vid = mr.vid
          $where", $args);


  $nodes = array();
  while ($reservation_nid = db_result($reservations)) {

    $nodes[$reservation_nid] = $reservation_nid;

  }
  return $nodes;
}
/**
 * Pulls an array of items that are reservable for the content type and date range.
 *
 * @param $content_type
 *   The content type name of the bucket/resource.
 * @param $start
 *   Start time in DATETIME format UTC timezone.
 * @param $end
 *   End time in DATETIME format UTC timezone.
 * @param $reservation_nid
 *   (Optional) A reservation nid to exclude from the reserved items.
 *
 * @return
 *   An array of reservable items, in select option format.
 */
function merci_get_reservable_items($content_type, $start = NULL, $end = NULL, $reservation_nid = NULL, $overdue = TRUE) {


  $merci_type = merci_type_setting($content_type);
  // Pull reservable items.  This query takes the following into consideration:
  //   1. Pulls all all item nodes of the content type that are in an available or checked in state,
  //   2. Excludes all item nodes that have associated reservations in the date range
  //      of the this reservation where the item is in an already reserved or checked out state.
  //   3. Allows a reservation to be excluded from the exclusions if necessary (this
  //      is usually used to allow an already assigned item to not conflict with itself.
  //   4. Exclude items from past reservations where the item is in a checked out state.

  $query = "SELECT n.nid, n.title, ni.title as insta
		FROM {node} n, {merci_reservation_item_node} m, {content_type_reservables} ctr, {node} ni
		WHERE n.vid = m.vid
		AND n.nid = ctr.nid
		AND ni.nid = ctr.field_ref_instalacion_nid
		AND m.merci_default_availability IN (%d, %d)
        AND n.type = '%s'
        ";

  $args = array(MERCI_AVA_F, MERCI_AVA_T, $content_type, MERCI_SUB_TYPE_ITEM);

  if ($start) {
    // Determine CCK table and columns the date data is stored in.
    $field             = content_fields('field_merci_date');
    $db_info           = content_database_info($field);
    $table             = $db_info['table'];
    $column_start_date = $db_info['columns']['value']['column'];
    $column_end_date   = $db_info['columns']['value2']['column'];

    $args = array_merge($args, array($start, $end, $start, $end, $start, $end, MERCI_ITEM_STATUS_AVAILABLE));

    // If there's an already selected bucket item, then we need to make sure we
    // include it in the list of available items.
    $query .= "
      AND n.nid NOT IN
      (SELECT md2.merci_item_nid FROM {" . $table . "} ct
      INNER JOIN {merci_reservation_detail} md2 ON ct.vid = md2.vid
      INNER JOIN {merci_reservation_item_node} m2 ON md2.merci_item_nid = m2.nid
      INNER JOIN {node} ctn ON ctn.vid = ct.vid
      INNER JOIN {node} m2n ON m2.vid = m2n.vid
      WHERE (
        (
          (($column_start_date >= '%s' AND $column_start_date <= '%s')
          OR ($column_end_date >= '%s' AND $column_end_date <= '%s')
          OR ($column_start_date <= '%s' AND $column_end_date >= '%s'))
          AND NOT md2.merci_item_status <= %d
        ) ";
    if ($reservation_nid) {
      $where = ' AND md2.nid <> %d';
      $args[] = $reservation_nid;
    } else {
      $where = '';
    }

    $query .= "
      )
      $where
    )
    ";

  }
  $query .= " ORDER BY ni.title, n.title";

  $items = db_query($query, $args);
  $options = array();

  while ($item = db_fetch_object($items)) {
    $options[$item->nid] = $item->title.' ('.$item->insta.')';
  }

  if ($overdue) {
    $overdue_items_array = merci_overdue_items($content_type, $start, $reservation_nid);
    if (!empty($overdue_items_array)) {
      foreach ($options as $item_nid => $title) {
        if (array_key_exists($item_nid, $overdue_items_array)) {
          unset($options[$item_nid]);
        }
      }
    }
  }
  return $options;
}

function merci_overdue_items($content_type, $start, $reservation_nid = NULL) {
  // Determine CCK table and columns the date data is stored in.
  $field             = content_fields('field_merci_date');
  $db_info           = content_database_info($field);
  $table             = $db_info['table'];
  $column_start_date = $db_info['columns']['value']['column'];
  $column_end_date   = $db_info['columns']['value2']['column'];

  // pull reservations in the past which are still checked out.
  $start = date_create($start, timezone_open("UTC")) >= date_create("now") ? gmdate("Y-m-d H:i:s") : $start;
  $args = array($start, $content_type, MERCI_ITEM_STATUS_CHECKED_OUT);

  $merci_type = merci_type_setting($content_type);

  // If we're checking an existing reservation, exclude it from the
  // reserved items.
  if (isset($reservation_nid)) {
    $where = ' AND ct.nid <> %d';
    $args[] = $reservation_nid;
  } else {
    $where = '';
  }

  $reserved_nodes = db_query("
    SELECT ct.nid,$column_start_date AS field_merci_date_value, $column_end_date AS field_merci_date_value2 ,md.merci_item_nid FROM {" . $table . "} ct
    INNER JOIN {merci_reservation_detail} md on ct.vid = md.vid
    INNER JOIN {merci_{$merci_type}_node} m on md.merci_placeholder_nid = m.nid
    INNER JOIN {node} ctn on ct.vid = ctn.vid
    INNER JOIN {node} mn on m.vid = mn.vid
    WHERE ($column_end_date <= '%s')
    AND mn.type = '%s'
    AND md.merci_item_nid !=0
    AND md.merci_item_status = %d
    $where",
    $args
  );

  // Use up items for assigned nodes.
  while ($node = db_fetch_object($reserved_nodes)) {
    $total_items_array[$node->merci_item_nid][$node->nid] = $node;
  }

  return isset($total_items_array) ? $total_items_array : array();
}

function _merci_sort_array($a, $b) {
  return count($b) - count($a);
}
//TODO: the following three functions look very much a like.
function merci_reserved_bucket_items($content_type, $start = NULL, $end = NULL, $reservation_vid = NULL, $overdue = TRUE) {

  // Determine CCK table and columns the date data is stored in.
  $field             = content_fields('field_merci_date');
  $db_info           = content_database_info($field);
  $table             = $db_info['table'];
  $column_start_date = $db_info['columns']['value']['column'];
  $column_end_date   = $db_info['columns']['value2']['column'];

  // Get all assignable nodes for this bucket item.
  $total_items_nodes = db_query("SELECT n.nid FROM {node} n INNER JOIN {merci_reservation_item_node} m ON n.vid = m.vid WHERE n.type = '%s' AND m.merci_sub_type = %d AND m.merci_default_availability IN (%d, %d)", $content_type, MERCI_SUB_TYPE_ITEM, MERCI_AVA_F);
  $total_items_array = array();
  while ($ctnodes = db_fetch_array($total_items_nodes)) {
    $total_items_array[$ctnodes['nid']] = array();
  }

  $args = array($start, $end, $start, $end, $start, $end, $content_type, MERCI_ITEM_STATUS_AVAILABLE);

  // If we're checking an existing reservation, exclude it from the
  // reserved items.
  if (isset($reservation_vid)) {
    $where = ' AND ct.vid <> %d';
    $args[] = $reservation_vid;
  }
  else {
    $where = '';
  }

  // pull reservations with assigned nodes and status of MERCI_ITEM_STATUS_RESERVED or MERCI_ITEM_STATUS_CHECKED_OUT
  $reserved_nodes = db_query("
    SELECT ct.nid,$column_start_date AS field_merci_date_value, $column_end_date AS field_merci_date_value2 ,md.merci_item_nid FROM {" . $table . "} ct
      INNER JOIN {merci_reservation_detail} md on ct.vid = md.vid
      INNER JOIN {merci_bucket_node} m on md.merci_placeholder_nid = m.nid
      INNER JOIN {node} ctn on ct.vid = ctn.vid
      INNER JOIN {node} mn on m.vid = mn.vid
        WHERE (
                ($column_start_date >= '%s' and $column_start_date <= '%s')
            OR  ($column_end_date >= '%s' and $column_end_date <= '%s')
            OR  ($column_start_date <= '%s' and $column_end_date >= '%s')
          )
          AND mn.type = '%s'
          AND md.merci_item_nid !=0
          AND NOT md.merci_item_status <= %d
          $where",
    $args
  );

  // Use up items for assigned nodes.
  while ($node = db_fetch_object($reserved_nodes)) {
    // If item is assigned then item is in use by this node.
    $total_items_array[$node->merci_item_nid][$node->nid] = $node;
  }

  if ($overdue) {
    $overdue_items_array = merci_overdue_items($content_type, $start, $reservation_vid);

    if (!empty($overdue_items_array)) {
      foreach ($overdue_items_array as $merci_item_nid => $nodes) {
        foreach ($nodes as $nid => $node) {
          $total_items_array[$node->merci_item_nid][$node->nid] = $node;
        }
      }
    }
  }

  // pull reservations without assigned nodes and not status of MERCI_ITEM_STATUS_CHECKED_IN
  $reserved_nodes = db_query("
    SELECT ct.nid,$column_start_date AS field_merci_date_value, $column_end_date AS field_merci_date_value2 ,md.merci_item_nid FROM {" . $table . "} ct
        INNER JOIN {merci_reservation_detail} md ON ct.vid = md.vid
        INNER JOIN {merci_bucket_node} m ON md.merci_placeholder_nid = m.nid
        INNER JOIN {node} ctn on ct.vid = ctn.vid
        INNER JOIN {node} mn ON m.vid = mn.vid
          WHERE (
                  ($column_start_date >= '%s' AND $column_start_date <= '%s')
              OR  ($column_end_date >= '%s' AND $column_end_date <= '%s')
              OR  ($column_start_date <= '%s' AND $column_end_date >= '%s')
            )
            AND mn.type = '%s'
            AND md.merci_item_nid = 0
            AND NOT md.merci_item_status < %d
            $where",
    $args
  );

  uasort( $total_items_array, '_merci_sort_array');
  // Temporarily assign an item for these nodes.
  while ($node = db_fetch_object($reserved_nodes)) {

    // Eat up a bucket item for this node.
    // If item is not assigned then temporarily add one.
    foreach ($total_items_array as $item_nid => $reservations) {
      $willitfit = TRUE;
      foreach ($reservations as $oldnode) {
        // Does the start date overlap this reservation.
        if (
          (
            date_create($node->field_merci_date_value) > date_create($oldnode->field_merci_date_value) and
            date_create($node->field_merci_date_value) < date_create($oldnode->field_merci_date_value2)
          ) or
          // Does the end date overlap this reservation.
          (
            date_create($node->field_merci_date_value2) > date_create($oldnode->field_merci_date_value) and
            date_create($node->field_merci_date_value2) < date_create($oldnode->field_merci_date_value2)
          ) or
          // Does the start and end date overlap this reservation.
          (
            date_create($node->field_merci_date_value) <= date_create($oldnode->field_merci_date_value) and
            date_create($node->field_merci_date_value2) >= date_create($oldnode->field_merci_date_value2)
          )
        ) {
          // Can't use this item for this reservation. So try another.
          $willitfit = FALSE;
          break;
        }
      }
      if ($willitfit) {
        $total_items_array[$item_nid][$node->nid] = $node;
        break;
      }
    }
  }

  return $total_items_array;
}

// merci_get_reservable_items

/**
 * Calculates the total number of available bucket items for a reservation.
 *
 * @param $content_type
 *   The bucket content type.
 * @param $start
 *   Start time in DATETIME format UTC timezone.
 * @param $end
 *   End time in DATETIME format UTC timezone.
 * @param $reservation_nid
 *   (Optional) A reservation nid to exclude from the reserved items.
 *
 * @return
 *   The number of available bucket items.
 */
function merci_get_available_bucket_count($content_type, $start = NULL, $end = NULL, $reservation = NULL) {
  //if there are no dates, return the active total

  if (!$start) {

    //if user is admin/manager and merci template is installed

    $count = db_fetch_object(db_query("SELECT COUNT(n.nid) as total FROM {node} n
      LEFT JOIN {merci_bucket_node} mbn ON n.vid = mbn.vid
      WHERE n.type = '%s' AND n.status = 1
      AND mbn.merci_default_availability = 1",
      $content_type
    ));
    return $count->total;
  }

  $total_items_array = merci_reserved_bucket_items($content_type, $start, $end, $reservation );

  $reserved_items = 0;
  foreach ($total_items_array as $item_nid => $reservations) {
    if (!empty($reservations)) {
      $reserved_items++;
    }
  }

  return sizeof($total_items_array) - $reserved_items;
}

/**
 * merci_get_count ($content_type, $default_availability)
 * returns total number of items available for check out.
 * @ $content_type resource to be counted
 * @ $default_availability
 */

function merci_get_count($type, $default_availability = MERCI_AVA_F) {
  return db_result(db_query("SELECT COUNT(n.nid) as total FROM {node} n
      LEFT JOIN {merci_" . $type['merci_type_setting'] . "_node} mbn ON n.vid = mbn.vid
      WHERE n.type = '%s'
      AND mbn.merci_default_availability = %d
      AND mbn.merci_sub_type = %d",
      $type['type'], $default_availability, MERCI_SUB_TYPE_ITEM
    ));
}

/**
 * Builds an array representing reservations for a Resource within a given timespan
 *
 * @return
 *   An associative array with keys as times (in MySQL datetime format) and values as number of reservations.
 */
function merci_load_reservations_for_node_in_timespan($item_nid, $type, $start_date, $end_date, $reservation_vid = NULL) {

  // Determine CCK table and columns the date data is stored in.
  $field             = content_fields('field_merci_date');
  $db_info           = content_database_info($field);
  $table             = $db_info['table'];
  $column_start_date = $db_info['columns']['value']['column'];
  $column_end_date   = $db_info['columns']['value2']['column'];
  /*
   */

  $type_settings = merci_type_setting($type);
  if ($type_settings == 'bucket' and empty($item_nid)) {
    return merci_reserved_bucket_items($type, $start_date, $end_date, $reservation_vid, FALSE);
  }
  else {
    $sql = "SELECT r.nid, $column_start_date AS field_merci_date_value, $column_end_date AS field_merci_date_value2, merci_item_nid
      FROM {node} n
      JOIN {merci_reservation_detail} d ON n.nid = d.merci_item_nid
      JOIN {" . $table . "} r ON d.vid = r.vid
      WHERE n.nid = %d
        AND
                    (($column_start_date >= '%s' AND $column_start_date <= '%s')
                    OR ($column_end_date >= '%s' AND $column_end_date <= '%s')
                    OR ($column_start_date <= '%s' AND $column_end_date >= '%s'))
      ";
  }

  $args = array($item_nid, $start_date, $end_date, $start_date, $end_date, $start_date, $end_date);

  // If we're checking an existing reservation, exclude it from the
  // reserved items.
  if ($reservation_vid) {
    $sql .= " AND d.vid <> %d";
    $args[] = $reservation_vid;
  }
  $sql .= " ORDER BY $column_start_date ";

  $reservations = db_query($sql, $args);
  while ($reservation = db_fetch_object($reservations)) {
    $return[$item_nid][$reservation->nid] = $reservation;
  }

  return isset($return) ? $return : NULL;
}

