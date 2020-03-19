/**
     * 兑换绑金
     * return 5005 GoldExchangeResult
     */
    public function msgid_5004()
    {
        $uid = $this->uid;
        $data = $this->data;
        //兑换档次
        $dataReq = GoldExchangeReq::decode($data);
        echo("接收的请求：");
        var_dump($dataReq);
        $goldExchange = new GoldExchange($uid);
        if ($dataReq > 0) {
            if ($goldExchange->getRestExchangeTimes() < 1) {
                echo("玩家剩余兑换次数不足");
                $this->send(5005, $this->fd, 0,'BuyCountMax',1);
            }else {
                $iFreeGold = $goldExchange->getFreeGold(); //获取非绑金数目
                $exchangeGrade = $goldExchange->getExchangeGrade($dataReq);//获取兑换档次（比率）
                $iFGoldNum = $exchangeGrade['iFGoldNum']; //要兑换非绑金数量
                if ($iFreeGold < $iFGoldNum) { //剩余非绑金足够此次兑换，才可进行兑换
                    echo("非绑金不足，无法兑换");
                    $this->send(5005, $this->fd, 0, 'ChangeGoldLimit', 1);
                }
            }
        }
        $dataRes = $goldExchange->GoldExchange($dataReq);
        if ($dataReq > 0) {
            $iSuccess = $dataRes['success'];
            if ($iSuccess == 2) {
                echo("绑金兑换失败");
                $this->send(5005, $this->fd, 0,'ChangeMoneyErr',1);
            }
        }

        if ($dataRes) {
            $str = GoldExchangeResult::encode($dataRes);
            $this->send(5005, $this->fd, $str);
        }
    }
