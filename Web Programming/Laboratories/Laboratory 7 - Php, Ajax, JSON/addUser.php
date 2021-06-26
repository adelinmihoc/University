<?php
include 'config.php';

$name = $_POST['name'];
$username = $_POST['username'];
$password = $_POST['password'];
$age = $_POST['age'];
$role = $_POST['role'];
$profile = $_POST['profile'];
$email = $_POST['email'];
$webpage = $_POST['webpage'];

$sql = "insert into user (U_name, U_username, U_password, U_age, U_role, U_profile, U_email, U_webpage) 
values ('$name', '$username', '$password', '$age', '$role', '$profile', '$email', '$webpage')";

if (!empty($link)) {
    if (mysqli_query($link, $sql)) {
        echo json_encode(array("statusCode" => 200));
    }
    else {
        echo json_encode(array("statusCode" => 201));
    }
    mysqli_close($link);
}