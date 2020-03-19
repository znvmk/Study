#include "stdafx.h"
#include "GraphDraw.h"





CGraphDraw::CGraphDraw()
{
	a = b = 5;
	c = 1;


	m_nSelect = 0;

	r = 0;

}


CGraphDraw::~CGraphDraw()
{
}



BEGIN_MESSAGE_MAP(CGraphDraw, CWnd)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()




void CGraphDraw::GLDraw(int select)
{
	m_nSelect = select;

	switch (select)
	{
	case 0:;break;
	
	default:break;
	}
	

	r += 10;if (r>360) r = 0;

	glPushMatrix();
	glPointSize(4);										//点的大小
	glTranslatef(-5, 4, -13);glRotatef(r, 1.0, 1.0, 1.0);	//整体旋转
	glColor3f(1.0f, 0.0f, 0.0f);Point();		//画点
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 4, -13);glRotatef(r, 1.0, 1.0, 1.0); //整体旋转
	glColor3f(0.0f, 1.0f, 0.0f);Line();		//画线
	glPopMatrix();
	glPushMatrix();
	glTranslatef(5, 4, -13);glRotatef(r, 1.0, 1.0, 1.0); //整体旋转
	glColor3f(0.0f, 0.0f, 1.0f);Triangle();	//画面
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5, 0, -13);glRotatef(r, 1.0, 1.0, 1.0); //整体旋转
	glColor3f(1.0f, 1.0f, 0.0f);Square();		//画正方面
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, -13);glRotatef(r, 1.0, 1.0, 1.0); //整体旋转
	glColor3f(0.0f, 1.0f, 1.0f);Esquare();		//画正方体
	glPopMatrix();
	glPushMatrix();
	glTranslatef(5, 0, -13);glRotatef(r, 1.0, 1.0, 1.0); //整体旋转
	glColor3f(1.0f, 0.0f, 1.0f);Park();		//画园
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5, -4, -13);glRotatef(r, 1.0, 1.0, 1.0); //整体旋转
	glColor3f(1.0f, 1.0f, 1.0f);Pillar();		//园柱
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -4, -13);glRotatef(r, 1.0, 1.0, 1.0); //整体旋转
	glColor3f(0.7f, 0.7f, 0.7f);glutSolidCone(1.0f, 2.0f, 10, 10);  	//辅助库物体实面园锥
	glPopMatrix();
	glPushMatrix();
	glTranslatef(5, -4, -13);glRotatef(r, 1.0, 1.0, 1.0); //整体旋转
	glColor3f(0.4f, 0.4f, 0.4f);auxWireTeapot(1);	//辅助库物体线茶壶
	glPopMatrix();



}






void CGraphDraw::Point()//画点
{
	glBegin(GL_POINTS);// 单个顶点
	glVertex3f(0.0f, 1.0f, -1.0f);//a点
	glVertex3f(-1.0f, -1.0f, 0.0f);//b点
	glVertex3f(1.0f, -1.0f, 0.0f);//c点
	glEnd();
}
void CGraphDraw::Line()//画线
{
	glBegin(GL_LINE_LOOP); //闭合折线
	glVertex3f(0.0f, 1.0f, -1.0f);//a点
	glVertex3f(-1.0f, -1.0f, 0.0f);//b点
	glVertex3f(1.0f, -1.0f, 0.0f);//c点
	glEnd();
}
void CGraphDraw::Triangle()//画面
{
	glBegin(GL_POLYGON);//填充凸多边形
	glVertex3f(0.0f, 1.0f, -1.0f);//a点
	glVertex3f(-1.0f, -1.0f, 0.0f);//b点
	glVertex3f(1.0f, -1.0f, 0.0f);//c点
	glEnd();
}
void CGraphDraw::Square()//画正方面
{
	glBegin(GL_POLYGON);//填充凸多边形
	glVertex3f(0.0f, 0.0f, 0.0f);//a点
	glVertex3f(1.0f, 0.0f, 0.0f);//b点
	glVertex3f(1.0f, 0.0f, -1.0f);//c点
	glVertex3f(0.0f, 0.0f, -1.0f);//d点
	glEnd();
}
void CGraphDraw::Esquare()//画正方体
{
	glBegin(GL_QUAD_STRIP);//填充凸多边形
	glVertex3f(0.0f, 0.0f, 0.0f);//a0点
	glVertex3f(0.0f, 1.0f, 0.0f);//a1点
	glVertex3f(1.0f, 0.0f, 0.0f);//b0点
	glVertex3f(1.0f, 1.0f, 0.0f);//b1点
	glVertex3f(1.0f, 0.0f, -1.0f);//c0点
	glVertex3f(1.0f, 1.0f, -1.0f);//c1点
	glVertex3f(0.0f, 0.0f, -1.0f);//d0点
	glVertex3f(0.0f, 1.0f, -1.0f);//d1点
	glVertex3f(0.0f, 0.0f, 0.0f);//a0点
	glVertex3f(0.0f, 1.0f, 0.0f);//a1点
	glEnd();
	//现在这个正方体还缺上下两个面。应该补上。
	glBegin(GL_POLYGON);//填充凸多边形
	glVertex3f(0.0f, 0.0f, 0.0f);//a0点
	glVertex3f(1.0f, 0.0f, 0.0f);//b0点
	glVertex3f(1.0f, 0.0f, -1.0f);//c0点
	glVertex3f(0.0f, 0.0f, -1.0f);//d0点
	glVertex3f(0.0f, 1.0f, 0.0f);//a1点
	glVertex3f(1.0f, 1.0f, 0.0f);//b1点
	glVertex3f(1.0f, 1.0f, -1.0f);//c1点
	glVertex3f(0.0f, 1.0f, -1.0f);//d1点
	glEnd();
}
void CGraphDraw::Park()//画园
{
	glBegin(GL_TRIANGLE_FAN);//扇形连续填充三角形串
	glVertex3f(0, 0, 0.0f);
	for (int i = 0;i <= 390;i += 30)
	{
		float p = (float)(i*3.14 / 180);
		glVertex3f((float)sin(p), (float)cos(p), 0.0f);// 园轨迹
	}
	glEnd();
}
void CGraphDraw::Pillar() //园柱
{
	glBegin(GL_QUAD_STRIP);// 连续填充四边形串
	for (int i = 0;i <= 390;i += 30)
	{
		float p = (float)(i*3.14 / 180);
		glVertex3f((float)sin(p) / 2, (float)cos(p) / 2, 1.0f);// 前园 
		glVertex3f((float)sin(p) / 2, (float)cos(p) / 2, 0.0f);// 后园 
	}
	glEnd();
}