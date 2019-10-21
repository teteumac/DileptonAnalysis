#define pileup_protons_cxx
#include "pileup_protons.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void pileup_protons::Loop(Int_t maxEvents)
{
//   In a ROOT session, you can do:
//      root> .L pileup_protons.C
//      root> pileup_protons t
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
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

	output_file->cd();
	TH1F* h_event_selection = new TH1F("event_selection", "", 2, 0, 2);

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries ; jentry++) {
      if( maxEvents > 0 && jentry >= maxEvents ) break;

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      //
      h_event_selection->Fill(0);

      if( !select_events_protons ){
         out_tree->Fill();
      } else{
         bool has_pixel_23 = false;
         bool has_pixel_123 = false;
			for ( unsigned int idx = 0; idx < nRecoProtCand; ++idx ) {
         	//cout << idx << " " << ProtCand_rpid[idx] << " " << ProtCand_arm[idx] << " " << ProtCand_xi[idx] << endl;
            if (ProtCand_rpid[idx] == 23)  has_pixel_23 = true;
            if (ProtCand_rpid[idx] == 123) has_pixel_123 = true;
              
         }
         if( has_pixel_23 || has_pixel_123 ){    
            h_event_selection->Fill(1);
            out_tree->Fill();
         }
      }
   }
   output_file->Write();
}
int run() {
   pileup_protons m;
   m.SelectEvents(true);
   m.Loop();

   return 0;
   }

