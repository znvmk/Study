<?php
/**
 * Created by PhpStorm.
 * User: ZhangYunian
 * Date: 2018/8/18
 * Time: 15:17
 */


namespace App\Protobuf\Result;

/**
 * 领取奖励返回
 * class ReceiveRewardResult
 * @package App\Protobuf\Result
 */
class ReceiveRewardResult
{
    public static function encode($data)
    {
        echo("加密");
        var_dump($data);
        $ReceiveRewardResult = new \AutoMsg\ReceiveRewardResult();
        $ReceiveRewardResult->getRewardId();
        $str = $ReceiveRewardResult->serializeToString();
        return $str;
    }

}