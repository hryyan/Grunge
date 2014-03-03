#include <cstdio>
#include <cstring>
#define MAXLEN 1000 + 50

int index;
char big[5], small[5], t[5];
char l[MAXLEN][5];

void getNext()
{
    char tmp;
    for (int i = 1; i < 4; ++i)
        for (int j = i; j > 0; --j)
            if (small[j] < small[j-1])
            {
                tmp = small[j-1];
                small[j-1] = small[j];
                small[j] = tmp;
            }

    for (int i = 0; i < 4; ++i)
        big[i] = small[3-i];
}

void calculate()
{
    int g=0;
    char tmp;
    for (int i = 3; i >= 0; --i)
    {
        tmp = small[i];
        small[i] = (big[i]-small[i]-g) >= 0 ? (big[i]-small[i]-g) : (big[i]-small[i]-g+10);
        small[i] += 48;
        g = (big[i]-tmp-g) >= 0 ? 0 : 1;
    }
}

int main()
{
    big[4] = small[4] = t[4] = '\0';
    scanf("%s", small);
    strcpy(&(l[index++][0]), small);
    while (strcmp(t, small) != 0)
    {
        strcpy(t, small);
        getNext();
        calculate();
        strcpy(&(l[index++][0]), small);
    }
    int i;
    for (i = 0; i < index-2; ++i)
        printf("%s->", l[i]);
    printf("%s", l[index-1]);
    return 0;
}