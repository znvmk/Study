<?php
/**
 * Created by PhpStorm.
 * User: ZhangYunian
 * Date: 2018/8/18
 * Time: 15:16
 */


namespace App\Protobuf\Req;

/**
 * 领取奖励请求
 * class ReceiveRewardReq
 * @package App\Protobuf\Req
 */
class ReceiveRewardReq
{
    public static function decode($data)
    {
        $ReceiveRewardReq = new \AutoMsg\ReceiveRewardReq();
        $ReceiveRewardReq->mergeFromString($data);
        $RewardId=$ReceiveRewardReq->getRewardId();
        return $RewardId;
    }
}