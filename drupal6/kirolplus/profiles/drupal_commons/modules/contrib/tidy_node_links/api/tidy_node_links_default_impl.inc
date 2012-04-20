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
 * TidyNodeLinksMappingDefault contains the default configution of tidy_node_links
 *
 * 'Comment' link appears alone on a div floating on the left.
 * All the other links are group in a drop down floating on the right. The first links to appear are notification links.
 * (see get_weight below)
 *
 * When title is specified, it's used instead of default link title.
 *
 */
class TidyNodeLinksMappingDefault implements TidyNodeLinksMapping {
  public function get_mapping() {
    return array(
      'comment_add' => array(
        // replace default title
        'title' => t('Comment'),
        'display_class' => 'TidyNodeLinksElementDefault',
      ),
      'comment_comments' => array(
        // replace default title
        'title' => t('Comment'),
        'display_class' => 'TidyNodeLinksElementDefault',
      ),
    'remaining_links' => array(
        'display_class' => 'TidyNodeLinksListDefault',
      ),
    );
  }
}

/**
 *
 * Div implementation for single tag
 * display() method could also be a Drupal theme function.
 *
 */
class TidyNodeLinksElementDefault extends TidyNodeLinksElement {
  public function display($mapping_name, &$mapping_entry) {
    $output    = '<div class="' . $this->get_css_class($mapping_entry) . '">';
    $links=$mapping_entry['links'];
    if (isset($links)) {
      $link      = current($links);
      $title_tag = $this->get_title($mapping_entry, $link);
      $title_tag = strip_tags($title_tag);
      $output .= l($title_tag, $link['href'], $link);
    }
    $output .= '</div>';
    return $output;
  }
}

/**
 *
 * Dropdown implementation of list
 * display() display_end() display_item() methods could also be a Drupal theme functions, but the object oriented aproach is cleaner.
 *
 */
class TidyNodeLinksListDefault extends TidyNodeLinksList {
  public function display_start($list_name, $mapping_entry) {
    $output = '';
    $drop_down_form_name = 'drop_down_form_' . $list_name;
    $drop_down_input_name = 'drop_down_input_' . $list_name;
  
    //dropdown begin
    $output .= '<div class="' . $this->get_css_class($mapping_entry) . '">';
    $output .= '<ul class="node_link_style-dropdown">';
    return $output;
  }
  public function display_end() {
    $output = '';
    //dropdown end
    $output .= '</ul>';
    $output .= '</div>';
    return $output;
  }

  public function display_item($link_title, &$link, $first, $last) {
    $output = '';

    //dropdown
    $title_tag = strip_tags($link_title);
    if ($first) {
      $output .= '<li class="node_link_style-dropdown-main">';
      $title_tag = '<span>' . $title_tag . '</span>';
    }
    else $output .= '<li class="node_link_style-dropdown-item">';

    if (isset($link)) {
      if (isset($link['href'])) {
  
        $output .= l($title_tag, $link['href'], $link);
  
      }
      else {
        //try to extract href from title
        $path = $this->extract_href($link['title']);
        $output .= '<a href="' . $path . '">' . $title_tag . '</a>';
      }
    }

    if (!$first) {


      $output .= '</li>';


    }
    if ($first && !$last) {
      $output .= '<ul>';
    }
    elseif ($last && !$first) {
      $output .= '</ul>';
    }
    if ($last) {
      $output .= '</li>';
    }

    return $output;
  }


  public function get_weight($link_name) {
    //notification links first
    if (preg_match("/notification/i", $link_name, $matches))
    return - 1;
    return 0;
  }
}

