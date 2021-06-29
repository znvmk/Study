#include <iostream>
#include <iomanip>
#include <string>
#include <map>

using namespace std;
 
int main()
{
	string snames[3]={"red","blue","green"};
	int colors[3]={0xff0000,0x00ff00,0x0000ff};
	map<string,int>m1;
	for(int i=0;i<3;i++)
		m1[snames[i]]=colors[i];
	cout<<"red color = ";
	cout<<hex<<setw(6)<<setfill('0');
	cout<<m1["red"]<<endl;
	cout<<"green color = ";
	cout<<hex<<setw(6)<<setfill('0');
	cout<<m1["green"]<<endl;
	cout<<"blue color = ";
	cout<<hex<<setw(6)<<setfill('0');
	cout<<m1["blue"]<<endl;
	
	return 0;
}

