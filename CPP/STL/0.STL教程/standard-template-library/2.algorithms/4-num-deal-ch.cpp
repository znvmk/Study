#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

using namespace std;

int main()
{
	const int N=7;
	int ary1[N]={1,6,3,4,6,5,9};
	vector<int>v1(ary1,ary1+N);
	vector<int>v2(N);
	vector<int>::iterator itv;
	ostream_iterator<int>output(cout," ");

	fill(v2.begin(),v2.end(),10);

	cout<<"original v1:";
	copy(v1.begin(),v1.end(),output);
	cout<<endl<<"original v2:";
	copy(v2.begin(),v2.end(),output);
	cout<<endl;

	cout<<"v1 after reverse():";
	reverse(v1.begin(),v1.end());
	copy(v1.begin(),v1.end(),output);
	cout<<endl;

	cout<<"v1 after remove():";
	itv=remove(v1.begin(),v1.end(),6);	//删除v1中所有的6，共两个
	v1.erase(itv,v1.end());		
	copy(v1.begin(),v1.end(),output);
	cout<<endl;
	
	cout<<"v1 after swap():";
	swap(v1,v2);
	copy(v1.begin(),v1.end(),output);
	cout<<endl<<"v2 after swap():";
	copy(v2.begin(),v2.end(),output);
	cout<<endl;
	return 0;		
}	
