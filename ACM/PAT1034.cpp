/*************************************************************************
	> File Name: PAT1034.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月09日 星期六 12时42分19秒
 ************************************************************************/

#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <iostream>
#include <algorithm>
using namespace std;

typedef pair<int, int> Record;
typedef vector<Record> Records;
Records r[20000];
int f[20000];
vector<int> key;
vector<Record> gangs;
int N, K;

int bfs()
{
    int res = 0;
    int flag = 1;
    for (int i = 0; i < key.size(); i++)
    {
        queue<int> que;
        que.push(key[i]);
        int sum = 0;
        int num_of_gang = 0;

        while (!que.empty())
        {
            int tmp = que.front();
            que.pop();

            if (f[tmp] == 0)
            {
                f[tmp] = flag;
                num_of_gang++;
                for (int j = 0; j < r[tmp].size(); j++)
                {
                    Record record = r[tmp][j];
                    sum += record.second;
                    que.push(record.first);
                }
            }
        }
        if (sum / 2 > K && num_of_gang > 2)
        {
            res++;
            gangs.push_back(Record(flag, num_of_gang));
        }
        flag++;
    }
    return res;
}

int searchHead(int flag)
{
    int head = 0;
    int time_max = 0;
    for (int i = 0; i < key.size(); i++)
    {
        if (f[key[i]] == flag)
        {
            int t = 0;
            for (int j = 0; j < r[key[i]].size(); j++)
            {
                t += r[key[i]][j].second;
            }
            if (t > time_max)
            {
                time_max = t;
                head = i;
            }
        }
    }
    return head;
}

int nameToId(char a[])
{
    int t0 = a[0] - 'A';
    int t1 = a[1] - 'A';
    int t2 = a[2] - 'A';
    return t0*27*27+t1*27+t2;
}

void IdToname(int id, char* a)
{
    a[0] = id / 27 / 27 + 'A';
    a[1] = id % (27 * 27) / 27 + 'A';
    a[2] = id % 27 + 'A';
}

bool comp(pair<int,int> a, pair<int,int> b)
{
    return a.first < b.first;
}

int main()
{
    //freopen("PAT1034.input", "r", stdin);
    //freopen("PAT1034.input2", "r", stdin);

    scanf("%d %d\n", &N, &K);
    char a[3], b[3];
    int length;
    for (int i = 0; i < N; i++)
    {
        scanf("%s %s %d\n", a, b, &length);
        int a_id = nameToId(a);
        int b_id = nameToId(b);
        r[a_id].push_back(Record(b_id, length));
        r[b_id].push_back(Record(a_id, length));
        key.push_back(a_id);
        key.push_back(b_id);
    }

    int res = bfs();

    if (res == 0)
        printf("%d\n", res);
    else
    {
        printf("%d\n", res);
        vector<pair<int, int> > vec;
        for (int i = 0; i < gangs.size(); i++)
        {
            int head = searchHead(gangs[i].first);
            int num = gangs[i].second;
            vec.push_back(make_pair(key[head], num));
        }
        sort(vec.begin(), vec.end(), comp);
        for (int i = 0; i < vec.size(); i++)
        {
            char a[3];
            IdToname(vec[i].first, a);
            printf("%s %d\n", a, vec[i].second);
        }
    }
}
