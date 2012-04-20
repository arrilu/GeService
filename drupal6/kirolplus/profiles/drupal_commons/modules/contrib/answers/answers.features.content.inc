<?php

/**
 * Implementation of hook_content_default_fields().
 */
function answers_content_default_fields() {
  $fields = array();

  // Exported field: field_answer_question
  $fields['answer-field_answer_question'] = array(
    'field_name' => 'field_answer_question',
    'type_name' => 'answer',
    'display_settings' => array(
      'weight' => '4',
      'parent' => '',
      'label' => array(
        'format' => 'inline',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference',
    'required' => '1',
    'multiple' => '0',
    'module' => 'nodereference',
    'active' => '1',
    'referenceable_types' => array(
      'question' => 'question',
      'answer' => 0,
      'assessment' => 0,
      'blog' => 0,
      'chip_test' => 0,
      'forum' => 0,
      'other_resource' => 0,
      'page' => 0,
      'poll' => 0,
      'quotation' => 0,
      'story' => 0,
      'tool' => 0,
      'training' => 0,
      'video' => 0,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'node_link' => array(
        'teaser' => 0,
        'full' => 1,
        'title' => 'Post an answer',
        'hover_title' => 'Answer this question',
        'destination' => 'node',
      ),
      'fallback' => 'page_not_found',
      'edit_fallback' => 0,
      'label' => 'Answer to the question',
      'weight' => '4',
      'description' => '',
      'type' => 'nodereference_url',
      'module' => 'nodereference_url',
    ),
  );

  // Exported field: field_answer_count
  $fields['question-field_answer_count'] = array(
    'field_name' => 'field_answer_count',
    'type_name' => 'question',
    'display_settings' => array(
      'weight' => '4',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'nodereference_count',
    'required' => '0',
    'multiple' => '0',
    'module' => 'nodereference_count',
    'active' => '1',
    'referenceable_fields' => array(
      'field_answer_question' => 'field_answer_question',
    ),
    'widget' => array(
      'default_value' => NULL,
      'default_value_php' => NULL,
      'label' => 'Answer Count',
      'weight' => '4',
      'description' => '',
      'type' => 'nodereference_count_widget',
      'module' => 'nodereference_count',
    ),
  );

  // Exported field: field_notify_p
  $fields['question-field_notify_p'] = array(
    'field_name' => 'field_notify_p',
    'type_name' => 'question',
    'display_settings' => array(
      'weight' => '-3',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'number_integer',
    'required' => '1',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => '',
    'min' => '',
    'max' => '',
    'allowed_values' => '0 | No
1 | Yes
',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '0 ',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Notify on Answer',
      'weight' => '-3',
      'description' => 'Would you like to receive notifications by email when users post answers to your question?',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_question_locked_p
  $fields['question-field_question_locked_p'] = array(
    'field_name' => 'field_question_locked_p',
    'type_name' => 'question',
    'display_settings' => array(
      'weight' => '6',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'number_integer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => '',
    'min' => '',
    'max' => '',
    'allowed_values' => '0 | No
1 | Yes',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Question Locked',
      'weight' => '6',
      'description' => '',
      'type' => 'optionwidgets_buttons',
      'module' => 'optionwidgets',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Answer Count');
  t('Answer to the question');
  t('Notify on Answer');
  t('Question Locked');

  return $fields;
}
