<?php
header('Access-Control-Allow-Headers: Access-Control-Allow-Origin, Content-Type');
header('Access-Control-Allow-Origin: *');
header('Content-Type: application/json, charset=utf-8');

include 'config.php';

$json =  file_get_contents('php://input');

$obj = json_decode($json);

$id = $obj->{'id'};
$name = $obj->{'name'};
$username = $obj->{'username'};
$password = $obj->{'password'};
$age = $obj->{'age'};
$role = $obj->{'role'};
$profile = $obj->{'profile'};
$email = $obj->{'email'};
$webpage = $obj->{'webpage'};

$sql = "update user set U_name = '$name', U_username = '$username', U_password = '$password',
                U_age = '$age', U_role = '$role', U_profile = '$profile', U_email =  '$email',
                U_webpage = '$webpage' where U_id = '$id'";

if (!empty($link)) {
    if (mysqli_query($link, $sql)) {
        echo json_encode(array("statusCode" => 200));
    }
    else {
        echo json_encode(array("statusCode" => 201));
    }
    mysqli_close($link);
}
