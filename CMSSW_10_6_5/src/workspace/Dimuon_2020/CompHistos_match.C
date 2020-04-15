#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TSystem.h>
#include <TROOT.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TMultiGraph.h>
#include <TSpline.h>
#include <math.h>
#include <TH1F.h>
#include <THStack.h>
#include "tdrstyle.C"
#include "CMS_lumi.C"


#include <iostream>
#include <vector>
#include <set>
using namespace std;

int CompHistos_match()
{
   gStyle->SetOptStat(0);

   char const* hist_match[]= {"mumu_mass_rp23_match","mumu_mass_rp123_match","mumu_pt_rp23_match","mumu_pt_rp123_match","mumu_y_rp23_match","mumu_y_rp123_match","proton_xi_left_rp23_match","proton_xi_left_rp23_nprot_match","proton_xi_right_rp123_match","proton_xi_right_rp123_nprot_match","proton_xi_left_multi_match","proton_xi_right_multi_match","diff_proton_reco_pair_xi_left_rp23_match","diff_proton_reco_pair_xi_left_rp23_nprot_match","diff_proton_reco_pair_xi_right_rp123_match","diff_proton_reco_pair_xi_right_rp123_nprot_match","diff_proton_reco_pair_xi_left_multi_match","diff_proton_reco_pair_xi_right_multi_match","ratio_proton_reco_pair_xi_left_rp23_match","ratio_proton_reco_pair_xi_left_rp23_nprot_match","ratio_proton_reco_pair_xi_right_rp123_match","ratio_proton_reco_pair_xi_right_rp123_nprot_match","ratio_proton_reco_pair_xi_left_multi_match","ratio_proton_reco_pair_xi_right_multi_match","pair_xi_left_rp23_match","pair_xi_right_rp123_match","proton_left_reco_multi_ThX_match","proton_left_reco_multi_ThY_match","proton_right_reco_multi_ThX_match","proton_right_reco_multi_ThY_match"};

   setTDRStyle();
   int iPeriod = 4;
   int iPos = 11;

   size_t Nmatch = sizeof(hist_match)/sizeof(hist_match[0]);		

   TFile *f_elastic = new TFile("histos_MC/output_elastic_xangle130.root", "READ");
   TFile *f_elastic_x100 = new TFile("histos_MC/output_elastic_xangle100.root", "READ");
   TFile *f_elastic_x110 = new TFile("histos_MC/output_elastic_xangle110.root", "READ");
   TFile *f_elastic_x120 = new TFile("histos_MC/output_elastic_xangle120.root", "READ");
   TFile *f_elastic_x130 = new TFile("histos_MC/output_elastic_xangle130.root", "READ");
   TFile *f_elastic_x140 = new TFile("histos_MC/output_elastic_xangle140.root", "READ");
   TFile *f_elastic_x150 = new TFile("histos_MC/output_elastic_xangle150.root", "READ");
   TFile *f_inel_el = new TFile("histos_MC/output_inel-el_xangle130.root", "READ");
   TFile *f_inel_el_x100 = new TFile("histos_MC/output_inel-el_xangle100.root", "READ");
   TFile *f_inel_el_x110 = new TFile("histos_MC/output_inel-el_xangle110.root", "READ");
   TFile *f_inel_el_x120 = new TFile("histos_MC/output_inel-el_xangle120.root", "READ");
   TFile *f_inel_el_x130 = new TFile("histos_MC/output_inel-el_xangle130.root", "READ");
   TFile *f_inel_el_x140 = new TFile("histos_MC/output_inel-el_xangle140.root", "READ");
   TFile *f_inel_el_x150 = new TFile("histos_MC/output_inel-el_xangle150.root", "READ");
   TFile *f_dy = new TFile("histos_MC/output_dy_sigma_EG.root", "READ");
   //TFile *f_dy = new TFile("histos_MC/output_dy_sigma_EG_sem_reweight.root", "READ");
   TFile *f_dy_resample = new TFile("histos_MC/output_dy_resample_sigma_EG.root", "READ");
   TFile *f_elastic_mixpu = new TFile("histos_MC/exclusive_mixpu.root", "READ");
   TFile *f_inel_el_mixpu = new TFile("histos_MC/semi-exclusive_mixpu.root", "READ");
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
   double limit_lumi = 18.346268; //Used on the limited luminosity data
   double event_selection; //Used on the pile-up protons mixing
   double rap_gap_surv_elastic = 0.89; 
   double rap_gap_surv_inel_el = 0.76; 
   double rap_gap_surv_inelastic = 0.13; 

   double scale_factor_elastic = limit_lumi*rap_gap_surv_elastic*0.017254036*1000 / n_events_h_elastic ; //
   double scale_factor_elastic_x100 = xangle100*limit_lumi*rap_gap_surv_elastic*0.017254036*1000 / n_events_h_elastic ; //
   double scale_factor_elastic_x110 = xangle110*limit_lumi*rap_gap_surv_elastic*0.017254036*1000 / n_events_h_elastic ; //
   double scale_factor_elastic_x120 = xangle120*limit_lumi*rap_gap_surv_elastic*0.017254036*1000 / n_events_h_elastic ; //
   double scale_factor_elastic_x130 = xangle130*limit_lumi*rap_gap_surv_elastic*0.017254036*1000 / n_events_h_elastic ; //
   double scale_factor_elastic_x140 = xangle140*limit_lumi*rap_gap_surv_elastic*0.017254036*1000 / n_events_h_elastic ; //
   double scale_factor_elastic_x150 = xangle150*limit_lumi*rap_gap_surv_elastic*0.017254036*1000 / n_events_h_elastic ; //
   double scale_factor_inel_el = limit_lumi*rap_gap_surv_inel_el*0.025643100*1000 / n_events_h_inel_el ; //
   double scale_factor_inel_el_x100 = xangle100*limit_lumi*rap_gap_surv_inel_el*0.025643100*1000 / n_events_h_inel_el ; //
   double scale_factor_inel_el_x110 = xangle110*limit_lumi*rap_gap_surv_inel_el*0.025643100*1000 / n_events_h_inel_el ; //
   double scale_factor_inel_el_x120 = xangle120*limit_lumi*rap_gap_surv_inel_el*0.025643100*1000 / n_events_h_inel_el ; //
   double scale_factor_inel_el_x130 = xangle130*limit_lumi*rap_gap_surv_inel_el*0.025643100*1000 / n_events_h_inel_el ; //
   double scale_factor_inel_el_x140 = xangle140*limit_lumi*rap_gap_surv_inel_el*0.025643100*1000 / n_events_h_inel_el ; //
   double scale_factor_inel_el_x150 = xangle150*limit_lumi*rap_gap_surv_inel_el*0.025643100*1000 / n_events_h_inel_el ; //
   double scale_factor_dy = limit_lumi*5334000 / n_events_h_dy; 
   double scale_factor_dy_resample = limit_lumi*5334000 / ( n_events_h_dy*number_of_samples ) ; 

   for (int k = 0; k < Nmatch; k++) {

      if( (k >= 0 && k <= 5) || k == 24 || k == 25 ){
         event_selection = 1; //Used on the pile-up protons mixing
      }
      else {
         event_selection = 18964806./23701056; //Used on the pile-up protons mixing
      }   

      double scale_factor_dy_prot_sel = event_selection*limit_lumi*5334000 / n_events_h_dy; 
      double scale_factor_dy_resample_prot_sel = event_selection*limit_lumi*5334000 / ( n_events_h_dy*number_of_samples ) ; 

      TH1 *h_match_elastic_signal = 0; f_elastic->GetObject(hist_match[k], h_match_elastic_signal);
      TH1 *h_match_elastic_x100 = 0; f_elastic_x100->GetObject(hist_match[k], h_match_elastic_x100);
      TH1 *h_match_elastic_x110 = 0; f_elastic_x110->GetObject(hist_match[k], h_match_elastic_x110);
      TH1 *h_match_elastic_x120 = 0; f_elastic_x120->GetObject(hist_match[k], h_match_elastic_x120);
      TH1 *h_match_elastic_x130 = 0; f_elastic_x130->GetObject(hist_match[k], h_match_elastic_x130);
      TH1 *h_match_elastic_x140 = 0; f_elastic_x140->GetObject(hist_match[k], h_match_elastic_x140);
      TH1 *h_match_elastic_x150 = 0; f_elastic_x150->GetObject(hist_match[k], h_match_elastic_x150);
      TH1 *h_match_inel_el_signal = 0; f_inel_el->GetObject(hist_match[k], h_match_inel_el_signal);
      TH1 *h_match_inel_el_x100 = 0; f_inel_el_x100->GetObject(hist_match[k], h_match_inel_el_x100);
      TH1 *h_match_inel_el_x110 = 0; f_inel_el_x110->GetObject(hist_match[k], h_match_inel_el_x110);
      TH1 *h_match_inel_el_x120 = 0; f_inel_el_x120->GetObject(hist_match[k], h_match_inel_el_x120);
      TH1 *h_match_inel_el_x130 = 0; f_inel_el_x130->GetObject(hist_match[k], h_match_inel_el_x130);
      TH1 *h_match_inel_el_x140 = 0; f_inel_el_x140->GetObject(hist_match[k], h_match_inel_el_x140);
      TH1 *h_match_inel_el_x150 = 0; f_inel_el_x150->GetObject(hist_match[k], h_match_inel_el_x150);
      TH1 *h_match_dy = 0; f_dy->GetObject(hist_match[k], h_match_dy);
      TH1 *h_match_dy_resample = 0; f_dy_resample->GetObject(hist_match[k], h_match_dy_resample);
      TH1 *h_match_elastic_mixpu = 0; f_elastic_mixpu->GetObject(hist_match[k], h_match_elastic_mixpu);
      TH1 *h_match_inel_el_mixpu = 0; f_inel_el_mixpu->GetObject(hist_match[k], h_match_inel_el_mixpu);
      TH1 *h_match_data = 0; f_data->GetObject(hist_match[k], h_match_data);

      if ( k >= 0 && k <= 25 ) {
         h_match_elastic_signal->SetLineColor(kBlue-4);
         h_match_elastic_x100->SetLineColor(kCyan);
         h_match_elastic_x110->SetLineColor(kBlue);
         h_match_elastic_x120->SetLineColor(kBlue+3);
         h_match_elastic_x130->SetLineColor(kPink-9);
         h_match_elastic_x140->SetLineColor(kMagenta+1);
         h_match_elastic_x150->SetLineColor(kViolet-3);
         h_match_inel_el_signal->SetLineColor(kGreen-3);
         h_match_inel_el_x100->SetLineColor(kYellow);
         h_match_inel_el_x110->SetLineColor(kOrange);
         h_match_inel_el_x120->SetLineColor(kGreen);
         h_match_inel_el_x130->SetLineColor(kSpring-1);
         h_match_inel_el_x140->SetLineColor(kGreen+2);
         h_match_inel_el_x150->SetLineColor(kTeal-1);
         h_match_dy->SetLineColor(kRed-3);
         h_match_dy_resample->SetLineColor(kRed-3);
         h_match_data->SetLineColor(kBlack);
         h_match_elastic_mixpu->SetLineColor(kOrange-1);
         h_match_inel_el_mixpu->SetLineColor(kOrange-1);
         h_match_elastic_signal->SetFillColor(kBlue-4);
         h_match_elastic_x100->SetFillColor(kCyan);
         h_match_elastic_x110->SetFillColor(kBlue);
         h_match_elastic_x120->SetFillColor(kBlue+3);
         h_match_elastic_x130->SetFillColor(kPink-9);
         h_match_elastic_x140->SetFillColor(kMagenta+1);
         h_match_elastic_x150->SetFillColor(kViolet-3);
         h_match_inel_el_signal->SetFillColor(kGreen-3);
         h_match_inel_el_x100->SetFillColor(kYellow);
         h_match_inel_el_x110->SetFillColor(kOrange);
         h_match_inel_el_x120->SetFillColor(kGreen);
         h_match_inel_el_x130->SetFillColor(kSpring-1);
         h_match_inel_el_x140->SetFillColor(kGreen+2);
         h_match_inel_el_x150->SetFillColor(kTeal-1);
         h_match_dy->SetFillColor(kRed-3);
         h_match_dy_resample->SetFillColor(kRed-3);
         h_match_elastic_mixpu->SetFillColor(kOrange-1);
         h_match_inel_el_mixpu->SetFillColor(kOrange-1);
         h_match_data->SetMarkerStyle(8);
      }
      else { 
         h_match_data->SetLineColor(kBlack);
         h_match_data->SetMarkerStyle(8);
      }

      if( k >= 0 && k <= 5 ){
         h_match_elastic_signal->Scale(scale_factor_elastic);
         h_match_elastic_x100->Scale(scale_factor_elastic_x100);
         h_match_elastic_x110->Scale(scale_factor_elastic_x110);
         h_match_elastic_x120->Scale(scale_factor_elastic_x120);
         h_match_elastic_x130->Scale(scale_factor_elastic_x130);
         h_match_elastic_x140->Scale(scale_factor_elastic_x140);
         h_match_elastic_x150->Scale(scale_factor_elastic_x150);
         h_match_inel_el_signal->Scale(scale_factor_inel_el);
         h_match_inel_el_x100->Scale(scale_factor_inel_el_x100);
         h_match_inel_el_x110->Scale(scale_factor_inel_el_x110);
         h_match_inel_el_x120->Scale(scale_factor_inel_el_x120);
         h_match_inel_el_x130->Scale(scale_factor_inel_el_x130);
         h_match_inel_el_x140->Scale(scale_factor_inel_el_x140);
         h_match_inel_el_x150->Scale(scale_factor_inel_el_x150);
         h_match_dy->Scale(scale_factor_dy_prot_sel);
         h_match_dy_resample->Scale(scale_factor_dy_resample_prot_sel);
         h_match_data->Scale(1);
         h_match_elastic_mixpu->Scale(scale_factor_elastic);
         h_match_inel_el_mixpu->Scale(scale_factor_inel_el);
      }
      else if ( k >= 26 && k <= 29 ) {
         h_match_data->Scale(1); 
      }   
      else { 
         h_match_elastic_signal->Scale(scale_factor_elastic, "width");
         h_match_elastic_x100->Scale(scale_factor_elastic_x100, "width");
         h_match_elastic_x110->Scale(scale_factor_elastic_x110, "width");
         h_match_elastic_x120->Scale(scale_factor_elastic_x120, "width");
         h_match_elastic_x130->Scale(scale_factor_elastic_x130, "width");
         h_match_elastic_x140->Scale(scale_factor_elastic_x140, "width");
         h_match_elastic_x150->Scale(scale_factor_elastic_x150, "width");
         h_match_inel_el_signal->Scale(scale_factor_inel_el, "width");
         h_match_inel_el_x100->Scale(scale_factor_inel_el_x100, "width");
         h_match_inel_el_x110->Scale(scale_factor_inel_el_x110, "width");
         h_match_inel_el_x120->Scale(scale_factor_inel_el_x120, "width");
         h_match_inel_el_x130->Scale(scale_factor_inel_el_x130, "width");
         h_match_inel_el_x140->Scale(scale_factor_inel_el_x140, "width");
         h_match_inel_el_x150->Scale(scale_factor_inel_el_x150, "width");
         h_match_dy->Scale(scale_factor_dy_prot_sel, "width");
         h_match_dy_resample->Scale(scale_factor_dy_resample_prot_sel, "width");
         h_match_data->Scale(1, "width");
         h_match_elastic_mixpu->Scale(scale_factor_elastic, "width");
         h_match_inel_el_mixpu->Scale(scale_factor_inel_el, "width");
      }

      THStack* hs_match_xangle = new THStack("hs_match_xangle", Form("%s", hist_match[k]));
      if ( k >= 0 && k <= 25 ) {
         hs_match_xangle->Add(h_match_elastic_x100); 
         hs_match_xangle->Add(h_match_elastic_x110); 
         hs_match_xangle->Add(h_match_elastic_x120); 
         hs_match_xangle->Add(h_match_elastic_x130); 
         hs_match_xangle->Add(h_match_elastic_x140); 
         hs_match_xangle->Add(h_match_elastic_x150); 
         hs_match_xangle->Add(h_match_inel_el_x100); 
         hs_match_xangle->Add(h_match_inel_el_x110); 
         hs_match_xangle->Add(h_match_inel_el_x120); 
         hs_match_xangle->Add(h_match_inel_el_x130); 
         hs_match_xangle->Add(h_match_inel_el_x140); 
         hs_match_xangle->Add(h_match_inel_el_x150); 
         hs_match_xangle->Add(h_match_dy); 
      }
      TH1F *h_match_xangle_new = 0;
      if ( k >= 0 && k <= 25 ) {
         h_match_xangle_new = (TH1F*)h_match_elastic_x100->Clone("h_match_xangle_new");
         h_match_xangle_new->Add(h_match_elastic_x110); 
         h_match_xangle_new->Add(h_match_elastic_x120); 
         h_match_xangle_new->Add(h_match_elastic_x130); 
         h_match_xangle_new->Add(h_match_elastic_x140); 
         h_match_xangle_new->Add(h_match_elastic_x150); 
         h_match_xangle_new->Add(h_match_inel_el_x100); 
         h_match_xangle_new->Add(h_match_inel_el_x110); 
         h_match_xangle_new->Add(h_match_inel_el_x120); 
         h_match_xangle_new->Add(h_match_inel_el_x130); 
         h_match_xangle_new->Add(h_match_inel_el_x140); 
         h_match_xangle_new->Add(h_match_inel_el_x150); 
         h_match_xangle_new->Add(h_match_dy); 

         h_match_xangle_new->Sumw2();
         h_match_xangle_new->SetFillColor(1);
         h_match_xangle_new->SetFillStyle(3004);
         h_match_xangle_new->SetMarkerStyle(6);
         h_match_xangle_new->SetMarkerSize(0);
         h_match_xangle_new->SetLineWidth(0);
      }

      THStack* hs_match_xangle_resample = new THStack("hs_match_xangle_resample", Form("%s_resample", hist_match[k]));
      if ( k >= 0 && k <= 25 ) {
         hs_match_xangle_resample->Add(h_match_elastic_x100); 
         hs_match_xangle_resample->Add(h_match_elastic_x110); 
         hs_match_xangle_resample->Add(h_match_elastic_x120); 
         hs_match_xangle_resample->Add(h_match_elastic_x130); 
         hs_match_xangle_resample->Add(h_match_elastic_x140); 
         hs_match_xangle_resample->Add(h_match_elastic_x150); 
         hs_match_xangle_resample->Add(h_match_inel_el_x100); 
         hs_match_xangle_resample->Add(h_match_inel_el_x110); 
         hs_match_xangle_resample->Add(h_match_inel_el_x120); 
         hs_match_xangle_resample->Add(h_match_inel_el_x130); 
         hs_match_xangle_resample->Add(h_match_inel_el_x140); 
         hs_match_xangle_resample->Add(h_match_inel_el_x150); 
         hs_match_xangle_resample->Add(h_match_dy_resample); 
      }

      TH1F *h_match_xangle_new_resample = 0;
      if ( k >= 0 && k <= 25 ) {
         h_match_xangle_new_resample = (TH1F*)h_match_elastic_x100->Clone("h_match_xangle_new_resample");
         h_match_xangle_new_resample->Add(h_match_elastic_x110); 
         h_match_xangle_new_resample->Add(h_match_elastic_x120); 
         h_match_xangle_new_resample->Add(h_match_elastic_x130); 
         h_match_xangle_new_resample->Add(h_match_elastic_x140); 
         h_match_xangle_new_resample->Add(h_match_elastic_x150); 
         h_match_xangle_new_resample->Add(h_match_inel_el_x100); 
         h_match_xangle_new_resample->Add(h_match_inel_el_x110); 
         h_match_xangle_new_resample->Add(h_match_inel_el_x120); 
         h_match_xangle_new_resample->Add(h_match_inel_el_x130); 
         h_match_xangle_new_resample->Add(h_match_inel_el_x140); 
         h_match_xangle_new_resample->Add(h_match_inel_el_x150); 
         h_match_xangle_new_resample->Add(h_match_dy_resample); 

         h_match_xangle_new_resample->Sumw2();
         h_match_xangle_new_resample->SetFillColor(1);
         h_match_xangle_new_resample->SetFillStyle(3004);
         h_match_xangle_new_resample->SetMarkerStyle(6);
         h_match_xangle_new_resample->SetMarkerSize(0);
         h_match_xangle_new_resample->SetLineWidth(0);
      }

      THStack* hs_match = new THStack("hs_match", Form("%s", hist_match[k]));
      if ( k >= 0 && k <= 25 ) {
         hs_match->Add(h_match_elastic_signal); 
         hs_match->Add(h_match_inel_el_signal); 
         if(k == 7 || k == 9 || k == 13 || k == 15 || k == 19 || k == 21) {
            hs_match->Add(h_match_elastic_mixpu); 
            hs_match->Add(h_match_inel_el_mixpu); 
         }
         hs_match->Add(h_match_dy); 
      }

      TH1F *h_match_new = 0;
      if ( k >= 0 && k <= 25 ) {
         h_match_new = (TH1F*)h_match_elastic_signal->Clone("h_match_new");
         h_match_new->Add(h_match_inel_el_signal); 
         if(k == 7 || k == 9 || k == 13 || k == 15 || k == 19 || k == 21) {
            h_match_new->Add(h_match_elastic_mixpu); 
            h_match_new->Add(h_match_inel_el_mixpu);
         } 
         h_match_new->Add(h_match_dy); 

         h_match_new->Sumw2();
         h_match_new->SetFillColor(1);
         h_match_new->SetFillStyle(3004);
         h_match_new->SetMarkerStyle(6);
         h_match_new->SetMarkerSize(0);
         h_match_new->SetLineWidth(0);
      }

      THStack* hs_match_resample = new THStack("hs_match_resample", Form("%s_resample", hist_match[k]));
      if ( k >= 0 && k <= 25 ) {
         hs_match_resample->Add(h_match_elastic_signal); 
         hs_match_resample->Add(h_match_inel_el_signal); 
         if(k == 7 || k == 9 || k == 13 || k == 15 || k == 19 || k == 21) {
            hs_match_resample->Add(h_match_elastic_mixpu); 
            hs_match_resample->Add(h_match_inel_el_mixpu);
         }   
         hs_match_resample->Add(h_match_dy_resample); 
      }

      TH1F *h_match_new_resample = 0; 
      if ( k >= 0 && k <= 25 ) {
         h_match_new_resample = (TH1F*)h_match_elastic_signal->Clone("h_match_new_resample");
         h_match_new_resample->Add(h_match_inel_el_signal); 
         if(k == 7 || k == 9 || k == 13 || k == 15 || k == 19 || k == 21) {
            h_match_new_resample->Add(h_match_elastic_mixpu); 
            h_match_new_resample->Add(h_match_inel_el_mixpu);
         }   
         h_match_new_resample->Add(h_match_dy_resample); 

         h_match_new_resample->Sumw2();
         h_match_new_resample->SetFillColor(1);
         h_match_new_resample->SetFillStyle(3004);
         h_match_new_resample->SetMarkerStyle(6);
         h_match_new_resample->SetMarkerSize(0);
         h_match_new_resample->SetLineWidth(0);
      }
      TH1F *h_match_new_10 = 0;
      if( k == 10 || k == 11) {
         h_match_new_10 = (TH1F*)h_match_dy_resample->Clone("h_match_new_10");
         h_match_new_10->Sumw2();
         h_match_new_10->SetFillColor(1);
         h_match_new_10->SetFillStyle(3004);
         h_match_new_10->SetMarkerStyle(6);
         h_match_new_10->SetMarkerSize(0);
         h_match_new_10->SetLineWidth(0);

      }

      double max_hs_match_xangle = 0.0;
      double max_hs_match_xangle_resample = 0.0;
      double max_hs_match = 0.0;
      double max_hs_match_resample = 0.0;
      double max_match_data = 0.0;


      if ( k >= 0 && k <= 25 ) {
         if(hs_match_xangle->GetMaximum() > h_match_data->GetMaximum()) {
            max_hs_match_xangle = hs_match_xangle->GetMaximum();
         }
         else {
            max_hs_match_xangle = h_match_data->GetMaximum();
         }
         if(hs_match_xangle_resample->GetMaximum() > h_match_data->GetMaximum()) {
            max_hs_match_xangle_resample = hs_match_xangle_resample->GetMaximum();
         }
         else {
            max_hs_match_xangle_resample = h_match_data->GetMaximum();
         }
         if(hs_match->GetMaximum() > h_match_data->GetMaximum()) {
            max_hs_match = hs_match->GetMaximum();
         }
         else {
            max_hs_match = h_match_data->GetMaximum();
         }
         if(hs_match_resample->GetMaximum() > h_match_data->GetMaximum()) {
            max_hs_match_resample = hs_match_resample->GetMaximum();
         }
         else {
            max_hs_match_resample = h_match_data->GetMaximum();
         }
      }
      double step_hs_match_xangle =0.25*max_hs_match_xangle;
      double step_hs_match_xangle_resample =0.25*max_hs_match_xangle_resample;
      double step_hs_match =0.25*max_hs_match;
      double step_hs_match_resample =0.25*max_hs_match_resample;

      TCanvas *c_match_xangle = new TCanvas("c_match_xangle","",0,0,1200,1000);
      TPad *pad_match_xangle = new TPad("pad_match_xangle", "pad_match_xangle", 0.0, 0.0, 1.0, 1.0);
      if ( k >= 0 && k <= 25 ) {
         //pad_match_xangle->SetBottomMargin(0); // Upper and lower plot are joined
         pad_match_xangle->Draw();             // Draw the upper pad: pad1
         pad_match_xangle->cd();               // pad1 becomes the current pad
         hs_match_xangle->SetMaximum(max_hs_match_xangle+step_hs_match_xangle);
         h_match_data->SetMaximum(max_hs_match_xangle+step_hs_match_xangle);
         hs_match_xangle->Draw("HIST");
         hs_match_xangle->GetXaxis()->SetTitleOffset(1.1);
         if ( k == 0 || k == 1) {
            hs_match_xangle->GetXaxis()->SetTitle("M_{#mu^{+}#mu^{-}} (GeV/c^{2})");
            hs_match_xangle->GetYaxis()->SetTitle("Events");
         }
         if ( k == 2 || k == 3) {
            hs_match_xangle->GetXaxis()->SetTitle("p_{T #mu^{+}#mu^{-}} (GeV/c)");
            hs_match_xangle->GetYaxis()->SetTitle("Events");
         }
         if ( k == 4 || k == 5) {
            hs_match_xangle->GetXaxis()->SetTitle("y_{#mu^{+}#mu^{-}}");
            hs_match_xangle->GetYaxis()->SetTitle("Events");
         }    
         if ( k >= 6 && k <= 11 ) {
            hs_match_xangle->GetXaxis()->SetTitle("#xi(RP)");
            hs_match_xangle->GetYaxis()->SetTitle("dN/d#xi(RP)");
            hs_match_xangle->GetYaxis()->SetTitleOffset(1.3);
         }   
         if ( k >= 12 && k <= 17 ) {
            hs_match_xangle->GetXaxis()->SetTitle("#xi(RP) - #xi(#mu^{+}#mu^{-})");
            hs_match_xangle->GetYaxis()->SetTitle("dN/d(#xi(RP) - #xi(#mu^{+}#mu^{-}))");
            hs_match_xangle->GetYaxis()->SetTitleOffset(1.3);
         }   
         if ( k >= 18 && k <= 23 ) {
            hs_match_xangle->GetXaxis()->SetTitle("1 - #xi(RP)/#xi(#mu^{+}#mu^{-})");
            hs_match_xangle->GetYaxis()->SetTitle("dN/d(1 - #xi(RP)/#xi(#mu^{+}#mu^{-}))");
            hs_match_xangle->GetYaxis()->SetTitleOffset(1.3);
         }   
         if ( k == 24 || k == 25 ) {
            hs_match_xangle->GetXaxis()->SetTitle("#xi(#mu^{+}#mu^{-})");
            hs_match_xangle->GetYaxis()->SetTitle("dN/d#xi(#mu^{+}#mu^{-})");
            hs_match_xangle->GetYaxis()->SetTitleOffset(1.3);
         }   
         h_match_data->Draw("SAME");
         h_match_xangle_new->Draw("E2 SAME");
      }
      auto l_match_xangle = new TLegend(0.925,0.925,0.625,0.625);
      if ( k >= 0 && k <= 25 ) {
         l_match_xangle->AddEntry(h_match_data,"2017 Data","lep");
         l_match_xangle->AddEntry((TObject*)0,"pp -> p #gamma#gamma p","");
         l_match_xangle->AddEntry(h_match_elastic_x100,"xangle 100","f");
         l_match_xangle->AddEntry(h_match_elastic_x110,"xangle 110","f");
         l_match_xangle->AddEntry(h_match_elastic_x120,"xangle 120","f");
         l_match_xangle->AddEntry(h_match_elastic_x130,"xangle 130","f");
         l_match_xangle->AddEntry(h_match_elastic_x140,"xangle 140","f");
         l_match_xangle->AddEntry(h_match_elastic_x150,"xangle 150","f");
         l_match_xangle->AddEntry((TObject*)0,"pp -> p #gamma#gamma p*","");
         l_match_xangle->AddEntry(h_match_inel_el_x100,"xangle 100","f");
         l_match_xangle->AddEntry(h_match_inel_el_x110,"xangle 110","f");
         l_match_xangle->AddEntry(h_match_inel_el_x120,"xangle 120","f");
         l_match_xangle->AddEntry(h_match_inel_el_x130,"xangle 130","f");
         l_match_xangle->AddEntry(h_match_inel_el_x140,"xangle 140","f");
         l_match_xangle->AddEntry(h_match_inel_el_x150,"xangle 150","f");
         l_match_xangle->AddEntry(h_match_dy,"Drell-Yan mixed with pileup","f");
         l_match_xangle->AddEntry(h_match_xangle_new,"Statistic Uncertainties","f");
         l_match_xangle->Draw();
         pad_match_xangle->RedrawAxis();
         writeExtraText = true;       // if extra text
         extraText  = "Preliminary";  // default extra text is "Preliminary"
         lumi_13TeV  = "18.34 fb^{-1}";  // default is "20.1 fb^{-1}"
         CMS_lumi( pad_match_xangle, iPeriod, iPos );
         pad_match_xangle->Update();
         c_match_xangle->cd();
         gPad->Update();
         if ( k >= 18 && k <= 23 ){
            l_match_xangle->SetX1NDC(0.4);
            l_match_xangle->SetX2NDC(0.6);
         }
         gPad->Modified();
      }
      //char const* name = Form("comp_new/normal/%s.png", hist[i]);
      char const* name_match_xangle = Form("comp_xangle/match/%s.pdf", hist_match[k]);
      if ( k >= 0 && k <= 25 ) {
         c_match_xangle->SaveAs(name_match_xangle);
         c_match_xangle->cd();
         c_match_xangle->Close();
      }

      TCanvas *c_match_xangle_resample = new TCanvas("c_match_xangle_resample","",0,0,1200,1000);
      TPad *pad_match_xangle_resample = new TPad("pad_match_xangle_resample", "pad_match_xangle_resample", 0.0, 0.0, 1.0, 1.0);
      if ( k >= 0 && k <= 25 ) {
         //pad_match_xangle_resample->SetBottomMargin(0); // Upper and lower plot are joined
         pad_match_xangle_resample->Draw();             // Draw the upper pad: pad1
         pad_match_xangle_resample->cd();               // pad1 becomes the current pad
         hs_match_xangle_resample->SetMaximum(max_hs_match_xangle_resample+step_hs_match_xangle_resample);
         h_match_data->SetMaximum(max_hs_match_xangle_resample+step_hs_match_xangle_resample);
         hs_match_xangle_resample->Draw("HIST");
         hs_match_xangle_resample->GetXaxis()->SetTitleOffset(1.1);
         if ( k == 0 || k == 1) {
            hs_match_xangle_resample->GetXaxis()->SetTitle("M_{#mu^{+}#mu^{-}} (GeV/c^{2})");
            hs_match_xangle_resample->GetYaxis()->SetTitle("Events");
         }
         if ( k == 2 || k == 3) {
            hs_match_xangle_resample->GetXaxis()->SetTitle("p_{T #mu^{+}#mu^{-}} (GeV/c)");
            hs_match_xangle_resample->GetYaxis()->SetTitle("Events");
         }
         if ( k == 4 || k == 5) {
            hs_match_xangle_resample->GetXaxis()->SetTitle("y_{#mu^{+}#mu^{-}}");
            hs_match_xangle_resample->GetYaxis()->SetTitle("Events");
         }    
         if ( k >= 6 && k <= 11 ) {
            hs_match_xangle_resample->GetXaxis()->SetTitle("#xi(RP)");
            hs_match_xangle_resample->GetYaxis()->SetTitle("dN/d#xi(RP)");
            hs_match_xangle_resample->GetYaxis()->SetTitleOffset(1.3);
         }   
         if ( k >= 12 && k <= 17 ) {
            hs_match_xangle_resample->GetXaxis()->SetTitle("#xi(RP) - #xi(#mu^{+}#mu^{-})");
            hs_match_xangle_resample->GetYaxis()->SetTitle("dN/d(#xi(RP) - #xi(#mu^{+}#mu^{-}))");
            hs_match_xangle_resample->GetYaxis()->SetTitleOffset(1.3);
         }   
         if ( k >= 18 && k <= 23 ) {
            hs_match_xangle_resample->GetXaxis()->SetTitle("1 - #xi(RP)/#xi(#mu^{+}#mu^{-})");
            hs_match_xangle_resample->GetYaxis()->SetTitle("dN/d(1 - #xi(RP)/#xi(#mu^{+}#mu^{-}))");
            hs_match_xangle_resample->GetYaxis()->SetTitleOffset(1.3);
         }   
         if ( k == 24 || k == 25 ) {
            hs_match_xangle_resample->GetXaxis()->SetTitle("#xi(#mu^{+}#mu^{-})");
            hs_match_xangle_resample->GetYaxis()->SetTitle("dN/d#xi(#mu^{+}#mu^{-})");
            hs_match_xangle_resample->GetYaxis()->SetTitleOffset(1.3);
         }   
         h_match_data->Draw("SAME");
         h_match_xangle_new_resample->Draw("E2 SAME");
      }
      auto l_match_xangle_resample = new TLegend(0.925,0.925,0.625,0.625);
      if ( k >= 0 && k <= 25 ) {
         l_match_xangle_resample->AddEntry(h_match_data,"2017 Data","lep");
         l_match_xangle_resample->AddEntry((TObject*)0,"pp -> p #gamma#gamma p","");
         l_match_xangle_resample->AddEntry(h_match_elastic_x100,"xangle 100","f");
         l_match_xangle_resample->AddEntry(h_match_elastic_x110,"xangle 110","f");
         l_match_xangle_resample->AddEntry(h_match_elastic_x120,"xangle 120","f");
         l_match_xangle_resample->AddEntry(h_match_elastic_x130,"xangle 130","f");
         l_match_xangle_resample->AddEntry(h_match_elastic_x140,"xangle 140","f");
         l_match_xangle_resample->AddEntry(h_match_elastic_x150,"xangle 150","f");
         l_match_xangle_resample->AddEntry((TObject*)0,"pp -> p #gamma#gamma p*","");
         l_match_xangle_resample->AddEntry(h_match_inel_el_x100,"xangle 100","f");
         l_match_xangle_resample->AddEntry(h_match_inel_el_x110,"xangle 110","f");
         l_match_xangle_resample->AddEntry(h_match_inel_el_x120,"xangle 120","f");
         l_match_xangle_resample->AddEntry(h_match_inel_el_x130,"xangle 130","f");
         l_match_xangle_resample->AddEntry(h_match_inel_el_x140,"xangle 140","f");
         l_match_xangle_resample->AddEntry(h_match_inel_el_x150,"xangle 150","f");
         l_match_xangle_resample->AddEntry(h_match_dy,"Drell-Yan mixed with pileup","f");
         l_match_xangle_resample->AddEntry(h_match_xangle_new,"Statistic Uncertainties","f");
         l_match_xangle_resample->Draw();
         pad_match_xangle_resample->RedrawAxis();
         writeExtraText = true;       // if extra text
         extraText  = "Preliminary";  // default extra text is "Preliminary"
         lumi_13TeV  = "18.34 fb^{-1}";  // default is "20.1 fb^{-1}"
         CMS_lumi( pad_match_xangle_resample, iPeriod, iPos );
         pad_match_xangle_resample->Update();
         c_match_xangle_resample->cd();
         gPad->Update();
         if ( k >= 18 && k <= 23 ){
            l_match_xangle_resample->SetX1NDC(0.4);
            l_match_xangle_resample->SetX2NDC(0.6);
         }
         gPad->Modified();
         //char const* name_resample = Form("comp_new/resample/%s_resample.png", hist[i]);
      }
      char const* name_match_xangle_resample = Form("comp_xangle/match_resample/%s_resample.pdf", hist_match[k]);
      if ( k >= 0 && k <= 25 ) {
         c_match_xangle_resample->SaveAs(name_match_xangle_resample);
         c_match_xangle_resample->cd();
         c_match_xangle_resample->Close();
      }

      TCanvas *c_match = new TCanvas("c_match","",0,0,1200,1000);
      TPad *pad_match = new TPad("pad_match", "pad_match", 0.0, 0.0, 1.0, 1.0);
      //pad_match->SetBottomMargin(0); // Upper and lower plot are joined
      pad_match->Draw();             // Draw the upper pad: pad1
      pad_match->cd();               // pad1 becomes the current pad
      if ( (k >= 0 && k <= 9) || (k >= 12 && k <= 25) ) { 
         hs_match->SetMaximum(max_hs_match+step_hs_match);
         h_match_data->SetMaximum(max_hs_match+step_hs_match);
         hs_match->Draw("HIST");
         hs_match->GetXaxis()->SetTitleOffset(1.1);
         if ( k == 0 || k == 1) {
            hs_match->GetXaxis()->SetTitle("M_{#mu^{+}#mu^{-}} (GeV/c^{2})");
            hs_match->GetYaxis()->SetTitle("Events");
         }
         if ( k == 2 || k == 3) {
            hs_match->GetXaxis()->SetTitle("p_{T #mu^{+}#mu^{-}} (GeV/c)");
            hs_match->GetYaxis()->SetTitle("Events");
         }
         if ( k == 4 || k == 5) {
            hs_match->GetXaxis()->SetTitle("y_{#mu^{+}#mu^{-}}");
            hs_match->GetYaxis()->SetTitle("Events");
         }    
         if ( k >= 6 && k <= 9 ) {
            hs_match->GetXaxis()->SetTitle("#xi(RP)");
            hs_match->GetYaxis()->SetTitle("dN/d#xi(RP)");
            hs_match->GetYaxis()->SetTitleOffset(1.3);
         }   
         if ( k >= 12 && k <= 17 ) {
            hs_match->GetXaxis()->SetTitle("#xi(RP) - #xi(#mu^{+}#mu^{-})");
            hs_match->GetYaxis()->SetTitle("dN/d(#xi(RP) - #xi(#mu^{+}#mu^{-}))");
            hs_match->GetYaxis()->SetTitleOffset(1.3);
         }   
         if ( k >= 18 && k <= 23 ) {
            hs_match->GetXaxis()->SetTitle("1 - #xi(RP)/#xi(#mu^{+}#mu^{-})");
            hs_match->GetYaxis()->SetTitle("dN/d(1 - #xi(RP)/#xi(#mu^{+}#mu^{-}))");
            hs_match->GetYaxis()->SetTitleOffset(1.3);
         }   
         if ( k == 24 || k == 25 ) {
            hs_match->GetXaxis()->SetTitle("#xi(#mu^{+}#mu^{-})");
            hs_match->GetYaxis()->SetTitle("dN/d#xi(#mu^{+}#mu^{-})");
            hs_match->GetYaxis()->SetTitleOffset(1.3);
         }
         h_match_data->Draw("SAME");
         h_match_new->Draw("E2 SAME");
      }
      else if ( k == 10 || k == 11 ){
         h_match_dy_resample->SetMaximum(200);
         h_match_dy_resample->Draw("HIST");
         h_match_data->Draw("SAME");
         h_match_new_10->Draw("E2 SAME");
         h_match_dy_resample->GetXaxis()->SetTitle("#xi(RP)");
         h_match_dy_resample->GetYaxis()->SetTitle("dN/d#xi(RP)");
         h_match_dy_resample->GetYaxis()->SetTitleOffset(1.3);
      }
      else {
         h_match_data->SetMaximum(6.5);
         h_match_data->Draw();
         if ( k == 26 || k == 28 ) h_match_data->GetXaxis()->SetTitle("#theta_{X} (rad)");
         if ( k == 27 || k == 29 ) h_match_data->GetXaxis()->SetTitle("#theta_{Y} (rad)");
         h_match_data->GetYaxis()->SetTitle("Events");
         //h_match_data->GetYaxis()->SetTitleOffset(1.3);

      }   
      auto l_match = new TLegend(0.895,0.925,0.695,0.725);
      if ( (k >= 0 && k <= 9) || (k >= 12 && k <= 25) ) { 
         l_match->AddEntry(h_match_data,"2017 Data","lep");
         l_match->AddEntry(h_match_elastic_signal,"pp -> p #gamma#gamma p","f");
         l_match->AddEntry(h_match_inel_el_signal,"pp -> p #gamma#gamma p*","f");
         if(k == 7 || k == 9 || k == 13 || k == 15 || k == 19 || k == 21) {
            l_match->AddEntry(h_match_elastic_mixpu,"pp -> p #gamma#gamma p(*) mixed with pileup","f");
         }   
         l_match->AddEntry(h_match_dy,"Drell-Yan mixed with pileup","f");
         l_match->AddEntry(h_match_new,"Statistic Uncertainties","f");
      }
      else {
         l_match->AddEntry(h_match_data,"2017 Data","lep");
         l_match->AddEntry(h_match_dy,"Drell-Yan mixed with pileup","f");
         l_match->AddEntry(h_match_new,"Statistic Uncertainties","f");
      }
      l_match->Draw();
      pad_match->RedrawAxis();
      writeExtraText = true;       // if extra text
      extraText  = "Preliminary";  // default extra text is "Preliminary"
      lumi_13TeV  = "18.34 fb^{-1}";  // default is "20.1 fb^{-1}"
      CMS_lumi( pad_match, iPeriod, iPos );
      pad_match->Update();
      c_match->cd();
      gPad->Update();
      if ( k >= 18 && k <= 23 ){
         l_match->SetX1NDC(0.4);
         l_match->SetX2NDC(0.6);
      }
      gPad->Modified();
      //char const* name_match = Form("comp_new/match/%s.png", hist_match[k]);
      char const* name_match = Form("comp_mixpu/match/%s.pdf", hist_match[k]);
      c_match->SaveAs(name_match);
      c_match->cd();
      c_match->Close();

      TCanvas *c_match_resample = new TCanvas("c_match_resample","",0,0,1200,1000);
      TPad *pad_match_resample = new TPad("pad_match_resample", "pad_match_resample", 0.0, 0.0, 1.0, 1.0);
      if ( k >= 0 && k <= 25 ) {
         //pad_match_resample->SetBottomMargin(0); // Upper and lower plot are joined
         pad_match_resample->Draw();             // Draw the upper pad: pad1
         pad_match_resample->cd();               // pad1 becomes the current pad
         hs_match_resample->SetMaximum(max_hs_match_resample+step_hs_match_resample);
         h_match_data->SetMaximum(max_hs_match_resample+step_hs_match_resample);
         hs_match_resample->Draw("HIST");
         hs_match_resample->GetXaxis()->SetTitleOffset(1.1);
         if ( k == 0 || k == 1) {
            hs_match_resample->GetXaxis()->SetTitle("M_{#mu^{+}#mu^{-}} (GeV/c^{2})");
            hs_match_resample->GetYaxis()->SetTitle("Events");
         }
         if ( k == 2 || k == 3) {
            hs_match_resample->GetXaxis()->SetTitle("p_{T #mu^{+}#mu^{-}} (GeV/c)");
            hs_match_resample->GetYaxis()->SetTitle("Events");
         }
         if ( k == 4 || k == 5) {
            hs_match_resample->GetXaxis()->SetTitle("y_{#mu^{+}#mu^{-}}");
            hs_match_resample->GetYaxis()->SetTitle("Events");
         }    
         if ( k >= 6 && k <= 11 ) {
            hs_match_resample->GetXaxis()->SetTitle("#xi(RP)");
            hs_match_resample->GetYaxis()->SetTitle("dN/d#xi(RP)");
            hs_match_resample->GetYaxis()->SetTitleOffset(1.3);
         }   
         if ( k >= 12 && k <= 17 ) {
            hs_match_resample->GetXaxis()->SetTitle("#xi(RP) - #xi(#mu^{+}#mu^{-})");
            hs_match_resample->GetYaxis()->SetTitle("dN/d(#xi(RP) - #xi(#mu^{+}#mu^{-}))");
            hs_match_resample->GetYaxis()->SetTitleOffset(1.3);
         }   
         if ( k >= 18 && k <= 23 ) {
            hs_match_resample->GetXaxis()->SetTitle("1 - #xi(RP)/#xi(#mu^{+}#mu^{-})");
            hs_match_resample->GetYaxis()->SetTitle("dN/d(1 - #xi(RP)/#xi(#mu^{+}#mu^{-}))");
            hs_match_resample->GetYaxis()->SetTitleOffset(1.3);
         }   
         if ( k == 24 || k == 25 ) {
            hs_match_resample->GetXaxis()->SetTitle("#xi(#mu^{+}#mu^{-})");
            hs_match_resample->GetYaxis()->SetTitle("dN/d#xi(#mu^{+}#mu^{-})");
            hs_match_resample->GetYaxis()->SetTitleOffset(1.3);
         }   
         h_match_data->Draw("SAME");
         h_match_new_resample->Draw("E2 SAME");
      }
      auto l_match_resample = new TLegend(0.925,0.925,0.725,0.725);
      if ( k >= 0 && k <= 25 ) {
         l_match_resample->AddEntry(h_match_data,"2017 Data","lep");
         l_match_resample->AddEntry(h_match_elastic_signal,"pp -> p #gamma#gamma p","f");
         l_match_resample->AddEntry(h_match_inel_el_signal,"pp -> p #gamma#gamma p*","f");
         if(k == 7 || k == 9 || k == 13 || k == 15 || k == 19 || k == 21) {
            l_match_resample->AddEntry(h_match_elastic_mixpu,"pp -> p #gamma#gamma p(*) mixed with pileup","f");
         }   
         l_match_resample->AddEntry(h_match_dy_resample,"Drell-Yan mixed with pileup","f");
         l_match_resample->AddEntry(h_match_new_resample,"Statistic Uncertainties","f");
         l_match_resample->Draw();
         pad_match_resample->RedrawAxis();
         writeExtraText = true;       // if extra text
         extraText  = "Preliminary";  // default extra text is "Preliminary"
         lumi_13TeV  = "18.34 fb^{-1}";  // default is "20.1 fb^{-1}"
         CMS_lumi( pad_match_resample, iPeriod, iPos );
         pad_match_resample->Update();
         c_match_resample->cd();
         gPad->Update();
         if ( k >= 18 && k <= 23 ){
            l_match_resample->SetX1NDC(0.4);
            l_match_resample->SetX2NDC(0.6);
         }
         gPad->Modified();
         //char const* name_match_resample = Form("comp_new/match_resample/%s_resample.png", hist_match[k]);
      }
      char const* name_match_resample = Form("comp_mixpu/match_resample/%s_resample.pdf", hist_match[k]);
      if ( k >= 0 && k <= 25 ) {
         c_match_resample->SaveAs(name_match_resample);
         c_match_resample->cd();
         c_match_resample->Close();
      }
   }
   return 0;
}
