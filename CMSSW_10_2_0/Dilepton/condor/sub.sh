#!/bin/tcsh -f

set file=$1

cd /afs/cern.ch/user/m/malvesga/work/ProtonRecon/CMSSW_10_2_0/src/
cmsenv
cd -

cp /eos/cms/store/group/phys_pps/ProtonRecoValidation/Dileptons/2017/$file input.root 
cp /afs/cern.ch/user/m/malvesga/work/ProtonRecon/CMSSW_10_2_0/src/workspace/Dilepton/ntp1.* .

root -b -l <<EOS
.L ntp1.C
run()
.q
EOS

rm  ntp1.* input.root

cp output.root /afs/cern.ch/user/m/malvesga/condor/root/$file 

rm output.root

