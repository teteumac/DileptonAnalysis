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

int CompHistos_re()
{
   gStyle->SetOptStat(0);

   char* hist[] = {"multiplicity_0prot_cut"};

   //setTDRStyle();

   size_t Nhist = sizeof(hist)/sizeof(hist[0]);		

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
   double scale_factor_dy_prot_sel = event_selection*limit_lumi*5334000 / n_events_h_dy; 

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
      TH1 *h_data = 0; f_data->GetObject(hist[i], h_data);

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
      h_dy->Scale(scale_factor_dy);

      h_elastic_x100->Add(h_elastic_x110); 
      h_elastic_x100->Add(h_elastic_x120); 
      h_elastic_x100->Add(h_elastic_x130); 
      h_elastic_x100->Add(h_elastic_x140); 
      h_elastic_x100->Add(h_elastic_x150); 
      h_elastic_x100->Add(h_inel_el_x100); 
      h_elastic_x100->Add(h_inel_el_x110); 
      h_elastic_x100->Add(h_inel_el_x120); 
      h_elastic_x100->Add(h_inel_el_x130); 
      h_elastic_x100->Add(h_inel_el_x140); 
      h_elastic_x100->Add(h_inel_el_x150); 
      
      TH1F *h_signal = (TH1F*)h_elastic_x100->Clone("h_signal"); 
      TH1F *h_data_sub = (TH1F*)h_data->Clone("h_data_sub"); 

      h_elastic_x100->Add(h_dy);

      h_elastic_x100->Scale(1/h_elastic_x100->Integral());
      h_data->Scale(1/h_data->Integral());
      h_elastic_x100->Divide(h_data);

      h_data_sub->Add(h_signal, -1);
      h_data_sub->Scale(1/h_data_sub->Integral());
      h_dy->Scale(1/h_dy->Integral());
      h_dy->Divide(h_data_sub);
   
      h_elastic_x100->SetTitle("sum MC / data");
      h_dy->SetTitle("bkg MC / data - signal MC");

      TFile* f = new TFile("reweight/reweight_multi.root", "RECREATE");
      h_elastic_x100->Write();
      h_dy->Write();
   }
   return 0;
}
