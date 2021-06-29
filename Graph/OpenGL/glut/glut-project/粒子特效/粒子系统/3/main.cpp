#pragma once;
#include "stdafx.h"
#include<iostream>
#include "ParticleSystem.h"

#define GLEW_STATIC


using namespace std;
/** 用来设置粒子的属性值 */
float px, py, pz, vx, vy, vz, ax, ay, az, sizeP, life, fade;
float r, g, b;




CParticleSystem Snow;


/** 载入纹理 */
GLuint  texName[2];
/*
bool LoadTextures()
{
	GLbyte *pBits[2];
	int nWidth, nHeight;
	char a[] = "fasdfa";
	char fileName[] = { "/Users/app05/Desktop/opengl/wall.bmp","/Users/app05/Desktop/opengl/snowball.bmp" };

	for (int i = 0; i<2; i++)
	{
		pBits[i] = gltReadBMPBits(fileName[i], &nWidth, &nHeight);
		if (pBits[i] == NULL)
		{
			printf("bmp load failed");
			exit(-1);
		}

		glGenTextures(1, &texName[i]);

		// 创建纹理对象 
		glBindTexture(GL_TEXTURE_2D, texName[i]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, nWidth, nHeight,
			GL_RGB, GL_UNSIGNED_BYTE, pBits[i]);
	}
	return true;
}
*/







void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'y':
		//gkeys['y'] = true;
		break;
	case 'c':
		//++col;
		//if (col >= 12)
		{
		//	col -= 12;
		}
		glutPostRedisplay();
		break;
	case 'l':
		//slowdown -= 0.3;
		glutPostRedisplay();
		break;
	case 'h':
		//slowdown += 0.3;
		glutPostRedisplay();
		break;
	case 'w':
		//Y += 0.3;
		glutPostRedisplay();
		break;
	case 'a':
		//X -= 0.3;
		glutPostRedisplay();
		break;
	case 's':
	   // Y -= 0.3;
		glutPostRedisplay();
		break;
	case 'd':
		//X += 0.3;
		glutPostRedisplay();
		break;
	case 'z':
		//Z -= 0.3;
		glutPostRedisplay();
		break;
	case 'x':
		//Z += 0.3;
		glutPostRedisplay();
		break;
	case 'j':
		//parSys.sp -= 10;
		glutPostRedisplay();
		break;
	case 'k':
		//parSys.sp += 10;
		glutPostRedisplay();
		break;

	default:
		break;
	}
}





/** 绘制地面 */
float angle = 0;
void DrawGround()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -6.0f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	/** 指定纹理 */
	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glColor4ub(255, 255, 255, 255);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f, -1.0f, 2.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-2.5f, -1.0f, -2.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.5f, -1.0f, -2.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(2.5f, -1.0f, 2.5f);
	glEnd();
	glPopMatrix();

	/** 地面转动的角度 */
	angle += 0.02f;
}

/** 初始化雪花粒子 */
bool InitSnow()
{
	for (int i = 0; i < Snow.GetNumOfParticle(); ++i)
	{
		///初始化颜色（白色）
		r = 255;
		g = 255;
		b = 255;
		Snow.SetColor(i, r, g, b);

		///初始化坐标
		px = 0.1f * (rand() % 50) - 2.5f;
		py = 2 + 0.1f * (rand() % 2);
		if ((int)px % 2 == 0)
			pz = rand() % 6;
		else
			px = -rand() % 3;
		Snow.SetPosition(i, px, py, pz);

		///初始化速度
		vx = 0.00001 * (rand() % 100);
		vy = 0.0000002 * (rand() % 28000);
		vz = 0;
		Snow.SetVelocity(i, vx, vy, vz);

		///初始化加速度
		ax = 0;
		ay = 0.000005f;
		az = 0;
		Snow.SetAcceleration(i, ax, ay, az);

		///初始化生命周期
		life = 100;
		Snow.SetLife(i, life);

		///消失速度
		fade = 0.005 * (rand() % 50);
		Snow.SetFade(i, fade);

		///初始化大小
		Snow.SetSize(i, 0.03f);
	}
	return true;
}

/** 更新粒子 */
void UpdateSnow()
{
	/** 更新位置 */
	px += (vx * 5);
	py -= vy;

	/** 更新速度 */
	vy += ay;

	/** 更新生存时间 */
	life -= fade;

	if (px > 3)
		px = -2;

	/** 如果粒子消失或生命结束 */
	if (py <= -1 || life <= 0)
	{
		/** 初始化位置 */
		px = 0.1f * (rand() % 50) - 2.5f;
		py = 2 + 0.1f * (rand() % 2);
		if ((int)px % 2 == 0)
			pz = rand() % 6;
		else
			pz = -rand() % 3;

		/** 初始化速度 */
		vx = (float)(0.00001 * (rand() % 100));
		vy = (float)(0.0000002 * (rand() % 28000));
		vz = 0;

		/** 初始化加速度 */
		ax = 0;
		ay = 0.000005f;
		az = 0;
		life = 100;
		fade = 0.005*(rand() % 50);
	}
}

/** 绘制粒子 */
void DrawParticle()
{
	/** 绑定纹理 */
	glBindTexture(GL_TEXTURE_2D, texName[1]);
	
	for (int i = 0; i<Snow.GetNumOfParticle(); ++i)
	{
		/** 获得粒子的所有属性 */
		Snow.GetAll(i, r, g, b, px, py, pz, vx, vy, vz, ax, ay, az, sizeP, life, fade);
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -6.0f);
		glColor4ub(r, g, b, 255);
		glNormal3f(0.0f, 0.0f, 1.0f);   /**< 定义法线方向 */
										/** 画出粒子 */
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(px - sizeP, py - sizeP, pz);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(px - sizeP, py + sizeP, pz);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(px + sizeP, py + sizeP, pz);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(px + sizeP, py - sizeP, pz);
		glEnd();

		/** 更新粒子属性 */
		UpdateSnow();
		Snow.SetAll(i, r, g, b, px, py, pz, vx, vy, vz, ax, ay, az, sizeP, life, fade);
	}
	glutPostRedisplay();//发送渲染请求

	
}

/////////////////////////////////////////////////////////////////
/** 初始化 */
void init(void)
{
	/** 用户自定义的初始化过程 */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);//指定深度缓冲区的清除值(即将深度缓冲区里的值设置为1)
	glDepthFunc(GL_LEQUAL);//指定用于深度缓冲比较值(即新进像素深度值与原来的1比较，<=则通过，否则丢弃)
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_TEXTURE_2D);             /**< 开启纹理映射 */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);    /**< 设置混合因子获得半透明效果 */
	glEnable(GL_BLEND);                  /**< 启用混和 */

										 /**  载入纹理 */
	//if (!LoadTextures())
	{
		//printf("bmp load failed");
		//exit(-1);
	}

	/** 创建500个粒子 */
	Snow.Create(500);

	/** 初始化粒子 */
	InitSnow();
}

/** 渲染 */
void display(void)
{
	/** 用户自定义的绘制过程 */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	/** 绘制地面 */
	DrawGround();

	/** 绘制粒子 */
	DrawParticle();

	//glFlush(); /**<强制执行所有的OpenGL命令 */
	glutSwapBuffers();
}


void ChangeSize(int width, int height)
{
	glViewport(0, 0, width, height);    /**< 重新设置视口 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1700.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("SnowPraticle");
	init();
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
