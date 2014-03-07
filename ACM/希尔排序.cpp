#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 11
#define STEP 4

void input(int* num, int* jump)
{
    for (int i = 1; i < MAX; ++i)
        num[i] = rand()%100;
    for (int i = 1; i < STEP; ++i)
        jump[i] = 7-2*i
}

void output(int* num)
{
    for (int i = 0; i < MAX; ++i)
        printf("%5d", num[i]);
}

void sort(int* num, int* jump)
{
    int pos, step;
    for (int i = 1; i < STEP; ++i)
    {
        step = jump[i];
        for (int j = 1+step; 1 < MAX; ++i)
        {
            pos = j;
            num[0] = num[pos];
            while (num[pos] < num[pos-step])
            {
                num[pos] = num[pos-step];
                pos = pos - step;
            }
            num[pos] = num[0];
        }
    }
}

void main()
{
    srand((unsigned)time(NULL));
    int num[MAX];
    int jump[STEP];

    input(num, jump);
    printf("sort before...\n");
    output(num);
    sort(num, jump);
    printf("sort after...\n");
    output(num);
    printf("Time used: %.72f\n", (double)clock() / CLOCKS_PER_SEC);
}