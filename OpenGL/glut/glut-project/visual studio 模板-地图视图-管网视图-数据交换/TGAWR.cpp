#include "stdafx.h"
#include "TGAWR.h"


CTGAWR::CTGAWR()
{
}


CTGAWR::~CTGAWR()
{
}

GLint CTGAWR::gltWriteTGA(const char* szFileName)
{
	/*
	FILE *pFile;		//头文件指针
	TGAHeader tgaHeader;//TGA头文件
	unsigned long lImageSize;//图像的大小，用字节表示
	GLbyte* pBits = NULL; //指向位的指针
	GLint iViewport[4];//以像素表示的视口
	//GLenum  lastBuffer;
	GLint  lastBuffer;//储存当前的读取缓冲区设置
	//获取视口大小
	glGetIntegerv(GL_VIEWPORT, iViewport);
	//图像应该多大（targa文件将被紧密包装）
	lImageSize = iViewport[2] * 3 * iViewport[3];
	//分配块，如果这种操作不起作用则返回
	pBits = (GLbyte*)malloc(lImageSize);
	if (pBits == NULL)
		return 0;

	//从颜色缓冲区读取
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ROW_LENGTH, 0);
	glPixelStorei(GL_PACK_SKIP_ROWS, 0);
	glPixelStorei(GL_PACK_SKIP_PIXELS, 0);

	//获取当前读取缓冲区设置并进行保存
	//切换到前台缓冲区并进行读取操作，最后恢复读取缓冲区状态
	glGetIntegerv(GL_READ_BUFFER, &lastBuffer);
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, iViewport[2], iViewport[3], GL_BGR, GL_UNSIGNED_BYTE, pBits);
	glReadBuffer(lastBuffer);
	//初始化Targa头
	
	*/
	return 0;
}

bool CTGAWR::LoadTGA(TextureImage * texture, CString cfilename)
{
	
	
	
	if (!cfile.Open(cfilename, CFile::modeRead | CFile::typeBinary, NULL))
	{
		return false;
	}
	//else return true;
			// Open The TGA File  
	
	
	
	if (cfile == NULL)
	{                                
		return false;
	}
	//cfile.SeekToBegin();
	for (int i = 0; i < 12;i++)
	{
		cfile.Seek(i, CFile::begin);
		cfile.Read((tgaheader.Header + i), 1);

	}


	


	

	if (TGAHeaderCompare(uTGAcompare, tgaheader.Header))
	{
		//读取未压缩的TGA文件
		LoadUncompressedTGA(texture);
	}
	//else if (TGAHeaderCompare(uTGAcompare, tgaheader.Header))
	{
		//读取未压缩的TGA文件
	//	LoadCompressedTGA(texture);
	}
	//else
	{
	//	cfile.Close();
	//	return false;
	}

	
	cfile.Close();
	return true;                                       
}

