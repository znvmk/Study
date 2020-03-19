#include<iostream>
#include<map>
#include<string>

using namespace std;

int main()
{
	typedef map<string,float>StringFloatMap;
	StringFloatMap col1;
	col1["VAT"]=0.15;
	col1["PI"]=3.1415;
	col1["an arbitrary number"]=4983.223;
	col1["Null"]=0;

	StringFloatMap::iterator pos;
	for(pos=col1.begin();pos !=col1.end();pos++){
		cout<<"key:\""<<pos->first<<"\" "<<"value:"<<pos->second<<endl;
	}
}
