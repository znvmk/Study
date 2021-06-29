#pragma once
#include"stdafx.h"

#ifndef __TEXTURE_H__    // 看看此头文件是否已经被包含
#define __TEXTURE_H__    // 如果没有，定义它


//纹理结构体定义  
typedef struct
{
	GLubyte *imageData;//图像数据  
	GLuint bpp;//像素深度  
	GLuint width;//图像宽度  
	GLuint height;//图像高度  
	GLuint texID;//对应的纹理ID  
	GLuint type;     // 描述存储在*ImageData中的数据(GL_RGB Or GL_RGBA)
}TextureImage;



typedef struct
{
	GLubyte Header[12];   // 文件头决定文件类型
	GLuint Header1;   // 文件头决定文件类型
} TGAHeader;




typedef struct
{
	GLubyte header[12];    // 控制前6个字节
	//int header[6];    // 控制前6个字节
	GLuint bytesPerPixel;   // 每像素的字节数 (3 或 4)
	GLuint imageSize;    // 控制存储图像所需的内存空间
	GLuint type;    // 图像类型 GL_RGB 或 GL_RGBA
	GLuint Height;    // 图像的高度
	GLuint Width;    // 图像宽度
	GLuint Bpp;    // 每像素的比特数 (24 或 32)
} TGA;




class CTGAWR
{
public:
	CTGAWR();
	~CTGAWR();


public:

	
	
	TGAHeader tgaheader;    // 用来存储我们的文件头


	
	

	TGA tga;      // 用来存储文件信息

	CFile cfile;

				  // 未压缩的TGA头
	GLubyte uTGAcompare[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
	// 压缩的TGA头
	GLubyte cTGAcompare[12] = { 0,0,10,0,0,0,0,0,0,0,0,0 };



	
	
public:

	//TGA头比较函数
	bool TGAHeaderCompare(GLubyte* TGACompare, GLubyte* HeaderCompare);

	////加载TGA图像（无压缩格式），生成纹理 
	bool LoadTGA(TextureImage* texture, CString cfilename);
	// 读取一个未压缩的文件
	bool LoadUncompressedTGA(TextureImage* texture);
	// 读取一个压缩的文件
	bool LoadCompressedTGA(TextureImage* texture);

	GLint gltWriteTGA(const char* szFileName);



	
	void zTexture2D(TextureImage* texture, int p);








	
};

#endif      // __TEXTURE_H__ 结束包含保护