/*************************************************************************
	> File Name: PAT1029.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月07日 星期四 10时27分51秒
 ************************************************************************/

#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

long v1[2000100];
long v2[2000100];
int index1;
int index2;

int main()
{
    //freopen("PAT1029.input", "r", stdin);

    int n1, n2, total;
    scanf("%d", &n1);
    total = n1;
    for (index1 = 0; index1 < n1; index1++)
    {
        scanf("%ld", &v1[index1]);
    }
    scanf("%d", &n2);
    total += n2;
    for (index2 = 0; index2 < n2; index2++)
    {
        scanf("%ld", &v2[index2]);
    }

    int index1 = index2 = 0;
    for (int i = 0; i < (total-1)/2; i++)
    {
        if (index1 == n1)
            index2++;
        else if (index2 == n2)
            index1++;
        else if (v1[index1] < v2[index2])
            index1++;
        else
            index2++;
    }

    if (index1 == n1)
        printf("%ld\n", v2[index2]);
    else if (index2 == n2)
        printf("%ld\n", v1[index1]);
    else if (v1[index1] < v2[index2])
        printf("%ld\n", v1[index1]);
    else
        printf("%ld\n", v2[index2]);
}
