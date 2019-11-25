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
#include <TGraph.h>
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


int draw_function()
{
   TFile *input = new TFile("histos_MC/output_elastic_xangle130.root", "READ");
 
   TGraph *gr_rp3 = (TGraph*)input->Get("gr_rp3");
	TF1 *f_rp3 = (TF1*)gr_rp3->GetListOfFunctions()->FindObject("f_rp3");
   f_rp3->SetName("f_rp3");
	double coef_ang_rp3 = f_rp3->GetParameter(1);
	double coef_ang_err_rp3 = f_rp3->GetParError(1);
   cout << "p1: " << coef_ang_rp3 << "+/-" << coef_ang_err_rp3 << endl;

   TGraph *gr_rp23 = (TGraph*)input->Get("gr_rp23");
	TF1 *f_rp23 = (TF1*)gr_rp23->GetListOfFunctions()->FindObject("f_rp23");
   f_rp23->SetName("f_rp23");
	double coef_ang_rp23 = f_rp23->GetParameter(1);
	double coef_ang_err_rp23 = f_rp23->GetParError(1);
   cout << "p1: " << coef_ang_rp23 << "+/-" << coef_ang_err_rp23 << endl;
 
   TGraph *gr_left_single = (TGraph*)input->Get("gr_left_single");
	TF1 *f_left_single = (TF1*)gr_left_single->GetListOfFunctions()->FindObject("f_left_single");
   f_left_single->SetName("f_left_single");
	double coef_ang_left_single = f_left_single->GetParameter(1);
	double coef_ang_err_left_single = f_left_single->GetParError(1);
   cout << "p1: " << coef_ang_left_single << "+/-" << coef_ang_err_left_single << endl;

   TGraph *gr_rp103 = (TGraph*)input->Get("gr_rp103");
	TF1 *f_rp103 = (TF1*)gr_rp103->GetListOfFunctions()->FindObject("f_rp103");
   f_rp103->SetName("f_rp103");
	double coef_ang_rp103 = f_rp103->GetParameter(1);
	double coef_ang_err_rp103 = f_rp103->GetParError(1);
   cout << "p1: " << coef_ang_rp103 << "+/-" << coef_ang_err_rp103 << endl;
 
   TGraph *gr_rp123 = (TGraph*)input->Get("gr_rp123");
	TF1 *f_rp123 = (TF1*)gr_rp123->GetListOfFunctions()->FindObject("f_rp123");
   f_rp123->SetName("f_rp123");
	double coef_ang_rp123 = f_rp123->GetParameter(1);
	double coef_ang_err_rp123 = f_rp123->GetParError(1);
   cout << "p1: " << coef_ang_rp123 << "+/-" << coef_ang_err_rp123 << endl;

   TGraph *gr_right_single = (TGraph*)input->Get("gr_right_single");
	TF1 *f_right_single = (TF1*)gr_right_single->GetListOfFunctions()->FindObject("f_right_single");
   f_right_single->SetName("f_right_single");
	double coef_ang_right_single = f_right_single->GetParameter(1);
	double coef_ang_err_right_single = f_right_single->GetParError(1);
   cout << "p1: " << coef_ang_right_single << "+/-" << coef_ang_err_right_single << endl;
 
   TGraph *gr_left_multi = (TGraph*)input->Get("gr_left_multi");
	TF1 *f_left_multi = (TF1*)gr_left_multi->GetListOfFunctions()->FindObject("f_left_multi");
   f_left_multi->SetName("f_left_multi");
	double coef_ang_left_multi = f_left_multi->GetParameter(1);
	double coef_ang_err_left_multi = f_left_multi->GetParError(1);
   cout << "p1: " << coef_ang_left_multi << "+/-" << coef_ang_err_left_multi << endl;

   TGraph *gr_right_multi = (TGraph*)input->Get("gr_right_multi");
	TF1 *f_right_multi = (TF1*)gr_right_multi->GetListOfFunctions()->FindObject("f_right_multi");
   f_right_multi->SetName("f_right_multi");
	double coef_ang_right_multi = f_right_multi->GetParameter(1);
	double coef_ang_err_right_multi = f_right_multi->GetParError(1);
   cout << "p1: " << coef_ang_right_multi << "+/-" << coef_ang_err_right_multi << endl;
 
   TFile* f = new TFile("histos_MC/pol_function.root", "RECREATE");
   f_rp3->Draw();
   f_rp23->Draw();
   f_left_single->Draw();
   f_rp103->Draw();
   f_rp123->Draw();
   f_right_single->Draw();
   f_left_multi->Draw();
   f_right_multi->Draw();
   f_rp3->Write();
   f_rp23->Write();
   f_left_single->Write();
   f_rp103->Write();
   f_rp123->Write();
   f_right_single->Write();
   f_left_multi->Write();
   f_right_multi->Write();

   f->Close();
}

int run() {
   draw_function();
   return 0; 
}

