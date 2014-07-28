#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
using namespace std;

struct customer
{
    // 任务开始时间
    int task_start;
    // 任务结束时间
    int task_end;
    // 任务延续时间
    int task_last;
    // 在哪个队中
    int pipe_num;
};

struct Comp
{
    bool operator() (customer a, customer b){
        return a.task_end > b.task_end;
    }
};

const int MAX_K = 1200;
const int MAX_N = 22;
const int MAX_M = 12;
int N, M, K, Q;
customer c[MAX_K];
int query[MAX_K];

// 队列下一次可以进入的时间
int t[MAX_N];
// 把已经排上队的顾客放入最小堆
priority_queue<customer, vector<customer>, Comp> pq;

int main()
{
    // freopen("PAT1014.input", "r", stdin);

    cin >> N >> M >> K >> Q;
    for (int i = 1; i <= K; ++i)
        cin >> c[i].task_last;
    for (int i = 0; i < Q; ++i)
        cin >> query[i];

    int k = 1, m = 0, n = 0;
    while (k <= K){
        if (m == M && n == N)
            break;
        for (m = 0; m < M; ++m){
            for (n = 0; n < N; ++n){
                if (k <= K){
                    c[k].task_start = t[n];
                    t[n] += c[k].task_last;
                    c[k].task_end = t[n];
                    c[k].pipe_num = n;
                    pq.push(c[k]);
                    k++;
                }
            }
        }
    }

    while (k <= K)
    {
        customer iter = pq.top();
        pq.pop();
        c[k].pipe_num = iter.pipe_num;
        c[k].task_start = t[c[k].pipe_num];
        c[k].task_end = c[k].task_start + c[k].task_last;
        t[c[k].pipe_num] = c[k].task_end;
        pq.push(c[k]);
        k++;
    }

    for (int i = 0; i < Q; ++i)
    {
        if (c[query[i]].task_start >= 540)
            cout << "Sorry" << endl;
        else
        {
            int total = c[query[i]].task_end;
            int h = 8 + total / 60;
            int m = total % 60;
            printf("%02d:%02d\n", h, m);
        }
    }
}