#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include "print.hpp"

using namespace std;

int square(int value)
{
	return value*value;
}

int main()
{
	set<int>col1;
	vector<int>col2;

	for(int i=1;i<=9;i++)
	{
		col1.insert(i);
	}
	PRINT_ELEMENTS(col1,"initialized: ");

	transform(col1.begin(),col1.end(),back_inserter(col2),square);
	PRINT_ELEMENTS(col2,"squared: ");
	cout<<endl;

	copy(col1.begin(),col1.end(),back_inserter(col2));
	//col2.pash_back(123);

	PRINT_ELEMENTS(col2,"squared: ");
	cout<<endl;

	//transform(col1.begin(),col1.end(),back_inserter(col2),square);
	//PRINT_ELEMENTS(col2,"squared: ");
	//cout<<endl;
	transform(col2.begin(),col2.end(),back_inserter(col2),square);
	PRINT_ELEMENTS(col2,"squared: ");
	cout<<endl;
	
	return 0;
}	
