#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

using namespace std;

int main()
{
	int ary1[]={1,3,5,7,9,4,22,17,34};	//不够的元素默认为0
	int ary2[]={98,546,5,58,6584,3};
	int num1=sizeof(ary1)/sizeof(int);
	int num2=sizeof(ary2)/sizeof(int);
	vector<int>v1(ary1,ary1+num1);
	vector<int>v2(ary2,ary2+num2);
	vector<int>v3(num1+num2);
	ostream_iterator<int>output(cout," ");


	cout<<"Original data v1:";
	copy(v1.begin(),v1.end(),output);	//输出数据
	cout<<endl<<"Original data v2:";
	copy(v2.begin(),v2.end(),output);	//输出数据
	sort(v2.begin(),v2.end());		//默认升序
	cout<<endl<<"Sort v2: ";
	copy(v2.begin(),v2.end(),output);	//输出数据

	//以v1.begin()+4处的元素为分界，对前面的元素进行排序
	partial_sort(v1.begin(),v1.begin()+3,v1.end());	
	cout<<endl<<"v1 part sort：";
	copy(v1.begin(),v1.end(),output);
	//合并v1,v2中的元素到v3中幷进行排序
	merge(v1.begin(),v1.end(),v2.begin(),v2.end(),v3.begin());
	sort(v3.begin(),v3.end(),greater<int>());		//设定降序
	cout<<endl<<"Sort v3: ";
	copy(v3.begin(),v3.end(),output);
	cout<<endl;
	return 0;
}

