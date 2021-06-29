#include "stdafx.h"
#include "GraphDraw.h"





CGraphDraw::CGraphDraw()
{
	a = b = 0;
	c = 0;


	m_nSelect = 0;

	m_nViewSelect = 2;

	r = 0;

	g_text = gluNewQuadric();
	
	//LoadTGATexture()




	g_eye[0] = MAP;//
	g_eye[2] = -MAP;//

	g_eye[0] = 0;//
	g_eye[2] =5;//
	g_Angle = 0;//
	g_elev = -0;//360;//
	
	gao = -50;


	g_eye[1] = gao;


	m_keyleft=m_keyright=m_keydown = m_keyup = m_keyshift = m_keypagedown = m_keypageup = m_lbuttondown = m_rbuttondown =m_mousemove = m_keyP =0;

	m_BoxSize = 100;
	m_BoxBottomHeightMax = 5;
	//m_BoxBottomHeight[10][10] = 10;
	//m_BoxBottomHeight[50][50] = 10;
	/*
	for(int i=0;i<m_BoxSize;i++)
		for (int j = 0;j < m_BoxSize;j++)
		{
			GLfloat temp,temprand;
			temp = temprand = 0;
			while (1)
			{
				temprand = GLfloat(rand() % m_BoxBottomHeightMax);
				temprand /= 10;
				temp = temprand - m_BoxBottomHeight[i][j];
				if (temp < 0)temp = -temp;
				if (temp < 0.2)
				{
					m_BoxBottomHeight[i][j] = temp;
					break;
				}
				
			}
			
		}
	*/
	m_tgawr.LoadTGA(&texture[0], _T("E:\\data\\data\\pictrues\\tga\\airbox\\4front.tga"));
	//*
	m_tgawr.LoadTGA(&texture[1], _T("E:\\data\\data\\pictrues\\tga\\airbox\\4back.tga"));
	m_tgawr.LoadTGA(&texture[2], _T("E:\\data\\data\\pictrues\\tga\\airbox\\4left.tga"));
	m_tgawr.LoadTGA(&texture[3], _T("E:\\data\\data\\pictrues\\tga\\airbox\\4right.tga"));
	m_tgawr.LoadTGA(&texture[4], _T("E:\\data\\data\\pictrues\\tga\\airbox\\4top.tga"));
	m_tgawr.LoadTGA(&texture[5], _T("E:\\data\\data\\pictrues\\tga\\sands\\sand0.tga"));
	m_tgawr.LoadTGA(&texture[6], _T("E:\\data\\data\\pictrues\\tga\\map\\map1.tga"));
	m_tgawr.LoadTGA(&texture[7] , _T("E:\\data\\data\\pictrues\\tga\\map\\baidumap1_1.tga"));
	//m_tgawr.LoadTGA(&texture[6], _T("E:\\data\\data\\pictrues\\tga\\map\\sand1.tga"));
	
	/*
	m_tgawr.LoadTGA(&texture[7], _T("E:\\data\\data\\pictrues\\tga\\airbox\\4left.tga"));
	m_tgawr.LoadTGA(&texture[8], _T("E:\\data\\data\\pictrues\\tga\\airbox\\4left.tga"));
	m_tgawr.LoadTGA(&texture[9], _T("E:\\data\\data\\pictrues\\tga\\airbox\\4left.tga"));
	m_tgawr.LoadTGA(&texture[10], _T("E:\\data\\data\\pictrues\\tga\\airbox\\4left.tga"));
	m_tgawr.LoadTGA(&texture[11], _T("E:\\data\\data\\pictrues\\tga\\airbox\\4left.tga"));
	m_tgawr.LoadTGA(&texture[12], _T("E:\\data\\data\\pictrues\\tga\\airbox\\4left.tga"));
	m_tgawr.LoadTGA(&texture[13], _T("E:\\data\\data\\pictrues\\tga\\airbox\\4left.tga"));
	m_tgawr.LoadTGA(&texture[14], _T("E:\\data\\data\\pictrues\\tga\\airbox\\4left.tga"));
	m_tgawr.LoadTGA(&texture[15], _T("E:\\data\\data\\pictrues\\tga\\airbox\\4left.tga"));
	m_tgawr.LoadTGA(&texture[16], _T("E:\\data\\data\\pictrues\\tga\\airbox\\4left.tga"));
	//*/
	//InitTerrain(5);//初始化地面


	x2D = 10.0f;
	y2D = 10.0f;
	z2D = -13.0f;


	m_fAngelX = m_fAngelY = m_fAngelZ = 0.0f;
	m_fPosX = 40;
	m_fPosY = -52;
	m_fPosZ = -70;
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


	if (m_nViewSelect == 2)
	{
		ViewSelect2D();
	}
	else
		if (m_nViewSelect == 3)
		{
			ViewSelect3D();
		}
			
	
	

}


