#include "FileReadWrite.h"
#include <iostream>
#include <fstream>

using namespace std;

//顺序文件读写
void FileReadWrite::WriteOrderFile()
{
	ofstream myFile;
	myFile.open("dataOrder.txt", ios::out);
	if (!myFile)
	{
		cout << "打开文件错误" << endl;
		return;
	}
	myFile << "张三" << endl << "李四" << endl;


	myFile.close();

	cout << endl << "写dataOrder.txt文件";

}

void FileReadWrite::ReadOrderFile()
{
	ifstream myFile;
	myFile.open("dataOrder.txt", ios::in);
	if (!myFile)
	{
		cout << "打开文件错误" << endl;
		return;
	}
	cout << endl << "读取dataOrder.txt文件内容如下所示：" << endl;
	int value;
	while ((value = myFile.get()) != EOF)
	{
		cout << (char)value;
	}
	myFile.close();
}

void FileReadWrite::WriteRandomFile()
{
	ofstream myFile;
	char tmp[10] = "数据";
	
	string a;
	a = "sdffffffff";
	const char* p = a.c_str();
	//char* 赋值
	//char ch = 'a';
	//for (int i = 0; i < 10; i++)tmp[i] = ch+i;
	//char* p=tmp;
	//for (int i = 0; i < 10; i++)*(p + i) = ch + i;
	const char* tex = tmp;
	myFile.open("dataRandom.txt",ios::out|ios::binary);
	if (!myFile)
	{
		cout << "打开文件错误" << endl;
		return;
	}
	for(int j=0;j<100000;j++)
		myFile.write(tex, sizeof(tex));

	myFile.close();
	cout << endl << "写dataRandom.txt文件" << endl;

	/*
	myFile.open("dataRandom.txt", ios::app | ios::binary);
	if (!myFile)
	{
		cout << "打开文件错误";
		return;
	}

	char addtmp[10] = "追加";
//	tex = addtmp;
	myFile.seekp(100);
	myFile.write((const char*)addtmp, sizeof(tex));
	myFile.close();
	cout << "追加数据";
	*/
}

void FileReadWrite::ReadRandomFile()
{
	ifstream myFile;
	myFile.open("dataRandom.txt", ios::in|ios::binary);
//	myFile.open("1.bmp", ios::in|ios::binary);

	if (!myFile)
	{
		cout << "打开文件错误" << endl;
		return;
	}
	cout << endl << "读dataRandom.txt文件" << endl;
	//定义存放获取记录的变量
//	char tex[100];

	//把文件的写指针从文件的开头向后移一条记录
//	myFile.seekg(sizeof(tex), ios::beg);
	//读取文件第二条记录
	//myFile.read(tex, sizeof(tex));
	//myFile.read(tex, 1000);
	myFile.seekg(0,ios::end);
	int len = 0;
	len = myFile.tellg();
	cout << "文件长度：" << len << endl;

	myFile.seekg(0, ios::beg);
	char* data;
	data = (char*)malloc(len);
	myFile.read(data, len);

	//输出其中可转换成asscii表中字符的数值
	cout << endl << (char*)data << endl;
	//以十六进制输出所有二进制数据
	for (int i = 0; i < len; i++)
	{
		cout << hex <<(short int)data[i] << " ";
	}

	myFile.close();
}


