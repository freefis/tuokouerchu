<?php
/*
 * 常用函数 直接调用BASE包 
 * Design by  Free.Wang <freefis@gmail.com>
 * Date :  June 10 2010
 *
 */


function datetime_to_timestamp($datetime)
{
    $months = array(
        'Jan'=>1, 
        'Feb'=>2, 
        'Mar'=>3, 
        'Apr'=>4, 
        'May'=>5, 
        'Jun'=>6, 
        'Jul'=>7, 
        'Aug'=>8, 
        'Sep'=>9, 
        'Oct'=>10, 
        'Nov'=>11, 
        'Dec'=>12
    );
    //Thu, 09 Sep 2010 16:00:00 
    $year = (int)substr($datetime,13,2);
    $mon = $months[substr($datetime,9,3)];
    $day = (int)substr($datetime,6,2);
    $hour = (int)substr($datetime,18,2);
    $min = (int)substr($datetime,21,2);
    $sec = (int)substr($datetime,24,2);
    return mktime($sec,$min,$hour,$day,$mon,$year);
}




/*
 * 初始化DB对象
 */
function init_db()
{
    global  $config;
    $db_obj = new DB(
            $config['db']['host'],
            $config['db']['user'],
            $config['db']['pw'],
            $config['db']['name']
        );
    return $db_obj;
}

/*
 * 直接返回查询结果的简单查询
 */
function easy_query($sql)
{
    $db_obj = init_db();
    $query = $db_obj->query($sql);
    $result = $db_obj->fetch_arrays($query);
    unset($query);
    unset($db_obj);
    return $result;
}

function get_latest_id($table)
{
    $sql = "SELECT max(id) FROM {$table}";
    $content = easy_query($sql);
    return $content[0]['max(id)'];
}

function filter_query_field($QuerySet,$field)
{
    if(empty($QuerySet)) 
        return array();

    $result = array();
    foreach($QuerySet as $Query) 
    {
        if(!array_key_exists($field,$Query))
    	{
            throw new Exception("No such field:{$field} ");
            exit;
        }
        $result[] = $Query[$field];  
    }

    return $result;
}

/*
 * 直接返回查询结果的简单查询
 */
function last_insert_id()
{
    $db_obj = init_db();
    $result = $db_obj->insert_id();
    unset($db_obj);
    return $result;
}

/* 清理缓存 */
function flush_mc($key)
{
    $mc_obj = mem_cache::get_instance();

//    if($mc_obj->get($key)) 
    $mc_obj->delete($key);
}



/*
 * JSON编码
 */
if(!function_exists("json_encode"))
{
function json_encode($data) 
{
  $json = new Services_JSON();
  return( $json->encode($data) );
}
}

/*
 * JSON解码
 * @param $data
 * @param $bool  如果$bool=TRUE,则JSON的数据形式为HASH,否则为OBJECT
 */
if(!function_exists("json_decode"))
{
	function json_decode($data, $bool)
	{
	  if ($bool) {
	      $json = new Services_JSON(SERVICES_JSON_LOOSE_TYPE);
	  } else {
	      $json = new Services_JSON();
	  }
	  return( $json->decode($data) );
	}
}

/*
 * array_remove(array('a','b','c'),'b') 
 *      =>
 * array('a','c'); 
 */
if(!function_exists("array_remove"))
{
    function array_remove(& $array, $var)
    {               
        if(empty($array))
            return $array;

        $p = NULL;
        foreach($array as $key=>$value)
        {
            if($value==$var) {
                $p = $key;
                break;
            }
        }
        if(!is_null($p))
            array_splice(& $array,$p,1);
//        return $array;
    }    
}


if(!function_exists("array_insert"))
{
    function array_insert($array,$pos,$ele)
    {
        $temp = array_chunk($array,$pos,true);
        $a = $temp[0]; 
        $a[] = $ele;
        $b = $temp[1];
        return array_merge($a,$b);
    }
}

/*
 * array_offset(array(1,2,3),2)  => 1
 */
if(!function_exists("array_offset"))
{
    function array_offset($array,$ele)
    {
        $i = 0;
        foreach($array as $one) {
            if($one==$ele) {
                return $i; 
            }
            $i += 1;
        }
        return NULL;
    }
}

/*
 * intval_array(array('a'=>'1','b'=>'sdfsdfs')) => array('a'=>1,'b'=>'sdfsdfs')
 */
function intval_array($array)
{
    foreach($array as $key => $value){
        if(preg_match("/^[0-9]+$/",$value))
            $array[$key] = (int)$value;
    }
    return $array;
}





