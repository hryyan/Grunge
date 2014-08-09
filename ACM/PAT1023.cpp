/*************************************************************************
	> File Name: PAT1023.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月05日 星期二 14时51分37秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
using namespace std;

int n[30];
int a[10];

int main()
{
    //freopen("PAT1023.input", "r", stdin);

    int i = 0;
    char c;
    while ((c = getchar()) >= '0' && c <= '9')
    {
        n[i++] = c-'0';
        a[c-'0']++;
    }

    int g = 0;
    for (int j = i-1; j >= 0; j--)
    {
        int b = (n[j]*2+g);
        n[j] = b % 10;
        g = b / 10;
    }
    if (g > 0)
    {
        for (int j = i; j > 0; j--)
            n[j] = n[j-1];
        n[0] = 1;
        i++;
    }
    
    bool on = true;
    for (int j = 0; j < i; j++)
    {
        if (a[n[j]]-- == 0)
            on = false;
    }

    if (on)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    for (int j = 0; j < i; j++)
    {
        cout << n[j];
    }
    cout << endl;
}
