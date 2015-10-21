#! /usr/bin/env python

from subprocess import *

#get pid
proc = './hashtable --get 500 --count 1000 '
#call('./out & pid = $!', shell=True)
#call(proc, shell=True)
record = 'sudo ../linux-3.19/tools/perf/perf stat -I 100 -e mem-stores\
     ./hashtable --get 5000 --count 10000 2> perfReport.txt' 
#call('pidof -s ' + proc + '> pid.txt', shell=True)
#call('ps ax | pgrep out > pid.txt', shell=True)
#id = call('./pid pid.txt', shell=True)
#print pid
#pid = '0'

#components of command
#sudo = 'sudo '
#path = '../linux-3.19/tools/perf/'
#cmd = 'perf stat '
#interv = '-I 100 '
#event = '-e mem-stores '
#process = '-p ' + pid
#time = ' sleep 2 '
#redirect = '2> '
#outfile = 'perfReport.txt'
#record = sudo + path + cmd + interv + event + process + time + redirect + outfile
calc = './calculate ' 
calculate = calc + 'perfReport.txt'



#count the events and redirect to a file
call(record, shell=True)

#add the latency
call(calculate, shell=True)
