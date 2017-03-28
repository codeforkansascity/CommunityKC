<?php


class GeoJsonService
{
	public function __construct()
	{
		
	}
	
	public function getProjectsGeoJson()
	{
		$projectNodeIds = array_keys(db_query("SELECT n.nid FROM {node} n WHERE n.type = :type AND n.status = 1", [
			':type' => 'project'
		])->fetchAllKeyed());
		
		$projects = node_load_multiple($projectNodeIds);
		$resultSet = [
			'type' => 'FeatureCollection',
			'features' => []
		];
		
		foreach ($projects as $project) {
			
			$properties = [
				'title' => $project->title,
				'address' => _custom_safe_get_field($project, 'field_address', LANGUAGE_NONE, 0, 'thoroughfare'),
				'city' => _custom_safe_get_field($project, 'field_address', LANGUAGE_NONE, 0, 'locality'),
				'state' => _custom_safe_get_field($project, 'field_address', LANGUAGE_NONE, 0, 'administrative_area'),
				'postal' => _custom_safe_get_field($project, 'field_address', LANGUAGE_NONE, 0, 'postal_code'),
				'description' => _custom_safe_get_field($project, 'body', LANGUAGE_NONE, 0, 'value'),
				'neighborhoods' => [],
				'project_type' => [],
				'marker_symbol' => ['blue']
			];
			
			$resultSet['features'][] = [
				'type' => 'Feature',
				'geometry' => [
					'type' => 'Point',
					'coordinates' => [
						_custom_safe_get_field($project, 'field_geocoded_address', LANGUAGE_NONE, 0, 'lat'),
						_custom_safe_get_field($project, 'field_geocoded_address', LANGUAGE_NONE, 0, 'lon'),
					]
				],
				'properties' => $properties
			];
		}
		
		return $resultSet;
	}
}