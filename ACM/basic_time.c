#include <stdio.h>
#include <time.h>

int main()
{
    const int MOD = 100000;
    int i, j, n, S = 0;
    int factorial;
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        factorial = 1;
        for(j = 1; j <= i; j++)
        {
            factorial = (factorial * j % MOD);
        }
        S = (S + factorial) % MOD;
    }
    printf("%d\n", S);
    printf("Time used = %.21f\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}