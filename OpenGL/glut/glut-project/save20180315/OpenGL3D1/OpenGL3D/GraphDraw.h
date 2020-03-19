#pragma once
#include "stdafx.h"
#include"TGAWR.h"






//enum { Cube };

/************************************************************************************************/
/*                                                                                              */
/*窗口大小在CMainFrame类中#初始化：cs.cx,cs.cy***************************************************/
/*                                                                                              */
/***************************************OpenGL初始化*********************************************/
/*                                                                                              */
/*GLInit()初始化在view类Init()初始化函数中被调用，用于初始化绘图窗口*****************************/
/*GLSize()初始化在view类Size()初始化函数中被调用，用于初始化GL绘图窗口视点大小*******************/
/*GLDraw()初始化在view类OnDraw()函数中被调用，GLDraw()调用DrawScene()初始化绘图窗口**************/
/*GLDestroy()初始化在view类OnDestroy()函数中被调用，用来销毁绘图窗口*****************************/
/*                                                                                              */
/************************************************************************************************/




class CGraphDraw :
	public CWnd
{
public:
	CGraphDraw();
	~CGraphDraw();







	/*特性*/
protected:

	int a, b, c;


	/*特性*/
public:
	int m_nSelect;
	double r;

	/*当前窗口大小*/
	GLint m_iWindowWidth;
	GLint m_iWindowHeight;

	

	


	/*特性*/
public:

	UINT g_cactus[16];	//贴图
	GLUquadricObj *g_text;
	void Box(float x, float y, float z);
	void picter(float x, float y, float z);//组合图形
	void airplane(float x, float y, float z);//组合飞机
	void light0(float x, float y, float z, float a);//光
	bool LoadT8(char *filename, GLuint &texture);//调8位贴图

	/*操作：初始化*/
protected:
	
	/*操作*/
public:
	

	CTGAWR m_tgawr;

	TextureImage texture[1];
	GLfloat xRot, yRot, zRot;

	int numtest;

	/*操作*/
public:

	


	void TextureDraw();
	void Textureaa();








	






public:


public:
	/*绘画选择*/
	void GLDraw(int select);

	

	
	/*生成的消息映射函数*/
public:
	DECLARE_MESSAGE_MAP()



};

