/*************************************************************************
	> File Name: PAT1030.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月07日 星期四 11时33分23秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

int d[600][600];
int c[600][600];
int N, M, S, D;
vector<int> p[600][600];
typedef pair<int, int> P; // cost, index

struct Path
{
    int index;
    vector<int> v;
    Path(int _index, vector<int> _v):index(_index), v(_v){};
};

void floyd()
{
    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                if (d[i][j] > d[i][k]+d[k][j])
                {
                    p[i][j].clear();
                    p[i][j].push_back(k);
                    d[i][j] = d[i][k]+d[k][j];
                }
                else if (d[i][j] == d[i][k]+d[k][j] && j != k)
                {
                    p[i][j].push_back(k);
                }
            }
}

vector<vector<int> > bfs()
{
    vector<vector<int> > vec;
    queue<Path> que;
    que.push(Path(D, vector<int>()));

    while (!que.empty())
    {
        Path tmp = que.front();
        que.pop();
        if (tmp.index == S)
        {
            //tmp.v.erase(tmp.v.end()-1);
            reverse(tmp.v.begin(), tmp.v.end());
            tmp.v.push_back(D);
            vec.push_back(tmp.v);
        }
        else
        {
            for (int i = 0; i < p[S][tmp.index].size(); i++)
            {
                vector<int> t2 = tmp.v;
                t2.push_back(p[S][tmp.index][i]);
                que.push(Path(p[S][tmp.index][i], t2));
            }
        }
    }
    return vec;
}

int main()
{
    //freopen("PAT1030.input", "r", stdin);

    int start, end, length, cost;
    cin >> N >> M >> S >> D;
    for (int i = 0; i < 600; i++)
        for (int j = 0; j < 600; j++)
        {
            if (i != j)
            {
                d[i][j] = 1 << 28;
                c[i][j] = 1 << 29;
            }
        }
    for (int i = 0; i < M; i++)
    {
        cin >> start >> end >> length >> cost;
        d[start][end] = length;
        d[end][start] = length;
        c[start][end] = cost;
        c[end][start] = cost;
    }

    floyd();

    vector<vector<int> > vec = bfs();

    int max = 1 << 29;
    int m;
    for (int i = 0; i < vec.size(); i++)
    {
        int cost = 0;
        for (int j = 0; j < vec[i].size()-1; j++)
        {
            cost += c[vec[i][j]][vec[i][j+1]];
            //cout << vec[i][j] << " ";
        }
        if (max > cost)
        {
            m = i;
            max = min(max, cost);
        }
    }

    for (int i = 0; i < vec[m].size(); i++)
    {
        cout << vec[m][i] << " ";
    }

    cout << d[S][D] << " " << max;
}
