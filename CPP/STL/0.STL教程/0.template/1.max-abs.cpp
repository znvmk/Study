#include <iostream>
#include <cstring>

using namespace std;

template<typename T>T Max(T a,T b)
{
	return a>b?a:b;
}
template<typename T>T Abs(T a,T b)
{
	return a>=0?a:-a;
}
template<typename T>T& MaxClass(T& a,T& b) //使用引用来传递对象
{
	return a>b?a:b;
}

char* Max(char* pa,char* pb)
{
	return strcmp(pa,pb)>0?pa:pb;
}
//////////////////////////////
//模板与类结合

class Student
{
	int number;
	char name[20];
public:
	Student(int number,char* name) //构造
	{
		this->number = number;
		//this->name = name;
		strcpy(this->name,name);
	}
	bool operator > (Student &st)
	{
		return this->number>st.number;
	}
	void Print()
	{
		cout<<"Number:"<<this->number<<endl;
		cout<<"Name:"<<this->name<<endl;
	}
};

	

int main(void)
{
	int ia=-5,ib=11,ic;
	float fa=3.14f,fb=7.2f,fc;
	Student st1(12,"Zhang"),st2(11,"Li"),st3(0,"");

	cout<<"ia="<<ia<<",ib="<<ib<<endl<<"fa="<<fa<<",fb="<<fb<<endl;
	cout<<"st1:";st1.Print();
	cout<<"st2:";st2.Print();
	cout<<"st3:";st3.Print();

	ic=Max(ia,ib);
	cout<<"Max(ia,ib)="<<ic<<endl;
	ic=Abs(ia,ib);
	cout<<"Abs(ia,ib)="<<ic<<endl;

	fc=Max(fa,fb);
	cout<<"Max(fa,fb)="<<fc<<endl;
	fc=Abs(fa,fb);
	cout<<"Abx(fa,fb)="<<fc<<endl;

	cout<<"如果是特殊类型，需要自己定义重载，程序会先进行重载匹配，而不是模板匹配"<<endl;
	cout<<"Max(\"Hello\",\"Fellow\")="<<Max("Hello","Fellow")<<endl;

	cout<<"st3=Max(st1,st2):"<<endl;
	st3=MaxClass(st1,st2);
	st3.Print();

	return 0;
}

	
