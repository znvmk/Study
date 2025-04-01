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
	for (int i = 0; i < ArrayLength; i++)
	{
		for (int j = 0; j < ArrayLength; j++)
		{
			//if (i > 5 && i < 20 && j>20 && j < 35)
				//LifeArray[i][j] = 1;
		}
	}

	//设置生命数组
	if (put)
	{
		if (x >= 0 && x < ArrayLength && y >= 0 && y < ArrayLength)
		{
			LifeArray[x][y] = 1;
		}
	}
	else
	{
		if (x >= 0 && x < ArrayLength && y >= 0 && y < ArrayLength)
		{
			LifeArray[x][y] = 0;
		}
	}

}


void CDataProcessor::Reset()
{
	for (int i = 0; i < ArrayLength; i++)
	{
		for (int j = 0; j < ArrayLength; j++)
		{
			LifeArray[i][j] = 0;
		}
	}
}

void CDataProcessor::LoadModel()
{
	CDataProcessor::Reset();
	if (model > 3) model = 1;
	model = 1;
	switch (model)
	{
	case 1:
		//model1:
		LifeArray[1][5] = 1; LifeArray[1][6] = 1; LifeArray[2][5] = 1; LifeArray[2][6] = 1;
		LifeArray[11][6] = 1; LifeArray[12][5] = 1; LifeArray[12][6] = 1; LifeArray[12][7] = 1;
		LifeArray[13][4] = 1; LifeArray[13][5] = 1; LifeArray[13][6] = 1; LifeArray[13][7] = 1;
		LifeArray[13][8] = 1; LifeArray[14][3] = 1; LifeArray[14][4] = 1; LifeArray[14][8] = 1;
		LifeArray[14][9] = 1; LifeArray[15][4] = 1; LifeArray[15][5] = 1; LifeArray[15][6] = 1;
		LifeArray[15][7] = 1; LifeArray[15][8] = 1; LifeArray[16][4] = 1; LifeArray[16][8] = 1;
		LifeArray[17][5] = 1; LifeArray[17][7] = 1; LifeArray[18][6] = 1; LifeArray[21][4] = 1;
		LifeArray[22][2] = 1; LifeArray[22][3] = 1; LifeArray[22][5] = 1; LifeArray[22][6] = 1;
		LifeArray[24][1] = 1; LifeArray[24][7] = 1; LifeArray[26][1] = 1; LifeArray[26][2] = 1;
		LifeArray[26][4] = 1; LifeArray[26][6] = 1; LifeArray[26][7] = 1; LifeArray[35][3] = 1;
		LifeArray[35][4] = 1; LifeArray[36][3] = 1; LifeArray[36][4] = 1;
		break;
	case 2:
		//model2:y+10
		LifeArray[2][14] = 1; LifeArray[2][15] = 1; LifeArray[3][14] = 1; LifeArray[3][15] = 1;
		LifeArray[6][17] = 1; LifeArray[6][18] = 1; LifeArray[7][17] = 1; LifeArray[7][18] = 1;
		LifeArray[9][14] = 1; LifeArray[9][15] = 1; LifeArray[10][14] = 1; LifeArray[10][15] = 1;
		LifeArray[19][17] = 1; LifeArray[20][16] = 1; LifeArray[20][18] = 1; LifeArray[22][16] = 1;
		LifeArray[22][17] = 1; LifeArray[23][18] = 1;LifeArray[23][19] = 1; LifeArray[24][20] = 1;
		LifeArray[24][21] = 1;  LifeArray[25][18] = 1; LifeArray[25][20] = 1;LifeArray[25][21] = 1;
		LifeArray[26][18] = 1;LifeArray[26][19] = 1; LifeArray[26][25] = 1; LifeArray[26][26] = 1; 
		LifeArray[27][25] = 1;LifeArray[27][26] = 1; LifeArray[29][22] = 1; LifeArray[29][23] = 1; 
		LifeArray[30][22] = 1;LifeArray[30][23] = 1; LifeArray[33][25] = 1; LifeArray[33][26] = 1; 
		LifeArray[34][25] = 1;LifeArray[34][26] = 1; 
		//阻挡滑翔翼
		//LifeArray[22][31] = 1; LifeArray[22][32] = 1; LifeArray[24][33] = 1; LifeArray[23][33] = 1; LifeArray[25][33] = 1; LifeArray[23][31] = 1; LifeArray[25][34] = 1;
		break;
	case 3:
		//model3：x+10,y+10
		LifeArray[10][10] = 1; LifeArray[19][10] = 1; LifeArray[11][11] = 1; LifeArray[12][11] = 1;
		LifeArray[17][11] = 1; LifeArray[18][11] = 1; LifeArray[11][12] = 1; LifeArray[12][12] = 1;
		LifeArray[13][12] = 1; LifeArray[14][12] = 1; LifeArray[15][12] = 1; LifeArray[16][12] = 1;
		LifeArray[17][12] = 1; LifeArray[18][12] = 1; LifeArray[11][13] = 1; LifeArray[14][13] = 1;
		LifeArray[15][13] = 1; LifeArray[18][13] = 1;LifeArray[13][14] = 1; LifeArray[16][14] = 1;
		LifeArray[13][16] = 1;  LifeArray[16][16] = 1; LifeArray[14][17] = 1; LifeArray[15][17] = 1;
		break;
	default:break;
	}
	model++;
}

