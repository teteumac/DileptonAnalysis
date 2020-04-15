//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Aug  6 21:55:25 2019 by ROOT version 6.18/00
// from TTree ntp1/ntp1
// found on file: /afs/cern.ch/user/m/malvesga/work/ProtonRecon/TEST/CMSSW_10_6_0/src/test-simu/output_single_xangle150.root
//////////////////////////////////////////////////////////

#ifndef ntp1_h
#define ntp1_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <string>
#include <iostream>

class ntp1 {
   public :
      TTree          *fChain;   //!pointer to the analyzed TTree or TChain
      Int_t           fCurrent; //!current Tree number in a TChain

      TFile* mix_file;
      TTree* pileup_tree;
      bool mix_pileup;

      bool resample;
      bool reweighting;
      int resample_number;   

      std::string fileName;
      std::string outfileName;

      std::string fileNamePileUp;

      // Fixed size dimensions of array or collections stored in the TTree if any.

      static constexpr unsigned int NMAXPROTONS = 25;

      // Declaration of leaf types
      UInt_t          Run;
      UInt_t          LumiSection;
      UInt_t          BX;
      UInt_t          EventNum;
      Float_t         CrossingAngle;
      UInt_t          nHLT;
      Int_t           HLT_Accept[1];   //[nHLT]
      Int_t           HLT_Prescl[1];   //[nHLT]
      vector<string>  *HLT_Name;
      UInt_t          nMuonCand;
      Double_t        MuonCand_pt[2];   //[nMuonCand]
      Double_t        MuonCand_eta[2];   //[nMuonCand]
      Double_t        MuonCand_phi[2];   //[nMuonCand]
      Double_t        MuonCand_e[2];   //[nMuonCand]
      Int_t           MuonCand_charge[2];   //[nMuonCand]
      Double_t        MuonCand_vtxx[2];   //[nMuonCand]
      Double_t        MuonCand_vtxy[2];   //[nMuonCand]
      Double_t        MuonCand_vtxz[2];   //[nMuonCand]
      Double_t        MuonCand_dxy[2];   //[nMuonCand]
      Int_t           MuonCand_nstatseg[2];   //[nMuonCand]
      Int_t           MuonCand_ntrklayers[2];   //[nMuonCand]
      Int_t           MuonCand_npxlhits[2];   //[nMuonCand]
      Int_t           MuonCand_isglobal[2];   //[nMuonCand]
      Int_t           MuonCand_istracker[2];   //[nMuonCand]
      Int_t           MuonCand_isstandalone[2];   //[nMuonCand]
      Int_t           MuonCand_ispfmuon[2];   //[nMuonCand]
      Int_t           MuonCand_istight[2];   //[nMuonCand]
      Int_t           MuonCandTrack_nmuchits[2];   //[nMuonCand]
      Double_t        MuonCandTrack_chisq[2];   //[nMuonCand]
      Double_t        MuonCand_innerTrackPt[2];   //[nMuonCand]
      Double_t        MuonCand_innerTrackEta[2];   //[nMuonCand]
      Double_t        MuonCand_innerTrackPhi[2];   //[nMuonCand]
      Double_t        MuonCand_innerTrackVtxz[2];   //[nMuonCand]
      UInt_t          nGenMuonCand;
      UInt_t          nGenMuonCandOutOfAccept;
      Double_t        GenMuonCand_pt[2];   //[nGenMuonCand]
      Double_t        GenMuonCand_eta[2];   //[nGenMuonCand]
      Double_t        GenMuonCand_phi[2];   //[nGenMuonCand]
      Double_t        GenMuonCand_e[2];   //[nGenMuonCand]
      UInt_t          nGenProtCand;
      Double_t        GenProtCand_pt[2];   //[nGenProtCand]
      Double_t        GenProtCand_eta[2];   //[nGenProtCand]
      Double_t        GenProtCand_phi[2];   //[nGenProtCand]
      Double_t        GenProtCand_e[2];   //[nGenProtCand]
      Int_t           GenProtCand_status[2];   //[nGenProtCand]
      UInt_t          nPrimVertexCand;
      Double_t        PrimVertexCand_x[54];   //[nPrimVertexCand]
      Double_t        PrimVertexCand_y[54];   //[nPrimVertexCand]
      Double_t        PrimVertexCand_z[54];   //[nPrimVertexCand]
      Double_t        PrimVertexCand_chi2[54];   //[nPrimVertexCand]
      UInt_t          PrimVertexCand_ndof[54];   //[nPrimVertexCand]
      UInt_t          PrimVertexCand_tracks[54];   //[nPrimVertexCand]
      UInt_t          nPfCand;
      Double_t        PfCand_phi[89];   //[nPfCand]
      Double_t        PfCand_eta[89];   //[nPfCand]
      Double_t        PfCand_fromPV[89];   //[nPfCand]
      Double_t        PfCand_dz[89];   //[nPfCand]
      UInt_t          nPair;
      Int_t           Pair_lepton1[1];   //[nPair]
      Int_t           Pair_lepton2[1];   //[nPair]
      Double_t        Pair_mass[1];   //[nPair]
      Double_t        Pair_pt[1];   //[nPair]
      Double_t        Pair_eta[1];   //[nPair]
      Double_t        Pair_phi[1];   //[nPair]
      Double_t        Pair_dpt[1];   //[nPair]
      Double_t        Pair_dphi[1];   //[nPair]
      Double_t        Pair_3Dangle[1];   //[nPair]
      UInt_t          Pair_extratracks0p5mm[1];   //[nPair]
      UInt_t          Pair_extratracks1mm[1];   //[nPair]
      UInt_t          Pair_extratracks2mm[1];   //[nPair]
      UInt_t          Pair_extratracks3mm[1];   //[nPair]
      UInt_t          Pair_extratracks4mm[1];   //[nPair]
      UInt_t          Pair_extratracks5mm[1];   //[nPair]
      UInt_t          Pair_extratracks1cm[1];   //[nPair]
      UInt_t          Pair_extratracks2cm[1];   //[nPair]
      UInt_t          Pair_extratracks3cm[1];   //[nPair]
      UInt_t          Pair_extratracks4cm[1];   //[nPair]
      UInt_t          Pair_extratracks5cm[1];   //[nPair]
      UInt_t          Pair_extratracks10cm[1];   //[nPair]
      Double_t        KalmanVertexCand_x[1];   //[nPair]
      Double_t        KalmanVertexCand_y[1];   //[nPair]
      Double_t        KalmanVertexCand_z[1];   //[nPair]
      Double_t        GenPair_mass;
      Double_t        GenPair_pt;
      Double_t        GenPair_eta;
      Double_t        GenPair_phi;
      Double_t        GenPair_dpt;
      Double_t        GenPair_dphi;
      Double_t        GenPair_3Dangle;
      UInt_t          nLocalProtCand;
      Double_t        LocalProtCand_x[2];   //[nLocalProtCand]
      Double_t        LocalProtCand_y[2];   //[nLocalProtCand]
      Double_t        LocalProtCand_t[2];   //[nLocalProtCand]
      Double_t        LocalProtCand_xSigma[2];   //[nLocalProtCand]
      Double_t        LocalProtCand_ySigma[2];   //[nLocalProtCand]
      Double_t        LocalProtCand_tSigma[2];   //[nLocalProtCand]
      Int_t           LocalProtCand_arm[2];   //[nLocalProtCand]
      Int_t           LocalProtCand_station[2];   //[nLocalProtCand]
      Int_t           LocalProtCand_pot[2];   //[nLocalProtCand]
      Int_t           LocalProtCand_rpid[2];   //[nLocalProtCand]
      /*UInt_t          nRecoProtCand;
        Double_t        ProtCand_xi[3];   //[nRecoProtCand]
        Double_t        ProtCand_t[3];   //[nRecoProtCand]
        Double_t        ProtCand_ThX[3];   //[nRecoProtCand]
        Double_t        ProtCand_ThY[3];   //[nRecoProtCand]
        Int_t           ProtCand_rpid[3];   //[nRecoProtCand]
        Int_t           ProtCand_arm[3];   //[nRecoProtCand]
        Int_t           ProtCand_ismultirp[3];   //[nRecoProtCand]
        Double_t        ProtCand_time[3];   //[nRecoProtCand]
        Double_t        ProtCand_trackx1[3];   //[nRecoProtCand]
        Double_t        ProtCand_tracky1[3];   //[nRecoProtCand]
        Double_t        ProtCand_trackx2[3];   //[nRecoProtCand]
        Double_t        ProtCand_tracky2[3];   //[nRecoProtCand]
        Int_t           ProtCand_rpid1[3];   //[nRecoProtCand]
        Int_t           ProtCand_rpid2[3];   //[nRecoProtCand]
        Int_t           ProtCand_trackpixshift1[3];   //[nRecoProtCand]
        Int_t           ProtCand_trackpixshift2[3];   //[nRecoProtCand]*/
      UInt_t          nRecoProtCand;
      Double_t        ProtCand_xi[NMAXPROTONS];   //[nRecoProtCand]
      Double_t        ProtCand_t[NMAXPROTONS];   //[nRecoProtCand]
      Double_t        ProtCand_ThX[NMAXPROTONS];   //[nRecoProtCand]
      Double_t        ProtCand_ThY[NMAXPROTONS];   //[nRecoProtCand]
      Int_t           ProtCand_rpid[NMAXPROTONS];   //[nRecoProtCand]
      Int_t           ProtCand_arm[NMAXPROTONS];   //[nRecoProtCand]
      Int_t           ProtCand_ismultirp[NMAXPROTONS];   //[nRecoProtCand]
      Double_t        ProtCand_time[NMAXPROTONS];   //[nRecoProtCand]
      Double_t        ProtCand_trackx1[NMAXPROTONS];   //[nRecoProtCand]
      Double_t        ProtCand_tracky1[NMAXPROTONS];   //[nRecoProtCand]
      Double_t        ProtCand_trackx2[NMAXPROTONS];   //[nRecoProtCand]
      Double_t        ProtCand_tracky2[NMAXPROTONS];   //[nRecoProtCand]
      Int_t           ProtCand_rpid1[NMAXPROTONS];   //[nRecoProtCand]
      Int_t           ProtCand_rpid2[NMAXPROTONS];   //[nRecoProtCand]
      Int_t           ProtCand_trackpixshift1[NMAXPROTONS];   //[nRecoProtCand]
      Int_t           ProtCand_trackpixshift2[NMAXPROTONS];   //[nRecoProtCand]
      UInt_t          nQualityExtraTrack;
      Double_t        ClosestExtraTrack_vtxdxyz[1];   //[nPair]
      Int_t           ClosestExtraTrack_id[1];   //[nPair]
      Double_t        ClosestHighPurityExtraTrack_vtxdxyz[1];   //[nPair]
      Int_t           ClosestHighPurityExtraTrack_id[1];   //[nPair]
      Double_t        Weight;
      Double_t        PUWeightTrue;

