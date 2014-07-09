#include <stdio.h>
#include <string.h>
#include <deque>
#include <utility>
using std::deque;
using std::pair;
using std::make_pair;

const int MAXN = 30;
bool visitd[MAXN][MAXN];
int height, width;
typedef pair<int, int> P;
deque<P> deq, res;

void dfs(int x, int y)
{
    deq.push_back(make_pair(x, y));
    visitd[x][y] = true;
    if (deq.size() == height*width)
    {
        if (res.empty())
        {
            res = deq;
        }
        else
        {
            for (int i = 0; i < height*width; ++i)
            {
                if (deq[i].second < res[i].second)
                {
                    res = deq;
                    break;
                }
                if (deq[i].second == res[i].second)
                {
                    if (deq[i].first < res[i].first)
                    {
                        res = deq;
                        break;
                    }
                    if (deq[i].first > res[i].first)
                        break;
                }
                if (deq[i].second > res[i].second)
                    break;
            }
        }
    }
    if (x-2>=0 && y+1<width && !visitd[x-2][y+1])
        dfs(x-2, y+1);
    if (x-1>=0 && y+2<width && !visitd[x-1][y+2])
        dfs(x-1, y+2);
    if (x+1<height && y+2<width && !visitd[x+1][y+2])
        dfs(x+1, y+2);
    if (x+2<height && y+1<width && !visitd[x+2][y+1])
        dfs(x+2, y+1);
    if (x+2<height && y-1>=0 && !visitd[x+2][y-1])
        dfs(x+2, y-1);
    if (x+1<height && y-2>=0 && !visitd[x+1][y-2])
        dfs(x+1, y-2);
    if (x-1>=0 && y-2>=0 && !visitd[x-1][y-2])
        dfs(x-1, y-2);
    if (x-2>=0 && y-1>=0 && !visitd[x-2][y-1])
        dfs(x-2, y-1);
    visitd[x][y] = false;
    deq.pop_back();
}

int main()
{
    // freopen("POJ2488.input", "r", stdin);

    int m;
    scanf("%d\n", &m);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d %d\n", &height, &width);
        while (!deq.empty())
            deq.clear();
        while (!res.empty())
            res.clear();
        memset(visitd, false, sizeof(visitd));
        dfs(0, 0);
        printf("Scenario #%d:\n", i+1);
        if (res.empty())
            printf("impossible");
        while (!res.empty())
        {
            printf("%c%d", res.front().second+65, res.front().first+1);
            res.pop_front();
        }
        printf("\n\n");
    }
    return 0;
}   