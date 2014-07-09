#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

const int MAXN = 200000;
int store[MAXN];

int trans_helper(char c)
{
    switch(c)
    {
        case 'A': return 2;
        case 'B': return 2;
        case 'C': return 2;
        case 'D': return 3;
        case 'E': return 3;
        case 'F': return 3;
        case 'G': return 4;
        case 'H': return 4;
        case 'I': return 4;
        case 'J': return 5;
        case 'K': return 5;
        case 'L': return 5;
        case 'M': return 6;
        case 'N': return 6;
        case 'O': return 6;
        case 'P': return 7;
        case 'R': return 7;
        case 'S': return 7;
        case 'T': return 8;
        case 'U': return 8;
        case 'V': return 8;
        case 'W': return 9;
        case 'X': return 9;
        case 'Y': return 9;
        default: exit(2);
    }
}

int trans(char *s, int len)
{
    int num = 0;
    int index = 1;
    for (int i = 0; i < len-1; i++)
    {
        if (s[i] == 0)
            break;
        if (s[i] == '-')
            continue;
        else if (isdigit(s[i]))
            num += (s[i]-48) * pow(10, 7-index++);
        else
            num += trans_helper(s[i]) * pow(10, 7-index++);
    }
    return num;
}

int cmp(const void *a, const void *b)
{
    const int *num_a = (int*)a;
    const int *num_b = (int*)b;
    return (*num_a - *num_b);
}

void int_to_char(int a, char* s)
{
    for (int i = 0, k = 0; i < 7; ++i, ++k)
    {
        if (i == 3 && k == 3)
        {
            i--;
            s[k] = '-';
        }
        else
        {
            s[k] = a % (int)pow (10, 7-i) / (int)pow(10, 7-i-1) + 48;
        }
    }
    s[8] = 0;
}

int main()
{
    // freopen("POJ1002.input", "r", stdin);

    int n = 0;
    scanf("%d", &n);

    char s[100];
    memset(s, 0, sizeof(s));
    for (int i = 0; i < n; ++i)
    {
        scanf("%s", s);
        store[i] = trans(s, sizeof(s));
   }
   qsort(store, n ,sizeof(store[0]), cmp);
   store[n] = 10000000;

   // 这个pre是绝对不会在号码中出现的
   int pre = 10000000;
   // 计数从1开始
   int count = 1;
   // 是否相同，默认为false
   bool dup = false;
   // 计数，有多少个相同的
   int o = 0;
   for (int i = 0; i < n+1; ++i)
   {
        // 当前数字等于之前的那个数字
        if (store[i] == pre)
        {
            dup = true;
            count++;
            o++;
        }
        // 当前数字不等于之前的那个数字
        // 有两种情况，第一是该数字是第一个数字
        // 第二是该数字与之前的那个不同，该输出并且重置参数了
        else
        {
            if (pre == 10000000)
            {
                pre = store[i];
                continue;
            }
            else
            {
                if (dup)
                {
                    int_to_char(pre, s);
                    printf("%s %d\n", s, count);
                }
                dup = false;
                count = 1;
                pre = store[i];
            }
        }
        if (i == n && o == 0)
            printf("No duplicates.\n");
    }
   return 0;
}