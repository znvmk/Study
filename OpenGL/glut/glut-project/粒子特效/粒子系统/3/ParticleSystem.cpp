#include "ParticleSystem.h"

CParticleSystem::CParticleSystem()
{
	pPar = NULL;
	iNumPar = 0;
}

CParticleSystem::~CParticleSystem()
{
	delete []pPar;
	pPar = NULL;
}


/** 创建一个包含num个元素的粒子数组 */
int CParticleSystem::Create(long num)
{
	/** 删除粒子数组 */
	if (pPar)
		delete[]pPar;

	/** 创建数组 */
	if (pPar = new particles[num])
	{
		memset(pPar, 0, sizeof(particles)*iNumPar);
		iNumPar = num;

		/** 返回粒子个数 */
		return iNumPar;
	}
	return 0;
}


/** 设置和获取颜色Color的函数实现 */
int CParticleSystem::SetColor(float r, float g, float b)
{
	for (int index = 0; index<iNumPar; ++index)
	{
		pPar[index].r = r;
		pPar[index].g = g;
		pPar[index].b = b;
	}
	return true;
}

int CParticleSystem::SetColor(int index, float r, float g, float b)
{
	if (index >= 0 && index<iNumPar)
	{
		pPar[index].r = r;
		pPar[index].g = g;
		pPar[index].b = b;
		return true;
	}
	return false;
}

int CParticleSystem::GetColor(int index, float &r, float &g, float &b)
{
	if (index >= 0 && index<iNumPar)
	{
		r = pPar[index].r;
		g = pPar[index].g;
		b = pPar[index].b;
		return true;
	}
	return false;
}

/** 设置和获取位置Position的函数实现 */
int CParticleSystem::SetPosition(float x, float y, float z)
{
	for (int index = 0; index<iNumPar; ++index)
	{
		pPar[index].px = x;
		pPar[index].py = y;
		pPar[index].pz = z;
	}
	return true;
}

int CParticleSystem::SetPosition(int index, float x, float y, float z)
{
	if (index >= 0 && index<iNumPar)
	{
		pPar[index].px = x;
		pPar[index].py = y;
		pPar[index].pz = z;
		return true;
	}
	return false;
}

int CParticleSystem::GetPosition(int index, float &x, float &y, float &z)
{
	if (index >= 0 && index<iNumPar)
	{
		x = pPar[index].px;
		y = pPar[index].py;
		z = pPar[index].pz;
		return true;
	}
	return false;
}
/** 设置和获取加速度Acceleration的函数实现 */
int CParticleSystem::SetAcceleration(float ax, float ay, float az)
{
	for (int index = 0; index<iNumPar; ++index)
	{
		pPar[index].ax = ax;
		pPar[index].ay = ay;
		pPar[index].az = az;
	}
	return true;
}

int CParticleSystem::SetAcceleration(int index, float ax, float ay, float az)
{
	if (index >= 0 && index<iNumPar)
	{
		pPar[index].ax = ax;
		pPar[index].ay = ay;
		pPar[index].az = az;
		return true;
	}
	return false;
}


int CParticleSystem::GetAcceletation(int index, float &ax, float &ay, float &az)
{
	if (index >= 0 && index<iNumPar)
	{
		ax = pPar[index].ax;
		ay = pPar[index].ay;
		az = pPar[index].az;
		return true;
	}
	return false;
}



/** Velocity函数的实现 */
int CParticleSystem::SetVelocity(float vx, float vy, float vz)
{
	for (int index = 0; index<iNumPar; ++index)
	{
		pPar[index].vx = vx;
		pPar[index].vy = vy;
		pPar[index].vz = vz;
	}
	return true;
}

int CParticleSystem::SetVelocity(int index, float vx, float vy, float vz)
{
	if (index >= 0 && index<iNumPar)
	{
		pPar[index].vx = vx;
		pPar[index].vy = vy;
		pPar[index].vz = vz;
		return true;
	}
	return false;
}

