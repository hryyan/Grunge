#include <stdio.h>
#define MAXLEN 1000
int r[MAXLEN];

int main()
{
    freopen("17.input", "r", stdin);
    int k, x, y, n, index;
    double a, b;
    while(scanf("%d", &k) == 1)
    {
        index = 0;
        for (int i = 0; i <= 2*k; ++i)
        {
            a = (double)(i*k) / (double)(i-k);
            if (a-(int)a/1==0 && (int)a > 0)
                // printf("1/%d = 1/%d + 1/%d\n", k, (int)a, i);
                {
                    r[index++] = (int)a;
                    r[index++] = i;
                } 
        }
        printf("%d\n", (index+1)/2);
        for (int i = 0; i < index; )
        {
            printf("1/%d = 1/%d + 1/%d\n", k, r[i++], r[i++]);
        }
    }
    return 0;
}