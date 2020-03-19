<?php

/**
 * Created by PhpStorm.
 * User: dongkai
 * Date: 2018/4/19
 * Time: 下午2:05
 */

namespace App\Models\Excel;
use App\Models\Model;
use think\Db;
use App\Utility\Cache;
use App\Models\User\Role;

/**
 * 充值金额列表
 * Class Topup
 * @package App\Models\Excel
 */
class Topup extends Model
{
    public $table = 'ckzc.Topup';

    private $cache;
    private $roleKey;//角色键key
    private $FirstRechargeKey;//首充key

    public function __construct()
    {
        parent::__construct();
        $this->cache = Cache::getInstance();
        $this->init();
    }

    /**
     * 初始化类
     */
    public function init()
    {
        $this->roleKey='RoleInfo:uid:';
        $this->FirstRechargeKey='FirstRecharge';
    }

    public function insert($arr)
    {
        Db::table($this->table)->insert($arr);
    }

    /**
     * 获取一条数据
     * @param $id
     */
    public function findById($id)
    {
        $data = Db::table($this->table)->where(['Id'=>$id])->find();
        return $data;
    }

    /**
     * 判断是否首充
     * @param $uid
     * @return bool
     */
    public function isFirstRcharge($uid)
    {
        $bExistFir=$this->cache->client()->hExists($this->roleKey.$uid,$this->FirstRechargeKey);
        if($bExistFir){
            $role=new Role($uid);
            $iFirstRecharge=$role['FirstRecharge'];
            if($iFirstRecharge){
                return true;
            }else{
                return false;
            }
        }else{
            return true;
        }
    }

    /**
     * 修改首充记录
     * @param $uid
     * @return bool
     */
    public function WriteFirstRechargeLog($uid)
    {
        $bhSet=$this->cache->client()->hSet($this->roleKey.$uid,$this->FirstRechargeKey,1);
        if($bhSet){
            return true;
        }else{
            return false;
        }
    }
}