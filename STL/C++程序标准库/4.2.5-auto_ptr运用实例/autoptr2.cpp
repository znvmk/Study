#include<iostream>
#include<memory>

using namespace std;

template <class T>
ostream& operator<<(ostream& strm,const auto_ptr<T>& p)
{
	if(p.get()==NULL)
	{
		strm<<"NULL";
       	}
	else
	{
		strm<<*p;
	}
	return strm;
}

int main()
{
	const auto_ptr<int> p(new int(42));
	const auto_ptr<int> q(new int(0));
	const auto_ptr<int>r;
	cout<<"after initialization:"<<endl;
	cout<<"p:"<<p<<endl;
	cout<<"q:"<<p<<endl;
	cout<<"r:"<<r<<endl;
	*q=*p;
	//*r=*p; //error undefined behavior
	*p=-77;
	cout<<"after assingining values:"<<endl;
	cout<<"p:"<<p<<endl;
	cout<<"q:"<<q<<endl;
	cout<<"r:"<<r<<endl;
	//q=p; //error at compile time
	//r=p; //error at compile time
	
}
