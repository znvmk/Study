#include "stdafx.h"
#include "OpenGLBaseOperation.h"


COpenGLBaseOperation::COpenGLBaseOperation()
{
	a = b = 5;
	c = 1;

	m_WindowWidth = 400;
	m_WindowHeight = 435;

	m_nSelect = 0;


	InitLightParameter();
	InitMatrialParameter();

	m_fAngleY = 10.0f;
	m_fAngleX = 1.0f;
	m_fAngleZ = 5.0f;

	glReadPixels(0, 0, 64, 64, GL_RGB, GL_UNSIGNED_BYTE, image);

	m_iWindowWidth=m_WindowWidth;
	m_iWindowHeight=m_WindowHeight;

	/*交互技术*/
	/*拾取物体*/
	
}


COpenGLBaseOperation::~COpenGLBaseOperation()
{
}



BEGIN_MESSAGE_MAP(COpenGLBaseOperation, CWnd)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


BOOL COpenGLBaseOperation::bSetupPixelFormat(CClientDC* m_pDC)
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

void COpenGLBaseOperation::InitLightParameter()
{
	m_lightAmb[0] = 1.0f;m_lightAmb[1] = 0.2f;m_lightAmb[2] = 0.2f;m_lightAmb[3] = 1.0f;
	m_lightDif[0] = 1.0f;m_lightDif[1] = 1.0f;m_lightDif[2] = 0.3f;m_lightDif[3] = 1.0f;
	m_lightSpe[0] = 1.0f;m_lightSpe[1] = 1.0f;m_lightSpe[2] = 1.0f;m_lightSpe[3] = 1.0f;
	m_lightPos[0] = 1.0f;m_lightPos[1] = 1.0f;m_lightPos[2] = 1.0f;m_lightPos[3] = 0.0f;
}

void COpenGLBaseOperation::InitMatrialParameter()
{
	m_materialAmb[0] = 1.0f;m_materialAmb[1] = 0.2f;m_materialAmb[2] = 0.2f;m_materialAmb[3] = 1.0f;
	m_materialDif[0] = 1.0f;m_materialDif[1] = 1.0f;m_materialDif[2] = 0.3f;m_materialDif[3] = 1.0f;
	m_materialSpe[0] = 1.0f;m_materialSpe[1] = 1.0f;m_materialSpe[2] = 1.0f;m_materialSpe[3] = 1.0f;
	m_materialPos[0] = 1.0f;m_materialPos[1] = 1.0f;m_materialPos[2] = 1.0f;m_materialPos[3] = 0.0f;
	m_materialShininess[0] = 10.0f;m_materialShininess[1] = 10.0f;m_materialShininess[2] = 0.0f;m_materialShininess[3] = 10.0f;
}

void COpenGLBaseOperation::CreateLights()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, m_lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, m_lightDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, m_lightSpe);
	glLightfv(GL_LIGHT0, GL_POSITION, m_lightPos);


	glEnable(GL_LIGHTING);
	/*最多可创建8盏灯*/
	glEnable(GL_LIGHT0);

}

void COpenGLBaseOperation::CreateMaterial()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_materialAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_materialDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_materialSpe);
	glMaterialfv(GL_FRONT, GL_POSITION, m_materialPos);
	glMaterialfv(GL_FRONT, GL_SHININESS, m_materialShininess);

}

void COpenGLBaseOperation::GLInit(CClientDC* m_pDC)
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

void COpenGLBaseOperation::GLSize(UINT nType, int cx, int cy, CRect m_oldRect)
{


	// TODO: 在此处添加消息处理程序代码

	m_iWindowWidth = cx;
	m_iWindowHeight = cy;





	if (cy > 0)
	{
		if ((m_oldRect.right > cx) || (m_oldRect.bottom > cy))
			RedrawWindow();
		m_oldRect.right = cx;
		m_oldRect.bottom = cy;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//glFrustum(-1.0, 1.0, -1.0, 1.0, 0.0, 7.0);

		glFrustum(-1.0, 1.0, -1.0, 1.0, 3.0, 7.0);

		glViewport(0, 0, cx, cy);
	}
}

void COpenGLBaseOperation::GLDestroy(CClientDC* m_pDC)
{


	// TODO: 在此处添加消息处理程序代码
	HGLRC hrc;
	hrc = ::wglGetCurrentContext();
	if (hrc)::wglDeleteContext(hrc);
	if (m_pDC)delete m_pDC;

}

void COpenGLBaseOperation::GLDraw(int select)
{
	m_nSelect = select;
	DrawScene();
	glPushMatrix();

	/*坐标变换*/
	glRotatef(m_fAngleX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fAngleY, 0.0f, 1.0f, 0.0f);
	glRotatef(m_fAngleZ, 0.0f, 0.0f, 1.0f);


	switch (select)
	{
	case 0:;break;
	case 1:DrawPoints();break;
	case 2:DrawLines();break;
	case 3:DrawTraingles();break;
	case 4:DrawTraingleStrip();break;
	case 5:DrawTraingleFun();break;
	case 6:DrawQuadrilateral();break;
	case 7:DrawQuadrilateralStrip();break;
	case 8:DrawNonConvex();break;
	case 9:DrawCube();break;
	case 10:DrawCube(0.9);break;
	case 11:PfmTranslate();break;
	case 12:PfmRotate();break;
	case 13:PfmScale();break;
	case 14:PfmClip();break;
	case 15:PfmAssemble();break;
	case 16:PfmMatrixStack();break;
	case 17:Trous();break;
	case 18:DrawSphere();break;
	case 19:DrawSmoothCube();break;
	case 20:mImage();break;
	case 21:TexturePlane();break;
	//case 22:TexGenerate();break;
	case 22:Mipmapping();break;
	case 23:BlendQuads();break;
	case 24:BlendObjects();break;
	case 25:DrawQuadrics();break;
	case 26:AutoMipmapping();break;
	case 27:DrawBezier();break;
	case 28:DrawNurbsCurve();break;
	case 29:BzrSufacMesh();break;
	case 30:BzrSufacMeshFill();break;
	case 31:NurbsSurface();break;
	case 32:StencilMask();break;
	case 33:StencilClip();break;
	case 34:;break;
	default:break;	
	}
	glPopMatrix();
	glDisable(GL_LIGHTING);
	//glDisable(GL_TEXTURE_2D);
	glFinish();

	/*双缓冲*/
	SwapBuffers(wglGetCurrentDC());
}

void COpenGLBaseOperation::DrawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glColor3f(1.0f, 0.0f, 0.0f);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -4.5f);


	CreateLights();
	CreateMaterial();
   
	
}

void COpenGLBaseOperation::DrawPoints()
{
	GLfloat fPointSize[2];
	glGetFloatv(GL_POINT_SIZE_RANGE, fPointSize);
	glPointSize(fPointSize[1] / 2.0f);

	glColor3f(0.0f, 1.0f, 1.0f);

	glBegin(GL_POINTS);
	if (a<0)for (int i = -1;i>a;i--)glVertex2f(i*0.1f, 0.0f);
	for (int i = 0;i<a;i++)glVertex2f(i*0.1f, 0.0f);
	if (b<0)for (int j = -1;j>b;j--)glVertex2f(0.0f, j*0.1f);
	for (int j = 0;j<b;j++)glVertex2f(0.0f, j*0.1f);
	glEnd();
	
}

void COpenGLBaseOperation::DrawLines()
{

	GLfloat fLineWidth[2];
	glGetFloatv(GL_LINE_WIDTH_RANGE, fLineWidth);
	glLineWidth(fLineWidth[1] / 6.0f);

	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_LINES);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.5f, 0.9f);

	glEnd();



	/*
	//改变线型函数
	glEnable(GL_LINE_STIPPLE);

	glLineStipple(1, 0x00FF);
	glBegin(GL_LINES);
	glVertex2f(-0.5f, 0.8f);

	glVertex2f(0.5f, -0.5f);
	glEnd();


	/*
	glLineStipple(1, 0x0F0F);
	glBegin(GL_LINES);
	glVertex2f(-0.8f, a);
	glVertex2f(1.0f, a);
	glEnd();



	glLineStipple(1, 0x0101);
	glBegin(GL_LINES);
	glVertex2f(-0.8f, a);
	glVertex2f(0.8f, a);
	glEnd();


	glLineStipple(1, 0x1C47);
	glBegin(GL_LINES);
	glVertex2f(-0.8f, -0.8f);
	glVertex2f(0.8f, -0.8f);
	glEnd();

	*/


	//glFinish();

}

