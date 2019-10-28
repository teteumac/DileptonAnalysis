//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Oct  8 21:13:32 2019 by ROOT version 6.14/09
// from TTree pileup_protons/
// found on file: pileup_protons_data.root
//////////////////////////////////////////////////////////

#ifndef randomize_tree_h
#define randomize_tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class randomize_tree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   TFile          *output_file; 
   TTree          *out_tree;   //
// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          nRecoProtCand;
   Double_t        ProtCand_xi[23];   //[nRecoProtCand]
   Double_t        ProtCand_t[23];   //[nRecoProtCand]
   Double_t        ProtCand_ThX[23];   //[nRecoProtCand]
   Double_t        ProtCand_ThY[23];   //[nRecoProtCand]
   Int_t           ProtCand_rpid[23];   //[nRecoProtCand]
   Int_t           ProtCand_arm[23];   //[nRecoProtCand]
   Int_t           ProtCand_ismultirp[23];   //[nRecoProtCand]
   Double_t        ProtCand_time[23];   //[nRecoProtCand]
   Double_t        ProtCand_trackx1[23];   //[nRecoProtCand]
   Double_t        ProtCand_tracky1[23];   //[nRecoProtCand]
   Double_t        ProtCand_trackx2[23];   //[nRecoProtCand]
   Double_t        ProtCand_tracky2[23];   //[nRecoProtCand]
   Int_t           ProtCand_rpid1[23];   //[nRecoProtCand]
   Int_t           ProtCand_rpid2[23];   //[nRecoProtCand]
   Int_t           ProtCand_trackpixshift1[23];   //[nRecoProtCand]
   Int_t           ProtCand_trackpixshift2[23];   //[nRecoProtCand]

   // List of branches
   TBranch        *b_nRecoProtCand;   //!
   TBranch        *b_ProtCand_xi;   //!
   TBranch        *b_ProtCand_t;   //!
   TBranch        *b_ProtCand_ThX;   //!
   TBranch        *b_ProtCand_ThY;   //!
   TBranch        *b_ProtCand_rpid;   //!
   TBranch        *b_ProtCand_arm;   //!
   TBranch        *b_ProtCand_ismultirp;   //!
   TBranch        *b_ProtCand_time;   //!
   TBranch        *b_ProtCand_trackx1;   //!
   TBranch        *b_ProtCand_tracky1;   //!
   TBranch        *b_ProtCand_trackx2;   //!
   TBranch        *b_ProtCand_tracky2;   //!
   TBranch        *b_ProtCand_rpid1;   //!
   TBranch        *b_ProtCand_rpid2;   //!
   TBranch        *b_ProtCand_trackpixshift1;   //!
   TBranch        *b_ProtCand_trackpixshift2;   //!

   randomize_tree(TTree *tree=0);
   virtual ~randomize_tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef randomize_tree_cxx
randomize_tree::randomize_tree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("pileup_protons_data.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("pileup_protons_data.root");
      }
      f->GetObject("pileup_protons",tree);

   }
   Init(tree);
}

