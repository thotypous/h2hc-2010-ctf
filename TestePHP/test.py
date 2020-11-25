from pylab import *
import sys
img = imread(sys.argv[1])
h,w,depth = img.shape
assert(depth == 3)
for x in xrange(w):
    for y in xrange(h):
        r,g,b = img[y][x]
        if r > 1 or g < 10:
            img[y][x] = [255.,255.,255.]
imsave(sys.argv[2], img)
