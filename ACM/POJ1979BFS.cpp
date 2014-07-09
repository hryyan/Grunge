#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>
using std::queue;

bool room[21][21];
int  width, height;
int  stand_row, stand_col;
int  dr[4] = {-1, 0, 1,  0};
int  dc[4] = { 0, 1, 0, -1};

struct Point
{
    int row;
    int col;
};

int bfs()
{
    int res = 0;
    Point p;
    p.row = stand_row;
    p.col = stand_col;
    queue<Point> que;
    que.push(p);

    while (!que.empty())
    {
        res++;
        Point point;
        point = que.front();
        que.pop();
        for (int i = 0; i < 4; ++i)
        {
            int r = point.row + dr[i];
            int c = point.col + dc[i];
            if  (r >= 0 && r < height && c >= 0 && c < width \
                 && room[r][c] == false)
            {
                room[r][c] = true;
                Point tmp;
                tmp.row = r;
                tmp.col = c;
                que.push(tmp);
            }
        }
    }
    return res;
}

int main()
{
    // freopen("POJ1979.input", "r", stdin);

    char c;
    while(scanf("%d %d\n", &width, &height) == 2)
    {
        if (width == 0 && height == 0)
            exit(0);
        memset(room, false, sizeof(room));
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                scanf("%c", &c);
                if (c == '#')
                    room[i][j] = true;
                else if (c == '@')
                {
                    room[i][j] = true;
                    stand_row = i;
                    stand_col = j;
                }
            }
            getc(stdin);
            getc(stdin);
        }
        printf("%d\n", bfs());
    }
    return 0;
}