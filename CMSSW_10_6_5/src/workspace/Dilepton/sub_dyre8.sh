root -b -l <<EOS
.L ntp1-miniaod_MC_pileup.C
run("/eos/user/m/malvesga/miniaod/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_8.root", true, 100)
.q
EOS

mv output_cut.root output_dy_8.root

