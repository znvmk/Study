<?php

/**
 * Created by PhpStorm.
 * User: ZhangYunian
 * Date: 2018/7/6
 * Time: 15:50
 */


namespace App\Models\AngelPlayer;
use App\Models\Model;
use App\Utility\Cache;
use App\Models\User\Role;
use App\Models\BagInfo\Bag;

/**
 * 充值金额列表
 * Class AngelPlayer
 * @package App\Models\Excel
 */
class AngelPlayer extends Model
{

    private $cache;
    private $AngelPlayerKey;//天使玩家键 key
    private $roleKey;//角色键key
    private $likekey;//点赞key
    private $updatekey;//天使玩家排行榜更新时间key



    public function __construct()
    {
        parent::__construct();
        $this->cache = Cache::getInstance();
        $this->init();
    }

    /**
     * 初始化类
     */
    public function init()
    {
        $this->AngelPlayerKey= 'AngelPlayer';
        $this->roleKey='RoleInfo:uid:';
        $this->likekey='like:';
        $this->updatekey='updateTime:anglePlayer';
    }


    /**
     * 判断天使玩家是否存在
     * @param int $uid
     * @return bool
     */
    public function isAngelPlayerExist($uid)
    {
        $Id=(string)$uid;
        $res=$this->cache->client()->zRank($this->AngelPlayerKey,$Id);
        $isAngelPlayer=(string)$res;
        if($isAngelPlayer==''){
            return false;
        }else{
            return true;
        }
    }

    /**
     * 获得天使玩家排行榜
     * @return Array()
     */
    public function getAngelPlayerArrayList($likeId)
    {
        //$this->batchAddAngelPlayer();
        $this->cleanAngelPlayerList();
        $this->isUpdateAngel();

        //天使玩家ID数组
        $arrAngel=$this->AngelPlayerRank();

        //天使玩家列表：天使玩家排行榜
        $arrAngelList=[];
        $i=1;
        foreach ($arrAngel as $key=>$value){
            //var_dump($arrAngelP);
            $roleArray = $this->getAngelPlayerArray($key);
            //var_dump($roleArray);
            //是否点赞
            if($this->isLikeExist($key,$likeId)){
                $like=1;
            }else{
                $like=2;
            }

            $arrAngelList[$i]=[
                'uid'=>$key,
                'name'=>$roleArray['name'],
                'icon'=>$roleArray['icon'],//头像
                'level'=>$roleArray['level'],
                'popularity'=>$roleArray['popularity'],
                'SocialStatus'=>$roleArray['SocialStatus'],//身价值
                'vip'=>$roleArray['vip'],
                'sign'=>$roleArray['sign'],
                'like'=>$like
            ];
            $i++;
        }
        //var_dump($arrAngelList);
        //返回所有数据数组
        return $arrAngelList;
    }

    /**
     * 添加天使玩家
     * @param int $uid
     * @return bool
     */
    public function isAddAngelPlayer($uid)
    {
        if($this->isAngelPlayerExist($uid)==true) {
            var_dump("该玩家已存在");
            return ;
        }


        //判断玩家是否存在，如果不存在，返回false
        $bExit=$this->cache->client()->exists($this->rolekey.$uid);
        if(!$bExit){
            //echo("该玩家不存在，请确认后再添加");
            //return false;
        }

        $Role = new Role();
        $shenjiazhi = $Role->getShenjiazhi($uid);

        $data = [
            'uid' => $uid,
            'socialStatus' => $shenjiazhi,
            'like'=>$uid
        ];
        var_dump("添加玩家".$uid);
        var_dump($data);
        $bIdAdd = $this->cache->client()->zAdd($this->AngelPlayerKey,$data['socialStatus'],$data['uid']);
        $bLikeAdd=$this->cache->client()->sAdd($this->likekey.$uid,$data['like']);
        var_dump($bIdAdd);
        if($bIdAdd&&$bLikeAdd){
            var_dump("天使玩家".$uid."已成功添加！");
            return true;
        }else{
            var_dump("玩家".$uid."添加失败");
            return false;
        }
        //$fans = empty($itemaID) ? $fans : ($itemData['fans'] + $fans);
    }

