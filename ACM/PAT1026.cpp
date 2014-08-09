/*************************************************************************
	> File Name: PAT1026.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月06日 星期三 15时54分23秒
 ************************************************************************/
#include <cstdio>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

struct Player
{
    int arrive_time;
    int play_time;
    int left_time;
    Player(int h, int m, int s, int _play_time):play_time(_play_time){
        arrive_time = h*3600 + m*60 + s;
        left_time = 0;
    }
    Player(){arrive_time = 24*3600;};
};

bool operator<(Player p1, Player p2)
{
    return p1.arrive_time > p2.arrive_time;
};

int N, K, M;
priority_queue<Player, vector<Player> > nor;
priority_queue<Player, vector<Player> > vip;
int tf[120]; // 1 to K

int main()
{
    freopen("PAT1026.input", "r", stdin);

    int h, m, s, pt, flag;
    cin >> N;
    while (N--)
    {
        scanf("%d:%d:%d %d %d", &h, &m, &s, &pt, &flag);
        if (flag == 1)
            vip.push(Player(h, m, s, pt));
        else
            nor.push(Player(h, m, s, pt));
    }

    cin >> K >> M;
    for (int i = 0; i < M; i++)
    {
        cin >> flag;
        tf[flag] = 1;
    }

    /*cout << "普通玩家" << endl;
    while (!nor.empty())
    {
        Player p = nor.top();
        nor.pop();
        printf("%d:%d:%d %d\n", p.arrive_time/3600, p.arrive_time%3600/60, p.arrive_time%60, p.play_time);
    }

    cout << "VIP玩家" << endl;
    while (!vip.empty())
    {
        Player p = vip.top();
        vip.pop();
        printf("%d:%d:%d %d\n", p.arrive_time/3600, p.arrive_time%3600/60, p.arrive_time%60, p.play_time);
    }*/

    int count = 0;
    // 开始的时候，对于所有到达时间小于8*3600的玩家
    // 若普通桌则排序，若VIP桌则优先
    for (int i = 1; i <= K; i++)
    {
        if (tf[i] == 0)
        {
            Player first, nor_p, vip_p;
            if (!nor.empty() && nor.top().arrive_time <= 8*3600)
                nor_p = nor.top();
            if (!vip.empty() && vip.top().arrive_time <= 8*3600)
                vip_p = vip.top();
            if (vip_p < nor_p && nor_p.arrive_time <= 8*3600)
            {
                // 普通玩家可以去玩了
                printf("%d:%d:%d %d nor\n", nor_p.arrive_time/3600, nor_p.arrive_time%3600/60, nor_p.arrive_time%60, nor_p.play_time);
                nor.pop();
            }
            else if (vip_p.arrive_time <= 8*3600)
            {
                // VIP玩家可以去玩了
                printf("%d:%d:%d %d vip\n", vip_p.arrive_time/3600, vip_p.arrive_time%3600/60, vip_p.arrive_time%60, vip_p.play_time);
                vip.pop();
            }
            else
                break;
        }
        else
        {
            Player first, nor_p, vip_p;
            if (!vip.empty() && vip.top().arrive_time <= 8*3600)
            {
                first = vip.top();
                vip.pop();
            }
            else if (!nor.empty() && nor.top().arrive_time <= 8*3600)
            {
                first = nor.top();
                nor.pop();
            }
            else
                break;
        }
    }
}
