<?php

/**
 * Implements hook_default_services_endpoint()
 * Defines services (api calls) that are supported by this module
 * This populates the admin shown in /admin/structure/services/list/api
 * Settings can be overridden in the database, but they will revert to these.
 * Resource list has to match resources defined in custom.resources.inc hook_services_resources()
 * That hook defines possible resources, this list defines which ones are enabled for this service definition.
 */
function custom_default_services_endpoint()
{
	$endpoints = array();
	$endpoint = new stdClass();
	$endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
	$endpoint->api_version = 3;
	$endpoint->name = 'api';
	$endpoint->server = 'rest_server';
  $endpoint->path = 'api/v1';
  $endpoint->authentication = array();
  $endpoint->server_settings = array(
    'formatters' => array(
      'json' => TRUE,
      'bencode' => FALSE,
      'jsonp' => FALSE,
      'php' => FALSE,
      'xml' => FALSE,
      'yaml' => FALSE,
    ),
    'parsers' => array(
      'application/json' => TRUE,
      'application/vnd.php.serialized' => FALSE,
      'application/x-www-form-urlencoded' => FALSE,
      'application/x-yaml' => FALSE,
      'application/xml' => FALSE,
      'multipart/form-data' => FALSE,
      'text/xml' => FALSE,
    ),
  );
  $endpoint->resources = array(
    'project' => array(
      'operations' => array(
        'index' => array('enabled' => '1', 'description' => 'Get GEOJson formatted data for projects by neighborhood and type or for all projects'), // geojson project list
        'retrieve' => array('enabled' => '1', 'description' => 'Get data for individual project') // project display
      ),
    ),
    'neighborhood' => array(
      'operations' => array(
        'index' => array('enabled' => '1'), // list of neighborhoods
      ),
    ),
    'project_type' => array(
      'operations' => array(
        'index' => array('enabled' => '1'),
      ),
    ),
  );
  $endpoint->debug = 0;
  $endpoints['api'] = $endpoint;
  return $endpoints;
}
