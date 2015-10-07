#! /usr/bin/env python

from subprocess import *

#components of command
sudo = 'sudo '
path = '../linux-3.19/tools/perf/'
cmd = 'perf stat '
interv = '-I 100 '
event = '-e mem-stores '
time = '-a sleep 2 '
redirect = '2> '
outfile = 'perfReport.txt'
record = sudo + path + cmd + interv + event + time + redirect + outfile
calc = './calculate ' 
calculate = calc + outfile



#count the events and redirect to a file
call(record, shell=True)

#add the latency
#call(calculate, shell=True)
