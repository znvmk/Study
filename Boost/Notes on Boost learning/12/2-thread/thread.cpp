#define BOOST_THREAD_VERSION 4


#include <iostream>
#include <boost/atomic.hpp>
#include <boost/thread.hpp>

using namespace std;
using namespace boost;

void dummy(int n)
{
	for (int i = 0; i < n; i++);
	cout << n << endl;
}

int main()
{
	thread t1(dummy, 100);
	thread t2(dummy, 500);

	//this_thread::sleep_for(200_ms);
	


	std::system("pause");
	return 0;
}