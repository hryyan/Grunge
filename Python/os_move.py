import os, shutil

for i in range(1, 41):
    path = "D:\\kanbox\\Facerecognition\\Database\\att_faces_backup\\" + "s" + str(i)
    des = "D:\\kanbox\\Facerecognition\\Database\\att_faces_test\\" + "s" + str(i)
    os.chdir(path)
    for i in range(4, 6):
        shutil.move(path + "\\" +str(i) + ".pgm", des + "\\" + str(i) + ".pgm")
print 'ok'