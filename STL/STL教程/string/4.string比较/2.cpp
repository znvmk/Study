#include<iostream>
#include<string>

using namespace std;

void TureOrFalse(int x)
{
	cout<<(x?"Ture":"False")<<endl;
}

int main()
{
	string s1="DEF";
	string cp1="ABC";
	string cp2="DEF";
	string cp3="DEFG";
	string cp4="def";
	cout<<"s1="<<s1<<endl;
	cout<<"cp1"<<cp1<<endl;
	cout<<"cp2"<<cp2<<endl;
	cout<<"cp3"<<cp3<<endl;
	cout<<"cp4"<<cp4<<endl;
	cout<<" s1<=cp1 returned ";
	TureOrFalse(s1<=cp1);
	cout<<" s1<=cp2 returned ";
	TureOrFalse(s1<=cp2);
	cout<<" s1<=cp3 returned ";
	TureOrFalse(s1<=cp3);
	cout<<" cp1<=s1 returned ";
	TureOrFalse(cp1<=s1);
	cout<<" cp2<=s1 returned ";
	TureOrFalse(cp2<=s1);
	cout<<" cp4<=s1 returned ";
	TureOrFalse(cp4<=s1);
	return 0;


}
