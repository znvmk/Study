#include "stdafx.h"
#include<iostream>
#define GLEW_STATIC

using namespace std;

//粒子数量
#define MAX_PARTICLES 10000

typedef struct//structrue for particle:粒子结构体
{
	bool active;//active or not
	float life;//last time
	float fade;//describe the decreasing of life
	float r, g, b;//color
	float x, y, z;//the position
	float xi, yi, zi;//what direction to move
	float xg, yg, zg;//gravity
}particles;

bool rainbow = true;
bool sp, rp;//space button and return button pressed or not?
float slowdown = 2.0f;
float xspeed, yspeed;
float zoom = -40.0f;
bool gkeys[256];

GLuint loop, col, delay, texture[1];

particles paticle[MAX_PARTICLES];

static GLfloat colors[12][3] =     // Rainbow Of Colors 
{
	{ 1.0f,0.5f,0.5f },{ 1.0f,0.75f,0.5f },{ 1.0f,1.0f,0.5f },{ 0.75f,1.0f,0.5f },
{ 0.5f,1.0f,0.5f },{ 0.5f,1.0f,0.75f },{ 0.5f,1.0f,1.0f },{ 0.5f,0.75f,1.0f },
{ 0.5f,0.5f,1.0f },{ 0.75f,0.5f,1.0f },{ 1.0f,0.5f,1.0f },{ 1.0f,0.5f,0.75f }
};


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

	for (loop = 0; loop < MAX_PARTICLES; ++loop)
	{
		paticle[loop].active = true;
		paticle[loop].life = 1.0f;//full life is 1.0f
								  //life decrease rate(a random value add 0.003f : never equals 0)
		paticle[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;
		paticle[loop].r = colors[loop * (12 / MAX_PARTICLES)][0];
		paticle[loop].g = colors[loop * (12 / MAX_PARTICLES)][1];
		paticle[loop].b = colors[loop * (12 / MAX_PARTICLES)][2];

		paticle[loop].xi = float((rand() % 50) - 26.0f) * 10.0f;
		paticle[loop].yi = float((rand() % 50) - 25.0f) * 10.0f;
		paticle[loop].zi = float((rand() % 50) - 25.0f) * 10.0f;

		paticle[loop].xg = 0.0f;
		paticle[loop].yg = -0.8f;
		paticle[loop].zg = 0.8f;
	}
	return true;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	for (loop = 0; loop < MAX_PARTICLES; ++loop)
	{
		if (paticle[loop].active)//the particle is alive
		{
			float x = paticle[loop].x;
			float y = paticle[loop].y;
			//our scene is moved into the screen
			float z = paticle[loop].z + zoom;

			glColor4f(paticle[loop].r,
				paticle[loop].g,
				paticle[loop].r,
				//use life as alpha value:
				//as particle dies,it becomes more and more transparent
				paticle[loop].life);

			//draw particles : use triangle strip instead of quad to speed
			glBegin(GL_TRIANGLE_STRIP);
			//粒子大小
			float length = 0.1;
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

			//Move On The X Axis By X Speed 
			paticle[loop].x += paticle[loop].xi / (slowdown * 1000);
			//Move On The Y Axis By Y Speed 
			paticle[loop].y += paticle[loop].yi / (slowdown * 1000);
			//Move On The Z Axis By Z Speed 
			paticle[loop].z += paticle[loop].zi / (slowdown * 1000);

			//add gravity or resistance : acceleration
			paticle[loop].xi += paticle[loop].xg;
			paticle[loop].yi += paticle[loop].yg;
			paticle[loop].zi += paticle[loop].zg;

			//decrease particles' life
			paticle[loop].life -= paticle[loop].fade;

			//if particle is dead,rejuvenate it
			if (paticle[loop].life < 0.0f)
			{
				paticle[loop].life = 1.0f;//alive again
				paticle[loop].fade = float(rand() % 100) / 1000.0f + 0.003f;

				//reset its position
				paticle[loop].x = 0.0f;
				paticle[loop].y = 0.0f;
				paticle[loop].z = 0.0f;

				//X Axis Speed And Direction 
				paticle[loop].xi = xspeed + float((rand() % 60) - 32.0f);
				// Y Axis Speed And Direction 
				paticle[loop].yi = yspeed + float((rand() % 60) - 30.0f);
				// Z Axis Speed And Direction 
				paticle[loop].zi = float((rand() % 60) - 30.0f);

				paticle[loop].r = colors[col][0];			// Select Red From Color Table
				paticle[loop].g = colors[col][1];			// Select Green From Color Table
				paticle[loop].b = colors[col][2];			// Select Blue From Color Table
			}
		}
	}

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'y':
		gkeys['y'] = true;
		break;
	case 'c':
		++col;
		if (col >= 12)
		{
			col -= 12;
		}
		glutPostRedisplay();
		break;
	case 'l':
		slowdown -= 0.3;
		glutPostRedisplay();
		break;
	case 'h':
		slowdown += 0.3;
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

