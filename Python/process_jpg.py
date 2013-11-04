# -*- coding: utf-8 -*-
from __future__ import division
import os
from PIL import Image

def processJPG(name):
	img = Image.open(name)
	width, height = img.size
	print "width: %d, height: %d" % (width, height)
	new_height = (int)(height/width*900)
	print "new width: %d, new height: %d" % (900, new_height)
	new_img = img.resize((900, new_height), Image.ANTIALIAS)
	new_img.save(name, quality = 95)
	print "%s processd" % name

file_list = [f for f in os.listdir(os.getcwd()) if f.decode('gbk').split('.')[-1] == 'JPG' or f.decode('gbk').split('.')[-1] == 'jpg']

for f in file_list:
	print f.decode('gbk')
	processJPG(f)