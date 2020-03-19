<?php

public function index()
{
    echo("aa");
    $gg=new \App\Models\Excel\GameGifts();
    $ft=$gg->findById(3);
    var_dump($ft);
    echo("dsdddddddddddddddddddddd");
    var_dump($ft['GetItems']);
    echo("11111111111111111ddddddddddddddd");

   //*
           $a=explode(';',$ft['GetItems'],10000);
           var_dump($a);

           $d1=array();

                  foreach ($a as $bb){
                      $c=explode(',',$bb,2);
                      var_dump($c);
                      $d1[$c[0]]=$c[1];
                  }
                  echo("奖励数组：\n");
     var_dump ($d1);


                 //*/

    $bag=new \App\Models\BagInfo\Bag(119);
    echo("11111111111111111daaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaadddddddddddddd");
   $dd= $bag->getCountByItemId(2);
   var_dump("\n".$dd);
    $dd= $bag->getCountByItemId(6);
    var_dump("\n".$dd);

   $bag->batchAddBag($d1);

    $dd= $bag->getCountByItemId(2);
    var_dump("\n".$dd);
    $dd= $bag->getCountByItemId(6);
    var_dump("\n".$dd);
}
