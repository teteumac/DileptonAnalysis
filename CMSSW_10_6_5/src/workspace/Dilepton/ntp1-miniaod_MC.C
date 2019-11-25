#define ntp1_cxx
#include "ntp1.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TSystem.h>
#include <TROOT.h>
#include <TH1.h>
#include <TF1.h>
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
   //
   bool match = false;
   unsigned int n_sigmas_xi = 2.;

   TH1D *PrimVertex_ndof = new TH1D("PrimVertex_ndof", "PrimVertexCand_ndof", 200, 0, 200);
   TH1D *PrimVertex_chi2 = new TH1D("PrimVertex_chi2", "PrimVertexCand_chi2", 100, 0, 200);
   TH1D *mumu_mass = new TH1D("mumu_mass", "#mu^{+}#mu^{-} Mass", 20, 0, 600);
   TH1D *mumu_pt = new TH1D("mumu_pt", "#mu^{+}#mu^{-} p_{T}", 20, 0, 25);
   TH1D *mumu_y = new TH1D("mumu_y", "#mu^{+}#mu^{-} y", 20, -3, 3);

   ////////////////////////////////////////////////////////////////////////////PROTON//////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////LEFT STRIPS//////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Sem eficiencia 
   TH1D *proton_xi_left_rp3 = new TH1D("proton_xi_left_rp3", "#xi Proton Left - RP 3", 20, 0, 0.16);
   TH1D *proton_resolution_left_gen_rp3 = new TH1D("proton_resolution_left_gen_rp3", "#xi Left gen Proton Resolution - RP 3", 20, -.8, .8);
   TH1D *proton_resolution_left_reco_rp3 = new TH1D("proton_resolution_left_reco_rp3", "#xi Left reco Proton Resolution - RP 3", 20, -.8, .8);
   TH1D *pair_xi_left_rp3 = new TH1D("pair_xi_left_rp3", "#xi Pair Left - RP 3", 20, 0, 0.16);
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
   TH1D *proton_resolution_left_rp3_1 = new TH1D("proton_resolution_left_rp3_1", "#xi Proton Left Proton Resolution - RP 3", 20, -.05, .05);
   TH1D *proton_resolution_left_rp3_2 = new TH1D("proton_resolution_left_rp3_2", "#xi Proton Left Proton Resolution - RP 3", 20, -.05, .05);
   TH1D *proton_resolution_left_rp3_3 = new TH1D("proton_resolution_left_rp3_3", "#xi Proton Left Proton Resolution - RP 3", 20, -.05, .05);
   TH1D *proton_resolution_left_rp3_4 = new TH1D("proton_resolution_left_rp3_4", "#xi Proton Left Proton Resolution - RP 3", 20, -.05, .05);
   TH1D *proton_resolution_left_rp3_5 = new TH1D("proton_resolution_left_rp3_5", "#xi Proton Left Proton Resolution - RP 3", 20, -.05, .05);
   TH1D *diff_proton_reco_pair_xi_left_rp3 = new TH1D("diff_proton_reco_pair_xi_left_rp3", "reco (Proton - Pair) #xi Left - RP 3", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_left_rp3 = new TH1D("ratio_proton_reco_pair_xi_left_rp3", "reco (1 - Proton/Pair) #xi Left - RP 3", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Com eficiencia 
   TH1D *proton_xi_left_rp3_eff = new TH1D("proton_xi_left_rp3_eff", "#xi Proton Left - RP 3", 20, 0, 0.16);
   TH1D *pair_xi_left_rp3_eff = new TH1D("pair_xi_left_rp3_eff", "#xi Pair Left - RP 3", 20, 0, 0.16);
   TH2D *xi_left_reco_rp3_eff = new TH2D("xi_left_reco_rp3_eff", "#xi Left Correlation - RP 3", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_rp3_eff = new TGraph();
   g_xi_left_reco_rp3_eff->SetName("g_xi_left_reco_rp3_eff");
   g_xi_left_reco_rp3_eff->SetTitle("#xi Left Correlation - RP 3");
   TH2D *xi_left_reco_rp3_eff_match = new TH2D("xi_left_reco_rp3_eff_match", "#xi Left Correlation - Matching Events - RP 3", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_rp3_eff_match = new TGraph(); 
   g_xi_left_reco_rp3_eff_match->SetName("g_xi_left_reco_rp3_eff_match");
   g_xi_left_reco_rp3_eff_match->SetTitle("#xi Left Correlation - Matching Events - RP 3");
   TH2D *xi_left_reco_rp3_eff_non_match = new TH2D("xi_left_reco_rp3_eff_non_match", "#xi Left Correlation - Non-Matching Events - RP 3", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_rp3_eff_non_match = new TGraph(); 
   g_xi_left_reco_rp3_eff_non_match->SetName("g_xi_left_reco_rp3_eff_non_match");
   g_xi_left_reco_rp3_eff_non_match->SetTitle("#xi Left Correlation - Non-Matching Events - RP 3");
   TH1D *diff_proton_reco_pair_xi_left_rp3_eff = new TH1D("diff_proton_reco_pair_xi_left_rp3_eff", "reco (Proton - Pair) #xi Left - RP 3", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_left_rp3_eff = new TH1D("ratio_proton_reco_pair_xi_left_rp3_eff", "reco (1 - Proton/Pair) #xi Left - RP 3", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////LEFT PIXEL///////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Sem eficiencia - 1 proton
   TH1D *proton_xi_left_rp23 = new TH1D("proton_xi_left_rp23", "#xi Proton Left - RP 23", 20, 0, 0.16);
   TH1D *proton_resolution_left_gen_rp23 = new TH1D("proton_resolution_left_gen_rp23", "#xi Left gen Proton Resolution - RP 23", 20, -.8, .8);
   TH1D *proton_resolution_left_reco_rp23 = new TH1D("proton_resolution_left_reco_rp23", "#xi Left reco Proton Resolution - RP 23", 20, -.8, .8);
   TH1D *pair_xi_left_rp23 = new TH1D("pair_xi_left_rp23", "#xi Pair Left - RP 23", 20, 0, 0.16);
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
   TH1D *proton_resolution_left_rp23_1 = new TH1D("proton_resolution_left_rp23_1", "#xi Proton Left Proton Resolution - RP 23", 20, -.05, .05);
   TH1D *proton_resolution_left_rp23_2 = new TH1D("proton_resolution_left_rp23_2", "#xi Proton Left Proton Resolution - RP 23", 20, -.05, .05);
   TH1D *proton_resolution_left_rp23_3 = new TH1D("proton_resolution_left_rp23_3", "#xi Proton Left Proton Resolution - RP 23", 20, -.05, .05);
   TH1D *proton_resolution_left_rp23_4 = new TH1D("proton_resolution_left_rp23_4", "#xi Proton Left Proton Resolution - RP 23", 20, -.05, .05);
   TH1D *proton_resolution_left_rp23_5 = new TH1D("proton_resolution_left_rp23_5", "#xi Proton Left Proton Resolution - RP 23", 20, -.05, .05);
   TH1D *diff_proton_reco_pair_xi_left_rp23 = new TH1D("diff_proton_reco_pair_xi_left_rp23", "reco (Proton - Pair) #xi Left - RP 23", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_left_rp23 = new TH1D("ratio_proton_reco_pair_xi_left_rp23", "reco (1 - Proton/Pair) #xi Left - RP 23", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Com eficiencia - 1 proton
   TH1D *proton_xi_left_rp23_eff = new TH1D("proton_xi_left_rp23_eff", "#xi Proton Left - RP 23", 20, 0, 0.16);
   TH1D *pair_xi_left_rp23_eff = new TH1D("pair_xi_left_rp23_eff", "#xi Pair Left - RP 23", 20, 0, 0.16);
   TH2D *xi_left_reco_rp23_eff = new TH2D("xi_left_reco_rp23_eff", "#xi Left Correlation - RP 23", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_rp23_eff = new TGraph(); 
   g_xi_left_reco_rp23_eff->SetName("g_xi_left_reco_rp23_eff");
   g_xi_left_reco_rp23_eff->SetTitle("#xi Left Correlation - RP 23");
   TH2D *xi_left_reco_rp23_eff_match = new TH2D("xi_left_reco_rp23_eff_match", "#xi Left Correlation - Matching Events - RP 23", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_rp23_eff_match = new TGraph(); 
   g_xi_left_reco_rp23_eff_match->SetName("g_xi_left_reco_rp23_eff_match");
   g_xi_left_reco_rp23_eff_match->SetTitle("#xi Left Correlation - Matching Events - RP 23");
   TH2D *xi_left_reco_rp23_eff_non_match = new TH2D("xi_left_reco_rp23_eff_non_match", "#xi Left Correlation - Non-Matching Events - RP 23", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_rp23_eff_non_match = new TGraph(); 
   g_xi_left_reco_rp23_eff_non_match->SetName("g_xi_left_reco_rp23_eff_non_match");
   g_xi_left_reco_rp23_eff_non_match->SetTitle("#xi Left Correlation - Non-Matching Events - RP 23");
   TH1D *diff_proton_reco_pair_xi_left_rp23_eff = new TH1D("diff_proton_reco_pair_xi_left_rp23_eff", "reco (Proton - Pair) #xi Left - RP 23", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_left_rp23_eff = new TH1D("ratio_proton_reco_pair_xi_left_rp23_eff", "reco (1 - Proton/Pair) #xi Left - RP 23", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Sem eficiencia - n protons
   TH1D *proton_xi_left_rp23_nprot = new TH1D("proton_xi_left_rp23_nprot", "#xi Proton Left - RP 23", 20, 0, 0.16);
   TH1D *proton_resolution_left_gen_rp23_nprot = new TH1D("proton_resolution_left_gen_rp23_nprot", "#xi Left gen Proton Resolution - RP 23", 20, -.8, .8);
   TH1D *proton_resolution_left_reco_rp23_nprot = new TH1D("proton_resolution_left_reco_rp23_nprot", "#xi Left reco Proton Resolution - RP 23", 20, -.8, .8);
   TH1D *pair_xi_left_rp23_nprot = new TH1D("pair_xi_left_rp23_nprot", "#xi Pair Left - RP 23", 20, 0, 0.16);
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
   TH1D *proton_resolution_left_rp23_nprot_1 = new TH1D("proton_resolution_left_rp23_nprot_1", "#xi Proton Left Proton Resolution - RP 23", 20, -.05, .05);
   TH1D *proton_resolution_left_rp23_nprot_2 = new TH1D("proton_resolution_left_rp23_nprot_2", "#xi Proton Left Proton Resolution - RP 23", 20, -.05, .05);
   TH1D *proton_resolution_left_rp23_nprot_3 = new TH1D("proton_resolution_left_rp23_nprot_3", "#xi Proton Left Proton Resolution - RP 23", 20, -.05, .05);
   TH1D *proton_resolution_left_rp23_nprot_4 = new TH1D("proton_resolution_left_rp23_nprot_4", "#xi Proton Left Proton Resolution - RP 23", 20, -.05, .05);
   TH1D *proton_resolution_left_rp23_nprot_5 = new TH1D("proton_resolution_left_rp23_nprot_5", "#xi Proton Left Proton Resolution - RP 23", 20, -.05, .05);
   TH1D *diff_proton_reco_pair_xi_left_rp23_nprot = new TH1D("diff_proton_reco_pair_xi_left_rp23_nprot", "reco (Proton - Pair) #xi Left - RP 23", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_left_rp23_nprot = new TH1D("ratio_proton_reco_pair_xi_left_rp23_nprot", "reco (1 - Proton/Pair) #xi Left - RP 23", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Com eficiencia - n protons
   TH1D *proton_xi_left_rp23_nprot_eff = new TH1D("proton_xi_left_rp23_nprot_eff", "#xi Proton Left - RP 23", 20, 0, 0.16);
   TH1D *pair_xi_left_rp23_nprot_eff = new TH1D("pair_xi_left_rp23_nprot_eff", "#xi Pair Left - RP 23", 20, 0, 0.16);
   TH2D *xi_left_reco_rp23_nprot_eff = new TH2D("xi_left_reco_rp23_nprot_eff", "#xi Left Correlation - RP 23", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_rp23_nprot_eff = new TGraph(); 
   g_xi_left_reco_rp23_nprot_eff->SetName("g_xi_left_reco_rp23_nprot_eff");
   g_xi_left_reco_rp23_nprot_eff->SetTitle("#xi Left Correlation - RP 23");
   TH2D *xi_left_reco_rp23_nprot_eff_match = new TH2D("xi_left_reco_rp23_nprot_eff_match", "#xi Left Correlation - Matching Events - RP 23", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_rp23_nprot_eff_match = new TGraph(); 
   g_xi_left_reco_rp23_nprot_eff_match->SetName("g_xi_left_reco_rp23_nprot_eff_match");
   g_xi_left_reco_rp23_nprot_eff_match->SetTitle("#xi Left Correlation - Matching Events - RP 23");
   TH2D *xi_left_reco_rp23_nprot_eff_non_match = new TH2D("xi_left_reco_rp23_nprot_eff_non_match", "#xi Left Correlation - Non-Matching Events - RP 23", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_rp23_nprot_eff_non_match = new TGraph(); 
   g_xi_left_reco_rp23_nprot_eff_non_match->SetName("g_xi_left_reco_rp23_nprot_eff_non_match");
   g_xi_left_reco_rp23_nprot_eff_non_match->SetTitle("#xi Left Correlation - Non-Matching Events - RP 23");
   TH1D *diff_proton_reco_pair_xi_left_rp23_nprot_eff = new TH1D("diff_proton_reco_pair_xi_left_rp23_nprot_eff", "reco (Proton - Pair) #xi Left - RP 23", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_left_rp23_nprot_eff = new TH1D("ratio_proton_reco_pair_xi_left_rp23_nprot_eff", "reco (1 - Proton/Pair) #xi Left - RP 23", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////LEFT STRIPS+PIXEL////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Sem eficiencia 
   TH1D *proton_xi_left_single = new TH1D("proton_xi_left_single", "#xi Proton Left - Single RP", 20, 0, 0.16);
   TH1D *proton_resolution_left_gen_single = new TH1D("proton_resolution_left_gen_single", "#xi Left gen Proton Resolution - Single RP", 20, -.8, .8);
   TH1D *proton_resolution_left_reco_single = new TH1D("proton_resolution_left_reco_single", "#xi Left reco Proton Resolution - Single RP", 20, -.8, .8);
   TH1D *pair_xi_left_single = new TH1D("pair_xi_left_single", "#xi Pair Left - Single RP", 20, 0, 0.16);
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
   TH1D *proton_resolution_left_single_1 = new TH1D("proton_resolution_left_single_1", "#xi Proton Left Proton Resolution - Single RP", 20, -.05, .05);
   TH1D *proton_resolution_left_single_2 = new TH1D("proton_resolution_left_single_2", "#xi Proton Left Proton Resolution - Single RP", 20, -.05, .05);
   TH1D *proton_resolution_left_single_3 = new TH1D("proton_resolution_left_single_3", "#xi Proton Left Proton Resolution - Single RP", 20, -.05, .05);
   TH1D *proton_resolution_left_single_4 = new TH1D("proton_resolution_left_single_4", "#xi Proton Left Proton Resolution - Single RP", 20, -.05, .05);
   TH1D *proton_resolution_left_single_5 = new TH1D("proton_resolution_left_single_5", "#xi Proton Left Proton Resolution - Single RP", 20, -.05, .05);
   TH1D *diff_proton_reco_pair_xi_left_single = new TH1D("diff_proton_reco_pair_xi_left_single", "reco (Proton - Pair) #xi Left - Single", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_left_single = new TH1D("ratio_proton_reco_pair_xi_left_single", "reco (1 - reco Proton/Pair) #xi Left - Single", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Com eficiencia 
   TH1D *proton_xi_left_single_eff = new TH1D("proton_xi_left_single_eff", "#xi Proton Left - Single RP", 20, 0, 0.16);
   TH1D *pair_xi_left_single_eff = new TH1D("pair_xi_left_single_eff", "#xi Pair Left - Single RP", 20, 0, 0.16);
   TH2D *xi_left_reco_single_eff = new TH2D("xi_left_reco_single_eff", "#xi Left Correlation - Single RP", 20, 0, 0.16, 20, 0, 0.16); 	
   TGraph *g_xi_left_reco_single_eff = new TGraph(); 
   g_xi_left_reco_single_eff->SetName("g_xi_left_reco_single_eff");
   g_xi_left_reco_single_eff->SetTitle("#xi Left Correlation - Single RP");
   TH2D *xi_left_reco_single_eff_match = new TH2D("xi_left_reco_single_eff_match", "#xi Left Correlation - Matching Events - Single RP", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_single_eff_match = new TGraph(); 
   g_xi_left_reco_single_eff_match->SetName("g_xi_left_reco_single_eff_match");
   g_xi_left_reco_single_eff_match->SetTitle("#xi Left Correlation - Matching Events - Single RP");
   TH2D *xi_left_reco_single_eff_non_match = new TH2D("xi_left_reco_single_eff_non_match", "#xi Left Correlation - Non-Matching Events - Single RP", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_single_eff_non_match = new TGraph(); 
   g_xi_left_reco_single_eff_non_match->SetName("g_xi_left_reco_single_eff_non_match");
   g_xi_left_reco_single_eff_non_match->SetTitle("#xi Left Correlation - Non-Matching Events - Single RP");
   TH1D *diff_proton_reco_pair_xi_left_single_eff = new TH1D("diff_proton_reco_pair_xi_left_single_eff", "reco (Proton - Pair) #xi Left - Single", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_left_single_eff = new TH1D("ratio_proton_reco_pair_xi_left_single_eff", "reco (1 - reco Proton/Pair) #xi Left - Single", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////RIGHT STRIPS//////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Sem eficiencia 
   TH1D *proton_xi_right_rp103 = new TH1D("proton_xi_right_rp103", "#xi Proton Right - RP 103", 20, 0, 0.16);
   TH1D *proton_resolution_right_gen_rp103 = new TH1D("proton_resolution_right_gen_rp103", "#xi Right gen Proton Resolution - RP 103", 20, -.8, .8);
   TH1D *proton_resolution_right_reco_rp103 = new TH1D("proton_resolution_right_reco_rp103", "#xi Right reco Proton Resolution - RP 103", 20, -.8, .8);
   TH1D *pair_xi_right_rp103 = new TH1D("pair_xi_right_rp103", "#xi Pair Right - RP 103", 20, 0, 0.16);
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
   TH1D *proton_resolution_right_rp103_1 = new TH1D("proton_resolution_right_rp103_1", "#xi Proton Right Proton Resolution - RP 103", 20, -.05, .05);
   TH1D *proton_resolution_right_rp103_2 = new TH1D("proton_resolution_right_rp103_2", "#xi Proton Right Proton Resolution - RP 103", 20, -.05, .05);
   TH1D *proton_resolution_right_rp103_3 = new TH1D("proton_resolution_right_rp103_3", "#xi Proton Right Proton Resolution - RP 103", 20, -.05, .05);
   TH1D *proton_resolution_right_rp103_4 = new TH1D("proton_resolution_right_rp103_4", "#xi Proton Right Proton Resolution - RP 103", 20, -.05, .05);
   TH1D *proton_resolution_right_rp103_5 = new TH1D("proton_resolution_right_rp103_5", "#xi Proton Right Proton Resolution - RP 103", 20, -.05, .05);
   TH1D *diff_proton_reco_pair_xi_right_rp103 = new TH1D("diff_proton_reco_pair_xi_right_rp103", "reco (Proton - Pair) #xi Right - RP 103", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_right_rp103 = new TH1D("ratio_proton_reco_pair_xi_right_rp103", "reco (1 - Proton/Pair) #xi Right - RP 103", 10, -20, 103);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Com eficiencia 
   TH1D *proton_xi_right_rp103_eff = new TH1D("proton_xi_right_rp103_eff", "#xi Proton Right - RP 103", 20, 0, 0.16);
   TH1D *pair_xi_right_rp103_eff = new TH1D("pair_xi_right_rp103_eff", "#xi Pair Right - RP 103", 20, 0, 0.16);
   TH2D *xi_right_reco_rp103_eff = new TH2D("xi_right_reco_rp103_eff", "#xi Right Correlation - RP 103", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_rp103_eff = new TGraph();
   g_xi_right_reco_rp103_eff->SetName("g_xi_right_reco_rp103_eff");
   g_xi_right_reco_rp103_eff->SetTitle("#xi Right Correlation - RP 103");
   TH2D *xi_right_reco_rp103_eff_match = new TH2D("xi_right_reco_rp103_eff_match", "#xi Right Correlation - Matching Events - RP 103", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_rp103_eff_match = new TGraph(); 
   g_xi_right_reco_rp103_eff_match->SetName("g_xi_right_reco_rp103_eff_match");
   g_xi_right_reco_rp103_eff_match->SetTitle("#xi Right Correlation - Matching Events - RP 103");
   TH2D *xi_right_reco_rp103_eff_non_match = new TH2D("xi_right_reco_rp103_eff_non_match", "#xi Right Correlation - Non-Matching Events - RP 103", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_rp103_eff_non_match = new TGraph(); 
   g_xi_right_reco_rp103_eff_non_match->SetName("g_xi_right_reco_rp103_eff_non_match");
   g_xi_right_reco_rp103_eff_non_match->SetTitle("#xi Right Correlation - Non-Matching Events - RP 103");
   TH1D *diff_proton_reco_pair_xi_right_rp103_eff = new TH1D("diff_proton_reco_pair_xi_right_rp103_eff", "reco (Proton - Pair) #xi Right - RP 103", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_right_rp103_eff = new TH1D("ratio_proton_reco_pair_xi_right_rp103_eff", "reco (1 - Proton/Pair) #xi Right - RP 103", 10, -20, 103);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////RIGHT PIXEL///////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Sem eficiencia - 1 proton
   TH1D *proton_xi_right_rp123 = new TH1D("proton_xi_right_rp123", "#xi Proton Right - RP 123", 20, 0, 0.16);
   TH1D *proton_resolution_right_gen_rp123 = new TH1D("proton_resolution_right_gen_rp123", "#xi Right gen Proton Resolution - RP 123", 20, -.8, .8);
   TH1D *proton_resolution_right_reco_rp123 = new TH1D("proton_resolution_right_reco_rp123", "#xi Right reco Proton Resolution - RP 123", 20, -.8, .8);
   TH1D *pair_xi_right_rp123 = new TH1D("pair_xi_right_rp123", "#xi Pair Right - RP 123", 20, 0, 0.16);
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
   TH1D *proton_resolution_right_rp123_1 = new TH1D("proton_resolution_right_rp123_1", "#xi Proton Right Proton Resolution - RP 123", 20, -.05, .05);
   TH1D *proton_resolution_right_rp123_2 = new TH1D("proton_resolution_right_rp123_2", "#xi Proton Right Proton Resolution - RP 123", 20, -.05, .05);
   TH1D *proton_resolution_right_rp123_3 = new TH1D("proton_resolution_right_rp123_3", "#xi Proton Right Proton Resolution - RP 123", 20, -.05, .05);
   TH1D *proton_resolution_right_rp123_4 = new TH1D("proton_resolution_right_rp123_4", "#xi Proton Right Proton Resolution - RP 123", 20, -.05, .05);
   TH1D *proton_resolution_right_rp123_5 = new TH1D("proton_resolution_right_rp123_5", "#xi Proton Right Proton Resolution - RP 123", 20, -.05, .05);
   TH1D *diff_proton_reco_pair_xi_right_rp123 = new TH1D("diff_proton_reco_pair_xi_right_rp123", "reco (Proton - Pair) #xi Right - RP 123", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_right_rp123 = new TH1D("ratio_proton_reco_pair_xi_right_rp123", "reco (1 - Proton/Pair) #xi Right - RP 123", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Com eficiencia - 1 proton
   TH1D *proton_xi_right_rp123_eff = new TH1D("proton_xi_right_rp123_eff", "#xi Proton Right - RP 123", 20, 0, 0.16);
   TH1D *pair_xi_right_rp123_eff = new TH1D("pair_xi_right_rp123_eff", "#xi Pair Right - RP 123", 20, 0, 0.16);
   TH2D *xi_right_reco_rp123_eff = new TH2D("xi_right_reco_rp123_eff", "#xi Right Correlation - RP 123", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_rp123_eff = new TGraph(); 
   g_xi_right_reco_rp123_eff->SetName("g_xi_right_reco_rp123_eff");
   g_xi_right_reco_rp123_eff->SetTitle("#xi Right Correlation - RP 123");
   TH2D *xi_right_reco_rp123_eff_match = new TH2D("xi_right_reco_rp123_eff_match", "#xi Right Correlation - Matching Events - RP 123", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_rp123_eff_match = new TGraph(); 
   g_xi_right_reco_rp123_eff_match->SetName("g_xi_right_reco_rp123_eff_match");
   g_xi_right_reco_rp123_eff_match->SetTitle("#xi Right Correlation - Matching Events - RP 123");
   TH2D *xi_right_reco_rp123_eff_non_match = new TH2D("xi_right_reco_rp123_eff_non_match", "#xi Right Correlation - Non-Matching Events - RP 123", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_rp123_eff_non_match = new TGraph(); 
   g_xi_right_reco_rp123_eff_non_match->SetName("g_xi_right_reco_rp123_eff_non_match");
   g_xi_right_reco_rp123_eff_non_match->SetTitle("#xi Right Correlation - Non-Matching Events - RP 123");
   TH1D *diff_proton_reco_pair_xi_right_rp123_eff = new TH1D("diff_proton_reco_pair_xi_right_rp123_eff", "reco (Proton - Pair) #xi Right - RP 123", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_right_rp123_eff = new TH1D("ratio_proton_reco_pair_xi_right_rp123_eff", "reco (1 - Proton/Pair) #xi Right - RP 123", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Sem eficiencia - n protons
   TH1D *proton_xi_right_rp123_nprot = new TH1D("proton_xi_right_rp123_nprot", "#xi Proton Right - RP 123", 20, 0, 0.16);
   TH1D *proton_resolution_right_gen_rp123_nprot = new TH1D("proton_resolution_right_gen_rp123_nprot", "#xi Right gen Proton Resolution - RP 123", 20, -.8, .8);
   TH1D *proton_resolution_right_reco_rp123_nprot = new TH1D("proton_resolution_right_reco_rp123_nprot", "#xi Right reco Proton Resolution - RP 123", 20, -.8, .8);
   TH1D *pair_xi_right_rp123_nprot = new TH1D("pair_xi_right_rp123_nprot", "#xi Pair Right - RP 123", 20, 0, 0.16);
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
   TH1D *proton_resolution_right_rp123_nprot_1 = new TH1D("proton_resolution_right_rp123_nprot_1", "#xi Proton Right Proton Resolution - RP 123", 20, -.05, .05);
   TH1D *proton_resolution_right_rp123_nprot_2 = new TH1D("proton_resolution_right_rp123_nprot_2", "#xi Proton Right Proton Resolution - RP 123", 20, -.05, .05);
   TH1D *proton_resolution_right_rp123_nprot_3 = new TH1D("proton_resolution_right_rp123_nprot_3", "#xi Proton Right Proton Resolution - RP 123", 20, -.05, .05);
   TH1D *proton_resolution_right_rp123_nprot_4 = new TH1D("proton_resolution_right_rp123_nprot_4", "#xi Proton Right Proton Resolution - RP 123", 20, -.05, .05);
   TH1D *proton_resolution_right_rp123_nprot_5 = new TH1D("proton_resolution_right_rp123_nprot_5", "#xi Proton Right Proton Resolution - RP 123", 20, -.05, .05);
   TH1D *diff_proton_reco_pair_xi_right_rp123_nprot = new TH1D("diff_proton_reco_pair_xi_right_rp123_nprot", "reco (Proton - Pair) #xi Right - RP 123", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_right_rp123_nprot = new TH1D("ratio_proton_reco_pair_xi_right_rp123_nprot", "reco (1 - Proton/Pair) #xi Right - RP 123", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Com eficiencia - n protons
   TH1D *proton_xi_right_rp123_nprot_eff = new TH1D("proton_xi_right_rp123_nprot_eff", "#xi Proton Right - RP 123", 20, 0, 0.16);
   TH1D *pair_xi_right_rp123_nprot_eff = new TH1D("pair_xi_right_rp123_nprot_eff", "#xi Pair Right - RP 123", 20, 0, 0.16);
   TH2D *xi_right_reco_rp123_nprot_eff = new TH2D("xi_right_reco_rp123_nprot_eff", "#xi Right Correlation - RP 123", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_rp123_nprot_eff = new TGraph(); 
   g_xi_right_reco_rp123_nprot_eff->SetName("g_xi_right_reco_rp123_nprot_eff");
   g_xi_right_reco_rp123_nprot_eff->SetTitle("#xi Right Correlation - RP 123");
   TH2D *xi_right_reco_rp123_nprot_eff_match = new TH2D("xi_right_reco_rp123_nprot_eff_match", "#xi Right Correlation - Matching Events - RP 123", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_rp123_nprot_eff_match = new TGraph(); 
   g_xi_right_reco_rp123_nprot_eff_match->SetName("g_xi_right_reco_rp123_nprot_eff_match");
   g_xi_right_reco_rp123_nprot_eff_match->SetTitle("#xi Right Correlation - Matching Events - RP 123");
   TH2D *xi_right_reco_rp123_nprot_eff_non_match = new TH2D("xi_right_reco_rp123_nprot_eff_non_match", "#xi Right Correlation - Non-Matching Events - RP 123", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_rp123_nprot_eff_non_match = new TGraph(); 
   g_xi_right_reco_rp123_nprot_eff_non_match->SetName("g_xi_right_reco_rp123_nprot_eff_non_match");
   g_xi_right_reco_rp123_nprot_eff_non_match->SetTitle("#xi Right Correlation - Non-Matching Events - RP 123");
   TH1D *diff_proton_reco_pair_xi_right_rp123_nprot_eff = new TH1D("diff_proton_reco_pair_xi_right_rp123_nprot_eff", "reco (Proton - Pair) #xi Right - RP 123", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_right_rp123_nprot_eff = new TH1D("ratio_proton_reco_pair_xi_right_rp123_nprot_eff", "reco (1 - Proton/Pair) #xi Right - RP 123", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////RIGHT STRIPS+PIXEL////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Sem eficiencia 
   TH1D *proton_xi_right_single = new TH1D("proton_xi_right_single", "#xi Proton Right - Single RP", 20, 0, 0.16);
   TH1D *proton_resolution_right_gen_single = new TH1D("proton_resolution_right_gen_single", "#xi Right gen Proton Resolution - Single RP", 20, -.8, .8);
   TH1D *proton_resolution_right_reco_single = new TH1D("proton_resolution_right_reco_single", "#xi Right reco Proton Resolution - Single RP", 20, -.8, .8);
   TH1D *pair_xi_right_single = new TH1D("pair_xi_right_single", "#xi Pair Right - Single RP", 20, 0, 0.16);
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
   TH1D *proton_resolution_right_single_1 = new TH1D("proton_resolution_right_single_1", "#xi Proton Right Proton Resolution - Single RP", 20, -.05, .05);
   TH1D *proton_resolution_right_single_2 = new TH1D("proton_resolution_right_single_2", "#xi Proton Right Proton Resolution - Single RP", 20, -.05, .05);
   TH1D *proton_resolution_right_single_3 = new TH1D("proton_resolution_right_single_3", "#xi Proton Right Proton Resolution - Single RP", 20, -.05, .05);
   TH1D *proton_resolution_right_single_4 = new TH1D("proton_resolution_right_single_4", "#xi Proton Right Proton Resolution - Single RP", 20, -.05, .05);
   TH1D *proton_resolution_right_single_5 = new TH1D("proton_resolution_right_single_5", "#xi Proton Right Proton Resolution - Single RP", 20, -.05, .05);
   TH1D *diff_proton_reco_pair_xi_right_single = new TH1D("diff_proton_reco_pair_xi_right_single", "reco (Proton - Pair) #xi Right - Single", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_right_single = new TH1D("ratio_proton_reco_pair_xi_right_single", "reco (1 - reco Proton/Pair) #xi Right - Single", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Com eficiencia 
   TH1D *proton_xi_right_single_eff = new TH1D("proton_xi_right_single_eff", "#xi Proton Right - Single RP", 20, 0, 0.16);
   TH1D *pair_xi_right_single_eff = new TH1D("pair_xi_right_single_eff", "#xi Pair Right - Single RP", 20, 0, 0.16);
   TH2D *xi_right_reco_single_eff = new TH2D("xi_right_reco_single_eff", "#xi Right Correlation - Single RP", 20, 0, 0.16, 20, 0, 0.16); 	
   TGraph *g_xi_right_reco_single_eff = new TGraph(); 
   g_xi_right_reco_single_eff->SetName("g_xi_right_reco_single_eff");
   g_xi_right_reco_single_eff->SetTitle("#xi Right Correlation - Single RP");
   TH2D *xi_right_reco_single_eff_match = new TH2D("xi_right_reco_single_eff_match", "#xi Right Correlation - Matching Events - Single RP", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_single_eff_match = new TGraph(); 
   g_xi_right_reco_single_eff_match->SetName("g_xi_right_reco_single_eff_match");
   g_xi_right_reco_single_eff_match->SetTitle("#xi Right Correlation - Matching Events - Single RP");
   TH2D *xi_right_reco_single_eff_non_match = new TH2D("xi_right_reco_single_eff_non_match", "#xi Right Correlation - Non-Matching Events - Single RP", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_single_eff_non_match = new TGraph(); 
   g_xi_right_reco_single_eff_non_match->SetName("g_xi_right_reco_single_eff_non_match");
   g_xi_right_reco_single_eff_non_match->SetTitle("#xi Right Correlation - Non-Matching Events - Single RP");
   TH1D *diff_proton_reco_pair_xi_right_single_eff = new TH1D("diff_proton_reco_pair_xi_right_single_eff", "reco (Proton - Pair) #xi Right - Single", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_right_single_eff = new TH1D("ratio_proton_reco_pair_xi_right_single_eff", "reco (1 - reco Proton/Pair) #xi Right - Single", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////LEFT MULTI///////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Sem eficiencia
   TH1D *proton_xi_left_multi = new TH1D("proton_xi_left_multi", "#xi Proton Left - Multi RP", 20, 0, 0.16);
   TH1D *proton_resolution_left_gen_multi = new TH1D("proton_resolution_left_gen_multi", "#xi Left gen Proton Resolution - Multi RP", 20, -2, 2);
   TH1D *proton_resolution_left_reco_multi = new TH1D("proton_resolution_left_reco_multi", "#xi Left reco Proton Resolution - Multi RP", 20, -2, 2);
   TH1D *pair_xi_left_multi = new TH1D("pair_xi_left_multi", "#xi Pair Left - Multi RP", 20, 0, 0.16);
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
   TH1D *proton_resolution_left_multi_1 = new TH1D("proton_resolution_left_multi_1", "#xi Proton Left Proton Resolution - Multi RP", 20, -.05, .05);
   TH1D *proton_resolution_left_multi_2 = new TH1D("proton_resolution_left_multi_2", "#xi Proton Left Proton Resolution - Multi RP", 20, -.05, .05);
   TH1D *proton_resolution_left_multi_3 = new TH1D("proton_resolution_left_multi_3", "#xi Proton Left Proton Resolution - Multi RP", 20, -.05, .05);
   TH1D *proton_resolution_left_multi_4 = new TH1D("proton_resolution_left_multi_4", "#xi Proton Left Proton Resolution - Multi RP", 20, -.05, .05);
   TH1D *proton_resolution_left_multi_5 = new TH1D("proton_resolution_left_multi_5", "#xi Proton Left Proton Resolution - Multi RP", 20, -.05, .05);
   TH1D *diff_proton_reco_pair_xi_left_multi = new TH1D("diff_proton_reco_pair_xi_left_multi", "reco (Proton - Pair) #xi Left - Multi", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_left_multi = new TH1D("ratio_proton_reco_pair_xi_left_multi", "reco (1 - Proton/Pair) #xi Left - Multi", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Com eficiencia
   TH1D *proton_xi_left_multi_eff = new TH1D("proton_xi_left_multi_eff", "#xi Proton Left - Multi RP", 20, 0, 0.16);
   TH1D *pair_xi_left_multi_eff = new TH1D("pair_xi_left_multi_eff", "#xi Pair Left - Multi RP", 20, 0, 0.16);
   TH2D *xi_left_reco_multi_eff = new TH2D("xi_left_reco_multi_eff", "#xi Left Correlation - Multi RP", 20, 0, 0.16, 20, 0, 0.16); 	
   TGraph *g_xi_left_reco_multi_eff = new TGraph(); 
   g_xi_left_reco_multi_eff->SetName("g_xi_left_reco_multi_eff");
   g_xi_left_reco_multi_eff->SetTitle("#xi Left Correlation - Multi RP");
   TH2D *xi_left_reco_multi_eff_match = new TH2D("xi_left_reco_multi_eff_match", "#xi Left Correlation - Matching Events - Multi RP", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_multi_eff_match = new TGraph(); 
   g_xi_left_reco_multi_eff_match->SetName("g_xi_left_reco_multi_eff_match");
   g_xi_left_reco_multi_eff_match->SetTitle("#xi Left Correlation - Matching Events - Multi RP");
   TH2D *xi_left_reco_multi_eff_non_match = new TH2D("xi_left_reco_multi_eff_non_match", "#xi Left Correlation - Non-Matching Events - Multi RP", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_left_reco_multi_eff_non_match = new TGraph(); 
   g_xi_left_reco_multi_eff_non_match->SetName("g_xi_left_reco_multi_eff_non_match");
   g_xi_left_reco_multi_eff_non_match->SetTitle("#xi Left Correlation - Non-Matching Events - Multi RP");
   TH1D *diff_proton_reco_pair_xi_left_multi_eff = new TH1D("diff_proton_reco_pair_xi_left_multi_eff", "reco (Proton - Pair) #xi Left - Multi", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_left_multi_eff = new TH1D("ratio_proton_reco_pair_xi_left_multi_eff", "reco (1 - Proton/Pair) #xi Left - Multi", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////RIGHT MULTI///////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Sem eficiencia
   TH1D *proton_xi_right_multi = new TH1D("proton_xi_right_multi", "#xi Proton Right - Multi RP", 20, 0, 0.16);
   TH1D *proton_resolution_right_gen_multi = new TH1D("proton_resolution_right_gen_multi", "#xi Right gen Proton Resolution - Multi RP", 20, -.2, .2);
   TH1D *proton_resolution_right_reco_multi = new TH1D("proton_resolution_right_reco_multi", "#xi Right reco Proton Resolution - Multi RP", 20, -2, 2);
   TH1D *pair_xi_right_multi = new TH1D("pair_xi_right_multi", "#xi Pair Right - Multi RP", 20, 0, 0.16);
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
   TH1D *proton_resolution_right_multi_1 = new TH1D("proton_resolution_right_multi_1", "#xi Proton Right Proton Resolution - Multi RP", 20, -.05, .05);
   TH1D *proton_resolution_right_multi_2 = new TH1D("proton_resolution_right_multi_2", "#xi Proton Right Proton Resolution - Multi RP", 20, -.05, .05);
   TH1D *proton_resolution_right_multi_3 = new TH1D("proton_resolution_right_multi_3", "#xi Proton Right Proton Resolution - Multi RP", 20, -.05, .05);
   TH1D *proton_resolution_right_multi_4 = new TH1D("proton_resolution_right_multi_4", "#xi Proton Right Proton Resolution - Multi RP", 20, -.05, .05);
   TH1D *proton_resolution_right_multi_5 = new TH1D("proton_resolution_right_multi_5", "#xi Proton Right Proton Resolution - Multi RP", 20, -.05, .05);
   TH1D *diff_proton_reco_pair_xi_right_multi = new TH1D("diff_proton_reco_pair_xi_right_multi", "reco (Proton - Pair) #xi Right - Multi", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_right_multi = new TH1D("ratio_proton_reco_pair_xi_right_multi", "reco (1 - Proton/Pair) #xi Right - Multi", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //Com eficiencia
   TH1D *proton_xi_right_multi_eff = new TH1D("proton_xi_right_multi_eff", "#xi Proton Right - Multi RP", 20, 0, 0.16);
   TH1D *proton_resolution_right_gen_multi_eff = new TH1D("proton_resolution_right_gen_multi_eff", "#xi Right gen Proton Resolution - Multi RP", 20, -.2, .2);
   TH1D *proton_resolution_right_reco_multi_eff = new TH1D("proton_resolution_right_reco_multi_eff", "#xi Right reco Proton Resolution - Multi RP", 20, -2, 2);
   TH1D *pair_xi_right_multi_eff = new TH1D("pair_xi_right_multi_eff", "#xi Pair Right - Multi RP", 20, 0, 0.16);
   TH2D *xi_right_reco_multi_eff = new TH2D("xi_right_reco_multi_eff", "#xi Right Correlation - Multi RP", 20, 0, 0.16, 20, 0, 0.16); 	
   TGraph *g_xi_right_reco_multi_eff = new TGraph(); 
   g_xi_right_reco_multi_eff->SetName("g_xi_right_reco_multi_eff");
   g_xi_right_reco_multi_eff->SetTitle("#xi Right Correlation - Multi RP");
   TH2D *xi_right_reco_multi_eff_match = new TH2D("xi_right_reco_multi_eff_match", "#xi Right Correlation - Matching Events - Multi RP", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_multi_eff_match = new TGraph(); 
   g_xi_right_reco_multi_eff_match->SetName("g_xi_right_reco_multi_eff_match");
   g_xi_right_reco_multi_eff_match->SetTitle("#xi Right Correlation - Matching Events - Multi RP");
   TH2D *xi_right_reco_multi_eff_non_match = new TH2D("xi_right_reco_multi_eff_non_match", "#xi Right Correlation - Non-Matching Events - Multi RP", 20, 0, 0.16, 20, 0, 0.16); 
   TGraph *g_xi_right_reco_multi_eff_non_match = new TGraph(); 
   g_xi_right_reco_multi_eff_non_match->SetName("g_xi_right_reco_multi_eff_non_match");
   g_xi_right_reco_multi_eff_non_match->SetTitle("#xi Right Correlation - Non-Matching Events - Multi RP");
   TH1D *proton_resolution_right_multi_eff_1 = new TH1D("proton_resolution_right_multi_eff_1", "#xi Proton Right Proton Resolution - Multi RP", 20, -.05, .05);
   TH1D *proton_resolution_right_multi_eff_2 = new TH1D("proton_resolution_right_multi_eff_2", "#xi Proton Right Proton Resolution - Multi RP", 20, -.05, .05);
   TH1D *proton_resolution_right_multi_eff_3 = new TH1D("proton_resolution_right_multi_eff_3", "#xi Proton Right Proton Resolution - Multi RP", 20, -.05, .05);
   TH1D *proton_resolution_right_multi_eff_4 = new TH1D("proton_resolution_right_multi_eff_4", "#xi Proton Right Proton Resolution - Multi RP", 20, -.05, .05);
   TH1D *proton_resolution_right_multi_eff_5 = new TH1D("proton_resolution_right_multi_eff_5", "#xi Proton Right Proton Resolution - Multi RP", 20, -.05, .05);
   TH1D *diff_proton_reco_pair_xi_right_multi_eff = new TH1D("diff_proton_reco_pair_xi_right_multi_eff", "reco (Proton - Pair) #xi Right - Multi", 10, -1, 1);
   TH1D *ratio_proton_reco_pair_xi_right_multi_eff = new TH1D("ratio_proton_reco_pair_xi_right_multi_eff", "reco (1 - Proton/Pair) #xi Right - Multi", 10, -20, 3);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   /////////////////////////////////////////////////////////////////////////////MUON///////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   TH1D *xi_pair_resolution_left = new TH1D("xi_pair_resolution_left", "Left #xi #mu^{+}#mu^{-} gen - #xi #mu^{+}#mu^{-} reco", 20, -.005, .005);
   TH1D *xi_pair_resolution_left_1 = new TH1D("xi_pair_resolution_left_1", "Left #xi #mu^{+}#mu^{-} gen - #xi #mu^{+}#mu^{-} reco", 20, -.005, .005);
   TH1D *xi_pair_resolution_left_2 = new TH1D("xi_pair_resolution_left_2", "Left #xi #mu^{+}#mu^{-} gen - #xi #mu^{+}#mu^{-} reco", 20, -.005, .005);
   TH1D *xi_pair_resolution_left_3 = new TH1D("xi_pair_resolution_left_3", "Left #xi #mu^{+}#mu^{-} gen - #xi #mu^{+}#mu^{-} reco", 20, -.005, .005);
   TH1D *xi_pair_resolution_left_4 = new TH1D("xi_pair_resolution_left_4", "Left #xi #mu^{+}#mu^{-} gen - #xi #mu^{+}#mu^{-} reco", 20, -.005, .005);
   TH1D *xi_pair_resolution_left_5 = new TH1D("xi_pair_resolution_left_5", "Left #xi #mu^{+}#mu^{-} gen - #xi #mu^{+}#mu^{-} reco", 20, -.005, .005);
   TH1D *xi_pair_resolution_right = new TH1D("xi_pair_resolution_right", "Right #xi #mu^{+}#mu^{-} gen - #xi #mu^{+}#mu^{-} reco", 20, -.005, .005);
   TH1D *xi_pair_resolution_right_1 = new TH1D("xi_pair_resolution_right_1", "Right #xi #mu^{+}#mu^{-} gen - #xi #mu^{+}#mu^{-} reco", 20, -.005, .005);
   TH1D *xi_pair_resolution_right_2 = new TH1D("xi_pair_resolution_right_2", "Right #xi #mu^{+}#mu^{-} gen - #xi #mu^{+}#mu^{-} reco", 20, -.005, .005);
   TH1D *xi_pair_resolution_right_3 = new TH1D("xi_pair_resolution_right_3", "Right #xi #mu^{+}#mu^{-} gen - #xi #mu^{+}#mu^{-} reco", 20, -.005, .005);
   TH1D *xi_pair_resolution_right_4 = new TH1D("xi_pair_resolution_right_4", "Right #xi #mu^{+}#mu^{-} gen - #xi #mu^{+}#mu^{-} reco", 20, -.005, .005);
   TH1D *xi_pair_resolution_right_5 = new TH1D("xi_pair_resolution_right_5", "Right #xi #mu^{+}#mu^{-} gen - #xi #mu^{+}#mu^{-} reco", 20, -.005, .005);

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   if (fChain == 0) return;

   TFile *eff_pixel = new TFile("/afs/cern.ch/user/m/malvesga/work/ProtonRecon/TEST/CMSSW_10_6_5/src/workspace/Dilepton_15_11_19/pixelEfficiencies.root");
   TH2F *eff_pixel_rddam_B_45 = (TH2F*)eff_pixel->Get("Pixel/2017/2017B/h45_220_2017B_all_2D");
   TH2F *eff_pixel_rddam_C1_45 = (TH2F*)eff_pixel->Get("Pixel/2017/2017C1/h45_220_2017C1_all_2D");
   TH2F *eff_pixel_rddam_E_45 = (TH2F*)eff_pixel->Get("Pixel/2017/2017E/h45_220_2017E_all_2D");
   TH2F *eff_pixel_rddam_F1_45 = (TH2F*)eff_pixel->Get("Pixel/2017/2017F1/h45_220_2017F1_all_2D");
   TH2F *eff_pixel_rddam_B_56 = (TH2F*)eff_pixel->Get("Pixel/2017/2017B/h56_220_2017B_all_2D");
   TH2F *eff_pixel_rddam_C1_56 = (TH2F*)eff_pixel->Get("Pixel/2017/2017C1/h56_220_2017C1_all_2D");
   TH2F *eff_pixel_rddam_E_56 = (TH2F*)eff_pixel->Get("Pixel/2017/2017E/h56_220_2017E_all_2D");
   TH2F *eff_pixel_rddam_F1_56 = (TH2F*)eff_pixel->Get("Pixel/2017/2017F1/h56_220_2017F1_all_2D");

   TFile *eff_strips = new TFile("/afs/cern.ch/user/m/malvesga/work/ProtonRecon/TEST/CMSSW_10_6_5/src/workspace/Dilepton_15_11_19/PreliminaryEfficiencies_October92019_1D2DMultiTrack.root");
   TH2F *eff_strips_rddam_B_45 = (TH2F*)eff_strips->Get("Strips/2017/2017B/h45_2017B_all_2D");
   TH2F *eff_strips_rddam_C1_45 = (TH2F*)eff_strips->Get("Strips/2017/2017C1/h45_2017C1_all_2D");
   TH2F *eff_strips_rddam_D_45 = (TH2F*)eff_strips->Get("Strips/2017/2017D/h45_2017D_all_2D");
   TH2F *eff_strips_rddam_E_45 = (TH2F*)eff_strips->Get("Strips/2017/2017E/h45_2017E_all_2D");
   TH2F *eff_strips_rddam_F1_45 = (TH2F*)eff_strips->Get("Strips/2017/2017F1/h45_2017F1_all_2D");
   TH2F *eff_strips_rddam_B_56 = (TH2F*)eff_strips->Get("Strips/2017/2017B/h56_2017B_all_2D");
   TH2F *eff_strips_rddam_C1_56 = (TH2F*)eff_strips->Get("Strips/2017/2017C1/h56_2017C1_all_2D");
   TH2F *eff_strips_rddam_D_56 = (TH2F*)eff_strips->Get("Strips/2017/2017D/h56_2017D_all_2D");
   TH2F *eff_strips_rddam_E_56 = (TH2F*)eff_strips->Get("Strips/2017/2017E/h56_2017E_all_2D");
   TH2F *eff_strips_rddam_F1_56 = (TH2F*)eff_strips->Get("Strips/2017/2017F1/h56_2017F1_all_2D");
   TH2F *eff_strips_multitrack_B_45 = (TH2F*)eff_strips->Get("Strips/2017/2017B/h45multitrackeff_2017B_avg_RP3");
   TH2F *eff_strips_multitrack_C1_45 = (TH2F*)eff_strips->Get("Strips/2017/2017C1/h45multitrackeff_2017C1_avg_RP3");
   TH2F *eff_strips_multitrack_D_45 = (TH2F*)eff_strips->Get("Strips/2017/2017D/h45multitrackeff_2017D_avg_RP3");
   TH2F *eff_strips_multitrack_E_45 = (TH2F*)eff_strips->Get("Strips/2017/2017E/h45multitrackeff_2017E_avg_RP3");
   TH2F *eff_strips_multitrack_F1_45 = (TH2F*)eff_strips->Get("Strips/2017/2017F1/h45multitrackeff_2017F1_avg_RP3");
   TH2F *eff_strips_multitrack_B_56 = (TH2F*)eff_strips->Get("Strips/2017/2017B/h56multitrackeff_2017B_avg_RP103");
   TH2F *eff_strips_multitrack_C1_56 = (TH2F*)eff_strips->Get("Strips/2017/2017C1/h56multitrackeff_2017C1_avg_RP103");
   TH2F *eff_strips_multitrack_D_56 = (TH2F*)eff_strips->Get("Strips/2017/2017D/h56multitrackeff_2017D_avg_RP103");
   TH2F *eff_strips_multitrack_E_56 = (TH2F*)eff_strips->Get("Strips/2017/2017E/h56multitrackeff_2017E_avg_RP103");
   TH2F *eff_strips_multitrack_F1_56 = (TH2F*)eff_strips->Get("Strips/2017/2017F1/h56multitrackeff_2017F1_avg_RP103");

   TFile *input = new TFile("/afs/cern.ch/user/m/malvesga/work/ProtonRecon/TEST/CMSSW_10_6_5/src/workspace/Dilepton_15_11_19/histos_MC/pol_function.root", "READ");
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

   //double sigma_xi_mumu_left = 0.00068243; 
   //double sigma_xi_mumu_right = 0.000696733; 

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      double L_B = 2.367133065;
      double L_C1 = 5.372685500;
      double L_D = 4.142654225;
      double L_E = 9.061579666;
      double L_F1 = 1.714870205;
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
      int cont_single_rp23 = 0;
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
      zerocortes++;		

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
                           if(contador_PV3 <= 3){
                              oitocortes++;
                              mumu_mass->Fill(v.M());
                              mumu_pt->Fill(v.Pt());
                              mumu_y->Fill(v.Rapidity());
                              xi_pair_resolution_left->Fill(xi_pair_diff_left);
                              if (xi_pair_left_reco >= 0.02 && xi_pair_left_reco < 0.04) {
                                 xi_pair_resolution_left_1->Fill(xi_pair_diff_left);
                              }
                              if (xi_pair_left_reco >= 0.04 && xi_pair_left_reco < 0.06) {
                                 xi_pair_resolution_left_2->Fill(xi_pair_diff_left);
                              }
                              if (xi_pair_left_reco >= 0.06 && xi_pair_left_reco < 0.08) {
                                 xi_pair_resolution_left_3->Fill(xi_pair_diff_left);
                              }
                              if (xi_pair_left_reco >= 0.08 && xi_pair_left_reco < 0.10) {
                                 xi_pair_resolution_left_4->Fill(xi_pair_diff_left);
                              }
                              xi_pair_resolution_right->Fill(xi_pair_diff_right);
                              if (xi_pair_right_reco >= 0.02 && xi_pair_right_reco < 0.04) {
                                 xi_pair_resolution_right_1->Fill(xi_pair_diff_right);
                              }
                              if (xi_pair_right_reco >= 0.04 && xi_pair_right_reco < 0.06) {
                                 xi_pair_resolution_right_2->Fill(xi_pair_diff_right);
                              }
                              if (xi_pair_right_reco >= 0.06 && xi_pair_right_reco < 0.08) {
                                 xi_pair_resolution_right_3->Fill(xi_pair_diff_right);
                              }
                              if (xi_pair_right_reco >= 0.08 && xi_pair_right_reco < 0.10) {
                                 xi_pair_resolution_right_4->Fill(xi_pair_diff_right);
                              }
                              double sigma_xi_mumu_left = f_pair_left->Eval( xi_pair_left_reco );
                              double sigma_xi_mumu_right = f_pair_right->Eval( xi_pair_right_reco );

                              for (unsigned int idz = 0; idz < nGenProtCand; ++idz ) {
                                 if (GenProtCand_eta[idz] > 0) xi_proton_gen_left = (1 - GenProtCand_e[idz]/6500);
                                 if (GenProtCand_eta[idz] < 0) xi_proton_gen_right = (1 - GenProtCand_e[idz]/6500);
                              }

                              for (unsigned int idx = 0; idx < nRecoProtCand; ++idx ) {

                                 if (ProtCand_trackpixshift1[idx] == 0) { 

                                    if (ProtCand_rpid[idx] == 3) {
                                       if (ProtCand_ismultirp[idx] == 0) {
                                          double weight_rddam_B = eff_strips_rddam_B_45->GetBinContent(eff_strips_rddam_B_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_rddam_C1 = eff_strips_rddam_C1_45->GetBinContent(eff_strips_rddam_C1_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_rddam_E = eff_strips_rddam_E_45->GetBinContent(eff_strips_rddam_E_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_rddam_F1 = eff_strips_rddam_F1_45->GetBinContent(eff_strips_rddam_F1_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_rddam = (weight_rddam_B*L_B + weight_rddam_C1*L_C1 + weight_rddam_E*L_E + weight_rddam_F1*L_F1)/(L_B+L_C1+L_E+L_F1);
                                          double weight_multitrack_B = eff_strips_multitrack_B_45->GetBinContent(eff_strips_multitrack_B_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_multitrack_C1 = eff_strips_multitrack_C1_45->GetBinContent(eff_strips_multitrack_C1_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_multitrack_E = eff_strips_multitrack_E_45->GetBinContent(eff_strips_multitrack_E_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_multitrack_F1 = eff_strips_multitrack_F1_45->GetBinContent(eff_strips_multitrack_F1_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_multitrack = (weight_multitrack_B*L_B + weight_multitrack_C1*L_C1 + weight_multitrack_E*L_E + weight_multitrack_F1*L_F1)/(L_B+L_C1+L_E+L_F1);
                                          double weight = weight_rddam*weight_multitrack;
                                          proton_xi_left_rp3_eff->Fill(ProtCand_xi[idx], weight);
                                          proton_xi_left_rp3->Fill(ProtCand_xi[idx], 0.999999);
                                          proton_resolution_left_gen_rp3->Fill((xi_proton_gen_left - ProtCand_xi[idx])/xi_proton_gen_left);
                                          proton_resolution_left_reco_rp3->Fill((ProtCand_xi[idx] - xi_proton_gen_left)/ProtCand_xi[idx]);
                                          pair_xi_left_rp3->Fill(xi_pair_left_reco);
                                          xi_left_reco_rp3->Fill(ProtCand_xi[idx], xi_pair_left_reco);
                                          g_xi_left_reco_rp3->SetPoint(g_xi_left_reco_rp3->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                          diff_proton_reco_pair_xi_left_rp3->Fill(ProtCand_xi[idx] - xi_pair_left_reco); 
                                          ratio_proton_reco_pair_xi_left_rp3->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco); 
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
                                          double sigma_xi_RP3 = f_rp3->Eval( ProtCand_xi[idx] );
                                          if ( sigma_xi_RP3 > 0.) {
                                             double sigma_xi_rp3_mumu = TMath::Sqrt( sigma_xi_RP3*sigma_xi_RP3 + sigma_xi_mumu_left*sigma_xi_mumu_left );
                                             if ( TMath::Abs( ProtCand_xi[idx] - xi_pair_left_reco ) <= n_sigmas_xi*sigma_xi_rp3_mumu ) {
                                                match = true;
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
                                          double weight_rddam_B = eff_pixel_rddam_B_45->GetBinContent(eff_pixel_rddam_B_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_rddam_C1 = eff_pixel_rddam_C1_45->GetBinContent(eff_pixel_rddam_C1_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_rddam_E = eff_pixel_rddam_E_45->GetBinContent(eff_pixel_rddam_E_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_rddam_F1 = eff_pixel_rddam_F1_45->GetBinContent(eff_pixel_rddam_F1_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_rddam = (weight_rddam_B*L_B + weight_rddam_C1*L_C1 + weight_rddam_E*L_E + weight_rddam_F1*L_F1)/(L_B+L_C1+L_E+L_F1);
                                          proton_xi_left_rp23_nprot_eff->Fill(ProtCand_xi[idx], weight_rddam);
                                          proton_xi_left_rp23_nprot->Fill(ProtCand_xi[idx], 0.999999);
                                          proton_resolution_left_gen_rp23_nprot->Fill((xi_proton_gen_left - ProtCand_xi[idx])/xi_proton_gen_left);
                                          proton_resolution_left_reco_rp23_nprot->Fill((ProtCand_xi[idx] - xi_proton_gen_left)/ProtCand_xi[idx]);
                                          pair_xi_left_rp23_nprot->Fill(xi_pair_left_reco);
                                          xi_left_reco_rp23_nprot->Fill(ProtCand_xi[idx], xi_pair_left_reco); 
                                          g_xi_left_reco_rp23_nprot->SetPoint(g_xi_left_reco_rp23_nprot->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                          diff_proton_reco_pair_xi_left_rp23_nprot->Fill(ProtCand_xi[idx] - xi_pair_left_reco); 
                                          ratio_proton_reco_pair_xi_left_rp23_nprot->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco); 
                                          if (ProtCand_xi[idx] >= 0.02 && ProtCand_xi[idx] < 0.04) {
                                             proton_resolution_left_rp23_nprot_1->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
                                          }
                                          if (ProtCand_xi[idx] >= 0.04 && ProtCand_xi[idx] < 0.06) {
                                             proton_resolution_left_rp23_nprot_2->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
                                          }
                                          if (ProtCand_xi[idx] >= 0.06 && ProtCand_xi[idx] < 0.08) {
                                             proton_resolution_left_rp23_nprot_3->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
                                          }
                                          if (ProtCand_xi[idx] >= 0.08 && ProtCand_xi[idx] < 0.10) {
                                             proton_resolution_left_rp23_nprot_4->Fill(ProtCand_xi[idx] - xi_proton_gen_left);
                                          }
                                          double sigma_xi_RP23_nprot = f_rp23_nprot->Eval( ProtCand_xi[idx] );
                                          if ( sigma_xi_RP23_nprot > 0.) {
                                             double sigma_xi_rp23_nprot_mumu = TMath::Sqrt( sigma_xi_RP23_nprot*sigma_xi_RP23_nprot + sigma_xi_mumu_left*sigma_xi_mumu_left );
                                             if ( TMath::Abs( ProtCand_xi[idx] - xi_pair_left_reco ) <= n_sigmas_xi*sigma_xi_rp23_nprot_mumu ) {
                                                match = true;
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

                                    if(ProtCand_rpid[idx] == 3 && ProtCand_ismultirp[idx] == 0) {
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

                                    if (ProtCand_rpid[idx] == 103) {                           
                                       if (ProtCand_ismultirp[idx] == 0) {
                                          double weight_rddam_B = eff_strips_rddam_B_45->GetBinContent(eff_strips_rddam_B_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_rddam_C1 = eff_strips_rddam_C1_45->GetBinContent(eff_strips_rddam_C1_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_rddam_E = eff_strips_rddam_E_45->GetBinContent(eff_strips_rddam_E_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_rddam_F1 = eff_strips_rddam_F1_45->GetBinContent(eff_strips_rddam_F1_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_rddam = (weight_rddam_B*L_B + weight_rddam_C1*L_C1 + weight_rddam_E*L_E + weight_rddam_F1*L_F1)/(L_B+L_C1+L_E+L_F1);
                                          double weight_multitrack_B = eff_strips_multitrack_B_45->GetBinContent(eff_strips_multitrack_B_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_multitrack_C1 = eff_strips_multitrack_C1_45->GetBinContent(eff_strips_multitrack_C1_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_multitrack_E = eff_strips_multitrack_E_45->GetBinContent(eff_strips_multitrack_E_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_multitrack_F1 = eff_strips_multitrack_F1_45->GetBinContent(eff_strips_multitrack_F1_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_multitrack = (weight_multitrack_B*L_B + weight_multitrack_C1*L_C1 + weight_multitrack_E*L_E + weight_multitrack_F1*L_F1)/(L_B+L_C1+L_E+L_F1);
                                          double weight = weight_rddam*weight_multitrack;
                                          proton_xi_right_rp103_eff->Fill(ProtCand_xi[idx], weight);
                                          proton_xi_right_rp103->Fill(ProtCand_xi[idx], 0.999999);
                                          proton_resolution_right_gen_rp103->Fill((xi_proton_gen_right - ProtCand_xi[idx])/xi_proton_gen_right);
                                          proton_resolution_right_reco_rp103->Fill((ProtCand_xi[idx] - xi_proton_gen_right)/ProtCand_xi[idx]);
                                          pair_xi_right_rp103->Fill(xi_pair_right_reco);
                                          xi_right_reco_rp103->Fill(ProtCand_xi[idx], xi_pair_right_reco);
                                          g_xi_right_reco_rp103->SetPoint(g_xi_right_reco_rp103->GetN(), ProtCand_xi[idx], xi_pair_right_reco);
                                          diff_proton_reco_pair_xi_right_rp103->Fill(ProtCand_xi[idx] - xi_pair_right_reco); 
                                          ratio_proton_reco_pair_xi_right_rp103->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco); 
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
                                          double sigma_xi_RP103 = f_rp103->Eval( ProtCand_xi[idx] );
                                          if ( sigma_xi_RP103 > 0.) {
                                             double sigma_xi_rp103_mumu = TMath::Sqrt( sigma_xi_RP103*sigma_xi_RP103 + sigma_xi_mumu_right*sigma_xi_mumu_right );
                                             if ( TMath::Abs( ProtCand_xi[idx] - xi_pair_right_reco ) <= n_sigmas_xi*sigma_xi_rp103_mumu ) {
                                                match = true;
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
                                          double weight_rddam_B = eff_pixel_rddam_B_45->GetBinContent(eff_pixel_rddam_B_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_rddam_C1 = eff_pixel_rddam_C1_45->GetBinContent(eff_pixel_rddam_C1_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_rddam_E = eff_pixel_rddam_E_45->GetBinContent(eff_pixel_rddam_E_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_rddam_F1 = eff_pixel_rddam_F1_45->GetBinContent(eff_pixel_rddam_F1_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                          double weight_rddam = (weight_rddam_B*L_B + weight_rddam_C1*L_C1 + weight_rddam_E*L_E + weight_rddam_F1*L_F1)/(L_B+L_C1+L_E+L_F1);
                                          proton_xi_right_rp123_nprot_eff->Fill(ProtCand_xi[idx], weight_rddam);
                                          proton_xi_right_rp123_nprot->Fill(ProtCand_xi[idx], 0.999999);
                                          proton_resolution_right_gen_rp123_nprot->Fill((xi_proton_gen_right - ProtCand_xi[idx])/xi_proton_gen_right);
                                          proton_resolution_right_reco_rp123_nprot->Fill((ProtCand_xi[idx] - xi_proton_gen_right)/ProtCand_xi[idx]);
                                          pair_xi_right_rp123_nprot->Fill(xi_pair_right_reco);
                                          xi_right_reco_rp123_nprot->Fill(ProtCand_xi[idx], xi_pair_right_reco); 
                                          g_xi_right_reco_rp123_nprot->SetPoint(g_xi_right_reco_rp123_nprot->GetN(), ProtCand_xi[idx], xi_pair_right_reco);
                                          diff_proton_reco_pair_xi_right_rp123_nprot->Fill(ProtCand_xi[idx] - xi_pair_right_reco); 
                                          ratio_proton_reco_pair_xi_right_rp123_nprot->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco); 
                                          if (ProtCand_xi[idx] >= 0.02 && ProtCand_xi[idx] < 0.04) {
                                             proton_resolution_right_rp123_nprot_1->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
                                          }
                                          if (ProtCand_xi[idx] >= 0.04 && ProtCand_xi[idx] < 0.06) {
                                             proton_resolution_right_rp123_nprot_2->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
                                          }
                                          if (ProtCand_xi[idx] >= 0.06 && ProtCand_xi[idx] < 0.08) {
                                             proton_resolution_right_rp123_nprot_3->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
                                          }
                                          if (ProtCand_xi[idx] >= 0.08 && ProtCand_xi[idx] < 0.10) {
                                             proton_resolution_right_rp123_nprot_4->Fill(ProtCand_xi[idx] - xi_proton_gen_right);
                                          }
                                          double sigma_xi_RP123_nprot = f_rp123_nprot->Eval( ProtCand_xi[idx] );
                                          if ( sigma_xi_RP123_nprot > 0.) {
                                             double sigma_xi_rp123_nprot_mumu = TMath::Sqrt( sigma_xi_RP123_nprot*sigma_xi_RP123_nprot + sigma_xi_mumu_right*sigma_xi_mumu_right );
                                             if ( TMath::Abs( ProtCand_xi[idx] - xi_pair_right_reco ) <= n_sigmas_xi*sigma_xi_rp123_nprot_mumu ) {
                                                match = true;
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

                                    if(ProtCand_rpid[idx] == 103 && ProtCand_ismultirp[idx] == 0) {
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

                                    if (ProtCand_trackpixshift2[idx] == 0) { 
                                       if (ProtCand_arm[idx] == 0) {
                                          if (ProtCand_ismultirp[idx] == 1) {
                                             double pixel_weight_rddam_B = eff_pixel_rddam_B_45->GetBinContent(eff_pixel_rddam_B_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double pixel_weight_rddam_C1 = eff_pixel_rddam_C1_45->GetBinContent(eff_pixel_rddam_C1_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double pixel_weight_rddam_E = eff_pixel_rddam_E_45->GetBinContent(eff_pixel_rddam_E_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double pixel_weight_rddam_F1 = eff_pixel_rddam_F1_45->GetBinContent(eff_pixel_rddam_F1_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double pixel_weight_rddam = (pixel_weight_rddam_B*L_B + pixel_weight_rddam_C1*L_C1 + pixel_weight_rddam_E*L_E + pixel_weight_rddam_F1*L_F1)/(L_B+L_C1+L_E+L_F1);
                                             double strips_weight_rddam_B = eff_strips_rddam_B_45->GetBinContent(eff_strips_rddam_B_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double strips_weight_rddam_C1 = eff_strips_rddam_C1_45->GetBinContent(eff_strips_rddam_C1_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double strips_weight_rddam_E = eff_strips_rddam_E_45->GetBinContent(eff_strips_rddam_E_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double strips_weight_rddam_F1 = eff_strips_rddam_F1_45->GetBinContent(eff_strips_rddam_F1_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double strips_weight_rddam = (strips_weight_rddam_B*L_B + strips_weight_rddam_C1*L_C1 + strips_weight_rddam_E*L_E + strips_weight_rddam_F1*L_F1)/(L_B+L_C1+L_E+L_F1);
                                             double strips_weight_multitrack_B = eff_strips_multitrack_B_45->GetBinContent(eff_strips_multitrack_B_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double strips_weight_multitrack_C1 = eff_strips_multitrack_C1_45->GetBinContent(eff_strips_multitrack_C1_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double strips_weight_multitrack_E = eff_strips_multitrack_E_45->GetBinContent(eff_strips_multitrack_E_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double strips_weight_multitrack_F1 = eff_strips_multitrack_F1_45->GetBinContent(eff_strips_multitrack_F1_45->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double strips_weight_multitrack = (strips_weight_multitrack_B*L_B + strips_weight_multitrack_C1*L_C1 + strips_weight_multitrack_E*L_E + strips_weight_multitrack_F1*L_F1)/(L_B+L_C1+L_E+L_F1);
                                             double weight = pixel_weight_rddam*strips_weight_rddam*strips_weight_multitrack;
                                             proton_xi_left_multi_eff->Fill(ProtCand_xi[idx], weight);
                                             proton_xi_left_multi->Fill(ProtCand_xi[idx], 0.999999);
                                             proton_resolution_left_gen_multi->Fill((xi_proton_gen_left - ProtCand_xi[idx])/xi_proton_gen_left);
                                             proton_resolution_left_reco_multi->Fill((ProtCand_xi[idx] - xi_proton_gen_left)/ProtCand_xi[idx]);
                                             pair_xi_left_multi->Fill(xi_pair_left_reco);
                                             xi_left_reco_multi->Fill(ProtCand_xi[idx], xi_pair_left_reco); 
                                             g_xi_left_reco_multi->SetPoint(g_xi_left_reco_multi->GetN(), ProtCand_xi[idx], xi_pair_left_reco);
                                             diff_proton_reco_pair_xi_left_multi->Fill(ProtCand_xi[idx] - xi_pair_left_reco); 
                                             ratio_proton_reco_pair_xi_left_multi->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco); 
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
                                             double sigma_xi_left_multi = f_left_multi->Eval( ProtCand_xi[idx] );
                                             if ( sigma_xi_left_multi > 0.) {
                                                double sigma_xi_lm_mumu = TMath::Sqrt( sigma_xi_left_multi*sigma_xi_left_multi + sigma_xi_mumu_left*sigma_xi_mumu_left );
                                                if ( TMath::Abs( ProtCand_xi[idx] - xi_pair_left_reco ) <= n_sigmas_xi*sigma_xi_lm_mumu ) { 
                                                   match = true;
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

                                       if (ProtCand_arm[idx] == 1) {                           
                                          if (ProtCand_ismultirp[idx] == 1) {
                                             double pixel_weight_rddam_B = eff_pixel_rddam_B_56->GetBinContent(eff_pixel_rddam_B_56->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double pixel_weight_rddam_C1 = eff_pixel_rddam_C1_56->GetBinContent(eff_pixel_rddam_C1_56->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double pixel_weight_rddam_E = eff_pixel_rddam_E_56->GetBinContent(eff_pixel_rddam_E_56->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double pixel_weight_rddam_F1 = eff_pixel_rddam_F1_56->GetBinContent(eff_pixel_rddam_F1_56->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double pixel_weight_rddam = (pixel_weight_rddam_B*L_B + pixel_weight_rddam_C1*L_C1 + pixel_weight_rddam_E*L_E + pixel_weight_rddam_F1*L_F1)/(L_B+L_C1+L_E+L_F1);
                                             double strips_weight_rddam_B = eff_strips_rddam_B_56->GetBinContent(eff_strips_rddam_B_56->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double strips_weight_rddam_C1 = eff_strips_rddam_C1_56->GetBinContent(eff_strips_rddam_C1_56->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double strips_weight_rddam_E = eff_strips_rddam_E_56->GetBinContent(eff_strips_rddam_E_56->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double strips_weight_rddam_F1 = eff_strips_rddam_F1_56->GetBinContent(eff_strips_rddam_F1_56->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double strips_weight_rddam = (strips_weight_rddam_B*L_B + strips_weight_rddam_C1*L_C1 + strips_weight_rddam_E*L_E + strips_weight_rddam_F1*L_F1)/(L_B+L_C1+L_E+L_F1);
                                             double strips_weight_multitrack_B = eff_strips_multitrack_B_56->GetBinContent(eff_strips_multitrack_B_56->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double strips_weight_multitrack_C1 = eff_strips_multitrack_C1_56->GetBinContent(eff_strips_multitrack_C1_56->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double strips_weight_multitrack_E = eff_strips_multitrack_E_56->GetBinContent(eff_strips_multitrack_E_56->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double strips_weight_multitrack_F1 = eff_strips_multitrack_F1_56->GetBinContent(eff_strips_multitrack_F1_56->FindBin(ProtCand_trackx1[idx], ProtCand_tracky1[idx]));
                                             double strips_weight_multitrack = (strips_weight_multitrack_B*L_B + strips_weight_multitrack_C1*L_C1 + strips_weight_multitrack_E*L_E + strips_weight_multitrack_F1*L_F1)/(L_B+L_C1+L_E+L_F1);
                                             double weight = pixel_weight_rddam*strips_weight_rddam*strips_weight_multitrack;
                                             proton_xi_right_multi_eff->Fill(ProtCand_xi[idx], weight);
                                             proton_xi_right_multi->Fill(ProtCand_xi[idx], 0.999999);
                                             proton_resolution_right_gen_multi->Fill((xi_proton_gen_right - ProtCand_xi[idx])/xi_proton_gen_right);
                                             proton_resolution_right_reco_multi->Fill((ProtCand_xi[idx] - xi_proton_gen_right)/ProtCand_xi[idx]);
                                             pair_xi_right_multi->Fill(xi_pair_right_reco);
                                             xi_right_reco_multi->Fill(ProtCand_xi[idx], xi_pair_right_reco);
                                             g_xi_right_reco_multi->SetPoint(g_xi_right_reco_multi->GetN(), ProtCand_xi[idx], xi_pair_right_reco);
                                             diff_proton_reco_pair_xi_right_multi->Fill(ProtCand_xi[idx] - xi_pair_right_reco); 
                                             ratio_proton_reco_pair_xi_right_multi->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco); 
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
                                             double sigma_xi_right_multi = f_right_multi->Eval( ProtCand_xi[idx] );
                                             if ( sigma_xi_right_multi > 0.) {
                                                double sigma_xi_rm_mumu = TMath::Sqrt( sigma_xi_right_multi*sigma_xi_right_multi + sigma_xi_mumu_right*sigma_xi_mumu_right );
                                                if ( TMath::Abs( ProtCand_xi[idx] - xi_pair_right_reco ) <= n_sigmas_xi*sigma_xi_rm_mumu ) {
                                                   match = true;
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
                              if (cont_single_rp23==1 && single_rp23_xi > 0){
                                 double weight_rddam_B = eff_pixel_rddam_B_45->GetBinContent(eff_pixel_rddam_B_45->FindBin(single_rp23_trackx1, single_rp23_tracky1));
                                 double weight_rddam_C1 = eff_pixel_rddam_C1_45->GetBinContent(eff_pixel_rddam_C1_45->FindBin(single_rp23_trackx1, single_rp23_tracky1));
                                 double weight_rddam_E = eff_pixel_rddam_E_45->GetBinContent(eff_pixel_rddam_E_45->FindBin(single_rp23_trackx1, single_rp23_tracky1));
                                 double weight_rddam_F1 = eff_pixel_rddam_F1_45->GetBinContent(eff_pixel_rddam_F1_45->FindBin(single_rp23_trackx1, single_rp23_tracky1));
                                 double weight_rddam = (weight_rddam_B*L_B + weight_rddam_C1*L_C1 + weight_rddam_E*L_E + weight_rddam_F1*L_F1)/(L_B+L_C1+L_E+L_F1);
                                 proton_xi_left_rp23_eff->Fill(single_rp23_xi, weight_rddam);
                                 proton_xi_left_rp23->Fill(single_rp23_xi, 0.999999);
                                 xi_left_reco_rp23->Fill(single_rp23_xi,xi_pair_left_reco);
                                 g_xi_left_reco_rp23->SetPoint(g_xi_left_reco_rp23->GetN(), single_rp23_xi, xi_pair_left_reco);
                                 diff_proton_reco_pair_xi_left_rp23->Fill(single_rp23_xi - xi_pair_left_reco); 
                                 ratio_proton_reco_pair_xi_left_rp23->Fill(1 - single_rp23_xi/xi_pair_left_reco); 
                                 if (single_rp23_xi >= 0.02 && single_rp23_xi < 0.04) {
                                    proton_resolution_left_rp23_1->Fill(single_rp23_xi - xi_proton_gen_left);
                                 }
                                 if (single_rp23_xi >= 0.04 && single_rp23_xi < 0.06) {
                                    proton_resolution_left_rp23_2->Fill(single_rp23_xi - xi_proton_gen_left);
                                 }
                                 if (single_rp23_xi >= 0.06 && single_rp23_xi < 0.08) {
                                    proton_resolution_left_rp23_3->Fill(single_rp23_xi - xi_proton_gen_left);
                                 }
                                 if (single_rp23_xi >= 0.08 && single_rp23_xi < 0.10) {
                                    proton_resolution_left_rp23_4->Fill(single_rp23_xi - xi_proton_gen_left);
                                 }
                                 double sigma_xi_left_rp23 = f_rp23->Eval( single_rp23_xi );
                                 if ( sigma_xi_left_rp23 > 0.) {
                                    double sigma_xi_rp23_mumu = TMath::Sqrt( sigma_xi_left_rp23*sigma_xi_left_rp23 + sigma_xi_mumu_left*sigma_xi_mumu_left );
                                    if ( TMath::Abs( single_rp23_xi - xi_pair_left_reco ) <= n_sigmas_xi*sigma_xi_rp23_mumu ) {
                                       match = true;
                                       xi_left_reco_rp23_match->Fill(single_rp23_xi, xi_pair_left_reco);
                                       g_xi_left_reco_rp23_match->SetPoint(g_xi_left_reco_rp23_match->GetN(), single_rp23_xi, xi_pair_left_reco);
                                    }
                                    else {
                                       xi_left_reco_rp23_non_match->Fill(single_rp23_xi, xi_pair_left_reco);
                                       g_xi_left_reco_rp23_non_match->SetPoint(g_xi_left_reco_rp23_non_match->GetN(), single_rp23_xi, xi_pair_left_reco);
                                    }
                                 }
                              }

                              if (cont_single_rp23==1 && single_rp23_xi > 0){
                                 single_left_xi = single_rp23_xi;
                                 single_left_trackx1 = single_rp23_trackx1;
                                 single_left_tracky1 = single_rp23_tracky1;
                                 double weight_rddam_B = eff_pixel_rddam_B_45->GetBinContent(eff_pixel_rddam_B_45->FindBin(single_left_trackx1, single_left_tracky1));
                                 double weight_rddam_C1 = eff_pixel_rddam_C1_45->GetBinContent(eff_pixel_rddam_C1_45->FindBin(single_left_trackx1, single_left_tracky1));
                                 double weight_rddam_E = eff_pixel_rddam_E_45->GetBinContent(eff_pixel_rddam_E_45->FindBin(single_left_trackx1, single_left_tracky1));
                                 double weight_rddam_F1 = eff_pixel_rddam_F1_45->GetBinContent(eff_pixel_rddam_F1_45->FindBin(single_left_trackx1, single_left_tracky1));
                                 double weight_rddam = (weight_rddam_B*L_B + weight_rddam_C1*L_C1 + weight_rddam_E*L_E + weight_rddam_F1*L_F1)/(L_B+L_C1+L_E+L_F1);
                                 proton_xi_left_single_eff->Fill(single_left_xi, weight_rddam);
                                 proton_xi_left_single->Fill(single_left_xi, 0.999999);
                                 xi_left_reco_single->Fill(single_left_xi,xi_pair_left_reco);
                                 g_xi_left_reco_single->SetPoint(g_xi_left_reco_single->GetN(), single_left_xi, xi_pair_left_reco);
                                 diff_proton_reco_pair_xi_left_single->Fill(single_left_xi - xi_pair_left_reco); 
                                 ratio_proton_reco_pair_xi_left_single->Fill(1 - single_left_xi/xi_pair_left_reco); 
                                 if (single_left_xi >= 0.02 && single_left_xi < 0.04) {
                                    proton_resolution_left_single_1->Fill(single_left_xi - xi_proton_gen_left);
                                 }
                                 if (single_left_xi >= 0.04 && single_left_xi < 0.06) {
                                    proton_resolution_left_single_2->Fill(single_left_xi - xi_proton_gen_left);
                                 }
                                 if (single_left_xi >= 0.06 && single_left_xi < 0.08) {
                                    proton_resolution_left_single_3->Fill(single_left_xi - xi_proton_gen_left);
                                 }
                                 if (single_left_xi >= 0.08 && single_left_xi < 0.10) {
                                    proton_resolution_left_single_4->Fill(single_left_xi - xi_proton_gen_left);
                                 }
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
                                 single_left_trackx1 = single_rp3_trackx1;
                                 single_left_tracky1 = single_rp3_tracky1;
                                 double weight_rddam_B = eff_strips_rddam_B_45->GetBinContent(eff_strips_rddam_B_45->FindBin(single_left_trackx1, single_left_tracky1));
                                 double weight_rddam_C1 = eff_strips_rddam_C1_45->GetBinContent(eff_strips_rddam_C1_45->FindBin(single_left_trackx1, single_left_tracky1));
                                 double weight_rddam_E = eff_strips_rddam_E_45->GetBinContent(eff_strips_rddam_E_45->FindBin(single_left_trackx1, single_left_tracky1));
                                 double weight_rddam_F1 = eff_strips_rddam_F1_45->GetBinContent(eff_strips_rddam_F1_45->FindBin(single_left_trackx1, single_left_tracky1));
                                 double weight_rddam = (weight_rddam_B*L_B + weight_rddam_C1*L_C1 + weight_rddam_E*L_E + weight_rddam_F1*L_F1)/(L_B+L_C1+L_E+L_F1);
                                 double weight_multitrack_B = eff_strips_multitrack_B_45->GetBinContent(eff_strips_multitrack_B_45->FindBin(single_left_trackx1, single_left_tracky1));
                                 double weight_multitrack_C1 = eff_strips_multitrack_C1_45->GetBinContent(eff_strips_multitrack_C1_45->FindBin(single_left_trackx1, single_left_tracky1));
                                 double weight_multitrack_E = eff_strips_multitrack_E_45->GetBinContent(eff_strips_multitrack_E_45->FindBin(single_left_trackx1, single_left_tracky1));
                                 double weight_multitrack_F1 = eff_strips_multitrack_F1_45->GetBinContent(eff_strips_multitrack_F1_45->FindBin(single_left_trackx1, single_left_tracky1));
                                 double weight_multitrack = (weight_multitrack_B*L_B + weight_multitrack_C1*L_C1 + weight_multitrack_E*L_E + weight_multitrack_F1*L_F1)/(L_B+L_C1+L_E+L_F1);
                                 double weight = weight_rddam*weight_multitrack;
                                 proton_xi_left_single_eff->Fill(single_left_xi, weight);
                                 proton_xi_left_single->Fill(single_left_xi, 0.999999);
                                 xi_left_reco_single->Fill(single_left_xi,xi_pair_left_reco);
                                 g_xi_left_reco_single->SetPoint(g_xi_left_reco_single->GetN(), single_left_xi, xi_pair_left_reco);
                                 diff_proton_reco_pair_xi_left_single->Fill(single_left_xi - xi_pair_left_reco); 
                                 ratio_proton_reco_pair_xi_left_single->Fill(1 - single_left_xi/xi_pair_left_reco); 
                                 if (single_left_xi >= 0.02 && single_left_xi < 0.04) {
                                    proton_resolution_left_single_1->Fill(single_left_xi - xi_proton_gen_left);
                                 }
                                 if (single_left_xi >= 0.04 && single_left_xi < 0.06) {
                                    proton_resolution_left_single_2->Fill(single_left_xi - xi_proton_gen_left);
                                 }
                                 if (single_left_xi >= 0.06 && single_left_xi < 0.08) {
                                    proton_resolution_left_single_3->Fill(single_left_xi - xi_proton_gen_left);
                                 }
                                 if (single_left_xi >= 0.08 && single_left_xi < 0.10) {
                                    proton_resolution_left_single_4->Fill(single_left_xi - xi_proton_gen_left);
                                 }
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

                              if (cont_single_rp123==1 && single_rp123_xi > 0){
                                 double weight_rddam_B = eff_pixel_rddam_B_56->GetBinContent(eff_pixel_rddam_B_56->FindBin(single_rp123_trackx1, single_rp123_tracky1));
                                 double weight_rddam_C1 = eff_pixel_rddam_C1_56->GetBinContent(eff_pixel_rddam_C1_56->FindBin(single_rp123_trackx1, single_rp123_tracky1));
                                 double weight_rddam_E = eff_pixel_rddam_E_56->GetBinContent(eff_pixel_rddam_E_56->FindBin(single_rp123_trackx1, single_rp123_tracky1));
                                 double weight_rddam_F1 = eff_pixel_rddam_F1_56->GetBinContent(eff_pixel_rddam_F1_56->FindBin(single_rp123_trackx1, single_rp123_tracky1));
                                 double weight_rddam = (weight_rddam_B*L_B + weight_rddam_C1*L_C1 + weight_rddam_E*L_E + weight_rddam_F1*L_F1)/(L_B+L_C1+L_E+L_F1);
                                 proton_xi_right_rp123_eff->Fill(single_rp123_xi, weight_rddam);
                                 proton_xi_right_rp123->Fill(single_rp123_xi, 0.999999);
                                 xi_right_reco_rp123->Fill(single_rp123_xi,xi_pair_right_reco);
                                 g_xi_right_reco_rp123->SetPoint(g_xi_right_reco_rp123->GetN(), single_rp123_xi, xi_pair_right_reco);
                                 diff_proton_reco_pair_xi_right_rp123->Fill(single_rp123_xi - xi_pair_right_reco); 
                                 ratio_proton_reco_pair_xi_right_rp123->Fill(1 - single_rp123_xi/xi_pair_right_reco); 
                                 if (single_rp123_xi >= 0.02 && single_rp123_xi < 0.04) {
                                    proton_resolution_right_rp123_1->Fill(single_rp123_xi - xi_proton_gen_right);
                                 }
                                 if (single_rp123_xi >= 0.04 && single_rp123_xi < 0.06) {
                                    proton_resolution_right_rp123_2->Fill(single_rp123_xi - xi_proton_gen_right);
                                 }
                                 if (single_rp123_xi >= 0.06 && single_rp123_xi < 0.08) {
                                    proton_resolution_right_rp123_3->Fill(single_rp123_xi - xi_proton_gen_right);
                                 }
                                 if (single_rp123_xi >= 0.08 && single_rp123_xi < 0.10) {
                                    proton_resolution_right_rp123_4->Fill(single_rp123_xi - xi_proton_gen_right);
                                 }
                                 double sigma_xi_right_rp123 = f_rp123->Eval( single_rp123_xi );
                                 if ( sigma_xi_right_rp123 > 0.) {
                                    double sigma_xi_rp123_mumu = TMath::Sqrt( sigma_xi_right_rp123*sigma_xi_right_rp123 + sigma_xi_mumu_right*sigma_xi_mumu_right );
                                    if ( TMath::Abs( single_rp123_xi - xi_pair_right_reco ) <= n_sigmas_xi*sigma_xi_rp123_mumu ) {
                                       match = true;
                                       xi_right_reco_rp123_match->Fill(single_rp123_xi, xi_pair_right_reco);
                                       g_xi_right_reco_rp123_match->SetPoint(g_xi_right_reco_rp123_match->GetN(), single_rp123_xi, xi_pair_right_reco);
                                    }
                                    else {
                                       xi_right_reco_rp123_non_match->Fill(single_rp123_xi, xi_pair_right_reco);
                                       g_xi_right_reco_rp123_non_match->SetPoint(g_xi_right_reco_rp123_non_match->GetN(), single_rp123_xi, xi_pair_right_reco);
                                    }
                                 }
                              }

                              if (cont_single_rp123==1 && single_rp123_xi > 0){
                                 single_right_xi = single_rp123_xi;
                                 single_right_trackx1 = single_rp123_trackx1;
                                 single_right_tracky1 = single_rp123_tracky1;
                                 double weight_rddam_B = eff_pixel_rddam_B_56->GetBinContent(eff_pixel_rddam_B_56->FindBin(single_right_trackx1, single_right_tracky1));
                                 double weight_rddam_C1 = eff_pixel_rddam_C1_56->GetBinContent(eff_pixel_rddam_C1_56->FindBin(single_right_trackx1, single_right_tracky1));
                                 double weight_rddam_E = eff_pixel_rddam_E_56->GetBinContent(eff_pixel_rddam_E_56->FindBin(single_right_trackx1, single_right_tracky1));
                                 double weight_rddam_F1 = eff_pixel_rddam_F1_56->GetBinContent(eff_pixel_rddam_F1_56->FindBin(single_right_trackx1, single_right_tracky1));
                                 double weight_rddam = (weight_rddam_B*L_B + weight_rddam_C1*L_C1 + weight_rddam_E*L_E + weight_rddam_F1*L_F1)/(L_B+L_C1+L_E+L_F1);
                                 proton_xi_right_single_eff->Fill(single_right_xi, weight_rddam);
                                 proton_xi_right_single->Fill(single_right_xi, 0.999999);
                                 xi_right_reco_single->Fill(single_right_xi,xi_pair_right_reco);
                                 g_xi_right_reco_single->SetPoint(g_xi_right_reco_single->GetN(), single_right_xi, xi_pair_right_reco);
                                 diff_proton_reco_pair_xi_right_single->Fill(single_right_xi - xi_pair_right_reco); 
                                 ratio_proton_reco_pair_xi_right_single->Fill(1 - single_right_xi/xi_pair_right_reco); 
                                 if (single_right_xi >= 0.02 && single_right_xi < 0.04) {
                                    proton_resolution_right_single_1->Fill(single_right_xi - xi_proton_gen_right);
                                 }
                                 if (single_right_xi >= 0.04 && single_right_xi < 0.06) {
                                    proton_resolution_right_single_2->Fill(single_right_xi - xi_proton_gen_right);
                                 }
                                 if (single_right_xi >= 0.06 && single_right_xi < 0.08) {
                                    proton_resolution_right_single_3->Fill(single_right_xi - xi_proton_gen_right);
                                 }
                                 if (single_right_xi >= 0.08 && single_right_xi < 0.10) {
                                    proton_resolution_right_single_4->Fill(single_right_xi - xi_proton_gen_right);
                                 }
                                 double sigma_xi_right_single = f_right_single->Eval( single_right_xi );
                                 if ( sigma_xi_right_single > 0.) {
                                    double sigma_xi_rs_mumu = TMath::Sqrt( sigma_xi_right_single*sigma_xi_right_single + sigma_xi_mumu_right*sigma_xi_mumu_right );
                                    if ( TMath::Abs( single_right_xi - xi_pair_right_reco ) <= n_sigmas_xi*sigma_xi_rs_mumu ) {
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
                                 single_right_trackx1 = single_rp103_trackx1;
                                 single_right_tracky1 = single_rp103_tracky1;
                                 double weight_rddam_B = eff_strips_rddam_B_56->GetBinContent(eff_strips_rddam_B_56->FindBin(single_right_trackx1, single_right_tracky1));
                                 double weight_rddam_C1 = eff_strips_rddam_C1_56->GetBinContent(eff_strips_rddam_C1_56->FindBin(single_right_trackx1, single_right_tracky1));
                                 double weight_rddam_E = eff_strips_rddam_E_56->GetBinContent(eff_strips_rddam_E_56->FindBin(single_right_trackx1, single_right_tracky1));
                                 double weight_rddam_F1 = eff_strips_rddam_F1_56->GetBinContent(eff_strips_rddam_F1_56->FindBin(single_right_trackx1, single_right_tracky1));
                                 double weight_rddam = (weight_rddam_B*L_B + weight_rddam_C1*L_C1 + weight_rddam_E*L_E + weight_rddam_F1*L_F1)/(L_B+L_C1+L_E+L_F1);
                                 double weight_multitrack_B = eff_strips_multitrack_B_56->GetBinContent(eff_strips_multitrack_B_56->FindBin(single_right_trackx1, single_right_tracky1));
                                 double weight_multitrack_C1 = eff_strips_multitrack_C1_56->GetBinContent(eff_strips_multitrack_C1_56->FindBin(single_right_trackx1, single_right_tracky1));
                                 double weight_multitrack_E = eff_strips_multitrack_E_56->GetBinContent(eff_strips_multitrack_E_56->FindBin(single_right_trackx1, single_right_tracky1));
                                 double weight_multitrack_F1 = eff_strips_multitrack_F1_56->GetBinContent(eff_strips_multitrack_F1_56->FindBin(single_right_trackx1, single_right_tracky1));
                                 double weight_multitrack = (weight_multitrack_B*L_B + weight_multitrack_C1*L_C1 + weight_multitrack_E*L_E + weight_multitrack_F1*L_F1)/(L_B+L_C1+L_E+L_F1);
                                 double weight = weight_rddam*weight_multitrack;
                                 proton_xi_right_single_eff->Fill(single_right_xi, weight);
                                 proton_xi_right_single->Fill(single_right_xi, 0.999999);
                                 xi_right_reco_single->Fill(single_right_xi,xi_pair_right_reco);
                                 g_xi_right_reco_single->SetPoint(g_xi_right_reco_single->GetN(), single_right_xi, xi_pair_right_reco);
                                 diff_proton_reco_pair_xi_right_single->Fill(single_right_xi - xi_pair_right_reco); 
                                 ratio_proton_reco_pair_xi_right_single->Fill(1 - single_right_xi/xi_pair_right_reco); 
                                 if (single_right_xi >= 0.02 && single_right_xi < 0.04) {
                                    proton_resolution_right_single_1->Fill(single_right_xi - xi_proton_gen_right);
                                 }
                                 if (single_right_xi >= 0.04 && single_right_xi < 0.06) {
                                    proton_resolution_right_single_2->Fill(single_right_xi - xi_proton_gen_right);
                                 }
                                 if (single_right_xi >= 0.06 && single_right_xi < 0.08) {
                                    proton_resolution_right_single_3->Fill(single_right_xi - xi_proton_gen_right);
                                 }
                                 if (single_right_xi >= 0.08 && single_right_xi < 0.10) {
                                    proton_resolution_right_single_4->Fill(single_right_xi - xi_proton_gen_right);
                                 }
                                 double sigma_xi_right_single = f_right_single->Eval( single_right_xi );
                                 if ( sigma_xi_right_single > 0.) {
                                    double sigma_xi_rs_mumu = TMath::Sqrt( sigma_xi_right_single*sigma_xi_right_single + sigma_xi_mumu_right*sigma_xi_mumu_right );
                                    if ( TMath::Abs( single_right_xi - xi_pair_right_reco ) <= n_sigmas_xi*sigma_xi_rs_mumu ) {
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

   double xi_pair_left[5];
   double xi_pair_left_err[5];
   xi_pair_resolution_left_1->Fit("gaus");
   TF1 *f_xi_pair_resolution_left_1 = (TF1*)xi_pair_resolution_left_1->GetListOfFunctions()->FindObject("gaus");
   xi_pair_left[0] = f_xi_pair_resolution_left_1->GetParameter(2);
   xi_pair_left_err[0] = f_xi_pair_resolution_left_1->GetParError(2);
   xi_pair_resolution_left_2->Fit("gaus");
   TF1 *f_xi_pair_resolution_left_2 = (TF1*)xi_pair_resolution_left_2->GetListOfFunctions()->FindObject("gaus");
   xi_pair_left[1] = f_xi_pair_resolution_left_2->GetParameter(2);
   xi_pair_left_err[1] = f_xi_pair_resolution_left_2->GetParError(2);
   xi_pair_resolution_left_3->Fit("gaus");
   TF1 *f_xi_pair_resolution_left_3 = (TF1*)xi_pair_resolution_left_3->GetListOfFunctions()->FindObject("gaus");
   xi_pair_left[2] = f_xi_pair_resolution_left_3->GetParameter(2);
   xi_pair_left_err[2] = f_xi_pair_resolution_left_3->GetParError(2);
   xi_pair_resolution_left_4->Fit("gaus");
   TF1 *f_xi_pair_resolution_left_4 = (TF1*)xi_pair_resolution_left_4->GetListOfFunctions()->FindObject("gaus");
   xi_pair_left[3] = f_xi_pair_resolution_left_4->GetParameter(2);
   xi_pair_left_err[3] = f_xi_pair_resolution_left_4->GetParError(2);

   double xi_pair_right[5];
   double xi_pair_right_err[5];
   xi_pair_resolution_right_1->Fit("gaus");
   TF1 *f_xi_pair_resolution_right_1 = (TF1*)xi_pair_resolution_right_1->GetListOfFunctions()->FindObject("gaus");
   xi_pair_right[0] = f_xi_pair_resolution_right_1->GetParameter(2);
   xi_pair_right_err[0] = f_xi_pair_resolution_right_1->GetParError(2);
   xi_pair_resolution_right_2->Fit("gaus");
   TF1 *f_xi_pair_resolution_right_2 = (TF1*)xi_pair_resolution_right_2->GetListOfFunctions()->FindObject("gaus");
   xi_pair_right[1] = f_xi_pair_resolution_right_2->GetParameter(2);
   xi_pair_right_err[1] = f_xi_pair_resolution_right_2->GetParError(2);
   xi_pair_resolution_right_3->Fit("gaus");
   TF1 *f_xi_pair_resolution_right_3 = (TF1*)xi_pair_resolution_right_3->GetListOfFunctions()->FindObject("gaus");
   xi_pair_right[2] = f_xi_pair_resolution_right_3->GetParameter(2);
   xi_pair_right_err[2] = f_xi_pair_resolution_right_3->GetParError(2);
   xi_pair_resolution_right_4->Fit("gaus");
   TF1 *f_xi_pair_resolution_right_4 = (TF1*)xi_pair_resolution_right_4->GetListOfFunctions()->FindObject("gaus");
   xi_pair_right[3] = f_xi_pair_resolution_right_4->GetParameter(2);
   xi_pair_right_err[3] = f_xi_pair_resolution_right_4->GetParError(2);

   double proton_left_rp3[5];
   double proton_left_rp3_err[5];
   proton_resolution_left_rp3_1->Fit("gaus");
   TF1 *f_proton_resolution_left_rp3_1 = (TF1*)proton_resolution_left_rp3_1->GetListOfFunctions()->FindObject("gaus");
   proton_left_rp3[0] = f_proton_resolution_left_rp3_1->GetParameter(2);
   proton_left_rp3_err[0] = f_proton_resolution_left_rp3_1->GetParError(2);
   proton_resolution_left_rp3_2->Fit("gaus");
   TF1 *f_proton_resolution_left_rp3_2 = (TF1*)proton_resolution_left_rp3_2->GetListOfFunctions()->FindObject("gaus");
   proton_left_rp3[1] = f_proton_resolution_left_rp3_2->GetParameter(2);
   proton_left_rp3_err[1] = f_proton_resolution_left_rp3_2->GetParError(2);
   proton_resolution_left_rp3_3->Fit("gaus");
   TF1 *f_proton_resolution_left_rp3_3 = (TF1*)proton_resolution_left_rp3_3->GetListOfFunctions()->FindObject("gaus");
   proton_left_rp3[2] = f_proton_resolution_left_rp3_3->GetParameter(2);
   proton_left_rp3_err[2] = f_proton_resolution_left_rp3_3->GetParError(2);
   proton_resolution_left_rp3_4->Fit("gaus");
   TF1 *f_proton_resolution_left_rp3_4 = (TF1*)proton_resolution_left_rp3_4->GetListOfFunctions()->FindObject("gaus");
   proton_left_rp3[3] = f_proton_resolution_left_rp3_4->GetParameter(2);
   proton_left_rp3_err[3] = f_proton_resolution_left_rp3_4->GetParError(2);

   double proton_left_rp23[5];
   double proton_left_rp23_err[5];
   proton_resolution_left_rp23_1->Fit("gaus");
   TF1 *f_proton_resolution_left_rp23_1 = (TF1*)proton_resolution_left_rp23_1->GetListOfFunctions()->FindObject("gaus");
   proton_left_rp23[0] = f_proton_resolution_left_rp23_1->GetParameter(2);
   proton_left_rp23_err[0] = f_proton_resolution_left_rp23_1->GetParError(2);
   proton_resolution_left_rp23_2->Fit("gaus");
   TF1 *f_proton_resolution_left_rp23_2 = (TF1*)proton_resolution_left_rp23_2->GetListOfFunctions()->FindObject("gaus");
   proton_left_rp23[1] = f_proton_resolution_left_rp23_2->GetParameter(2);
   proton_left_rp23_err[1] = f_proton_resolution_left_rp23_2->GetParError(2);
   proton_resolution_left_rp23_3->Fit("gaus");
   TF1 *f_proton_resolution_left_rp23_3 = (TF1*)proton_resolution_left_rp23_3->GetListOfFunctions()->FindObject("gaus");
   proton_left_rp23[2] = f_proton_resolution_left_rp23_3->GetParameter(2);
   proton_left_rp23_err[2] = f_proton_resolution_left_rp23_3->GetParError(2);
   proton_resolution_left_rp23_4->Fit("gaus");
   TF1 *f_proton_resolution_left_rp23_4 = (TF1*)proton_resolution_left_rp23_4->GetListOfFunctions()->FindObject("gaus");
   proton_left_rp23[3] = f_proton_resolution_left_rp23_4->GetParameter(2);
   proton_left_rp23_err[3] = f_proton_resolution_left_rp23_4->GetParError(2);

   double proton_left_rp23_nprot[5];
   double proton_left_rp23_nprot_err[5];
   proton_resolution_left_rp23_nprot_1->Fit("gaus");
   TF1 *f_proton_resolution_left_rp23_nprot_1 = (TF1*)proton_resolution_left_rp23_nprot_1->GetListOfFunctions()->FindObject("gaus");
   proton_left_rp23_nprot[0] = f_proton_resolution_left_rp23_nprot_1->GetParameter(2);
   proton_left_rp23_nprot_err[0] = f_proton_resolution_left_rp23_nprot_1->GetParError(2);
   proton_resolution_left_rp23_nprot_2->Fit("gaus");
   TF1 *f_proton_resolution_left_rp23_nprot_2 = (TF1*)proton_resolution_left_rp23_nprot_2->GetListOfFunctions()->FindObject("gaus");
   proton_left_rp23_nprot[1] = f_proton_resolution_left_rp23_nprot_2->GetParameter(2);
   proton_left_rp23_nprot_err[1] = f_proton_resolution_left_rp23_nprot_2->GetParError(2);
   proton_resolution_left_rp23_nprot_3->Fit("gaus");
   TF1 *f_proton_resolution_left_rp23_nprot_3 = (TF1*)proton_resolution_left_rp23_nprot_3->GetListOfFunctions()->FindObject("gaus");
   proton_left_rp23_nprot[2] = f_proton_resolution_left_rp23_nprot_3->GetParameter(2);
   proton_left_rp23_nprot_err[2] = f_proton_resolution_left_rp23_nprot_3->GetParError(2);
   proton_resolution_left_rp23_nprot_4->Fit("gaus");
   TF1 *f_proton_resolution_left_rp23_nprot_4 = (TF1*)proton_resolution_left_rp23_nprot_4->GetListOfFunctions()->FindObject("gaus");
   proton_left_rp23_nprot[3] = f_proton_resolution_left_rp23_nprot_4->GetParameter(2);
   proton_left_rp23_nprot_err[3] = f_proton_resolution_left_rp23_nprot_4->GetParError(2);

   double proton_left_single[5];
   double proton_left_single_err[5];
   proton_resolution_left_single_1->Fit("gaus");
   TF1 *f_proton_resolution_left_single_1 = (TF1*)proton_resolution_left_single_1->GetListOfFunctions()->FindObject("gaus");
   proton_left_single[0] = f_proton_resolution_left_single_1->GetParameter(2);
   proton_left_single_err[0] = f_proton_resolution_left_single_1->GetParError(2);
   proton_resolution_left_single_2->Fit("gaus");
   TF1 *f_proton_resolution_left_single_2 = (TF1*)proton_resolution_left_single_2->GetListOfFunctions()->FindObject("gaus");
   proton_left_single[1] = f_proton_resolution_left_single_2->GetParameter(2);
   proton_left_single_err[1] = f_proton_resolution_left_single_2->GetParError(2);
   proton_resolution_left_single_3->Fit("gaus");
   TF1 *f_proton_resolution_left_single_3 = (TF1*)proton_resolution_left_single_3->GetListOfFunctions()->FindObject("gaus");
   proton_left_single[2] = f_proton_resolution_left_single_3->GetParameter(2);
   proton_left_single_err[2] = f_proton_resolution_left_single_3->GetParError(2);
   proton_resolution_left_single_4->Fit("gaus");
   TF1 *f_proton_resolution_left_single_4 = (TF1*)proton_resolution_left_single_4->GetListOfFunctions()->FindObject("gaus");
   proton_left_single[3] = f_proton_resolution_left_single_4->GetParameter(2);
   proton_left_single_err[3] = f_proton_resolution_left_single_4->GetParError(2);

   double proton_right_rp103[5];
   double proton_right_rp103_err[5];
   proton_resolution_right_rp103_1->Fit("gaus");
   TF1 *f_proton_resolution_right_rp103_1 = (TF1*)proton_resolution_right_rp103_1->GetListOfFunctions()->FindObject("gaus");
   proton_right_rp103[0] = f_proton_resolution_right_rp103_1->GetParameter(2);
   proton_right_rp103_err[0] = f_proton_resolution_right_rp103_1->GetParError(2);
   proton_resolution_right_rp103_2->Fit("gaus");
   TF1 *f_proton_resolution_right_rp103_2 = (TF1*)proton_resolution_right_rp103_2->GetListOfFunctions()->FindObject("gaus");
   proton_right_rp103[1] = f_proton_resolution_right_rp103_2->GetParameter(2);
   proton_right_rp103_err[1] = f_proton_resolution_right_rp103_2->GetParError(2);
   proton_resolution_right_rp103_3->Fit("gaus");
   TF1 *f_proton_resolution_right_rp103_3 = (TF1*)proton_resolution_right_rp103_3->GetListOfFunctions()->FindObject("gaus");
   proton_right_rp103[2] = f_proton_resolution_right_rp103_3->GetParameter(2);
   proton_right_rp103_err[2] = f_proton_resolution_right_rp103_3->GetParError(2);
   proton_resolution_right_rp103_4->Fit("gaus");
   TF1 *f_proton_resolution_right_rp103_4 = (TF1*)proton_resolution_right_rp103_4->GetListOfFunctions()->FindObject("gaus");
   proton_right_rp103[3] = f_proton_resolution_right_rp103_4->GetParameter(2);
   proton_right_rp103_err[3] = f_proton_resolution_right_rp103_4->GetParError(2);

   double proton_right_rp123[5];
   double proton_right_rp123_err[5];
   proton_resolution_right_rp123_1->Fit("gaus");
   TF1 *f_proton_resolution_right_rp123_1 = (TF1*)proton_resolution_right_rp123_1->GetListOfFunctions()->FindObject("gaus");
   proton_right_rp123[0] = f_proton_resolution_right_rp123_1->GetParameter(2);
   proton_right_rp123_err[0] = f_proton_resolution_right_rp123_1->GetParError(2);
   proton_resolution_right_rp123_2->Fit("gaus");
   TF1 *f_proton_resolution_right_rp123_2 = (TF1*)proton_resolution_right_rp123_2->GetListOfFunctions()->FindObject("gaus");
   proton_right_rp123[1] = f_proton_resolution_right_rp123_2->GetParameter(2);
   proton_right_rp123_err[1] = f_proton_resolution_right_rp123_2->GetParError(2);
   proton_resolution_right_rp123_3->Fit("gaus");
   TF1 *f_proton_resolution_right_rp123_3 = (TF1*)proton_resolution_right_rp123_3->GetListOfFunctions()->FindObject("gaus");
   proton_right_rp123[2] = f_proton_resolution_right_rp123_3->GetParameter(2);
   proton_right_rp123_err[2] = f_proton_resolution_right_rp123_3->GetParError(2);
   proton_resolution_right_rp123_4->Fit("gaus");
   TF1 *f_proton_resolution_right_rp123_4 = (TF1*)proton_resolution_right_rp123_4->GetListOfFunctions()->FindObject("gaus");
   proton_right_rp123[3] = f_proton_resolution_right_rp123_4->GetParameter(2);
   proton_right_rp123_err[3] = f_proton_resolution_right_rp123_4->GetParError(2);

   double proton_right_rp123_nprot[5];
   double proton_right_rp123_nprot_err[5];
   proton_resolution_right_rp123_nprot_1->Fit("gaus");
   TF1 *f_proton_resolution_right_rp123_nprot_1 = (TF1*)proton_resolution_right_rp123_nprot_1->GetListOfFunctions()->FindObject("gaus");
   proton_right_rp123_nprot[0] = f_proton_resolution_right_rp123_nprot_1->GetParameter(2);
   proton_right_rp123_nprot_err[0] = f_proton_resolution_right_rp123_nprot_1->GetParError(2);
   proton_resolution_right_rp123_nprot_2->Fit("gaus");
   TF1 *f_proton_resolution_right_rp123_nprot_2 = (TF1*)proton_resolution_right_rp123_nprot_2->GetListOfFunctions()->FindObject("gaus");
   proton_right_rp123_nprot[1] = f_proton_resolution_right_rp123_nprot_2->GetParameter(2);
   proton_right_rp123_nprot_err[1] = f_proton_resolution_right_rp123_nprot_2->GetParError(2);
   proton_resolution_right_rp123_nprot_3->Fit("gaus");
   TF1 *f_proton_resolution_right_rp123_nprot_3 = (TF1*)proton_resolution_right_rp123_nprot_3->GetListOfFunctions()->FindObject("gaus");
   proton_right_rp123_nprot[2] = f_proton_resolution_right_rp123_nprot_3->GetParameter(2);
   proton_right_rp123_nprot_err[2] = f_proton_resolution_right_rp123_nprot_3->GetParError(2);
   proton_resolution_right_rp123_nprot_4->Fit("gaus");
   TF1 *f_proton_resolution_right_rp123_nprot_4 = (TF1*)proton_resolution_right_rp123_nprot_4->GetListOfFunctions()->FindObject("gaus");
   proton_right_rp123_nprot[3] = f_proton_resolution_right_rp123_nprot_4->GetParameter(2);
   proton_right_rp123_nprot_err[3] = f_proton_resolution_right_rp123_nprot_4->GetParError(2);

   double proton_right_single[5];
   double proton_right_single_err[5];
   proton_resolution_right_single_1->Fit("gaus");
   TF1 *f_proton_resolution_right_single_1 = (TF1*)proton_resolution_right_single_1->GetListOfFunctions()->FindObject("gaus");
   proton_right_single[0] = f_proton_resolution_right_single_1->GetParameter(2);
   proton_right_single_err[0] = f_proton_resolution_right_single_1->GetParError(2);
   proton_resolution_right_single_2->Fit("gaus");
   TF1 *f_proton_resolution_right_single_2 = (TF1*)proton_resolution_right_single_2->GetListOfFunctions()->FindObject("gaus");
   proton_right_single[1] = f_proton_resolution_right_single_2->GetParameter(2);
   proton_right_single_err[1] = f_proton_resolution_right_single_2->GetParError(2);
   proton_resolution_right_single_3->Fit("gaus");
   TF1 *f_proton_resolution_right_single_3 = (TF1*)proton_resolution_right_single_3->GetListOfFunctions()->FindObject("gaus");
   proton_right_single[2] = f_proton_resolution_right_single_3->GetParameter(2);
   proton_right_single_err[2] = f_proton_resolution_right_single_3->GetParError(2);
   proton_resolution_right_single_4->Fit("gaus");
   TF1 *f_proton_resolution_right_single_4 = (TF1*)proton_resolution_right_single_4->GetListOfFunctions()->FindObject("gaus");
   proton_right_single[3] = f_proton_resolution_right_single_4->GetParameter(2);
   proton_right_single_err[3] = f_proton_resolution_right_single_4->GetParError(2);

   double proton_left_multi[5];
   double proton_left_multi_err[5];
   proton_resolution_left_multi_1->Fit("gaus");
   TF1 *f_proton_resolution_left_multi_1 = (TF1*)proton_resolution_left_multi_1->GetListOfFunctions()->FindObject("gaus");
   proton_left_multi[0] = f_proton_resolution_left_multi_1->GetParameter(2);
   proton_left_multi_err[0] = f_proton_resolution_left_multi_1->GetParError(2);
   proton_resolution_left_multi_2->Fit("gaus");
   TF1 *f_proton_resolution_left_multi_2 = (TF1*)proton_resolution_left_multi_2->GetListOfFunctions()->FindObject("gaus");
   proton_left_multi[1] = f_proton_resolution_left_multi_2->GetParameter(2);
   proton_left_multi_err[1] = f_proton_resolution_left_multi_2->GetParError(2);
   proton_resolution_left_multi_3->Fit("gaus");
   TF1 *f_proton_resolution_left_multi_3 = (TF1*)proton_resolution_left_multi_3->GetListOfFunctions()->FindObject("gaus");
   proton_left_multi[2] = f_proton_resolution_left_multi_3->GetParameter(2);
   proton_left_multi_err[2] = f_proton_resolution_left_multi_3->GetParError(2);
   proton_resolution_left_multi_4->Fit("gaus");
   TF1 *f_proton_resolution_left_multi_4 = (TF1*)proton_resolution_left_multi_4->GetListOfFunctions()->FindObject("gaus");
   proton_left_multi[3] = f_proton_resolution_left_multi_4->GetParameter(2);
   proton_left_multi_err[3] = f_proton_resolution_left_multi_4->GetParError(2);

   double proton_right_multi[5];
   double proton_right_multi_err[5];
   proton_resolution_right_multi_1->Fit("gaus");
   TF1 *f_proton_resolution_right_multi_1 = (TF1*)proton_resolution_right_multi_1->GetListOfFunctions()->FindObject("gaus");
   proton_right_multi[0] = f_proton_resolution_right_multi_1->GetParameter(2);
   proton_right_multi_err[0] = f_proton_resolution_right_multi_1->GetParError(2);
   proton_resolution_right_multi_2->Fit("gaus");
   TF1 *f_proton_resolution_right_multi_2 = (TF1*)proton_resolution_right_multi_2->GetListOfFunctions()->FindObject("gaus");
   proton_right_multi[1] = f_proton_resolution_right_multi_2->GetParameter(2);
   proton_right_multi_err[1] = f_proton_resolution_right_multi_2->GetParError(2);
   proton_resolution_right_multi_3->Fit("gaus");
   TF1 *f_proton_resolution_right_multi_3 = (TF1*)proton_resolution_right_multi_3->GetListOfFunctions()->FindObject("gaus");
   proton_right_multi[2] = f_proton_resolution_right_multi_3->GetParameter(2);
   proton_right_multi_err[2] = f_proton_resolution_right_multi_3->GetParError(2);
   proton_resolution_right_multi_4->Fit("gaus");
   TF1 *f_proton_resolution_right_multi_4 = (TF1*)proton_resolution_right_multi_4->GetListOfFunctions()->FindObject("gaus");
   proton_right_multi[3] = f_proton_resolution_right_multi_4->GetParameter(2);
   proton_right_multi_err[3] = f_proton_resolution_right_multi_4->GetParError(2);

   cout << "0cortes: " << zerocortes << endl;
   cout << "1cortes: " << umcortes << endl;
   cout << "2cortes: " << doiscortes << endl;
   cout << "3cortes: " << trescortes << endl;
   cout << "4cortes: " << quatrocortes << endl;
   cout << "5cortes: " << cincocortes << endl;
   cout << "6cortes: " << seiscortes << endl;
   cout << "7cortes: " << setecortes << endl;
   cout << "8cortes: " << oitocortes << endl;

   Int_t n = 4;

   TCanvas *pair_left = new TCanvas("pair_left","#sigma x #xi - Pair Left",200,10,700,500);
   Double_t x_pair_left[5], y_pair_left[5], ex_pair_left[5], ey_pair_left[5];
   for (Int_t i = 0;i<n;i++) {
      x_pair_left[i] = 0.03+0.02*i;
      y_pair_left[i] = xi_pair_left[i];
      ex_pair_left[i] = 0.01;
      ey_pair_left[i] = xi_pair_left_err[i];
   }
   TGraph *gr_pair_left = new TGraphErrors(n,x_pair_left,y_pair_left,ex_pair_left,ey_pair_left);
   gr_pair_left->SetTitle("#sigma x #xi - Pair Left");
   gr_pair_left->SetName("gr_pair_left");
   gr_pair_left->Fit("pol1");

   TCanvas *pair_right = new TCanvas("pair_right","#sigma x #xi - Pair Right",200,10,700,500);
   Double_t x_pair_right[5], y_pair_right[5], ex_pair_right[5], ey_pair_right[5];
   for (Int_t i = 0;i<n;i++) {
      x_pair_right[i] = 0.03+0.02*i;
      y_pair_right[i] = xi_pair_right[i];
      ex_pair_right[i] = 0.01;
      ey_pair_right[i] = xi_pair_right_err[i];
   }
   TGraph *gr_pair_right = new TGraphErrors(n,x_pair_right,y_pair_right,ex_pair_right,ey_pair_right);
   gr_pair_right->SetTitle("#sigma x #xi - Pair Right");
   gr_pair_right->SetName("gr_pair_right");
   gr_pair_right->Fit("pol1");

   TCanvas *rp3 = new TCanvas("rp3","#sigma x #xi - Proton Left - RP 3",200,10,700,500);
   Double_t x_rp3[5], y_rp3[5], ex_rp3[5], ey_rp3[5];
   for (Int_t i = 0;i<n;i++) {
      x_rp3[i] = 0.03+0.02*i;
      y_rp3[i] = proton_left_rp3[i];
      ex_rp3[i] = 0.01;
      ey_rp3[i] = proton_left_rp3_err[i];
   }
   TGraph *gr_rp3 = new TGraphErrors(n,x_rp3,y_rp3,ex_rp3,ey_rp3);
   gr_rp3->SetTitle("#sigma x #xi - Proton Left - RP 3");
   gr_rp3->SetName("gr_rp3");
   gr_rp3->Fit("pol1");

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
   gr_rp23->SetName("gr_rp23");
   gr_rp23->Fit("pol1");

   TCanvas *rp23_nprot = new TCanvas("rp23_nprot","#sigma x #xi - Proton Left - RP 23",200,10,700,500);
   Double_t x_rp23_nprot[10], y_rp23_nprot[10], ex_rp23_nprot[10], ey_rp23_nprot[10];
   for (Int_t i = 0;i<n;i++) {
      x_rp23_nprot[i] = 0.03+0.02*i;
      y_rp23_nprot[i] = proton_left_rp23_nprot[i];
      ex_rp23_nprot[i] = 0.01;
      ey_rp23_nprot[i] = proton_left_rp23_nprot_err[i];
   }
   TGraph *gr_rp23_nprot = new TGraphErrors(n,x_rp23_nprot,y_rp23_nprot,ex_rp23_nprot,ey_rp23_nprot);
   gr_rp23_nprot->SetTitle("#sigma x #xi - Proton Left - RP 23");
   gr_rp23_nprot->SetName("gr_rp23_nprot");
   gr_rp23_nprot->Fit("pol1");

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
   gr_left_single->SetName("gr_left_single");
   gr_left_single->Fit("pol1");

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
   gr_rp103->SetName("gr_rp103");
   gr_rp103->Fit("pol1");

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
   gr_rp123->SetName("gr_rp123");
   gr_rp123->Fit("pol1");

   TCanvas *rp123_nprot = new TCanvas("rp123_nprot","#sigma x #xi - Proton Right - RP 123",200,10,700,500);
   Double_t x_rp123_nprot[10], y_rp123_nprot[10], ex_rp123_nprot[10], ey_rp123_nprot[10];
   for (Int_t i = 0;i<n;i++) {
      x_rp123_nprot[i] = 0.03+0.02*i;
      y_rp123_nprot[i] = proton_right_rp123_nprot[i];
      ex_rp123_nprot[i] = 0.01;
      ey_rp123_nprot[i] = proton_right_rp123_nprot_err[i];
   }
   TGraph *gr_rp123_nprot = new TGraphErrors(n,x_rp123_nprot,y_rp123_nprot,ex_rp123_nprot,ey_rp123_nprot);
   gr_rp123_nprot->SetTitle("#sigma x #xi - Proton Right - RP 123");
   gr_rp123_nprot->SetName("gr_rp123_nprot");
   gr_rp123_nprot->Fit("pol1");

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
   gr_right_single->SetName("gr_right_single");
   gr_right_single->Fit("pol1");

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
   gr_left_multi->SetName("gr_left_multi");
   gr_left_multi->Fit("pol1");

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
   gr_right_multi->SetName("gr_right_multi");
   gr_right_multi->Fit("pol1");

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

   TFile* f = new TFile("output_cut.root", "RECREATE");
   PrimVertex_ndof->Write();
   PrimVertex_chi2->Write();
   mumu_mass->Write();
   mumu_pt->Write();
   mumu_y->Write();

   proton_xi_left_rp3->Write();
   proton_xi_left_rp3_eff->Write();
   proton_resolution_left_gen_rp3->Write();
   proton_resolution_left_reco_rp3->Write();
   pair_xi_left_rp3->Write();
   xi_left_reco_rp3->Write();
   g_xi_left_reco_rp3->Write();
   xi_left_reco_rp3_match->Write();
   g_xi_left_reco_rp3_match->Write();
   xi_left_reco_rp3_non_match->Write();
   g_xi_left_reco_rp3_non_match->Write();
   diff_proton_reco_pair_xi_left_rp3->Write();
   ratio_proton_reco_pair_xi_left_rp3->Write();
   gr_rp3->Write();

   proton_xi_left_rp23->Write();
   proton_xi_left_rp23_eff->Write();
   proton_resolution_left_gen_rp23->Write();
   proton_resolution_left_reco_rp23->Write();
   pair_xi_left_rp23->Write();
   xi_left_reco_rp23->Write();
   g_xi_left_reco_rp23->Write();
   xi_left_reco_rp23_match->Write();
   g_xi_left_reco_rp23_match->Write();
   xi_left_reco_rp23_non_match->Write();
   g_xi_left_reco_rp23_non_match->Write();
   diff_proton_reco_pair_xi_left_rp23->Write();
   ratio_proton_reco_pair_xi_left_rp23->Write();
   gr_rp23->Write();

   proton_xi_left_rp23_nprot->Write();
   proton_xi_left_rp23_nprot_eff->Write();
   proton_resolution_left_gen_rp23_nprot->Write();
   proton_resolution_left_reco_rp23_nprot->Write();
   pair_xi_left_rp23_nprot->Write();
   xi_left_reco_rp23_nprot->Write();
   g_xi_left_reco_rp23_nprot->Write();
   xi_left_reco_rp23_nprot_match->Write();
   g_xi_left_reco_rp23_nprot_match->Write();
   xi_left_reco_rp23_nprot_non_match->Write();
   g_xi_left_reco_rp23_nprot_non_match->Write();
   diff_proton_reco_pair_xi_left_rp23_nprot->Write();
   ratio_proton_reco_pair_xi_left_rp23_nprot->Write();
   gr_rp23_nprot->Write();

   proton_xi_left_single->Write();
   proton_xi_left_single_eff->Write();
   proton_resolution_left_gen_single->Write();
   proton_resolution_left_reco_single->Write();
   pair_xi_left_single->Write();
   xi_left_reco_single->Write();
   g_xi_left_reco_single->Write();
   xi_left_reco_single_match->Write();
   g_xi_left_reco_single_match->Write();
   xi_left_reco_single_non_match->Write();
   g_xi_left_reco_single_non_match->Write();
   diff_proton_reco_pair_xi_left_single->Write();
   ratio_proton_reco_pair_xi_left_single->Write();
   gr_left_single->Write();

   proton_xi_right_rp103->Write();
   proton_xi_right_rp103_eff->Write();
   proton_resolution_right_gen_rp103->Write();
   proton_resolution_right_reco_rp103->Write();
   pair_xi_right_rp103->Write();
   xi_right_reco_rp103->Write();
   g_xi_right_reco_rp103->Write();
   xi_right_reco_rp103_match->Write();
   g_xi_right_reco_rp103_match->Write();
   xi_right_reco_rp103_non_match->Write();
   g_xi_right_reco_rp103_non_match->Write();
   diff_proton_reco_pair_xi_right_rp103->Write();
   ratio_proton_reco_pair_xi_right_rp103->Write();
   gr_rp103->Write();

   proton_xi_right_rp123->Write();
   proton_xi_right_rp123_eff->Write();
   proton_resolution_right_gen_rp123->Write();
   proton_resolution_right_reco_rp123->Write();
   pair_xi_right_rp123->Write();
   xi_right_reco_rp123->Write();
   g_xi_right_reco_rp123->Write();
   xi_right_reco_rp123_match->Write();
   g_xi_right_reco_rp123_match->Write();
   xi_right_reco_rp123_non_match->Write();
   g_xi_right_reco_rp123_non_match->Write();
   diff_proton_reco_pair_xi_right_rp123->Write();
   ratio_proton_reco_pair_xi_right_rp123->Write();
   gr_rp123->Write();

   proton_xi_right_rp123_nprot->Write();
   proton_xi_right_rp123_nprot_eff->Write();
   proton_resolution_right_gen_rp123_nprot->Write();
   proton_resolution_right_reco_rp123_nprot->Write();
   pair_xi_right_rp123_nprot->Write();
   xi_right_reco_rp123_nprot->Write();
   g_xi_right_reco_rp123_nprot->Write();
   xi_right_reco_rp123_nprot_match->Write();
   g_xi_right_reco_rp123_nprot_match->Write();
   xi_right_reco_rp123_nprot_non_match->Write();
   g_xi_right_reco_rp123_nprot_non_match->Write();
   diff_proton_reco_pair_xi_right_rp123_nprot->Write();
   ratio_proton_reco_pair_xi_right_rp123_nprot->Write();
   gr_rp123_nprot->Write();

   proton_xi_right_single->Write();
   proton_xi_right_single_eff->Write();
   proton_resolution_right_gen_single->Write();
   proton_resolution_right_reco_single->Write();
   pair_xi_right_single->Write();
   xi_right_reco_single->Write();
   g_xi_right_reco_single->Write();
   xi_right_reco_single_match->Write();
   g_xi_right_reco_single_match->Write();
   xi_right_reco_single_non_match->Write();
   g_xi_right_reco_single_non_match->Write();
   diff_proton_reco_pair_xi_right_single->Write();
   ratio_proton_reco_pair_xi_right_single->Write();
   gr_right_single->Write();

   proton_xi_left_multi->Write();
   proton_xi_left_multi_eff->Write();
   proton_resolution_left_gen_multi->Write();
   proton_resolution_left_reco_multi->Write();
   pair_xi_left_multi->Write();
   xi_left_reco_multi->Write();
   g_xi_left_reco_multi->Write();
   xi_left_reco_multi_match->Write();
   g_xi_left_reco_multi_match->Write();
   xi_left_reco_multi_non_match->Write();
   g_xi_left_reco_multi_non_match->Write();
   diff_proton_reco_pair_xi_left_multi->Write();
   ratio_proton_reco_pair_xi_left_multi->Write();
   gr_left_multi->Write();

   proton_xi_right_multi->Write();
   proton_xi_right_multi_eff->Write();
   proton_resolution_right_gen_multi->Write();
   proton_resolution_right_reco_multi->Write();
   pair_xi_right_multi->Write();
   xi_right_reco_multi->Write();
   g_xi_right_reco_multi->Write();
   xi_right_reco_multi_match->Write();
   g_xi_right_reco_multi_match->Write();
   xi_right_reco_multi_non_match->Write();
   g_xi_right_reco_multi_non_match->Write();
   diff_proton_reco_pair_xi_right_multi->Write();
   ratio_proton_reco_pair_xi_right_multi->Write();
   gr_right_multi->Write();

   xi_pair_resolution_left->Write();
   gr_pair_left->Write();
   xi_pair_resolution_right->Write();
   gr_pair_right->Write();

   f->Close();

   //cout << "oi" <<endl;
}

int run(std::string fileName="input.root") {
   //TFile* f = new TFile(outfileName.c_str(), "RECREATE");
   ntp1 m(fileName);
   //f->Close();
   m.Loop();

   return 0;
}
