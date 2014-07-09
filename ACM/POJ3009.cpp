#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAXN = 40;
int board[MAXN][MAXN];
int height, width;
int start_x, start_y;
int end_x, end_y;
int minimun;

void dfs(int x, int y, int num)
{
    // 超出最大数
    if (num > 10)
        return;

    board[x][y] = 0;
    // 往上需要满足几点
    // 1、它不是在边缘
    // 2、它不是靠着BLOCK（可以靠着END）
    // 3、往那个方向至少有一个BLOCK
    if (x>0 && board[x-1][y] != 1)
    {
        // 检测那个方向至少有一个BLOCK
        for (int i = x-1; i >= 0; --i)
        {
            // 如果先碰到END，则成立
            if (board[i][y] == 3)
            {
                minimun = minimun>num?num:minimun;
                return;
            }
            // 先碰到BLOCK，则继续递归
            else if (board[i][y] == 1)
            {
                board[i][y] = 0;
                dfs(i+1, y, num+1);
                board[i][y] = 1;
                break;
            }
        }
    }
    // 往下
    if (x<height-1 && board[x+1][y] != 1)
    {
        for (int i = x+1; i < height; ++i)
        {
            if (board[i][y] == 3)
            {
                minimun = minimun>num?num:minimun;
                return;
            }
            else if (board[i][y] == 1)
            {
                board[i][y] = 0;
                dfs(i-1, y, num+1);
                board[i][y] = 1;
                break;
            }
        }
    } 
    // 往左
    if (y>0 && board[x][y-1] != 1)
    {
        for (int i = y-1; i >= 0; --i)
        {
            if (board[x][i] == 3)
            {
                minimun = minimun>num?num:minimun;
                return;
            }
            else if (board[x][i] == 1)
            {
                board[x][i] = 0;
                dfs(x, i+1, num+1);
                board[x][i] = 1;
                break;
            }   
        }
    }
    // 往右
    if (y<width-1 && board[x][y+1] != 1)
    {
        for (int i = y+1; i < width; ++i)
        {
            if (board[x][i] == 3)
            {
                minimun = minimun>num?num:minimun;
                return;
            }
            else if (board[x][i] == 1)
            {
                board[x][i] = 0;
                dfs(x, i-1, num+1);
                board[x][i] = 1;
                break;
            }
        }
    }
}

int main()
{
    // freopen("POJ3009.input", "r", stdin);

    while (scanf("%d %d\n", &width, &height) == 2)
    {
        if (width == 0 && height == 0)
            exit(0);

        memset(board, -1, sizeof(board));
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                scanf("%d", &board[i][j]);
                int b = board[i][j];
                if (board[i][j] == 2)
                {
                    start_x = i;
                    start_y = j;
                }
                else if (board[i][j] == 3)
                {
                    end_x = i;
                    end_y = j;
                }
            }
            getc(stdin);
            // getc(stdin);
        }
        minimun = 1000000;
        dfs(start_x, start_y, 1);
        int res = (minimun==1000000)?-1:minimun;
        printf("%d\n", res);
    }
}