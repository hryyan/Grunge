#include <cstdio>
#include <cstdlib>
#include <cmath>

char m[4][4];
FILE* pFile;
char dot = '.';
char x = 'X';

void dfs(int i, int sum)
{
    if (i == pow(sum, 2) - 1)
        for (int i = 0; i < sum; ++i)
            for (int j = 0; j < sum; ++j)
                printf("%c", m[i][j]);
        
    m[i/sum][i%sum] = dot;
    dfs(i+1, sum);
    m[i/sum][i%sum] = x;
    dfs(i+1, sum);
}

int main()
{
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 0; j < pow(i, 2); j++)
        {
            dfs(j, i);
        }
    }
}