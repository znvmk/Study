#include "stdafx.h"
#include "OpenGLFrame.h"


COpenGLFrame::COpenGLFrame()
{
	a = b = 5;
	c = 1;

	m_WindowWidth = 500;
	m_WindowHeight = 500;

	m_fAngelX = 0.0f;
	m_fAngelY = 0.0f;
	m_fAngelZ = 0.0f;

	m_fPositionX = 0.0f;
	m_fPositionY = 0.0f;
	m_fPositionZ = 0.0f;



	m_nSelect = 0;



	InitLightParameter();
	InitMatrialParameter();



	

	glReadPixels(0, 0, 64, 64, GL_RGB, GL_UNSIGNED_BYTE, image);

	m_iWindowWidth=m_WindowWidth;
	m_iWindowHeight=m_WindowHeight;


	m_fRevolveAngleStep=10.0f;
	m_fTranslationStep = 0.1f;

	
}


COpenGLFrame::~COpenGLFrame()
{
}



BEGIN_MESSAGE_MAP(COpenGLFrame, CWnd)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


BOOL COpenGLFrame::bSetupPixelFormat(CClientDC* m_pDC)//检测安装OpenGL
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),// pfd结构的大小
		1,                                          // 版本号 
		PFD_DRAW_TO_WINDOW |// 支持在窗口中绘图
		PFD_SUPPORT_OPENGL | // 支持 OpenGL
		PFD_DOUBLEBUFFER,// 双缓存模式
		PFD_TYPE_RGBA,// RGBA 颜色模式
		24, // 24 位颜色深度
		0,0,0,0,0,0,// 忽略颜色位 
		0,// 没有非透明度缓存
		0,                                // 忽略移位位 
		0,                                // 无累加缓存 
		0, 0, 0, 0,                       // 忽略累加位 
		32,                               // 32 位深度缓存     
		0,                                // 无模板缓存 
		0,                                // 无辅助缓存 
		PFD_MAIN_PLANE,                   // 主层 
		0,                                // 保留 
		0, 0, 0                           // 忽略层,可见性和损毁掩模 
	};

	int pixelformat;// 象素点格式
	if ((pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0)
	{
		AfxMessageBox(_T("没找到合适的显示模式!"));
		return FALSE;
	}
	if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		AfxMessageBox(_T("设置像素储存格式失败!"));
		return FALSE;
	}//设置当前设备的像素点格式


	 //hRC = wglCreateContext(hDC);          //获取渲染描述句柄
	 //wglMakeCurrent(hDC, hRC);             //激活渲染描述句柄
	return TRUE;
}

void COpenGLFrame::InitLightParameter()
{
	m_lightAmb[0] = 1.0f;m_lightAmb[1] = 0.2f;m_lightAmb[2] = 0.2f;m_lightAmb[3] = 1.0f;
	m_lightDif[0] = 1.0f;m_lightDif[1] = 1.0f;m_lightDif[2] = 0.3f;m_lightDif[3] = 1.0f;
	m_lightSpe[0] = 1.0f;m_lightSpe[1] = 1.0f;m_lightSpe[2] = 1.0f;m_lightSpe[3] = 1.0f;
	m_lightPos[0] = 1.0f;m_lightPos[1] = 1.0f;m_lightPos[2] = 1.0f;m_lightPos[3] = 0.0f;
}

void COpenGLFrame::InitMatrialParameter()
{
	m_materialAmb[0] = 1.0f;m_materialAmb[1] = 0.2f;m_materialAmb[2] = 0.2f;m_materialAmb[3] = 1.0f;
	m_materialDif[0] = 1.0f;m_materialDif[1] = 1.0f;m_materialDif[2] = 0.3f;m_materialDif[3] = 1.0f;
	m_materialSpe[0] = 1.0f;m_materialSpe[1] = 1.0f;m_materialSpe[2] = 1.0f;m_materialSpe[3] = 1.0f;
	m_materialPos[0] = 1.0f;m_materialPos[1] = 1.0f;m_materialPos[2] = 1.0f;m_materialPos[3] = 0.0f;
	m_materialShininess[0] = 10.0f;m_materialShininess[1] = 10.0f;m_materialShininess[2] = 0.0f;m_materialShininess[3] = 10.0f;
}

void COpenGLFrame::CreateLights()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, m_lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, m_lightDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, m_lightSpe);
	glLightfv(GL_LIGHT0, GL_POSITION, m_lightPos);


	glEnable(GL_LIGHTING);
	/*最多可创建8盏灯*/
	glEnable(GL_LIGHT0);

}

void COpenGLFrame::CreateMaterial()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_materialAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_materialDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_materialSpe);
	glMaterialfv(GL_FRONT, GL_POSITION, m_materialPos);
	glMaterialfv(GL_FRONT, GL_SHININESS, m_materialShininess);

}

