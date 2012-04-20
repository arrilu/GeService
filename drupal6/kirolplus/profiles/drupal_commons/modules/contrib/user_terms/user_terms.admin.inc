<?php

/**
 * @file
 *   Provides admin pages for the module.
 */

/**
 * The admin form for choosing the vocabulary to associate users with.
 *
 * @return array
 *   The form elements.
 */
function user_terms_settings() {
  drupal_add_js(drupal_get_path('module', 'user_terms') . '/user_terms.js', 'module');
  $form = array();
  $vocabs = taxonomy_get_vocabularies();
  $vocabs_enabled   = variable_get('user_terms_vocabs', array());
  $vocabs_path      = variable_get('user_terms_vocabs_path', array());
  $vocabs_register  = variable_get('user_terms_vocabs_register', array());

  $profile_exists = module_exists('profile');

  if ($profile_exists) {
    $categories = profile_categories();
    $category_options = array(
      'account' => t('Account (main page)'),
    );
    foreach ($categories as $cat) {
      // Profile categories have no machine name; title and name fields are
      // identical. We can't use the index as their order may change.
      $category_options[$cat['name']] = $cat['name'];
    }
  }

  foreach ($vocabs as $vid => $voc) {
    $form['vocabularies'][$vid]['name'] = array('#value' => check_plain($voc->name));
    $form['vocabularies'][$vid]['enabled'] = array(
      '#type'           => 'checkbox', 
      '#default_value'  => isset($vocabs_enabled[$vid]), 
      '#attributes'     => array('class' => 'enabled'),
    );
    // Only add this option if the profile module is enabled.
    if ($profile_exists) {
      $form['vocabularies'][$vid]['category'] = array(
        '#type' => 'select', 
        '#options' => $category_options,
        '#default_value' => isset($vocabs_path[$vid]) ? $vocabs_path[$vid] : 'account',
      );
    }
    $form['vocabularies'][$vid]['registration'] = array(
      '#type'           => 'checkbox',
      '#default_value'  => isset($vocabs_register[$vid]),
      '#attributes'     => array('class' => 'registration'),
    );
  } 
  $form['vocabularies']['#tree'] = TRUE;
  $form['vocabularies']['#theme'] = 'user_terms_settings';
  
  $form['user_terms_group'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Group terms'),
    '#collapsible'  => FALSE,
  );

    $form['user_terms_group']['user_terms_group_terms'] = array(
      '#type'           => 'checkbox',
      '#title'          => t('Group terms'),
      '#default_value'  => variable_get('user_terms_group_terms', FALSE),
      '#description'    => t('Show all terms from all vocabularies under a single heading, rather than one heading per vocabulary.'),
    );

    $form['user_terms_group']['user_terms_group_title'] = array(
      '#type'           => 'textfield',
      '#title'          => t('Grouped terms heading'),
      '#default_value'  => variable_get('user_terms_group_title', USER_TERMS_GROUP_TITLE),
      '#description'    => t('The text to use as a heading when all terms are grouped.'),
      '#size'           => 32,
    );

  // Add our own submit handler to process the table. 
  $form['#submit'] = array('user_terms_settings_submit');

  return system_settings_form($form);
}

/**
 * Theme the admin settings form.
 *
 * @ingroup themeable
 * @see user_terms_settings()
 */
function theme_user_terms_settings($form) {
  $profile_exists = module_exists('profile');

  $rows = array();
  foreach (element_children($form) as $key) {
    $field = &$form[$key];

    $row = array();
    $row[] = drupal_render($field['name']);
    $row[] = drupal_render($field['enabled']);
    if ($profile_exists) {
      $row[] = drupal_render($field['category']);
    }
    $row[] = drupal_render($field['registration']);

    $rows[] = $row;
  }

  if (empty($rows)) {
    $rows[] = array(array('data' => t('No vocabularies available.'), 'colspan' => 3));
  }

  $header[] = t('Vocabulary'); 
  $header[] = t('Enabled'); 
  if ($profile_exists) {
    $header[] = t('Profile category');
  }
  $header[] = t('Use on registration'); 

  $output = theme('table', $header, $rows, array('id' => 'user-terms-fields'));
  $output .= drupal_render($form);

  return $output;
}

/**
 * Submit handler for the admin settings form.
 *
 * Handles the table of vocabularies.
 * Other settings that are simple elements are saved by system_settings_form()'s
 * system_settings_form_submit handler.
 */
function user_terms_settings_submit($form, &$form_state) {
  // Save the enabled vocabularies.
  $user_terms_vocabs = array();
  foreach ($form_state['values']['vocabularies'] as $vid => $vocab_values) {
    // Enabled vocabularies.
    if ($vocab_values['enabled']) {
      $user_terms_vocabs[$vid] = $vid;
    }
    // Registration vocabularies.
    if ($vocab_values['registration']) {
      $user_terms_vocabs_register[$vid] = $vid;
    }
    // Vocabulary categories.
    if (isset($vocab_values['category'])) {
      $user_terms_vocabs_path[$vid] = $vocab_values['category'];
    }
    elseif ($vocab_values['enabled']) {
      // There was no 'category' form item because profile module is not present
      // so set the path to 'account' if the vocab is enabled.
      $user_terms_vocabs_path[$vid] = 'account';
    }
  }
  variable_set('user_terms_vocabs', $user_terms_vocabs);
  variable_set('user_terms_vocabs_register', $user_terms_vocabs_register);
  
  variable_set('user_terms_vocabs_path', $user_terms_vocabs_path);

  // Remove the form values so system_settings_form_submit() doesn't save them.
  unset($form_state['values']['vocabularies']);
}
