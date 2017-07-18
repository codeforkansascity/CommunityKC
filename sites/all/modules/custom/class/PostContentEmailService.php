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

    $list_all = "";
    foreach ($projects as $project) {
      $user = $users[(int)$project->uid];
      $email = $user->mail;
      $fullname = $user->field_full_name['und'][0]['value'];
      $project_name = $project->title;
      $last_rev = $project->revision_timestamp;

      //Used only for testing
      $list_all = $list_all."Email: ".$email." | Info: ".$fullname."'s ".$project_name.PHP_EOL;

      //Queue up items - WIP
      /*
      $queue = new stdClass();
      $queue->uid = $uid;
      $queue->mail_type = 'custom_project_notification_email';
      $queue->tokens = serialize($tokens);
      $queue->created = REQUEST_TIME;
      $queue->sent = null;
      drupal_write_record( 'custom_notify_email_queue', $queue);
      */
    send_mail($list_all);
  }

}
