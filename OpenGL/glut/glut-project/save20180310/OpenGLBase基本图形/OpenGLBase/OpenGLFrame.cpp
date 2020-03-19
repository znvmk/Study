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


BOOL COpenGLFrame::bSetupPixelFormat(CClientDC* m_pDC)
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,/*双缓冲*/
		PFD_TYPE_RGBA,
		24,
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,0,0,0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0,
	};
	int pixelformat;
	if ((pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0)
	{
		AfxMessageBox(_T("ChoosePixFormat failed!"));
		return FALSE;
	}
	if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		AfxMessageBox(_T("SetPixelFormat failed!"));
		return FALSE;
	}
	return TRUE;
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


		glViewport(0, 0, cx, cy);				// 设置OpenGL视口大小。	
		glMatrixMode(GL_PROJECTION);			// 设置当前矩阵为投影矩阵。
		glLoadIdentity();						// 重置当前指定的矩阵为单位矩阵
		gluPerspective							// 设置透视图
		(54.0f,									// 透视角设置为 45 度
			(GLfloat)cx / (GLfloat)cy,			// 窗口的宽与高比
			0.1f,								// 视野透视深度:近点1.0f
			3000.0f								// 视野透视深度:始点0.1f远点1000.0f
		);
		// 这和照象机很类似，第一个参数设置镜头广角度，第二个参数是长宽比，后面是远近剪切。
		glMatrixMode(GL_MODELVIEW);				// 设置当前矩阵为模型视图矩阵
		glLoadIdentity();						// 重置当前指定的矩阵为单位矩阵

		//glFrustum(-1.0, 1.0, -1.0, 1.0, 0.0, 7.0);



		glFrustum(-1.0, 1.0, -1.0, 1.0, 3.0, 7.0);

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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glColor3f(1.0f, 0.0f, 0.0f);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -4.5f);


	glFlush();										 // 更新窗口
	SwapBuffers(hDC);								 // 切换缓冲区
   
	
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

