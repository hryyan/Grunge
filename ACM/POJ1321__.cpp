#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAXN = 20;
char board[MAXN][MAXN];
bool cols[MAXN];
bool rows[MAXN];
int n, k, ans;

void dfs(int row, int num)
{
    if (num == k)
    {
        ans++;
        return;
    }
    for (int i = row+1; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (board[i][j] != '.' && !cols[j] && !rows[i])
            {
                cols[j] = true;
                rows[i] = true;
                dfs(i, num+1);
                cols[j] = false;
                rows[i] = false;
            }
}

int main()
{
    // freopen("POJ1321.input", "r", stdin);

    while (scanf("%d %d\n", &n, &k) == 2)
    {
        if (n == -1 && k == -1)
            exit(1);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                scanf("%c", &board[i][j]);                
            }
            scanf("\n");
        }
            
        memset(cols, false, sizeof(cols));
        ans = 0;
        dfs(-1, 0);
        printf("%d\n", ans);
    }
    return 0;
}