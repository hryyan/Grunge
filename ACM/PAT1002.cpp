#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

float t[1500];

int main()
{
    // freopen("PAT1002.input", "r", stdin);

    int k, times, n;
    float an;
    k = 0;
    times = 2;
    n = 0;
    an = 0.0;

    memset(t, 0, sizeof(t));

    while (times--)
    {
        scanf("%d", &k);
        while (k--)
        {
            scanf("%d %f", &n, &an);
            t[n] += an;
        }
    }

    k = 1500;
    times = 0;
    while (--k >= 0)
    {
        if (t[k] != 0)
            times++;
    }

    printf("%d", times);

    k = 1500;
    while (--k >= 0)
    {
        if (t[k] != 0)
            printf(" %d %.1f", k, t[k]);
    }
}