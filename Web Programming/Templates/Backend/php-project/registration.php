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

$sql = "insert into Users (username, password) values ('$username', '$password')";

if (!empty($link)) {
//  mysqli_query($link, $sql);
    if (mysqli_query($link, $sql)) {
        echo $json;
    }
    else {
        header("HTTP/1.0 404 Not Found");
    }
    mysqli_close($link);
}
