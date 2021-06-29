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
		col1.push_front(i);
		col1.push_back(i);
	}
	cout<<"all:";	
	copy(col1.begin(),col1.end(),ostream_iterator<int>(cout," "));
	cout<<endl;

	col1.erase(remove(col1.begin(),col1.end(),3),col1.end());
	cout<<"remove 3:";
	copy(col1.begin(),col1.end(),ostream_iterator<int>(cout," "));
	cout<<endl;
	
	col1.remove(4);
	cout<<"remove 4:";
	copy(col1.begin(),col1.end(),ostream_iterator<int>(cout," "));
	cout<<endl;
}
