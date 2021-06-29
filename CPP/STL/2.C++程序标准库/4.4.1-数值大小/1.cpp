#include<iostream>
#include<algorithm>

using namespace std;

bool int_ptr_less(int* a,int* b)
{
	return *a <*b;
}

int main()
{
	int x=17,y=42;
	int* px=&x;
	int* py=&y;
	int* pmax;

	pmax =max(px,py,int_ptr_less);

	cout<<"*pmax:"<<*pmax<<endl;

	return 0;
}
