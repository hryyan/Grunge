#include <stdio.h>
#include "fortest.h"

int main()
{
    fortest a;
    for (int i = 0; i < 5; ++i)
    {
        printf("%d\n", a.data[i]);        
    }
    printf("%d\n", a.a);
    int d;
    printf("d=%d\n", d);
    float f;
    printf("f=%f\n", f);
}