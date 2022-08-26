#include <iostream>
#include <boost/format.hpp>

using namespace std;
using namespace boost;
int main()
{
	cout << format("%s:%d+%d=%d\n") % "sum" % 1 % 2 % (1 + 2);

	format fmt("(%1% + %2%) * %2% = %3%\n");
	fmt % 2 % 5;
	fmt % ((2 + 5) * 5);
	cout << fmt.str();
	


	system("pause");
	return 0;
}