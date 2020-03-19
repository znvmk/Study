#pragma once;
#include "stdafx.h"
#include "iostream"//包含了rand()函数

//粒子数量
#define MAX_PARTICLES 10000


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
		float life;//生命力
		float fade;//死亡速率
		float r, g, b;//color
		float x, y, z;//the position位置
		float xd, yd, zd;//方向
		float xa, ya, za;//acceleration加速度
	}particles;


private:
	//颜色模式
	int m_iColorModel;
	//方向模式
	int m_iDirectionModel;
	//加速度模式
	int m_iAccelerationModel;

public:
	particles paticle[MAX_PARTICLES];
	float xSpeed, ySpeed;
	float zoom;
	float sp;
private:
	//初始化粒子
	bool initPractile();
	//改变粒子颜色
	void Color(int n);
	//改变粒子方向
	void Direction(int n);
	//改变粒子加速度
	void Acceleration(int n);
	//改变粒子位置
	void Posiation(int n);

public:
	//设置粒子模式
	void setPractileMode(int color, int direction, int acceleration);

	//改变粒子状态
	//只改变所需的粒子的粒子状态：1-10000
	void changePractile(int num);


	
	
};