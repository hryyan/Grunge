/*************************************************************************
	> File Name: APAT1001.cpp
	> Author:
	> Mail:
	> Created Time: 2014年08月11日 星期一 09时54分39秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
using namespace std;

struct Sum
{
    private:
    int s;

    public:
    Sum(int _s):s(_s){}
    void operator()(int a){
        s += a;
    }
    string value(){
        string a = to_string(s);
        int i = a.size();
        while ((i -= 3) > 0 && a[i-1] != '-')
            a.insert(i, ",");
        return a;
    }
};

int main()
{
    freopen("../PAT1001.input", "r", stdin);
    vector<int> vec;

    copy(istream_iterator<int>(cin),
        istream_iterator<int>(),
        back_inserter(vec));

    Sum s = for_each(vec.begin(), vec.end(), Sum(0));
    cout << s.value() << endl;
}
