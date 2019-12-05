#!/bin/bash

file=$1
echo "Input file: $file"
echo "Listing input file:"
ls -la $file
echo "Listing current dir:"
ls -la .
pwd

#cd /cvmfs/cms.cern.ch/slc7_amd64_gcc700/cms/cmssw/CMSSW_10_6_0/src
#export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
#source $VO_CMS_SW_DIR/cmsset_default.sh
#eval `scram runtime -sh`
#pwd

#if [ -r CMSSW_10_6_0/src ] ; then 
#echo release CMSSW_10_6_0 already exists
#else
#scram p CMSSW CMSSW_10_6_0
#fi
#cd CMSSW_10_6_0/src
#eval `scram runtime -sh`

#scram p CMSSW CMSSW_10_6_0

#cd CMSSW_10_6_0/src/

#eval `scramv1 runtime -sh`

echo 'Running'
root -b -l <<EOS
std::cout << "$file" << std::endl;
TFile* file = TFile::Open("$file", "READ");
file->ls();
file->Close();
.q
EOS

