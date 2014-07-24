#include <cstdio>
#include <iostream>
using namespace std;

double p1[1200];
double p2[1200];
double res[2500];

int main()
{
    // freopen("PAT1009.input", "r", stdin);

    int k1, k2, exp;
    double coe;
    cin >> k1;
    for (int i = 0; i < k1; ++i)
    {
        cin >> exp >> coe;
        p1[exp] = coe;
    }
    cin >> k2;
    for (int i = 0; i < k2; ++i)
    {
        cin >> exp >> coe;
        p2[exp] = coe;
    }

    for (int i = 0; i < 1200; ++i)
    {
        if (p1[i] == 0) continue;
        for (int j = 0; j < 1200; ++j)
        {
            if (p2[j] == 0) continue;
            res[i+j] += p1[i] * p2[j];
        }
    }

    int count = 0;
    int last = -1;
    for (int i = 2499; i >= 0; --i)
        if (res[i] != 0)
        {
            count++;
            last = i;
        }

    printf("%d ", count);
    for (int i = 2499; i >= 0; --i)
    {
        if (res[i] != 0 && i != last)
            printf("%d %.1f ", i, res[i]);
        else if (res[i] != 0 && i == last)
            printf("%d %.1f\n", i, res[i]);
    }
}