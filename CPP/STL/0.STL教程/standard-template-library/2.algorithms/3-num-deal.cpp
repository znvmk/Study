#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

int main()
{
	int ary[]={12,34,7,23,87,71,44,67};
	int num=sizeof(ary)/sizeof(int);
	vector<int>v1(ary,ary+num);
	vector<int>::iterator itv;
	int key=44;

	size_t cnt=count(v1.begin(),v1.end(),key);
	cout<<key<<" presens "<<(int)cnt<<" times :"<<endl;

	itv =find(v1.begin(),v1.end(),key);
	if(itv==v1.end())
		cout<<"not found."<<endl;
	else 
		cout<<"found it,"<<key<<" is at num "<<itv-v1.begin()<<endl;	//元素计数是从0开始的，而不是1.

	itv =max_element(v1.begin(),v1.end());
	cout<<"the max is:"<<*itv<<endl;
	itv =min_element(v1.begin(),v1.end());
	cout<<"the min is:"<<*itv<<endl;


	return 0;
}
			
