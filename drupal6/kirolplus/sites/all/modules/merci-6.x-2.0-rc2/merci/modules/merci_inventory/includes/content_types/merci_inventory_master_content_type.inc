<?php

/**
 * @file
 * merci inventory content types installation
 */


/**
 * function to create Open Media Timeslot Theme CCK content type
 */
function _merci_inventory_install_create_merci_inventory_master_content_type() {

  $result = _merci_inventory_install_import_content_type("\$content[type]  = array (
  'name' => 'MERCI Inventory Master',
  'type' => 'merci_inventory_master',
  'description' => '',
  'title_label' => 'Title',
  'body_label' => 'Body',
  'min_word_count' => '0',
  'help' => '',
  'node_options' =>
  array (
    'status' => true,
    'promote' => false,
    'sticky' => false,
    'revision' => false,
  ),
  'creativecommons' => 0,
  'old_type' => 'merci_inventory_master',
  'orig_type' => '',
  'module' => 'node',
  'custom' => '1',
  'modified' => '1',
  'locked' => '0',
  'og_content_type_usage' => 'omitted',
  'comment' => '0',
  'comment_default_mode' => '4',
  'comment_default_order' => '1',
  'comment_default_per_page' => '50',
  'comment_controls' => '3',
  'comment_anonymous' => 0,
  'comment_subject_field' => '1',
  'comment_preview' => '1',
  'comment_form_location' => '0',
  'merci_type_setting' => 'disabled',
  'merci_reservation_status' => 1,
  'merci_spare_items' => 0,
  'merci_grouping' => 0,
  'merci_max_hours_per_reservation' => 0,
  'merci_allow_overnight' => 0,
  'merci_allow_weekends' => 0,
  'merci_rate_per_hour' => 0,
  'merci_late_fee_per_hour' => 0,
  'merci_fee_free_hours' => 0,
  'merci_min_cancel_hours' => 0,
  'merci_autocheckout' => 0,
  'merci_autocheckin' => 0,
  'merci_selfcheckout' => 0,
  'ant' => '0',
  'ant_pattern' => '',
  'ant_php' => 0,
);
\$content[groups]  = array (
  0 =>
  array (
    'label' => 'MERCI Inventory',
    'group_type' => 'standard',
    'settings' =>
    array (
      'form' =>
      array (
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' =>
      array (
        'description' => '',
        'teaser' =>
        array (
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' =>
        array (
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        4 =>
        array (
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' =>
        array (
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '-2',
    'group_name' => 'group_merci_inventory',
  ),
);
\$content[fields]  = array (
  0 =>
  array (
    'label' => 'Model',
    'field_name' => 'field_merci_model',
    'type' => 'text',
    'widget_type' => 'text_textfield',
    'change' => 'Change basic information',
    'weight' => '-1',
    'rows' => 5,
    'size' => '60',
    'description' => '',
    'default_value' =>
    array (
      0 =>
      array (
        'value' => '',
        '_error_element' => 'default_value_widget][field_merci_model][0][value',
      ),
    ),
    'default_value_php' => '',
    'default_value_widget' => NULL,
    'group' => 'group_merci_inventory',
    'required' => 0,
    'multiple' => '0',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'op' => 'Save field settings',
    'module' => 'text',
    'widget_module' => 'text',
    'columns' =>
    array (
      'value' =>
      array (
        'type' => 'text',
        'size' => 'big',
        'not null' => false,
        'sortable' => true,
      ),
    ),
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      4 =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
  ),
  1 =>
  array (
    'label' => 'Make',
    'field_name' => 'field_merci_make',
    'type' => 'text',
    'widget_type' => 'text_textfield',
    'change' => 'Change basic information',
    'weight' => 0,
    'rows' => 5,
    'size' => '60',
    'description' => '',
    'default_value' =>
    array (
      0 =>
      array (
        'value' => '',
        '_error_element' => 'default_value_widget][field_merci_make][0][value',
      ),
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_merci_make' =>
      array (
        0 =>
        array (
          'value' => '',
          '_error_element' => 'default_value_widget][field_merci_make][0][value',
        ),
      ),
    ),
    'group' => 'group_merci_inventory',
    'required' => 0,
    'multiple' => '0',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'op' => 'Save field settings',
    'module' => 'text',
    'widget_module' => 'text',
    'columns' =>
    array (
      'value' =>
      array (
        'type' => 'text',
        'size' => 'big',
        'not null' => false,
        'sortable' => true,
      ),
    ),
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      4 =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
  ),
  2 =>
  array (
    'label' => 'Serial Number',
    'field_name' => 'field_merci_serial_number',
    'type' => 'text',
    'widget_type' => 'text_textfield',
    'change' => 'Change basic information',
    'weight' => '1',
    'rows' => 5,
    'size' => '60',
    'description' => '',
    'default_value' =>
    array (
      0 =>
      array (
        'value' => '',
        '_error_element' => 'default_value_widget][field_merci_serial_number][0][value',
      ),
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_merci_serial_number' =>
      array (
        0 =>
        array (
          'value' => '',
          '_error_element' => 'default_value_widget][field_merci_serial_number][0][value',
        ),
      ),
    ),
    'group' => 'group_merci_inventory',
    'required' => 0,
    'multiple' => '0',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'op' => 'Save field settings',
    'module' => 'text',
    'widget_module' => 'text',
    'columns' =>
    array (
      'value' =>
      array (
        'type' => 'text',
        'size' => 'big',
        'not null' => false,
        'sortable' => true,
      ),
    ),
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      4 =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
  ),
  3 =>
  array (
    'label' => 'Inventory Code',
    'field_name' => 'field_merci_inventory_code',
    'type' => 'text',
    'widget_type' => 'text_textfield',
    'change' => 'Change basic information',
    'weight' => '2',
    'rows' => 5,
    'size' => '60',
    'description' => '',
    'default_value' =>
    array (
      0 =>
      array (
        'value' => '',
        '_error_element' => 'default_value_widget][field_merci_inventory_code][0][value',
      ),
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_merci_inventory_code' =>
      array (
        0 =>
        array (
          'value' => '',
          '_error_element' => 'default_value_widget][field_merci_inventory_code][0][value',
        ),
      ),
    ),
    'group' => 'group_merci_inventory',
    'required' => 0,
    'multiple' => '0',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'op' => 'Save field settings',
    'module' => 'text',
    'widget_module' => 'text',
    'columns' =>
    array (
      'value' =>
      array (
        'type' => 'text',
        'size' => 'big',
        'not null' => false,
        'sortable' => true,
      ),
    ),
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      4 =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
  ),
  4 =>
  array (
    'label' => 'Warranty',
    'field_name' => 'field_merci_warranty',
    'type' => 'text',
    'widget_type' => 'text_textfield',
    'change' => 'Change basic information',
    'weight' => '3',
    'rows' => 5,
    'size' => '60',
    'description' => '',
    'default_value' =>
    array (
      0 =>
      array (
        'value' => '',
        '_error_element' => 'default_value_widget][field_merci_warranty][0][value',
      ),
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_merci_warranty' =>
      array (
        0 =>
        array (
          'value' => '',
          '_error_element' => 'default_value_widget][field_merci_warranty][0][value',
        ),
      ),
    ),
    'group' => 'group_merci_inventory',
    'required' => 0,
    'multiple' => '0',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'op' => 'Save field settings',
    'module' => 'text',
    'widget_module' => 'text',
    'columns' =>
    array (
      'value' =>
      array (
        'type' => 'text',
        'size' => 'big',
        'not null' => false,
        'sortable' => true,
      ),
    ),
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      4 =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
  ),
);
\$content[extra]  = array (
  'title' => '-5',
  'body_field' => '-3',
  'menu' => '-4',
);
");

  return;
}
// function _merci_inventory_install_create_merci_inventory_master_content_type

