#!/bin/tcsh -f

set file=$1

scram p CMSSW CMSSW_10_6_5
cd CMSSW_10_6_5/src/
eval `/cvmfs/cms.cern.ch/common/scramv1 runtime -csh`

cp /afs/cern.ch/user/m/malvesga/work/ProtonRecon/TEST/CMSSW_10_6_5/src/workspace/Dilepton_15_11_19/ntp1* .

echo  'running'
root -b -l <<EOS
.L ntp1-miniaod_MC_pileup.C
run("/eos/user/m/malvesga/miniaod/$file", true, 100)
.q
EOS

rm  ntp1* 

echo 'moving file'
cp output_cut.root /afs/cern.ch/user/m/malvesga/work/ProtonRecon/TEST/CMSSW_10_6_5/src/workspace/Dilepton_15_11_19/condor/histos_dy_resample/$file

rm output_cut.root 
