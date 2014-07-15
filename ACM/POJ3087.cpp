#include <cstdio>

const int MAXN = 150;
int s[8][MAXN];
int d[8][MAXN];
int map[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

int main()
{
    freopen("POJ3087.input", "r", stdin);

    int n;
    scanf("%d\n", &n);
    for (int i = 1; i < n+1; ++i)
    {
        int c = 0, offset = 0;
        char str[MAXN];
        scanf("%d\n", &c);
        for (int j = 0; j < 2; ++j)
        {
            scanf("%s", str);
            int o = 0;
            while (str[o] != '\n')
            {
                for (int k = 0; k < 8; ++k)
                    if (str[o] == map[k])
                        s[k][o+offset] = 1;
                o++;
            }
            offset = c;
        }
        scanf("%s", str);
        int o = 0;
        while (str[0] != '\n')
        {
            for (int j = 0; j < 8; ++j)
                if (str[o] == map[j])
                    s[j][o] = 1;
            o++;
        }

        for (int j = 0; j < 8; ++j)
        {
            
        }
    }
}