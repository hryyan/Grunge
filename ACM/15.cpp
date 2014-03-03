#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    freopen("15.input", "r", stdin);
    int n, a=0, b=0, c=0, d=0, e=0, tmp=0;
    int *s;
    bool found;
    s = (int*)malloc(sizeof(int)*10);
    while(scanf("%d", &n) == 1)
    {
        a = 0;
        while(a<10)
        {
            b = 0;
            while(b<10)
            {
                c = 0;
                while(c<10)
                {
                    d = 0;
                    while(d<10)
                    {
                        e = 0;
                        while(e<10)
                        {
                            found = false;
                            tmp = a*10000+b*1000+c*100+d*10+e;
                            if(tmp % n == 0)
                            {
                                s[0] = a;
                                s[1] = b;
                                s[2] = c;
                                s[3] = d;
                                s[4] = e;
                                tmp /= n;
                                s[5] = tmp / 10000;
                                s[6] = tmp % 10000 / 1000;
                                s[7] = tmp % 1000 / 100;
                                s[8] = tmp % 100 / 10;
                                s[9] = tmp % 10;
                                for (int i = 0; i < 10; ++i)
                                    for (int j = i+1; j < 10; ++j)
                                        if (s[i] == s[j])
                                        {
                                            found = true;
                                            break;
                                        }
                                if (!found)
                                    printf("%d%d%d%d%d / %d%d%d%d%d = %d\n", s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[8], s[9], n);                      
                            }
                            e++;
                        }
                        d++;
                    }
                    c++;
                }
                b++;
            }
            a++;
        }
    }
    free(s);
}