    /**
     * 批量添加天使玩家
     * @return bool
     */
    public function batchAddAngelPlayer()
    {
        //获得所有玩家key
        $playerKeys=$this->cache->client()->getKeys('RoleInfo:uid:*');

        //提取ID
        $temp=array();
        foreach ($playerKeys as $key=>$value){
            $value = preg_replace('/RoleInfo:uid:/','',$value);
            $temp[$key]=(int)$value;
        }
        $playerID=$temp;

        $role=new Role();
        foreach ($playerID as $key=>$value){
            $roleArr=$role->getRoleById($value);
            var_dump($roleArr);
            //判断级别是否达到天使玩家
            if($roleArr['game_level']==1){
                //$iSocialStatus=$roleArr['shenjiazhi'];
                $this->isAddAngelPlayer($value);
            }
        }
        return true;

    }

    /**
     * 去除非天使玩家：当天使玩家级别变化后，不再属于天使玩家，因此要在天使玩家列表中删除这些玩家
     * @return bool
     */
    public function cleanAngelPlayerList()
    {
        //天使玩家ID数组
        $arrAngel=$this->AngelPlayerRank();
        var_dump($arrAngel);
        $role=new Role();
        foreach ($arrAngel as $key=>$value) {
            $roleArr=$role->getRoleById($key);
            //判断级别是否超过天使玩家，如果不是删除
            if($roleArr['game_level']!=1){
                //$this->cache->client()->zRem($this->AngelPlayerKey,$value);
                $this->isDelAngelPlayer($key);
                var_dump("删除了".$key);
            }
        }
    }

    /**
     * 慎用！
     * 删除天使玩家：删除天使玩家在名人堂的所有数据（名人堂ID，人气，粉丝）
     * @param int $uid
     * @return bool
     */
    public function isDelAngelPlayer($uid)
    {
        if($this->isAngelPlayerExist($uid)== false) {
            var_dump("该玩家".$uid."不存在");
            $bIdRem=true;
        }else{
            var_dump("删除玩家".$uid);
            $bIdRem= $this->cache->client()->zRem( $this->AngelPlayerKey,(string)$uid);
            var_dump($bIdRem);
        }
        if($this->cache->client()->exists($this->likekey.$uid)){
            var_dump("删除玩家点赞".$uid);
            $bLikeRem=$this->cache->client()->del($this->likekey.$uid);
        }else{
            var_dump("玩家点赞不存在".$uid);
            $bIdRem=true;
        }


        if($bIdRem&&$bLikeRem){
            var_dump("天使玩家".$uid."及点赞已成功删除！");
            return true;
        }
        //$fans = empty($itemaID) ? $fans : ($itemData['fans'] + $fans);
    }

    /**
     * 判断是否对天使玩家点赞
     * @param int $uid
     * @param int $likeId
     * @return bool
     */
    public function isLikeExist($uid,$likeId)
    {
        if($this->cache->client()->sIsMember($this->likekey.$uid,(string)$likeId)){
            var_dump($likeId."点赞".$uid."已存在\n");
            return true;
        }else{
            var_dump($likeId."点赞".$uid."不存在\n");
            return false;
        }
    }

    /**
     * 对天使玩家点赞：添加天使玩家人气
     * @param int $uid
     * @param int $likeId
     * @return array()
     */
    public function Like($uid,$likeId)
    {
        if ($this->isAngelPlayerExist($uid)) {

            //判断人气字段是否存在，如果不存在添加，并设置为1
            $bExit=$this->cache->client()->hExists($this->roleKey.$uid,'popularity');
            var_dump($bExit);
            if(!$bExit){
                echo("设置key");
                $this->cache->client()->hSet($this->roleKey.$uid,'popularity','1');
            }

            $populGet=$this->cache->client()->hGet($this->roleKey.$uid,'popularity');
            if ($this->isLikeExist($uid, $likeId)) {
                $iLikeResult = 1;
            } else {
                if ($this->isAddLike($uid, $likeId)) {
                    $iLikeResult = 1;
                } else {
                    $iLikeResult = 2;
                }
            }
            $data = [
                'likeresult' => $iLikeResult,
                'AngelPlayerId' => $uid,
                //未点赞之前的人气值+1
                'popularity' => $populGet+1
            ];
        }else{
            $data = [
                'likeresult' => 2,
                'AngelPlayerId' => $uid,
                'popularity' => 0
            ];
        }
        return $data;
    }

