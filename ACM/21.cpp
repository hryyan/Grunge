#include <stdio.h>
#include <stdlib.h>

struct unit
{
    int b;
    int j;
    int s;
};

int unitCmp(const void* a_, const void* b_)
{
    unit* a = (unit*)a_;
    unit* b = (unit*)b_;
    if (a->j > b->j)
        return -1;
    else if (a->j == b->j)
        if (a->b < b->b)
            return -1;
        else
            return 1;
    else 
        return 1;
}

const int workerNum = 20000;
unit worker[workerNum];

int main()
{
    freopen("21.input", "r", stdin);
    int jobNum;
    while(scanf("%d", &jobNum), jobNum != 0)
    {
        int index = 0;
        int sum = 0;
        while(jobNum--)
        {
            scanf("%d %d", &(worker[index].b), &(worker[index].j));
            index++;
        }
        qsort(worker, index, sizeof(unit), unitCmp);
        for (int i = 0; i < index; ++i)
        {
            worker[i].s = sum;
            sum += worker[i].b;
        }
        int m = 0;
        for (int i = 0; i < index; ++i)
        {
            worker[i].s += worker[i].b + worker[i].j;
            if (worker[i].s > m)
                m = worker[i].s;
        }
        printf("%d\n", m);
    }
    return 0;
}