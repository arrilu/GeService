<?php

/**
 * @file
 * merci calendar view default views
 */


/**
 * Implements hook_views_default_views().
 */
function merci_calendar_view_views_default_views() {

  /*
   * Merci Reservation Calendar View.
   */

  $view = new view;
  $view->name = 'merci_reservation_calendar';
  $view->description = 'A multi-dimensional calendar view for Merci Reservations with back/next navigation.';
  $view->tag = 'Merci Reservation Calendar';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Default', 'default');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'name' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 1,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'field_merci_date_value' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_to' => '',
        'group' => TRUE,
      ),
      'repeat' => array(
        'show_repeat_rule' => '',
      ),
      'fromto' => array(
        'fromto' => 'both',
      ),
      'exclude' => 0,
      'id' => 'field_merci_date_value',
      'table' => 'node_data_field_merci_date',
      'field' => 'field_merci_date_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'status' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'status',
      'table' => 'merci_reservation',
      'field' => 'status',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'item_nid2' => array(
      'label' => 'Reserved items',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'type' => 'separator',
      'separator' => ', ',
      'exclude' => 0,
      'id' => 'item_nid2',
      'table' => 'merci_reservation_detail',
      'field' => 'item_nid2',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'field_merci_date_value' => array(
      'exposed' => FALSE,
      'order' => 'ASC',
      'identifier' => 'unsorted',
      'delta' => -1,
      'id' => 'field_merci_date_value',
      'table' => 'node_data_field_merci_date',
      'field' => 'field_merci_date_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'date_argument' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'date',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'date_fields' => array(
        'node_data_field_merci_date.field_merci_date_value' => 'node_data_field_merci_date.field_merci_date_value',
      ),
      'year_range' => '-3:+3',
      'date_method' => 'OR',
      'granularity' => 'week',
      'id' => 'date_argument',
      'table' => 'node',
      'field' => 'date_argument',
      'relationship' => 'none',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_type' => 'tid',
      'validate_argument_php' => '',
      'override' => array(
        'button' => 'Override',
      ),
      'default_options_div_prefix' => '',
      'validate_argument_is_member' => 0,
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '9' => 0,
        '6' => 0,
        '7' => 0,
        '10' => 0,
        '11' => 0,
        '8' => 0,
        '12' => 0,
        '15' => 0,
        '3' => 0,
        '4' => 0,
        '5' => 0,
        '14' => 0,
        '13' => 0,
        '16' => 0,
      ),
      'default_argument_image_size' => '_original',
      'validate_argument_node_type' => array(
        'blog' => 0,
        'image' => 0,
        'merci_reservation' => 0,
        'cbb_submission' => 0,
        'event' => 0,
        'feed' => 0,
        'ical_feed' => 0,
        'merci_audio_field_mixer' => 0,
        'merci_canon_vixia' => 0,
        'merci_conference_room' => 0,
        'merci_edit_suite1' => 0,
        'merci_firestor' => 0,
        'merci_gl2_camcorder' => 0,
        'merci_gl2_xlr_adaptor' => 0,
        'merci_grip_control' => 0,
        'merci_kodak_zx1' => 0,
        'merci_lcd_projector' => 0,
        'merci_litepanel_micro' => 0,
        'merci_macbook' => 0,
        'merci_mic_635a' => 0,
        'merci_mic_boom' => 0,
        'merci_mic_drum_kit' => 0,
        'merci_mic_floor_stand' => 0,
        'merci_mic_lavalier' => 0,
        'merci_mic_sm57' => 0,
        'merci_mic_sm58' => 0,
        'merci_mic_stereo' => 0,
        'merci_mic_table' => 0,
        'merci_mic_table_stand' => 0,
        'merci_mic_wireless_lavalier' => 0,
        'merci_sd_memory_card' => 0,
        'merci_shotgun' => 0,
        'merci_sony_hvr_25u' => 0,
        'merci_studio' => 0,
        'merci_studio_control_room' => 0,
        'merci_tripod' => 0,
        'merci_xl2_camcorder' => 0,
        'merci_xl2_wide_angle_lens' => 0,
        'om_airing' => 0,
        'om_cablecast_show' => 0,
        'om_feed' => 0,
        'om_project' => 0,
        'om_project_type' => 0,
        'om_show' => 0,
        'om_timeslot_event' => 0,
        'om_timeslot_rule' => 0,
        'om_timeslot_server' => 0,
        'om_timeslot_theme' => 0,
        'page' => 0,
        'project_blog' => 0,
        'project_wiki' => 0,
        'story' => 0,
        'test_media_mover' => 0,
      ),
      'validate_argument_vocabulary' => array(
        '7' => 0,
        '8' => 0,
        '21' => 0,
        '19' => 0,
        '20' => 0,
        '22' => 0,
        '3' => 0,
        '1' => 0,
        '2' => 0,
        '4' => 0,
        '5' => 0,
      ),
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'image_size' => array(
        '_original' => '_original',
        'thumbnail' => 'thumbnail',
        'preview' => 'preview',
      ),
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'merci_reservation' => 'merci_reservation',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => 'type_op',
        'label' => 'Node: Type',
        'use_operator' => 0,
        'identifier' => 'type',
        'optional' => 1,
        'single' => 1,
        'remember' => 0,
        'reduce' => 1,
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'status_1' => array(
      'operator' => 'in',
      'value' => array(),
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'status_1_op',
        'identifier' => 'status_1',
        'label' => 'Status',
        'bef_filter_description' => '',
        'bef_format' => 'default',
        'optional' => 1,
        'single' => 1,
        'remember' => 0,
        'reduce' => 0,
        'bef_select_all_none' => 0,
      ),
      'id' => 'status_1',
      'table' => 'merci_reservation',
      'field' => 'status',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'manage reservations',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Merci Reservation Calendar');
  $handler->override_option('header_format', '2');
  $handler->override_option('header_empty', 0);
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 0);
  $handler->override_option('distinct', 1);
  $handler->override_option('style_plugin', 'calendar_nav');
  $handler->override_option('style_options', array(
    'name_size' => '3',
    'with_weekno' => '0',
  ));
  $handler = $view->new_display('calendar', 'Calendar page', 'calendar_1');
  $handler->override_option('style_options', array());
  $handler->override_option('row_plugin', '');
  $handler->override_option('row_options', NULL);
  $handler->override_option('path', 'admin/merci/manage/reservations');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Manage Reservations',
    'description' => 'Calendar to browse reservations',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('calendar_colors', array(
    'page' => '#ffff66',
    'story' => '#668cff',
  ));
  $handler->override_option('calendar_colors_vocabulary', array());
  $handler->override_option('calendar_colors_taxonomy', array());
  $handler->override_option('calendar_popup', '1');
  $handler->override_option('calendar_date_link', 'merci_reservation');
  $handler = $view->new_display('calendar_period', 'Year view', 'calendar_period_1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'title' => 'title',
      'name' => 'name',
      'field_merci_date_value' => 'field_merci_date_value',
      'item_nid2' => 'item_nid2',
      'status' => 'status',
    ),
    'info' => array(
      'title' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'name' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'field_merci_date_value' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'item_nid2' => array(
        'separator' => '',
      ),
      'status' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler->override_option('attachment_position', 'after');
  $handler->override_option('inherit_arguments', TRUE);
  $handler->override_option('inherit_exposed_filters', TRUE);
  $handler->override_option('inherit_pager', FALSE);
  $handler->override_option('render_pager', TRUE);
  $handler->override_option('displays', array(
    'calendar_1' => 'calendar_1',
    'default' => 0,
    'calendar_block_1' => 0,
  ));
  $handler->override_option('calendar_type', 'year');
  $handler = $view->new_display('calendar_period', 'Month view', 'calendar_period_2');
  $handler->override_option('distinct', 0);
  $handler->override_option('style_plugin', 'calendar_style');
  $handler->override_option('style_options', array(
    'name_size' => '3',
    'with_weekno' => '0',
    'max_items' => '0',
    'max_items_behavior' => 'more',
    'groupby_times' => 'hour',
    'groupby_times_custom' => '',
    'groupby_field' => '',
  ));
  $handler->override_option('attachment_position', 'after');
  $handler->override_option('inherit_arguments', TRUE);
  $handler->override_option('inherit_exposed_filters', TRUE);
  $handler->override_option('inherit_pager', FALSE);
  $handler->override_option('render_pager', TRUE);
  $handler->override_option('displays', array(
    'calendar_1' => 'calendar_1',
    'default' => 0,
    'calendar_block_1' => 0,
  ));
  $handler->override_option('calendar_type', 'month');
  $handler = $view->new_display('calendar_period', 'Day view', 'calendar_period_3');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'title' => 'title',
      'name' => 'name',
      'field_merci_date_value' => 'field_merci_date_value',
      'item_nid2' => 'item_nid2',
      'status' => 'status',
      'title_1' => 'title_1',
    ),
    'info' => array(
      'title' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'name' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'field_merci_date_value' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'item_nid2' => array(
        'separator' => '',
      ),
      'status' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'title_1' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler->override_option('attachment_position', 'after');
  $handler->override_option('inherit_arguments', TRUE);
  $handler->override_option('inherit_exposed_filters', TRUE);
  $handler->override_option('inherit_pager', FALSE);
  $handler->override_option('render_pager', TRUE);
  $handler->override_option('displays', array(
    'calendar_1' => 'calendar_1',
    'default' => 0,
    'block_1' => 0,
  ));
  $handler->override_option('calendar_type', 'day');
  $handler = $view->new_display('calendar_period', 'Week view', 'calendar_period_4');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'title' => 'title',
      'field_merci_date_value' => 'field_merci_date_value',
      'status' => 'status',
      'item_nid2' => 'item_nid2',
    ),
    'info' => array(
      'title' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'field_merci_date_value' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'status' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'item_nid2' => array(
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler->override_option('attachment_position', 'after');
  $handler->override_option('inherit_arguments', TRUE);
  $handler->override_option('inherit_exposed_filters', TRUE);
  $handler->override_option('inherit_pager', FALSE);
  $handler->override_option('render_pager', TRUE);
  $handler->override_option('displays', array(
    'calendar_1' => 'calendar_1',
    'default' => 0,
    'block_1' => 0,
    'block_2' => 0,
    'block_3' => 0,
  ));
  $handler->override_option('calendar_type', 'week');
  $handler = $view->new_display('block', 'Upcoming Reservations', 'block_1');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'name' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 1,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'field_merci_date_value' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_to' => '',
        'group' => TRUE,
      ),
      'repeat' => array(
        'show_repeat_rule' => '',
      ),
      'fromto' => array(
        'fromto' => 'both',
      ),
      'exclude' => 0,
      'id' => 'field_merci_date_value',
      'table' => 'node_data_field_merci_date',
      'field' => 'field_merci_date_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'item_nid2' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'type' => 'separator',
      'separator' => ', ',
      'exclude' => 0,
      'id' => 'item_nid2',
      'table' => 'merci_reservation_detail',
      'field' => 'item_nid2',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'status' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'status',
      'table' => 'merci_reservation',
      'field' => 'status',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
  ));
  $handler->override_option('sorts', array(
    'field_merci_date_value' => array(
      'exposed' => FALSE,
      'order' => 'ASC',
      'identifier' => 'unsorted',
      'delta' => -1,
      'id' => 'field_merci_date_value',
      'table' => 'node_data_field_merci_date',
      'field' => 'field_merci_date_value',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'merci_reservation' => 'merci_reservation',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => 'type_op',
        'label' => 'Node: Type',
        'use_operator' => 0,
        'identifier' => 'type',
        'optional' => 1,
        'single' => 1,
        'remember' => 0,
        'reduce' => 1,
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'date_filter' => array(
      'operator' => '>=',
      'value' => array(
        'value' => NULL,
        'min' => NULL,
        'max' => NULL,
        'default_date' => 'now',
        'default_to_date' => '',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'date_fields' => array(
        'node_data_field_merci_date.field_merci_date_value' => 'node_data_field_merci_date.field_merci_date_value',
      ),
      'date_method' => 'OR',
      'granularity' => 'second',
      'form_type' => 'date_select',
      'default_date' => 'now',
      'default_to_date' => '',
      'year_range' => '-3:+3',
      'id' => 'date_filter',
      'table' => 'node',
      'field' => 'date_filter',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('title', 'Upcoming Reservations');
  $handler->override_option('items_per_page', 5);
  $handler->override_option('use_more', 1);
  $handler->override_option('use_more_always', 0);
  $handler->override_option('style_plugin', 'default');
  $handler->override_option('style_options', array(
    'grouping' => '',
  ));
  $handler->override_option('block_description', 'MERCI: Upcoming Reservations');
  $handler->override_option('block_caching', -1);
  $handler = $view->new_display('block', 'User Reservations', 'block_2');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'name' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 1,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'field_merci_date_value' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_to' => '',
        'group' => TRUE,
      ),
      'repeat' => array(
        'show_repeat_rule' => '',
      ),
      'fromto' => array(
        'fromto' => 'both',
      ),
      'exclude' => 0,
      'id' => 'field_merci_date_value',
      'table' => 'node_data_field_merci_date',
      'field' => 'field_merci_date_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'item_nid2' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'type' => 'separator',
      'separator' => ', ',
      'exclude' => 0,
      'id' => 'item_nid2',
      'table' => 'merci_reservation_detail',
      'field' => 'item_nid2',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'status' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'status',
      'table' => 'merci_reservation',
      'field' => 'status',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'merci_reservation' => 'merci_reservation',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => 'type_op',
        'label' => 'Node: Type',
        'use_operator' => 0,
        'identifier' => 'type',
        'optional' => 1,
        'single' => 1,
        'remember' => 0,
        'reduce' => 1,
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'date_filter' => array(
      'operator' => '>=',
      'value' => array(
        'value' => NULL,
        'min' => NULL,
        'max' => NULL,
        'default_date' => 'now',
        'default_to_date' => '',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'date_fields' => array(
        'node_data_field_merci_date.field_merci_date_value' => 'node_data_field_merci_date.field_merci_date_value',
      ),
      'date_method' => 'OR',
      'granularity' => 'second',
      'form_type' => 'date_select',
      'default_date' => 'now',
      'default_to_date' => '',
      'year_range' => '-3:+3',
      'id' => 'date_filter',
      'table' => 'node',
      'field' => 'date_filter',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'uid_current' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'uid_current',
      'table' => 'users',
      'field' => 'uid_current',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('title', 'My Reservations');
  $handler->override_option('style_plugin', 'default');
  $handler->override_option('style_options', array(
    'grouping' => '',
  ));
  $handler->override_option('block_description', 'MERCI: User Upcoming Reservations');
  $handler->override_option('block_caching', -1);
  $handler = $view->new_display('block', 'Past Due Reservations', 'block_3');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'name' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 1,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'field_merci_date_value' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_to' => '',
        'group' => TRUE,
      ),
      'repeat' => array(
        'show_repeat_rule' => '',
      ),
      'fromto' => array(
        'fromto' => 'both',
      ),
      'exclude' => 0,
      'id' => 'field_merci_date_value',
      'table' => 'node_data_field_merci_date',
      'field' => 'field_merci_date_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'item_nid2' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'type' => 'separator',
      'separator' => ', ',
      'exclude' => 0,
      'id' => 'item_nid2',
      'table' => 'merci_reservation_detail',
      'field' => 'item_nid2',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'status' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'status',
      'table' => 'merci_reservation',
      'field' => 'status',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
  ));
  $handler->override_option('arguments', array());
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'merci_reservation' => 'merci_reservation',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => 'type_op',
        'label' => 'Node: Type',
        'use_operator' => 0,
        'identifier' => 'type',
        'optional' => 1,
        'single' => 1,
        'remember' => 0,
        'reduce' => 1,
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'status_1' => array(
      'operator' => 'in',
      'value' => array(
        '3' => '3',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => 'status_1_op',
        'label' => 'Status',
        'use_operator' => 0,
        'identifier' => 'status_1',
        'bef_filter_description' => '',
        'bef_format' => 'default',
        'optional' => 1,
        'single' => 1,
        'remember' => 0,
        'reduce' => 0,
        'bef_select_all_none' => 0,
      ),
      'id' => 'status_1',
      'table' => 'merci_reservation',
      'field' => 'status',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'date_filter' => array(
      'operator' => '<=',
      'value' => array(
        'value' => NULL,
        'min' => NULL,
        'max' => NULL,
        'default_date' => 'now',
        'default_to_date' => '',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'date_fields' => array(
        'node_data_field_merci_date.field_merci_date_value2' => 'node_data_field_merci_date.field_merci_date_value2',
      ),
      'date_method' => 'OR',
      'granularity' => 'second',
      'form_type' => 'date_select',
      'default_date' => 'now',
      'default_to_date' => '',
      'year_range' => '-3:+3',
      'id' => 'date_filter',
      'table' => 'node',
      'field' => 'date_filter',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('title', 'Past Due Reservations');
  $handler->override_option('style_plugin', 'default');
  $handler->override_option('style_options', array(
    'grouping' => '',
  ));
  $handler->override_option('block_description', 'MERCI: Past Due Reservations');
  $handler->override_option('block_caching', -1);


  $views[$view->name] = $view;

  /*
   * View 'merci_inventory'
   */

  $view               = new view;
  $view->name         = 'merci_inventory';
  $view->description  = '';
  $view->tag          = '';
  $view->view_php     = '';
  $view->base_table   = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version  = 2;
  /* Edit this to true to make a default view disabled initially */
  $view->disabled = FALSE;
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => 'Title',
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'type' => array(
      'label' => 'Type',
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
  ));
  $handler->override_option('sorts', array(
    'title' => array(
      'order' => 'ASC',
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'type_setting' => array(
      'operator' => 'in',
      'value' => array(
        'bucket' => 'bucket',
        'resource' => 'resource',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type_setting',
      'table' => 'merci_node_type',
      'field' => 'type_setting',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'manage reservations',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'MERCI Inventory');
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'title' => 'title',
      'type' => 'type',
    ),
    'info' => array(
      'title' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'type' => array(
        'sortable' => 1,
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'admin/merci/manage/inventory');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Manage Inventory',
    'description' => 'Manage reservable equipment',
    'weight' => '8',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $views[$view->name] = $view;

  return $views;
}

