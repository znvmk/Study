<?php

/**
 * Created by PhpStorm.
 * User: ZhangYunian
 * Date: 2018/7/6
 * Time: 15:50
 */


namespace App\Models\Excel;
use App\Models\Model;
use App\Utility\Cache;
use App\Models\User\Role;

/**
 * 充值金额列表
 * Class AngelPlayer
 * @package App\Models\Excel
 */
class AngelPlayer extends Model
{

    private $cache;
    private $AngelPlayerKey;//天使玩家键 key
    private $AngelPlayerList;//天使玩家列表 list


    public function __construct()
    {
        parent::__construct();
        //$this->uid = $uid;
        $this->cache = Cache::getInstance();
        $this->init();
    }

    /**
     * 初始化类
     */
    public function init()
    {
        $this->AngelPlayerKey= 'AngelPlayer:uid:';

    }


    /**
     * 获取信息
     * @return array
     */
    //*
    public function getAngelPlayer($uid)
    {

        $this->AngelPlayerList=$this->cache->stringGet( $this->AngelPlayerKey.$uid,'write');

        if( $this->AngelPlayerList ==NULL){
            echo("没有此玩家！");
            return NULL;
        }
        //var_dump($a);
        //var_dump($this->AngelPlayerList);
        return $this->AngelPlayerList;
    }

    /**
     * 添加天使玩家
     * @return bool
     */
    public function addAngelPlayer($uid)
    {
        if($this->getAngelPlayer()!=NULL) {
            echo("该玩家已存在");
        }
        $data = [
            'uid' => $uid,
            'value' => 0,
            'popularity' => 0,
            'fans'=>0
        ];
        echo("添加玩家");
        var_dump($data);
        $setRes = $this->cache->stringSet( $this->AngelPlayerKey.$uid,$data);
        var_dump($setRes);
        if($setRes){
            echo("天使玩家已成功添加！");
        }
        //$fans = empty($itemaID) ? $fans : ($itemData['fans'] + $fans);
    }


    /**
     * 慎用！
     * 删除天使玩家：删除天使玩家在名人堂的所有数据（名人堂ID，人气，粉丝）
     * @return bool
     */
    public function delAngelPlayer()
    {
        if($this->getAngelPlayer() == NULL) {
            echo("该玩家不存在");
        }

        echo("删除玩家");

        $setRes = $this->cache->stringDel( $this->AngelPlayerKey);
        var_dump($setRes);
        if($setRes){
            echo("天使玩家已成功删除！");
        }
        //$fans = empty($itemaID) ? $fans : ($itemData['fans'] + $fans);
    }

    /**
     * 添加天使玩家粉丝
     * @return bool
     */
    public function addFans($uid,$fansId)
    {
        if($this->isFansExist($fansId)){
            echo("粉丝已存在，不用添加\n");
            return ;
        }
        echo("粉丝不存在，添加数据\n");

        $apdata=$this->getAngelPlayer($uid);
        $fans=$apdata['fans'].','.$fansId;

        echo("人气加 1\n");
        var_dump($apdata['popularity']."\n");
        $popularity= $apdata['popularity']+1;
        var_dump($popularity."\n");

        var_dump($fans."\n");
        $data = [
            'uid' => $uid,
            'value' => $apdata['value'],
            'popularity' => $popularity,
            'fans'=>$fans
        ];

        echo("要更新的数据：\n");
        var_dump($data);

        $setRes = $this->cache->stringSet( $this->AngelPlayerKey.$uid,$data);
        var_dump("添加数据后天使玩家信息：\n".$setRes."\n");
        //$fans = empty($itemData) ? $fans : ($itemData['fans'] + $fans);
    }

    /**
     * 判断天使玩家粉丝是否存在
     * @return bool
     */
    public function isFansExist($fansId)
    {
        $apdata=$this->getAngelPlayer();
        $fans=$apdata['fans'];
        var_dump($fans);

        echo("获取天使玩家粉丝数组\n");
        $data = explode(',',$fans);
        var_dump($data);


        if($fansId==$this->uid){
            var_dump("粉丝 ".$fansId." 存在\n");
            return true;
        }

        foreach ($data as $d) {

            if($d==$fansId){
                var_dump("粉丝 ".$fansId." 存在\n");
                return true;
            }
        }
        var_dump("粉丝 ".$fansId." 不存在\n");
        return false;

    }


    /**
     * 天使玩家粉丝重置
     * 凌晨3点重置
     * @return bool
     */
    public function FansReset($uid)
    {

        //判定时间
        $ntime="03:01";

        //var_dump(date("H:i:s"));
        //var_dump(date("H:i"));

        if(date("H:i",date("H:i")==$ntime))
        {echo("时间到了,重置粉丝数据！");}



        if($this->getAngelPlayer($uid)!=NULL) {
            echo("该玩家已存在");
        }
        $apdata=$this->getAngelPlayer($uid);

        //粉丝记录重置
        $fans= "0";

        $data = [
            'uid' => $uid,
            'value' => $apdata['value'],
            'popularity' => $apdata['popularity'],
            'fans'=>$fans
        ];

        echo("粉丝重置\n");
        var_dump($data);

        $setRes = $this->cache->stringSet( $this->AngelPlayerKey.$uid,$data);
        var_dump("粉丝重置后玩家信息：\n".$setRes."\n");

        return true;

    }
    /**
     * 玩家身价
     * @return int
     */
    public function getAngelPlayerValue($uid)
    {
        //$player=new Role($uid);
        //$playerValue=$player->getShenjiazhi($uid);
        $player=new Role(116);
        $playerValue=$player->getShenjiazhi(116);
        var_dump($playerValue);
    }

    /**
     * 获得天使玩家数组:粉丝改为是否存在
     * @return Array()
     */
    public function getAngelPlayerArray($uid)
    {
        $apdata=$this->getAngelPlayer($uid);
        $data = [
            'uid' => $uid,
            'value' => $apdata['value'],
            'popularity' => $apdata['popularity'],
            'like'=>0
        ];
        return $data;
    }

    /**
     * 获得天使玩家数排行榜
     * @return Array()
     */
    public function getAngelPlayerArrayList()
    {
        for($i=1;$i<6;$i++){
            $this->getAnglePlayerArray($i);
        }

    }
}
