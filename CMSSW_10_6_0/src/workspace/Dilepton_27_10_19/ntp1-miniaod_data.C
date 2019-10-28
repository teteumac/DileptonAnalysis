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
	TH1D *pair_xi_left_rp3 = new TH1D("pair_xi_left_rp3", "#xi Pair Left - RP 3", 20, 0, 0.16);
	TH2D *xi_left_reco_rp3 = new TH2D("xi_left_reco_rp3", "#xi Left Correlation - RP 3", 20, 0, 0.16, 20, 0, 0.16); 
	TH1D *diff_proton_reco_pair_xi_left_rp3 = new TH1D("diff_proton_reco_pair_xi_left_rp3", "reco (Proton - Pair) #xi Left - RP 3", 10, -1, 1);
	TH1D *ratio_proton_reco_pair_xi_left_rp3 = new TH1D("ratio_proton_reco_pair_xi_left_rp3", "reco (1 - Proton/Pair) #xi Left - RP 3", 10, -10, 1);

	TH1D *proton_xi_left_rp23 = new TH1D("proton_xi_left_rp23", "#xi Proton Left - RP 23", 20, 0, 0.16);
	TH1D *pair_xi_left_rp23 = new TH1D("pair_xi_left_rp23", "#xi Pair Left - RP 23", 20, 0, 0.16);
	TH2D *xi_left_reco_rp23 = new TH2D("xi_left_reco_rp23", "#xi Left Correlation - RP 23", 20, 0, 0.16, 20, 0, 0.16); 
	TH1D *diff_proton_reco_pair_xi_left_rp23 = new TH1D("diff_proton_reco_pair_xi_left_rp23", "reco (Proton - Pair) #xi Left - RP 23", 10, -1, 1);
	TH1D *ratio_proton_reco_pair_xi_left_rp23 = new TH1D("ratio_proton_reco_pair_xi_left_rp23", "reco (1 - Proton/Pair) #xi Left - RP 23", 10, -10, 1);

	TH1D *proton_xi_left_single = new TH1D("proton_xi_left_single", "#xi Proton Left - Single RP", 20, 0, 0.16);
	TH1D *pair_xi_left_single = new TH1D("pair_xi_left_single", "#xi Pair Left - Single RP", 20, 0, 0.16);
	TH2D *xi_left_reco_single = new TH2D("xi_left_reco_single", "#xi Left Correlation - Single RP", 20, 0, 0.16, 20, 0, 0.16); 	
	TH2D *xi_left_reco_single_2 = new TH2D("xi_left_reco_single_2", "#xi Left Correlation - Single RP", 20, 0, 0.16, 20, 0, 0.16); 	
	TH1D *diff_proton_reco_pair_xi_left_single = new TH1D("diff_proton_reco_pair_xi_left_single", "reco (Proton - Pair) #xi Left - Single", 10, -1, 1);
	TH1D *ratio_proton_reco_pair_xi_left_single = new TH1D("ratio_proton_reco_pair_xi_left_single", "reco (1 - reco Proton/Pair) #xi Left - Single", 10, -10, 1);

	TH1D *proton_xi_right_rp103 = new TH1D("proton_xi_right_rp103", "#xi Proton Right - RP 103", 20, 0, 0.16);
	TH1D *pair_xi_right_rp103 = new TH1D("pair_xi_right_rp103", "#xi Pair Right - RP 103", 20, 0, 0.16);
	TH2D *xi_right_reco_rp103 = new TH2D("xi_right_reco_rp103", "#xi Right Correlation - RP 103", 20, 0, 0.16, 20, 0, 0.16); 
	TH1D *diff_proton_reco_pair_xi_right_rp103 = new TH1D("diff_proton_reco_pair_xi_right_rp103", "reco (Proton - Pair) #xi Right - RP 103", 10, -1, 1);
	TH1D *ratio_proton_reco_pair_xi_right_rp103 = new TH1D("ratio_proton_reco_pair_xi_right_rp103", "reco (1 - Proton/Pair) #xi Right - RP 103", 10, -10, 1);

	TH1D *proton_xi_right_rp123 = new TH1D("proton_xi_right_rp123", "#xi Proton Right - RP 123", 20, 0, 0.16);
	TH1D *pair_xi_right_rp123 = new TH1D("pair_xi_right_rp123", "#xi Pair Right - RP 123", 20, 0, 0.16);
	TH2D *xi_right_reco_rp123 = new TH2D("xi_right_reco_rp123", "#xi Right Correlation - RP 123", 20, 0, 0.16, 20, 0, 0.16); 
	TH1D *diff_proton_reco_pair_xi_right_rp123 = new TH1D("diff_proton_reco_pair_xi_right_rp123", "reco (Proton - Pair) #xi Right - RP 123", 10, -1, 1);
	TH1D *ratio_proton_reco_pair_xi_right_rp123 = new TH1D("ratio_proton_reco_pair_xi_right_rp123", "reco (1 - Proton/Pair) #xi Right - RP 123", 10, -10, 1);

	TH1D *proton_xi_right_single = new TH1D("proton_xi_right_single", "#xi Proton Right - Single RP", 20, 0, 0.16);
	TH1D *pair_xi_right_single = new TH1D("pair_xi_right_single", "#xi Pair Right - Single RP", 20, 0, 0.16);
	TH2D *xi_right_reco_single = new TH2D("xi_right_reco_single", "#xi Right Correlation - Single RP", 20, 0, 0.16, 20, 0, 0.16); 	
	TH2D *xi_right_reco_single_2 = new TH2D("xi_right_reco_single_2", "#xi Right Correlation - Single RP", 20, 0, 0.16, 20, 0, 0.16); 	
	TH1D *diff_proton_reco_pair_xi_right_single = new TH1D("diff_proton_reco_pair_xi_right_single", "reco (Proton - Pair) #xi Right - Single", 10, -1, 1);
	TH1D *ratio_proton_reco_pair_xi_right_single = new TH1D("ratio_proton_reco_pair_xi_right_single", "reco (1 - Proton/Pair) #xi Right - Single", 10, -10, 1);

	TH1D *proton_xi_left_multi = new TH1D("proton_xi_left_multi", "#xi Proton Left - Multi RP", 20, 0, 0.16);
	TH1D *pair_xi_left_multi = new TH1D("pair_xi_left_multi", "#xi Pair Left - Multi RP", 20, 0, 0.16);
	TH2D *xi_left_reco_multi = new TH2D("xi_left_reco_multi", "#xi Left Correlation - Multi RP", 20, 0, 0.16, 20, 0, 0.16); 	
	TH1D *diff_proton_reco_pair_xi_left_multi = new TH1D("diff_proton_reco_pair_xi_left_multi", "reco (Proton - Pair) #xi Left - Multi", 10, -1, 1);
	TH1D *ratio_proton_reco_pair_xi_left_multi = new TH1D("ratio_proton_reco_pair_xi_left_multi", "reco (1 - Proton/Pair) #xi Left - Multi", 10, -10, 1);

	TH1D *proton_xi_right_multi = new TH1D("proton_xi_right_multi", "#xi Proton Right - Multi RP", 20, 0, 0.16);
	TH1D *pair_xi_right_multi = new TH1D("pair_xi_right_multi", "#xi Pair Right - Multi RP", 20, 0, 0.16);
	TH2D *xi_right_reco_multi = new TH2D("xi_right_reco_multi", "#xi Right Correlation - Multi RP", 20, 0, 0.16, 20, 0, 0.16); 	
	TH1D *diff_proton_reco_pair_xi_right_multi = new TH1D("diff_proton_reco_pair_xi_right_multi", "reco (Proton - Pair) #xi Right - Multi", 10, -1, 1);
	TH1D *ratio_proton_reco_pair_xi_right_multi = new TH1D("ratio_proton_reco_pair_xi_right_multi", "reco (1 - Proton/Pair) #xi Right - Multi", 10, -10, 1);

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
										for ( int idx = 0; idx < nRecoProtCand; ++idx ) {
											//cout << idx << " " << ProtCand_rpid[idx] << " " << ProtCand_arm[idx] << " " << ProtCand_xi[idx] << endl;
											if (ProtCand_trackpixshift1[idx] == 0) { 
											if (ProtCand_rpid[idx] == 3) {
												if (ProtCand_ismultirp[idx] == 0) {
													proton_xi_left_rp3->Fill(ProtCand_xi[idx]);
													pair_xi_left_rp3->Fill(xi_pair_left_reco);
													xi_left_reco_rp3->Fill(ProtCand_xi[idx], xi_pair_left_reco); 
													diff_proton_reco_pair_xi_left_rp3->Fill(ProtCand_xi[idx] - xi_pair_left_reco); 
													ratio_proton_reco_pair_xi_left_rp3->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco); 
													//xi_left_wrong->Fill(ProtCand_xi[idx], xi_pair_right); 
												}		
											}
											if (ProtCand_rpid[idx] == 23) {
												if (ProtCand_ismultirp[idx] == 0) {
													proton_xi_left_rp23->Fill(ProtCand_xi[idx]);
													pair_xi_left_rp23->Fill(xi_pair_left_reco);
													xi_left_reco_rp23->Fill(ProtCand_xi[idx], xi_pair_left_reco); 
													diff_proton_reco_pair_xi_left_rp23->Fill(ProtCand_xi[idx] - xi_pair_left_reco); 
													ratio_proton_reco_pair_xi_left_rp23->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco); 
													//xi_left_wrong->Fill(ProtCand_xi[idx], xi_pair_right); 
												}		
											}
											if ((ProtCand_rpid[idx] == 3) || (ProtCand_rpid[idx] == 23)) {
												if (ProtCand_ismultirp[idx] == 0) {
													//cout << idx << "   " << ProtCand_xi[idx] << endl;
													proton_xi_left_single->Fill(ProtCand_xi[idx]);
													pair_xi_left_single->Fill(xi_pair_left_reco);
													xi_left_reco_single->Fill(ProtCand_xi[idx], xi_pair_left_reco); 
													diff_proton_reco_pair_xi_left_single->Fill(ProtCand_xi[idx] - xi_pair_left_reco); 
													ratio_proton_reco_pair_xi_left_single->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco); 
													//xi_left_wrong->Fill(ProtCand_xi[idx], xi_pair_right); 
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
													pair_xi_right_rp103->Fill(xi_pair_right_reco);
													xi_right_reco_rp103->Fill(ProtCand_xi[idx], xi_pair_right_reco);
													diff_proton_reco_pair_xi_right_rp103->Fill(ProtCand_xi[idx] - xi_pair_right_reco); 
													ratio_proton_reco_pair_xi_right_rp103->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco); 
													//xi_right_wrong->Fill(ProtCand_xi[idx], xi_pair_left);
												}		
											}
											if (ProtCand_rpid[idx] == 123) {                           
            	              	   	if (ProtCand_ismultirp[idx] == 0) {
													proton_xi_right_rp123->Fill(ProtCand_xi[idx]);
													pair_xi_right_rp123->Fill(xi_pair_right_reco);
													xi_right_reco_rp123->Fill(ProtCand_xi[idx], xi_pair_right_reco);
													diff_proton_reco_pair_xi_right_rp123->Fill(ProtCand_xi[idx] - xi_pair_right_reco); 
													ratio_proton_reco_pair_xi_right_rp123->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco); 
													//xi_right_wrong->Fill(ProtCand_xi[idx], xi_pair_left);
												}		
											}
											if ((ProtCand_rpid[idx] == 103) || (ProtCand_rpid[idx] == 123)) {                           
            	              	   	if (ProtCand_ismultirp[idx] == 0) {
													proton_xi_right_single->Fill(ProtCand_xi[idx]);
													pair_xi_right_single->Fill(xi_pair_right_reco);
													xi_right_reco_single->Fill(ProtCand_xi[idx], xi_pair_right_reco);
													diff_proton_reco_pair_xi_right_single->Fill(ProtCand_xi[idx] - xi_pair_right_reco); 
													ratio_proton_reco_pair_xi_right_single->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco); 
													//xi_right_wrong->Fill(ProtCand_xi[idx], xi_pair_left);
												}		
											}
			
											if(ProtCand_rpid[idx] == 103 && ProtCand_ismultirp[idx] == 0) single_rp103_xi = ProtCand_xi[idx];

											if(ProtCand_rpid[idx] == 123 && ProtCand_ismultirp[idx] == 0){
 												single_rp123_xi = ProtCand_xi[idx];
 												cont_single_rp123++; 
											}
											}
									
											if (ProtCand_trackpixshift2[idx] == 0) { 
											if (ProtCand_arm[idx] == 0) {
												if (ProtCand_ismultirp[idx] == 1) {
													proton_xi_left_multi->Fill(ProtCand_xi[idx]);
													pair_xi_left_multi->Fill(xi_pair_left_reco);
													xi_left_reco_multi->Fill(ProtCand_xi[idx], xi_pair_left_reco); 
													diff_proton_reco_pair_xi_left_multi->Fill(ProtCand_xi[idx] - xi_pair_left_reco); 
													ratio_proton_reco_pair_xi_left_multi->Fill(1 - ProtCand_xi[idx]/xi_pair_left_reco); 
													//xi_left_wrong->Fill(ProtCand_xi[idx], xi_pair_right); 
												}		
											}
											if (ProtCand_arm[idx] == 1) {                           
            	              	   	if (ProtCand_ismultirp[idx] == 1) {
													proton_xi_right_multi->Fill(ProtCand_xi[idx]);
													pair_xi_right_multi->Fill(xi_pair_right_reco);
													xi_right_reco_multi->Fill(ProtCand_xi[idx], xi_pair_right_reco);
													diff_proton_reco_pair_xi_right_multi->Fill(ProtCand_xi[idx] - xi_pair_right_reco); 
													ratio_proton_reco_pair_xi_right_multi->Fill(1 - ProtCand_xi[idx]/xi_pair_right_reco); 
													//xi_right_wrong->Fill(ProtCand_xi[idx], xi_pair_left);
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
	
	cout << "0cortes: " << zerocortes << endl;
	cout << "1cortes: " << umcortes << endl;
	cout << "2cortes: " << doiscortes << endl;
	cout << "3cortes: " << trescortes << endl;
	cout << "4cortes: " << quatrocortes << endl;
	cout << "5cortes: " << cincocortes << endl;
	cout << "6cortes: " << seiscortes << endl;
	cout << "7cortes: " << setecortes << endl;
	cout << "8cortes: " << oitocortes << endl;

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
	pair_xi_left_rp3->Write();
   xi_left_reco_rp3->Write();
	diff_proton_reco_pair_xi_left_rp3->Write();
	ratio_proton_reco_pair_xi_left_rp3->Write();

	proton_xi_left_rp23->Write();
	pair_xi_left_rp23->Write();
   xi_left_reco_rp23->Write();
	diff_proton_reco_pair_xi_left_rp23->Write();
	ratio_proton_reco_pair_xi_left_rp23->Write();

	proton_xi_left_single->Write();
	pair_xi_left_single->Write();
   xi_left_reco_single->Write();
   xi_left_reco_single_2->Write();
	diff_proton_reco_pair_xi_left_single->Write();
	ratio_proton_reco_pair_xi_left_single->Write();

	proton_xi_right_rp103->Write();
	pair_xi_right_rp103->Write();
   xi_right_reco_rp103->Write();
	diff_proton_reco_pair_xi_right_rp103->Write();
	ratio_proton_reco_pair_xi_right_rp103->Write();

	proton_xi_right_rp123->Write();
	pair_xi_right_rp123->Write();
   xi_right_reco_rp123->Write();
	diff_proton_reco_pair_xi_right_rp123->Write();
	ratio_proton_reco_pair_xi_right_rp123->Write();

	proton_xi_right_single->Write();
	pair_xi_right_single->Write();
   xi_right_reco_single->Write();
   xi_right_reco_single_2->Write();
	diff_proton_reco_pair_xi_right_single->Write();
	ratio_proton_reco_pair_xi_right_single->Write();

	proton_xi_left_multi->Write();
	pair_xi_left_multi->Write();
   xi_left_reco_multi->Write();
	diff_proton_reco_pair_xi_left_multi->Write();
	ratio_proton_reco_pair_xi_left_multi->Write();

	proton_xi_right_multi->Write();
	pair_xi_right_multi->Write();
   xi_right_reco_multi->Write();
	diff_proton_reco_pair_xi_right_multi->Write();
	ratio_proton_reco_pair_xi_right_multi->Write();

	f->Close();

	//cout << "oi" <<endl;
}
	
int run() {
	ntp1 m;
 	m.Loop();

 	return 0;
 	}
