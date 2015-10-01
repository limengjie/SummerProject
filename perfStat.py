#! /usr/bin/env python

from subprocess import *

path = '../linux-3.19/tools/perf/'
cmd_record = 'perf record -e LLC-store-misses -a sleep 3'
cmd_redirect = 'perf report > perfReport.txt'
cmd_calc = './calculate perfReport.txt'
event = 'sudo '+ path + cmd_record
redirect = 'sudo ' + path + cmd_redirect
calculate = cmd_calc


#record the performance stat
call(event, shell=True)

#redirect the stat to textfile
call(redirect, shell=True)

#add the latency
call(calculate, shell=True)
