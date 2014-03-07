#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void input_num1(int* num, int n1)
{
    for (int i = 1; i <= n1; ++i)
        num[i] = 3*(i-1);
    printf("\nnum 1:\n");
    for (int i = 1; i <= n1; ++i)
        printf("%5d", num[i]);
    printf("\n");
}

void input_num2(int* num, int n2)
{
    for (int i = 1; i <= n2; ++i)
        num[i] = i;
    printf("\nnum 2:\n");
    for (int i = 1; i <= n2; ++i)
        printf("%5d", num[i]);
    printf("\n");
}

void output_num3(int* num1, int n1, int* num2, int n2, int* num3, int n3)
{
    int pos1, pos2, pos3;
    pos1 = pos2 = pos3 = 1;

    while (pos1 <= n1 && pos2 <= n2)
    {
        if (num1[pos1] < num2[pos2])
            num3[pos3++] = num1[pos1++];
        else
            num3[pos3++] = num2[pos2++];
    }
    while (pos1 <= n1)
        num3[pos3++] = num1[pos1++];
    while (pos2 <= n2)
        num3[pos3++] = num1[pos2++];
    printf("\nnum 3:\n");
    for (pos3 = 1; pos3 <= n3; ++pos3)
    {
        printf("%5d ", num3[pos3]);
        if (pos3 % 10 == 0)
            printf("\n");
    }
}

int main()
{
    srand((unsigned)time(NULL));
    int num1[11];
    int num2[21];
    int num3[31];

    input_num1(num1, 10);
    input_num2(num2, 20);
    output_num3(num1, 10, num2, 20, num3, 30);
    printf("Time used: %.21f\n", (double)clock() / CLOCKS_PER_SEC);
}