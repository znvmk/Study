#pragma once


/*图形绘制类*/
class CGraphPlot
{
public:
	CGraphPlot();
	virtual~CGraphPlot();


public:
	double r;

public:
	//*
public:
	int			m_Time, m_Fram;
	////摄像机////////////////////////////////////////////////////////////////////
private:GLdouble	g_eye[3];		//
		GLdouble	g_look[3];		//
		float		rad_xz;			//角度
		float		g_Angle;		//左右转
		float		g_elev;			//仰俯角
		UINT g_cactus[16];	//贴图
		GLUquadricObj *g_text;
public:
	GLvoid		DrawGround();	//篮色网格地面线
	BOOL		DisplayScene();	//摄像机
	void		light0();
	void		picter(float x, float y, float z);//组合图形
	void		Box(float x, float y, float z);
	void		airplane(float x, float y, float z);//组合飞机
	bool LoadT8(char *filename, GLuint &texture);//调8位贴图
	//*/

public:
public:
public:
public:
public:


};

