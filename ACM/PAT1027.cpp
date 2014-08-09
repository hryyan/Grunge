/*************************************************************************
	> File Name: PAT1027.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月07日 星期四 09时31分19秒
 ************************************************************************/

#include <cstdio>
#include <cmath>
#include <string>
#include <iostream>
using namespace std;
char c[3];

char* process(int n)
{
    int up = n / 13;
    int low = n % 13;
    if (up < 10)
        c[0] = up + '0';
    else if (up == 10)
        c[0] = 'A';
    else if (up == 11)
        c[0] = 'B';
    else
        c[0] = 'C';

    if (low < 10)
        c[1] = low + '0';
    else if (low == 10)
        c[1] = 'A';
    else if (low == 11)
        c[1] = 'B';
    else
        c[1] = 'C';

    return c;
}

int main()
{
    //freopen("PAT1027.input", "r", stdin);

    int r, g, b;
    cin >> r >> g >> b;
    cout << "#" << process(r);
    cout << process(g);
    cout << process(b) << endl;
}
