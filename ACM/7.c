//http://acm.hdu.edu.cn/game/entry/problem/show.php?chapterid=2&sectionid=1&problemid=9

#include <stdio.h>
#include <math.h>
#include <set>

int main(void)
{
    __int64 n, a, b, c, i;
    freopen("7.input", "r", stdin);
    std::set<__int64> v;

    while(scanf("%I64d", &n) != EOF)
    {
        v.clear();
        for (i = 1; n >= i; i = i * 10)
        {
            a = (n / i) / 11;

            b = (n / i) % 11;
            if (b < 10 && (a != 0 || b != 0))
            {
                c = n - a * i * 11 - b * i;
                if (c % 2 == 0)
                {
                    v.insert(a * 11 * i + b * i + c / 2);
                }
            }

            b = (n / i) % 11 - 1;
            if (b >= 0 && (a != 0 || b != 0))
            {
                c = n - a * i * 11 - b * i;
                if (c % 2 == 0)
                {
                    v.insert(a * 11 * i + b * i + c / 2);
                }            }
        }

        if (v.size() == 0)
        {
            printf("No solution.\n");
            continue;
        }

        i = 0;
        for (std::set<__int64>::iterator index = v.begin(); index != v.end(); ++index, ++i)
        {
            printf("%I64d%c", *index, (i == v.size() - 1)? '\n' : ' ');
        }
    }
}