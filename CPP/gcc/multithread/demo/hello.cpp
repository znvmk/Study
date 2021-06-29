#include <iostream>
#include <unistd.h>
#include "hello.h"


void hello()
//void* hello(void* ptr)
{
    for(int i=0;i<3;i++) 
    {
        sleep(1);
        std::cout<<"hello world !"<<std::endl;
    }
}
