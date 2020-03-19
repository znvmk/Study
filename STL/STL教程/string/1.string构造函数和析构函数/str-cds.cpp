#include<iostream>
#include<string>

using namespace std;

int main()
{
	string str("123456789");
	char ch[]="abcdefgh";
	string a;//定义一个空字符串
	string str1(str);//构造函数，全部复制
	string str2(str,2,5);//构造函数，从字符串str的第2个字符开始，复制5个字符，赋值给str2
	string str3(ch,5);//将字符串ch的前5个字符赋值给str_3
	string str4(5,'X');//将5个'X'组成的字符串“XXXXX”赋值给str4
	string str5(str.begin(),str.end());//复制字符串str的所有字符到str5
	cout<<str<<endl<<ch<<endl;
	cout<<str1<<endl<<str2<<endl<<str3<<endl<<str4<<endl<<str5<<endl;
	return 0;
}
