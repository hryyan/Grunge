#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
char n[10];

void num2char(int num)
{
    memset(n, '0', sizeof(n));
    for (int i = 6; i >= 0; i--)
    {
        int value = static_cast<int>(pow(10, i));
        n[i] = num / value + '0';
        num = num % value;
    }
}

int main()
{
    // freopen("PAT1001.input", "r", stdin);

    int a, b, sum;
    a = b = sum = 0;
    while (scanf("%d %d", &a, &b) == 2)
    {
        sum = a + b;

        if (sum < 0)
        {
            printf("-");
            sum = 0 - sum;            
        }

        num2char(sum);

        int i = 9;
        while (n[i] == '0' && i >= 0) i--;

        if (i == -1)
            printf("0");

        while (i >= 0)
        {
            putc(n[i], stdout);
            if (i == 3 || i == 6)
                printf(",");
            i--;
        }

        printf("\n");
    }
}