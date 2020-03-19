#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;
int main()
{
	int x = lexical_cast<int>("100");//str->int
	long y = lexical_cast<long>("2000");//str->long
	float pai = lexical_cast<float>("3.14159e5");//str->float
	double e = lexical_cast<double>("2.71828");//str->double
	double r = lexical_cast<double>("2.71828,x",5);//C str->double

	cout << x << y << pai << e << r << endl;

	string str = lexical_cast<string>(456);//int->str
	cout << str << endl;
	cout << lexical_cast<string>(0.618) << endl;//float->str
	cout << lexical_cast<string>(0x10) << endl;//0x->str


	system("pause");
	return 0;
}