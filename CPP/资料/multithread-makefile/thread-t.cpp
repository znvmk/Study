#include "thread-t.h"
#include <thread>
#include "hello.h"
#include <iostream>


void usethread()
{
    std::thread t(hello);
    t.join();
}
