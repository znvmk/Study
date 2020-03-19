<?php
/**
 * Created by PhpStorm.
 * User: ZhangYunian
 * Date: 2018/8/18
 * Time: 15:40
 */


namespace App\Protobuf\Result;

/**
 *
 * Class RewardInfo
 * @package App\Protobuf\Result
 */
class RewardInfo
{
    public static function encode($data)
    {
        echo("打包");
         var_dump($data);
        $RewardInfo = new \AutoMsg\RewardInfo();
        $RewardInfo->setFlag($data['flag']);
        $RewardInfo->setGiftBag($data['giftBag']);
        return $RewardInfo;
    }
}