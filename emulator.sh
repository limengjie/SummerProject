#!/bin/bash - 
#=============================================================================
# Non-Volatile Memory Emulator for hashTable Benchmark
# 
#=============================================================================

#### perf command

INTERVAL=100
EVENT=LLC-store-misses
PERF_STAT="sudo ../linux-3.19/tools/perf/perf stat -I $INTERVAL -e $EVENT"
echo $PERF_STAT


#### built-in benchmarks
#assign the parameters for corresponding built-in benchmarks

### parameters
ENTRIES=5000000
ITERATIONS=5000001

call_hashtable ()
{
  #echo call hashtable
  benchmark="./benchmarks/hashtable"
  opt0="--get"
  opt1="--count"
  BENCHMARK_CMD="$benchmark $opt0 $ENTRIES $opt1 $ITERATIONS"
  echo $BENCHMARK_CMD
}

call_hashtable_log ()
{
  #echo call hashtable
  benchmark="./benchmarks/hashtable_log"
  opt0="--get"
  opt1="--count"
  BENCHMARK_CMD="$benchmark $opt0 $ENTRIES $opt1 $ITERATIONS"
}

call_sps () 
{
  #echo call sps
  benchmark="./benchmarks/_sps"
  opt0="--count"
  opt1="--swaps"
  BENCHMARK_CMD="$benchmark $opt0 $ENTRIES $opt1 $ITERATIONS"
}

call_sps_log () 
{
  #echo call sps_log
  benchmark="./benchmarks/sps_log"
  opt0="--count"
  opt1="--swaps"
  BENCHMARK_CMD="$benchmark $opt0 $ENTRIES $opt1 $ITERATIONS"
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
    ### custmized benchmark
    0 )
      echo -n "Enter correct benchmark path and name: "
      read benchmark
      if [ ! -f "$benchmark" ]
      then
        echo "No such file"
        exit 1
      else
        echo -n "Enter the options if it needs: "
        read opt
        BENCHMARK_CMD="$benchmark $opt"
        valid_opt=1
      fi
      ;;
    ### built-in benchmarks
    1 ) 
      call_hashtable
      valid_opt=1
      ;;
    2 )
      call_hashtable_log
      valid_opt=1
      ;;
    3 )
      call_sps
      valid_opt=1
      ;;
    4 )
      call_sps_log
      valid_opt=1
      ;;
    * ) 
      echo no such benchmark
      echo "Benchmarks list:"
      echo "   0.customized benchmark"
      echo "   1.hashtable"
      echo "   2.hashtable_log"
      echo "   3._sps"
      echo "   4.sps_log"
      exit 2
  esac
done


#### collect perf stat and calculate the writing latency for NV-memory

### parameters
OUTFILE=perfReport.txt
CALCULATOR="./calculator/calculator"

#sudo ../linux-3.19/tools/perf/perf stat -I $INTERVAL -e $EVENT\
  #$benchmark $opt0 $ENTRIES $opt1 $ITERATIONS 2> $OUTFILE 

### collection
$PERF_STAT $BENCHMARK_CMD 2> $OUTFILE

### calculation 
$CALCULATOR $OUTFILE



