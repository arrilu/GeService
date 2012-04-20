<?php

/**
 * @file
 * MERCI - Managed Equipment Reservation Checkout and Inventory
 */

function template_preprocess_merci_conflict_grid(&$variables) {

  $type = $variables['type'];
  $title = $variables['title'];
  $start = $variables['start'];
  $end = $variables['end'];
  $nid = $variables['nid'];
  $reservation_vid = $variables['reservation_vid'];

  $hours = array();
  if (user_access('create reservations outside hours of operation')) {
    $adminhours = explode('-', variable_get('merci_hours_admin', '07:00-23:00'));

    for ($day = 0; $day < 7; $day++) {
      $hours[$day]['open'] = $adminhours[0];
      $hours[$day]['close'] = $adminhours[1];
    }
  }
  else {
    $hours = merci_load_hours_of_operation();
  }

  // Convert the start and end dates to the site timezone.
  $start = date_make_date($start, "UTC");
  $end = date_make_date($end, "UTC");
  $timezone = variable_get('date_default_timezone_name', 'UTC');
  date_timezone_set($start, timezone_open($timezone));
  date_timezone_set($end, timezone_open($timezone));

  // Expand our search to the entire day in the users timezone.
  $start_day = date_format($start, 'w');
  $end_day = date_format($end, 'w');
  $start_date = $dates['value']['date'] = date_format($start, 'Y-m-d');
  $dates['value']['time'] = $hours[$start_day]['open'];
  $end_date = $dates['value2']['date'] = date_format($end, 'Y-m-d');
  $dates['value2']['time'] = $hours[$end_day]['close'];

  $dates = merci_convert_date_popup($dates, 'Y-m-d H:i');

  $start_mysql = $dates['value'];
  $end_mysql = $dates['value2'];

  $reservations = merci_load_reservations_for_node_in_timespan($nid, $type, $start_mysql, $end_mysql, $reservation_vid);

  $reservations_by_date = array();

  //for each day we are looking at.
  while ($start_date <= $end_date) {


    $day = date('w', strtotime($start_date));

    // loop through all the items.
    if (!empty($hours[$day])) {
      //$reservations_by_date[$start_date] = array();
      foreach ($reservations as $item => $values) {

        $reservations_by_date[$start_date][$item] = array();

        $time = strtotime($start_date . ' ' . $hours[$day]['open']);
        $close = strtotime($start_date . ' ' . $hours[$day]['close']);

        // all the reservations for that item.
        foreach ($values as $reservation) {

          // Convert to site timezone.
          $tz_start_date = date_make_date($reservation->field_merci_date_value, "UTC");
          $tz_end_date = date_make_date($reservation->field_merci_date_value2, "UTC");
          date_timezone_set($tz_start_date, timezone_open($timezone));
          date_timezone_set($tz_end_date, timezone_open($timezone));
          $tz_start_date = date_format($tz_start_date, "U");
          $tz_end_date = date_format($tz_end_date, "U");

          $tz_start_date = $tz_start_date < $close ? $tz_start_date : $close;
          $tz_end_date   = $tz_end_date < $close ? $tz_end_date : $close;
          if ($tz_end_date <= $time) {
            continue;
          }
          while ($time < $tz_start_date) {
            $reservations_by_date[$start_date][$item][date('H:i', $time)] = array(
              'class' => 'available',
              'data' => '',
            );
            $time += 15 * 60;
          }
          while ($time >= $tz_start_date && $time < $tz_end_date) {
            $reservations_by_date[$start_date][$item][date('H:i', $time)] = array(
              'class' => 'unavailable',
              'data' => $reservation->nid,
            );
            $time += 15 * 60;
          }
          $time = $tz_end_date;
        }
        while ($time < $close) {
          $reservations_by_date[$start_date][$item][date('H:i', $time)] = array(
            'class' => 'available',
            'data' => '',
          );
          $time += 15 * 60;
        }
      }
    }
    $start_date = date('Y-m-d', strtotime($start_date . ' +1 day'));
  }

  $variables['reservations_by_date'] = $reservations_by_date;

  $pretty_hours = array();

  foreach ($reservations_by_date as $date => $values) {
    $day = date('w', strtotime($date));
    $time = $hours[$day]['open'];
    while ($time < $hours[$day]['close']) {
      $pretty_hours[$date][] = date('ga', strtotime($time));
      // Don't overflow to next day.
      if ($time >= '23:00') break;
      $time = date('H:i', strtotime($time . ' +1 hour'));
    }
  }


  $variables['pretty_hours'] = $pretty_hours;
}

