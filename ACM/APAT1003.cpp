#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

int dist[600];
int emergency[600];
int e[600][600];
int take[600];
int N, M, S, D;
vector<int> pre[600];

void dijkstra(int s)
{
    bool used[600];
    fill(used, used+600, false);
    fill(take, take+600, 0);
    dist[s] = 0;
    take[s] = emergency[s];

    while (true)
    {
        int v = -1;
        for (int i = 0; i < N; i++)
            if (!used[i] && (v == -1 || dist[i] < dist[v]))
                v = i;

        if (v == -1)
            break;
        used[v] = true;

        for (int i = 0; i < N; i++)
        {
            if (dist[i] > dist[v]+e[v][i])
            {
                pre[i].clear();
                pre[i].push_back(v);
                dist[i] = dist[v]+e[v][i];
                take[i] = take[v]+emergency[i];
            }
            else if (dist[i] == dist[v]+e[v][i] && i != v)
            {
                pre[i].push_back(v);
                take[i] = max(take[i], take[v]+emergency[i]);
            }
        }
    }
}

int count(int d)
{
    queue<int> que;
    que.push(d);
    int c = 0;

    while (!que.empty())
    {
        int tmp = que.front();
        que.pop();

        if (tmp == S)
            c++;
        for (auto it = pre[tmp].begin(); it != pre[tmp].end(); it++)
            que.push(*it);
    }
    return c;
}

int main()
{
    freopen("../input", "r", stdin);

    int s, d, c;
    cin >> N >> M >> S >> D;
    fill(dist, dist+600, 1<<29);
    for (int i = 0; i < 600; i++)
        for (int j = 0; j < 600; j++)
            if (i != j)
                e[i][j] = 1 << 29;

    for (int i = 0; i < N; i++)
        cin >> emergency[i];

    for (int i = 0; i < M; i++)
    {
        cin >> s >> d >> c;
        e[s][d] = e[d][s] = c;
    }

    dijkstra(S);
    cout << count(D) << " " << take[D] << endl;
}
