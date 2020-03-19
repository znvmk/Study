/****************************************************************************
 Particles.h  粒子，爆炸
/********************************* Includes *********************************/
#include "stdafx.h"
#include "explosion.h"
//*****************************************************************************/
CExplosion::CExplosion(int numParticles, CVector origin, float spread, GLuint texture)
  : m_texture(texture), m_spread(spread), CParticleSystem(numParticles, origin)
{ srand(timeGetTime());
  CParticleSystem::InitializeSystem();
  Emit(numParticles);
} // end CExplosion::Constructor
//*****************************************************************************/
void CExplosion::InitializeParticle(int index)//爆炸初始化
{ // start the particle at the sky at a random location in the emission zone
  m_particleList[index].m_pos.x = m_origin.x + FRAND * m_spread;
  m_particleList[index].m_pos.y = m_origin.y + FRAND * m_spread;
  m_particleList[index].m_pos.z = m_origin.z + FRAND * m_spread;
  // set the size of the particle
  m_particleList[index].m_size = PARTICLE_SIZE + FRAND * SIZE_VARIATION;
  // give the particle a random velocity
  m_particleList[index].m_velocity.x = PARTICLE_VELOCITY.x + FRAND * VELOCITY_VARIATION.x;
  m_particleList[index].m_velocity.y = PARTICLE_VELOCITY.y + FRAND * VELOCITY_VARIATION.y;
  m_particleList[index].m_velocity.z = PARTICLE_VELOCITY.z + FRAND * VELOCITY_VARIATION.z;
  m_particleList[index].m_acceleration = PARTICLE_ACCELERATION;
  m_particleList[index].m_color[0] = 1.0;
  m_particleList[index].m_color[1] = 0.5f + FRAND * 0.5f;///////////
  m_particleList[index].m_color[2] = 0.01f;
  m_particleList[index].m_color[3] = 1.0;
  m_particleList[index].m_energy = 1.5f + FRAND/2.0f;///////////
  m_particleList[index].m_colorDelta[0] = 0.0;
  m_particleList[index].m_colorDelta[1] = -(m_particleList[index].m_color[1]/2.0f)/m_particleList[index].m_energy;
  m_particleList[index].m_colorDelta[2] = 0.0;
  m_particleList[index].m_colorDelta[3] = -1.0f/m_particleList[index].m_energy;
  m_particleList[index].m_sizeDelta = -m_particleList[index].m_size/m_particleList[index].m_energy;
} // end CExplosion::InitializeParticle
/*****************************************************************************
 CExplosion::Update

 Update the existing particles, killing them and creating new ones as needed
*****************************************************************************/
void CExplosion::Update(float elapsedTime)//清除爆炸动画
{ for (int i = 0; i < m_numParticles; )
  { // update the particle's position based on the elapsed time and velocity
    m_particleList[i].m_pos = m_particleList[i].m_pos + m_particleList[i].m_velocity * elapsedTime;
    m_particleList[i].m_velocity = m_particleList[i].m_velocity + m_particleList[i].m_acceleration * elapsedTime;
    m_particleList[i].m_energy -= elapsedTime;
    m_particleList[i].m_size += m_particleList[i].m_sizeDelta * elapsedTime;
    m_particleList[i].m_color[3] += m_particleList[i].m_colorDelta[3] * elapsedTime;
    m_particleList[i].m_color[1] += m_particleList[i].m_colorDelta[1] * elapsedTime;
    // if the particle has hit the ground plane, kill it
    if (m_particleList[i].m_energy <= 0.0)
    { // move the last particle to the current positon, and decrease the count
      m_particleList[i] = m_particleList[--m_numParticles];
    }
    else
    { ++i;
    }
  }
} // end CExplosion::Update()


/*****************************************************************************
 CExplosion::Render()

 Draw the snowflake particles as textured quads
*****************************************************************************/
void CExplosion::Render()//爆炸动画
{ glPushAttrib(GL_CURRENT_BIT);//保存现有颜色属性 glPopAttrib();//恢复前一属性
  float viewMatrix[16];
  glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);
  CVector right(viewMatrix[0], viewMatrix[4], viewMatrix[8]);
  CVector up(viewMatrix[1], viewMatrix[5], viewMatrix[9]);

  glDepthMask(GL_FALSE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, m_texture);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  glBegin(GL_QUADS);
  for (int i = 0; i < m_numParticles; ++i)
  {GLfloat size = m_particleList[i].m_size/3;
   CVector pos =  m_particleList[i].m_pos;
    glColor4fv(m_particleList[i].m_color);
    glTexCoord2f(0.0, 0.0); glVertex3fv((pos + (right + up) * -size).v);
    glTexCoord2f(1.0, 0.0); glVertex3fv((pos + (right - up) * size).v);
    glTexCoord2f(1.0, 1.0); glVertex3fv((pos + (right + up) * size).v);
    glTexCoord2f(0.0, 1.0); glVertex3fv((pos + (up - right) * size).v);
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
  glDepthMask(GL_TRUE);
  glPopAttrib();//恢复前一属性
} // end CExplosion::Update

