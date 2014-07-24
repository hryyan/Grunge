#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAX_N = 120;
int N, M;

struct Node
{
    int parent;
    int num_child;
    int children[MAX_N];
    Node(int p, int n){parent = p; num_child = n; memset(children, 0, sizeof(children));};
    Node(){parent = 0; num_child = 0; memset(children, 0, sizeof(children));};
};

struct Edge
{
    int start, end;
    Edge(int s, int e):start(s), end(e){};
    Edge(){};
};

Node* nodes[MAX_N];
Edge edges[MAX_N];
int edge_index = 0;
int leaves[MAX_N];
int maxlevel = 0;

void dfs(int level, int parent)
{
    if (level > N)
        return;
    for (int i = 0; i < MAX_N; ++i)
    {
        if (nodes[i] && nodes[i]->parent == parent)
        {
            if (nodes[i]->num_child == 0)
                leaves[level]++;
            maxlevel = maxlevel > level ? maxlevel : level;
            dfs(level+1, i);
        }
    }
}

int main()
{
    // freopen("PAT1004.input", "r", stdin);

    cin >> N >> M;
    int label = 0, num_child = 0, end = 0;
    for (int i = 0; i < M; ++i)
    {
        cin >> label >> num_child;
        for (int j = 0; j < num_child; ++j)
        {
            cin >> end;
            edges[edge_index++] = Edge(label, end);
        }
    }

    for (int i = 0; i < edge_index; ++i)
    {
        Edge ep = edges[i];
        if (nodes[ep.start] == NULL)
            nodes[ep.start] = new Node();
        Node *sn = nodes[ep.start];
        Node *en = nodes[ep.end];
        sn->children[sn->num_child++] = ep.end;
        if (nodes[ep.end] == NULL)
            nodes[ep.end] = new Node(ep.start, 0);
        nodes[ep.end]->parent = ep.start;
    }

    dfs(0, 0);

    if (M == 0)
        cout << N;
    else
    {
        for (int i = 0; i <= maxlevel; ++i)
        {
            cout << leaves[i];
            if (i != maxlevel)
                cout << " ";
        }
    }
    cout << endl;
}