<?php

/**
 *
 * @file
 * This file contains the default implementation of tidy_node_links.
 * The CSS file used here is: css/tidy_node_links.css
 * Another implementation can be used instead by extending the same classes.
 *
 */

include_once ('tidy_node_links.api.inc');

/**
 * TidyNodeLinksMappingWithThemeFunctions contains the default configution of tidy_node_links
 * It does the same as with tidy_node_links_default_impl.inc but with limitations: only one single link and only one dropdown.
 *
 * 'Comment' link appears alone on a div floating on the left.
 * All the other links are group in a drop down floating on the right. The first links to appear are notification links.
 * (see get_weight below)
 *
 * When title is specified, it's used instead of default link title.
 *
 *
 */
class TidyNodeLinksMappingWithThemeFunctions implements TidyNodeLinksMapping {
  public function get_mapping() {
    return array(
      'comment_add' => array(
        // replace default title
        'title' => t('Comment'),
        'display_class' => 'TidyNodeLinksElementWithThemeFunctions',
      ),
      'comment_comments' => array(
        // replace default title
        'title' => t('Comment'),
        'display_class' => 'TidyNodeLinksElementWithThemeFunctions',
      ),
    'remaining_links' => array(
        'display_class' => 'TidyNodeLinksListWithThemeFunctions',
      ),
    );
  }
}

/**
 * Theme function version of TidyNodeLinksElement
 * Just an adapter
 */
class TidyNodeLinksElementWithThemeFunctions extends TidyNodeLinksElement {
  public function display($mapping_name, &$mapping_entry) {
    if (!$this->is_visible($mapping_entry)) {
      return '';
    }
    return theme('tidy_node_links_element', $mapping_name, $mapping_entry, $this);
  }
}

/**
 * Theme function version of TidyNodeLinksList
 * Just an adapter
 */
class TidyNodeLinksListWithThemeFunctions extends TidyNodeLinksList {
  public function display_start($list_name, $mapping_entry) {
    return theme('tidy_node_links_list_start', $list_name, $mapping_entry, $this);
  }
  public function display_end() {
    return theme('tidy_node_links_list_end');
  }
  public function display_item($link_title, &$link, $first, $last) {
    return theme('tidy_node_links_list_item', $link_title, $link, $first, $last, $this);
  }
  public function get_weight($link_name) {
    //notification links first
    if (preg_match("/notification/i", $link_name, $matches))
    return - 1;
    return 0;
  }
}