void COpenGLBaseOperation::DrawTraingles()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.0f);

	glColor3f(1.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5f, 0.4f);
	glVertex2f(-0.6f, -0.5f);
	glVertex2f(0.5f, -0.5f);

	glVertex2f(-0.5f, 0.8f);
	glVertex2f(-0.5f, 0.6f);
	glVertex2f(0.5f, 0.5f);
	glEnd();

}

void  COpenGLBaseOperation::DrawTraingleStrip()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.0f);

	glColor3f(1.0f, 0.0f, 1.0f);

	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(-0.8f, 0.3f);
	glVertex2f(-0.8f, -0.3f);
	glVertex2f(-0.3f, 0.3f);
	glVertex2f(-0.0f, -0.3f);
	glVertex2f(-0.3f, 0.5f);
	glVertex2f(-0.6f, 0.4f);
	glVertex2f(-0.8f, 0.8f);
	glEnd();
}

void  COpenGLBaseOperation::DrawTraingleFun()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(-0.5f, -0.3f);
	glVertex2f(0.3f, -0.0f);
	glVertex2f(0.3f, -0.3f);
	glVertex2f(0.4f, -0.6f);
	glVertex2f(-0.0f, 0.6f);
	glVertex2f(-0.3f, 0.6f);
	glEnd();
}

void COpenGLBaseOperation::DrawQuadrilateral()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.0f);

	glColor3f(1.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS);
	glVertex2f(-0.6f, 0.8f);
	glVertex2f(-0.6f, -0.6f);
	glVertex2f(0.5f, 0.0f);
	glVertex2f(0.6f, 0.5f);
	glEnd();
}

void COpenGLBaseOperation::DrawQuadrilateralStrip()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.0f);

	glColor3f(0.0f, 0.0f, 1.0f);

	glBegin(GL_QUAD_STRIP);
	glVertex2f(-0.8f, 0.3f);
	glVertex2f(-0.7f, 0.6f);
	glVertex2f(-0.6f, 0.1f);
	glVertex2f(-0.3f, 0.6f);
	glVertex2f(-0.1f, -0.2f);
	glVertex2f(0.0f, 0.55f);
	glVertex2f(0.3f, -0.4f);
	glVertex2f(0.5f, 0.6f);
	glVertex2f(0.8f, -0.4f);
	glVertex2f(0.9f, 0.5f);
	glEnd();
}

void COpenGLBaseOperation::DrawNonConvex()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.0f);

	glColor3f(0.5f, 1.0f, 0.0f);

	glBegin(GL_POLYGON);

	glEdgeFlag(TRUE);
	glVertex2f(-0.3f, 0.3f);

	glEdgeFlag(FALSE);
	glVertex2f(-0.1f, -0.1f);

	glEdgeFlag(TRUE);
	glVertex2f(0.0f, -0.1f);
	glVertex2f(0.0f, 0.3f);
	glEnd();

	glBegin(GL_POLYGON);

	glEdgeFlag(TRUE);
	glVertex2f(-0.1f, -0.1f);
	glVertex2f(-0.2f, -0.4f);

	glEdgeFlag(FALSE);
	glVertex2f(-0.0f, -0.4f);
	glVertex2f(0.0f, -0.1f);

	glEnd();

	glBegin(GL_POLYGON);

	glEdgeFlag(FALSE);
	glVertex2f(0.0f, -0.1f);


	glEdgeFlag(TRUE);
	glVertex2f(0.0f, -0.4f);
	glVertex2f(0.4f, -0.4f);
	glVertex2f(0.45f, 0.1f);

	glEnd();
}

void COpenGLBaseOperation::DrawCube()
{
	glColor3f(0.2f, 0.5f, 1.0f);


	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.5f);
	glColor3f(0.5f, 1.0f, 1.0f);


	glPushMatrix();

	/*将盒子绕y轴70度*/
	/*参数：度数，x轴，y轴，z轴*/
	glRotatef(70.0f, 0.0f, 1.0f, 0.0f);

	/*将盒子绕z轴55度*/
	glRotatef(55.0f, 0.0f, 0.0f, 1.0f);

	/*前面*/
	glBegin(GL_POLYGON);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glEnd();

	/*后面*/
	glBegin(GL_POLYGON);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glEnd();

	/*左面*/
	glBegin(GL_POLYGON);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glEnd();

	/*右面*/
	glBegin(GL_POLYGON);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glEnd();

	/*底面*/
	glBegin(GL_POLYGON);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glEnd();

	/*顶面*/
	glBegin(GL_POLYGON);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();

	glPopMatrix();
}

void COpenGLBaseOperation::DrawCube(GLdouble GLdLength)
{
	GLdouble GLdAbsLength;
	GLdAbsLength = ABS(GLdLength);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glLineWidth(1.5f);

	glColor3f(0.2f, 0.5f, 1.0f);

	glBegin(GL_QUAD_STRIP);
	glVertex3d(-GLdAbsLength, GLdAbsLength, GLdAbsLength);
	glVertex3d(-GLdAbsLength, -GLdAbsLength, GLdAbsLength);
	glVertex3d(GLdAbsLength, GLdAbsLength, GLdAbsLength);
	glVertex3d(GLdAbsLength, -GLdAbsLength, GLdAbsLength);

	glVertex3d(GLdAbsLength, GLdAbsLength, -GLdAbsLength);
	glVertex3d(GLdAbsLength, -GLdAbsLength, -GLdAbsLength);

	glVertex3d(-GLdAbsLength, GLdAbsLength, -GLdAbsLength);
	glVertex3d(-GLdAbsLength, -GLdAbsLength, -GLdAbsLength);

	glVertex3d(-GLdAbsLength, GLdAbsLength, GLdAbsLength);
	glVertex3d(-GLdAbsLength, -GLdAbsLength, GLdAbsLength);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3d(-GLdAbsLength, GLdAbsLength, GLdAbsLength);
	glVertex3d(GLdAbsLength, GLdAbsLength, GLdAbsLength);
	glVertex3d(GLdAbsLength, GLdAbsLength, -GLdAbsLength);
	glVertex3d(-GLdAbsLength, GLdAbsLength, -GLdAbsLength);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3d(-GLdAbsLength, -GLdAbsLength, GLdAbsLength);
	glVertex3d(GLdAbsLength, -GLdAbsLength, GLdAbsLength);
	glVertex3d(GLdAbsLength, -GLdAbsLength, -GLdAbsLength);
	glVertex3d(-GLdAbsLength, -GLdAbsLength, -GLdAbsLength);
	glEnd();



}

void COpenGLBaseOperation::PfmTranslate()
{
	glPushMatrix();

	glTranslatef(0.2f, 0.3f, 1.0f);

	glRotatef(60.0f, 0.0f, 1.0f, 0.0f);
	glRotated(10.0, 1.0, 0.0, 0.0);
	glRotatef(15.0f, 0.0f, 0.0f, 1.0f);

	DrawCube(0.5);
	glPopMatrix();
}

void COpenGLBaseOperation::PfmRotate()
{
	glPushMatrix();
	glRotatef(60.0f, 0.0f, 1.0f, 0.0f);
	glRotated(10.0, 1.0, 0.0, 0.0);
	glRotatef(15.0f, 0.0f, 0.0f, 1.0f);

	DrawCube(0.5);
	glPopMatrix();
}

void COpenGLBaseOperation::PfmScale()
{
	
	glPushMatrix();

	glRotatef(60.0f, 0.0f, 1.0f, 0.0f);
	glRotated(10.0, 1.0, 0.0, 0.0);
	glRotatef(15.0f, 0.0f, 0.0f, 1.0f);


	glScalef(1.5f, 1.0f, 1.0f);
	DrawCube(0.5);

	glPopMatrix();
}

void COpenGLBaseOperation::PfmClip()
{
	

	GLdouble dPlaneEquation[4] = { 1.0,1.0,1.0,-1.0 };
	glPushMatrix();

	glRotatef(60.0f, 0.0f, 1.0f, 0.0f);
	glRotated(10.0, 1.0, 0.0, 0.0);
	glRotatef(15.0f, 0.0f, 0.0f, 1.0f);


	glClipPlane(GL_CLIP_PLANE0, dPlaneEquation);
	glEnable(GL_CLIP_PLANE0);
	glRotatef(60.0f, 0.0f, 1.0f, 0.0f);
	glRotated(10.0, 1.0, 0.0, 0.0);
	glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
	DrawCube(0.5);
	glDisable(GL_CLIP_PLANE0);
	glPopMatrix();
}

