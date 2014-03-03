#include <stdio.h>
#include <math.h>
#include "Prime.c"
int v[1000], a[1000];

int main()
{
    freopen("12.input", "r", stdin);
    int n, num, k;
    while(scanf("%d", &n) == 1)
    {
        memset(a, 0, sizeof(int) * 1000);
        num = getPrime(n, v, 2);
        for (int i = num-1; i >= 0; --i)
        {
            for (int j = 2; j <= n; ++j)
            {
                k = j;
                while (k % v[i] == 0)
                {
                    k /= v[i];
                    a[i]++;                
                }                
            }
        }
        for (int i = 0; i < num; ++i)
        {
            printf("%d ", a[i]);
        }
        printf("\n");
    }
}