int CParticleSystem::GetVelocity(int index, float &vx, float &vy, float &vz)
{
	if (index >= 0 && index<iNumPar)
	{
		vx = pPar[index].vx;
		vy = pPar[index].vy;
		vz = pPar[index].vz;
		return true;
	}
	return false;
}


/** Size函数的实现 */
int CParticleSystem::SetSize(float size)
{
	for (int index = 0; index<iNumPar; ++index)
	{
		pPar[index].size = size;
	}
	return true;
}

int CParticleSystem::SetSize(int index, float size)
{
	if (index >= 0 && index<iNumPar)
	{
		pPar[index].size = size;
		return true;
	}
	return false;
}

int CParticleSystem::GetSize(int index, float &size)
{
	if (index >= 0 && index < iNumPar)
	{
		size = pPar[index].size;
		return true;
	}
	return false;
}

/** 消失速度fade函数 */
int CParticleSystem::SetFade(float fade)
{
	for (int index = 0; index<iNumPar; ++index)
	{
		pPar[index].fade = fade;
	}
	return true;
}

int CParticleSystem::SetFade(int index, float fade)
{
	if (index >= 0 && index < iNumPar)
	{
		pPar[index].fade = fade;
		return true;
	}
	return false;
}

int CParticleSystem::GetFade(int index, float &fade)
{
	if (index >= 0 && index < iNumPar)
	{
		fade = pPar[index].fade;
		return true;
	}
	return false;
}

/** 设置粒子的life 属性 */
int CParticleSystem::SetLife(float life)
{
	for (int index = 0; index<iNumPar; ++index)
	{
		pPar[index].life = life;
	}
	return true;
}

int CParticleSystem::SetLife(int index, float life)
{
	if (index >= 0 && index < iNumPar)
	{
		pPar[index].life = life;
		return true;
	}
	return false;
}

/** 获得粒子的life属性 */
int CParticleSystem::GetLife(int index, float &life)
{
	if (index >= 0 && index < iNumPar)
	{
		life = pPar[index].life;
		return true;
	}
	return false;
}

/** 获取粒子的所有属性 */
int CParticleSystem::GetAll(int index, float &r, float &g, float &b,         /**< 粒子的颜色 */
	float &px, float &py, float &pz,     /**< 位置 */
	float &vx, float &vy, float &vz,  /**< 速度 */
	float &ax, float &ay, float &az,  /**< 加速度 */
	float &size,                            /**< 大小 */
	float &life,                        /**< 生命时间 */
	float &fade                          /**< 消失速度 */
)
{
	if (index >= 0 && index<iNumPar)
	{
		r = pPar[index].r;
		g = pPar[index].g;
		b = pPar[index].b;
		px = pPar[index].px;
		py = pPar[index].py;
		pz = pPar[index].pz;
		vx = pPar[index].vx;
		vy = pPar[index].vy;
		vz = pPar[index].vz;
		ax = pPar[index].ax;
		ay = pPar[index].ay;
		az = pPar[index].az;
		life = pPar[index].life;
		size = pPar[index].size;
		fade = pPar[index].fade;
		return true;
	}
	return false;
}

/** 设置粒子的所有属性 */
int CParticleSystem::SetAll(int index, float r, float g, float b,        /**< 粒子的颜色 */
	float px, float py, float pz,        /**< 位置 */
	float vx, float vy, float vz, /**< 速度 */
	float ax, float ay, float az, /**< 加速度 */
	float size,                     /**< 大小 */
	float life,                 /**< 生命时间 */
	float fade                           /**< 消失速度 */
)
{
	if (index >= 0 && index<iNumPar)
	{
		pPar[index].r = r;
		pPar[index].g = g;
		pPar[index].b = b;
		pPar[index].px = px;
		pPar[index].py = py;
		pPar[index].pz = pz;
		pPar[index].vx = vx;
		pPar[index].vy = vy;
		pPar[index].vz = vz;
		pPar[index].ax = ax;
		pPar[index].ay = ay;
		pPar[index].az = az;
		pPar[index].life = life;
		pPar[index].size = size;
		pPar[index].fade = fade;
		return true;
	}
	return false;
}