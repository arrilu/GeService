<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function answers_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: navigation:node/add/answer
  $menu_links['navigation:node/add/answer'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'node/add/answer',
    'router_path' => 'node/add/answer',
    'link_title' => 'Answer',
    'options' => array(
      'attributes' => array(
        'title' => 'An answer provided to a member of the community to a question',
      ),
    ),
    'module' => 'system',
    'hidden' => '-1',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
    'parent_path' => 'node/add',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Answer');


  return $menu_links;
}