randomize_tree::~randomize_tree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t randomize_tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t randomize_tree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void randomize_tree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nRecoProtCand", &nRecoProtCand, &b_nRecoProtCand);
   fChain->SetBranchAddress("ProtCand_xi", ProtCand_xi, &b_ProtCand_xi);
   fChain->SetBranchAddress("ProtCand_t", ProtCand_t, &b_ProtCand_t);
   fChain->SetBranchAddress("ProtCand_ThX", ProtCand_ThX, &b_ProtCand_ThX);
   fChain->SetBranchAddress("ProtCand_ThY", ProtCand_ThY, &b_ProtCand_ThY);
   fChain->SetBranchAddress("ProtCand_rpid", ProtCand_rpid, &b_ProtCand_rpid);
   fChain->SetBranchAddress("ProtCand_arm", ProtCand_arm, &b_ProtCand_arm);
   fChain->SetBranchAddress("ProtCand_ismultirp", ProtCand_ismultirp, &b_ProtCand_ismultirp);
   fChain->SetBranchAddress("ProtCand_time", ProtCand_time, &b_ProtCand_time);
   fChain->SetBranchAddress("ProtCand_trackx1", ProtCand_trackx1, &b_ProtCand_trackx1);
   fChain->SetBranchAddress("ProtCand_tracky1", ProtCand_tracky1, &b_ProtCand_tracky1);
   fChain->SetBranchAddress("ProtCand_trackx2", ProtCand_trackx2, &b_ProtCand_trackx2);
   fChain->SetBranchAddress("ProtCand_tracky2", ProtCand_tracky2, &b_ProtCand_tracky2);
   fChain->SetBranchAddress("ProtCand_rpid1", ProtCand_rpid1, &b_ProtCand_rpid1);
   fChain->SetBranchAddress("ProtCand_rpid2", ProtCand_rpid2, &b_ProtCand_rpid2);
   fChain->SetBranchAddress("ProtCand_trackpixshift1", ProtCand_trackpixshift1, &b_ProtCand_trackpixshift1);
   fChain->SetBranchAddress("ProtCand_trackpixshift2", ProtCand_trackpixshift2, &b_ProtCand_trackpixshift2);
   Notify();

   output_file = new TFile( "pileup_protons_random.root", "RECREATE");
   output_file->cd();
	out_tree = new TTree("pileup_protons_random","");
	out_tree->Branch( "nRecoProtCand", &nRecoProtCand, "nRecoProtCand/i" );
   out_tree->Branch( "ProtCand_xi", ProtCand_xi, "ProtCand_xi[nRecoProtCand]/D" );
   out_tree->Branch( "ProtCand_t", ProtCand_t, "ProtCand_t[nRecoProtCand]/D" );
   out_tree->Branch( "ProtCand_ThX", ProtCand_ThX, "ProtCand_ThX[nRecoProtCand]/D" );
   out_tree->Branch( "ProtCand_ThY", ProtCand_ThY, "ProtCand_ThY[nRecoProtCand]/D" );
   out_tree->Branch( "ProtCand_rpid", ProtCand_rpid, "ProtCand_rpid[nRecoProtCand]/I" );
   out_tree->Branch( "ProtCand_arm", ProtCand_arm, "ProtCand_arm[nRecoProtCand]/I" );
   out_tree->Branch( "ProtCand_ismultirp", ProtCand_ismultirp, "ProtCand_ismultirp[nRecoProtCand]/I" );
   out_tree->Branch( "ProtCand_time", ProtCand_time, "ProtCand_time[nRecoProtCand]/D" );
   out_tree->Branch( "ProtCand_trackx1", ProtCand_trackx1, "ProtCand_trackx1[nRecoProtCand]/D" );
   out_tree->Branch( "ProtCand_tracky1", ProtCand_tracky1, "ProtCand_tracky1[nRecoProtCand]/D" );
   out_tree->Branch( "ProtCand_trackx2", ProtCand_trackx2, "ProtCand_trackx2[nRecoProtCand]/D" );
   out_tree->Branch( "ProtCand_tracky2", ProtCand_tracky2, "ProtCand_tracky2[nRecoProtCand]/D" );
   out_tree->Branch( "ProtCand_rpid1", ProtCand_rpid1, "ProtCand_rpid1[nRecoProtCand]/I" );
   out_tree->Branch( "ProtCand_rpid2", ProtCand_rpid2, "ProtCand_rpid2[nRecoProtCand]/I" );
	out_tree->Branch( "ProtCand_trackpixshift1", ProtCand_trackpixshift1, "ProtCand_trackpixshift1[nRecoProtCand]/I" );
   out_tree->Branch( "ProtCand_trackpixshift2", ProtCand_trackpixshift2, "ProtCand_trackpixshift2[nRecoProtCand]/I" ); 
}

Bool_t randomize_tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void randomize_tree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t randomize_tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef randomize_tree_cxx
