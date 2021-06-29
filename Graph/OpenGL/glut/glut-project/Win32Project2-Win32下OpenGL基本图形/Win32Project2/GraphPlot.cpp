#include"stdafx.h"
#include "GraphPlot.h"



CGraphPlot::CGraphPlot()
{
	r = 3;
}


CGraphPlot::~CGraphPlot()
{
}

///////////////////////////////////////////////////////////////
void CGraphPlot::Point()//画点
{
	glBegin(GL_POINTS);// 单个顶点
	glVertex3f(0.0f, 1.0f, -1.0f);//a点
	glVertex3f(-1.0f, -1.0f, 0.0f);//b点
	glVertex3f(1.0f, -1.0f, 0.0f);//c点
	glEnd();
}
void CGraphPlot::Line()//画线
{
	glBegin(GL_LINE_LOOP); //闭合折线
	glVertex3f(0.0f, 1.0f, -1.0f);//a点
	glVertex3f(-1.0f, -1.0f, 0.0f);//b点
	glVertex3f(1.0f, -1.0f, 0.0f);//c点
	glEnd();
}
void CGraphPlot::Triangle()//画面
{
	glBegin(GL_POLYGON);//填充凸多边形
	glVertex3f(0.0f, 1.0f, -1.0f);//a点
	glVertex3f(-1.0f, -1.0f, 0.0f);//b点
	glVertex3f(1.0f, -1.0f, 0.0f);//c点
	glEnd();
}
void CGraphPlot::Square()//画正方面
{
	glBegin(GL_POLYGON);//填充凸多边形
	glVertex3f(0.0f, 0.0f, 0.0f);//a点
	glVertex3f(1.0f, 0.0f, 0.0f);//b点
	glVertex3f(1.0f, 0.0f, -1.0f);//c点
	glVertex3f(0.0f, 0.0f, -1.0f);//d点
	glEnd();
}
void CGraphPlot::Esquare()//画正方体
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
void CGraphPlot::Park()//画园
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
void CGraphPlot::Pillar() //园柱
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
void CGraphPlot::Draw()
{
	
}