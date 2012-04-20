<?php

/**
 * @file
 * Simpletest case for node_example module.
 *
 * Verify example module functionality.
 */

/**
 * Functionality tests for merci module.
 * General setup and functions all merci tests should inherit.
 */
class MerciTestCase extends DrupalWebTestCase {


  public $admin_user;

  function setUp() {
    // Enable the module.
    parent::setUp(
        //'node',
        //'devel',
        'content',
        'fieldgroup',
        'optionwidgets',
        'text',
        'number',
        'jquery_ui',
        'date_api',
        'date',
        'date_timezone',
        'date_popup',
        'text',
        'views',
        'merci'
        //'merci_staff'

        );

    // Create admin user. 
    $this->admin_user = $this->drupalCreateUser(array(
      'administer nodes', // Required to set revision checkbox
      'administer content types',
      'access administration pages',
      'administer site configuration',
      'view revisions',
      'revert revisions',
      //'access devel information',
      'administer MERCI',
      'manage reservations'
    ));
    // Login the admin user.
    $this->drupalLogin($this->admin_user);

    $settings = array (
      'merci_default_reservation_status' => '2',
      'merci_max_days_advance_reservation' => '0',
      'merci_saturday_is_weekend' => '1',
      'merci_sunday_is_weekend' => '1',
      'merci_hours_mon' => '09:00-18:00',
      'merci_hours_tue' => '09:00-18:00',
      'merci_hours_wed' => '09:00-18:00',
      'merci_hours_thu' => '09:00-18:00',
      'merci_hours_fri' => '09:00-18:00',
      'merci_hours_sat' => '09:00-18:00',
      'merci_hours_sun' => '09:00-18:00',
      'merci_hours_admin' => '07:00-22:00',
      'merci_closed_dates' => '12-25',
      'merci_lock'    => FALSE,
    );

    $this->merciCreateConfig($settings);

    $settings = array (
      'date_default_timezone_name' => 'America/Los_Angeles',
      );
    $this->drupalPost('admin/settings/date-time' , $settings, t('Save configuration'));
    $this->assertText(t("The configuration options have been saved."));

    $settings = array ( 
      'input_format' => 'Y-m-d H:i',
    );
    $this->drupalPost('admin/content/node-type/merci-reservation/fields/field_merci_date', $settings, t('Save field settings'));
    $this->assertText(t("Saved field Reservation."));
  }


  function merciCreateContentType($settings,$merci_type,$merci_settings=NULL) {
    // Create resource content type
    // Disable the rating for this content type: 0 for Disabled, 1 for Enabled.
    if (node_get_types('type', $settings['type'])) {
      return $settings['type'];
    }
    $content_type = $this->drupalCreateContentType($settings);
    $type = $content_type->type;
    $settings = array(
        'merci_type_setting' => $merci_type,
        'merci_max_hours_per_reservation' => 5
    );
    if($merci_settings) {
      $settings = $settings + $merci_settings;
    }
    $this->drupalPost('admin/content/node-type/' . $type, $settings, t('Save content type'));
    $this->assertResponse(200);
    $this->assertRaw(' has been updated.', t('Settings modified successfully for content type.'));
    return $type;
  }

  function merciCreateNode($type,$settings,$pass=TRUE) {
    $this->drupalPost('node/add/' . $type, $settings, t('Save'));
    $node = node_load(array('title' => $settings['title']));
    //$this->verbose('Node created: ' . var_export($node, TRUE));
    return $node;
  }

  function merciUpdateNode($nid,$settings,$pass=TRUE) {
    $this->drupalPost("node/$nid/edit", $settings, t('Save'));
    $node = node_load($nid);
    return $node;
  }

  function merciCreateConfig($settings) {
    $this->drupalPost('admin/settings/merci' , $settings, t('Save configuration'));
    $this->assertText(t("The configuration options have been saved."));
  }

  function merciCreateItem($merci_type, $type = NULL, $merci_settings = array()) {

    $type = $type ? $type : $merci_type;
    $settings = array (
        'type'  => $type,
        );
    $type = $this->merciCreateContentType($settings, $merci_type, $merci_settings);
    // Create resource item
    $edit = array(
      'title' => $this->randomName()
    );

    $item = $this->merciCreateNode($type, $edit);
    $this->assertText(t("@title has been created", array('@title' => $edit['title'])));
    return $item;
  }
}

