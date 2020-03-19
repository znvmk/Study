GameGifts.php
<?php

/**
 * Created by PhpStorm.
 * User: zhangyunian
 * Date: 2018/7/4
 * Time: 14:39
 */


namespace App\Models\Excel;
use App\Models\Model;
use think\Db;

/**
 * 游戏奖励列表
 * Class GameGifts
 * @package App\Models\Excel
 */
class GameGifts extends Model
{
    public $table = 'ckzc.Excel_GameGifts';
    /*
    public function insert($arr)
    {
        Db::table($this->table)->insert($arr);
    }
    */

    /**
     * 获取一条数据
     * @param $id
     */
    public function findById($id)
    {
        $data = Db::table($this->table)->where(['Id'=>$id])->find();
        return $data;
    }

    /**
     * 首充奖励：所有奖励道具
     * 奖励道具ID=3
     * 返回奖励道具数组：key：背包道具ID，value：道具数量
     * @return array()
     */
    public function FirstTopup()
    {
        echo("获取首充奖励数组");
        $award = $this->findById(3);
        $data = explode(';',$award['GetItems']);
        $newData = [];
        foreach ($data as $d) {
            $temp = explode(',',$d);
            $newData[$temp['0']] = $temp['1'];
        }

        return $newData;
    }

    /**
     * 首充金币奖励：只有金币奖励项目
     * 奖励道具ID=3
     * 金币奖励ID=2
     * 返回首充金币数量
     * @return int
     */
    public function FirstTopupGold()
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
}

/*aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa*/

测试时将：App\Models\User\Account.php->payByApp()中
//$arr['cdode']=400，测试时改为：200
$arr['code']=200;
测试时将：App\Websocket\Controller\web.php->msgid_1165()中
//$res['cdode']=400，测试时改为：200
$res['code']=200;
