#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    // freopen("PAT1008.input", "r", stdin);

    int num = 0;
    cin >> num;
    int req[num];
    for (int i = 0; i < num; ++i)
        cin >> req[i];

    int sum = 0;
    sum += num * 5;
    sum += req[0] * 6;
    for (int i = 1; i < num; ++i)
    {
        int j = req[i-1] - req[i];
        if (j > 0)
            sum += j * 4;
        else
            sum -= j * 6;
    }
    cout << sum;
}