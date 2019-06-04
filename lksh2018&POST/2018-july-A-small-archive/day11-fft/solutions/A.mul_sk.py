import sys
import time

def time_stamp(s):
  sys.stderr.write("%.2f: %s\n" % (time.clock(), s));

time_stamp("start")

a = sys.stdin.readline()
b = sys.stdin.readline()

time_stamp("read")

a = int(a)
b = int(b)

time_stamp("convert")

c = a * b

time_stamp("mul")

c = str(c)

time_stamp("convert")

print(c)

time_stamp("finish")
