#pragma once
//#include "afxwin.h"
#include"stdafx.h"




/**/





#define ABS(x) ((x)<0?-(x):(x)>0?(x):0)





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
public:





	int m_nSelect;


	/*特性*/
protected:

	int a, b, c;



	GLubyte image[64][64][3];




	/*特性*/
public:

	/*Mip贴图*//*Mip自动贴图*/
	GLint m_iWindowWidth;
	GLint m_iWindowHeight;


	/*操作：初始化*/
protected:



	/*操作*/
public:





	/*操作*/
public:















public:


public:
	/*绘画选择*/
	void GLDraw(int select);




	/*生成的消息映射函数*/
public:
	DECLARE_MESSAGE_MAP()



};