void COpenGLBaseOperation::PfmAssemble()
{
	glPushMatrix();
	DrawCube(0.3);
	glTranslatef(0.8f, 0.0f, 0.0f);
	DrawCube(0.3);
	glTranslatef(-1.6f, 0.0f, 0.0f);
	DrawCube(0.3);
	glTranslatef(0.8f, 0.8f, 0.0f);
	DrawCube(0.3);
	glPopMatrix();

	glPushMatrix();
	/*向下平移0.8个单位*/
	glTranslatef(0.0f, -0.8f, 0.0f);
	DrawCube(0.3);
	glTranslatef(0.8f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	DrawCube(0.3);
	glTranslatef(0.0f, 0.0f, -1.6f);
	DrawCube(0.3);
	glTranslatef(0.0f, 0.0f, 0.8f);
	DrawCube(0.3);
	glPopMatrix();
}

/*车厢*/
void COpenGLBaseOperation::Quadrangle(GLdouble dQuadWidth, GLdouble dQuadHeight)
{
	GLdouble dWidth, dHeight, dTemp;

	dWidth = ABS(dQuadWidth);
	dHeight = ABS(dQuadHeight);

	if (dWidth < dHeight)
	{
		dTemp = dWidth;
		dWidth = dHeight;
		dHeight = dTemp;
	}

	if (dHeight == 0.0)
	{
		AfxMessageBox(_T("Error:the Length of Quadrangle is 0.0f!"));
		return;
	}

	dWidth = dWidth / 2.0;
	dHeight = dHeight / 2, 0;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.5f);

	glBegin(GL_QUADS);
	glVertex2d(-dWidth, dHeight);
	glVertex2d(-dWidth, -dHeight);
	glVertex2d(dWidth, -dHeight);
	glVertex2d(dWidth, dHeight);
	glEnd();
}

/*轮子*/
void COpenGLBaseOperation::Wheel(GLdouble dWheelRadius)
{
	GLdouble dRadius = ABS(dWheelRadius);
	GLdouble dStep = 0.1;
	GLdouble dTwoPie = 2.0*3.141592653 + dStep;

	glBegin(GL_LINE_STRIP);
	glVertex2d(dRadius, 0.0f);
	for (GLdouble dIndex = dStep ; dIndex <= dTwoPie;dIndex += dStep)
		glVertex2d(dRadius*cos(dIndex), dRadius*sin(dIndex));
	glEnd();
}

/*卡车*/
void COpenGLBaseOperation::PfmMatrixStack()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.5f);
	glColor3f(0.2f, 0.5f, 1.0f);
	
	glPushMatrix(); 
	{
		glTranslatef(0.4f, 0.0f, 0.0f);
	
		/*主货箱*/
		Quadrangle(0.4, 0.8);

		/*连接主货箱与拖箱*/
		glBegin(GL_LINES);
			glVertex2f(-0.4f, 0.0f);
			glVertex2f(-0.7f, 0.0f);
		glEnd();

			/*主货箱的两个轮子*/
			glPushMatrix();
			{
				glTranslatef(0.0f, -0.3f, 0.0f);
				glTranslatef(-0.3f, 0.0f, 0.0f);
				Wheel(0.1);
				glTranslatef(0.6f, 0.0f, 0.0f);
				Wheel(0.1);
			}
			glPopMatrix();
			

			glPushMatrix();
			{
				glTranslatef(-1.0f, 0.0f, 0.0f);

				/*拖箱*/
				Quadrangle(0.4, 0.6);

				/*拖箱的两个轮子*/
				glPushMatrix();
				{
					glTranslated(0.0f, -0.3f, 0.0f);
					glTranslatef(-0.2f, 0.0f, 0.0f);
					Wheel(0.1);
					glTranslatef(0.4f, 0.0f, 0.0f);
					Wheel(0.1);
				}
				glPopMatrix();
			}
			glPopMatrix();
	}
	glPopMatrix();
	
}

void COpenGLBaseOperation::Trous()
{
	GLint i, j, k;
	GLdouble s, t, x, y, z, twopi;
	GLdouble PI = 3.141592653589793238462;
	twopi = 2 * PI;


	



	/*定义一个显示列表*/
	//glNewList(1, GL_COMPILE);
	/*管理显示列表*/
	GLint iListIndex = glGenLists(1);
	if (iListIndex != 0)
	{
		glNewList(iListIndex, GL_COMPILE);
		for (i = 0;i < 64;i++)
		{
			glBegin(GL_QUAD_STRIP);
			for (j = 0;j <= 64;j++)
				for (k = 1;k >= 0;k--)
				{
					s = (i + k) % 64 + 0.5;
					t = j % 64;

					x = (1 + 0.1*cos(s*twopi / 64))*cos(t*twopi / 64);
					y = (1 + 0.1*cos(s*twopi / 64))*sin(t*twopi / 64);
					z = 0.1*sin(s*twopi / 64);

					glVertex3f(x, y, z);
				}
			glEnd();
		}
		glEndList();


		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(1.0f);

		glColor3f(1.0f, 0.0f, 0.0f);
		
	}

	/*glIsList(1)检测显示列表1是否存在*/
	if (glIsList(1))
	{
		glPushMatrix();
		glCallList(1);
		glTranslatef(0.8f, 0.0f, 0.0f);
		glCallList(1);
		glTranslatef(-1.6f, 0.0f, 0.0f);
		glCallList(1);
		glTranslatef(0.8f, 0.8f, 0.0f);
		glCallList(1);

		glPopMatrix();
	}

}

void COpenGLBaseOperation::DrawSphere()
{
	GLUquadricObj* quadObj;

	glNewList(2, GL_COMPILE);
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluSphere(quadObj, 0.7, 64, 64);
	glEndList();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);


	/*glIsList(1)检测显示列表1是否存在*/
	if (glIsList(2))
	{
		//glPushMatrix();
		glCallList(2);
		//glPopMatrix();
	}
	
}

void COpenGLBaseOperation::DrawSmoothCube()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_LIGHTING);

	glPushMatrix();
	glRotatef(25.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);

	glScalef(1.2f, 1.2f, 1.2f);

	glBegin(GL_QUAD_STRIP);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);

	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	
	glEnd();

	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);

	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	glEnd();

	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);

	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	glEnd();
	
	glPopMatrix();

	glEnable(GL_LIGHTING);
}

void COpenGLBaseOperation::mImage()
{
	


	GLubyte image1[64][64][3];
	GLubyte image2[64][64][3];

	for (int i = 0;i < 64;i++)
		for (int j = 0;j < 64;j++)
		{
			image1[i][j][0] = (GLubyte)j*3.5;
			image1[i][j][1] = (GLubyte)j*3.5;
			image1[i][j][2] = (GLubyte)j*3.5;
		}
	/*画至左上角*/
	glRasterPos3f(-1.2f, 0.5f, 0.0f);
	glDrawPixels(64, 64, GL_RGB, GL_UNSIGNED_BYTE, image1);
	GLint rasPostion[4];
	glGetIntegerv(GL_CURRENT_RASTER_POSITION, rasPostion);
	glReadPixels(rasPostion[0], rasPostion[1], 64, 64, GL_RGB, GL_UNSIGNED_BYTE, image2);

	/*画至左上角*/
	glRasterPos3f(0.6f, 0.5f, 0.0f);
	glDrawPixels(64, 64, GL_RGB, GL_UNSIGNED_BYTE, image2);
	glGetIntegerv(GL_CURRENT_RASTER_POSITION, rasPostion);

	glRasterPos3f(-1.2f, -0.3f, 0.0f);
	glCopyPixels(rasPostion[0], rasPostion[1], 64, 32, GL_COLOR );

	glRasterPos3f(0.6f, -0.3f, 0.0f);
	glPixelZoom(2.0f, 1.0f);
	glCopyPixels(rasPostion[0], rasPostion[1], 32, 32, GL_COLOR);
}

void COpenGLBaseOperation::TexturePlane()
{
	GLubyte image[64][64][3];

	/*创建纹理*/
	int i, j, g, b, c;
	for (i = 0;i < 64;i++)
		for (j = 0;j < 64;j++)
		{
			c = (((i & 0x04) == 0)^((j & 0x04) == 0)) * 255;
			g = (4 * i) % 255;
			b = (j * i) % 255;
			image[i][j][0]=(GLubyte)c;
			image[i][j][0]=(GLubyte)g;
			image[i][j][0]=(GLubyte)b;
		}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	/*定义纹理*/
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	/*控制纹理*/
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	/*说明纹理贴图方式*/
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	/*启动纹理贴图*/
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	/*定义纹理坐标和物体几何坐标*/
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(-1.0f,-1.0f ,0.0f);
	glTexCoord2f(0.0f, 1.0f);glVertex3f(-1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void COpenGLBaseOperation::BitmapTexture()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glDisable(GL_LIGHTING);


	m_pDib = new CDib(_T("aoe.bmp"));

	GLubyte* pTextureBits = (GLubyte*)m_pDib->GetDibBitsPtr();

	GLint width = m_pDib->GetDibWidth();
	GLint height = m_pDib->GetDibHeight();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	/*定义纹理*/
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pTextureBits);

	/*控制纹理*/
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	/*说明纹理贴图方式*/
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	/*启动纹理贴图*/
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);

	/*定义纹理坐标和物体坐标*/
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);glVertex3f(-1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);

}

