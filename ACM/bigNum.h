#include <algorithm>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <string>
#include <iostream>

#define MAXLEN 10000

class bigNum
{
public:
    int data[MAXLEN];
    int length;
    bool symbol;

    bigNum();
    bigNum(const char*);
    bigNum(int);
    ~bigNum();

    bigNum operator+(const bigNum& n) const;
    bigNum operator-(const bigNum& n) const;
    bigNum operator*(const bigNum& n) const;
    bigNum operator/(const bigNum& n) const;

    bigNum operator+=(const bigNum& n);
    bigNum operator-=(const bigNum& n);
    bigNum operator*=(const bigNum& n);
    bigNum operator/=(const bigNum& n);

    std::string str() const;

    bigNum operator=(const char* num);
    bigNum operator=(int n);

    bool operator<(const bigNum& n) const;
    bool operator>(const bigNum& n) const;
    bool operator==(const bigNum& n) const;
    bool operator<=(const bigNum& n) const;
    bool operator>=(const bigNum& n) const;
    bool operator!=(const bigNum& n) const;

    bool lessHelper(const bigNum& n) const;
    bigNum plusHelper(const bigNum& n, bool s) const;
    bigNum minuxHelper(const bigNum& n) const;
    void clean();
};

std::istream& operator>>(std::istream &in, bigNum &n);
std::ostream& operator<<(std::ostream &out, const bigNum &n);