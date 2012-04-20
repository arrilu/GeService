<?php

/**
 * @file
 * Up Down Widget.
 */

$path = drupal_get_path('module', 'vud');
drupal_add_js("$path/widgets/thumbs_up_down/thumbs_up_down.js");

/**
 * Implementation of hook_vud_widgets(). (Specialized)
 */
function vud_thumbs_up_down_vud_widgets() {
  return array(
    'title' => t('Thumbs up and down'),
    'widget template' => 'widget',
    'alter template variables' => 'vud_widget_thumbs_up_down_alter_template_vars',
  );
}

function vud_widget_thumbs_up_down_alter_template_vars($template_type, &$variables) {
  $criteria['content_id'] = $variables['content_id'];
  $criteria['content_type'] = $variables['type'];
  $criteria['value_type'] = 'points';
  $criteria['function']  = 'sum';
  $vote_sum = votingapi_select_single_result_value($criteria);
  $variables['vote_sum'] = $vote_sum;
}
