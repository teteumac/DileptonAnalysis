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

#define PI 3.14159265358979323846

#include <iostream>
#include <vector>
#include <set>
using namespace std;

int CompHistos()
{
		  gStyle->SetOptStat(0);

		  //char* const hist[] = {"mumu_mass", "mumu_pt", "mumu_y", "xi_left", "xi_right"}; 

		  //size_t Nhist = sizeof(hist)/sizeof(hist[0]);

		  //TFile *f_elastic_x120 = new TFile("histos/output_elastic_xangle120_cut.root");
		  TFile *f_elastic_x130 = new TFile("histos/output_elastic_xangle130_cut.root");
		  //TFile *f_elastic_x140 = new TFile("histos/output_elastic_xangle140_cut.root");
		  //TFile *f_elastic_x150 = new TFile("histos/output_elastic_xangle150_cut.root");
		  //TFile *f_inel_el_x120 = new TFile("histos/output_inel-el_xangle120_cut.root");
		  TFile *f_inel_el_x130 = new TFile("histos/output_inel-el_xangle130_cut.root");
		  //TFile *f_inel_el_x140 = new TFile("histos/output_inel-el_xangle140_cut.root");
		  //TFile *f_inel_el_x150 = new TFile("histos/output_inel-el_xangle150_cut.root");
		  TFile *f_dy = new TFile("histos/output_dy_cut.root");
		  TFile *f_data = new TFile("histos/output_data_cut.root");

		  //for (int i = 0; i < Nhist; i++) {

		  double scale_factor_elastic_x120, scale_factor_elastic_x130, scale_factor_elastic_x140, scale_factor_elastic_x150;
		  double scale_factor_inel_el_x120, scale_factor_inel_el_x130, scale_factor_inel_el_x140, scale_factor_inel_el_x150;
		  double scale_factor_dy;
		  //double eff_trigger_elastic_x120 = 1;
		  double eff_trigger_elastic_x130 = 1;
		  //double eff_trigger_elastic_x140 = 1;
		  //double eff_trigger_elastic_x150 = 1;
		  //double eff_trigger_inel_el_x120 = 1;
		  double eff_trigger_inel_el_x130 = 1;
		  //double eff_trigger_inel_el_x140 = 1;
		  //double eff_trigger_inel_el_x150 = 1;
		  double eff_trigger_dy = 1;

		  //TH1* h_elastic_x120_mass = 0;					
		  TH1* h_elastic_x130_mass = 0;
		  //TH1* h_elastic_x140_mass = 0;
		  //TH1* h_elastic_x150_mass = 0;
		  //TH1* h_inel_el_x120_mass = 0;					
		  TH1* h_inel_el_x130_mass = 0;
		  //TH1* h_inel_el_x140_mass = 0;
		  //TH1* h_inel_el_x150_mass = 0;
		  TH1* h_dy_mass = 0;
		  TH1* h_data_mass = 0;
		  //TH1* h_elastic_x120_pt = 0;					
		  TH1* h_elastic_x130_pt = 0;
		  //TH1* h_elastic_x140_pt = 0;
		  //TH1* h_elastic_x150_pt = 0;
		  //TH1* h_inel_el_x120_pt = 0;					
		  TH1* h_inel_el_x130_pt = 0;
		  //TH1* h_inel_el_x140_pt = 0;
		  //TH1* h_inel_el_x150_pt = 0;
		  TH1* h_dy_pt = 0;
		  TH1* h_data_pt = 0;
		  //TH1* h_elastic_x120_y = 0;					
		  TH1* h_elastic_x130_y = 0;
		  //TH1* h_elastic_x140_y = 0;
		  //TH1* h_elastic_x150_y = 0;
		  //TH1* h_inel_el_x120_y = 0;					
		  TH1* h_inel_el_x130_y = 0;
		  //TH1* h_inel_el_x140_y = 0;
		  //TH1* h_inel_el_x150_y = 0;
		  TH1* h_dy_y = 0;
		  TH1* h_data_y = 0;
		  TH1* h_elastic_x130_n_ext_fromPV = 0;
		  TH1* h_inel_el_x130_n_ext_fromPV = 0;
		  TH1* h_dy_n_ext_fromPV = 0;
		  TH1* h_data_n_ext_fromPV = 0;
		  TH1* h_elastic_x130_n_ext_fromPV_2 = 0;
		  TH1* h_inel_el_x130_n_ext_fromPV_2 = 0;
		  TH1* h_dy_n_ext_fromPV_2 = 0;
		  TH1* h_data_n_ext_fromPV_2 = 0;
		  TH1* h_elastic_x130_n_ext_fromPV_3 = 0;
		  TH1* h_inel_el_x130_n_ext_fromPV_3 = 0;
		  TH1* h_dy_n_ext_fromPV_3 = 0;
		  TH1* h_data_n_ext_fromPV_3 = 0;
		  TH1* h_elastic_x130_n_ext_fromPV_dz02 = 0;
		  TH1* h_inel_el_x130_n_ext_fromPV_dz02 = 0;
		  TH1* h_dy_n_ext_fromPV_dz02 = 0;
		  TH1* h_data_n_ext_fromPV_dz02 = 0;
		  TH1* h_elastic_x130_n_ext_fromPV_2_dz02 = 0;
		  TH1* h_inel_el_x130_n_ext_fromPV_2_dz02 = 0;
		  TH1* h_dy_n_ext_fromPV_2_dz02 = 0;
		  TH1* h_data_n_ext_fromPV_2_dz02 = 0;
		  TH1* h_elastic_x130_n_ext_fromPV_3_dz02 = 0;
		  TH1* h_inel_el_x130_n_ext_fromPV_3_dz02 = 0;
		  TH1* h_dy_n_ext_fromPV_3_dz02 = 0;
		  TH1* h_data_n_ext_fromPV_3_dz02 = 0;
		  TH1* h_elastic_x130_n_ext_fromPV_dz01 = 0;
		  TH1* h_inel_el_x130_n_ext_fromPV_dz01 = 0;
		  TH1* h_dy_n_ext_fromPV_dz01 = 0;
		  TH1* h_data_n_ext_fromPV_dz01 = 0;
		  TH1* h_elastic_x130_n_ext_fromPV_2_dz01 = 0;
		  TH1* h_inel_el_x130_n_ext_fromPV_2_dz01 = 0;
		  TH1* h_dy_n_ext_fromPV_2_dz01 = 0;
		  TH1* h_data_n_ext_fromPV_2_dz01 = 0;
		  TH1* h_elastic_x130_n_ext_fromPV_3_dz01 = 0;
		  TH1* h_inel_el_x130_n_ext_fromPV_3_dz01 = 0;
		  TH1* h_dy_n_ext_fromPV_3_dz01 = 0;
		  TH1* h_data_n_ext_fromPV_3_dz01 = 0;

		  //f_elastic_x120->GetObject("mumu_mass", h_elastic_x120_mass);
		  f_elastic_x130->GetObject("mumu_mass", h_elastic_x130_mass);
		  //f_elastic_x140->GetObject("mumu_mass", h_elastic_x140_mass);
		  //f_elastic_x150->GetObject("mumu_mass", h_elastic_x150_mass);
		  //f_inel_el_x120->GetObject("mumu_mass", h_inel_el_x120_mass);
		  f_inel_el_x130->GetObject("mumu_mass", h_inel_el_x130_mass);
		  //f_inel_el_x140->GetObject("mumu_mass", h_inel_el_x140_mass);
		  //f_inel_el_x150->GetObject("mumu_mass", h_inel_el_x150_mass);
		  //f_elastic_x120->GetObject("mumu_pt", h_elastic_x120_pt);
		  f_dy->GetObject("mumu_mass", h_dy_mass);
		  f_data->GetObject("mumu_mass", h_data_mass);
		  //f_elastic_x120->GetObject("mumu_pt", h_elastic_x120_pt);
		  f_elastic_x130->GetObject("mumu_pt", h_elastic_x130_pt);
		  //f_elastic_x140->GetObject("mumu_pt", h_elastic_x140_pt);
		  //f_elastic_x150->GetObject("mumu_pt", h_elastic_x150_pt);
		  //f_inel_el_x120->GetObject("mumu_pt", h_inel_el_x120_pt);
		  f_inel_el_x130->GetObject("mumu_pt", h_inel_el_x130_pt);
		  //f_inel_el_x140->GetObject("mumu_pt", h_inel_el_x140_pt);
		  //f_inel_el_x150->GetObject("mumu_pt", h_inel_el_x150_pt);
		  f_dy->GetObject("mumu_pt", h_dy_pt);
		  f_data->GetObject("mumu_pt", h_data_pt);
		  //f_elastic_x120->GetObject("mumu_y", h_elastic_x120_y);
		  f_elastic_x130->GetObject("mumu_y", h_elastic_x130_y);
		  //f_elastic_x140->GetObject("mumu_y", h_elastic_x140_y);
		  //f_elastic_x150->GetObject("mumu_y", h_elastic_x150_y);
		  //f_inel_el_x120->GetObject("mumu_y", h_inel_el_x120_y);
		  f_inel_el_x130->GetObject("mumu_y", h_inel_el_x130_y);
		  //f_inel_el_x140->GetObject("mumu_y", h_inel_el_x140_y);
		  //f_inel_el_x150->GetObject("mumu_y", h_inel_el_x150_y);
		  f_dy->GetObject("mumu_y", h_dy_y);
		  f_data->GetObject("mumu_y", h_data_y);
		  f_elastic_x130->GetObject("n_ext_fromPV", h_elastic_x130_n_ext_fromPV);
		  f_inel_el_x130->GetObject("n_ext_fromPV", h_inel_el_x130_n_ext_fromPV);
		  f_dy->GetObject("n_ext_fromPV", h_dy_n_ext_fromPV);
		  f_data->GetObject("n_ext_fromPV", h_data_n_ext_fromPV);
		  f_elastic_x130->GetObject("n_ext_fromPV_2", h_elastic_x130_n_ext_fromPV_2);
		  f_inel_el_x130->GetObject("n_ext_fromPV_2", h_inel_el_x130_n_ext_fromPV_2);
		  f_dy->GetObject("n_ext_fromPV_2", h_dy_n_ext_fromPV_2);
		  f_data->GetObject("n_ext_fromPV_2", h_data_n_ext_fromPV_2);
		  f_elastic_x130->GetObject("n_ext_fromPV_3", h_elastic_x130_n_ext_fromPV_3);
		  f_inel_el_x130->GetObject("n_ext_fromPV_3", h_inel_el_x130_n_ext_fromPV_3);
		  f_dy->GetObject("n_ext_fromPV_3", h_dy_n_ext_fromPV_3);
		  f_data->GetObject("n_ext_fromPV_3", h_data_n_ext_fromPV_3);
		  f_elastic_x130->GetObject("n_ext_fromPV_dz02", h_elastic_x130_n_ext_fromPV_dz02);
		  f_inel_el_x130->GetObject("n_ext_fromPV_dz02", h_inel_el_x130_n_ext_fromPV_dz02);
		  f_dy->GetObject("n_ext_fromPV_dz02", h_dy_n_ext_fromPV_dz02);
		  f_data->GetObject("n_ext_fromPV_dz02", h_data_n_ext_fromPV_dz02);
		  f_elastic_x130->GetObject("n_ext_fromPV_2_dz02", h_elastic_x130_n_ext_fromPV_2_dz02);
		  f_inel_el_x130->GetObject("n_ext_fromPV_2_dz02", h_inel_el_x130_n_ext_fromPV_2_dz02);
		  f_dy->GetObject("n_ext_fromPV_2_dz02", h_dy_n_ext_fromPV_2_dz02);
		  f_data->GetObject("n_ext_fromPV_2_dz02", h_data_n_ext_fromPV_2_dz02);
		  f_elastic_x130->GetObject("n_ext_fromPV_3_dz02", h_elastic_x130_n_ext_fromPV_3_dz02);
		  f_inel_el_x130->GetObject("n_ext_fromPV_3_dz02", h_inel_el_x130_n_ext_fromPV_3_dz02);
		  f_dy->GetObject("n_ext_fromPV_3_dz02", h_dy_n_ext_fromPV_3_dz02);
		  f_data->GetObject("n_ext_fromPV_3_dz02", h_data_n_ext_fromPV_3_dz02);
		  f_elastic_x130->GetObject("n_ext_fromPV_dz01", h_elastic_x130_n_ext_fromPV_dz01);
		  f_inel_el_x130->GetObject("n_ext_fromPV_dz01", h_inel_el_x130_n_ext_fromPV_dz01);
		  f_dy->GetObject("n_ext_fromPV_dz01", h_dy_n_ext_fromPV_dz01);
		  f_data->GetObject("n_ext_fromPV_dz01", h_data_n_ext_fromPV_dz01);
		  f_elastic_x130->GetObject("n_ext_fromPV_2_dz01", h_elastic_x130_n_ext_fromPV_2_dz01);
		  f_inel_el_x130->GetObject("n_ext_fromPV_2_dz01", h_inel_el_x130_n_ext_fromPV_2_dz01);
		  f_dy->GetObject("n_ext_fromPV_2_dz01", h_dy_n_ext_fromPV_2_dz01);
		  f_data->GetObject("n_ext_fromPV_2_dz01", h_data_n_ext_fromPV_2_dz01);
		  f_elastic_x130->GetObject("n_ext_fromPV_3_dz01", h_elastic_x130_n_ext_fromPV_3_dz01);
		  f_inel_el_x130->GetObject("n_ext_fromPV_3_dz01", h_inel_el_x130_n_ext_fromPV_3_dz01);
		  f_dy->GetObject("n_ext_fromPV_3_dz01", h_dy_n_ext_fromPV_3_dz01);
		  f_data->GetObject("n_ext_fromPV_3_dz01", h_data_n_ext_fromPV_3_dz01);

        //double n_events_h_elastic_x120 = 200000;
        double n_events_h_elastic_x130 = 200000;
        //double n_events_h_elastic_x140 = 200000;
        //double n_events_h_elastic_x150 = 200000;
		  //double n_events_h_elastic = n_events_h_elastic_x120 + n_events_h_elastic_x130 + n_events_h_elastic_x140 + n_events_h_elastic_x150;
        //double n_events_h_inel_el_x120 = 200000;
        double n_events_h_inel_el_x130 = 200000;
        //double n_events_h_inel_el_x140 = 200000;
        //double n_events_h_inel_el_x150 = 200000;
		  //double n_events_h_inel_el = n_events_h_inel_el_x120 + n_events_h_inel_el_x130 + n_events_h_inel_el_x140 + n_events_h_inel_el_x150;
        double n_events_h_dy = 48675378;

		  //xsec1 = eff_trigger1*37.022*0.017254036*1000*(h1->GetEntries()/2000) ; //
		  //xsec2 = eff_trigger2*37.022*0.025643100*1000*(h2->GetEntries()/2000) ;//
		  //scale_factor_elastic_x120 = eff_trigger_elastic_x120*37.022*0.017254036*1000 / n_events_h_elastic_x120 ; //
		  scale_factor_elastic_x130 = eff_trigger_elastic_x130*37.022*0.017254036*1000 / n_events_h_elastic_x130 ; //
		  //scale_factor_elastic_x140 = eff_trigger_elastic_x140*37.022*0.017254036*1000 / n_events_h_elastic_x140 ; //
		  //scale_factor_elastic_x150 = eff_trigger_elastic_x150*37.022*0.017254036*1000 / n_events_h_elastic_x150 ; //
		  //scale_factor_inel_el_x120 = eff_trigger_inel_el_x120*37.022*0.025643100*1000 / n_events_h_inel_el_x120 ; //
		  scale_factor_inel_el_x130 = eff_trigger_inel_el_x130*37.022*0.025643100*1000 / n_events_h_inel_el_x130 ; //
		  //scale_factor_inel_el_x140 = eff_trigger_inel_el_x140*37.022*0.025643100*1000 / n_events_h_inel_el_x140 ; //
		  //scale_factor_inel_el_x150 = eff_trigger_inel_el_x150*37.022*0.025643100*1000 / n_events_h_inel_el_x150 ; //
		  scale_factor_dy = eff_trigger_dy*37.022*5334000 / n_events_h_dy ; //

		  //h_elastic_x120_mass->SetLineColor(kBlue);
		  h_elastic_x130_mass->SetLineColor(kBlue);
		  //h_elastic_x140_mass->SetLineColor(kBlue);
		  //h_elastic_x150_mass->SetLineColor(kBlue);
		  //h_inel_el_x120_mass->SetLineColor(kGreen);
		  h_inel_el_x130_mass->SetLineColor(kGreen);
		  //h_inel_el_x140_mass->SetLineColor(kGreen);
		  //h_inel_el_x150_mass->SetLineColor(kGreen);
		  h_dy_mass->SetLineColor(kRed);
		  //h_elastic_x120_mass->SetFillColor(kBlue);
		  h_elastic_x130_mass->SetFillColor(kBlue);
		  //h_elastic_x140_mass->SetFillColor(kBlue);
		  //h_elastic_x150_mass->SetFillColor(kBlue);
		  //h_inel_el_x120_mass->SetFillColor(kGreen);
		  h_inel_el_x130_mass->SetFillColor(kGreen);
		  //h_inel_el_x140_mass->SetFillColor(kGreen);
		  //h_inel_el_x150_mass->SetFillColor(kGreen);
		  h_dy_mass->SetFillColor(kRed);
		  h_data_mass->SetMarkerStyle(8);
		  h_data_mass->Sumw2();
		  //h_elastic_x120_pt->SetLineColor(kBlue);
		  h_elastic_x130_pt->SetLineColor(kBlue);
		  //h_elastic_x140_pt->SetLineColor(kBlue);
		  //h_elastic_x150_pt->SetLineColor(kBlue);
		  //h_inel_el_x120_pt->SetLineColor(kGreen);
		  h_inel_el_x130_pt->SetLineColor(kGreen);
		  //h_inel_el_x140_pt->SetLineColor(kGreen);
		  //h_inel_el_x150_pt->SetLineColor(kGreen);
		  h_dy_pt->SetLineColor(kRed);
		  //h_elastic_x120_pt->SetFillColor(kBlue);
		  h_elastic_x130_pt->SetFillColor(kBlue);
		  //h_elastic_x140_pt->SetFillColor(kBlue);
		  //h_elastic_x150_pt->SetFillColor(kBlue);
		  //h_inel_el_x120_pt->SetFillColor(kGreen);
		  h_inel_el_x130_pt->SetFillColor(kGreen);
		  //h_inel_el_x140_pt->SetFillColor(kGreen);
		  //h_inel_el_x150_pt->SetFillColor(kGreen);
		  h_dy_pt->SetFillColor(kRed);
		  h_data_pt->SetMarkerStyle(8);
		  h_data_pt->Sumw2();
		  //h_elastic_x120_y->SetLineColor(kBlue);
		  h_elastic_x130_y->SetLineColor(kBlue);
		  //h_elastic_x140_y->SetLineColor(kBlue);
		  //h_elastic_x150_y->SetLineColor(kBlue);
		  //h_inel_el_x120_y->SetLineColor(kGreen);
		  h_inel_el_x130_y->SetLineColor(kGreen);
		  //h_inel_el_x140_y->SetLineColor(kGreen);
		  //h_inel_el_x150_y->SetLineColor(kGreen);
		  h_dy_y->SetLineColor(kRed);
		  //h_elastic_x120_y->SetFillColor(kBlue);
		  h_elastic_x130_y->SetFillColor(kBlue);
		  //h_elastic_x140_y->SetFillColor(kBlue);
		  //h_elastic_x150_y->SetFillColor(kBlue);
		  //h_inel_el_x120_y->SetFillColor(kGreen);
		  h_inel_el_x130_y->SetFillColor(kGreen);
		  //h_inel_el_x140_y->SetFillColor(kGreen);
		  //h_inel_el_x150_y->SetFillColor(kGreen);
		  h_dy_y->SetFillColor(kRed);
		  h_data_y->SetMarkerStyle(8);
		  h_data_y->Sumw2();
		  h_elastic_x130_n_ext_fromPV->SetLineColor(kBlue);
		  h_inel_el_x130_n_ext_fromPV->SetLineColor(kGreen);
		  h_dy_n_ext_fromPV->SetLineColor(kRed);
		  h_elastic_x130_n_ext_fromPV->SetFillColor(kBlue);
		  h_inel_el_x130_n_ext_fromPV->SetFillColor(kGreen);
		  h_dy_n_ext_fromPV->SetFillColor(kRed);
		  h_data_n_ext_fromPV->SetMarkerStyle(8);
		  h_data_n_ext_fromPV->Sumw2();
		  h_elastic_x130_n_ext_fromPV_2->SetLineColor(kBlue);
		  h_inel_el_x130_n_ext_fromPV_2->SetLineColor(kGreen);
		  h_dy_n_ext_fromPV_2->SetLineColor(kRed);
		  h_elastic_x130_n_ext_fromPV_2->SetFillColor(kBlue);
		  h_inel_el_x130_n_ext_fromPV_2->SetFillColor(kGreen);
		  h_dy_n_ext_fromPV_2->SetFillColor(kRed);
		  h_data_n_ext_fromPV_2->SetMarkerStyle(8);
		  h_data_n_ext_fromPV_2->Sumw2();
		  h_elastic_x130_n_ext_fromPV_3->SetLineColor(kBlue);
		  h_inel_el_x130_n_ext_fromPV_3->SetLineColor(kGreen);
		  h_dy_n_ext_fromPV_3->SetLineColor(kRed);
		  h_elastic_x130_n_ext_fromPV_3->SetFillColor(kBlue);
		  h_inel_el_x130_n_ext_fromPV_3->SetFillColor(kGreen);
		  h_dy_n_ext_fromPV_3->SetFillColor(kRed);
		  h_data_n_ext_fromPV_3->SetMarkerStyle(8);
		  h_data_n_ext_fromPV_3->Sumw2();
		  h_elastic_x130_n_ext_fromPV_dz02->SetLineColor(kBlue);
		  h_inel_el_x130_n_ext_fromPV_dz02->SetLineColor(kGreen);
		  h_dy_n_ext_fromPV_dz02->SetLineColor(kRed);
		  h_elastic_x130_n_ext_fromPV_dz02->SetFillColor(kBlue);
		  h_inel_el_x130_n_ext_fromPV_dz02->SetFillColor(kGreen);
		  h_dy_n_ext_fromPV_dz02->SetFillColor(kRed);
		  h_data_n_ext_fromPV_dz02->SetMarkerStyle(8);
		  h_data_n_ext_fromPV_dz02->Sumw2();
		  h_elastic_x130_n_ext_fromPV_2_dz02->SetLineColor(kBlue);
		  h_inel_el_x130_n_ext_fromPV_2_dz02->SetLineColor(kGreen);
		  h_dy_n_ext_fromPV_2_dz02->SetLineColor(kRed);
		  h_elastic_x130_n_ext_fromPV_2_dz02->SetFillColor(kBlue);
		  h_inel_el_x130_n_ext_fromPV_2_dz02->SetFillColor(kGreen);
		  h_dy_n_ext_fromPV_2_dz02->SetFillColor(kRed);
		  h_data_n_ext_fromPV_2_dz02->SetMarkerStyle(8);
		  h_data_n_ext_fromPV_2_dz02->Sumw2();
		  h_elastic_x130_n_ext_fromPV_3_dz02->SetLineColor(kBlue);
		  h_inel_el_x130_n_ext_fromPV_3_dz02->SetLineColor(kGreen);
		  h_dy_n_ext_fromPV_3_dz02->SetLineColor(kRed);
		  h_elastic_x130_n_ext_fromPV_3_dz02->SetFillColor(kBlue);
		  h_inel_el_x130_n_ext_fromPV_3_dz02->SetFillColor(kGreen);
		  h_dy_n_ext_fromPV_3_dz02->SetFillColor(kRed);
		  h_data_n_ext_fromPV_3_dz02->SetMarkerStyle(8);
		  h_data_n_ext_fromPV_3_dz02->Sumw2();
		  h_elastic_x130_n_ext_fromPV_dz01->SetLineColor(kBlue);
		  h_inel_el_x130_n_ext_fromPV_dz01->SetLineColor(kGreen);
		  h_dy_n_ext_fromPV_dz01->SetLineColor(kRed);
		  h_elastic_x130_n_ext_fromPV_dz01->SetFillColor(kBlue);
		  h_inel_el_x130_n_ext_fromPV_dz01->SetFillColor(kGreen);
		  h_dy_n_ext_fromPV_dz01->SetFillColor(kRed);
		  h_data_n_ext_fromPV_dz01->SetMarkerStyle(8);
		  h_data_n_ext_fromPV_dz01->Sumw2();
		  h_elastic_x130_n_ext_fromPV_2_dz01->SetLineColor(kBlue);
		  h_inel_el_x130_n_ext_fromPV_2_dz01->SetLineColor(kGreen);
		  h_dy_n_ext_fromPV_2_dz01->SetLineColor(kRed);
		  h_elastic_x130_n_ext_fromPV_2_dz01->SetFillColor(kBlue);
		  h_inel_el_x130_n_ext_fromPV_2_dz01->SetFillColor(kGreen);
		  h_dy_n_ext_fromPV_2_dz01->SetFillColor(kRed);
		  h_data_n_ext_fromPV_2_dz01->SetMarkerStyle(8);
		  h_data_n_ext_fromPV_2_dz01->Sumw2();
		  h_elastic_x130_n_ext_fromPV_3_dz01->SetLineColor(kBlue);
		  h_inel_el_x130_n_ext_fromPV_3_dz01->SetLineColor(kGreen);
		  h_dy_n_ext_fromPV_3_dz01->SetLineColor(kRed);
		  h_elastic_x130_n_ext_fromPV_3_dz01->SetFillColor(kBlue);
		  h_inel_el_x130_n_ext_fromPV_3_dz01->SetFillColor(kGreen);
		  h_dy_n_ext_fromPV_3_dz01->SetFillColor(kRed);
		  h_data_n_ext_fromPV_3_dz01->SetMarkerStyle(8);
		  h_data_n_ext_fromPV_3_dz01->Sumw2();
		  
		  //h_elastic_x120_mass->Scale(scale_factor_elastic_x120);
		  h_elastic_x130_mass->Scale(scale_factor_elastic_x130);
		  //h_elastic_x140_mass->Scale(scale_factor_elastic_x140);
		  //h_elastic_x150_mass->Scale(scale_factor_elastic_x150);
		  //h_inel_el_x120_mass->Scale(scale_factor_inel_el_x120);
		  h_inel_el_x130_mass->Scale(scale_factor_inel_el_x130);
		  //h_inel_el_x140_mass->Scale(scale_factor_inel_el_x140);
		  //h_inel_el_x150_mass->Scale(scale_factor_inel_el_x150);
		  h_dy_mass->Scale(scale_factor_dy);
		  //h_elastic_x120_pt->Scale(scale_factor_elastic_x120);
		  h_elastic_x130_pt->Scale(scale_factor_elastic_x130);
		  //h_elastic_x140_pt->Scale(scale_factor_elastic_x140);
		  //h_elastic_x150_pt->Scale(scale_factor_elastic_x150);
		  //h_inel_el_x120_pt->Scale(scale_factor_inel_el_x120);
		  h_inel_el_x130_pt->Scale(scale_factor_inel_el_x130);
		  //h_inel_el_x140_pt->Scale(scale_factor_inel_el_x140);
		  //h_inel_el_x150_pt->Scale(scale_factor_inel_el_x150);
		  h_dy_pt->Scale(scale_factor_dy);
		  //h_elastic_x120_y->Scale(scale_factor_elastic_x120);
		  h_elastic_x130_y->Scale(scale_factor_elastic_x130);
		  //h_elastic_x140_y->Scale(scale_factor_elastic_x140);
		  //h_elastic_x150_y->Scale(scale_factor_elastic_x150);
		  //h_inel_el_x120_y->Scale(scale_factor_inel_el_x120);
		  h_inel_el_x130_y->Scale(scale_factor_inel_el_x130);
		  //h_inel_el_x140_y->Scale(scale_factor_inel_el_x140);
		  //h_inel_el_x150_y->Scale(scale_factor_inel_el_x150);
		  h_dy_y->Scale(scale_factor_dy);
		  h_elastic_x130_n_ext_fromPV->Scale(scale_factor_elastic_x130);
		  h_inel_el_x130_n_ext_fromPV->Scale(scale_factor_inel_el_x130);
		  h_dy_n_ext_fromPV->Scale(scale_factor_dy);
		  h_elastic_x130_n_ext_fromPV_2->Scale(scale_factor_elastic_x130);
		  h_inel_el_x130_n_ext_fromPV_2->Scale(scale_factor_inel_el_x130);
		  h_dy_n_ext_fromPV_2->Scale(scale_factor_dy);
		  h_elastic_x130_n_ext_fromPV_3->Scale(scale_factor_elastic_x130);
		  h_inel_el_x130_n_ext_fromPV_3->Scale(scale_factor_inel_el_x130);
		  h_dy_n_ext_fromPV_3->Scale(scale_factor_dy);
		  h_elastic_x130_n_ext_fromPV_dz02->Scale(scale_factor_elastic_x130);
		  h_inel_el_x130_n_ext_fromPV_dz02->Scale(scale_factor_inel_el_x130);
		  h_dy_n_ext_fromPV_dz02->Scale(scale_factor_dy);
		  h_elastic_x130_n_ext_fromPV_2_dz02->Scale(scale_factor_elastic_x130);
		  h_inel_el_x130_n_ext_fromPV_2_dz02->Scale(scale_factor_inel_el_x130);
		  h_dy_n_ext_fromPV_2_dz02->Scale(scale_factor_dy);
		  h_elastic_x130_n_ext_fromPV_3_dz02->Scale(scale_factor_elastic_x130);
		  h_inel_el_x130_n_ext_fromPV_3_dz02->Scale(scale_factor_inel_el_x130);
		  h_dy_n_ext_fromPV_3_dz02->Scale(scale_factor_dy);
		  h_elastic_x130_n_ext_fromPV_dz01->Scale(scale_factor_elastic_x130);
		  h_inel_el_x130_n_ext_fromPV_dz01->Scale(scale_factor_inel_el_x130);
		  h_dy_n_ext_fromPV_dz01->Scale(scale_factor_dy);
		  h_elastic_x130_n_ext_fromPV_2_dz01->Scale(scale_factor_elastic_x130);
		  h_inel_el_x130_n_ext_fromPV_2_dz01->Scale(scale_factor_inel_el_x130);
		  h_dy_n_ext_fromPV_2_dz01->Scale(scale_factor_dy);
		  h_elastic_x130_n_ext_fromPV_3_dz01->Scale(scale_factor_elastic_x130);
		  h_inel_el_x130_n_ext_fromPV_3_dz01->Scale(scale_factor_inel_el_x130);
		  h_dy_n_ext_fromPV_3_dz01->Scale(scale_factor_dy);
		  
        //double integral_h_elastic_x120_mass = h_elastic_x120_mass->Integral( 0, ( h_elastic_x120_mass->GetNbinsX() + 1 ) ); // With under and overflow
        double integral_h_elastic_x130_mass = h_elastic_x130_mass->Integral( 0, ( h_elastic_x130_mass->GetNbinsX() + 1 ) ); // With under and overflow
        //double integral_h_elastic_x140_mass = h_elastic_x140_mass->Integral( 0, ( h_elastic_x140_mass->GetNbinsX() + 1 ) ); // With under and overflow
        //double integral_h_elastic_x150_mass = h_elastic_x150_mass->Integral( 0, ( h_elastic_x150_mass->GetNbinsX() + 1 ) ); // With under and overflow
        //double integral_h_inel_el_x120_mass = h_inel_el_x120_mass->Integral( 0, ( h_inel_el_x120_mass->GetNbinsX() + 1 ) ); // With under and overflow
        double integral_h_inel_el_x130_mass = h_inel_el_x130_mass->Integral( 0, ( h_inel_el_x130_mass->GetNbinsX() + 1 ) ); // With under and overflow
        //double integral_h_inel_el_x140_mass = h_inel_el_x140_mass->Integral( 0, ( h_inel_el_x140_mass->GetNbinsX() + 1 ) ); // With under and overflow
        //double integral_h_inel_el_x150_mass = h_inel_el_x150_mass->Integral( 0, ( h_inel_el_x150_mass->GetNbinsX() + 1 ) ); // With under and overflow
        double integral_h_dy_mass = h_dy_mass->Integral( 0, ( h_dy_mass->GetNbinsX() + 1 ) ); // With under and overflow
        double sum_integral_mass = integral_h_elastic_x130_mass + integral_h_inel_el_x130_mass + integral_h_dy_mass;
        double scale_data_mass = h_data_mass->GetEntries() / sum_integral_mass ;
        cout << "Scale factor mass data normalization: " << scale_data_mass << endl;        
        //double integral_h_elastic_x120_pt = h_elastic_x120_pt->Integral( 0, ( h_elastic_x120_pt->GetNbinsX() + 1 ) ); // With under and overflow
        double integral_h_elastic_x130_pt = h_elastic_x130_pt->Integral( 0, ( h_elastic_x130_pt->GetNbinsX() + 1 ) ); // With under and overflow
        //double integral_h_elastic_x140_pt = h_elastic_x140_pt->Integral( 0, ( h_elastic_x140_pt->GetNbinsX() + 1 ) ); // With under and overflow
        //double integral_h_elastic_x150_pt = h_elastic_x150_pt->Integral( 0, ( h_elastic_x150_pt->GetNbinsX() + 1 ) ); // With under and overflow
        //double integral_h_inel_el_x120_pt = h_inel_el_x120_pt->Integral( 0, ( h_inel_el_x120_pt->GetNbinsX() + 1 ) ); // With under and overflow
        double integral_h_inel_el_x130_pt = h_inel_el_x130_pt->Integral( 0, ( h_inel_el_x130_pt->GetNbinsX() + 1 ) ); // With under and overflow
        //double integral_h_inel_el_x140_pt = h_inel_el_x140_pt->Integral( 0, ( h_inel_el_x140_pt->GetNbinsX() + 1 ) ); // With under and overflow
        //double integral_h_inel_el_x150_pt = h_inel_el_x150_pt->Integral( 0, ( h_inel_el_x150_pt->GetNbinsX() + 1 ) ); // With under and overflow
        double integral_h_dy_pt = h_dy_pt->Integral( 0, ( h_dy_pt->GetNbinsX() + 1 ) ); // With under and overflow
        double sum_integral_pt = integral_h_elastic_x130_pt + integral_h_inel_el_x130_pt + integral_h_dy_pt;
        double scale_data_pt = h_data_pt->GetEntries() / sum_integral_pt ;
        cout << "Scale factor pt data normalization: " << scale_data_pt << endl;        
        //double integral_h_elastic_x120_y = h_elastic_x120_y->Integral( 0, ( h_elastic_x120_y->GetNbinsX() + 1 ) ); // With under and overflow
        double integral_h_elastic_x130_y = h_elastic_x130_y->Integral( 0, ( h_elastic_x130_y->GetNbinsX() + 1 ) ); // With under and overflow
        //double integral_h_elastic_x140_y = h_elastic_x140_y->Integral( 0, ( h_elastic_x140_y->GetNbinsX() + 1 ) ); // With under and overflow
        //double integral_h_elastic_x150_y = h_elastic_x150_y->Integral( 0, ( h_elastic_x150_y->GetNbinsX() + 1 ) ); // With under and overflow
        //double integral_h_inel_el_x120_y = h_inel_el_x120_y->Integral( 0, ( h_inel_el_x120_y->GetNbinsX() + 1 ) ); // With under and overflow
        double integral_h_inel_el_x130_y = h_inel_el_x130_y->Integral( 0, ( h_inel_el_x130_y->GetNbinsX() + 1 ) ); // With under and overflow
        //double integral_h_inel_el_x140_y = h_inel_el_x140_y->Integral( 0, ( h_inel_el_x140_y->GetNbinsX() + 1 ) ); // With under and overflow
        //double integral_h_inel_el_x150_y = h_inel_el_x150_y->Integral( 0, ( h_inel_el_x150_y->GetNbinsX() + 1 ) ); // With under and overflow
        double integral_h_dy_y = h_dy_y->Integral( 0, ( h_dy_y->GetNbinsX() + 1 ) ); // With under and overflow
        double sum_integral_y = integral_h_elastic_x130_y + integral_h_inel_el_x130_y + integral_h_dy_y;
        double scale_data_y = h_data_y->GetEntries() / sum_integral_y ;
        cout << "Scale factor y data normalization: " << scale_data_y << endl;        
       
        // Clone MC histograms and scale
        
        //TH1F *h_elastic_x120_clone_mass = (TH1F*)h_elastic_x120_mass->Clone("h_elastic_x120_clone_mass");
        TH1F *h_elastic_x130_clone_mass = (TH1F*)h_elastic_x130_mass->Clone("h_elastic_x130_clone_mass");
        //TH1F *h_elastic_x140_clone_mass = (TH1F*)h_elastic_x140_mass->Clone("h_elastic_x140_clone_mass");
        //TH1F *h_elastic_x150_clone_mass = (TH1F*)h_elastic_x150_mass->Clone("h_elastic_x150_clone_mass");
        //TH1F *h_inel_el_x120_clone_mass = (TH1F*)h_inel_el_x120_mass->Clone("h_inel_el_x120_clone_mass");
        TH1F *h_inel_el_x130_clone_mass = (TH1F*)h_inel_el_x130_mass->Clone("h_inel_el_x130_clone_mass");
        //TH1F *h_inel_el_x140_clone_mass = (TH1F*)h_inel_el_x140_mass->Clone("h_inel_el_x140_clone_mass");
        //TH1F *h_inel_el_x150_clone_mass = (TH1F*)h_inel_el_x150_mass->Clone("h_inel_el_x150_clone_mass");
        TH1F *h_dy_clone_mass = (TH1F*)h_dy_mass->Clone("h_dy_clone_mass");
        //TH1F *h_elastic_x120_clone_pt = (TH1F*)h_elastic_x120_pt->Clone("h_elastic_x120_clone_pt");
        TH1F *h_elastic_x130_clone_pt = (TH1F*)h_elastic_x130_pt->Clone("h_elastic_x130_clone_pt");
        //TH1F *h_elastic_x140_clone_pt = (TH1F*)h_elastic_x140_pt->Clone("h_elastic_x140_clone_pt");
        //TH1F *h_elastic_x150_clone_pt = (TH1F*)h_elastic_x150_pt->Clone("h_elastic_x150_clone_pt");
        //TH1F *h_inel_el_x120_clone_pt = (TH1F*)h_inel_el_x120_pt->Clone("h_inel_el_x120_clone_pt");
        TH1F *h_inel_el_x130_clone_pt = (TH1F*)h_inel_el_x130_pt->Clone("h_inel_el_x130_clone_pt");
        //TH1F *h_inel_el_x140_clone_pt = (TH1F*)h_inel_el_x140_pt->Clone("h_inel_el_x140_clone_pt");
        //TH1F *h_inel_el_x150_clone_pt = (TH1F*)h_inel_el_x150_pt->Clone("h_inel_el_x150_clone_pt");
        TH1F *h_dy_clone_pt = (TH1F*)h_dy_pt->Clone("h_dy_clone_pt");
        //TH1F *h_elastic_x120_clone_y = (TH1F*)h_elastic_x120_y->Clone("h_elastic_x120_clone_y");
        TH1F *h_elastic_x130_clone_y = (TH1F*)h_elastic_x130_y->Clone("h_elastic_x130_clone_y");
        //TH1F *h_elastic_x140_clone_y = (TH1F*)h_elastic_x140_y->Clone("h_elastic_x140_clone_y");
        //TH1F *h_elastic_x150_clone_y = (TH1F*)h_elastic_x150_y->Clone("h_elastic_x150_clone_y");
        //TH1F *h_inel_el_x120_clone_y = (TH1F*)h_inel_el_x120_y->Clone("h_inel_el_x120_clone_y");
        TH1F *h_inel_el_x130_clone_y = (TH1F*)h_inel_el_x130_y->Clone("h_inel_el_x130_clone_y");
        //TH1F *h_inel_el_x140_clone_y = (TH1F*)h_inel_el_x140_y->Clone("h_inel_el_x140_clone_y");
        //TH1F *h_inel_el_x150_clone_y = (TH1F*)h_inel_el_x150_y->Clone("h_inel_el_x150_clone_y");
        TH1F *h_dy_clone_y = (TH1F*)h_dy_y->Clone("h_dy_clone_y");
		  
		  //h_elastic_x120_clone_mass->Scale(scale_data_mass);
        h_elastic_x130_clone_mass->Scale(scale_data_mass);
        //h_elastic_x140_clone_mass->Scale(scale_data_mass);
        //h_elastic_x150_clone_mass->Scale(scale_data_mass);
		  //h_inel_el_x120_clone_mass->Scale(scale_data_mass);
        h_inel_el_x130_clone_mass->Scale(scale_data_mass);
        //h_inel_el_x140_clone_mass->Scale(scale_data_mass);
        //h_inel_el_x150_clone_mass->Scale(scale_data_mass);
        h_dy_clone_mass->Scale(scale_data_mass);
		  //h_elastic_x120_clone_pt->Scale(scale_data_pt);
        h_elastic_x130_clone_pt->Scale(scale_data_pt);
        //h_elastic_x140_clone_pt->Scale(scale_data_pt);
        //h_elastic_x150_clone_pt->Scale(scale_data_pt);
		  //h_inel_el_x120_clone_pt->Scale(scale_data_pt);
        h_inel_el_x130_clone_pt->Scale(scale_data_pt);
        //h_inel_el_x140_clone_pt->Scale(scale_data_pt);
        //h_inel_el_x150_clone_pt->Scale(scale_data_pt);
        h_dy_clone_pt->Scale(scale_data_pt);
		  //h_elastic_x120_clone_y->Scale(scale_data_y);
        h_elastic_x130_clone_y->Scale(scale_data_y);
        //h_elastic_x140_clone_y->Scale(scale_data_y);
        //h_elastic_x150_clone_y->Scale(scale_data_y);
		  //h_inel_el_x120_clone_y->Scale(scale_data_y);
        h_inel_el_x130_clone_y->Scale(scale_data_y);
        //h_inel_el_x140_clone_y->Scale(scale_data_y);
        //h_inel_el_x150_clone_y->Scale(scale_data_y);
        h_dy_clone_y->Scale(scale_data_y);
		  
		  /*
	     h_elastic_x130_div30_mass->Add(h_elastic_x140_div30_mass);
	     h_elastic_x130_div30_mass->Add(h_elastic_x150_div30_mass);
	     h_elastic_x130_div30_pt->Add(h_elastic_x140_div30_pt);
	     h_elastic_x130_div30_pt->Add(h_elastic_x150_div30_pt);
	     h_elastic_x130_div30_y->Add(h_elastic_x140_div30_y);
	     h_elastic_x130_div30_y->Add(h_elastic_x150_div30_y);
	     h_elastic_x130_div30_xil->Add(h_elastic_x140_div30_xil);
	     h_elastic_x130_div30_xil->Add(h_elastic_x150_div30_xil);	     
		  h_elastic_x130_div30_xir->Add(h_elastic_x140_div30_xir);
	     h_elastic_x130_div30_xir->Add(h_elastic_x150_div30_xir);

	     h_elastic_x130_div30_clone_mass->Add(h_elastic_x140_div30_clone_mass);
	     h_elastic_x130_div30_clone_mass->Add(h_elastic_x150_div30_clone_mass);
	     h_elastic_x130_div30_clone_pt->Add(h_elastic_x140_div30_clone_pt);
	     h_elastic_x130_div30_clone_pt->Add(h_elastic_x150_div30_clone_pt);
	     h_elastic_x130_div30_clone_y->Add(h_elastic_x140_div30_clone_y);
	     h_elastic_x130_div30_clone_y->Add(h_elastic_x150_div30_clone_y);
	     h_elastic_x130_div30_clone_xil->Add(h_elastic_x140_div30_clone_xil);
	     h_elastic_x130_div30_clone_xil->Add(h_elastic_x150_div30_clone_xil);
	     h_elastic_x130_div30_clone_xir->Add(h_elastic_x140_div30_clone_xir);
	     h_elastic_x130_div30_clone_xir->Add(h_elastic_x150_div30_clone_xir);
		  */
  
		  THStack hs_mass("hs_mass","");
		  hs_mass.Add(h_elastic_x130_mass);
		  hs_mass.Add(h_inel_el_x130_mass);
		  hs_mass.Add(h_dy_mass);
		  THStack hs_pt("hs_pt","");
		  hs_pt.Add(h_elastic_x130_pt);
		  hs_pt.Add(h_inel_el_x130_pt);
		  hs_pt.Add(h_dy_pt);
		  THStack hs_y("hs_y","");
		  hs_y.Add(h_elastic_x130_y);
		  hs_y.Add(h_inel_el_x130_y);
		  hs_y.Add(h_dy_y);
		  THStack hs_n_ext_fromPV("hs_n_ext_fromPV","");
		  hs_n_ext_fromPV.Add(h_elastic_x130_n_ext_fromPV);
		  hs_n_ext_fromPV.Add(h_inel_el_x130_n_ext_fromPV);
		  hs_n_ext_fromPV.Add(h_dy_n_ext_fromPV);
		  THStack hs_n_ext_fromPV_2("hs_n_ext_fromPV_2","");
		  hs_n_ext_fromPV_2.Add(h_elastic_x130_n_ext_fromPV_2);
		  hs_n_ext_fromPV_2.Add(h_inel_el_x130_n_ext_fromPV_2);
		  hs_n_ext_fromPV_2.Add(h_dy_n_ext_fromPV_2);
		  THStack hs_n_ext_fromPV_3("hs_n_ext_fromPV_3","");
		  hs_n_ext_fromPV_3.Add(h_elastic_x130_n_ext_fromPV_3);
		  hs_n_ext_fromPV_3.Add(h_inel_el_x130_n_ext_fromPV_3);
		  hs_n_ext_fromPV_3.Add(h_dy_n_ext_fromPV_3);
		  THStack hs_n_ext_fromPV_dz02("hs_n_ext_fromPV_dz02","");
		  hs_n_ext_fromPV_dz02.Add(h_elastic_x130_n_ext_fromPV_dz02);
		  hs_n_ext_fromPV_dz02.Add(h_inel_el_x130_n_ext_fromPV_dz02);
		  hs_n_ext_fromPV_dz02.Add(h_dy_n_ext_fromPV_dz02);
		  THStack hs_n_ext_fromPV_2_dz02("hs_n_ext_fromPV_2_dz02","");
		  hs_n_ext_fromPV_2_dz02.Add(h_elastic_x130_n_ext_fromPV_2_dz02);
		  hs_n_ext_fromPV_2_dz02.Add(h_inel_el_x130_n_ext_fromPV_2_dz02);
		  hs_n_ext_fromPV_2_dz02.Add(h_dy_n_ext_fromPV_2_dz02);
		  THStack hs_n_ext_fromPV_3_dz02("hs_n_ext_fromPV_3_dz02","");
		  hs_n_ext_fromPV_3_dz02.Add(h_elastic_x130_n_ext_fromPV_3_dz02);
		  hs_n_ext_fromPV_3_dz02.Add(h_inel_el_x130_n_ext_fromPV_3_dz02);
		  hs_n_ext_fromPV_3_dz02.Add(h_dy_n_ext_fromPV_3_dz02);
		  THStack hs_n_ext_fromPV_dz01("hs_n_ext_fromPV_dz01","");
		  hs_n_ext_fromPV_dz01.Add(h_elastic_x130_n_ext_fromPV_dz01);
		  hs_n_ext_fromPV_dz01.Add(h_inel_el_x130_n_ext_fromPV_dz01);
		  hs_n_ext_fromPV_dz01.Add(h_dy_n_ext_fromPV_dz01);
		  THStack hs_n_ext_fromPV_2_dz01("hs_n_ext_fromPV_2_dz01","");
		  hs_n_ext_fromPV_2_dz01.Add(h_elastic_x130_n_ext_fromPV_2_dz01);
		  hs_n_ext_fromPV_2_dz01.Add(h_inel_el_x130_n_ext_fromPV_2_dz01);
		  hs_n_ext_fromPV_2_dz01.Add(h_dy_n_ext_fromPV_2_dz01);
		  THStack hs_n_ext_fromPV_3_dz01("hs_n_ext_fromPV_3_dz01","");
		  hs_n_ext_fromPV_3_dz01.Add(h_elastic_x130_n_ext_fromPV_3_dz01);
		  hs_n_ext_fromPV_3_dz01.Add(h_inel_el_x130_n_ext_fromPV_3_dz01);
		  hs_n_ext_fromPV_3_dz01.Add(h_dy_n_ext_fromPV_3_dz01);
     
		  THStack hs_clone_mass("hs_clone_mass","");
		  hs_clone_mass.Add(h_elastic_x130_clone_mass);
		  hs_clone_mass.Add(h_inel_el_x130_clone_mass);
		  hs_clone_mass.Add(h_dy_clone_mass);
		  THStack hs_clone_pt("hs_clone_pt","");
		  hs_clone_pt.Add(h_elastic_x130_clone_pt);
		  hs_clone_pt.Add(h_inel_el_x130_clone_pt);
		  hs_clone_pt.Add(h_dy_clone_pt);
		  THStack hs_clone_y("hs_clone_y","");
		  hs_clone_y.Add(h_elastic_x130_clone_y);
		  hs_clone_y.Add(h_inel_el_x130_clone_y);
		  hs_clone_y.Add(h_dy_clone_y);
		  

		  TCanvas *c_mass = new TCanvas("c_mass","",0,0,1200,1000);
		  hs_mass.Draw("HIST");
		  h_data_mass->Draw("SAME");
		  c_mass->SaveAs("comp/mass.png");
		  c_mass->cd();
		  c_mass->Close();

		  TCanvas *c_pt = new TCanvas("c_pt","",0,0,1200,1000);
		  hs_pt.Draw("HIST");
		  h_data_pt->Draw("SAME");
		  c_pt->SaveAs("comp/pt.png");
		  c_pt->cd();
		  c_pt->Close();

		  TCanvas *c_y = new TCanvas("c_y","",0,0,1200,1000);
		  hs_y.Draw("HIST");
		  h_data_y->Draw("SAME");
		  c_y->SaveAs("comp/y.png");
		  c_y->cd();
		  c_y->Close();

		  TCanvas *c_n_ext_fromPV = new TCanvas("c_n_ext_fromPV","",0,0,1200,1000);
		  hs_n_ext_fromPV.Draw("HIST");
		  h_data_n_ext_fromPV->Draw("SAME");
		  c_n_ext_fromPV->SaveAs("comp/n_ext_fromPV.png");
		  c_n_ext_fromPV->cd();
		  c_n_ext_fromPV->Close();

		  TCanvas *c_n_ext_fromPV_2 = new TCanvas("c_n_ext_fromPV_2","",0,0,1200,1000);
		  hs_n_ext_fromPV_2.Draw("HIST");
		  h_data_n_ext_fromPV_2->Draw("SAME");
		  c_n_ext_fromPV_2->SaveAs("comp/n_ext_fromPV_2.png");
		  c_n_ext_fromPV_2->cd();
		  c_n_ext_fromPV_2->Close();

		  TCanvas *c_n_ext_fromPV_3 = new TCanvas("c_n_ext_fromPV_3","",0,0,1200,1000);
		  hs_n_ext_fromPV_3.Draw("HIST");
		  h_data_n_ext_fromPV_3->Draw("SAME");
		  c_n_ext_fromPV_3->SaveAs("comp/n_ext_fromPV_3.png");
		  c_n_ext_fromPV_3->cd();
		  c_n_ext_fromPV_3->Close();

		  TCanvas *c_n_ext_fromPV_dz02 = new TCanvas("c_n_ext_fromPV_dz02","",0,0,1200,1000);
		  hs_n_ext_fromPV_dz02.Draw("HIST");
		  h_data_n_ext_fromPV_dz02->Draw("SAME");
		  c_n_ext_fromPV_dz02->SaveAs("comp/n_ext_fromPV_dz02.png");
		  c_n_ext_fromPV_dz02->cd();
		  c_n_ext_fromPV_dz02->Close();

		  TCanvas *c_n_ext_fromPV_2_dz02 = new TCanvas("c_n_ext_fromPV_2_dz02","",0,0,1200,1000);
		  hs_n_ext_fromPV_2_dz02.Draw("HIST");
		  h_data_n_ext_fromPV_2_dz02->Draw("SAME");
		  c_n_ext_fromPV_2_dz02->SaveAs("comp/n_ext_fromPV_2_dz02.png");
		  c_n_ext_fromPV_2_dz02->cd();
		  c_n_ext_fromPV_2_dz02->Close();

		  TCanvas *c_n_ext_fromPV_3_dz02 = new TCanvas("c_n_ext_fromPV_3_dz02","",0,0,1200,1000);
		  hs_n_ext_fromPV_3_dz02.Draw("HIST");
		  h_data_n_ext_fromPV_3_dz02->Draw("SAME");
		  c_n_ext_fromPV_3_dz02->SaveAs("comp/n_ext_fromPV_3_dz02.png");
		  c_n_ext_fromPV_3_dz02->cd();
		  c_n_ext_fromPV_3_dz02->Close();

		  TCanvas *c_n_ext_fromPV_dz01 = new TCanvas("c_n_ext_fromPV_dz01","",0,0,1200,1000);
		  hs_n_ext_fromPV_dz01.Draw("HIST");
		  h_data_n_ext_fromPV_dz01->Draw("SAME");
		  c_n_ext_fromPV_dz01->SaveAs("comp/n_ext_fromPV_dz01.png");
		  c_n_ext_fromPV_dz01->cd();
		  c_n_ext_fromPV_dz01->Close();

		  TCanvas *c_n_ext_fromPV_2_dz01 = new TCanvas("c_n_ext_fromPV_2_dz01","",0,0,1200,1000);
		  hs_n_ext_fromPV_2_dz01.Draw("HIST");
		  h_data_n_ext_fromPV_2_dz01->Draw("SAME");
		  c_n_ext_fromPV_2_dz01->SaveAs("comp/n_ext_fromPV_2_dz01.png");
		  c_n_ext_fromPV_2_dz01->cd();
		  c_n_ext_fromPV_2_dz01->Close();

		  TCanvas *c_n_ext_fromPV_3_dz01 = new TCanvas("c_n_ext_fromPV_3_dz01","",0,0,1200,1000);
		  hs_n_ext_fromPV_3_dz01.Draw("HIST");
		  h_data_n_ext_fromPV_3_dz01->Draw("SAME");
		  c_n_ext_fromPV_3_dz01->SaveAs("comp/n_ext_fromPV_3_dz01.png");
		  c_n_ext_fromPV_3_dz01->cd();
		  c_n_ext_fromPV_3_dz01->Close();

		  TFile* f4 = new TFile("comp/comp_data_MC_2017.root", "RECREATE");
		  hs_mass.Draw("HIST");
		  hs_pt.Draw("HIST");
		  hs_y.Draw("HIST");
		  hs_n_ext_fromPV.Draw("HIST");
		  hs_n_ext_fromPV_2.Draw("HIST");
		  hs_n_ext_fromPV_3.Draw("HIST");
		  hs_n_ext_fromPV_dz02.Draw("HIST");
		  hs_n_ext_fromPV_2_dz02.Draw("HIST");
		  hs_n_ext_fromPV_3_dz02.Draw("HIST");
		  hs_n_ext_fromPV_dz01.Draw("HIST");
		  hs_n_ext_fromPV_2_dz01.Draw("HIST");
		  hs_n_ext_fromPV_3_dz01.Draw("HIST");
		  hs_clone_mass.Draw("HIST");
		  hs_clone_pt.Draw("HIST");
		  hs_clone_y.Draw("HIST");
		  h_data_mass->Draw("SAME");
		  h_data_pt->Draw("SAME");
		  h_data_y->Draw("SAME");
		  h_data_n_ext_fromPV->Draw("SAME");
		  h_data_n_ext_fromPV_2->Draw("SAME");
		  h_data_n_ext_fromPV_3->Draw("SAME");
		  h_data_n_ext_fromPV_dz02->Draw("SAME");
		  h_data_n_ext_fromPV_2_dz02->Draw("SAME");
		  h_data_n_ext_fromPV_3_dz02->Draw("SAME");
		  h_data_n_ext_fromPV_dz01->Draw("SAME");
		  h_data_n_ext_fromPV_2_dz01->Draw("SAME");
		  h_data_n_ext_fromPV_3_dz01->Draw("SAME");
		  hs_mass.Write();
		  hs_pt.Write();
		  hs_y.Write();
		  hs_n_ext_fromPV.Write();
		  hs_n_ext_fromPV_2.Write();
		  hs_n_ext_fromPV_3.Write();
		  hs_n_ext_fromPV_dz02.Write();
		  hs_n_ext_fromPV_2_dz02.Write();
		  hs_n_ext_fromPV_3_dz02.Write();
		  hs_n_ext_fromPV_dz01.Write();
		  hs_n_ext_fromPV_2_dz01.Write();
		  hs_n_ext_fromPV_3_dz01.Write();
		  hs_clone_mass.Write();
		  hs_clone_pt.Write();
		  hs_clone_y.Write();
	     h_data_mass->Write();
	     h_data_pt->Write();
	     h_data_y->Write();
		  h_data_n_ext_fromPV->Write();
		  h_data_n_ext_fromPV_2->Write();
		  h_data_n_ext_fromPV_3->Write();
		  h_data_n_ext_fromPV_dz02->Write();
		  h_data_n_ext_fromPV_2_dz02->Write();
		  h_data_n_ext_fromPV_3_dz02->Write();
		  h_data_n_ext_fromPV_dz01->Write();
		  h_data_n_ext_fromPV_2_dz01->Write();
		  h_data_n_ext_fromPV_3_dz01->Write();
		  f4->Close();
		 // }
		  return 0;
}