      /*const unsigned int NMAXPROTONS = 10;
        UInt_t          nRecoMixProtCand;
        Double_t        MixProtCand_xi[NMAX];   //[nRecoMixProtCand]
        Double_t        MixProtCand_t[NMAX];   //[nRecoMixProtCand]
        Double_t        MixProtCand_ThX[NMAX];   //[nRecoMixProtCand]
        Double_t        MixProtCand_ThY[NMAX];   //[nRecoMixProtCand]
        Int_t           MixProtCand_rpid[NMAX];   //[nRecoMixProtCand]
        Int_t           MixProtCand_arm[NMAX];   //[nRecoMixProtCand]
        Int_t           MixProtCand_ismultirp[NMAX];   //[nRecoMixProtCand]
        Double_t        MixProtCand_time[NMAX];   //[nRecoMixProtCand]
        Double_t        MixProtCand_trackx1[NMAX];   //[nRecoMixProtCand]
        Double_t        MixProtCand_tracky1[NMAX];   //[nRecoMixProtCand]
        Double_t        MixProtCand_trackx2[NMAX];   //[nRecoMixProtCand]
        Double_t        MixProtCand_tracky2[NMAX];   //[nRecoMixProtCand]
        Int_t           MixProtCand_rpid1[NMAX];   //[nRecoMixProtCand]
        Int_t           MixProtCand_rpid2[NMAX];   //[nRecoMixProtCand]
        Int_t           MixProtCand_trackpixshift1[NMAX];   //[nRecoMixProtCand]
        Int_t           MixProtCand_trackpixshift2[NMAX];   //[nRecoMixProtCand]*/
      // List of branches
      TBranch        *b_Run;   //!
      TBranch        *b_LumiSection;   //!
      TBranch        *b_BX;   //!
      TBranch        *b_EventNum;   //!
      TBranch        *b_CrossingAngle;   //!
      TBranch        *b_nHLT;   //!
      TBranch        *b_HLT_Accept;   //!
      TBranch        *b_HLT_Prescl;   //!
      TBranch        *b_HLT_Name;   //!
      TBranch        *b_nMuonCand;   //!
      TBranch        *b_MuonCand_pt;   //!
      TBranch        *b_MuonCand_eta;   //!
      TBranch        *b_MuonCand_phi;   //!
      TBranch        *b_MuonCand_e;   //!
      TBranch        *b_MuonCand_charge;   //!
      TBranch        *b_MuonCand_vtxx;   //!
      TBranch        *b_MuonCand_vtxy;   //!
      TBranch        *b_MuonCand_vtxz;   //!
      TBranch        *b_MuonCand_dxy;   //!
      TBranch        *b_MuonCand_nstatseg;   //!
      TBranch        *b_MuonCand_ntrklayers;   //!
      TBranch        *b_MuonCand_npxlhits;   //!
      TBranch        *b_MuonCand_isglobal;   //!
      TBranch        *b_MuonCand_istracker;   //!
      TBranch        *b_MuonCand_isstandalone;   //!
      TBranch        *b_MuonCand_ispfmuon;   //!
      TBranch        *b_MuonCand_istight;   //!
      TBranch        *b_MuonCandTrack_nmuchits;   //!
      TBranch        *b_MuonCandTrack_chisq;   //!
      TBranch        *b_MuonCand_innerTrackPt;   //!
      TBranch        *b_MuonCand_innerTrackEta;   //!
      TBranch        *b_MuonCand_innerTrackPhi;   //!
      TBranch        *b_MuonCand_innerTrackVtxz;   //!
      TBranch        *b_nGenMuonCand;   //!
      TBranch        *b_nGenMuonCandOutOfAccept;   //!
      TBranch        *b_GenMuonCand_pt;   //!
      TBranch        *b_GenMuonCand_eta;   //!
      TBranch        *b_GenMuonCand_phi;   //!
      TBranch        *b_GenMuonCand_e;   //!
      TBranch        *b_nGenProtCand;   //!
      TBranch        *b_GenProtCand_pt;   //!
      TBranch        *b_GenProtCand_eta;   //!
      TBranch        *b_GenProtCand_phi;   //!
      TBranch        *b_GenProtCand_e;   //!
      TBranch        *b_GenProtCand_status;   //!
      TBranch        *b_nPrimVertexCand;   //!
      TBranch        *b_PrimVertexCand_x;   //!
      TBranch        *b_PrimVertexCand_y;   //!
      TBranch        *b_PrimVertexCand_z;   //!
      TBranch        *b_PrimVertexCand_chi2;   //!
      TBranch        *b_PrimVertexCand_ndof;   //!
      TBranch        *b_PrimVertexCand_tracks;   //!
      TBranch        *b_nPfCand;   //!
      TBranch        *b_PfCand_phi;   //!
      TBranch        *b_PfCand_eta;   //!
      TBranch        *b_PfCand_fromPV;   //!
      TBranch        *b_PfCand_dz;   //!
      TBranch        *b_nPair;   //!
      TBranch        *b_Pair_lepton1;   //!
      TBranch        *b_Pair_lepton2;   //!
      TBranch        *b_Pair_mass;   //!
      TBranch        *b_Pair_pt;   //!
      TBranch        *b_Pair_eta;   //!
      TBranch        *b_Pair_phi;   //!
      TBranch        *b_Pair_dpt;   //!
      TBranch        *b_Pair_dphi;   //!
      TBranch        *b_Pair_3Dangle;   //!
      TBranch        *b_Pair_extratracks0p5mm;   //!
      TBranch        *b_Pair_extratracks1mm;   //!
      TBranch        *b_Pair_extratracks2mm;   //!
      TBranch        *b_Pair_extratracks3mm;   //!
      TBranch        *b_Pair_extratracks4mm;   //!
      TBranch        *b_Pair_extratracks5mm;   //!
      TBranch        *b_Pair_extratracks1cm;   //!
      TBranch        *b_Pair_extratracks2cm;   //!
      TBranch        *b_Pair_extratracks3cm;   //!
      TBranch        *b_Pair_extratracks4cm;   //!
      TBranch        *b_Pair_extratracks5cm;   //!
      TBranch        *b_Pair_extratracks10cm;   //!
      TBranch        *b_KalmanVertexCand_x;   //!
      TBranch        *b_KalmanVertexCand_y;   //!
      TBranch        *b_KalmanVertexCand_z;   //!
      TBranch        *b_GenPair_mass;   //!
      TBranch        *b_GenPair_pt;   //!
      TBranch        *b_GenPair_eta;   //!
      TBranch        *b_GenPair_phi;   //!
      TBranch        *b_GenPair_dpt;   //!
      TBranch        *b_GenPair_dphi;   //!
      TBranch        *b_GenPair_3Dangle;   //!
      TBranch        *b_nLocalProtCand;   //!
      TBranch        *b_LocalProtCand_x;   //!
      TBranch        *b_LocalProtCand_y;   //!
      TBranch        *b_LocalProtCand_t;   //!
      TBranch        *b_LocalProtCand_xSigma;   //!
      TBranch        *b_LocalProtCand_ySigma;   //!
      TBranch        *b_LocalProtCand_tSigma;   //!
      TBranch        *b_LocalProtCand_arm;   //!
      TBranch        *b_LocalProtCand_station;   //!
      TBranch        *b_LocalProtCand_pot;   //!
      TBranch        *b_LocalProtCand_rpid;   //!
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
      TBranch        *b_nQualityExtraTrack;   //!
      TBranch        *b_ClosestExtraTrack_vtxdxyz;   //!
      TBranch        *b_ClosestExtraTrack_id;   //!
      TBranch        *b_ClosestHighPurityExtraTrack_vtxdxyz;   //!
      TBranch        *b_ClosestHighPurityExtraTrack_id;   //!
      TBranch        *b_Weight;   //!
      TBranch        *b_PUWeightTrue;   //!

