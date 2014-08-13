/*************************************************************************
	> File Name: ACM/STLtest.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月10日 星期日 16时37分36秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

int main()
{
    priority_queue<int, vector<int>, less<int> > pq;
    deque<int> deq;
    vector<int> vec;
    set<int, less<int> > s;
    multiset<int, less<int> > ms;
    for (int i = 0; i < 10; i++)
    {
        pq.push(i);
        s.insert(i);
        ms.insert(i);
        pq.push(i);
        s.insert(i);
        ms.insert(i);
        deq.push_back(i-1);
    }
    while (!pq.empty())
    {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
    for (set<int, less<int> >::iterator it = s.begin(); it != s.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    for (multiset<int, less<int> >::iterator it = ms.begin(); it != ms.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    vec = vector<int>(ms.begin(), ms.end());
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}
