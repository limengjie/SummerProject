#!/bin/bash - 
#=============================================================================
# Non-Volatile Memory Emulator for hashTable Benchmark
# 
#=============================================================================

#### parameters

INTERVAL=100
ENTRIES=5000000
ITERATIONS=5000001
OUTFILE=perfReport.txt
CALCULATOR=calculate


#### functions
#assign the parameters for corresponding benchmarks

call_hashtable ()
{
  #echo call hashtable
  benchmark="hashtable"
  opt0="--get"
  opt1="--count"
}

call_sps () 
{
  #echo call sps
  benchmark="sps"
  opt0="--count"
  opt1="--swaps"
}

call_sps_log () 
{
  #echo call sps_log
  benchmark="sps_log"
  opt0="--count"
  opt1="--swaps"
}

#### selection

valid_opt=0

while [ "$valid_opt" = 0 ]; do
  if [ "$#" = 1 ]; then
    selection=$1
  else
    echo need 2 args
    exit 1
  fi

  case $selection in 
    1 ) 
      call_hashtable
      valid_opt=1
      ;;
    2 )
      call_sps
      valid_opt=1
      ;;
    3 )
      call_sps_log
      valid_opt=1
      ;;
    * ) 
      echo no such benchmark
      echo "Benchmark list:"
      echo "   1.hashtable"
      echo "   2.sps"
      echo "   3.sps_log"
      exit 1
  esac
done




sudo ../linux-3.19/tools/perf/perf stat -I $INTERVAL -e mem-stores\
  ./$benchmark $opt0 $ENTRIES $opt1 $ITERATIONS 2> $OUTFILE 

./$CALCULATOR $OUTFILE



