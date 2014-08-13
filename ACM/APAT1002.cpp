#include <cstdio>
#include <map>
#include <iomanip>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    //freopen("../input", "r", stdin);

    map<int, double, greater<int>> m;
    int N1, N2, n;
    float k;
    cin >> N1;
    while (N1--)
    {
        cin >> n >> k;
        m[n] = k;
    }
    cin >> N2;
    while (N2--)
    {
        cin >> n >> k;
        m[n] += k;
    }

    for (auto it = m.begin(); it != m.end(); it++)
    {
        if (it->second == 0)
            m.erase(it);
    }
    cout << m.size();
    for (auto it = m.begin(); it != m.end(); it++)
    {
        cout << setiosflags(ios::fixed) << setprecision(1) << " " << it->first << " " << it->second;
    }
    cout << endl;
}
