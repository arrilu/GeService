<?php
// $Id$

/**
 * @file
 * Rules data types, actions, conditions, events (tokens).
 */

# Events

/**
* Implementation of hook_rules_event_info().
* @ingroup rules
*/
function votingpoints_rules_event_info() {
  return array(
    'votingpoints_event' => array(
      'label' => t('User votes to content'),
      'module' => 'Votingpoints',
      'arguments' => array(
        'user' => array('type' => 'user', 'label' => t('User who votes.')),
        'node' => array('type' => 'node', 'label' => t('Node that has been voted on')),
        'vote' => array('type' => 'comment', 'label' => t('The vote itself.')),
      ),
      'redirect' => TRUE,
    ),
  );
}
