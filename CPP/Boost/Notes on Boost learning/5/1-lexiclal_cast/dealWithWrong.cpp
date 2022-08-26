#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;
int main()
{
	try
	{
		cout << lexical_cast<int>("0x100") << endl;//str->int
		cout << lexical_cast<long>("ehoo") << endl;//str->long
		cout << lexical_cast<double>("1010L") << endl;//str->double
		cout << lexical_cast<double>("false") << endl;//C str->double

	}
	catch(bad_lexical_cast&  e)
	{
		cout << "error:" << e.what() << endl;
	}
	


	system("pause");
	return 0;
}