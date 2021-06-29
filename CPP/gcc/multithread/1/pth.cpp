#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

const int count=5;
void *thread(void *ptr)
{
	for(int i=0;i<count;i++)
	{
		cout<<"this is a pthread call."<<endl;
		sleep(1);
	}
	return  0;
}

int main(int argc , char* argv[])
{
	pthread_t pt;
	int ret = pthread_create(&pt,NULL,thread,NULL);
	if(ret)
	{
		cout<<"create pthread failed!"<<endl;
		return 1;
	}
	for(int i=0;i<count;i++)
	{
		cout<<"this is the main process."<<endl;
		sleep(1);
	}
	pthread_join(pt,NULL);
	return 0;
}

