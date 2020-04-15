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
#include <TPad.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
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

   //variables used in the signal region determination
   bool match = false;
   unsigned int n_sigmas_xi = 2.;

   //variable binning 
   const int nbins_left = 5;
   double bins_left[nbins_left+1] = {0, 0.02, 0.035, 0.05, 0.1, 0.16};
   const int nbins_right = 4;
   double bins_right[nbins_right+1] = {0, 0.03, 0.05, 0.1, 0.16};
   const int nbons = 55;
   double bons[nbons+1] = {0,1,2,3,4,5,6,7,8,9,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100};

   TH1::SetDefaultSumw2( true );

   TH1D *h_crossing_angle = new TH1D("h_crossing_angle", "CrossingAngle", 70, 90, 160);

   TH1D *PrimVertex_ndof = new TH1D("PrimVertex_ndof", "PrimVertexCand_ndof", 200, 0, 200);
   TH1D *PrimVertex_chi2 = new TH1D("PrimVertex_chi2", "PrimVertexCand_chi2", 100, 0, 200);
   TH1D *mumu_mass = new TH1D("mumu_mass", "#mu^{+}#mu^{-} Mass", 20, 0, 600);
   TH1D *mumu_pt = new TH1D("mumu_pt", "#mu^{+}#mu^{-} p_{T}", 20, 0, 25);
   TH1D *mumu_y = new TH1D("mumu_y", "#mu^{+}#mu^{-} y", 20, -3, 3);

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
   TH1D *proton_left_reco_rp3_ThX_match = new TH1D("proton_left_reco_rp3_ThX_match", "Proton Left Theta X - Matching Events - RP 3", 20, -0.0002, 0.0002); 
   TH1D *proton_left_reco_rp3_ThY_match = new TH1D("proton_left_reco_rp3_ThY_match", "Proton Left Theta Y - Matching Events - RP 3", 20, -0.03, 0.03); 

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
   TH1D *proton_xi_left_rp23_match = new TH1D("proton_xi_left_rp23_match", "#xi Proton Left - Match - RP 23", nbins_left, bins_left);
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
   TH1D *proton_left_reco_rp23_ThX_match = new TH1D("proton_left_reco_rp23_ThX_match", "Proton Left Theta X - Matching Events - RP 23", 20, -0.0002, 0.0002); 
   TH1D *proton_left_reco_rp23_ThY_match = new TH1D("proton_left_reco_rp23_ThY_match", "Proton Left Theta Y - Matching Events - RP 23", 20, -0.03, 0.03); 

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //n protons
   TH1D *proton_xi_left_rp23_nprot = new TH1D("proton_xi_left_rp23_nprot", "#xi Proton Left - RP 23", 10, 0, 0.16);
   TH1D *proton_xi_left_rp23_nprot_match = new TH1D("proton_xi_left_rp23_nprot_match", "#xi Proton Left - Match - RP 23", nbins_left, bins_left);
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
   TH1D *proton_left_reco_rp23_ThX_nprot_match = new TH1D("proton_left_reco_rp23_ThX_nprot_match", "Proton Left Theta X - Matching Events - RP 23", 20, -0.0002, 0.0002); 
   TH1D *proton_left_reco_rp23_ThY_nprot_match = new TH1D("proton_left_reco_rp23_ThY_nprot_match", "Proton Left Theta Y - Matching Events - RP 23", 20, -0.03, 0.03); 

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
   TH1D *proton_right_reco_rp103_ThX_match = new TH1D("proton_right_reco_rp103_ThX_match", "Proton Right Theta X - Matching Events - RP 103", 20, -0.0002, 0.0002); 
   TH1D *proton_right_reco_rp103_ThY_match = new TH1D("proton_right_reco_rp103_ThY_match", "Proton Right Theta Y - Matching Events - RP 103", 20, -0.03, 0.03); 

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
   TH1D *proton_xi_right_rp123_match = new TH1D("proton_xi_right_rp123_match", "#xi Proton Right - Match - RP 123", nbins_right, bins_right);
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
   TH1D *proton_right_reco_rp123_ThX_match = new TH1D("proton_right_reco_rp123_ThX_match", "Proton Right Theta X - Matching Events - RP 123", 20, -0.0002, 0.0002); 
   TH1D *proton_right_reco_rp123_ThY_match = new TH1D("proton_right_reco_rp123_ThY_match", "Proton Right Theta Y - Matching Events - RP 123", 20, -0.03, 0.03); 

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //n protons
   TH1D *proton_xi_right_rp123_nprot = new TH1D("proton_xi_right_rp123_nprot", "#xi Proton Right - RP 123", 10, 0, 0.16);
   TH1D *proton_xi_right_rp123_nprot_match = new TH1D("proton_xi_right_rp123_nprot_match", "#xi Proton Right - Match - RP 123", nbins_right, bins_right);
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
   TH1D *proton_right_reco_rp123_ThX_nprot_match = new TH1D("proton_right_reco_rp123_ThX_nprot_match", "Proton Right Theta X - Matching Events - RP 123", 20, -0.0002, 0.0002); 
   TH1D *proton_right_reco_rp123_ThY_nprot_match = new TH1D("proton_right_reco_rp123_ThY_nprot_match", "Proton Right Theta Y - Matching Events - RP 123", 20, -0.03, 0.03); 

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
   TH1D *proton_xi_left_multi_match = new TH1D("proton_xi_left_multi_match", "#xi Proton Left - Match - Multi RP", nbins_left, bins_left);
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
   TH1D *proton_left_reco_multi_ThX_match = new TH1D("proton_left_reco_multi_ThX_match", "Proton Left Theta X - Matching Events - Multi RP", 6, -0.0002, 0.0002); 
   TH1D *proton_left_reco_multi_ThY_match = new TH1D("proton_left_reco_multi_ThY_match", "Proton Left Theta Y - Matching Events - Multi RP", 6, -0.0002, 0.0002); 

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////RIGHT MULTI///////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   TH1D *proton_xi_right_multi = new TH1D("proton_xi_right_multi", "#xi Proton Right - Multi RP", 10, 0, 0.16);
   TH1D *proton_xi_right_multi_match = new TH1D("proton_xi_right_multi_match", "#xi Proton Right - Match - Multi RP", nbins_right, bins_right);
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
   TH1D *proton_right_reco_multi_ThX_match = new TH1D("proton_right_reco_multi_ThX_match", "Proton Right Theta X - Matching Events - Multi RP", 6, -0.0002, 0.0002); 
   TH1D *proton_right_reco_multi_ThY_match = new TH1D("proton_right_reco_multi_ThY_match", "Proton Right Theta Y - Matching Events - Multi RP", 6, -0.0002, 0.0002); 

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   TH1D *razao_1prot = new TH1D("razao_1prot", "Razao pelo 1 menos um proton", 4, 0, 4);   

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

   //sigma(xi) versus xi - determination of the signal region
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

   //cutflow
   int zerocortes = 0;
   int umcortes = 0;
   int doiscortes = 0;
   int trescortes = 0;
   int quatrocortes = 0;
   int cincocortes = 0;
   int seiscortes = 0;
   int setecortes = 0;
   int oitocortes = 0;

   //signal region cut 
   int corte_match_rp3 = 0;
   int corte_match_rp23_nprot = 0;
   int corte_match_rp23_1prot = 0;
   int corte_match_rp103 = 0;
   int corte_match_rp123_nprot = 0;
   int corte_match_rp123_1prot = 0;
   int corte_match_left_multi = 0;
   int corte_match_right_multi = 0;

   //number of events
   double cont_total = 0;
   double cont_event_rp23_1prot = 0;
   double cont_event_45_1prot = 0;
   double cont_event_rp123_1prot = 0;
   double cont_event_56_1prot = 0;

   //ttree loop 
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      cont_total++;

      h_crossing_angle->Fill(CrossingAngle);
      //if (CrossingAngle < 120) cout << "xangle: " << CrossingAngle << endl;

      //variables used to obtain the number of protons for each case studied 
      //total 
      double cont_prot = 0;

      //left
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
      double single_rp23_ThX = -999;
      double single_rp23_ThY = -999;
      double single_rp3_xi = -999;
      double single_rp3_trackx1 = -999;
      double single_rp3_tracky1 = -999;
      double single_rp3_trackx2 = -999;
      double single_rp3_tracky2 = -999;
      int cont_single_rp23 = 0;
      
      //right
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
      double single_rp123_ThX = -999;
      double single_rp123_ThY = -999;
      int cont_single_rp123 = 0;

      //study on the primary vertex options 
      int contador_PV = 0, contador_PV2 = 0, contador_PV3 = 0, contador_ext_PV = 0, contador_ext_PV2 = 0, contador_ext_PV3 = 0;
      int contador_PV_dz02 = 0, contador_PV2_dz02 = 0, contador_PV3_dz02 = 0, contador_ext_PV_dz02 = 0, contador_ext_PV2_dz02 = 0, contador_ext_PV3_dz02 = 0;
      int contador_PV_dz01 = 0, contador_PV2_dz01 = 0, contador_PV3_dz01 = 0, contador_ext_PV_dz01 = 0, contador_ext_PV2_dz01 = 0, contador_ext_PV3_dz01 = 0;
      
      //xi equation for the muon pair on the central system (CMS)
      double xi_pair_left_reco = (1./13000) * ( MuonCand_pt[0]*exp( MuonCand_eta[0] ) + MuonCand_pt[1]*exp( MuonCand_eta[1] ) );
      double xi_pair_right_reco = (1./13000) * ( MuonCand_pt[0]*exp( -MuonCand_eta[0] ) + MuonCand_pt[1]*exp( -MuonCand_eta[1] ) );

      //TLorentzVector for the two muons and for the muon pair
      TLorentzVector mu1;
      TLorentzVector mu2;
      TLorentzVector v;

      mu1.SetPtEtaPhiM(MuonCand_pt[0],MuonCand_eta[0],MuonCand_phi[0],0.1057);
      mu2.SetPtEtaPhiM(MuonCand_pt[1],MuonCand_eta[1],MuonCand_phi[1],0.1057);
      v.SetPxPyPzE(0,0,0,0);
      v += mu1; v += mu2;

      //acoplanarity of the muon pair
      double a = 1 - fabs(deltaPhi(mu1.Phi(),mu2.Phi()))/PI;
      zerocortes++;		

      //diff between the muon 1 vertex and muon 2 vertex
      mu1_z_mu2_z->Fill(MuonCand_vtxz[0] - MuonCand_vtxz[1]);
      //diff between the muon 1 vertex and the primary vertex
      mu1_z_primvertex_z->Fill(MuonCand_vtxz[0] - PrimVertexCand_z[0]);
      //diff between the muon 2 vertex and the primary vertex
      mu2_z_primvertex_z->Fill(MuonCand_vtxz[1] - PrimVertexCand_z[0]);

      double cont_prot_rp23 = 0;
      double cont_prot_45 = 0;
      double cont_prot_rp123 = 0;
      double cont_prot_56 = 0;
      //loop for the protons
      for ( unsigned int idx = 0; idx < nRecoProtCand; ++idx ) {
         //total number of protons 
         cont_prot++;
         //number of protons on RP 23
         if(ProtCand_rpid[idx] == 23) cont_prot_rp23++;
         //number of protons on RP 3
         if(ProtCand_rpid[idx] == 3 || ProtCand_rpid[idx] == 23) cont_prot_45++;
         //number of protons on RP 123
         if(ProtCand_rpid[idx] == 123) cont_prot_rp123++;
         //number of protons on RP 103
         if(ProtCand_rpid[idx] == 103 || ProtCand_rpid[idx] == 123) cont_prot_56++;
      }
      //events with at least 1 proton
      if(cont_prot_rp23 > 0) cont_event_rp23_1prot++;
      if(cont_prot_45 > 0) cont_event_45_1prot++;
      if(cont_prot_rp123 > 0) cont_event_rp123_1prot++;
      if(cont_prot_56 > 0) cont_event_56_1prot++;

      //study on the primary vertex options 
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

      //number of extra tracks on events without protons and without any cut applied
      if (cont_prot==0) multiplicity_0prot->Fill(contador_ext_PV3);
      
      //selection cuts 
      if(MuonCand_pt[0] > 50 && MuonCand_pt[1] > 50 && MuonCand_eta[0] <= 2.4 && MuonCand_eta[1] <= 2.4){ 
         umcortes++;
         if (cont_prot==0) multiplicity_0prot_pt->Fill(contador_ext_PV3);
         if(MuonCand_charge[0] * MuonCand_charge[1] < 0){
            doiscortes++;
            if(MuonCand_istight[0] && MuonCand_istight[1]){
               trescortes++;
               if(v.M() > 110.){
                  quatrocortes++;
                  if( fabs( PrimVertexCand_z[0] ) < 15.){
                     cincocortes++;
                     PrimVertex_ndof->Fill(PrimVertexCand_ndof[0]);
                     PrimVertex_chi2->Fill(PrimVertexCand_chi2[0]);
                     if((fabs(MuonCand_vtxz[0] - PrimVertexCand_z[0]) < 3*0.004) && (fabs(MuonCand_vtxz[1] - PrimVertexCand_z[0]) < 3*0.004)){
                        seiscortes++;
                        if(a < 0.009){
                           setecortes++;
                           //number of extra tracks on events without protons and with all cuts applied
                           if (cont_prot==0) multiplicity_0prot_cut->Fill(contador_ext_PV3);
                           //number of extra tracks on events with all cuts applied
                           multiplicity_cut->Fill(contador_ext_PV3);

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

                           //at least three extra tracks 
                           if(contador_ext_PV3 <= 3){
                              oitocortes++;
                              mumu_mass->Fill(v.M());
                              mumu_pt->Fill(v.Pt());
                              mumu_y->Fill(v.Rapidity());
                              //sigma for the muon pair 
                              double sigma_xi_mumu_left = f_pair_left->Eval( xi_pair_left_reco );
                              double sigma_xi_mumu_right = f_pair_right->Eval( xi_pair_right_reco );
                              
                              //loop for the protons
                              for ( unsigned int idx = 0; idx < nRecoProtCand; ++idx ) {
                                 cont_prot++;

                                 //study on events without restriction on the number of protons

                                 //fiducial cuts
                                 bool fid_45 = false;
                                 bool fid_56 = false;
                                 if(ProtCand_xi[idx] >= .02 && ProtCand_trackx1[idx] >= 1.995 && ProtCand_trackx1[idx] <= 24.334 && ProtCand_tracky1[idx] >= -10.098 && ProtCand_tracky1[idx] <= 4.298) fid_45 = true;
                                 if(ProtCand_xi[idx] >= .03 && ProtCand_trackx1[idx] >= 2.422 && ProtCand_trackx1[idx] <= 24.620 && ProtCand_tracky1[idx] >= -9.698 && ProtCand_tracky1[idx] <= 4.698) fid_56 = true;
                                 if (ProtCand_trackpixshift1[idx] == 0) {    
                                    //left side - single RP        
                                    if(fid_45) {
                                       //RP 3 
                                       if (ProtCand_rpid[idx] == 3) {
                                          if (ProtCand_ismultirp[idx] == 0) {
                                             //only muon selection cuts
                                             proton_xi_left_rp3->Fill(ProtCand_xi[idx]);
                                             pair_xi_left_rp3->Fill(xi_pair_left_reco);
                                             xi_left_reco_rp3->Fill(ProtCand_xi[idx], xi_pair_left_reco); 
                                             g_xi_left_reco_rp3->SetPoint(g_xi_left_reco_rp3->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                             diff_proton_reco_pair_xi_left_rp3->Fill(ProtCand_xi[idx] - xi_pair_left_reco); 
                                             ratio_proton_reco_pair_xi_left_rp3->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco); 
                                             double sigma_xi_RP3 = f_rp3->Eval( ProtCand_xi[idx] );
                                             if ( sigma_xi_RP3 > 0.) {
                                                double sigma_xi_rp3_mumu = TMath::Sqrt( sigma_xi_RP3*sigma_xi_RP3 + sigma_xi_mumu_left*sigma_xi_mumu_left );
                                                //inside signal region 
                                                if ( TMath::Abs( ProtCand_xi[idx] - xi_pair_left_reco ) <= n_sigmas_xi*sigma_xi_rp3_mumu ) {
                                                   match = true;
                                                   corte_match_rp3++;
                                                   proton_xi_left_rp3_match->Fill(ProtCand_xi[idx]);
                                                   diff_proton_reco_pair_xi_left_rp3_match->Fill(ProtCand_xi[idx] - xi_pair_left_reco); 
                                                   ratio_proton_reco_pair_xi_left_rp3_match->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco); 
                                                   xi_left_reco_rp3_match->Fill(ProtCand_xi[idx], xi_pair_left_reco);
                                                   g_xi_left_reco_rp3_match->SetPoint(g_xi_left_reco_rp3_match->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                                }
                                                //outside signal region
                                                else {
                                                   xi_left_reco_rp3_non_match->Fill(ProtCand_xi[idx], xi_pair_left_reco);
                                                   g_xi_left_reco_rp3_non_match->SetPoint(g_xi_left_reco_rp3_non_match->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                                }
                                             }       
                                          }		
                                       }
                                       
                                       //RP 23
                                       if (ProtCand_rpid[idx] == 23) {
                                          if (ProtCand_ismultirp[idx] == 0) {
                                             //only muon selection cuts
                                             proton_xi_left_rp23_nprot->Fill(ProtCand_xi[idx]);
                                             pair_xi_left_rp23_nprot->Fill(xi_pair_left_reco);
                                             xi_left_reco_rp23_nprot->Fill(ProtCand_xi[idx], xi_pair_left_reco); 
                                             g_xi_left_reco_rp23_nprot->SetPoint(g_xi_left_reco_rp23_nprot->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                             diff_proton_reco_pair_xi_left_rp23_nprot->Fill(ProtCand_xi[idx] - xi_pair_left_reco); 
                                             ratio_proton_reco_pair_xi_left_rp23_nprot->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco); 
                                             double sigma_xi_RP23_nprot = f_rp23_nprot->Eval( ProtCand_xi[idx] );
                                             if ( sigma_xi_RP23_nprot > 0.) {
                                                double sigma_xi_rp23_nprot_mumu = TMath::Sqrt( sigma_xi_RP23_nprot*sigma_xi_RP23_nprot + sigma_xi_mumu_left*sigma_xi_mumu_left );
                                                //inside signal region 
                                                if ( TMath::Abs( ProtCand_xi[idx] - xi_pair_left_reco ) <= n_sigmas_xi*sigma_xi_rp23_nprot_mumu ) {
                                                   match = true;
                                                   corte_match_rp23_nprot++;
                                                   proton_xi_left_rp23_nprot_match->Fill(ProtCand_xi[idx]);
                                                   diff_proton_reco_pair_xi_left_rp23_nprot_match->Fill(ProtCand_xi[idx] - xi_pair_left_reco); 
                                                   ratio_proton_reco_pair_xi_left_rp23_nprot_match->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco); 
                                                   xi_left_reco_rp23_nprot_match->Fill(ProtCand_xi[idx], xi_pair_left_reco);
                                                   g_xi_left_reco_rp23_nprot_match->SetPoint(g_xi_left_reco_rp23_nprot_match->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                                   proton_left_reco_rp23_ThX_nprot_match->Fill(ProtCand_ThX[idx]);
                                                   proton_left_reco_rp23_ThY_nprot_match->Fill(ProtCand_ThY[idx]);
                                                }
                                                //outside signal region
                                                else {
                                                   xi_left_reco_rp23_nprot_non_match->Fill(ProtCand_xi[idx], xi_pair_left_reco);
                                                   g_xi_left_reco_rp23_nprot_non_match->SetPoint(g_xi_left_reco_rp23_nprot_non_match->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                                }
                                             }
                                          }		
                                       }
                                       
                                       //RP 3 
                                       if(ProtCand_rpid[idx] == 3 && ProtCand_ismultirp[idx] == 0){
                                          single_rp3_xi = ProtCand_xi[idx];
                                          single_rp3_trackx1 = ProtCand_trackx1[idx];
                                          single_rp3_tracky1 = ProtCand_tracky1[idx];
                                       }

                                       //RP 23 
                                       if(ProtCand_rpid[idx] == 23 && ProtCand_ismultirp[idx] == 0){
                                          single_rp23_xi = ProtCand_xi[idx];
                                          single_rp23_trackx1 = ProtCand_trackx1[idx];
                                          single_rp23_tracky1 = ProtCand_tracky1[idx];
                                          single_rp23_ThX = ProtCand_ThX[idx];
                                          single_rp23_ThY = ProtCand_ThY[idx];
                                          cont_single_rp23++; 
                                       }
                                    }

                                    //right side - single RP
                                    if(fid_56) { 
                                       //RP 103  
                                       if (ProtCand_rpid[idx] == 103) {                           
                                          if (ProtCand_ismultirp[idx] == 0) {
                                             proton_xi_right_rp103->Fill(ProtCand_xi[idx]);
                                             pair_xi_right_rp103->Fill(xi_pair_right_reco);
                                             xi_right_reco_rp103->Fill(ProtCand_xi[idx], xi_pair_right_reco);
                                             g_xi_right_reco_rp103->SetPoint(g_xi_right_reco_rp103->GetN(), ProtCand_xi[idx], xi_pair_right_reco);
                                             diff_proton_reco_pair_xi_right_rp103->Fill(ProtCand_xi[idx] - xi_pair_right_reco); 
                                             ratio_proton_reco_pair_xi_right_rp103->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco); 
                                             double sigma_xi_RP103 = f_rp103->Eval( ProtCand_xi[idx] );
                                             if ( sigma_xi_RP103 > 0.) {
                                                double sigma_xi_rp103_mumu = TMath::Sqrt( sigma_xi_RP103*sigma_xi_RP103 + sigma_xi_mumu_right*sigma_xi_mumu_right );
                                                //inside signal region 
                                                if ( TMath::Abs( ProtCand_xi[idx] - xi_pair_right_reco ) <= n_sigmas_xi*sigma_xi_rp103_mumu ) {
                                                   match = true;
                                                   corte_match_rp103++;
                                                   proton_xi_right_rp103_match->Fill(ProtCand_xi[idx]);
                                                   diff_proton_reco_pair_xi_right_rp103_match->Fill(ProtCand_xi[idx] - xi_pair_right_reco); 
                                                   ratio_proton_reco_pair_xi_right_rp103_match->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco); 
                                                   xi_right_reco_rp103_match->Fill(ProtCand_xi[idx], xi_pair_right_reco);
                                                   g_xi_right_reco_rp103_match->SetPoint(g_xi_right_reco_rp103_match->GetN(), ProtCand_xi[idx], xi_pair_right_reco);
                                                }
                                                //outside signal region 
                                                else {
                                                   xi_right_reco_rp103_non_match->Fill(ProtCand_xi[idx], xi_pair_right_reco);
                                                   g_xi_right_reco_rp103_non_match->SetPoint(g_xi_right_reco_rp103_non_match->GetN(), ProtCand_xi[idx], xi_pair_right_reco);
                                                }
                                             }       
                                          }		
                                       }

                                       //RP 123
                                       if (ProtCand_rpid[idx] == 123) {                           
                                          if (ProtCand_ismultirp[idx] == 0) {
                                             proton_xi_right_rp123_nprot->Fill(ProtCand_xi[idx]);
                                             pair_xi_right_rp123_nprot->Fill(xi_pair_right_reco);
                                             xi_right_reco_rp123_nprot->Fill(ProtCand_xi[idx], xi_pair_right_reco);
                                             g_xi_right_reco_rp123_nprot->SetPoint(g_xi_right_reco_rp123_nprot->GetN(), ProtCand_xi[idx], xi_pair_right_reco);
                                             diff_proton_reco_pair_xi_right_rp123_nprot->Fill(ProtCand_xi[idx] - xi_pair_right_reco); 
                                             ratio_proton_reco_pair_xi_right_rp123_nprot->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco); 
                                             double sigma_xi_RP123_nprot = f_rp123_nprot->Eval( ProtCand_xi[idx] );
                                             if ( sigma_xi_RP123_nprot > 0.) {
                                                double sigma_xi_rp123_nprot_mumu = TMath::Sqrt( sigma_xi_RP123_nprot*sigma_xi_RP123_nprot + sigma_xi_mumu_right*sigma_xi_mumu_right );
                                                //inside signal region 
                                                if ( TMath::Abs( ProtCand_xi[idx] - xi_pair_right_reco ) <= n_sigmas_xi*sigma_xi_rp123_nprot_mumu ) { 
                                                   match = true;
                                                   corte_match_rp123_nprot++;
                                                   proton_xi_right_rp123_nprot_match->Fill(ProtCand_xi[idx]);
                                                   diff_proton_reco_pair_xi_right_rp123_nprot_match->Fill(ProtCand_xi[idx] - xi_pair_right_reco); 
                                                   ratio_proton_reco_pair_xi_right_rp123_nprot_match->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco); 
                                                   xi_right_reco_rp123_nprot_match->Fill(ProtCand_xi[idx], xi_pair_right_reco);
                                                   g_xi_right_reco_rp123_nprot_match->SetPoint(g_xi_right_reco_rp123_nprot_match->GetN(), ProtCand_xi[idx], xi_pair_right_reco);
                                                   proton_right_reco_rp123_ThX_nprot_match->Fill(ProtCand_ThX[idx]);
                                                   proton_right_reco_rp123_ThY_nprot_match->Fill(ProtCand_ThY[idx]);
                                                }
                                                //outside signal region 
                                                else {
                                                   xi_right_reco_rp123_nprot_non_match->Fill(ProtCand_xi[idx], xi_pair_right_reco);
                                                   g_xi_right_reco_rp123_nprot_non_match->SetPoint(g_xi_right_reco_rp123_nprot_non_match->GetN(), ProtCand_xi[idx], xi_pair_right_reco);
                                                }
                                             }       
                                          }		
                                       }
                                       
                                       //RP 103
                                       if(ProtCand_rpid[idx] == 103 && ProtCand_ismultirp[idx] == 0){
                                          single_rp103_xi = ProtCand_xi[idx];
                                          single_rp103_trackx1 = ProtCand_trackx1[idx];
                                          single_rp103_tracky1 = ProtCand_tracky1[idx];
                                       }

                                       //RP 123
                                       if(ProtCand_rpid[idx] == 123 && ProtCand_ismultirp[idx] == 0){
                                          single_rp123_xi = ProtCand_xi[idx];
                                          single_rp123_trackx1 = ProtCand_trackx1[idx];
                                          single_rp123_tracky1 = ProtCand_tracky1[idx];
                                          single_rp123_ThX = ProtCand_ThX[idx];
                                          single_rp123_ThY = ProtCand_ThY[idx];
                                          cont_single_rp123++; 
                                       }
                                    }
                                 }

                                 if (ProtCand_trackpixshift2[idx] == 0) { 
                                    //left side - multi RP
                                    if(fid_45) {  
                                       if (ProtCand_arm[idx] == 0) {
                                          if (ProtCand_ismultirp[idx] == 1) {
                                             proton_xi_left_multi->Fill(ProtCand_xi[idx]);
                                             pair_xi_left_multi->Fill(xi_pair_left_reco);
                                             xi_left_reco_multi->Fill(ProtCand_xi[idx], xi_pair_left_reco); 
                                             g_xi_left_reco_multi->SetPoint(g_xi_left_reco_multi->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                             diff_proton_reco_pair_xi_left_multi->Fill(ProtCand_xi[idx] - xi_pair_left_reco); 
                                             ratio_proton_reco_pair_xi_left_multi->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco); 
                                             double sigma_xi_left_multi = f_left_multi->Eval( ProtCand_xi[idx] );
                                             if ( sigma_xi_left_multi > 0.) {
                                                double sigma_xi_lm_mumu = TMath::Sqrt( sigma_xi_left_multi*sigma_xi_left_multi + sigma_xi_mumu_left*sigma_xi_mumu_left );
                                                //inside signal region
                                                if ( TMath::Abs( ProtCand_xi[idx] - xi_pair_left_reco ) <= n_sigmas_xi*sigma_xi_lm_mumu ) { 
                                                   match = true;
                                                   corte_match_left_multi++;
                                                   proton_xi_left_multi_match->Fill(ProtCand_xi[idx]);
                                                   diff_proton_reco_pair_xi_left_multi_match->Fill(ProtCand_xi[idx] - xi_pair_left_reco); 
                                                   ratio_proton_reco_pair_xi_left_multi_match->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco); 
                                                   xi_left_reco_multi_match->Fill(ProtCand_xi[idx], xi_pair_left_reco);
                                                   g_xi_left_reco_multi_match->SetPoint(g_xi_left_reco_multi_match->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                                   proton_left_reco_multi_ThX_match->Fill(ProtCand_ThX[idx]);
                                                   proton_left_reco_multi_ThY_match->Fill(ProtCand_ThY[idx]);
                                                }
                                                //outside signal region
                                                else { 
                                                   xi_left_reco_multi_non_match->Fill(ProtCand_xi[idx], xi_pair_left_reco);
                                                   g_xi_left_reco_multi_non_match->SetPoint(g_xi_left_reco_multi_non_match->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                                }
                                             }
                                          }		
                                       }
                                    }

                                    //right side - multi RP
                                    if (ProtCand_arm[idx] == 1) {                           
                                       if(fid_56) { 
                                          if (ProtCand_ismultirp[idx] == 1) {
                                             proton_xi_right_multi->Fill(ProtCand_xi[idx]);
                                             pair_xi_right_multi->Fill(xi_pair_right_reco);
                                             xi_right_reco_multi->Fill(ProtCand_xi[idx], xi_pair_right_reco);
                                             g_xi_right_reco_multi->SetPoint(g_xi_right_reco_multi->GetN(), ProtCand_xi[idx], xi_pair_right_reco);
                                             diff_proton_reco_pair_xi_right_multi->Fill(ProtCand_xi[idx] - xi_pair_right_reco); 
                                             ratio_proton_reco_pair_xi_right_multi->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco); 
                                             double sigma_xi_right_multi = f_right_multi->Eval( ProtCand_xi[idx] );
                                             if ( sigma_xi_right_multi > 0.) {
                                                double sigma_xi_rm_mumu = TMath::Sqrt( sigma_xi_right_multi*sigma_xi_right_multi + sigma_xi_mumu_right*sigma_xi_mumu_right );
                                                //inside signal region
                                                if ( TMath::Abs( ProtCand_xi[idx] - xi_pair_right_reco ) <= n_sigmas_xi*sigma_xi_rm_mumu ) {
                                                   match = true;
                                                   corte_match_right_multi++;
                                                   proton_xi_right_multi_match->Fill(ProtCand_xi[idx]);
                                                   diff_proton_reco_pair_xi_right_multi_match->Fill(ProtCand_xi[idx] - xi_pair_right_reco); 
                                                   ratio_proton_reco_pair_xi_right_multi_match->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco); 
                                                   xi_right_reco_multi_match->Fill(ProtCand_xi[idx], xi_pair_right_reco);
                                                   g_xi_right_reco_multi_match->SetPoint(g_xi_right_reco_multi_match->GetN(), ProtCand_xi[idx], xi_pair_right_reco);
                                                   proton_right_reco_multi_ThX_match->Fill(ProtCand_ThX[idx]);
                                                   proton_right_reco_multi_ThY_match->Fill(ProtCand_ThY[idx]);
                                                }
                                                //outside signal region
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

                              //study on events with only 1 proton (analogous to the previous section)

                              bool fid_45_1prot = false;
                              bool fid_56_1prot = false;
                              if(single_rp23_xi >= .02 && single_rp23_trackx1 >= 1.995 && single_rp23_trackx1 <= 24.334 && single_rp23_tracky1 >= -10.098 && single_rp23_tracky1 <= 4.298) fid_45_1prot = true;
                              if(single_rp123_xi >= .03 && single_rp123_trackx1 >= 2.422 && single_rp123_trackx1 <= 24.620 && single_rp123_tracky1 >= -9.698 && single_rp123_tracky1 <= 4.698) fid_56_1prot = true;

                              if (cont_single_rp23==1 && fid_45_1prot){
                                 mumu_mass_rp23->Fill(v.M());
                                 mumu_pt_rp23->Fill(v.Pt());
                                 mumu_y_rp23->Fill(v.Rapidity());
                                 proton_xi_left_rp23->Fill(single_rp23_xi);
                                 pair_xi_left_rp23->Fill(xi_pair_left_reco);
                                 xi_left_reco_rp23->Fill(single_rp23_xi,xi_pair_left_reco);
                                 g_xi_left_reco_rp23->SetPoint(g_xi_left_reco_rp23->GetN(), single_rp23_xi, xi_pair_left_reco);
                                 diff_proton_reco_pair_xi_left_rp23->Fill(single_rp23_xi - xi_pair_left_reco); 
                                 ratio_proton_reco_pair_xi_left_rp23->Fill(1 - single_rp23_xi/xi_pair_left_reco); 
                                 double sigma_xi_left_rp23 = f_rp23->Eval( single_rp23_xi );
                                 if ( sigma_xi_left_rp23 > 0.) {
                                    double sigma_xi_rp23_mumu = TMath::Sqrt( sigma_xi_left_rp23*sigma_xi_left_rp23 + sigma_xi_mumu_left*sigma_xi_mumu_left );
                                    if ( TMath::Abs( single_rp23_xi - xi_pair_left_reco ) <= n_sigmas_xi*sigma_xi_rp23_mumu ) {
                                       match = true;
                                       corte_match_rp23_1prot++;
                                       mumu_mass_rp23_match->Fill(v.M());
                                       mumu_pt_rp23_match->Fill(v.Pt());
                                       mumu_y_rp23_match->Fill(v.Rapidity());
                                       proton_xi_left_rp23_match->Fill(single_rp23_xi);
                                       pair_xi_left_rp23_match->Fill(xi_pair_left_reco);
                                       diff_proton_reco_pair_xi_left_rp23_match->Fill(single_rp23_xi - xi_pair_left_reco); 
                                       ratio_proton_reco_pair_xi_left_rp23_match->Fill(1 - single_rp23_xi/xi_pair_left_reco); 
                                       xi_left_reco_rp23_match->Fill(single_rp23_xi, xi_pair_left_reco);
                                       g_xi_left_reco_rp23_match->SetPoint(g_xi_left_reco_rp23_match->GetN(), single_rp23_xi, xi_pair_left_reco);
                                       proton_left_reco_rp23_ThX_match->Fill(single_rp23_ThX);
                                       proton_left_reco_rp23_ThY_match->Fill(single_rp23_ThY);
                                    }
                                    else {
                                       xi_left_reco_rp23_non_match->Fill(single_rp23_xi, xi_pair_left_reco);
                                       g_xi_left_reco_rp23_non_match->SetPoint(g_xi_left_reco_rp23_non_match->GetN(), single_rp23_xi, xi_pair_left_reco);
                                    }
                                 }
                              }
                              if (cont_single_rp23==1 && fid_45_1prot){
                                 single_left_xi = single_rp23_xi;
                                 proton_xi_left_single->Fill(single_left_xi);
                                 xi_left_reco_single->Fill(single_left_xi,xi_pair_left_reco);
                                 g_xi_left_reco_single->SetPoint(g_xi_left_reco_single->GetN(), single_left_xi, xi_pair_left_reco);
                                 diff_proton_reco_pair_xi_left_single->Fill(single_left_xi - xi_pair_left_reco); 
                                 ratio_proton_reco_pair_xi_left_single->Fill(1 - single_left_xi/xi_pair_left_reco); 
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
                                 proton_xi_left_single->Fill(single_left_xi);
                                 xi_left_reco_single->Fill(single_left_xi,xi_pair_left_reco);
                                 g_xi_left_reco_single->SetPoint(g_xi_left_reco_single->GetN(), single_left_xi, xi_pair_left_reco);
                                 diff_proton_reco_pair_xi_left_single->Fill(single_left_xi - xi_pair_left_reco); 
                                 ratio_proton_reco_pair_xi_left_single->Fill(1 - single_left_xi/xi_pair_left_reco); 
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

                              if (cont_single_rp123==1 && fid_56_1prot){
                                 mumu_mass_rp123->Fill(v.M());
                                 mumu_pt_rp123->Fill(v.Pt());
                                 mumu_y_rp123->Fill(v.Rapidity());
                                 proton_xi_right_rp123->Fill(single_rp123_xi);
                                 pair_xi_right_rp123->Fill(xi_pair_right_reco);
                                 xi_right_reco_rp123->Fill(single_rp123_xi,xi_pair_right_reco);
                                 g_xi_right_reco_rp123->SetPoint(g_xi_right_reco_rp123->GetN(), single_rp123_xi, xi_pair_right_reco);
                                 diff_proton_reco_pair_xi_right_rp123->Fill(single_rp123_xi - xi_pair_right_reco); 
                                 ratio_proton_reco_pair_xi_right_rp123->Fill(1 - single_rp123_xi/xi_pair_right_reco); 
                                 double sigma_xi_right_rp123 = f_rp123->Eval( single_rp123_xi );
                                 if ( sigma_xi_right_rp123 > 0.) {
                                    double sigma_xi_rp123_mumu = TMath::Sqrt( sigma_xi_right_rp123*sigma_xi_right_rp123 + sigma_xi_mumu_right*sigma_xi_mumu_right );
                                    if ( TMath::Abs( single_rp123_xi - xi_pair_right_reco ) <= n_sigmas_xi*sigma_xi_rp123_mumu ) {
                                       match = true;
                                       corte_match_rp123_1prot++;
                                       mumu_mass_rp123_match->Fill(v.M());
                                       mumu_pt_rp123_match->Fill(v.Pt());
                                       mumu_y_rp123_match->Fill(v.Rapidity());
                                       proton_xi_right_rp123_match->Fill(single_rp123_xi);
                                       pair_xi_right_rp123_match->Fill(xi_pair_right_reco);
                                       diff_proton_reco_pair_xi_right_rp123_match->Fill(single_rp123_xi - xi_pair_right_reco); 
                                       ratio_proton_reco_pair_xi_right_rp123_match->Fill(1 - single_rp123_xi/xi_pair_right_reco); 
                                       xi_right_reco_rp123_match->Fill(single_rp123_xi, xi_pair_right_reco);
                                       g_xi_right_reco_rp123_match->SetPoint(g_xi_right_reco_rp123_match->GetN(), single_rp123_xi, xi_pair_right_reco);
                                       proton_right_reco_rp123_ThX_match->Fill(single_rp123_ThX);
                                       proton_right_reco_rp123_ThY_match->Fill(single_rp123_ThY);
                                    }
                                    else {
                                       xi_right_reco_rp123_non_match->Fill(single_rp123_xi, xi_pair_right_reco);
                                       g_xi_right_reco_rp123_non_match->SetPoint(g_xi_right_reco_rp123_non_match->GetN(), single_rp123_xi, xi_pair_right_reco);
                                    }
                                 }
                              }

                              if (cont_single_rp123==1 && fid_56_1prot){
                                 single_right_xi = single_rp123_xi;
                                 proton_xi_right_single->Fill(single_right_xi);
                                 xi_right_reco_single->Fill(single_right_xi,xi_pair_right_reco);
                                 g_xi_right_reco_single->SetPoint(g_xi_right_reco_single->GetN(), single_right_xi, xi_pair_right_reco);
                                 diff_proton_reco_pair_xi_right_single->Fill(single_right_xi - xi_pair_right_reco); 
                                 ratio_proton_reco_pair_xi_right_single->Fill(1 - single_right_xi/xi_pair_right_reco); 
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
                                 proton_xi_right_single->Fill(single_right_xi);
                                 xi_right_reco_single->Fill(single_right_xi,xi_pair_right_reco);
                                 g_xi_right_reco_single->SetPoint(g_xi_right_reco_single->GetN(), single_right_xi, xi_pair_right_reco);
                                 diff_proton_reco_pair_xi_right_single->Fill(single_right_xi - xi_pair_right_reco); 
                                 ratio_proton_reco_pair_xi_right_single->Fill(1 - single_right_xi/xi_pair_right_reco); 
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

      //print cutflow values 
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

      //print each signal region cut
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

      //ratio between events with at least one proton and the total events
      
      if(cont_event_rp23_1prot > 0) {
         cout << "Razao pelo menos 1 proton - rp23: " << cont_event_rp23_1prot/cont_total << endl;
         razao_1prot->SetBinContent(1, cont_event_rp23_1prot/cont_total);
      }   
      if(cont_event_45_1prot > 0) {
         cout << "Razao pelo menos 1 proton - 45: " << cont_event_45_1prot/cont_total << endl;
         razao_1prot->SetBinContent(2, cont_event_45_1prot/cont_total);
      }   
      if(cont_event_rp123_1prot > 0) {
         cout << "Razao pelo menos 1 proton - rp123: " << cont_event_rp123_1prot/cont_total << endl;
         razao_1prot->SetBinContent(3, cont_event_rp123_1prot/cont_total);
      }   
      if(cont_event_56_1prot > 0) {
         cout << "Razao pelo menos 1 proton - 56: " << cont_event_56_1prot/cont_total << endl;
         razao_1prot->SetBinContent(4, cont_event_56_1prot/cont_total);
      }   

      //write the histograms
      TFile* f = new TFile(outfileName.c_str(), "RECREATE");

      h_crossing_angle->Write();
      PrimVertex_ndof->Write();
      PrimVertex_chi2->Write();
      mumu_mass->Write();
      mumu_pt->Write();
      mumu_y->Write();

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
      proton_left_reco_rp23_ThX_match->Write();
      proton_left_reco_rp23_ThY_match->Write();

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
      proton_left_reco_rp23_ThX_nprot_match->Write();
      proton_left_reco_rp23_ThY_nprot_match->Write();

      proton_xi_left_single->Write();
      pair_xi_left_single->Write();
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
      proton_right_reco_rp123_ThX_match->Write();
      proton_right_reco_rp123_ThY_match->Write();

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
      proton_right_reco_rp123_ThX_nprot_match->Write();
      proton_right_reco_rp123_ThY_nprot_match->Write();

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
      proton_left_reco_multi_ThX_match->Write();
      proton_left_reco_multi_ThY_match->Write();

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
      proton_right_reco_multi_ThX_match->Write();
      proton_right_reco_multi_ThY_match->Write();

      razao_1prot->Write();

      multiplicity_0prot->Write();
      multiplicity_0prot_pt->Write();
      multiplicity_0prot_cut->Write();
      multiplicity_cut->Write();
      cut_flow->Write();
      cut_match->Write();
      f->Close();

   }

   int run(std::string fileName="input.root", std::string outfileName="output_cut.root") {
      ntp1 m(fileName, outfileName);
      m.Loop();

      return 0;
   }
