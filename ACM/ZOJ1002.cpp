#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int n, result;
int m[10][10];

bool test(int i, int j)
{
    if (i < 0 || i >=n || j < 0 || j >= n)
        return false;

    if (m[i][j] == 1 || m[i][j] == 2)
        return false;

    int a, b;

    a = i;
    while (--a >= 0)
    {
        if (m[a][j] == 1) break;
        if (m[a][j] == 2) return false;        
    }

    a = i;
    while (++a < n)
    {
        if (m[a][j] == 1) break;
        if (m[a][j] == 2) return false;
    }

    b = j;
    while (--b >= 0)
    {
        if (m[i][b] == 1) break;
        if (m[i][b] == 2) return false;
    }

    b = j;
    while (++b < n)
    {
        if (m[i][b] == 1) break;
        if (m[i][b] == 2) return false;
    }

    return true;
}

void dfs(int i, int j, int s)
{
    int l = i*n+j + 1;
    if (l == n*n + 1)
    {
        if (s > result)
            result = s;
    }
    else
    {
        if (test(i, j))
        {
            m[i][j] = 2;
            dfs(l/n, l%n, s+1);
            m[i][j] = 0;
        }
        dfs(l/n, l%n, s);
    }
}

int main()
{
    int tmp;
    //freopen("ZOJ1002.input", "r", stdin);
    scanf("%d\n", &n);
    while (n != 0)
    {
        result = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (46 == getc(stdin))
                    m[i][j] = 0;
                else
                    m[i][j] = 1;
            }
            getc(stdin);            
        } 

        memcpy(m, m, sizeof(m));
        dfs(0, 0, 0);

        printf("%d\n", result);
        scanf("%d\n", &n);
    }
}