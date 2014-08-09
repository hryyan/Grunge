/*************************************************************************
	> File Name: PAT1030_1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月07日 星期四 18时54分46秒
 ************************************************************************/

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

int N, M, S, D;
int dist[600][600];
int cost[600][600];
int d[600];
int c[600];
int used[600];
int pre[600];

void dijkstra(int s)
{
    fill(pre, pre+600, -1);
    fill(c, c+600, 1<<29);
    fill(d, d+600, 1<<29);
    d[s] = 0;
    c[s] = 0;

    while (true)
    {
        int v = -1;
        for (int i = 0; i < N; i++)
            if (!used[i] && (v == -1 || d[i] < d[v]))
                v = i;

        if (v == -1)
            break;
        used[v] = true;

        for (int i = 0; i < N; i++)
        {
            if (d[i] > d[v]+dist[v][i] || \
                (d[i] == d[v]+dist[v][i] && c[i] > c[v]+cost[v][i]))
            {
                d[i] = d[v]+dist[v][i];
                c[i] = c[v]+cost[v][i];
                pre[i] = v;
            }
        }
    }
}

vector<int> printPath(int t)
{
    vector<int> vec;
    for (; t != -1; t = pre[t])
        vec.push_back(t);
    reverse(vec.begin(), vec.end());
    return vec;
}

int main()
{
    //freopen("PAT1030.input", "r", stdin);

    int start, end, _dist, _cost;
    cin >> N >> M >> S >> D;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (i != j)
            {
                dist[i][j] = 1<<29;
                cost[i][j] = 1<<29;
            }

    for (int i = 0; i < M; i++)
    {
        cin >> start >> end >> _dist >> _cost;
        dist[start][end] = _dist;
        dist[end][start] = _dist;
        cost[start][end] = _cost;
        cost[end][start] = _cost;
    }

    dijkstra(S);

    vector<int> vec = printPath(D);
    for (int i = 0; i < vec.size(); i++)
        cout << vec[i] << " ";
    cout << d[D] << " " << c[D] << endl;
}
