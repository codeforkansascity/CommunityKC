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
                    n.uid
                  FROM ccf_node n
                  WHERE
                    n.type = 'project' AND
                    n.status = 1 AND
                    n.changed <= UNIX_TIMESTAMP( DATE_ADD(DATE_ADD(CURDATE(), INTERVAL -6 MONTH), INTERVAL -1 SECOND) );
                  ";

    $queryResults = db_query($sql_query)->fetchAll();
    if (empty($queryResults))
      return;

    $length = count($queryResults);
    $projectNodeIds = array_fill(0, $queryResults, null);
    $projectUserIds = array_fill(0, $queryResults, null);

    for ($i = 0; $i < $length; $i++) {
      $projectId = intval($queryResults[$i]->nid);
      $projectNodeIds[$i] = $projectId;
      $projectUserIds[$projectId] = intval($queryResults[$i]->uid);
    }

    $users = user_load_multiple($projectUserIds);
    $projects = node_load_multiple($projectNodeIds);


    foreach ($projects as $project) {
      $user = $users[(int)$project->uid];
      $email = $user->mail;
      $fullname = $user->field_full_name['und'][0]['value'];
      $project_name = $project->title;
      $last_rev = $project->revision_timestamp;
      $test = 0;

      // Using above four vars, send email to myself.
    }
  }

}
