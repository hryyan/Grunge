#! -*- coding:utf-8 -*-
from PIL import Image
import os

def grayscale(image_path):
    image_file = Image.open(image_path)
    image_file = image_file.convert('L')
    image_file.save(image_path)

file_list = [f for f in os.listdir(os.getcwd()) if f.decode('gbk').split('.')[-1] == 'JPG' or f.decode('gbk').split('.')[-1] == 'jpg']

for f in file_list:
    print f
    grayscale(f)