#include <cstdio>
#include <iostream>
using namespace std;

int N;
int data[12000];
int res = -1;
int s, e;
int d[12000];

void dp()
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N-i; ++j)
        {
            if (j == 0)
                d[j] = data[i];
            else
                d[j] = d[j-1] + data[i+j];
            if (d[j] > res)
            {
                res = d[j];
                s = i;
                e = i+j;
            }
        }
    }
    if (res == -1)
    {
        res = 0;
        s = 0;
        e = N-1;
    }
}

int main()
{
    // freopen("PAT1007.input", "r", stdin);

    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> data[i];

    dp();
    cout << res << " " << data[s] << " " << data[e] << endl;
}