void COpenGLFrame::GLInit(CClientDC* m_pDC)
{
	PIXELFORMATDESCRIPTOR pfd;
	int n;
	HGLRC hrc;

	ASSERT(m_pDC != NULL);
	if (!bSetupPixelFormat(m_pDC))return;

	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);
	hrc = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(), hrc);

	//GetClientRect(&m_oldRect);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void COpenGLFrame::GLSize(UINT nType, int cx, int cy, CRect m_oldRect)
{


	// TODO: 在此处添加消息处理程序代码

	m_iWindowWidth = cx;
	m_iWindowHeight = cy;
	m_gd.m_iWindowWidth = m_iWindowWidth;
	m_gd.m_iWindowHeight = m_iWindowHeight;




	if (cy > 0)
	{
		if ((m_oldRect.right > cx) || (m_oldRect.bottom > cy))
			RedrawWindow();
		m_oldRect.right = cx;
		m_oldRect.bottom = cy;

		glViewport(0, 0, cx, cy);			// 设置OpenGL视口大小。	
		glMatrixMode(GL_PROJECTION);			// 设置当前矩阵为投影矩阵。
		glLoadIdentity();						// 重置当前指定的矩阵为单位矩阵
		gluPerspective							// 设置透视图
		(54.0f,							// 透视角设置为 45 度
			(GLfloat)cx / (GLfloat)cy,	// 窗口的宽与高比
			0.1f,								// 视野透视深度:近点1.0f
			3000.0f							// 视野透视深度:始点0.1f远点1000.0f
		);
		// 这和照象机很类似，第一个参数设置镜头广角度，第二个参数是长宽比，后面是远近剪切。
		glMatrixMode(GL_MODELVIEW);				// 设置当前矩阵为模型视图矩阵
		glLoadIdentity();						// 重置当前指定的矩阵为单位矩阵




												//glFrustum(-1.0, 1.0, -1.0, 1.0, 0.0, 7.0);

												//glFrustum(-1.0, 1.0, -1.0, 1.0, 3.0, 7.0);

												//glViewport(0, 0, cx, cy);
	}
}

void COpenGLFrame::GLDestroy(CClientDC* m_pDC)
{


	// TODO: 在此处添加消息处理程序代码
	HGLRC hrc;
	hrc = ::wglGetCurrentContext();
	if (hrc)::wglDeleteContext(hrc);
	if (m_pDC)delete m_pDC;

}

void COpenGLFrame::GLDraw(int select)
{
	m_nSelect = select;
	DrawScene();
	glPushMatrix();

	/*坐标变换*/
	glTranslatef(m_fPositionX , m_fPositionY , m_fPositionZ);

	glRotatef(m_fAngelX , 1.0f , 0.0f , 0.0f);
	glRotated(m_fAngelY , 0.0 , 1.0 , 0.0);
	glRotatef(m_fAngelZ , 0.0f , 0.0f , 1.0f);

	//绘制图形
	m_gd.GLDraw(select);
	
	glPopMatrix();
	glDisable(GL_LIGHTING);
	//glDisable(GL_TEXTURE_2D);
	glFinish();

	/*双缓冲*/
	SwapBuffers(wglGetCurrentDC());
}

void COpenGLFrame::DrawScene()
{
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);			 // 设置刷新背景色
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 刷新背景
	glLoadIdentity();								 // 重置当前的模型观察矩阵

													 //	glColor3f(1.0f, 0.0f, 0.0f);


													 //	glMatrixMode(GL_MODELVIEW);
													 //	glLoadIdentity();
													 //	glTranslatef(0.0f, 0.0f, -4.5f);


													 //	CreateLights();
													 //	CreateMaterial();

	glFlush();										 // 更新窗口
	//SwapBuffers(hDC);								 // 切换缓冲区
   
	
}

void COpenGLFrame::PfmTranslate(int translation_direction)
{
	switch (translation_direction)
	{
	case 0:m_fPositionX += m_fTranslationStep;break;
	case 1:m_fPositionX -= m_fTranslationStep;break;
	case 2:m_fPositionY += m_fTranslationStep;break;
	case 3:m_fPositionY -= m_fTranslationStep;break;
	case 4:m_fPositionZ += m_fTranslationStep;break;
	case 5:m_fPositionZ -= m_fTranslationStep;break;
	default:break;
	}

	glTranslatef(m_fPositionX, m_fPositionY, m_fPositionZ);




}

void COpenGLFrame::PfmRotate(int revolve_direction)
{
	switch (revolve_direction)
	{
	case 0:m_fAngelX += m_fRevolveAngleStep;break;
	case 1:m_fAngelX -= m_fRevolveAngleStep;break;
	case 2:m_fAngelY += m_fRevolveAngleStep;break;
	case 3:m_fAngelY -= m_fRevolveAngleStep;break;
	case 4:m_fAngelZ += m_fRevolveAngleStep;break;
	case 5:m_fAngelZ -= m_fRevolveAngleStep;break;
	default:break;
	}

	glRotatef(m_fAngelX, 1.0f, 0.0f, 0.0f);
	glRotated(m_fAngelY, 0.0, 1.0, 0.0);
	glRotatef(m_fAngelZ, 0.0f, 0.0f, 1.0f);


}

void COpenGLFrame::GLDrawTest()
{
	/*初始化画布*/
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -4.5f);


	glPushMatrix();

	/*坐标变换*/
	//*

	//*/

	//m_gd.BitmapTexture();

	glPopMatrix();

	//glDisable(GL_LIGHTING);

	glFinish();

	/*双缓冲*/
	SwapBuffers(wglGetCurrentDC());
}


void COpenGLFrame::LButtonDown(UINT nFlags , CPoint point)
{
	if (m_nSelect != 34)return;

	
}

