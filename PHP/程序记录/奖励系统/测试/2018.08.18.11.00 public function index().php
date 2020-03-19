<?php

public function index()
{
    $gamegift=new RewardSystem();
    //var_dump("giftbag:1111111111111111111111111111111111111111111111111111111111111111"."\n");
    // $giftbag=$gamegift->getGameGiftBag(99);
    //$icon=$gamegift->getGameGiftBagIcon(99);
    //var_dump("图标：".$icon);
    //var_dump("item:2222222222222222222222222222222222222222222222222222222222222222222"."\n");
    //$item=$gamegift->getGiftBagItemArray(99);

    //var_dump($item);
    //$gamegift->reciveFirstRechargeGift(10);
    $gbag=$gamegift->getGiftBagList(10);
    var_dump($gbag);
    $rew=new RewardSystemResult();
    $rewdata=$rew::encode($gbag);
    echo("endoce:");
    //var_dump($rewdata);
}
