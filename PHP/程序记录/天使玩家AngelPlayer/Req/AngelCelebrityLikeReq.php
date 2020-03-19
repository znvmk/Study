<?php
/**
 * Created by PhpStorm.
 * User: ZhangYunian
 * Date: 2018/7/10
 * Time: 13:35
 */


namespace App\Protobuf\Req;

/**
 * 天使名人点赞请求
 * Class AngelCelebrityOpenReq
 * @package App\Protobuf\Req
 */
class AngelCelebrityLikeReq
{
    public static function decode($data)
    {
        $AngelCelebrityLikeReq = new \AutoMsg\AngelCelebrityLikeReq();
        $AngelCelebrityLikeReq->mergeFromString($data);
        $AngelPlayerId=$AngelCelebrityLikeReq->getAngelPlayerId();
        return $AngelPlayerId;
    }
}
