#include "ParticleSystem.h"

CParticleSystem::CParticleSystem()
{
	m_iColorModel = 0;
	m_iDirectionModel = 0;
	m_iAccelerationModel = 0;
	zoom = -40.0f;
	float sp=40;
	xSpeed = 5;
	ySpeed = 5;
	initPractile();
}

CParticleSystem::~CParticleSystem()
{

}


bool CParticleSystem::initPractile()
{
	int idn = 0;
	for (idn = 0; idn <MAX_PARTICLES; ++idn)
	{
		paticle[idn].active = true;
		paticle[idn].life = 1.0f;//full life is 1.0f
								  //life decrease rate(a random value add 0.003f : never equals 0)
		paticle[idn].fade = float(rand() % 100) / 1000.0f + 0.003f;
		paticle[idn].r = 0.0;
		paticle[idn].g = 0.0;
		paticle[idn].b = 0.0;

		//paticle[idn].xd = float((rand() % 50) - 26.0f) * 10.0f;
		//paticle[idn].yd = float((rand() % 50) - 25.0f) * 10.0f;
		//paticle[idn].zd = float((rand() % 50) - 25.0f) * 10.0f;hhhh

		paticle[idn].xd = float((rand() % 10) / 10);
		paticle[idn].yd = float((rand() % 10) / 10);
		paticle[idn].zd = float((rand() % 10) / 10);

		paticle[idn].xa = 0.0f;
		paticle[idn].ya = -0.8f;
		paticle[idn].za = 0.8f;

		//reset its position
		//paticle[idn].x = 0.0f;
		//paticle[idn].y = 0.0f;
		//paticle[idn].z = 0.0f;
	}
	return true;
}


void CParticleSystem::changePractile(int num)
{
	int idnMax = 10;
	if (num > 0 && num <= MAX_PARTICLES) idnMax = num;
	int idn = num;
	//for (int idn = 0; idn <idnMax; ++idn)
	//{
	if (paticle[idn].active)//the particle is alive
	{
		//Direction(idn);
		Posiation(idn);
		Acceleration(idn);
		Color(idn);

		//decrease particles' life
		paticle[idn].life -= paticle[idn].fade;
	}
	//if particle is dead,rejuvenate it
	if (paticle[idn].life < 0.0f)
	{
		paticle[idn].life = 1.0f;//alive again
		paticle[idn].fade = float(rand() % 100) / 1000.0f + 0.003f;

		//reset its position
		/*
		paticle[idn].x = 0.0f;
		paticle[idn].y = 0.0f;
		paticle[idn].z = 0.0f;
		*/
		int a = 10;
		paticle[idn].x = float(rand() % a) / 10.0f;
		paticle[idn].y = float(rand() % a) / 10.0f;
		paticle[idn].z = float(rand() % a) / 10.0f;


	}		
}
//改变粒子颜色
void CParticleSystem::Color(int n)
{
	/*
	paticle[n].r = 0.5;
	paticle[n].g = 0.7;
	paticle[n].b = 0.6;
	*/

	paticle[n].r = float((rand() % 10)) / 10.0f;
	paticle[n].g = float((rand() % 10)) / 10.0f;
	paticle[n].b = float((rand() % 10)) / 10.0f;
}
//改变粒子方向
void CParticleSystem::Direction(int n)
{
	paticle[n].xd = float((rand() % 10) / 10);
	paticle[n].yd = float((rand() % 10) / 10);
	paticle[n].zd = float((rand() % 10) / 10);
}
//改变粒子加速度
void CParticleSystem::Acceleration(int n)
{
	//paticle[n].xa = 0.0f;
	//paticle[n].ya = -0.8f;
	//paticle[n].za = 0.8f;

	//X Axis Speed And Direction
	paticle[n].xd = xSpeed + float((rand() % 60) - 32.0f);
	// Y Axis Speed And Direction
	paticle[n].yd = ySpeed + float((rand() % 60) - 30.0f);
	// Z Axis Speed And Direction
	paticle[n].zd = float((rand() % 60) - 30.0f);
}

//改变粒子位置
void CParticleSystem::Posiation(int n)
{
	//float sp = 10;
	//Move On The X Axis By X Speed
	paticle[n].x += paticle[n].xd / (sp * 10);
	//Move On The Y Axis By Y Speed
	paticle[n].y += paticle[n].yd / (sp * 10);
	//Move On The Z Axis By Z Speed
	paticle[n].z += paticle[n].zd / (sp * 10);
}

void CParticleSystem::setPractileMode(int color, int direction, int acceleration)
{
	m_iColorModel = color;
	m_iDirectionModel = direction;
	m_iAccelerationModel = acceleration;
}