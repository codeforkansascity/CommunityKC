<?php
/**
 * @file
 * custom_feature.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function custom_feature_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_about|node|project|form';
  $field_group->group_name = 'group_about';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'project';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'About You',
    'weight' => '0',
    'children' => array(
      0 => 'field_your_name',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-about field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_about|node|project|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_location|node|project|form';
  $field_group->group_name = 'group_location';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'project';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Location',
    'weight' => '3',
    'children' => array(
      0 => 'field_geocoded_address',
      1 => 'field_address',
      2 => 'field_if_your_project_is_area_wi',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Location',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-location field-group-fieldset',
        'description' => 'Add the address of your project. If your project has more than one location you can use the address of your organization or click "Add Another Address" to enter more locations. ',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $field_groups['group_location|node|project|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_media|node|project|form';
  $field_group->group_name = 'group_media';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'project';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Media',
    'weight' => '2',
    'children' => array(
      0 => 'field_photos',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Media',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-media field-group-fieldset',
        'description' => 'A picture is worth a thousand words and helps users connect with your project. You can add up to five photos of your project. If your project is still in the planning phase, you can even add pictures of the future project site, group members, or the problem your project will address.
',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $field_groups['group_media|node|project|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_org|node|project|form';
  $field_group->group_name = 'group_org';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'project';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Organization Info',
    'weight' => '4',
    'children' => array(
      0 => 'field_organization_name',
      1 => 'field_organization_website_or_ph',
      2 => 'field_organization_type',
      3 => 'field_lead_contact_person',
      4 => 'field_lead_contact_email',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-org field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_org|node|project|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_project|node|project|form';
  $field_group->group_name = 'group_project';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'project';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'About the Project',
    'weight' => '1',
    'children' => array(
      0 => 'body',
      1 => 'field_project_website',
      2 => 'field_year_established',
      3 => 'field_phase',
      4 => 'field_partners',
      5 => 'field_neighborhood',
      6 => 'field_project_type',
      7 => 'field_funder',
      8 => 'title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'About the Project',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-project field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $field_groups['group_project|node|project|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('About You');
  t('About the Project');
  t('Location');
  t('Media');
  t('Organization Info');

  return $field_groups;
}
