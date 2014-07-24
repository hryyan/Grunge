#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct P
{
    string id;
    int c, m, e;
    int crank, mrank, erank, arank;
    double a;
    P(string _id, int _c, int _m, int _e)\
    :id(_id), c(_c), m(_m), e(_e){a=(double)(_c+_m+_e)/3;};
    P():c(-1), m(-1), e(-1), a(-1){};
};

struct Cmp1{
    bool operator()(P p1, P p2){return p1.c > p2.c;}
} cMore;

struct Cmp2{
    bool operator()(P p1, P p2){return p1.m > p2.m;}
} mMore;

struct Cmp3{
    bool operator()(P p1, P p2){return p1.e > p2.e;}
} eMore;

struct Cmp4{
    bool operator()(P p1, P p2){return p1.a > p2.a;}
} aMore;

P v[2200];

int main()
{
    // freopen("PAT1012.input", "r", stdin);

    string id;
    int N, M, c, m, e, a;
    cin >> N >> M;
    for (int i = 0; i < N; ++i)
    {
        cin >> id >> c >> m >> e;
        v[i] = P(id, c, m, e);
    }

    int pre = -1, cur = -1, rank = -1;
    sort(v, v+2200, cMore);
    for (int i = 0; i < N; ++i)
    {
        if (i == 0)
        {
            rank = 1;
            pre = v[i].c;
        }
        else if (v[i].c != pre)
        {
            rank++;
            pre = v[i].c;
        }
        v[i].crank = rank;
    }

    pre = -1, cur = -1, rank = -1;
    sort(v, v+2200, mMore);
    for (int i = 0; i < N; ++i)
    {
        if (i == 0)
        {
            rank = 1;
            pre = v[i].m;
        }
        else if (v[i].m != pre)
        {
            rank++;
            pre = v[i].m;
        }
        v[i].mrank = rank;
    }

    pre = -1, cur = -1, rank = -1;
    sort(v, v+2200, eMore);
    for (int i = 0; i < N; ++i)
    {
        if (i == 0)
        {
            rank = 1;
            pre = v[i].e;
        }
        else if (v[i].e != pre)
        {
            rank++;
            pre = v[i].e;
        }
        v[i].erank = rank;
    }

    double p = -1.;
    pre = -1, rank = -1;
    sort(v, v+2200, aMore);
    for (int i = 0; i < N; ++i)
    {
        if (i == 0)
        {
            rank = 1;
            p = v[i].a;
        }
        else if (v[i].a != p)
        {
            rank++;
            p = v[i].a;
        }
        v[i].arank = rank;
    }

    for (int i = 0; i < M; ++i)
    {
        cin >> id;
        int index = -1;
        for (int j = 0; j < N && index == -1; ++j)
            if (v[j].id == id)
                index = j;
        if (index == -1)
            cout << "N/A" << endl;
        else
        {
            P p = v[index];
            if (p.arank <= p.crank && p.arank <= p.mrank && \
                p.arank <= p.erank)
                cout << p.arank << " " << "A" << endl;
            else if (p.crank < p.arank && p.crank <= p.mrank && \
                p.crank <= p.erank)
                cout << p.crank << " " << "C" << endl;
            else if (p.mrank < p.arank && p.mrank < p.crank && \
                p.mrank <= p.erank)
                cout << p.mrank << " " << "M" << endl;
            else
                cout << p.erank << " " << "E" << endl;
        }
    }
}