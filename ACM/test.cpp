#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 11

void input(int* num)
{
    for (int i = 0; i < MAX; ++i)
        num[i] = rand()%100;
}

void output(int* num)
{
    for (int i = 0; i < MAX; ++i)
        printf("%5d ", num[i]);
    printf("\n");
}

void sort(int* num)
{
    int pos, tmp;
    for (int i = 1; i < MAX; ++i)
    {
        pos = i;
        tmp = num[pos];
        while (pos>0 && tmp<num[pos-1])
        {
            num[pos] = num[pos-1];
            pos--;
        }
        num[pos] = tmp;
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
    printf("Time used %.21f\n", (double)clock() / CLOCKS_PER_SEC);
}
