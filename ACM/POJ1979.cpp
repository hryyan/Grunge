#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using std::cout;
using std::cin;

const int MAXN = 55;
char room[MAXN][MAXN];
bool res[MAXN][MAXN];
int width, height;
int start_row, start_col;

int dfs(int r, int c)
{
    res[r][c] = true;
    if (r-1>=0     && room[r-1][c] == '.' && !res[r-1][c])
        dfs(r-1, c);
    if (r+1<height && room[r+1][c] == '.' && !res[r+1][c])
        dfs(r+1, c);
    if (c-1>=0     && room[r][c-1] == '.' && !res[r][c-1])
        dfs(r, c-1);
    if (c+1<width  && room[r][c+1] == '.' && !res[r][c+1])
        dfs(r, c+1);
}

int main()
{
    // freopen("POJ1979.input", "r", stdin);

    while (scanf("%d %d\n", &width, &height) == 2)
    {
        if (width == 0 && height == 0)
            exit(0);
        memset(res, false, sizeof(res));
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                scanf("%c", &room[i][j]);
                if (room[i][j] == '@')
                {
                    start_row = i;
                    start_col = j;
                }
            }
            getc(stdin);
        }
        dfs(start_row, start_col);
        int r = 0;
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                if (res[i][j] == true)
                    r++;
            }
        }
        printf("%d\n", r);
    }
    return 0;
}