<?php


/**
 * Implements hook_services_resources()
 * Defines resources and operations on those resources for the service module that are custom to this module.
 * Operations are considered only CRUD and Index. Create is POST, UPDATE is PUT, Retrieve is GET, Delete is DELETE
 * Actions are performed on the resource type, not an individual resource. Can only use POST.
 * Targed actions are performed on an individual resource. They can only use POST
 * @see https://github.com/hugowetterberg/rest_server
 */
function custom_services_resources() {
  $resources = array(
    '#api_version' => 3001
  );
  $resources['project'] = array(
    'operations' => array(
      'index' => array(
        'access callback' => '_custom_api_access',
        'args' => array(
          array(
            'name' => 'neighborhood',
            'optional' => TRUE,
            'type' => 'int',
            'description' => 'neighborhood tid',
            'source' => array('param' => 'neighborhood'),
          ),
          array(
            'name' => 'type',
            'optional' => TRUE,
            'type' => 'int',
            'description' => 'project type tid',
            'source' => array('param' => 'project_type'),
          ),
        ),
        'file' => array(
          'type' => 'inc',
          'module' => 'custom',
          'name' => 'project/project.resource'
        ),
        'callback' => 'custom_project_resource_index'
      ),
      'retrieve' => array(
        'access callback' => '_custom_api_access',
        'args' => array(
          array(
            'name' => 'project_id',
            'optional' => FALSE,
            'type' => 'int',
            'description' => 'Node id of project',
            'source' => array('path' => 0),
          ),
        ),
        'file' => array(
          'type' => 'inc',
          'module' => 'custom',
          'name' => 'project/project.resource'
        ),
        'callback' => 'custom_project_resource_retrieve'
      ),
    ),
  );
  $resources['neighborhood'] = array(
    'operations' => array(
      'index' => array(
        'access callback' => '_custom_api_access',
        'file' => array(
          'type' => 'inc',
          'module' => 'custom',
          'name' => 'neighborhood/neighborhood.resource'
        ),
        'callback' => 'custom_neighborhood_resource_index'
      ),
    ),
  );
  $resources['project_type'] = array(
    'operations' => array(
      'index' => array(
        'access callback' => '_custom_api_access',
        'file' => array(
          'type' => 'inc',
          'module' => 'custom',
          'name' => 'project/project.resource',
        ),
        'callback' => 'custom_project_type_resource_index'
      ),
    ),
  );

  return $resources;
}

function _custom_api_access() {
  return true;
}

