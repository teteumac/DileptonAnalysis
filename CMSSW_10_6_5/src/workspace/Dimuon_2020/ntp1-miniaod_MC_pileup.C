#define ntp1_cxx
#include "ntp1_pileup.h"
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
#include <TRandom3.h>
#include <TF1.h>
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

   bool match = false;
   unsigned int n_sigmas_xi = 2.;
   const int nbins_left = 5;
   double bins_left[nbins_left+1] = {0, 0.02, 0.035, 0.05, 0.1, 0.16};
   const int nbins_right = 4;
   double bins_right[nbins_right+1] = {0, 0.03, 0.05, 0.1, 0.16};
   const int nbons = 55;
   double bons[nbons+1] = {0,1,2,3,4,5,6,7,8,9,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100};

   TH1::SetDefaultSumw2( true );

   TH1D *h_PrimVertex_z = new TH1D("h_PrimVertex_z", "PrimVertexCand_z", 100, -25, 25);
   TH1D *h_PrimVertex_dif_muon1 = new TH1D("h_PrimVertex_dif_muon1", "PrimVertexCand_dif_muon1", 100, -0.1, 0.1);
   TH1D *h_PrimVertex_dif_muon2 = new TH1D("h_PrimVertex_dif_muon2", "PrimVertexCand_dif_muon2", 100, -0.1, 0.1);
   TH1D *h_acoplanarity = new TH1D("h_acoplanarity", "Acoplanarity", 200, 0, 0.01);
   TH1D *h_deltaphi = new TH1D("h_deltaphi", "Delta #phi", 100, -3.5, 3.5);
   TH1D *PrimVertex_ndof = new TH1D("PrimVertex_ndof", "PrimVertexCand_ndof", 200, 0, 200);
   TH1D *PrimVertex_chi2 = new TH1D("PrimVertex_chi2", "PrimVertexCand_chi2", 100, 0, 200);
   TH1D *mumu_mass = new TH1D("mumu_mass", "#mu^{+}#mu^{-} Mass", 20, 0, 600);
   TH1D *mumu_pt = new TH1D("mumu_pt", "#mu^{+}#mu^{-} p_{T}", 20, 0, 25);
   TH1D *mumu_y = new TH1D("mumu_y", "#mu^{+}#mu^{-} y", 20, -3, 3);
   TH1D *n_fromPV_3_signal = new TH1D("n_fromPV_3_signal", "n from PV 3", 50, 0, 100);
   TH1D *n_fromPV_3_bkg = new TH1D("n_fromPV_3_bkg", "n from PV 3", 50, 0, 100);

   TH1D *n_fromPV = new TH1D("n_fromPV", "n from PV", 50, 0, 100);
   TH1D *n_fromPV_2 = new TH1D("n_fromPV_2", "n from PV 2", 50, 0, 100);
   TH1D *n_fromPV_3 = new TH1D("n_fromPV_3", "n from PV 3", 50, 0, 100);
   TH1D *n_ext_fromPV = new TH1D("n_ext_fromPV", "n extra from PV", 50, 0, 100);
   TH1D *n_ext_fromPV_2 = new TH1D("n_ext_fromPV_2", "n extra from PV 2", 50, 0, 100);
   TH1D *n_ext_fromPV_3 = new TH1D("n_ext_fromPV_3", "n extra from PV 3", 50, 0, 100);
   TH1D *n_fromPV_dz02 = new TH1D("n_fromPV_dz02", "n from PV with dz < 0.2", 50, 0, 100);
   TH1D *n_fromPV_2_dz02 = new TH1D("n_fromPV_2_dz02", "n from PV 2 with dz < 0.2", 50, 0, 100);
   TH1D *n_fromPV_3_dz02 = new TH1D("n_fromPV_3_dz02", "n from PV 3 with dz < 0.2", 50, 0, 100);
   TH1D *n_ext_fromPV_dz02 = new TH1D("n_ext_fromPV_dz02", "n extra from PV with dz < 0.2", 50, 0, 100);
   TH1D *n_ext_fromPV_2_dz02 = new TH1D("n_ext_fromPV_2_dz02", "n extra from PV 2 with dz < 0.2", 50, 0, 100);
   TH1D *n_ext_fromPV_3_dz02 = new TH1D("n_ext_fromPV_3_dz02", "n extra from PV 3 with dz < 0.2", 50, 0, 100);
   TH1D *n_fromPV_dz01 = new TH1D("n_fromPV_dz01", "n from PV with dz < 0.1", 50, 0, 100);
   TH1D *n_fromPV_2_dz01 = new TH1D("n_fromPV_2_dz01", "n from PV 2 with dz < 0.1", 50, 0, 100);
   TH1D *n_fromPV_3_dz01 = new TH1D("n_fromPV_3_dz01", "n from PV 3 with dz < 0.1", 50, 0, 100);
   TH1D *n_ext_fromPV_dz01 = new TH1D("n_ext_fromPV_dz01", "n extra from PV with dz < 0.1", 50, 0, 100);
   TH1D *n_ext_fromPV_2_dz01 = new TH1D("n_ext_fromPV_2_dz01", "n extra from PV 2 with dz < 0.1", 50, 0, 100);
   TH1D *n_ext_fromPV_3_dz01 = new TH1D("n_ext_fromPV_3_dz01", "n extra from PV 3 with dz < 0.1", 50, 0, 100);
   TH1D *mu1_z_mu2_z = new TH1D("mu1_z_mu2_z", "#mu^{+} z - #mu^{-} z", 1000, -.02, .02);
   TH1D *mu1_z_primvertex_z = new TH1D("mu1_z_primevertex_z", "#mu 1 z - primary vertex z", 1000, -.02, .02);
   TH1D *mu2_z_primvertex_z = new TH1D("mu2_z_primevertex_z", "#mu 2 z - primary vertex z", 1000, -.02, .02);

   ////////////////////////////////////////////////////////////////////////////PROTON//////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////LEFT STRIPS//////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   TH1D *proton_xi_left_rp3 = new TH1D("proton_xi_left_rp3", "#xi Proton Left - RP 3", 10, 0, 0.16);
   TH1D *proton_xi_left_rp3_match = new TH1D("proton_xi_left_rp3_match", "#xi Proton Left - Matching Events - RP 3", nbins_left, bins_left);
   TH1D *pair_xi_left_rp3 = new TH1D("pair_xi_left_rp3", "#xi Pair Left - RP 3", 10, 0, 0.16);
   TH2D *xi_left_reco_rp3 = new TH2D("xi_left_reco_rp3", "#xi Left Correlation - RP 3", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_rp3 = new TGraph();
   g_xi_left_reco_rp3->SetName("g_xi_left_reco_rp3");
   g_xi_left_reco_rp3->SetTitle("#xi Left Correlation - RP 3");
   TH2D *xi_left_reco_rp3_match = new TH2D("xi_left_reco_rp3_match", "#xi Left Correlation - Matching Events - RP 3", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_rp3_match = new TGraph(); 
   g_xi_left_reco_rp3_match->SetName("g_xi_left_reco_rp3_match");
   g_xi_left_reco_rp3_match->SetTitle("#xi Left Correlation - Matching Events - RP 3");
   TH2D *xi_left_reco_rp3_non_match = new TH2D("xi_left_reco_rp3_non_match", "#xi Left Correlation - Non-Matching Events - RP 3", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_rp3_non_match = new TGraph(); 
   g_xi_left_reco_rp3_non_match->SetName("g_xi_left_reco_rp3_non_match");
   g_xi_left_reco_rp3_non_match->SetTitle("#xi Left Correlation - Non-Matching Events - RP 3");
   TH1D *diff_proton_reco_pair_xi_left_rp3 = new TH1D("diff_proton_reco_pair_xi_left_rp3", "reco (Proton - Pair) #xi Left - RP 3", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_left_rp3 = new TH1D("ratio_proton_reco_pair_xi_left_rp3", "reco (1 - Proton/Pair) #xi Left - RP 3", 10, -20, 3);
   TH1D *diff_proton_reco_pair_xi_left_rp3_match = new TH1D("diff_proton_reco_pair_xi_left_rp3_match", "reco (Proton - Pair) #xi Left - Matching Events - RP 3", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_left_rp3_match = new TH1D("ratio_proton_reco_pair_xi_left_rp3_match", "reco (1 - Proton/Pair) #xi Left - Matching Events - RP 3", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////LEFT PIXEL///////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //1 proton
   TH1D *mumu_mass_rp23 = new TH1D("mumu_mass_rp23", "#mu^{+}#mu^{-} Mass - RP 23", 20, 0, 600);
   TH1D *mumu_pt_rp23 = new TH1D("mumu_pt_rp23", "#mu^{+}#mu^{-} p_{T} - RP 23", 20, 0, 25);
   TH1D *mumu_y_rp23 = new TH1D("mumu_y_rp23", "#mu^{+}#mu^{-} y - RP 23", 20, -3, 3);
   TH1D *mumu_mass_rp23_match = new TH1D("mumu_mass_rp23_match", "#mu^{+}#mu^{-} Mass - Matching Events - RP 23", 20, 0, 600);
   TH1D *mumu_pt_rp23_match = new TH1D("mumu_pt_rp23_match", "#mu^{+}#mu^{-} p_{T} - Matching Events - RP 23", 20, 0, 25);
   TH1D *mumu_y_rp23_match = new TH1D("mumu_y_rp23_match", "#mu^{+}#mu^{-} y - Matching Events - RP 23", 20, -3, 3);
   TH1D *proton_xi_left_rp23 = new TH1D("proton_xi_left_rp23", "#xi Proton Left - RP 23", 10, 0, 0.16);
   TH1D *proton_xi_left_rp23_match = new TH1D("proton_xi_left_rp23_match", "#xi Proton Left - Matching Events - RP 23", nbins_left, bins_left);
   TH1D *pair_xi_left_rp23 = new TH1D("pair_xi_left_rp23", "#xi Pair Left - RP 23", 10, 0, 0.16);
   TH1D *pair_xi_left_rp23_match = new TH1D("pair_xi_left_rp23_match", "#xi Pair Left - Matching Events - RP 23", 10, 0, 0.16);
   TH2D *xi_left_reco_rp23 = new TH2D("xi_left_reco_rp23", "#xi Left Correlation - RP 23", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_rp23 = new TGraph(); 
   g_xi_left_reco_rp23->SetName("g_xi_left_reco_rp23");
   g_xi_left_reco_rp23->SetTitle("#xi Left Correlation - RP 23");
   TH2D *xi_left_reco_rp23_match = new TH2D("xi_left_reco_rp23_match", "#xi Left Correlation - Matching Events - RP 23", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_rp23_match = new TGraph(); 
   g_xi_left_reco_rp23_match->SetName("g_xi_left_reco_rp23_match");
   g_xi_left_reco_rp23_match->SetTitle("#xi Left Correlation - Matching Events - RP 23");
   TH2D *xi_left_reco_rp23_non_match = new TH2D("xi_left_reco_rp23_non_match", "#xi Left Correlation - Non-Matching Events - RP 23", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_rp23_non_match = new TGraph(); 
   g_xi_left_reco_rp23_non_match->SetName("g_xi_left_reco_rp23_non_match");
   g_xi_left_reco_rp23_non_match->SetTitle("#xi Left Correlation - Non-Matching Events - RP 23");
   TH1D *diff_proton_reco_pair_xi_left_rp23 = new TH1D("diff_proton_reco_pair_xi_left_rp23", "reco (Proton - Pair) #xi Left - RP 23", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_left_rp23 = new TH1D("ratio_proton_reco_pair_xi_left_rp23", "reco (1 - Proton/Pair) #xi Left - RP 23", 10, -20, 3);
   TH1D *diff_proton_reco_pair_xi_left_rp23_match = new TH1D("diff_proton_reco_pair_xi_left_rp23_match", "reco (Proton - Pair) #xi Left - Matching Events - RP 23", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_left_rp23_match = new TH1D("ratio_proton_reco_pair_xi_left_rp23_match", "reco (1 - Proton/Pair) #xi Left - Matching Events - RP 23", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //n protons
   TH1D *proton_xi_left_rp23_nprot = new TH1D("proton_xi_left_rp23_nprot", "#xi Proton Left - RP 23", 10, 0, 0.16);
   TH1D *proton_xi_left_rp23_nprot_match = new TH1D("proton_xi_left_rp23_nprot_match", "#xi Proton Left - Matching Events - RP 23", nbins_left, bins_left);
   TH1D *pair_xi_left_rp23_nprot = new TH1D("pair_xi_left_nprot_rp23", "#xi Pair Left - RP 23", 10, 0, 0.16);
   TH1D *pair_xi_left_rp23_nprot_match = new TH1D("pair_xi_left_rp23_nprot_match", "#xi Pair Left - Matching Events - RP 23", 10, 0, 0.16);
   TH2D *xi_left_reco_rp23_nprot = new TH2D("xi_left_reco_rp23_nprot", "#xi Left Correlation - RP 23", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_rp23_nprot = new TGraph(); 
   g_xi_left_reco_rp23_nprot->SetName("g_xi_left_reco_rp23_nprot");
   g_xi_left_reco_rp23_nprot->SetTitle("#xi Left Correlation - RP 23");
   TH2D *xi_left_reco_rp23_nprot_match = new TH2D("xi_left_reco_rp23_nprot_match", "#xi Left Correlation - Matching Events - RP 23", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_rp23_nprot_match = new TGraph(); 
   g_xi_left_reco_rp23_nprot_match->SetName("g_xi_left_reco_rp23_nprot_match");
   g_xi_left_reco_rp23_nprot_match->SetTitle("#xi Left Correlation - Matching Events - RP 23");
   TH2D *xi_left_reco_rp23_nprot_non_match = new TH2D("xi_left_reco_rp23_nprot_non_match", "#xi Left Correlation - Non-Matching Events - RP 23", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_rp23_nprot_non_match = new TGraph(); 
   g_xi_left_reco_rp23_nprot_non_match->SetName("g_xi_left_reco_rp23_nprot_non_match");
   g_xi_left_reco_rp23_nprot_non_match->SetTitle("#xi Left Correlation - Non-Matching Events - RP 23");
   TH1D *diff_proton_reco_pair_xi_left_rp23_nprot = new TH1D("diff_proton_reco_pair_xi_left_rp23_nprot", "reco (Proton - Pair) #xi Left - RP 23", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_left_rp23_nprot = new TH1D("ratio_proton_reco_pair_xi_left_rp23_nprot", "reco (1 - Proton/Pair) #xi Left - RP 23", 10, -20, 3);
   TH1D *diff_proton_reco_pair_xi_left_rp23_nprot_match = new TH1D("diff_proton_reco_pair_xi_left_rp23_nprot_match", "reco (Proton - Pair) #xi Left - Matching Events - RP 23", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_left_rp23_nprot_match = new TH1D("ratio_proton_reco_pair_xi_left_rp23_nprot_match", "reco (1 - Proton/Pair) #xi Left - Matching Events - RP 23", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////LEFT STRIPS+PIXEL////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   TH1D *proton_xi_left_single = new TH1D("proton_xi_left_single", "#xi Proton Left - Single RP", 10, 0, 0.16);
   TH1D *pair_xi_left_single = new TH1D("pair_xi_left_single", "#xi Pair Left - Single RP", 10, 0, 0.16);
   TH2D *xi_left_reco_single = new TH2D("xi_left_reco_single", "#xi Left Correlation - Single RP", 20, 0, 0.16, 20, 0, 0.16); 	
   TGraph *g_xi_left_reco_single = new TGraph(); 
   g_xi_left_reco_single->SetName("g_xi_left_reco_single");
   g_xi_left_reco_single->SetTitle("#xi Left Correlation - Single RP");
   TH2D *xi_left_reco_single_match = new TH2D("xi_left_reco_single_match", "#xi Left Correlation - Matching Events - Single RP", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_single_match = new TGraph(); 
   g_xi_left_reco_single_match->SetName("g_xi_left_reco_single_match");
   g_xi_left_reco_single_match->SetTitle("#xi Left Correlation - Matching Events - Single RP");
   TH2D *xi_left_reco_single_non_match = new TH2D("xi_left_reco_single_non_match", "#xi Left Correlation - Non-Matching Events - Single RP", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_single_non_match = new TGraph(); 
   g_xi_left_reco_single_non_match->SetName("g_xi_left_reco_single_non_match");
   g_xi_left_reco_single_non_match->SetTitle("#xi Left Correlation - Non-Matching Events - Single RP");
   TH1D *diff_proton_reco_pair_xi_left_single = new TH1D("diff_proton_reco_pair_xi_left_single", "reco (Proton - Pair) #xi Left - Single", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_left_single = new TH1D("ratio_proton_reco_pair_xi_left_single", "reco (1 - reco Proton/Pair) #xi Left - Single", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////RIGHT STRIPS//////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   TH1D *proton_xi_right_rp103 = new TH1D("proton_xi_right_rp103", "#xi Proton Right - RP 103", 10, 0, 0.16);
   TH1D *proton_xi_right_rp103_match = new TH1D("proton_xi_right_rp103_match", "#xi Proton Right - Matching Events - RP 103", nbins_right, bins_right);
   TH1D *pair_xi_right_rp103 = new TH1D("pair_xi_right_rp103", "#xi Pair Right - RP 103", 10, 0, 0.16);
   TH2D *xi_right_reco_rp103 = new TH2D("xi_right_reco_rp103", "#xi Right Correlation - RP 103", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_rp103 = new TGraph();
   g_xi_right_reco_rp103->SetName("g_xi_right_reco_rp103");
   g_xi_right_reco_rp103->SetTitle("#xi Right Correlation - RP 103");
   TH2D *xi_right_reco_rp103_match = new TH2D("xi_right_reco_rp103_match", "#xi Right Correlation - Matching Events - RP 103", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_rp103_match = new TGraph(); 
   g_xi_right_reco_rp103_match->SetName("g_xi_right_reco_rp103_match");
   g_xi_right_reco_rp103_match->SetTitle("#xi Right Correlation - Matching Events - RP 103");
   TH2D *xi_right_reco_rp103_non_match = new TH2D("xi_right_reco_rp103_non_match", "#xi Right Correlation - Non-Matching Events - RP 103", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_rp103_non_match = new TGraph(); 
   g_xi_right_reco_rp103_non_match->SetName("g_xi_right_reco_rp103_non_match");
   g_xi_right_reco_rp103_non_match->SetTitle("#xi Right Correlation - Non-Matching Events - RP 103");
   TH1D *diff_proton_reco_pair_xi_right_rp103 = new TH1D("diff_proton_reco_pair_xi_right_rp103", "reco (Proton - Pair) #xi Right - RP 103", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_right_rp103 = new TH1D("ratio_proton_reco_pair_xi_right_rp103", "reco (1 - Proton/Pair) #xi Right - RP 103", 10, -20, 103);
   TH1D *diff_proton_reco_pair_xi_right_rp103_match = new TH1D("diff_proton_reco_pair_xi_right_rp103_match", "reco (Proton - Pair) #xi Right - Matching Events - RP 103", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_right_rp103_match = new TH1D("ratio_proton_reco_pair_xi_right_rp103_match", "reco (1 - Proton/Pair) #xi Right - Matching Events - RP 103", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////RIGHT PIXEL///////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //1 proton
   TH1D *mumu_mass_rp123 = new TH1D("mumu_mass_rp123", "#mu^{+}#mu^{-} Mass - RP 123", 20, 0, 600);
   TH1D *mumu_pt_rp123 = new TH1D("mumu_pt_rp123", "#mu^{+}#mu^{-} p_{T} - RP 123", 20, 0, 25);
   TH1D *mumu_y_rp123 = new TH1D("mumu_y_rp123", "#mu^{+}#mu^{-} y - RP 123", 20, -3, 3);
   TH1D *mumu_mass_rp123_match = new TH1D("mumu_mass_rp123_match", "#mu^{+}#mu^{-} Mass - Matching Events - RP 123", 20, 0, 600);
   TH1D *mumu_pt_rp123_match = new TH1D("mumu_pt_rp123_match", "#mu^{+}#mu^{-} p_{T} - Matching Events - RP 123", 20, 0, 25);
   TH1D *mumu_y_rp123_match = new TH1D("mumu_y_rp123_match", "#mu^{+}#mu^{-} y - Matching Events - RP 123", 20, -3, 3);
   TH1D *proton_xi_right_rp123 = new TH1D("proton_xi_right_rp123", "#xi Proton Right - RP 123", 10, 0, 0.16);
   TH1D *proton_xi_right_rp123_match = new TH1D("proton_xi_right_rp123_match", "#xi Proton Right - Matching Events - RP 123", nbins_right, bins_right);
   TH1D *pair_xi_right_rp123 = new TH1D("pair_xi_right_rp123", "#xi Pair Right - RP 123", 10, 0, 0.16);
   TH1D *pair_xi_right_rp123_match = new TH1D("pair_xi_right_rp123_match", "#xi Pair Right - Matching Events - RP 123", 10, 0, 0.16);
   TH2D *xi_right_reco_rp123 = new TH2D("xi_right_reco_rp123", "#xi Right Correlation - RP 123", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_rp123 = new TGraph(); 
   g_xi_right_reco_rp123->SetName("g_xi_right_reco_rp123");
   g_xi_right_reco_rp123->SetTitle("#xi Right Correlation - RP 123");
   TH2D *xi_right_reco_rp123_match = new TH2D("xi_right_reco_rp123_match", "#xi Right Correlation - Matching Events - RP 123", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_rp123_match = new TGraph(); 
   g_xi_right_reco_rp123_match->SetName("g_xi_right_reco_rp123_match");
   g_xi_right_reco_rp123_match->SetTitle("#xi Right Correlation - Matching Events - RP 123");
   TH2D *xi_right_reco_rp123_non_match = new TH2D("xi_right_reco_rp123_non_match", "#xi Right Correlation - Non-Matching Events - RP 123", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_rp123_non_match = new TGraph(); 
   g_xi_right_reco_rp123_non_match->SetName("g_xi_right_reco_rp123_non_match");
   g_xi_right_reco_rp123_non_match->SetTitle("#xi Right Correlation - Non-Matching Events - RP 123");
   TH1D *diff_proton_reco_pair_xi_right_rp123 = new TH1D("diff_proton_reco_pair_xi_right_rp123", "reco (Proton - Pair) #xi Right - RP 123", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_right_rp123 = new TH1D("ratio_proton_reco_pair_xi_right_rp123", "reco (1 - Proton/Pair) #xi Right - RP 123", 10, -20, 3);
   TH1D *diff_proton_reco_pair_xi_right_rp123_match = new TH1D("diff_proton_reco_pair_xi_right_rp123_match", "reco (Proton - Pair) #xi Right - Matching Events - RP 123", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_right_rp123_match = new TH1D("ratio_proton_reco_pair_xi_right_rp123_match", "reco (1 - Proton/Pair) #xi Right - Matching Events - RP 123", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //n protons
   TH1D *proton_xi_right_rp123_nprot = new TH1D("proton_xi_right_rp123_nprot", "#xi Proton Right - RP 123", 10, 0, 0.16);
   TH1D *proton_xi_right_rp123_nprot_match = new TH1D("proton_xi_right_rp123_nprot_match", "#xi Proton Right - Matching Events - RP 123", nbins_right, bins_right);
   TH1D *pair_xi_right_rp123_nprot = new TH1D("pair_xi_right_nprot_rp123", "#xi Pair Right - RP 123", 10, 0, 0.16);
   TH1D *pair_xi_right_rp123_nprot_match = new TH1D("pair_xi_right_rp123_nprot_match", "#xi Pair Right - Matching Events - RP 123", 10, 0, 0.16);
   TH2D *xi_right_reco_rp123_nprot = new TH2D("xi_right_reco_rp123_nprot", "#xi Right Correlation - RP 123", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_rp123_nprot = new TGraph(); 
   g_xi_right_reco_rp123_nprot->SetName("g_xi_right_reco_rp123_nprot");
   g_xi_right_reco_rp123_nprot->SetTitle("#xi Right Correlation - RP 123");
   TH2D *xi_right_reco_rp123_nprot_match = new TH2D("xi_right_reco_rp123_nprot_match", "#xi Right Correlation - Matching Events - RP 123", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_rp123_nprot_match = new TGraph(); 
   g_xi_right_reco_rp123_nprot_match->SetName("g_xi_right_reco_rp123_nprot_match");
   g_xi_right_reco_rp123_nprot_match->SetTitle("#xi Right Correlation - Matching Events - RP 123");
   TH2D *xi_right_reco_rp123_nprot_non_match = new TH2D("xi_right_reco_rp123_nprot_non_match", "#xi Right Correlation - Non-Matching Events - RP 123", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_rp123_nprot_non_match = new TGraph(); 
   g_xi_right_reco_rp123_nprot_non_match->SetName("g_xi_right_reco_rp123_nprot_non_match");
   g_xi_right_reco_rp123_nprot_non_match->SetTitle("#xi Right Correlation - Non-Matching Events - RP 123");
   TH1D *diff_proton_reco_pair_xi_right_rp123_nprot = new TH1D("diff_proton_reco_pair_xi_right_rp123_nprot", "reco (Proton - Pair) #xi Right - RP 123", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_right_rp123_nprot = new TH1D("ratio_proton_reco_pair_xi_right_rp123_nprot", "reco (1 - Proton/Pair) #xi Right - RP 123", 10, -20, 3);
   TH1D *diff_proton_reco_pair_xi_right_rp123_nprot_match = new TH1D("diff_proton_reco_pair_xi_right_rp123_nprot_match", "reco (Proton - Pair) #xi Right - Matching Events - RP 123", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_right_rp123_nprot_match = new TH1D("ratio_proton_reco_pair_xi_right_rp123_nprot_match", "reco (1 - Proton/Pair) #xi Right - Matching Events - RP 123", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////RIGHT STRIPS+PIXEL////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   TH1D *proton_xi_right_single = new TH1D("proton_xi_right_single", "#xi Proton Right - Single RP", 10, 0, 0.16);
   TH1D *pair_xi_right_single = new TH1D("pair_xi_right_single", "#xi Pair Right - Single RP", 10, 0, 0.16);
   TH2D *xi_right_reco_single = new TH2D("xi_right_reco_single", "#xi Right Correlation - Single RP", 20, 0, 0.16, 20, 0, 0.16); 	
   TGraph *g_xi_right_reco_single = new TGraph(); 
   g_xi_right_reco_single->SetName("g_xi_right_reco_single");
   g_xi_right_reco_single->SetTitle("#xi Right Correlation - Single RP");
   TH2D *xi_right_reco_single_match = new TH2D("xi_right_reco_single_match", "#xi Right Correlation - Matching Events - Single RP", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_single_match = new TGraph(); 
   g_xi_right_reco_single_match->SetName("g_xi_right_reco_single_match");
   g_xi_right_reco_single_match->SetTitle("#xi Right Correlation - Matching Events - Single RP");
   TH2D *xi_right_reco_single_non_match = new TH2D("xi_right_reco_single_non_match", "#xi Right Correlation - Non-Matching Events - Single RP", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_single_non_match = new TGraph(); 
   g_xi_right_reco_single_non_match->SetName("g_xi_right_reco_single_non_match");
   g_xi_right_reco_single_non_match->SetTitle("#xi Right Correlation - Non-Matching Events - Single RP");
   TH1D *diff_proton_reco_pair_xi_right_single = new TH1D("diff_proton_reco_pair_xi_right_single", "reco (Proton - Pair) #xi Right - Single", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_right_single = new TH1D("ratio_proton_reco_pair_xi_right_single", "reco (1 - reco Proton/Pair) #xi Right - Single", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////LEFT MULTI///////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   TH1D *proton_xi_left_multi = new TH1D("proton_xi_left_multi", "#xi Proton Left - Multi RP", 10, 0, 0.16);
   TH1D *proton_xi_left_multi_match = new TH1D("proton_xi_left_multi_match", "#xi Proton Left - Matching Events - Multi RP", nbins_left, bins_left);
   TH1D *pair_xi_left_multi = new TH1D("pair_xi_left_multi", "#xi Pair Left - Multi RP", 10, 0, 0.16);
   TH2D *xi_left_reco_multi = new TH2D("xi_left_reco_multi", "#xi Left Correlation - Multi RP", 20, 0, 0.16, 20, 0, 0.16); 	
   TGraph *g_xi_left_reco_multi = new TGraph(); 
   g_xi_left_reco_multi->SetName("g_xi_left_reco_multi");
   g_xi_left_reco_multi->SetTitle("#xi Left Correlation - Multi RP");
   TH2D *xi_left_reco_multi_match = new TH2D("xi_left_reco_multi_match", "#xi Left Correlation - Matching Events - Multi RP", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_multi_match = new TGraph(); 
   g_xi_left_reco_multi_match->SetName("g_xi_left_reco_multi_match");
   g_xi_left_reco_multi_match->SetTitle("#xi Left Correlation - Matching Events - Multi RP");
   TH2D *xi_left_reco_multi_non_match = new TH2D("xi_left_reco_multi_non_match", "#xi Left Correlation - Non-Matching Events - Multi RP", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_multi_non_match = new TGraph(); 
   g_xi_left_reco_multi_non_match->SetName("g_xi_left_reco_multi_non_match");
   g_xi_left_reco_multi_non_match->SetTitle("#xi Left Correlation - Non-Matching Events - Multi RP");
   TH1D *diff_proton_reco_pair_xi_left_multi = new TH1D("diff_proton_reco_pair_xi_left_multi", "reco (Proton - Pair) #xi Left - Multi", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_left_multi = new TH1D("ratio_proton_reco_pair_xi_left_multi", "reco (1 - Proton/Pair) #xi Left - Multi", 10, -20, 3);
   TH1D *diff_proton_reco_pair_xi_left_multi_match = new TH1D("diff_proton_reco_pair_xi_left_multi_match", "reco (Proton - Pair) #xi Left - Matching Events - Multi", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_left_multi_match = new TH1D("ratio_proton_reco_pair_xi_left_multi_match", "reco (1 - Proton/Pair) #xi Left - Matching Events - Multi", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////RIGHT MULTI///////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   TH1D *proton_xi_right_multi = new TH1D("proton_xi_right_multi", "#xi Proton Right - Multi RP", 10, 0, 0.16);
   TH1D *proton_xi_right_multi_match = new TH1D("proton_xi_right_multi_match", "#xi Proton Right - Matching Events - Multi RP", nbins_right, bins_right);
   TH1D *pair_xi_right_multi = new TH1D("pair_xi_right_multi", "#xi Pair Right - Multi RP", 10, 0, 0.16);
   TH2D *xi_right_reco_multi = new TH2D("xi_right_reco_multi", "#xi Right Correlation - Multi RP", 20, 0, 0.16, 20, 0, 0.16); 	
   TGraph *g_xi_right_reco_multi = new TGraph(); 
   g_xi_right_reco_multi->SetName("g_xi_right_reco_multi");
   g_xi_right_reco_multi->SetTitle("#xi Right Correlation - Multi RP");
   TH2D *xi_right_reco_multi_match = new TH2D("xi_right_reco_multi_match", "#xi Right Correlation - Matching Events - Multi RP", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_multi_match = new TGraph(); 
   g_xi_right_reco_multi_match->SetName("g_xi_right_reco_multi_match");
   g_xi_right_reco_multi_match->SetTitle("#xi Right Correlation - Matching Events - Multi RP");
   TH2D *xi_right_reco_multi_non_match = new TH2D("xi_right_reco_multi_non_match", "#xi Right Correlation - Non-Matching Events - Multi RP", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_multi_non_match = new TGraph(); 
   g_xi_right_reco_multi_non_match->SetName("g_xi_right_reco_multi_non_match");
   g_xi_right_reco_multi_non_match->SetTitle("#xi Right Correlation - Non-Matching Events - Multi RP");
   TH1D *diff_proton_reco_pair_xi_right_multi = new TH1D("diff_proton_reco_pair_xi_right_multi", "reco (Proton - Pair) #xi Right - Multi", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_right_multi = new TH1D("ratio_proton_reco_pair_xi_right_multi", "reco (1 - Proton/Pair) #xi Right - Multi", 10, -20, 3);
   TH1D *diff_proton_reco_pair_xi_right_multi_match = new TH1D("diff_proton_reco_pair_xi_right_multi_match", "reco (Proton - Pair) #xi Right - Matching Events - Multi", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_right_multi_match = new TH1D("ratio_proton_reco_pair_xi_right_multi_match", "reco (1 - Proton/Pair) #xi Right - Matching Events - Multi", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   TH1D *multiplicity_0prot = new TH1D("multiplicity_0prot", "Track Multiplicity 0 proton", 50, 0, 100);
   TH1D *multiplicity_0prot_pt = new TH1D("multiplicity_0prot_pt", "Track Multiplicity 0 proton - corte p_{T}", 50, 0, 100);
   //TH1D *multiplicity_0prot_cut = new TH1D("multiplicity_0prot_cut", "Track Multiplicity 0 proton - cortes", nbons, bons);
   TH1D *multiplicity_0prot_cut = new TH1D("multiplicity_0prot_cut", "Track Multiplicity 0 proton - cortes", 50, 0, 100);
   TH1D *multiplicity_cut = new TH1D("multiplicity_cut", "Track Multiplicity - cortes", 50, 0, 100);
   TH1D *cut_flow = new TH1D("cut_flow", "Cut Flow", 9, 0, 9);
   TH1D *cut_match = new TH1D("cut_match", "Cut Match", 8, 0, 8);

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   TFile *sf_ID_BC = new TFile("/mnt/hadoop/cms/store/user/malvesga/efficiencies/RunBC_SF_ID.root");
   TH2F *sf_tight_ID_BC = (TH2F*)sf_ID_BC->Get("NUM_TightID_DEN_genTracks");

   TFile *sf_ID_DE = new TFile("/mnt/hadoop/cms/store/user/malvesga/efficiencies/RunDE_SF_ID.root");
   TH2F *sf_tight_ID_DE = (TH2F*)sf_ID_DE->Get("NUM_TightID_DEN_genTracks");

   TFile *sf_ID_F = new TFile("/mnt/hadoop/cms/store/user/malvesga/efficiencies/RunF_SF_ID.root");
   TH2F *sf_tight_ID_F = (TH2F*)sf_ID_F->Get("NUM_TightID_DEN_genTracks");
   /*
      TFile *sf_ISO_BC = new TFile("/mnt/hadoop/cms/store/user/malvesga/efficiencies/RunBC_SF_ISO.root");
      TH2F *sf_tight_ISO_BC = (TH2F*)sf_ISO_BC->Get("NUM_TightRelIso_DEN_TightIDandIPCut");

      TFile *sf_ISO_DE = new TFile("/mnt/hadoop/cms/store/user/malvesga/efficiencies/RunDE_SF_ISO.root");
      TH2F *sf_tight_ISO_DE = (TH2F*)sf_ISO_DE->Get("NUM_TightRelIso_DEN_TightIDandIPCut");

      TFile *sf_ISO_F = new TFile("/mnt/hadoop/cms/store/user/malvesga/efficiencies/RunF_SF_ISO.root");
      TH2F *sf_tight_ISO_F = (TH2F*)sf_ISO_F->Get("NUM_TightRelIso_DEN_TightIDandIPCut");
      */
   TFile *input = new TFile("/mnt/hadoop/cms/store/user/malvesga/etc/pol_function.root", "READ");
   TF1 *f_rp3 = (TF1*)input->Get("f_rp3");
   TF1 *f_rp23 = (TF1*)input->Get("f_rp23");
   TF1 *f_rp23_nprot = (TF1*)input->Get("f_rp23_nprot");
   TF1 *f_left_single = (TF1*)input->Get("f_left_single");
   TF1 *f_rp103 = (TF1*)input->Get("f_rp103");
   TF1 *f_rp123 = (TF1*)input->Get("f_rp123");
   TF1 *f_rp123_nprot = (TF1*)input->Get("f_rp123_nprot");
   TF1 *f_right_single = (TF1*)input->Get("f_right_single");
   TF1 *f_left_multi = (TF1*)input->Get("f_left_multi");
   TF1 *f_right_multi = (TF1*)input->Get("f_right_multi");
   TF1 *f_pair_left = (TF1*)input->Get("f_pair_left");
   TF1 *f_pair_right = (TF1*)input->Get("f_pair_right");

   TFile *input_re = new TFile("/mnt/hadoop/cms/store/user/malvesga/etc/pol_re.root", "READ");
   TF1 *re_0prot_2 = (TF1*)input_re->Get("re_0prot_2");

   double zerocortes = 0;
   double umcortes = 0;
   double doiscortes = 0;
   double trescortes = 0;
   double quatrocortes = 0;
   double cincocortes = 0;
   double seiscortes = 0;
   double setecortes = 0;
   double oitocortes = 0;
   double corte_match_rp3 = 0;
   double corte_match_rp23_nprot = 0;
   double corte_match_rp23_1prot = 0;
   double corte_match_rp103 = 0;
   double corte_match_rp123_nprot = 0;
   double corte_match_rp123_1prot = 0;
   double corte_match_left_multi = 0;
   double corte_match_right_multi = 0;

   //double sigma_xi_mumu_left = 0.00068243; 
   //double sigma_xi_mumu_right = 0.000696733; 

   Long64_t nentries_pileup = pileup_tree->GetEntriesFast();
   std::cout << "Loaded " << nentries_pileup << " pileup events." << std::endl;

   Long64_t nentries_corr = nentries;
   std::cout << "Total number of events: " << nentries << std::endl;
   if( resample ){ 
      nentries_corr = nentries*resample_number;
      std::cout << "Total number of events (resampled): " << nentries_corr << std::endl; 
   }

   unsigned int pileup_per_bkg = ( nentries_pileup / nentries );
   unsigned int pileup_incr = 1;
   if( pileup_per_bkg > 1 ) pileup_incr = pileup_per_bkg;
   std::cout << "Pileup sample increment: " << pileup_incr << std::endl;

   Long64_t nbytes = 0, nb = 0;

   for (Long64_t jentry=0,ientry_pileup=0; jentry < nentries_corr; jentry++) {

      ientry_pileup += pileup_incr;

      Long64_t jentry_corr = ( jentry % nentries );

      Long64_t ientry = LoadTree(jentry_corr);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry_corr);   nbytes += nb;

      Long64_t ientry_pileup_corr = ( ientry_pileup % nentries_pileup );

      if( mix_pileup ){
         pileup_tree->GetEntry( ientry_pileup_corr );
      }

      // if (Cut(ientry) < 0) continue;
      double cont_prot = 0;
      //double L_B = 2.367133065;
      //double L_C1 = 5.372685500;
      //double L_D = 4.142654225;
      //double L_E = 9.061579666;
      //double L_F1 = 1.714870205;
      double L_B = 2.360904801;
      double L_C1 = 5.313012839;
      double L_E = 8.958810514;
      double L_F1 = 1.708478656;
      double ineff_1prot_rp23 = (0.448371*L_B + 0.47801142*L_C1 + 0.58999141*L_E + 0.63426072*L_F1)/(L_B+L_C1+L_E+L_F1);
      double ineff_1prot_rp123 = (0.335561*L_B + 0.35748955*L_C1 + 0.47780778*L_E + 0.42991661*L_F1)/(L_B+L_C1+L_E+L_F1);
      double eff_1prot_rp23 = 1 - ineff_1prot_rp23;
      double eff_1prot_rp123 = 1 - ineff_1prot_rp123;
      double single_left_xi = -999;
      double single_left_trackx1 = -999;
      double single_left_tracky1 = -999;
      double single_left_trackx2 = -999;
      double single_left_tracky2 = -999;
      double single_rp23_xi = -999;
      double single_rp23_trackx1 = -999;
      double single_rp23_tracky1 = -999;
      double single_rp23_trackx2 = -999;
      double single_rp23_tracky2 = -999;
      double single_rp3_xi = -999;
      double single_rp3_trackx1 = -999;
      double single_rp3_tracky1 = -999;
      double single_rp3_trackx2 = -999;
      double single_rp3_tracky2 = -999;
      double cont_single_rp23 = 0;
      double single_right_xi = -999;
      double single_right_trackx1 = -999;
      double single_right_tracky1 = -999;
      double single_right_trackx2 = -999;
      double single_right_tracky2 = -999;
      double single_rp103_xi = -999;
      double single_rp103_trackx1 = -999;
      double single_rp103_tracky1 = -999;
      double single_rp103_trackx2 = -999;
      double single_rp103_tracky2 = -999;
      double single_rp123_xi = -999;
      double single_rp123_trackx1 = -999;
      double single_rp123_tracky1 = -999;
      double single_rp123_trackx2 = -999;
      double single_rp123_tracky2 = -999;
      double cont_single_rp123 = 0;
      int contador_xangle = 0;
      int contador_PV = 0, contador_PV2 = 0, contador_PV3 = 0, contador_PV3_bkg = 0, contador_ext_PV = 0, contador_ext_PV2 = 0, contador_ext_PV3 = 0;
      int contador_PV_dz02 = 0, contador_PV2_dz02 = 0, contador_PV3_dz02 = 0, contador_ext_PV_dz02 = 0, contador_ext_PV2_dz02 = 0, contador_ext_PV3_dz02 = 0;
      int contador_PV_dz01 = 0, contador_PV2_dz01 = 0, contador_PV3_dz01 = 0, contador_ext_PV_dz01 = 0, contador_ext_PV2_dz01 = 0, contador_ext_PV3_dz01 = 0;
      double xi_pair_left_reco = (1./13000) * ( MuonCand_pt[0]*exp( MuonCand_eta[0] ) + MuonCand_pt[1]*exp( MuonCand_eta[1] ) );
      double xi_pair_right_reco = (1./13000) * ( MuonCand_pt[0]*exp( -MuonCand_eta[0] ) + MuonCand_pt[1]*exp( -MuonCand_eta[1] ) );
      double xi_pair_left_gen = (1./13000) * ( GenMuonCand_pt[0]*exp( GenMuonCand_eta[0] ) + GenMuonCand_pt[1]*exp( GenMuonCand_eta[1] ) );
      double xi_pair_right_gen = (1./13000) * ( GenMuonCand_pt[0]*exp( -GenMuonCand_eta[0] ) + GenMuonCand_pt[1]*exp( -GenMuonCand_eta[1] ) );
      double xi_pair_diff_left = (xi_pair_left_reco - xi_pair_left_gen);
      double xi_pair_diff_right = (xi_pair_right_reco - xi_pair_right_gen);
      double xi_proton_gen_left, xi_proton_gen_right;
      double sf_tight_ID_B_0;
      double sf_tight_ID_B_1;
      double sf_tight_ID_C1_0;
      double sf_tight_ID_C1_1;
      double sf_tight_ID_E_0;
      double sf_tight_ID_E_1;
      double sf_tight_ID_F1_0;
      double sf_tight_ID_F1_1;
      /*
         double sf_tight_ISO_B_0;
         double sf_tight_ISO_B_1;
         double sf_tight_ISO_C1_0;
         double sf_tight_ISO_C1_1;
         double sf_tight_ISO_E_0;
         double sf_tight_ISO_E_1;
         double sf_tight_ISO_F1_0;
         double sf_tight_ISO_F1_1;
         */
      double reweight;

      TLorentzVector mu1;
      TLorentzVector mu2;
      TLorentzVector v;

      mu1.SetPtEtaPhiM(MuonCand_pt[0],MuonCand_eta[0],MuonCand_phi[0],0.1057);
      mu2.SetPtEtaPhiM(MuonCand_pt[1],MuonCand_eta[1],MuonCand_phi[1],0.1057);

      if ( MuonCand_pt[0]  < 120 ) {
         sf_tight_ID_B_0 = sf_tight_ID_BC->GetBinContent(sf_tight_ID_BC->FindBin(MuonCand_pt[0], fabs(MuonCand_eta[0])));
         //sf_tight_ISO_B_0 = sf_tight_ISO_BC->GetBinContent(sf_tight_ISO_BC->FindBin(MuonCand_pt[0], fabs(MuonCand_eta[0])));
      }
      else {
         sf_tight_ID_B_0 = sf_tight_ID_BC->GetBinContent(sf_tight_ID_BC->FindBin(119, fabs(MuonCand_eta[0])));
         //sf_tight_ISO_B_0 = sf_tight_ISO_BC->GetBinContent(sf_tight_ISO_BC->FindBin(119, fabs(MuonCand_eta[0])));
      }
      if ( MuonCand_pt[1]  < 120 ) {
         sf_tight_ID_B_1 = sf_tight_ID_BC->GetBinContent(sf_tight_ID_BC->FindBin(MuonCand_pt[1], fabs(MuonCand_eta[1])));
         //sf_tight_ISO_B_1 = sf_tight_ISO_BC->GetBinContent(sf_tight_ISO_BC->FindBin(MuonCand_pt[1], fabs(MuonCand_eta[1])));
      }
      else {
         sf_tight_ID_B_1 = sf_tight_ID_BC->GetBinContent(sf_tight_ID_BC->FindBin(119, fabs(MuonCand_eta[1])));
         //sf_tight_ISO_B_1 = sf_tight_ISO_BC->GetBinContent(sf_tight_ISO_BC->FindBin(119, fabs(MuonCand_eta[1])));
      }
      if ( MuonCand_pt[0]  < 120 ) {
         sf_tight_ID_C1_0 = sf_tight_ID_BC->GetBinContent(sf_tight_ID_BC->FindBin(MuonCand_pt[0], fabs(MuonCand_eta[0])));
         //sf_tight_ISO_C1_0 = sf_tight_ISO_BC->GetBinContent(sf_tight_ISO_BC->FindBin(MuonCand_pt[0], fabs(MuonCand_eta[0])));
      }
      else {
         sf_tight_ID_C1_0 = sf_tight_ID_BC->GetBinContent(sf_tight_ID_BC->FindBin(119, fabs(MuonCand_eta[0])));
         //sf_tight_ISO_C1_0 = sf_tight_ISO_BC->GetBinContent(sf_tight_ISO_BC->FindBin(119, fabs(MuonCand_eta[0])));
      }
      if ( MuonCand_pt[1]  < 120 ) {
         sf_tight_ID_C1_1 = sf_tight_ID_BC->GetBinContent(sf_tight_ID_BC->FindBin(MuonCand_pt[1], fabs(MuonCand_eta[1])));
         //sf_tight_ISO_C1_1 = sf_tight_ISO_BC->GetBinContent(sf_tight_ISO_BC->FindBin(MuonCand_pt[1], fabs(MuonCand_eta[1])));
      }
      else {
         sf_tight_ID_C1_1 = sf_tight_ID_BC->GetBinContent(sf_tight_ID_BC->FindBin(119, fabs(MuonCand_eta[1])));
         //sf_tight_ISO_C1_1 = sf_tight_ISO_BC->GetBinContent(sf_tight_ISO_BC->FindBin(119, fabs(MuonCand_eta[1])));
      }
      if ( MuonCand_pt[0]  < 120 ) {
         sf_tight_ID_E_0 = sf_tight_ID_DE->GetBinContent(sf_tight_ID_DE->FindBin(MuonCand_pt[0], fabs(MuonCand_eta[0])));
         //sf_tight_ISO_E_0 = sf_tight_ISO_DE->GetBinContent(sf_tight_ISO_DE->FindBin(MuonCand_pt[0], fabs(MuonCand_eta[0])));
      }
      else {
         sf_tight_ID_E_0 = sf_tight_ID_DE->GetBinContent(sf_tight_ID_DE->FindBin(119, fabs(MuonCand_eta[0])));
         //sf_tight_ISO_E_0 = sf_tight_ISO_DE->GetBinContent(sf_tight_ISO_DE->FindBin(119, fabs(MuonCand_eta[0])));
      }
      if ( MuonCand_pt[1]  < 120 ) {
         sf_tight_ID_E_1 = sf_tight_ID_DE->GetBinContent(sf_tight_ID_DE->FindBin(MuonCand_pt[1], fabs(MuonCand_eta[1])));
         //sf_tight_ISO_E_1 = sf_tight_ISO_DE->GetBinContent(sf_tight_ISO_DE->FindBin(MuonCand_pt[1], fabs(MuonCand_eta[1])));
      }
      else {
         sf_tight_ID_E_1 = sf_tight_ID_DE->GetBinContent(sf_tight_ID_DE->FindBin(119, fabs(MuonCand_eta[1])));
         //sf_tight_ISO_E_1 = sf_tight_ISO_DE->GetBinContent(sf_tight_ISO_DE->FindBin(119, fabs(MuonCand_eta[1])));
      }
      if ( MuonCand_pt[0]  < 120 ) {
         sf_tight_ID_F1_0 = sf_tight_ID_F->GetBinContent(sf_tight_ID_F->FindBin(MuonCand_pt[0], fabs(MuonCand_eta[0])));
         //sf_tight_ISO_F1_0 = sf_tight_ISO_F->GetBinContent(sf_tight_ISO_F->FindBin(MuonCand_pt[0], fabs(MuonCand_eta[0])));
      }
      else {
         sf_tight_ID_F1_0 = sf_tight_ID_F->GetBinContent(sf_tight_ID_F->FindBin(119, fabs(MuonCand_eta[0])));
         //sf_tight_ISO_F1_0 = sf_tight_ISO_F->GetBinContent(sf_tight_ISO_F->FindBin(119, fabs(MuonCand_eta[0])));
      }
      if ( MuonCand_pt[1]  < 120 ) {
         sf_tight_ID_F1_1 = sf_tight_ID_F->GetBinContent(sf_tight_ID_F->FindBin(MuonCand_pt[1], fabs(MuonCand_eta[1])));
         //sf_tight_ISO_F1_1 = sf_tight_ISO_F->GetBinContent(sf_tight_ISO_F->FindBin(MuonCand_pt[1], fabs(MuonCand_eta[1])));
      }
      else {
         sf_tight_ID_F1_1 = sf_tight_ID_F->GetBinContent(sf_tight_ID_F->FindBin(119, fabs(MuonCand_eta[1])));
         //sf_tight_ISO_F1_1 = sf_tight_ISO_F->GetBinContent(sf_tight_ISO_F->FindBin(119, fabs(MuonCand_eta[1])));
      }

      double sf_tight_ID_0 = (sf_tight_ID_B_0*L_B + sf_tight_ID_C1_0*L_C1 + sf_tight_ID_E_0*L_E + sf_tight_ID_F1_0*L_F1)/(L_B+L_C1+L_E+L_F1);
      //double sf_tight_ISO_0 = (sf_tight_ISO_B_0*L_B + sf_tight_ISO_C1_0*L_C1 + sf_tight_ISO_E_0*L_E + sf_tight_ISO_F1_0*L_F1)/(L_B+L_C1+L_E+L_F1);
      double sf_tight_ID_1 = (sf_tight_ID_B_1*L_B + sf_tight_ID_C1_1*L_C1 + sf_tight_ID_E_1*L_E + sf_tight_ID_F1_1*L_F1)/(L_B+L_C1+L_E+L_F1);
      //double sf_tight_ISO_1 = (sf_tight_ISO_B_1*L_B + sf_tight_ISO_C1_1*L_C1 + sf_tight_ISO_E_1*L_E + sf_tight_ISO_F1_1*L_F1)/(L_B+L_C1+L_E+L_F1);
      double sf_tight_muon_ID = sf_tight_ID_0*sf_tight_ID_1;
      //double sf_tight_muon_ISO = sf_tight_ISO_0*sf_tight_ISO_1;
      double sf_tight_muon = sf_tight_muon_ID/**sf_tight_muon_ISO*/;

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

      if ( !reweighting ) reweight = 1;
      if ( reweighting ) reweight = 1/re_0prot_2->Eval( contador_ext_PV3 );

      double weight = Weight*sf_tight_muon*reweight;
      
      //v.SetPtEtaPhiM(Pair_pt[0],Pair_eta[0],Pair_phi[0],Pair_mass[0]);      
      v.SetPxPyPzE(0,0,0,0);
      v += mu1; v += mu2;

      double a = 1 - fabs(deltaPhi(mu1.Phi(),mu2.Phi()))/PI;
      zerocortes = zerocortes + Weight*sf_tight_muon;		

      mu1_z_mu2_z->Fill(MuonCand_vtxz[0] - MuonCand_vtxz[1], Weight*sf_tight_muon);
      mu1_z_primvertex_z->Fill(MuonCand_vtxz[0] - PrimVertexCand_z[0], Weight*sf_tight_muon);
      mu2_z_primvertex_z->Fill(MuonCand_vtxz[1] - PrimVertexCand_z[0], Weight*sf_tight_muon);

      multiplicity_0prot->Fill(contador_ext_PV3, eff_1prot_rp23*eff_1prot_rp123*weight);

      if(MuonCand_pt[0] > 50 && MuonCand_pt[1] > 50 && fabs(MuonCand_eta[0]) <= 2.4 && fabs(MuonCand_eta[1]) <= 2.4){ 
         umcortes = umcortes + weight;
         multiplicity_0prot_pt->Fill(contador_ext_PV3, eff_1prot_rp23*eff_1prot_rp123*weight);
         if(MuonCand_charge[0] * MuonCand_charge[1] < 0){
            doiscortes = doiscortes + weight;
            if(MuonCand_istight[0] && MuonCand_istight[1]){
               trescortes = trescortes + weight;
               if(v.M() > 110.){
                  quatrocortes = quatrocortes + weight;
                  h_PrimVertex_z->Fill(PrimVertexCand_z[0], weight);
                  if( fabs( PrimVertexCand_z[0] ) < 15.){
                     cincocortes = cincocortes + weight;
                     h_PrimVertex_dif_muon1->Fill(MuonCand_vtxz[0] - PrimVertexCand_z[0], weight);
                     h_PrimVertex_dif_muon2->Fill(MuonCand_vtxz[1] - PrimVertexCand_z[0], weight);
                     PrimVertex_ndof->Fill(PrimVertexCand_ndof[0], weight);
                     PrimVertex_chi2->Fill(PrimVertexCand_chi2[0], weight);
                     if( ( fabs( MuonCand_vtxz[0] - PrimVertexCand_z[0] ) < 3*0.004 ) && ( fabs( MuonCand_vtxz[1] - PrimVertexCand_z[0] ) < 3*0.004 ) ){
                        seiscortes = seiscortes + weight;
                        for (size_t pf = 0; pf < nPfCand; pf++) { 
                           if(PfCand_fromPV[pf] == 3) contador_PV3_bkg++;
                        }  
                        h_acoplanarity->Fill(a, weight);
                        h_deltaphi->Fill(deltaPhi(mu1.Phi(),mu2.Phi()), weight);
                        if(a < 0.009){
                           setecortes = setecortes + weight;
                           multiplicity_cut->Fill(contador_ext_PV3, weight);
                           multiplicity_0prot_cut->Fill(contador_ext_PV3, eff_1prot_rp23*eff_1prot_rp123*weight);

                           n_fromPV->Fill(contador_PV, Weight*sf_tight_muon);
                           n_fromPV_2->Fill(contador_PV2, Weight*sf_tight_muon);
                           n_fromPV_3->Fill(contador_PV3, Weight*sf_tight_muon);
                           n_ext_fromPV->Fill(contador_ext_PV, Weight*sf_tight_muon);
                           n_ext_fromPV_2->Fill(contador_ext_PV2, Weight*sf_tight_muon);
                           n_ext_fromPV_3->Fill(contador_ext_PV3, Weight*sf_tight_muon);
                           n_fromPV_dz02->Fill(contador_PV_dz02, Weight*sf_tight_muon);
                           n_fromPV_2_dz02->Fill(contador_PV2_dz02, Weight*sf_tight_muon);
                           n_fromPV_3_dz02->Fill(contador_PV3_dz02, Weight*sf_tight_muon);
                           n_ext_fromPV_dz02->Fill(contador_ext_PV_dz02, Weight*sf_tight_muon);
                           n_ext_fromPV_2_dz02->Fill(contador_ext_PV2_dz02, Weight*sf_tight_muon);
                           n_ext_fromPV_3_dz02->Fill(contador_ext_PV3_dz02, Weight*sf_tight_muon);
                           n_fromPV_dz01->Fill(contador_PV_dz01, Weight*sf_tight_muon);
                           n_fromPV_2_dz01->Fill(contador_PV2_dz01, Weight*sf_tight_muon);
                           n_fromPV_3_dz01->Fill(contador_PV3_dz01, Weight*sf_tight_muon); 
                           n_ext_fromPV_dz01->Fill(contador_ext_PV_dz01, Weight*sf_tight_muon);
                           n_ext_fromPV_2_dz01->Fill(contador_ext_PV2_dz01, Weight*sf_tight_muon);
                           n_ext_fromPV_3_dz01->Fill(contador_ext_PV3_dz01, Weight*sf_tight_muon); 

                           //if(contador_ext_PV3 <= 1){
                           if(contador_ext_PV3 <= 3){
                              oitocortes = oitocortes + weight;
                              mumu_mass->Fill(v.M(), Weight*sf_tight_muon*reweight);
                              mumu_pt->Fill(v.Pt(), Weight*sf_tight_muon*reweight);
                              mumu_y->Fill(v.Rapidity(),  Weight*sf_tight_muon*reweight);
                              double sigma_xi_mumu_left = f_pair_left->Eval( xi_pair_left_reco );
                              double sigma_xi_mumu_right = f_pair_right->Eval( xi_pair_right_reco );
                              for ( unsigned int idz = 0; idz < nGenProtCand; ++idz ) {
                                 if (GenProtCand_eta[idz] > 0) xi_proton_gen_left = (1 - GenProtCand_e[idz]/6500);
                                 if (GenProtCand_eta[idz] < 0) xi_proton_gen_right = (1 - GenProtCand_e[idz]/6500);
                              }
                              for ( unsigned int idx = 0; idx < nRecoProtCand; ++idx ) {
                                 cont_prot = cont_prot + weight;
                                 bool fid_45 = false;
                                 bool fid_56 = false;
                                 if(ProtCand_xi[idx] >= .02 && ProtCand_trackx1[idx] >= 1.995 && ProtCand_trackx1[idx] <= 24.334 && ProtCand_tracky1[idx] >= -10.098 && ProtCand_tracky1[idx] <= 4.298) fid_45 = true;
                                 if(ProtCand_xi[idx] >= .03 && ProtCand_trackx1[idx] >= 2.422 && ProtCand_trackx1[idx] <= 24.620 && ProtCand_tracky1[idx] >= -9.698 && ProtCand_tracky1[idx] <= 4.698) fid_56 = true;
                                 if (ProtCand_trackpixshift1[idx] == 0) { 
                                    if(fid_45) {  
                                       if (ProtCand_rpid[idx] == 3) {
                                          if (ProtCand_ismultirp[idx] == 0) {
                                             proton_xi_left_rp3->Fill(ProtCand_xi[idx], weight);
                                             pair_xi_left_rp3->Fill(xi_pair_left_reco, weight);
                                             xi_left_reco_rp3->Fill(ProtCand_xi[idx], xi_pair_left_reco);
                                             g_xi_left_reco_rp3->SetPoint(g_xi_left_reco_rp3->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                             diff_proton_reco_pair_xi_left_rp3->Fill(ProtCand_xi[idx] - xi_pair_left_reco, weight); 
                                             ratio_proton_reco_pair_xi_left_rp3->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco, weight); 
                                             double sigma_xi_RP3 = f_rp3->Eval( ProtCand_xi[idx] );
                                             if ( sigma_xi_RP3 > 0.) {
                                                double sigma_xi_rp3_mumu = TMath::Sqrt( sigma_xi_RP3*sigma_xi_RP3 + sigma_xi_mumu_left*sigma_xi_mumu_left );
                                                if ( TMath::Abs( ProtCand_xi[idx] - xi_pair_left_reco ) <= n_sigmas_xi*sigma_xi_rp3_mumu ) {
                                                   match = true;
                                                   corte_match_rp3 = corte_match_rp3 + weight;
                                                   proton_xi_left_rp3_match->Fill(ProtCand_xi[idx], weight);
                                                   diff_proton_reco_pair_xi_left_rp3_match->Fill(ProtCand_xi[idx] - xi_pair_left_reco, weight); 
                                                   ratio_proton_reco_pair_xi_left_rp3_match->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco, weight); 
                                                   xi_left_reco_rp3_match->Fill(ProtCand_xi[idx], xi_pair_left_reco);
                                                   g_xi_left_reco_rp3_match->SetPoint(g_xi_left_reco_rp3_match->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                                }
                                                else {
                                                   xi_left_reco_rp3_non_match->Fill(ProtCand_xi[idx], xi_pair_left_reco);
                                                   g_xi_left_reco_rp3_non_match->SetPoint(g_xi_left_reco_rp3_non_match->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                                }
                                             }       
                                          }		
                                       }

                                       if (ProtCand_rpid[idx] == 23) {
                                          if (ProtCand_ismultirp[idx] == 0) {
                                             proton_xi_left_rp23_nprot->Fill(ProtCand_xi[idx], weight);
                                             pair_xi_left_rp23_nprot->Fill(xi_pair_left_reco, weight);
                                             xi_left_reco_rp23_nprot->Fill(ProtCand_xi[idx], xi_pair_left_reco); 
                                             g_xi_left_reco_rp23_nprot->SetPoint(g_xi_left_reco_rp23_nprot->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                             diff_proton_reco_pair_xi_left_rp23_nprot->Fill(ProtCand_xi[idx] - xi_pair_left_reco, weight); 
                                             ratio_proton_reco_pair_xi_left_rp23_nprot->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco, weight); 
                                             double sigma_xi_RP23_nprot = f_rp23_nprot->Eval( ProtCand_xi[idx] );
                                             if ( sigma_xi_RP23_nprot > 0.) {
                                                double sigma_xi_rp23_nprot_mumu = TMath::Sqrt( sigma_xi_RP23_nprot*sigma_xi_RP23_nprot + sigma_xi_mumu_left*sigma_xi_mumu_left );
                                                if ( TMath::Abs( ProtCand_xi[idx] - xi_pair_left_reco ) <= n_sigmas_xi*sigma_xi_rp23_nprot_mumu ) {
                                                   match = true;
                                                   corte_match_rp23_nprot = corte_match_rp23_nprot + weight;
                                                   proton_xi_left_rp23_nprot_match->Fill(ProtCand_xi[idx], weight);
                                                   diff_proton_reco_pair_xi_left_rp23_nprot_match->Fill(ProtCand_xi[idx] - xi_pair_left_reco, weight); 
                                                   ratio_proton_reco_pair_xi_left_rp23_nprot_match->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco, weight); 
                                                   xi_left_reco_rp23_nprot_match->Fill(ProtCand_xi[idx], xi_pair_left_reco);
                                                   g_xi_left_reco_rp23_nprot_match->SetPoint(g_xi_left_reco_rp23_nprot_match->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                                }
                                                else {
                                                   xi_left_reco_rp23_nprot_non_match->Fill(ProtCand_xi[idx], xi_pair_left_reco);
                                                   g_xi_left_reco_rp23_nprot_non_match->SetPoint(g_xi_left_reco_rp23_nprot_non_match->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                                }
                                             }
                                          }		
                                       }

                                       if(ProtCand_rpid[idx] == 3 && ProtCand_ismultirp[idx] == 0){
                                          single_rp3_xi = ProtCand_xi[idx];
                                          single_rp3_trackx1 = ProtCand_trackx1[idx];
                                          single_rp3_tracky1 = ProtCand_tracky1[idx];
                                       }

                                       if(ProtCand_rpid[idx] == 23 && ProtCand_ismultirp[idx] == 0){
                                          single_rp23_xi = ProtCand_xi[idx];
                                          single_rp23_trackx1 = ProtCand_trackx1[idx];
                                          single_rp23_tracky1 = ProtCand_tracky1[idx];
                                          cont_single_rp23++;
                                       }
                                    }

                                    if(fid_56) {  
                                       if (ProtCand_rpid[idx] == 103) {                           
                                          if (ProtCand_ismultirp[idx] == 0) {
                                             proton_xi_right_rp103->Fill(ProtCand_xi[idx], weight);
                                             pair_xi_right_rp103->Fill(xi_pair_right_reco, weight);
                                             xi_right_reco_rp103->Fill(ProtCand_xi[idx], xi_pair_right_reco);
                                             g_xi_right_reco_rp103->SetPoint(g_xi_right_reco_rp103->GetN(), ProtCand_xi[idx], xi_pair_right_reco);
                                             diff_proton_reco_pair_xi_right_rp103->Fill(ProtCand_xi[idx] - xi_pair_right_reco, weight); 
                                             ratio_proton_reco_pair_xi_right_rp103->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco, weight); 
                                             double sigma_xi_RP103 = f_rp103->Eval( ProtCand_xi[idx] );
                                             if ( sigma_xi_RP103 > 0.) {
                                                double sigma_xi_rp103_mumu = TMath::Sqrt( sigma_xi_RP103*sigma_xi_RP103 + sigma_xi_mumu_right*sigma_xi_mumu_right );
                                                if ( TMath::Abs( ProtCand_xi[idx] - xi_pair_right_reco ) <= n_sigmas_xi*sigma_xi_rp103_mumu ) {
                                                   match = true;
                                                   corte_match_rp103 = corte_match_rp103 + weight;
                                                   proton_xi_right_rp103_match->Fill(ProtCand_xi[idx], weight);
                                                   diff_proton_reco_pair_xi_right_rp103_match->Fill(ProtCand_xi[idx] - xi_pair_right_reco, weight); 
                                                   ratio_proton_reco_pair_xi_right_rp103_match->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco, weight); 
                                                   xi_right_reco_rp103_match->Fill(ProtCand_xi[idx], xi_pair_right_reco);
                                                   g_xi_right_reco_rp103_match->SetPoint(g_xi_right_reco_rp103_match->GetN(), ProtCand_xi[idx], xi_pair_right_reco);
                                                }
                                                else {
                                                   xi_right_reco_rp103_non_match->Fill(ProtCand_xi[idx], xi_pair_right_reco);
                                                   g_xi_right_reco_rp103_non_match->SetPoint(g_xi_right_reco_rp103_non_match->GetN(), ProtCand_xi[idx], xi_pair_right_reco);
                                                }
                                             }       
                                          }		
                                       }

                                       if (ProtCand_rpid[idx] == 123) {                           
                                          if (ProtCand_ismultirp[idx] == 0) {
                                             proton_xi_right_rp123_nprot->Fill(ProtCand_xi[idx], weight);
                                             pair_xi_right_rp123_nprot->Fill(xi_pair_right_reco, weight);
                                             xi_right_reco_rp123_nprot->Fill(ProtCand_xi[idx], xi_pair_right_reco);
                                             g_xi_right_reco_rp123_nprot->SetPoint(g_xi_right_reco_rp123_nprot->GetN(), ProtCand_xi[idx], xi_pair_right_reco);
                                             diff_proton_reco_pair_xi_right_rp123_nprot->Fill(ProtCand_xi[idx] - xi_pair_right_reco, weight); 
                                             ratio_proton_reco_pair_xi_right_rp123_nprot->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco, weight); 
                                             double sigma_xi_RP123_nprot = f_rp123_nprot->Eval( ProtCand_xi[idx] );
                                             if ( sigma_xi_RP123_nprot > 0.) {
                                                double sigma_xi_rp123_nprot_mumu = TMath::Sqrt( sigma_xi_RP123_nprot*sigma_xi_RP123_nprot + sigma_xi_mumu_right*sigma_xi_mumu_right );
                                                if ( TMath::Abs( ProtCand_xi[idx] - xi_pair_right_reco ) <= n_sigmas_xi*sigma_xi_rp123_nprot_mumu ) { 
                                                   match = true;
                                                   corte_match_rp123_nprot = corte_match_rp123_nprot + weight;
                                                   proton_xi_right_rp123_nprot_match->Fill(ProtCand_xi[idx], weight);
                                                   diff_proton_reco_pair_xi_right_rp123_nprot_match->Fill(ProtCand_xi[idx] - xi_pair_right_reco, weight); 
                                                   ratio_proton_reco_pair_xi_right_rp123_nprot_match->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco, weight); 
                                                   xi_right_reco_rp123_nprot_match->Fill(ProtCand_xi[idx], xi_pair_right_reco);
                                                   g_xi_right_reco_rp123_nprot_match->SetPoint(g_xi_right_reco_rp123_nprot_match->GetN(), ProtCand_xi[idx], xi_pair_right_reco);
                                                }
                                                else {
                                                   xi_right_reco_rp123_nprot_non_match->Fill(ProtCand_xi[idx], xi_pair_right_reco);
                                                   g_xi_right_reco_rp123_nprot_non_match->SetPoint(g_xi_right_reco_rp123_nprot_non_match->GetN(), ProtCand_xi[idx], xi_pair_right_reco);
                                                }
                                             }       
                                          }		
                                       }

                                       if(ProtCand_rpid[idx] == 103 && ProtCand_ismultirp[idx] == 0){
                                          single_rp103_xi = ProtCand_xi[idx];
                                          single_rp103_trackx1 = ProtCand_trackx1[idx];
                                          single_rp103_tracky1 = ProtCand_tracky1[idx];
                                       }
                                       if(ProtCand_rpid[idx] == 123 && ProtCand_ismultirp[idx] == 0){
                                          single_rp123_xi = ProtCand_xi[idx];
                                          single_rp123_trackx1 = ProtCand_trackx1[idx];
                                          single_rp123_tracky1 = ProtCand_tracky1[idx];
                                          cont_single_rp123++;
                                       }
                                    }
                                 }
                                 if (ProtCand_trackpixshift2[idx] == 0) { 
                                    if(fid_45) {  
                                       if (ProtCand_arm[idx] == 0) {
                                          if (ProtCand_ismultirp[idx] == 1) {
                                             proton_xi_left_multi->Fill(ProtCand_xi[idx], weight);
                                             pair_xi_left_multi->Fill(xi_pair_left_reco, weight);
                                             xi_left_reco_multi->Fill(ProtCand_xi[idx], xi_pair_left_reco); 
                                             g_xi_left_reco_multi->SetPoint(g_xi_left_reco_multi->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                             diff_proton_reco_pair_xi_left_multi->Fill(ProtCand_xi[idx] - xi_pair_left_reco, weight); 
                                             ratio_proton_reco_pair_xi_left_multi->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco, weight); 
                                             double sigma_xi_left_multi = f_left_multi->Eval( ProtCand_xi[idx] );
                                             if ( sigma_xi_left_multi > 0.) {
                                                double sigma_xi_lm_mumu = TMath::Sqrt( sigma_xi_left_multi*sigma_xi_left_multi + sigma_xi_mumu_left*sigma_xi_mumu_left );
                                                if ( TMath::Abs( ProtCand_xi[idx] - xi_pair_left_reco ) <= n_sigmas_xi*sigma_xi_lm_mumu ) { 
                                                   match = true;
                                                   corte_match_left_multi = corte_match_left_multi + weight;
                                                   proton_xi_left_multi_match->Fill(ProtCand_xi[idx], weight);
                                                   diff_proton_reco_pair_xi_left_multi_match->Fill(ProtCand_xi[idx] - xi_pair_left_reco, weight); 
                                                   ratio_proton_reco_pair_xi_left_multi_match->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco, weight); 
                                                   xi_left_reco_multi_match->Fill(ProtCand_xi[idx], xi_pair_left_reco);
                                                   g_xi_left_reco_multi_match->SetPoint(g_xi_left_reco_multi_match->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                                }
                                                else { 
                                                   xi_left_reco_multi_non_match->Fill(ProtCand_xi[idx], xi_pair_left_reco);
                                                   g_xi_left_reco_multi_non_match->SetPoint(g_xi_left_reco_multi_non_match->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                                }
                                             }
                                          }		
                                       }
                                    }
                                    if (ProtCand_arm[idx] == 1) {                           
                                       if(fid_56) {  
                                          if (ProtCand_ismultirp[idx] == 1) {
                                             proton_xi_right_multi->Fill(ProtCand_xi[idx], weight);
                                             pair_xi_right_multi->Fill(xi_pair_right_reco, weight);
                                             xi_right_reco_multi->Fill(ProtCand_xi[idx], xi_pair_right_reco);
                                             g_xi_right_reco_multi->SetPoint(g_xi_right_reco_multi->GetN(), ProtCand_xi[idx], xi_pair_right_reco);
                                             diff_proton_reco_pair_xi_right_multi->Fill(ProtCand_xi[idx] - xi_pair_right_reco, weight); 
                                             ratio_proton_reco_pair_xi_right_multi->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco, weight); 
                                             double sigma_xi_right_multi = f_right_multi->Eval( ProtCand_xi[idx] );
                                             if ( sigma_xi_right_multi > 0.) {
                                                double sigma_xi_rm_mumu = TMath::Sqrt( sigma_xi_right_multi*sigma_xi_right_multi + sigma_xi_mumu_right*sigma_xi_mumu_right );
                                                if ( TMath::Abs( ProtCand_xi[idx] - xi_pair_right_reco ) <= n_sigmas_xi*sigma_xi_rm_mumu ) {
                                                   match = true;
                                                   corte_match_right_multi = corte_match_right_multi + weight;
                                                   proton_xi_right_multi_match->Fill(ProtCand_xi[idx], weight);
                                                   diff_proton_reco_pair_xi_right_multi_match->Fill(ProtCand_xi[idx] - xi_pair_right_reco, weight); 
                                                   ratio_proton_reco_pair_xi_right_multi_match->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco, weight); 
                                                   xi_right_reco_multi_match->Fill(ProtCand_xi[idx], xi_pair_right_reco);
                                                   g_xi_right_reco_multi_match->SetPoint(g_xi_right_reco_multi_match->GetN(), ProtCand_xi[idx], xi_pair_right_reco);
                                                }
                                                else {
                                                   xi_right_reco_multi_non_match->Fill(ProtCand_xi[idx], xi_pair_right_reco);
                                                   g_xi_right_reco_multi_non_match->SetPoint(g_xi_right_reco_multi_non_match->GetN(), ProtCand_xi[idx], xi_pair_right_reco);
                                                }
                                             }
                                          }	
                                       }
                                    }
                                 }
                              }
                              bool fid_45_1prot = false;
                              bool fid_56_1prot = false;
                              if(single_rp23_xi >= .02 && single_rp23_trackx1 >= 1.995 && single_rp23_trackx1 <= 24.334 && single_rp23_tracky1 >= -10.098 && single_rp23_tracky1 <= 4.298) fid_45_1prot = true;
                              if(single_rp123_xi >= .03 && single_rp123_trackx1 >= 2.422 && single_rp123_trackx1 <= 24.620 && single_rp123_tracky1 >= -9.698 && single_rp123_tracky1 <= 4.698) fid_56_1prot = true;

                              if (cont_single_rp23==1 && fid_45_1prot){
                                 mumu_mass_rp23->Fill(v.M(), weight);
                                 mumu_pt_rp23->Fill(v.Pt(), weight);
                                 mumu_y_rp23->Fill(v.Rapidity(), weight);
                                 proton_xi_left_rp23->Fill(single_rp23_xi, weight);
                                 pair_xi_left_rp23->Fill(xi_pair_left_reco, weight);
                                 xi_left_reco_rp23->Fill(single_rp23_xi,xi_pair_left_reco);
                                 g_xi_left_reco_rp23->SetPoint(g_xi_left_reco_rp23->GetN(), single_rp23_xi, xi_pair_left_reco);
                                 diff_proton_reco_pair_xi_left_rp23->Fill(single_rp23_xi - xi_pair_left_reco, weight); 
                                 ratio_proton_reco_pair_xi_left_rp23->Fill(1 - single_rp23_xi/xi_pair_left_reco, weight); 
                                 double sigma_xi_left_rp23 = f_rp23->Eval( single_rp23_xi );
                                 if ( sigma_xi_left_rp23 > 0.) {
                                    double sigma_xi_rp23_mumu = TMath::Sqrt( sigma_xi_left_rp23*sigma_xi_left_rp23 + sigma_xi_mumu_left*sigma_xi_mumu_left );
                                    if ( TMath::Abs( single_rp23_xi - xi_pair_left_reco ) <= n_sigmas_xi*sigma_xi_rp23_mumu ) {
                                       match = true;
                                       corte_match_rp23_1prot = corte_match_rp23_1prot + weight;
                                       mumu_mass_rp23_match->Fill(v.M(), weight);
                                       mumu_pt_rp23_match->Fill(v.Pt(), weight);
                                       mumu_y_rp23_match->Fill(v.Rapidity(), weight);
                                       proton_xi_left_rp23_match->Fill(single_rp23_xi, weight);
                                       pair_xi_left_rp23_match->Fill(xi_pair_left_reco, weight);
                                       diff_proton_reco_pair_xi_left_rp23_match->Fill(single_rp23_xi - xi_pair_left_reco, weight); 
                                       ratio_proton_reco_pair_xi_left_rp23_match->Fill(1 - single_rp23_xi/xi_pair_left_reco, weight); 
                                       xi_left_reco_rp23_match->Fill(single_rp23_xi, xi_pair_left_reco);
                                       g_xi_left_reco_rp23_match->SetPoint(g_xi_left_reco_rp23_match->GetN(), single_rp23_xi, xi_pair_left_reco);
                                    }
                                    else {
                                       xi_left_reco_rp23_non_match->Fill(single_rp23_xi, xi_pair_left_reco);
                                       g_xi_left_reco_rp23_non_match->SetPoint(g_xi_left_reco_rp23_non_match->GetN(), single_rp23_xi, xi_pair_left_reco);
                                    }
                                 }
                              }

                              if (cont_single_rp23==1 && fid_45_1prot){
                                 single_left_xi = single_rp23_xi;
                                 proton_xi_left_single->Fill(single_left_xi, Weight*sf_tight_muon*reweight);
                                 xi_left_reco_single->Fill(single_left_xi,xi_pair_left_reco);
                                 g_xi_left_reco_single->SetPoint(g_xi_left_reco_single->GetN(), single_left_xi, xi_pair_left_reco);
                                 diff_proton_reco_pair_xi_left_single->Fill(single_left_xi - xi_pair_left_reco, Weight*sf_tight_muon*reweight); 
                                 ratio_proton_reco_pair_xi_left_single->Fill(1 - single_left_xi/xi_pair_left_reco, Weight*sf_tight_muon*reweight); 
                                 double sigma_xi_left_single = f_left_single->Eval( single_left_xi );
                                 if ( sigma_xi_left_single > 0.) {
                                    double sigma_xi_ls_mumu = TMath::Sqrt( sigma_xi_left_single*sigma_xi_left_single + sigma_xi_mumu_left*sigma_xi_mumu_left );
                                    if ( TMath::Abs( single_left_xi - xi_pair_left_reco ) <= n_sigmas_xi*sigma_xi_ls_mumu ) {
                                       match = true;
                                       xi_left_reco_single_match->Fill(single_left_xi, xi_pair_left_reco);
                                       g_xi_left_reco_single_match->SetPoint(g_xi_left_reco_single_match->GetN(), single_left_xi, xi_pair_left_reco);
                                    }
                                    else {
                                       xi_left_reco_single_non_match->Fill(single_left_xi, xi_pair_left_reco);
                                       g_xi_left_reco_single_non_match->SetPoint(g_xi_left_reco_single_non_match->GetN(), single_left_xi, xi_pair_left_reco);
                                    }
                                 }
                              }
                              else {
                                 single_left_xi = single_rp3_xi;
                                 proton_xi_left_single->Fill(single_left_xi, Weight*sf_tight_muon*reweight);
                                 xi_left_reco_single->Fill(single_left_xi,xi_pair_left_reco);
                                 g_xi_left_reco_single->SetPoint(g_xi_left_reco_single->GetN(), single_left_xi, xi_pair_left_reco);
                                 diff_proton_reco_pair_xi_left_single->Fill(single_left_xi - xi_pair_left_reco); 
                                 ratio_proton_reco_pair_xi_left_single->Fill(1 - single_left_xi/xi_pair_left_reco, Weight*sf_tight_muon*reweight); 
                                 double sigma_xi_left_single = f_left_single->Eval( single_left_xi, Weight*sf_tight_muon*reweight);
                                 if ( sigma_xi_left_single > 0.) {
                                    double sigma_xi_ls_mumu = TMath::Sqrt( sigma_xi_left_single*sigma_xi_left_single + sigma_xi_mumu_left*sigma_xi_mumu_left );
                                    if ( TMath::Abs( single_left_xi - xi_pair_left_reco ) <= n_sigmas_xi*sigma_xi_ls_mumu ) {
                                       match = true;
                                       xi_left_reco_single_match->Fill(single_left_xi, xi_pair_left_reco);
                                       g_xi_left_reco_single_match->SetPoint(g_xi_left_reco_single_match->GetN(), single_left_xi, xi_pair_left_reco);
                                    }
                                    else {
                                       xi_left_reco_single_non_match->Fill(single_left_xi, xi_pair_left_reco);
                                       g_xi_left_reco_single_non_match->SetPoint(g_xi_left_reco_single_non_match->GetN(), single_left_xi, xi_pair_left_reco);
                                    }
                                 }
                              }

                              if (cont_single_rp123==1 && fid_56_1prot){
                                 mumu_mass_rp123->Fill(v.M(), weight);
                                 mumu_pt_rp123->Fill(v.Pt(), weight);
                                 mumu_y_rp123->Fill(v.Rapidity(), weight);
                                 proton_xi_right_rp123->Fill(single_rp123_xi, weight);
                                 pair_xi_right_rp123->Fill(xi_pair_right_reco, weight);
                                 xi_right_reco_rp123->Fill(single_rp123_xi,xi_pair_right_reco);
                                 g_xi_right_reco_rp123->SetPoint(g_xi_right_reco_rp123->GetN(), single_rp123_xi, xi_pair_right_reco);
                                 diff_proton_reco_pair_xi_right_rp123->Fill(single_rp123_xi - xi_pair_right_reco, weight); 
                                 ratio_proton_reco_pair_xi_right_rp123->Fill(1 - single_rp123_xi/xi_pair_right_reco, weight); 
                                 double sigma_xi_right_rp123 = f_rp123->Eval( single_rp123_xi );
                                 if ( sigma_xi_right_rp123 > 0.) {
                                    double sigma_xi_rp123_mumu = TMath::Sqrt( sigma_xi_right_rp123*sigma_xi_right_rp123 + sigma_xi_mumu_right*sigma_xi_mumu_right );
                                    if ( TMath::Abs( single_rp123_xi - xi_pair_right_reco ) <= n_sigmas_xi*sigma_xi_rp123_mumu ) {
                                       match = true;
                                       corte_match_rp123_1prot = corte_match_rp123_1prot + weight;
                                       mumu_mass_rp123_match->Fill(v.M(), weight);
                                       mumu_pt_rp123_match->Fill(v.Pt(), weight);
                                       mumu_y_rp123_match->Fill(v.Rapidity(), weight);
                                       proton_xi_right_rp123_match->Fill(single_rp123_xi, weight);
                                       pair_xi_right_rp123_match->Fill(xi_pair_right_reco, weight);
                                       diff_proton_reco_pair_xi_right_rp123_match->Fill(single_rp123_xi - xi_pair_right_reco, weight); 
                                       ratio_proton_reco_pair_xi_right_rp123_match->Fill(1 - single_rp123_xi/xi_pair_right_reco, weight); 
                                       xi_right_reco_rp123_match->Fill(single_rp123_xi, xi_pair_right_reco);
                                       g_xi_right_reco_rp123_match->SetPoint(g_xi_right_reco_rp123_match->GetN(), single_rp123_xi, xi_pair_right_reco);
                                    }
                                    else {
                                       xi_right_reco_rp123_non_match->Fill(single_rp123_xi, xi_pair_right_reco);
                                       g_xi_right_reco_rp123_non_match->SetPoint(g_xi_right_reco_rp123_non_match->GetN(), single_rp123_xi, xi_pair_right_reco);
                                    }
                                 }
                              }

                              if (cont_single_rp123==1 && fid_56_1prot){
                                 single_right_xi = single_rp123_xi;
                                 proton_xi_right_single->Fill(single_right_xi, Weight*sf_tight_muon*reweight);
                                 xi_right_reco_single->Fill(single_right_xi,xi_pair_right_reco);
                                 g_xi_right_reco_single->SetPoint(g_xi_right_reco_single->GetN(), single_right_xi, xi_pair_right_reco);
                                 diff_proton_reco_pair_xi_right_single->Fill(single_right_xi - xi_pair_right_reco, Weight*sf_tight_muon*reweight); 
                                 ratio_proton_reco_pair_xi_right_single->Fill(1 - single_right_xi/xi_pair_right_reco, Weight*sf_tight_muon*reweight); 
                                 double sigma_xi_right_single = f_right_single->Eval( single_right_xi );
                                 if ( sigma_xi_right_single > 0.) {
                                    double sigma_xi_rm_mumu = TMath::Sqrt( sigma_xi_right_single*sigma_xi_right_single + sigma_xi_mumu_right*sigma_xi_mumu_right );
                                    if ( TMath::Abs( single_right_xi - xi_pair_right_reco ) <= n_sigmas_xi*sigma_xi_rm_mumu ) {
                                       match = true;
                                       xi_right_reco_single_match->Fill(single_right_xi, xi_pair_right_reco);
                                       g_xi_right_reco_single_match->SetPoint(g_xi_right_reco_single_match->GetN(), single_right_xi, xi_pair_right_reco);
                                    }
                                    else {
                                       xi_right_reco_single_non_match->Fill(single_right_xi, xi_pair_right_reco);
                                       g_xi_right_reco_single_non_match->SetPoint(g_xi_right_reco_single_non_match->GetN(), single_right_xi, xi_pair_right_reco);
                                    }
                                 }
                              }
                              else {
                                 single_right_xi = single_rp103_xi;
                                 proton_xi_right_single->Fill(single_right_xi, Weight*sf_tight_muon*reweight);
                                 xi_right_reco_single->Fill(single_right_xi,xi_pair_right_reco);
                                 g_xi_right_reco_single->SetPoint(g_xi_right_reco_single->GetN(), single_right_xi, xi_pair_right_reco);
                                 diff_proton_reco_pair_xi_right_single->Fill(single_right_xi - xi_pair_right_reco, Weight*sf_tight_muon*reweight); 
                                 ratio_proton_reco_pair_xi_right_single->Fill(1 - single_right_xi/xi_pair_right_reco, Weight*sf_tight_muon*reweight); 
                                 double sigma_xi_right_single = f_right_single->Eval( single_right_xi );
                                 if ( sigma_xi_right_single > 0.) {
                                    double sigma_xi_rm_mumu = TMath::Sqrt( sigma_xi_right_single*sigma_xi_right_single + sigma_xi_mumu_right*sigma_xi_mumu_right );
                                    if ( TMath::Abs( single_right_xi - xi_pair_right_reco ) <= n_sigmas_xi*sigma_xi_rm_mumu ) {
                                       match = true;
                                       xi_right_reco_single_match->Fill(single_right_xi, xi_pair_right_reco);
                                       g_xi_right_reco_single_match->SetPoint(g_xi_right_reco_single_match->GetN(), single_right_xi, xi_pair_right_reco);
                                    }
                                    else {
                                       xi_right_reco_single_non_match->Fill(single_right_xi, xi_pair_right_reco);
                                       g_xi_right_reco_single_non_match->SetPoint(g_xi_right_reco_single_non_match->GetN(), single_right_xi, xi_pair_right_reco);
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
         }   
      }

      cout << "0cortes: " << zerocortes << endl;
      cut_flow->SetBinContent(1, zerocortes);
      cut_flow->GetXaxis()->SetBinLabel(1, "only triggers");
      cout << "1cortes: " << umcortes << endl;
      cut_flow->SetBinContent(2, umcortes);
      cut_flow->GetXaxis()->SetBinLabel(2, "p_{T}");
      cout << "2cortes: " << doiscortes << endl;
      cut_flow->SetBinContent(3, doiscortes);
      cut_flow->GetXaxis()->SetBinLabel(3, "opp signal");
      cout << "3cortes: " << trescortes << endl;
      cut_flow->SetBinContent(4, trescortes);
      cut_flow->GetXaxis()->SetBinLabel(4, "istight");
      cout << "4cortes: " << quatrocortes << endl;
      cut_flow->SetBinContent(5, quatrocortes);
      cut_flow->GetXaxis()->SetBinLabel(5, "inv mass");
      cout << "5cortes: " << cincocortes << endl;
      cut_flow->SetBinContent(6, cincocortes);
      cut_flow->GetXaxis()->SetBinLabel(6, "primver z");
      cout << "6cortes: " << seiscortes << endl;
      cut_flow->SetBinContent(7, seiscortes);
      cut_flow->GetXaxis()->SetBinLabel(7, "muonver-primver");
      cout << "7cortes: " << setecortes << endl;
      cut_flow->SetBinContent(8, setecortes);
      cut_flow->GetXaxis()->SetBinLabel(8, "acoplan");
      cout << "8cortes: " << oitocortes << endl;
      cut_flow->SetBinContent(9, oitocortes);
      cut_flow->GetXaxis()->SetBinLabel(9, "extra tracks");

      cout << "corte_match_rp3: " << corte_match_rp3 << endl;
      cut_match->SetBinContent(1, corte_match_rp3);
      cut_match->GetXaxis()->SetBinLabel(1, "match rp3");
      cout << "corte_match_rp23_nprot: " << corte_match_rp23_nprot << endl;
      cut_match->SetBinContent(2, corte_match_rp23_nprot);
      cut_match->GetXaxis()->SetBinLabel(2, "match rp23 nprot");
      cout << "corte_match_rp23_1prot: " << corte_match_rp23_1prot << endl;
      cut_match->SetBinContent(3, corte_match_rp23_1prot);
      cut_match->GetXaxis()->SetBinLabel(3, "match rp23 1prot");
      cout << "corte_match_rp103: " << corte_match_rp103 << endl;
      cut_match->SetBinContent(4, corte_match_rp103);
      cut_match->GetXaxis()->SetBinLabel(4, "match rp103");
      cout << "corte_match_rp123_nprot: " << corte_match_rp123_nprot << endl;
      cut_match->SetBinContent(5, corte_match_rp123_nprot);
      cut_match->GetXaxis()->SetBinLabel(5, "match rp123 nprot");
      cout << "corte_match_rp123_1prot: " << corte_match_rp123_1prot << endl;
      cut_match->SetBinContent(6, corte_match_rp123_1prot);
      cut_match->GetXaxis()->SetBinLabel(6, "match rp123 1prot");
      cout << "corte_match_left_multi: " << corte_match_left_multi << endl;
      cut_match->SetBinContent(7, corte_match_left_multi);
      cut_match->GetXaxis()->SetBinLabel(7, "match left multi");
      cout << "corte_match_right_multi: " << corte_match_right_multi << endl;
      cut_match->SetBinContent(8, corte_match_right_multi);
      cut_match->GetXaxis()->SetBinLabel(8, "match right multi");

      TCanvas *c_graph = new TCanvas("c_graph","",0,0,1200,1000);
      g_xi_left_reco_rp3->Draw("AP");
      g_xi_left_reco_rp3_match->Draw("AP");
      g_xi_left_reco_rp3_non_match->Draw("AP");
      g_xi_left_reco_rp23->Draw("AP");
      g_xi_left_reco_rp23_match->Draw("AP");
      g_xi_left_reco_rp23_non_match->Draw("AP");
      g_xi_left_reco_rp23_nprot->Draw("AP");
      g_xi_left_reco_rp23_nprot_match->Draw("AP");
      g_xi_left_reco_rp23_nprot_non_match->Draw("AP");
      g_xi_left_reco_single->Draw("AP");
      g_xi_left_reco_single_match->Draw("AP");
      g_xi_left_reco_single_non_match->Draw("AP");
      g_xi_right_reco_rp103->Draw("AP");
      g_xi_right_reco_rp103_match->Draw("AP");
      g_xi_right_reco_rp103_non_match->Draw("AP");
      g_xi_right_reco_rp123->Draw("AP");
      g_xi_right_reco_rp123_match->Draw("AP");
      g_xi_right_reco_rp123_non_match->Draw("AP");
      g_xi_right_reco_rp123_nprot->Draw("AP");
      g_xi_right_reco_rp123_nprot_match->Draw("AP");
      g_xi_right_reco_rp123_nprot_non_match->Draw("AP");
      g_xi_right_reco_single->Draw("AP");
      g_xi_right_reco_single_match->Draw("AP");
      g_xi_right_reco_single_non_match->Draw("AP");
      g_xi_left_reco_multi->Draw("AP");
      g_xi_left_reco_multi_match->Draw("AP");
      g_xi_left_reco_multi_non_match->Draw("AP");
      g_xi_right_reco_multi->Draw("AP");
      g_xi_right_reco_multi_match->Draw("AP");
      g_xi_right_reco_multi_non_match->Draw("AP");
      c_graph->cd();
      c_graph->Close();

      TFile* f = new TFile(outfileName.c_str(), "RECREATE");
      h_PrimVertex_z->Write();
      h_PrimVertex_dif_muon1->Write();
      h_PrimVertex_dif_muon2->Write();
      h_acoplanarity->Write();
      h_deltaphi->Write();
      PrimVertex_ndof->Write();
      PrimVertex_chi2->Write();
      mumu_mass->Write();
      mumu_pt->Write();
      mumu_y->Write();
      n_fromPV_3_signal->Write();
      n_fromPV_3_bkg->Write();

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

      proton_xi_left_rp3->Write();
      proton_xi_left_rp3_match->Write();
      pair_xi_left_rp3->Write();
      xi_left_reco_rp3->Write();
      g_xi_left_reco_rp3->Write();
      xi_left_reco_rp3_match->Write();
      g_xi_left_reco_rp3_match->Write();
      xi_left_reco_rp3_non_match->Write();
      g_xi_left_reco_rp3_non_match->Write();
      diff_proton_reco_pair_xi_left_rp3->Write();
      ratio_proton_reco_pair_xi_left_rp3->Write();
      diff_proton_reco_pair_xi_left_rp3_match->Write();
      ratio_proton_reco_pair_xi_left_rp3_match->Write();

      mumu_mass_rp23->Write();
      mumu_pt_rp23->Write();
      mumu_y_rp23->Write();
      mumu_mass_rp23_match->Write();
      mumu_pt_rp23_match->Write();
      mumu_y_rp23_match->Write();
      proton_xi_left_rp23->Write();
      proton_xi_left_rp23_match->Write();
      pair_xi_left_rp23->Write();
      pair_xi_left_rp23_match->Write();
      xi_left_reco_rp23->Write();
      g_xi_left_reco_rp23->Write();
      xi_left_reco_rp23_match->Write();
      g_xi_left_reco_rp23_match->Write();
      xi_left_reco_rp23_non_match->Write();
      g_xi_left_reco_rp23_non_match->Write();
      diff_proton_reco_pair_xi_left_rp23->Write();
      ratio_proton_reco_pair_xi_left_rp23->Write();
      diff_proton_reco_pair_xi_left_rp23_match->Write();
      ratio_proton_reco_pair_xi_left_rp23_match->Write();

      proton_xi_left_rp23_nprot->Write();
      proton_xi_left_rp23_nprot_match->Write();
      pair_xi_left_rp23_nprot->Write();
      pair_xi_left_rp23_nprot_match->Write();
      xi_left_reco_rp23_nprot->Write();
      g_xi_left_reco_rp23_nprot->Write();
      xi_left_reco_rp23_nprot_match->Write();
      g_xi_left_reco_rp23_nprot_match->Write();
      xi_left_reco_rp23_nprot_non_match->Write();
      g_xi_left_reco_rp23_nprot_non_match->Write();
      diff_proton_reco_pair_xi_left_rp23_nprot->Write();
      ratio_proton_reco_pair_xi_left_rp23_nprot->Write();
      diff_proton_reco_pair_xi_left_rp23_nprot_match->Write();
      ratio_proton_reco_pair_xi_left_rp23_nprot_match->Write();

      proton_xi_left_single->Write();
      pair_xi_left_single->Write();
      xi_left_reco_single->Write();
      xi_left_reco_single->Write();
      g_xi_left_reco_single->Write();
      xi_left_reco_single_match->Write();
      g_xi_left_reco_single_match->Write();
      xi_left_reco_single_non_match->Write();
      g_xi_left_reco_single_non_match->Write();
      diff_proton_reco_pair_xi_left_single->Write();
      ratio_proton_reco_pair_xi_left_single->Write();

      proton_xi_right_rp103->Write();
      proton_xi_right_rp103_match->Write();
      pair_xi_right_rp103->Write();
      xi_right_reco_rp103->Write();
      g_xi_right_reco_rp103->Write();
      xi_right_reco_rp103_match->Write();
      g_xi_right_reco_rp103_match->Write();
      xi_right_reco_rp103_non_match->Write();
      g_xi_right_reco_rp103_non_match->Write();
      diff_proton_reco_pair_xi_right_rp103->Write();
      ratio_proton_reco_pair_xi_right_rp103->Write();
      diff_proton_reco_pair_xi_right_rp103_match->Write();
      ratio_proton_reco_pair_xi_right_rp103_match->Write();

      mumu_mass_rp123->Write();
      mumu_pt_rp123->Write();
      mumu_y_rp123->Write();
      mumu_mass_rp123_match->Write();
      mumu_pt_rp123_match->Write();
      mumu_y_rp123_match->Write();
      mumu_mass_rp123->Write();
      mumu_pt_rp123->Write();
      mumu_y_rp123->Write();
      proton_xi_right_rp123->Write();
      proton_xi_right_rp123_match->Write();
      pair_xi_right_rp123->Write();
      pair_xi_right_rp123_match->Write();
      xi_right_reco_rp123->Write();
      g_xi_right_reco_rp123->Write();
      xi_right_reco_rp123_match->Write();
      g_xi_right_reco_rp123_match->Write();
      xi_right_reco_rp123_non_match->Write();
      g_xi_right_reco_rp123_non_match->Write();
      diff_proton_reco_pair_xi_right_rp123->Write();
      ratio_proton_reco_pair_xi_right_rp123->Write();
      diff_proton_reco_pair_xi_right_rp123_match->Write();
      ratio_proton_reco_pair_xi_right_rp123_match->Write();

      proton_xi_right_rp123_nprot->Write();
      proton_xi_right_rp123_nprot_match->Write();
      pair_xi_right_rp123_nprot->Write();
      pair_xi_right_rp123_nprot_match->Write();
      xi_right_reco_rp123_nprot->Write();
      g_xi_right_reco_rp123_nprot->Write();
      xi_right_reco_rp123_nprot_match->Write();
      g_xi_right_reco_rp123_nprot_match->Write();
      xi_right_reco_rp123_nprot_non_match->Write();
      g_xi_right_reco_rp123_nprot_non_match->Write();
      diff_proton_reco_pair_xi_right_rp123_nprot->Write();
      ratio_proton_reco_pair_xi_right_rp123_nprot->Write();
      diff_proton_reco_pair_xi_right_rp123_nprot_match->Write();
      ratio_proton_reco_pair_xi_right_rp123_nprot_match->Write();

      proton_xi_right_single->Write();
      pair_xi_right_single->Write();
      xi_right_reco_single->Write();
      g_xi_right_reco_single->Write();
      xi_right_reco_single_match->Write();
      g_xi_right_reco_single_match->Write();
      xi_right_reco_single_non_match->Write();
      g_xi_right_reco_single_non_match->Write();
      diff_proton_reco_pair_xi_right_single->Write();
      ratio_proton_reco_pair_xi_right_single->Write();

      proton_xi_left_multi->Write();
      proton_xi_left_multi_match->Write();
      pair_xi_left_multi->Write();
      xi_left_reco_multi->Write();
      g_xi_left_reco_multi->Write();
      xi_left_reco_multi_match->Write();
      g_xi_left_reco_multi_match->Write();
      xi_left_reco_multi_non_match->Write();
      g_xi_left_reco_multi_non_match->Write();
      diff_proton_reco_pair_xi_left_multi->Write();
      ratio_proton_reco_pair_xi_left_multi->Write();
      diff_proton_reco_pair_xi_left_multi_match->Write();
      ratio_proton_reco_pair_xi_left_multi_match->Write();

      proton_xi_right_multi->Write();
      proton_xi_right_multi_match->Write();
      pair_xi_right_multi->Write();
      xi_right_reco_multi->Write();
      g_xi_right_reco_multi->Write();
      xi_right_reco_multi_match->Write();
      g_xi_right_reco_multi_match->Write();
      xi_right_reco_multi_non_match->Write();
      g_xi_right_reco_multi_non_match->Write();
      diff_proton_reco_pair_xi_right_multi->Write();
      ratio_proton_reco_pair_xi_right_multi->Write();
      diff_proton_reco_pair_xi_right_multi_match->Write();
      ratio_proton_reco_pair_xi_right_multi_match->Write();

      multiplicity_0prot->Write();
      multiplicity_0prot_pt->Write();
      multiplicity_0prot_cut->Write();
      multiplicity_cut->Write();
      cut_flow->Write();
      cut_match->Write();

      f->Close();

      //cout << "oi" <<endl;
   }

   int run(std::string fileName="input.root", std::string outfileName="output_cut.root", bool resample=false, unsigned int number_of_samples=-1, bool reweighting=false) {
      ntp1 m( fileName, outfileName );
      m.SetResample( resample );
      m.SetNumberOfSamples( number_of_samples );
      m.SetReweight( reweighting );

      m.Loop();

      return 0;
   }

