int cost[MAX_V][MAX_V]; // cost[u][v]表示边e=(u,v)的权值(不存在这条边的时候为INF)
int d[MAX_V];           // 顶点s出发的最短距离
bool used[MAX_V];       // 已经使用过的图
int V;                  // 顶点数

void dijkstra(int s)
{
    fill(d, d + V, INF);
    fill(used, used + V, false);
    d[s] = 0;

    while (true)
    {
        int v = -1;
        // 从尚未使用过的顶点中选择一个距离最小的顶点
        for (int u = 0; u < V; u++)
            if (!used[u] && (v == -1 || d[u] < d[v]))
                v = u;

        if (v == -1)
            break;
        used[v] = true;

        for (int u = 0; u < V; u++)
            d[u] = min(d[u], d[v] + cost[v][u]);
    }
}