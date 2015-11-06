#!/bin/bash - 
#=============================================================================
# Non-Volatile Memory Emulator for hashTable Benchmark
# 
#=============================================================================

INTERVAL=100
ENTRIES=500000
ITERATIONS=500001
OUTFILE=perfReport.txt

#mark start time
date +%s%N
#bash -c 'TIMEFORMAT=%3R; time date +%s'

sudo ../linux-3.19/tools/perf/perf stat -I $INTERVAL -e mem-stores\
  ./hashtable --get $ENTRIES --count $ITERATIONS 2> $OUTFILE 

#mark finish time
date +%s%N
#date

./calculate $OUTFILE



