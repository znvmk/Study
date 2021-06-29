#include "stdafx.h"
#include "GraphDraw.h"





CGraphDraw::CGraphDraw()
{
	a = b = 5;
	c = 1;


	m_nSelect = 0;

	r = 0;

	g_text = gluNewQuadric();
	LoadT8("aa.BMP", g_cactus[0]);//帖图
	LoadT8("bb.BMP", g_cactus[1]);//帖图
	//LoadTGATexture()

	numtest = 0;

	m_tgawr.LoadTGA(&texture[0], _T("F:\\znpop\\xmbb.tga"));

	
		
}


CGraphDraw::~CGraphDraw()
{
}



BEGIN_MESSAGE_MAP(CGraphDraw, CWnd)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()




void CGraphDraw::GLDraw(int select)
{
	m_nSelect = select;

	switch (select)
	{
	case 0:;break;
	
	default:break;
	}
	

	
	//picter(4, -4, -10);					//显示组合图形
	//if(numtest==1) airplane(0, 8, -50);					//组合飞机

	//TextureDraw();
	
	Textureaa();
}


void CGraphDraw::light0(float x, float y, float z, float a)//光
{
	GLfloat light_position[] = { x,y,z,a };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
}

void CGraphDraw::airplane(float x, float y, float z)//组合飞机
{
	r += 1;if (r>360) r = 0;
	glPushMatrix();//压入堆栈
	glTranslatef(x, y, z);//飞机的定位
	glRotatef(-r, 0.0, 1.0, 0.0);//飞机的旋转
	glTranslatef(30, 0, 0);		 //飞机的旋转半径
	glRotatef(30, 0.0, 0.0, 1.0);//飞机的倾斜
								 //=============================================
	glPushMatrix();//
	glRotatef(-r * 30, 0.0, 0.0, 1.0);//飞机的旋转
	glColor3f(0.0, 0.0, 1.0);
	Box(1.0f, 0.1f, 0.02f);		//方，螺旋浆	
	glPopMatrix();
	glColor3f(1.0, 1.0, 1.0);		//白色
	glEnable(GL_TEXTURE_2D);		//使用纹理
	glBindTexture(GL_TEXTURE_2D, g_cactus[1]);//
	glTranslatef(0.0f, 0.0f, -0.5f);	//后移
	gluSphere(g_text, 0.4f, 8, 8);  //机头园(半径)
									//=============================================
	glTranslatef(0.0f, -0.0f, -2);	//位置调整,与机头对接
	gluCylinder(g_text, 0.4, 0.4, 2.0, 8, 4);//机身,园柱(半径、高)
											 //=====================================================
	glRotatef(-180, 1.0, 0.0, 0.0); //角度调整
	glTranslatef(0.0f, -0.0f, 0.0f);	//位置调整,缩进一点		
	gluCylinder(g_text, 0.4, 0.1, 1.5, 8, 4);//机尾,园锥(底半径、高)
											 //======================================================
	glBindTexture(GL_TEXTURE_2D, g_cactus[0]);//
	glTranslatef(0.0f, -0.8f, 1.2f);	//位置调整
	Box(1.0, 0.05f, 0.3f);			//后翼
	glTranslatef(0.0f, 0.1f, 0.0f);	//位置调整
	Box(0.05f, 0.6f, 0.30f);			//后垂翼
										//======================================================
	glTranslatef(0.0f, 0.7f, -1.9f);	//位置调整
	Box(3, 0.05f, 0.5f);				//前翼
										//======================================================
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void CGraphDraw::Box(float x, float y, float z)
{
	glPushMatrix();//压入堆栈
	glScalef(x, y, z);
	glEnable(GL_TEXTURE_2D);		//使用纹理
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);// 前
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// 后
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);// 上
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// 下
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);// 左
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// 右
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void CGraphDraw::picter(float x, float y, float z)//组合图形
{
	r += 1;if (r>360) r = 0;
	glPushAttrib(GL_CURRENT_BIT);//保存现有颜色属实性
	glPushMatrix();//平台==============================
	glTranslatef(x, y + 0.5f, z);		//平台的定位
	glColor3f(0.0f, 1.0f, 0.2f);		//绿色
	//auxSolidCube(1);				//方台(边长)
	glutSolidCube(1);
	glTranslatef(0.0f, 0.8f, 0.0f);	//架的位置调整,上升0.8
	glColor3f(0.0f, 0.0f, 1.0f);		//蓝色
	//auxSolidBox(.2f, 1.3f, .2f);		//长方架(宽、高、长)
	
	glPopMatrix();
	glPushMatrix();//雷达==============================
	glTranslatef(x, y + 2.5f, z);		//雷达的定位1
	glRotatef(-r, 0.0, 1.0, 0.0);	//雷达旋转2
										//=======================================
	glColor3f(1.0f, 1.0f, 1.0f);		//白色
	glRotatef(45, 1.0, 0.0, 0.0);	//盘的角度调整，仰30度
	//auxWireCone(1.5, 0.6f);			//线园锥盘(底半径、高)
	glutSolidCone(1.5,0.6f,50,50);				

	//=======================================
	glRotatef(180, 1.0, 0.0, 0.0);	//杆的角度调整,反方向转
	glTranslatef(0.0f, 0.0f, -0.7f);  //杆的位置调整,缩进一点
	//auxWireCone(0.2f, 2.0f);			//园锥杆(底半径、高)
	glutSolidCone(0.2, 2.0f, 50, 50);

	glColor3f(FRAND, 0, 0);			//随机红色
	glTranslatef(0.0f, 0.0f, 2.0f);	//杆的位置调整,缩进一点
	//auxSolidSphere(0.1f);			//园(半径)
	glutSolidSphere(0.1f,50,50);

	glPopMatrix();

	glPushMatrix();//火箭=============================
	glTranslatef(x, y+7.0f , z);		//火箭的定位
	glRotatef(-r, 0.0, 1.0, 0.0);	//火箭的旋转
	glTranslatef(15, 0, 0);			//火箭的定位
									//=============================================
	glColor3f(1.0f, 0.0f, 0.0f);		//红色
	//glRotatef(180, 0.0, 1.0, 0.0);	//角度调整,与雷达平行，箭头朝前
	//auxSolidCone(.2, 0.6);			//园锥(底半径、高)
	glutSolidCone(0.2, 0.6f, 50, 50);							
	//=============================================
	glColor3f(1.0f, 1.0f, 1.0f);		//白色
	glRotatef(90, 1.0, 0.0, 0.0);	//角度调整,与火箭头对接
	glTranslatef(0.0f, -1.0f, 0);		//位置调整,与火箭头对接
	//auxSolidCylinder(.2f, 1);		//园柱(半径、高)
	//glScalef(6.0f, 6.0f, 6.0f);//x,y,z轴均放大6倍  
	//glutWireDodecahedron();
	glutSolidCube(0.3);
	glRotatef(-270, 1.0, 0.0, 0.0);
	glColor3f(FRAND + .6f, 0.2f, 0.0f);	//随机色
	glTranslatef(0.0f, -0.0f, -0.2f); //位置调整,缩进一点
	//auxSolidCone(.2, 1.5);			//园锥(底半径、高)
	glutSolidCone(0.2, 1.5f, 50, 50);
	glPopMatrix();
	glPopAttrib();//恢复前一属性
	
}

