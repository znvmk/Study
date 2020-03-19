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


    $a=explode(';',$ft['GetItems'],10000);
    var_dump($a);

    $d1=array();

           foreach ($a as $bb){
               $c=explode(',',$bb,2);
               var_dump($c);
               $d1[$c[0]]=$c[1];
               //if($c[0]=='2'){
               //    $d1=$bb;
               //    break;
              // }
           }
           echo("aaaaaaaaaaaaaaaa");
           var_dump($d1);
    /*
                  $awardmoney=0;
                  foreach ($a as $bb){
                      $c=explode(',',$bb,2);
                      var_dump($c);
                      if($c[0]=='6'){
                          $awardmoney=$c[1];
                          break;
                      }
                  }

                  var_dump ("撒扥带".$d1);
                  var_dump($awardmoney);
          */
}