      TBranch        *b_nRecoMixProtCand;   //!
      TBranch        *b_MixProtCand_xi;   //!
      TBranch        *b_MixProtCand_t;   //!
      TBranch        *b_MixProtCand_ThX;   //!
      TBranch        *b_MixProtCand_ThY;   //!
      TBranch        *b_MixProtCand_rpid;   //!
      TBranch        *b_MixProtCand_arm;   //!
      TBranch        *b_MixProtCand_ismultirp;   //!
      TBranch        *b_MixProtCand_time;   //!
      TBranch        *b_MixProtCand_trackx1;   //!
      TBranch        *b_MixProtCand_tracky1;   //!
      TBranch        *b_MixProtCand_trackx2;   //!
      TBranch        *b_MixProtCand_tracky2;   //!
      TBranch        *b_MixProtCand_rpid1;   //!
      TBranch        *b_MixProtCand_rpid2;   //!
      TBranch        *b_MixProtCand_trackpixshift1;   //!
      TBranch        *b_MixProtCand_trackpixshift2;   //!

      ntp1(TTree *tree=0);
      ntp1(std::string const&, std::string const&, TTree *tree=0);
      virtual ~ntp1();
      virtual Int_t    Cut(Long64_t entry);
      virtual Int_t    GetEntry(Long64_t entry);
      virtual Long64_t LoadTree(Long64_t entry);
      virtual void     Init(TTree *tree);
      virtual void     Loop();
      virtual Bool_t   Notify();
      virtual void     Show(Long64_t entry = -1);
      virtual void     SetResample(bool);
      virtual void     SetReweight(bool);
      virtual void     SetNumberOfSamples(unsigned int);

