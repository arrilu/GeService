<?php
// $Id: views_plugin_argument_validate_node.inc,v 1.2 2009/06/10 22:04:57 merlinofchaos Exp $
/**
 * @file
 * Contains the 'node' argument validator plugin.
 */

/**
 * Validate whether an argument is an acceptable node.
 */
class views_plugin_argument_validate_merci_node extends views_plugin_argument_validate {
  var $option_name = 'validate_argument_merci_type';

  function validate_form(&$form, &$form_state) {
    $options  = array(
      'disabled' => t('Disabled'),
      'bucket' => t('Bucket'),
      'resource' => t('Resource'),
    );


    $arg = $this->get_argument();
    if (empty($arg)) {
      $arg = array();
    }

    $form[$this->option_name] = array(
      '#type' => 'checkboxes',
      '#prefix' => '<div id="edit-options-validate-argument-merci-type-wrapper">',
      '#suffix' => '</div>',
      '#title' => t('Types'),
      '#options' => $options,
      '#default_value' => $arg,
      '#description' => t('If you wish to validate for specific node types, check them; if none are checked, all nodes will pass.'),
      '#process' => array('expand_checkboxes', 'views_process_dependency'),
      '#dependency' => array('edit-options-validate-type' => array($this->id)),
    );

    $form['validate_argument_merci_sub_type'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Argument type'),
      '#prefix' => '<div id="edit-options-validate-argument-merci-sub-type-wrapper">',
      '#suffix' => '</div>',
      '#options' => array(
        1 => "MERCI Item",
        2 => "MERCI Reservaton Item",
      ),
      '#default_value' => isset($this->argument->options['validate_argument_merci_sub_type']) ? $this->argument->options['validate_argument_merci_sub_type'] : array(),
      '#description' => t('If you wish to validate for specific node types, check them; if none are checked, all nodes will pass.'),
      '#process' => array('expand_checkboxes', 'views_process_dependency'),
      '#dependency' => array('edit-options-validate-type' => array($this->id)),
    );
  }
  function validate_argument($argument) {

    $node = node_load($argument);

    $types = array_filter($this->argument->options[$this->option_name]);

    $sub_types = array_filter($this->argument->options['validate_argument_merci_sub_type']);

    if (!isset($types[$node->merci_type_setting])) {
      return FALSE;
    }

    if (!isset($sub_types[$node->merci_sub_type])) {
      return FALSE;
    }

    return TRUE;
  }
}

