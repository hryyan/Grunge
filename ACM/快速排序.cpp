#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 21

void input(int* num)
{
    for (int i=1; i < MAX; i++)
        num[i] = rand()%100;
}

void output(int* num)
{
    for (int i=1; i < MAX; i++)
        printf("%5d", num[i]);
    printf("\n");
}

void sort(int* num, int low, int high)
{
    int l, h;
    l = low;
    h = high;
    if (low < high)
    {
        num[0] = num[l]; // num[0]为flag

        while (l<h)
        {
            while (l<h && num[h]>=num[0])
                h--;
            num[l] = num[h];
            while (l<h && num[l]<=num[0])
                l++;
            num[h] = num[l];
        }
        num[l] = num[0];
        sort(num, low, l-1);
        sort(num, l+1, high);
    }
}

int main()
{
    srand((unsigned)time(NULL));
    int num[MAX];
    input(num);
    printf("\nsort before...\n");
    output(num);
    sort(num, 1, MAX-1);
    printf("\nsort after...\n");
    output(num);
    printf("Time used: %.21f\n", (double)clock()/CLOCKS_PER_SEC);
}