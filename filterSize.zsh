#!/bin/bash

dbs=("./db/astral/astral-scopedom-seqres-gd-sel-gs-bib-40-2.06.fa" "./db/astral/astral-scopedom-seqres-gd-sel-gs-bib-95-2.06.fa")
tests=("./scripts/3mb_100_tests.txt" "./scripts/7mb_100_tests.txt")
# filter_sizes=(100 200 300 400 500 600 700 800 900 1000)
folders=("rsf_astral_3mb" "rsf_astral_7mb")
for j in `seq 8 8`; do
  j100=$((j * 100))
  sed -i "7s/.*/#define SIMPLE_FILTER_SIZE $j100/" bloom/SimpleBloomFilter.h
  make
  for i in {0..1}; do
    echo "${dbs[$i]} ${tests[$i]}"
    mkdir -p "results/${folders[$i]}"
    printf -v j000 "%04d" $j100
    echo $j100
    # sleep 1
    # NO DEPTH ONLY
    # mkdir "results/${folders[$i]}/size_$j000"
    ./sbt "${dbs[$i]}" "${tests[$i]}" 100 > "results/${folders[$i]}/no_time_test_size_$j000.txt"
  done
done
