#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

struct Job{
    int j, b;
    bool operator < (const Job &x) const{
        return j > x.j;
    }
};

int main()
{
    int n, b, j, kase = 1;
    while(scanf("%d", &n) == 1 & n)
    {
        vector<Job>
    }
}