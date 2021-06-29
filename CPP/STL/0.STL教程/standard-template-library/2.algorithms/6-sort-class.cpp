#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class Student
{
public:
	int number;
	string name;

	Student(int i,string s)
	{number=i;name=s;}
	void print()
	{cout<<number<<","<<name<<endl;}
};


struct numbercmp
{
	bool operator()(Student &st1,Student &st2)
	{return st1.number<st2.number;}
};

int main()
{
	Student st1(1003,"wang"),st2(1001,"li"),st3(1002,"zhao");
	vector<Student>v1;
	v1.push_back(st1);
	v1.push_back(st2);
	v1.push_back(st3);

	sort(v1.begin(),v1.end(),numbercmp());
	for(int i=0;i<3;i++)v1[i].print();
	return 0;
}

