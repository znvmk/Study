#include<iostream>
#include<list>

using namespace std;

int main()
{
	list<char>col1;
	for(char c='a';c<='z';c++){
		col1.push_back(c);
	}
	list<char>::const_iterator pos;
	for(pos=col1.begin();pos!=col1.end();pos++){
		cout<<*pos<<' ';
	}
	cout<<endl;
}
