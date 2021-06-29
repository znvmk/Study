#pragma once
//#include "afxwin.h"
#include"stdafx.h"


#define ABS(x) ((x)<0?-(x):(x)>0?(x):0)

#include"GraphDraw.h"





//enum { Cube };

/************************************************************************************************/
/*                                                                                              */
/*���ڴ�С��CMainFrame����#��ʼ����cs.cx,cs.cy***************************************************/
/*                                                                                              */
/***************************************OpenGL��ʼ��*********************************************/
/*                                                                                              */
/*GLInit()��ʼ����view��Init()��ʼ�������б����ã����ڳ�ʼ����ͼ����*****************************/
/*GLSize()��ʼ����view��Size()��ʼ�������б����ã����ڳ�ʼ��GL��ͼ�����ӵ��С*******************/
/*GLDraw()��ʼ����view��OnDraw()�����б����ã�GLDraw()����DrawScene()��ʼ����ͼ����**************/
/*GLDestroy()��ʼ����view��OnDestroy()�����б����ã��������ٻ�ͼ����*****************************/
/*                                                                                              */
/************************************************************************************************/




class COpenGLFrame :
	public CWnd
{
public:
	COpenGLFrame();
	~COpenGLFrame();


	

	/*����*/
public:
	/*���ô��ڳ�ʼ��С*/
	int m_WindowWidth , m_WindowHeight;

	/*��ʼλ��*/
	GLfloat m_fAngelX, m_fAngelY , m_fAngelZ;
	/*��ʼ�Ƕ�*/
	GLfloat m_fPositionX, m_fPositionY , m_fPositionZ;

	/*��ת����*/
	GLfloat m_fRevolveAngleStep;
	/*ƽ�Ʋ���*/
	GLfloat m_fTranslationStep;




	int m_nSelect;


  /*����*/
protected:

	int a, b, c;

	CGraphDraw m_gd;


	/*��Դ*/
	/*���û����⣬������⣬�۹�ָ������Դλ��*/
	GLfloat m_lightAmb[4], m_lightDif[4], m_lightSpe[4], m_lightPos[4];

	/*����*/
	GLfloat m_materialAmb[4], m_materialDif[4], m_materialSpe[4], m_materialPos[4], m_materialShininess[4];
	BOOL m_bMatrial;

	GLubyte image[64][64][3];

	
	
	/*��ǰ���ڴ�С*/
	GLint m_iWindowWidth;
	GLint m_iWindowHeight;


	

/*��������ʼ��*/
protected:
	/*��ʼ����Դ����*/
	void InitLightParameter();

	/*��ʼ�����ʲ���*/
	void InitMatrialParameter();

	/*������Դ*/
	void CreateLights();

	/*��������*/
	void CreateMaterial();

	/*��ʼ������*/
	void DrawScene();


	/*����*/
public:
	BOOL bSetupPixelFormat(CClientDC* m_pDC);

	/*��ʼ����view���ʼ�������б�����*/
	void GLInit(CClientDC* m_pDC);

	void GLDestroy(CClientDC* m_pDC);

	/*�ӿڱ任*/
	void GLSize(UINT nType , int cx , int cy , CRect m_oldRect);



	
/*����*/
protected:

	
	

public:
	

public:
	/*�滭ѡ��*/
	void GLDraw(int select);

	/*�滭����*/
	void GLDrawTest();

	void LButtonDown(UINT nFlags , CPoint point);


	/*ƽ�Ʊ任*/
	/*ǰ��front ,��back , ��left , �ң�right*/
	/*����direction��ǰ��0 , ��1 ,��2 ,�ң�3*/
	void PfmTranslate(int translation_direction);


	/*��ת�任*/
	/*γ�ȣ�latitude,���ȣ�longitude,˳ʱ�룺clockwise,��ʱ�룺anticlockwise*/
	/*�Ƕȷ���angel_direction��ˮƽ˳ʱ�룺0��ˮƽ��ʱ�룺1����ֱ˳ʱ�룺2����ֱ��ʱ�룺3*/
	void PfmRotate(int revolve_direction);

/*���ɵ���Ϣӳ�亯��*/
public:
	DECLARE_MESSAGE_MAP()


	
};
