#include<iostream>
#include<fstream>
#include<cmath>
#include <string>

using namespace std; 

int main()
{
   //*
    unsigned short a[10] = { 1,2,3,4,5,10,20,30,45,50 };
    unsigned short b[10];

    ofstream ouF;
    ouF.open("me.dat", std::ofstream::binary);
    ouF.write(reinterpret_cast<const char*>(a), sizeof(short) * 10);
    ouF.close();

    ifstream inF;
    inF.open("me.dat", std::ifstream::binary);
    inF.read(reinterpret_cast<char*>(b), sizeof(short) *10);
    inF.close();

    for (int i = 0; i < 10; i++)
    {
        cout <<hex<< b[i] << " ";
    }
   // */
    /*
    int a[5] = { 1,2,3,4,50 };
    unsigned short b[100];
    int size;

    ofstream ouF;
    ouF.open("me.bmp", std::ofstream::binary);
    size = ouF.tellp();
    //ouF.seekp(size);
     unsigned short bd[58] = { 0x42, 0x4d, 0x3a, 0, 0, 0, 0, 0, 0, 0, 0x36, 0, 0, 0, 0x28, 0, 
         0, 0, 0x1, 0, 0, 0, 0x1, 0, 0, 0, 0x1, 0, 0x18, 0, 0, 0, 
         0, 0, 0x4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0x7c, 0x9a, 0xc6, 0};
    int length = sizeof(bd) / sizeof(bd[0]);
   // length -= 4;
    //for (int i = 0; i < length; i++)
      //  ofile << bd[i];
    ouF.write(reinterpret_cast<const char*>(bd), sizeof(unsigned short)*58);
    ouF.close();

    ifstream inF;
    inF.open("me.bmp", std::ifstream::binary);
    size = inF.tellg();
    cout << "size: " << size << endl;
    inF.read(reinterpret_cast<char*>(b), sizeof(bd));
    inF.close();

    for (int i = 0; i < 58; i++)
    {
        cout <<hex<< b[i] << " ";
    }



   /*
    ofstream ofile;
    ofile.open("3.bmp",ios::binary);
    //像cout一样输入向文件输入数据
    //unsigned short bd[] = { 0x42, 0x4d, 0x3a, 0, 0, 0, 0, 0, 0, 0, 0x36, 0, 0, 0, 0x28, 0, 0, 0, 0x1, 0, 0, 0, 0x1, 0, 0, 0, 0x1, 0, 0x18, 0, 0, 0, 0, 0, 0x4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x7c, 0x9a, 0xc6, 0, 0xffff };
    //int length = sizeof(bd) / sizeof(bd[0]);
    //for (int i = 0; i < length; i++)
      //  ofile << bd[i];
    unsigned short tes = 0x0;
    int is = tes;
    is -= 12543;
    int size = 0;
    size = ofile.tellp();
    cout << "size: " << size << endl;
    ofile <<is;
    //ofile << tes;
    ofile.close();

    ifstream ifile;
   // char output[100];
    int x;
    x = 2;
    ifile.open("3.bmp",ios::binary);
  
    char ac_temp[1000] = { 0 };
    string s_out;
    s_out = "";
    unsigned short us;
    int temp;
    string su;
    su = "";
    while (!ifile.eof())
    {
        us = ifile.get();
        cout <<hex<< us<<" ";
        temp = us;
              
       
        su += to_string(temp);//包含头文件#include <string>
        su += " ";
       
    }
    cout << endl<< su;
//*/

/****** short,unsigned short基本数据类型测试
    unsigned short us,usm;
    us =0xffff;
    usm = -1;
   short smax =0;
    smax = 0x7fff;//最高位是符号位，+-0x7fff，bin:0111 1111 1111 1111
   // s = 0xfff0;
    int i;
    i = 0xff;
    int ismax = pow(2, 14) + pow(2, 13) + pow(2, 12) + pow(2, 11) + pow(2, 10) + pow(2, 9) + pow(2, 8) + pow(2, 7) + pow(2, 6) + pow(2, 5) + pow(2, 4) + pow(2, 3) + pow(2, 2) + pow(2, 1) + 1;
    //cout << sizeof(short) << endl;
    cout <<hex<< "us:" << us<<endl;
    cout << hex << "usm:" << usm << endl;
    cout <<dec<< "smax:" << smax<<endl;
    cout <<dec<< "2^15 阶乘:" << ismax << endl;
    cout <<dec<< "us max 2^16阶乘 i:" << usm<<endl;
    cout << dec << "i:" << i << endl;
    */
    system("pause");
	return  0;
}