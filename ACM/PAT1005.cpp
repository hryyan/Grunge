#include <cstdio>
#include <cmath>
char s[10][10] = {"zero", "one", "two",   "three", "four",\
                  "five", "six", "seven", "eight", "nine"};

int main()
{
    // freopen("PAT1004.input", "r", stdin);
    char c;
    int sum = 0;
    while ((c = getchar()) != '\n')
        sum += (c-'0');
    int on = false;
    for (int i = 5; i >= 0; i--)
    {
        int a = sum % (int)pow(10, i+1) / (int)pow(10, i);
        if (a == 0 && !on)
            continue;
        else
        {
            printf("%s", s[a]);
            on = true;
        }
        if (i != 0 && on)
            printf(" ");
    }
    if (sum == 0)
        printf("zero");
    printf("\n");
}