void CGraphDraw::light0()//光
{
	GLfloat light_position[] = { 1.0,5.0,1.0,1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
}

void CGraphDraw::ViewSelect2D()
{
	DisplayScene2D();
	//Textureaa();
}


void CGraphDraw::ViewSelect3D()
{
	DisplayScene3D();						 // 摄像机
											 //airplane(0, 8, -50);					//组合飞机
	airplane(MAP , 0 , -MAP);					//组合飞机
												//TextureDraw();

												//Textureaa();


														
												//DrawSand();							 // 显示随机山势
	CreateSkyBox(3 , 6 , 3 , 6);				 // 显示天

	picter(MAP + 10 , -52 , -MAP);				//显示组合图形

												//DrawGround();

	DrawPipleNet();

	//DrawMap();
	DrawBottom();
}


BOOL CGraphDraw::DisplayScene2D()
{
	m_tgawr.zTexture2D(texture , 7);
	glEnable(GL_TEXTURE_2D);

	
	

	if (m_keyleft&&x2D>5)x2D--;
    if (m_keyright&&x2D<15)x2D++;
	if (m_keydown&&y2D>5)y2D--;
	if (m_keyup&&y2D<15)y2D++;
	
	if (m_keypageup&&z2D<-5)z2D++;
	if (m_keypagedown&&z2D>-13.0)z2D--;


	GLfloat x , y , z;
	x = x2D;
	y = y2D;
	z = z2D;


	glBegin(GL_QUADS);

	glTexCoord2f(0.0f , 0.0f); glVertex3f(x-20.0 , y - 20.0 , z);

	glTexCoord2f(1.0f , 0.0f); glVertex3f(x , y-20.0 , z);

	glTexCoord2f(1.0f , 1.0f); glVertex3f(x , y , z);

	glTexCoord2f(0.0f , 1.0f); glVertex3f(x-20.0 , y , z);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	return TRUE;
}


BOOL CGraphDraw::DisplayScene3D()//摄像漫游
{
	float speed = 5.0f;						//步长
	float x = g_eye[0], y = g_eye[2], z = g_eye[2];
	if (m_keyshift)  speed = speed * 2;//按SHIFT时的加速true
	if (m_keyleft)   g_Angle -= speed * 2;//左转,方位角-
	if (m_keyright)  g_Angle += speed * 2;//右转,方位角+
	rad_xz = float(3.141592653589793* g_Angle / 180.0f);	//计算左右旋转角度
	if (m_keypageup)	   g_elev += speed;	//Page UP  键
	if (m_keypagedown)		   g_elev -= speed;	//Page Down键
	if (g_elev<-360)		   g_elev = -360;	//仰俯角
	if (g_elev> 360)		   g_elev = 360;	//仰俯角
	if (m_keyup)						//前进
	{
		g_eye[2] += (float)sin(rad_xz)*speed;			//视点的x分量
		g_eye[0] += (float)cos(rad_xz)*speed;			//视点的Z分量
	}
	if (m_keydown)					//后退
	{
		g_eye[2] -= (float)sin(rad_xz)*speed;			//视点的x分量
		g_eye[0] -= (float)cos(rad_xz)*speed;			//视点的Z分量
	}
	//控制到摄像机不离开地面
	if (g_eye[0]<  MAP_SCALE)			g_eye[0] = MAP_SCALE;
	if (g_eye[0]> (MAP_W - 2)*MAP_SCALE)	g_eye[0] = (MAP_W - 2)*MAP_SCALE;
	if (g_eye[2]<-(MAP_W - 2)*MAP_SCALE)	g_eye[2] = -(MAP_W - 2)*MAP_SCALE;
	if (g_eye[2]> -MAP_SCALE)			g_eye[2] = -MAP_SCALE;
	//g_eye[1] = GetHeight((float)g_eye[0], (float)g_eye[2]) + gao;//设置摄像机对地位置高
	g_eye[1] = gao;//设置摄像机对地位置高
	
	//摄像机的方向
	g_look[0] = (float)(g_eye[0] + 100 * cos(rad_xz));	//目标点X分量
	g_look[2] = (float)(g_eye[2] + 100 * sin(rad_xz));	//目标点Z分量
	g_look[1] = g_eye[1] + g_elev;				//目标点Y分量
												//建立modelview矩阵方向
	//g_eye[0] = 0;g_eye[1] = 0;g_eye[2] = 5;g_look[0] = 0;g_look[1] = 0;g_look[2] = 0;
	gluLookAt(g_eye[0], g_eye[1], g_eye[2],		//视点
		g_look[0], g_look[1], g_look[2],	//目标点
		0.0, 1.0, 0.0						//视点方向
	);
	return TRUE;
}

void CGraphDraw::InitTerrain(float h)//建立地域数组
{
	int index = 0;
	int Vertex;
	for (int z = 0; z < MAP_W; z++)
		for (int x = 0; x < MAP_W; x++)
		{
			Vertex = z * MAP_W + x;
			//g_terrain[Vertex][0] = float(x)*MAP_SCALE;	//地域数据X分量
			//g_terrain[Vertex][1] = (float)(g_imageData[(z*MAP_W + x) * 3] / 3);//Y分量，山的高度
																			   //	  g_terrain [Vertex][1] = h + FRAND * h;		//Y分量，随机产生山的高度
			//g_terrain[Vertex][2] = -float(z)*MAP_SCALE;	//地域数据Z分量
			//g_texcoord[Vertex][0] = (float)x;			//索引数组x
			//g_texcoord[Vertex][1] = (float)z;				//索引数组z
			//g_index[index++] = Vertex;					//顶点数组1维
			//g_index[index++] = Vertex + MAP_W;

			g_terrain[Vertex][0] = x*MAP_SCALE;	//地域数据X分量
			//g_terrain[Vertex][1] = (float)(g_imageData[(z*MAP_W + x) * 3] / 3);//Y分量，山的高度
			g_terrain [Vertex][1] = h + FRAND * h;		//Y分量，随机产生山的高度
			g_terrain[Vertex][2] = -z*MAP_SCALE;	//地域数据Z分量
			g_texcoord[Vertex][0] = (float)x;			//索引数组x
			g_texcoord[Vertex][1] = (float)z;				//索引数组z
			g_index[index++] = Vertex;					//顶点数组1维
			g_index[index++] = Vertex + MAP_W;

		}
	glEnableClientState(GL_VERTEX_ARRAY);				//允许使用地域数组
	glVertexPointer(3, GL_FLOAT, 0, g_terrain);		//装入地域数据
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);		//允许使用索引数组
	glTexCoordPointer(2, GL_FLOAT, 0, g_texcoord);		//装入索引数组
}
void CGraphDraw::DrawSand()//显示随机山势
{
	//glGenTextures(1, &texture[0]);
	//glBindTexture(GL_TEXTURE_2D, g_cactus[5]);//地贴图
	//glBindTexture(GL_TEXTURE_2D, texture[5]);//地贴图
	m_tgawr.zTexture2D(texture, 5);		
	//glEnable(GL_TEXTURE_2D);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//放大采用线性滤波
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	for (int z = 0; z < MAP_W - 1; z++)
		glDrawElements(GL_TRIANGLE_STRIP, MAP_W * 2, GL_UNSIGNED_INT, &g_index[z*MAP_W * 2]);
	glDisable(GL_TEXTURE_2D);
	//显示由顶点数组指定的面。
}
float CGraphDraw::GetHeight(float x, float z)// 取地面高度
{
	float CameraX = x / MAP_SCALE;              //计算在那一块
	float CameraZ = -z / MAP_SCALE;              //计算在那一块
	int Col0 = int(CameraX);                  //块的列号
	int Row0 = int(CameraZ);                  //块的行号
	int Col1 = Col0 + 1;                      //相邻列
	int Row1 = Row0 + 1;                      //相邻行
	if (Col1 > MAP_W)	Col1 = 0;             //相邻列大于地块数，取首列
	if (Row1 > MAP_W)	Row1 = 0;             //相邻行大于地块数，取首行
	float h00 = g_terrain[Col0 + Row0*MAP_W][1];//获取块四角的高度
	float h01 = g_terrain[Col1 + Row0*MAP_W][1];
	float h11 = g_terrain[Col1 + Row1*MAP_W][1];
	float h10 = g_terrain[Col0 + Row1*MAP_W][1];
	float tx = CameraX - int(CameraX);         //求块内X偏移位置
	float ty = CameraZ - int(CameraZ);         //求块内Z偏移位置
	float txty = tx * ty;                     //以下为双线性插值(内插)计算
	return h00*(1.0f - ty - tx + txty)
		+ h01*(tx - txty)
		+ h11*txty
		+ h10*(ty - txty);                  //返回插值计算值，为所求点的高度。
}
void CGraphDraw::CreateSkyBox(int a, int wi, int he, int le)//显示天空
{
	float width = MAP*wi;		// 天空盒宽
	float height = MAP*he;		// 天空盒高
	float length = MAP*le;		// 天空盒长
	float x = MAP - width / 2;	// 天空的位置x
	float y = MAP / a - height / 2;	// 天空的位置y
	float z = -MAP - length / 2;	// 天空的位置z
									///////////////////////////////////////////////////////////////////////////////
	m_tgawr.zTexture2D(texture, 2);		// 设置BACK贴图左
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);			// 多组独立填充四边形	
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	m_tgawr.zTexture2D(texture, 3);		// 设置FRONT贴图右
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);			// 多组独立填充四边形
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	m_tgawr.zTexture2D(texture, 4);		// 设置TOP贴图顶
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);			// 多组独立填充四边形		
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	m_tgawr.zTexture2D(texture, 0);		// 设置LEFT贴图前
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);			// 多组独立填充四边形
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	m_tgawr.zTexture2D(texture, 1);		// 设置RIGHT贴图后
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);			// 多组独立填充四边形		
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

