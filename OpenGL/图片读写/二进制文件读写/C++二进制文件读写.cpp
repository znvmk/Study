
//转自https://blog.csdn.net/u014646950/article/details/51100185
//C/C++二进制读写png文件

#include "iostream"
#include "fstream"
#include "string"

using namespace std;



/*
class PngMsg
{
private :
unsigned char markMsg[8]; //十进制，相当于16进制89.50.4e.47.0d.0a.1a.0a；
char widthloc;
char heigtMsgloc;
char BitDepthloc;//图像深度
char ColorTypeloc;
char CompressionMethodloc;//压缩方法（LZ77派生算法）
char FilterMethodloc;//滤波器方法
char InterlaceMethodloc;
public:
PngMsg()
{
markMsg[0] = 137;markMsg[1] = 80; markMsg[2] = 78;markMsg[3] = 71; markMsg[4] = 13;markMsg[5] = 10; markMsg[6] = 26; markMsg[7] = 10;
widthloc = 'a';
heigtMsgloc = 'b';
BitDepthloc = 'c';//图像深度
ColorTypeloc = 'd';
CompressionMethodloc = 'e';//压缩方法（LZ77派生算法）
FilterMethodloc = 'f';//滤波器方法
InterlaceMethodloc = 'g';
}
long int getMsg(char loc)
{
if (loc == 'a')return 0x10;
if (loc == 'b')return 0x14;
if (loc == 'c')return 0x15;
if (loc == 'd')return 0x16;
if (loc == 'e')return 0x17;
if (loc == 'f')return 0x18;
if (loc == 'g')return 0x19;
}
unsigned char width[4];//图像宽度，单位像素
unsigned char height[4];//图像高度，单位像素
unsigned char BitDepth;
//图像深度
//索引彩色1.2.4.8；灰度1.2.4.8.16；真彩色8.16
unsigned char ColorType;
//0灰度1.2.4.8.16；2真彩色8.16；3索引彩色1.2.4.8
//4带α通道数据的灰度8.16；6带α通道数据的真彩色8.16
unsigned char CompressionMethod;//压缩方法（LZ77派生算法）
unsigned char FilterMethod;//滤波器方法
unsigned char InterlaceMethod;//0:非隔行扫描；1：Adam7
};*/


//===============================


//===============
//二进制读入。书上写ASCII码读取和二进制读取，如果对象是字母，那么一致。如果是数字，那么不一致
//书中说明【文件中数据的组织形式，分为ASCII文件（一个字节存放一个ASCII代码）和二进制文件（内部文件，存储形式原样在磁盘上存放），】
//字符，内存存储=ASCII=二进制形式
//数值数据，内存存储和ASCII码不同。
//样例内存整数100000.
//----------------------------------------------------------------
//内存地址       0x00       01       02       03            
//内存             00000000 00000000 00100111 00010000【大端模式下】
//----------------------------------------------------------------
//二进制           00000000 00000000 00100111 00010000
//----------------------------------------------------------------
//ASCII           00110001  00110000 00110000 00110000 00110000 00110000【6个字节】
//ASCII码对应     1的49      0的48    0的48    0的48    0的48    0的48
//----------------------------------------------------------------



//只有含‘写’的不存在的文件会新建，其他会报错

//r只读；w只写；a尾增(附加/写)；文本ASCII
//rb读；wb写；ab尾增；二进制
//以下读写↓
//r+；w+；a+；文本ASCII
//rb+；wb+；ab+二进制



void  writeImage(unsigned char* imgbuf, int size)
{
	//FILE* fp = fopen(shaderFile, "wb");
	//由于vs甚么安全性的原因，不让使用fopen，用下面的fopen_s代替；
	FILE*imgPo;
	fopen_s(&imgPo, "D:\\2.png", "wb");//这里是用二进制读取，read-r；binary-b；因为只弄r结果出错！！弄了后面那个的再来看这个才发现是这个的问题！！
	if (imgPo == NULL)return;
	fwrite(imgbuf, sizeof(char), size, imgPo);
	fclose(imgPo);
}
void  WriteImage(unsigned char* imgbuf, int size)
{

	ofstream imgFo("D:\\3.png", ios::binary);
	if (!imgFo)
	{
		cerr << "open error!" << endl;
		abort();
	}
	imgFo.write((char*)imgbuf, size);//一次性写入后面注释的是循环写入
	/*	for (int i = 0; i < size; i++)
	{
		char ct = (imgbuf[i] & 0xFF);
		imgFo.write(&ct, sizeof(char));
		//unsigned char ct = (imgbuf[i] & 0xFF);
		//imgFo.write((char*)&ct, sizeof(unsigned char));
		//尝试这样输出的是否正确.
		//unsigned char是我自己给名的unsigned char，出来的是对的，用char也可以。都是一个字节。
	}
	*/
	imgFo.close();
}

void readImageFile(const char* Imgname)
{
	//FILE* fp = fopen(shaderFile, "rb");
	//由于vs甚么安全性的原因，不让使用fopen，用下面的fopen_s代替；
	FILE*imgP;
	fopen_s(&imgP, Imgname, "rb");//这里是用二进制读取，read-r；binary-b；因为只弄r结果出错！！弄了后面那个的再来看这个才发现是这个的问题！！
	if (imgP == NULL)return;
	fseek(imgP, 0L, SEEK_END);
	long size = ftell(imgP);
	unsigned char*imgbuf = new unsigned char[size + 1];
	fseek(imgP, 0x0L, SEEK_SET);//图片源 
	fread(imgbuf, sizeof(imgbuf[0]), size, imgP);
	for (int j = 0; j < size; j++)
	cout << (imgbuf[j] & 0xff) << "  ";
	fclose(imgP);
	writeImage(imgbuf, size);
	WriteImage(imgbuf, size);
}


//===========================================================



void ReadImageFile(const char* Imgname)
{
	ifstream imgF(Imgname, ios::binary);
	if (!imgF) {
		cerr << "open error!" << endl;
		abort();
	}
	imgF.seekg(0, ios::end);
	int size = imgF.tellg();
	//查了C++Library Reference才知道怎么得到size。
	/*int pixscnt;
	unsigned char width[4], height[4];
	imgF.seekg(0x10);
	imgF.read((char*)&width, sizeof(width));
	imgF.seekg(0x14);
	imgF.read((char*)&height, sizeof(height));

	for (int i = 0; i < 4; i++)
	cout << (width[i] & 0xff) << ":";
	for (int i = 0; i < 4; i++)
	cout << (height[i] & 0xff) << ":";

	pixscnt = (width[2] * (0x100) + width[3])*(height[2] * (0x100) + height[3]);
	cout << pixscnt << endl;//像素
	cout << size << endl;*/
	unsigned char* imgbuf = new unsigned char[size];
	//imgF.seekg(0x10); 
	imgF.seekg(0, ios::beg);
	imgF.read((char*)imgbuf, size);//一次性读入，书上的不知是错的还是旧的不可行。后面注释的是循环读入
	/*
	for (int i = 0; i<size; i++)
	imgF.read( (char*)&imgbuf[i], sizeof(unsigned char));
	*/
	imgF.close();
	/*
	for (int i = 0; i < size; i++)
	{
	cout << hex << (imgbuf[i] & 0xff) << ":";
	if (i % 4 == 0)cout << endl;
	} 
	*/
	WriteImage(imgbuf, size);
}

int  main()
{
	//readImageFile("D:\\1.png");//C/C++的
	ReadImageFile("D:\\1.png");//C++的
	system("pause");
	return 0;
}