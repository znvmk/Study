#include <iostream>
#include <thread>
#include "thread-t.h"
#include "hello.h"
#include "wec.h"


void threadhe()
{
    std::thread he(hello);
    he.join();
}
void threadwe()
{
    //std::thread we(welcome);
    //we.join();
}
