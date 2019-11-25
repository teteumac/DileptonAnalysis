root -b -l <<EOS
.L ntp1-miniaod_data.C
run("/eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017B/output_dataB.root")
.q
EOS
mv output_cut.root histos_data/output_dataB_sigma.root

root -b -l <<EOS
.L ntp1-miniaod_data.C
run("/eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017C_limitRun/output_dataC_0_limitRun.root")
.q
EOS
mv output_cut.root histos_data/output_dataC_0_limitRun_sigma.root

root -b -l <<EOS
.L ntp1-miniaod_data.C
run("/eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017C_limitRun/output_dataC_1_limitRun.root")
.q
EOS
mv output_cut.root histos_data/output_dataC_1_limitRun_sigma.root

root -b -l <<EOS
.L ntp1-miniaod_data.C
run("/eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017C_limitRun/output_dataC_2_limitRun.root")
.q
EOS
mv output_cut.root histos_data/output_dataC_2_limitRun_sigma.root

root -b -l <<EOS
.L ntp1-miniaod_data.C
run("/eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017C_limitRun/output_dataC_3_limitRun.root")
.q
EOS
mv output_cut.root histos_data/output_dataC_3_limitRun_sigma.root

root -b -l <<EOS
.L ntp1-miniaod_data.C
run("/eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017D/output_dataD_0.root")
.q
EOS
mv output_cut.root histos_data/output_dataD_0_sigma.root

root -b -l <<EOS
.L ntp1-miniaod_data.C
run("/eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017D/output_dataD_1.root")
.q
EOS
mv output_cut.root histos_data/output_dataD_1_sigma.root

root -b -l <<EOS
.L ntp1-miniaod_data.C
run("/eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017D/output_dataD_2.root")
.q
EOS
mv output_cut.root histos_data/output_dataD_2_sigma.root

root -b -l <<EOS
.L ntp1-miniaod_data.C
run("/eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017E/output_dataE_0.root")
.q
EOS
mv output_cut.root histos_data/output_dataE_0_sigma.root

root -b -l <<EOS
.L ntp1-miniaod_data.C
run("/eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017E/output_dataE_1.root")
.q
EOS
mv output_cut.root histos_data/output_dataE_1_sigma.root

root -b -l <<EOS
.L ntp1-miniaod_data.C
run("/eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017E/output_dataE_2.root")
.q
EOS
mv output_cut.root histos_data/output_dataE_2_sigma.root

root -b -l <<EOS
.L ntp1-miniaod_data.C
run("/eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017E/output_dataE_3.root")
.q
EOS
mv output_cut.root histos_data/output_dataE_3_sigma.root

root -b -l <<EOS
.L ntp1-miniaod_data.C
run("/eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017E/output_dataE_4.root")
.q
EOS
mv output_cut.root histos_data/output_dataE_4_sigma.root

root -b -l <<EOS
.L ntp1-miniaod_data.C
run("/eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017E/output_dataE_5.root")
.q
EOS
mv output_cut.root histos_data/output_dataE_5_sigma.root

root -b -l <<EOS
.L ntp1-miniaod_data.C
run("/eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017E/output_dataE_6.root")
.q
EOS
mv output_cut.root histos_data/output_dataE_6_sigma.root

root -b -l <<EOS
.L ntp1-miniaod_data.C
run("/eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017F_limitRun/output_dataF_0_limitRun.root")
.q
EOS
mv output_cut.root histos_data/output_dataF_0_limitRun_sigma.root

root -b -l <<EOS
.L ntp1-miniaod_data.C
run("/eos/user/m/malvesga/miniaod/DoubleMuon/crab_DoubleMuon_Data_2017F_limitRun/output_dataF_1_limitRun.root")
.q
EOS
mv output_cut.root histos_data/output_dataF_1_limitRun_sigma.root
