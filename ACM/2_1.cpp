#include <stdio.h> 

static const int MAX_N = 100;
int a[MAX_N];
int n, k;

bool dfs(int i, int sum)
{
    if (i == n) return sum == k;

    if (dfs(i+1, sum)) return true;

    if (dfs(i+1, sum+a[i])) return true;

    return false;
}

int solve()
{
    if (dfs(0, 0)) printf("Yes\n");
    else printf("No\n");
}