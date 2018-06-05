<?php

class FieldChangeHelper {

  /**
   * Change a field's type, even if it has data.
   *
   * @param $field_name
   *   The name of the field to change.
   * @param $type
   *   The type of field to change it to.
   * @param array $column_renames
   *   An array of existing field schema columns to rename. For example, if the
   *   old field type has a column 'value' which maps to the new field type's
   *   'data' column, use array('value' => 'data') to ensure the old column
   *   is just renamed instead of dropped. To ensure an old field column is
   *   dropped, for example, if the same column name is used in the new
   *   field type, but is used to store different data, use
   *   array('old_column' => FALSE).
   * @param array $field_overrides
   *   An optional array that overrides any of the values in the $field
   *   definition array prior to saving.
   * @param array $field_instance_overrides
   *   An optional array that overrides any of the values in any of the field's
   *   instance definition array prior to saving.
   *
   * @return array
   *   The change field if everything was successful.
   *
   * @throws Exception
   */
  public static function changeType($field_name, $type, array $column_renames = array(), array $field_overrides = array(), array $field_instance_overrides = array()) {
    $field = $prior_field = field_read_field($field_name);
    if (empty($field)) {
      throw new Exception("Field $field_name does not exist or is inactive or deleted.");
    }

    if ($field['type'] === $type) {
      throw new Exception("Field $field_name is already type $type.");
    }

    if ($field['storage']['type'] !== 'field_sql_storage') {
      throw new Exception("Unable to change field type for field {$field_name} using storage {$field['storage']['type']}.");
    }

    $type_info = field_info_field_types($type);
    if (empty($type_info)) {
      throw new Exception("Invalid field type $type.");
    }

    $transaction = db_transaction();
    try {
      // Serialize properties back into the data property so it can be saved
      // to the database.
      $field['data'] = array();
      foreach ($field as $key => $value) {
        switch ($key) {
          case 'id':
          case 'field_name':
          case 'type':
          case 'module':
          case 'active':
          case 'locked':
          case 'cardinality':
          case 'deleted':
          case 'data':
            break;

          default:
            $field['data'][$key] = &$field[$key];
        }
      }

      // Update basic information on the field config.
      $field['type'] = $type;
      $field['module'] = $type_info['module'];
      $field['settings'] = array_intersect_key($field['settings'], $type_info['settings']);
      $field['settings'] += $type_info['settings'];

      // @todo Check if $field['translatable'] needs to be changed.

      // Make any final field overrides before updating the schema and saving
      // the field config record back to the database.
      $field = drupal_array_merge_deep($field, $field_overrides);
      static::changeSchema($field, $column_renames);
      drupal_write_record('field_config', $field, array('id'));

      // Now update the instances for this field.
      static::changeInstances($field, $field_instance_overrides);

      // Clear caches
      field_cache_clear();

      // Invoke external hooks after the cache is cleared for API consistency.
      $has_data = field_has_data($field);
      module_invoke_all('field_update_field', $field, $prior_field, $has_data);

      watchdog('helper', "Converted field $field_name from {$prior_field['type']} to {$type}.");

      return $field;
    }
    catch (Exception $e) {
      $transaction->rollback();
      watchdog_exception('helper', $e);
      throw $e;
    }
  }

