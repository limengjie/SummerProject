#! /usr/bin/env python

from subprocess import *
import matplotlib.pyplot as plt
import numpy


## clean up the cache
call('./clean_cache/cl_cache 2000000', shell=True)

# benchmarks
benchmarks = {'hashtable' : 1, 'sps' : 2, 'sps_log' : 3}
b_num = len(benchmarks)


##build a 2 dimensional list

M = [] #list of mean values
D = [] #list of deviations 
times = 5

for i in range(1, len(benchmarks) + 1):
  L = []
  for j in range(0, times):
    proc = Popen(["./emulator.sh", str(i)], stdout=PIPE)
    for line in proc.stdout.readlines():
      print line.rstrip()
      L.append(float(line.rstrip()))
  #calculate the mean and std dev value
  M.append(numpy.mean(L))
  D.append( numpy.std(L))

print "mean = {}".format(M)  
print "dev  = {}".format(D)  


#draw the graph

opacity = 0.4
bar_width = 0.15


#multiple bars
###generate x coordinates
X = range(1, 2*len(benchmarks), 2)
plt.bar(X, M, yerr=D, color='y')
plt.axis([0, 2*len(benchmarks) + 2, 46, 51])


##single bar
#x = 1
#plt.bar(x, m, yerr=d, color='y')
#plt.axis([0, 4, 46, 51])


plt.ylabel('mean latency')
plt.title('latency')

plt.show()
