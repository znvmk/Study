#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
	int a[5]={1,3,5,7,9};
	vector<int>v1(a,a+5);
	ostream_iterator<int>output(cout," ");
	copy(v1.begin(),v1.end(),output);
	return 0;
}

