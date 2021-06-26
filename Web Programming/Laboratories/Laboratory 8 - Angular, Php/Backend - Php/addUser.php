<?php
header('Access-Control-Allow-Headers: Access-Control-Allow-Origin, Content-Type');
header('Access-Control-Allow-Origin: *');
header('Content-Type: application/json, charset=utf-8');

include 'config.php';

$json =  file_get_contents('php://input');

$obj = json_decode($json);

$name = $obj->{'name'};
$username = $obj->{'username'};
$password = $obj->{'password'};
$age = $obj->{'age'};
$role = $obj->{'role'};
$profile = $obj->{'profile'};
$email = $obj->{'email'};
$webpage = $obj->{'webpage'};


$sql = "insert into user (U_name, U_username, U_password, U_age, U_role, U_profile, U_email, U_webpage)
values ('$name', '$username', '$password', '$age', '$role', '$profile', '$email', '$webpage')";

if (!empty($link)) {
//  mysqli_query($link, $sql);
    if (mysqli_query($link, $sql)) {
        echo json_encode(array("statusCode" => 200));
    }
    else {
        echo json_encode(array("statusCode" => 201));
    }
    mysqli_close($link);
}
