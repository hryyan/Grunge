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
vector<int> prime;

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

int main()
{
    generatePrime();
    printf("%d\n", prime.size()*prime.size());
    for (int i = 0; i < prime.size(); ++i)
    {
        for (int j = 0; j < prime.size(); ++j)
        {
            printf("%d %d\n", prime[i], prime[j]);
        }
    }
}