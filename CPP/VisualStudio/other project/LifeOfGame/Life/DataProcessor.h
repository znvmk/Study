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
	// Initaliza Setting�����������ʼ������
	void InitSetting(int x, int y, bool put);
	//������������
	void Reset();
	//�ݻ���ʼ
	void Evolution();
	void LoadModel();
};

