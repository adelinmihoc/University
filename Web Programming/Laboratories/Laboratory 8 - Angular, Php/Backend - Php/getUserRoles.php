<?php
header('Access-Control-Allow-Headers: Access-Control-Allow-Origin, Content-Type');
header('Access-Control-Allow-Origin: *');
header('Content-Type: application/json, charset=utf-8');

require_once "config.php";

$sql = "SELECT distinct U_role FROM user";
$roles = array();
if (!empty($link)) {
    if($result = mysqli_query($link, $sql)){
        if(mysqli_num_rows($result) > 0){
            while($row = mysqli_fetch_array($result)) {
                array_push($roles, $row[0]);
            }

            mysqli_free_result($result);
        } else{
            echo '<div><em>No records were found.</em></div>';
        }
    } else{
        echo "Oops! Something went wrong. Please try again later.";
    }
    // Close connection
    mysqli_close($link);
    echo json_encode($roles);
}
