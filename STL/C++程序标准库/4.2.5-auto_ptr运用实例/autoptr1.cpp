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
	auto_ptr<int> p(new int(42));
	auto_ptr<int> q;
	cout<<"after initialization:"<<endl;
	cout<<"p:"<<p<<endl;
	cout<<"q:"<<q<<endl;
	q=p;
	cout<<"after assigning auto pointers:"<<endl;
	cout<<"p:"<<p<<endl;
	cout<<"q:"<<q<<endl;
	*q +=13;
	p=q;
	cout<<"after change and reassignment:"<<endl;
	cout<<"p:"<<p<<endl;
	cout<<"q:"<<q<<endl;
}
