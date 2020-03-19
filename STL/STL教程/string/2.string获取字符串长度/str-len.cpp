#include<iostream>
#include<string>

using namespace std;

int main()
{
	int size=0;
	int length=0;
	unsigned long maxsize=0;
	int capacity=0;
	string str("123456789");
	string str_custom=str;
	str_custom.resize(5);
	size=str_custom.size();
	length=str_custom.length();
	maxsize=str_custom.max_size();
	capacity=str_custom.capacity();
	cout<<"size="<<size<<endl;
	cout<<"length="<<length<<endl;
	cout<<"maxsize="<<maxsize<<endl;
	cout<<"capacity="<<capacity<<endl;
	return 0;
}
