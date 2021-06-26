<?php
include 'config.php';
$id=$_POST['id'];
$sql = "delete from user where U_id=$id";
if (!empty($link)) {
    if (mysqli_query($link, $sql)) {
        echo json_encode(array("statusCode" => 200));
    } else {
        echo json_encode(array("statusCode" => 201));
    }
    mysqli_close($link);
}