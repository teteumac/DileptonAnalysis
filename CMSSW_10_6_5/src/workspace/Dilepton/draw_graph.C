#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TSystem.h>
#include <TROOT.h>
#include <TH1.h>
#include <TF1.h>
#include <TH2.h>
#include <TMath.h>
#include <TFile.h>
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

int draw_graph( TFile* f, string gr_name, string gr_name_match, string gr_name_non_match, string f_name, string fileName )
{
	TFile *input_graph = new TFile("histos_data/output_data_sigma.root", "READ");
	TFile *input_func = new TFile("histos_MC/pol_function.root", "READ");

   TGraph *gr = (TGraph*)input_graph->Get( gr_name.c_str() );
   TGraph *gr_match = (TGraph*)input_graph->Get( gr_name_match.c_str() );
   TGraph *gr_non_match = (TGraph*)input_graph->Get( gr_name_non_match.c_str() );
	TF1 *func = (TF1*)input_func->Get( f_name.c_str() );
 
   func->SetName( f_name.c_str() );
   double coef_lin = func->GetParameter(0);
   double coef_lin_err = func->GetParError(0);
   double coef_ang = func->GetParameter(1);
   double coef_ang_err = func->GetParError(1);
   //cout << "p0 = " << coef_lin << "+/-" << coef_lin_err << endl;
   //cout << "p1 = " << coef_ang << "+/-" << coef_ang_err << endl;

   TCanvas *canvas1 = new TCanvas;
   gr_match->SetDrawOption("AP");
   gr_match->SetMarkerStyle(22);
   gr_match->SetMarkerColor(4);
   gr_non_match->SetDrawOption("AP");
   gr_non_match->SetMarkerStyle(23);
   gr_non_match->SetMarkerColor(2);
   TMultiGraph *mg = new TMultiGraph();
   mg->SetTitle( gr_name.c_str() );
   mg->GetXaxis()->SetTitle("#xi(RP)");
   mg->GetXaxis()->SetLimits(.02, .16);
   mg->GetYaxis()->SetTitle("#xi(#mu^{+}#mu^{-})");
   mg->SetMinimum(.02);
   mg->SetMaximum(.16);
   mg->Add(gr_match, "AP");
   mg->Add(gr_non_match, "AP");
   mg->Draw("AP");
   canvas1->SaveAs( fileName.c_str() );
   canvas1->cd();
   canvas1->Close();

	//TFile* f = new TFile("pol_graph.root", "RECREATE");

	//f->Close();

	//cout << "oi" <<endl;

   return 0;
}
	
int run() {
	TFile* f = new TFile("comp_graph.root", "RECREATE");

   int rp3 = draw_graph( f , "g_xi_left_reco_rp3", "g_xi_left_reco_rp3_match", "g_xi_left_reco_rp3_non_match", "f_rp3", "histos_data/xi_corr_rp3.png" );
   int rp23 = draw_graph( f , "g_xi_left_reco_rp23", "g_xi_left_reco_rp23_match", "g_xi_left_reco_rp23_non_match", "f_rp23", "histos_data/xi_corr_rp23.png" );
   int l_s = draw_graph( f , "g_xi_left_reco_single", "g_xi_left_reco_single_match", "g_xi_left_reco_single_non_match", "f_left_single", "histos_data/xi_corr_left_single.png" );
   int l_s_2 = draw_graph( f , "g_xi_left_reco_single_2", "g_xi_left_reco_single_match_2", "g_xi_left_reco_single_non_match_2", "f_left_single_2", "histos_data/xi_corr_left_single_2.png" );
   int rp103 = draw_graph( f , "g_xi_right_reco_rp103", "g_xi_right_reco_rp103_match", "g_xi_right_reco_rp103_non_match", "f_rp103", "histos_data/xi_corr_rp103.png" );
   int rp123 = draw_graph( f , "g_xi_right_reco_rp123", "g_xi_right_reco_rp123_match", "g_xi_right_reco_rp123_non_match", "f_rp123", "histos_data/xi_corr_rp123.png" );
   int r_s = draw_graph( f , "g_xi_right_reco_single", "g_xi_right_reco_single_match", "g_xi_right_reco_single_non_match", "f_right_single", "histos_data/xi_corr_right_single.png" );
   int r_s_2 = draw_graph( f , "g_xi_right_reco_single_2", "g_xi_right_reco_single_match_2", "g_xi_right_reco_single_non_match_2", "f_right_single_2", "histos_data/xi_corr_right_single_2.png" );
   int l_m = draw_graph( f , "g_xi_left_reco_multi", "g_xi_left_reco_multi_match", "g_xi_left_reco_multi_non_match", "f_left_multi", "histos_data/xi_corr_left_multi.png" );
   int r_m = draw_graph( f , "g_xi_right_reco_multi", "g_xi_right_reco_multi_match", "g_xi_right_reco_multi_non_match", "f_right_multi", "histos_data/xi_corr_right_multi.png" );

	f->Close();

 	return rp3, rp23, l_s,  l_s_2, rp103, rp123, r_s, r_s_2, l_m, r_m;
 	}
