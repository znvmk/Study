<?php
/**
 * Created by PhpStorm.
 * User: ZhangYunian
 * Date: 2018/7/4
 * Time: 14:39
 */


namespace App\Models\RewardSystem;
use App\Models\Model;
use think\Db;
use App\Models\Excel\Topup;
use App\Models\BagInfo\Bag;

/**
 * 游戏奖励列表
 * Class GameGifts
 * @package App\Models\Excel
 */
class RewardSystem extends Model
{
    public $tableGameGifts ;
    public $tableItem;

    public function __construct()
    {
        parent::__construct();
        $this->init();
    }

    /**
     * 初始化类
     */
    public function init()
    {
        $this->tableGameGifts = 'ckzc.Excel_SpecialGiftBag';
        $this->tableItem='ckzc.item';
    }
    /**
     * 获取一条数据
     * @param $id
     */
    public function findById($id)
    {
        $data = Db::table($this->tableGameGifts)->where(['Id'=>$id])->find();
        return $data;
    }

    /**
     *获取表数据
     *@param $table,$id
     *return data
     */
    public function selectData($table,$id)
    {
        $data = Db::table($table)->where(['Id'=>$id])->find();
        return $data;
    }

    /**
     * 获取礼包
     * @param $id:礼包id
     * @return array
     */
    public function getGameGiftBag($id)
    {
        echo("获取礼包");
        $strGiftBag=$this->selectData($this->tableGameGifts,$id);
        $arrGiftBag=explode(',',$strGiftBag['Item'],2);
        var_dump($arrGiftBag);
        return $arrGiftBag;
    }

    /**
     * 获取礼包图标
     * @param $GiftBagid
     * @return string
     */
    public function getGameGiftBagIcon($GiftBagid)
    {
        //echo("获取奖励道具数组");
        $arrGiftBag=$this->getGameGiftBag($GiftBagid);
        //var_dump()
        $id=(int)$arrGiftBag[0];
        var_dump($id);
        $num=$arrGiftBag[1];
        $award = $this->selectData($this->tableItem,$id);
        var_dump($award);

       return $award['Icon'];
    }
    /**
     * 获取礼包道具：所有奖励道具
     * 奖励道具ID=3
     * 返回奖励道具数组：key：背包道具ID，value：道具数量
     * @return array()
     */
    public function getGiftBagItemArray($GiftBagid)
    {
        //echo("获取奖励道具数组");
        $arrGiftBag=$this->getGameGiftBag($GiftBagid);
        //var_dump()
        $id=(int)$arrGiftBag[0];
        var_dump($id);
        $num=$arrGiftBag[1];
        $award = $this->selectData($this->tableItem,$id);
        var_dump($award);
        $data = explode(';',$award['UseEffet']);
        var_dump("UseEffet:".$award['UseEffet']);
        var_dump($data);

        $newData = [];
        foreach ($data as $d) {
            $temp = explode(',',$d);
            //var_dump($temp);
            $newData[$temp['1']] = $temp['2'];
        }
        echo("获取奖励道具数组");
        var_dump($newData);
        return $newData;
    }

    /**
     * 首充金币奖励：只有金币奖励项目
     * 奖励道具ID=3
     * 金币奖励ID=2
     * 返回首充金币数量
     * @return int
     */
    public function FirstRechargeGold()
    {
        echo("获取首充金币数量");
        $award=$this->findById(3);
        $a=explode(';',$award['GetItems'],10000);
        $awardmoney=0;
        foreach ($a as $bb){
            $c=explode(',',$bb,2);
            if($c[0]=='2'){
                $awardmoney=$c[1];
                break;
            }
        }

        return  $awardmoney;
    }

    /**
     * 领取首充奖励：0、未充值；1、已首次充值，但未领取首充奖励；2、已领取首充奖励。
     * @Param uid
     * @return bool
     */
    public function reciveGift($uid,$id)
    {
        if($id==1){

        }
        $topup= new Topup();
        $bag=new Bag($uid);
        $iRechargeFlag=$topup->getFirstRechargeFlag($uid);
        var_dump("rechFlag:".$iRechargeFlag);
        $iRechargeFlag=1;
        if($iRechargeFlag==1){
            $gamegift=$this->getGiftBagItemArray(99);
            //var_dump($gamegift);
            //批量增加道具
            $bag->batchAddBag($gamegift);
            //首充flag修改为2：已经领取首充奖励
            $topup->ModifyFirstRechargeFlag($uid,2);
            return true;
        }else{
            return false;
        }
    }

     /**
     * 获取奖励礼包列表：
     */
    public function getGiftBagList($uid)
    {
        $topup=new Topup();
        $arrGiftBagList=[];
        $i=1;

        $arrGiftBagList[1]=[
            'flag'=>$topup->getFirstRechargeFlag($uid),
            //'giftBag'=>$this->getGameGiftBag(99)['0']
            'giftBag'=>1
        ];
        if($arrGiftBagList){
            //返回所有数据数组
            return $arrGiftBagList;
        }else{
            return false;
        }

    }
}