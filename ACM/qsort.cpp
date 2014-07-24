#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int partition(int *a, int start, int end)
{
    int num = start;
    int key = a[end];
    for (int i = start; i < end; ++i)
        if (a[i] < key)
            swap(a[num++], a[i]);
    swap(a[num], a[end]);
    return num;
}

void qsort(int *a, int start, int end)
{
    if (start < end)
    {
        int q = partition(a, start, end);
        qsort(a, start, q-1);
        qsort(a, q+1, end);        
    }
}

int main()
{
    srand(time(NULL));
    int v[1000];
    for (int i = 0; i < 1000; ++i)
        v[i] = rand() % 1000;
    qsort(v, 0, 999);
    for (int i = 0; i < 1000; ++i)
        cout << v[i] << " ";
    cout << endl;
}