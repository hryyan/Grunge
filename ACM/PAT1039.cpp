/*************************************************************************
	> File Name: PAT1039.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月09日 星期六 18时05分38秒
 ************************************************************************/

#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

vector<short> m[50000];
vector<short> key;
map<string, int> name;

vector<short> search(string s)
{
    vector<short> vec;
    for (int i = 0; i < key.size(); i++)
    {
        for (int j = 0; j < m[key[i]].size(); j++)
        {
            if (m[key[i]][j] == s)
                vec.push_back(key[i]);
        }
    }
    return vec;
}

int main()
{
    //freopen("PAT1039.input", "r", stdin);

    int N, K;
    int index, num;
    int mmm = 0;
    scanf("%d %d", &N, &K);
    while (K--)
    {
        scanf("%d %d", &index, &num);
        key.push_back(index);
        while (num--)
        {
            char s[4];
            scanf("%s ", s);
            if (name.find(string(s)) == name.end())
                name.insert(s, mmm);
            m[index].push_back(mmm);
        }
    }

    while (N--)
    {
        char s[4];
        scanf("%s ", s);
        vector<short> vec = search(s);
        sort(vec.begin(), vec.end());
        if (vec.size() != 0)
            cout << s << " " << vec.size() << " ";
        else
            cout << s << " " << vec.size();
        for (int i = 0; i < vec.size(); i++)
        {
            if (i == vec.size()-1)
                cout << vec[i] << endl;
            else
                cout << vec[i] << " ";
        }
    }
}
