<?php
/**
 * Created by PhpStorm.
 * User: ZhangYunian
 * Date: 2018/7/17
 * Time: 17:42
 */


namespace App\Protobuf\Result;

/**
 * 绑金兑换返回
 * class GoldExchangeResult
 * @package App\Protobuf\Result
 */
class GoldExchangeResult
{
    public static function encode($data)
    {
        echo("加密");
        var_dump($data);
        $GoldExchangeResult = new \AutoMsg\GoldExchangeResult();
        $GoldExchangeResult->setSuccess($data['success']);
        $GoldExchangeResult->setFreeGold($data['freegold']);
        $GoldExchangeResult->setBindGold($data['bindgold']);
        $GoldExchangeResult->setSurplusTimes($data['surplustimes']);
        $str = $GoldExchangeResult->serializeToString();
        return $str;
    }

}
