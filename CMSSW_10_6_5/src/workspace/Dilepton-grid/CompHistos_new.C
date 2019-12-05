#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TSystem.h>
#include <TROOT.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TSpline.h>
#include <math.h>
#include <TH1F.h>
#include <THStack.h>

#include <iostream>
#include <vector>
#include <set>
using namespace std;

int CompHistos_new()
{
   gStyle->SetOptStat(0);

   char* hist[] = {"proton_xi_left_rp23","proton_xi_left_rp23_nprot","proton_xi_right_rp123","proton_xi_right_rp123_nprot","proton_xi_left_multi","proton_xi_right_multi","diff_proton_reco_pair_xi_left_rp23","diff_proton_reco_pair_xi_left_rp23_nprot","diff_proton_reco_pair_xi_right_rp123","diff_proton_reco_pair_xi_right_rp123_nprot","diff_proton_reco_pair_xi_left_multi","diff_proton_reco_pair_xi_right_multi","ratio_proton_reco_pair_xi_left_rp23","ratio_proton_reco_pair_xi_left_rp23_nprot","ratio_proton_reco_pair_xi_right_rp123","ratio_proton_reco_pair_xi_right_rp123_nprot","ratio_proton_reco_pair_xi_left_multi","ratio_proton_reco_pair_xi_right_multi"};
   char*  hist_match[]= {"proton_xi_left_rp23_match","proton_xi_left_rp23_nprot_match","proton_xi_right_rp123_match","proton_xi_right_rp123_nprot_match","proton_xi_left_multi_match","proton_xi_right_multi_match","diff_proton_reco_pair_xi_left_rp23_match","diff_proton_reco_pair_xi_left_rp23_nprot_match","diff_proton_reco_pair_xi_right_rp123_match","diff_proton_reco_pair_xi_right_rp123_nprot_match","diff_proton_reco_pair_xi_left_multi_match","diff_proton_reco_pair_xi_right_multi_match","ratio_proton_reco_pair_xi_left_rp23_match","ratio_proton_reco_pair_xi_left_rp23_nprot_match","ratio_proton_reco_pair_xi_right_rp123_match","ratio_proton_reco_pair_xi_right_rp123_nprot_match","ratio_proton_reco_pair_xi_left_multi_match","ratio_proton_reco_pair_xi_right_multi_match"};
   char*  hist_bkg[] = {"xi_left_reco_rp3_match","xi_left_reco_rp23_match","xi_right_reco_rp103_match","xi_right_reco_rp123_match","xi_left_reco_multi_match","xi_right_reco_multi_match"};

   //setTDRStyle();

   size_t Nhist = sizeof(hist)/sizeof(hist[0]);		
   size_t Nbkg = sizeof(hist_bkg)/sizeof(hist_bkg[0]);		

   TFile *f_elastic_x100 = new TFile("histos_MC/output_elastic_xangle100.root", "READ");
   TFile *f_elastic_x110 = new TFile("histos_MC/output_elastic_xangle110.root", "READ");
   TFile *f_elastic_x120 = new TFile("histos_MC/output_elastic_xangle120.root", "READ");
   TFile *f_elastic_x130 = new TFile("histos_MC/output_elastic_xangle130.root", "READ");
   TFile *f_elastic_x140 = new TFile("histos_MC/output_elastic_xangle140.root", "READ");
   TFile *f_elastic_x150 = new TFile("histos_MC/output_elastic_xangle150.root", "READ");
   TFile *f_inel_el_x100 = new TFile("histos_MC/output_inel-el_xangle100.root", "READ");
   TFile *f_inel_el_x110 = new TFile("histos_MC/output_inel-el_xangle110.root", "READ");
   TFile *f_inel_el_x120 = new TFile("histos_MC/output_inel-el_xangle120.root", "READ");
   TFile *f_inel_el_x130 = new TFile("histos_MC/output_inel-el_xangle130.root", "READ");
   TFile *f_inel_el_x140 = new TFile("histos_MC/output_inel-el_xangle140.root", "READ");
   TFile *f_inel_el_x150 = new TFile("histos_MC/output_inel-el_xangle150.root", "READ");
   TFile *f_dy = new TFile("histos_MC/output_dy_sigma_EG.root", "READ");
   TFile *f_dy_resample = new TFile("histos_MC/output_dy_resample_sigma_EG.root", "READ");
   TFile *f_data = new TFile("histos_data/output_data_sigma_limitRun.root", "READ");

   // Obtained from data separation on crossing angles
   double xangle100 = 160080.00/51828878.;
   double xangle110 = 1324607.0/51828878.;
   double xangle120 = 12533577./51828878.;
   double xangle130 = 16316053./51828878.;
   double xangle140 = 9414932.0/51828878.;
   double xangle150 = 12079629./51828878.;

   double n_events_h_elastic = 200000;
   double n_events_h_inel_el = 200000;
   double n_events_h_dy = 48675378;
   double n_events_pileup = 18964805;
   double number_of_samples = 100; //Used on the resampled DY  
   double total_lumi = 37.498268; //Used on the total luminosity data
   double limit_lumi = 18.516268; //Used on the limited luminosity data
   double event_selection = 18964806./23701056; //Used on the pile-up protons mixing
   double rap_gap_surv_elastic = 0.89; 
   double rap_gap_surv_inel_el = 0.76; 
   double rap_gap_surv_inelastic = 0.13; 

   double scale_factor_elastic_x100 = xangle100*limit_lumi*rap_gap_surv_elastic*0.017254036*1000 / n_events_h_elastic ; //
   double scale_factor_elastic_x110 = xangle110*limit_lumi*rap_gap_surv_elastic*0.017254036*1000 / n_events_h_elastic ; //
   double scale_factor_elastic_x120 = xangle120*limit_lumi*rap_gap_surv_elastic*0.017254036*1000 / n_events_h_elastic ; //
   double scale_factor_elastic_x130 = xangle130*limit_lumi*rap_gap_surv_elastic*0.017254036*1000 / n_events_h_elastic ; //
   double scale_factor_elastic_x140 = xangle140*limit_lumi*rap_gap_surv_elastic*0.017254036*1000 / n_events_h_elastic ; //
   double scale_factor_elastic_x150 = xangle150*limit_lumi*rap_gap_surv_elastic*0.017254036*1000 / n_events_h_elastic ; //
   double scale_factor_inel_el_x100 = xangle100*limit_lumi*rap_gap_surv_inel_el*0.025643100*1000 / n_events_h_inel_el ; //
   double scale_factor_inel_el_x110 = xangle110*limit_lumi*rap_gap_surv_inel_el*0.025643100*1000 / n_events_h_inel_el ; //
   double scale_factor_inel_el_x120 = xangle120*limit_lumi*rap_gap_surv_inel_el*0.025643100*1000 / n_events_h_inel_el ; //
   double scale_factor_inel_el_x130 = xangle130*limit_lumi*rap_gap_surv_inel_el*0.025643100*1000 / n_events_h_inel_el ; //
   double scale_factor_inel_el_x140 = xangle140*limit_lumi*rap_gap_surv_inel_el*0.025643100*1000 / n_events_h_inel_el ; //
   double scale_factor_inel_el_x150 = xangle150*limit_lumi*rap_gap_surv_inel_el*0.025643100*1000 / n_events_h_inel_el ; //
   double scale_factor_dy = limit_lumi*5334000 / n_events_h_dy; 
   double scale_factor_dy_resample = limit_lumi*5334000 / ( n_events_h_dy*number_of_samples ) ; 
   double scale_factor_dy_prot_sel = event_selection*limit_lumi*5334000 / n_events_h_dy; 
   double scale_factor_dy_resample_prot_sel = event_selection*limit_lumi*5334000 / ( n_events_h_dy*number_of_samples ) ; 

   for (int j = 0; j < Nbkg; j++) {

      TH1 *h_est_bkg = 0; f_dy_resample->GetObject(hist_bkg[j], h_est_bkg);

      double int_err[10];
      double int_err_left_rp3, int_err_left_rp23, int_err_right_rp103, int_err_right_rp123, int_err_left_multi, int_err_right_multi;
      int_err[0] =  int_err_left_rp3; int_err[1] = int_err_left_rp23; int_err[2] = int_err_right_rp103; int_err[3] = int_err_right_rp123; int_err[4] = int_err_left_multi; int_err[5] = int_err_right_multi;

      h_est_bkg->Scale(scale_factor_dy_resample_prot_sel); 
      cout << "estimativa bkg: " << h_est_bkg->IntegralAndError(0, (h_est_bkg->GetNbinsX() + 1), int_err[j], "") << " +/- " << int_err[j] << endl;

   }
   for (int i = 0; i < Nhist; i++) {

      TH1 *h_elastic_x100 = 0; f_elastic_x100->GetObject(hist[i], h_elastic_x100);
      TH1 *h_elastic_x110 = 0; f_elastic_x110->GetObject(hist[i], h_elastic_x110);
      TH1 *h_elastic_x120 = 0; f_elastic_x120->GetObject(hist[i], h_elastic_x120);
      TH1 *h_elastic_x130 = 0; f_elastic_x130->GetObject(hist[i], h_elastic_x130);
      TH1 *h_elastic_x140 = 0; f_elastic_x140->GetObject(hist[i], h_elastic_x140);
      TH1 *h_elastic_x150 = 0; f_elastic_x150->GetObject(hist[i], h_elastic_x150);
      TH1 *h_inel_el_x100 = 0; f_inel_el_x100->GetObject(hist[i], h_inel_el_x100);
      TH1 *h_inel_el_x110 = 0; f_inel_el_x110->GetObject(hist[i], h_inel_el_x110);
      TH1 *h_inel_el_x120 = 0; f_inel_el_x120->GetObject(hist[i], h_inel_el_x120);
      TH1 *h_inel_el_x130 = 0; f_inel_el_x130->GetObject(hist[i], h_inel_el_x130);
      TH1 *h_inel_el_x140 = 0; f_inel_el_x140->GetObject(hist[i], h_inel_el_x140);
      TH1 *h_inel_el_x150 = 0; f_inel_el_x150->GetObject(hist[i], h_inel_el_x150);
      TH1 *h_dy = 0; f_dy->GetObject(hist[i], h_dy);
      TH1 *h_dy_resample = 0; f_dy_resample->GetObject(hist[i], h_dy_resample);
      TH1 *h_data = 0; f_data->GetObject(hist[i], h_data);

      TH1 *h_match_elastic_x100 = 0; f_elastic_x100->GetObject(hist_match[i], h_match_elastic_x100);
      TH1 *h_match_elastic_x110 = 0; f_elastic_x110->GetObject(hist_match[i], h_match_elastic_x110);
      TH1 *h_match_elastic_x120 = 0; f_elastic_x120->GetObject(hist_match[i], h_match_elastic_x120);
      TH1 *h_match_elastic_x130 = 0; f_elastic_x130->GetObject(hist_match[i], h_match_elastic_x130);
      TH1 *h_match_elastic_x140 = 0; f_elastic_x140->GetObject(hist_match[i], h_match_elastic_x140);
      TH1 *h_match_elastic_x150 = 0; f_elastic_x150->GetObject(hist_match[i], h_match_elastic_x150);
      TH1 *h_match_inel_el_x100 = 0; f_inel_el_x100->GetObject(hist_match[i], h_match_inel_el_x100);
      TH1 *h_match_inel_el_x110 = 0; f_inel_el_x110->GetObject(hist_match[i], h_match_inel_el_x110);
      TH1 *h_match_inel_el_x120 = 0; f_inel_el_x120->GetObject(hist_match[i], h_match_inel_el_x120);
      TH1 *h_match_inel_el_x130 = 0; f_inel_el_x130->GetObject(hist_match[i], h_match_inel_el_x130);
      TH1 *h_match_inel_el_x140 = 0; f_inel_el_x140->GetObject(hist_match[i], h_match_inel_el_x140);
      TH1 *h_match_inel_el_x150 = 0; f_inel_el_x150->GetObject(hist_match[i], h_match_inel_el_x150);
      TH1 *h_match_dy = 0; f_dy->GetObject(hist_match[i], h_match_dy);
      TH1 *h_match_dy_resample = 0; f_dy_resample->GetObject(hist_match[i], h_match_dy_resample);
      TH1 *h_match_data = 0; f_data->GetObject(hist_match[i], h_match_data);

      h_elastic_x100->SetLineColor(kCyan);
      h_elastic_x110->SetLineColor(kBlue);
      h_elastic_x120->SetLineColor(kBlue+3);
      h_elastic_x130->SetLineColor(kPink-9);
      h_elastic_x140->SetLineColor(kMagenta+1);
      h_elastic_x150->SetLineColor(kViolet-3);
      h_inel_el_x100->SetLineColor(kYellow);
      h_inel_el_x110->SetLineColor(kOrange);
      h_inel_el_x120->SetLineColor(kGreen);
      h_inel_el_x130->SetLineColor(kSpring-1);
      h_inel_el_x140->SetLineColor(kGreen+2);
      h_inel_el_x150->SetLineColor(kTeal-1);
      h_dy->SetLineColor(kRed);
      h_dy_resample->SetLineColor(kRed);
      h_elastic_x100->SetFillColor(kCyan);
      h_elastic_x110->SetFillColor(kBlue);
      h_elastic_x120->SetFillColor(kBlue+3);
      h_elastic_x130->SetFillColor(kPink-9);
      h_elastic_x140->SetFillColor(kMagenta+1);
      h_elastic_x150->SetFillColor(kViolet-3);
      h_inel_el_x100->SetFillColor(kYellow);
      h_inel_el_x110->SetFillColor(kOrange);
      h_inel_el_x120->SetFillColor(kGreen);
      h_inel_el_x130->SetFillColor(kSpring-1);
      h_inel_el_x140->SetFillColor(kGreen+2);
      h_inel_el_x150->SetFillColor(kTeal-1);
      h_dy->SetFillColor(kRed);
      h_dy_resample->SetFillColor(kRed);
      h_data->SetMarkerStyle(8);
      h_data->Sumw2();

      h_match_elastic_x100->SetLineColor(kCyan);
      h_match_elastic_x110->SetLineColor(kBlue);
      h_match_elastic_x120->SetLineColor(kBlue+3);
      h_match_elastic_x130->SetLineColor(kPink-9);
      h_match_elastic_x140->SetLineColor(kMagenta+1);
      h_match_elastic_x150->SetLineColor(kViolet-3);
      h_match_inel_el_x100->SetLineColor(kYellow);
      h_match_inel_el_x110->SetLineColor(kOrange);
      h_match_inel_el_x120->SetLineColor(kGreen);
      h_match_inel_el_x130->SetLineColor(kSpring-1);
      h_match_inel_el_x140->SetLineColor(kGreen+2);
      h_match_inel_el_x150->SetLineColor(kTeal-1);
      h_match_dy->SetLineColor(kRed);
      h_match_dy_resample->SetLineColor(kRed);
      h_match_elastic_x100->SetFillColor(kCyan);
      h_match_elastic_x110->SetFillColor(kBlue);
      h_match_elastic_x120->SetFillColor(kBlue+3);
      h_match_elastic_x130->SetFillColor(kPink-9);
      h_match_elastic_x140->SetFillColor(kMagenta+1);
      h_match_elastic_x150->SetFillColor(kViolet-3);
      h_match_inel_el_x100->SetFillColor(kYellow);
      h_match_inel_el_x110->SetFillColor(kOrange);
      h_match_inel_el_x120->SetFillColor(kGreen);
      h_match_inel_el_x130->SetFillColor(kSpring-1);
      h_match_inel_el_x140->SetFillColor(kGreen+2);
      h_match_inel_el_x150->SetFillColor(kTeal-1);
      h_match_dy->SetFillColor(kRed);
      h_match_dy_resample->SetFillColor(kRed);
      h_match_data->SetMarkerStyle(8);
      h_match_data->Sumw2();

      h_elastic_x100->Scale(scale_factor_elastic_x100);
      h_elastic_x110->Scale(scale_factor_elastic_x110);
      h_elastic_x120->Scale(scale_factor_elastic_x120);
      h_elastic_x130->Scale(scale_factor_elastic_x130);
      h_elastic_x140->Scale(scale_factor_elastic_x140);
      h_elastic_x150->Scale(scale_factor_elastic_x150);
      h_inel_el_x100->Scale(scale_factor_inel_el_x100);
      h_inel_el_x110->Scale(scale_factor_inel_el_x110);
      h_inel_el_x120->Scale(scale_factor_inel_el_x120);
      h_inel_el_x130->Scale(scale_factor_inel_el_x130);
      h_inel_el_x140->Scale(scale_factor_inel_el_x140);
      h_inel_el_x150->Scale(scale_factor_inel_el_x150);
      h_dy->Scale(scale_factor_dy_prot_sel);
      h_dy_resample->Scale(scale_factor_dy_resample_prot_sel);

      h_match_elastic_x100->Scale(scale_factor_elastic_x100, "width");
      h_match_elastic_x110->Scale(scale_factor_elastic_x110, "width");
      h_match_elastic_x120->Scale(scale_factor_elastic_x120, "width");
      h_match_elastic_x130->Scale(scale_factor_elastic_x130, "width");
      h_match_elastic_x140->Scale(scale_factor_elastic_x140, "width");
      h_match_elastic_x150->Scale(scale_factor_elastic_x150, "width");
      h_match_inel_el_x100->Scale(scale_factor_inel_el_x100, "width");
      h_match_inel_el_x110->Scale(scale_factor_inel_el_x110, "width");
      h_match_inel_el_x120->Scale(scale_factor_inel_el_x120, "width");
      h_match_inel_el_x130->Scale(scale_factor_inel_el_x130, "width");
      h_match_inel_el_x140->Scale(scale_factor_inel_el_x140, "width");
      h_match_inel_el_x150->Scale(scale_factor_inel_el_x150, "width");
      h_match_dy->Scale(scale_factor_dy_prot_sel, "width");
      h_match_dy_resample->Scale(scale_factor_dy_resample_prot_sel, "width");
      h_match_data->Scale(1, "width");
      
      THStack hs("hs","Proton #xi;#xi(RP);Events");
      hs.Add(h_elastic_x100); 
      hs.Add(h_elastic_x110); 
      hs.Add(h_elastic_x120); 
      hs.Add(h_elastic_x130); 
      hs.Add(h_elastic_x140); 
      hs.Add(h_elastic_x150); 
      hs.Add(h_inel_el_x100); 
      hs.Add(h_inel_el_x110); 
      hs.Add(h_inel_el_x120); 
      hs.Add(h_inel_el_x130); 
      hs.Add(h_inel_el_x140); 
      hs.Add(h_inel_el_x150); 
      hs.Add(h_dy); 

      THStack hs_match("hs_match","Proton #xi;#xi(RP);dN/d#xi");
      hs_match.Add(h_match_elastic_x100); 
      hs_match.Add(h_match_elastic_x110); 
      hs_match.Add(h_match_elastic_x120); 
      hs_match.Add(h_match_elastic_x130); 
      hs_match.Add(h_match_elastic_x140); 
      hs_match.Add(h_match_elastic_x150); 
      hs_match.Add(h_match_inel_el_x100); 
      hs_match.Add(h_match_inel_el_x110); 
      hs_match.Add(h_match_inel_el_x120); 
      hs_match.Add(h_match_inel_el_x130); 
      hs_match.Add(h_match_inel_el_x140); 
      hs_match.Add(h_match_inel_el_x150); 
      hs_match.Add(h_match_dy); 

      TH1F *h_new = (TH1F*)h_elastic_x100->Clone("h_new");
      h_new->Add(h_elastic_x110); 
      h_new->Add(h_elastic_x120); 
      h_new->Add(h_elastic_x130); 
      h_new->Add(h_elastic_x140); 
      h_new->Add(h_elastic_x150); 
      h_new->Add(h_inel_el_x100); 
      h_new->Add(h_inel_el_x110); 
      h_new->Add(h_inel_el_x120); 
      h_new->Add(h_inel_el_x130); 
      h_new->Add(h_inel_el_x140); 
      h_new->Add(h_inel_el_x150); 
      h_new->Add(h_dy); 

      h_new->Sumw2();
      h_new->SetFillColor(1);
      h_new->SetFillStyle(3004);
      h_new->SetMarkerStyle(6);
      h_new->SetMarkerSize(0);
      h_new->SetLineWidth(0);

      TH1F *h_match_new = (TH1F*)h_match_elastic_x100->Clone("h_match_new");
      h_match_new->Add(h_match_elastic_x110); 
      h_match_new->Add(h_match_elastic_x120); 
      h_match_new->Add(h_match_elastic_x130); 
      h_match_new->Add(h_match_elastic_x140); 
      h_match_new->Add(h_match_elastic_x150); 
      h_match_new->Add(h_match_inel_el_x100); 
      h_match_new->Add(h_match_inel_el_x110); 
      h_match_new->Add(h_match_inel_el_x120); 
      h_match_new->Add(h_match_inel_el_x130); 
      h_match_new->Add(h_match_inel_el_x140); 
      h_match_new->Add(h_match_inel_el_x150); 
      h_match_new->Add(h_match_dy); 

      h_match_new->Sumw2();
      h_match_new->SetFillColor(1);
      h_match_new->SetFillStyle(3004);
      h_match_new->SetMarkerStyle(6);
      h_match_new->SetMarkerSize(0);
      h_match_new->SetLineWidth(0);

      THStack hs_resample("hs_resample","Proton #xi - Resample;#xi(RP);Events");
      hs_resample.Add(h_elastic_x100); 
      hs_resample.Add(h_elastic_x110); 
      hs_resample.Add(h_elastic_x120); 
      hs_resample.Add(h_elastic_x130); 
      hs_resample.Add(h_elastic_x140); 
      hs_resample.Add(h_elastic_x150); 
      hs_resample.Add(h_inel_el_x100); 
      hs_resample.Add(h_inel_el_x110); 
      hs_resample.Add(h_inel_el_x120); 
      hs_resample.Add(h_inel_el_x130); 
      hs_resample.Add(h_inel_el_x140); 
      hs_resample.Add(h_inel_el_x150); 
      hs_resample.Add(h_dy_resample); 

      THStack hs_match_resample("hs_match_resample","Proton #xi - Resample;#xi(RP);dN/d#xi");
      hs_match_resample.Add(h_match_elastic_x100); 
      hs_match_resample.Add(h_match_elastic_x110); 
      hs_match_resample.Add(h_match_elastic_x120); 
      hs_match_resample.Add(h_match_elastic_x130); 
      hs_match_resample.Add(h_match_elastic_x140); 
      hs_match_resample.Add(h_match_elastic_x150); 
      hs_match_resample.Add(h_match_inel_el_x100); 
      hs_match_resample.Add(h_match_inel_el_x110); 
      hs_match_resample.Add(h_match_inel_el_x120); 
      hs_match_resample.Add(h_match_inel_el_x130); 
      hs_match_resample.Add(h_match_inel_el_x140); 
      hs_match_resample.Add(h_match_inel_el_x150); 
      hs_match_resample.Add(h_match_dy_resample); 

      TH1F *h_new_resample = (TH1F*)h_elastic_x100->Clone("h_new_resample");
      h_new_resample->Add(h_elastic_x110); 
      h_new_resample->Add(h_elastic_x120); 
      h_new_resample->Add(h_elastic_x130); 
      h_new_resample->Add(h_elastic_x140); 
      h_new_resample->Add(h_elastic_x150); 
      h_new_resample->Add(h_inel_el_x100); 
      h_new_resample->Add(h_inel_el_x110); 
      h_new_resample->Add(h_inel_el_x120); 
      h_new_resample->Add(h_inel_el_x130); 
      h_new_resample->Add(h_inel_el_x140); 
      h_new_resample->Add(h_inel_el_x150); 
      h_new_resample->Add(h_dy_resample); 

      h_new_resample->Sumw2();
      h_new_resample->SetFillColor(1);
      h_new_resample->SetFillStyle(3004);
      h_new_resample->SetMarkerStyle(6);
      h_new_resample->SetMarkerSize(0);
      h_new_resample->SetLineWidth(0);

      TH1F *h_match_new_resample = (TH1F*)h_match_elastic_x100->Clone("h_match_new_resample");
      h_match_new_resample->Add(h_match_elastic_x110); 
      h_match_new_resample->Add(h_match_elastic_x120); 
      h_match_new_resample->Add(h_match_elastic_x130); 
      h_match_new_resample->Add(h_match_elastic_x140); 
      h_match_new_resample->Add(h_match_elastic_x150); 
      h_match_new_resample->Add(h_match_inel_el_x100); 
      h_match_new_resample->Add(h_match_inel_el_x110); 
      h_match_new_resample->Add(h_match_inel_el_x120); 
      h_match_new_resample->Add(h_match_inel_el_x130); 
      h_match_new_resample->Add(h_match_inel_el_x140); 
      h_match_new_resample->Add(h_match_inel_el_x150); 
      h_match_new_resample->Add(h_match_dy_resample); 

      h_match_new_resample->Sumw2();
      h_match_new_resample->SetFillColor(1);
      h_match_new_resample->SetFillStyle(3004);
      h_match_new_resample->SetMarkerStyle(6);
      h_match_new_resample->SetMarkerSize(0);
      h_match_new_resample->SetLineWidth(0);
  
      double max_hs = 0.0;
      double max_hs_match = 0.0;
      double max_hs_resample = 0.0;
      double max_hs_match_resample = 0.0;
      double max_data = 0.0;
      double max_match_data = 0.0;

      if(hs.GetMaximum() > h_data->GetMaximum()) {
         max_hs = hs.GetMaximum();
      }
      else {
         max_hs = h_data->GetMaximum();
      }
      if(hs_match.GetMaximum() > h_match_data->GetMaximum()) {
         max_hs_match = hs_match.GetMaximum();
      }
      else {
         max_hs_match = h_match_data->GetMaximum();
      }
      if(hs_resample.GetMaximum() > h_data->GetMaximum()) {
         max_hs_resample = hs_resample.GetMaximum();
      }
      else {
         max_hs_resample = h_data->GetMaximum();
      }
      if(hs_match_resample.GetMaximum() > h_match_data->GetMaximum()) {
         max_hs_match_resample = hs_match_resample.GetMaximum();
      }
      else {
         max_hs_match_resample = h_match_data->GetMaximum();
      }
      
      double step_hs =0.25*max_hs;
      double step_hs_match =0.25*max_hs_match;
      double step_hs_resample =0.25*max_hs_resample;
      double step_hs_match_resample =0.25*max_hs_match_resample;

      TCanvas *c = new TCanvas("c","",0,0,1200,1000);
      hs.SetMaximum(max_hs+step_hs);
      h_data->SetMaximum(max_hs+step_hs);
      hs.Draw("HIST");
      h_data->Draw("SAME");
      h_new->Draw("E2 SAME");
      auto l = new TLegend(0.9,0.9,0.7,0.7);
      l->SetHeader("Work in progress","C"); // option "C" allows to center the header
      l->AddEntry(h_data,"Dados","lep");
      l->AddEntry((TObject*)0, "", "");
      l->AddEntry((TObject*)0, "Monte Carlo", "");
      l->AddEntry((TObject*)0, "", "");
      l->AddEntry(h_elastic_x100,"Exclusivo","f");
      l->AddEntry(h_elastic_x110,"Exclusivo","f");
      l->AddEntry(h_elastic_x120,"Exclusivo","f");
      l->AddEntry(h_elastic_x130,"Exclusivo","f");
      l->AddEntry(h_elastic_x140,"Exclusivo","f");
      l->AddEntry(h_elastic_x150,"Exclusivo","f");
      l->AddEntry(h_inel_el_x100,"Semi-exclusivo","f");
      l->AddEntry(h_inel_el_x110,"Semi-exclusivo","f");
      l->AddEntry(h_inel_el_x120,"Semi-exclusivo","f");
      l->AddEntry(h_inel_el_x130,"Semi-exclusivo","f");
      l->AddEntry(h_inel_el_x140,"Semi-exclusivo","f");
      l->AddEntry(h_inel_el_x150,"Semi-exclusivo","f");
      l->AddEntry(h_dy,"Drell-Yan","f");
      l->AddEntry(h_new,"Statistic Uncertainties","f");
      l->Draw();
      char* name = Form("comp_new/%s.png", hist[i]);
      c->SaveAs(name);
      c->cd();
      c->Close();

      TCanvas *c_match = new TCanvas("c_match","",0,0,1200,1000);
      hs_match.SetMaximum(max_hs_match+step_hs_match);
      h_match_data->SetMaximum(max_hs_match+step_hs_match);
      hs_match.Draw("HIST");
      h_match_data->Draw("SAME");
      h_match_new->Draw("E2 SAME");
      auto l_match = new TLegend(0.9,0.9,0.7,0.7);
      l_match->SetHeader("Work in progress","C"); // option "C" allows to center the header
      l_match->AddEntry(h_match_data,"Dados","lep");
      l_match->AddEntry((TObject*)0, "", "");
      l_match->AddEntry((TObject*)0, "Monte Carlo", "");
      l_match->AddEntry((TObject*)0, "", "");
      l_match->AddEntry(h_match_elastic_x100,"Exclusivo","f");
      l_match->AddEntry(h_match_elastic_x110,"Exclusivo","f");
      l_match->AddEntry(h_match_elastic_x120,"Exclusivo","f");
      l_match->AddEntry(h_match_elastic_x130,"Exclusivo","f");
      l_match->AddEntry(h_match_elastic_x140,"Exclusivo","f");
      l_match->AddEntry(h_match_elastic_x150,"Exclusivo","f");
      l_match->AddEntry(h_match_inel_el_x100,"Semi-exclusivo","f");
      l_match->AddEntry(h_match_inel_el_x110,"Semi-exclusivo","f");
      l_match->AddEntry(h_match_inel_el_x120,"Semi-exclusivo","f");
      l_match->AddEntry(h_match_inel_el_x130,"Semi-exclusivo","f");
      l_match->AddEntry(h_match_inel_el_x140,"Semi-exclusivo","f");
      l_match->AddEntry(h_match_inel_el_x150,"Semi-exclusivo","f");
      l_match->AddEntry(h_match_dy,"Drell-Yan","f");
      l_match->AddEntry(h_match_new,"Statistic Uncertainties","f");
      l_match->Draw();
      char* name_match = Form("comp_new/%s.png", hist_match[i]);
      c_match->SaveAs(name_match);
      c_match->cd();
      c_match->Close();

      TCanvas *c_resample = new TCanvas("c_resample","",0,0,1200,1000);
      hs_resample.SetMaximum(max_hs_resample+step_hs_resample);
      h_data->SetMaximum(max_hs_resample+step_hs_resample);
      hs_resample.Draw("HIST");
      h_data->Draw("SAME");
      h_new_resample->Draw("E2 SAME");
      auto l_resample = new TLegend(0.9,0.9,0.7,0.7);
      l_resample->SetHeader("Work in progress","C"); // option "C" allows to center the header
      l_resample->AddEntry(h_data,"Dados","lep");
      l_resample->AddEntry((TObject*)0, "", "");
      l_resample->AddEntry((TObject*)0, "Monte Carlo", "");
      l_resample->AddEntry((TObject*)0, "", "");
      l_resample->AddEntry(h_elastic_x100,"Exclusivo","f");
      l_resample->AddEntry(h_elastic_x110,"Exclusivo","f");
      l_resample->AddEntry(h_elastic_x120,"Exclusivo","f");
      l_resample->AddEntry(h_elastic_x130,"Exclusivo","f");
      l_resample->AddEntry(h_elastic_x140,"Exclusivo","f");
      l_resample->AddEntry(h_elastic_x150,"Exclusivo","f");
      l_resample->AddEntry(h_inel_el_x100,"Semi-exclusivo","f");
      l_resample->AddEntry(h_inel_el_x110,"Semi-exclusivo","f");
      l_resample->AddEntry(h_inel_el_x120,"Semi-exclusivo","f");
      l_resample->AddEntry(h_inel_el_x130,"Semi-exclusivo","f");
      l_resample->AddEntry(h_inel_el_x140,"Semi-exclusivo","f");
      l_resample->AddEntry(h_inel_el_x150,"Semi-exclusivo","f");
      l_resample->AddEntry(h_dy,"Drell-Yan","f");
      l_resample->AddEntry(h_new_resample,"Statistic Uncertainties","f");
      l_resample->Draw();
      char* name_resample = Form("comp_new/%s_resample.png", hist[i]);
      c_resample->SaveAs(name_resample);
      c_resample->cd();
      c_resample->Close();

      TCanvas *c_match_resample = new TCanvas("c_match_resample","",0,0,1200,1000);
      hs_match_resample.SetMaximum(max_hs_match_resample+step_hs_match_resample);
      h_match_data->SetMaximum(max_hs_match_resample+step_hs_match_resample);
      hs_match_resample.Draw("HIST");
      h_match_data->Draw("SAME");
      h_match_new_resample->Draw("E2 SAME");
      auto l_match_resample = new TLegend(0.9,0.9,0.7,0.7);
      l_match_resample->SetHeader("Work in progress","C"); // option "C" allows to center the header
      l_match_resample->AddEntry(h_match_data,"Dados","lep");
      l_match_resample->AddEntry((TObject*)0, "", "");
      l_match_resample->AddEntry((TObject*)0, "Monte Carlo", "");
      l_match_resample->AddEntry((TObject*)0, "", "");
      l_match_resample->AddEntry(h_match_elastic_x100,"Exclusivo","f");
      l_match_resample->AddEntry(h_match_elastic_x110,"Exclusivo","f");
      l_match_resample->AddEntry(h_match_elastic_x120,"Exclusivo","f");
      l_match_resample->AddEntry(h_match_elastic_x130,"Exclusivo","f");
      l_match_resample->AddEntry(h_match_elastic_x140,"Exclusivo","f");
      l_match_resample->AddEntry(h_match_elastic_x150,"Exclusivo","f");
      l_match_resample->AddEntry(h_match_inel_el_x100,"Semi-exclusivo","f");
      l_match_resample->AddEntry(h_match_inel_el_x110,"Semi-exclusivo","f");
      l_match_resample->AddEntry(h_match_inel_el_x120,"Semi-exclusivo","f");
      l_match_resample->AddEntry(h_match_inel_el_x130,"Semi-exclusivo","f");
      l_match_resample->AddEntry(h_match_inel_el_x140,"Semi-exclusivo","f");
      l_match_resample->AddEntry(h_match_inel_el_x150,"Semi-exclusivo","f");
      l_match_resample->AddEntry(h_match_dy,"Drell-Yan","f");
      l_match_resample->AddEntry(h_match_new_resample,"Statistic Uncertainties","f");
      l_match_resample->Draw();
      char* name_match_resample = Form("comp_new/%s.png", hist_match[i]);
      c_match_resample->SaveAs(name_match_resample);
      c_match_resample->cd();
      c_match_resample->Close();

   }
   return 0;
}
