# -*- coding: utf-8 -*-
import threading
from urllib2 import urlopen
import re
#mylock用于为输入加锁
#otherlock用于为输出枷锁
mylock = threading.RLock()
otherlock = threading.RLock()
num = 0

class myThread(threading.Thread):
    #为thread设定输入
    def __init__(self, list_link, dict_mail, dict_re_suffix):
        threading.Thread.__init__(self)
        self.data = list_link
        self.dict_mail = dict_mail
        self.dict_re_suffix = dict_re_suffix

    def run(self):
        global num
        global html_data
        data = []
        while True:
            #输入临界区开始
            mylock.acquire()
            if num == len(self.data):
                mylock.release()
                break
            link = self.data[num]
            num += 1
            mylock.release()
            #输入临界区结束
            
            try:
                html_data = urlopen(link, timeout=0.5).read()
            except:
                print "Link timeout:  " + link

            dict_tmp = {}
            for em in self.dict_re_suffix.keys():
                suffix = self.dict_re_suffix[em]
                data = em.finditer(html_data)
                
                for m in data:
                    dict_tmp[m.groups()[0]] = (link, suffix)
            
            #输出临界区开始
            otherlock.acquire()
            self.dict_mail.update(dict_tmp)
            otherlock.release()
            #输出临界区结束

if __name__ == '__main__':
    test('gmail.com')