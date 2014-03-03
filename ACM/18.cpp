#include <stdio.h>
#include <math.h>
char num[100];

bool transformScale(int n, int scale)
{
    int j = 1;
    bool on = true;
    while (pow(scale, j) <= n) j++;
    for (int i = j-1; i >= 0; --i)
        num[i] = n % (int)pow(scale, i+1) / (int)pow(scale, i);
    for (int i = 0; i < j/2; ++i)
        if (num[i] != num[j-1-i])
            on = false;
    return on;
}

int main()
{
    freopen("18.input", "r", stdin);
    int n, found;
    while (scanf("%d", &n) == 1)
        for (int i = n+1; ; ++i)
        {
            found = 0;
            for (int j = 2; j <= 10; ++j)
                if (transformScale(i, j))
                    found++;
            if (found > 1)
            {
                printf("%d\n", i);
                return 0;                
            }
        }
}