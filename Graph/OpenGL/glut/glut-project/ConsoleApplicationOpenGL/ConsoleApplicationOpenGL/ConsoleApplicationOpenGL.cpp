// ConsoleApplicationOpenGL.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <GL/glut.h>  





void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(-1.5f, -1.9f, 1.0f, 1.9f);
	glFlush();
}




void DrawPoints()
{
	GLfloat fpointSize[2];
	glGetFloatv(GL_POINT_SIZE_RANGE, fpointSize);
	glPointSize(fpointSize[1] / 2.0f);


	glBegin(GL_POINT);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(-0.8f, 0.7f);
	glVertex2f(0.6f, -0.3f);
	glVertex2f(-0.4f, 0.1f);
	glVertex2f(0.2f, -0.9f);
	glEnd();
}




void DrawLines()
{
	GLfloat fLineWidth[2];
	glGetFloatv(GL_LINE_WIDTH_RANGE, fLineWidth);
	glLineWidth(fLineWidth[1] / 2.0f);


	glBegin(GL_LINES);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(-0.8f, 0.7f);
	glVertex2f(0.6f, -0.3f);
	glVertex2f(-0.4f, 0.1f);
	glVertex2f(0.2f, -0.9f);
	glEnd();
}






int main()
{
	//glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);


	glutCreateWindow("第一个OpenGL程序");
	glutDisplayFunc(&myDisplay);
	DrawPoints();
	DrawLines();
	glutMainLoop();
	


	
    return 0;
}




























