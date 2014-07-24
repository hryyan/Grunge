#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

void insert_sort(int *a, int size)
{
    for (int i = 1; i < size; ++i)
    {
        int t = a[i];
        int j;
        for (j = i-1; j >= 0 && a[j] > t; --j)
            a[j+1] = a[j];
        a[j+1] = t;
    }
}

int main()
{
    srand(time(NULL));
    int v[1000];
    for (int i = 0; i < 1000; ++i)
        v[i] = rand() % 1000;
    insert_sort(v, 1000);
    for (int i = 0; i < 1000; ++i)
        cout << v[i] << " ";
    cout << endl;
}