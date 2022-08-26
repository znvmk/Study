#include "DbQuery.h"
#include <iostream>
#include <fstream>


int main()
{
   //char data[ARRAYSIZE];
   const char *fileName="znsql.zdb";
   DbQuery dq;

   while(1)
   {
	   std::cout<<"****************zdb**************"<<std::endl;
	   std::cout<<"**************Welcom!************"<<std::endl;
	   std::cout<<">>>";
	   char oper[50];
	   //if(getchar()=='\n') continue;
	   std::cin>>oper;
	   
	   std::cout<<"You entered:"<<oper<<std::endl;

	   if(std::strcmp((const char *)oper,"start")==0)
	   {
	       std::cout<<"welcome to user zdb !"<<std::endl;
	   }
	   else if(std::strcmp((const char *)oper,"quit")==0)
		{
	       std::cout<<"Bye !"<<std::endl;
			exit(0);
		}
	   else if(std::strcmp((const char *)oper,"help")==0)
<<<<<<< HEAD
			std::cout<<"Operate:[start],[quit],[help]"<<std::endl;
=======
			std::cout<<"Operate:[start],[quit]"<<std::endl;
>>>>>>> 127b8814dd865e696293b898eb19793bd4de2666
	   else 
		   std::cout<<"Wrong operate !"<<std::endl;
	   //switch(*oper)
	   //{
	   //case "start":
	       //std::cout<<"welcome to user zdb !"<<std::endl;
		   //continue;
		   //break;
	   //case "quit":
	    	//std::cout<<"Bye !"<<std::endl;
			//exit(0);
			 //break;
	   //defalut:
			 //break;
	   //}
   }

   return 0;
}
