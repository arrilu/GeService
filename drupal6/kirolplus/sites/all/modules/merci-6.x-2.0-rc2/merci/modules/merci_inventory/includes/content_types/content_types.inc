<?php

/**
 * @file
 * merci inventory content types
 */


/**
 * function to create CCK content types
 */
function _merci_inventory_install_create_content_types() {

  // in order to create CCK content types, we use the form-based content_copy import/export functionality

  //Load existing content_types so we're not trying to recreate something that already exists
  $content_info = _content_type_info();

  // create om_timeslot_theme content type
  if (!in_array('merci_inventory_master', array_keys($content_info['content types']))) {
    module_load_include('inc', 'merci_inventory', 'includes/content_types/merci_inventory_master_content_type');
    _merci_inventory_install_create_merci_inventory_master_content_type();
  }


  return;
}
// function _merci_create_content_types

/**
 * function to import a new content type using CCK import functionality
 */
function _merci_inventory_install_import_content_type($macro) {
  $form_state = array();
  $form = content_copy_import_form($form_state);
  $form_state['values']['type_name'] = 'merci_inventory_master';
  $form_state['values']['macro'] = $macro;
  return content_copy_import_form_submit($form, $form_state);
}
// function _om_project_install_import_content_type

