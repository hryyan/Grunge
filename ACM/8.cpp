#include <stdio.h>
#include <algorithm>

int main()
{
    freopen("in.txt", "r", stdin);
    int a, b;
    while((scanf("%d %d", &a, &b)) != -1)
    {
        int tmp, k = 0, g = 0, sum = 0;
        if (a == 0 && b == 0)
            return 0;
        if (a < b) std::swap(a, b);
        tmp = b;
        while ((tmp /= 10) > 0) k++;

        for (int i = 0; i < k + 1; ++i)
        { 
            g = (a%10 + b%10 + g) > 9 ? 1 : 0;
            sum += g;
            a = a / 10; b = b / 10;
        }
        printf("%d\n", sum);
    }
}