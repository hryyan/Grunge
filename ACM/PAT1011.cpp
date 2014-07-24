#include <cstdio>
#include <iostream>
using namespace std;

double data[3];
int position[3];
char str[3] = {'W', 'T', 'L'};

int main()
{
    // freopen("PAT1011.input", "r", stdin);

    double w, t, l, max;

    for (int i = 0; i < 3; i++)
    {
        cin >> w >> t >> l;
        max = w > t ? w : t;
        max = max > l ? max : l;
        data[i] = max;
        if (max == w)
            position[i] = 0;
        else if (max == t)
            position[i] = 1;
        else if (max == l)
            position[i] = 2;
    }
    
    cout << str[position[0]] << " " << str[position[1]] << \
    " " << str[position[2]] << " ";
    printf("%.2f\n", 2*(data[0]*data[1]*data[2]*0.65-1));
}