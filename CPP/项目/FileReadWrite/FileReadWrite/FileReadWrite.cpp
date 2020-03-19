#include<iostream>
#include<fstream>
using namespace std;

//顺序文件读写
void WriteOrderFile()
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


void ReadOrderFile()
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


//随机文件读写
struct Record
{
	char value[10];
};

void WriteRandomFile()
{
	Record record[3] = { "01-张三","02-李四","03-王五" };


	ofstream myFile;
	myFile.open("dataRandom.txt",ios::out|ios::binary);
	if (!myFile)
	{
		cout << "打开文件错误" << endl;
		return;
	}
	for (int i = 0;i < 3;i++)
	{
		myFile.write((const char*)&record[i], sizeof(Record));

	}
	


	myFile.close();

	cout << endl << "写dataRandom.txt文件";

}

void ReadRandomFile()
{

	ifstream myFile;
	myFile.open("dataRandom.txt", ios::in|ios::binary);
	if (!myFile)
	{
		cout << "打开文件错误" << endl;
		return;
	}

	cout << endl << "读dataRandom.txt文件" << endl;
	//定义存放获取记录的变量
	Record record;
	//把文件的写指针从文件的开头向后移一条记录
	myFile.seekg(sizeof(Record), ios::beg);
	//读取文件第二条记录
	myFile.read((char*)&record, sizeof(record));
	cout << (char*)&record;

	myFile.close();

	

}





void main()
{
	int a;
	a = 7753;
	cout << a;

	//WriteOrderFile();

	ReadOrderFile();


	WriteRandomFile();

	ReadRandomFile();

	system("pause");
}
