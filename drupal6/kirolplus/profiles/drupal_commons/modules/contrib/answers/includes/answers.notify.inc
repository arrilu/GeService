<?php

/**
 * @file
 * Notification functionality for 'Answers' to inform users of answers.
 *
 * @author Chip Cleary
 *
 */

 // Default text for answers notification email.
define('ANSWERS_DEFAULT_NEW_ANSWER_NOTICE_SUBJECT', 'You have a new answer to your question "!question_title"!');

define('ANSWERS_DEFAULT_NEW_ANSWER_NOTICE_BODY', 'Dear !question_user_name,
<br /><br />
You have a new answer to your question: "!question_title".
<br /><br />
To view your answer, <a href="!question_url" target="_blank">click here</a>.
<br />
</p>
<hr>
<p style="font-family: Georgia, sans-serif; font-size: 12px; font-style: italic;  color: #00CC00;">
This is an automatic message from the team at !site.</i>
</p>'); 

/**
 * Pseudo implementation of hook_settings().
 *
 * @see answers_settings()
 */

function _answers_notify_settings() {
  $form = array();

  $form['answers_notification'] = array(
    '#type' => 'fieldset',
    '#description' => t('Settings for the email which is sent to notify a question asker when a new answer is posted (if the asker asks for notification).'),
    '#title' => t('Notification Email Settings'),
  );

  $form['answers_notification']['answers_new_answer_notice_allow_p'] = array(
    '#type' => 'checkbox',
    '#title' => t('Give users the option to be notified'),
    '#default_value' => variable_get('answers_new_answer_notice_allow_p', TRUE),
    '#description' => t('If disabled, users will not be offered the option to receive notifications. Also, any new answers to questions will not trigger notifications, even if their authors had previously requested notification. '),
  );

  $form['answers_notification']['answers_answer_notification_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject line'),
    '#default_value' => variable_get('answers_answer_notification_subject', ANSWERS_DEFAULT_NEW_ANSWER_NOTICE_SUBJECT),
    '#description' => t('Dynamic variables available: !question_user_name, !answer_user_name, !question_title, !question_url, and !site'),
    '#required' => TRUE
  );

  $form['answers_notification']['answers_answer_notification_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Body'),
    '#default_value' => variable_get('answers_answer_notification_body', ANSWERS_DEFAULT_NEW_ANSWER_NOTICE_BODY),
    '#description' => t('Dynamic variables available: !question_user_name, !answer_user_name, !question_title, !question_url, and !site.'),
    '#required' => TRUE
  );

  return $form;
}

/**
 * Pseudo implementation of hook_nodeapi().
 *
 * @see answers_nodeapi()
 */
function _answers_notify_nodeapi(&$node, $op, $teaser) {
  switch ($op) {

    case 'insert':
      // When a new answer is posted, notify the question author if appropriate.
      if ($node->type=='answer' && variable_get('answers_new_answer_notice_allow_p', TRUE)) {
        $question_id = $node->field_answer_question[0]['nid']; // extract the nid of the question
        if ($question_id) {
          answers_notify_new_answer($question_id);
        }
      }
      break;

  }
}

/**
 * If configured to, notify question author of an answer.
 *
 * @param $nid
 *   Numeric node NID of question.
 */
function answers_notify_new_answer($nid) {

  global $user;

  $question = node_load($nid);
  $notify_p = $question->field_notify_p[0]['value'];

  if ($notify_p) {

    $question_user = user_load($question->uid);

    $params = array(
      '!question_user_name'  => $question_user->name,
      '!answer_user_name'    => $user->uid == 0 ? 'anonymous' : $user->name,
      '!question_title'      => $question->title,
      '!question_url'        => url('node/' . $nid, array('absolute' => TRUE, 'target' => '_blank')),
      '!site'                => variable_get('site_name', 'drupal'),
      );

    $language = user_preferred_language($question_user);

    $subject_template = variable_get('answers_answer_notification_subject', ANSWERS_DEFAULT_NEW_ANSWER_NOTICE_SUBJECT);
    $subject = t($subject_template, $params,  $language->language);

    $body_template = variable_get('answers_answer_notification_body', ANSWERS_DEFAULT_NEW_ANSWER_NOTICE_BODY);
    $body = t($body_template, $params,  $language->language);

    $headers['MIME-Version'] = '1.0';
    $headers['Content-Type'] = "text/html";
    $headers['From'] = variable_get('site_mail', ini_get('sendmail_from'));

    $message = array(
      'headers' => $headers,
      'to'      => $question_user->mail,
      'from'    => variable_get('site_mail', ini_get('sendmail_from')),
      'subject' => $subject,
      'body'    => $body,
      );

    drupal_mail_send($message);

  };
}
