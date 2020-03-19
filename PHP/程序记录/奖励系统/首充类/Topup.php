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
    public function isFirstRecharge($uid)
    {
        $bExistFir=$this->cache->client()->hExists($this->roleKey.$uid,$this->FirstRechargeKey);
        var_dump("记录是否存在".$bExistFir);
        if($bExistFir){
            $role=new Role();
            $roleArry=$role->getRoleById($uid);
            var_dump($roleArry);
            echo(".............2");
            $iFirstRecharge=$roleArry['FirstRecharge'];
            var_dump($iFirstRecharge);
            if($iFirstRecharge==0){
                return true;
            }else{
                return false;
            }
        }else{
            return true;
        }
    }

    /**
     * 获取首充标识：0、未充值；1、已首次充值，但未领取首充奖励；2、已领取首充奖励。
     * @param $uid
     * @return int
     */
    public function getFirstRechargeFlag($uid)
    {
        $bExistFir=$this->cache->client()->hExists($this->roleKey.$uid,$this->FirstRechargeKey);
        var_dump("记录是否存在".$bExistFir);
        if($bExistFir) {
            $role = new Role($uid);
            $roleArry = $role->getRoleById($uid);
            var_dump($roleArry);
            echo(".............2");
            $iFirstRecharge = $roleArry['FirstRecharge'];
            var_dump($iFirstRecharge);
            return $iFirstRecharge;
        }else{
            return 0;
        }
    }

    /**
     * 修改首充标识:成功返回首充flag，失败返回0
     * @param $uid,$flag
     * @return int
     */
    public function ModifyFirstRechargeFlag($uid,$flag)
    {
        $bhSet=$this->cache->client()->hSet($this->roleKey.$uid,$this->FirstRechargeKey,$flag);
        if($bhSet){
            return $flag;
        }else{
            return 0;
        }
    }
}