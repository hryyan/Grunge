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
        printf("%5d", num[i]);
    printf("\n");
}

void sort(int* num)
{
    int tmp;
    for (int i = 0; i < MAX-1; ++i)
    {
        printf("bubble...\n");
        for (int j = 0; j < MAX-i-1; ++j)
        {
            printf("%5d", num[j]);
            if (num[j] > num[j+1])
            {
                tmp = num[j];
                num[j] = num[j+1];
                num[j+1] = tmp;
            }
        }
        printf("%5d\n", num[MAX-i]);

        printf("bubble after...\n");
        for (int j = 0; j < MAX; ++j)
            printf("%5d", num[j]);
        printf("\n");
    }
}

int main()
{
    srand((unsigned)time(NULL));
    // freopen("test.input", 'r', stdin);
    int num[MAX];
    printf("sort before...\n");
    input(num);
    output(num);
    sort(num);
    printf("sort after...\n");
    output(num);
    printf("Time used = %.21f\n", (double)clock() / CLOCKS_PER_SEC);
}