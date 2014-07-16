#! -*- coding: utf-8 -*-

f1 = open('POJ3126.output1')
f2 = open('POJ3126.output2')
f1_lines = f1.readlines()
f2_lines = f2.readlines()

for x in range(len(f1_lines)):
    if not f1_lines[x] == f2_lines[x]:
        print '%d: %s %s' % (x+1, f1_lines[x][0], f2_lines[x][0])