  public static function changeSchema(array &$field, array $column_renames = array()) {
    // Update the field schema
    $old_schema = array_intersect_key($field, array('columns' => '', 'indexes' => '', 'foreign keys' => ''));
    module_load_install($field['module']);
    $new_schema = (array) module_invoke($field['module'], 'field_schema', $field);
    $new_schema += array('columns' => array(), 'indexes' => array(), 'foreign keys' => array());
    $field['data']['columns'] = $new_schema['columns'];
    $field['data']['indexes'] = $new_schema['indexes'];
    $field['data']['foreign keys'] = $new_schema['foreign keys'];

    $data_table = _field_sql_storage_tablename($field);
    $revision_table = _field_sql_storage_revision_tablename($field);

    // Validate that all the columns described in the existing schema actually exist.
    foreach (array_keys($old_schema['columns']) as $old_column) {
      $old_column_name = _field_sql_storage_columnname($field['field_name'], $old_column);
      if (!db_field_exists($data_table, $old_column_name)) {
        throw new Exception();
      }
      if (!db_field_exists($revision_table, $old_column_name)) {
        throw new Exception();
      }
      // Attempt to re-use any columns that have the same name.
      // This can be skipped by setting $column_renames['column-name'] = FALSE;
      if (!empty($new_schema['columns'][$old_column]) && !isset($column_renames[$old_column])) {
        $column_renames[$old_column] = $old_column;
      }
    }

    // Validate that any columns to be renamed actually exist.
    foreach ($column_renames as $old_column => $new_column) {
      if (!isset($old_schema['columns'][$old_column])) {
        throw new Exception("Cannot rename field {$field['field_name']} column {$old_column} because it does not exist in the old schema.");
      }
      if (!isset($new_schema['columns'][$new_column])) {
        throw new Exception("Cannot rename field {$field['field_name']} column {$old_column} to {$new_column} because it does not exist in the new schema.");
      }
    }

    // Remove all existing indexes.
    foreach ($old_schema['indexes'] as $index => $index_fields) {
      $index_name =_field_sql_storage_indexname($field['field_name'], $index);
      if (db_index_exists($data_table, $index_name)) {
        watchdog('helper', "Dropped index $data_table.$index_name");
        db_drop_index($data_table, $index_name);
      }
      if (db_index_exists($revision_table, $index_name)) {
        watchdog('helper', "Dropped index $revision_table.$index_name");
        db_drop_index($revision_table, $index_name);
      }
    }

    // Rename any columns.
    foreach ($column_renames as $old_column => $new_column) {
      $old_column_name = _field_sql_storage_columnname($field['field_name'], $old_column);
      if ($new_column === FALSE) {
        db_drop_field($data_table, $old_column_name);
        watchdog('helper', "Dropped column $data_table.$old_column_name");
        db_drop_field($revision_table, $old_column_name);
        watchdog('helper', "Dropped column $revision_table.$old_column_name");
        unset($old_schema['columns'][$old_column]);
      }
      else {
        $new_column_name = _field_sql_storage_columnname($field['field_name'], $new_column);
        db_change_field($data_table, $old_column_name, $new_column_name, $new_schema['columns'][$new_column]);
        watchdog('helper', "Changed column $data_table.$old_column_name<br/><pre>" . print_r($new_schema['columns'][$new_column], TRUE) . '</pre>');
        db_change_field($revision_table, $old_column_name, $new_column_name, $new_schema['columns'][$new_column]);
        watchdog('helper', "Changed column $revision_table.$old_column_name<br/><pre>" . print_r($new_schema['columns'][$new_column], TRUE) . '</pre>');
        // Remove these fields so they aren't removed or added in the code below.
        unset($new_schema['columns'][$new_column]);
        unset($old_schema['columns'][$old_column]);
      }
    }

    // Remove any old columns.
    $old_columns = array_diff_key($old_schema['columns'], $new_schema['columns']);
    foreach (array_keys($old_columns) as $old_column) {
      $old_column_name = _field_sql_storage_columnname($field['field_name'], $old_column);
      db_drop_field($data_table, $old_column_name);
      watchdog('helper', "Dropped column $data_table.$old_column_name");
      db_drop_field($revision_table, $old_column_name);
      watchdog('helper', "Dropped column $revision_table.$old_column_name");
    }

    // Add any new columns.
    $new_columns = array_diff_key($new_schema['columns'], $old_schema['columns']);
    foreach (array_keys($new_columns) as $new_column) {
      $new_column_name = _field_sql_storage_columnname($field['field_name'], $new_column);
      db_add_field($data_table, $new_column_name, $new_schema['columns'][$new_column]);
      watchdog('helper', "Added column $data_table.$new_column_name");
      db_add_field($revision_table, $new_column_name, $new_schema['columns'][$new_column]);
      watchdog('helper', "Added column $revision_table.$new_column_name");
    }

    // Re-add indexes.
    foreach ($new_schema['indexes'] as $index => $index_fields) {
      foreach ($index_fields as &$index_field) {
        if (is_array($index_field)) {
          $index_field[0] = _field_sql_storage_columnname($field['field_name'], $index_field[0]);
        }
        else {
          $index_field = _field_sql_storage_columnname($field['field_name'], $index_field);
        }
      }
      $index_name =_field_sql_storage_indexname($field['field_name'], $index);
      db_add_index($data_table, $index_name, $index_fields);
      watchdog('helper', "Added index $data_table.$index_name<br/><pre>" . print_r($index_fields, TRUE) . '</pre>');
      db_add_index($revision_table, $index_name, $index_fields);
      watchdog('helper', "Added index $revision_table.$index_name<br/><pre>" . print_r($index_fields, TRUE) . '</pre>');
    }
  }

