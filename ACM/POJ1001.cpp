#include <stdio.h>
#include <string.h>

const int MAXN = 200;
char num[MAXN];

void multi(unsigned char a[], unsigned char b[])
{
    unsigned char tmp[MAXN];
    memset(tmp, 0, MAXN*sizeof(unsigned char));
    int a_point = 0;
    int b_point = 0;
    int a_end = 0;
    int b_end = 0;
    int maxbit = 0;
    for (int i = 0; i < MAXN; ++i)
    {
        if (a[i] == '.')
            a_point = i;
        if (a[i] == 0)
        {
            a_end = i;
            break;
        }
    }

    for (int i = 0; i < MAXN; ++i)
    {
        if (b[i] == '.')
            b_point = i;
        if (b[i] == 0)
        {
            b_end = i;
            break;
        }
    }

    for (int i = 0, ri = 0; i < b_end; i++, ri++)
    {
        if (b[i] == '.')
        {
            ri--;
            continue;
        }
        for (int j = 0, rj = 0; j < a_end; j++, rj++)
        {
            if (a[j] == '.')
            {
                rj--;
                continue;
            }
            else if (a[j] && b[i])
                tmp[rj+ri] += (a[j]-48) * (b[i]-48);
            maxbit = maxbit>(ri+rj)?maxbit:(ri+rj);
        }

    }

    for (int i = 0; i <= maxbit; i++)
    {
        tmp[i+1] += tmp[i] / 10;
        tmp[i] = tmp[i] % 10;
    }

    if (tmp[maxbit+1] != 0)
        maxbit++;

    for (int i = 0; i <= maxbit; i++)
        tmp[i] += 48;

    int offset = 0;
    for (int i = 0; i <= maxbit+1; i++)
    {
        if (i == a_point+b_point)
        {
            a[i] = '.';
            offset++;
        }
        a[i+offset] = tmp[i];
    }

    // printf("%s\n", a);
}

void flip(unsigned char *a, int len)
{
    unsigned char b[10];
    for (int i = 0; i < len; ++i)
    {
        b[i] = a[len-i-1];
    }
    for (int i = 0; i < len; ++i)
    {
        a[i] = b[i];
    }
}

void cutdown_flip(unsigned char *src, unsigned char *des)
{
    int begin, end, len;
    for (int i = 0; i < MAXN; ++i)
    {
        if (src[i] != '0')
        {
            begin = i;
            break;
        }
    }
    for (int i = MAXN-1; i >= 0; --i)
    {
        if (src[i] != '0' && src[i] != 0)
        {
            end = i;
            break;
        }
    }
    len = end - begin;
    for (int i = begin, j = 0; i <= end; i++, j++)
        des[len-j] = src[i];
}

int main()
{
    // freopen("POJ1001.input", "r", stdin);
    unsigned char r[10];
    int n;
    while (scanf("%s %d", &r, &n) == 2)
    {
        unsigned char tmp[MAXN];
        unsigned char dst[MAXN];
        flip(r, 6);
        memset(tmp, 0, MAXN*sizeof(unsigned char));
        memset(dst, 0, MAXN*sizeof(unsigned char));
        memcpy(tmp, r, 6*sizeof(unsigned char));

        for (int i = n; i > 1; --i)
        {
            multi(tmp, r);
        }
        cutdown_flip(tmp, dst);
        printf("%s\n", dst);
        memset(r, 0, 10*sizeof(unsigned char));
    }
    return 0;
}