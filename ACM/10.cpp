#include <iostream>
#include <cstdio>
#include <cstring>
#include <stdlib.h>

#define WORDLEN 10
#define LISTLEN 1000
char word[WORDLEN];
char t[WORDLEN];
char list[LISTLEN][WORDLEN];
char gotl[LISTLEN][WORDLEN];

static int index;

char* normalize(char *w, char *r)
{
    strcpy(t, w);
    char tmp;
    for (int i = 1; i < strlen(t); i++)
        for (int j = i; j > 0; --j)
            if (t[j] > t[j-1])
            {
                tmp = t[j-1];
                t[j-1] = t[j];
                t[j] = tmp;
            }
    strcpy(r, t);
    return r;
}

void search(char *w)
{
    memset(gotl, 0, LISTLEN*WORDLEN);
    int j = 0;
    char *a, *b;
    a = (char*)(malloc(10));
    b = (char*)(malloc(10));
    normalize(w, b);
    for (int i = 0; i < index; i++)
    {
        normalize(list[i], a);
        if (strcmp(a, b) == 0)
            strcpy(gotl[j++], list[i]);
    }
    if (j == 0)
        printf(":(\n");
    else
    {
        for(int i = 0; i < j-1; i++)
            printf("%s ", gotl[i]);
        printf("%s\n", gotl[j-1]);
    }
}

int main()
{
    freopen("10.input", "r", stdin);
    index = 0;
    char w[10] = "******";
    char test[10];
    while(scanf("%s", word), strcmp(word, w))
        strcpy(list[index++], word);

    while(scanf("%s", test) == 1)
    {
        if (strcmp(test, w) == 0)
            break;
        search(test);
    }
    // for (int i = 0; i < index; ++i)
    //     printf("%s\n", list[i]);
    return 0;
}