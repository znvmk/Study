<?php

public function index()
    {
        $cache = Cache::getInstance();
       $angel=new AngelPlayer();
       $angel->updateAngelPlayerRank();
       //$angel->isLikeReset(112);
       // $cache->client()->del('like:112');
//        $sget=$cache->stringGet('updateTime:anglePlayer');
//        var_dump($sget);
//        var_dump($sget['date']);
//
//        $data = [
//            'timing'=>'0300',
//            'date'=>date("YmdHis", time())
//        ];
//        var_dump($data);
//        $cache->stringSet('updateTime:anglePlayer',$data);
//
//        $t1=strtotime("20180717114002");
//        var_dump($t1);
//        $t2=strtotime(date("YmdHis",time()));
//        var_dump($t2);
//        $subLast=ceil(($t1-$t2)/60);
//        $sub=ceil(($t1-$t2)/60);
//        if($sub>=0){
//            var_dump("超过时间：".$sub);
//        }else{
//            $sub= ($sub>=0)? $sub:-$sub;
//            var_dump("差：".$sub);
//        }
//
//
//
//
//
//        var_dump("超过时间：".$subLast);
//        //现在时间（不用日期）
//        $timeNow=strtotime(date("His",time()));
//        var_dump(date("His",time()));
//        //更新时间点
//        $timePoint=strtotime("030000");
//        var_dump($timePoint);
//        $subPoint=ceil(($timeNow-$timePoint)/60);
//        var_dump($subPoint);
//        if($subPoint>0&&$subPoint<$subLast){}
////            //更新数据
////            $this->updateAngelPlayerRank();
//
//
//            //数据更新时间记录
//            $recDate=date("Ymd", time()).$sget['timing'];
//            //更新时间记录
//            $data = [
//                'timing'=> $sget['timing'],
//                'date'=>$recDate
//            ];
//            var_dump($data);
//            //写入更新记录
//            $cache->stringSet('updateTime:anglePlayer',$data);
//            return true;
//        }else{
//            return false;
//        }


//        $d=mktime(3, 12, 31, 6, 10, 2015);
//        echo "创建日期是 " . date("YmdHis", $d);
//        $a="2018-07-16 17"
//        var_dump(date("YmdHis", time())."\n");
//        time());
//        $ntime="17:12";
//        var_dump(date("H:i:s"));
//        var_dump(date("H:i"));
//        if(date("H:i",date("H:i")==$ntime))
//        {echo("时间到了");}



//        $uid=112;
//        $popGet=$cache->client()->hGet('RoleInfo:uid:'.$uid,'popularity');
//        var_dump("点赞前:".$popGet);
//        $popSet=(int)$popGet +1;
//
//        $cache->client()->hSet('RoleInfo:uid:'.$uid,'popularity',$popSet);
//        $popGet=$cache->client()->hGet('RoleInfo:uid:'.$uid,'popularity');
//        var_dump("点赞后:".$popGet);
    }
