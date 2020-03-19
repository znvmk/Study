#include"stdafx.h"
#include"Hello.h"
#include<time.h>
const int TIME_MAX = 32;

void pruintDate()
{
	//定义tm结构的时间变量
	struct tm newdate;
	
	//定义time_t结构的时间变量
	time_t long_date;
	//获取时间
	time(&long_date);

	//将时间转换为本地时间
	 localtime_s(&newdate, &long_date);

	 char stTmp[TIME_MAX];

	 asctime_s(stTmp, &newdate);
	//打印当前时间
	 printf("当前时间是：%s\n", stTmp);

}