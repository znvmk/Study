<?php

/**
 * Created by PhpStorm.
 * User: ZhangYunian
 * Date: 2018/7/10
 * Time: 13:42
 */

namespace App\Protobuf\Result;

/**
 * 天使名人点赞返回
 * Class AngelCelebrityLikeResult
 * @package App\Protobuf\Result
 */
class AngelCelebrityLikeResult
{
    public static function encode($data)
    {
        $AngelCelebrityLikeResult = new \AutoMsg\AngelCelebrityLikeResult();
        $AngelCelebrityLikeResult->setLikeResult($data['likeresult']);
        $AngelCelebrityLikeResult->setAngelPlayerId($data['AngelPlayerId']);
        $AngelCelebrityLikeResult->setPopularity($data['popularity']);
        $str = $AngelCelebrityLikeResult->serializeToString();
        return $str;
    }

}
