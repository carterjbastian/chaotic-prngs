#!/bin/bash
PATH_OUT="./output/"
PATH_LOGS="./testlogs/"
EXT_LOGS=".log"

TEST_IDS="0
1
2
3
4
5
6
7
8
9
10
11
12
13
15
16
17
100
101
102
200
201
202"

TEST_IDS2="204
205
206
207
208
209"

# Build
make clean; make

# Generate the files
for id in `seq 0 11`; do
  echo "generating for map with ID $id "
  echo -e "\nPerformance Results for Map with ID $id :" >> ./performance.log
  { time ./RunPRNG $id ; } 2>> ./performance.log
done

FILES=`ls ./output/`

echo "Finished Generating all PRNG Sample Files"
echo "Starting dieharder tests"

# Do the smaller tests
for file in $FILES
do
  output=$PATH_OUT$file
  logfile=$PATH_LOGS$file$EXT_LOGS

  echo "Starting diharder tests on $output"
  for tid in $TEST_IDS
  do
    echo "Starting test number $tid on file $file "
    dieharder -d $tid -g 202 -f $output >> $logfile
  done
done

# Do the larger tests
echo "======================================================"
echo "Done with all of the basic tests"
echo "======================================================"
for tid in $TEST_IDS2
do
  for file in $FILES
  do
    output=$PATH_OUT$file
    logfile=$PATH_LOGS$file$EXT_LOGS

    echo "Starting test number $tid on file $file"
    dieharder -d $tid -g 202 -f $output >> $logfile

  done
done

echo "Done with all testing of RNGs"
