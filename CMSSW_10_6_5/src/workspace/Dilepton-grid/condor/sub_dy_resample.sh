#!/bin/bash

file=$1
echo "Input file: $file"
echo "Listing input file:"
ls -la $file
echo "Listing current dir:"
ls -la .
pwd

echo 'Running'
root -b -l <<EOS
.L ntp1-miniaod_MC_pileup.C
run("/mnt/hadoop/cms/store/user/malvesga/MC_bkg/$file", "$file", true, 100)
.q
EOS