    /**
     * 添加天使玩家点赞：添加点赞的ID集合
     * @param int $uid
     * @param int $likeId
     * @return bool
     */
    public function isAddLike($uid,$likeId)
    {
        if($this->isLikeExist($uid,$likeId)){
            var_dump($likeId."点赞".$uid."已存在，不用添加\n");
            return true;
        }
        var_dump($likeId."点赞".$uid."不存在，添加数据\n");

        $bLikeAdd=$this->cache->client()->sAdd($this->likekey.$uid,(string)$likeId);
        //*
        //添加人气
        if ($this->isAngelPlayerExist($uid)) {
            $popGet=$this->cache->client()->hGet($this->roleKey.$uid,'popularity');
            var_dump("点赞前".$popGet);
            $popSet=(int)$popGet +1;

            $this->cache->client()->hSet($this->roleKey.$uid,'popularity',$popSet);
            $popGet=$this->cache->client()->hGet($this->roleKey.$uid,'popularity');
            var_dump("点赞后".$popGet);
        }
        //*/
        if($bLikeAdd){
            var_dump($likeId."点赞".$uid."添加成功");
            var_dump($likeId."获得绑金100");
            $this->GoldAward($likeId);
            return true;
        }else{
            var_dump($likeId."点赞".$uid."添加失败");
            return false;
        }
    }

    /**
     *天使玩家数据更新：更新排名，清空天使玩家点赞ID集合
     *@return bool
     */
    public function isUpdateAngel()
    {
        var_dump("更新开始");

        //判断天使玩家排名表是否存在，如果不存在，添加
        //更新时间记录
        $bExit=$this->cache->client()->exists($this->updatekey);
        var_dump($bExit);
        if(!$bExit){
            echo("设置key");
            $recDate=date("Ymd", time()).'030000';
            var_dump($recDate);
            $data = [
                'timing'=> '030000',
                'date'=>$recDate
            ];

            $this->cache->stringSet($this->updatekey,$data);
        }


        //获得天使玩家更新时间信息
        $updateData=$this->cache->stringGet('updateTime:anglePlayer');
        //取出上次更新的时间
        $dateLast=strtotime( $updateData['date']);
        var_dump($dateLast);
        //现在时间
        $dateNow=strtotime(date("YmdHis",time()));
        var_dump($dateNow);
        $subLast=ceil(( $dateNow-$dateLast)/60);
        if($subLast>=0){
            var_dump("超过时间：".$subLast);
            //现在时间（不用日期）
            $timeNow=strtotime(date("His",time()));
            //更新时间点
            $timePoint=strtotime("030000");
            $subPoint=ceil(($timeNow-$timePoint)/60);
            if($subPoint>0&&$subPoint<$subLast){
                //更新数据

                $this->updateAngelPlayerRank();
                var_dump("更新数据");

                //数据更新时间记录
                $recDate=date("Ymd", time()).$updateData['timing'];
                //更新时间记录
                $data = [
                    'timing'=> $updateData['timing'],
                    'date'=>$recDate
                ];
                var_dump("数据更新时间记录");
                var_dump($data);
                //写入更新记录
                $this->cache->stringSet('updateTime:anglePlayer',$data);
                return true;
            }else{
                return false;
            }
        }
        var_dump("更新完毕");

    }

