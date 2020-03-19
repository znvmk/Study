<?php

//App\Websocket\Colltroller\Web.php  中
//引用 App\Models\Excel\GameGifts
use App\Models\Excel\GameGifts;
/**
     * 金币充值
     */
    public function msgid_1165()
    {
        var_dump($this->uid);
        $data_pay = CKApiReq::decode($this->data);
        $Id = $data_pay['PayParams']['Id'];
        $Pwd = $data_pay['PayParams']['Pwd'];

        //获取充值的id
        $Topup = new Topup();
        $data_Topup = $Topup->findById($Id);

        //判断app余额是否足够
        $Account = new Account();

        $res = $Account->payByApp($this->uid,$data_Topup['Gold'],$Pwd,'game_recharge');

        //$res['cdode']=400，测试时改为：200
        $res['code']=200;

        if($res['code'] == 200){

            //充值成功
            $Pay = new Pay();

            //背包金额增加
            $Bag = new Bag($this->uid);

            //是否是首次充值
            //如果是首次充值，基本充值金额+首充奖励；如果不是，只有充值金额
            if($Pay->getFirstRecharge($this->uid)){

                echo("是首次充值：奖励");
                //本次充值的总金额：充值金额+首充奖励
                //获取首充奖励数据
                $gamegifts=new GameGifts();
                $ft=$gamegifts->FirstTopup();

                //如果是金币（ID=2），充值金额+首充奖励
                foreach ($ft as $k => $value) {
                    if ($k == 2) {
                        $ft[$k] = $value + $data_Topup['Gold'];
                    }

                }
                //批量增加道具
               $Bag->batchAddBag($ft);

            }elseif(!$Pay->getFirstRecharge($this->uid)){
                echo("不是首次充值");
                //金币ID：2
                $rs = $Bag->addBag(2,$data_Topup['Gold']);
                //减少金币
                //$Bag->delBag(2,62500);

                if($rs){
                    $Pay->create(['Uid'=>$this->uid,'Gold'=>$data_Topup['Gold'],'CreateTime'=>time()]);
                    //返回充值成功
                    $data  = CkPayResult::encode(true);
                    $this->send(1224,$this->fd,$data);
                }
            }
        }else {
            //充值失败
            $data = CkPayResult::encode(false);
            $WsResult = new WsResult();
            if ($res['datas']['error'] == '您输入的密码有误') {
//                $data_ws = $WsResult->getOne('APP支付密码不对');
                $this->send(1224, $this->fd, $data, 'APP支付密码不对');
            } elseif ($res['datas']['error'] == '余额不足！！！') {
//                $data_ws = $WsResult->getOne('APP余额不足');
                $this->send(1224, $this->fd, $data, 'APP余额不足');
            }
        }
    }
