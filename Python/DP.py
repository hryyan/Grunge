# -*- coding: utf-8 -*-
# 策略模式

# class Strategy1(object):
# 	"""Strategy1"""
# 	def __init__(self):
# 		super(Strategy1, self).__init__()
# 	@staticmethod
# 	def sta_method():
# 		print 'Strategy1_Static'
# 	@classmethod
# 	def cls_method(cls):
# 		print 'Strategy1!'

# class Strategy2(object):
# 	"""Strategy2"""
# 	def __init__(self):
# 		super(Strategy2, self).__init__()
# 	@staticmethod
# 	def sta_method():
# 		print 'Strategy2_Static'
# 	@classmethod
# 	def cls_method(cls):
# 		print 'Strategy2!'

# class Context(object):
# 	"""Context"""
# 	def __init__(self, strategy):
# 		super(Context, self).__init__()
# 		self.operate = strategy.cls_method
# 		self.st_method = strategy.sta_method

# s1 = Context(Strategy1())
# s2 = Context(Strategy2())

# s1.operate()
# s1.st_method()
# s2.operate()
# s2.st_method()

# pythonic策略模式，策略模式的本质是获取一个函数或者一个打包的对象，但是JAVA不允许函数指针，所以只能使用类来实现
# 而C/C++支持函数指针，所以在C/C++中可以使用函数指针，而在python中，函数是第一类对象，所以更加方便
# Python是动态语言，没有类型之分，所以策略模式和代理模式的界限更加模糊

# def strategy1():
# 	print 'Strategy1!'

# def strategy2():
# 	print 'Strategy2!'

# s1 = strategy1
# s2 = strategy2

# s1()
# s2()

# 代理模式

# class Girl(object):
# 	"""Girl"""
# 	sex = 'female'
# 	def __init__(self):
# 		super(Girl, self).__init__()
# 	def kiss(self):
# 		print 'Kiss!', self.sex
# 	def hug(self):
# 		print 'Hug!', self.sex

# class Boy(object):
# 	"""Boy"""
# 	sex = 'male'
# 	def __init__(self):
# 		super(Boy, self).__init__()
# 	def kiss(self):
# 		print 'Kiss!', self.sex
# 	def hug(self):
# 		print 'Hug!', self.sex

# class Wrap(object):
# 	"""Wrap"""
# 	def __init__(self, girl):
# 		super(Wrap, self).__init__()
# 		self.kiss = girl.kiss
# 		self.hug = girl.hug

# girl = Girl()
# wrap_1 = Wrap(girl)
# wrap_1.kiss()
# wrap_1.hug()

# boy = Boy()
# wrap_2 = Wrap(boy)
# wrap_2.kiss()
# wrap_2.hug()

## 单例模式(Singleton Pattern)
# 方法1：新建对象的时候调用__new__方法
# class Singleton(object):
# 	"""docstring for Singleton"""
# 	def __new__(cls, *args, **kw):
# 		if not hasattr(cls, '_instance'):
# 			cls._instance = super(Singleton, cls).__new__(cls, *args, **kw)
# 		return cls._instance

# class MyClass(Singleton):
# 	a = 1

# one = MyClass()
# two = MyClass()

# three = Singleton()

# print one is two


#方法2：本质上是方法1的升级（或者说高级）版
#Singleton2是用type的派生类Singleton2创建的，__init__初始化这个类，若不修改则调用type的__init__方法
#然后使用__call__更改使用Singleton2创建的类的属性，使MyClass3()的时候调用__call__方法。
# class Singleton2(type):
#     def __init__(cls, name, bases, dict):
#         super(Singleton2, cls).__init__(name, bases, dict)
#         cls._instance = None
#     def __call__(cls, *args, **kw):
#         if cls._instance is None:
#             cls._instance = super(Singleton2, cls).__call__(*args, **kw)
#         return cls._instance

# class MyClass3(object):
#     __metaclass__ = Singleton2

# one = MyClass3()
# two = MyClass3()

# print one is two

#方法3：是方法2的升级版
#使用装饰器。这个装饰器接收类作为参数，并且返回函数名
#当使用MyClass4()时，则如同调用_singleton函数

# def singleton(cls, *args, **kw):
# 	instance = {}
# 	def _singleton():
# 		if cls not in instance:
# 			instance[cls] = cls(*args, **kw)
# 		return instance[cls]
# 	return _singleton

# @singleton
# class MyClass4(object):
# 	"""docstring for MyClass4"""
# 	def __init__(self):
# 		pass

# one = MyClass4()
# two = MyClass4()

# print one is two

## 多例模式(Multition Pattern)

#装饰器
# import random
# def multition(cls, *args, **kw):
# 	instances = {}
# 	instances[cls] = []
# 	def _multition():
# 		if len(instances[cls]) < 2:
# 			instance = cls(*args, **kw)
# 			instances[cls].append(instance)
# 			print "Create instance", cls, len(instances[cls]) - 1
# 		else:
# 			num = random.randint(0, 1)
# 			instance = instances[cls][num]
# 			print "Return instance", cls, num
# 		return instance
# 	return _multition

# @multition
# class MyClass(object):
# 	"""docstring for MyClass"""
# 	def __init__(self):
# 		pass

# @multition
# class MyClass2(object):
# 	"""docstring for MyClass2"""
# 	def __init__(self):
# 		pass

# for x in range(10):
# 	a = MyClass()
# for x in range(10):
# 	b = MyClass2()

