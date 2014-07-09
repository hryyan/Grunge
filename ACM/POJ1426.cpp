#include <cstdio>
#include <deque>
using std::deque;

int n;
deque<long long> deq;

long long bfs()
{
    while (!deq.empty())
        deq.clear();
    long long a = 1;
    deq.push_back(a);

    while (!deq.empty())
    {
        long long b = deq.front();
        deq.pop_front();
        if (b % n == 0)
            return b;
        deq.push_back(b*10);
        deq.push_back(b*10+1);
    }
}

int main()
{
    // freopen("POJ1426.input", "r", stdin);
    while (scanf("%d", &n) == 1 && n != 0)
        printf("%lld\n", bfs());
}