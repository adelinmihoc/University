<?php

const DB_SERVER = 'localhost';
const DB_USERNAME = 'root';
const DB_PASSWORD = 'adelin123';
const DB_NAME = 'pw_lab7';

$link = mysqli_connect(DB_SERVER, DB_USERNAME, DB_PASSWORD, DB_NAME);

if($link === false){
    die("ERROR: Could not connect. " . mysqli_connect_error());
}
