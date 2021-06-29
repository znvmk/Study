#include<iostream>
#include<vector>
#include<list>
#include<deque>
#include<algorithm>

using namespace std;

int main()
{
	list<int>col1;
	vector<int>col2;
	for(int i=1;i<9;i++){
		col1.push_back(i);
	}
	col2.resize(col1.size());
	copy(col1.begin(),col1.end(),col2.begin());
	deque<int>col3(col1.size());
	copy(col1.begin(),col1.end(),col3.begin());

}
