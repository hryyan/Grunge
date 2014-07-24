#include <cstdio>
#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

// 最大的顶点数
const int MAX_V = 600;
// 条件
int V, E, C1, C2;
// 放在队列中的东西
struct P
{
    int distance, index;
    vector<int> ph;
    P(int _distance, int _index, vector<int> _ph)\
    :distance(_distance), index(_index), ph(_ph){};
};

bool operator<(P a, P b)
{
    return a.distance > b.distance;
}

// 邻接表
struct edge
{
    int to, cost;
    edge(){};
    edge(int _to, int _cost):to(_to), cost(_cost){};
};
vector<edge> G[MAX_V];
// 距离
int d[MAX_V];
// 路径
vector<vector<int> >Path;

void dijkstra(int s)
{
    priority_queue<P> que;
    // 因为后面还得加，得留些余量
    fill(d, d+V, 1 << 30);
    d[s] = 0;
    vector<int> a;
    a.push_back(s);
    que.push(P(0, s, a));

    while (!que.empty())
    {
        P p = que.top();
        que.pop();
        int v = p.index;
        // 到C2了，意味着路径结束了，我们把这个路径保存起来
        if (v == C2)
        {
            Path.push_back(p.ph);
            continue;            
        }
        // 既然已经在C2后面了，就不要再算了
        if (d[v] > d[C2]) continue;
        // v顶点的d已经更新
        if (d[v] < p.distance) continue;
        for (int i = 0; i < G[v].size(); ++i)
        {
            edge e = G[v][i];
            if (d[e.to] >= d[v] + e.cost)
            {
                d[e.to] = d[v] + e.cost;
                // 复制一个新的路径
                vector<int> a(p.ph);
                bool on = false;
                for (int j = 0; j < a.size(); ++j)
                {
                    if (e.to == a[j])
                        on = true;
                }
                if (!on)
                    a.push_back(e.to);
                que.push(P(d[e.to], e.to, a));
            }
        }
    }
}

int main()
{
    // freopen("PAT1003.input", "r", stdin);

    cin >> V >> E >> C1 >> C2;
    int team[V];
    int start, to, cost;
    for (int i = 0; i < V; ++i)
        cin >> team[i];
    for (int i = 0; i < E; ++i)
    {
        cin >> start >> to >> cost;
        G[start].push_back(edge(to, cost));
        G[to].push_back(edge(start, cost));
    }

    dijkstra(C1);

    int m = 0;
    for (int i = 0; i < Path.size(); ++i)
    {
        int count = 0;
        for (int j = 0; j < Path[i].size(); ++j)
            count += team[Path[i][j]];
        m = max(m, count);
    }
    printf("%d %d\n", Path.size(), m);
}