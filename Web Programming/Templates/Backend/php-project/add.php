<?php
header('Access-Control-Allow-Headers: Access-Control-Allow-Origin, Content-Type');
header('Access-Control-Allow-Origin: *');
header('Content-Type: application/json, charset=utf-8');

include 'config.php';

$json =  file_get_contents('php://input');

$obj = json_decode($json);

$field1 = $obj->{'title'};
$field2 = $obj->{'genre'};

$sql = "insert into Movies (title, genre) values ('$field1', '$field2')";

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
