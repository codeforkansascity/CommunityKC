<?php


// CCF_Node - holds all projects. Use changed field for criteria
class PostContentEmailService
{
  public function __construct()
  {

  }

  public function run()
  {

    $sql_query = "SELECT     
                    n.nid,
                    n.uid,
                    n.changed
                  FROM ccf_node n 
                  WHERE 
                    n.type = 'project' AND
                    n.status = 1 AND
                    n.changed <= UNIX_TIMESTAMP( DATE_ADD(DATE_ADD(CURDATE(), INTERVAL -6 MONTH), INTERVAL -1 SECOND) );
                  ";
    
    //Using above query, load the projects
    $projectNodeIds = array_keys(db_query($sql_query)->fetchAllKeyed());
		$projects = node_load_multiple($projectNodeIds);
    //Go through each project to 1) Send email to owner and 2) Set the timestamp to now

    //Trying to get a field from node
    foreach ($projects as &$project){
      $some_variable = $project->field_project_type[$project->language][0]['value'];
    }
    //Watchdog - used for testing 
    //watchdog([module name], [message string], [array of token replacements], [severity constant]);
    watchdog(     
      'custom',
      'Result: !some',
      array('!some'=>$some_variable),
      WATCHDOG_DEBUG 
    );
  }

}
