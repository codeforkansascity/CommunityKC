<?php
/**
 * @file
 * custom_feature.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function custom_feature_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'dashboard';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Dashboard';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'status' => 'status',
    'edit_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'No Projects';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'You don\'t have any projects. Would you like to <a href="/communitykc/submit">add one now?</a>';
  $handler->display->display_options['empty']['area']['format'] = 'filtered';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Edit';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'project' => 'project',
  );
  /* Filter criterion: User: Current */
  $handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['table'] = 'users';
  $handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid_current']['value'] = '1';

  /* Display: Dashboard Block */
  $handler = $view->new_display('block', 'Dashboard Block', 'block');
  $export['dashboard'] = $view;

  $view = new view();
  $view->name = 'events';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Events';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Events';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'node';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_project_target_id']['id'] = 'field_project_target_id';
  $handler->display->display_options['relationships']['field_project_target_id']['table'] = 'field_data_field_project';
  $handler->display->display_options['relationships']['field_project_target_id']['field'] = 'field_project_target_id';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'event' => 'event',
  );
  /* Filter criterion: Content: Event Neighborhood (field_event_neighborhood) */
  $handler->display->display_options['filters']['field_event_neighborhood_tid']['id'] = 'field_event_neighborhood_tid';
  $handler->display->display_options['filters']['field_event_neighborhood_tid']['table'] = 'field_data_field_event_neighborhood';
  $handler->display->display_options['filters']['field_event_neighborhood_tid']['field'] = 'field_event_neighborhood_tid';
  $handler->display->display_options['filters']['field_event_neighborhood_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_event_neighborhood_tid']['expose']['operator_id'] = 'field_event_neighborhood_tid_op';
  $handler->display->display_options['filters']['field_event_neighborhood_tid']['expose']['label'] = 'Event Neighborhood (field_event_neighborhood)';
  $handler->display->display_options['filters']['field_event_neighborhood_tid']['expose']['operator'] = 'field_event_neighborhood_tid_op';
  $handler->display->display_options['filters']['field_event_neighborhood_tid']['expose']['identifier'] = 'field_event_neighborhood_tid';
  $handler->display->display_options['filters']['field_event_neighborhood_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_event_neighborhood_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_event_neighborhood_tid']['vocabulary'] = 'neighborhood';
  /* Filter criterion: Content: Event Type (field_event_type) */
  $handler->display->display_options['filters']['field_event_type_tid']['id'] = 'field_event_type_tid';
  $handler->display->display_options['filters']['field_event_type_tid']['table'] = 'field_data_field_event_type';
  $handler->display->display_options['filters']['field_event_type_tid']['field'] = 'field_event_type_tid';
  $handler->display->display_options['filters']['field_event_type_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_event_type_tid']['expose']['operator_id'] = 'field_event_type_tid_op';
  $handler->display->display_options['filters']['field_event_type_tid']['expose']['label'] = 'Event Type (field_event_type)';
  $handler->display->display_options['filters']['field_event_type_tid']['expose']['operator'] = 'field_event_type_tid_op';
  $handler->display->display_options['filters']['field_event_type_tid']['expose']['identifier'] = 'field_event_type_tid';
  $handler->display->display_options['filters']['field_event_type_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_event_type_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_event_type_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_event_type_tid']['vocabulary'] = 'project_type';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'events/view';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'View Events';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['events'] = $view;

  $view = new view();
  $view->name = 'faq';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'FAQ';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Frequently Asked Questions';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_accordion';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['collapsible'] = 1;
  $handler->display->display_options['style_options']['row-start-open'] = 'none';
  $handler->display->display_options['style_options']['autoheight'] = 0;
  $handler->display->display_options['style_options']['clearstyle'] = 1;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Field: Content: Photos */
  $handler->display->display_options['fields']['field_photos']['id'] = 'field_photos';
  $handler->display->display_options['fields']['field_photos']['table'] = 'field_data_field_photos';
  $handler->display->display_options['fields']['field_photos']['field'] = 'field_photos';
  $handler->display->display_options['fields']['field_photos']['label'] = '';
  $handler->display->display_options['fields']['field_photos']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_photos']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_photos']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_photos']['delta_limit'] = 'all';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'faq' => 'faq',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'faq';
  $export['faq'] = $view;

  $view = new view();
  $view->name = 'map';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'map';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Project Map';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Submit';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'ip_geoloc_leaflet';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => '',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['map_height'] = '800';
  $handler->display->display_options['style_options']['ip_geoloc_views_plugin_latitude'] = array(
    'field_geocoded_address' => 'field_geocoded_address',
  );
  $handler->display->display_options['style_options']['ip_geoloc_views_plugin_longitude'] = 'field_geocoded_address';
  $handler->display->display_options['style_options']['default_marker']['default_marker_color'] = 'blue';
  $handler->display->display_options['style_options']['differentiator']['differentiator_field'] = 'field_project_type';
  $handler->display->display_options['style_options']['center_option'] = '0';
  $handler->display->display_options['style_options']['sync']['2'] = 0;
  $handler->display->display_options['style_options']['sync']['4'] = 0;
  $handler->display->display_options['style_options']['sync']['8'] = 1;
  $handler->display->display_options['style_options']['sync']['16'] = 1;
  $handler->display->display_options['style_options']['full_screen'] = 0;
  $handler->display->display_options['style_options']['scale_metric'] = 0;
  $handler->display->display_options['style_options']['scale_imperial'] = 0;
  $handler->display->display_options['style_options']['zoom_indicator'] = 0;
  $handler->display->display_options['style_options']['map_reset'] = 0;
  $handler->display->display_options['style_options']['map_cluster_toggle'] = 0;
  $handler->display->display_options['style_options']['mini_map']['on'] = 0;
  $handler->display->display_options['style_options']['mini_map']['height'] = '100';
  $handler->display->display_options['style_options']['mini_map']['width'] = '150';
  $handler->display->display_options['style_options']['mini_map']['toggle'] = 1;
  $handler->display->display_options['style_options']['mini_map']['zoom_delta'] = '-5';
  $handler->display->display_options['style_options']['cluster_differentiator']['cluster_differentiator_fields'] = array(
    '' => '',
  );
  $handler->display->display_options['style_options']['cluster_differentiator']['zoom_ranges'] = array(
    1 => '',
  );
  $handler->display->display_options['style_options']['cluster_differentiator']['cluster_tooltips'] = 1;
  $handler->display->display_options['style_options']['cluster_differentiator']['cluster_outline'] = '0';
  $handler->display->display_options['style_options']['cluster_aggregation']['aggregation_function'] = 'average';
  $handler->display->display_options['style_options']['cluster_aggregation']['ranges']['small'] = '10';
  $handler->display->display_options['style_options']['cluster_aggregation']['ranges']['medium'] = '100';
  $handler->display->display_options['style_options']['cluster_aggregation']['ranges']['large'] = '1000';
  $handler->display->display_options['style_options']['map_options']['maxzoom'] = '18';
  $handler->display->display_options['style_options']['map_options']['zoom'] = '11';
  $handler->display->display_options['style_options']['map_options']['scrollwheelzoom'] = '1';
  $handler->display->display_options['style_options']['map_options']['dragging'] = '1';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '250',
  );
  /* Field: Content: Project Type */
  $handler->display->display_options['fields']['field_project_type']['id'] = 'field_project_type';
  $handler->display->display_options['fields']['field_project_type']['table'] = 'field_data_field_project_type';
  $handler->display->display_options['fields']['field_project_type']['field'] = 'field_project_type';
  $handler->display->display_options['fields']['field_project_type']['hide_empty'] = TRUE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'project' => 'project',
  );

  /* Display: Map */
  $handler = $view->new_display('page', 'Map', 'page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Submit';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'ip_geoloc_leaflet';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => '',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['map'] = 'bing';
  $handler->display->display_options['style_options']['map_height'] = '600';
  $handler->display->display_options['style_options']['ip_geoloc_views_plugin_latitude'] = array(
    'field_geocoded_address' => 'field_geocoded_address',
  );
  $handler->display->display_options['style_options']['ip_geoloc_views_plugin_longitude'] = 'field_geocoded_address';
  $handler->display->display_options['style_options']['visitor_marker']['visitor_marker_accuracy_circle'] = 0;
  $handler->display->display_options['style_options']['differentiator']['differentiator_field'] = 'field_project_type';
  $handler->display->display_options['style_options']['center_option'] = '0';
  $handler->display->display_options['style_options']['tooltips']['marker_tooltip'] = 'title';
  $handler->display->display_options['style_options']['sync']['2'] = 0;
  $handler->display->display_options['style_options']['sync']['4'] = 0;
  $handler->display->display_options['style_options']['sync']['8'] = 1;
  $handler->display->display_options['style_options']['sync']['16'] = 1;
  $handler->display->display_options['style_options']['full_screen'] = 0;
  $handler->display->display_options['style_options']['scale_metric'] = 0;
  $handler->display->display_options['style_options']['scale_imperial'] = 0;
  $handler->display->display_options['style_options']['zoom_indicator'] = 0;
  $handler->display->display_options['style_options']['open_balloons_on_click'] = 1;
  $handler->display->display_options['style_options']['open_balloons_on_hover'] = 0;
  $handler->display->display_options['style_options']['goto_content_on_click'] = 0;
  $handler->display->display_options['style_options']['map_reset'] = 1;
  $handler->display->display_options['style_options']['map_cluster_toggle'] = 0;
  $handler->display->display_options['style_options']['mini_map']['on'] = 0;
  $handler->display->display_options['style_options']['mini_map']['height'] = '100';
  $handler->display->display_options['style_options']['mini_map']['width'] = '150';
  $handler->display->display_options['style_options']['mini_map']['toggle'] = 1;
  $handler->display->display_options['style_options']['mini_map']['zoom_delta'] = '-5';
  $handler->display->display_options['style_options']['cluster_differentiator']['cluster_differentiator_fields'] = array(
    'field_project_type' => 'field_project_type',
  );
  $handler->display->display_options['style_options']['cluster_differentiator']['zoom_ranges'] = array(
    1 => '',
    2 => '',
  );
  $handler->display->display_options['style_options']['cluster_differentiator']['cluster_tooltips'] = 1;
  $handler->display->display_options['style_options']['cluster_differentiator']['cluster_outline'] = '0';
  $handler->display->display_options['style_options']['cluster_aggregation']['aggregation_field'] = 'field_geocoded_address';
  $handler->display->display_options['style_options']['cluster_aggregation']['aggregation_function'] = 'average';
  $handler->display->display_options['style_options']['cluster_aggregation']['ranges']['small'] = '10';
  $handler->display->display_options['style_options']['cluster_aggregation']['ranges']['medium'] = '100';
  $handler->display->display_options['style_options']['cluster_aggregation']['ranges']['large'] = '1000';
  $handler->display->display_options['style_options']['map_options']['maxzoom'] = '18';
  $handler->display->display_options['style_options']['map_options']['zoom'] = '10';
  $handler->display->display_options['style_options']['map_options']['zoom_on_click'] = '17';
  $handler->display->display_options['style_options']['map_options']['scrollwheelzoom'] = '1';
  $handler->display->display_options['style_options']['map_options']['dragging'] = '1';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Unfiltered text */
  $handler->display->display_options['header']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['header']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['content'] = '<h1>Browse Projects</h1>
<div class="toggle"><a href="list">Go to List View</a></div>';
  $handler->display->display_options['defaults']['footer'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '250',
  );
  /* Field: Content: Geocoded Address */
  $handler->display->display_options['fields']['field_geocoded_address']['id'] = 'field_geocoded_address';
  $handler->display->display_options['fields']['field_geocoded_address']['table'] = 'field_data_field_geocoded_address';
  $handler->display->display_options['fields']['field_geocoded_address']['field'] = 'field_geocoded_address';
  $handler->display->display_options['fields']['field_geocoded_address']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_geocoded_address']['click_sort_column'] = 'geom';
  $handler->display->display_options['fields']['field_geocoded_address']['type'] = 'geofield_latlon';
  $handler->display->display_options['fields']['field_geocoded_address']['settings'] = array(
    'data' => 'full',
    'format' => 'decimal_degrees',
    'labels' => 1,
  );
  $handler->display->display_options['fields']['field_geocoded_address']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_geocoded_address']['delta_offset'] = '0';
  /* Field: Content: Project Type */
  $handler->display->display_options['fields']['field_project_type']['id'] = 'field_project_type';
  $handler->display->display_options['fields']['field_project_type']['table'] = 'field_data_field_project_type';
  $handler->display->display_options['fields']['field_project_type']['field'] = 'field_project_type';
  $handler->display->display_options['fields']['field_project_type']['hide_empty'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'project' => 'project',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Geocoded Address (field_geocoded_address:delta) */
  $handler->display->display_options['filters']['delta']['id'] = 'delta';
  $handler->display->display_options['filters']['delta']['table'] = 'field_data_field_geocoded_address';
  $handler->display->display_options['filters']['delta']['field'] = 'delta';
  $handler->display->display_options['filters']['delta']['operator'] = 'not empty';
  $handler->display->display_options['filters']['delta']['group'] = 1;
  /* Filter criterion: Content: Neighborhood (field_neighborhood) */
  $handler->display->display_options['filters']['field_neighborhood_tid']['id'] = 'field_neighborhood_tid';
  $handler->display->display_options['filters']['field_neighborhood_tid']['table'] = 'field_data_field_neighborhood';
  $handler->display->display_options['filters']['field_neighborhood_tid']['field'] = 'field_neighborhood_tid';
  $handler->display->display_options['filters']['field_neighborhood_tid']['value'] = '';
  $handler->display->display_options['filters']['field_neighborhood_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_neighborhood_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_neighborhood_tid']['expose']['operator_id'] = 'field_neighborhood_tid_op';
  $handler->display->display_options['filters']['field_neighborhood_tid']['expose']['label'] = 'Neighborhood Name';
  $handler->display->display_options['filters']['field_neighborhood_tid']['expose']['operator'] = 'field_neighborhood_tid_op';
  $handler->display->display_options['filters']['field_neighborhood_tid']['expose']['identifier'] = 'field_neighborhood_tid';
  $handler->display->display_options['filters']['field_neighborhood_tid']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_neighborhood_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_neighborhood_tid']['vocabulary'] = 'neighborhood';
  /* Filter criterion: Content: Project Type (field_project_type) */
  $handler->display->display_options['filters']['field_project_type_tid']['id'] = 'field_project_type_tid';
  $handler->display->display_options['filters']['field_project_type_tid']['table'] = 'field_data_field_project_type';
  $handler->display->display_options['filters']['field_project_type_tid']['field'] = 'field_project_type_tid';
  $handler->display->display_options['filters']['field_project_type_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_project_type_tid']['expose']['operator_id'] = 'field_project_type_tid_op';
  $handler->display->display_options['filters']['field_project_type_tid']['expose']['label'] = 'Project Type (field_project_type)';
  $handler->display->display_options['filters']['field_project_type_tid']['expose']['operator'] = 'field_project_type_tid_op';
  $handler->display->display_options['filters']['field_project_type_tid']['expose']['identifier'] = 'field_project_type_tid';
  $handler->display->display_options['filters']['field_project_type_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_project_type_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_project_type_tid']['vocabulary'] = 'project_type';
  $handler->display->display_options['filters']['field_project_type_tid']['hierarchy'] = 1;
  $handler->display->display_options['path'] = 'original-map';

  /* Display: Page - List View */
  $handler = $view->new_display('page', 'Page - List View', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Project List';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'list-display';
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Submit';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Unfiltered text */
  $handler->display->display_options['header']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['header']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['content'] = '<div class="toggle"><a href="map">Go to Map View</a></div>';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = '<span style="color:red; font-weight:bold; font-size:1.2em;">Sorry, there are currently no projects associated with this neighborhood. </span>';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '250',
  );
  /* Field: Content: Geocoded Address */
  $handler->display->display_options['fields']['field_geocoded_address']['id'] = 'field_geocoded_address';
  $handler->display->display_options['fields']['field_geocoded_address']['table'] = 'field_data_field_geocoded_address';
  $handler->display->display_options['fields']['field_geocoded_address']['field'] = 'field_geocoded_address';
  $handler->display->display_options['fields']['field_geocoded_address']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_geocoded_address']['click_sort_column'] = 'geom';
  $handler->display->display_options['fields']['field_geocoded_address']['settings'] = array(
    'data' => 'full',
  );
  $handler->display->display_options['fields']['field_geocoded_address']['delta_offset'] = '0';
  /* Field: Content: Address of the Project */
  $handler->display->display_options['fields']['field_address']['id'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['table'] = 'field_data_field_address';
  $handler->display->display_options['fields']['field_address']['field'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['label'] = '';
  $handler->display->display_options['fields']['field_address']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  $handler->display->display_options['fields']['field_address']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_address']['delta_offset'] = '0';
  /* Field: Content: Organization Name */
  $handler->display->display_options['fields']['field_organization_name']['id'] = 'field_organization_name';
  $handler->display->display_options['fields']['field_organization_name']['table'] = 'field_data_field_organization_name';
  $handler->display->display_options['fields']['field_organization_name']['field'] = 'field_organization_name';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'project' => 'project',
  );
  /* Filter criterion: Content: Neighborhood (field_neighborhood) */
  $handler->display->display_options['filters']['field_neighborhood_tid']['id'] = 'field_neighborhood_tid';
  $handler->display->display_options['filters']['field_neighborhood_tid']['table'] = 'field_data_field_neighborhood';
  $handler->display->display_options['filters']['field_neighborhood_tid']['field'] = 'field_neighborhood_tid';
  $handler->display->display_options['filters']['field_neighborhood_tid']['value'] = '';
  $handler->display->display_options['filters']['field_neighborhood_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_neighborhood_tid']['expose']['operator_id'] = 'field_neighborhood_tid_op';
  $handler->display->display_options['filters']['field_neighborhood_tid']['expose']['label'] = 'Neighborhood';
  $handler->display->display_options['filters']['field_neighborhood_tid']['expose']['description'] = 'Begin typing the name of a neighborhood';
  $handler->display->display_options['filters']['field_neighborhood_tid']['expose']['operator'] = 'field_neighborhood_tid_op';
  $handler->display->display_options['filters']['field_neighborhood_tid']['expose']['identifier'] = 'field_neighborhood_tid';
  $handler->display->display_options['filters']['field_neighborhood_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_neighborhood_tid']['vocabulary'] = 'neighborhood';
  /* Filter criterion: Content: Project Type (field_project_type) */
  $handler->display->display_options['filters']['field_project_type_tid']['id'] = 'field_project_type_tid';
  $handler->display->display_options['filters']['field_project_type_tid']['table'] = 'field_data_field_project_type';
  $handler->display->display_options['filters']['field_project_type_tid']['field'] = 'field_project_type_tid';
  $handler->display->display_options['filters']['field_project_type_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_project_type_tid']['expose']['operator_id'] = 'field_project_type_tid_op';
  $handler->display->display_options['filters']['field_project_type_tid']['expose']['label'] = 'Project Type';
  $handler->display->display_options['filters']['field_project_type_tid']['expose']['description'] = 'Select a project type';
  $handler->display->display_options['filters']['field_project_type_tid']['expose']['operator'] = 'field_project_type_tid_op';
  $handler->display->display_options['filters']['field_project_type_tid']['expose']['identifier'] = 'field_project_type_tid';
  $handler->display->display_options['filters']['field_project_type_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_project_type_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_project_type_tid']['vocabulary'] = 'project_type';
  $handler->display->display_options['filters']['field_project_type_tid']['hierarchy'] = 1;
  /* Filter criterion: Content: Phase (field_phase) */
  $handler->display->display_options['filters']['field_phase_value']['id'] = 'field_phase_value';
  $handler->display->display_options['filters']['field_phase_value']['table'] = 'field_data_field_phase';
  $handler->display->display_options['filters']['field_phase_value']['field'] = 'field_phase_value';
  $handler->display->display_options['filters']['field_phase_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_phase_value']['expose']['operator_id'] = 'field_phase_value_op';
  $handler->display->display_options['filters']['field_phase_value']['expose']['label'] = 'Phase';
  $handler->display->display_options['filters']['field_phase_value']['expose']['operator'] = 'field_phase_value_op';
  $handler->display->display_options['filters']['field_phase_value']['expose']['identifier'] = 'field_phase_value';
  $handler->display->display_options['filters']['field_phase_value']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_phase_value']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_phase_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['path'] = 'list';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Location List';
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '200',
  );
  /* Field: Content: Project Type */
  $handler->display->display_options['fields']['field_project_type']['id'] = 'field_project_type';
  $handler->display->display_options['fields']['field_project_type']['table'] = 'field_data_field_project_type';
  $handler->display->display_options['fields']['field_project_type']['field'] = 'field_project_type';
  $handler->display->display_options['fields']['field_project_type']['label'] = '';
  $handler->display->display_options['fields']['field_project_type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_project_type']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'project' => 'project',
  );
  /* Filter criterion: Content: Project Type (field_project_type) */
  $handler->display->display_options['filters']['field_project_type_tid']['id'] = 'field_project_type_tid';
  $handler->display->display_options['filters']['field_project_type_tid']['table'] = 'field_data_field_project_type';
  $handler->display->display_options['filters']['field_project_type_tid']['field'] = 'field_project_type_tid';
  $handler->display->display_options['filters']['field_project_type_tid']['value'] = array(
    460 => '460',
    457 => '457',
    461 => '461',
    458 => '458',
    459 => '459',
    456 => '456',
  );
  $handler->display->display_options['filters']['field_project_type_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_project_type_tid']['vocabulary'] = 'project_type';
  $handler->display->display_options['block_description'] = 'Map Location List';

  /* Display: Advanced Search */
  $handler = $view->new_display('page', 'Advanced Search', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Advanced Search';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'adv-search';
  $handler->display->display_options['display_description'] = 'Advanced Search';
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Unfiltered text */
  $handler->display->display_options['header']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['header']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = '<span style="color:red; font-weight:bold; font-size:1.2em;">Sorry, there are currently no projects associated with this search. </span>';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '250',
  );
  /* Field: Content: Geocoded Address */
  $handler->display->display_options['fields']['field_geocoded_address']['id'] = 'field_geocoded_address';
  $handler->display->display_options['fields']['field_geocoded_address']['table'] = 'field_data_field_geocoded_address';
  $handler->display->display_options['fields']['field_geocoded_address']['field'] = 'field_geocoded_address';
  $handler->display->display_options['fields']['field_geocoded_address']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_geocoded_address']['click_sort_column'] = 'geom';
  $handler->display->display_options['fields']['field_geocoded_address']['settings'] = array(
    'data' => 'full',
  );
  $handler->display->display_options['fields']['field_geocoded_address']['delta_offset'] = '0';
  /* Field: Content: Address of the Project */
  $handler->display->display_options['fields']['field_address']['id'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['table'] = 'field_data_field_address';
  $handler->display->display_options['fields']['field_address']['field'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['label'] = '';
  $handler->display->display_options['fields']['field_address']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  $handler->display->display_options['fields']['field_address']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_address']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Project Name';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Content: Neighborhood (field_neighborhood) */
  $handler->display->display_options['filters']['field_neighborhood_tid']['id'] = 'field_neighborhood_tid';
  $handler->display->display_options['filters']['field_neighborhood_tid']['table'] = 'field_data_field_neighborhood';
  $handler->display->display_options['filters']['field_neighborhood_tid']['field'] = 'field_neighborhood_tid';
  $handler->display->display_options['filters']['field_neighborhood_tid']['value'] = '';
  $handler->display->display_options['filters']['field_neighborhood_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_neighborhood_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_neighborhood_tid']['expose']['operator_id'] = 'field_neighborhood_tid_op';
  $handler->display->display_options['filters']['field_neighborhood_tid']['expose']['label'] = 'Neighborhood';
  $handler->display->display_options['filters']['field_neighborhood_tid']['expose']['description'] = 'Begin typing the name of a neighborhood';
  $handler->display->display_options['filters']['field_neighborhood_tid']['expose']['operator'] = 'field_neighborhood_tid_op';
  $handler->display->display_options['filters']['field_neighborhood_tid']['expose']['identifier'] = 'field_neighborhood_tid';
  $handler->display->display_options['filters']['field_neighborhood_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['filters']['field_neighborhood_tid']['vocabulary'] = 'neighborhood';
  /* Filter criterion: Content: Organization Name (field_organization_name) */
  $handler->display->display_options['filters']['field_organization_name_value']['id'] = 'field_organization_name_value';
  $handler->display->display_options['filters']['field_organization_name_value']['table'] = 'field_data_field_organization_name';
  $handler->display->display_options['filters']['field_organization_name_value']['field'] = 'field_organization_name_value';
  $handler->display->display_options['filters']['field_organization_name_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_organization_name_value']['group'] = 1;
  $handler->display->display_options['filters']['field_organization_name_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_organization_name_value']['expose']['operator_id'] = 'field_organization_name_value_op';
  $handler->display->display_options['filters']['field_organization_name_value']['expose']['label'] = 'Organization Name';
  $handler->display->display_options['filters']['field_organization_name_value']['expose']['operator'] = 'field_organization_name_value_op';
  $handler->display->display_options['filters']['field_organization_name_value']['expose']['identifier'] = 'field_organization_name_value';
  $handler->display->display_options['filters']['field_organization_name_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Content: Project Type (field_project_type) */
  $handler->display->display_options['filters']['field_project_type_tid']['id'] = 'field_project_type_tid';
  $handler->display->display_options['filters']['field_project_type_tid']['table'] = 'field_data_field_project_type';
  $handler->display->display_options['filters']['field_project_type_tid']['field'] = 'field_project_type_tid';
  $handler->display->display_options['filters']['field_project_type_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_project_type_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_project_type_tid']['expose']['operator_id'] = 'field_project_type_tid_op';
  $handler->display->display_options['filters']['field_project_type_tid']['expose']['label'] = 'Project Type';
  $handler->display->display_options['filters']['field_project_type_tid']['expose']['operator'] = 'field_project_type_tid_op';
  $handler->display->display_options['filters']['field_project_type_tid']['expose']['identifier'] = 'field_project_type_tid';
  $handler->display->display_options['filters']['field_project_type_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['field_project_type_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_project_type_tid']['vocabulary'] = 'project_type';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'project' => 'project',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Phase (field_phase) */
  $handler->display->display_options['filters']['field_phase_value']['id'] = 'field_phase_value';
  $handler->display->display_options['filters']['field_phase_value']['table'] = 'field_data_field_phase';
  $handler->display->display_options['filters']['field_phase_value']['field'] = 'field_phase_value';
  $handler->display->display_options['filters']['field_phase_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_phase_value']['expose']['operator_id'] = 'field_phase_value_op';
  $handler->display->display_options['filters']['field_phase_value']['expose']['label'] = 'Phase';
  $handler->display->display_options['filters']['field_phase_value']['expose']['operator'] = 'field_phase_value_op';
  $handler->display->display_options['filters']['field_phase_value']['expose']['identifier'] = 'field_phase_value';
  $handler->display->display_options['filters']['field_phase_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Content: Funder (field_funder) */
  $handler->display->display_options['filters']['field_funder_value']['id'] = 'field_funder_value';
  $handler->display->display_options['filters']['field_funder_value']['table'] = 'field_data_field_funder';
  $handler->display->display_options['filters']['field_funder_value']['field'] = 'field_funder_value';
  $handler->display->display_options['filters']['field_funder_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_funder_value']['expose']['operator_id'] = 'field_funder_value_op';
  $handler->display->display_options['filters']['field_funder_value']['expose']['label'] = 'Funder';
  $handler->display->display_options['filters']['field_funder_value']['expose']['operator'] = 'field_funder_value_op';
  $handler->display->display_options['filters']['field_funder_value']['expose']['identifier'] = 'field_funder_value';
  $handler->display->display_options['filters']['field_funder_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  /* Filter criterion: Content: Organization Type (field_organization_type) */
  $handler->display->display_options['filters']['field_organization_type_value']['id'] = 'field_organization_type_value';
  $handler->display->display_options['filters']['field_organization_type_value']['table'] = 'field_data_field_organization_type';
  $handler->display->display_options['filters']['field_organization_type_value']['field'] = 'field_organization_type_value';
  $handler->display->display_options['filters']['field_organization_type_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_organization_type_value']['expose']['operator_id'] = 'field_organization_type_value_op';
  $handler->display->display_options['filters']['field_organization_type_value']['expose']['label'] = 'Organization Type';
  $handler->display->display_options['filters']['field_organization_type_value']['expose']['operator'] = 'field_organization_type_value_op';
  $handler->display->display_options['filters']['field_organization_type_value']['expose']['identifier'] = 'field_organization_type_value';
  $handler->display->display_options['filters']['field_organization_type_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  );
  $handler->display->display_options['path'] = 'advanced-search';
  $export['map'] = $view;

  $view = new view();
  $view->name = 'no_neighborhood';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'No Neighborhood';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'No Neighborhood Listed';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'project' => 'project',
  );
  /* Filter criterion: Content: Neighborhood (field_neighborhood) */
  $handler->display->display_options['filters']['field_neighborhood_tid']['id'] = 'field_neighborhood_tid';
  $handler->display->display_options['filters']['field_neighborhood_tid']['table'] = 'field_data_field_neighborhood';
  $handler->display->display_options['filters']['field_neighborhood_tid']['field'] = 'field_neighborhood_tid';
  $handler->display->display_options['filters']['field_neighborhood_tid']['operator'] = 'empty';
  $handler->display->display_options['filters']['field_neighborhood_tid']['value'] = '';
  $handler->display->display_options['filters']['field_neighborhood_tid']['vocabulary'] = 'neighborhood';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'no-neighborhood';
  $export['no_neighborhood'] = $view;

  $view = new view();
  $view->name = 'recently_added';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Recently Added';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Recently Added';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'time ago';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'project' => 'project',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['recently_added'] = $view;

  $view = new view();
  $view->name = 'sidebar_fields';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'field content for sidebar';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Address';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Address of the Project */
  $handler->display->display_options['fields']['field_address']['id'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['table'] = 'field_data_field_address';
  $handler->display->display_options['fields']['field_address']['field'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['label'] = '';
  $handler->display->display_options['fields']['field_address']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  $handler->display->display_options['fields']['field_address']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_address']['multi_type'] = 'ul';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'project' => 'project',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'address-block';

  /* Display: Map Sidebar Block */
  $handler = $view->new_display('block', 'Map Sidebar Block', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Map';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'ip_geoloc_leaflet';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => '',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['map'] = 'bing';
  $handler->display->display_options['style_options']['map_height'] = '200';
  $handler->display->display_options['style_options']['ip_geoloc_views_plugin_latitude'] = array(
    'field_geocoded_address' => 'field_geocoded_address',
  );
  $handler->display->display_options['style_options']['ip_geoloc_views_plugin_longitude'] = 'field_geocoded_address';
  $handler->display->display_options['style_options']['center_option'] = '0';
  $handler->display->display_options['style_options']['sync']['2'] = 0;
  $handler->display->display_options['style_options']['sync']['4'] = 0;
  $handler->display->display_options['style_options']['sync']['8'] = 1;
  $handler->display->display_options['style_options']['sync']['16'] = 1;
  $handler->display->display_options['style_options']['full_screen'] = 0;
  $handler->display->display_options['style_options']['scale_metric'] = 0;
  $handler->display->display_options['style_options']['scale_imperial'] = 0;
  $handler->display->display_options['style_options']['zoom_indicator'] = 0;
  $handler->display->display_options['style_options']['map_reset'] = 0;
  $handler->display->display_options['style_options']['map_cluster_toggle'] = 0;
  $handler->display->display_options['style_options']['mini_map']['on'] = 0;
  $handler->display->display_options['style_options']['mini_map']['height'] = '100';
  $handler->display->display_options['style_options']['mini_map']['width'] = '150';
  $handler->display->display_options['style_options']['mini_map']['toggle'] = 1;
  $handler->display->display_options['style_options']['mini_map']['zoom_delta'] = '-5';
  $handler->display->display_options['style_options']['cluster_differentiator']['cluster_differentiator_fields'] = array(
    '' => '',
  );
  $handler->display->display_options['style_options']['cluster_differentiator']['zoom_ranges'] = array(
    1 => '',
  );
  $handler->display->display_options['style_options']['cluster_differentiator']['cluster_tooltips'] = 0;
  $handler->display->display_options['style_options']['cluster_differentiator']['cluster_outline'] = '0';
  $handler->display->display_options['style_options']['cluster_aggregation']['aggregation_function'] = 'average';
  $handler->display->display_options['style_options']['cluster_aggregation']['ranges']['small'] = '10';
  $handler->display->display_options['style_options']['cluster_aggregation']['ranges']['medium'] = '100';
  $handler->display->display_options['style_options']['cluster_aggregation']['ranges']['large'] = '1000';
  $handler->display->display_options['style_options']['map_options']['maxzoom'] = '18';
  $handler->display->display_options['style_options']['map_options']['zoom'] = '14';
  $handler->display->display_options['style_options']['map_options']['scrollwheelzoom'] = '1';
  $handler->display->display_options['style_options']['map_options']['dragging'] = '1';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Address of the Project */
  $handler->display->display_options['fields']['field_address']['id'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['table'] = 'field_data_field_address';
  $handler->display->display_options['fields']['field_address']['field'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['label'] = '';
  $handler->display->display_options['fields']['field_address']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_address']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  $handler->display->display_options['fields']['field_address']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_address']['multi_type'] = 'ul';
  /* Field: Content: Geocoded Address */
  $handler->display->display_options['fields']['field_geocoded_address']['id'] = 'field_geocoded_address';
  $handler->display->display_options['fields']['field_geocoded_address']['table'] = 'field_data_field_geocoded_address';
  $handler->display->display_options['fields']['field_geocoded_address']['field'] = 'field_geocoded_address';
  $handler->display->display_options['fields']['field_geocoded_address']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_geocoded_address']['click_sort_column'] = 'geom';
  $handler->display->display_options['fields']['field_geocoded_address']['type'] = 'geofield_latlon';
  $handler->display->display_options['fields']['field_geocoded_address']['settings'] = array(
    'data' => 'full',
    'format' => 'decimal_degrees',
    'labels' => 1,
  );
  $handler->display->display_options['fields']['field_geocoded_address']['delta_offset'] = '0';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  $export['sidebar_fields'] = $view;

  return $export;
}