// 演化开始
void CDataProcessor::Evolution()
{
	//设置临时容器数组
	int temp[ArrayLength][ArrayLength] = { 0 };
	for (int i = 0; i < ArrayLength; i++)
	{
		for (int j = 0; j < ArrayLength; j++)
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
			else if (i == 0 && j > 0 && j < 99)
			{
				life = 0;
				life += (LifeArray[i][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i][j + 1] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j + 1] == 1) ? 1 : 0;
				goto lab;
			}
			else if (i == 0 && j == 99)
			{
				life = 0;
				life += (LifeArray[i][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j] == 1) ? 1 : 0;
				goto lab;
			}
			else if (i > 0 && i < 99 && j == 0)
			{
				life = 0;
				life += (LifeArray[i - 1][j] == 1) ? 1 : 0;
				life += (LifeArray[i - 1][j + 1] == 1) ? 1 : 0;
				life += (LifeArray[i][j + 1] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j + 1] == 1) ? 1 : 0;
				goto lab;
			}
			else if (i > 0 && i < 99 && j >0 && j < 99)
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
			else if (i > 0 && i < 99 && j == 99)
			{
				life = 0;
				life += (LifeArray[i - 1][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i - 1][j] == 1) ? 1 : 0;
				life += (LifeArray[i][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i + 1][j] == 1) ? 1 : 0;
				goto lab;
			}
			else if (i == 99 && j == 0)
			{
				life = 0;
				life += (LifeArray[i - 1][j] == 1) ? 1 : 0;
				life += (LifeArray[i - 1][j + 1] == 1) ? 1 : 0;
				life += (LifeArray[i][j + 1] == 1) ? 1 : 0;
				goto lab;
			}
			else if (i == 99 && j > 0 && j < 99)
			{
				life = 0;
				life += (LifeArray[i - 1][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i - 1][j] == 1) ? 1 : 0;
				life += (LifeArray[i - 1][j + 1] == 1) ? 1 : 0;
				life += (LifeArray[i][j - 1] == 1) ? 1 : 0;
				life += (LifeArray[i][j + 1] == 1) ? 1 : 0;
				goto lab;
			}
			else if (i == 99 && j == 99)
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

	for (int i = 0; i < ArrayLength; i++)
	{
		for (int j = 0; j < ArrayLength; j++)
		{
			LifeArray[i][j] = temp[i][j];
		}
	}
}
