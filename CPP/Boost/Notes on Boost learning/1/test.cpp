#include <boost/lexical_cast.hpp>
#include <iostream>
using namespace std;
int main()
{
	using boost::lexical_cast;
	int a = lexical_cast<int>("123");
	double b = lexical_cast<double>("123.0123456789");
	string s0 = lexical_cast<string>(a);
	string s1 = lexical_cast<string>(b);
	cout << "number: " << a << "  " << b << endl;
	cout << "string: " << s0 << "  " << s1 << endl;
	int c = 0;
	try {
		c = lexical_cast<int>("abcd");
	}
	catch (boost::bad_lexical_cast& e) {
		cout << e.what() << endl;
	}

	system("pause");
	return 0;
}