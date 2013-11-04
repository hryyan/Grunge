# -*- coding: utf-8 -*-
# import sys

# for filename in filter(lambda v : v, map(lambda m: getattr(m, "__file__", None), sys.modules.values())):
# 	if filename.endswith(".pyc") or filename.endswith(".pyo"):
# 		print filename
# 		filename = filename[:-1]
# 		print filename

# print sys.executable

from urllib2 import Request, urlopen
import re

content = open("couplet_input.txt", "r").readlines()
result = open("couplet_output.txt", "r+")
words = [x[:-1] for x in content if x != None]

# print words[0]
for y in words:
	headers = {
	            'Cookie':'S=quotestreamer=hk8J-5Xn0dwZhNMGTDPZRQ; NID=67=m3JCV6UIdnWaQE9kGH1dSOa6Sgf24EFooeWaElMovPo5yJFzG97Vq5TdEXNrSDBSnpsABgj8LGC5Vu05RV01OIKDq7YM-yliqTLd_LzVcfvKy_1nm8ozcvx6JxgfJZg4; GDSESS=ID=6fd590a7ac6f48de:TM=1373795581:C=c:IP=221.12.26.146-:S=APGng0u96LuKQ9FDy6qMX9JdnAQE16VU7w; PREF=ID=4a3d56158d80a473:U=7478adac7064d958:FF=2:LD=zh-CN:NR=100:NW=1:TM=1364455817:LM=1373803219:GM=1:SG=2:S=d_q8vJJM-REAvdjq',
	            #'User-Agent': 'iPad; CPU OS 6_0 like Mac OS X) AppleWebKit/536.26 (KHTML, like Gecko) Mobile/10A403 Safari/7534.48.3'
				'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; rv:22.0) Gecko/20100101 Firefox/22.0'
	}


	urlstr = 'http://chengyu.911cha.com/q_' + y
	global html
	global opener
	try:
		opener = Request(urlstr, headers=headers)
		html = urlopen(opener).read()
	except Exception, e:
		result.write(y)

	re_1 = re.compile(r'/.+?html')
	data = re_1.findall(html)

	fullpath = "http://chengyu.911cha.com" + data[0]
	try:
		opener = Request(fullpath, headers=headers)
		html = urlopen(opener).read()
	except Exception, e:
		result.write(y)

	re_2 = re.compile(r'褒义|中性|贬义')
	data = re_2.findall(html)

	a = ''

	for x in data:
		a = x.encode('utf-8')
		# print a

	if '中性' == a:
		b = u"中性"
	elif '贬义' == a:
		b = u"贬义"
	elif '褒义' == a:
		b = u"褒义"
	else:
		b = u"没有感情色彩"

	y = y.encode('utf-8')
	y += ": " + b + '\n'
	result.write(y)
	# print html