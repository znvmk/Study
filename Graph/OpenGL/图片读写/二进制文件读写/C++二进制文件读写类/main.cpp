#pragma once
#include "stdafx.h"

#include "BinaryFileReadWrite.h"



void main()
{
	CBinaryFileReadWrite bfwr;
	bfwr.ReadFile("D:\\1.png");
	bfwr.ReadFile1("D:\\1.png");
	system("pause");
}