#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

struct Position
{
    int l;
    int r;
    int c;
    int step;
    Position(int _l, int _r, int _c, int _step):l(_l), r(_r), c(_c), step(_step){};
};

const int MAXN = 120;
char dungeons[MAXN][MAXN][MAXN];
bool visited[MAXN][MAXN][MAXN];
int L, R, C;
int s_l, s_r, s_c;
queue<Position> que;

int bfs()
{
    while (!que.empty())
        que.pop();
    que.push(Position(s_l, s_r, s_c, 0));

    while (!que.empty())
    {
        Position p = que.front();
        que.pop();

        if (dungeons[p.l][p.r][p.c] == 3)
            return p.step;

        // East
        if (p.c-1>=0 && !visited[p.l][p.r][p.c-1] && dungeons[p.l][p.r][p.c-1] != 1)
            que.push(Position(p.l, p.r, p.c-1, p.step+1));
        // West
        if (p.c+1<C  && !visited[p.l][p.r][p.c+1] && dungeons[p.l][p.r][p.c+1] != 1)
            que.push(Position(p.l, p.r, p.c+1, p.step+1));
        // North
        if (p.r-1>=0 && !visited[p.l][p.r-1][p.c] && dungeons[p.l][p.r-1][p.c] != 1)
            que.push(Position(p.l, p.r-1, p.c, p.step+1));
        // South
        if (p.r+1<R  && !visited[p.l][p.r+1][p.c] && dungeons[p.l][p.r+1][p.c] != 1)
            que.push(Position(p.l, p.r+1, p.c, p.step+1));
        // Up
        if (p.l-1>=0 && !visited[p.l-1][p.r][p.c] && dungeons[p.l-1][p.r][p.c] != 1)
            que.push(Position(p.l-1, p.r, p.c, p.step+1));
        // Down
        if (p.l+1<L  && !visited[p.l+1][p.r][p.c] && dungeons[p.l+1][p.r][p.c] != 1)
            que.push(Position(p.l+1, p.r, p.c, p.step+1));
    }

    if (que.empty())
        return -1;
}

int main()
{
    // freopen("POJ2251.input", "r", stdin);

    char ch;
    while (cin >> L >> R >> C)
    {
        // 把格子和访问位初始化
        memset(dungeons, 1, sizeof(dungeons));
        memset(visited, 0, sizeof(visited));
        // 吃掉数字后的那个回车
        cin.get();
        // 如果L为0，则返回
        if (L == 0)
            return 0;
        // 把每一层都放置到格子中
        for (int l = 0; l < L; ++l)
        {
            for (int r = 0; r < R; ++r)
            {
                for (int c = 0; c < C; ++c)
                {
                    if ((ch = cin.get()) == '.')
                        dungeons[l][r][c] = 0;
                    else if (ch == '#')
                        dungeons[l][r][c] = 1;
                    else if (ch == 'S')
                    {
                        dungeons[l][r][c] = 2;
                        s_l = l; s_r = r; s_c = c;
                    }
                    else
                        dungeons[l][r][c] = 3;
                }
                // 吃掉一行后的回车
                cin.get();
            }
            // 吃掉一组数之后的回车
            cin.get();
        }

        int res = bfs();
        if (res == -1)
            printf("Trapped!\n");
        else
            printf("Escaped in %d minute(s).\n", res);
    }
}