void COpenGLBaseOperation::TexGenerate()
{
		GLfloat currentCoelf[]={1.0f,1.0f,1.0f,1.0f};
		
		m_pDib=new CDib(_T("aoe.bmp"));
		GLubyte* pTextureBits=(GLubyte*)m_pDib->GetDibBitsPtr();
		GLint width=m_pDib->GetDibWidth();
		GLint height=m_pDib->GetDibHeight();
		
		glPixelStorei(GL_UNPACK_ALIGNMENT,1);
		
		glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D,0,3,width,height,0,GL_BGR_EXT,GL_UNSIGNED_BYTE,pTextureBits);
		
		/*纹理坐标的自动*/
		glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
		glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
		glTexGenfv(GL_S, GL_OBJECT_PLANE, currentCoelf);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, currentCoelf);

		/*启用纹理贴图*/
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_AUTO_NORMAL);
		glEnable(GL_NORMALIZE);
		glEnable(GL_CW);
		glEnable(GL_BACK);

		glMaterialf(GL_FRONT, GL_SHININESS, 32.0);

		glPushMatrix();
		glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(-5.0f, 0.0f, 1.0f, 0.0f);
		//auxSolidTeapot(0.8);
		glPopMatrix();

		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_AUTO_NORMAL);
		glDisable(GL_NORMALIZE);

}

void COpenGLBaseOperation::GLDrawTest()
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
	glRotatef(m_fAngleX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fAngleY, 0.0f, 1.0f, 0.0f);
	glRotatef(m_fAngleZ, 0.0f, 0.0f, 1.0f);
	//*/
	
	BitmapTexture();

	glPopMatrix();
	
	//glDisable(GL_LIGHTING);
	
	glFinish();

	/*双缓冲*/
	SwapBuffers(wglGetCurrentDC());
}

void COpenGLBaseOperation::Mipmapping()
{
	int i, j;

	GLubyte mipmap32[32][32][4];
	GLubyte mipmap16[16][16][4];
	GLubyte mipmap8[8][8][4];
	GLubyte mipmap4[4][4][4];
	GLubyte mipmap2[2][2][4];
	GLubyte mipmap1[1][1][4];

	/*做Mip贴图的图像数据*/
	for (i = 0;i < 32;i++)
	{
		for (j = 0;j < 32;j++)
		{
			mipmap32[i][j][0] = 50;
			mipmap32[i][j][1] = 125;
			mipmap32[i][j][2] = 255;
			mipmap32[i][j][3] = 255;
		}
	}

	for (i = 0;i < 16;i++)
	{
		for (j = 0;j < 16;j++)
		{
			mipmap16[i][j][0] = 200;
			mipmap16[i][j][1] = 200;
			mipmap16[i][j][2] = 0;
			mipmap16[i][j][3] = 255;
		}
	}

	for (i = 0;i < 8;i++)
	{
		for (j = 0;j < 8;j++)
		{
			mipmap8[i][j][0] = 255;
			mipmap8[i][j][1] = 0;
			mipmap8[i][j][2] = 0;
			mipmap8[i][j][3] = 255;
		}
	}

	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 4;j++)
		{
			mipmap4[i][j][0] = 0;
			mipmap4[i][j][1] = 200;
			mipmap4[i][j][2] = 0;
			mipmap4[i][j][3] = 255;
		}
	}

	for (i = 0;i < 2;i++)
	{
		for (j = 0;j < 2;j++)
		{
			mipmap2[i][j][0] = 0;
			mipmap2[i][j][1] = 0;
			mipmap2[i][j][2] = 200;
			mipmap2[i][j][3] = 255;
		}
	}

	for (i = 0;i < 1;i++)
	{
		for (j = 0;j < 1;j++)
		{
			mipmap1[i][j][0] = 255;
			mipmap1[i][j][1] = 255;
			mipmap1[i][j][2] = 255;
			mipmap1[i][j][3] = 255;
		}
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glShadeModel(GL_FLAT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	/*第零级*/
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 32, 32, 0, GL_RGBA, GL_UNSIGNED_BYTE, &mipmap32);

	/*第一级*/
	glTexImage2D(GL_TEXTURE_2D, 1, 3, 16, 16, 0, GL_RGBA, GL_UNSIGNED_BYTE, &mipmap16);

	/*第二级*/
	glTexImage2D(GL_TEXTURE_2D, 2, 3, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, &mipmap8);

	/*第三级*/
	glTexImage2D(GL_TEXTURE_2D, 3, 3, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, &mipmap4);

	/*第四级*/
	glTexImage2D(GL_TEXTURE_2D, 4, 3, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &mipmap2);

	/*第五级*/
	glTexImage2D(GL_TEXTURE_2D, 5, 3, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &mipmap1);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	
	/*平滑处理*/
	/*
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//*/
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEnable(GL_TEXTURE_2D);

	/*放大视线，体现Mip贴图的作用*/
	gluPerspective(60.0, 1.0*(GLfloat)m_iWindowWidth / (GLfloat)m_iWindowHeight, 1.0, 30000.0);

	/*Mip贴图处理的物体*/

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);glVertex3f(-2.0, -1.0, 0.0);
	glTexCoord2f(0.0, 5.0);glVertex3f(-2.0, 1.0, 0.0);
	glTexCoord2f(5.0, 5.0);glVertex3f(1500.0, 1.0, -5000.0);
	glTexCoord2f(5.0, 0.0);glVertex3f(1500.0, -1.0, -5000.0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	/*视线回位*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 3.0, 7.0);
}

void COpenGLBaseOperation::AutoMipmapping()
{
	int i, j;

	GLubyte mipmap32[32][32][4];
	GLubyte mipmap16[16][16][4];
	GLubyte mipmap8[8][8][4];
	GLubyte mipmap4[4][4][4];
	GLubyte mipmap2[2][2][4];
	GLubyte mipmap1[1][1][4];

	/*做Mip贴图的图像数据*/
	for (i = 0;i < 32;i++)
	{
		for (j = 0;j < 32;j++)
		{
			mipmap32[i][j][0] = 50;
			mipmap32[i][j][1] = 125;
			mipmap32[i][j][2] = 255;
			mipmap32[i][j][3] = 255;
		}
	}

	for (i = 0;i < 16;i++)
	{
		for (j = 0;j < 16;j++)
		{
			mipmap16[i][j][0] = 200;
			mipmap16[i][j][1] = 200;
			mipmap16[i][j][2] = 0;
			mipmap16[i][j][3] = 255;
		}
	}

	for (i = 0;i < 8;i++)
	{
		for (j = 0;j < 8;j++)
		{
			mipmap8[i][j][0] = 255;
			mipmap8[i][j][1] = 0;
			mipmap8[i][j][2] = 0;
			mipmap8[i][j][3] = 255;
		}
	}

	for (i = 0;i < 4;i++)
	{
		for (j = 0;j < 4;j++)
		{
			mipmap4[i][j][0] = 0;
			mipmap4[i][j][1] = 200;
			mipmap4[i][j][2] = 0;
			mipmap4[i][j][3] = 255;
		}
	}

	for (i = 0;i < 2;i++)
	{
		for (j = 0;j < 2;j++)
		{
			mipmap2[i][j][0] = 0;
			mipmap2[i][j][1] = 0;
			mipmap2[i][j][2] = 200;
			mipmap2[i][j][3] = 255;
		}
	}

	for (i = 0;i < 1;i++)
	{
		for (j = 0;j < 1;j++)
		{
			mipmap1[i][j][0] = 255;
			mipmap1[i][j][1] = 255;
			mipmap1[i][j][2] = 255;
			mipmap1[i][j][3] = 255;
		}
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glShadeModel(GL_FLAT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	/*第零级*/
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, 32, 32, GL_RGBA, GL_UNSIGNED_BYTE, mipmap32);

	/*第一级*/
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, 16, 16, GL_RGBA, GL_UNSIGNED_BYTE, mipmap16);

	/*第二级*/
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, 8, 8,  GL_RGBA, GL_UNSIGNED_BYTE, mipmap8);

	/*第三级*/
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, 4, 4,  GL_RGBA, GL_UNSIGNED_BYTE, mipmap4);

	/*第四级*/
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, 2, 2,  GL_RGBA, GL_UNSIGNED_BYTE, mipmap2);

	/*第五级*/
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, 1, 1,  GL_RGBA, GL_UNSIGNED_BYTE, mipmap1);



	/*第零级*/
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32, 32, 0, GL_RGBA, GL_UNSIGNED_BYTE, &mipmap32);

	/*第一级*/
	glTexImage2D(GL_TEXTURE_2D, 1, GL_RGBA, 16, 16, 0, GL_RGBA, GL_UNSIGNED_BYTE, &mipmap16);

	/*第二级*/
	glTexImage2D(GL_TEXTURE_2D, 2,GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, &mipmap8);

	/*第三级*/
	glTexImage2D(GL_TEXTURE_2D, 3,GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, &mipmap4);

	/*第四级*/
	glTexImage2D(GL_TEXTURE_2D, 4,GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &mipmap2);

	/*第五级*/
	glTexImage2D(GL_TEXTURE_2D, 5,GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &mipmap1);
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glEnable(GL_TEXTURE_2D);

	/*放大视线，体现Mip贴图的作用*/
	gluPerspective(60.0, 1.0*(GLfloat)m_iWindowWidth / (GLfloat)m_iWindowHeight, 1.0, 30000.0);

	/*Mip贴图处理的物体*/

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);glVertex3f(-2.0, -1.0, 0.0);
	glTexCoord2f(0.0, 5.0);glVertex3f(-2.0, 1.0, 0.0);
	glTexCoord2f(5.0, 5.0);glVertex3f(1500.0, 1.0, -5000.0);
	glTexCoord2f(5.0, 0.0);glVertex3f(1500.0, -1.0, -5000.0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	/*视线回位*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 3.0, 7.0);
}

void COpenGLBaseOperation::BlendQuads()
{
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.0f, 1.0f, 0.0f, 0.75f);
	glRectf(-0.7f, 0.3f, 0.3f, -0.7f);
	glColor4f(0.0f, 0.0f, 1.0f, 0.5f);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.05f);
	glRectf(-0.1f, 1.0f, 1.0f, -0.1f);
	glPushMatrix();
	glDisable(GL_BLEND);

}

GLint COpenGLBaseOperation::Sphere(GLdouble radius)
{
	GLint sphereList = glGenLists(1);
	GLUquadricObj* quadObj;
	glNewList(sphereList, GL_COMPILE);
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluSphere(quadObj, radius, 32, 32);
	glEndList();
	return sphereList;
}

void COpenGLBaseOperation::BlendObjects()
{
	glDisable(GL_LIGHTING);
	/*光的位置*/
	GLfloat HghtPosition[] = { 0.5f,0.5f,1.0f,0.0f, };
	/*不透明物体材质*/
	GLfloat matSpecular[] = { 1.0f,1.0f,1.0f,0.15f };
	GLfloat matShininess[] = { 100.0f };
	GLfloat matSolid[] = { 0.75f,0.75f,0.0f,1.0f };
	GLfloat matZero[] = { 0.0f,0.0f,0.0f,1.0f };
	/*透明物体材质*/
	GLfloat matTransparent[] = { 0.0f,0.0f,0.0f,1.0f };
	GLfloat matEmission[] = { 0.0f,0.3f,0.3f,0.6f };
	glLightfv(GL_LIGHT0, GL_POSITION, HghtPosition);
	
	/*球*/
	GLint sphereList=Sphere(0.7);

	/*玻璃*/
	GLint cubeList = glGenLists(1);
	glNewList(cubeList, GL_COMPILE);
	DrawCube();
	glEndList();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/*第一步：启动深度测试*/
	glEnable(GL_DEPTH_TEST);

	/*第二步：绘制不透明体*/
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.05f);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matSolid);
	glCallList(sphereList);
	glPopMatrix();
	
	/*第三步：设置深度缓存为只读模式，并启动融合*/
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	/*第四步：绘制透明体*/
	glPushMatrix();
	glTranslatef(-0.8f, -0.8f, 0.1f);
	glRotatef(5.0f, 1.0f, 1.0f, 0.0f);
	glRotatef(10.0f, 0.0f, 1.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matTransparent);
	glCallList(cubeList);
	glPopMatrix();

	/*第五步：恢复深度缓存的可读写属性*/
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	
}

