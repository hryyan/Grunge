#include <stdio.h>
#include <algorithm>
#define MAXLEN 40000
int nl[MAXLEN];
int ml[MAXLEN];

int intcmp(const void* _a, const void* _b)
{
    int *a = (int*)_a;
    int *b = (int*)_b;
    if (*a >= *b)
        return 1;
    else
        return -1;
}

int main()
{
    // freopen("19.input", "r", stdin);
    int m, n, sum, ni=0, mi=0;
    bool on;
    while(scanf("%d %d", &n, &m), !(m==0 && n==0))
    {
        sum = ni = mi = 0;
        on = true;
        while(n--)
            scanf("%d", &nl[ni++]);
        while(m--)
            scanf("%d", &ml[mi++]);
        qsort(nl, ni, sizeof(int), intcmp);
        qsort(ml, mi, sizeof(int), intcmp);
        int index = 0;
        for (int i = 0; i < ni; ++i)
        {
            while (index < mi && ml[index] < nl[i])
                index++;
            if (index == mi)
            {
                on = false;
                break;
            }
            else
            {
                sum += ml[index];
                index++;
            }
        }
        if (on)
            printf("%d\n", sum);
        else
            printf("Loowater is doomed!\n");
    }
    return 0;
}