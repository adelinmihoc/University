<?php
header('Access-Control-Allow-Headers: Access-Control-Allow-Origin, Content-Type');
header('Access-Control-Allow-Origin: *');
header('Content-Type: application/json, charset=utf-8');

include 'config.php';
$json =  file_get_contents('php://input');

$obj = json_decode($json);

$id = $obj->{'id'};
$sql = "delete from user where U_id=$id";
if (!empty($link)) {
    if (mysqli_query($link, $sql)) {
        echo json_encode(array("statusCode" => 200));
    } else {
        echo json_encode(array("statusCode" => 201));
    }
    mysqli_close($link);
}
