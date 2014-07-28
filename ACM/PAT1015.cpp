#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

int v[20];

int main()
{
    // freopen("PAT1015.input", "r", stdin);

    int N, D;
    while (cin >> N >> D)
    {
        if (N < 0)
            break;

        fill(v, v+20, 0);

        // 把数转换成D进制
        int i;
        for (i = 0; N / (int)pow(D, i) != 0; ++i)
            v[i] = N % (int)pow(D, i+1) / (int)pow(D, i);

        // 把数翻转,并得到10进制数
        int reverse = 0;
        for (int j = 0; j < i; ++j)
            reverse += v[j] * (int)pow(D, i-1-j);

        bool isPrime = true;
        if (reverse == 0 || reverse == 1 || N == 0 || N == 1)
            isPrime = false;
        else
        {
            for (int j = 2; j <= sqrt(reverse); ++j)
                if (reverse % j == 0)
                    isPrime = false;
            for (int j = 2; j <= sqrt(N); ++j)
                if (N % j == 0)
                    isPrime = false;
        }

        if (isPrime)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
}