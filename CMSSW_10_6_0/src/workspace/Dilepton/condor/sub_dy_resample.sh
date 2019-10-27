#!/bin/tcsh -f

set file=$1

cp /eos/user/m/malvesga/miniaod/$file input.root 
cp /afs/cern.ch/user/m/malvesga/work/ProtonRecon/TEST/CMSSW_10_6_0/src/workspace/Dilepton_23_10_19/ntp1* .

root -b -l <<EOS
.L ntp1-miniaod_MC_pileup.C
run(true, 100)
.q
EOS

rm  ntp1* input.root

cp output_cut.root /afs/cern.ch/user/m/malvesga/work/ProtonRecon/TEST/CMSSW_10_6_0/src/workspace/Dilepton_23_10_19/condor/histos_dy_resample/$file

rm output_cut.root 
