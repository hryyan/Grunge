# -*- coding:utf-8 -*-

# Derived from built-in types


class int_modify(int):

    """test for derived from int"""

    def __init__(self, x):
        super(int_modify, self).__init__()
        print x

int_modify(5)


# Pass by value
def fun(y):
    y = 1
    print y

y = 2
fun(y)
print y

# class namespace


class MyClass:

    '''A'''
    i = 12345

    def f(self):
        self.u = 111

        print self.i

c = MyClass()
c.f()
print c.i
print c.f
print c.__doc__n

# threading.setprofile & threading.settrace
import threading

a = threading.RLock()
print repr(a)


def fun(a, b, c):
    print "fun"

threading.settrace(fun)


class MyThread(threading.Thread):

    """docstring for MyThread"""

    def __init__(self):
        super(MyThread, self).__init__()

    def run(self):
        print '1'

thread1 = MyThread()
thread1.start()
thread1.join()
print "End"

# RLock.acquire()

import threading

a = threading.RLock()
print a._is_owned()
print a.acquire()
print a._is_owned()
print a.acquire()


class MyThread(threading.Thread):

    """docstring for MyThread"""

    def __init__(self):
        super(MyThread, self).__init__()

    def run(self):
        print a.acquire()

thread1 = MyThread()
thread1.start()
thread1.join()
print "End"

# threading.Event
import threading

a = threading.Event()
print a.wait(timeout=1)
a.set()
print a.wait()

# Class Iterator


class MyClass(object):

    """docstring for MyClass"""

    def __init__(self, data):
        super(MyClass, self).__init__()
        self.data = data
        self.index = len(data)

    def __iter__(self):
        return self

    def next(self):
        if self.index == 0:
            raise StopIteration
        self.index = self.index - 1
        return self.data[self.index]

a = MyClass('asdfgh')
for b in a:
    print b

print iter(a)

# Yield


def reverse(data):
    for index in range(len(data) - 1, -1, -1):
        yield data[index]

for char in reverse('golf'):
    print char

# timeit
from timeit import Timer
print Timer('a, b = 1, 2; a, b = b, a').timeit()

# OS module
import os
print os.name
import sys
print sys.platform
print os.environ
print os.getenv("TMP")

# built-in Function

a = [True, True, True]
print all(a)

a = 127
print bin(a)

a = 55
print bool(a)

a = ['a', 'b', 'c', 'd']
print bytearray(a)


def a():
    print 'abc'
print callable(a)


class MyClass(object):

    """docstring for MyClass"""

    def __init__(self):
        super(MyClass, self).__init__()

    def __call__(self):
        print 'abc'
print callable(MyClass)
b = MyClass()
b()
print callable(b)

b = 45
print chr(b)
c = '-'
print ord(c)

print cmp(1, 3)

print dir()
x = 'x'
print dir(x)


class MyStr(str):

    """docstring for MyStr"""

    def __init__(self):
        super(MyStr, self).__init__()

    def __dir__(self):
        return []
a = MyStr()
print dir(a)

seasons = ['Spring', 'Summer', 'Fall', 'Winter']
print list(enumerate(seasons))


def a(sequence):
    n = 0
    for elem in sequence:
        yield n, elem
        n = n + 1

for x in a(seasons):
    print x

a = file('x.txt', 'w')

# 闭包(closure)
# 一个函数和它的环境变量合在一起，就构成了一个闭包(closure)。


def line_conf():
    b = 15

    def line(x):
        return 2 * x + b
    return line

b = 5
my_line = line_conf()
print my_line(5)


def line_conf(a, b):
    def line(x):
        return a * x + b
    return line

line1 = line_conf(1, 1)
line2 = line_conf(4, 5)
print line1(5), line2(5)


! /usr / bin / env python
-*- coding:
    utf - 8 - *-

# lambda


def lambda_fun(n):
    '''lambda is a function <lambda>

    class 1 object
    '''
    return lambda x: x + n

f = lambda_fun(40)
print f(2)
print help(lambda_fun)

# List
a = [66.25, 333, 33, 1, 1234.5]
print a.count(333), a.count(66.25), a.count('x')
a.insert(2, -1)
a.append(333)
print a
print a.index(333)
a.remove(333)
print a
a.reverse()
print a
a.sort()
print a

