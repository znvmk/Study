#pragma once

class FileReadWrite
{

public:

	void WriteOrderFile();
	void ReadOrderFile();
	void WriteRandomFile();
	void ReadRandomFile();
	void ReadRandomFilePicture();
	void ifsr();
	void ofsr();


};
/*
* 4��char ���ͺϳ�һ��int����
char a = 0x12;
char b = 0x34;
char c = 0x56;
char d = 0x78;
int i = 0; //����λ��0
i = a << 24; //����a���i�����8λ
i |= b << 16; //����b���i�Ĵθ�8λ
i |= c << 8; //����c���i�Ĵε�8λ
i |= d; //�����d���i�����8λ
printf("%x", i); //���12345678
//int���Ϊ4��char�����������̵������
*/