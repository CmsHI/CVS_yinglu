//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr  6 18:56:49 2011 by ROOT version 5.28/00
// from TTree Test/Test
// found on file: AllPhysics2760_Run2011A-PromptReco-v2.root
//////////////////////////////////////////////////////////

#ifndef PP_h
#define PP_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>


class PP {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           Run;
   Int_t           Lumi;
   Int_t           Bunch;
   Int_t           Event;
   Float_t         CaloMET;
   Float_t         CaloSumET;
   Float_t         CaloMETPhi;
   Int_t           nCaloJets;
   Float_t         CaloJet_HT20;
   Float_t         CaloJet_MHT20;
   Float_t         CaloJet_MHT20Phi;
   Float_t         CaloJet_rawHT20;
   Float_t         CaloJet_rawMHT20;
   Float_t         CaloJet_rawMHT20Phi;
   Int_t           CaloJet_n90Hits[85];   //[nCaloJets]
   Float_t         CaloJet_rawpt[85];   //[nCaloJets]
   Float_t         CaloJet_rawE[85];   //[nCaloJets]
   Float_t         CaloJet_rawphi[85];   //[nCaloJets]
   Float_t         CaloJet_raweta[85];   //[nCaloJets]
   Float_t         CaloJet_emf[85];   //[nCaloJets]
   Float_t         CaloJet_corpt[85];   //[nCaloJets]
   Float_t         CaloJet_corE[85];   //[nCaloJets]
   Float_t         CaloJet_coreta[85];   //[nCaloJets]
   Float_t         CaloJet_corphi[85];   //[nCaloJets]
   Float_t         CaloJet_fHPD[85];   //[nCaloJets]
   Float_t         CaloJet_fRBX[85];   //[nCaloJets]
   Int_t           CaloJet_n90[85];   //[nCaloJets]
   Float_t         CaloJet_etaMoment[85];   //[nCaloJets]
   Float_t         CaloJet_phiMoment[85];   //[nCaloJets]
   Float_t         CaloJet_HBE[85];   //[nCaloJets]
   Float_t         CaloJet_HEE[85];   //[nCaloJets]
   Float_t         CaloJet_HOE[85];   //[nCaloJets]
   Float_t         CaloJet_EBE[85];   //[nCaloJets]
   Float_t         CaloJet_EEE[85];   //[nCaloJets]
   Float_t         CaloJet_EMHFE[85];   //[nCaloJets]
   Int_t           nPhotons;
   Float_t         Photon_pt[25];   //[nPhotons]
   Float_t         Photon_E[25];   //[nPhotons]
   Float_t         Photon_eta[25];   //[nPhotons]
   Float_t         Photon_phi[25];   //[nPhotons]
   Float_t         Photon_HoverE[25];   //[nPhotons]
   Float_t         Photon_EcalIso[25];   //[nPhotons]
   Float_t         Photon_HcalIso[25];   //[nPhotons]
   Float_t         Photon_TrackIsoPtHol[25];   //[nPhotons]
   Float_t         Photon_TrackIsoPtSol[25];   //[nPhotons]
   Float_t         Photon_sigmaIetaIeta[25];   //[nPhotons]
   Float_t         Photon_r9[25];   //[nPhotons]
   Int_t           Photon_hasPixelSeed[25];   //[nPhotons]
   Int_t           Photon_isEGGap[25];   //[nPhotons]
   Int_t           Photon_isEB[25];   //[nPhotons]
   Int_t           Photon_isEBEEGap[25];   //[nPhotons]
   Int_t           Photon_isConv[25];   //[nPhotons]
   Float_t         Photon_ScE[25];   //[nPhotons]
   Float_t         Photon_ScRawE[25];   //[nPhotons]
   Float_t         Photon_ScEta[25];   //[nPhotons]
   Float_t         Photon_ScPhi[25];   //[nPhotons]
   Int_t           Photon_nTrackHol[25];   //[nPhotons]
   Int_t           Photon_nTrackSol[25];   //[nPhotons]
   Float_t         Photon_EcalIsoDR03[25];   //[nPhotons]
   Float_t         Photon_HcalIsoDR03[25];   //[nPhotons]
   Float_t         Photon_TrackIsoPtHolDR03[25];   //[nPhotons]
   Float_t         Photon_TrackIsoPtSolDR03[25];   //[nPhotons]
   Int_t           Photon_nTrackHolDR03[25];   //[nPhotons]
   Int_t           Photon_nTrackSolDR03[25];   //[nPhotons]
   Int_t           GenInfo_Size;
   Float_t         GenInfo_mChi0;
   Float_t         GenInfo_mGluino;
   Float_t         GenInfo_mSquark;
   Float_t         GenInfo_xsec;
   Int_t           GenInfo_Index[1];   //[GenInfo_Size]
   Int_t           GenInfo_Charge[1];   //[GenInfo_Size]
   Int_t           GenInfo_Status[1];   //[GenInfo_Size]
   Int_t           GenInfo_pdgId[1];   //[GenInfo_Size]
   Float_t         GenInfo_Pt[1];   //[GenInfo_Size]
   Float_t         GenInfo_Pz[1];   //[GenInfo_Size]
   Float_t         GenInfo_Mass[1];   //[GenInfo_Size]
   Float_t         GenInfo_Phi[1];   //[GenInfo_Size]
   Float_t         GenInfo_Eta[1];   //[GenInfo_Size]
   Float_t         GenInfo_Vx[1];   //[GenInfo_Size]
   Float_t         GenInfo_Vy[1];   //[GenInfo_Size]
   Float_t         GenInfo_Vz[1];   //[GenInfo_Size]
   Int_t           GenInfo_nMothers[1];   //[GenInfo_Size]
   Int_t           GenInfo_nDaughters[1];   //[GenInfo_Size]
   Int_t           GenInfo_momIndex[1];   //[GenInfo_Size]
   Int_t           GenInfo_dauIndex[1][10];   //[GenInfo_Size]
   Int_t           HLT_Jet20_v1_L1prescale;
   Int_t           HLT_Jet20_v1_HLTprescale;
   Int_t           HLT_Jet20_v1_fired;
   Int_t           HLT_Jet40_v1_L1prescale;
   Int_t           HLT_Jet40_v1_HLTprescale;
   Int_t           HLT_Jet40_v1_fired;
   Int_t           HLT_Jet60_v1_L1prescale;
   Int_t           HLT_Jet60_v1_HLTprescale;
   Int_t           HLT_Jet60_v1_fired;
   Int_t           HLT_ZeroBias_v1_L1prescale;
   Int_t           HLT_ZeroBias_v1_HLTprescale;
   Int_t           HLT_ZeroBias_v1_fired;
   Int_t           HLT_ZeroBiasPixel_SingleTrack_v1_L1prescale;
   Int_t           HLT_ZeroBiasPixel_SingleTrack_v1_HLTprescale;
   Int_t           HLT_ZeroBiasPixel_SingleTrack_v1_fired;

