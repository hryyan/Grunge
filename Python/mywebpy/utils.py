#! -*- coding: utf-8 -*-

from threading import local as threadlocal

__all__ = [
    "group", "ThreadDict", "threaddict"
]

def group(seq, size):
    def take(seq, n):
        for i in range(n):
            yield seq.next()

    if not hasattr(seq, 'next'):
        seq = iter(seq)
    while True:
        x = list(take(seq, size))
        if x:
            yield x
        else:
            break

class ThreadDict(threadlocal):
    """
    线程私有数据
    """

    _instance = set()

    def __init__(self):
        ThreadDict._instance.add(self)

    def __del__(self):
        ThreadDict._instance.remove(self)

    def __hash__(self):
        return id(self)

    @staticmethod
    def clear_all(self):
        """
        清除所有ThreadDict实例
        """
        for t in list(ThreadDict._instance):
            t.clear()

    def __getitem__(self, key):
        return self.__dict__[key]

    def __setitem__(self, key, value):
        self.__dict__[key] = value

    def __delitem__(self, key):
        del self.__dict__[key]

    def __contains__(self, key):
        return key in self.__dict__

    has_key = __contains__

    def clear(self):
        self.__dict__.clear()

    def copy(self):
        return self.__dict__.copy()

    def get(self, key, default=None):
        return self.__dict__.get(key, default)

    def items(self):
        return self.__dict__.items()

    def iteritems(self):
        return self.__dict__.iteritems()

    def keys(self):
        return self.__dict__.keys()

    def iterkeys(self):
        return self.__dict__.iterkeys()

    iter = iterkeys

    def values(self):
        return self.__dict__.values()

    def itervalues(self):
        return self.__dict__.itervalues()

    def pop(self, key, *args):
        return self.__dict__.pop(key, *args)

    def popitem(self):
        return self.__dict__.popitem()

    def setdefault(self, key, default=None):
        return self.__dict__.setdefault(key, default)

    def update(self, *args, **kwargs):
        self.__dict__.update(*args, **kwargs)

    def __repr__(self):
        return '<ThreadedDict %r>' % self.__dict__

    __str__ = __repr__
    
threadeddict = ThreadDict