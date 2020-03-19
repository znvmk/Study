#include<iostream>
#include<vector>

using namespace std;

int main()
{
	vector<int>vol1;
	for(int i=1;i<=6;i++){
		vol1.push_back(i);
	}
	for(int i=0;i<vol1.size();i++){
		cout<<vol1[i]<<' ';
	}
	cout<<endl;
}
