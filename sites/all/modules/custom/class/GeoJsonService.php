<?php


class GeoJsonService
{
	const PROJECT_TYPES_TAXONOMY_ID = 2;
	const NEIGHBORHOODS_TAXONOMY_ID = 1;
	
	private static $taxonomyMemoizationList = [];
	
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
			$projectTypesRaw = $project->field_project_type['und'];
			$neighborhoodsRaw = $project->field_neighborhood['und'];
			
			$projectTypes = array_map(function ($obj) {
				return $obj['tid'];
			}, $projectTypesRaw);
			$projectTypes = $this->projectTypes($projectTypes);
			
			$neighborhoods = array_map(function ($obj) {
				return $obj['tid'];
			}, $neighborhoodsRaw);
			$neighborhoods = $this->neighborhoods($neighborhoods);
			
			$properties = [
				'title' => $project->title,
				'address' => _custom_safe_get_field($project, 'field_address', LANGUAGE_NONE, 0, 'thoroughfare'),
				'city' => _custom_safe_get_field($project, 'field_address', LANGUAGE_NONE, 0, 'locality'),
				'state' => _custom_safe_get_field($project, 'field_address', LANGUAGE_NONE, 0, 'administrative_area'),
				'postal' => _custom_safe_get_field($project, 'field_address', LANGUAGE_NONE, 0, 'postal_code'),
				'description' => _custom_safe_get_field($project, 'body', LANGUAGE_NONE, 0, 'value'),
				'neighborhoods' => $neighborhoods,
				'project_type' => $projectTypes,
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
	
	
	private function neighborhoods($neighborhoods)
	{
		if (is_null($neighborhoods))
			return [];
		
		$this->setupTaxonomyMemoization(self::NEIGHBORHOODS_TAXONOMY_ID, 'neighborhoods', function ($taxonomy) {
			return $taxonomy->name;
		});
		
		return $this->buildList('neighborhoods', $neighborhoods);
	}
	
	
	private function projectTypes($types)
	{
		if (is_null($types))
			return [];
		
		$this->setupTaxonomyMemoization(self::PROJECT_TYPES_TAXONOMY_ID, 'projectTypes', function ($taxonomy) {
			return $taxonomy->name;
		});
		
		return $this->buildList('projectTypes', $types);
	}
	
	
	private function setupTaxonomyMemoization($id, $name, Callable $propertyReturn)
	{
		if (!empty(self::$taxonomyMemoizationList[$name]))
			return;
		
		$taxonomies = taxonomy_get_tree($id);
		foreach ($taxonomies as $taxonomy) {
			self::$taxonomyMemoizationList[$name][$taxonomy->tid] = $propertyReturn($taxonomy);
		}
	}
	
	
	private function getTaxonomy($name, $tid)
	{
		if (empty(self::$taxonomyMemoizationList[$name][$tid]))
			return '';
		
		return self::$taxonomyMemoizationList[$name][$tid];
	}
	
	
	private function buildList($name, array $items)
	{
		$taxonomies = [];
		foreach ($items as $tid) {
			$taxonomy = $this->getTaxonomy($name, $tid);
			
			if (empty($taxonomy))
				continue;
			
			$taxonomies[] = $taxonomy;
		}
		
		return $taxonomies;
	}
}