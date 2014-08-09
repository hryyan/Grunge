/*************************************************************************
	> File Name: PAT1033.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月08日 星期五 21时14分53秒
 ************************************************************************/

#include <cstdio>
#include <cstdlib>

struct Station
{
    float price;
    float dist;
};

int comp(const void *a, const void *b)
{
    Station *s1 = (Station*)a;
    Station *s2 = (Station*)b;
    return s1->dist > s2->dist;
}
Station s[600];

int main()
{
    //freopen("PAT1033.input", "r", stdin);

    int Cmax, D, Davg, N;
    scanf("%d %d %d %d\n", &Cmax, &D, &Davg, &N);
    for (int i = 0; i < N; i++)
        scanf("%f %f\n", &s[i].price, &s[i].dist);

    s[N].dist = D;
    qsort(s, N, sizeof(Station), comp);

    double gasleft = 0;
    double sum = 0;
    bool possible = true;
    int index = 0;

    if (s[0].dist != 0)
        printf("The maximum travel distance = 0.00");
    else
    {
        while (true)
        {
            int nextDist = s[index].dist + Cmax * Davg;
            // 终止条件1：加满油也无法开到下一个站
            if (nextDist < s[index+1].dist)
            {
                possible = false;
                break;
            }
            // 终止条件2：我们现在已经在终点站了，由于终点站的price为0，所以肯定会进入
            else if (index == N)
            {
                sum += (((D-s[index].dist)*1.0/Davg)-gasleft)*s[index].price;
                break;
            }

            int dest = index;
            for (int i = index+1; i <= N && s[i].dist <= nextDist; ++i)
            {
                // 找到个比当前站点便宜的站点,我们就先开过去
                if (s[i].price < s[index].price)
                {
                    dest = i;
                    break;
                }
                // 第一个条件是用来陷入的，找到在沿途上，比当前站点贵一点点的站
                else if (dest == index || s[i].price < s[dest].price)
                    dest = i;
            }

            // 要去站点油价比当前便宜，所以我们只要加最少量的油就行了
            if (s[dest].price < s[index].price)
            {
                if ((s[dest].dist - s[index].dist)*1.0/Davg >= gasleft)
                {
                    sum += (((s[dest].dist - s[index].dist)/Davg)-gasleft)*s[index].price;
                    gasleft = 0;
                }
                else
                    gasleft -= (s[dest].dist - s[index].dist)/Davg;
            }
            // 要去的站点都比当前油价贵，所以要加满
            else
            {
                sum += (Cmax-gasleft)*s[index].price;
                gasleft = Cmax - ((s[dest].dist - s[index].dist) / Davg);
            }
            index = dest;
        }
        if (possible)
            printf("%.2lf\n", sum);
        else
            printf("The maximum travel distance = %.2lf\n", (double)s[index].dist+Cmax*Davg);
    }
}