   // List of branches
   TBranch        *b_Run;   //!
   TBranch        *b_Lumi;   //!
   TBranch        *b_Bunch;   //!
   TBranch        *b_Event;   //!
   TBranch        *b_CaloMET;   //!
   TBranch        *b_CaloSumET;   //!
   TBranch        *b_CaloMETPhi;   //!
   TBranch        *b_nCaloJets;   //!
   TBranch        *b_Calojet_HT20;   //!
   TBranch        *b_Calojet_MHT20;   //!
   TBranch        *b_Calojet_MHT20Phi;   //!
   TBranch        *b_Calojet_rawHT20;   //!
   TBranch        *b_Calojet_rawMHT20;   //!
   TBranch        *b_Calojet_rawMHT20Phi;   //!
   TBranch        *b_CaloJet_n90Hits;   //!
   TBranch        *b_CaloJet_rawpt;   //!
   TBranch        *b_CaloJet_rawE;   //!
   TBranch        *b_CaloJet_rawphi;   //!
   TBranch        *b_CaloJet_raweta;   //!
   TBranch        *b_CaloJet_emf;   //!
   TBranch        *b_CaloJet_corpt;   //!
   TBranch        *b_CaloJet_corE;   //!
   TBranch        *b_CaloJet_coreta;   //!
   TBranch        *b_CaloJet_corphi;   //!
   TBranch        *b_CaloJet_fHPD;   //!
   TBranch        *b_CaloJet_fRBX;   //!
   TBranch        *b_CaloJet_n90;   //!
   TBranch        *b_CaloJet_etaMoment;   //!
   TBranch        *b_CaloJet_phiMoment;   //!
   TBranch        *b_CaloJet_HBE;   //!
   TBranch        *b_CaloJet_HEE;   //!
   TBranch        *b_CaloJet_HOE;   //!
   TBranch        *b_CaloJet_EBE;   //!
   TBranch        *b_CaloJet_EEE;   //!
   TBranch        *b_CaloJet_EMHFE;   //!
   TBranch        *b_nPhotons;   //!
   TBranch        *b_Photon_pt;   //!
   TBranch        *b_Photon_E;   //!
   TBranch        *b_Photon_eta;   //!
   TBranch        *b_Photon_phi;   //!
   TBranch        *b_Photon_HoverE;   //!
   TBranch        *b_Photon_EcalIso;   //!
   TBranch        *b_Photon_HcalIso;   //!
   TBranch        *b_Photon_TrackIsoPtHol;   //!
   TBranch        *b_Photon_TrackIsoPtSol;   //!
   TBranch        *b_Photon_sigmaIetaIeta;   //!
   TBranch        *b_Photon_r9;   //!
   TBranch        *b_Photon_hasPixelSeed;   //!
   TBranch        *b_Photon_isEGGap;   //!
   TBranch        *b_Photon_isEB;   //!
   TBranch        *b_Photon_isEBEEGap;   //!
   TBranch        *b_Photon_isConv;   //!
   TBranch        *b_Photon_ScE;   //!
   TBranch        *b_Photon_ScRawE;   //!
   TBranch        *b_Photon_ScEta;   //!
   TBranch        *b_Photon_ScPhi;   //!
   TBranch        *b_Photon_nTrackHol;   //!
   TBranch        *b_Photon_nTrackSol;   //!
   TBranch        *b_Photon_EcalIsoDR03;   //!
   TBranch        *b_Photon_HcalIsoDR03;   //!
   TBranch        *b_Photon_TrackIsoPtHolDR03;   //!
   TBranch        *b_Photon_TrackIsoPtSolDR03;   //!
   TBranch        *b_Photon_nTrackHolDR03;   //!
   TBranch        *b_Photon_nTrackSolDR03;   //!
   TBranch        *b_GenInfo_Size;   //!
   TBranch        *b_GenInfo_mChi0;   //!
   TBranch        *b_GenInfo_mGluino;   //!
   TBranch        *b_GenInfo_mSquark;   //!
   TBranch        *b_GenInfo_xsec;   //!
   TBranch        *b_GenInfo_Index;   //!
   TBranch        *b_GenInfo_Charge;   //!
   TBranch        *b_GenInfo_Status;   //!
   TBranch        *b_GenInfo_pdgId;   //!
   TBranch        *b_GenInfo_Pt;   //!
   TBranch        *b_GenInfo_Pz;   //!
   TBranch        *b_GenInfo_Mass;   //!
   TBranch        *b_GenInfo_Phi;   //!
   TBranch        *b_GenInfo_Eta;   //!
   TBranch        *b_GenInfo_Vx;   //!
   TBranch        *b_GenInfo_Vy;   //!
   TBranch        *b_GenInfo_Vz;   //!
   TBranch        *b_GenInfo_nMothers;   //!
   TBranch        *b_GenInfo_nDaughters;   //!
   TBranch        *b_GenInfo_momIndex;   //!
   TBranch        *b_GenInfo_dauIndex;   //!
   TBranch        *b_HLT_Jet20_v1;   //!
   TBranch        *b_HLT_Jet40_v1;   //!
   TBranch        *b_HLT_Jet60_v1;   //!
   TBranch        *b_HLT_ZeroBias_v1;   //!
   TBranch        *b_HLT_ZeroBiasPixel_SingleTrack_v1;   //!

