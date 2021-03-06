#include"stdafx.h"
#include "GraphPlot.h"



CGraphPlot::CGraphPlot()
{
	g_eye[0] = MAP;//
	g_eye[2] = -MAP;//
	g_Angle = 0;//方位角
	g_elev = 0;//俯仰角
	g_text = gluNewQuadric();
	LoadT8("aa.BMP", g_cactus[0]);//飞机帖图
	LoadT8("bb.BMP", g_cactus[1]);//飞机帖图
}


CGraphPlot::~CGraphPlot()
{
}

///////////////////////////////////////////////////////////////
//*
void CGraphPlot::light0()
{
	GLfloat light_position[] = { 1.0,10.0,-51.0,10.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
}
BOOL CGraphPlot::DisplayScene()//摄像机
{
	float speed = 0.2f;							//步长
	if (KEY_DOWN(VK_SHIFT))  speed = speed * 4;//按SHIFT时的加速
	if (KEY_DOWN(VK_LEFT))   g_Angle -= speed * 2;//左转
	if (KEY_DOWN(VK_RIGHT))  g_Angle += speed * 2;//右转
	rad_xz = float(3.13149* g_Angle / 180.0f);	//计算左右旋转角度
	if (KEY_DOWN(33)) g_elev += 0.2f;	//Page UP  键
	if (KEY_DOWN(34)) g_elev -= 0.2f;	//Page Down键
	if (g_elev<-100)	g_elev = -100;	//仰俯角
	if (g_elev> 100)	g_elev = 100;	//仰俯角
	if (KEY_DOWN(VK_UP))				//前进
	{
		g_eye[2] += sin(rad_xz)*speed;
		g_eye[0] += cos(rad_xz)*speed;
	}
	if (KEY_DOWN(VK_DOWN))			//后退
	{
		g_eye[2] -= sin(rad_xz)*speed;
		g_eye[0] -= cos(rad_xz)*speed;
	}
	//控制到摄像机不离开地面
	/*  if(g_eye[0]<  MAP_SCALE*2)		 g_eye[0]=  MAP_SCALE*2;
	if(g_eye[0]> (MAP_W-3)*MAP_SCALE) g_eye[0]= (MAP_W-3)*MAP_SCALE;
	if(g_eye[2]<-(MAP_W-3)*MAP_SCALE) g_eye[2]=-(MAP_W-3)*MAP_SCALE;
	if(g_eye[2]> -MAP_SCALE*2)		 g_eye[2]= -MAP_SCALE*2;*/
	if (g_eye[0]<-(MAP * 2 - 20))	g_eye[0] = -(MAP * 2 - 20); //视点的X分量限制
	if (g_eye[0]> (MAP * 2 - 20))	g_eye[0] = (MAP * 2 - 20);
	if (g_eye[2]<-(MAP * 2 - 20))	g_eye[2] = -(MAP * 2 - 20); //视点的Z分量限制
	if (g_eye[2]> (MAP * 2 - 20))	g_eye[2] = (MAP * 2 - 20);
	g_eye[1] = 1.8;//设置摄像机对地位置高
				   //摄像机的方向
	g_look[0] = float(g_eye[0] + 100 * cos(rad_xz));
	g_look[2] = float(g_eye[2] + 100 * sin(rad_xz));
	g_look[1] = g_eye[1];
	//建立modelview矩阵方向
	gluLookAt(g_eye[0], g_eye[1], g_eye[2], g_look[0], g_look[1] + g_elev, g_look[2], 0.0, 1.0, 0.0);
	return TRUE;
}
GLvoid CGraphPlot::DrawGround()//篮色网格地面线
{
	glPushAttrib(GL_CURRENT_BIT);//保存现有颜色属实性
	glEnable(GL_BLEND);//使用纹理
	glPushMatrix();
	glColor3f(0.5f, 0.7f, 1.0f);//设置蓝色
	glTranslatef(0, 0.0f, 0);		//平台的定位
	int size0 = (int)(MAP * 2);
	glBegin(GL_LINES);//划一界线
	for (int x = -size0; x < size0;x += 4)
	{
		glVertex3i(x, 0, -size0); glVertex3i(x, 0, size0);
	}
	for (int z = -size0; z < size0;z += 4)
	{
		glVertex3i(-size0, 0, z); glVertex3i(size0, 0, z);
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
	glPopAttrib();//恢复前一属性
}
//==========================================================================
void CGraphPlot::picter(float x, float y, float z)//组合图形
{
	glPushAttrib(GL_CURRENT_BIT);//保存现有颜色属实性
	glPushMatrix();//平台==============================
	glTranslatef(x, y + 0.5f, z);		//平台的定位
	glColor3f(0.0f, 1.0f, 0.2f);		//绿色
	auxSolidCube(1);				//方台(边长)
	glTranslatef(0.0f, 0.8f, 0.0f);	//架的位置调整,上升0.8
	glColor3f(0.0f, 0.0f, 1.0f);		//蓝色
	auxSolidBox(.2f, 1.3f, .2f);		//长方架(宽、高、长)
	glPopMatrix();
	glPushMatrix();//雷达==============================
	glTranslatef(x, y + 2.5f, z);		//雷达的定位1
	glRotatef(r - 90, 0.0, 1.0, 0.0);	//雷达旋转2
										//=======================================
	glColor3f(1.0f, 1.0f, 1.0f);		//白色
	glRotatef(45, 1.0, 0.0, 0.0);	//盘的角度调整，仰30度
	auxWireCone(1.5, 0.6f);			//线园锥盘(底半径、高)
									//=======================================
	glRotatef(180, 1.0, 0.0, 0.0);	//杆的角度调整,反方向转
	glTranslatef(0.0f, 0.0f, -0.7f);  //杆的位置调整,缩进一点
	auxWireCone(0.2f, 2.0f);			//园锥杆(底半径、高)
	glColor3f(FRAND, 0, 0);			//随机红色
	glTranslatef(0.0f, 0.0f, 2.0f);	//杆的位置调整,缩进一点
	auxSolidSphere(0.1f);			//园(半径)
	glPopMatrix();
	/* glPushMatrix();//火箭=============================
	glTranslatef(x,y+10.0f,z);//火箭的定位
	glRotatef(r, 0.0, 1.0, 0.0);	//火箭的旋转
	glTranslatef(x/15,0,0);//火箭的定位
	//=============================================
	glColor3f(1.0f,0.0f,0.0f);		//红色
	glRotatef(180, 0.0, 1.0, 0.0);	//角度调整,与雷达平行，箭头朝前
	auxSolidCone(.2,0.6);			//园锥(底半径、高)
	//=============================================
	glColor3f(1.0f,1.0f,1.0f);		//白色
	glRotatef(90, 1.0, 0.0, 0.0);	//角度调整,与火箭头对接
	glTranslatef(0.0f,-1.0f,0);		//位置调整,与火箭头对接
	auxSolidCylinder(.2f,1);		//园柱(半径、高)
	glRotatef(-270, 1.0, 0.0, 0.0);
	glColor3f(FRAND+.6f,0.2f,0.0f);	//随机色
	glTranslatef(0.0f,-0.0f,-0.2f); //位置调整,缩进一点
	auxSolidCone(.2,1.5);			//园锥(底半径、高)
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);*/
	glPopAttrib();//恢复前一属性
	r += 0.1f;if (r>360) r = 0;

}
void CGraphPlot::airplane(float x, float y, float z)//组合飞机
{
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
	Box(1.0, 0.05f, 0.3f);				//后翼
	glTranslatef(0.0f, 0.1f, 0.0f);	//位置调整
	Box(0.05f, 0.6f, 0.30f);			//后垂翼
										//======================================================
	glTranslatef(0.0f, 0.7f, -1.9f);	//位置调整
	Box(3, 0.05f, 0.5f);				//前翼
										//======================================================
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void CGraphPlot::Box(float x, float y, float z)
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
bool CGraphPlot::LoadT8(char *filename, GLuint &texture)//调8位贴图
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