    /**
     * 点赞玩家获绑金
     */
    public function GoldAward($likeId)
    {
        //背包金额增加
        $Bag = new Bag($likeId);
        //充值成功
        $Pay = new Pay();

        //增加绑金
        //金币ID：6
        $rs = $Bag->addBag(6,100);
        //减少金币
        //$Bag->delBag(2,62500);
        if ($rs) {
            $Pay->create(['Uid' => $likeId, 'Gold' => 100, 'CreateTime' => time()]);
        }
            //返回充值成功
    }

    /**
     * 更新天使玩家排名及点赞
     */
    public function updateAngelPlayerRank()
    {
        var_dump("天使排名更新");
        $arrAngel=$this->AngelPlayerRank();
        foreach ($arrAngel as $key=>$value){
            $role=new Role($key);
            //角色数组
            $roleArray=$role->getRoleById($key);
            $this->cache->client()->zAdd($this->AngelPlayerKey,$roleArray['shenjiazhi'],$key);

            //重置天使玩家点赞
            $this->isLikeReset($key);
        }

    }

    /**
     * 天使玩家点赞重置
     * @param int $uid
     * @return bool
     */
    public function isLikeReset($uid)
    {
        var_dump("时间到了,重置天使玩家数据！");

        if($this->isAngelPlayerExist($uid)!=NULL) {
            var_dump("该玩家已存在");
        }

        var_dump("粉丝重置\n");
        $bLikeRem=0;
        if($this->cache->client()->exists($this->likekey.$uid)){
            var_dump("删除玩家点赞".$uid);
            $bLikeRem=$this->cache->client()->del($this->likekey.$uid);
        }else{
            var_dump("玩家点赞不存在".$uid);
            $bLikeRem=true;
        }
        if($bLikeRem){
            var_dump("点赞重置成功");
            return true;
        }else{
            var_dump("点赞重置失败");
            return false;
        }


    }

    /**
     * 获得天使玩家
     * @param int $uid
     * @return Array()
     */
    public function getAngelPlayerArray($uid)
    {
        $role=new Role($uid);
        //角色数组
        $roleArray=$role->getRoleById($uid);
        //var_dump($roleArray);

        $iSocialStatus=$roleArray['shenjiazhi'];
        if($iSocialStatus==0){
            echo("为0，改为1");
            $iSocialStatus=1;
        }
        //判断玩家人气是否存在，如果存在，若为0则赋值为1，不为0则直接获取；如果不存在，则在数据表中添加，并设为1
        $iPopularity=1;
        $bExistPoP=$this->cache->client()->hExists($this->roleKey.$uid,'popularity');
        if($bExistPoP){
            if($roleArray['popularity']==0){
                $iPopularity=1;
            }else{
                $iPopularity=$roleArray['popularity'];
            }
        }else{
            $this->cache->client()->hSet($this->roleKey.$uid,'popularity',1);
            $iPopularity=1;
        }
       //玩家数组
        $data=[
            'uid'=>$uid,
            'name'=>$roleArray['nickname'],
            'icon'=>$roleArray['icon'],//头像
            'level'=>$roleArray['level'],
            'SocialStatus'=>$iSocialStatus,//身价值
            'vip'=>$roleArray['vip'],
            'sign'=>$roleArray['sign'],
            'popularity'=>$iPopularity
        ];
        return $data;
    }

    /**
     * 获得天使玩家数量
     * @return int
     */
    public function getAngelPlayerNum()
    {
        $AngelPlayerNum=$this->cache->client()->zCard($this->AngelPlayerKey);
        return $AngelPlayerNum;
    }

    /**
     * 获得天使玩家排名
     * @return array()
     */
    public function AngelPlayerRank()
    {
        var_dump("天使排名获取");
        //获得最高分数
        $arrMaxScore=$this->cache->client()->zRevRange($this->AngelPlayerKey,0,0,true);
        $iMaxScore=0;
        //取得score
        foreach ($arrMaxScore as &$value){
            $iMaxScore=$value;
        }

        //以最高分数获取所有玩家
        //天使玩家数组
        $arrAngelP=$this->cache->client()->zRevRangeByScore($this->AngelPlayerKey,(int)$iMaxScore,0,array('withscores' => true));
        //var_dump($arrAngelP);

        return $arrAngelP;
    }


}