root -b -l <<EOS
.L ntp1-miniaod_MC_pileup.C
run("/eos/user/m/malvesga/miniaod/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_3.root", true, 100)
.q
EOS

mv output_cut.root /afs/cern.ch/user/m/malvesga/work/ProtonRecon/TEST/CMSSW_10_6_0/src/workspace/Dilepton_27_10_19/condor/histos_dy_resample/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_3.root

