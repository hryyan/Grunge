#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define swap(x, y) {int tmp; tmp=x; x=y; y=tmp;}
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

void sort(int* num, int low, int high)
{
    while (low < high)
    {
        for (int i = low; i < high; ++i)
            if (num[i] > num[i+1])
                swap(num[i], num[i+1]);
        high--;

        for (int i = high; i > low; --i)
            if (num[i] < num[i-1])
                swap(num[i], num[i-1]);
        low++;
    }
}

int main()
{
    srand((unsigned)time(NULL));
    int num[MAX];
    input(num);

    printf("sort before...\n");
    output(num);

    sort(num, 0, MAX-1);
    printf("sort after...\n");
    output(num);
    printf("Time used = %.21f\n", (double)clock() / CLOCKS_PER_SEC);
}