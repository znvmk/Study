#include<iostream>
#include<string>

using namespace std;

int main()
{
	string var("abcdefghigklmn");
	const string dest("1234");
	string dest2("567891234");
	var.replace(3,3,dest);
	cout<<"1:"<<var<<endl;
	var="abcefghigklmn";
	var.replace(3,1,dest.c_str(),1,3);
	cout<<"2:"<<var<<endl;
	var="abcefghigklmn";
	var.replace(3,1,dest.c_str(),1,3);
	cout<<"2:"<<var<<endl;
	var="abcefghigklmn";
	var.replace(3,1,5,'x');
	cout<<"3:"<<var<<endl;
	string::iterator itA,itB,itC,itD;
	var="abcefghigklmn";
	//var.replace(itA,itB,dest.begin()+1,dest.end());
	cout<<"4:"<<var<<endl;
	itA=var.begin();
	itB=var.end();
	itC=dest2.begin()+1;
	itD=dest2.end();
	var="abcefghigklmn";
	var.replace(itA,itB,itC,itD);
	cout<<"5:"<<var<<endl;
	var="abcefghigklmn";
	var.replace(3,1,dest.c_str(),4);
	cout<<"6:"<<var<<endl;
	return 0;
}