bool CGraphDraw::LoadT8(char *filename, GLuint &texture)//调8位贴图
{
	AUX_RGBImageRec *pImage = NULL;


	WCHAR wfilename[256];
	memset(wfilename, 0, sizeof(wfilename));
	MultiByteToWideChar(CP_ACP, 0, filename, strlen(filename) + 1, wfilename, sizeof(wfilename) / sizeof(wfilename[0]));

	pImage = auxDIBImageLoad(wfilename);			// 装入位图	



	if (pImage == NULL)		return false;		// 确保位图数据已经装入
	glGenTextures(1, &texture);					// 生成纹理
	glBindTexture(GL_TEXTURE_2D, texture);	// 捆绑纹理
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, pImage->sizeX,
		pImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
	free(pImage->data);	//释放位图占据的内存资源
	free(pImage);
	return true;// 返回true
}

void CGraphDraw::TextureDraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);

	glBegin(GL_QUADS);
	// Front Face   
	// Bottom Left Of The Texture and Quad   
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	// Bottom Right Of The Texture and Quad   
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	// Top Right Of The Texture and Quad   
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	// Top Left Of The Texture and Quad   
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);
	glBegin(GL_QUADS);
	// Back Face   
	// Bottom Right Of The Texture and Quad   
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	// Top Right Of The Texture and Quad   
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	// Top Left Of The Texture and Quad   
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	// Bottom Left Of The Texture and Quad   
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);
	glBegin(GL_QUADS);
	// Top Face   
	// Top Left Of The Texture and Quad   
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	// Bottom Left Of The Texture and Quad   
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	// Bottom Right Of The Texture and Quad   
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	// Top Right Of The Texture and Quad   
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);
	glBegin(GL_QUADS);
	// Bottom Face   
	// Top Right Of The Texture and Quad   
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	// Top Left Of The Texture and Quad   
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	// Bottom Left Of The Texture and Quad   
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	// Bottom Right Of The Texture and Quad   
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);
	glBegin(GL_QUADS);
	// Right face   
	// Bottom Right Of The Texture and Quad   
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	// Top Right Of The Texture and Quad   
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	// Top Left Of The Texture and Quad   
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	// Bottom Left Of The Texture and Quad   
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);
	glBegin(GL_QUADS);
	// Left Face   
	// Bottom Left Of The Texture and Quad   
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	// Bottom Right Of The Texture and Quad   
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	// Top Right Of The Texture and Quad   
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	// Top Left Of The Texture and Quad   
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
}

void CGraphDraw::Textureaa()
{
	m_tgawr.zTexture2D(texture, 0);

	glBegin(GL_QUADS);
	
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();

	
	glBegin(GL_QUADS);
	
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	
	glBegin(GL_QUADS);
	
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();

	
	glBegin(GL_QUADS);
	
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	
	glBegin(GL_QUADS);
	
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	
	glBegin(GL_QUADS);
	
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}