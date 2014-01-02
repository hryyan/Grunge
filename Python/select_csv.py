#! -*- coding: utf-8 -*-
import csv

rf = open('muct76.csv', 'rb')
reader = csv.reader(rf)
reader.next()  # 过滤第一行
wf = open('muct76_test.csv', 'wb')
writer = csv.writer(wf)

for x in xrange(1,2000):
    try:
        x = reader.next()
        writer.writerow(x)
        for x in xrange(1,5):
            reader.next()
    except Exception, e:
        pass