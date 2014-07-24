#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

string N1, N2;
int radix;
long _n1[10], _n2[10];

int main()
{
    // freopen("PAT1010.input", "r", stdin);

    int tag;
    cin >> N1 >> N2 >> tag >> radix;
    if (tag == 2)
        swap(N1, N2);

    // 将N1和N2转换为int的数组，把字母全部用数字替换掉
    for (int i = 0; i < N1.size(); ++i)
    {
        if (N1[i] <= '9')
            _n1[i] = N1[i] - '0';
        else
            _n1[i] = N1[i] - 'a' + 10; 
    }

    for (int i = 0; i < N2.size(); ++i)
    {
        if (N2[i] <= '9')
            _n2[i] = N2[i] - '0';
        else
            _n2[i] = N2[i] - 'a' + 10;
    }

    // 求得N1的十进制数
    long restore = 0;
    for (int i = 0; i < N1.size(); ++i)
    {
        restore += _n1[i] * (long)pow(radix, N1.size()-1-i);
    }
    // cout << restore << endl;

    long res = 0;
    if (N2.size() == 1)
    {
        cout << "Impossible" << endl;
        exit(0);
    }

    for (long i = 2; ; i++)
    {
        long get = 0;
        for (int j = 0; j < N2.size(); ++j)
        {
            get += _n2[j] * (long)pow(i, N2.size()-1-j);
        }
        if (get == restore)
            res = i;
        if (get < restore)
            continue;
        break;
    }

    if (res != 0)
        cout << res << endl;
    else
        cout << "Impossible" << endl;
}