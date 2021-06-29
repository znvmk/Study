#include<iostream>
#include<vector>
#include<list>
#include<deque>
#include<set>
#include<algorithm>

using namespace std;

int main()
{
	list<int>col1;
	for(int i=1;i<=9;i++){
		col1.push_back(i);
	}
	vector<int>col2;
	copy(col1.begin(),col1.end(),back_inserter(col2));
	deque<int>col3;
	copy(col1.begin(),col1.end(),front_inserter(col3));
	set<int>col4;
	copy(col1.begin(),col1.end(),inserter(col4,col4.begin()));
}
