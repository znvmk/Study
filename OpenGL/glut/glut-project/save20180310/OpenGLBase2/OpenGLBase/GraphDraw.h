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

	GLfloat	r;       //飞机盘旋角度
	float  gao = 1.8f;
	CString	test;    //场景信息



	/*操作*/
public:

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
	UINT		g_cactus[16];	                    //贴图
	BITMAPINFOHEADER  g_bit;                        //
	unsigned char    *g_imageData;                  //
	void		CreateSkyBox(int a, int wi, int he, int le);//显示天
	void		texture(UINT textur);				//设置贴图滤波
	void		light0();                           // 环境光
													//D、
	void		picter(float x, float y, float z);    //组合图形
	bool		LoadT8(char *filename, GLuint &texture); //调8位贴图
	void		LoadT16(char *filename, GLuint &texture);//调16位帖图
	unsigned char* LoadBit(char *filename, BITMAPINFOHEADER *bitmap);
	//E、树
	void		ShowTree(float x, float z, float h, float s, int cactus);//树
	void		ShowTree0(float x, float z, float h, float s, int cactus);//普通平面树













public:


public:
	/*绘画选择*/
	void GLDraw(int select);




	/*生成的消息映射函数*/
public:
	DECLARE_MESSAGE_MAP()



};

