#include <iostream>
#include <vector>

using namespace std;
void print(vector<float>&vct)
{
	size_t numelem=vct.size();
	for(size_t i=0;i<numelem;i++) 
		cout<<vct[i]<<" ";
	cout<<endl;
}
int main()
{
	vector<float>v1,v2;
	v1.push_back(3.14f);
	v1.push_back(21.7f);
	for(size_t i=0;i<3;i++)
		v2.push_back(2.6f*(i+1));
	cout<<"v1:";
	print(v1);
	cout<<"v2:";
	print(v2);
	cout<<"v2 after erase:";
	v2.erase(v2.begin()+1);
	print(v2);
	v1.swap(v2);
	cout<<"v1:";
	print(v1);
	cout<<"v2:";
	print(v2);
	return 0;
}

