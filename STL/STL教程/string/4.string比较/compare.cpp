#include<iostream>
#include<string>

using namespace std;

int main()
{
	string A("aBcDef");
	string B("AbcdEf");
	string C("123456");
	string D("123dfg");

	int m=A.compare(B);//完整的A和B比较
	int n=A.compare(1,5,B,4,2);//A的1位置开始后的5个元素和B的4位置开始后的2个元素比较
	int p=C.compare(1,5,B,4,2);
	int q=C.compare(0,3,D,0,3);
	cout<<"m="<<m<<endl<<"n="<<n<<endl<<"p="<<p<<endl<<"q="<<q<<endl;
	return 0;
}
