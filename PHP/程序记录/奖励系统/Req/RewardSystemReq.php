<?php
/**
 * Created by PhpStorm.
 * User: ZhangYunian
 * Date: 2018/8/18
 * Time: 15:15
 */


namespace App\Protobuf\Req;

/**
 * 打开奖励系统请求
 * class RewardSystemReq
 * @package App\Protobuf\Req
 */
class RewardSystemReq
{
    public static function decode($data)
    {
        $RewardSystemReq = new \AutoMsg\RewardSystemReq();
        $RewardSystemReq->mergeFromString($data);
        //return $Grade;
    }
}