function theme_merci_type_setting($element) {
  $element['#description'] = filter_xss(theme('item_list', $element['#description_items']));
  $element['#type'] = 'radios';
  unset($element['#title']);
  return drupal_render($element);
}
/**
 * Theme the reservation form for choices.
 */
function theme_merci_choices($form) {
  // Change the button title to reflect the behavior when using JavaScript.
  //drupal_add_js('if (Drupal.jsEnabled) { $(document).ready(function() { $("#edit-merci-more").val("'. t('Add another item') {  .'"); }); }', 'inline');}

  $output = '';
  $output .= drupal_render($form);
  return $output;
}
/**
 * Builds the reserved items table.
 */
function theme_merci_build_reservation_table_form($form) {

  $output = '';
  $header = $form['#header'];
  $node   = $form['#node'];
  $rows   = array();
  foreach (element_children($form) as $did) {

    if (strstr($did, 'form_')) {
      continue;
    }
    $values = $form[$did];

    $name = drupal_render($values['display_name']);

    if ($values['merci_item_nid']['#type'] == 'value') {
      $item = ($values['display_item_title']['#value']) ? drupal_render($values['display_item_title']) : t('SPECIFIC ITEM NOT SELECTED');
    }
    else {
      $item = drupal_render($values['merci_item_nid']);
    }

    $row = array(
      $item,
      $name,
    );

    foreach ($form['#header'] as $index => $value) {
      if ($value == t('Accessories')) {
        $row[$index] = drupal_render($values['accessories']);
      }
      else if ($value == t('Operations')) {
        $row[$index] = drupal_render($values['ops']);
      }
    }

    $rows[$did] = $row;
  }

  if (!empty($rows)) {
    $table_caption = in_array((int) $node->merci_reservation_status, array(MERCI_STATUS_CHECKED_OUT, MERCI_STATUS_CHECKED_IN)) ? t('Checked out items') : t('Currently reserved items');
    $output .= '<div class="existing-items-table-header">' . $table_caption . '</div>';
    $output .= theme('table', $header, $rows);
  }

  return $output;
}

/**
 * returns the number of items currently checked out for each content type
 * TODO: change this to a views view.
 */
function theme_merci_current_inventory() {

  $header = array(
    t('Item'),
    t('On Hand'),
    t('Unavailable'),
    t('Checked Out'),
    t('Total'),
    t('Operations'),
  );

  $merci_types = merci_content_types();


  $rows   = array();

  foreach ($merci_types as $merci_type) {

    $info = content_types($merci_type['type']);

    $operations = l(t('Edit'), 'admin/content/node-type/' . $info['url_str'], array('query' => array('destination' => 'admin/merci/manage/current_inventory')));
    $operations .= " | ";
    $operations .= l(t('Add Item'), 'node/add/' . $info['url_str'], array('query' => array('destination' => 'admin/merci/manage/current_inventory')));

    $checked_out = merci_get_reservation_count($merci_type['type']);

    $available = merci_get_count($merci_type, MERCI_AVA_F);
    $onhand = $available - $checked_out;

    $unavailable = merci_get_count($merci_type, MERCI_UNA_F);
    $total = $onhand + $unavailable + $checked_out;
    $available = l($onhand, 'admin/merci/manage/current_inventory/' . $info['type'] . '/Available');
    $checked_out = l($checked_out, 'admin/merci/manage/current_inventory/' . $info['type'] . '/checked-out');
    $unavailable = l($unavailable, 'admin/merci/manage/current_inventory/' . $info['type'] . '/Unavailable');

    $title = views_get_view('merci_inventory_view')
        ? l($info['name'], 'admin/merci/manage/inventory', array('html' => TRUE, 'query' => 'merci_content_type=' . $merci_type['type']))
        : $info['name'];

    $rows[] = array(
      $title,
      $available,
      $unavailable,
      $checked_out,
      $total,
      $operations,
    );
  }
  $output = theme('table', $header, $rows);
  $output .= '&raquo; ' . l(t('Add a new content type'), 'admin/content/types/add', array('query' => array('destination' => 'admin/merci/manage/current_inventory')));
  return $output;
}
