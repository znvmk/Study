//寻找第一个质数
#include <iostream>
#include <list>
#include <algorithm>
#include <cstdlib> //for abs()

using namespace std;

bool isPrime(int number)
{
	number =abs(number);
	if(number == 0 || number ==1)
	{
		return true;
	}
	
	int divisor;
	for(divisor=number/2;number%divisor !=0;divisor--)
	{;}
	return divisor==1;
}

int main()
{
	list<int>col1;
	for(int i=24;i<=30;i++)
	{
		col1.push_back(i);
	}
	list<int>::iterator pos;
	pos =find_if(col1.begin(),col1.end(),isPrime);
	if(pos!=col1.end())
	{
		cout<<*pos<<" is the first prime number found."<<endl;
	}
	else
	{
		cout<<"prime number not found."<<endl;
	}

	return 0;
}

