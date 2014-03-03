#include <stdio.h>
#include <math.h>

int main()
{
    freopen("11.input", "r", stdin);
    int i, n, a, nu, de;                   //nu是分子，de是分母
    while(scanf("%d", &n) == 1)
    {
        i = 0;
        while((pow(i,2)+i)/2<n) i++;    //计算行号
        a = n - (pow(i-1,2)+i-1)/2;
        if (i % 2 == 1)                 //奇数
        {
            nu = i+1-a;
            de = i+1-nu;
        }
        if (i % 2 == 0)
        {
            de = i+1-a;
            nu = i+1-de;
        }
        printf("%d/%d\n", nu, de);
    }
    return 0;
}