#include <stdio.h>
#include <stdlib.h>

typedef struct unit
{
    int d;
    char o;
    bool turning;
    int i;
}unit;

int unitcmp(const void* a_, const void* b_)
{
    unit* a = (unit*)a_;
    unit* b = (unit*)b_;
    if (a->d < b->d)
        return -1;
    else
        return 1;
}

int backToIndex(const void* a_, const void* b_)
{
    unit* a = (unit*)a_;
    unit* b = (unit*)b_;
    if (a->i < b->i)
        return -1;
    else
        return 1;
}

const int maxsize = 20000;
unit ant[maxsize];

int main()
{
    freopen("20.input", "r", stdin);
    int m, caseIndex = 1;
    scanf("%d", &m);
    while (m--)
    {
        int l, t, n;
        scanf("%d %d %d", &l, &t, &n);
        int index = 0, tmp = n;
        while (tmp--)
        {
            scanf("%d %s", &(ant[index].d), &(ant[index].o));
            ant[index].i = index;
            index++;
        }
        qsort(ant, index, sizeof(unit), unitcmp);
        for (int i = 0; i < t; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                ant[j].turning = false;
                if (ant[j].o == 'R')
                    ant[j].d += 1;
                else
                    ant[j].d -= 1;
            }
            for (int j = 0; j < n-1; ++j)
            {
                if (ant[j].d > ant[j+1].d)
                {
                    unit tmp = ant[j];
                    ant[j] = ant[j+1];
                    ant[j+1] = tmp;
                    int p;
                    p = ant[j].i;
                    ant[j].i = ant[j+1].i;
                    ant[j+1].i = p;
                }
                if (ant[j].d == ant[j+1].d)
                {
                    ant[j].o = 'L';
                    ant[j].turning = true;
                    ant[j+1].o = 'R';
                    ant[j+1].turning = true;
                }
            }
        }
        qsort(ant, index, sizeof(unit), backToIndex);
        printf("Case #%d:\n", caseIndex++);
        for (int i = 0; i < n; ++i)
        {
            if (ant[i].d < 0 || ant[i].d > l)
            {
                printf("Fell off\n");
                continue;                
            }
            else
                printf("%d ", ant[i].d);

            if (ant[i].turning)
                printf("Turning");
            else
                putchar(ant[i].o);
            printf("\n");
        }
    }
    return 0;
}