  public static function changeInstances(array $field, array $field_instance_overrides = array()) {
    $type_info = field_info_field_types($field['type']);
    $instances = field_read_instances(array('field_name' => $field['field_name']));

    foreach ($instances as $instance) {
      $prior_instance = $instance;

      // Serialize properties back into the data property so it can be saved
      // to the database.
      $instance['data'] = array();
      foreach ($instance as $key => $value) {
        switch ($key) {
          case 'id':
          case 'field_id':
          case 'field_name':
          case 'entity_type':
          case 'bundle':
          case 'deleted':
          case 'data':
            break;

          default:
            $instance['data'][$key] = &$instance[$key];
        }
      }

      $instance['settings'] = array_intersect_key($instance['settings'], $type_info['instance_settings']);
      $instance['settings'] += $type_info['instance_settings'];

      // Validate the existing widget can be used with the new field type.
      $widget_info = field_info_widget_types($instance['widget']['type']);
      if (!in_array($field['type'], $widget_info['field types'])) {
        // Fallback to using the field type's default widget.
        $instance['widget']['type'] = $type_info['default_widget'];
        $widget_info = field_info_widget_types($type_info['default_widget']);
        $instance['widget']['module'] = $widget_info['module'];
        $instance['widget']['settings'] = array_intersect_key($instance['widget']['settings'], $widget_info['settings']);
        $instance['widget']['settings'] += $widget_info['settings'];
      }

      // Validate the existing formatters can be used with the new field type.
      foreach ($instance['display'] as $view_mode => $display) {
        if ($display['type'] !== 'hidden') {
          $formatter_info = field_info_formatter_types($display['type']);
          if (!in_array($field['type'], $formatter_info['field types'])) {
            // Fallback to using the field type's default formatter.
            $instance['display'][$view_mode]['type'] = $type_info['default_formatter'];
            $formatter_info = field_info_formatter_types($type_info['default_formatter']);
            $instance['display'][$view_mode]['module'] = $formatter_info['module'];
            $instance['display'][$view_mode]['settings'] = array_intersect_key($instance['display'][$view_mode], $formatter_info['settings']);
            $instance['display'][$view_mode]['settings'] += $formatter_info['settings'];

          }
        }
      }

      // Allow anything to be overridden before it gets saved.
      $instance = drupal_array_merge_deep($instance, $field_instance_overrides);

      drupal_write_record('field_config_instance', $instance, array('id'));

      // Clear caches.
      field_cache_clear();

      module_invoke_all('field_update_instance', $instance, $prior_instance);
    }
  }

  public static function changeInstanceField(array $instance, $new_field_name) {
    $old_field = field_info_field($instance['field_name']);
    $new_field = field_info_field($new_field_name);

    if ($old_field['type'] != $new_field['type']) {
      throw new FieldException("Cannot change field instance because they are not the same field type.");
    }
    if ($old_field['storage']['type'] !== 'field_sql_storage') {
      throw new FieldException("Unable to change field type for field {$old_field['field_name']} using storage {$old_field['storage']['type']}.");
    }
    if ($new_field['storage']['type'] !== 'field_sql_storage') {
      throw new FieldException("Unable to change field type for field {$new_field['field_name']} using storage {$new_field['storage']['type']}.");
    }

    if (!field_info_instance($instance['entity_type'], $new_field_name, $instance['bundle'])) {
      $new_instance = $instance;
      $new_instance['field_name'] = $new_field_name;
      field_create_instance($new_instance);
      watchdog('helper', "Created new field instance: {$instance['entity_type']}.{$instance['bundle']}.{$new_field_name}");
    }

    // Copy data from old field tables to the new field tables.
    $old_data_table = _field_sql_storage_tablename($old_field);
    $new_data_table = _field_sql_storage_tablename($new_field);
    $query = db_select($old_data_table, 'old');
    $query->fields('old');
    $query->condition('entity_type', $instance['entity_type']);
    $query->condition('bundle', $instance['bundle']);
    db_insert($new_data_table)
      ->from($query)
      ->execute();

    $old_revision_table = _field_sql_storage_revision_tablename($old_field);
    if (db_table_exists($old_revision_table)) {
      $new_revision_table = _field_sql_storage_revision_tablename($new_field);
      $query = db_select($old_revision_table, 'old');
      $query->fields('old');
      $query->condition('entity_type', $instance['entity_type']);
      $query->condition('bundle', $instance['bundle']);
      db_insert($new_revision_table)
        ->from($query)
        ->execute();
    }

    FieldHelper::deleteInstance($instance);
  }

  public static function mergeFields($old_field_name, $new_field_name) {
    $old_field = field_info_field($old_field_name);
    $new_field = field_info_field($new_field_name);

    if (empty($old_field)) {
      throw new FieldException("Field {$old_field_name} does not exist.");
    }
    if (empty($new_field)) {
      throw new FieldException("Field {$new_field_name} does not exist.");
    }
    if ($old_field['type'] != $new_field['type']) {
      throw new FieldException("Cannot merge fields because they are not the same field type.");
    }
    if ($old_field['storage']['type'] !== 'field_sql_storage') {
      throw new FieldException("Unable to change field type for field {$old_field['field_name']} using storage {$old_field['storage']['type']}.");
    }
    if ($new_field['storage']['type'] !== 'field_sql_storage') {
      throw new FieldException("Unable to change field type for field {$new_field['field_name']} using storage {$new_field['storage']['type']}.");
    }

    $instances = field_read_instances(array('field_name' => $old_field_name));
    foreach ($instances as $instance) {
      static::changeInstanceField($instance, $new_field_name);
    }

    // I don't think this is necessary since this will remove all the instances
    // for a field, which deletes the field as well.
    // FieldHelper::deleteField($old_field);
  }
}
