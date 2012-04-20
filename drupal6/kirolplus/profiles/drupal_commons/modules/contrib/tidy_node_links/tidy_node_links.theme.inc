<?php

/**
 * @file
 * Theme functions for tidy_node_links
 * Note that the module provides another implementation object oriented and supporting more general use cases.
 * It's limited here to one comment element and one dropdown of the other links
 */

/**
 *
 * @ingroup themeable
 */
function theme_tidy_node_links_element($mapping_name, $mapping_entry, $ref) {
  $output    = '<div class="' . $ref->get_css_class($mapping_entry) . '">';
  $links=$mapping_entry['links'];
  if (isset($links)) {
    $link      = current($links);
    $title_tag = $ref->get_title($mapping_entry, $link);
    $title_tag = strip_tags($title_tag);
    $output .= l($title_tag, $link['href'], $link);
  }
  $output .= '</div>';
  return $output;
}

/**
 *
 * @ingroup themeable
 */
function theme_tidy_node_links_list_start($list_name, $mapping_entry, $ref) {
  $output = '';
  $drop_down_form_name = 'drop_down_form_' . $list_name;
  $drop_down_input_name = 'drop_down_input_' . $list_name;

  //dropdown begin
  $output .= '<div class="' . $ref->get_css_class($mapping_entry) . '">';
  $output .= '<ul class="node_link_style-dropdown">';
  return $output;
}

/**
 *
 * @ingroup themeable
 */
function theme_tidy_node_links_list_end() {
  $output = '';
  //dropdown end
  $output .= '</ul>';
  $output .= '</div>';
  return $output;
}

/**
 *
 * @ingroup themeable
 */
function theme_tidy_node_links_list_item($link_title, $link, $first, $last, $ref) {
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
      $path = $ref->extract_href($link['title']);
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

