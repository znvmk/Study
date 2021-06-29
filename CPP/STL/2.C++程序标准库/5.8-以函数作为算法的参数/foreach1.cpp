#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void paint(int elem)
{
	cout<<elem<<' ';
}

int main()
{
	vector<int>col1;
	for(int i=1;i<+9;i++)
	{
		col1.push_back(i);
	}

	for_each (col1.begin(),col1.end(),paint);
	cout<<endl;
	//for_each(col1.begin(),col1.end(),paint());
	cout<<endl;

	return 0;

}
