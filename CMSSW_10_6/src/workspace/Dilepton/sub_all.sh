cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017B/output_dataB.root input.root 
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataB_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017C/output_dataC_0.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataC_0_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017C/output_dataC_1.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataC_1_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017C/output_dataC_2.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataC_2_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017C/output_dataC_3.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataC_3_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017C/output_dataC_4.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataC_4_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017C/output_dataC_5.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataC_5_cut.root
rm input.root

cd histos/
hadd output_dataC_cut.root output_dataC_*_cut.root
rm output_dataC_*_.root 
cd -

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017D/output_dataD_0.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataD_0_cut.root
rm input.root
	
cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017D/output_dataD_1.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataD_1_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017D/output_dataD_2.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataD_2_cut.root
rm input.root

cd histos/
hadd output_dataD_cut.root output_dataD_*_cut.root
rm output_dataD_*_.root
cd -

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017E/output_dataE_0.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataE_0_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017E/output_dataE_1.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataE_1_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017E/output_dataE_2.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataE_2_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017E/output_dataE_3.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataE_3_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017E/output_dataE_4.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataE_4_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017E/output_dataE_5.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataE_5_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017E/output_dataE_6.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataE_6_cut.root
rm input.root

cd histos/
hadd output_dataE_cut.root output_dataE_*_cut.root
rm output_dataE_*_.root 
cd -

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017F/output_dataF_0.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataF_0_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017F/output_dataF_1.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataF_1_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017F/output_dataF_2.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataF_2_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017F/output_dataF_3.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataF_3_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017F/output_dataF_4.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataF_4_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017F/output_dataF_5.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataF_5_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017F/output_dataF_6.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataF_6_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017F/output_dataF_7.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataF_7_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017F/output_dataF_8.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataF_8_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017F/output_dataF_9.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dataF_9_cut.root
rm input.root

cd histos/
hadd output_dataF_cut.root output_dataF_*_cut.root
rm output_dataF_*_.root
cd -

cp /eos/user/m/malvesga/miniaod/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_0.root input.root 
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dy_0_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_1.root input.root 
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dy_1_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_2.root input.root 
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dy_2_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_3.root input.root 
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dy_3_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_4.root input.root 
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dy_4_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_5.root input.root 
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dy_5_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_6.root input.root 
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dy_6_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_7.root input.root 
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dy_7_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/output_dy_8.root input.root 
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_dy_8_cut.root
rm input.root

cd histos/
hadd output_dy_cut.root output_dy_*_cut.root
rm output_dy_*_.root
cd -

cp /eos/user/m/malvesga/miniaod/GGToMuMu_Pt-50_Elastic_13TeV-lpair/output_elastic_xangle120.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_elastic_xangle120_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/GGToMuMu_Pt-50_Elastic_13TeV-lpair/output_elastic_xangle130.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_elastic_xangle130_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/GGToMuMu_Pt-50_Elastic_13TeV-lpair/output_elastic_xangle140.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_elastic_xangle140_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/GGToMuMu_Pt-50_Elastic_13TeV-lpair/output_elastic_xangle150.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_elastic_xangle150_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/GGToMuMu_Pt-50_Inel-El_13TeV-lpair/output_inel-el_xangle120.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_inel-el_xangle120_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/GGToMuMu_Pt-50_Inel-El_13TeV-lpair/output_inel-el_xangle130.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_inel-el_xangle130_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/GGToMuMu_Pt-50_Inel-El_13TeV-lpair/output_inel-el_xangle140.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_inel-el_xangle140_cut.root
rm input.root

cp /eos/user/m/malvesga/miniaod/GGToMuMu_Pt-50_Inel-El_13TeV-lpair/output_inel-el_xangle150.root input.root
root -b -l <<EOS
.L ntp1-miniaod.C
run()
.q
EOS
mv output_cut.root histos/output_inel-el_xangle150_cut.root
rm input.root

