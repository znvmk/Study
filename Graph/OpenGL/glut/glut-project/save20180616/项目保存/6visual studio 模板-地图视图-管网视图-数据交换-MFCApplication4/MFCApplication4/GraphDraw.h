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

	


	/*特性*/
public:


	float a, b, c;

	bool m_keyleft,m_keyright,m_keydown, m_keyup, m_keyshift, m_keypageup, m_keypagedown , m_lbuttondown , m_rbuttondown , m_mousemove,  m_keyP;

	int m_nViewSelect;

	int m_nSelect;
	double r;

	/*当前窗口大小*/
	GLint m_iWindowWidth;
	GLint m_iWindowHeight;

	

	/*特性*//*2D视图*/
public:
	GLfloat x2D , y2D , z2D;
	
	/*操作*//*2D视图*/
public:
	void ViewSelect2D();
	BOOL		DisplayScene2D();



	/*特性*//*3D视图*/
public:

	/*操作*//*3D视图*/
public:
	void ViewSelect3D();

public:

	UINT g_cactus[16];	//贴图
	GLUquadricObj *g_text;

	CTGAWR m_tgawr;
	float  gao ;

	TextureImage texture[16];
	BITMAPINFOHEADER  g_bit;                        //
	unsigned char    *g_imageData;                  //

	int m_BoxSize,m_BoxBottomHeightMax;
	GLfloat m_BoxBottomHeight[100][100] = { 0 };

public:
	//A、地
	float		g_terrain[MAP_W*MAP_W][3];	    //地域数据
	GLuint		g_index[MAP_W*MAP_W * 2];	    //顶点数组
	float		g_texcoord[MAP_W*MAP_W][2];	    //索引数组
	void		InitTerrain(float h);	            //载入地域数组
	void		DrawSand();					        //显示随机山势
	float		GetHeight(float x, float z);        //取当前位置高度
	//B、漫游
	float	    g_eye[3]; 	                        //视点
	float	    g_look[3];	                        //目标点
	float	    rad_xz;		                        //角度
	float	    g_Angle;	                        //方位角
	float	    g_elev;		                        //仰俯角
	BOOL		DisplayScene3D();	                    //摄像漫游
	//C、天、其它
	//UINT		g_cactus[16];	                    //贴图
	
	void		CreateSkyBox(int a, int wi, int he, int le);//显示天
	
	void		light0();                           // 环境光

	GLvoid DrawGround();

	void Box(float x, float y, float z);
	void picter(float x, float y, float z);//组合图形
	void airplane(float x, float y, float z);//组合飞机
	//void light0(float x, float y, float z, float a);//光
	
	void DrawBottom();
	void DrawMap();



	



	/*操作：初始化*/
protected:
	
	/*操作*/
public:
	

	
	GLfloat xRot, yRot, zRot;

	

	/*操作*/
public:
	//载入TGA文件texture贴图测试
	void Textureaa();

	
													
	
	

public:
	/*绘画选择*/
	void GLDraw(int select);

	

	
	/*生成的消息映射函数*/
public:
	DECLARE_MESSAGE_MAP()


	public:

		/*光源*/
		/*设置环境光，漫反射光，聚光指数，光源位置*/
		GLfloat m_lightAmb[4] , m_lightDif[4] , m_lightSpe[4] , m_lightPos[4];

		/*材质*/
		GLfloat m_materialAmb[4] , m_materialDif[4] , m_materialSpe[4] , m_materialPos[4] , m_materialShininess[4];
		BOOL m_bMatrial;


		/*操作：初始化*/
protected:
	/*初始化光源参数*/
	void InitLightParameter();

	/*初始化材质参数*/
	void InitMatrialParameter(int s);

	/*创建光源*/
	void CreateLights();

	/*创建材质*/
	void CreateMaterial();




public:
	/*初始角度*/
	GLfloat m_fAngelX , m_fAngelY , m_fAngelZ;

	/*初始位置*/
	GLfloat m_fPosX , m_fPosY , m_fPosZ;
	int pipleposX[3][10] = { 0 };
	int pipleposZ[3][10] = { 0 };

	int piplenum[3][10] = { { 1,2,3,4,5,6,7,8,9,10 },{ 1,2,3,4,5,6,7,8,9,10 },{ 1,2,3,4,5,6,7,8,9,10 } };
	float piplelength[3][10] = { 10 };
	int piplecolor[3][10] = { { 1,2,3,1,2,3,1,2,3,1 },{ 1,2,3,1,2,3,1,2,3,1 },{ 1,2,3,1,2,3,1,2,3,1 } };
	bool pipledraw[3][10] = { 1 };
	//int piplelayer[3][10] = { 0 };


public:
	//int story , int num , int color;
	void DrawCylinder(GLfloat x , GLfloat y , GLfloat z);
	void DrawPiple(GLfloat x , GLfloat y , GLfloat z , int color);
	void drawaaa();
	void picter1(float x , float y , float z);
	void DrawPipleNet();

};

