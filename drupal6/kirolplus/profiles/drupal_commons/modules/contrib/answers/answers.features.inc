<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function answers_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function answers_node_info() {
  $items = array(
    'answer' => array(
      'name' => t('Answer'),
      'module' => 'features',
      'description' => t('An answer provided to a member of the community to a question'),
      'has_title' => '1',
      'title_label' => t('Answer'),
      'has_body' => '1',
      'body_label' => t('Description'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'question' => array(
      'name' => t('Question'),
      'module' => 'features',
      'description' => t('A question asked by a member of the community'),
      'has_title' => '1',
      'title_label' => t('Question'),
      'has_body' => '1',
      'body_label' => t('Description'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function answers_views_api() {
  return array(
    'api' => '2',
  );
}