      //struct PileUpEvent {
      //	UInt_t          nRecoProtCand;
      //	Double_t        ProtCand_xi[NMAXPROTONS];   //[nRecoProtCand]
      //	//Double_t        ProtCand_t[NMAXPROTONS];   //[nRecoProtCand]
      //	Double_t        ProtCand_ThX[NMAXPROTONS];   //[nRecoProtCand]
      //	Double_t        ProtCand_ThY[NMAXPROTONS];   //[nRecoProtCand]
      //	Int_t           ProtCand_rpid[NMAXPROTONS];   //[nRecoProtCand]
      //	Int_t           ProtCand_arm[NMAXPROTONS];   //[nRecoProtCand]
      //	Int_t           ProtCand_ismultirp[NMAXPROTONS];   //[nRecoProtCand]
      //	//Double_t        ProtCand_time[NMAXPROTONS];   //[nRecoProtCand]
      //	//Double_t        ProtCand_trackx1[NMAXPROTONS];   //[nRecoProtCand]
      //	//Double_t        ProtCand_tracky1[NMAXPROTONS];   //[nRecoProtCand]
      //	//Double_t        ProtCand_trackx2[NMAXPROTONS];   //[nRecoProtCand]
      //	//Double_t        ProtCand_tracky2[NMAXPROTONS];   //[nRecoProtCand]
      //	//Int_t           ProtCand_rpid1[NMAXPROTONS];   //[nRecoProtCand]
      //	//Int_t           ProtCand_rpid2[NMAXPROTONS];   //[nRecoProtCand]
      //	//Int_t           ProtCand_trackpixshift1[NMAXPROTONS];   //[nRecoProtCand]
      //	//Int_t           ProtCand_trackpixshift2[NMAXPROTONS];   //[nRecoProtCand]
      //};
};

