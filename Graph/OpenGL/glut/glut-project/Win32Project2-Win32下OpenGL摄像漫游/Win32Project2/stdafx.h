// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once


//#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 

//#include <afxwin.h>

#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO:  在此处引用程序需要的其他头文件

#include <mmsystem.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//OpenGL头文件


#include <gl/glew.h>      // 包含最新的gl.h,glu.h库  
#include <gl/glut.h>      // 包含OpenGL实用库


#include <gl\gl.h>		// OpenGL32库的头文件
#include <gl\glu.h>		// GLu32库的头文件
#include <gl\glaux.h>	// GLaux库的头文件

  

//OpenGL链接库

#pragma comment( lib, "winmm.lib")
#pragma comment( lib, "opengl32.lib")	// OpenGL32连接库
#pragma comment( lib, "glu32.lib")		// GLu32连接库
#pragma comment( lib, "glaux.lib")		// GLaux连接库

#define FRAND   (((float)rand()-(float)rand())/RAND_MAX)
//#define MAP_W       16.0f       // size of map along x-axis 32 
//#define MAP_SCALE   16.0f     // the scale of the terrain map24
#define MAP		40//	MAP_W*MAP_SCALE/2
#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
