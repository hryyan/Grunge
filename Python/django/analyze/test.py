# # -*- coding: utf-8 -*-
# # def generator():
# # 	i = 1
# # 	while True:
# # 		yield i
# # 		i = i + 1

# # from itertools import islice, takewhile

# # def take(n, iterable):
# # 	return list(islice(iterable, n))

# # # print take(5, generator())
# # print list(islice(generator(), 5, 10))
# # print islice(generator(), 5)

# # def primes():
# #     for n in generator():
# #         if not any(i > 1 and i != n and n%i == 0 for i in islice(generator(), n)):
# #             yield n

# # print list(islice(primes(), 10))

# # def primes():
# #     for n in generator():
# #         if not any(p != n and n%p == 0
# #                    for p in takewhile(lambda x: n>x, primes())):
# #             yield n
 
# # print take(2, primes())

# # list(islice((time.sleep(x) for x in xrange(3)), 3))
# # import time
# # a = 'str'
# # b = time.sleep(1)
# # c = time.sleep(2)

# # [a, b, c][0]

# # from itertools import islice
# # print list(islice((time.sleep(x) for x in range(3)), 3))
# # print list(islice(('a' for x in range(3)), 3))

# from xml.sax import *
# class UserDecodeHandler(ContentHandler):
# 	users = None
# 	map = None
# 	temp = ""
# 	currenttag = None
# 	user = None

# 	def startDocument(self):
# 		print "start xml document"

# 	def endDocument(self):
# 		print "end xml document"

# 	def startElement(self, name, attrs):
# 		if name == "users":
# 			self.users = []
# 		elif name == "user":
# 			self.user = {"name":attrs['name']}
# 		self.currenttag = name

# 	def endElement(self, name):
# 		if name == "user":
# 			self.users.append(self.user)
# 		elif name == "description":
# 			self.user.update({"description": self.temp.strip()})
# 			self.temp = ""
# 		self.currenttag = None

# 	def characters(self, content):
# 		print self.temp, content
# 		self.temp += content

# print "=" * 10, "SAX", "=" * 10
# parser = make_parser()
# handler = UserDecodeHandler()
# parser.setContentHandler(handler)
# data = ""
# with open("xml.xml") as file:
# 	data = file.read().strip()
# import StringIO

# parser.parse(StringIO.StringIO(data))

# for item in handler.users:
# 	print "=" * 10
# 	for i in item.items():
# 		key, value = i
# 		print key, value.encode("utf-8")

# class ClassName(object):
# 	"""docstring for ClassName"""
# 	def __init__(self, arg):
# 		super(ClassName, self).__init__()
# 		print arg

# 	@classmethod
# 	def new_instance(cls, arg):
# 		obj = ClassName(arg)
# 		obj.__class__ = ClassName
# 		return obj

# a = ClassName.new_instance('xx')
# print a.__class__

# a = [1]
# b = []
# c = [1, 2]
# a.extend(c)
# a.append(c)
# print a
# print len(a), len(b)

# a = 1
# b = 2
# a = b
# b = 3
# print a, b

# import itertools

# def compat_tee(iterable):
#     """
#     Return two independent iterators from a single iterable.

#     Based on http://www.python.org/doc/2.3.5/lib/itertools-example.html
#     """
#     # Note: Using a dictionary and a list as the default arguments here is
#     # deliberate and safe in this instance.
#     def gen(next, data={}, cnt=[0]):
#         dpop = data.pop
#         for i in itertools.count():
#             if i == cnt[0]:
#             	print 'if: ', i
#                 item = data[i] = next()
#                 print 'item: ', item
#                 cnt[0] += 1
#             else:
#             	print 'else: ', i
#                 item = dpop(i)
#             yield item
#     next = iter(iterable).next
#     return gen(next), gen(next)

# a = 'ABCD'
# b = compat_tee(a)
# print b
# print b[0].next(), b[1].next()
# print b[0].next(), b[1].next()
# print b[0].next()
# print b[1].next()

# def groupby(iterable, keyfunc=None):
#     """
#     Taken from http://docs.python.org/lib/itertools-functions.html
#     """
#     if keyfunc is None:
#         keyfunc = lambda x:x
#     iterable = iter(iterable)
#     l = [iterable.next()]
#     lastkey = keyfunc(l[0])
#     for item in iterable:
#         key = keyfunc(item)
#         if key != lastkey:
#             yield lastkey, l
#             lastkey = key
#             l = [item]
#         else:
#             l.append(item)
#     yield lastkey, l

# a = 'ABCD'

# for x in groupby(a, lambda x: x + '1'):
# 	print x

# a = {}
# print a.get('debug', False)
# import sys
# a = sys.modules['__main__']
# file = getattr(a, '__file__', None)

# import os
# print os.path.splitext(os.path.basename(file))[0]

# print globals().get('__file__'), globals().get('__name__')

# import sys
# print sys.modules.values()

# def p(s):
# 	print s

# a = lambda : p('xoxo')
# a()

import web

urls = ("/", "index")
app = web.application(urls, globals())

class index:
	def GET(self):
		return "Hello, world!"

if __name__ == '__main__':
	print app.request().data
