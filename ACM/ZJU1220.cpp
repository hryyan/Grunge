#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
using namespace std;

struct guy
{
    string name;
    set<string> gen;
    guy(string n) {name = n;};
    bool addGen(string g)
    { 
        if (gen.end() == find(gen.begin(), gen.end(), g))
        {
            gen.insert(g);
            return true;
        }
        else
            return false;
    };
};

vector<guy> list;

bool findName(guy someone, string testName)
{
    if (someone.name == testName)
        return true;
    else
        return false;
}

int main()
{
    bool consistent, safe;
    int n;
    char w_desname[15], w_srcname[15], w_gen[10], buffer[1000];
    vector<guy>::iterator it;

    guy ADAM = guy(string("ADAM"));
    list.push_back(ADAM);

    // freopen("ZJU1220.input", "r", stdin);
    fgets(buffer, 1000, stdin);
    while (sscanf(buffer, "clone %s from %s", w_desname, w_srcname) == 2)
    {
        n = 0;
        consistent = true;  safe = true;
        if ((it = find_if(list.begin(), list.end(), bind2nd(ptr_fun(findName), w_srcname))) != list.end())
        {
            guy oneguy = guy(w_desname);
            oneguy.gen = it->gen;
            n = 12 + strlen(w_srcname) + strlen(w_desname);
            while (sscanf(buffer+n, "%s", w_gen) == 1)
            {
                if (!strcmp(w_gen, "mutating"))
                {
                    n += 10;
                    continue;
                }
                if (!oneguy.addGen(w_gen))
                {
                    safe = false;
                    break;
                }
                n += 4;
            }
            if (safe)
                list.push_back(oneguy);
        }
        else
            consistent = false;

        printf("clone %s from %s ", w_desname, w_srcname);
        if (consistent && safe)
            printf("is consistent and safe\n");
        else if (consistent)
            printf("was at least twice mutated %s\n", w_gen);
        else
            printf("has no connection to ADAM\n");

        if (fgets(buffer, 1000, stdin) == NULL)
            break;
    }
    return 0;
}