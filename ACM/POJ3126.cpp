#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <deque>
#include <utility>
using std::sqrt;
using std::pow;
using std::abs;
using std::memset;
using std::vector;
using std::deque;
using std::pair;
using std::make_pair;

int n;
int start, end;
vector<int> prime;
typedef pair<int, int> P;

bool isPrime(int a)
{
    for (int i = 2; i < sqrt(a); ++i)
        if (a % i == 0)
            return false;
    return true;
}

void generatePrime()
{
    for (int i = 1000; i < 10000; ++i)
        if (isPrime(i))
            prime.push_back(i);
}

bool diff(int a, int b)
{
    int d[4] = {0, 0, 0, 0};
    int e[4] = {0, 0, 0, 0};
    d[0] = a % 10000 / 1000;
    d[1] = a % 1000  / 100 ;
    d[2] = a % 100   / 10  ;
    d[3] = a % 10    / 1   ;
    e[0] = b % 10000 / 1000;
    e[1] = b % 1000  / 100 ;
    e[2] = b % 100   / 10  ;
    e[3] = b % 10    / 1   ;
    if (d[0] != e[0] && d[1] == e[1] && d[2] == e[2] && d[3] == e[3])
        return true;
    if (d[0] == e[0] && d[1] != e[1] && d[2] == e[2] && d[3] == e[3])
        return true;
    if (d[0] == e[0] && d[1] == e[1] && d[2] != e[2] && d[3] == e[3])
        return true;
    if (d[0] == e[0] && d[1] == e[1] && d[2] == e[2] && d[3] != e[3])
        return true;
    return false;
}

int bfs(bool* hash, int size)
{
    deque<P> deq;
    memset(hash, false, size);

    int i = 0;
    for (i = 0; i < size; ++i)
        if (start == prime[i])
            break;
    deq.push_back(make_pair(i, 0));
    hash[i] = 1;

    while (!deq.empty())
    {
        P a = deq.front();
        deq.pop_front();

        if (prime[a.first] == end)
            return a.second;
        for (int j = 0; j < size; ++j)
        {
            if (!hash[j] && diff(prime[a.first], prime[j]))
            {
                hash[j] = true;
                deq.push_back(make_pair(j, a.second+1));
            }
        }
    }
    return -1;
}

int main()
{
    // freopen("POJ3126.input", "r", stdin);
    freopen("POJ3126.allsource", "r", stdin);

    scanf("%d", &n);
    generatePrime();
    int size = prime.size();
    bool hash[size];

    while (n--)
    {
        scanf("%d %d", &start, &end);
        int res = bfs(hash, size);
        if (res == -1)
            printf("Impossible\n");
        else
            printf("%d\n", res);
    }
}