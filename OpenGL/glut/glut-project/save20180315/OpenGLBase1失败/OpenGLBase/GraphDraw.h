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

	bool m_keydown, m_keyup, m_keyshift, m_keypageup, m_keypagedown;

	int m_nSelect;
	double r;

	/*当前窗口大小*/
	GLint m_iWindowWidth;
	GLint m_iWindowHeight;

	

	


	/*特性*/
public:

	UINT g_cactus[16];	//贴图
	GLUquadricObj *g_text;

	CTGAWR m_tgawr;
	float  gao = 1.8f;

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
	BOOL		DisplayScene();	                    //摄像漫游
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



};

