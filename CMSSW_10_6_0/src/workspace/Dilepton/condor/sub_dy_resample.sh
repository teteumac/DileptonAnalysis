#!/bin/tcsh -f

set file=$1

cp /eos/user/m/malvesga/miniaod/$file input.root 
root -b -l <<EOS
.L ntp1-miniaod_MC_pileup.C
run(true, 100)
.q
EOS
mv output_cut.root histos_dy_resample/$file
rm input.root

cp /eos/user/m/malvesga/miniaod/GGToMuMu_Pt-50_Elastic_13TeV-lpair/output_elastic_xangle130.root input.root
root -b -l <<EOS
.L ntp1-miniaod_MC.C
run()
.q
EOS
mv output_cut.root histos_MC/output_elastic_xangle130_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/GGToMuMu_Pt-50_Inel-El_13TeV-lpair/output_inel-el_xangle130.root input.root
root -b -l <<EOS
.L ntp1-miniaod_MC.C
run()
.q
EOS
mv output_cut.root histos_MC/output_inel-el_xangle130_cut.root
rm input.root
