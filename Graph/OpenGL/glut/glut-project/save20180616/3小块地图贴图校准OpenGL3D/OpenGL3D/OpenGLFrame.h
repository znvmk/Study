#pragma once
#include"stdafx.h"
#include"GraphDraw.h"
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




class COpenGLFrame :
	public CWnd
{
public:
	COpenGLFrame();
	~COpenGLFrame();


	

	/*特性*/
protected:

	

	CGraphDraw m_gd;

	/*当前窗口大小*/
	GLint m_iWindowWidth;
	GLint m_iWindowHeight;

	HDC		hDC;		// GDI设备描述表
	HGLRC	hRC;		// 永久着色描述表
	/*特性*/
protected:
	
	
	
	


	/*特性*/
public:
	/*设置窗口初始大小*/
	int m_WindowWidth , m_WindowHeight;

	/*初始位置*/
	GLfloat m_fAngelX, m_fAngelY , m_fAngelZ;
	/*初始角度*/
	GLfloat m_fPositionX, m_fPositionY , m_fPositionZ;

	/*旋转幅度*/
	GLfloat m_fRevolveAngleStep;
	/*平移步距*/
	GLfloat m_fTranslationStep;


	int m_nSelect;



	/*特性*/
public:
	float a, b, c;
	bool m_keyleft, m_keyright, m_keydown, m_keyup, m_keyshift, m_keypageup, m_keypagedown , m_lbuttondown , m_rbuttondown , m_mousemove;
	int m_nViewSelect;

/*操作：初始化*/
protected:
	

	/*初始化画布*/
	void DrawScene();


	/*操作*/
public:
	BOOL bSetupPixelFormat(CClientDC* m_pDC);

	/*初始化在view类初始化函数中被调用*/
	void GLInit(CClientDC* m_pDC);

	void GLDestroy(CClientDC* m_pDC);

	/*视口变换*/
	void GLSize(UINT nType , int cx , int cy , CRect m_oldRect);



	
/*操作*/
protected:

	
	

public:
	

public:
	/*绘画选择*/
	void GLDraw(int select);

	/*绘画测试*/
	void GLDrawTest();

	void LButtonDown(UINT nFlags , CPoint point);


	/*平移变换*/
	/*前：front ,后：back , 左：left , 右：right*/
	/*方向：direction：前：0 , 后：1 ,左：2 ,右：3*/
	void PfmTranslate(int translation_direction);


	/*旋转变换*/
	/*纬度：latitude,经度：longitude,顺时针：clockwise,逆时针：anticlockwise*/
	/*角度方向：angel_direction：水平顺时针：0，水平逆时针：1，垂直顺时针：2，垂直逆时针：3*/
	void PfmRotate(int revolve_direction);

/*生成的消息映射函数*/
public:
	DECLARE_MESSAGE_MAP()



	/*操作*/
public:


	void MessageTransfer();
	
};

