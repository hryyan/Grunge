#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int N, M;

struct Person
{
    string id;
    int c, m, e;
    double a;
    int rankc, rankm, ranke, ranka;
    Person(string _id, int _c, int _m, int _e)\
    :id(_id), c(_c), m(_m), e(_e){
        a = (double)(c+m+e) / 3;
    }
    Person(){id = ""; c = m = e = a = -1;}
};

Person v[2200];
int index;

struct Comp1{
    bool operator()(Person a, Person b){
        return a.c > b.c;}
}cMore;

struct Comp2{
    bool operator()(Person a, Person b){
        return a.m > b.m;}
}mMore;

struct Comp3{
    bool operator()(Person a, Person b){
        return a.e > b.e;}
}eMore;

struct Comp4{
    bool operator()(Person a, Person b){
        return a.a > b.a;}
}aMore;

int main()
{
    // freopen("PAT1012.input", "r", stdin);

    string id;
    int c, m, e;
    cin >> N >> M;
    while (N--)
    {
        cin >> id >> c >> m >> e;
        v[index++] = Person(id, c, m, e);
    }

    double p = -1.;
    int r = 0;
    sort(v, v+index, aMore);
    for (int i = 0; i < index; ++i){
        if (v[i].a != p){
            r = i+1;
            p = v[i].a;
        }
        else
            r = v[i-1].ranka;
        v[i].ranka = r;
    }

    int pre = -1;
    r = 0;
    sort(v, v+index, cMore);
    for (int i = 0; i < index; ++i){
        if (v[i].c != pre){
            r = i+1;
            pre = v[i].c;
        }
        else
            r = v[i-1].rankc;
        v[i].rankc = r;
    }

    pre = -1, r = 0;
    sort(v, v+index, mMore);
    for (int i = 0; i < index; ++i){
        if (v[i].m != pre){
            r = i+1;
            pre = v[i].m;
        }
        else
            r = v[i-1].rankm;
        v[i].rankm = r;
    }

    pre = -1, r = 0;
    sort(v, v+index, eMore);
    for (int i = 0; i < index; ++i){
        if (v[i].e != pre){
            r = i+1;
            pre = v[i].e;
        }
        else
            r = v[i-1].ranke;
        v[i].ranke = r;
    }

    while (M--)
    {
        cin >> id;
        int d = -1;
        for (int i = 0; i < index; ++i)
            if (v[i].id == id)
                d = i;
        if (d == -1)
            cout << "N/A" << endl;
        else
        {
            Person p = v[d];
            if (p.ranka <= p.rankc && p.ranka <= p.rankm && \
                p.ranka <= p.ranke)
                cout << p.ranka << " A" << endl;
            if (p.rankc < p.ranka && p.rankc <= p.rankm && \
                p.rankc <= p.ranke)
                cout << p.rankc << " C" << endl;
            if (p.rankm < p.ranka && p.rankm < p.rankc && \
                p.rankm <= p.ranke)
                cout << p.rankm << " M" << endl;
            if (p.ranke < p.ranka && p.ranke < p.rankc && \
                p.ranke < p.rankm)
                cout << p.ranke << " E" << endl;
        }
    }
}