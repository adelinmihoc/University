<?php
include 'config.php';

$id = $_POST['id'];
$name = $_POST['name'];
$username = $_POST['username'];
$password = $_POST['password'];
$age = $_POST['age'];
$role = $_POST['role'];
$profile = $_POST['profile'];
$email = $_POST['email'];
$webpage = $_POST['webpage'];

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