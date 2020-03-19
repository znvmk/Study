#pragma once
#include "stdafx.h"

#include "iostream"
#include "fstream"
#include "string"


using namespace std;

class CBinaryFileReadWrite
{
public:
	CBinaryFileReadWrite();
	~CBinaryFileReadWrite();


public:
	void ReadFile(const char* filename);
	void ReadFile1(const char* filename);
	void WriteFile(unsigned char* imgbuf, int size);
	void WriteFile1(unsigned char* imgbuf, int size);

};

