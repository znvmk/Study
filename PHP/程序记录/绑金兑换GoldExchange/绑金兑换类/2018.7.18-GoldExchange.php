<?php
/**
 * Created by PhpStorm.
 * User: ZhangYunian
 * Date: 2018/7/17
 * Time: 17:58
 */


namespace App\Models\Excel;
use App\Models\Model;
use App\Utility\Cache;
use App\Models\User\Role;
use App\Models\BagInfo\Bag;

/**
 * 绑金兑换
 * Class GoldExchange
 * @package App\Models\Excel
 */
class GoldExchange extends Model
{
    private $uid;
    private $cache;
    private $roleKey;//角色键key
    private $GoldExchangeTimes;//金币兑换剩余次数键key



    public function __construct(int $uid)
    {
        parent::__construct();

        $this->uid = $uid;
        $this->cache = Cache::getInstance();
        $this->init();
    }

    /**
     * 初始化类
     */
    public function init()
    {
        $this->roleKey = 'RoleInfo:uid:';
        $this->GoldExchangeTimes='goldExchangeTimes';
    }

    /**
     *获取绑金兑换剩余次数
     * @return int
     */
    public function getRestExchangeTimes()
    {
        //获取绑金兑换剩余次数
        $iGoldExchangeTimes=$this->cache->client()->hGet($this->roleKey.$this->uid,$this->GoldExchangeTimes);
        return $iGoldExchangeTimes;
    }

    /**
     *修改绑金兑换剩余次数
     * @return bool
     */
    public function setExchangeTimes()
    {
        $iGoldExchangeTimes=$this->getRestExchangeTimes();
        //减少绑金兑换剩余次数
        $iGoldExchangeTimesAfter = $iGoldExchangeTimes - 1;
        $this->cache->client()->hSet($this->roleKey.$this->uid,$this->GoldExchangeTimes, $iGoldExchangeTimesAfter);

        $iGoldExchangeTimesAfter=$this->getRestExchangeTimes();
        if($iGoldExchangeTimesAfter==($iGoldExchangeTimes-1)){
            return true;
        }else{
            return true;
        }

    }

    /**
     * 兑换档次（比率）
     * @param int grade://判断是否为兑换：0为打开兑换页面请求,返回null；1-5为兑换金币档次
     * @return array()
     */
    public function getExchangeGrade($grade)
    {
        if($grade > 0) {
            //要兑换非绑金数量
            $iFGoldNum = 0;
            //所得相应绑金数量
            $iBGoldNum = 0;
            switch ($grade) {
                case 1:
                    $iFGoldNum = 10;
                    $iBGoldNum = 3500;
                    break;
                case 2:
                    $iFGoldNum = 50;
                    $iBGoldNum = 17500;
                    break;
                case 3:
                    $iFGoldNum = 100;
                    $iBGoldNum = 35000;
                    break;
                case 4:
                    $iFGoldNum = 500;
                    $iBGoldNum = 175000;
                    break;
                case 5:
                    $iFGoldNum = 1000;
                    $iBGoldNum = 350000;
                    break;
                default:
                    break;
            }
            $data = [
                'iFGoldNum' => $iFGoldNum,
                'iBGoldNum' => $iBGoldNum
            ];
            return $data;
        }else{
            return NULL;
        }
    }

    /**
     * 获取非绑金数目
     * @return int
     */
    public function getFreeGold()
    {
        $bag=new Bag($this->uid);
        $arrFreeGold=$bag->getBagByItemId(2);
        $iFreeGold=(int)$arrFreeGold['CurCount'];
        return $iFreeGold;
    }

    /**
     * 获取绑金数目
     * @return int
     */
    public function getBindGold()
    {
        $bag=new Bag($this->uid);
        $arrBindGold=$bag->getBagByItemId(6);
        $iBindGold=(int)$arrBindGold['CurCount'];
        return $iBindGold;
    }

    /**
     * 绑金兑换
     * @return array()
     */
    public function GoldExchange($grade)
    {
        var_dump($this->uid);
        //获取绑金兑换剩余次数
        $iGoldExchangeTimes=$this->getRestExchangeTimes();
        var_dump("剩余次数：".$iGoldExchangeTimes);

        $bag=new Bag($this->uid);
        //var_dump($bag);
        echo("1....3");
        //获取非绑金数目
        $iFreeGold=$this->getFreeGold();
        echo("非绑金");
        var_dump($iFreeGold);
        echo("1....4");
        //获取绑金数目
        $iBindGold=$this->getBindGold();
        echo ("绑金");
        var_dump($iBindGold);
        echo("1....5");
        //判断剩余次数是否足够
        if($iGoldExchangeTimes>0){
            //判断是否为兑换：0为打开兑换页面请求，1-5为兑换金币档次
            if($grade > 0){
                //获取兑换档次（比率）
                $exchangeGrade=$this->getExchangeGrade($grade);
                //要兑换非绑金数量
                $iFGoldNum=$exchangeGrade['iFGoldNum'];
                //所得相应绑金数量
                $iBGoldNum=$exchangeGrade['iBGoldNum'];

                //剩余非绑金足够此次兑换，才可进行兑换
                if($iFreeGold>=$iFGoldNum){
                    //减去相应数量非绑金
                    $delRes=$bag->delBag(2,$iFGoldNum);
                    //如果非绑金扣除成功
                    if($delRes) {
                        //增加相应数量绑金
                        $addRes=$bag->addBag(6,$iBGoldNum);
                        //绑金增加成功
                        if($addRes){
                            //减少绑金兑换剩余次数
                            $this->setExchangeTimes();

                            //获取操作后结果，返回
                            //获取非绑金数目
                            $iFreeGold=$this->getFreeGold();
                            echo("非绑金");
                            var_dump($iFreeGold);
                            echo("1....4");
                            //获取绑金数目
                            $iBindGold=$this->getBindGold();
                            echo ("绑金");
                            var_dump($iBindGold);
                            //获取绑金兑换剩余次数
                            $iGoldExchangeTimes=$this->getRestExchangeTimes();

                            $data=[
                                'success'=>1,//成功
                                'freegold'=> $iFreeGold,
                                'bindgold'=> $iBindGold,
                                'surplustimes'=>$iGoldExchangeTimes
                            ];
                            return $data;
                        }else{
                            //如果绑金增加失败，还原非绑金
                            $bag->addBag(2,$iFGoldNum);
                        }
                    }
                }
            }
        }
        echo("1....6");
        //grade=0：为打开页面请求，返回玩家信息
        $data=[
           'success'=>2,
           'freegold'=>$iFreeGold,
           'bindgold'=>$iBindGold,
           'surplustimes'=>$iGoldExchangeTimes
        ];
        var_dump($data);
        return $data;
    }
};
