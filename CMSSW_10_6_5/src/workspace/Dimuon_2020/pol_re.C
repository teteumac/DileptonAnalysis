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

int draw_function( TFile* f, std::string h_name, std::string f_name )
{
   TFile *input = new TFile("reweight/reweight_multi.root", "READ");

   TH1 *h = (TH1*)input->Get( h_name.c_str() );
   h->Fit( "pol8" );
	//TF1 *func = (TF1*)gr->GetListOfFunctions()->FindObject( "pol8" );
	TF1 *func = (TF1*)h->GetListOfFunctions()->FindObject( "pol8" );
   if ( !func ) return -1;

   func->SetName( f_name.c_str() );
   f->cd();
 
   TCanvas* canvas1 = new TCanvas;
   func->Draw();

	//TFile* f = new TFile("pol_function.root", "RECREATE");
	func->Write();

	//f->Close();

	//cout << "oi" <<endl;

   return 0;
}
	
int run() {
	TFile* f = new TFile("pol_re.root", "RECREATE");

   int multiplicity_0prot_re = draw_function( f , "multiplicity_0prot_cut;1", "re_0prot" );
   int multiplicity_0prot_re_2 = draw_function( f , "multiplicity_0prot_cut;2", "re_0prot_2" );

	f->Close();

 	return multiplicity_0prot_re, multiplicity_0prot_re_2;
 	}
