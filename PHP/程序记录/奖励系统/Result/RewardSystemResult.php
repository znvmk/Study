<?php
/**
 * Created by PhpStorm.
 * User: ZhangYunian
 * Date: 2018/8/18
 * Time: 15:16
 */


namespace App\Protobuf\Result;

/**
 * 打开奖励系统返回
 * class RewardSystemResult
 * @package App\Protobuf\Result
 */
class RewardSystemResult
{
    public static function encode($data)
    {
        $RewardSystemResult=new \AutoMsg\RewardSystemResult();
        $RewardSystem=[];
        if($data){
            foreach ($data as $k=>$datum) {
                $RewardSystem[$k] = RewardInfo::encode($datum);
            }
        }
        //var_dump($AngelPlayers);
        $RewardSystemResult->setRewardInfoDic($RewardSystem);
        $str = $RewardSystemResult->serializeToString();
        return $str;
        //测试
        //return $RewardSystem;
    }

}