//读取未压缩的TGA文件
bool CTGAWR::LoadUncompressedTGA(TextureImage* texture)
{

	//这个函数有3个参数。头两个和LoadTGA中的一样，仅仅是简单的传递。第三个是来自前一个函数中的文件指针，因此我们没有丢失我们的空间。
	//	接下来我们试着再从文件中读取6个字节的内容，并且存储在tga.header中。如果他失败了，我们运行一些错误处理代码，并且返回false。
	
		// 尝试继续读取6个字节的内容
	for (int i = 12; i < 18;i++)
	{
		cfile.Seek(i , CFile::begin);
		cfile.Read((tga.header + i - 12), 1);
	}
	

	//现在我们有了计算图像的高度、宽度和BPP的全部信息。我们在纹理和本地结构中都将存储它。

	texture->width = tga.header[1] * 256 + tga.header[0]; // 计算高度
	texture->height = tga.header[3] * 256 + tga.header[2]; // 计算宽度
	texture->bpp = tga.header[4];   // 计算BPP
	tga.Width = texture->width;    // 拷贝Width到本地结构中去
	tga.Height = texture->height;   // 拷贝Height到本地结构中去
	tga.Bpp = texture->bpp;    // 拷贝Bpp到本地结构中去

	//现在，我们需要确认高度和宽度至少为1个像素，并且bpp是24或32。如果这些值中的任何一个超出了它们的界限，我们将再一次显示一个错误，关闭文件，并且离开此函数。

		// 确认所有的信息都是有效的
	if ((texture->width <= 0) || (texture->height <= 0) || ((texture->bpp != 24) && (texture->bpp != 32)))
	{
		//	...Error code here...
		return false;    // 返回 False
	}

	//接下来我们设置图像的类型。24 bit图像是GL_RGB，32 bit 图像是GL_RGBA

	if (texture->bpp == 24)    // 是24 bit图像吗？
	{
		texture->type = GL_RGB;   //如果是，设置类型为GL_RGB
	}
	else      // 如果不是24bit,则必是32bit
	{
		texture->type = GL_RGBA;  //这样设置类型为GL_RGBA
	}

	//现在我们计算每像素的字节数和总共的图像数据。

	tga.bytesPerPixel = (tga.Bpp / 8);  // 计算BPP
										// 计算存储图像所需的内存
	tga.imageSize = (tga.bytesPerPixel * tga.Width * tga.Height);

	//我们需要一些空间去存储整个图像数据，因此我们将要使用malloc分配正确的内存数量
		//然后我们确认内存已经分配，并且它不是NULL。如果出现了错误，则运行错误处理代码。


		// 分配内存
	texture->imageData = (GLubyte *)malloc(tga.imageSize);
	if (texture->imageData == NULL)   // 确认已经分配成功
	{
		//...Error code here...
		return false;    // 确认已经分配成功
	}

	//这里我们尝试读取所有的图像数据。如果不能，我们将再次触发错误处理代码。

		// 尝试读取所有图像数据
	

	for (int i = 18; i < tga.imageSize+18;i++)
	{
		cfile.Seek(i, CFile::begin);
		cfile.Read((texture->imageData + i-18), 1);

	}


	//TGA文件用逆OpenGL需求顺序的方式存储图像，因此我们必须将格式从BGR到RGB。为了达到这一点，我们交换每个像素的第一个和第三个字节的内容。
	//	Steve Thomas补充：我已经编写了能稍微更快速读取TGA文件的代码。它涉及到仅用3个二进制操作将BGR转换到RGB的方法。
	//	然后我们关闭文件，并且成功退出函数。


		//  开始循环
	for (GLuint cswap = 0; cswap < (int)tga.imageSize; cswap += tga.bytesPerPixel)
	{
		// 第一字节 XOR第三字节XOR 第一字节 XOR 第三字节
		texture->imageData[cswap] ^= texture->imageData[cswap + 2] ^=
			texture->imageData[cswap] ^= texture->imageData[cswap + 2];
	}
	//cfile.Close();     // 关闭文件
	return true;     // 返回成功
}

//以上是读取未压缩型TGA文件的方法。读取RLE压缩型文件的步骤稍微难一点。我们像平时一样读取文件头并且收集高度／宽度／色彩深度，这和读取未压缩版本是一致的。

