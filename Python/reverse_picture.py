import os
from PIL import Image

def roll(filename):
    im = Image.open(filename)
    name = filename[0] + 'r' + filename[1:]

    out = im.transpose(Image.FLIP_LEFT_RIGHT)
    out.save(name, quality = 95)

file_list = [f for f in os.listdir(os.getcwd()) if f.decode('gbk').split('.')[-1] == 'JPG' or f.decode('gbk').split('.')[-1] == 'jpg']

for f in file_list:
    print f
    roll(f)

print len(file_list)