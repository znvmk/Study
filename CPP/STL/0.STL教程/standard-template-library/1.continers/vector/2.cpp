#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	vector<string>vs;
	string s1="We ";
	vs.push_back(s1);
	vs.push_back("like ");
	vs.push_back("STL.");
	for(size_t i=0;i<vs.size();i++)
		cout<<vs[i];
	cout<<endl;
	return 0;
}
