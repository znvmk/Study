#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
using namespace std;


void WriteOrderFile(int r, int g, int b,int l);
string ColorConvert(int r, int g, int b);


void ReadOrderFile();
//Ëæ»úÎÄ¼þ¶ÁÐ´
struct Record;
void WriteRandomFile();
void ReadRandomFile();