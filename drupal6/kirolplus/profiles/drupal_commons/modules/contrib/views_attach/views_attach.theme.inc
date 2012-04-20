<?php
/**
 * @file
 * Preprocess handlers for theme functions
 */

function _template_preprocess_views_attach_display_view(&$vars) {
  template_preprocess_views_view($vars);
  $view = $vars['view'];
  $display = $view->display_handler;
  $vars['title'] = $display->get_option('show_title') ? filter_xss_admin($view->get_title()) : '';
}

function template_preprocess_views_attach_display_node_content_view(&$vars) {
  _template_preprocess_views_attach_display_view($vars);
}

function template_preprocess_views_attach_display_profile_view(&$vars) {
  _template_preprocess_views_attach_display_view($vars);
}
