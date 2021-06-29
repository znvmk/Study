#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>

using namespace std;

int main()
{
	const int N=6;
	int ary1[N]={1,2,3,4,5,6};
	int ary2[N]={3,5,7,6,2,9};
	vector<int>v1(ary1,ary1+N);
	vector<int>v2(ary2,ary2+N);
	vector<int>v3(N);
	ostream_iterator<int>output(cout," ");

	cout<<accumulate(v1.begin(),v1.end(),0);	//元素累加和
	cout<<endl;

	partial_sum(v1.begin(),v1.end(),v3.begin());	//部分元素和
	copy(v3.begin(),v3.end(),output);
	cout<<endl;

	adjacent_difference(v2.begin(),v2.end(),v3.begin(),v3.end());	//计算序列中相邻元素的差
	copy(v3.begin(),v3.end(),output);
	cout<<endl;
	//计算两个序列的内积
	cout<<inner_product(v1.begin(),v1.end(),v2.begin(),0);
	return 0;
}


