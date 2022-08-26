#include <iostream>
#include <fstream>
#include <vector>
#include <boost/timer.hpp>
#include <boost/progress.hpp>

using namespace std;
using namespace boost;
int main()
{
	//字符串向量
	vector<string> v(100);
	//文件输出流
	ofstream fs("test.txt");
	//声明对象，基数是v的大小
	progress_display pd(v.size());
	//开始迭代遍历向量，处理字符串，写入文件
	for (auto& x : v)//for+auto循环
	{
		fs << x << endl;//更新进度显示
		++pd;
	}

	system("pause");
	return 0;
}