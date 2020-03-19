<?php

/**
 * Created by PhpStorm.
 * User: ZhangYunian
 * Date: 2018/7/10
 * Time: 11:28
 */


namespace App\Protobuf\Result;

/**
 *
 * Class AngelPlayerList
 * @package App\Protobuf\Result
 */
class AngelPlayerInfo
{
    public static function encode($data)
    {
       // var_dump($data);
        $AngelPlayerInfo = new \AutoMsg\AngelPlayerInfo();
        $AngelPlayerInfo->setAngelPlayerId($data['uid']);
        $AngelPlayerInfo->setName($data['name']);
        $AngelPlayerInfo->setIcon($data['icon']);
        $AngelPlayerInfo->setLevel($data['level']);
        $AngelPlayerInfo->setSocialStatus($data['SocialStatus']);
        $AngelPlayerInfo->setVip($data['vip']);
        $AngelPlayerInfo->setSign($data['sign']);
        $AngelPlayerInfo->setPopularity($data['popularity']);
        $AngelPlayerInfo->setLike($data['like']);
        return $AngelPlayerInfo;
    }
}
