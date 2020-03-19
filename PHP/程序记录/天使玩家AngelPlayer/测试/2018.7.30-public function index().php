<?php

 $a=['a:b:c:0','a:b:c:1','A:b:c:d:2','a:b:c:3','a:b:c:4','a:b:c:5'];
        var_dump($a);
        $b=array();
        foreach ($a as $key=>$value){
            // $value = preg_replace('/a:b:c:/i','',$value);//i用来忽略大小写
            // $value = preg_replace('/[abc:]/i','',$value);//替换方括号中的每一个字符,i用来忽略大小写
            $value = preg_replace('/a:b:c:/','',$value);//替换"a:b:c"
            $b[$key]=$value;
        }
        var_dump($b);
        $c=array();
        foreach ($b as $key=>$value){
            //$value = preg_replace('/a:b:c:/','',$value);
            $c[$key]=(int)$value;
        }
        //$a=$b;
        var_dump($c);