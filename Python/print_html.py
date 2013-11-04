# -*- coding: utf-8 -*-
from urllib2 import Request, urlopen
headers = {
            'Cookie':'S=quotestreamer=hk8J-5Xn0dwZhNMGTDPZRQ; NID=67=m3JCV6UIdnWaQE9kGH1dSOa6Sgf24EFooeWaElMovPo5yJFzG97Vq5TdEXNrSDBSnpsABgj8LGC5Vu05RV01OIKDq7YM-yliqTLd_LzVcfvKy_1nm8ozcvx6JxgfJZg4; GDSESS=ID=6fd590a7ac6f48de:TM=1373795581:C=c:IP=221.12.26.146-:S=APGng0u96LuKQ9FDy6qMX9JdnAQE16VU7w; PREF=ID=4a3d56158d80a473:U=7478adac7064d958:FF=2:LD=zh-CN:NR=100:NW=1:TM=1364455817:LM=1373803219:GM=1:SG=2:S=d_q8vJJM-REAvdjq',
            #'User-Agent': 'iPad; CPU OS 6_0 like Mac OS X) AppleWebKit/536.26 (KHTML, like Gecko) Mobile/10A403 Safari/7534.48.3'
			'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; rv:22.0) Gecko/20100101 Firefox/22.0'
}
urlstr = 'http://hangzhou.anjuke.com/sale/xihu/p1/#filtersort'
opener = Request(urlstr, headers=headers)
html = urlopen(opener).read()

print html