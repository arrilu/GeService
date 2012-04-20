<?php
/**
 * Implementation of hook_rules_event_info().
 * @ingroup rules
 */
 /**
 * Evento para validar el perfil
 *
 */
function profile_rules_event_info() {
  return array(
    'validate_profile' => array(
      'label' => t('Valida el profile'),
      'module' => 'profile',
      'arguments' => array(
        'edit' => array('type' => 'node', 'label' => t('Edit.')),
        'category' => array('type' => 'node', 'label' => t('category.')),
		'result' => array('type' => 'node', 'label' => t('category.')),
      ),
    ),
  );
}
?>