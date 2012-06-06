<?php
// reservasresource.inc

/**
* Callback for creating reservas resources.
*
* @param object $data
* @return object
*/
function _reservasresource_create($data) {
	global $user;

	unset($data->nid);
	$data->uid = $user->uid;
	$data->created = time();
	$data->modified = time();

	if (!isset($data->merci_reservation_status)) {
		return services_error('Missing reservas attribute status', 406);
	}


	reservasresource_write_reservas($data);
	return (object)array(
		'nid' => $data->nid,
		'uri' => services_resource_uri(array('merci_reservation', $data->nid)),
	);
}

/**
* Callback for updating note resources.
*
* @param int $nid
* @param object $data
* @return object
*/
function _reservasresource_update($nid, $data) {
	global $user;
	$note = reservasresource_get_reservas($nid);

	unset($data->created);
	$data->nid = $nid;
	$data->uid = $note->uid;
	$data->modified = time();

	reservasresource_write_reservas($data);
	return (object)array(
		'nid' => $nid,
		'uri' => services_resource_uri(array('merci_reservation', $nid)),
	);
}

/**
* Callback for retrieving reservas resources.
*
* @param int $nid
* @return object
*/
function _reservasresource_retrieve($nid) {
	return reservasresource_get_reservas($nid);
}

/**
* Callback for deleting reservas resources.
*
* @param int $nid
* @return object
*/
function _reservasresource_delete($nid) {
	reservasresource_delete_reservas($nid);
	return (object)array(
		'nid' => $nid,
	);
}

/**
* Callback for listing notes.
*
* @param int $page
* @param array $parameters
* @return array
*/
function _reservasresource_index($page, $parameters) {

	$reservas = array();
	$res = db_query("SELECT CONCAT(pr1.value,  ' ',pr2.value) AS usuario,n2.title AS reservable,
					n3.title AS instalacion,mre.field_merci_date_value AS fecha_inicio,mre.field_merci_date_value2 AS fecha_final
					FROM {node} n1,{node} n2,{node} n3,{content_type_merci_reservation} mre,{merci_reservation_detail} rd,
					profile_values pr1,profile_values pr2,content_type_reservables re
					WHERE n1.nid = rd.nid
					AND n2.nid = rd.merci_item_nid
					AND pr1.uid = n1.uid
					AND pr2.uid = n1.uid
					AND rd.merci_item_nid = re.nid
					AND re.field_ref_instalacion_nid = n3.nid
					AND n1.nid = mre.nid
					AND n1.type = 'merci_reservation'
					AND pr1.fid = 1
					AND pr2.fid = 2
");

	while ($reserva = db_fetch_object($res)) {
		$reservas[] = $reserva;
	}

	return $reservas;
}


