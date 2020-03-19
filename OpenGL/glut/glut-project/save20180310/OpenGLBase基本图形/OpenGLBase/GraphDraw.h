#pragma once
//#include "stdafx.h"







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
	int r;

	/*当前窗口大小*/
	GLint m_iWindowWidth;
	GLint m_iWindowHeight;

	

	


	/*特性*/
public:

	void	Point();	//画点
	void	Line();		//画线
	void	Triangle();	//画面
	void	Square();	//画正方面
	void	Esquare();	//画正方体
	void	Park();		//画园
	void	Pillar();	//园柱

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

