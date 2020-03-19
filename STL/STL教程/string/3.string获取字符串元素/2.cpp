#include<iostream>
#include<string>

int main()
{
	std::string s("adobe");
	std::cout<<s<<std::endl;
	char& r=s[2];
	char* p=&s[3];
	r='X';
	*p='Y';
	std::cout<<s<<std::endl;
	return 0;
}
