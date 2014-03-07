#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 11
int num2[MAX];
void input(int* num)
{
    for (int i = 1; i < MAX; ++i)
        num[i] = rand()%100;
}

void output(int* num)
{
    for (int i = 1; i < MAX; ++i)
        printf("%5d ", num[i]);
    printf("\n");
}

void sort(int num[], int len)
{
    int i, j, pos, head, tail;
    head = tail = 1;
    num2[1] = num[1];
    for (i = 2; i <= len; ++i)
    {
        if (num[i] > num2[1])
        {
            for (j = tail; i > 1; j--)
            {
                if (num[i]<num2[j])
                    num2[j+1] = num2[j];
                else
                    break;
            }
            num2[j+1] = num[i];
            tail++;
        }
        else
        {
            if (head==1)
            {
                num2[len] = num[i];
                head = len;
            }
            else
            {
                for (j = head; j <=len; j++)
                {
                    if (num[i] > num2[j])
                        num2[j-1] = num2[j];
                    else
                        break;
                }
                num2[j-1] = num[i];
                head--;
            }
        }
    }

    pos = 1;
    for (i = 0; i <= len; ++i)
    {
        if (head <= len)
            num[i] = num2[head++];
        else if (pos <= tail)
            num[i] = num2[pos++];
    }
}

int main()
{
    srand((unsigned)time(NULL));
    int num[MAX];
    input(num);
    printf("sort before...\n");
    output(num);
    sort(num, MAX-1);
    printf("sort after...\n");
    output(num);
    printf("Time used: %.21f\n", (double)clock() / CLOCKS_PER_SEC);
}