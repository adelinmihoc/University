<?php
session_id("mySessionId");
session_start();

header('Access-Control-Allow-Headers: Access-Control-Allow-Origin, Content-Type');
header('Access-Control-Allow-Origin: *');
header('Content-Type: application/json, charset=utf-8');

require_once "config.php";

$sql = "SELECT * FROM Movies";
$entities = array();
if (!empty($link)) {
    if($result = mysqli_query($link, $sql)){
        if(mysqli_num_rows($result) > 0){
            while($row = mysqli_fetch_array($result)) {
                $entity = new StdClass();
                $entity->id = $row['id'];
                $entity->title = $row['title'];
                $entity->genre = $row['genre'];

                array_push($entities, $entity);
            }

            mysqli_free_result($result);
        } else{
            header("HTTP/1.0 404 Not Found");
        }
    } else{
        header("HTTP/1.0 404 Not Found");
    }
    // Close connection
    mysqli_close($link);
    echo json_encode($entities);
}