   PP(TTree *tree=0);
   virtual ~PP();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual void     Fillhistos(Int_t);
   virtual void     normhistos(); 
   virtual void     drawhistos();
   virtual bool     pass_HLT_Jet(Int_t);
   virtual bool     pass_eta_pt(Int_t,Float_t,Int_t);
   virtual bool     pass_JetID(Int_t);
   virtual bool     pass_MET();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
	
	TH1F *hcorpt_leading;
	TH1F *hcoreta_leading;
	TH1F *hcorphi_leading;
	TH1F *hcoremf_leading;
	TH2F *hcor_etavsphi_leading;	
	TH1F *hcorpt_trailing;
	TH1F *hcoreta_trailing;
	TH1F *hcorphi_trailing;
	TH1F *hcoremf_trailing;
	TH2F *hcor_etavsphi_trailing;
	
	TH1F *hcorpt;
	TH1F *hcoreta;
	TH1F *hcorphi;
	TH1F *hcoremf;
	TH2F *hcor_etavsphi;
	
	TH1F *hdN_dpt_cor;
	TH1F *hcor_MET;
	TH1F *hcor_SumET;
	TH1F *hcor_fMET;
	
	


};

#endif

#ifdef PP_cxx
PP::PP(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("AllPhysics2760_Run2011A-PromptReco-v2.root");
      if (!f) {
         f = new TFile("AllPhysics2760_Run2011A-PromptReco-v2.root");
         f->cd("AllPhysics2760_Run2011A-PromptReco-v2.root:/dave");
      }
      tree = (TTree*)gDirectory->Get("Test");

   }
   Init(tree);
}