GLvoid CGraphDraw::DrawGround()//篮色网格地面线
{
	glPushAttrib(GL_CURRENT_BIT);//保存现有颜色属实性
	glEnable(GL_BLEND);//使用纹理
	glPushMatrix();
	glColor3f(0.5f, 0.7f, 1.0f);//设置蓝色
	glTranslatef(0, 0.0f, 0);		//平台的定位
	int size0 = (int)(MAP * 2);
	glBegin(GL_LINES);//划一界线
	int bottom;
	bottom = 0;
	for (int x = -size0; x < size0;x += 4)
	{
		glVertex3i(x, bottom, -size0); glVertex3i(x, bottom, size0);
	}
	for (int z = -size0; z < size0;z += 4)
	{
		glVertex3i(-size0, bottom, z); glVertex3i(size0, bottom, z);
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
	glPopAttrib();//恢复前一属性
}


void CGraphDraw::DrawMap()
{
	float size = (float)(MAP * 2);
	size = 10.0f;
	float bottom;
	bottom = 20.0f;

	glTranslatef(0, 0.0f, 0);		//平台的定位

	glDisable(GL_TEXTURE_2D);
	m_tgawr.zTexture2D(texture,6);
	/*
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -bottom, -size);

	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, -bottom, size);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, bottom, size);

	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, bottom, -size);
	glEnd();
	*/
	/*
	float a;
	a = 10;
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, -a, -a);

	glTexCoord2f(0.0f, 1.0f); glVertex3f(-a, -a, a);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(-a, a, a);

	glTexCoord2f(1.0f, 0.0f); glVertex3f(-a, a, -a);
	glEnd();
	*/
	//MAP=384,width=2304,height=1152,length=2304,x=-768,y=-384,z=-1536
	//float wi, he, le, a;
	//he = a = 3;wi = le = 6;
	//glDisable(GL_TEXTURE_2D);float width = MAP*wi;		// 天空盒宽
	//float height = MAP*he;		// 天空盒高
	//float length = MAP*le;		// 天空盒长
	//float x = MAP - width / 2;	// 天空的位置x
	//float y = MAP / a - height / 2;	// 天空的位置y
	//float z = -MAP - length / 2;	// 天空的位置z

	
	float width , height , length , x , y , z ;
	width = 2304; height = 1152; length = 2304; x = -768; y = -384; z = -1536;
	y = -80;


	//glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);			// 多组独立填充四边形		
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y , z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y , z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y , z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
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





void CGraphDraw::Textureaa()
{
	m_tgawr.zTexture2D(texture, 0);
	glEnable(GL_TEXTURE_2D);
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


void CGraphDraw::DrawBottom()
{
	m_tgawr.zTexture2D(texture, 5);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	
	int length,width;
	length = width = m_BoxSize-1;
	GLfloat bottomheight = 0;
	GLfloat microSquare = 0.5;
	GLfloat posX, posY,posZ;

	/*
	for(int i=0;i<length;i++)
		for (int j = 0;j < width;j++)
		{
			bottomheight = m_BoxBottomHeight[i][j];

			posX = microSquare*(GLfloat)i;
			posY = microSquare*(GLfloat)j;

			if (i < 100 && j < 100)
			{
				//底面
				glBegin(GL_QUADS);

				glTexCoord2f(0.0f, 0.0f); glVertex3f(posX, posY, m_BoxBottomHeight[i][j]);

				glTexCoord2f(0.0f, 1.0f); glVertex3f(posX, posY + microSquare, m_BoxBottomHeight[i][j + 1]);

				glTexCoord2f(1.0f, 1.0f); glVertex3f(posX + microSquare, posY + microSquare, m_BoxBottomHeight[i + 1][j + 1]);

				glTexCoord2f(1.0f, 0.0f); glVertex3f(posX + microSquare, posY, m_BoxBottomHeight[i + 1][j]);
				glEnd();
			}
			
		}
	//*/
	//bottomheight = -1536;
	microSquare = 50;
	length = 2304;
	width = 2304;
	posY = -60;
	//posY = -70;


	for (int i = 0;i<50;i++)
		for (int j = 0;j <50 ;j++)
		{
			//bottomheight = m_BoxBottomHeight[i][j];

			posX = microSquare*(GLfloat)i-1000;
			posZ = microSquare*(GLfloat)j-1536;
			//posX = microSquare;
			//posZ = microSquare-1536;
			//if (i != 25 && j != 25)
			{
				//底面
				glBegin(GL_QUADS);

				glTexCoord2f(1.0f , 1.0f); glVertex3f(posX + microSquare , posY , posZ);

				glTexCoord2f(0.0f , 1.0f); glVertex3f(posX + microSquare , posY , posZ + microSquare);

				glTexCoord2f(0.0f , 0.0f); glVertex3f(posX  , posY  , posZ + microSquare);

				glTexCoord2f(1.0f , 0.0f); glVertex3f(posX  , posY , posZ);
				glEnd();
			}


		}

	/*
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -1.0f);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 0.0f, -1.0f);

	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();
	
	*/

	glDisable(GL_TEXTURE_2D);
}

















void CGraphDraw::InitLightParameter()
{
	m_lightAmb[0] = 1.0f;m_lightAmb[1] = 0.2f;m_lightAmb[2] = 0.2f;m_lightAmb[3] = 1.0f;
	m_lightDif[0] = 1.0f;m_lightDif[1] = 1.0f;m_lightDif[2] = 0.3f;m_lightDif[3] = 1.0f;
	m_lightSpe[0] = 1.0f;m_lightSpe[1] = 1.0f;m_lightSpe[2] = 1.0f;m_lightSpe[3] = 1.0f;
	m_lightPos[0] = 1.0f;m_lightPos[1] = 1.0f;m_lightPos[2] = 1.0f;m_lightPos[3] = 0.0f;
}

void CGraphDraw::InitMatrialParameter(int s)
{
	/*
	m_materialAmb[0] = 1.0f;m_materialAmb[1] = 0.2f;m_materialAmb[2] = 0.2f;m_materialAmb[3] = 1.0f;
	m_materialDif[0] = 1.0f;m_materialDif[1] = 1.0f;m_materialDif[2] = 0.3f;m_materialDif[3] = 1.0f;
	m_materialSpe[0] = 1.0f;m_materialSpe[1] = 1.0f;m_materialSpe[2] = 1.0f;m_materialSpe[3] = 1.0f;
	m_materialPos[0] = 1.0f;m_materialPos[1] = 1.0f;m_materialPos[2] = 1.0f;m_materialPos[3] = 0.0f;
	m_materialShininess[0] = 10.0f;m_materialShininess[1] = 10.0f;m_materialShininess[2] = 0.0f;m_materialShininess[3] = 10.0f;
	*/
	switch (s)
	{
	case 0:
	{
		//金//铬
		m_materialAmb[0] = 0.25f;m_materialAmb[1] = 0.25f;m_materialAmb[2] = 0.25f;m_materialAmb[3] = 1.0f;
		m_materialDif[0] = 0.4f;m_materialDif[1] = 0.4f;m_materialDif[2] = 0.4f;m_materialDif[3] = 1.0f;
		m_materialSpe[0] = 0.774597f;m_materialSpe[1] = 0.774597f;m_materialSpe[2] = 0.774597f;m_materialSpe[3] = 0.774597f;
		m_materialPos[0] = 1.0f;m_materialPos[1] = 1.0f;m_materialPos[2] = 1.0f;m_materialPos[3] = 0.0f;
		m_materialShininess[0] = m_materialShininess[1] = m_materialShininess[2] = m_materialShininess[3] = 76.800003;

	}break;
	case 1:
	{
		//绿//金
		m_materialAmb[0] = 0.24725f;m_materialAmb[1] = 0.199500f;m_materialAmb[2] = 0.074500f;m_materialAmb[3] = 1.0f;
		m_materialDif[0] = 0.751640f;m_materialDif[1] = 0.606480f;m_materialDif[2] = 0.226480f;m_materialDif[3] = 1.0f;
		m_materialSpe[0] = 0.628281f;m_materialSpe[1] = 0.555802f;m_materialSpe[2] = 0.366065f;m_materialSpe[3] = 0.774597f;
		m_materialPos[0] = 1.0f;m_materialPos[1] = 1.0f;m_materialPos[2] = 1.0f;m_materialPos[3] = 0.0f;
		m_materialShininess[0] = m_materialShininess[1] = m_materialShininess[2] = m_materialShininess[3] = 51.200001f;
	}break;
	case 2:
	{
		//绿//银
		m_materialAmb[0] = 0.192250f;m_materialAmb[1] = 0.192250f;m_materialAmb[2] = 0.192250f;m_materialAmb[3] = 1.0f;
		m_materialDif[0] = 0.507540f;m_materialDif[1] = 0.507540f;m_materialDif[2] = 0.507540f;m_materialDif[3] = 1.0f;
		m_materialSpe[0] = 0.508273f;m_materialSpe[1] = 0.508273f;m_materialSpe[2] = 0.508273f;m_materialSpe[3] = 0.774597f;
		m_materialPos[0] = 1.0f;m_materialPos[1] = 1.0f;m_materialPos[2] = 1.0f;m_materialPos[3] = 0.0f;
		m_materialShininess[0] = m_materialShininess[1] = m_materialShininess[2] = m_materialShininess[3] = 51.200001f;
	}break;
	default:
	{
		//金//铬
		m_materialAmb[0] = 0.25f;m_materialAmb[1] = 0.25f;m_materialAmb[2] = 0.25f;m_materialAmb[3] = 1.0f;
		m_materialDif[0] = 0.4f;m_materialDif[1] = 0.4f;m_materialDif[2] = 0.4f;m_materialDif[3] = 1.0f;
		m_materialSpe[0] = 0.774597f;m_materialSpe[1] = 0.774597f;m_materialSpe[2] = 0.774597f;m_materialSpe[3] = 0.774597f;
		m_materialPos[0] = 1.0f;m_materialPos[1] = 1.0f;m_materialPos[2] = 1.0f;m_materialPos[3] = 0.0f;
		m_materialShininess[0] = m_materialShininess[1] = m_materialShininess[2] = m_materialShininess[3] = 76.800003;
	}
	}



}

void CGraphDraw::CreateLights()
{
	glLightfv(GL_LIGHT0 , GL_AMBIENT , m_lightAmb);
	glLightfv(GL_LIGHT0 , GL_DIFFUSE , m_lightDif);
	glLightfv(GL_LIGHT0 , GL_SPECULAR , m_lightSpe);
	glLightfv(GL_LIGHT0 , GL_POSITION , m_lightPos);


	glEnable(GL_LIGHTING);
	/*最多可创建8盏灯*/
	glEnable(GL_LIGHT0);

}

void CGraphDraw::CreateMaterial()
{
	glMaterialfv(GL_FRONT , GL_AMBIENT , m_materialAmb);
	glMaterialfv(GL_FRONT , GL_DIFFUSE , m_materialDif);
	glMaterialfv(GL_FRONT , GL_SPECULAR , m_materialSpe);
	glMaterialfv(GL_FRONT , GL_POSITION , m_materialPos);
	glMaterialfv(GL_FRONT , GL_SHININESS , m_materialShininess);
	glEnable(GL_COLOR_MATERIAL);

}






void CGraphDraw::DrawCylinder(GLfloat x , GLfloat y , GLfloat z)
{
	if (m_keydown)m_fAngelX -= 3;
	if (m_keyup)m_fAngelX += 3;
	if (m_keyleft)m_fAngelY -= 3;
	if (m_keyright)m_fAngelY += 3;


	InitLightParameter();
	InitMatrialParameter(2);

	CreateLights();
	CreateMaterial();


	GLUquadricObj* quadObj;
	/*圆柱*/
	glNewList(1 , GL_COMPILE);
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj , GLU_FILL);
	gluQuadricNormals(quadObj , GLU_SMOOTH);
	gluCylinder(quadObj , 0.3 , 0.3 , 0.8 , 16 , 16);
	glEndList();




	glPushAttrib(GL_CURRENT_BIT);//保存现有颜色属实性

	glPolygonMode(GL_FRONT_AND_BACK , GL_FILL);
	glLineWidth(1.5f);
	glColor3f(0.5f , 1.0f , 1.0f);




	glPushMatrix();//平台==============================
	glTranslatef(x , y + 0.5f , z);		//平台的定位


	glRotatef(-90.0f , 0.0f , 1.0f , 0.0f);
	glTranslatef(0.0f , 0.0f , 1.0f);
	glRotatef(m_fAngelX , 1.0f , 0.0f , 0.0f);
	glRotated(m_fAngelY , 0.0 , 1.0 , 0.0);
	glRotatef(m_fAngelZ , 0.0f , 0.0f , 1.0f);

	//glRotatef(r , 1 , 1 , 1);
	glScalef(0.3 , 0.3 , 3.0);
	glCallList(1);
	glPopMatrix();



	//接口
	glLoadIdentity();
	glPushMatrix();

	glRotatef(m_fAngelX , 1.0f , 0.0f , 0.0f);
	glRotated(m_fAngelY , 0.0 , 1.0 , 0.0);
	glRotatef(m_fAngelZ , 0.0f , 0.0f , 1.0f);

	glPushMatrix();
	glColor3f(0.5f , 0.0f , 1.0f);
	glTranslatef(0.0f , 0.0f , 0.0f);
	//glRotatef(m_fAngelX , 1.0f , 0.0f , 0.0f);
	//glRotated(m_fAngelY , 0.0 , 1.0 , 0.0);
	//glRotatef(m_fAngelZ , 0.0f , 0.0f , 1.0f);
	glScalef(0.1f , 0.1f , 1.0f);
	glCallList(1);
	glPopMatrix();

	//接口中间
	glPushMatrix();
	glColor3f(0.0f , 0.0f , 0.0f);
	//glTranslatef(0.0f , 0.0f , 0.0f);
	//glRotatef(0, 0.0f , 1.0f , 0.0f);
	//glRotatef(m_fAngelX , 1.0f , 0.0f , 0.0f);
	//glRotated(m_fAngelY-90 , 0.0 , 1.0 , 0.0);
	//glRotatef(m_fAngelZ , 0.0f , 0.0f , 1.0f);
	glScalef(0.1f , 0.1f , 0.1f);
	glCallList(1);
	glPopMatrix();
	glPopMatrix();
	glPopAttrib();

	/*
	glPushMatrix();
	glColor3f(0 , 1 , 0);
	glTranslatef(-2 , 2.0 , -12);
	glRotatef(r , 1 , 1 , 1);
	glScalef(0.3 , 0.3 , 10.0);
	Cylinder();
	glPopMatrix();

	glColor3f(0.0f , 0.0f , 1.0f);
	glRotatef(15 / 360.0*360.0 , 0.0f , 0.0f , -1.0f);
	glTranslatef(150 , 0.0f , 0.0f);
	glutSolidSphere(15.945 , 100 , 100);
	*/

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_COLOR_MATERIAL);
}


void CGraphDraw::DrawPiple(GLfloat x , GLfloat y , GLfloat z , int color)
{

	//InitLightParameter();
	//InitMatrialParameter(1);

	//CreateLights();
	//CreateMaterial();

	//glPolygonMode(GL_FRONT_AND_BACK , GL_FILL);
	//glLineWidth(1.5f);
	//glColor3f(0.5f , 1.0f , 1.0f);




	GLUquadricObj* quadObj;
	/*圆柱*/
	glNewList(1 , GL_COMPILE);
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj , GLU_FILL);
	gluQuadricNormals(quadObj , GLU_SMOOTH);
	gluCylinder(quadObj , 0.3 , 0.3 , 0.8 , 16 , 16);
	glEndList();



	glPushAttrib(GL_CURRENT_BIT);//保存现有颜色属实性

	glPolygonMode(GL_FRONT_AND_BACK , GL_FILL);
	glLineWidth(1.5f);

	if (color == 1)glColor3f(0.5f , 1.0f , 1.0f);
	if (color == 2)glColor3f(0.5f , 0.0f , 1.0f);
	if (color == 3)glColor3f(0.5f , 1.0f , 0.0f);

	glPushMatrix();//平台==============================

	glTranslatef(x , y , z);		//平台的定位

									//glColor3f(0.0f , 1.0f , 0.2f);		//绿色

	glRotatef(90 , 0.0 , 1.0 , 0.0);
	glScalef(1 , 1 , 80.0);
	glCallList(1);
	glPopMatrix();

	glPopAttrib();//恢复前一属性



}


