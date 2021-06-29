#include "BinaryFileReadWrite.h"



CBinaryFileReadWrite::CBinaryFileReadWrite()
{
}


CBinaryFileReadWrite::~CBinaryFileReadWrite()
{
}

void CBinaryFileReadWrite::ReadFile(const char* filename)
{
	//FILE* fp = fopen(shaderFile, "rb");
	//由于vs甚么安全性的原因，不让使用fopen，用下面的fopen_s代替；
	FILE*fileP;
	fopen_s(&fileP, filename, "rb");//这里是用二进制读取，read-r；binary-b；因为只弄r结果出错！！弄了后面那个的再来看这个才发现是这个的问题！！
	if (fileP == NULL)return;
	fseek(fileP, 0L, SEEK_END);
	long size = ftell(fileP);
	unsigned char*filebuf = new unsigned char[size + 1];
	fseek(fileP, 0x0L, SEEK_SET);//图片源 
	fread(filebuf, sizeof(filebuf[0]), size, fileP);
	for (int j = 0; j < size; j++)
		cout << (filebuf[j] & 0xff) << "  ";
	fclose(fileP);
	WriteFile(filebuf, size);
	WriteFile1(filebuf, size);
}

void CBinaryFileReadWrite::ReadFile1(const char* filename)
{
	ifstream fileF(filename, ios::binary);
	if (!fileF) {
		cerr << "open error!" << endl;
		abort();
	}
	fileF.seekg(0, ios::end);
	int size = fileF.tellg();
	//查了C++Library Reference才知道怎么得到size。
	/*int pixscnt;
	unsigned char width[4], height[4];
	fileF.seekg(0x10);
	fileF.read((char*)&width, sizeof(width));
	fileF.seekg(0x14);
	fileF.read((char*)&height, sizeof(height));

	for (int i = 0; i < 4; i++)
	cout << (width[i] & 0xff) << ":";
	for (int i = 0; i < 4; i++)
	cout << (height[i] & 0xff) << ":";

	pixscnt = (width[2] * (0x100) + width[3])*(height[2] * (0x100) + height[3]);
	cout << pixscnt << endl;//像素
	cout << size << endl;
	*/
	unsigned char*filebuf = new unsigned char[size];
	//fileF.seekg(0x10); 
	fileF.seekg(0, ios::beg);
	fileF.read((char*)filebuf, size);//一次性读入，书上的不知是错的还是旧的不可行。后面注释的是循环读入
	/*
	for (int i = 0; i<size; i++)
	fileF.read( (char*)&filebuf[i], sizeof(unsigned char));
	*/
	fileF.close();
	/*
	for (int i = 0; i < size; i++)
	{
	cout << hex << (filebuf[i] & 0xff) << ":";
	if (i % 4 == 0)cout << endl;
	}
	*/
	WriteFile1(filebuf, size);
}


void CBinaryFileReadWrite::WriteFile(unsigned char* filebuf, int size)
{
	//FILE* fp = fopen(shaderFile, "wb");
	//由于vs甚么安全性的原因，不让使用fopen，用下面的fopen_s代替；
	FILE*filePo;
	fopen_s(&filePo, "D:\\2.png", "wb");//这里是用二进制读取，read-r；binary-b；因为只弄r结果出错！！弄了后面那个的再来看这个才发现是这个的问题！！
	if (filePo == NULL)return;
	fwrite(filebuf, sizeof(char), size, filePo);
	fclose(filePo);
}


void CBinaryFileReadWrite::WriteFile1(unsigned char* filebuf, int size)
{
	ofstream fileFo("D:\\3.png", ios::binary);
	if (!fileFo)
	{
		cerr << "open error!" << endl;
		abort();
	}
	fileFo.write((char*)filebuf, size);//一次性写入后面注释的是循环写入
	/*	for (int i = 0; i < size; i++)
	{
	char ct = (filebuf[i] & 0xFF);
	fileFo.write(&ct, sizeof(char));
	//unsigned char ct = (filebuf[i] & 0xFF);
	//fileFo.write((char*)&ct, sizeof(unsigned char));
	//尝试这样输出的是否正确.
	//unsigned char是我自己给名的unsigned char，出来的是对的，用char也可以。都是一个字节。
	}
	*/
	fileFo.close();
}

