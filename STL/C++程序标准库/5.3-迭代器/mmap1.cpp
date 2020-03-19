#include<iostream>
#include<map>
#include<string>

using namespace std;

int main()
{
	typedef multimap<int,string>IntStringMMap;
	IntStringMMap col1;

	col1.insert(make_pair(5,"tagged"));
	col1.insert(make_pair(2,"a"));
	col1.insert(make_pair(1,"this"));
	col1.insert(make_pair(4,"of"));
	col1.insert(make_pair(6,"strings"));
	col1.insert(make_pair(1,"is"));
	col1.insert(make_pair(3,"multimap"));
	IntStringMMap::iterator pos;
	for(pos=col1.begin();pos !=col1.end();pos++){
		cout<<pos->second<<' ';
	}

	cout<<endl;
}
