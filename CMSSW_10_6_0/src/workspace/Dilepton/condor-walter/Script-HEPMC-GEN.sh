#!/bin/tcsh -f
set filetoanalyse=$1
set ScriptsFolder=/afs/cern.ch/work/w/walterjr/MadGraph-Gen-ZZ-Dim6-Script/

#export SCRAM_ARCH=slc7_amd64_gcc820
#source /cvmfs/cms.cern.ch/cmsset_default.sh
#if [ -r CMSSW_10_6_0_patch1/src ] ; then 
# echo release CMSSW_10_6_0_patch1 already exists
#else
#scram p CMSSW CMSSW_10_6_0_patch1
#fi
#cd CMSSW_10_6_0_patch1/src
#eval `scram runtime -sh`

scram p CMSSW CMSSW_10_6_1

cd CMSSW_10_6_1/src/

eval `/cvmfs/cms.cern.ch/common/scramv1 runtime -csh`
#cd -


cp $ScriptsFolder/*.py .

echo 'copying file'
cp $filetoanalyse/tag_1_pythia8_events.hepmc.gz .

echo 'uncompacting file'
gunzip tag_1_pythia8_events.hepmc.gz

echo 'Runnig EDM Process '
cmsRun HEPMCtoEDM.py

echo 'Runnig GEN Process '
cmsRun HEPMCtoEDMtoGEN.py

echo 'moving file  '
cp *.root $filetoanalyse

ls -l
echo 'moved file  '