void COpenGLBaseOperation::DrawQuadrics()
{
	/*光照与材质*/
	GLfloat position[] = { 0.0,0.0,3.0,0.0 };
	glLightfv(GL_LIGHT0 , GL_POSITION , position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	{
		GLfloat material[3] = { 0.2f,0.05f,0.05f };
		glMaterialfv(GL_FRONT , GL_AMBIENT , material);

		material[0] = 1.0f;
		material[1] = 0.2f;
		material[2] = 0.1f;
		glMaterialfv(GL_FRONT , GL_DIFFUSE, material);

		material[0] = 0.8f;
		material[1] = 0.8f;
		material[2] = 0.8f;
		glMaterialfv(GL_FRONT , GL_SPECULAR , material);
		glMaterialf(GL_FRONT , GL_SHININESS , 60.0);

	}
	GLUquadricObj* quadObj;

	/*点球*/
	glNewList(1 , GL_COMPILE);
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj , GLU_POINT);
	gluQuadricNormals(quadObj , GLU_SMOOTH);
	gluSphere(quadObj , 0.4 , 32 , 32);
	glEndList();

	/*圆锥*/
	glNewList(2 , GL_COMPILE);
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj , GLU_FILL);
	gluQuadricNormals(quadObj , GLU_SMOOTH);
	gluCylinder(quadObj , 0.0,0.3,0.8,16,16);
	glEndList();

	/*圆柱*/
	glNewList(3 , GL_COMPILE);
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj , GLU_FILL);
	gluQuadricNormals(quadObj , GLU_SMOOTH);
	gluCylinder(quadObj , 0.3 , 0.3 , 0.8 , 16 , 16);
	glEndList();

	/*台锥*/
	glNewList(4 , GL_COMPILE);
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj , GLU_FILL);
	gluQuadricNormals(quadObj , GLU_SMOOTH);
	gluCylinder(quadObj , 0.1 , 0.3 , 0.6 , 16 , 16);
	glEndList();

	/*圆环*/
	glNewList(5 , GL_COMPILE);
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj , GLU_FILL);
	gluQuadricNormals(quadObj , GLU_SMOOTH);
	gluQuadricNormals(quadObj , GLU_OUTSIDE);
	gluDisk(quadObj , 0.1 , 0.3 , 16 , 16);
	glEndList();

	/*圆盘*/
	glNewList(6 , GL_COMPILE);
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj , GLU_FILL);
	gluQuadricNormals(quadObj , GLU_SMOOTH);
	gluDisk(quadObj , 0.0 , 0.3 , 16 , 16);
	glEndList();

	/*扇形*/
	glNewList(7 , GL_COMPILE);
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj , GLU_FILL);
	gluQuadricNormals(quadObj , GLU_SMOOTH);
	gluPartialDisk(quadObj , 0.1 , 0.3 , 16 , 16, 0.0, 60);
	glEndList();

	/*球*/
	glNewList(8 , GL_COMPILE);
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj , GLU_FILL);
	gluQuadricNormals(quadObj , GLU_SMOOTH);
	gluSphere(quadObj , 0.4 , 32 , 32);
	glEndList();




	glPushMatrix();
	glTranslatef(-1.0f , 0.8f , 0.0f);
	glCallList(5);
	glTranslatef(0.7f , 0.0f , 0.0f);
	glCallList(6);
	glTranslatef(0.7f , 0.0f , 0.0f);
	glCallList(7);

	glTranslatef(-0.4f , -0.8f , 0.0f);
	glRotatef(90.0f , 1.0f , 0.0f , 0.0f);
	glCallList(2);
	glTranslatef(-1.0f , 0.0f , 0.0f);
	glCallList(1);
	glTranslatef(2.0f , 0.0f , 0.0f);
	glCallList(3);
	glTranslatef(0.0f , 0.8f , -1.0f);
	glCallList(4);
	glTranslatef(0.0f , 0.8f , 0.0f);
	glCallList(8);

	glPopMatrix();

}

void COpenGLBaseOperation::DrawBezierCurve()
{
	glColor3f(1.0, 0.0, 0.0);

	/*控制点*/
	GLfloat controlPoints[9][3]={
		{-1.0f,0.0f,0.0f},{-0.75f,0.707f,0.0f},{-0.5f,1.0f,0.0f},
		{-0.25f,0.707f,0.0f},{0.0f,0.0f,0.0f},{0.25f,-0.707f,0.0f},
		{0.5f,-1.0f,0.0f},{0.75f,-0.707f,0.0f},{1.0f,0.0f,0.0f}
	};

	/*一维评价器*/
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 9, (const float*)controlPoints);
	/*激活*/
	glEnable(GL_MAP1_VERTEX_3);

	/*计算曲线坐标并连接*/
	/*评价器获得区县近似点后，还需要用直线段的方法将他们连接成线，而glMap1并不能完成这一工作*/
	/*其中50可理解为公用50段直线段来逼近这条曲线，数值越高，逼近程度越高，但需要的计算量越大*/
	glBegin(GL_LINE_STRIP);
	for (int i = 0;i <= 50;i++)
		glEvalCoord1f((GLfloat)i / (GLfloat)50.0);
	glEnd();
	/*挂起*/
	glDisable(GL_MAP1_VERTEX_3);

}

