#define ntp1_cxx
#include "ntp1.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TSystem.h>
#include <TROOT.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TSpline.h>
#include <math.h>
#include "DataFormats/Math/interface/deltaPhi.h"

#define PI 3.14159265358979323846

#include <iostream>
#include <vector>
#include <set>
using namespace std;


void ntp1::Loop()
{
//   In a ROOT session, you can do:
//      root> .L ntp1.C
//      root> ntp1 t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch


	TH1D *PrimVertex_ndof = new TH1D("PrimVertex_ndof", "PrimVertexCand_ndof", 200, 0, 200);
	TH1D *PrimVertex_chi2 = new TH1D("PrimVertex_chi2", "PrimVertexCand_chi2", 100, 0, 200);
	TH1D *mumu_mass = new TH1D("mumu_mass", "#mu^{+}#mu^{-} Mass", 20, 0, 600);
	TH1D *mumu_pt = new TH1D("mumu_pt", "#mu^{+}#mu^{-} p_{T}", 20, 0, 25);
	TH1D *mumu_y = new TH1D("mumu_y", "#mu^{+}#mu^{-} y", 20, -3, 3);
	/*	
	TH1D *n_fromPV = new TH1D("n_fromPV", "n from PV", 100, 0, 100);
	TH1D *n_fromPV_2 = new TH1D("n_fromPV_2", "n from PV 2", 100, 0, 100);
	TH1D *n_fromPV_3 = new TH1D("n_fromPV_3", "n from PV 3", 100, 0, 100);
	TH1D *n_ext_fromPV = new TH1D("n_ext_fromPV", "n extra from PV", 100, 0, 100);
	TH1D *n_ext_fromPV_2 = new TH1D("n_ext_fromPV_2", "n extra from PV 2", 100, 0, 100);
	TH1D *n_ext_fromPV_3 = new TH1D("n_ext_fromPV_3", "n extra from PV 3", 100, 0, 100);
	TH1D *n_fromPV_dz02 = new TH1D("n_fromPV_dz02", "n from PV with dz < 0.2", 100, 0, 100);
	TH1D *n_fromPV_2_dz02 = new TH1D("n_fromPV_2_dz02", "n from PV 2 with dz < 0.2", 100, 0, 100);
	TH1D *n_fromPV_3_dz02 = new TH1D("n_fromPV_3_dz02", "n from PV 3 with dz < 0.2", 100, 0, 100);
	TH1D *n_ext_fromPV_dz02 = new TH1D("n_ext_fromPV_dz02", "n extra from PV with dz < 0.2", 100, 0, 100);
	TH1D *n_ext_fromPV_2_dz02 = new TH1D("n_ext_fromPV_2_dz02", "n extra from PV 2 with dz < 0.2", 100, 0, 100);
	TH1D *n_ext_fromPV_3_dz02 = new TH1D("n_ext_fromPV_3_dz02", "n extra from PV 3 with dz < 0.2", 100, 0, 100);
	TH1D *n_fromPV_dz01 = new TH1D("n_fromPV_dz01", "n from PV with dz < 0.1", 100, 0, 100);
	TH1D *n_fromPV_2_dz01 = new TH1D("n_fromPV_2_dz01", "n from PV 2 with dz < 0.1", 100, 0, 100);
	TH1D *n_fromPV_3_dz01 = new TH1D("n_fromPV_3_dz01", "n from PV 3 with dz < 0.1", 100, 0, 100);
	TH1D *n_ext_fromPV_dz01 = new TH1D("n_ext_fromPV_dz01", "n extra from PV with dz < 0.1", 100, 0, 100);
	TH1D *n_ext_fromPV_2_dz01 = new TH1D("n_ext_fromPV_2_dz01", "n extra from PV 2 with dz < 0.1", 100, 0, 100);
	TH1D *n_ext_fromPV_3_dz01 = new TH1D("n_ext_fromPV_3_dz01", "n extra from PV 3 with dz < 0.1", 100, 0, 100);
	TH1D *mu1_z_mu2_z = new TH1D("mu1_z_mu2_z", "#mu^{+} z - #mu^{-} z", 1000, -.02, .02);
	TH1D *mu1_z_primvertex_z = new TH1D("mu1_z_primevertex_z", "#mu 1 z - primary vertex z", 1000, -.02, .02);
	TH1D *mu2_z_primvertex_z = new TH1D("mu2_z_primevertex_z", "#mu 2 z - primary vertex z", 1000, -.02, .02);
	*/
	TH1D *proton_xi_left_rp3 = new TH1D("proton_xi_left_rp3", "#xi Proton Left - RP 3", 20, 0, 0.16);
	TH1D *proton_resolution_left_gen_rp3 = new TH1D("proton_resolution_left_gen_rp3", "#xi Left gen Proton Resolution - RP 3", 20, -.8, .8);
	TH1D *proton_resolution_left_reco_rp3 = new TH1D("proton_resolution_left_reco_rp3", "#xi Left reco Proton Resolution - RP 3", 20, -.8, .8);
	TH1D *pair_xi_left_rp3 = new TH1D("pair_xi_left_rp3", "#xi Pair Left - RP 3", 20, 0, 0.16);
	TH2D *xi_left_reco_rp3 = new TH2D("xi_left_reco_rp3", "#xi Left Correlation - RP 3", 20, 0, 0.16, 20, 0, 0.16); 
	TH1D *proton_resolution_left_rp3_1 = new TH1D("proton_resolution_left_rp3_1", "#xi Proton Left Proton Resolution - RP 3", 20, -.05, .05);
	TH1D *proton_resolution_left_rp3_2 = new TH1D("proton_resolution_left_rp3_2", "#xi Proton Left Proton Resolution - RP 3", 20, -.05, .05);
	TH1D *proton_resolution_left_rp3_3 = new TH1D("proton_resolution_left_rp3_3", "#xi Proton Left Proton Resolution - RP 3", 20, -.05, .05);
	TH1D *proton_resolution_left_rp3_4 = new TH1D("proton_resolution_left_rp3_4", "#xi Proton Left Proton Resolution - RP 3", 20, -.05, .05);
	TH1D *proton_resolution_left_rp3_5 = new TH1D("proton_resolution_left_rp3_5", "#xi Proton Left Proton Resolution - RP 3", 20, -.05, .05);
	TH1D *proton_resolution_left_rp3_6 = new TH1D("proton_resolution_left_rp3_6", "#xi Proton Left Proton Resolution - RP 3", 20, -.05, .05);
	TH1D *proton_resolution_left_rp3_7 = new TH1D("proton_resolution_left_rp3_7", "#xi Proton Left Proton Resolution - RP 3", 20, -.05, .05);
	TH1D *diff_proton_reco_pair_xi_left_rp3 = new TH1D("diff_proton_reco_pair_xi_left_rp3", "reco (Proton - Pair) #xi Left - RP 3", 10, -1, 1);
	TH1D *ratio_proton_reco_pair_xi_left_rp3 = new TH1D("ratio_proton_reco_pair_xi_left_rp3", "reco (1 - Proton/Pair) #xi Left - RP 3", 10, -20, 3);

	TH1D *proton_xi_left_rp23 = new TH1D("proton_xi_left_rp23", "#xi Proton Left - RP 23", 20, 0, 0.16);
	TH1D *proton_resolution_left_gen_rp23 = new TH1D("proton_resolution_left_gen_rp23", "#xi Left gen Proton Resolution - RP 23", 20, -.8, .8);
	TH1D *proton_resolution_left_reco_rp23 = new TH1D("proton_resolution_left_reco_rp23", "#xi Left reco Proton Resolution - RP 23", 20, -.8, .8);
	TH1D *pair_xi_left_rp23 = new TH1D("pair_xi_left_rp23", "#xi Pair Left - RP 23", 20, 0, 0.16);
	TH2D *xi_left_reco_rp23 = new TH2D("xi_left_reco_rp23", "#xi Left Correlation - RP 23", 20, 0, 0.16, 20, 0, 0.16); 
	TH1D *proton_resolution_left_rp23_1 = new TH1D("proton_resolution_left_rp23_1", "#xi Proton Left Proton Resolution - RP 23", 20, -.05, .05);
	TH1D *proton_resolution_left_rp23_2 = new TH1D("proton_resolution_left_rp23_2", "#xi Proton Left Proton Resolution - RP 23", 20, -.05, .05);
	TH1D *proton_resolution_left_rp23_3 = new TH1D("proton_resolution_left_rp23_3", "#xi Proton Left Proton Resolution - RP 23", 20, -.05, .05);
	TH1D *proton_resolution_left_rp23_4 = new TH1D("proton_resolution_left_rp23_4", "#xi Proton Left Proton Resolution - RP 23", 20, -.05, .05);
	TH1D *proton_resolution_left_rp23_5 = new TH1D("proton_resolution_left_rp23_5", "#xi Proton Left Proton Resolution - RP 23", 20, -.05, .05);
	TH1D *proton_resolution_left_rp23_6 = new TH1D("proton_resolution_left_rp23_6", "#xi Proton Left Proton Resolution - RP 23", 20, -.05, .05);
	TH1D *proton_resolution_left_rp23_7 = new TH1D("proton_resolution_left_rp23_7", "#xi Proton Left Proton Resolution - RP 23", 20, -.05, .05);
	TH1D *diff_proton_reco_pair_xi_left_rp23 = new TH1D("diff_proton_reco_pair_xi_left_rp23", "reco (Proton - Pair) #xi Left - RP 23", 10, -1, 1);
	TH1D *ratio_proton_reco_pair_xi_left_rp23 = new TH1D("ratio_proton_reco_pair_xi_left_rp23", "reco (1 - Proton/Pair) #xi Left - RP 23", 10, -20, 3);

	TH1D *proton_xi_left_single = new TH1D("proton_xi_left_single", "#xi Proton Left - Single RP", 20, 0, 0.16);
	TH1D *proton_resolution_left_gen_single = new TH1D("proton_resolution_left_gen_single", "#xi Left gen Proton Resolution - Single RP", 20, -.8, .8);
	TH1D *proton_resolution_left_reco_single = new TH1D("proton_resolution_left_reco_single", "#xi Left reco Proton Resolution - Single RP", 20, -.8, .8);
	TH1D *pair_xi_left_single = new TH1D("pair_xi_left_single", "#xi Pair Left - Single RP", 20, 0, 0.16);
	TH2D *xi_left_reco_single = new TH2D("xi_left_reco_single", "#xi Left Correlation - Single RP", 20, 0, 0.16, 20, 0, 0.16); 	
	TH2D *xi_left_reco_single_2 = new TH2D("xi_left_reco_single_2", "#xi Left Correlation - Single RP", 20, 0, 0.16, 20, 0, 0.16); 	
	TH1D *proton_resolution_left_single_1 = new TH1D("proton_resolution_left_single_1", "#xi Proton Left Proton Resolution - Single RP", 20, -.05, .05);
	TH1D *proton_resolution_left_single_2 = new TH1D("proton_resolution_left_single_2", "#xi Proton Left Proton Resolution - Single RP", 20, -.05, .05);
	TH1D *proton_resolution_left_single_3 = new TH1D("proton_resolution_left_single_3", "#xi Proton Left Proton Resolution - Single RP", 20, -.05, .05);
	TH1D *proton_resolution_left_single_4 = new TH1D("proton_resolution_left_single_4", "#xi Proton Left Proton Resolution - Single RP", 20, -.05, .05);
	TH1D *proton_resolution_left_single_5 = new TH1D("proton_resolution_left_single_5", "#xi Proton Left Proton Resolution - Single RP", 20, -.05, .05);
	TH1D *proton_resolution_left_single_6 = new TH1D("proton_resolution_left_single_6", "#xi Proton Left Proton Resolution - Single RP", 20, -.05, .05);
	TH1D *proton_resolution_left_single_7 = new TH1D("proton_resolution_left_single_7", "#xi Proton Left Proton Resolution - Single RP", 20, -.05, .05);
	TH1D *diff_proton_reco_pair_xi_left_single = new TH1D("diff_proton_reco_pair_xi_left_single", "reco (Proton - Pair) #xi Left - Single", 10, -1, 1);
	TH1D *ratio_proton_reco_pair_xi_left_single = new TH1D("ratio_proton_reco_pair_xi_left_single", "reco (1 - reco Proton/Pair) #xi Left - Single", 10, -20, 3);

	TH1D *proton_xi_right_rp103 = new TH1D("proton_xi_right_rp103", "#xi Proton Right - RP 103", 20, 0, 0.16);
	TH1D *proton_resolution_right_gen_rp103 = new TH1D("proton_resolution_right_gen_rp103", "#xi Right gen Proton Resolution - RP 103", 20, -.8, .8);
	TH1D *proton_resolution_right_reco_rp103 = new TH1D("proton_resolution_right_reco_rp103", "#xi Right reco Proton Resolution - RP 103", 20, -.8, .8);
	TH1D *pair_xi_right_rp103 = new TH1D("pair_xi_right_rp103", "#xi Pair Right - RP 103", 20, 0, 0.16);
	TH2D *xi_right_reco_rp103 = new TH2D("xi_right_reco_rp103", "#xi Right Correlation - RP 103", 20, 0, 0.16, 20, 0, 0.16); 
	TH1D *proton_resolution_right_rp103_1 = new TH1D("proton_resolution_right_rp103_1", "#xi Proton Right Proton Resolution - RP 103", 20, -.05, .05);
	TH1D *proton_resolution_right_rp103_2 = new TH1D("proton_resolution_right_rp103_2", "#xi Proton Right Proton Resolution - RP 103", 20, -.05, .05);
	TH1D *proton_resolution_right_rp103_3 = new TH1D("proton_resolution_right_rp103_3", "#xi Proton Right Proton Resolution - RP 103", 20, -.05, .05);
	TH1D *proton_resolution_right_rp103_4 = new TH1D("proton_resolution_right_rp103_4", "#xi Proton Right Proton Resolution - RP 103", 20, -.05, .05);
	TH1D *proton_resolution_right_rp103_5 = new TH1D("proton_resolution_right_rp103_5", "#xi Proton Right Proton Resolution - RP 103", 20, -.05, .05);
	TH1D *proton_resolution_right_rp103_6 = new TH1D("proton_resolution_right_rp103_6", "#xi Proton Right Proton Resolution - RP 103", 20, -.05, .05);
	TH1D *proton_resolution_right_rp103_7 = new TH1D("proton_resolution_right_rp103_7", "#xi Proton Right Proton Resolution - RP 103", 20, -.05, .05);
	TH1D *diff_proton_reco_pair_xi_right_rp103 = new TH1D("diff_proton_reco_pair_xi_right_rp103", "reco (Proton - Pair) #xi Right - RP 103", 10, -1, 1);
	TH1D *ratio_proton_reco_pair_xi_right_rp103 = new TH1D("ratio_proton_reco_pair_xi_right_rp103", "reco (1 - Proton/Pair) #xi Right - RP 103", 10, -20, 3);

	TH1D *proton_xi_right_rp123 = new TH1D("proton_xi_right_rp123", "#xi Proton Right - RP 123", 20, 0, 0.16);
	TH1D *proton_resolution_right_gen_rp123 = new TH1D("proton_resolution_right_gen_rp123", "#xi Right gen Proton Resolution - RP 123", 20, -.8, .8);
	TH1D *proton_resolution_right_reco_rp123 = new TH1D("proton_resolution_right_reco_rp123", "#xi Right reco Proton Resolution - RP 123", 20, -.8, .8);
	TH1D *pair_xi_right_rp123 = new TH1D("pair_xi_right_rp123", "#xi Pair Right - RP 123", 20, 0, 0.16);
	TH2D *xi_right_reco_rp123 = new TH2D("xi_right_reco_rp123", "#xi Right Correlation - RP 123", 20, 0, 0.16, 20, 0, 0.16); 
	TH1D *proton_resolution_right_rp123_1 = new TH1D("proton_resolution_right_rp123_1", "#xi Proton Right Proton Resolution - RP 123", 20, -.05, .05);
	TH1D *proton_resolution_right_rp123_2 = new TH1D("proton_resolution_right_rp123_2", "#xi Proton Right Proton Resolution - RP 123", 20, -.05, .05);
	TH1D *proton_resolution_right_rp123_3 = new TH1D("proton_resolution_right_rp123_3", "#xi Proton Right Proton Resolution - RP 123", 20, -.05, .05);
	TH1D *proton_resolution_right_rp123_4 = new TH1D("proton_resolution_right_rp123_4", "#xi Proton Right Proton Resolution - RP 123", 20, -.05, .05);
	TH1D *proton_resolution_right_rp123_5 = new TH1D("proton_resolution_right_rp123_5", "#xi Proton Right Proton Resolution - RP 123", 20, -.05, .05);
	TH1D *proton_resolution_right_rp123_6 = new TH1D("proton_resolution_right_rp123_6", "#xi Proton Right Proton Resolution - RP 123", 20, -.05, .05);
	TH1D *proton_resolution_right_rp123_7 = new TH1D("proton_resolution_right_rp123_7", "#xi Proton Right Proton Resolution - RP 123", 20, -.05, .05);
	TH1D *diff_proton_reco_pair_xi_right_rp123 = new TH1D("diff_proton_reco_pair_xi_right_rp123", "reco (Proton - Pair) #xi Right - RP 123", 10, -1, 1);
	TH1D *ratio_proton_reco_pair_xi_right_rp123 = new TH1D("ratio_proton_reco_pair_xi_right_rp123", "reco (1 - Proton/Pair) #xi Right - RP 123", 10, -20, 3);

	TH1D *proton_xi_right_single = new TH1D("proton_xi_right_single", "#xi Proton Right - Single RP", 20, 0, 0.16);
	TH1D *proton_resolution_right_gen_single = new TH1D("proton_resolution_right_gen_single", "#xi Right gen Proton Resolution - Single RP", 20, -.8, .8);
	TH1D *proton_resolution_right_reco_single = new TH1D("proton_resolution_right_reco_single", "#xi Right reco Proton Resolution - Single RP", 20, -.8, .8);
	TH1D *pair_xi_right_single = new TH1D("pair_xi_right_single", "#xi Pair Right - Single RP", 20, 0, 0.16);
	TH2D *xi_right_reco_single = new TH2D("xi_right_reco_single", "#xi Right Correlation - Single RP", 20, 0, 0.16, 20, 0, 0.16); 	
	TH2D *xi_right_reco_single_2 = new TH2D("xi_right_reco_single_2", "#xi Right Correlation - Single RP", 20, 0, 0.16, 20, 0, 0.16); 	
	TH1D *proton_resolution_right_single_1 = new TH1D("proton_resolution_right_single_1", "#xi Proton Right Proton Resolution - Single RP", 20, -.05, .05);
	TH1D *proton_resolution_right_single_2 = new TH1D("proton_resolution_right_single_2", "#xi Proton Right Proton Resolution - Single RP", 20, -.05, .05);
	TH1D *proton_resolution_right_single_3 = new TH1D("proton_resolution_right_single_3", "#xi Proton Right Proton Resolution - Single RP", 20, -.05, .05);
	TH1D *proton_resolution_right_single_4 = new TH1D("proton_resolution_right_single_4", "#xi Proton Right Proton Resolution - Single RP", 20, -.05, .05);
	TH1D *proton_resolution_right_single_5 = new TH1D("proton_resolution_right_single_5", "#xi Proton Right Proton Resolution - Single RP", 20, -.05, .05);
	TH1D *proton_resolution_right_single_6 = new TH1D("proton_resolution_right_single_6", "#xi Proton Right Proton Resolution - Single RP", 20, -.05, .05);
	TH1D *proton_resolution_right_single_7 = new TH1D("proton_resolution_right_single_7", "#xi Proton Right Proton Resolution - Single RP", 20, -.05, .05);
	TH1D *diff_proton_reco_pair_xi_right_single = new TH1D("diff_proton_reco_pair_xi_right_single", "reco (Proton - Pair) #xi Right - Single", 10, -1, 1);
	TH1D *ratio_proton_reco_pair_xi_right_single = new TH1D("ratio_proton_reco_pair_xi_right_single", "reco (1 - Proton/Pair) #xi Right - Single", 10, -20, 3);

	TH1D *proton_xi_left_multi = new TH1D("proton_xi_left_multi", "#xi Proton Left - Multi RP", 20, 0, 0.16);
	TH1D *proton_resolution_left_gen_multi = new TH1D("proton_resolution_left_gen_multi", "#xi Left gen Proton Resolution - Multi RP", 20, -2, 2);
	TH1D *proton_resolution_left_reco_multi = new TH1D("proton_resolution_left_reco_multi", "#xi Left reco Proton Resolution - Multi RP", 20, -2, 2);
	TH1D *pair_xi_left_multi = new TH1D("pair_xi_left_multi", "#xi Pair Left - Multi RP", 20, 0, 0.16);
	TH2D *xi_left_reco_multi = new TH2D("xi_left_reco_multi", "#xi Left Correlation - Multi RP", 20, 0, 0.16, 20, 0, 0.16); 	
	TH1D *proton_resolution_left_multi_1 = new TH1D("proton_resolution_left_multi_1", "#xi Proton Left Proton Resolution - Multi RP", 20, -.05, .05);
	TH1D *proton_resolution_left_multi_2 = new TH1D("proton_resolution_left_multi_2", "#xi Proton Left Proton Resolution - Multi RP", 20, -.05, .05);
	TH1D *proton_resolution_left_multi_3 = new TH1D("proton_resolution_left_multi_3", "#xi Proton Left Proton Resolution - Multi RP", 20, -.05, .05);
	TH1D *proton_resolution_left_multi_4 = new TH1D("proton_resolution_left_multi_4", "#xi Proton Left Proton Resolution - Multi RP", 20, -.05, .05);
	TH1D *proton_resolution_left_multi_5 = new TH1D("proton_resolution_left_multi_5", "#xi Proton Left Proton Resolution - Multi RP", 20, -.05, .05);
	TH1D *proton_resolution_left_multi_6 = new TH1D("proton_resolution_left_multi_6", "#xi Proton Left Proton Resolution - Multi RP", 20, -.05, .05);
	TH1D *proton_resolution_left_multi_7 = new TH1D("proton_resolution_left_multi_7", "#xi Proton Left Proton Resolution - Multi RP", 20, -.05, .05);
	TH1D *diff_proton_reco_pair_xi_left_multi = new TH1D("diff_proton_reco_pair_xi_left_multi", "reco (Proton - Pair) #xi Left - Multi", 10, -1, 1);
	TH1D *ratio_proton_reco_pair_xi_left_multi = new TH1D("ratio_proton_reco_pair_xi_left_multi", "reco (1 - Proton/Pair) #xi Left - Multi", 10, -20, 3);

	TH1D *proton_xi_right_multi = new TH1D("proton_xi_right_multi", "#xi Proton Right - Multi RP", 20, 0, 0.16);
	TH1D *proton_resolution_right_gen_multi = new TH1D("proton_resolution_right_gen_multi", "#xi Right gen Proton Resolution - Multi RP", 20, -.2, .2);
	TH1D *proton_resolution_right_reco_multi = new TH1D("proton_resolution_right_reco_multi", "#xi Right reco Proton Resolution - Multi RP", 20, -2, 2);
	TH1D *pair_xi_right_multi = new TH1D("pair_xi_right_multi", "#xi Pair Right - Multi RP", 20, 0, 0.16);
	TH2D *xi_right_reco_multi = new TH2D("xi_right_reco_multi", "#xi Right Correlation - Multi RP", 20, 0, 0.16, 20, 0, 0.16); 	
	TH1D *proton_resolution_right_multi_1 = new TH1D("proton_resolution_right_multi_1", "#xi Proton Right Proton Resolution - Multi RP", 20, -.05, .05);
	TH1D *proton_resolution_right_multi_2 = new TH1D("proton_resolution_right_multi_2", "#xi Proton Right Proton Resolution - Multi RP", 20, -.05, .05);
	TH1D *proton_resolution_right_multi_3 = new TH1D("proton_resolution_right_multi_3", "#xi Proton Right Proton Resolution - Multi RP", 20, -.05, .05);
	TH1D *proton_resolution_right_multi_4 = new TH1D("proton_resolution_right_multi_4", "#xi Proton Right Proton Resolution - Multi RP", 20, -.05, .05);
	TH1D *proton_resolution_right_multi_5 = new TH1D("proton_resolution_right_multi_5", "#xi Proton Right Proton Resolution - Multi RP", 20, -.05, .05);
	TH1D *proton_resolution_right_multi_6 = new TH1D("proton_resolution_right_multi_6", "#xi Proton Right Proton Resolution - Multi RP", 20, -.05, .05);
	TH1D *proton_resolution_right_multi_7 = new TH1D("proton_resolution_right_multi_7", "#xi Proton Right Proton Resolution - Multi RP", 20, -.05, .05);
	TH1D *diff_proton_reco_pair_xi_right_multi = new TH1D("diff_proton_reco_pair_xi_right_multi", "reco (Proton - Pair) #xi Right - Multi", 10, -1, 1);
	TH1D *ratio_proton_reco_pair_xi_right_multi = new TH1D("ratio_proton_reco_pair_xi_right_multi", "reco (1 - Proton/Pair) #xi Right - Multi", 10, -20, 3);

	TH1D *xi_pair_resolution_left = new TH1D("xi_pair_resolution_left", "Left #xi #mu^{+}#mu^{-} gen - #xi #mu^{+}#mu^{-} reco", 20, -.005, .005);
	TH1D *xi_pair_resolution_right = new TH1D("xi_pair_resolution_right", "Right #xi #mu^{+}#mu^{-} gen - #xi #mu^{+}#mu^{-} reco", 20, -.005, .005);

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

	int zerocortes = 0;
	int umcortes = 0;
	int doiscortes = 0;
	int trescortes = 0;
	int quatrocortes = 0;
	int cincocortes = 0;
	int seiscortes = 0;
	int setecortes = 0;
	int oitocortes = 0;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
		double single_left_xi = -999;
      double single_rp23_xi = -999;
      double single_rp3_xi = -999;
      int cont_single_rp23 = 0;
      double single_right_xi = -999;
      double single_rp103_xi = -999;
      double single_rp123_xi = -999;
      int cont_single_rp123 = 0;
		int contador_xangle = 0;
		int contador_PV = 0, contador_PV2 = 0, contador_PV3 = 0, contador_ext_PV = 0, contador_ext_PV2 = 0, contador_ext_PV3 = 0;
		int contador_PV_dz02 = 0, contador_PV2_dz02 = 0, contador_PV3_dz02 = 0, contador_ext_PV_dz02 = 0, contador_ext_PV2_dz02 = 0, contador_ext_PV3_dz02 = 0;
		int contador_PV_dz01 = 0, contador_PV2_dz01 = 0, contador_PV3_dz01 = 0, contador_ext_PV_dz01 = 0, contador_ext_PV2_dz01 = 0, contador_ext_PV3_dz01 = 0;
		double xi_pair_left_reco = (1./13000) * ( MuonCand_pt[0]*exp( MuonCand_eta[0] ) + MuonCand_pt[1]*exp( MuonCand_eta[1] ) );
      double xi_pair_right_reco = (1./13000) * ( MuonCand_pt[0]*exp( -MuonCand_eta[0] ) + MuonCand_pt[1]*exp( -MuonCand_eta[1] ) );
		double xi_pair_left_gen = (1./13000) * ( GenMuonCand_pt[0]*exp( GenMuonCand_eta[0] ) + GenMuonCand_pt[1]*exp( GenMuonCand_eta[1] ) );
      double xi_pair_right_gen = (1./13000) * ( GenMuonCand_pt[0]*exp( -GenMuonCand_eta[0] ) + GenMuonCand_pt[1]*exp( -GenMuonCand_eta[1] ) );
		double xi_pair_diff_left = (xi_pair_left_reco - xi_pair_left_gen);
      double xi_pair_diff_right = (xi_pair_right_reco - xi_pair_right_gen);
		double xi_proton_gen_left, xi_proton_gen_right;

		TLorentzVector mu1;
		TLorentzVector mu2;
		TLorentzVector v;

		mu1.SetPtEtaPhiM(MuonCand_pt[0],MuonCand_eta[0],MuonCand_phi[0],0.1057);
      mu2.SetPtEtaPhiM(MuonCand_pt[1],MuonCand_eta[1],MuonCand_phi[1],0.1057);
    	//v.SetPtEtaPhiM(Pair_pt[0],Pair_eta[0],Pair_phi[0],Pair_mass[0]);      
      v.SetPxPyPzE(0,0,0,0);
      v += mu1; v += mu2;

		double a = 1 - fabs(deltaPhi(mu1.Phi(),mu2.Phi()))/PI;
		/*
		mu1_z_mu2_z->Fill(MuonCand_vtxz[0] - MuonCand_vtxz[1]);
		mu1_z_primvertex_z->Fill(MuonCand_vtxz[0] - PrimVertexCand_z[0]);
		mu2_z_primvertex_z->Fill(MuonCand_vtxz[1] - PrimVertexCand_z[0]);
      */
		zerocortes++;		

		//if(CrossingAngle==150) contador_xangle++;
		if(MuonCand_pt[0] > 50 && MuonCand_pt[1] > 50){ 
			umcortes++;
			if(MuonCand_charge[0] * MuonCand_charge[1] < 0){
				doiscortes++;
				if(MuonCand_istight[0] && MuonCand_istight[1]){
					trescortes++;
        			if(v.M() > 110.){
						quatrocortes++;
              		if(fabs(PrimVertexCand_z[0] < 15.)){
							cincocortes++;
							PrimVertex_ndof->Fill(PrimVertexCand_ndof[0]);
							PrimVertex_chi2->Fill(PrimVertexCand_chi2[0]);
							if((fabs(MuonCand_vtxz[0] - PrimVertexCand_z[0]) < 3*0.004) && (fabs(MuonCand_vtxz[1] - PrimVertexCand_z[0]) < 3*0.004)){
								seiscortes++;
								if(a < 0.009){
									setecortes++;
									for (size_t pf = 0; pf < nPfCand; pf++) {
										contador_PV++;
										if(PfCand_fromPV[pf] == 2) contador_PV2++;	
										if(PfCand_fromPV[pf] == 3) contador_PV3++;	
										if (((pow( pow(deltaPhi(PfCand_phi[pf],mu1.Phi()),2) + pow( PfCand_eta[pf]-(mu1.Eta()),2),0.5))>0.3) && ((pow( pow(deltaPhi(PfCand_phi[pf],mu2.Phi()),2) + pow( PfCand_eta[pf]-(mu2.Eta()),2),0.5))>0.3)){
											contador_ext_PV++;
                                 if(PfCand_fromPV[pf] == 2) contador_ext_PV2++;
                                 if(PfCand_fromPV[pf] == 3) contador_ext_PV3++;
										
										}
										if(PfCand_dz[pf] < .2){
											contador_PV_dz02++;
											if(PfCand_fromPV[pf] == 2) contador_PV2_dz02++;	
											if(PfCand_fromPV[pf] == 3) contador_PV3_dz02++;	
											if (((pow( pow(deltaPhi(PfCand_phi[pf],mu1.Phi()),2) + pow( PfCand_eta[pf]-(mu1.Eta()),2),0.5))>0.3) && ((pow( pow(deltaPhi(PfCand_phi[pf],mu2.Phi()),2) + pow( PfCand_eta[pf]-(mu2.Eta()),2),0.5))>0.3)){
												contador_ext_PV_dz02++;
                                 	if(PfCand_fromPV[pf] == 2) contador_ext_PV2_dz02++;
                                 	if(PfCand_fromPV[pf] == 3) contador_ext_PV3_dz02++;
					
											}
												
											if(PfCand_dz[pf] < .1){
												contador_PV_dz01++;
												if(PfCand_fromPV[pf] == 2) contador_PV2_dz01++;	
												if(PfCand_fromPV[pf] == 3) contador_PV3_dz01++;	
												if (((pow( pow(deltaPhi(PfCand_phi[pf],mu1.Phi()),2) + pow( PfCand_eta[pf]-(mu1.Eta()),2),0.5))>0.3) && ((pow( pow(deltaPhi(PfCand_phi[pf],mu2.Phi()),2) + pow( PfCand_eta[pf]-(mu2.Eta()),2),0.5))>0.3)){
													contador_ext_PV_dz01++;
                                 		if(PfCand_fromPV[pf] == 2) contador_ext_PV2_dz01++;
                                 		if(PfCand_fromPV[pf] == 3) contador_ext_PV3_dz01++;
					
												}
											}
										}
									}
									/*
									n_fromPV->Fill(contador_PV);
									n_fromPV_2->Fill(contador_PV2);
									n_fromPV_3->Fill(contador_PV3);
									n_ext_fromPV->Fill(contador_ext_PV);
									n_ext_fromPV_2->Fill(contador_ext_PV2);
									n_ext_fromPV_3->Fill(contador_ext_PV3);
									n_fromPV_dz02->Fill(contador_PV_dz02);
									n_fromPV_2_dz02->Fill(contador_PV2_dz02);
									n_fromPV_3_dz02->Fill(contador_PV3_dz02);
									n_ext_fromPV_dz02->Fill(contador_ext_PV_dz02);
									n_ext_fromPV_2_dz02->Fill(contador_ext_PV2_dz02);
									n_ext_fromPV_3_dz02->Fill(contador_ext_PV3_dz02);
									n_fromPV_dz01->Fill(contador_PV_dz01);
									n_fromPV_2_dz01->Fill(contador_PV2_dz01);
									n_fromPV_3_dz01->Fill(contador_PV3_dz01);
									n_ext_fromPV_dz01->Fill(contador_ext_PV_dz01);
									n_ext_fromPV_2_dz01->Fill(contador_ext_PV2_dz01);
									n_ext_fromPV_3_dz01->Fill(contador_ext_PV3_dz01);
									//cout << *ProtCand_arm << endl;
									*/
									if(contador_PV3 <= 3){
										oitocortes++;
										mumu_mass->Fill(v.M());
										mumu_pt->Fill(v.Pt());
										mumu_y->Fill(v.Rapidity());
										xi_pair_resolution_left->Fill(xi_pair_diff_left);
										xi_pair_resolution_right->Fill(xi_pair_diff_right);
										for ( int idz = 0; idz < nGenProtCand; ++idz ) {
										//cout << idz << "   " << GenProtCand_status[idz] << "   " << GenProtCand_eta[idz] << "   " << (1 - GenProtCand_e[idz]/6500) << endl;
									   	if (GenProtCand_eta[idz] > 0) xi_proton_gen_left = (1 - GenProtCand_e[idz]/6500);
									   	if (GenProtCand_eta[idz] < 0) xi_proton_gen_right = (1 - GenProtCand_e[idz]/6500);
										}
										for ( int idx = 0; idx < nRecoProtCand; ++idx ) {
											//cout << idx << " " << ProtCand_rpid[idx] << " " << ProtCand_arm[idx] << " " << ProtCand_xi[idx] << endl;
											if (ProtCand_rpid[idx] == 3) {
												if (ProtCand_ismultirp[idx] == 0) {
													proton_xi_left_rp3->Fill(ProtCand_xi[idx]);
													proton_resolution_left_gen_rp3->Fill((xi_proton_gen_left - ProtCand_xi[idx])/xi_proton_gen_left);
													proton_resolution_left_reco_rp3->Fill((ProtCand_xi[idx] - xi_proton_gen_left)/ProtCand_xi[idx]);
													pair_xi_left_rp3->Fill(xi_pair_left_reco);
													xi_left_reco_rp3->Fill(ProtCand_xi[idx], xi_pair_left_reco);
													diff_proton_reco_pair_xi_left_rp3->Fill(ProtCand_xi[idx] - xi_pair_left_reco); 
													ratio_proton_reco_pair_xi_left_rp3->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco); 
													//xi_left_wrong->Fill(ProtCand_xi[idx], xi_pair_right); 
													if (ProtCand_xi[idx] >= 0.02 && ProtCand_xi[idx] < 0.04) {
														proton_resolution_left_rp3_1->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.04 && ProtCand_xi[idx] < 0.06) {
														proton_resolution_left_rp3_2->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.06 && ProtCand_xi[idx] < 0.08) {
														proton_resolution_left_rp3_3->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.08 && ProtCand_xi[idx] < 0.10) { 
														proton_resolution_left_rp3_4->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.10 && ProtCand_xi[idx] < 0.12) {
														proton_resolution_left_rp3_5->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.12 && ProtCand_xi[idx] < 0.14) {
														proton_resolution_left_rp3_6->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}	
                                       if (ProtCand_xi[idx] >= 0.14 && ProtCand_xi[idx] < 0.16) {
														proton_resolution_left_rp3_7->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
												}		
											}
											if (ProtCand_rpid[idx] == 23) {
												if (ProtCand_ismultirp[idx] == 0) {
													proton_xi_left_rp23->Fill(ProtCand_xi[idx]);
													proton_resolution_left_gen_rp23->Fill((xi_proton_gen_left - ProtCand_xi[idx])/xi_proton_gen_left);
													proton_resolution_left_reco_rp23->Fill((ProtCand_xi[idx] - xi_proton_gen_left)/ProtCand_xi[idx]);
													pair_xi_left_rp23->Fill(xi_pair_left_reco);
													xi_left_reco_rp23->Fill(ProtCand_xi[idx], xi_pair_left_reco); 
													diff_proton_reco_pair_xi_left_rp23->Fill(ProtCand_xi[idx] - xi_pair_left_reco); 
													ratio_proton_reco_pair_xi_left_rp23->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco); 
													//xi_left_wrong->Fill(ProtCand_xi[idx], xi_pair_right); 
													if (ProtCand_xi[idx] >= 0.02 && ProtCand_xi[idx] < 0.04) {
														proton_resolution_left_rp23_1->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.04 && ProtCand_xi[idx] < 0.06) {
														proton_resolution_left_rp23_2->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.06 && ProtCand_xi[idx] < 0.08) {
														proton_resolution_left_rp23_3->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.08 && ProtCand_xi[idx] < 0.10) {
														proton_resolution_left_rp23_4->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.10 && ProtCand_xi[idx] < 0.12) {
														proton_resolution_left_rp23_5->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.12 && ProtCand_xi[idx] < 0.14) {
														proton_resolution_left_rp23_6->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.14 && ProtCand_xi[idx] < 0.16) {
														proton_resolution_left_rp23_7->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
												}		
											}
											if ((ProtCand_rpid[idx] == 3) || (ProtCand_rpid[idx] == 23)) {
												if (ProtCand_ismultirp[idx] == 0) {
													//cout << idx << "   " << ProtCand_xi[idx] << endl;
													proton_xi_left_single->Fill(ProtCand_xi[idx]);
													proton_resolution_left_gen_single->Fill((xi_proton_gen_left - ProtCand_xi[idx])/xi_proton_gen_left);
													proton_resolution_left_reco_single->Fill((ProtCand_xi[idx] - xi_proton_gen_left)/ProtCand_xi[idx]);
													pair_xi_left_single->Fill(xi_pair_left_reco);
													xi_left_reco_single->Fill(ProtCand_xi[idx], xi_pair_left_reco); 
													diff_proton_reco_pair_xi_left_single->Fill(ProtCand_xi[idx] - xi_pair_left_reco); 
													ratio_proton_reco_pair_xi_left_single->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco); 
													//xi_left_wrong->Fill(ProtCand_xi[idx], xi_pair_right); 
													if (ProtCand_xi[idx] >= 0.02 && ProtCand_xi[idx] < 0.04) {
														proton_resolution_left_single_1->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.04 && ProtCand_xi[idx] < 0.06) {
														proton_resolution_left_single_2->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.06 && ProtCand_xi[idx] < 0.08) {
														proton_resolution_left_single_3->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.08 && ProtCand_xi[idx] < 0.10) {
														proton_resolution_left_single_4->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.10 && ProtCand_xi[idx] < 0.12) {	
														proton_resolution_left_single_5->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.12 && ProtCand_xi[idx] < 0.14) {
														proton_resolution_left_single_6->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.14 && ProtCand_xi[idx] < 0.16) {
														proton_resolution_left_single_7->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
												}		
											}

											if(ProtCand_rpid[idx] == 3 && ProtCand_ismultirp[idx] == 0) single_rp3_xi = ProtCand_xi[idx];

                                 if(ProtCand_rpid[idx] == 23 && ProtCand_ismultirp[idx] == 0){
                                    single_rp23_xi = ProtCand_xi[idx];
                                    cont_single_rp23++;
                                 }

											if (ProtCand_rpid[idx] == 103) {                           
            	              	   	if (ProtCand_ismultirp[idx] == 0) {
													proton_xi_right_rp103->Fill(ProtCand_xi[idx]);
													proton_resolution_right_gen_rp103->Fill((xi_proton_gen_right - ProtCand_xi[idx])/xi_proton_gen_right);
													proton_resolution_right_reco_rp103->Fill((ProtCand_xi[idx] - xi_proton_gen_right)/ProtCand_xi[idx]);
													pair_xi_right_rp103->Fill(xi_pair_right_reco);
													xi_right_reco_rp103->Fill(ProtCand_xi[idx], xi_pair_right_reco);
													diff_proton_reco_pair_xi_right_rp103->Fill(ProtCand_xi[idx] - xi_pair_right_reco); 
													ratio_proton_reco_pair_xi_right_rp103->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco); 
													//xi_right_wrong->Fill(ProtCand_xi[idx], xi_pair_left);
													if (ProtCand_xi[idx] >= 0.02 && ProtCand_xi[idx] < 0.04) {
														proton_resolution_right_rp103_1->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.04 && ProtCand_xi[idx] < 0.06) {
														proton_resolution_right_rp103_2->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.06 && ProtCand_xi[idx] < 0.08) {
														proton_resolution_right_rp103_3->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.08 && ProtCand_xi[idx] < 0.10) {
														proton_resolution_right_rp103_4->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.10 && ProtCand_xi[idx] < 0.12) {
														proton_resolution_right_rp103_5->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.12 && ProtCand_xi[idx] < 0.14) {
														proton_resolution_right_rp103_6->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.14 && ProtCand_xi[idx] < 0.16) {
														proton_resolution_right_rp103_7->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
												}		
											}
											if (ProtCand_rpid[idx] == 123) {                           
            	              	   	if (ProtCand_ismultirp[idx] == 0) {
													proton_xi_right_rp123->Fill(ProtCand_xi[idx]);
													proton_resolution_right_gen_rp123->Fill((xi_proton_gen_right - ProtCand_xi[idx])/xi_proton_gen_right);
													proton_resolution_right_reco_rp123->Fill((ProtCand_xi[idx] - xi_proton_gen_right/ProtCand_xi[idx]));
													pair_xi_right_rp123->Fill(xi_pair_right_reco);
													xi_right_reco_rp123->Fill(ProtCand_xi[idx], xi_pair_right_reco);
													diff_proton_reco_pair_xi_right_rp123->Fill(ProtCand_xi[idx] - xi_pair_right_reco); 
													ratio_proton_reco_pair_xi_right_rp123->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco); 
													//xi_right_wrong->Fill(ProtCand_xi[idx], xi_pair_left);
													if (ProtCand_xi[idx] >= 0.02 && ProtCand_xi[idx] < 0.04) {
														proton_resolution_right_rp123_1->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.04 && ProtCand_xi[idx] < 0.06) {
														proton_resolution_right_rp123_2->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.06 && ProtCand_xi[idx] < 0.08) {	
														proton_resolution_right_rp123_3->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.08 && ProtCand_xi[idx] < 0.10) {
														proton_resolution_right_rp123_4->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.10 && ProtCand_xi[idx] < 0.12) {
														proton_resolution_right_rp123_5->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.12 && ProtCand_xi[idx] < 0.14) {
														proton_resolution_right_rp123_6->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.14 && ProtCand_xi[idx] < 0.16) {
														proton_resolution_right_rp123_6->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
												}		
											}
											if ((ProtCand_rpid[idx] == 103) || (ProtCand_rpid[idx] == 123)) {                           
            	              	   	if (ProtCand_ismultirp[idx] == 0) {
													proton_xi_right_single->Fill(ProtCand_xi[idx]);
													proton_resolution_right_gen_single->Fill((xi_proton_gen_right - ProtCand_xi[idx])/xi_proton_gen_right);
													proton_resolution_right_reco_single->Fill((ProtCand_xi[idx] - xi_proton_gen_right/ProtCand_xi[idx]));
													pair_xi_right_single->Fill(xi_pair_right_reco);
													xi_right_reco_single->Fill(ProtCand_xi[idx], xi_pair_right_reco);
													diff_proton_reco_pair_xi_right_single->Fill(ProtCand_xi[idx] - xi_pair_right_reco); 
													ratio_proton_reco_pair_xi_right_single->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco); 
													//xi_right_wrong->Fill(ProtCand_xi[idx], xi_pair_left);
													if (ProtCand_xi[idx] >= 0.02 && ProtCand_xi[idx] < 0.04) {
														proton_resolution_right_single_1->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.04 && ProtCand_xi[idx] < 0.06) {
														proton_resolution_right_single_2->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.06 && ProtCand_xi[idx] < 0.08) {
														proton_resolution_right_single_3->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.08 && ProtCand_xi[idx] < 0.10) {
														proton_resolution_right_single_4->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.10 && ProtCand_xi[idx] < 0.12) {
														proton_resolution_right_single_5->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.12 && ProtCand_xi[idx] < 0.14) {
														proton_resolution_right_single_6->Fill(ProtCand_xi[idx] - xi_proton_gen_right);	
													}
                                       if (ProtCand_xi[idx] >= 0.14 && ProtCand_xi[idx] < 0.16) {	
														proton_resolution_right_single_7->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
												}		
											}

											if(ProtCand_rpid[idx] == 103 && ProtCand_ismultirp[idx] == 0) single_rp103_xi = ProtCand_xi[idx];

                                 if(ProtCand_rpid[idx] == 123 && ProtCand_ismultirp[idx] == 0){
                                    single_rp123_xi = ProtCand_xi[idx];
                                    cont_single_rp123++;
                                 }
		
											if (ProtCand_arm[idx] == 0) {
												if (ProtCand_ismultirp[idx] == 1) {
													proton_xi_left_multi->Fill(ProtCand_xi[idx]);
													proton_resolution_left_gen_multi->Fill((xi_proton_gen_left - ProtCand_xi[idx])/xi_proton_gen_left);
													proton_resolution_left_reco_multi->Fill((ProtCand_xi[idx] - xi_proton_gen_left/ProtCand_xi[idx]));
													pair_xi_left_multi->Fill(xi_pair_left_reco);
													xi_left_reco_multi->Fill(ProtCand_xi[idx], xi_pair_left_reco); 
													diff_proton_reco_pair_xi_left_multi->Fill(ProtCand_xi[idx] - xi_pair_left_reco); 
													ratio_proton_reco_pair_xi_left_multi->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco); 
													//xi_left_wrong->Fill(ProtCand_xi[idx], xi_pair_right); 
													if (ProtCand_xi[idx] >= 0.02 && ProtCand_xi[idx] < 0.04) {
														proton_resolution_left_multi_1->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.04 && ProtCand_xi[idx] < 0.06) {
														proton_resolution_left_multi_2->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.06 && ProtCand_xi[idx] < 0.08) {
														proton_resolution_left_multi_3->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.08 && ProtCand_xi[idx] < 0.10) {
														proton_resolution_left_multi_4->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.10 && ProtCand_xi[idx] < 0.12) {	
														proton_resolution_left_multi_5->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.12 && ProtCand_xi[idx] < 0.14) {	
														proton_resolution_left_multi_6->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
                                       if (ProtCand_xi[idx] >= 0.14 && ProtCand_xi[idx] < 0.16) {	
														proton_resolution_left_multi_7->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
													}
												}		
											}
											if (ProtCand_arm[idx] == 1) {                           
            	              	   	if (ProtCand_ismultirp[idx] == 1) {
													proton_xi_right_multi->Fill(ProtCand_xi[idx]);
													proton_resolution_right_gen_multi->Fill((xi_proton_gen_right - ProtCand_xi[idx])/xi_proton_gen_right);
													proton_resolution_right_reco_multi->Fill((ProtCand_xi[idx] - xi_proton_gen_right/ProtCand_xi[idx]));
													pair_xi_right_multi->Fill(xi_pair_right_reco);
													xi_right_reco_multi->Fill(ProtCand_xi[idx], xi_pair_right_reco);
													diff_proton_reco_pair_xi_right_multi->Fill(ProtCand_xi[idx] - xi_pair_right_reco); 
													ratio_proton_reco_pair_xi_right_multi->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco); 
													//xi_right_wrong->Fill(ProtCand_xi[idx], xi_pair_left);
													if (ProtCand_xi[idx] >= 0.02 && ProtCand_xi[idx] < 0.04) {
														proton_resolution_right_multi_1->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.04 && ProtCand_xi[idx] < 0.06) {
														proton_resolution_right_multi_2->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.06 && ProtCand_xi[idx] < 0.08) {
														proton_resolution_right_multi_3->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.08 && ProtCand_xi[idx] < 0.10) {
														proton_resolution_right_multi_4->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.10 && ProtCand_xi[idx] < 0.12) {
														proton_resolution_right_multi_5->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.12 && ProtCand_xi[idx] < 0.14) {
														proton_resolution_right_multi_6->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
                                       if (ProtCand_xi[idx] >= 0.14 && ProtCand_xi[idx] < 0.16) {
														proton_resolution_right_multi_7->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
													}
												}	
               	          		}
                          		}
										if (cont_single_rp23==1 && single_rp23_xi > 0){
                                 single_left_xi = single_rp23_xi;
                                 xi_left_reco_single_2->Fill(single_left_xi,xi_pair_left_reco);
                              }
                              else {
                                 single_left_xi = single_rp3_xi;
                              }

                              if (cont_single_rp123==1 && single_rp123_xi > 0){
                                 single_right_xi = single_rp123_xi;
                                 xi_right_reco_single_2->Fill(single_right_xi,xi_pair_right_reco);
                              }
                              else {
                                 single_right_xi = single_rp103_xi;
                              }
							 		}
								}
							}
						}
					}
				}
			}		
		}
	}
	
	double proton_left_rp3[10];
	double proton_left_rp3_err[10];
	proton_left_rp3[0] = (proton_resolution_left_rp3_1->GetStdDev());
	proton_left_rp3_err[0] = (proton_resolution_left_rp3_1->GetStdDevError());
	proton_left_rp3[1] = (proton_resolution_left_rp3_2->GetStdDev());
	proton_left_rp3_err[1] = (proton_resolution_left_rp3_2->GetStdDevError());
	proton_left_rp3[2] = (proton_resolution_left_rp3_3->GetStdDev());
	proton_left_rp3_err[2] = (proton_resolution_left_rp3_3->GetStdDevError());
	proton_left_rp3[3] = (proton_resolution_left_rp3_4->GetStdDev());
	proton_left_rp3_err[3] = (proton_resolution_left_rp3_4->GetStdDevError());
	proton_left_rp3[4] = (proton_resolution_left_rp3_5->GetStdDev());
	proton_left_rp3_err[4] = (proton_resolution_left_rp3_5->GetStdDevError());
	//proton_left_rp3[5] = (proton_resolution_left_rp3_6->GetStdDev());
	//proton_left_rp3_err[5] = (proton_resolution_left_rp3_6->GetStdDevError());
	//proton_left_rp3[6] = (proton_resolution_left_rp3_7->GetStdDev());
	//proton_left_rp3_err[6] = (proton_resolution_left_rp3_7->GetStdDevError());

	double proton_left_rp23[10];
	double proton_left_rp23_err[10];
	proton_left_rp23[0] = (proton_resolution_left_rp23_1->GetStdDev());
	proton_left_rp23_err[0] = (proton_resolution_left_rp23_1->GetStdDevError());
	proton_left_rp23[1] = (proton_resolution_left_rp23_2->GetStdDev());
	proton_left_rp23_err[1] = (proton_resolution_left_rp23_2->GetStdDevError());
	proton_left_rp23[2] = (proton_resolution_left_rp23_3->GetStdDev());
	proton_left_rp23_err[2] = (proton_resolution_left_rp23_3->GetStdDevError());
	proton_left_rp23[3] = (proton_resolution_left_rp23_4->GetStdDev());
	proton_left_rp23_err[3] = (proton_resolution_left_rp23_4->GetStdDevError());
	proton_left_rp23[4] = (proton_resolution_left_rp23_5->GetStdDev());
	proton_left_rp23_err[4] = (proton_resolution_left_rp23_5->GetStdDevError());
	//proton_left_rp23[5] = (proton_resolution_left_rp23_6->GetStdDev());
	//proton_left_rp23_err[5] = (proton_resolution_left_rp23_6->GetStdDevError());
	//proton_left_rp23[6] = (proton_resolution_left_rp23_7->GetStdDev());
	//proton_left_rp23_err[6] = (proton_resolution_left_rp23_7->GetStdDevError());

	double proton_left_single[10];
	double proton_left_single_err[10];
	proton_left_single[0] = (proton_resolution_left_single_1->GetStdDev());
	proton_left_single_err[0] = (proton_resolution_left_single_1->GetStdDevError());
	proton_left_single[1] = (proton_resolution_left_single_2->GetStdDev());
	proton_left_single_err[1] = (proton_resolution_left_single_2->GetStdDevError());
	proton_left_single[2] = (proton_resolution_left_single_3->GetStdDev());
	proton_left_single_err[2] = (proton_resolution_left_single_3->GetStdDevError());
	proton_left_single[3] = (proton_resolution_left_single_4->GetStdDev());
	proton_left_single_err[3] = (proton_resolution_left_single_4->GetStdDevError());
	proton_left_single[4] = (proton_resolution_left_single_5->GetStdDev());
	proton_left_single_err[4] = (proton_resolution_left_single_5->GetStdDevError());
	//proton_left_single[5] = (proton_resolution_left_single_6->GetStdDev());
	//proton_left_single_err[5] = (proton_resolution_left_single_6->GetStdDevError());
	//proton_left_single[6] = (proton_resolution_left_single_7->GetStdDev());
	//proton_left_single_err[6] = (proton_resolution_left_single_7->GetStdDevError());

	double proton_right_rp103[10];
	double proton_right_rp103_err[10];
	proton_right_rp103[0] = (proton_resolution_right_rp103_1->GetStdDev());
	proton_right_rp103_err[0] = (proton_resolution_right_rp103_1->GetStdDevError());
	proton_right_rp103[1] = (proton_resolution_right_rp103_2->GetStdDev());
	proton_right_rp103_err[1] = (proton_resolution_right_rp103_2->GetStdDevError());
	proton_right_rp103[2] = (proton_resolution_right_rp103_3->GetStdDev());
	proton_right_rp103_err[2] = (proton_resolution_right_rp103_3->GetStdDevError());
	proton_right_rp103[3] = (proton_resolution_right_rp103_4->GetStdDev());
	proton_right_rp103_err[3] = (proton_resolution_right_rp103_4->GetStdDevError());
	proton_right_rp103[4] = (proton_resolution_right_rp103_5->GetStdDev());
	proton_right_rp103_err[4] = (proton_resolution_right_rp103_5->GetStdDevError());
	//proton_right_rp103[5] = (proton_resolution_right_rp103_6->GetStdDev());
	//proton_right_rp103_err[5] = (proton_resolution_right_rp103_6->GetStdDevError());
	//proton_right_rp103[6] = (proton_resolution_right_rp103_7->GetStdDev());
	//proton_right_rp103_err[6] = (proton_resolution_right_rp103_7->GetStdDevError());

	double proton_right_rp123[10];
	double proton_right_rp123_err[10];
	proton_right_rp123[0] = (proton_resolution_right_rp123_1->GetStdDev());
	proton_right_rp123_err[0] = (proton_resolution_right_rp123_1->GetStdDevError());
	proton_right_rp123[1] = (proton_resolution_right_rp123_2->GetStdDev());
	proton_right_rp123_err[1] = (proton_resolution_right_rp123_2->GetStdDevError());
	proton_right_rp123[2] = (proton_resolution_right_rp123_3->GetStdDev());
	proton_right_rp123_err[2] = (proton_resolution_right_rp123_3->GetStdDevError());
	proton_right_rp123[3] = (proton_resolution_right_rp123_4->GetStdDev());
	proton_right_rp123_err[3] = (proton_resolution_right_rp123_4->GetStdDevError());
	proton_right_rp123[4] = (proton_resolution_right_rp123_5->GetStdDev());
	proton_right_rp123_err[4] = (proton_resolution_right_rp123_5->GetStdDevError());
	//proton_right_rp123[5] = (proton_resolution_right_rp123_6->GetStdDev());
	//proton_right_rp123_err[5] = (proton_resolution_right_rp123_6->GetStdDevError());
	//proton_right_rp123[6] = (proton_resolution_right_rp123_7->GetStdDev());
	//proton_right_rp123_err[6] = (proton_resolution_right_rp123_7->GetStdDevError());

	double proton_right_single[10];
	double proton_right_single_err[10];
	proton_right_single[0] = (proton_resolution_right_single_1->GetStdDev());
	proton_right_single_err[0] = (proton_resolution_right_single_1->GetStdDevError());
	proton_right_single[1] = (proton_resolution_right_single_2->GetStdDev());
	proton_right_single_err[1] = (proton_resolution_right_single_2->GetStdDevError());
	proton_right_single[2] = (proton_resolution_right_single_3->GetStdDev());
	proton_right_single_err[2] = (proton_resolution_right_single_3->GetStdDevError());
	proton_right_single[3] = (proton_resolution_right_single_4->GetStdDev());
	proton_right_single_err[3] = (proton_resolution_right_single_4->GetStdDevError());
	proton_right_single[4] = (proton_resolution_right_single_5->GetStdDev());
	proton_right_single_err[4] = (proton_resolution_right_single_5->GetStdDevError());
	//proton_right_single[5] = (proton_resolution_right_single_6->GetStdDev());
	//proton_right_single_err[5] = (proton_resolution_right_single_6->GetStdDevError());
	//proton_right_single[6] = (proton_resolution_right_single_7->GetStdDev());
	//proton_right_single_err[6] = (proton_resolution_right_single_7->GetStdDevError());

	double proton_left_multi[10];
	double proton_left_multi_err[10];
	proton_left_multi[0] = (proton_resolution_left_multi_1->GetStdDev());
	proton_left_multi_err[0] = (proton_resolution_left_multi_1->GetStdDevError());
	proton_left_multi[1] = (proton_resolution_left_multi_2->GetStdDev());
	proton_left_multi_err[1] = (proton_resolution_left_multi_2->GetStdDevError());
	proton_left_multi[2] = (proton_resolution_left_multi_3->GetStdDev());
	proton_left_multi_err[2] = (proton_resolution_left_multi_3->GetStdDevError());
	proton_left_multi[3] = (proton_resolution_left_multi_4->GetStdDev());
	proton_left_multi_err[3] = (proton_resolution_left_multi_4->GetStdDevError());
	proton_left_multi[4] = (proton_resolution_left_multi_5->GetStdDev());
	proton_left_multi_err[4] = (proton_resolution_left_multi_5->GetStdDevError());
	//proton_left_multi[5] = (proton_resolution_left_multi_6->GetStdDev());
	//proton_left_multi_err[5] = (proton_resolution_left_multi_6->GetStdDevError());
	//proton_left_multi[6] = (proton_resolution_left_multi_7->GetStdDev());
	//proton_left_multi_err[6] = (proton_resolution_left_multi_7->GetStdDevError());

	double proton_right_multi[10];
	double proton_right_multi_err[10];
	proton_right_multi[0] = (proton_resolution_right_multi_1->GetStdDev());
	proton_right_multi_err[0] = (proton_resolution_right_multi_1->GetStdDevError());
	proton_right_multi[1] = (proton_resolution_right_multi_2->GetStdDev());
	proton_right_multi_err[1] = (proton_resolution_right_multi_2->GetStdDevError());
	proton_right_multi[2] = (proton_resolution_right_multi_3->GetStdDev());
	proton_right_multi_err[2] = (proton_resolution_right_multi_3->GetStdDevError());
	proton_right_multi[3] = (proton_resolution_right_multi_4->GetStdDev());
	proton_right_multi_err[3] = (proton_resolution_right_multi_4->GetStdDevError());
	proton_right_multi[4] = (proton_resolution_right_multi_5->GetStdDev());
	proton_right_multi_err[4] = (proton_resolution_right_multi_5->GetStdDevError());
	//proton_right_multi[5] = (proton_resolution_right_multi_6->GetStdDev());
	//proton_right_multi_err[5] = (proton_resolution_right_multi_6->GetStdDevError());
	//proton_right_multi[6] = (proton_resolution_right_multi_7->GetStdDev());
	//proton_right_multi_err[6] = (proton_resolution_right_multi_7->GetStdDevError());


	cout << "0cortes: " << zerocortes << endl;
	cout << "1cortes: " << umcortes << endl;
	cout << "2cortes: " << doiscortes << endl;
	cout << "3cortes: " << trescortes << endl;
	cout << "4cortes: " << quatrocortes << endl;
	cout << "5cortes: " << cincocortes << endl;
	cout << "6cortes: " << seiscortes << endl;
	cout << "7cortes: " << setecortes << endl;
	cout << "8cortes: " << oitocortes << endl;

   Int_t n = 5;
	
	TCanvas *rp3 = new TCanvas("rp3","#sigma x #xi - Proton Left - RP 3",200,10,700,500);
   Double_t x_rp3[10], y_rp3[10], ex_rp3[10], ey_rp3[10];
   for (Int_t i = 0;i<n;i++) {
     x_rp3[i] = 0.03+0.02*i;
     y_rp3[i] = proton_left_rp3[i];
	  ex_rp3[i] = 0.01;
	  ey_rp3[i] = proton_left_rp3_err[i];
   }
   TGraph *gr_rp3 = new TGraphErrors(n,x_rp3,y_rp3,ex_rp3,ey_rp3);
   gr_rp3->SetTitle("#sigma x #xi - Proton Left - RP 3");
	gr_rp3->Fit("pol1");
	TF1 *f_rp3 = (TF1*)gr_rp3->GetListOfFunctions()->FindObject("pol1");
	double coef_ang_rp3 = f_rp3->GetParameter(1);
	double coef_ang_err_rp3 = f_rp3->GetParError(1);

	//TCanvas *xi_reco_rp3 = new TCanvas("xi_reco_rp3","",0,0,1200,1000);
   //if () xi_left_reco_rp3->SetMartkerStyle("24");
   //if () xi_left_reco_rp3->SetMarkerStyle("26");
   //h_data_mass->Draw("SAME");
   //c_mass->SaveAs("comp/mass.png");
   //c_mass->cd();
   //c_mass->Close();

	TCanvas *rp23 = new TCanvas("rp23","#sigma x #xi - Proton Left - RP 23",200,10,700,500);
   Double_t x_rp23[10], y_rp23[10], ex_rp23[10], ey_rp23[10];
   for (Int_t i = 0;i<n;i++) {
     x_rp23[i] = 0.03+0.02*i;
     y_rp23[i] = proton_left_rp23[i];
	  ex_rp23[i] = 0.01;
	  ey_rp23[i] = proton_left_rp23_err[i];
   }
   TGraph *gr_rp23 = new TGraphErrors(n,x_rp23,y_rp23,ex_rp23,ey_rp23);
   gr_rp23->SetTitle("#sigma x #xi - Proton Left - RP 23");
	gr_rp23->Fit("pol1");
	TF1 *f_rp23 = (TF1*)gr_rp23->GetListOfFunctions()->FindObject("pol1");
	double coef_ang_rp23 = f_rp23->GetParameter(1);
	double coef_ang_err_rp23 = f_rp23->GetParError(1);

	TCanvas *left_single = new TCanvas("left_single","#sigma x #xi - Proton Left - Single RP",200,10,700,500);
   Double_t x_left_single[10], y_left_single[10], ex_left_single[10], ey_left_single[10];
   for (Int_t i = 0;i<n;i++) {
     x_left_single[i] = 0.03+0.02*i;
     y_left_single[i] = proton_left_single[i];
	  ex_left_single[i] = 0.01;
	  ey_left_single[i] = proton_left_single_err[i];
   }
   TGraph *gr_left_single = new TGraphErrors(n,x_left_single,y_left_single,ex_left_single,ey_left_single);
   gr_left_single->SetTitle("#sigma x #xi - Proton Left - Single RP");
	gr_left_single->Fit("pol1");
	TF1 *f_left_single = (TF1*)gr_left_single->GetListOfFunctions()->FindObject("pol1");
	double coef_ang_left_single = f_left_single->GetParameter(1);
	double coef_ang_err_left_single = f_left_single->GetParError(1);

	TCanvas *rp103 = new TCanvas("rp103","#sigma x #xi - Proton Right - RP 103",200,10,700,500);
   Double_t x_rp103[10], y_rp103[10], ex_rp103[10], ey_rp103[10];
   for (Int_t i = 0;i<n;i++) {
     x_rp103[i] = 0.03+0.02*i;
     y_rp103[i] = proton_right_rp103[i];
	  ex_rp103[i] = 0.01;
	  ey_rp103[i] = proton_right_rp103_err[i];
   }
   TGraph *gr_rp103 = new TGraphErrors(n,x_rp103,y_rp103,ex_rp103,ey_rp103);
   gr_rp103->SetTitle("#sigma x #xi - Proton Right - RP 103");
	gr_rp103->Fit("pol1");
	TF1 *f_rp103 = (TF1*)gr_rp103->GetListOfFunctions()->FindObject("pol1");
	double coef_ang_rp103 = f_rp103->GetParameter(1);
	double coef_ang_err_rp103 = f_rp103->GetParError(1);

	TCanvas *rp123 = new TCanvas("rp123","#sigma x #xi - Proton Right - RP 123",200,10,700,500);
   Double_t x_rp123[10], y_rp123[10], ex_rp123[10], ey_rp123[10];
   for (Int_t i = 0;i<n;i++) {
     x_rp123[i] = 0.03+0.02*i;
     y_rp123[i] = proton_right_rp123[i];
	  ex_rp123[i] = 0.01;
	  ey_rp123[i] = proton_right_rp123_err[i];
   }
   TGraph *gr_rp123 = new TGraphErrors(n,x_rp123,y_rp123,ex_rp123,ey_rp123);
   gr_rp123->SetTitle("#sigma x #xi - Proton Right - RP 123");
	gr_rp123->Fit("pol1");
	TF1 *f_rp123 = (TF1*)gr_rp123->GetListOfFunctions()->FindObject("pol1");
	double coef_ang_rp123 = f_rp123->GetParameter(1);
	double coef_ang_err_rp123 = f_rp123->GetParError(1);

	TCanvas *right_single = new TCanvas("right_single","#sigma x #xi - Proton Right - Single RP",200,10,700,500);
   Double_t x_right_single[10], y_right_single[10], ex_right_single[10], ey_right_single[10];
   for (Int_t i = 0;i<n;i++) {
     x_right_single[i] = 0.03+0.02*i;
     y_right_single[i] = proton_right_single[i];
	  ex_right_single[i] = 0.01;
	  ey_right_single[i] = proton_right_single_err[i];
   }
   TGraph *gr_right_single = new TGraphErrors(n,x_right_single,y_right_single,ex_right_single,ey_right_single);
   gr_right_single->SetTitle("#sigma x #xi - Proton Right - Single RP");
	gr_right_single->Fit("pol1");
	TF1 *f_right_single = (TF1*)gr_right_single->GetListOfFunctions()->FindObject("pol1");
	double coef_ang_right_single = f_right_single->GetParameter(1);
	double coef_ang_err_right_single = f_right_single->GetParError(1);

	TCanvas *left_multi = new TCanvas("left_multi","#sigma x #xi - Proton Left - Multi RP",200,10,700,500);
   Double_t x_left_multi[10], y_left_multi[10], ex_left_multi[10], ey_left_multi[10];
   for (Int_t i = 0;i<n;i++) {
     x_left_multi[i] = 0.03+0.02*i;
     y_left_multi[i] = proton_left_multi[i];
	  ex_left_multi[i] = 0.01;
	  ey_left_multi[i] = proton_left_multi_err[i];
   }
   TGraph *gr_left_multi = new TGraphErrors(n,x_left_multi,y_left_multi,ex_left_multi,ey_left_multi);
   gr_left_multi->SetTitle("#sigma x #xi - Proton Left - Multi RP");
	gr_left_multi->Fit("pol1");
	TF1 *f_left_multi = (TF1*)gr_left_multi->GetListOfFunctions()->FindObject("pol1");
	double coef_ang_left_multi = f_left_multi->GetParameter(1);
	double coef_ang_err_left_multi = f_left_multi->GetParError(1);

	TCanvas *right_multi = new TCanvas("right_multi","#sigma x #xi - Proton Right - Multi RP",200,10,700,500);
   Double_t x_right_multi[10], y_right_multi[10], ex_right_multi[10], ey_right_multi[10];
   for (Int_t i = 0;i<n;i++) {
     x_right_multi[i] = 0.03+0.02*i;
     y_right_multi[i] = proton_right_multi[i];
	  ex_right_multi[i] = 0.01;
	  ey_right_multi[i] = proton_right_multi_err[i];
   }
   TGraph *gr_right_multi = new TGraphErrors(n,x_right_multi,y_right_multi,ex_right_multi,ey_right_multi);
   gr_right_multi->SetTitle("#sigma x #xi - Proton Right - Multi RP");
	gr_right_multi->Fit("pol1");
	TF1 *f_right_multi = (TF1*)gr_right_multi->GetListOfFunctions()->FindObject("pol1");
	double coef_ang_right_multi = f_right_multi->GetParameter(1);
	double coef_ang_err_right_multi = f_right_multi->GetParError(1);

	TFile* f = new TFile("output_cut.root", "RECREATE");
	PrimVertex_ndof->Write();
	PrimVertex_chi2->Write();
   mumu_mass->Write();
   mumu_pt->Write();
   mumu_y->Write();
	/*
	n_fromPV->Write();
	n_fromPV_2->Write();
	n_fromPV_3->Write();
	n_ext_fromPV->Write();
	n_ext_fromPV_2->Write();
	n_ext_fromPV_3->Write();
	n_fromPV_dz02->Write();
	n_fromPV_2_dz02->Write();
	n_fromPV_3_dz02->Write();
	n_ext_fromPV_dz02->Write();
	n_ext_fromPV_2_dz02->Write();
	n_ext_fromPV_3_dz02->Write();
	n_fromPV_dz01->Write();
	n_fromPV_2_dz01->Write();
	n_fromPV_3_dz01->Write();
	n_ext_fromPV_dz01->Write();
	n_ext_fromPV_2_dz01->Write();
	n_ext_fromPV_3_dz01->Write();
   mu1_z_mu2_z->Write();
   mu1_z_primvertex_z->Write();
   mu2_z_primvertex_z->Write();
	*/
	proton_xi_left_rp3->Write();
  	proton_resolution_left_gen_rp3->Write();
  	proton_resolution_left_reco_rp3->Write();
	pair_xi_left_rp3->Write();
   xi_left_reco_rp3->Write();
	proton_resolution_left_rp3_1->Write();
	proton_resolution_left_rp3_2->Write();
	proton_resolution_left_rp3_3->Write();
	proton_resolution_left_rp3_4->Write();
	proton_resolution_left_rp3_5->Write();
	proton_resolution_left_rp3_6->Write();
	proton_resolution_left_rp3_7->Write();
	diff_proton_reco_pair_xi_left_rp3->Write();
	ratio_proton_reco_pair_xi_left_rp3->Write();
	gr_rp3->Write();

	proton_xi_left_rp23->Write();
  	proton_resolution_left_gen_rp23->Write();
  	proton_resolution_left_reco_rp23->Write();
	pair_xi_left_rp23->Write();
   xi_left_reco_rp23->Write();
	proton_resolution_left_rp23_1->Write();
	proton_resolution_left_rp23_2->Write();
	proton_resolution_left_rp23_3->Write();
	proton_resolution_left_rp23_4->Write();
	proton_resolution_left_rp23_5->Write();
	proton_resolution_left_rp23_6->Write();
	proton_resolution_left_rp23_7->Write();
	diff_proton_reco_pair_xi_left_rp23->Write();
	ratio_proton_reco_pair_xi_left_rp23->Write();
	gr_rp23->Write();

	proton_xi_left_single->Write();
  	proton_resolution_left_gen_single->Write();
  	proton_resolution_left_reco_single->Write();
	pair_xi_left_single->Write();
   xi_left_reco_single->Write();
   xi_left_reco_single_2->Write();
	proton_resolution_left_single_1->Write();
	proton_resolution_left_single_2->Write();
	proton_resolution_left_single_3->Write();
	proton_resolution_left_single_4->Write();
	proton_resolution_left_single_5->Write();
	proton_resolution_left_single_6->Write();
	proton_resolution_left_single_7->Write();
	diff_proton_reco_pair_xi_left_single->Write();
	ratio_proton_reco_pair_xi_left_single->Write();
	gr_left_single->Write();

	proton_xi_right_rp103->Write();
  	proton_resolution_right_gen_rp103->Write();
  	proton_resolution_right_reco_rp103->Write();
	pair_xi_right_rp103->Write();
   xi_right_reco_rp103->Write();
	proton_resolution_right_rp103_1->Write();
	proton_resolution_right_rp103_2->Write();
	proton_resolution_right_rp103_3->Write();
	proton_resolution_right_rp103_4->Write();
	proton_resolution_right_rp103_5->Write();
	proton_resolution_right_rp103_6->Write();
	proton_resolution_right_rp103_7->Write();
	diff_proton_reco_pair_xi_right_rp103->Write();
	ratio_proton_reco_pair_xi_right_rp103->Write();
	gr_rp103->Write();

	proton_xi_right_rp123->Write();
  	proton_resolution_right_gen_rp123->Write();
  	proton_resolution_right_reco_rp123->Write();
	pair_xi_right_rp123->Write();
   xi_right_reco_rp123->Write();
	proton_resolution_right_rp123_1->Write();
	proton_resolution_right_rp123_2->Write();
	proton_resolution_right_rp123_3->Write();
	proton_resolution_right_rp123_4->Write();
	proton_resolution_right_rp123_5->Write();
	proton_resolution_right_rp123_6->Write();
	proton_resolution_right_rp123_7->Write();
	diff_proton_reco_pair_xi_right_rp123->Write();
	ratio_proton_reco_pair_xi_right_rp123->Write();
	gr_rp123->Write();

	proton_xi_right_single->Write();
  	proton_resolution_right_gen_single->Write();
  	proton_resolution_right_reco_single->Write();
	pair_xi_right_single->Write();
   xi_right_reco_single->Write();
   xi_right_reco_single_2->Write();
	proton_resolution_right_single_1->Write();
	proton_resolution_right_single_2->Write();
	proton_resolution_right_single_3->Write();
	proton_resolution_right_single_4->Write();
	proton_resolution_right_single_5->Write();
	proton_resolution_right_single_6->Write();
	proton_resolution_right_single_7->Write();
	diff_proton_reco_pair_xi_right_single->Write();
	ratio_proton_reco_pair_xi_right_single->Write();
	gr_right_single->Write();

	proton_xi_left_multi->Write();
  	proton_resolution_left_gen_multi->Write();
  	proton_resolution_left_reco_multi->Write();
	pair_xi_left_multi->Write();
   xi_left_reco_multi->Write();
	proton_resolution_left_multi_1->Write();
	proton_resolution_left_multi_2->Write();
	proton_resolution_left_multi_3->Write();
	proton_resolution_left_multi_4->Write();
	proton_resolution_left_multi_5->Write();
	proton_resolution_left_multi_6->Write();
	proton_resolution_left_multi_7->Write();
	diff_proton_reco_pair_xi_left_multi->Write();
	ratio_proton_reco_pair_xi_left_multi->Write();
	gr_left_multi->Write();

	proton_xi_right_multi->Write();
  	proton_resolution_right_gen_multi->Write();
  	proton_resolution_right_reco_multi->Write();
	pair_xi_right_multi->Write();
   xi_right_reco_multi->Write();
	proton_resolution_right_multi_1->Write();
	proton_resolution_right_multi_2->Write();
	proton_resolution_right_multi_3->Write();
	proton_resolution_right_multi_4->Write();
	proton_resolution_right_multi_5->Write();
	proton_resolution_right_multi_6->Write();
	proton_resolution_right_multi_7->Write();
	diff_proton_reco_pair_xi_right_multi->Write();
	ratio_proton_reco_pair_xi_right_multi->Write();
	gr_right_multi->Write();

	xi_pair_resolution_left->Write();
	xi_pair_resolution_right->Write();

	f->Close();

	//cout << "oi" <<endl;
}
	
int run(std::string fileName="input.root") {
	ntp1 m(fileName);
 	m.Loop();

 	return 0;
 	}
