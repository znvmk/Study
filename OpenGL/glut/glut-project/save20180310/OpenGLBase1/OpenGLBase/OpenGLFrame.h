#pragma once
//#include "afxwin.h"
#include"stdafx.h"


#define ABS(x) ((x)<0?-(x):(x)>0?(x):0)

#include"GraphDraw.h"





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
protected:

	int a, b, c;

	CGraphDraw m_gd;


	/*光源*/
	/*设置环境光，漫反射光，聚光指数，光源位置*/
	GLfloat m_lightAmb[4], m_lightDif[4], m_lightSpe[4], m_lightPos[4];

	/*材质*/
	GLfloat m_materialAmb[4], m_materialDif[4], m_materialSpe[4], m_materialPos[4], m_materialShininess[4];
	BOOL m_bMatrial;

	GLubyte image[64][64][3];

	
	
	/*当前窗口大小*/
	GLint m_iWindowWidth;
	GLint m_iWindowHeight;


	

/*操作：初始化*/
protected:
	/*初始化光源参数*/
	void InitLightParameter();

	/*初始化材质参数*/
	void InitMatrialParameter();

	/*创建光源*/
	void CreateLights();

	/*创建材质*/
	void CreateMaterial();

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


	
};

