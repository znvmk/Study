#include<iostream>
#include<string>
#include<memory>

using namespace std;

int main()
{
	string s("abed");
	basic_string<char>s1(s.get_allocator());
	basic_string<char>::allocator_type aT=s1.get_allocator();
	string::size_type se=s1.size();
	cout<<se<<endl;
}
