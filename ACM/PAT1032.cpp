/*************************************************************************
	> File Name: PAT1032.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月08日 星期五 19时51分12秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
using namespace std;

struct Node
{
    int next_node;
    bool visited;
};

Node m[110000];

int find(int start)
{
    while (!m[start].visited && start != -1)
    {
        m[start].visited = true;
        start = m[start].next_node;
    }
    return start;
}

int main()
{
    //freopen("PAT1032.input", "r", stdin);

    int a, b, N;
    int address, next;
    char c;
    scanf("%d %d %d", &a, &b, &N);
    while (N--)
    {
        //cin >> address >> c >> next;
        scanf("%d %c %d\n", &address, &c, &next);
        m[address].next_node = next;
        m[address].visited = false;
    }

    find(a);
    int result = find(b);
    
    if (result == -1)
        printf("-1");
    else
        printf("%05d", result);
}
