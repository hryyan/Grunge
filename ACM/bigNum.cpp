#include "bigNum.h"

bigNum::bigNum()
:length(0), symbol(true)
{
    memset(data, 0, sizeof(data));
}

bigNum::bigNum(const char *num)
{
    *this = num;
}

bigNum::bigNum(int num)
{
    *this = num;
}

bigNum::~bigNum()
{

}

std::string bigNum::str() const
{
    std::string res = "";
    for (int i = 0; i < length; ++i)
        res = (char)(data[i] + '0') + res;
    if (!symbol)
        res = '-' + res;
    if (res == "")
        res = "0";
    return res;
}

bigNum bigNum::operator+(const bigNum& n) const
{
    if (this->symbol == true && n.symbol == true)
        return plusHelper(n, true);
    else if (this->symbol == false && n.symbol == false)
        return plusHelper(n, false);
    else if (this->symbol == true && n.symbol == false)
        return minuxHelper(n);
    else if (this->symbol == false && n.symbol == true)
        return n.minuxHelper(*this);
}

bigNum bigNum::plusHelper(const bigNum& n, bool s) const
{
    bigNum c;
    int g = 0;
    int maxLen = std::max(this->length, n.length);
    for (int i = 0; g || i < maxLen; ++i)
    {
        c.data[i] = (data[i] + n.data[i] + g) % 10;
        g = (data[i] + n.data[i] + g) / 10;
        c.length++;
    }
    c.clean();
    c.symbol = s;
    return c;
}

bigNum bigNum::operator+=(const bigNum& n)
{
    *this = *this + n;
    return *this;
}

bigNum bigNum::operator-(const bigNum& n) const
{
    if (this->symbol == true && n.symbol == true)
        return minuxHelper(n);
    else if (this->symbol == false && n.symbol == false)
        return n.minuxHelper(*this);
    else if (this->symbol == true && n.symbol == false)
        return plusHelper(n, true);
    else if (this->symbol == false && n.symbol == true)
        return plusHelper(n, false);
}

bigNum bigNum::minuxHelper(const bigNum& n) const
{
    bigNum c;
    const bigNum *bigger, *smaller;
    int g = 0, b, s;
    if (*this < n)
    {
        bigger = &n;
        smaller = this;
        c.symbol = false;
    }
    else
    {
        bigger = this;
        smaller = &n;
        c.symbol = true;
    }
    for (int i = 0; i < bigger->length; ++i)
    {
        b = bigger->data[i];
        s = smaller->data[i];
        c.data[i] = (b-s-g) >= 0 ? (b-s-g):(b-s-g+10);
        g = (b-s-g) >= 0 ? 0 : 1;
    }
    c.length = bigger->length;
    c.clean();
    return c;
}

bigNum bigNum::operator-=(const bigNum& n)
{
    *this = *this - n;
    return *this;
}

bigNum bigNum::operator*(const bigNum& n) const
{
    bigNum c;
    c.length = this->length + n.length;
    for (int i = 0; i < this->length; ++i)
        for (int j = 0; j < n.length; ++j)
            c.data[i+j] += this->data[i] * n.data[j];

    for (int i = 0; i < c.length - 1; ++i)
    {
        c.data[i+1] += c.data[i] / 10;
        c.data[i] = c.data[i] % 10;
    }
    c.clean();
    c.symbol = !(this->symbol ^ n.symbol);
    return c;
}

bigNum bigNum::operator*=(const bigNum& n)
{
    *this = *this * n;
    return *this;
}

bigNum bigNum::operator/(const bigNum& n) const
{
    bigNum c, tmp;
    int diff = this->length - n.length;
    if (*this < n)
        return (c = 0);
    tmp = *this;
    for (int i = diff; i >= 0; --i)
    {
        while (tmp >= n * pow(10, i))
        {
            tmp -= n * pow(10, i);
            c.data[i]++;
        }
    }
    c.length = this->length;
    c.clean();
    c.symbol = !(this->symbol ^ n.symbol);
    return c;
}

bigNum bigNum::operator/=(const bigNum& n)
{
    *this = *this / n;
    return *this;
}

bigNum bigNum::operator=(const char* num)
{
    length = strlen(num);
    int t = length;
    if (num[0] == '-')
    {
        symbol = false;
        t--;
    }
    else
        symbol = true;
    for(int i = 0; i < t; i++) data[i] = num[length-i-1] - '0';
    return *this;
}

bigNum bigNum::operator=(int num)
{
    char s[10000];
    sprintf(s, "%d", num);
    *this = s;
    return *this;
}

bool bigNum::operator<(const bigNum& n) const
{
    if (this->symbol == true)
    {
        if (n.symbol == false)
            return false;
        else if (n.symbol == true)
            return lessHelper(n);
    }
    else if (this->symbol == false)
    {
        if (n.symbol == false)
            return (!lessHelper(n));
        else if (n.symbol == true)
            return true;        
    }
}

bool bigNum::lessHelper(const bigNum& n) const
{
    if (this->length > n.length)
        return false;
    else if (this->length < n.length)
        return true;
    else
    {
        int l = this->length - 1;
        while (this->data[l] >= n.data[l] && l >= 0)
            l--;
        if (l < 0)
            return false;
        else
            return true;
    }
}

bool bigNum::operator>(const bigNum& n) const
{
    return n < (*this);
}

bool bigNum::operator==(const bigNum& n) const
{
    return !((*this) > n) && !((*this) < n);
}

bool bigNum::operator<=(const bigNum& n) const
{
    return ((*this) < n) || ((*this) == n);
}

bool bigNum::operator>=(const bigNum& n) const
{
    return ((*this) > n) || ((*this) == n);
}

bool bigNum::operator!=(const bigNum& n) const
{
    return !((*this) == n);
}

void bigNum::clean()
{
    while(length > 1 && !data[length-1])
        length--;
}


std::istream& operator>>(std::istream &in, bigNum &n)
{
    std::string s;
    in >> s;
    n = s.c_str();
    return in;
}

std::ostream& operator<<(std::ostream &out, const bigNum &n)
{
    out << n.str();
    return out;
}