/*************************************************************************
	> File Name: PAT1024.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月05日 星期二 15时19分51秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
using namespace std;

int num[110];
int max_step;
int index;

bool isPa()
{
    for (int i = index-1; i >= 0; i--)
        if (num[index-1-i] != num[i])
            return false;
    return true;
}

void onestep()
{
    int tmp[110];
    for (int i = index-1; i >= 0; i--)
    {
        tmp[i] = num[index-1-i];
    }

    int g = 0;
    for (int i = index-1; i >= 0; i--)
    {
        int a = num[i]+tmp[i]+g;
        num[i] = a % 10;
        g = a / 10;
    }
    if (g == 1)
    {
        for (int i = index; i > 0; i--)
            num[i] = num[i-1];
        num[0] = 1;
        index++;
    }

    //for (int i = 0; i < index; i++)
    //    cout << num[i];
}

int main()
{
    //freopen("PAT1024.input", "r", stdin);
    //freopen("PAT1024.input2", "r", stdin);

    char c;
    while ((c = getchar()) != ' ')
    {
        num[index++] = c-'0';
    }
    cin >> max_step;

    if (isPa())
    {
        for (int i = 0; i < index; i++)
            cout << num[i];
        cout << endl << 0 << endl;
        return 0;
    }

    for (int i = 1; i <= max_step; i++)
    {
        onestep();
        if (isPa())
        {
            for (int j = 0; j < index; j++)
                cout << num[j];
            cout << endl << i << endl;
            return 0;
        }
    }
    for (int j = 0; j < index; j++)
        cout << num[j];
    cout << endl << max_step << endl;
}
