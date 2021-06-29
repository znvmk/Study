#include "thread-t.h"
//#pragma once
#include <iostream>
#include <thread>
#include <pthread.h>
#include <unistd.h>
#include "hello.h"
#include "wec.h"

using namespace std;

void* welcomem(void* ptr)
{
	for(int i=0;i<3;i++) 
    {
        sleep(1);
        std::cout<<"Welcome to the world !"<<std::endl;
	}
	return 0;
}

int main(int argc,char* argv[])
{
	//hello();
	//welcome();
	thread he(hello);
	//thread we(welcome);	


	//pthread_t phe,pwe;
	pthread_t pwe;
	/*
	int pheRet=pthread_create(&phe,NULL,&hello,NULL);
	if(pheRet)
	{
		cout<<"create pthread hello error！"<<endl;
		return 1;
	}
	*/
	int pweRet=pthread_create(&pwe,NULL,welcome,NULL);
	if(pweRet)
	{
		cout<<"create pthread welcome error！"<<endl;
		return 1;
	}

	//cout<<argv[0]<<"  "<<argv[1]<<endl;

	//if(argc>0 && argv[1]=="t") 
	{
		//he.join();
		//we.join();
	}
	threadhe();
	//threadwe();
	
	//if(argc>0 && argv[1]=="pt"||argc<1) 
	//{
		//pthread_join(phe,NULL);
		//pthread_join(pwe,NULL);
	//}
	//hello();
	pthread_join(pwe,NULL);
					
    //usethread();
    return 0;
}

