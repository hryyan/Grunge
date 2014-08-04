/*************************************************************************
	> File Name: PAT1019.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月04日 星期一 16时35分58秒
 ************************************************************************/

#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;

int bit[50];

int main()
{
    //freopen("PAT1019.input", "r", stdin);
    int N, b;
    
    cin >> N >> b;
    int flag = 30;
    while (pow(b, flag) > N)
        flag--;

    for (int i = flag; i >= 0; i--)
    {
        bit[i] = N % (int)pow(b, i+1) / (int)pow(b, i);
    }

    int on = true;
    for (int i = flag; i >= 0; i--)
    {
        if (bit[i] != bit[flag-i])
            on = false;
    }
    if (on)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    if (N == 0)
        cout << N;
    for (int i = flag; i >= 0; i--)
    {
        cout << bit[i];
        if (i != 0)
            cout << " ";
    }
    cout << endl;
}
