#pragma once;

#include "FileReadWrite.h"
#include <iostream>
#pragma warning(disable:4996)

using namespace std;

int main() {
	FileReadWrite frw;
	frw.WriteRandomFile();
	frw.ReadRandomFile();
//	frw.ReadRandomFilePicture();
	frw.ifsr();
	frw.ofsr();
	frw.ifsr();
	/*
	char a = 0x12;
	char b = 0x34;
	char c = 0x56;
	char d = 0x78;
	int i = 0; //����λ��0
	i = a << 24; //����a���i�����8λ
	i |= b << 16; //����b���i�Ĵθ�8λ
	i |= c << 8; //����c���i�Ĵε�8λ
	i |= d; //�����d���i�����8λ
	//printf("%x\n", i); //���12345678
	char e = 'A';
	a = (int)e;
	i = 0;
	i |= e;
	//printf("%d\n", i);//���i=65����A����ASCIIֵ

	int j = 87654321;
	*/
	system("pause");
	return 0;

}