#include <stdio.h>
const int maxlen = 1000000;
int coin[maxlen];

int main()
{
    freopen("22.input", "r", stdin);
    int n;
    while(scanf("%d", &n) == 1)
    {
        int index = 0;
        while(n--)
        {
            scanf("%d", &(coin[index]));
            index++;
        }
        int sum = 0;
        for (int i = 0; i < index; ++i)
            sum += coin[i];
        for (int i = 0; i < index; ++i)
            coin[i] -= sum/index;

        int cost = 0;
        for (;;)
        {
            int max = 0, maxlabel = 0;
            for (int i = 0; i < index; ++i)
                if (coin[i] > max)
                {
                    max = coin[i];
                    maxlabel = i;                    
                }
            if (max == 0)
                break;
            else
                for (int i = 0; i < index/2; ++i)
                {
                    int plusOne = (maxlabel+1+i)%index;
                    int minuxOne = maxlabel-1-i < 0 ? (maxlabel-1-i+index)%index : maxlabel-1-i;
                    if (coin[plusOne] < 0)
                    {
                        coin[maxlabel]--;
                        coin[plusOne]++;
                        int distance = plusOne-maxlabel>0?plusOne-maxlabel:plusOne-maxlabel+index;
                        cost += distance;
                        continue;
                    }
                    if (coin[minuxOne] < 0)
                    {
                        coin[maxlabel]--;
                        coin[minuxOne]++;
                        int distance = maxlabel-minuxOne>0?maxlabel-minuxOne:maxlabel-minuxOne+index;
                        cost += distance;
                    }
                }
        }
        printf("%d\n", cost);
    }
    return 0;
}