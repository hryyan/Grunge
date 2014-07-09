#include <stdio.h>
#include <stdlib.h>
#include <deque>
#include <vector>
#include <utility>
#include <set>
using std::make_pair;
using std::pair;
using std::deque;
using std::set;

const int MAXN = 20;
char board[MAXN][MAXN];
bool occupy_x[MAXN];
bool occupy_y[MAXN];
int n, k;
char c;

typedef pair<int, int> Point;
vector<Point> vp;
set<Point> sep;
deque<set<Point> > res;

void dfs(int x, int y, int k)
{
    // 假设在此点放置棋子
    occupy_x[x] = true; occupy_y[y] = true;
    sep.insert(make_pair(x, y));
    // 把该点从deq中删除
    deq.erase(deq.find(make_pair(x, y)));

    // 若放了之后就不要放其他棋子了
    if (k-1 == 0)
    {
        bool haveOne = false;
        for (int i = 0; i < res.size(); ++i)
            if (sep == res[i])
                haveOne = true;
        if (!haveOne)
            res.push_back(sep);
    }
    // 放了之后还需要放其他棋子
    else
        while (!deq.empty())
        {
            int x2 = deq.front().first; int y2 = deq.front().second;
            if (occupy_x[x2] == false && occupy_y[y2] == false)
                dfs(x2, y2, k-1);
        }

    // 假设不在此点放置棋子
    occupy_x[x] = false; occupy_y[y] = false;
    sep.erase(sep.find(make_pair(x, y)));

    // 在其他点中放置棋子
    while (!deq.empty())
    {

    }
        dfs(deq.front().first, deq.front().second, k);
}

int main()
{
    freopen("POJ1321.input", "r", stdin);

    while (scanf("%d %d", &n, &k) == 2)
    {
        if (n == -1 && k == -1)
            exit(0);

        memset(deq, 0, sizeof(deq));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                scanf("%c", &c);
                if (c == '#')
                    vp.push_back(make_pair(i, j));
            }
        }
    }
}