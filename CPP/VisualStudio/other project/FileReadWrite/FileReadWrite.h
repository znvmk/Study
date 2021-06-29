#pragma once

class FileReadWrite
{

public:

	void WriteOrderFile();
	void ReadOrderFile();
	void WriteRandomFile();
	void ReadRandomFile();

};
/*
* 4个char 类型合成一个int类型
char a = 0x12;
char b = 0x34;
char c = 0x56;
char d = 0x78;
int i = 0; //所有位置0
i = a << 24; //先用a填充i的最高8位
i |= b << 16; //再用b填充i的次高8位
i |= c << 8; //再用c填充i的次低8位
i |= d; //最后用d填充i的最低8位
printf("%x", i); //输出12345678
//int拆分为4个char就是上述过程的逆过程
*/