bool CTGAWR::LoadCompressedTGA(TextureImage* texture)
{
	//这个函数有3个参数。头两个和LoadTGA中的一样，仅仅是简单的传递。第三个是来自前一个函数中的文件指针，因此我们没有丢失我们的空间。
	//	接下来我们试着再从文件中读取6个字节的内容，并且存储在tga.header中。如果他失败了，我们运行一些错误处理代码，并且返回false。

	// 尝试继续读取6个字节的内容
	for (int i = 12; i < 18;i++)
	{
		cfile.Seek(i, CFile::begin);
		cfile.Read((tga.header + i - 12), 1);
	}


	//现在我们有了计算图像的高度、宽度和BPP的全部信息。我们在纹理和本地结构中都将存储它。

	texture->width = tga.header[1] * 256 + tga.header[0]; // 计算高度
	texture->height = tga.header[3] * 256 + tga.header[2]; // 计算宽度
	texture->bpp = tga.header[4];   // 计算BPP
	tga.Width = texture->width;    // 拷贝Width到本地结构中去
	tga.Height = texture->height;   // 拷贝Height到本地结构中去
	tga.Bpp = texture->bpp;    // 拷贝Bpp到本地结构中去

							   //现在，我们需要确认高度和宽度至少为1个像素，并且bpp是24或32。如果这些值中的任何一个超出了它们的界限，我们将再一次显示一个错误，关闭文件，并且离开此函数。

							   // 确认所有的信息都是有效的
	if ((texture->width <= 0) || (texture->height <= 0) || ((texture->bpp != 24) && (texture->bpp != 32)))
	{
		//	...Error code here...
		return false;    // 返回 False
	}

	//接下来我们设置图像的类型。24 bit图像是GL_RGB，32 bit 图像是GL_RGBA

	if (texture->bpp == 24)    // 是24 bit图像吗？
	{
		texture->type = GL_RGB;   //如果是，设置类型为GL_RGB
	}
	else      // 如果不是24bit,则必是32bit
	{
		texture->type = GL_RGBA;  //这样设置类型为GL_RGBA
	}

	//现在我们计算每像素的字节数和总共的图像数据。

	tga.bytesPerPixel = (tga.Bpp / 8);  // 计算BPP
										// 计算存储图像所需的内存
	tga.imageSize = (tga.bytesPerPixel * tga.Width * tga.Height);

	//我们需要一些空间去存储整个图像数据，因此我们将要使用malloc分配正确的内存数量
	//然后我们确认内存已经分配，并且它不是NULL。如果出现了错误，则运行错误处理代码。

	//现在我们需要分配存储图像所需的空间，这是为我们解压缩之后准备的，我们将使用malloc。如果内存分配失败，运行错误处理代码，并且返回false。

	// 分配存储图像所需的内存空间
	texture->imageData = (GLubyte *)malloc(tga.imageSize);
	if (texture->imageData == NULL)   // 如果不能分配内存
	{
		//...Error code here...
		return false;    // 返回 False
	}

	//下一步我们需要决定组成图像的像素数。我们将它存储在变量“pixelcount”中。
	//我们也需要存储当前所处的像素，以及我们正在写入的图像数据的字节，这样避免溢出写入过多的旧数据。

	//我们将要分配足够的内存来存储一个像素。


	GLuint pixelcount = tga.Height * tga.Width; // 图像中的像素数
	GLuint currentpixel = 0;  // 当前正在读取的像素
	GLuint currentbyte = 0;   // 当前正在向图像中写入的像素
							  // 一个像素的存储空间
	GLubyte * colorbuffer = (GLubyte *)malloc(tga.bytesPerPixel);

	//接下来我们将要进行一个大循环。
	//让我们将它分解为更多可管理的块。
	//首先我们声明一个变量来存储“块”头。块头指示接下来的段是RLE还是RAW，它的长度是多少。
	//如果一字节头小于等于127，则它是一个RAW头。头的值是颜色数，是负数，在我们处理其它头字节之前，我们先读取它并且拷贝到内存中。
	//这样我们将我们得到的值加1，然后读取大量像素并且将它们拷贝到ImageData中，就像我们处理未压缩型图像一样。如果头大于127，
	//那么它是下一个像素值随后将要重复的次数。要获取实际重复的数量，我们将它减去127以除去1bit的的头标示符。
	//然后我们读取下一个像素并且依照上述次数连续拷贝它到内存中。


	do      // 开始循环
	{
		GLubyte chunkheader = 0;    // 存储Id块值的变量
		
			for (int i = 12; i < sizeof(GLubyte);i++)
			{
				cfile.Seek(i, CFile::begin);
				cfile.Read((&chunkheader + i-12), 1);

			}
			//return false;    // If It Fails, Return False
		

		//接下来我们将要看看它是否是RAW头。如果是，我们需要将此变量的值加1以获取紧随头之后的像素总数。

		if (chunkheader < 128)    // 如果是RAW块
		{
			chunkheader++;    // 变量值加1以获取RAW像素的总数

		//	我们开启另一个循环读取所有的颜色信息。它将会循环块头中指定的次数，并且每次循环读取和存储一个像素。
		//		首先，我们读取并检验像素数据。单个像素的数据将被存储在colorbuffer变量中。然后我们将检查它是否为RAW头。如果是，我们需要添加一个到变量之中以获取头之后的像素总数。


				// 开始像素读取循环
			for (short counter = 0; counter < chunkheader; counter++)
			{
				// 尝试读取一个像素
				//if (fread(colorbuffer, 1, tga.bytesPerPixel, fTGA) != tga.bytesPerPixel)
				{
					//				...Error code...
					return false;   // 如果失败，返回false
				}

				//			我们循环中的下一步将要获取存储在colorbuffer中的颜色值并且将其写入稍后将要使用的imageData变量中。在这个过程中，数据格式将会由BGR翻转为RGB或由BGRA转换为RGBA，具体情况取决于每像素的比特数。当我们完成任务后我们增加当前的字节和当前的像素计数器。

				texture->imageData[currentbyte] = colorbuffer[2];  // 写“R”字节
				texture->imageData[currentbyte + 1] = colorbuffer[1]; //写“G”字节
				texture->imageData[currentbyte + 2] = colorbuffer[0]; // 写“B”字节
				if (tga.bytesPerPixel == 4)     // 如果是32位图像...
				{
					texture->imageData[currentbyte + 3] = colorbuffer[3]; // 写“A”字节
				}
				// 依据每像素的字节数增加字节计数器
				currentbyte += tga.bytesPerPixel;
				currentpixel++;     // 像素计数器加1

		//		下一段处理描述RLE段的“块”头。首先我们将chunkheader减去127来得到获取下一个颜色重复的次数。
			}
		}
		else      // 如果是RLE头
		{
			chunkheader -= 127;   //  减去127获得ID Bit的Rid
		}
		//		然后我们尝试读取下一个颜色值。

					// 读取下一个像素
		//if (fread(colorbuffer, 1, tga.bytesPerPixel, fTGA) != tga.bytesPerPixel)
		{
			//				...Error code...
			return false;    // 如果失败，返回false
		}

		//接下来，我们开始循环拷贝我们多次读到内存中的像素，这由RLE头中的值规定。
		//	然后，我们将颜色值拷贝到图像数据中，预处理R和B的值交换。
		//	随后，我们增加当前的字节数、当前像素，这样我们再次写入值时可以处在正确的位置。


			// 开始循环
		for (short counter = 0; counter < chunkheader; counter++)
		{
			// 拷贝“R”字节
			texture->imageData[currentbyte] = colorbuffer[2];
			// 拷贝“G”字节
			texture->imageData[currentbyte + 1] = colorbuffer[1];
			// 拷贝“B”字节
			texture->imageData[currentbyte + 2] = colorbuffer[0];
			if (tga.bytesPerPixel == 4)  // 如果是32位图像
			{
				// 拷贝“A”字节
				texture->imageData[currentbyte + 3] = colorbuffer[3];
			}
			currentbyte += tga.bytesPerPixel; // 增加字节计数器
			currentpixel++;   // 增加字节计数器

	//		只要仍剩有像素要读取，我们将会继续主循环。
	//			最后，我们关闭文件并返回成功。
		}

	} while (currentpixel < pixelcount); // 是否有更多的像素要读取？开始循环直到最后
	//fclose(fTGA);   // 关闭文件
	return true;   // 返回成功
}

