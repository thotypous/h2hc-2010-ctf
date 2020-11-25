import sys
from pylab import *
a = loadtxt(sys.argv[1])
n,nvars = a.shape
sys.stdout.write('  { "%s", '%sys.argv[1])
for i in range(nvars):
    b = a[:,i]
    sys.stdout.write('{ %.7f, %.7f }, '%(b.mean(), b.std()))
sys.stdout.write('},\n')
