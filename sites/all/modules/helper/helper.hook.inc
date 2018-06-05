<?php

function _helper_hook_info_groups() {
  // Add modulename.group.inc support for most core hooks.
  $groups['block'] = array(
    'block_configure', 'block_info', 'block_info_alter', 'block_list_alter',
    'block_save', 'block_view', 'block_view_alter',
  );
  $groups['comment'] = array(
    'comment_delete', 'comment_insert', 'comment_load', 'comment_presave',
    'comment_publish', 'comment_unpublish', 'comment_update', 'comment_view',
    'comment_view_alter',
  );
  $groups['cron'] = array(
    'cron', 'cron_queue_info', 'cron_queue_info_alter',
  );
  $groups['date'] = array(
    'date_formats', 'date_formats_alter', 'date_format_types',
    'date_format_types_alter', 'format_date_alter',
  );
  $groups['entity'] = array(
    'entity_delete', 'entity_info', 'entity_info_alter', 'entity_insert',
    'entity_load', 'entity_prepare_view', 'entity_presave',
    'entity_query_alter', 'entity_update', 'entity_view', 'entity_view_alter',
  );
  $groups['field'] = array(
    'field_access',
    'field_attach_create_bundle',
    'field_attach_delete',
    'field_attach_delete_bundle',
    'field_attach_delete_revision',
    'field_attach_form',
    'field_attach_insert',
    'field_attach_load',
    'field_attach_prepare_translation_alter',
    'field_attach_preprocess_alter',
    'field_attach_presave',
    'field_attach_purge',
    'field_attach_rename_bundle',
    'field_attach_submit',
    'field_attach_update',
    'field_attach_validate',
    'field_attach_view_alter',
    'field_available_languages_alter',
    'field_create_field',
    'field_create_instance',
    'field_delete_field',
    'field_delete_instance',
    'field_extra_fields',
    'field_extra_fields_alter',
    'field_extra_fields_display_alter',
    'field_formatter_info',
    'field_formatter_info_alter',
    'field_info',
    'field_info_alter',
    'field_purge_field',
    'field_purge_instance',
    'field_read_field',
    'field_read_instance',
    'field_storage_create_field',
    'field_storage_delete_field',
    'field_storage_delete_instance',
    'field_storage_details_alter',
    'field_storage_info',
    'field_storage_info_alter',
    'field_storage_pre_insert',
    'field_storage_pre_load',
    'field_storage_pre_update',
    'field_update_field',
    'field_update_forbid',
    'field_update_instance',
    'field_widget_info',
    'field_widget_info_alter',
  );
  $groups['file'] = array(
    'file_copy', 'file_delete', 'file_download', 'file_download_access',
    'file_download_access_alter', 'file_insert', 'file_load',
    'file_mimetype_mapping_alter', 'file_move', 'file_presave', 'file_update',
    'file_url_alter', 'file_validate',
  );
  $groups['image'] = array(
    'image_default_styles', 'image_effect_info', 'image_effect_info_alter',
    'image_styles_alter', 'image_style_delete', 'image_style_flush',
    'image_style_save', 'image_toolkits',
  );
  $groups['menu'] = array(
    'menu', 'menu_alter', 'menu_breadcrumb_alter',
    'menu_contextual_links_alter', 'menu_delete', 'menu_get_item_alter',
    'menu_insert', 'menu_link_alter', 'menu_link_delete', 'menu_link_insert',
    'menu_link_update', 'menu_local_tasks_alter', 'menu_site_status_alter',
    'menu_update',
  );
  $groups['node'] = array(
    'node_access', 'node_access_records', 'node_access_records_alter',
    'node_delete', 'node_grants', 'node_grants_alter', 'node_info',
    'node_insert', 'node_load', 'node_operations', 'node_prepare',
    'node_presave', 'node_revision_delete', 'node_search_result',
    'node_submit', 'node_type_delete', 'node_type_insert', 'node_type_update',
    'node_update', 'node_update_index', 'node_validate', 'node_view',
    'node_view_alter',
  );

  // Contrib modules.
  $groups['admin_menu'] = array(
    'admin_menu_replacements', 'admin_menu_output_build',
    'admin_menu_output_alter', 'admin_menu_map', 'admin_menu_map_alter',
    'admin_menu_cache_info',
  );

  return $groups;
}