function randint(){
    $num = "";
    for($i;$i<=5;$i++)
    {
       $num .= (string)(mt_rand(0,9)); 
    }
    return $num;
}





/*
 * 获取POST或GET参数
 * @key
 * @def 代表该请求参数如果为空时的默认值
 */
function gp($key = '',$def = null) {
	$v = $key === '' ? $_GET : (isset($_GET[$key]) ? $_GET[$key] : null);
	if(is_null($v)){
		$v = $key === '' ? $_POST : (isset($_POST[$key]) ? $_POST[$key] : null);
	}
	if(is_null($v)){
		$v = $def;
	}
	return $v;
}

function to_utf8($s) {
	global $_SC;
	if($_SC['charset'] == 'utf-8') {
		return $s;
	} else {
		return  _iconv($_SC['charset'],'utf-8',$s);
	}
}

function from_utf8($s) {
	global $_SC;
	if($_SC['charset'] == 'utf-8') {
		return $s;
	} else {
		return  _iconv('utf-8',$_SC['charset'],$s);
	}
}

function to_unicode($s) { 
	return preg_replace("/^\"(.*)\"$/","$1",json_encode($s));
}


function  get_all_mc_key()
{
    global $config;
    $obj = mem_cache::get_instance();
    $items=$obj->getExtendedStats('items');
    var_dump($items);
    $items=$items[$config['mc']['servers']]['items'];

    foreach($items as $k => $v) {       
        $str=$obj->getExtendedStats("cachedump",$k,0);
        $line=$str[$config['mc']['servers']];

        if( is_array($line) && count($line)>0) {   
            foreach($line as $key=>$value) {   
                $temp[] = $key;
            }
        }
    }

    return $temp;
}


	function update($tblname, $arr_update_data, $str_where, $dbname = false)
	{
		foreach($arr_update_data as $db_key=> $db_value)
		{
			if ($db_key == "passwd")
			{
				$arr_set[] = " `{$db_key}`=" . $db_value;

			//------ 修正不能更新类似 col = col + 1 问题 by caijian 2010.05.07 ------//
			} elseif (preg_match("/^$db_key\s*([\+\-\*\/])\s*(\d+)\s*$/",$db_value,$matchs) ) {
				$arr_set [] = " `{$db_key}`=`{$db_key}`" . $matchs[1] . $matchs[2];
			//------------------------------------------------------------------//

			}
			else
			{
				$arr_set[] = " `{$db_key}`='" . mysql_escape_string($db_value) ."'";
			}
		}
		$str_set = "set " . implode(",", $arr_set);

		$sql ="update $tblname {$str_set} where {$str_where}";
		if ($this->debug)
		{
			echo "<!-- db::update() {$sql} -->\n";
		}
		
		$sth=$this->db_obj->prepare($sql,array(PDO::ATTR_CURSOR => PDO::CURSOR_FWDONLY));
		$res=$sth->execute();
		$af_rows = $sth->rowCount();

		return $res;
	}


function updatetable($table, $set_data, $where_data){
	reset($set_data);
	$query  = 'UPDATE `';
    $query .= $table. '` SET ';
	$col = array();
	while (list($columns, $value) = each($set_data)) 
	{
		$value=trim($value);
		$value = (strpos($value,'&|') === 0) ? substr($value, 2) : "'" . mysql_escape_string(str_replace(array('"',"'",'<','>'),array('&quot;' ,'&#039;','&lt;', '&gt;'),$value)) ."'";   
		$col[] = '`'.$columns.'`' . '='.$value;
	}
    $query .= implode(',',$col);
	if(!empty($where_data)) 
	{
		if(is_array($where_data)) {
			foreach ($where_data as $key => $value) {
				$wheres[] = '`'.$key.'`'.'=\''.$value.'\'';
			}
			$where = implode(' AND ',$wheres);
		}
		$query .= ' WHERE ' . $where;
	}
    return $query;
}

function insert_sql($table, $set_data){
	reset($set_data);
	$query  = 'INSERT `';
    $query .= $table. '` SET ';
	$col = array();
	while (list($columns, $value) = each($set_data)) 
	{
		$value=trim($value);
		$value = (strpos($value,'&|') === 0) ? substr($value, 2) : "'" . mysql_escape_string(str_replace(array('"',"'",'<','>'),array('&quot;' ,'&#039;','&lt;', '&gt;'),$value)) ."'";   
		$col[] = '`'.$columns.'`' . '=' .  $value ;
	}
    $query .= implode(',',$col);
    return $query;
}


?>


