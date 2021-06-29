#include <iostream>
#include <deque>

using namespace std;

void print(deque<double> &deq）
{
	size_t numelem=deq.size();
	for(size_t i=0;i<numelem;i++)
		cout<<endl;
}
int main()
{
	deque<double> ds;
	for(size_t i=1;i<5;i++)
	{
		ds.push_front(1.3*i);
		print(ds);
	}
	ds.pop_back();
	print(ds);
	return 0;

}

		
