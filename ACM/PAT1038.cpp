/*************************************************************************
	> File Name: PAT1038.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月09日 星期六 16时29分46秒
 ************************************************************************/

#include <cstdio>
#include <queue>
#include <string>
#include <iostream>
using namespace std;

struct MyString
{
    string data;
    int len;
    MyString(string _data, int _len):data(_data), len(_len){};
};

struct Comp
{
    bool operator()(MyString s1, MyString s2)
    {
        return s1.data > s2.data;
    }
};

priority_queue<MyString, vector<MyString>, Comp> que;

int main()
{
    //freopen("PAT1038.input", "r", stdin);

    int N;
    string a;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> a;
        int tmp = a.size();
        a.resize(8);
        for (int i = tmp; i < 8; i++)
            a[i] = a[i-tmp];
        que.push(MyString(a, tmp));
    }

    bool first = true;
    while (!que.empty())
    {
        MyString a = que.top();
        que.pop();

        if (first)
        {
            // 陷阱：数字为0
            int start = 0;
            for (int i = 0; i < a.len; i++)
                if (a.data[i] == '0')
                    start++;
                else
                    break;
            if (start == a.len)
                continue;
            a.len -= start;
            first = false;
            cout << a.data.substr(start, a.len);
        }
        else
            cout << a.data.substr(0, a.len);
    }
    // 陷阱：如果所有数为0
    if (first)
        cout << 0;
    cout << endl;
}
