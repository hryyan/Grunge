#include <stdio.h>
#include <string.h>
#define MAXLEN 30
int num[MAXLEN];

int main()
{
    freopen("16.input", "r", stdin);
    int n, index, max, sum;
    while(scanf("%d", &n) == 1)
    {
        max = index = 0;
        memset(num, 0, MAXLEN*sizeof(int));
        while(n--)
            scanf("%d", &(num[index++]));
        for (int i = 0; i < index; ++i)
            for (int j = i+1; j < index; ++j)
            {
                sum = 1;
                for (int k = i; k <= j; ++k)
                {
                    sum *= num[k];
                    if (sum > max)
                        max = sum;
                }
            }
        printf("%d\n", max);
    }
    return 0;
}