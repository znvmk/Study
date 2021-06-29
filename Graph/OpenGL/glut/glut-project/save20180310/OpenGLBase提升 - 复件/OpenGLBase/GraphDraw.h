#pragma once
//#include "afxwin.h"
#include"stdafx.h"

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

	CDib* m_pDib;


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







public:


public:
	/*绘画选择*/
	void GLDraw(int select);

	

	
	/*生成的消息映射函数*/
public:
	DECLARE_MESSAGE_MAP()



};

