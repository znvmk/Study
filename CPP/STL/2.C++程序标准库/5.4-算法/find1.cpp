#include<iostream>
#include<list>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
	list<int>col1;
	vector<int>col2;
	list<int>::iterator pos;
	vector<int>::iterator pos2;
	for(int i=20;i<=40;i++){
		col1.push_back(i);
	}
	for(pos=col1.begin();pos!=col1.end();pos++){
		cout<<*pos<<' ';
	}
	cout<<endl;
	//copy(col1.begin(),col1.end(),col2.begin());
	for(int i=20;i<=40;i++){
		col2.push_back(i);
	}
	for(pos2=col2.begin();pos2!=col2.end();pos2++){
		cout<<*pos2<<' ';
	}
	cout<<endl;
	pos=find(col1.begin(),col1.end(),3);
	reverse(pos,col1.end());
	list<int>::iterator pos25,pos35;
	pos25=find(col1.begin(),col1.end(),25);
	pos35=find(col1.begin(),col1.end(),35);
	cout<<"max:"<<*max_element(pos25,++pos35)<<endl;
	cout<<"max:"<<*max_element(pos25,++pos35)<<endl;
}
