#pragma once;

#include "FileReadWrite.h"
#include <iostream>
#pragma warning(disable:4996)

using namespace std;

int main() {
	FileReadWrite frw;
	frw.WriteRandomFile();
	frw.ReadRandomFile();
	/*
	char a = 0x12;
	char b = 0x34;
	char c = 0x56;
	char d = 0x78;
	int i = 0; //所有位置0
	i = a << 24; //先用a填充i的最高8位
	i |= b << 16; //再用b填充i的次高8位
	i |= c << 8; //再用c填充i的次低8位
	i |= d; //最后用d填充i的最低8位
	//printf("%x\n", i); //输出12345678
	char e = 'A';
	a = (int)e;
	i = 0;
	i |= e;
	//printf("%d\n", i);//输出i=65，‘A’的ASCII值

	int j = 87654321;
	*/
	system("pause");
	return 0;

}