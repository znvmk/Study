typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef long LONG;

#define PI 3.14159//圆周率宏定义
#define LENGTH_NAME_BMP 30//bmp图片文件名的最大长度

//bmp图片读写
//位图文件头定义;
//其中不包含文件类型信息（由于结构体的内存结构决定，
//要是加了的话将不能正确读取文件信息）
typedef struct  tagBITMAPFILEHEADER {
	//WORD bfType;//文件类型，必须是0x424D，即字符“BM”
	DWORD bfSize;//文件大小
	WORD bfReserved1;//保留字
	WORD bfReserved2;//保留字
	DWORD bfOffBits;//从文件头到实际位图数据的偏移字节数
}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
	DWORD biSize;//信息头大小
	LONG biWidth;//图像宽度
	LONG biHeight;//图像高度
	WORD biPlanes;//位平面数，必须为1
	WORD biBitCount;//每像素位数
	DWORD  biCompression; //压缩类型
	DWORD  biSizeImage; //压缩图像大小字节数
	LONG  biXPelsPerMeter; //水平分辨率
	LONG  biYPelsPerMeter; //垂直分辨率
	DWORD  biClrUsed; //位图实际用到的色彩数
	DWORD  biClrImportant; //本位图中重要的色彩数
}BITMAPINFOHEADER; //位图信息头定义

typedef struct tagRGBQUAD {
	BYTE rgbBlue; //该颜色的蓝色分量
	BYTE rgbGreen; //该颜色的绿色分量
	BYTE rgbRed; //该颜色的红色分量
	BYTE rgbReserved; //保留值
}RGBQUAD;//调色板定义

//像素信息
typedef struct tagIMAGEDATA
{
	BYTE red;
	BYTE green;
	BYTE blue;
}IMAGEDATA;

class BMP
{
public:
	BMP();
	~BMP();


public:
	//变量定义
	BITMAPFILEHEADER strHead;
	RGBQUAD strPla[256];//256色调色板
	BITMAPINFOHEADER strInfo;
	char strFile[LENGTH_NAME_BMP];//bmp文件名
	IMAGEDATA* imagedata;//动态分配存储原图片的像素信息的二维数组
	IMAGEDATA* imagedataRot;//动态分配存储旋转后的图片的像素信息的二维数组
	int width, height;//图片的宽度和高度

private:
	//显示位图文件头信息
	void showBmpHead(BITMAPFILEHEADER pBmpHead);
	void showBmpInforHead(tagBITMAPINFOHEADER pBmpInforHead);

public:
	int fileReadInBMPFormat();
	int fileWriteInBMPFormat();
	void RotBmp();
};