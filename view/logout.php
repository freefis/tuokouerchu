<?php
session_start();

if(!empty($_SESSION)) {
    echo "You have Logout";
    session_destroy();
}




?>
