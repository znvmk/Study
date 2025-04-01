#pragma once

#define ArrayLength  100

class CDataProcessor
{
public:
	CDataProcessor();
	~CDataProcessor();

public:
	int LifeArray[ArrayLength][ArrayLength] = { 0 };
	int model = 1;

public:
	// Initaliza Setting，生命数组初始化设置
	void InitSetting(int x, int y, bool put);
	//重置生命数组
	void Reset();
	//演化开始
	void Evolution();
	void LoadModel();
};

