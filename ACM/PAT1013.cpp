#include <cstdio>
#include <utility>
#include <vector>
#include <iostream>
using namespace std;

typedef pair<int, int> Edge;
const int MAX_N = 1000;
vector<Edge> v;
int concer[MAX_N];
int index;
int visited[MAX_N];

int main()
{
    // freopen("PAT1013.input", "r", stdin);

    int N, M, K;
    cin >> N >> M >> K;

    int s1, s2;
    while (M--)
    {
        cin >> s1 >> s2;
        v.push_back(Edge(s1, s2));
    }
    while (K--)
        cin >> concer[index++];

    for (int i = 0; i < index; ++i)
    {
        int occupied = concer[i];

        fill(visited, visited+MAX_N, 0);
        int G = 1;
        for (int j = 1; j < N+1; ++j)
        {
            if (!visited[j] && j != occupied)
            {
                visited[j] = G;
                while (true)
                {
                    bool update = false;
                    for (int k = 0; k < v.size(); ++k)
                    {
                        if (visited[v[k].first] == G && visited[v[k].second] != G)
                        {
                            if (v[k].second == occupied)
                                continue;
                            visited[v[k].second] = G;
                            update = true;
                        }
                        else if (visited[v[k].second] == G && visited[v[k].first] != G)
                        {
                            if (v[k].first == occupied)
                                continue;
                            visited[v[k].first] = G;
                            update = true;
                        }
                    }
                    if (!update)
                        break;
                }
                G++;
            }
        }
        cout << G-2 << endl;
    }
}