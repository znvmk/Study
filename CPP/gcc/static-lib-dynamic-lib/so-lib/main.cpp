#include <iostream>
#include "test.h"

int main()
{
	std::cout<<testFun(10,20)<<std::endl;

	return 0;
}

/*
 * g++ test.cpp -fPIC -shared -o libtest.so
 * g++ main.cpp -L. -ltest -o main
 * export LD_LIBRARY_PATH=/path/to/library:$LD_LIBRARY_PATH
 * 注：在CygWin中，编译链接需要写动态库得全称：
 * g++ main.cpp -L. -l:libtest.so -o main
 *./main
*/
