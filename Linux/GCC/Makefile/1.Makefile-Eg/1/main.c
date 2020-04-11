#include <stdio.h>
#include "add.h"
#include "sub.h"

int main()
{
    int a=10,b=12;
    float x=1.23456,y=9.87654321;

    printf("int a+b is:%d\n",add_int(a,b));
    printf("int a-b is:%d\n",sub_int(a,b));
    printf("float a+b is:%d\n",add_float(a,b));
    printf("float a-b is:%d\n",add_float(a,b));
    return 0;
}

