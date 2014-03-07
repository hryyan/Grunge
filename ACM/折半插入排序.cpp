#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 11

void input(int* num)
{
    for (int i = 1; i < MAX; ++i) //num[0]作为flag位
        num[i] = rand()%100;
}

void output(int* num)
{
    for (int i = 1; i < MAX; ++i)
        printf("%5d ", num[i]);
    printf("\n");
}

void sort(int* num, int low, int high)
{
    int mid, l, h;
    for (int i = 2; i <= high; ++i)
    {
        l = low;
        h = i - 1;
        num[0] = num[i];

        while (l <= h)
        {
            mid=(l+h)/2;
            if (num[0] < num[mid])
                h = mid-1;
            else
                l = mid+1;
        }

        for (int j = i; j > l; j--)
            num[j] = num[j-1];
        num[l] = num[0];
    }
}

int main()
{
    srand((unsigned)time(NULL));
    int num[MAX];
    input(num);
    printf("sort before...\n");
    output(num);
    sort(num, 1, MAX-1);
    printf("sort after...\n");
    output(num);
    printf("Time used: %.21f\n", (double)clock() / CLOCKS_PER_SEC);
}