void COpenGLBaseOperation::EvenBezierCurve()
{
	glColor3f(0.0f, 1.0f, 0.0f);
	/*控制点*/
	GLfloat controlPoints[9][3] = {
		{ -1.0f,0.0f,0.0f },{ -0.75f,0.707f,1.0f },{ -0.5f,1.0f,0.0f },
		{ -0.25f,0.707f,0.0f },{ 0.0f,0.0f,0.0f },{0.25f,-0.707f,0.0f },
		{ 0.5f,-1.0f,1.0f },{ 0.75f,-0.707f,0.0f },{ 1.0f,0.0f,0.0f }
	};

	/*一维评价器*/
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 9, (const float*)controlPoints);
	/*激活*/
	glEnable(GL_MAP1_VERTEX_3);

	/*计算曲线坐标并连接*/
	/*评价器获得区县近似点后，还需要用直线段的方法将他们连接成线，而glMap1并不能完成这一工作*/
	/*其中50可理解为公用50段直线段来逼近这条曲线，数值越高，逼近程度越高，但需要的计算量越大*/
	
	/*自动等分区间*/
	glMapGrid1f(50, 0.0f, 1.0f);

	/*绘制曲线*/
	/*用glEvalMesh1(GL_LINE, 0, 50)来连接这50段直线段*/
	glEvalMesh1(GL_LINE, 0, 50);

	/*挂起*/
	glDisable(GL_MAP1_VERTEX_3);
}

void COpenGLBaseOperation::DrawBezier()
{
	DrawBezierCurve();
	EvenBezierCurve();
}

void COpenGLBaseOperation::DrawNurbsCurve()
{
	/*控制点*/
	GLfloat controlPoints[7][3] = {
		{ -1.2f,0.8f,0.0f },{ -0.8f,-2.0,0.0f },{ -0.4f,0.4f,0.0f },
		{ 0.0f,2.0f,0.0f },{0.4f,0.4f,0.0f },{ 0.8f,-2.0f,0.0f },
		{ 1.2f,0.8f,0.0f }
	}; 

	/*节点*/
	GLfloat  knots[14] = {
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
	};

	glColor3f(0.0f, 0.0f, 1.0f);

	/*创建NURBS对象*/
	GLUnurbsObj* theNurb;
	theNurb = gluNewNurbsRenderer();

	/*属性*/
	gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 10.0);
	
	/*绘制*/
	glNewList(1, GL_COMPILE);
	gluBeginCurve(theNurb);
	gluNurbsCurve(theNurb, 14, knots, 3, (float*)controlPoints, 7, GL_MAP1_VERTEX_3);
	gluEndCurve(theNurb);
	glEndList();

	glCallList(1);
}

void COpenGLBaseOperation::BzrSufacMesh()
{
	int i, j;
	/*控制点*/
	GLfloat controlPoints[4][4][3] = {
		{ { -0.8f,-0.6f,0.8f },{ -0.2f,-0.6f,1.6f },{ 0.2f,-0.6f,-0.4f },{ 0.6f,-0.6f,0.8f } },
		{ { -0.6f,-0.2f,0.8f },{ -0.2f,-0.2f,1.6f },{ 0.2f,-0.2f,0.8f },{ -0.8f,-0.2f,0.8f } },
		{ { -0.6f,0.2f,0.8f },{ -0.2f,-0.2f,0.4f },{ 0.2f,0.2f,0.8f },{ 0.3f,0.2f,-0.4f } },
		{ { -0.6f,0.6f,0.8f },{ -0.2f,-0.6f,0.4f },{ -0.8f,0.6f,0.8f },{ 0.8f,0.6f,-0.4f } },
	};

	/*二维评价器*/
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 12, 4, (const float*)controlPoints);

	/*激活*/
	glEnable(GL_MAP2_VERTEX_3);
	glColor3f(0.0, 0.0, 1.0);

	/*绘制*/
	glPushMatrix();
	glRotatef(45.0, 1.0, 1.0, 1.0);
	for (j = 0;j <= 8;j++)
	{
		glBegin(GL_LINE_STRIP);
		for (i = 0;i <= 30;i++)
			glEvalCoord2f((GLfloat)i / 30.0, (GLfloat)j / 8.0);

		glEnd();
		glBegin(GL_LINE_STRIP);
		for (i = 0;i <= 30;i++)
			glEvalCoord2f((GLfloat)j / 8.0, (GLfloat)i / 30.0);
		glEnd();
	}
	glPopMatrix();

	/*挂起*/
	glDisable(GL_MAP2_VERTEX_3);
}

void COpenGLBaseOperation::BzrSufacMeshFill()
{
	/*几何控制点*/
	GLfloat controlPoints[4][4][3] = {
		{ { -0.8f,-0.6f,0.8f },{ -0.2f,-0.6f,1.6f },{ 0.2f,-0.6f,-0.4f },{ 0.6f,-0.6f,0.8f } },
		{ { -0.6f,-0.2f,0.8f },{ -0.2f,-0.2f,1.6f },{ 0.2f,-0.2f,0.8f },{ -0.8f,-0.2f,0.8f } },
		{ { -0.6f,0.2f,0.8f },{ -0.2f,-0.2f,0.4f },{ 0.2f,0.2f,0.8f },{ 0.3f,0.2f,-0.4f } },
		{ { -0.6f,0.6f,0.8f },{ -0.2f,-0.6f,0.4f },{ -0.8f,0.6f,0.8f },{ 0.8f,0.6f,-0.4f } },
	};
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/*二维评价器*/
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 12, 4, (const float*)controlPoints);

	/*自动网格*/
	glMapGrid2f(30.0, 0.0, 1.0, 30.0, 0.0, 1.0);

	/*激活*/
	glEnable(GL_MAP2_VERTEX_3);
	//glColor3f(0.0, 0.0, 1.0);

	/*绘制*/
	glPushMatrix();
	glRotatef(45.0, 1.0, 1.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 30, 0, 30);
	glPopMatrix();

	/*挂起*/
	glDisable(GL_MAP2_VERTEX_3);
	glDisable(GL_AUTO_NORMAL);
	glDisable(GL_NORMALIZE);
}

void COpenGLBaseOperation::BzrSufacTex()
{
	/*几何控制点*/
	GLfloat controlPoints[4][4][3] = {
		{ { -0.8f,-0.6f,0.8f },{ -0.2f,-0.6f,1.6f },{ 0.2f,-0.6f,-0.4f },{ 0.6f,-0.6f,0.8f } },
		{ { -0.6f,-0.2f,0.8f },{ -0.2f,-0.2f,1.6f },{ 0.2f,-0.2f,0.8f },{ -0.8f,-0.2f,0.8f } },
		{ { -0.6f,0.2f,0.8f },{ -0.2f,-0.2f,0.4f },{ 0.2f,0.2f,0.8f },{ 0.3f,0.2f,-0.4f } },
		{ { -0.6f,0.6f,0.8f },{ -0.2f,-0.6f,0.4f },{ -0.8f,0.6f,0.8f },{ 0.8f,0.6f,-0.4f } },
	};

	/*纹理控制点*/
	GLfloat textureCutrlPnt[2][2][2]=
	{
		{{0.0f,0.0f},{0.0f,0.1f}},
		{{1.0f,0.0f},{1.0f,1.0f}}
	};

	/*构造纹理*/
	m_pDib = new CDib(_T("aoe.bmp"));

	GLubyte* pTextureBits = (GLubyte*)m_pDib->GetDibBitsPtr();

	GLint width = m_pDib->GetDibWidth();
	GLint height = m_pDib->GetDibHeight();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	/*定义纹理*/
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pTextureBits);

	/*控制纹理*/
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	/*说明纹理贴图方式*/
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	/*二维评价器*/
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 23, 4, 1, 2, 12, 4, (const float*)controlPoints);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, (const float*)textureCutrlPnt);

	/*光照*/


	/*启动纹理贴图*/
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/*绘制*/
	glMapGrid2f(30, 0.0, 1.0, 30, 0.0, 1.0);
	glPushMatrix();
	glScalef(1.2f, 1.2f, 1.2f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(45.0f, 1.0f, 1.0f, 1.0f);
	glEvalMesh2(GL_FILL, 0, 30, 0, 30);
	glPopMatrix();

	/*挂起*/
	glDisable(GL_MAP2_VERTEX_3);
	glDisable(GL_MAP2_TEXTURE_COORD_2);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_AUTO_NORMAL);
	glDisable(GL_NORMALIZE);
}

