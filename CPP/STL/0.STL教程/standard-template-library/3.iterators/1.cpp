#include <iostream>
#include <list>

using namespace std;

int main()
{
	int ary[10]={1,7,9,3,2,8,6,2,4,0};
	list<int> l1(ary,ary+10);
	list<int>::iterator itl;
	itl=l1.begin();
	advance(itl,5);		//向后移动5个元素
	cout<<* itl<<" ";
	itl=l1.end();
	advance(itl,-2);	//向前移动2个元素
	cout<<*itl<<endl;
	return 0;
}

