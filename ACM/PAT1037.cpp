/*************************************************************************
	> File Name: PAT1037.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月09日 星期六 15时48分05秒
 ************************************************************************/

#include <cstdio>
#include <queue>
#include <iostream>
using namespace std;

priority_queue<int, vector<int>, less<int> > c1;
priority_queue<int, vector<int>, greater<int> > c2;
priority_queue<int, vector<int>, less<int> > d1;
priority_queue<int, vector<int>, greater<int> > d2;

int main()
{
    //freopen("PAT1037.input", "r", stdin);

    int N, tmp;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> tmp;
        if (tmp > 0)
            c1.push(tmp);
        else if (tmp < 0)
            c2.push(tmp);
    }

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> tmp;
        if (tmp > 0)
            d1.push(tmp);
        else if (tmp < 0)
            d2.push(tmp);
    }

    long long sum = 0;
    while (!c1.empty() && !d1.empty())
    {
        int a = c1.top();
        int b = d1.top();
        c1.pop();
        d1.pop();
        sum += a*b;
    }

    while (!c2.empty() && !d2.empty())
    {
        int a = c2.top();
        int b = d2.top();
        c2.pop();
        d2.pop();
        sum += a*b;
    }

    cout << sum << endl;
}
