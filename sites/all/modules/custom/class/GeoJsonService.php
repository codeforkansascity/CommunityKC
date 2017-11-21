<?php


class GeoJsonService
{
	const PROJECT_TYPES_TAXONOMY_ID = 2;
	const NEIGHBORHOODS_TAXONOMY_ID = 1;

	private static $taxonomyMemoizationList = [];
	private static $projectMarkerMap = [
		0   => '#808080', // 'gray',        // Gray color for project types without parents
		460 => '#0000FF', // 'blue',	      // Resource
		457 => '#FFA500', // 'orange',      // Economic Development and Housing
		461 => '#ADD8E6', // 'light-blue',	// Education, Arts, and Culture
		458 => '#008000',	// 'green'        // Environment and Energy
		459 => '#FFFF00', // 'yellow',	    // Public Health and Safety
		456 => '#B22222', // 'fire-brick',	// Capacity Building
	];

	public function __construct()
	{

	}

	public function getProjectsGeoJson()
	{
    // find node ids of all project nodes that are published

		$projectNodeIds = db_query("SELECT n.nid FROM {node} n WHERE n.type = :type AND n.status = 1", [
			':type' => 'project'
    ])->fetchCol(0);

    // load all the nodes at once
		$projects = node_load_multiple($projectNodeIds);
		$resultSet = [
			'type' => 'FeatureCollection',
			'features' => []
		];
    // loop through loaded nodes
		foreach ($projects as $project) {

      $projectTypes = [];
			if (!empty($project->field_project_type['und'])) {
        $projectTypes = array_map(function ($obj) {
          return $obj['tid'];
        }, $project->field_project_type['und']);
        $projectTypes = $this->projectTypes($projectTypes);
      }

			$projectTypeNames = [];
			$projectTypeMarkers = [];
			foreach ($projectTypes as $projectType) {
				$projectTypeNames[] = $projectType['taxonomy']->name;

				$colorId = $projectType['parent']->tid;
				$projectTypeMarkers[] = (isset(self::$projectMarkerMap[$colorId])) ? self::$projectMarkerMap[$colorId] : self::$projectMarkerMap[$colorId][0];
			}

			$projectTypeMarkers = array_values(array_unique($projectTypeMarkers));

      $neighborhoods = [];
      if (!empty($project->field_neighborhood['und'])) {
        $neighborhoods = array_map(function ($obj) {
          return $obj['tid'];
        }, $project->field_neighborhood['und']);
        $neighborhoods = $this->neighborhoods($neighborhoods);
      }

			$properties = [
        'nid' => $project->nid,
				'title' => $project->title,
				'address' => _custom_safe_get_field($project, 'field_address', LANGUAGE_NONE, 0, 'thoroughfare'),
				'city' => _custom_safe_get_field($project, 'field_address', LANGUAGE_NONE, 0, 'locality'),
				'state' => _custom_safe_get_field($project, 'field_address', LANGUAGE_NONE, 0, 'administrative_area'),
				'postal' => _custom_safe_get_field($project, 'field_address', LANGUAGE_NONE, 0, 'postal_code'),
				'description' => _custom_safe_get_field($project, 'body', LANGUAGE_NONE, 0, 'value'),
				'neighborhoods' => $neighborhoods,
				'project_type' => $projectTypeNames,
       // 'marker_symbol' => $projectTypeMarkers,
        'marker-color' => count($projectTypeMarkers)>0 ? $projectTypeMarkers[0] : 'gray'
			];

			$resultSet['features'][] = [
				'type' => 'Feature',
				'geometry' => [
					'type' => 'Point',
					'coordinates' => [
						doubleval(_custom_safe_get_field($project, 'field_geocoded_address', LANGUAGE_NONE, 0, 'lon')),
						doubleval(_custom_safe_get_field($project, 'field_geocoded_address', LANGUAGE_NONE, 0, 'lat')),
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
			$parents = taxonomy_get_parents($taxonomy->tid);
			$parent = $taxonomy;
			if (!empty($parents))
				$parent = array_shift($parents);

			return [
				'taxonomy' => $taxonomy,
				'parent' => $parent
			];
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
