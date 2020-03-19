#pragma once

class CDataProcessor
{
public:
	CDataProcessor();
	~CDataProcessor();

public:
	int LifeArray[40][40] = { 0 };

public:
	// Initaliza Setting，生命数组初始化设置
	void InitSetting(int x,int y, bool put);
	//重置生命数组
	void Reset();
	//演化开始
	void Evolution();
};

