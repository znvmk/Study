#include "stdafx.h"
#include "GOProcess.h"


CGOProcess::CGOProcess()
{
	
	flag = 0;
	//GameStart();
}


CGOProcess::~CGOProcess()
{
}

void CGOProcess::GameStart()
{
	//初始化围棋数组
	for (int i = 0;i<19;i++)
		for (int j = 0;j < 19;j++)
			GOMap[i][j] = 0;
			

	flag=1;
	
	step=0;
	
	BlackTaking = 0;
	WhiteTaking = 0;
	
	BlackTime = 0;
	WhiteTime = 0;
	
	stepTime = 0;
	
	komi = 7.5;

	
	coordinateX1 = -1;
	coordinateY1 = -1;
	coordinateX2 = -1;
	coordinateY2 = -1;
}

CString CGOProcess::TimeConvert(int seconds)
{
	int hour;
	int minute;
	int second;
	CString time;
	hour = minute = second = 0;
	hour = seconds / 3600;
	seconds -= hour * 3600;
	minute = seconds / 60;
	seconds -= minute * 60;
	second = seconds;

	CString strtemp;

	strtemp.Format(_T("%d"), hour);
	if (hour < 10)
	{
		time = "0";
		time += strtemp;
		time += ":";
	}
	else
	{
		time = strtemp;
		time += ":";
	}
	
	 
	strtemp.Format(_T("%d"), minute);
	if (minute < 10)
	{
		time += "0";
		time += strtemp;
		time += ":";
	}
	else
	{
		time += strtemp;
		time += ":";
	}

	strtemp.Format(_T("%d"),second);
	if (second < 10)
	{
		time += "0";
		time += strtemp;
	}
	else
	{
		time += strtemp;
	}

	return time;
}