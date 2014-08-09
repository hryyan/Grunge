/*************************************************************************
	> File Name: PAT1031.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月08日 星期五 18时51分28秒
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int main()
{
    //freopen("PAT1031.input", "r", stdin);

    char s[100];
    scanf("%s\n", s);
    int size = strlen(s);

    int n1, n2, n3;
    n1 = (size+2) / 3;
    n2 = size + 2 - n1 * 2;

    int offset = n2 - 2;
    for (int i = 0; i < n1-1; i++)
    {
        cout << s[i];
        for (int j = 0; j < offset; j++)
            cout << " ";
        cout << s[size-1-i] << endl;
    }
    for (int i = n1-1; i < n1+n2-1; i++)
        cout << s[i];
    cout << endl;
}
