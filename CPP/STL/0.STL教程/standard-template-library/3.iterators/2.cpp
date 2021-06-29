#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int a[5]={1,3,5,7,9};
	vector<int>v1(a,a+5);
	vector<double>v2;
	vector<int>::iterator itv;
	vector<int>::const_iterator citv;//只读迭代器
	v2.push_back(3.14);
	//itv =v2.begin();//出错，容器元素类型必须和迭代器元素类型一致
	for(itv =v1.begin();itv!=v1.end();itv++)
		*itv +=20;
	for(citv=v1.begin();citv!=v1.end();citv++)
		cout<<*citv<<" ";
	cout<<endl;
	return 0;
}

