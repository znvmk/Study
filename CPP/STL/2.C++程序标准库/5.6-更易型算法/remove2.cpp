#include<iostream>
#include<list>
#include<iterator>
#include<algorithm>

using namespace std;

int main()
{
	list<int>col1;
	for(int i=1;i<=6;i++){
		col1.push_front(i);
		col1.push_back(i);
	}
	copy(col1.begin(),col1.end(),ostream_iterator<int>(cout," "));
	cout<<endl;
	list<int>::iterator end=remove(col1.begin(),col1.end(),3);
	copy(col1.begin(),end,ostream_iterator<int>(cout," "));
	cout<<endl;
	cout<<"number of resulting elements:"<<distance(end,col1.end())<<endl;
	col1.erase(end,col1.end());
	copy(col1.begin(),col1.end(),ostream_iterator<int>(cout," "));
	cout<<endl;
}
