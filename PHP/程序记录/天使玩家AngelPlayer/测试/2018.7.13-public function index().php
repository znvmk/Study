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
      // $a = $cache->client()->zRank('angelPlayer','115');
       //zset添加数据
       //$a=$cache->client()->zAdd('angelPlayer',10,'117');
       //echo("asdfasdfasdfasdfasdfasd");
       //var_dump($a);
       //zset通过索引排序，分数从高到低：区间（0,0）即可获得最高分数和key，return array():key => scores
//        $a=$cache->client()->zRevRange('angelPlayer',0,0,true);
//        $aa=0;
//        foreach ($a as &$value){
//           $aa=$value;
//        }
//        var_dump($aa);
//        //var_dump($a);
//        var_dump("/n");
//        //zset通过分数排序,分数从高到低:由zRevRange取得最高分，最低分设置为0，zRevRangeByScore()即可获得全部数据按分数从高到低排序
//        $arrAngelP =$cache->client()->zRevRangeByScore('angelPlayer',(int)$aa,0,array('withscores' => true));
//        $angelPlayer=new AngelPlayer();
//        foreach ($arrAngelP as $key=>$value) {
//            $roleArray =$angelPlayer->getAngelPlayerArray($key);
//            var_dump($roleArray);
//            var_dump("奥赛发森".$arrAngelP[$key]);
//
//        }
       //$b= $cache->client()->zRank('angelPlayer','119');
       //var_dump($b);
      // $uid=118;
      // $Id=(string)$uid;
       //var_dump($Id);
      // $AngelPlayerIs=$cache->client()->zRank('angelPlayer',$Id);
       //var_dump($AngelPlayerIs);
      // if(!$AngelPlayerIs){
      //     echo("false");
      // }else{
      //     echo("true");
      // }
       //echo("asdfasdfasd");
       //删除key:返回true,false
//        $key='like';
//        $id=116;
//        $a=$cache->client()->del($key.":".(string)$id);
//        var_dump($a);
       $role=new Role(112);
//        //角色数组
       $roleArray=$role->getRoleById(112);
       var_dump($roleArray);
//        //玩家数组
//        $data=[
//            'uid'=>$roleArray['uid'],
//            'name'=>$roleArray['nickname'],
//            'icon'=>$roleArray['icon'],//头像
//            'level'=>$roleArray['level'],
//            'SocialStatus'=>$roleArray['shenjiazhi'],//身价值
//        ];
//        var_dump($data);



       //天使玩家数组
//        $data=[
//            'uid'=>$uid,
//            'name'=>$roleArray['name'],
//            'icon'=>$roleArray['icon'],
//       ];


   }