void CGraphDraw::drawaaa()
{
	InitLightParameter();
	//InitMatrialParameter(1);

	CreateLights();

	glColor3f(0 , 1 , 1);

	///定义材质属性值
	float no_mat[] = { 0.0f , 0.0f , 0.0f , 1.0f };        // 无材质颜色
	float mat_ambient[] = { 0.7f , 0.7f , 0.7f , 1.0f };   // 环境颜色
	float mat_ambient_color[] = { 0.8f , 0.6f , 0.2f , 1.0f };
	float mat_diffuse[] = { 0.2f , 0.5f , 0.8f , 1.0f };   // 散射颜色
	float mat_specular[] = { 1.0f , 1.0f , 1.0f , 1.0f };  // 镜面反射颜色
	float no_shininess[] = { 0.0f };                    // 镜面反射指数为0
	float low_shininess[] = { 5.0f };                   // 镜面反射指数为5.0
	float high_shininess[] = { 100.0f };                // 镜面反射指数为100.0
	float mat_emission[] = { 0.3f , 0.2f , 0.3f , 0.0f };  // 发射光颜色

														   //清除缓存并重置单位矩阵


														   // 第一行第一列绘制的球仅有漫反射光而无环境光和镜面光。
	glPushMatrix();
	glScalef(1 , 1 , 1);
	glTranslatef(-2.0f , 1.5f , -7.0f);
	glMaterialfv(GL_FRONT , GL_AMBIENT , no_mat);
	glMaterialfv(GL_FRONT , GL_DIFFUSE , mat_diffuse);
	glMaterialfv(GL_FRONT , GL_SPECULAR , no_mat);
	glMaterialfv(GL_FRONT , GL_SHININESS , no_shininess);
	glMaterialfv(GL_FRONT , GL_EMISSION , no_mat);
	glutSolidSphere(0.5f , 30 , 30); //(0.3f);
	glPopMatrix();

	// 第一行第二列绘制的球有漫反射光和镜面光，并有低高光，而无环境光
	glPushMatrix();
	glScalef(1 , 1 , 1);
	glTranslatef(-0.5f , 1.5f , -7.0f);
	glMaterialfv(GL_FRONT , GL_AMBIENT , no_mat);
	glMaterialfv(GL_FRONT , GL_DIFFUSE , mat_diffuse);
	glMaterialfv(GL_FRONT , GL_SPECULAR , mat_specular);
	glMaterialfv(GL_FRONT , GL_SHININESS , low_shininess);
	glMaterialfv(GL_FRONT , GL_EMISSION , no_mat);
	glutSolidSphere(0.5f , 30 , 30); //(0.3f);
	glPopMatrix();

	// 第一行第三列绘制的球有漫反射光和镜面光，并有很亮的高光，而无环境光 。*/
	glPushMatrix();
	glScalef(1 , 1 , 1);
	glTranslatef(1.0f , 1.5f , -7.0f);
	glMaterialfv(GL_FRONT , GL_AMBIENT , no_mat);
	glMaterialfv(GL_FRONT , GL_DIFFUSE , mat_diffuse);
	glMaterialfv(GL_FRONT , GL_SPECULAR , mat_specular);
	glMaterialfv(GL_FRONT , GL_SHININESS , high_shininess);
	glMaterialfv(GL_FRONT , GL_EMISSION , no_mat);
	glutSolidSphere(0.5f , 30 , 30); //(0.3f);
	glPopMatrix();

	// 第一行第四列绘制的球有漫反射光和辐射光，而无环境和镜面反射光。*/
	glPushMatrix();
	glScalef(1 , 1 , 1);
	glTranslatef(2.5f , 1.5f , -7.0f);
	glMaterialfv(GL_FRONT , GL_AMBIENT , no_mat);
	glMaterialfv(GL_FRONT , GL_DIFFUSE , mat_diffuse);
	glMaterialfv(GL_FRONT , GL_SPECULAR , no_mat);
	glMaterialfv(GL_FRONT , GL_SHININESS , no_shininess);
	glMaterialfv(GL_FRONT , GL_EMISSION , mat_emission);
	glutSolidSphere(0.5f , 30 , 30); //(0.3f);
	glPopMatrix();




	// 第二行第一列绘制的球有漫反射光和环境光，而镜面反射光。*/
	glPushMatrix();
	glScalef(1 , 1 , 1);
	glTranslatef(-2.0f , 0.5f , -7.0f);
	glMaterialfv(GL_FRONT , GL_AMBIENT , mat_ambient);
	glMaterialfv(GL_FRONT , GL_DIFFUSE , mat_diffuse);
	glMaterialfv(GL_FRONT , GL_SPECULAR , no_mat);
	glMaterialfv(GL_FRONT , GL_SHININESS , no_shininess);
	glMaterialfv(GL_FRONT , GL_EMISSION , no_mat);
	glutSolidSphere(0.5f , 30 , 30); //(0.3f);
	glPopMatrix();

	// 第二行第二列绘制的球有漫反射光、环境光和镜面光，且有低高光。*/
	glPushMatrix();
	glScalef(1 , 1 , 1);
	glTranslatef(-0.5f , 0.5f , -7.0f);
	glMaterialfv(GL_FRONT , GL_AMBIENT , mat_ambient);
	glMaterialfv(GL_FRONT , GL_DIFFUSE , mat_diffuse);
	glMaterialfv(GL_FRONT , GL_SPECULAR , mat_specular);
	glMaterialfv(GL_FRONT , GL_SHININESS , low_shininess);
	glMaterialfv(GL_FRONT , GL_EMISSION , no_mat);
	glutSolidSphere(0.5f , 30 , 30); //(0.3f);
	glPopMatrix();

	// 第二行第三列绘制的球有漫反射光、环境光和镜面光，且有很亮的高光。*/
	glPushMatrix();
	glScalef(1 , 1 , 1);
	glTranslatef(1.0f , 0.5f , -7.0f);
	glMaterialfv(GL_FRONT , GL_AMBIENT , mat_ambient);
	glMaterialfv(GL_FRONT , GL_DIFFUSE , mat_diffuse);
	glMaterialfv(GL_FRONT , GL_SPECULAR , mat_specular);
	glMaterialfv(GL_FRONT , GL_SHININESS , high_shininess);
	glMaterialfv(GL_FRONT , GL_EMISSION , no_mat);
	glutSolidSphere(0.5f , 30 , 30); //(0.3f);
	glPopMatrix();

	// 第二行第四列绘制的球有漫反射光、环境光和辐射光，而无镜面光。*/
	glPushMatrix();
	glScalef(1 , 1 , 1);
	glTranslatef(2.5f , 0.5f , -7.0f);
	glMaterialfv(GL_FRONT , GL_AMBIENT , mat_ambient);
	glMaterialfv(GL_FRONT , GL_DIFFUSE , mat_diffuse);
	glMaterialfv(GL_FRONT , GL_SPECULAR , no_mat);
	glMaterialfv(GL_FRONT , GL_SHININESS , no_shininess);
	glMaterialfv(GL_FRONT , GL_EMISSION , mat_emission);
	glutSolidSphere(0.5f , 30 , 30); //(0.3f);
	glPopMatrix();

	// 第三行第一列绘制的球有漫反射光和有颜色的环境光，而无镜面光。*/
	glPushMatrix();
	glScalef(1 , 1 , 1);
	glTranslatef(-2.0f , -1.5f , -7.0f);
	glMaterialfv(GL_FRONT , GL_AMBIENT , mat_ambient_color);
	glMaterialfv(GL_FRONT , GL_DIFFUSE , mat_diffuse);
	glMaterialfv(GL_FRONT , GL_SPECULAR , no_mat);
	glMaterialfv(GL_FRONT , GL_SHININESS , no_shininess);
	glMaterialfv(GL_FRONT , GL_EMISSION , no_mat);
	glutSolidSphere(0.5f , 30 , 30); //(0.3f);
	glPopMatrix();
	// 第三行第二列绘制的球有漫反射光和有颜色的环境光以及镜面光，且有低高光。*/
	glPushMatrix();
	glScalef(1 , 1 , 1);
	glTranslatef(-0.5f , -1.5f , -7.0f);
	glMaterialfv(GL_FRONT , GL_AMBIENT , mat_ambient_color);
	glMaterialfv(GL_FRONT , GL_DIFFUSE , mat_diffuse);
	glMaterialfv(GL_FRONT , GL_SPECULAR , mat_specular);
	glMaterialfv(GL_FRONT , GL_SHININESS , low_shininess);
	glMaterialfv(GL_FRONT , GL_EMISSION , no_mat);
	glutSolidSphere(0.5f , 30 , 30); //(0.3f);
	glPopMatrix();

	// 第三行第三列绘制的球有漫反射光和有颜色的环境光以及镜面光，且有很亮的高光。*/
	glPushMatrix();
	glScalef(1 , 1 , 1);
	glTranslatef(1.0f , -1.5f , -7.0f);
	glMaterialfv(GL_FRONT , GL_AMBIENT , mat_ambient_color);
	glMaterialfv(GL_FRONT , GL_DIFFUSE , mat_diffuse);
	glMaterialfv(GL_FRONT , GL_SPECULAR , mat_specular);
	glMaterialfv(GL_FRONT , GL_SHININESS , high_shininess);
	glMaterialfv(GL_FRONT , GL_EMISSION , no_mat);
	glutSolidSphere(0.5f , 30 , 30); //(0.3f);
	glPopMatrix();

	// 第三行第四列绘制的球有漫反射光和有颜色的环境光以及辐射光，而无镜面光。*/
	glPushMatrix();
	glScalef(1 , 1 , 1);
	glTranslatef(2.5f , -1.5f , -7.0f);
	glMaterialfv(GL_FRONT , GL_AMBIENT , mat_ambient_color);
	glMaterialfv(GL_FRONT , GL_DIFFUSE , mat_diffuse);
	glMaterialfv(GL_FRONT , GL_SPECULAR , no_mat);
	glMaterialfv(GL_FRONT , GL_SHININESS , no_shininess);
	glMaterialfv(GL_FRONT , GL_EMISSION , mat_emission);
	glutSolidSphere(0.5f , 30 , 30); //(0.3f);
	glPopMatrix();

}


