<?php

/**
 *
 * @file
 * This file contains the logic. All the theming code is in tidy_node_links_default_impl.inc
 *
 */

/**
 * This is the first class to instanciate. Then use call set_mapping_class load the configuration:
 * $toolkit = new TidyNodeLinksToolkit();
 * $toolkit->set_mapping_class($config_name);
 * $output = $toolkit->display($links);
 *
 */
class TidyNodeLinksToolkit {
  protected $mapping_class;
  protected $mapping_instance;

  public function set_mapping_class($mapping_class) {
    $this->mapping_class = $mapping_class;
    $this->mapping_instance = new $mapping_class;
  }

  /**
   *
   *
   * @param $links
   *
   * @return
   * HTML output
   */
  public function display($links) {
    $mapping = $this->mapping_instance->get_mapping();
    //selects the links according to mapping
    foreach ($links as $key => $link) {
      $entry_name = $key;
      if (!isset($mapping[$entry_name])) {
        $entry_name = 'remaining_links';
      }
      $mapping[$entry_name]['links'][$key] = $link;
    }

    //apply display classes
    $output = '';
    foreach ($mapping as $name => $value) {
      if (isset($value['links'])) { //if matching link found
        $display_object = new $value['display_class'];
        $output .= $display_object->display($key, $value);
      }
    }
    return $output;
  }
}

interface TidyNodeLinksMapping {
  public function get_mapping();
}


abstract class TidyNodeLinksElement {
  public abstract function display($mapping_name, &$mapping_entry);

  /**
   * Utility method. Extracts href
   *
   * @param html
   **/
  public function extract_href($s) {
    $s = strip_tags($s, '<a>');
    $matches = array();
    if (preg_match("/href=\"(.*?)\"/i", $s, $matches)) {
      return $matches[1];
    }
    return $s;
  }

  /**
   * Extracts change link title
   *
   * @param html
   **/
  function get_title(&$mapping_entry, &$link) {
    $link_name = $mapping_entry['title'];
    if (!isset($link_name)) {
      $link_name = $link['title'];
    }
    return $link_name;
  }
  
  /**
  * get CSS style if defined
  *
  * @param html
  **/
  function get_css_class(&$mapping_entry) {
    $css_class = $mapping_entry['css_class'];
    if (!isset($css_class)) {
      $css_class='comment_clear_style';
    }
    return $css_class;
  }
  
  /**
  * default TRUE
  *
  * @param html
  **/
  function is_visible(&$mapping_entry) {
    return !(isset($mapping_entry['visible']) && $mapping_entry['visible']==FALSE);
    
  }
  
}

abstract class TidyNodeLinksList extends TidyNodeLinksElement{

/**
 *
 * @return
 *   tags
 */
public function display($mapping_name, &$mapping_entry) {
  //first sort using weight method
  uksort($mapping_entry['links'], array($this, 'order_links'));
  //then display
  $output = $this->display_start($mapping_name, $mapping_entry);

  $i           = 0;
  $links       = $mapping_entry['links'];
  $links_count = count($links);
  foreach ($links as $key => $link) {
    $output .= $this->display_item($this->get_title($mapping_entry, $link), $link, $i == 0, $i == (len - 1));
    $i++;
    }$output .= $this->display_end();
    return $output;
  }

  // I'm not using closures for compatibility with PHP<5.3
  private function order_links($l1, $l2) {
    $w1 = $this->get_weight($l1);
    $w2 = $this->get_weight($l2);
    if ($w1 == $w2) {
      return 0;
    }
    return ($w1 < $w2) ? -1 : 1;
  }
  
  /**
  * get CSS style if defined
  *
  * @param html
  **/
  function get_css_class(&$mapping_entry) {
    $css_class = $mapping_entry['css_class'];
    if (!isset($css_class)) {
      $css_class='subscription_clear_style';
    }
    return $css_class;
  }
  

  /**
   *
   * @return
   *   dropdown tags - start
   */
  public abstract function display_start($list_name, $mapping_entry);

  /**
   *
   * @return
   * 	dropdown tags - end
   */
  public abstract function display_end();

  /**
   *
   * @return
   * 	dropdown tags - item
   */
  public abstract function display_item($link_name, &$link, $first, $last);
}

