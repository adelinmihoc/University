<?php
header('Access-Control-Allow-Headers: Access-Control-Allow-Origin, Content-Type');
header('Access-Control-Allow-Origin: *');
header('Content-Type: application/json, charset=utf-8');

require_once "config.php";

$sql = "SELECT * FROM user";
$users = array();
if (!empty($link)) {
    if($result = mysqli_query($link, $sql)){
        if(mysqli_num_rows($result) > 0){
            while($row = mysqli_fetch_array($result)) {
                $user = new StdClass();
                $user->id = $row['U_id'];
                $user->name = $row['U_name'];
                $user->username = $row['U_username'];
                $user->password = $row['U_password'];
                $user->age = $row['U_age'];
                $user->role = $row['U_role'];
                $user->profile = $row['U_profile'];
                $user->email = $row['U_email'];
                $user->webpage = $row['U_webpage'];

                array_push($users, $user);
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
    echo json_encode($users);
}
