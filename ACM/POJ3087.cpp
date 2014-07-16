#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <set>
using std::set;
using std::strcmp;
using std::string;

const int MAXN = 500;
char src[MAXN];
char dst[MAXN];
set<string> s;

void swap(char src[], int c)
{
    char tmp[MAXN];
    memset(tmp, 0, sizeof(char)*MAXN);
    for (int i = 0; i < 2*c; ++i)
    {
        if (i < c)
            tmp[2*i+1] = src[i];
        else
            tmp[2*(i-c)] = src[i];
    }
    memcpy(src, tmp, MAXN*sizeof(char));
}

int main()
{
    // freopen("POJ3087.input", "r", stdin);

    int n = 0;
    scanf("%d\n", &n);
    for (int l = 1; l < n+1; l++)
    {
        bool on = false;
        int c = 0, index = 0;
        char ch = 0;
        scanf("%d\n", &c);
        memset(src, 0, sizeof(char)*MAXN);
        memset(dst, 0, sizeof(char)*MAXN);
        while ((ch = getchar()) != '\n')
            src[index++] = ch;
        while ((ch = getchar()) != '\n')
            src[index++] = ch;
        index = 0;
        while ((ch = getchar()) != '\n')
            dst[index++] = ch;

        s.clear();
        int count = 0;
        string a(src);
        while (s.find(a) == s.end())
        {
            if (!strcmp(src, dst))
            {
                printf("%d %d\n", l, count);
                on = true;
                break;
            }
            s.insert(a);
            swap(src, c);
            a = string(src);
            count++;
        }
        if (!on)
            printf("%d -1\n", l);
    }
    return 0;
}