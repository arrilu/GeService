<?php

/**
 * @file
 * Rules integration with the button_field module.
 */

/**
 * Implementation of hook_rules_action_info().
 * 
 * @return array
 */
function button_field_rules_action_info() {
  $items['button_field_action_reload'] = array(
    'label' => t('Refresh page.'),
    'module' => 'Button Field',
  ); // end $items['button_field_action_reload']
  
  return $items;
} // end function button_field_rules_action_info()

/**
 * Implementation of hook_rules_condition_info().
 * 
 * @return array
 * 
 * @todo find out how to pass the field as an argument
 */
function button_field_rules_condition_info() {
  $items['button_field_condition_button_is'] = array(
    'label' => t('Button is'),
    'module' => 'Button Field',
    'arguments' => array(
      'button_name' => array(
        'type' => 'string',
        'label' => t('Field name of the button'),
      ),
    ),
  ); // end $items['button_field_condition_button_is']
  
  return $items;
} // end function button_field_rules_condision_info()

/**
 * Implementation of hook_rules_event_info().
 * 
 * @return array
 * 
 * @todo find out how to pass the field as an argument
 */
function button_field_rules_event_info() {
  $items['button_field_clicked'] = array(
    'label' => t('Users Clicks a Button'),
    'module' => 'Button Field',
    'arguments' => array(
      'node' => array(
          'type' => 'node',
          'label' => t('Node that the button was on')
      ),
      'user' => array(
        'type' => 'user',
        'label' => t('Currently logged in user'),
      ),
    ),
  ); // end $items['button_field_clicked']
  
  return $items;
} // end function button_field_rules_event_info()

/**
 * Reloads the current page.
 */
function button_field_action_reload() {
  // redirect to the current page
  $_REQUEST['destination'] = $_REQUEST['path'];
  
  return TRUE;
} // end function button_field_action_reload()

/**
 * Compares the field name of the button that was clicked to the field name
 * that was expected.
 * 
 * @param string $button_name
 * @return boolean
 */
function button_field_condition_button_is($button_name, $arguemnts, $settings,
  $variables) {
  $id = $_REQUEST['id'];
  list($field_name, $nid) = explode('-', $id);
  
  return ($button_name == $field_name);
} // end function button_field_condition_button_is()
