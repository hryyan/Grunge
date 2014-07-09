#include <cstdio>
#include <vector>
using std::vector;

vector<int> vec;
int main()
{
    int i = 0;
    while (1)
    {
        vec.push_back(i);
        if (vec.size() == 600)
            vec.erase(vec.begin(), vec.begin()+100);
        printf("%d\n", i);
        i++;
    }
}