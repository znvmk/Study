<?php

/**
 * Created by PhpStorm.
 * User: ZhangYunian
 * Date: 2018/7/10
 * Time: 10:52
 */


namespace App\Protobuf\Result;

/**
 * 打开天使名人返回
 * Class AngelCelebrityOpenResult
 * @package App\Protobuf\Result
 */
class AngelCelebrityOpenResult
{
    public static function encode($data,$Count)
    {
        $AngelCelebrityOpenResult = new \AutoMsg\AngelCelebrityOpenResult();
        $AngelPlayers=[];
        if($data){
            foreach ($data as $k=>$datum) {
                $AngelPlayers[$k] = AngelPlayerInfo::encode($datum);
            }
        }
        //var_dump($AngelPlayers);
        $AngelCelebrityOpenResult->setAngelPlayerDic($AngelPlayers);
        $AngelCelebrityOpenResult->setCount($Count);
        $str = $AngelCelebrityOpenResult->serializeToString();
        return $str;
    }



}
