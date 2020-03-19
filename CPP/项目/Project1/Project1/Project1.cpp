#include<iostream>
#include<fstream>
using namespace std;


void WriteOrderFile()
{
	ofstream myFile;
	myFile.open("data.txt", ios::out);
	if (!myFile)
	{
		cout << "打开文件错误" << endl;
		return;
	}
	myFile << "张三" << endl << "李四" << endl;


	myFile.close();

	cout << endl << "写data.txt文件" ;

}


void ReadOrderFile()
{
	ifstream myFile;
	myFile.open("data.txt", ios::in);
	if (!myFile)
	{
		cout << "打开文件错误" << endl;
		return;
	}
	cout << endl<<"读取data.txt文件内容如下所示：" << endl;
	int value;
	while ((value = myFile.get() )!= EOF)
	{
		cout << (char)value;
	}
	myFile.close();
}

void main()
{
	int a;
	a = 7753;
	cout << a;
	
	WriteOrderFile();

	ReadOrderFile();

	system("pause");
}