#endif

#ifdef ntp1_cxx
ntp1::ntp1(std::string const& fileName_, std::string const& outfileName_, TTree *tree) : fChain(0), resample(false), resample_number(-1), reweighting(false), fileName(fileName_), outfileName(outfileName_)
{
   // if parameter tree is not specified (or zero), connect the file
   // used to generate this class and read the Tree.
   std::string treeName = "ntp1";
   std::string str_aux = "";
   str_aux += fileName; str_aux += ":/ggll_miniaod";

   //fileNamePileUp = "/mnt/hadoop/cms/store/user/malvesga/pileup/pileup_protons_EG.root";
   fileNamePileUp = "/mnt/hadoop/cms/store/user/malvesga/pileup/unbias_pileup_protons_EG.root";

   if (tree == 0) {
      //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("input.root");
      //if (!f || !f->IsOpen()) {
      //   f = new TFile("input.root");
      //}
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject( fileName.c_str() );
      if (!f || !f->IsOpen()) {
         f = new TFile( fileName.c_str(), "READ" );
      }
      //TDirectory * dir = (TDirectory*)f->Get("input.root:/ggll_miniaod");
      std::cout << "Accessing dir " << str_aux << std::endl;
      TDirectory * dir = (TDirectory*)f->Get( str_aux.c_str() );
      dir->GetObject( treeName.c_str(), tree );

   }
   Init(tree);
}

ntp1::ntp1(TTree *tree) : ntp1("input.root", "output_cut.root", tree) {}

ntp1::~ntp1()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

void ntp1::SetResample(bool flag_) { resample = flag_; }

void ntp1::SetReweight(bool flag2_) { reweighting = flag2_; }

void ntp1::SetNumberOfSamples(unsigned int samples_) { resample_number = samples_; }

