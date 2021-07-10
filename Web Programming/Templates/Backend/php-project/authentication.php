<?php
session_id("mySessionId");
session_start();

header('Access-Control-Allow-Headers: Access-Control-Allow-Origin, Content-Type');
header('Access-Control-Allow-Origin: *');
header('Content-Type: application/json, charset=utf-8');

include 'config.php';

$json =  file_get_contents('php://input');

$obj = json_decode($json);

$username = $obj->{'username'};
$password = $obj->{'password'};

$sql = "select * from Users u where u.username = '$username' and u.password = '$password'";

if (!empty($link)) {
    if($result = mysqli_query($link, $sql)){
        if(mysqli_num_rows($result) > 0){
            echo $json;
        } else{
            header("HTTP/1.0 404 Not Found");
        }
    } else{
        header("HTTP/1.0 404 Not Found");
    }
    // Close connection
    mysqli_close($link);
}

