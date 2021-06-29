#include<iostream>
#include<string>

int main()
{
	const std::string cS("c.bianchen.net");
	std::string s("adobe");
	char temp,temp1,temp2,temp3,temp4,temp5;
	temp=temp1=temp2=temp3=temp4=temp5=0;
	temp=s[2];
	temp1=s.at(2);
	temp2=cS[cS.length()-1];
	temp3=s.at(s.length()-1);
	temp4=s[s.length()-1];
	temp5=cS.at(cS.length()-1);
	std::cout<<temp<<std::endl<<temp1<<std::endl<<temp2<<std::endl<<temp3<<std::endl<<temp4<<std::endl<<temp5<<std::endl;
	return 0;
}
