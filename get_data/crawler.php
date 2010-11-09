<?php
include("db.class.php");
include("config.php");
include("common.php");
include("mongo.class.php");

error_reporting(0);
include_once("lastRSS.php");

//get data from db
$sql = "SELECT url FROM source";
$DESTINATION_URL = easy_query($sql);

$mongo = new MongoApi("127.0.0.1:10001");
$mongo->selectDb("tuokouerchu");
//$mongo->drop_table("groupbuy");
$mongo->ensureIndex("groupbuy",array("title"=>1),array('unique'=>true));

//get data from rss
$obj = new lastRSS();
foreach($DESTINATION_URL as $url) 
{ 
    $result = $obj->Get($url['url']); $result['title'] = iconv($result['encoding'],"utf-8",$result['title']);
    $result['description'] = iconv($result['encoding'],"utf-8",$result['description']);

    // update site
    $sql = "SELECT id FROM site WHERE link=\"" . $result['link'] . "\"";
    $content = easy_query($sql);
    if(empty($content)) {
        $data['title'] = $result['title'];
        $data['link'] = $result['link'];
        $data['description'] = $result['description'];
        $sql =insert_sql("site",$data); 
        easy_query($sql);
        $site_id = get_last_id("site");
    } else
        $site_id = $content[0]['id'];

    // update commodity
    foreach($result['items'] as $item) {
        $data['description'] = iconv($result['encoding'],"utf-8",$item['description']);
        $data['title'] = iconv($result['encoding'],"utf-8",$item['title']);
        $data['link'] = $item['link'];
        $data['site_id'] = $site_id;
        $data['pub_timestamp'] = datetime_to_timestamp($item['pubDate']);
        unset($data["_id"]);
        try{
            $mongo->insert("groupbuy",$data);
            print $mongo->getError();
            print "\n";
        } catch(Exception $e){
            echo $e; 
        }
    }
}

?>