PP::~PP()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t PP::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t PP::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void PP::Init(TTree *tree)
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

   fChain->SetBranchAddress("Run", &Run, &b_Run);
   fChain->SetBranchAddress("Lumi", &Lumi, &b_Lumi);
   fChain->SetBranchAddress("Bunch", &Bunch, &b_Bunch);
   fChain->SetBranchAddress("Event", &Event, &b_Event);
   fChain->SetBranchAddress("CaloMET", &CaloMET, &b_CaloMET);
   fChain->SetBranchAddress("CaloSumET", &CaloSumET, &b_CaloSumET);
   fChain->SetBranchAddress("CaloMETPhi", &CaloMETPhi, &b_CaloMETPhi);
   fChain->SetBranchAddress("nCaloJets", &nCaloJets, &b_nCaloJets);
   fChain->SetBranchAddress("CaloJet_HT20", &CaloJet_HT20, &b_Calojet_HT20);
   fChain->SetBranchAddress("CaloJet_MHT20", &CaloJet_MHT20, &b_Calojet_MHT20);
   fChain->SetBranchAddress("CaloJet_MHT20Phi", &CaloJet_MHT20Phi, &b_Calojet_MHT20Phi);
   fChain->SetBranchAddress("CaloJet_rawHT20", &CaloJet_rawHT20, &b_Calojet_rawHT20);
   fChain->SetBranchAddress("CaloJet_rawMHT20", &CaloJet_rawMHT20, &b_Calojet_rawMHT20);
   fChain->SetBranchAddress("CaloJet_rawMHT20Phi", &CaloJet_rawMHT20Phi, &b_Calojet_rawMHT20Phi);
   fChain->SetBranchAddress("CaloJet_n90Hits", CaloJet_n90Hits, &b_CaloJet_n90Hits);
   fChain->SetBranchAddress("CaloJet_rawpt", CaloJet_rawpt, &b_CaloJet_rawpt);
   fChain->SetBranchAddress("CaloJet_rawE", CaloJet_rawE, &b_CaloJet_rawE);
   fChain->SetBranchAddress("CaloJet_rawphi", CaloJet_rawphi, &b_CaloJet_rawphi);
   fChain->SetBranchAddress("CaloJet_raweta", CaloJet_raweta, &b_CaloJet_raweta);
   fChain->SetBranchAddress("CaloJet_emf", CaloJet_emf, &b_CaloJet_emf);
   fChain->SetBranchAddress("CaloJet_corpt", CaloJet_corpt, &b_CaloJet_corpt);
   fChain->SetBranchAddress("CaloJet_corE", CaloJet_corE, &b_CaloJet_corE);
   fChain->SetBranchAddress("CaloJet_coreta", CaloJet_coreta, &b_CaloJet_coreta);
   fChain->SetBranchAddress("CaloJet_corphi", CaloJet_corphi, &b_CaloJet_corphi);
   fChain->SetBranchAddress("CaloJet_fHPD", CaloJet_fHPD, &b_CaloJet_fHPD);
   fChain->SetBranchAddress("CaloJet_fRBX", CaloJet_fRBX, &b_CaloJet_fRBX);
   fChain->SetBranchAddress("CaloJet_n90", CaloJet_n90, &b_CaloJet_n90);
   fChain->SetBranchAddress("CaloJet_etaMoment", CaloJet_etaMoment, &b_CaloJet_etaMoment);
   fChain->SetBranchAddress("CaloJet_phiMoment", CaloJet_phiMoment, &b_CaloJet_phiMoment);
   fChain->SetBranchAddress("CaloJet_HBE", CaloJet_HBE, &b_CaloJet_HBE);
   fChain->SetBranchAddress("CaloJet_HEE", CaloJet_HEE, &b_CaloJet_HEE);
   fChain->SetBranchAddress("CaloJet_HOE", CaloJet_HOE, &b_CaloJet_HOE);
   fChain->SetBranchAddress("CaloJet_EBE", CaloJet_EBE, &b_CaloJet_EBE);
   fChain->SetBranchAddress("CaloJet_EEE", CaloJet_EEE, &b_CaloJet_EEE);
   fChain->SetBranchAddress("CaloJet_EMHFE", CaloJet_EMHFE, &b_CaloJet_EMHFE);
   fChain->SetBranchAddress("nPhotons", &nPhotons, &b_nPhotons);
   fChain->SetBranchAddress("Photon_pt", Photon_pt, &b_Photon_pt);
   fChain->SetBranchAddress("Photon_E", Photon_E, &b_Photon_E);
   fChain->SetBranchAddress("Photon_eta", Photon_eta, &b_Photon_eta);
   fChain->SetBranchAddress("Photon_phi", Photon_phi, &b_Photon_phi);
   fChain->SetBranchAddress("Photon_HoverE", Photon_HoverE, &b_Photon_HoverE);
   fChain->SetBranchAddress("Photon_EcalIso", Photon_EcalIso, &b_Photon_EcalIso);
   fChain->SetBranchAddress("Photon_HcalIso", Photon_HcalIso, &b_Photon_HcalIso);
   fChain->SetBranchAddress("Photon_TrackIsoPtHol", Photon_TrackIsoPtHol, &b_Photon_TrackIsoPtHol);
   fChain->SetBranchAddress("Photon_TrackIsoPtSol", Photon_TrackIsoPtSol, &b_Photon_TrackIsoPtSol);
   fChain->SetBranchAddress("Photon_sigmaIetaIeta", Photon_sigmaIetaIeta, &b_Photon_sigmaIetaIeta);
   fChain->SetBranchAddress("Photon_r9", Photon_r9, &b_Photon_r9);
   fChain->SetBranchAddress("Photon_hasPixelSeed", Photon_hasPixelSeed, &b_Photon_hasPixelSeed);
   fChain->SetBranchAddress("Photon_isEGGap", Photon_isEGGap, &b_Photon_isEGGap);
   fChain->SetBranchAddress("Photon_isEB", Photon_isEB, &b_Photon_isEB);
   fChain->SetBranchAddress("Photon_isEBEEGap", Photon_isEBEEGap, &b_Photon_isEBEEGap);
   fChain->SetBranchAddress("Photon_isConv", Photon_isConv, &b_Photon_isConv);
   fChain->SetBranchAddress("Photon_ScE", Photon_ScE, &b_Photon_ScE);
   fChain->SetBranchAddress("Photon_ScRawE", Photon_ScRawE, &b_Photon_ScRawE);
   fChain->SetBranchAddress("Photon_ScEta", Photon_ScEta, &b_Photon_ScEta);
   fChain->SetBranchAddress("Photon_ScPhi", Photon_ScPhi, &b_Photon_ScPhi);
   fChain->SetBranchAddress("Photon_nTrackHol", Photon_nTrackHol, &b_Photon_nTrackHol);
   fChain->SetBranchAddress("Photon_nTrackSol", Photon_nTrackSol, &b_Photon_nTrackSol);
   fChain->SetBranchAddress("Photon_EcalIsoDR03", Photon_EcalIsoDR03, &b_Photon_EcalIsoDR03);
   fChain->SetBranchAddress("Photon_HcalIsoDR03", Photon_HcalIsoDR03, &b_Photon_HcalIsoDR03);
   fChain->SetBranchAddress("Photon_TrackIsoPtHolDR03", Photon_TrackIsoPtHolDR03, &b_Photon_TrackIsoPtHolDR03);
   fChain->SetBranchAddress("Photon_TrackIsoPtSolDR03", Photon_TrackIsoPtSolDR03, &b_Photon_TrackIsoPtSolDR03);
   fChain->SetBranchAddress("Photon_nTrackHolDR03", Photon_nTrackHolDR03, &b_Photon_nTrackHolDR03);
   fChain->SetBranchAddress("Photon_nTrackSolDR03", Photon_nTrackSolDR03, &b_Photon_nTrackSolDR03);
   fChain->SetBranchAddress("GenInfo_Size", &GenInfo_Size, &b_GenInfo_Size);
   fChain->SetBranchAddress("GenInfo_mChi0", &GenInfo_mChi0, &b_GenInfo_mChi0);
   fChain->SetBranchAddress("GenInfo_mGluino", &GenInfo_mGluino, &b_GenInfo_mGluino);
   fChain->SetBranchAddress("GenInfo_mSquark", &GenInfo_mSquark, &b_GenInfo_mSquark);
   fChain->SetBranchAddress("GenInfo_xsec", &GenInfo_xsec, &b_GenInfo_xsec);
   fChain->SetBranchAddress("GenInfo_Index", &GenInfo_Index, &b_GenInfo_Index);
   fChain->SetBranchAddress("GenInfo_Charge", &GenInfo_Charge, &b_GenInfo_Charge);
   fChain->SetBranchAddress("GenInfo_Status", &GenInfo_Status, &b_GenInfo_Status);
   fChain->SetBranchAddress("GenInfo_pdgId", &GenInfo_pdgId, &b_GenInfo_pdgId);
   fChain->SetBranchAddress("GenInfo_Pt", &GenInfo_Pt, &b_GenInfo_Pt);
   fChain->SetBranchAddress("GenInfo_Pz", &GenInfo_Pz, &b_GenInfo_Pz);
   fChain->SetBranchAddress("GenInfo_Mass", &GenInfo_Mass, &b_GenInfo_Mass);
   fChain->SetBranchAddress("GenInfo_Phi", &GenInfo_Phi, &b_GenInfo_Phi);
   fChain->SetBranchAddress("GenInfo_Eta", &GenInfo_Eta, &b_GenInfo_Eta);
   fChain->SetBranchAddress("GenInfo_Vx", &GenInfo_Vx, &b_GenInfo_Vx);
   fChain->SetBranchAddress("GenInfo_Vy", &GenInfo_Vy, &b_GenInfo_Vy);
   fChain->SetBranchAddress("GenInfo_Vz", &GenInfo_Vz, &b_GenInfo_Vz);
   fChain->SetBranchAddress("GenInfo_nMothers", &GenInfo_nMothers, &b_GenInfo_nMothers);
   fChain->SetBranchAddress("GenInfo_nDaughters", &GenInfo_nDaughters, &b_GenInfo_nDaughters);
   fChain->SetBranchAddress("GenInfo_momIndex", &GenInfo_momIndex, &b_GenInfo_momIndex);
   fChain->SetBranchAddress("GenInfo_dauIndex", &GenInfo_dauIndex, &b_GenInfo_dauIndex);
   fChain->SetBranchAddress("HLT_Jet20_v1", &HLT_Jet20_v1_L1prescale, &b_HLT_Jet20_v1);
   fChain->SetBranchAddress("HLT_Jet40_v1", &HLT_Jet40_v1_L1prescale, &b_HLT_Jet40_v1);
   fChain->SetBranchAddress("HLT_Jet60_v1", &HLT_Jet60_v1_L1prescale, &b_HLT_Jet60_v1);
   fChain->SetBranchAddress("HLT_ZeroBias_v1", &HLT_ZeroBias_v1_L1prescale, &b_HLT_ZeroBias_v1);
   fChain->SetBranchAddress("HLT_ZeroBiasPixel_SingleTrack_v1", &HLT_ZeroBiasPixel_SingleTrack_v1_L1prescale, &b_HLT_ZeroBiasPixel_SingleTrack_v1);
   Notify();
}

Bool_t PP::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void PP::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t PP::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef PP_cxx
