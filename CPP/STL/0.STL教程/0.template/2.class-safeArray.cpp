#include <iostream>

using namespace std;

template<typename T,int size>class SafeArray
{
private:
	T ary[size];
public:
	SafeArray();
	T& operator[](int i);
	void Print();
};
template<typename T,int size>SafeArray<T,size>::SafeArray()
{
	for(int i=0;i<size;i++) ary[i]=0;
}
template<typename T,int size>T& SafeArray<T,size>::operator[](int i)
{
	if(i<0||i>=size)
	{
		cout<<"Index out of bound"<<endl;
		exit(0);
	}
	return ary[i];
}
template<typename T,int size>void SafeArray<T,size>::Print()
{
	for(int i=0;i<size;i++) cout<<ary[i]<<" ";
	cout<<endl;
}

int main()
{
	SafeArray<int,5>isa;
	SafeArray<float,4>fsa;
	isa[2]=10;
	fsa[3]=3.1f;
	isa.Print();
	fsa.Print();

	isa[5]=7;
	return 0;
}