void COpenGLBaseOperation::NurbsSurface()
{
	GLint m_nurbsSurfaceMode;
	m_nurbsSurfaceMode = GLU_OUTLINE_POLYGON;
	/*控制点*/
	GLfloat controlPoints[4][4][3] = {
		{ { -0.8f,-0.6f,0.8f },{ -0.2f,-0.6f,1.6f },{ 0.2f,-0.6f,-0.4f },{ 0.6f,-0.6f,0.8f } },
		{ { -0.6f,-0.2f,0.8f },{ -0.2f,-0.2f,1.6f },{ 0.2f,-0.2f,0.8f },{ -0.8f,-0.2f,0.8f } },
		{ { -0.6f,0.2f,0.8f },{ -0.2f,-0.2f,0.4f },{ 0.2f,0.2f,0.8f },{ 0.3f,0.2f,-0.4f } },
		{ { -0.6f,0.6f,0.8f },{ -0.2f,-0.6f,0.4f },{ -0.8f,0.6f,0.8f },{ 0.8f,0.6f,-0.4f } },
	};

	/*节点*/
	GLfloat sknots[8] = { 0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f };
	GLfloat tknots[8] = { 0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f };

	/*光照*/

	glDepthFunc(GL_LESS);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/*NURBS对象及属性*/
	GLUnurbsObj* theNurb;
	theNurb = gluNewNurbsRenderer();
	gluNurbsProperty(theNurb , GLU_SAMPLING_TOLERANCE , 25.0);
	gluNurbsProperty(theNurb , GLU_DISPLAY_MODE , m_nurbsSurfaceMode);

	/*绘制*/
	glNewList(1 , GL_COMPILE);
	gluBeginSurface(theNurb);
	gluNurbsSurface(theNurb , 8 , sknots , 8 , tknots , 3 , 12 , (float*)controlPoints , 4 , 4 , GL_MAP2_VERTEX_3);
	gluEndSurface(theNurb);
	glEndList();

	glPushMatrix();
	glScalef(1.2f , 1.2f , 1.2f);
	glRotatef(45.0f , 0.0f , 0.0f , 1.0f);
	glRotatef(45.0f , 1.0f , 1.0f , 1.0f);
	glCallList(1);
	glPopMatrix();
	glDisable(GL_AUTO_NORMAL);
	glDisable(GL_NORMALIZE);
	

}

void COpenGLBaseOperation::NurbsSurfaceTrim()
{
	
	/*控制点*/
	GLfloat controlPoints[4][4][3] = {
		{ { -0.8f,-0.6f,0.8f },{ -0.2f,-0.6f,1.6f },{ 0.2f,-0.6f,-0.4f },{ 0.6f,-0.6f,0.8f } },
		{ { -0.6f,-0.2f,0.8f },{ -0.2f,-0.2f,1.6f },{ 0.2f,-0.2f,0.8f },{ -0.8f,-0.2f,0.8f } },
		{ { -0.6f,0.2f,0.8f },{ -0.2f,-0.2f,0.4f },{ 0.2f,0.2f,0.8f },{ 0.3f,0.2f,-0.4f } },
		{ { -0.6f,0.6f,0.8f },{ -0.2f,-0.6f,0.4f },{ -0.8f,0.6f,0.8f },{ 0.8f,0.6f,-0.4f } },
	};

	/*节点*/
	GLfloat sknots[8] = { 0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f };
	GLfloat tknots[8] = { 0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f };

	/*外边界：逆时针*/
	GLfloat edgePoint[5][2] = {
		{0.0f,0.0f},{1.0f,0.0f},{1.0f,1.0f},{0.0f,1.0f},{ 0.0f,0.0f }
	};

	/*内边界：顺时针*/
	GLfloat pwlPoint[5][2] = {
		{0.75f,.075f},{0.75f,0.25f},{0.25f,0.25f},{0.25f,0.75f},{0.75f,0.75f}
	};

	/*光照*/

	glDepthFunc(GL_LESS);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/*NURBS对象及属性*/
	GLUnurbsObj* theNurb;
	theNurb = gluNewNurbsRenderer();
	gluNurbsProperty(theNurb , GLU_SAMPLING_TOLERANCE , 25.0);
	gluNurbsProperty(theNurb , GLU_DISPLAY_MODE , GLU_FILL);

	/*绘制*/
	glNewList(1 , GL_COMPILE);
	gluBeginSurface(theNurb);
	gluNurbsSurface(theNurb , 8 , sknots , 8 , tknots , 3 , 12 , (float*)controlPoints , 4 , 4 , GL_MAP2_VERTEX_3);
	
	gluBeginTrim(theNurb);
	gluPwlCurve(theNurb , 5 , (float*)edgePoint , 2 , GLU_MAP1_TRIM_2);
	gluEndTrim(theNurb);
	
	gluBeginTrim(theNurb);
	gluPwlCurve(theNurb , 5 , (float*)pwlPoint , 2 , GLU_MAP1_TRIM_2);
	gluEndTrim(theNurb);

	gluEndSurface(theNurb);
	glEndList();

	glPushMatrix();
	glScalef(1.2f , 1.2f , 1.2f);
	glRotatef(45.0f , 0.0f , 0.0f , 1.0f);
	glRotatef(45.0f , 1.0f , 1.0f , 1.0f);
	glCallList(1);
	glPopMatrix();

	glDisable(GL_AUTO_NORMAL);
	glDisable(GL_NORMALIZE);
}

void COpenGLBaseOperation::StencilMask()
{
	GLfloat matDiffuse[] = { 0.8f,0.8f,0.0f,1.0f };
	GLfloat matSpecular[] = { 0.8f,0.8f,0.0f,1.0f };
	GLfloat maskDiffuse[] = { 0.8f , 0.8f , 0.0f , 1.0f };
	GLfloat maskSpecular[] = { 0.8f , 0.8f , 0.0f , 1.0f };
	GLfloat maskPosition[] = { 0.8f , 0.8f , 0.0f , 1.0f };
	//glLightfv(GL_LIGHT0 , GL_POSITION , lightPosition);
	GLint iMatList = glGenLists(2);

	glNewList(iMatList , GL_COMPILE);
	glMaterialfv(GL_FRONT , GL_DIFFUSE , maskSpecular);
	glMaterialf(GL_FRONT , GL_SHININESS , 25.0f);
	glEndList();

	glNewList(iMatList + 1 , GL_COMPILE);
	glMaterialfv(GL_FRONT , GL_DIFFUSE , matDiffuse);
	glMaterialfv(GL_FRONT , GL_SPECULAR , matSpecular);
	glMaterialf(GL_FRONT , GL_SHININESS , 70.0f);
	glEndList();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);

	/*创建一个正方形模块区域*/
	glStencilFunc(GL_ALWAYS , 0x1 , 0x1);
	glStencilOp(GL_REPLACE , GL_REPLACE , GL_REPLACE);
	glBegin(GL_QUADS);
	glVertex3f(-0.7f , 0.0f , 0.0f);
	glVertex3f(0.0f , 0.7f , 0.0f);
	glVertex3f(0.7f , 0.0f , 0.0f);
	glVertex3f(0.0f , -0.7f , 0.0f);
	glEnd();

	/*在模板值为1的地方绘制一个蓝色球*/
	glStencilFunc(GL_EQUAL , 0x1 , 0x1);
	glCallList(iMatList);
	DrawSphere();

	/*在模板值非1的地方绘制一个黄色求*/
	glStencilFunc(GL_NOTEQUAL , 0x1 , 0x1);
	glStencilOp(GL_KEEP , GL_KEEP , GL_KEEP);
	glPushMatrix();
	glCallList(iMatList + 1);
	DrawSphere();
	glPopMatrix();
}

