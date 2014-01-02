#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
using namespace std;

const int maxn = 1000;
struct bign
{
    int len, s[maxn];

    bign()
    {
        memset(s, 0, sizeof(s));
        len = 1;
    }

    bign(int num) { *this = num; }
    bign(const char* num) {*this = num;}

    void clean()
    {
        while(len > 1 && !s[len-1]) len--;
    }

    bign operator = (const char* num)
    {
        len = strlen(num);
        for (int i = 0; i < len; i++)
        {
            s[i] = num[len-i-1] - '0';
        }
        return *this;
    }

    bign operator = (int num)
    {
        char s[maxn];
        sprintf(s, "%d", num);
        *this = s;
        return *this;
    }

    bign operator + (const bign& b) const
    {
        bign c;
        c.len = 0;

        for (int i = 0, g = 0; g || i < max(len, b.len); i++ )
        {
            int x = g;
            if (i < len)
            {
                x += s[i];
            }
            if (i < b.len)
            {
                x += b.s[i];
            }
            c.s[c.len++] = x % 10;
            g = x / 10;
        }
        return c;
    }

    bign operator += (const bign& b)
    {
        *this = *this + b;
        return *this;
    }

    bign operator += (int a)
    {
        *this = *this + a;
        return *this;
    }

    bign operator - (const bign& b) const
    {
        bign c;
        c.len = 0;

        bign bigger, smaller;
        if (*this < b)
        {
            smaller = *this;
            bigger = b;
        }
        else
        {
            smaller = b;
            bigger = *this;
        }

        for (int i = 0, g = 0; i < bigger.len; i++)
        {
            int x = g;
            if (i < smaller.len)
            {
                x = bigger.s[i] - smaller.s[i] - x;
            }
            else
            {
                x = bigger.s[i] - x;
            }
            if (x < 0)
            {
                x += 10;
                g = 1;
            }
            c.s[c.len++] = x;
        }
        c.clean();
        return c;
    }

    bign operator -= (const bign& b)
    {
        *this = *this - b;
        return *this;
    }

    bign operator * (const bign& b)
    {
        bign c;
        c.len = len + b.len;
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < b.len; ++j)
            {
                c.s[i+j] += s[i] * b.s[j];
            }
        }
        for (int i = 0; i < c.len-1; ++i)
        {
            c.s[i+1] += c.s[i] / 10;
            c.s[i] = c.s[i] % 10;
        }
        c.clean();
        return c;
    }

    bool operator < (const bign& b) const
    {
        if (len != b.len)
        {
            return len < b.len;
        }
        for (int i = len-1; i >= 0; i--)
        {
            if (s[i] != b.s[i])
            {
                return s[i] < b.s[i];
            }
        }
        return false;
    }

    bool operator > (const bign& b) const
    {
        return b < *this;
    }

    bool operator <= (const bign& b) const
    {
        return !(b < *this);
    }

    bool operator >= (const bign& b) const
    {
        return !(*this < b);
    }

    bool operator == (const bign& b) const
    {
        return !(b < *this) && !(*this < b);
    }

    bool operator != (const bign& b) const
    {
        return !(*this == b);
    }

    string str() const
    {
        int i = 0;
        string res = "";
        for (i = 0; i < len; i++)
        {
            res = (char)(s[i] + '0') + res;
            if (res == "")
            {
                res = "0";
            }
        }
        return res;
    }
};

istream& operator >> (istream &in, bign &x)
{
    string s;
    in >> s;
    x = s.c_str();
    return in;
}

ostream& operator << (ostream &out, const bign &x)
{
    out << x.str();
    return out;
}