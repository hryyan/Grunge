/*************************************************************************
	> File Name: PAT1021.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月05日 星期二 08时26分53秒
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_N = 12000;
int N;
typedef vector<int> Edges;
Edges e[MAX_N];

// bfs
bool bfs(int root, bool* used)
{
    queue<int> que;
    que.push(root);
    used[root] = true;

    bool update = false;
    while (!que.empty())
    {
        int tmp = que.front();
        que.pop();
        for (int i = 0; i < e[tmp].size(); i++)
        {
            int pos = e[tmp][i];
            if (!used[pos])
            {
                update = true;
                used[pos] = true;
                que.push(pos);
            }
        }
        /*for (int i = 1; i <= N; i++)
        {
            if (!used[i] && find(e[tmp].begin(), e[tmp].end(), i) != e[tmp].end())
            {
                update = true;
                used[i] = true;
                que.push(i);
            }
        }*/
    }
    return update;
}

// 检测由几个图组成
int countComponent()
{
    bool used[N+1];
    memset(used, false, sizeof(used));
    int component = 0;

    for (int i = 1; i <= N; i++)
    {
        if (!used[i])
            component++;
        bool update = true;
        while (update)
        {
            update = bfs(i, used);
        }
    }
    return component;
}

// 如果由一个图组成，则计算最深树
int countDepth(int root)
{
    bool used[N+1];
    int level[N+1];
    memset(used, false, sizeof(used));
    memset(level, 0, sizeof(level));

    queue<int> que;
    que.push(root);
    used[root] = true;

    int max_depth = 0;
    while (!que.empty())
    {
        int tmp = que.front();
        que.pop();

        for (int i = 0; i < e[tmp].size(); i++)
        {
            int pos = e[tmp][i];
            if (!used[pos])
            {
                used[pos] = true;
                level[pos] = level[tmp] + 1;
                max_depth = max(max_depth, level[pos]);
                que.push(pos);
            }
        }
        /*for (int i = 1; i <= N; i++)
        {
            if (!used[i] && find(e[tmp].begin(), e[tmp].end(), i) != e[tmp].end())
            {
                used[i] = true;
                level[i] = level[tmp] + 1;
                max_depth = max(max_depth, level[i]);
                que.push(i);
            }
        }*/
    }
    return max_depth;
}

int main()
{
    //freopen("PAT1021.input", "r", stdin);
    //freopen("PAT1021.input2", "r", stdin);

    cin >> N;
    int p1, p2;
    for (int i = 1; i < N; i++)
    {
        cin >> p1 >> p2;
        e[p1].push_back(p2);
        e[p2].push_back(p1);
    }

    // 检测由几个图组成
    int component = countComponent();
    if (component != 1)
    {
        cout << "Error: " << component << " components" << endl;
        return 0;
    }

    // 如果由一个图组成，则计算最深树
    int max_length = 0;
    vector<int> res;
    bool cyclic = false;
    for (int i = 1; i <= N; i++)
    {
        int depth = countDepth(i);
        // 若存在环
        if (depth == -1)
        {
            cyclic = true;
            break;
        }
        if (depth > max_length)
        {
            max_length = depth;
            res.clear();
            res.push_back(i);
        }
        else if (depth == max_length)
        {
            res.push_back(i);
        }
    }

    // 如果存在环，则输出Error: 1 component
    // 如果不存在，则正常输出
    if (cyclic)
        cout << "Error: 1 component" << endl;
    else
        for (int i = 0; i < res.size(); i++)
            cout << res[i] << endl;
}
