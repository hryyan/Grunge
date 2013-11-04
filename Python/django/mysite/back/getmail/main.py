# -*- coding: utf-8 -*-
from urllib2 import Request, urlopen
import re
from locale import str
import datetime

from mythread import myThread

global headers
headers = {
            'Cookie':'S=quotestreamer=hk8J-5Xn0dwZhNMGTDPZRQ; NID=67=m3JCV6UIdnWaQE9kGH1dSOa6Sgf24EFooeWaElMovPo5yJFzG97Vq5TdEXNrSDBSnpsABgj8LGC5Vu05RV01OIKDq7YM-yliqTLd_LzVcfvKy_1nm8ozcvx6JxgfJZg4; GDSESS=ID=6fd590a7ac6f48de:TM=1373795581:C=c:IP=221.12.26.146-:S=APGng0u96LuKQ9FDy6qMX9JdnAQE16VU7w; PREF=ID=4a3d56158d80a473:U=7478adac7064d958:FF=2:LD=zh-CN:NR=100:NW=1:TM=1364455817:LM=1373803219:GM=1:SG=2:S=d_q8vJJM-REAvdjq',
            'User-Agent': 'Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.1 (KHTML, like Gecko) Chrome/21.0.1180.92 Safari/537.1 LBBROWSER'
}

def getmail_mode2(keyword, list_suffix, num):  
    #设置取得链接的正则表达式
    dict_mail = {}
    list_link = []
    dict_re_suffix = {}
    reg_link = r'class="r"><a href="(.+?)"'
    re_link = re.compile(reg_link)

    for suffix in list_suffix:
        reg_mail = r'([\w_\.]+)@' + suffix
        re_mail = re.compile(reg_mail)
        dict_re_suffix[re_mail] = suffix
        print suffix
    
    #取得链接group
    #i为每页的起始链接计数，num为该页所包含的链接计数，q为关键词
    i = int(0)
    num = int(num)
    while num > 0:
        global html
        try:
            urlstr = 'http://www.google.com.hk/search?num=' + str(min(num, 100)) + '&q=' + keyword + generater(list_suffix) + '&start=' + str(i)
            opener = Request(urlstr, headers=headers)
            html = urlopen(opener)
        except:
            print "Google connection error"
            return ("Google connection error", None)
        html_data = html.read()
        data = re_link.finditer(html_data)

        for m in data:
              list_link.append(m.groups()[0])
        num -= 100
        i += 100

    #本地测试开始
    # urlstr = 'file:///C:/Users/vincent/Desktop/test.html'
    # opener = Request(urlstr, headers=headers)
    # html = urlopen(opener)
    # html_data = html.read()
    # print html_data
    # data = re_link.finditer(html_data)

    # for m in data:
    #     list_link.append(m.groups()[0])
    # print list_link
    #本地测试结束

    #计时
    #start_time = datetime.datetime.now()

    threads = []
    for i in range(10):
        t= myThread(list_link, dict_mail, dict_re_suffix)
        threads.append(t)
    for i in range(10):
        threads[i].start()
    for i in range(10):
        threads[i].join()
    
    result = []
    link = []
    for addr in dict_mail.keys():
        a = addr + '@' + dict_mail[addr][1]
        b = dict_mail[addr][0]
        result.append(a)
        link.append(b)
    print result
    print link

    return (result, link)
    #计时
    #end_time = datetime.datetime.now()
    #print end_time-start_time

def getmail_mode1(keyword, list_suffix, num):
    dict_mail = {}
    list_mail = []
    dict_re_suffix = {}

    #对所有后缀匹配正则表达式，并且将其添加到list中
    for suffix in list_suffix:
        reg_mail = r'([\w_\.]+)@<em>' + suffix + '</em>'
        re_mail = re.compile(reg_mail)
        dict_re_suffix[re_mail] = suffix

    #i为每页的起始链接计数，num为该页所包含的链接计数，q为关键词
    #此处循环查找，获得包含指定链接计数的Google页面
    i = 0
    num = int(num)
    while num > 0:
        global html
        global urlstr
        try:
            urlstr = 'http://www.google.com.hk/search?num=' + str(min(num, 100)) + '&q=' + keyword + generater(list_suffix) + '&start=' + str(i)
            # urlstr='file:///C:/Users/vincent/Desktop/test1.html'
            print urlstr
            opener = Request(urlstr, headers=headers)
            html = urlopen(opener)
        except:
            return ["Google connection error"]
        html_data = html.read()
        for em in dict_re_suffix.keys():
            suffix = dict_re_suffix[em]
            data = em.finditer(html_data)
            #利用字典特性去重、排序
            for m in data:
                dict_mail[m.groups()[0]] = (urlstr, suffix)

        num -= 100
        i += 100

    result = []
    link = []
    for addr in dict_mail.keys():
        a = addr + '@' + dict_mail[addr][1]
        b = dict_mail[addr][0]
        result.append(a)
        link.append(b)
    print result
    print link

    return (result, link)

    #获得邮箱地址
    # list_mail = dict_mail.keys()
    
    #将邮箱写入txt中
    # try:
    #     fobj = open('email.txt', 'a')
    # except IOError:
    #         print 'File open error'
    # else:
    #     for em in list_mail:
    #         fobj.write(em + '@' + suffix + '\n')
    #     fobj.close()

def readsuffix(host):
    # try:
    #     #fobj = open('/static/search.txt', 'r')
    #     fobj = open('search.txt', 'r')
    # except IOError:
    #     print 'File open error!'
    # else:
    #     data = fobj.read()
    #     fobj.close()

    #urlstr = 'file:///E:/eclipse/workspace/mysite/getmail/search.txt'
    urlstr = 'http://' + host + '/static/search.txt'
    data = urlopen(urlstr).read()
    print data
    return data

def prosuffix(suffixs):
    list_tmp = suffixs.split(',')
    list_suffix = []
    for em in list_tmp:
        a = em.lstrip('@')
        list_suffix.append(a)
    print list_suffix
    return list_suffix

def generater(list_suffix):
    s = '+%40'
    for em in list_suffix[0:-1]:
        s += em + '+OR+%40'
    s += list_suffix[-1:][0]
    print s
    return s

if __name__ == "__main__":
    #getmail_mode1('支付宝', prosuffix(readsuffix()), 100)
    #getmail_mode2('支付宝', prosuffix(readsuffix()), 50)
    readsuffix()
    #getmail_mode1('gmail.com', readsuffix(), 100)
    #prosuffix('@gmail.com,@163.com')
    #generater(prosuffix(readsuffix()))
    #prosuffix(readsuffix())