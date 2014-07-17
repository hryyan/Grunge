#include <iostream>
#include <cstring>
#include <limits.h>
using namespace std;

struct Edge
{
    int from, to, cost;
    // Edge(int _from, int _to, int _cost)\
    // :from(_from), to(_to), cost(_cost){};
};

int V, E, C1, C2;

int main()
{
    freopen("PAT1003.input", "r", stdin);

    cin >> V >> E >> C1 >> C2;
    int city[V];
    Edge road[E];
    for (int i = 0; i < V; ++i)
        cin >> city[i];
    for (int i = 0; i < E; ++i)
        cin >> road[i].from >> road[i].to >> road[i].cost;

    int d[V];
    memset(d, INT_MAX, sizeof(int)*V);
    d[C1] = 0;

    while (true)
    {
        bool update = false;
        for (int i = 0; i < E; ++i)
        {
            Edge e = road[i];
            printf("for: %d %d %d\n", e.from, e.to, e.cost);
            if (d[e.from] != INT_MAX && d[e.to] > d[e.from] + e.cost)
            {
                d[e.to] = d[e.from] + e.cost;
                printf("if: %d %d %d\n", e.from, e.to, e.cost);
                update = true;
            }
        }
        if (!update)
            break;
    }
    cout << d[C2];
}