bool CTGAWR::TGAHeaderCompare(GLubyte* TGACompare, GLubyte* HeaderCompare)
{
	for (int i = 0;i < 12;i++)
	{
		if (!(*(TGACompare + i) == *(HeaderCompare + i)))
			return false;
	}
	return true;
}




void CTGAWR::zTexture2D(TextureImage* texture, int p)
{


	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


	

	/*定义纹理*/
	
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture[p].width, texture[p].height, 0, texture[p].type, GL_UNSIGNED_BYTE, texture[p].imageData);
	
	//控制纹理
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	

	//说明纹理贴图方式
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	/*启动纹理贴图*/
	glEnable(GL_TEXTURE_2D);
	
	//glShadeModel(GL_SMOOTH);
	/*定义纹理坐标和物体几何坐标*/
	//glBegin(GL_QUADS);
	//glTexCoord2f(0.0f, 0.0f);glVertex3f(-1.0f, -1.0f, 0.0f);
	//glTexCoord2f(0.0f, 1.0f);glVertex3f(-1.0f, 1.0f, 0.0f);
	//glTexCoord2f(1.0f, 1.0f);glVertex3f(1.0f, 1.0f, 0.0f);
	//glTexCoord2f(1.0f, 0.0f);glVertex3f(1.0f, -1.0f, 0.0f);
//	glEnd();

	//glDisable(GL_TEXTURE_2D);
	
}