void COpenGLBaseOperation::StencilClip()
{
	glDepthFunc(GL_LEQUAL);
	glColorMask(GL_FALSE , GL_FALSE , GL_FALSE , GL_FALSE);
	glStencilFunc(GL_ALWAYS , 0x1 , 0x3);
	glStencilOp(GL_REPLACE , GL_REPLACE , GL_REPLACE);
	glPushMatrix();
	glTranslatef(-0.4f , 0.0f , 0.0f);
	DrawSphere();
	glPopMatrix();
	glStencilFunc(GL_EQUAL , 0x1 , 0x3);
	glStencilOp(GL_KEEP , GL_INCR , GL_INCR);

	glPushMatrix();
	glTranslatef(0.4f , 0.0f , 0.0f);
	DrawSphere();
	glPopMatrix();
	glColorMask(GL_TRUE , GL_TRUE , GL_TRUE , GL_TRUE);
	glStencilFunc(GL_EQUAL , 0x2 , 0x3);
	glStencilOp(GL_KEEP , GL_INCR , GL_INCR);
	glPolygonMode(GL_FRONT , GL_FILL);


	glPushMatrix();
	glTranslatef(0.0f , 0.0f , 1.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f , 1.0f , 1.0f);
	glVertex3f(-0.8f , 0.8f , 0.0f);
	glVertex3f(0.8f , 0.8f , 0.0f);
	glColor3f(0.0f , 0.0f , 0.0f);
	glVertex3f(0.8f , -0.8f , 0.0f);
	glVertex3f(-0.8f , -0.8f , 0.0f);
	glEnd();
	glPopMatrix();
}
void COpenGLBaseOperation::CreateSphere()
{
	GLfloat matDif_1[] = { 0.8f , 0.8f , 0.0f , 1.0f };
	GLfloat matSpe_1[] = { 1.0f , 1.0f , 1.0f , 1.0f };
	GLfloat matDif_2[] = { 0.1f , 0.2f , 0.8f , 1.0f };
	GLfloat matSpe_2[] = { 0.1f , 1.0f , 1.0f , 1.0f };
	GLfloat matDif_3[] = { 0.1f , 0.8f , 0.8f , 1.0f };
	GLfloat matSpe_3[] = { 0.1f , 1.0f , 1.0f , 1.0f };
	GLfloat matDif_4[] = { 0.8f , 0.2f , 0.8f , 1.0f };
	GLfloat matSpe_4[] = { 0.0f , 3.0f , 2.0f , 0.0f };

	//glLightfv(GL_LIGHT0,GL_POSITION , lightPosition);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	glNewList(5 , GL_COMPILE);
	glMaterialfv(GL_FRONT , GL_DIFFUSE , matDif_1);
	glMaterialfv(GL_FRONT , GL_SPECULAR , matSpe_1);
	glMaterialf(GL_FRONT , GL_SHININESS , 25.0f);
	glEndList();

	glNewList(6 , GL_COMPILE);
	glMaterialfv(GL_FRONT , GL_DIFFUSE , matDif_2);
	glMaterialfv(GL_FRONT , GL_SPECULAR , matSpe_2);
	glMaterialf(GL_FRONT , GL_SHININESS , 70.0f);
	glEndList();

	glNewList(7 , GL_COMPILE);
	glMaterialfv(GL_FRONT , GL_DIFFUSE , matDif_3);
	glMaterialfv(GL_FRONT , GL_SPECULAR , matSpe_3);
	glMaterialf(GL_FRONT , GL_SHININESS , 50.0f);
	glEndList();

	glNewList(8 , GL_COMPILE);
	glMaterialfv(GL_FRONT , GL_DIFFUSE , matDif_4);
	glMaterialfv(GL_FRONT , GL_SPECULAR , matSpe_4);
	glMaterialf(GL_FRONT , GL_SHININESS , 60.0f);
	glEndList();

	GLUquadricObj* quadObj;

	glNewList(1 , GL_COMPILE);
	glCallList(5);
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj , GLU_FILL);
	gluQuadricNormals(quadObj , GLU_SMOOTH);
	gluSphere(quadObj , 0.2 , 16 , 16);
	glEndList();

	glNewList(2 , GL_COMPILE);
	glCallList(6);
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj , GLU_FILL);
	gluQuadricNormals(quadObj , GLU_SMOOTH);
	gluSphere(quadObj , 0.2 , 16 , 16);
	glEndList();

	glNewList(3 , GL_COMPILE);
	glCallList(7);
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj , GLU_FILL);
	gluQuadricNormals(quadObj , GLU_SMOOTH);
	gluSphere(quadObj , 0.2 , 16 , 16);
	glEndList();

	glNewList(4 , GL_COMPILE);
	glCallList(8);
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj , GLU_FILL);
	gluQuadricNormals(quadObj , GLU_SMOOTH);
	gluSphere(quadObj , 0.2 , 16 , 16);
	glEndList();

	glNewList(9 , GL_COMPILE);
	glPushMatrix();
	glTranslatef(-0.4f , 0.4f , 0.0f);
	glCallList(1);
	glTranslatef(-0.6f , 0.6f , 0.0f);
	glCallList(4);
	glPopMatrix();
	glEndList();

	glNewList(10 , GL_COMPILE);
	glPushMatrix();
	glTranslatef(0.4f , 0.4f , 0.0f);
	glCallList(2);
	glTranslatef(0.6f , 0.6f , 0.0f);
	glCallList(3);
	glPopMatrix();
	glEndList();

	glNewList(11 , GL_COMPILE);
	glPushMatrix();
	glTranslatef(-0.4f , -0.4f , 0.0f);
	glCallList(3);
	glTranslatef(-0.6f , -0.6f , 0.0f);
	glCallList(2);
	glPopMatrix();
	glEndList();

	glNewList(12 , GL_COMPILE);
	glPushMatrix();
	glTranslatef(0.4f , -0.4f , 0.0f);
	glCallList(4);
	glTranslatef(0.6f , -0.6f , 0.0f);
	glCallList(1);
	glPopMatrix();
	glEndList();
}
void COpenGLBaseOperation::Cicle(GLfloat dRadius,GLfloat fLine,GLfloat n)
{
	GLfloat dStep = (2 * 3.14159265) / (GLfloat)n;
	GLfloat fV[3];
	glLineWidth(fLine);

	glBegin(GL_LINE_STRIP);

	for (GLdouble i = 0.0;i <= 2 * 3.14159265 + dStep;i += dStep)
	{
		fV[0] = dRadius * cos(i);
		fV[1] = dRadius * sin(i);
		fV[2] = 0.0f;
		glVertex3fv(fV);
	}
	glEnd();
}

void COpenGLBaseOperation::DrawNameObjects()
{
	int i , j;
	for (i = 0;i < 2;i++)
	{
		glLoadName(i);
		for (j = 0;j < 2;j++)
		{
			glColor3f((GLfloat)i / 3.0 , (GLfloat)j / 3.0 , (GLfloat)BackColor[i][j] / 3.0);
			glRectf((i - 1)*1.5f , (j - 1)*1.5f , i*1.5f , j*1.5f);

			if ((i == 0) && (j == 0))
			{
				glCallList(9);

			}

			if ((i == 0) && (j == 1))
			{
				glCallList(10);

			}

			if ((i == 1) && (j == 0))
			{
				glCallList(11);

			}

			if ((i == 1) && (j == 1))
			{
				glCallList(12);

			}

		}
		glPopName();
	}
}

void COpenGLBaseOperation::WhatHits(GLint hits , GLuint* buffer)
{
	int i , j;
	GLuint ii , jj , names , *ptr;
	ii = jj = 0;
	ptr = buffer;
	for (i = 0;i < hits;i++)
	{
		names = *ptr;
		ptr += 3;
		for (j = 0;j < names;j++)
		{
			if (j == 0)ii = *ptr;
			else if (j == names - 1)jj = *ptr;
			ptr++;
		}
		BackColor[ii][jj] = (BackColor[ii][jj] + 1) % 4;
	}
}

void COpenGLBaseOperation::DrawNonSelect()
{
	GLfloat lw[2];
	glGetFloatv(GL_LINE_WIDTH_RANGE , lw);

	glPushMatrix();
	glTranslatef(0.0f , 0.0f , 0.01f);
	glColor3f(1.0f , 0.0f , 0.0f);
	//Circle(0.2 , lw[1] / 8.0 , 50);
	
}

void COpenGLBaseOperation::LButtonDown(UINT nFlags , CPoint point)
{
	if (m_nSelect != 34)return;

	GLuint selectBuf[512];
	GLint hits;
	GLint viewport[4];
	int x , y;

	x = point.x;
	y = point.y;
	glGetIntegerv(GL_VIEWPORT , viewport);

	glSelectBuffer(512 , selectBuf);
	glRenderMode(GL_SELECT);

	glInitNames();
	glPushName((unsigned)-1);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPickMatrix((GLdouble)x , (GLdouble)(viewport[3] - y) , 5.0 , 5.0 , viewport);
	glFrustum(-1.0 , 1.0 , -1.0 , 1.0 , 2.0 , 8.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f , 0.0f , -3.5f);
	DrawNameObjects();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	hits = glRenderMode(GL_RENDER);
	WhatHits(hits , selectBuf);

}

