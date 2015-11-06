#!/bin/bash - 
#=============================================================================
# count hardware events 
#=============================================================================

OUTFILE=perfReport.txt
PERFCMD=sudo ../linux-3.19/tools/perf/perf stat -I 100 -e mem-stores\
  ./hashtable --get 5000000 --count 5000001 2>> $OUTFILE

LOOPS=5
INDEX=0
while [ $INDEX -lt $LOOPS ]; do
  $PERFCMD
  INDEX=$((INDEX + 1))
done


