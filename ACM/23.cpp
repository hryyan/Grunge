#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = 2000;
double A[maxn], C[maxn], tot, M;

int main()
{
    freopen("23.input", "r", stdin);
    int n, m;
    while(scanf("%d%d", &n, &m) == 2)
    {
        M = (double)10000 / n;
        A[0] = 0.0;
        C[0] = 0.0;
        for (int i = 1; i < n; ++i)
            A[i] = A[0] + M;
        M = (double)10000 / (n+m);
        int j = 1;
        for (int i = 1; i < n; ++i)
        {
            while (j<m+n-1 && M*j < A[i])
                j++;
            if (A[i]-M*(j-1)>M*j-A[i])
                C[i] = A[i]-M*j;
            else
                C[i] = M*(j-1)-A[i];
        }
        sort(C, C+n);
        double x1 = C[n/2], ans = 0.0;
        for (int i = 0; i < n; ++i)
            if (C[i] > 0)
                ans += C[i];
            else
                ans -= C[i];
        printf("%.4lf\n", ans);
    }
    return 0;
}