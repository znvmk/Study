#pragma once
#include"stdafx.h"

class CGlobalParameterTransmit
{
public:
	CGlobalParameterTransmit();
	~CGlobalParameterTransmit();

public:
	//全局文件视图类参数传递
	typedef struct GlobalFileviewParameter
	{
		// 分层，深度
		int iStorey;
		//管子(判断是管子(Pipe)还是管接头(Pipe joints)？)
		bool bPiple;
		//编号
		int iNum;
		//头
		int iHead;
		//尾
		int iTail;
		//中间
		int iMiddle;

		
	}GFP;

	//全局文件视图类参数传递
	GFP gfp;

	int a;

public:
	void FileViewParameterVoluation(int iStorey , bool bPiple , int iNum , int iHead , int iTail , int iMiddle);
	void FileViewParameterVoluation(int iStorey , bool bPiple , int iNum , int iHead , int iTail );

};

