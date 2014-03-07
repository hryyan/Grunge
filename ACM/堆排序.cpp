#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 11

void input(int* num)
{
    for (int i = 1; i < MAX; ++i)
        num[i] = rand()%100;
}

void output(int* num)
{
    for (int i = 1; i < MAX; ++i)
        printf("%5d\n", num[i]);
    printf("\n");
}

void heapadjust(int* num, int s, int len)       //build large heap
{
    num[0] = num[s];
    for (int i = 2*s; i <= len; i*=2)
    {
        if (i < len && num[i] < num[i+1])
            i++;
        if (num[0] > num[i])
            break;
        num[s] = num[i];
        s = i;
    }
    num[s] = num[0];
}

void heapsort(int* num, int len)
{
    int tmp;
    for (i = len/2; i > 0; i--)     //build heap
        heapadjust(num, i, len);

    for (int i = len; i > 1; i--)   //sort heap
    {
        tmp = num[1];               //change largest data to end
        num[1] = num[i];
        num[i] = tmp;
        heapadjust(num, 1, i-1);    //rebuild large heap for (i-1) data 
    }
}

int main()
{
    srand((unsigned)time(NULL));
    int num[MAX];
    input(num);
    printf("sort before...\n");
    output(num);
    heapsort(num, MAX-1);
    printf("sort after...\n");
    output(num);
    printf("Time used: %.21f\n", (double)clock()/CLOCKS_PER_SEC);
}