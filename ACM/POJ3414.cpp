#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
using std::queue;

struct P
{
    int a;
    int b;
    int step;
    char* str;
    P(int _a, int _b, int _step, char* _str)\
    :a(_a), b(_b), step(_step), str(_str){};
};

int A, B, c;
char str[3][10] = {"FILL", "DROP", "POUR"};
queue<P> que;
bool iVisited[200][200];

void filter(P p)
{
    if (iVisited[p.a][p.b] == false)
        que.push(p);
    iVisited[p.a][p.b] = true;
}

void bfs(bool a_first)
{
    while (!que.empty())
        que.pop();

    char *a = (char*)malloc(sizeof(char)*5000);
    memset(a, 0, sizeof(char)*5000);
    que.push(P(0, 0, 0, a));
    char s1[15], s2[15], s3[15], s4[15];
    memset(s1, 0, sizeof(s1));
    memset(s2, 0, sizeof(s2));
    memset(s3, 0, sizeof(s3));
    memset(s4, 0, sizeof(s4));
    if (a_first)
    {
        sprintf(s1, "(1)");
        sprintf(s2, "(2)");
        sprintf(s3, "(1,2)");
        sprintf(s4, "(2,1)");
    }
    else
    {
        sprintf(s1, "(2)");
        sprintf(s2, "(1)");
        sprintf(s3, "(2,1)");
        sprintf(s4, "(1,2)");
    }

    while (!que.empty())
    {
        P p = que.front();
        que.pop();

        // printf("%s\n", p.str);

        if (p.a == c)
        {
            printf("%d", p.step);
            printf("%s\n", p.str);
            return;
        }

        // pour a to b
        if (p.a != 0 && p.b != B)
        {
            char* tmp = (char*)malloc(sizeof(char)*5000);
            memcpy(tmp, p.str, sizeof(char)*5000);
            strcat(tmp, "\n");
            strcat(tmp, str[2]);
            strcat(tmp, s3);
            if (p.a >= B-p.b)     // a里面的水能把b装满
                filter(P(p.a-(B-p.b), B, p.step+1, tmp));
            else                    // 不能装满
                filter(P(0, p.b+p.a, p.step+1, tmp));
        }

        // pour b to a
        if (p.a != A && p.b != 0)
        {
            char* tmp = (char*)malloc(sizeof(char)*5000);
            memcpy(tmp, p.str, sizeof(char)*5000);
            strcat(tmp, "\n");
            strcat(tmp, str[2]);
            strcat(tmp, s4);
            if (A-p.a <= p.b)     // b里面的水能把a装满
                filter(P(A, p.b-(A-p.a), p.step+1, tmp));
            else                    // 不能装满
                filter(P(p.b+p.a, 0, p.step+1, tmp));
        }

        // drop a
        if (p.a != 0)
        {
            char* tmp = (char*)malloc(sizeof(char)*5000);
            memcpy(tmp, p.str, sizeof(char)*5000);
            strcat(tmp, "\n");
            strcat(tmp, str[1]);
            strcat(tmp, s1);
            filter(P(0, p.b, p.step+1, tmp));
        }

        // drop b
        if (p.b != 0)
        {
            char* tmp = (char*)malloc(sizeof(char)*5000);
            memcpy(tmp, p.str, sizeof(char)*5000);
            strcat(tmp, "\n");
            strcat(tmp, str[1]);
            strcat(tmp, s2);
            filter(P(p.a, 0, p.step+1, tmp));
        }

        // fill a
        if (p.a == 0)
        {
            char* tmp = (char*)malloc(sizeof(char)*5000);
            memcpy(tmp, p.str, sizeof(char)*5000);
            strcat(tmp, "\n");
            strcat(tmp, str[0]);
            strcat(tmp, s1);
            filter(P(A, p.b, p.step+1, tmp));
        }

        // fill b
        if (p.b == 0)
        {
            char* tmp = (char*)malloc(sizeof(char)*5000);
            memcpy(tmp, p.str, sizeof(char)*5000);
            strcat(tmp, "\n");
            strcat(tmp, str[0]);
            strcat(tmp, s2);
            filter(P(p.a, B, p.step+1, tmp));
        }

        if (que.empty())
            printf("impossible\n");
    }
}

int main()
{
    // freopen("POJ3414.input", "r", stdin);

    int m, n;
    scanf("%d %d %d\n", &m, &n, &c);
    A = (m > c) ? m : n;
    B = (A == m) ? n : m;
    if (A == m)
        bfs(true);
    else
        bfs(false);
    return 0;
}