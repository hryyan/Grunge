#include <iostream>
using namespace std;
 
class Example
{
public:
    Example();
    ~Example();

    int f;
};

//在Example的构造函数中，f(0)将被转换为f = int(0)，结果为0。
Example::Example()
    : f(0)
{}

int main()
{
    Example* a = new Example();
    cout << a->f << endl;
    return 0;
}

//---------------------下一个例子-------------------------

class Example2
{
public:
    Example2();
    ~Example2();

    int f[100];
};

//尝试将{1, 2, 3}初始化给f数组，但是这是失败的，因为int*是一个指针，而指针没有这样的构造方法。
Example2::Example2()
    : f({1, 2, 3})
{}

int main()
{
    Example2* a = new Example2();
    cout << a->f[0] << endl;
    return 0;
}

//-------------------一个解决办法--------------------------------

class Example3
{
public:
    Example3();
    ~Example3();

    int* f;
};

int a[100] = {1, 2, 3};

Example3::Example3()
    : f(a)//指针的复制构造函数
{
}

int main()
{
    Example3* a = new Example3();
    cout << a->f[0] << endl
    return 0;
}

//-----------------------更好的解决方法-------------------------------

class Example4
{
public:
    Example4();
    ~Example4();

    int* g;
};

Example4::Example4()
{
    int a[100] = {1, 2, 3};
    g = a;//数组不是左值，而指针是。这其中的区别有点晦涩
}

int main()
{
    Example4* a = new Example4();
    cout << a->g[0] << endl;
    return 0;
}