void CGraphDraw::picter1(float x , float y , float z)//组合图形
{
	r += 1;if (r>360) r = 0;

	if (m_keydown)m_fAngelX -= 3;
	if (m_keyup)m_fAngelX += 3;
	if (m_keyleft)m_fAngelY -= 3;
	if (m_keyright)m_fAngelY += 3;
	if (m_keypagedown)m_fAngelZ -= 3;
	if (m_keypageup)m_fAngelZ += 3;

	InitLightParameter();
	InitMatrialParameter(2);

	CreateLights();
	CreateMaterial();


	GLUquadricObj* quadObj;
	/*圆柱*/
	glNewList(1 , GL_COMPILE);
	quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj , GLU_FILL);
	gluQuadricNormals(quadObj , GLU_SMOOTH);
	gluCylinder(quadObj , 0.3 , 0.3 , 0.8 , 16 , 16);
	glEndList();



	glPushAttrib(GL_CURRENT_BIT);//保存现有颜色属实性

	glPolygonMode(GL_FRONT_AND_BACK , GL_FILL);
	glLineWidth(1.5f);
	glColor3f(0.5f , 1.0f , 1.0f);

	glPushMatrix();//平台==============================
	glTranslatef(x , y + 0.5f , z);		//平台的定位
	glColor3f(0.0f , 1.0f , 0.2f);		//绿色
										//auxSolidCube(1);				//方台(边长)
	glutSolidCube(1);

	//

	//glRotatef(m_fAngelX , 1.0f , 0.0f , 0.0f);
	//glRotated(m_fAngelY , 0.0 , 1.0 , 0.0);
	//glRotatef(m_fAngelZ , 0.0f , 0.0f , 1.0f);
	//glTranslatef(x+m_fAngelX , y + 0.5f+m_fAngelY , z+m_fAngelZ);
	glRotatef(90 , 0.0 , 1.0 , 0.0);
	glScalef(3 , 3 , 30.0);
	glCallList(1);


	//
	//glRotatef(90 , 1.0 , 0.0 , 0.0);
	//glTranslatef(x , y + 0.5f , z);		//平台的定位												//glTranslatef(-2.0 , 0.1, m_fAngelY);
	//glScalef(3 , 3 , 5);
	//glCallList(1);
	//


	glTranslatef(0.0f , 0.8f , 0.0f);	//架的位置调整,上升0.8
	glColor3f(0.0f , 0.0f , 1.0f);		//蓝色
										//auxSolidBox(.2f, 1.3f, .2f);		//长方架(宽、高、长)
	glPopMatrix();

	glPushMatrix();
	//glLoadIdentity();
	glRotatef(90 , 1.0 , 0.0 , 1.0);
	glRotatef(m_fAngelX , 1.0f , 0.0f , 0.0f);
	glRotated(m_fAngelY , 0.0 , 1.0 , 0.0);
	glRotatef(m_fAngelZ , 0.0f , 0.0f , 1.0f);
	//glRotatef(90 , 0.0 , 0.0 , -1.0);
	glTranslatef(x , y + 0.5f , z);		//平台的定位												//glTranslatef(-2.0 , 0.1, m_fAngelY);
	glScalef(4 , 4 , 40);
	glCallList(1);
	glPopMatrix();


	glPushMatrix();
	//glLoadIdentity();
	//glRotatef(90 , 1.0 , 0.0 , 1.0);
	glTranslatef(x + 5 , y + 0.5f , z);		//平台的定位												//glTranslatef(-2.0 , 0.1, m_fAngelY);
	glScalef(4 , 4 , 40);
	glCallList(1);
	glPopMatrix();



	glPushMatrix();//雷达==============================
	glTranslatef(x , y + 2.5f , z);		//雷达的定位1
	glRotatef(-r , 0.0 , 1.0 , 0.0);	//雷达旋转2
										//=======================================
	glColor3f(1.0f , 1.0f , 1.0f);		//白色
	glRotatef(45 , 1.0 , 0.0 , 0.0);	//盘的角度调整，仰30度
										//auxWireCone(1.5, 0.6f);			//线园锥盘(底半径、高)
	glutSolidCone(1.5 , 0.6f , 50 , 50);

	//=======================================
	glRotatef(180 , 1.0 , 0.0 , 0.0);	//杆的角度调整,反方向转
	glTranslatef(0.0f , 0.0f , -0.7f);  //杆的位置调整,缩进一点
										//auxWireCone(0.2f, 2.0f);			//园锥杆(底半径、高)
	glutSolidCone(0.2 , 2.0f , 50 , 50);

	glColor3f(FRAND , 0 , 0);			//随机红色
	glTranslatef(0.0f , 0.0f , 2.0f);	//杆的位置调整,缩进一点
										//auxSolidSphere(0.1f);			//园(半径)
	glutSolidSphere(0.1f , 50 , 50);

	glPopMatrix();

	glPushMatrix();//火箭=============================
	glTranslatef(x , y + 7.0f , z);		//火箭的定位
	glRotatef(-r , 0.0 , 1.0 , 0.0);	//火箭的旋转
	glTranslatef(15 , 0 , 0);			//火箭的定位
										//=============================================
	glColor3f(1.0f , 0.0f , 0.0f);		//红色
										//glRotatef(180, 0.0, 1.0, 0.0);	//角度调整,与雷达平行，箭头朝前
										//auxSolidCone(.2, 0.6);			//园锥(底半径、高)
	glutSolidCone(0.2 , 0.6f , 50 , 50);
	//=============================================
	glColor3f(1.0f , 1.0f , 1.0f);		//白色
	glRotatef(90 , 1.0 , 0.0 , 0.0);	//角度调整,与火箭头对接
	glTranslatef(0.0f , -1.0f , 0);		//位置调整,与火箭头对接
										//auxSolidCylinder(.2f, 1);		//园柱(半径、高)
										//glScalef(6.0f, 6.0f, 6.0f);//x,y,z轴均放大6倍  
										//glutWireDodecahedron();
	glutSolidCube(0.3);
	glRotatef(-270 , 1.0 , 0.0 , 0.0);
	glColor3f(FRAND + .6f , 0.2f , 0.0f);	//随机色
	glTranslatef(0.0f , -0.0f , -0.2f); //位置调整,缩进一点
										//auxSolidCone(.2, 1.5);			//园锥(底半径、高)
	glutSolidCone(0.2 , 1.5f , 50 , 50);
	glPopMatrix();
	glPopAttrib();//恢复前一属性

}



void CGraphDraw::DrawPipleNet()
{
	GLfloat x , y , z;
	x = y = z = 0.0f;
	///*
	//int i = 0;
	for (int i = 0;i < 3;i++)
	{
		if (i == 0) y = m_fPosY;
		if (i == 1)y = m_fPosY + 3;
		if (i == 2)y = m_fPosY + 6;
		x = m_fPosX;
		z = m_fPosZ;

		//DrawPiple(x , y , z , 3);
		//DrawPiple(x , y , z+2 , 3);
		for (int j = 0;j < 10;j++)
		{
			//if (pipledraw[i][j])
			{

				DrawPiple(x , y , z , piplecolor[i][j]);
				z += 2;
			}
		}
	}




}
