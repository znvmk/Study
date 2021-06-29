#pragma once;
#include "stdafx.h"
#include<iostream>
#include "ParticleSystem.h"

#define GLEW_STATIC
//粒子数量:1-10000
int NUM = 1000;

float X, Y, Z;


using namespace std;


CParticleSystem parSys;


void reshape(int w, int h)
{
	if (0 == h)
		h = 1;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 200.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int init()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//really nice perspective calculations
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);

	X = Y = Z = 0.0f;

	return true;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	for (int loop = 0; loop < NUM; ++loop)
	{
		if (parSys.paticle[loop].active)//the particle is alive
		{
			parSys.changePractile(loop);


			glColor4f(parSys.paticle[loop].r,
				parSys.paticle[loop].g,
				parSys.paticle[loop].r,
				//use life as alpha value:
				//as particle dies,it becomes more and more transparent
				parSys.paticle[loop].life);

			//draw particles : use triangle strip instead of quad to speed
			float x, y, z;
			x = parSys.paticle[loop].x+X;
			y = parSys.paticle[loop].y+Y;
			z = parSys.paticle[loop].z-3.0f+Z;

			//粒子大小
			float length = 0.1;
			glBegin(GL_TRIANGLE_STRIP);
			//top right
			glTexCoord2d(1, 1);
			glVertex3f(x + length, y + length, z);
			//top left
			glTexCoord2d(0, 1);
			glVertex3f(x - length, y + length, z);
			//bottom right
			glTexCoord2d(1, 0);
			glVertex3f(x + length, y - length, z);
			//bottom left
			glTexCoord2d(0, 0);
			glVertex3f(x - length, y - length, z);
			glEnd();


			parSys.paticle[loop].life -= parSys.paticle[loop].fade;
		}
	}
	glutSwapBuffers();
}

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
		Y += 0.3;
		glutPostRedisplay();
		break;
	case 'a':
		X -= 0.3;
		glutPostRedisplay();
		break;
	case 's':
	    Y -= 0.3;
		glutPostRedisplay();
		break;
	case 'd':
		X += 0.3;
		glutPostRedisplay();
		break;
	case 'z':
		Z -= 0.3;
		glutPostRedisplay();
		break;
	case 'x':
		Z += 0.3;
		glutPostRedisplay();
		break;
	case 'j':
		parSys.sp -= 10;
		glutPostRedisplay();
		break;
	case 'k':
		parSys.sp += 10;
		glutPostRedisplay();
		break;

	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Particle");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
