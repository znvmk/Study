#pragma once


/*图形绘制类*/
class CGraphPlot
{
public:
	CGraphPlot();
	virtual~CGraphPlot();


public:
	double r;

public:
	//*
	UINT g_cactus[16];	//贴图
	GLUquadricObj *g_text;
	void Box(float x, float y, float z);
	void picter(float x, float y, float z);//组合图形
	void airplane(float x, float y, float z);//组合飞机
	void light0(float x, float y, float z, float a);//光
	bool LoadT8(char *filename, GLuint &texture);//调8位贴图
	//*/

public:
public:
public:
public:
public:


};

