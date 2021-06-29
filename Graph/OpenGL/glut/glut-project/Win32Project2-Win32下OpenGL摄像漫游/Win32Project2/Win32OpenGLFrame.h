#pragma once
#include"stdafx.h"

#include"GraphPlot.h"






HGLRC   hRC = NULL;       // 窗口着色描述表句柄  
HDC hDC = NULL;           // OpenGL渲染描述表句柄  
HWND    hWnd = NULL;  // 保存我们的窗口句柄  
HINSTANCE   hInstance;  // 保存程序的实例  
bool    keys[256];          // 保存键盘按键的数组  
bool    active = TRUE;        // 窗口的活动标志，缺省为TRUE  
bool    fullscreen = TRUE;        // 全屏标志缺省，缺省设定成全屏模式 

								  


				 //定义全局函数  
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);   // WndProc消息循环函数的定义  
BOOL CreateGLWindow(int width, int height, int bits, bool fullscreenflag);  //创建窗口函数定义  
GLvoid ReSizeGLScene(GLsizei width, GLsizei height);    // 重置OpenGL窗口大小函数定义  
int InitGL(GLvoid);     // 对OpenGL进行初始化函数  
int DrawGLScene(GLvoid);    //绘图函数  
							/**********************************************************
							*GLvoid KillGLWindow(GLvoid)
							*功能：销毁窗口
							*参数：无
							*返回值：无
							************************************************************/
GLvoid KillGLWindow(GLvoid);        // 正常销毁窗口函数  



////////////////////////////////////////////////////////////////////////////////////////
				
float	r;       //盘旋角度

CGraphPlot* m_gp;//绘图操作类

				




