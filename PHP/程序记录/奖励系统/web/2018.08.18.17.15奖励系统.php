<?php

 /**
     * 金币充值
     */
    public function msgid_1165()
    {
        $data_pay = CKApiReq::decode($this->data);
        $Id = $data_pay['PayParams']['Id'];
        $Pwd = $data_pay['PayParams']['Pwd'];

        //获取充值的id
        $Topup = new Topup();
        $data_Topup = $Topup->findById($Id);

        //判断app余额是否足够
        $Account = new Account();

        $res = $Account->payByApp($this->uid, $data_Topup['Gold'], $Pwd, 'game_recharge');
        if ($res) {
            //充值成功
            $Pay = new Pay();
            //背包
            $Bag = new Bag($this->uid);
            //是否是首次充值
            $bFirstRecharge=$Topup->isFirstRcharge($this->uid);
            if($bFirstRecharge){
                //是首次充值，修改为已首充，但未领取首充奖励
                $Topup->ModifyFirstRechargeFlag($this->uid,1);
            }

            //金币ID：2
            $rs = $Bag->addBag(2, $data_Topup['Gold']);
            //var_dump($rs);
            //减少金币
            //$Bag->delBag(2,62500);
            if ($rs) {
                $Pay->create(['Uid' => $this->uid, 'Gold' => $data_Topup['Gold'], 'CreateTime' => time()]);
                //返回充值成功
                $data = CkPayResult::encode(true);
                $this->send(1224, $this->fd, $data);
            } else {
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
    }

    
 /**
     * 奖励系统打开
     * return 5027
     */
    public function msgid_5026()
    {
       $rewardSystem=new RewardSystem();
       $GiftBagData=$rewardSystem->getGiftBagList($this->uid);
       $str=RewardSystemResult::encode($GiftBagData);
       if($GiftBagData)
       {
           $this->send(5027,$this->fd,$str);
       }else{
           var_dump("出错");
           $this->send(5027,$this->fd,'','Error',112);
       }
    }

    /**
     * 领取奖励
     * return 5029
     */
    public function msgid_5028()
    {
        $data=$this->data;
        $data_ReceiveRewardReq=ReceiveRewardReq::decode($data);
        $rewardSystem=new RewardSystem();
        $bool=$rewardSystem->reciveGift($this->uid,$data_ReceiveRewardReq);
        $str=ReceiveRewardResult::encode($data_ReceiveRewardReq);
        if($bool&&$str){
            $this->send(5029,$this->fd,$str);
        }else{
            var_dump("领取失败");
            $this->send(5029,$this->fd,'',112);

        }
    }

    $this->send(1226, $this->fd, '', $res['msg'], 12);