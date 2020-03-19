#include<iostream>
#include<list>
#include<algorithm>
#include<iterator>

using namespace std;

int main()
{
	list<int>col1;
	for(int i=1;i<=6;i++){
		col1.push_front(i);
		col1.push_back(i);
	}
	cout<<"pre:";
	copy(col1.begin(),col1.end(),ostream_iterator<int>(cout," "));
	cout<<endl;
	remove(col1.begin(),col1.end(),3);
	cout<<"post:";
	copy(col1.begin(),col1.end(),ostream_iterator<int>(cout," "));
	cout<<endl;
}
