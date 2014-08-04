#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

struct Custom
{
    int arrive_time;
    int start_serve_time;
    int end_serve_time;
    int processing_time;
    Custom(int _h, int _m, int _s, int _p){
        arrive_time = _h*60*60+_m*60+_s-28800;
        processing_time = _p*60;
        start_serve_time = 0;
        end_serve_time = 0;
    }
};

vector<Custom> vec;
typedef pair<int, int> pa;

bool Comp(Custom c1, Custom c2)
{
    if (c1.arrive_time < c2.arrive_time)
        return true;
    return false;
}

int main()
{
    //freopen("PAT1017.input", "r", stdin);

    priority_queue<pa, vector<pa>, greater<pa> > pq;
    int N, K;
    cin >> N >> K;
    while (N--)
    {
        int h, m, s, p;
        scanf("%d:%d:%d %d", &h, &m, &s, &p);
        vec.push_back(Custom(h, m, s, p));
    }
    sort(vec.begin(), vec.end(), Comp);
    
    int i = 0;
    // 给所有K分配
    for (int j=0; j<K; j++)
    {
        if (j < vec.size() && vec[j].arrive_time <= 32400)
        {
            if (vec[j].arrive_time < 0)
                vec[j].start_serve_time = 0;
            else
                vec[j].start_serve_time = vec[j].arrive_time;
            vec[j].end_serve_time = vec[j].start_serve_time + vec[j].processing_time;
            pq.push(pa(vec[j].end_serve_time, j));
            i = j+1;
        }
    }

    while (i < vec.size())
    {
        if (vec[i].arrive_time > 32400)
            break;
        int index = pq.top().second;
        pq.pop();

        vec[i].start_serve_time = max(vec[index].end_serve_time, vec[i].arrive_time);
        vec[i].end_serve_time = vec[i].start_serve_time+vec[i].processing_time;
        
        pq.push(pa(vec[i].end_serve_time, i));
        i++;
    }

    int sum = 0;
    for (int i =0; i < vec.size(); i++)
        if (vec[i].arrive_time <= 32400)
            sum += vec[i].start_serve_time - vec[i].arrive_time;
    printf("%.1f\n", sum/60./i);
}
