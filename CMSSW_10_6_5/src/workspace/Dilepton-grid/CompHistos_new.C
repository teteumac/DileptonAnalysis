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

   char* hist[] = {"proton_xi_left_rp23","proton_xi_left_rp23_match","proton_xi_left_rp23_nprot","proton_xi_left_rp23_nprot_match","proton_xi_right_rp123","proton_xi_right_rp123_match","proton_xi_right_rp123_nprot","proton_xi_right_rp123_nprot_match","proton_xi_left_multi","proton_xi_left_multi_match","proton_xi_right_multi","proton_xi_right_multi_match","diff_proton_reco_pair_xi_left_rp23","diff_proton_reco_pair_xi_left_rp23_match","diff_proton_reco_pair_xi_left_rp23_nprot","diff_proton_reco_pair_xi_left_rp23_nprot_match","diff_proton_reco_pair_xi_right_rp123","diff_proton_reco_pair_xi_right_rp123_match","diff_proton_reco_pair_xi_right_rp123_nprot","diff_proton_reco_pair_xi_right_rp123_nprot_match","diff_proton_reco_pair_xi_left_multi","diff_proton_reco_pair_xi_left_multi_match","diff_proton_reco_pair_xi_right_multi","diff_proton_reco_pair_xi_right_multi_match","ratio_proton_reco_pair_xi_left_rp23","ratio_proton_reco_pair_xi_left_rp23_match","ratio_proton_reco_pair_xi_left_rp23_nprot","ratio_proton_reco_pair_xi_left_rp23_nprot_match","ratio_proton_reco_pair_xi_right_rp123","ratio_proton_reco_pair_xi_right_rp123_match","ratio_proton_reco_pair_xi_right_rp123_nprot","ratio_proton_reco_pair_xi_right_rp123_nprot_match","ratio_proton_reco_pair_xi_left_multi","ratio_proton_reco_pair_xi_left_multi_match","ratio_proton_reco_pair_xi_right_multi","ratio_proton_reco_pair_xi_right_multi_match"};

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
   TFile *f_dy_resample = new TFile("histos_MC/output_dy_resample_sigma_EG.root", "READ");
   TFile *f_data = new TFile("histos_data/output_data_sigma_limitRun.root", "READ");
	
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

   double scale_factor_elastic_x100 = xangle100*limit_lumi*0.017254036*1000 / n_events_h_elastic ; //
   double scale_factor_elastic_x110 = xangle110*limit_lumi*0.017254036*1000 / n_events_h_elastic ; //
   double scale_factor_elastic_x120 = xangle120*limit_lumi*0.017254036*1000 / n_events_h_elastic ; //
   double scale_factor_elastic_x130 = xangle130*limit_lumi*0.017254036*1000 / n_events_h_elastic ; //
   double scale_factor_elastic_x140 = xangle140*limit_lumi*0.017254036*1000 / n_events_h_elastic ; //
   double scale_factor_elastic_x150 = xangle150*limit_lumi*0.017254036*1000 / n_events_h_elastic ; //
   double scale_factor_inel_el_x100 = xangle100*limit_lumi*0.025643100*1000 / n_events_h_inel_el ; //
   double scale_factor_inel_el_x110 = xangle110*limit_lumi*0.025643100*1000 / n_events_h_inel_el ; //
   double scale_factor_inel_el_x120 = xangle120*limit_lumi*0.025643100*1000 / n_events_h_inel_el ; //
   double scale_factor_inel_el_x130 = xangle130*limit_lumi*0.025643100*1000 / n_events_h_inel_el ; //
   double scale_factor_inel_el_x140 = xangle140*limit_lumi*0.025643100*1000 / n_events_h_inel_el ; //
   double scale_factor_inel_el_x150 = xangle150*limit_lumi*0.025643100*1000 / n_events_h_inel_el ; //
   double scale_factor_dy = limit_lumi*5334000 / n_events_h_dy; 
   double scale_factor_dy_resample = limit_lumi*5334000 / ( n_events_h_dy*number_of_samples ) ; 
   double scale_factor_dy_prot_sel = event_selection*limit_lumi*5334000 / n_events_h_dy; 
   double scale_factor_dy_resample_prot_sel = event_selection*limit_lumi*5334000 / ( n_events_h_dy*number_of_samples ) ; 

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

   TCanvas *c = new TCanvas("c","",0,0,1200,1000);
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

   TCanvas *c_resample = new TCanvas("c_resample","",0,0,1200,1000);
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

   }
   return 0;
   }
