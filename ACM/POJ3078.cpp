#include <cstdio>
#include <cstring>
#include <deque>
#include <utility>
using std::deque;
using std::pair;
using std::make_pair;

int n, k;
const int MAXN = 400005;
typedef pair<int, int> P;
deque<P> deq;

int bfs()
{
    if (!deq.empty())
        deq.clear();
    bool hash[MAXN];
    memset(hash, false, sizeof(hash));
    deq.push_back(make_pair(n, 1));
    while (!deq.empty())
    {
        P start = deq.front();
        deq.pop_front();
        // printf("size: %d, start: %d\n", deq.size(), start.first);
        if (start.first+1 == k || start.first-1 == k || \
            start.first*2 == k)
            return start.second;
        if (start.first < k*2 && start.first >= 0)
        {
            // 往前瞬移一次
            if (!hash[start.first*2])
            {
                hash[start.first*2] = true;
                deq.push_back(make_pair(start.first*2, start.second+1));
            }
            // 往左移动一格，如果上一次不是减
            if (!hash[start.first+1])
            {
                hash[start.first+1] = true;
                deq.push_back(make_pair(start.first+1, start.second+1));
            }
            // 往右移动一格，如果上一次不是增
            if (!hash[start.first-1])
            {
                hash[start.first-1] = true;
                deq.push_back(make_pair(start.first-1, start.second+1));
            }
        }
    }
}

int main()
{
    // freopen("POJ3078.input", "r", stdin);
    while (scanf("%d %d", &n, &k) != EOF)
    {
        if (n >= k)
            printf("%d\n", n-k);
        else            
            printf("%d\n", bfs());
    }
    return 0;
}