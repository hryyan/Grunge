struct edge {int to, cost};
typedef pair<int, int> P;   // first是最短距离，second是顶点的编号

int V;
vector<edge> G[MAX_V];
int d[MAX_V];

void dijkstra(int s)
{
    // 通过指定greater<P>参数，堆按照first从小到大的顺序取出值
    priority_queue<P, vector<P>, greater<P> > que;

    fill(d, d+V, INF);
    d[s] = 0;
    que.push(P(0, s));

    while (!que.empty())
    {
        P p = que.top();
        que.pop();
        int v = p.second;
        // 这个pair在放入queue到被取出的期间内，d[v]已经被修改过了
        if (d[v] < p.first) continue;
        // 根据刚才取出的pair，根据它的所有边，对其临近的顶点进行刷新
        // 刷新后放入que
        for (int i = 0; i < G[v].size(), i++)
        {
            edge e = G[v][i];
            if (d[e.to] > d[v] + e.cost)
            {
                d[e.to] = d[v] + e.cost;
                que.push(P(d[e.to], e.to));
            }
        }
    }
}