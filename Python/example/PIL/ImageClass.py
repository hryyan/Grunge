#! -*- coding:utf-8 -*-
from PIL import Image

# open and show a pic
def openAndShowPic():
    img = Image.open("i000qa-fn.bmp")
    print img.format, img.size, img.mode
    img.show()

# reading and writing image
def readingAndWritingImage():
    img = Image.open("i000qa-fn.bmp")
    img.save("i000qa-fn.jpg")

# create JPEG thumbnails
def createJpegThumbnails():
    img = Image.open("i000qa-fn.bmp")
    img.thumbnail((128, 128))
    img.save("i000qa-fn-thumbnail.jpg")
    img.show()

# cutting, pasting and merging images
def cutPasteMergeImage():
    img = Image.open("i000qa-fn.bmp")
    box = (100, 100, 400, 400)
    region = img.crop(box)
    # region.show()

    region = region.transpose(Image.ROTATE_180)
    img.paste(region, box)
    img.show()

# roll an image
def roll(delta = 140):
    "roll an image sideways"
    img = Image.open("i000qa-fn.bmp")

    xsize, ysize = img.size

    delta = delta % xsize
    if delta == 0:  return img

    part1 = img.crop((0, 0, delta, ysize))
    part2 = img.crop((delta, 0, xsize, ysize))
    img.paste(part2, (0, 0, xsize-delta, ysize))
    img.paste(part1, (xsize-delta, 0, xsize, ysize))

    img.show()

def splitAndMergingBands():
    img = Image.open("i000qa-fn-color.jpg")
    
    r, g, b = img.split()

    # 当这样显示的时候，RGB分量会被认为是灰度值
    # r.show()
    # g.show()
    # b.show()
    i = Image.merge("RGB", (r, g, b))
    i.show()

def geometricalTransforms():
    img = Image.open("i000qa-fn.jpg")

    img = img.resize((320, 240))
    img = img.rotate(45)
    img.show()

def colorTransforms():
    img = Image.open("i000qa-fn-color.jpg")
    img = img.convert("L")
    img.show()

# Image Enhancement
def applyFilter():
    from PIL import ImageFilter
    img = Image.open("i000qa-fn.jpg")
    out = img.filter(ImageFilter.DETAIL)

# Point Operations
def pointOperations():
    img = Image.open("i000qa-fn.jpg")
    # 255,255,255 is write
    img = img.point(lambda i : i * 1.2)
    img.show()

# process individual bands
def processIndividualBands():
    img = Image.open("i000qa-fn-color.jpg")
    
    source = img.split()
    R, G, B = 0, 1, 2

    # select regions where red is less than 100
    mask = source[R].point(lambda i : i < 100 and 255)
    
    # process the green band
    out = source[G].point(lambda i : i * 0.7)

    # paste the processed band back, but only where red less than 100
    source[G].paste(out, None, mask)

    # build a new multiband image
    img = Image.merge(img.mode, source)

    img.show()

# Enhancing images
def enhancingImage():
    from PIL import ImageEnhance
    img = Image.open("i000qa-fn.jpg")

    enh = ImageEnhance.Contrast(img)
    enh.enhance(1.3).show("30% more contrast")

# Postscript printing
def postscriptPrinting():
    img = Image.open("i000qa-fn.jpg")

    from PIL import PSDraw
    title = "lenaaaaaaaaaaa"
    box = (1*72, 2*72, 3*72, 5*72) #in points

    ps = PSDraw.PSDraw()
    ps.begin_document(title)

    # draw the image (75 dpi)
    ps.image(box, img, 75)
    ps.rectangle(box)

    # draw centered title
    ps.setfont("HelveticalNarrow-Bold", 36)
    ps.text((0, 0), title)

    ps.end_document()
    img.show()

if __name__ == '__main__':
    postscriptPrinting()