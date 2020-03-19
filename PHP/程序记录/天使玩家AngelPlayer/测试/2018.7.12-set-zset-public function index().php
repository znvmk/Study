<?php

public function index()
{
    //$AngelP=new AngelPlayer();
    //$AngelPArray=$AngelP->getAngelPlayerArray(1);
    //var_dump($AngelPArray);
    //var_dump($AngelPArray['uid']);
    //$AngelPList=new AngelPlayerList();
   // $AngelPList->encode( $AngelPArray);
   // var_dump($AngelPList);
    //$AngelOpenResult= new AngelCelebrityOpenResult();
    //$str=$AngelOpenResult::encode($AngelPArray,1);
    //var_dump($str);
    $cache = Cache::getInstance();
    //$cache->client()->expire(aaa,5);
    //$a=$cache->client()->zRank('angelPlayer','115');
    //获得数据的索引,return int,如果不存在则返回false
    $a = $cache->client()->zRank('angelPlayer','115');
    //zset添加数据
    $a=$cache->client()->zAdd('angelPlayer',10,'117');
    //echo("asdfasdfasdfasdfasdfasd");
    //var_dump($a);
    //zset通过索引排序，分数从高到低：区间（0,0）即可获得最高分数和key，return array():key => scores
    $a=$cache->client()->zRevRange('angelPlayer',0,0,true);
   // var_dump($a);
    //zset通过分数排序,分数从高到低:由zRevRange取得最高分，最低分设置为0，zRevRangeByScore()即可获得全部数据按分数从高到低排序
    $a=$cache->client()->zRevRangeByScore('angelPlayer',200,0,array('withscores' => true));
    $a = $cache->client()->zRank('angelPlayer','119');
   // var_dump($a);
    $uid=118;
    $Id=(string)$uid;
    //var_dump($Id);
    $AngelPlayerIs=$cache->client()->zRank('angelPlayer',$Id);
    //var_dump($AngelPlayerIs);
    if(!$AngelPlayerIs){
        echo("false");
    }else{
        echo("true");
    }
    //echo("asdfasdfasd");

}
