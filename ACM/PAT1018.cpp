/*************************************************************************
	> File Name: PAT1018.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月04日 星期一 10时25分34秒
 ************************************************************************/

#include <cstdio>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

const int C_MAX = 120;
const int N_MAX = 600;
int c, n, p, r;

// current bike
int b[N_MAX];
int d[N_MAX][N_MAX];
int f[N_MAX][N_MAX];
vector<int> path[N_MAX][N_MAX];

struct Path
{
    int index;
    vector<int> v;
    Path(int _index, vector<int> _v):index(_index), v(_v){};
};

void floyd()
{
    for (int k = 0; k <= n; k++)
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
            {
                //d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
                if (d[i][j] > d[i][k] + d[k][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                    path[i][j].clear();
                    path[i][j].push_back(k);
                    //f[i][j] = f[i][k]*f[k][j];
                }
                else if (d[i][j] == d[i][k] + d[k][j] && k != j)
                {
                    path[i][j].push_back(k);
                    //f[i][j] += f[i][k]*f[k][j];
                }
            }
}

vector<vector<int> > bfs()
{
    vector<vector<int> > vec;
    queue<Path> que;
    que.push(Path(p, vector<int>()));

    while (!que.empty())
    {
        Path tmp = que.front();
        que.pop();
        if (tmp.index == 0)
        {
            tmp.v.erase(tmp.v.end()-1);
            reverse(tmp.v.begin(), tmp.v.end());
            vec.push_back(tmp.v);
        }
        else
        {
            for (int i=0; i < path[0][tmp.index].size(); i++)
            {
                vector<int> t2 = tmp.v;
                t2.push_back(path[0][tmp.index][i]);
                que.push(Path(path[0][tmp.index][i], t2));
            }
        }
    }
    return vec;
}

int LargeSum(vector<int> v)
{
    int sum = 0, j = 0;
    for (int i=0; i<v.size(); i++)
    {
        //cout << v[i] << " " << c/2-b[v[i]] << endl;
        j += c/2-b[v[i]];
        sum = max(sum, j);
    }
    return sum;
}

int AllSum(vector<int> v)
{
    int sum = 0;
    for (int i=0; i<v.size(); i++)
    {
        sum += c/2-b[v[i]];
    }
    return sum;
}

int main()
{
    //freopen("PAT1018.input", "r", stdin);

    int _start, _end, _cost;
    cin >> c >> n >> p >> r;
    for (int i=1; i<=n; i++)
        cin >> b[i];

    for (int i=0; i<N_MAX; i++)
    {
        for (int j=0; j<N_MAX; j++)
        {
            if (i == j)
                d[i][j] = 0;
            else
                d[i][j] = 1<<29;
            f[i][j] = 1;
        }
    }
    
    for (int i=0; i<r; i++)
    {
        cin >> _start >> _end >> _cost;
        d[_start][_end] = d[_end][_start] = _cost;
    }

    floyd();

    /*for (int i=0; i <= n; i++)
    {
        vector<int> v = path[0][i];
        cout << i << endl;
        for (int j=0; j < v.size(); j++)
        {
            cout << v[j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    for (int i=0; i <= n; i++)
    {
        cout << i << " " << f[0][i] << endl;
    }*/

    vector<vector<int> > vec = bfs();
    
    int min_bring = 1 << 30, min_back = 1 << 30;
    int bring_index = -1;
    for (int i = 0; i < vec.size(); i++)
    {
        vec[i].push_back(p);
        int bring = LargeSum(vec[i]);
        int back = bring - AllSum(vec[i]);

        if (bring < min_bring)
        {
            min_bring = bring;
            min_back = back;
            bring_index = i;
        }
        else if (bring == min_bring && back < min_back)
        {
            bring_index = i;
            min_back = back;
        }
    }

    cout << min_bring << " 0";
    for (int i=0; i<vec[bring_index].size(); i++)
    {
        cout << "->" << vec[bring_index][i];
    }
    cout << " " << min_back << endl;
}
