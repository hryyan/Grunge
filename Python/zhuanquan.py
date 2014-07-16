import time
import sys

print "test"

for x in xrange(1,1000):
    time.sleep(0.1)
    if x % 4 == 0:
        sys.stdout.write("\b\b"),
        print "-",
    elif x % 4 == 1:
        sys.stdout.write("\b\b"),
        print "\\",
    elif x % 4 == 2:
        sys.stdout.write("\b\b"),
        print "|",
    elif x % 4 == 3:
        sys.stdout.write("\b\b"),
        print "/",