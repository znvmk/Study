#include "FileReadWrite.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//˳���ļ���д
void FileReadWrite::WriteOrderFile()
{
	ofstream myFile;
	myFile.open("dataOrder.txt", ios::out);
	if (!myFile)
	{
		cout << "���ļ�����" << endl;
		return;
	}
	myFile << "����" << endl << "����" << endl;


	myFile.close();

	cout << endl << "дdataOrder.txt�ļ�";

}

void FileReadWrite::ReadOrderFile()
{
	ifstream myFile;
	myFile.open("dataOrder.txt", ios::in);
	if (!myFile)
	{
		cout << "���ļ�����" << endl;
		return;
	}
	cout << endl << "��ȡdataOrder.txt�ļ�����������ʾ��" << endl;
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
	char tmp[10] = "����";

	//char tmp[2] = "a";

	string a;
	a = "sdffffffff";
	const char* p = a.c_str();
	//char* ��ֵ
//	char ch = 'a';
//	for (int i = 0; i < 10; i++)tmp[i] = ch+i;
//	char* p=tmp;
//	for (int i = 0; i < 10; i++)  *(p + i) = ch + i; 
//	tmp[0] = 1;
	const char* tex = tmp;
	myFile.open("dataRandom.txt", ios::out | ios::binary);
	if (!myFile)
	{
		cout << "���ļ�����" << endl;
		return;
	}
	for (int j = 0; j < 5; j++)
	{
		myFile.write(tex, sizeof(tex));
	//	myFile.write()
	}
	
	myFile.close();
	cout << endl << "дdataRandom.txt�ļ�" << endl;

	/*
	myFile.open("dataRandom.txt", ios::app | ios::binary);
	if (!myFile)
	{
		cout << "���ļ�����";
		return;
	}

	char addtmp[10] = "׷��";
//	tex = addtmp;
	myFile.seekp(100);
	myFile.write((const char*)addtmp, sizeof(tex));
	myFile.close();
	cout << "׷������";
	*/
}

void FileReadWrite::ReadRandomFile()
{
	ifstream myFile;
	myFile.open("dataRandom.txt", ios::in | ios::binary);
	//	myFile.open("1.bmp", ios::in|ios::binary);

	if (!myFile)
	{
		cout << "���ļ�����" << endl;
		return;
	}
	cout << endl << "��dataRandom.txt�ļ�" << endl;
	//�����Ż�ȡ��¼�ı���
//	char tex[100];

	//���ļ���дָ����ļ��Ŀ�ͷ�����һ����¼
//	myFile.seekg(sizeof(tex), ios::beg);
	//��ȡ�ļ��ڶ�����¼
	//myFile.read(tex, sizeof(tex));
	//myFile.read(tex, 1000);
	myFile.seekg(0, ios::end);
	int len = 0;
	len = myFile.tellg();
	cout << "�ļ����ȣ�" << len << endl;

	myFile.seekg(0, ios::beg);
	char* data;
	data = (char*)malloc(len);
	myFile.read(data, len);

	//������п�ת����asscii�����ַ�����ֵ
	cout << endl << (char*)data << endl;

	//��ʮ������������ж���������
	for (int i = 0; i < len; i++)
	{
		cout << hex << (short int)data[i] << " ";
	}

	myFile.close();
}
void FileReadWrite::ReadRandomFilePicture()
{
	ifstream myFile;
	//myFile.open("dataRandom.txt", ios::in | ios::binary);
	myFile.open("a.bmp", ios::in|ios::binary);

	if (!myFile)
	{
		cout << "���ļ�����" << endl;
		return;
	}
	cout << endl << "a.txt�ļ�" << endl;
	//�����Ż�ȡ��¼�ı���
//	char tex[100];

	//���ļ���дָ����ļ��Ŀ�ͷ�����һ����¼
//	myFile.seekg(sizeof(tex), ios::beg);
	//��ȡ�ļ��ڶ�����¼
	//myFile.read(tex, sizeof(tex));
	//myFile.read(tex, 1000);
	myFile.seekg(0, ios::end);
	int len = 0;
	len = myFile.tellg();
	cout << "�ļ����ȣ�" << len << endl;

	myFile.seekg(0, ios::beg);
	char* data;
	data = (char*)malloc(len);
	myFile.read(data, len);

	//������п�ת����asscii�����ַ�����ֵ
	cout << endl << (char*)data << endl;

	//��ʮ������������ж���������
	for (int i = 0; i < len; i++)
	{
		cout << hex << (short int)data[i] << " ";
	}

	myFile.close();
}
void FileReadWrite::ifsr()
{
	cout << endl;
	struct st
	{
	char s[4];

	};
	st s;
	ifstream inFile("dataRandom.txt", ios::in | ios::binary); //�����ƶ���ʽ��
	if (!inFile) {
		cout << "error" << endl;
		
	}
	while (inFile.read((char*)&s, sizeof(s))) { //һֱ�����ļ�����
		int readedBytes = inFile.gcount(); //���ղŶ��˶����ֽ�
		cout << "read: " << readedBytes << " bytes.";// << endl;
		cout <<setw(1)<< s.s << endl;
		//cout << s[0] << " " << s[1] << endl;
	//	cout << (char*)s << endl;
	}
	inFile.close();
}
void FileReadWrite::ofsr()
{
	struct st
	{
		char* s;

	};
	st s;
	char* test =(char*) "����";
	s.s = test;
	ofstream outFile("dataRandom.txt", ios::out | ios::binary); //�����ƶ���ʽ��
	if (!outFile) {
		cout << "error" << endl;

	}
	int writeBytes;
	for (int i = 0; i < 5;++i)
	{
		outFile.write(s.s, sizeof(s.s));  
	}
	outFile.close();
}