# Stack
stack = [3, 4, 5]
stack.append(6)
print stack
stack.pop()
stack.append(7)
print stack
stack.pop()
print stack

# Queue
from collections import deque
queue = deque(["Eric", "Join", "Michael"])
queue.append("Terry")
queue.append("Graham")
print queue.popleft()
print queue.popleft()
print queue

# filter() map() reduce()


def f(x):
    "return a bool"
    return x % 2 != 0 and x % 3 != 0
print filter(f, range(2, 25))


def cube(x):
    "reuturn a value"
    return x * x * x
print map(cube, range(1, 11))

seq = range(8)


def add(x, y):
    "return a value"
    return x + y
print map(add, seq, seq)


def add(x, y):
    "return a value"
    return x + y
print reduce(add, range(1, 11))


def sum(seq):
    def add(x, y):
        return x + y
    return reduce(add, seq, 0)
print sum(range(1, 11))

# List Comprehensions
squares = []
for x in range(10):
    squares.append(x ** 2)
print squares

squares = [x ** 2 for x in range(10)]
print squares

a = [(x, y) for x in [1, 2, 3] for y in [3, 1, 4] if x != y]
print a

vec = [-4, -2, 0, 2, 4]
a = [x * 2 for x in vec]
print 'a =', a

b = [x for x in vec if x >= 0]
print 'b =', b

c = [abs(x) for x in vec]
print 'c =', c

d = [(x, x ** 2) for x in range(6)]
print d

vec = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
e = [num for elem in vec for num in elem]
"""
if use e = [num for num in elem for elem in vec]
then name 'elem' is not defined
"""
print e

from math import pi
f = [str(round(pi, i)) for i in range(1, 6)]
print f

# Nested List Comprehensions
matrix = [
    [1, 2, 3, 4],
    [5, 6, 7, 8],
    [9, 10, 11, 12],
]

print matrix

a = [[row[i] for row in matrix] for i in range(4)]
print a

b = zip(*matrix)
print b

# Sets
basket = ['apple', 'orange', 'apple', 'pear', 'orange', 'banana']
fruit = set(basket)
print fruit

a = set('abracadabra')
b = set('alacazam')
print a  # unique letters in a
print b  # unique letters in b
print a - b  # letters in a but not in b
print a | b  # letters in either a or b
print a & b  # letters in both a and b
print a ^ b  # letters in a or b but not both

# Dictionaries
tel = {'jack': 4098, 'sape': 4139}
for x in tel:
    print x

a = dict([('sape', 4139), ('guido', 4127), ('jack', 4098)])
print a

knights = {'gallahad': 'the pure', 'robin': 'the brave'}
for k, v in knights.iteritems():
    print k, v

# Looping Techniques
for i, v in enumerate(['tic', 'tac', 'toe']):
    print i, v

a = enumerate(['tic', 'tac', 'toe'])
for x in a:
    print x

questions = ['name', 'quest', 'favorite color']
answers = ['lancelot', 'the holy grail', 'bule']
for q, a in zip(questions, answers):
    print 'What is your {0}? It is {1}.'.format(q, a)

for i in reversed(range(1, 10, 2)):
    print i

basket = ['apple', 'orange', 'apple', 'pear', 'orange', 'banana']
for x in sorted(set(basket)):
    print x

# dir()
dir() is used to find out which names a module defines
import fibo
import sys
print 'dir(fibo)', dir(fibo)
print 'dir(sys)', dir(sys)

# dir() lists the names you have defined currently
a = [1, 2, 3, 4, 5]
import fibo
fib = fibo.fib
print 'dir()', dir()

# it lists all types of names: variables, modules, functions, etc.
import __builtin__
print 'dir(__builtin__)', dir(__builtin__)

# Package
from fibo import fibo
fibo.fib(5)

import fibo.fibo
fibo.fibo.fib(5)

# Fancier Output Formatting
str() return the value which readable
repr() return the value which machine read
s = 'Hello, wordld.'
print str(s)
print repr(s)
print str(1.0 / 7.0)
print repr(1.0 / 7.0)

# The repr() of a string adds string quotes and backslashes:
hello = 'hello, world\n'
hellor = repr(hello)
hellos = str(hello)
print hellor
print hellos

