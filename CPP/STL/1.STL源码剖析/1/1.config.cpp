//file:1config.cpp
//test configurations defined in <stl_ config.h>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
# ifdef _sgi
	cout<<"_sgi"<<endl;
# endif

#ifdef _GUNC_
	cout<<"_GUNC_"<<endl;
	cout<<"_GUNC_"<<' '<<_GUNC_MINOR_<<endl;
	cout<<"_GLIBC_"<<endl;
#endif

#ifdef _STL_NO_DRAND48
	cout<<"_STL_NO_DRAND48 define"<<endl;
#else
	cout<<"_STL_NO_DRAND48 undefine"<<endl;
#endif
#ifdef _STL_CLASS_PARTIAL_SPECIALIZATION
	cout<<"_STL_CLASS_PARTIAL_SPECIALIZATION define"<<endl;
#else
	cout<<"_STL_CLASS_PARTIAL_SPECIALIZATION undefine"<<endl;
#endif
	return 0;
}


