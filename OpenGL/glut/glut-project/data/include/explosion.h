/****************************************************************************
 Snowstorm.h  Particle system representing a snowstorm
 Author   :   Dave Astle
 Date     :   3/17/2001
 Written for OpenGL Game Programming
*****************************************************************************/
#ifndef __EXPLOSION_H_INCLUDED__
#define __EXPLOSION_H_INCLUDED__
/********************************* Includes *********************************/
#include "Particles.h"
/*************************** Constants and Macros ***************************/
const CVector PARTICLE_VELOCITY  (0.0f, 2.0f, 0.0f);
const CVector VELOCITY_VARIATION  (4.0f, 4.0f, 4.0f);
const CVector PARTICLE_ACCELERATION  (0.0f, -5.0f, 0.0f);
const float     PARTICLE_SIZE      = 3.0f;//5.0f;
const float     SIZE_VARIATION     = 0.3f;//2.0f;
#define FRAND   (((float)rand()-(float)rand())/RAND_MAX)
/***************************** Data structures ******************************/
class CExplosion : public CParticleSystem
{
public:
  CExplosion(int maxParticles, CVector origin, float spread, GLuint texture);
  void  Update(float elapsedTime);
  void  Render();
  bool  IsDead() { return m_numParticles == 0; }
//protected:
  void    InitializeParticle(int index);
  float   m_spread;
  GLuint  m_texture;     // explosion texture
};
#endif // __EXPLOSION_H_INCLUDED__