# Write a table, rjust
for x in range(1, 11):
    print repr(x).rjust(2), repr(x * x).rjust(3),
    # Note trailing comma on previous line
    print repr(x * x * x).rjust(4)

for x in range(1, 11):
    print '{0:2d} {1:3d} {2:4d}'.format(x, x * x, x * x * x)

# Format
print 'We are the {0} who say "{1}!"'.format('knights', 'Ni')

print 'We are the {1} who say "{0}!"'.format('knights', 'Ni')

print 'This {food} is {adjective}.'.format(food='spam', adjective='absolutely horrible')

'!s'(apply str()) and '!r' (apple repr()) can be used to convert the value before it is formatted

import math
print 'The value of PI is approximately {0}.'.format(math.pi)
print 'The value of PI is approximately {0!r}.'.format(math.pi)

import math
print 'The value of PI is approximately {0:.3f}.'.format(math.pi)

table = {'Sjoerd': 4127, 'Jack': 4098, 'Dcab': 7678}
for name, phone in table.iteritems():
    print '{0:10} ======> {1:10d}'.format(name, phone)

# old string formatting
for tup in table.iteritems():
    print '%10s ======> %10d' % tup

# Reading and Writing Files
f = open('/var/www/main.py', 'r')
print f
f.close()

with open('/var/www/main.py', 'r') as f:
    read_data = f.read()
    print read_data

# 上下文管理器


class Context(object):

    """上下文管理器

__enter__为进入上下文时的函数
__exit__为退出上下文时的函数"""

    def __init__(self):
        super(Context, self).__init__()
        print 'Init the context'

    def __enter__(self):
        print 'Enter the context'

    def __exit__(self, exc_type, exc_val, traceback):
        print 'Exit the context'

with Context() as con:
    print "In the context"

# __dict__可以查看属性


class bird(object):
    feather = True


class chicken(bird):
    fly = False

    def __init__(self, age):
        self.age = age

summer = chicken(2)

print bird.__dict__
print chicken.__dict__
print summer.__dict__

# 特性，将静态的属性变为动态的属性


class bird(object):
    feather = True


class chicken(bird):
    fly = False

    def __init__(self, age):
        super(chicken, self).__init__()
        self.age = age

    def getAdult(self):
        if self.age > 1.0:
            return True
        else:
            return False
    adult = property(getAdult)

summer = chicken(2)

print summer.adult
summer.age = 0.5
print summer.adult

# property方法


class MyClass(object):

    """docstring for MyClass"""

    def __init__(self, arg):
        super(MyClass, self).__init__()
        self._arg = arg

    def foo():
        doc = "The foo property."

        def fget(self):
            return self._arg

        def fset(self, value):
            self._arg = value

        def fdel(self):
            del self._arg
        return locals()
    foo = property(**foo())

a = MyClass(2)
print a.foo
a.foo = 3
print a.foo
print a.__dict__
del a.foo
print a.__dict__

# property方法2


class MyClass(object):

    def __init__(self, value):
        super(MyClass, self).__init__()
        self.value = value

    def getVal(self):
        return self.value

    def setVal(self, value):
        self.value = value

    def delVal(self):
        print "Value also deleted"
        del self.value
    va = property(getVal, setVal, delVal, "Value")

x = MyClass(1.1)
print x.va
x.va = 2
print x.va

# __getattr__，使用__getattr__(self, name)来查询即时生成的属性。
# 当我们查询一个属性时，如果通过__dict__方法无法找到该属性，那么python会调用对象的__getattr__方法，来即时生成该属性


class bird(object):
    feather = True


class chicken(bird):
    fly = False
    def __init__(self, age):
        self.age = age

	def __getattr__(self, name):
        if name == 'adult':
            if self.age > 1.0:
                return True
            else:
                return False
        else:
            raise AttributeError(name)

summer = chicken(2)

print (summer.adult)
summer.age = 0.5
print (summer.adult)

# 将方法f转换为c的一个方法，注意，应该还缺少self或者cls参数
from types import MethodType


def f():
    pass


class c(object):

    def __init__(self):
        super(c, self).__init__()

print MethodType(f, None, c)
