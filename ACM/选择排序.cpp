#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 101

void input(int* num)
{
    for (int i = 0; i < MAX; ++i)
        num[i] = rand()%100;
}

void output(int* num)
{
    for (int i = 0; i < MAX; ++i)
    {
        printf("%5d", num[i]);
        if ((i+1) % 10 == 0 && i != 0)        
            printf("\n");
    }
    printf("\n");
}

void sort(int* num)
{
    int k, tmp;
    for (int i = 0; i < MAX-1; ++i)
    {
        k = i;
        for (int j = i+1; j < MAX; ++j)
            if (num[k] > num[j])
                k = j;
        if (i < k)
        {
            tmp = num[i];
            num[i] = num[k];
            num[k] = tmp;
        }
    }
}

int main()
{
    srand((unsigned)time(NULL));
    int num[MAX];
    printf("sort before...\n");
    input(num);
    output(num);
    sort(num);
    printf("sort after...\n");
    output(num);
    printf("Time used: %.21f\n", (double)clock() / CLOCKS_PER_SEC);
}