<?php

/**
 * Created by PhpStorm.
 * User: ZhangYunian
 * Date: 2018/7/17
 * Time: 17:41
 */


namespace App\Protobuf\Req;

/**
 * 绑金兑换请求
 * class GoldExchangeReq
 * @package App\Protobuf\Req
 */
class GoldExchangeReq
{
    public static function decode($data)
    {
        $GoldExchangeReq = new \AutoMsg\GoldExchangeReq();
        $GoldExchangeReq->mergeFromString($data);
        $Grade=$GoldExchangeReq->getGrade();
        return $Grade;
    }
}
