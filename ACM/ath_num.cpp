#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int partition(int *v, int start, int end)
{
    int num = 0;
    int key = v[end];
    for (int i = start; i < end; ++i)
        if (v[i] > key)
            swap(v[num++], v[i]);
    swap(v[num], v[end]);
    return num;
}

int find_nth_num(int *v, int start, int end, int i)
{
    if (start == end)
        return v[start];
    int q = partition(v, start, end);
    int k = q - start + 1;
    if (i == k)
        return v[q];
    else if (i < k)
        return find_nth_num(v, start, q-1, i);
    else
        return find_nth_num(v, q+1, end, i-k);
}

int main()
{
    int v[100];
    for (int i = 0; i < 100; ++i)
        v[i] = i;

    int n;
    while (cin >> n)
    {
        int res = find_nth_num(v, 0, 99, n);
        cout << res << endl;
    }
}