Int_t ntp1::GetEntry(Long64_t entry)
{
   // Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ntp1::LoadTree(Long64_t entry)
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

void ntp1::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   mix_pileup = true;

   //resample = true;
   //resample_number = 10000;   

   // Set object pointer
   HLT_Name = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Run", &Run, &b_Run);
   fChain->SetBranchAddress("LumiSection", &LumiSection, &b_LumiSection);
   fChain->SetBranchAddress("BX", &BX, &b_BX);
   fChain->SetBranchAddress("EventNum", &EventNum, &b_EventNum);
   fChain->SetBranchAddress("CrossingAngle", &CrossingAngle, &b_CrossingAngle);
   fChain->SetBranchAddress("nHLT", &nHLT, &b_nHLT);
   fChain->SetBranchAddress("HLT_Accept", &HLT_Accept, &b_HLT_Accept);
   fChain->SetBranchAddress("HLT_Prescl", &HLT_Prescl, &b_HLT_Prescl);
   fChain->SetBranchAddress("HLT_Name", &HLT_Name, &b_HLT_Name);
   fChain->SetBranchAddress("nMuonCand", &nMuonCand, &b_nMuonCand);
   fChain->SetBranchAddress("MuonCand_pt", MuonCand_pt, &b_MuonCand_pt);
   fChain->SetBranchAddress("MuonCand_eta", MuonCand_eta, &b_MuonCand_eta);
   fChain->SetBranchAddress("MuonCand_phi", MuonCand_phi, &b_MuonCand_phi);
   fChain->SetBranchAddress("MuonCand_e", MuonCand_e, &b_MuonCand_e);
   fChain->SetBranchAddress("MuonCand_charge", MuonCand_charge, &b_MuonCand_charge);
   fChain->SetBranchAddress("MuonCand_vtxx", MuonCand_vtxx, &b_MuonCand_vtxx);
   fChain->SetBranchAddress("MuonCand_vtxy", MuonCand_vtxy, &b_MuonCand_vtxy);
   fChain->SetBranchAddress("MuonCand_vtxz", MuonCand_vtxz, &b_MuonCand_vtxz);
   fChain->SetBranchAddress("MuonCand_dxy", MuonCand_dxy, &b_MuonCand_dxy);
   fChain->SetBranchAddress("MuonCand_nstatseg", MuonCand_nstatseg, &b_MuonCand_nstatseg);
   fChain->SetBranchAddress("MuonCand_ntrklayers", MuonCand_ntrklayers, &b_MuonCand_ntrklayers);
   fChain->SetBranchAddress("MuonCand_npxlhits", MuonCand_npxlhits, &b_MuonCand_npxlhits);
   fChain->SetBranchAddress("MuonCand_isglobal", MuonCand_isglobal, &b_MuonCand_isglobal);
   fChain->SetBranchAddress("MuonCand_istracker", MuonCand_istracker, &b_MuonCand_istracker);
   fChain->SetBranchAddress("MuonCand_isstandalone", MuonCand_isstandalone, &b_MuonCand_isstandalone);
   fChain->SetBranchAddress("MuonCand_ispfmuon", MuonCand_ispfmuon, &b_MuonCand_ispfmuon);
   fChain->SetBranchAddress("MuonCand_istight", MuonCand_istight, &b_MuonCand_istight);
   fChain->SetBranchAddress("MuonCandTrack_nmuchits", MuonCandTrack_nmuchits, &b_MuonCandTrack_nmuchits);
   fChain->SetBranchAddress("MuonCandTrack_chisq", MuonCandTrack_chisq, &b_MuonCandTrack_chisq);
   fChain->SetBranchAddress("MuonCand_innerTrackPt", MuonCand_innerTrackPt, &b_MuonCand_innerTrackPt);
   fChain->SetBranchAddress("MuonCand_innerTrackEta", MuonCand_innerTrackEta, &b_MuonCand_innerTrackEta);
   fChain->SetBranchAddress("MuonCand_innerTrackPhi", MuonCand_innerTrackPhi, &b_MuonCand_innerTrackPhi);
   fChain->SetBranchAddress("MuonCand_innerTrackVtxz", MuonCand_innerTrackVtxz, &b_MuonCand_innerTrackVtxz);
   fChain->SetBranchAddress("nGenMuonCand", &nGenMuonCand, &b_nGenMuonCand);
   fChain->SetBranchAddress("nGenMuonCandOutOfAccept", &nGenMuonCandOutOfAccept, &b_nGenMuonCandOutOfAccept);
   fChain->SetBranchAddress("GenMuonCand_pt", GenMuonCand_pt, &b_GenMuonCand_pt);
   fChain->SetBranchAddress("GenMuonCand_eta", GenMuonCand_eta, &b_GenMuonCand_eta);
   fChain->SetBranchAddress("GenMuonCand_phi", GenMuonCand_phi, &b_GenMuonCand_phi);
   fChain->SetBranchAddress("GenMuonCand_e", GenMuonCand_e, &b_GenMuonCand_e);
   fChain->SetBranchAddress("nGenProtCand", &nGenProtCand, &b_nGenProtCand);
   fChain->SetBranchAddress("GenProtCand_pt", GenProtCand_pt, &b_GenProtCand_pt);
   fChain->SetBranchAddress("GenProtCand_eta", GenProtCand_eta, &b_GenProtCand_eta);
   fChain->SetBranchAddress("GenProtCand_phi", GenProtCand_phi, &b_GenProtCand_phi);
   fChain->SetBranchAddress("GenProtCand_e", GenProtCand_e, &b_GenProtCand_e);
   fChain->SetBranchAddress("GenProtCand_status", GenProtCand_status, &b_GenProtCand_status);
   fChain->SetBranchAddress("nPrimVertexCand", &nPrimVertexCand, &b_nPrimVertexCand);
   fChain->SetBranchAddress("PrimVertexCand_x", PrimVertexCand_x, &b_PrimVertexCand_x);
   fChain->SetBranchAddress("PrimVertexCand_y", PrimVertexCand_y, &b_PrimVertexCand_y);
   fChain->SetBranchAddress("PrimVertexCand_z", PrimVertexCand_z, &b_PrimVertexCand_z);
   fChain->SetBranchAddress("PrimVertexCand_chi2", PrimVertexCand_chi2, &b_PrimVertexCand_chi2);
   fChain->SetBranchAddress("PrimVertexCand_ndof", PrimVertexCand_ndof, &b_PrimVertexCand_ndof);
   fChain->SetBranchAddress("PrimVertexCand_tracks", PrimVertexCand_tracks, &b_PrimVertexCand_tracks);
   fChain->SetBranchAddress("nPfCand", &nPfCand, &b_nPfCand);
   fChain->SetBranchAddress("PfCand_phi", PfCand_phi, &b_PfCand_phi);
   fChain->SetBranchAddress("PfCand_eta", PfCand_eta, &b_PfCand_eta);
   fChain->SetBranchAddress("PfCand_fromPV", PfCand_fromPV, &b_PfCand_fromPV);
   fChain->SetBranchAddress("PfCand_dz", PfCand_dz, &b_PfCand_dz);
   fChain->SetBranchAddress("nPair", &nPair, &b_nPair);
   fChain->SetBranchAddress("Pair_lepton1", &Pair_lepton1, &b_Pair_lepton1);
   fChain->SetBranchAddress("Pair_lepton2", &Pair_lepton2, &b_Pair_lepton2);
   fChain->SetBranchAddress("Pair_mass", &Pair_mass, &b_Pair_mass);
   fChain->SetBranchAddress("Pair_pt", &Pair_pt, &b_Pair_pt);
   fChain->SetBranchAddress("Pair_eta", &Pair_eta, &b_Pair_eta);
   fChain->SetBranchAddress("Pair_phi", &Pair_phi, &b_Pair_phi);
   fChain->SetBranchAddress("Pair_dpt", &Pair_dpt, &b_Pair_dpt);
   fChain->SetBranchAddress("Pair_dphi", &Pair_dphi, &b_Pair_dphi);
   fChain->SetBranchAddress("Pair_3Dangle", &Pair_3Dangle, &b_Pair_3Dangle);
   fChain->SetBranchAddress("Pair_extratracks0p5mm", &Pair_extratracks0p5mm, &b_Pair_extratracks0p5mm);
   fChain->SetBranchAddress("Pair_extratracks1mm", &Pair_extratracks1mm, &b_Pair_extratracks1mm);
   fChain->SetBranchAddress("Pair_extratracks2mm", &Pair_extratracks2mm, &b_Pair_extratracks2mm);
   fChain->SetBranchAddress("Pair_extratracks3mm", &Pair_extratracks3mm, &b_Pair_extratracks3mm);
   fChain->SetBranchAddress("Pair_extratracks4mm", &Pair_extratracks4mm, &b_Pair_extratracks4mm);
   fChain->SetBranchAddress("Pair_extratracks5mm", &Pair_extratracks5mm, &b_Pair_extratracks5mm);
   fChain->SetBranchAddress("Pair_extratracks1cm", &Pair_extratracks1cm, &b_Pair_extratracks1cm);
   fChain->SetBranchAddress("Pair_extratracks2cm", &Pair_extratracks2cm, &b_Pair_extratracks2cm);
   fChain->SetBranchAddress("Pair_extratracks3cm", &Pair_extratracks3cm, &b_Pair_extratracks3cm);
   fChain->SetBranchAddress("Pair_extratracks4cm", &Pair_extratracks4cm, &b_Pair_extratracks4cm);
   fChain->SetBranchAddress("Pair_extratracks5cm", &Pair_extratracks5cm, &b_Pair_extratracks5cm);
   fChain->SetBranchAddress("Pair_extratracks10cm", &Pair_extratracks10cm, &b_Pair_extratracks10cm);
   fChain->SetBranchAddress("KalmanVertexCand_x", &KalmanVertexCand_x, &b_KalmanVertexCand_x);
   fChain->SetBranchAddress("KalmanVertexCand_y", &KalmanVertexCand_y, &b_KalmanVertexCand_y);
   fChain->SetBranchAddress("KalmanVertexCand_z", &KalmanVertexCand_z, &b_KalmanVertexCand_z);
   fChain->SetBranchAddress("GenPair_mass", &GenPair_mass, &b_GenPair_mass);
   fChain->SetBranchAddress("GenPair_pt", &GenPair_pt, &b_GenPair_pt);
   fChain->SetBranchAddress("GenPair_eta", &GenPair_eta, &b_GenPair_eta);
   fChain->SetBranchAddress("GenPair_phi", &GenPair_phi, &b_GenPair_phi);
   fChain->SetBranchAddress("GenPair_dpt", &GenPair_dpt, &b_GenPair_dpt);
   fChain->SetBranchAddress("GenPair_dphi", &GenPair_dphi, &b_GenPair_dphi);
   fChain->SetBranchAddress("GenPair_3Dangle", &GenPair_3Dangle, &b_GenPair_3Dangle);
   fChain->SetBranchAddress("nLocalProtCand", &nLocalProtCand, &b_nLocalProtCand);
   fChain->SetBranchAddress("LocalProtCand_x", LocalProtCand_x, &b_LocalProtCand_x);
   fChain->SetBranchAddress("LocalProtCand_y", LocalProtCand_y, &b_LocalProtCand_y);
   fChain->SetBranchAddress("LocalProtCand_t", LocalProtCand_t, &b_LocalProtCand_t);
   fChain->SetBranchAddress("LocalProtCand_xSigma", LocalProtCand_xSigma, &b_LocalProtCand_xSigma);
   fChain->SetBranchAddress("LocalProtCand_ySigma", LocalProtCand_ySigma, &b_LocalProtCand_ySigma);
   fChain->SetBranchAddress("LocalProtCand_tSigma", LocalProtCand_tSigma, &b_LocalProtCand_tSigma);
   fChain->SetBranchAddress("LocalProtCand_arm", LocalProtCand_arm, &b_LocalProtCand_arm);
   fChain->SetBranchAddress("LocalProtCand_station", LocalProtCand_station, &b_LocalProtCand_station);
   fChain->SetBranchAddress("LocalProtCand_pot", LocalProtCand_pot, &b_LocalProtCand_pot);
   fChain->SetBranchAddress("LocalProtCand_rpid", LocalProtCand_rpid, &b_LocalProtCand_rpid);
   /*fChain->SetBranchAddress("nRecoProtCand", &nRecoProtCand, &b_nRecoProtCand);
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
     fChain->SetBranchAddress("ProtCand_trackpixshift2", ProtCand_trackpixshift2, &b_ProtCand_trackpixshift2);*/
   fChain->SetBranchAddress("nQualityExtraTrack", &nQualityExtraTrack, &b_nQualityExtraTrack);
   fChain->SetBranchAddress("ClosestExtraTrack_vtxdxyz", &ClosestExtraTrack_vtxdxyz, &b_ClosestExtraTrack_vtxdxyz);
   fChain->SetBranchAddress("ClosestExtraTrack_id", &ClosestExtraTrack_id, &b_ClosestExtraTrack_id);
   fChain->SetBranchAddress("ClosestHighPurityExtraTrack_vtxdxyz", &ClosestHighPurityExtraTrack_vtxdxyz, &b_ClosestHighPurityExtraTrack_vtxdxyz);
   fChain->SetBranchAddress("ClosestHighPurityExtraTrack_id", &ClosestHighPurityExtraTrack_id, &b_ClosestHighPurityExtraTrack_id);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   fChain->SetBranchAddress("PUWeightTrue", &PUWeightTrue, &b_PUWeightTrue);
   Notify();

   if( !mix_pileup ){
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
   } else {
      //mix_file = TFile::Open("/mnt/hadoop/cms/store/user/malvesga/pileup/pileup_protons_EG.root","READ");
      mix_file = TFile::Open( fileNamePileUp.c_str() );
      pileup_tree = (TTree*)mix_file->Get("pileup_protons");
      /*pileup_tree->SetBranchAddress("nRecoProtCand", &nRecoMixProtCand, &b_nRecoMixProtCand);
        pileup_tree->SetBranchAddress("ProtCand_xi", MixProtCand_xi, &b_MixProtCand_xi);
        pileup_tree->SetBranchAddress("ProtCand_t", MixProtCand_t, &b_MixProtCand_t);
        pileup_tree->SetBranchAddress("ProtCand_ThX", MixProtCand_ThX, &b_MixProtCand_ThX);
        pileup_tree->SetBranchAddress("ProtCand_ThY", MixProtCand_ThY, &b_MixProtCand_ThY);
        pileup_tree->SetBranchAddress("ProtCand_rpid", MixProtCand_rpid, &b_MixProtCand_rpid);
        pileup_tree->SetBranchAddress("ProtCand_arm", MixProtCand_arm, &b_MixProtCand_arm);
        pileup_tree->SetBranchAddress("ProtCand_ismultirp", MixProtCand_ismultirp, &b_MixProtCand_ismultirp);
        pileup_tree->SetBranchAddress("ProtCand_time", MixProtCand_time, &b_MixProtCand_time);
        pileup_tree->SetBranchAddress("ProtCand_trackx1", MixProtCand_trackx1, &b_MixProtCand_trackx1);
        pileup_tree->SetBranchAddress("ProtCand_tracky1", MixProtCand_tracky1, &b_MixProtCand_tracky1);
        pileup_tree->SetBranchAddress("ProtCand_trackx2", MixProtCand_trackx2, &b_MixProtCand_trackx2);
        pileup_tree->SetBranchAddress("ProtCand_tracky2", MixProtCand_tracky2, &b_MixProtCand_tracky2);
        pileup_tree->SetBranchAddress("ProtCand_rpid1", MixProtCand_rpid1, &b_MixProtCand_rpid1);
        pileup_tree->SetBranchAddress("ProtCand_rpid2", MixProtCand_rpid2, &b_MixProtCand_rpid2);
        pileup_tree->SetBranchAddress("ProtCand_trackpixshift1", MixProtCand_trackpixshift1, &b_MixProtCand_trackpixshift1);
        pileup_tree->SetBranchAddress("ProtCand_trackpixshift2", MixProtCand_trackpixshift2, &b_MixProtCand_trackpixshift2);*/
      pileup_tree->SetBranchAddress("nRecoProtCand", &nRecoProtCand, &b_nRecoMixProtCand);
      pileup_tree->SetBranchAddress("ProtCand_xi", ProtCand_xi, &b_MixProtCand_xi);
      pileup_tree->SetBranchAddress("ProtCand_t", ProtCand_t, &b_MixProtCand_t);
      pileup_tree->SetBranchAddress("ProtCand_ThX", ProtCand_ThX, &b_MixProtCand_ThX);
      pileup_tree->SetBranchAddress("ProtCand_ThY", ProtCand_ThY, &b_MixProtCand_ThY);
      pileup_tree->SetBranchAddress("ProtCand_rpid", ProtCand_rpid, &b_MixProtCand_rpid);
      pileup_tree->SetBranchAddress("ProtCand_arm", ProtCand_arm, &b_MixProtCand_arm);
      pileup_tree->SetBranchAddress("ProtCand_ismultirp", ProtCand_ismultirp, &b_MixProtCand_ismultirp);
      pileup_tree->SetBranchAddress("ProtCand_time", ProtCand_time, &b_MixProtCand_time);
      pileup_tree->SetBranchAddress("ProtCand_trackx1", ProtCand_trackx1, &b_MixProtCand_trackx1);
      pileup_tree->SetBranchAddress("ProtCand_tracky1", ProtCand_tracky1, &b_MixProtCand_tracky1);
      pileup_tree->SetBranchAddress("ProtCand_trackx2", ProtCand_trackx2, &b_MixProtCand_trackx2);
      pileup_tree->SetBranchAddress("ProtCand_tracky2", ProtCand_tracky2, &b_MixProtCand_tracky2);
      pileup_tree->SetBranchAddress("ProtCand_rpid1", ProtCand_rpid1, &b_MixProtCand_rpid1);
      pileup_tree->SetBranchAddress("ProtCand_rpid2", ProtCand_rpid2, &b_MixProtCand_rpid2);
      pileup_tree->SetBranchAddress("ProtCand_trackpixshift1", ProtCand_trackpixshift1, &b_MixProtCand_trackpixshift1);
      pileup_tree->SetBranchAddress("ProtCand_trackpixshift2", ProtCand_trackpixshift2, &b_MixProtCand_trackpixshift2);
   }
}

Bool_t ntp1::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ntp1::Show(Long64_t entry)
{
   // Print contents of entry.
   // If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ntp1::Cut(Long64_t entry)
{
   // This function may be called from Loop.
   // returns  1 if entry is accepted.
   // returns -1 otherwise.
   return 1;
}
#endif // #ifdef ntp1_cxx
