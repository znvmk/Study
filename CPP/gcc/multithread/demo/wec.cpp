#include <iostream>
#include <unistd.h>
#include "wec.h"


//void welcome()
void* welcome(void* ptr)
{
	for(int i=0;i<3;i++) 
    {
        sleep(1);
        std::cout<<"Welcome to the world !"<<std::endl;
	}
	return 0;
}

