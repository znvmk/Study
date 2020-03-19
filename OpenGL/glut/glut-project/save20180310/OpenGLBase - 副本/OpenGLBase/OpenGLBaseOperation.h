#pragma once
#include "afxwin.h"

/*OpenGL头文件*/
#include <GL\gl.h>  
#include <GL\glu.h>
#include <GL\glut.h>
#include <GL\glaux.h>



/**/


#include "Dib.h"


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




class COpenGLBaseOperation :
	public CWnd
{
public:
	COpenGLBaseOperation();
	~COpenGLBaseOperation();


	

	/*特性*/
public:
	GLfloat m_fAngleY , m_fAngleX , m_fAngleZ;

	/*设置窗口初始大小*/
	int m_WindowWidth , m_WindowHeight;
	int m_nSelect;

	/*操作*/
public:
	BOOL bSetupPixelFormat(CClientDC* m_pDC);

	/*初始化在view类初始化函数中被调用*/
	void GLInit(CClientDC* m_pDC);

	void GLDestroy(CClientDC* m_pDC);

	/*视口变换*/
	void GLSize(UINT nType , int cx , int cy , CRect m_oldRect);




  /*特性*/
protected:

	int a, b, c;

	/*光源*/
	/*设置环境光，漫反射光，聚光指数，光源位置*/
	GLfloat m_lightAmb[4],m_lightDif[4], m_lightSpe[4], m_lightPos[4];

	/*材质*/
	GLfloat m_materialAmb[4], m_materialDif[4], m_materialSpe[4], m_materialPos[4], m_materialShininess[4];
	BOOL m_bMatrial;

	GLubyte image[64][64][3];

	CDib* m_pDib;
	
	/*Mip贴图*//*Mip自动贴图*/
	GLint m_iWindowWidth;
	GLint m_iWindowHeight;

	/*交互技术*/
	/*拾取物体*/
	GLint BackColor[2][2] = { 0 };

	

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
protected:
	void DrawPoints();

	void DrawLines();

	void DrawTraingles();

	void DrawTraingleStrip();

	void DrawTraingleFun();

	/*四边形*/
	void DrawQuadrilateral();

	/*四边形片*/
	void DrawQuadrilateralStrip();

	/*凹多边形，边的可见性*/
	/*glEdgeFlag()函数用来说明边的可见性，TRUE 可见，FALSE 不可见*/
	void DrawNonConvex();

	/*由面创建三维图形*/
	/*立方体*/
	void DrawCube();

	void DrawCube(GLdouble GLdLength);

	/*平移变换*/
	void PfmTranslate();


	/*旋转变换*/
	void PfmRotate();

	/*缩放变换*/
	void PfmScale();

	/*剪切变换*/
	void PfmClip();

	/*集成*/
	void PfmAssemble();

	/*绘制卡车平面模型*/
	/*车厢*/
	void Quadrangle(GLdouble dQuadWidth, GLdouble dQuadHeight);
	/*轮子*/
	void Wheel(GLdouble dWheelRadius);
	/*卡车*/
	void PfmMatrixStack();

	/*显示列表*/
	/*管理显示列表*/
	/*圆环*/
	void Trous();

	/*画一个球*/
	void DrawSphere();

	/*平滑盒子*/
	void DrawSmoothCube();


	/*读取图像*/
	void mImage();

	/*纹理贴图*/
	void TexturePlane();

	/*位图贴图*/
	void BitmapTexture();
	
	/*纹理坐标自动生成*/
	void TexGenerate();

	/*Mip贴图*/
	void Mipmapping();

	/*Mip自动贴图*/
	void AutoMipmapping();

	/*融合四边形*/
	void BlendQuads();

	

	/*画一个球*/
	GLint Sphere(GLdouble radius);
	/*透明玻璃*/
	void BlendObjects();

	/*绘制二次曲面*/
	void DrawQuadrics();

	/*Berzier曲线*/
	/*绘制一条拟正弦曲线*/
	void DrawBezierCurve();
	void EvenBezierCurve();
	void DrawBezier();


	/*无法显示*/
	/*NURBS曲线*/
	/*绘制一条NURBS曲线*/
	void DrawNurbsCurve();

	/*Bezier曲面*/
	/*绘制网格曲面*/
	void BzrSufacMesh();

	/*Bezier曲面*/
	/*绘制网格曲面填充*/
	void BzrSufacMeshFill();

	/*无法显示*/
	/*Bezier曲面*/
	/*将位图贴到曲面上*/
	void BzrSufacTex();

	/*Nurbs曲面*/
	/*绘制网格曲面*/
	void NurbsSurface();

	/*意外中断*/
	/*Nurbs曲面剪切*/
	void NurbsSurfaceTrim();

	/*高级制作技术*/
	/*掩膜*/
	void StencilMask();
	/*高级剪切*/
	void StencilClip();




	/*交互技术*/
	/*拾取物体*/
	void CreateSphere();
	void Cicle(GLfloat dRadius , GLfloat fLine , GLfloat n);
	void DrawNonSelect();
	void DrawNameObjects();
	void WhatHits(GLint hits , GLuint* buffer);


public:
	

public:
	/*绘画选择*/
	void GLDraw(int select);

	/*绘画测试*/
	void GLDrawTest();

	void LButtonDown(UINT nFlags , CPoint point);

/*生成的消息映射函数*/
public:
	DECLARE_MESSAGE_MAP()


	
};

