<?php
include_once("config.php");
include_once("db.class.php");
include_once("mongo.class.php");
include_once("common.php");

easy_query("SET NAMES utf8");

$sql = "SELECT * FROM commodity ";
$content = easy_query($sql);



foreach($content as $row => $key) {
    unset($content[$row]['id']);
    echo $content[$row]["title"];
//    echo iconv("latin1","utf-8",$content[$row]["title"]);
    try {
       $mongo->insert("groupbuy",$content[$row]);
    } catch(Exception $e) {
        echo $e;
    }
}

$rows = $mongo->find("groupbuy");
foreach($rows as $row) {
//    var_dump($row);






?>
