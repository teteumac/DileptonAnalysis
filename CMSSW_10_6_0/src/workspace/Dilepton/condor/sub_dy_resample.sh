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
