#include "pch.h"
#include "DataProcessor.h"

CDataProcessor::CDataProcessor()
{

}

CDataProcessor::~CDataProcessor()
{

}

// Initaliza Setting，生命数组初始化设置
void CDataProcessor::InitSetting(int x, int y, bool put)
{
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			//if (i > 5 && i < 20 && j>20 && j < 35)
				//LifeArray[i][j] = 1;
		}
	}

	//设置生命数组
	if (put)
	{
		if (x >= 0 && x < 40 && y >= 0 && y < 40)
		{
			LifeArray[x][y] = 1;
		}
	}
	else
	{
		if (x >= 0 && x < 40 && y >= 0 && y < 40)
		{
			LifeArray[x][y] = 0;
		}
	}

}


void CDataProcessor::Reset()
{
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			LifeArray[i][j] = 0;
		}
	}
}



// 演化开始
void CDataProcessor::Evolution()
{
	//设置临时容器数组
	int temp[40][40] = { 0 };
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			int life = 0;

			if (i == 0 && j == 0)
			{
				life = 0;
				life += (LifeArray[i][j + 1] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j + 1] == 1) ? 1 : 0;
				goto lab;
			}
			else if (i == 0 && j > 0 && j < 39)
			{
				life = 0;
				life += (LifeArray[i][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i][j + 1] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j + 1] == 1) ? 1 : 0;
				goto lab;
			}
			else if (i == 0 && j == 39)
			{
				life = 0;
				life += (LifeArray[i][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j] == 1) ? 1 : 0;
				goto lab;
			}
			else if (i > 0 && i < 39 && j == 0)
			{
				life = 0;
				life += (LifeArray[i - 1][j] == 1) ? 1 : 0;
				life += (LifeArray[i - 1][j + 1] == 1) ? 1 : 0;
				life += (LifeArray[i][j + 1] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j + 1] == 1) ? 1 : 0;
				goto lab;
			}
			else if (i > 0 && i < 39 && j >0 && j< 39)
			{
				life = 0;
				life += (LifeArray[i - 1][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i - 1][j] == 1) ? 1 : 0;
				life += (LifeArray[i - 1][j + 1] == 1) ? 1 : 0;
				life += (LifeArray[i][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i][j + 1] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j + 1] == 1) ? 1 : 0;
				goto lab;
			}
			else if (i > 0 && i < 39 && j == 39)
			{
				life = 0;
				life += (LifeArray[i - 1][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i - 1][j] == 1) ? 1 : 0;
				life += (LifeArray[i][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j] == 1) ? 1 : 0;
				goto lab;
			}
			else if (i == 39 && j == 0)
			{
				life = 0;
				life += (LifeArray[i - 1][j] == 1) ? 1 : 0;
				life += (LifeArray[i - 1][j + 1] == 1) ? 1 : 0;
				life += (LifeArray[i][j + 1] == 1) ? 1 : 0;
				goto lab;
			}
			else if (i == 39 && j > 0 && j < 39)
			{
				life = 0;
				life += (LifeArray[i - 1][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i - 1][j] == 1) ? 1 : 0;
				life += (LifeArray[i - 1][j + 1] == 1) ? 1 : 0;
				life += (LifeArray[i][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i][j + 1] == 1) ? 1 : 0;
				goto lab;
			}
			else if (i == 39 && j == 39)
			{
				life = 0;
				life += (LifeArray[i - 1][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i - 1][j] == 1) ? 1 : 0;
				life += (LifeArray[i][j - 1] == 1) ? 1 : 0;
				goto lab;
			}
		lab:
			{
				if (life == 3)
				{
					temp[i][j] = 1;
				}
				else if (life == 2)
				{
					temp[i][j] = LifeArray[i][j];
				}
				else
				{
					temp[i][j] = 0;
				}
			}
		}
	}

	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			LifeArray[i][j] = temp[i][j];
		}
	}
}
