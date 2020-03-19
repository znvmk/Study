#pragma once;
#include "stdafx.h"
#include "iostream"//包含了rand()函数


class CParticleSystem
{
public:
	CParticleSystem();
	~CParticleSystem();

public:

	/**
	*粒子结构体
	*/
	typedef struct
	{
		bool active;//生死
		float life;//生命力：生存时间
		float fade;//死亡速率
		float r, g, b;//color
		float px,py, pz;//the position位置
		float vx, vy, vz;//速度
		float dx, dy, dz;//方向
		float ax, ay, az;//acceleration加速度
		float size;//粒子大小
	}particles;


private:
	particles*  pPar;//粒子指针
	int iNumPar;//粒子数目
public:
	/** 创建粒子数组 */
	int Create(long num);

	/** 设置和获取颜色属性 */
	int SetColor(float r, float g, float b);
	int SetColor(int index, float r, float g, float b);
	int GetColor(int index, float &r, float &g, float &b);

	/** 设置和获取速度属性 */
	int SetVelocity(float vx, float vy, float vz);
	int SetVelocity(int index, float vx, float vy, float vz);
	int GetVelocity(int index, float &vx, float &vy, float &vz);

	/** 设置和获取位置属性 */
	int SetPosition(float x, float y, float z);
	int SetPosition(int index, float x, float y, float z);
	int GetPosition(int index, float &x, float &y, float &z);

	/** 设置和获取加速度属性 */
	int SetAcceleration(float ax, float ay, float az);
	int SetAcceleration(int index, float ax, float ay, float az);
	int GetAcceletation(int index, float &ax, float &ay, float &az);

	/** 设置和获取尺寸属性 */
	int SetSize(float size);
	int SetSize(int index, float size);
	int GetSize(int index, float &size);

	/** 设置和获取消失速度属性 */
	int SetFade(float Fade);
	int SetFade(int index, float Fade);
	int GetFade(int index, float &Fade);

	/** 设置和获取生命值属性 */
	int SetLife(float lifetime);
	int SetLife(int index, float lifetime);
	int GetLife(int index, float &lifetime);

	/** 获取粒子数组地址 */
	particles *GetParticle() { return pPar; }

	/** 获得粒子的数目 */
	int GetNumOfParticle() { return iNumPar; }

	/** 获得粒子所有的属性 */
	int GetAll(int index,                               /**< 索引 */
		float &r, float &g, float &b,              /**< 粒子的颜色 */
		float &px, float &py, float &pz,        /**< 位置 */
		float &vx, float &vy, float &vz, /**< 速度 */
		float &ax, float &ay, float &az, /**< 加速度 */
		float &size,                           /**< 大小 */
		float &life,                       /**< 生命时间 */
		float &Fade                         /**< 消失速度 */
	);

	/** 设置粒子的所有属性 */
	int SetAll(int index,                           /**< 索引 */
		float r, float g, float b,         /**< 粒子的颜色 */
		float px, float py, float pz,       /**< 位置 */
		float vx, float vy, float vz,    /**< 速度 */
		float ax, float ay, float az,    /**< 加速度 */
		float size,                        /**< 大小 */
		float life,                    /**< 生命时间 */
		float fade                          /**< 消失速度 */
	);


};