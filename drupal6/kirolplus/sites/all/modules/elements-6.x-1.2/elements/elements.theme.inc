<?php

/**
 * @file
 * The theme include file for the elements module.
 *
 * Contains the theme functions for all the elements module elements.
 */

/**
 * Returns HTML for a table with radio buttons or checkboxes.
 *
 * An example of per-row options:
 * @code
 * $options = array();
 * $options[0]['title'] = "A red row"
 * $options[0]['#attributes'] = array ('class' => array('red-row'));
 * $options[1]['title'] = "A blue row"
 * $options[1]['#attributes'] = array ('class' => array('blue-row'));
 *
 * $form['myselector'] = array (
 * '#type' => 'tableselect',
 * '#title' => 'My Selector'
 * '#options' => $options,
 * );
 * @endcode
 *
 * @param $element
 *   An associative array containing the properties and children of the
 *   tableselect element. Properties used: #header, #options, #empty, and
 *   #js_select. The #options property is an array of selection options; each
 *   array element of #options is an array of properties. These properties can
 *   include #attributes, which is added to the table row's HTML attributes;
 *   see theme_table().
 *
 * @ingroup themeable
 */
function theme_tableselect($element) {
  $rows = array();
  $header = $element['#header'];
  if (!empty($element['#options'])) {
    // Generate a table row for each selectable item in #options.
    foreach (element_children($element) as $key) {
      $row = array();

      $row['data'] = array();
      if (isset($element['#options'][$key]['#attributes'])) {
        $row += $element['#options'][$key]['#attributes'];
      }

      // Render the checkbox / radio element.
      $element[$key]['#printed'] = NULL;  // Drupal 6 only
      $row['data'][] = drupal_render($element[$key]);

      // As theme_table only maps header and row columns by order, create the
      // correct order by iterating over the header fields.
      foreach ($element['#header'] as $fieldname => $title) {
        $row['data'][] = $element['#options'][$key][$fieldname];
      }
      $rows[] = $row;
    }
    // Add an empty header or a "Select all" checkbox to provide room for the
    // checkboxes/radios in the first table column.
    if ($element['#js_select']) {
      // Add a "Select all" checkbox.
      //drupal_add_js('misc/tableselect.js');
      //array_unshift($header, array('class' => 'select-all'));
      array_unshift($header, theme('table_select_header_cell')); // Drupal 6 only
    }
    else {
      // Add an empty header when radio buttons are displayed or a "Select all"
      // checkbox is not desired.
      array_unshift($header, '');
    }
  }

  // Add the 'empty' row message if available.
  if (!count($rows) && $element['#empty']) {
    $header_count = 0;
    foreach ($header as $header_cell) {
      if (is_array($header_cell)) {
        $header_count += isset($header_cell['colspan']) ? $header_cell['colspan'] : 1;
      }
      else {
        $header_count++;
      }
    }
    $rows[] = array(array(
      'data' => $element['#empty'],
      'colspan' => $header_count,
      'class' => 'empty message',
    ));
  }

  return theme('table', $header, $rows, $element['#attributes']);
}

/**
 * Wrapper for theming a form element to add field prefix and suffix support.
 */
function _elements_theme_form_element_wrapper($element, $output) {
  if (isset($element['#field_prefix'])) {
    $output = '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' . $output;
  }

  if (isset($element['#field_suffix'])) {
    $output .= ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>';
  }

  return theme('form_element', $element, $output);
}

/**
 * Returns HTML for an emailfield form element.
 *
 * @param $element
 *   An associative array containing the properties of the element.
 *   Properties used: #title, #value, #description, #size, #maxlength,
 *   #required, #placeholder, #attributes, #autocomplete_path.
 *
 * @ingroup themeable
 */
function theme_emailfield($element) {
  $element['#attributes']['type'] = 'email';
  element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength', 'placeholder'));
  _form_set_class($element, array('form-text', 'form-email'));

  $extra = elements_add_autocomplete($element);
  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';

  $output = _elements_theme_form_element_wrapper($element, $output . $extra);
  return $output;
}

/**
 * Returns HTML for a searchfield form element.
 *
 * @param $element
 *   An associative array containing the properties of the element.
 *   Properties used: #title, #value, #description, #size, #maxlength,
 *   #required, #placeholder, #attributes, #autocomplete_path.
 *
 * @ingroup themeable
 */
function theme_searchfield($element) {
  $element['#attributes']['type'] = 'search';
  element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength', 'placeholder'));
  _form_set_class($element, array('form-text', 'form-search'));

  $extra = elements_add_autocomplete($element);
  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';

  $output = _elements_theme_form_element_wrapper($element, $output . $extra);
  return $output;
}

/**
 * Returns HTML for a telfield form element.
 *
 * @param $element
 *   An associative array containing the properties of the element.
 *   Properties used: #title, #value, #description, #size, #maxlength,
 *   #required, #placeholder, #attributes.
 *
 * @ingroup themeable
 */
function theme_telfield($element) {
  $element['#attributes']['type'] = 'tel';
  element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength', 'placeholder'));
  _form_set_class($element, array('form-text', 'form-tel'));

  $extra = elements_add_autocomplete($element);
  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';

  $output = _elements_theme_form_element_wrapper($element, $output . $extra);
  return $output;
}

/**
 * Returns HTML for an urlfield form element.
 *
 * @param $element
 *   An associative array containing the properties of the element.
 *   Properties used: #title, #value, #description, #size, #maxlength,
 *   #required, #placeholder, #attributes, #autocomplete_path.
 *
 * @ingroup themeable
 */
function theme_urlfield($element) {
  $element['#attributes']['type'] = 'url';
  element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength', 'placeholder'));
  _form_set_class($element, array('form-text', 'form-url'));

  $extra = elements_add_autocomplete($element);
  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';

  $output = _elements_theme_form_element_wrapper($element, $output . $extra);
  return $output;
}

/**
 * Returns HTML for a numberfield form element.
 *
 * @param $element
 *   An associative array containing the properties of the element.
 *   Properties used: #title, #value, #description, #size, #maxlength,
 *   #placeholder, #min, #max, #step, #required, #attributes.
 *
 * @ingroup themeable
 */
function theme_numberfield($element) {
  $element['#attributes']['type'] = 'number';
  element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength', 'placeholder', 'min', 'max', 'step'));
  _form_set_class($element, array('form-text', 'form-number'));

  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';

  $output = _elements_theme_form_element_wrapper($element, $output);
  return $output;
}

/**
 * Returns HTML for a rangefield form element.
 *
 * @param $element
 *   An associative array containing the properties of the element.
 *   Properties used: #title, #value, #description, #size, #maxlength,
 *   #placeholder, #min, #max, #step, #required, #attributes.
 *
 * @ingroup themeable
 */
function theme_rangefield($element) {
  $element['#attributes']['type'] = 'range';
  element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength', 'placeholder', 'min', 'max', 'step'));
  _form_set_class($element, array('form-text', 'form-range'));

  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';

  $output = _elements_theme_form_element_wrapper($element, $output);
  return $output;
}
