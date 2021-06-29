#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main()
{
	int a[5]={3,8,2,7,1};
	vector<int>v1,v2(a,a+5);
	vector<int>::iterator itv;

	v1.insert(v1.begin(),4);
	v1.insert(v1.begin(),6);
	v2.insert(v2.begin(),9);
	v2.insert(v2.end(),5);
	 
	list<int>l1(v2.begin(),v2.end());
	list<int>::iterator itl;
	v2.erase(v2.begin());
	cout<<"v1:";
	for(itv=v1.begin();itv!=v1.end();itv++)
	       	cout<<*itv<<" ";
	cout<<endl<<"v2:";
	for(itv =v2.begin();itv!=v2.end();itv++)
		cout<<*itv<<" ";
	cout<<endl<<"l1:";
	for(itl =l1.begin();itl!=l1.end();itl++)
		cout<<*itl<<" ";
	return 0;
	

}

