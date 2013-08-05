#if !defined(__CINT__) || defined(__MAKECINT__)

#include "hiForest.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TMath.h"
#include "TLegend.h"


#endif



void drawCentTex(const int centbin);

void HcalNoise(int algo, int month, int date) // ic5=1;ak2=2;ak3=3; ak4=4...
{	

	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();
	
	
	
	float ptmax = 300.0;
	float ptmin = 100.0;
	
	const int int NBINS = 12;
	Double_t BOUNDARIES[NBINS] = {
100, 110, 120, 130, 140, 150, 160, 170,180, 200, 240, 300
};


	HiForest *c = new HiForest("/hadoop/store/user/belt/hiForest2/HiForest-ppskim-hihighpt-pt90-v1_v3_part.root","hif",1,0);
	HiForest *b = new HiForest("/hadoop/store/user/belt/hiForest2/HiForest-promptskim-hihighpt-hltjet80-pt90-v3_part.root");
	


		///// pp DATA

		// Jet spectra


		TH1F* hcorpt_pp= new TH1F("hcorpt_pp","All jets with selection;p_{T}; 1/N dN_{Jets}/dp_{T}",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pp_NoRej= new TH1F("hcorpt_pp_NoRej","All jets with selection;p_{T}; 1/N dN_{Jets}/dp_{T}",NBINS-1,BOUNDARIES);
		
   		TCanvas *c1 = new TCanvas("c1","");
		
		if (algo == 1)
		c->tree->Draw("icPu5.jtpt>>hcorpt_pp","abs(evtTree.vz[1])<15 && icPu5.trackMax/icPu5.jtpt>0.01 && hltTree.HLT_Jet60_v1 &&icPu5.jtpt>100 && abs(icPu5.jteta)<2 && skim.pcollisionEventSelection&& skim.pHBHENoiseFilter","e");
		
		if (algo == 2)
		c->tree->Draw("ak2PF.jtpt>>hcorpt_pp","abs(evtTree.vz[1])<15 && ak2PF.trackMax/ak2PF.jtpt>0.01 && hltTree.HLT_Jet60_v1&& ak2PF.jtpt>100 && abs(ak2PF.jteta)<2 && skim.pcollisionEventSelection&& skim.pHBHENoiseFilter","e");
		
		if (algo == 3)
		c->tree->Draw("ak3PF.jtpt>>hcorpt_pp","abs(evtTree.vz[1])<15 && ak3PF.trackMax/ak3PF.jtpt>0.01 && hltTree.HLT_Jet60_v1&& ak3PF.jtpt>100 && abs(ak3PF.jteta)<2 && skim.pcollisionEventSelection&& skim.pHBHENoiseFilter","e");
		
		if (algo == 4)
		c->tree->Draw("ak4PF.jtpt>>hcorpt_pp","abs(evtTree.vz[1])<15 && ak4PF.trackMax/ak4PF.jtpt>0.01 && hltTree.HLT_Jet60_v1&& ak4PF.jtpt>100 && abs(ak4PF.jteta)<2 && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","e");
		
		
		if (algo == 1)
		c->tree->Draw("icPu5.jtpt>>hcorpt_pp_NoRej","abs(evtTree.vz[1])<15 && icPu5.trackMax/icPu5.jtpt>0.01 && hltTree.HLT_Jet60_v1 &&icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection","e");
		
		if (algo == 2)
		c->tree->Draw("ak2PF.jtpt>>hcorpt_pp_NoRej","abs(evtTree.vz[1])<15 && ak2PF.trackMax/ak2PF.jtpt>0.01 && hltTree.HLT_Jet60_v1&& akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2 && skim.pcollisionEventSelection","e");
		
		if (algo == 3)
		c->tree->Draw("ak3PF.jtpt>>hcorpt_pp_NoRej","abs(evtTree.vz[1])<15 && ak3PF.trackMax/ak3PF.jtpt>0.01 && hltTree.HLT_Jet60_v1&& ak3PF.jtpt>100 && abs(ak3PF.jteta)<2 && skim.pcollisionEventSelection","e");
		
		if (algo == 4)
		c->tree->Draw("ak4PF.jtpt>>hcorpt_pp_NoRej","abs(evtTree.vz[1])<15 && ak4PF.trackMax/ak4PF.jtpt>0.01 && hltTree.HLT_Jet60_v1&& ak4PF.jtpt>100 && abs(ak4PF.jteta)<2 && skim.pcollisionEventSelection","e");
		
	
    	///// HEAVY ION DATA

		// Jet spectra
		
		TH1F* hcorpt_pbpb_cent1 = new TH1F("hcorpt_pbpb_cent1","All jets with selection;Jet p_{T} (GeV/c); Entries",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent2 = new TH1F("hcorpt_pbpb_cent2","All jets with selection;Jet p_{T} (GeV/c); Entries",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent3 = new TH1F("hcorpt_pbpb_cent3","All jets with selection;Jet p_{T} (GeV/c); Entries",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent4 = new TH1F("hcorpt_pbpb_cent4","All jets with selection;Jet p_{T} (GeV/c); Entries",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent5 = new TH1F("hcorpt_pbpb_cent5","All jets with selection;Jet p_{T} (GeV/c); Entries",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent6 = new TH1F("hcorpt_pbpb_cent6","All jets with selection;Jet p_{T} (GeV/c); Entries",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent7 = new TH1F("hcorpt_pbpb_cent7","All jets with selection;Jet p_{T} (GeV/c); Entries",NBINS-1,BOUNDARIES);
	
		TH1F* hcorpt_pbpb_cent1_NoRej = new TH1F("hcorpt_pbpb_cent1_NoRej","All jets with selection;Jet p_{T} (GeV/c); Entries",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent2_NoRej = new TH1F("hcorpt_pbpb_cent2_NoRej","All jets with selection;Jet p_{T} (GeV/c); Entries",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent3_NoRej = new TH1F("hcorpt_pbpb_cent3_NoRej","All jets with selection;Jet p_{T} (GeV/c); Entries",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent4_NoRej = new TH1F("hcorpt_pbpb_cent4_NoRej","All jets with selection;Jet p_{T} (GeV/c); Entries",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent5_NoRej = new TH1F("hcorpt_pbpb_cent5_NoRej","All jets with selection;Jet p_{T} (GeV/c); Entries",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent6_NoRej = new TH1F("hcorpt_pbpb_cent6_NoRej","All jets with selection;Jet p_{T} (GeV/c); Entries",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent7_NoRej = new TH1F("hcorpt_pbpb_cent7_NoRej","All jets with selection;Jet p_{T} (GeV/c); Entries",NBINS-1,BOUNDARIES);
		
		
		TH1F* NoiseRatio = new TH1F("NoiseRatio","Noise Ratio;Jet p_{T} (GeV/c); Ratio",NBINS-1,BOUNDARIES);

		
   		TCanvas *c2 = new TCanvas("c2","");
		gPad->SetLogy();
	    
	    //central events as 0-5%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent1", "abs(evtTree.vz[1])<15 && icPu5.trackMax/icPu5.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin<2 && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","e");
		
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent1", "abs(evtTree.vz[1])<15 && akPu2PF.trackMax/akPu2PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin<2 && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","e");
		
		if (algo == 3)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent1", "abs(evtTree.vz[1])<15 && akPu3PF.trackMax/akPu3PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin<2 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","e");
		
		if (algo == 4)
		b->tree->Draw("akPu4PF.jtpt>>hcorpt_pbpb_cent1", "abs(evtTree.vz[1])<15 && akPu4PF.trackMax/akPu4PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin<2 && akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","e");
		
		
		//central events as 5-10%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent2", "abs(evtTree.vz[1])<15 && icPu5.trackMax/icPu5.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>1 && evtTree.hiBin<4 && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent2", "abs(evtTree.vz[1])<15 && akPu2PF.trackMax/akPu2PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>1 && evtTree.hiBin<4 && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent2", "abs(evtTree.vz[1])<15 && akPu3PF.trackMax/akPu3PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>1 && evtTree.hiBin<4 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 4)
		b->tree->Draw("akP4PF.jtpt>>hcorpt_pbpb_cent2", "abs(evtTree.vz[1])<15 && akPu4PF.trackMax/akPu4PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>1 && evtTree.hiBin<4 && akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		
		
		
		//central events as 10-30%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent3", "abs(evtTree.vz[1])<15 && icPu5.trackMax/icPu5.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>3 && evtTree.hiBin<12 && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent3", "abs(evtTree.vz[1])<15 && akPu2PF.trackMax/akPu2PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 &&  evtTree.hiBin>3 && evtTree.hiBin<12  && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent3", "abs(evtTree.vz[1])<15 && akPu3PF.trackMax/akPu3PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 &&  evtTree.hiBin>3 && evtTree.hiBin<12  && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 4)
		b->tree->Draw("akPu4PF.jtpt>>hcorpt_pbpb_cent3", "abs(evtTree.vz[1])<15 && akPu4PF.trackMax/akPu4PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>3 && evtTree.hiBin<12 && akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		
		
		//central events as 30-50%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent4", "abs(evtTree.vz[1])<15 && icPu5.trackMax/icPu5.jtpt>0.01 && hltTree.HLT_HIJet80_v1 &&  evtTree.hiBin>11 && evtTree.hiBin<20  && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent4", "abs(evtTree.vz[1])<15 && akPu2PF.trackMax/akPu2PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>11 && evtTree.hiBin<20  && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent4", "abs(evtTree.vz[1])<15 && akPu3PF.trackMax/akPu3PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>11 && evtTree.hiBin<20  && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 4)
		b->tree->Draw("akPu4PF.jtpt>>hcorpt_pbpb_cent4", "abs(evtTree.vz[1])<15 && akPu4PF.trackMax/akPu4PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>11 && evtTree.hiBin<20  && akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		
		
		
		//central events as 50-70%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent5", "abs(evtTree.vz[1])<15 && icPu5.trackMax/icPu5.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && evtTree.hiBin<28 && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent5", "abs(evtTree.vz[1])<15 && akPu2PF.trackMax/akPu2PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && evtTree.hiBin<28  && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent5", "abs(evtTree.vz[1])<15 && akPu3PF.trackMax/akPu3PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && evtTree.hiBin<28  && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 4)
		b->tree->Draw("akPu4PF.jtpt>>hcorpt_pbpb_cent5", "abs(evtTree.vz[1])<15 && akPu4PF.trackMax/akPu4PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && evtTree.hiBin<28 && akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		
		//central events as 70-90%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent6", "abs(evtTree.vz[1])<15 && icPu5.trackMax/icPu5.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>27 && evtTree.hiBin<36 && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent6", "abs(evtTree.vz[1])<15 && akPu2PF.trackMax/akPu2PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>27 && evtTree.hiBin<36 && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent6", "abs(evtTree.vz[1])<15 && akPu3PF.trackMax/akPu3PF.jtpt>0.01 && abs(evtTree.vz[1])<15 && akPu2PF.trackMax/akPu2PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>27 && evtTree.hiBin<36 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 4)
		b->tree->Draw("akPu4PF.jtpt>>hcorpt_pbpb_cent6", "abs(evtTree.vz[1])<15 && akPu4PF.trackMax/akPu4PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>27 && evtTree.hiBin<36 && akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		
		//central events as 0-90%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent7", "abs(evtTree.vz[1])<15 && icPu5.trackMax/icPu5.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>-1 && evtTree.hiBin<36 && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent7", "abs(evtTree.vz[1])<15 && akPu2PF.trackMax/akPu2PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>-1 && evtTree.hiBin<36 && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent7", "abs(evtTree.vz[1])<15 && akPu3PF.trackMax/akPu3PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>-1 && evtTree.hiBin<36 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 4)
		b->tree->Draw("akPu4PF.jtpt>>hcorpt_pbpb_cent7", "abs(evtTree.vz[1])<15 && akPu4PF.trackMax/akPu4PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>-1 && evtTree.hiBin<36 && akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		
		//////// No Noise Rejection
		
		
		
		 //central events as 0-5%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent1_NoRej", "abs(evtTree.vz[1])<15 && icPu5.trackMax/icPu5.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin<2 && icPu5.jtpt>100 && abs(icPu5.jteta)<2 && skim.pcollisionEventSelection","e");
		
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent1_NoRej", "abs(evtTree.vz[1])<15 && akPu2PF.trackMax/akPu2PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin<2 && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2 && skim.pcollisionEventSelection","e");
		
		if (algo == 3)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent1_NoRej", "abs(evtTree.vz[1])<15 && akPu3PF.trackMax/akPu3PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin<2 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2 && skim.pcollisionEventSelection","e");
		
		if (algo == 4)
		b->tree->Draw("akPu4PF.jtpt>>hcorpt_pbpb_cent1_NoRej", "abs(evtTree.vz[1])<15 && akPu4PF.trackMax/akPu4PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin<2 && akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2 && skim.pcollisionEventSelection","e");
		
		
		//central events as 5-10%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent2_NoRej", "abs(evtTree.vz[1])<15 && icPu5.trackMax/icPu5.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>1 && evtTree.hiBin<4 && icPu5.jtpt>100 && abs(icPu5.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent2_NoRej", "abs(evtTree.vz[1])<15 && akPu2PF.trackMax/akPu2PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>1 && evtTree.hiBin<4 && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent2_NoRej", "abs(evtTree.vz[1])<15 && akPu3PF.trackMax/akPu3PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>1 && evtTree.hiBin<4 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		if (algo == 4)
		b->tree->Draw("akPu4PF.jtpt>>hcorpt_pbpb_cent2_NoRej", "abs(evtTree.vz[1])<15 && akPu4PF.trackMax/akPu4PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>1 && evtTree.hiBin<4 && akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		
		
		
		//central events as 10-30%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent3_NoRej", "abs(evtTree.vz[1])<15 && icPu5.trackMax/icPu5.jtpt>0.01&& hltTree.HLT_HIJet80_v1 && evtTree.hiBin>3 && evtTree.hiBin<12 && icPu5.jtpt>100 && abs(icPu5.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent3_NoRej", "abs(evtTree.vz[1])<15 && akPu2PF.trackMax/akPu2PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 &&  evtTree.hiBin>3 && evtTree.hiBin<12  && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent3_NoRej", "abs(evtTree.vz[1])<15 && akPu3PF.trackMax/akPu3PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 &&  evtTree.hiBin>3 && evtTree.hiBin<12  && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		if (algo == 4)
		b->tree->Draw("akPu4PF.jtpt>>hcorpt_pbpb_cent3_NoRej", "abs(evtTree.vz[1])<15 && akPu4PF.trackMax/akPu4PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>3 && evtTree.hiBin<12 && akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		
		
		//central events as 30-50%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent4_NoRej", "abs(evtTree.vz[1])<15 && icPu5.trackMax/icPu5.jtpt>0.01&& hltTree.HLT_HIJet80_v1 &&  evtTree.hiBin>11 && evtTree.hiBin<20  && icPu5.jtpt>100 && abs(icPu5.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent4_NoRej", "abs(evtTree.vz[1])<15 && akPu2PF.trackMax/akPu2PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>11 && evtTree.hiBin<20  && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent4_NoRej", "abs(evtTree.vz[1])<15 && akPu3PF.trackMax/akPu3PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>11 && evtTree.hiBin<20  && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		if (algo == 4)
		b->tree->Draw("akPu4PF.jtpt>>hcorpt_pbpb_cent4_NoRej", "abs(evtTree.vz[1])<15 && akPu4PF.trackMax/akPu4PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>11 && evtTree.hiBin<20  && akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		
		
		
		//central events as 50-70%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent5_NoRej", "abs(evtTree.vz[1])<15 && icPu5.trackMax/icPu5.jtpt>0.01&& hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && evtTree.hiBin<28 && icPu5.jtpt>100 && abs(icPu5.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent5_NoRej", "abs(evtTree.vz[1])<15 && akPu2PF.trackMax/akPu2PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && evtTree.hiBin<28  && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent5_NoRej", "abs(evtTree.vz[1])<15 && akPu3PF.trackMax/akPu3PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && evtTree.hiBin<28  && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		if (algo == 4)
		b->tree->Draw("akPu4PF.jtpt>>hcorpt_pbpb_cent5_NoRej", "abs(evtTree.vz[1])<15 && akPu4PF.trackMax/akPu4PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && evtTree.hiBin<28 && akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		
		//central events as 70-90%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent6_NoRej", "abs(evtTree.vz[1])<15 && icPu5.trackMax/icPu5.jtpt>0.01&& hltTree.HLT_HIJet80_v1 && evtTree.hiBin>27 && evtTree.hiBin<36 && icPu5.jtpt>100 && abs(icPu5.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent6_NoRej", "abs(evtTree.vz[1])<15 && akPu2PF.trackMax/akPu2PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>27 && evtTree.hiBin<36 && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent6_NoRej", "abs(evtTree.vz[1])<15 && akPu3PF.trackMax/akPu3PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>27 && evtTree.hiBin<36 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		if (algo == 4)
		b->tree->Draw("akPu4PF.jtpt>>hcorpt_pbpb_cent6_NoRej", "abs(evtTree.vz[1])<15 && akPu4PF.trackMax/akPu4PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>27 && evtTree.hiBin<36 && akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		
		//central events as 0-90%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent7_NoRej", "abs(evtTree.vz[1])<15 && icPu5.trackMax/icPu5.jtpt>0.01&& hltTree.HLT_HIJet80_v1 && evtTree.hiBin>-1 && evtTree.hiBin<36 && icPu5.jtpt>100 && abs(icPu5.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent7_NoRej", "abs(evtTree.vz[1])<15 && akPu2PF.trackMax/akPu2PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>-1 && evtTree.hiBin<36 && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent7_NoRej", "abs(evtTree.vz[1])<15 && akPu3PF.trackMax/akPu3PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>-1 && evtTree.hiBin<36 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		if (algo == 4)
		b->tree->Draw("akPu4PF.jtpt>>hcorpt_pbpb_cent7_NoRej", "abs(evtTree.vz[1])<15 && akPu4PF.trackMax/akPu4PF.jtpt>0.01 && hltTree.HLT_HIJet80_v1 && evtTree.hiBin>-1 && evtTree.hiBin<36 && akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2 && skim.pcollisionEventSelection","esame");
		
		
		gROOT->LoadMacro("erf.C");
	
	
		TGraphAsymmErrors *Ratio1= new TGraphAsymmErrors;
		TGraphAsymmErrors *Ratio2= new TGraphAsymmErrors;
		TGraphAsymmErrors *Ratio3= new TGraphAsymmErrors;
		TGraphAsymmErrors *Ratio4= new TGraphAsymmErrors;
		TGraphAsymmErrors *Ratio5= new TGraphAsymmErrors;
		TGraphAsymmErrors *Ratio6= new TGraphAsymmErrors;
		TGraphAsymmErrors *Ratio7= new TGraphAsymmErrors;
		TGraphAsymmErrors *Ratio_pp= new TGraphAsymmErrors;
		
		Ratio1->BayesDivide(hcorpt_pbpb_cent1,hcorpt_pbpb_cent1_NoRej);
		Ratio2->BayesDivide(hcorpt_pbpb_cent2,hcorpt_pbpb_cent2_NoRej);
		Ratio3->BayesDivide(hcorpt_pbpb_cent3,hcorpt_pbpb_cent3_NoRej);
		Ratio4->BayesDivide(hcorpt_pbpb_cent4,hcorpt_pbpb_cent4_NoRej);
		Ratio5->BayesDivide(hcorpt_pbpb_cent5,hcorpt_pbpb_cent5_NoRej);
		Ratio6->BayesDivide(hcorpt_pbpb_cent6,hcorpt_pbpb_cent6_NoRej);
		Ratio7->BayesDivide(hcorpt_pbpb_cent7,hcorpt_pbpb_cent7_NoRej);
		Ratio_pp->BayesDivide(hcorpt_pp,hcorpt_pp_NoRej);
		
		
		
		/*
		
		hcorpt_pp->Scale(0.1);
		hcorpt_pbpb_cent1->Scale(1);
		hcorpt_pbpb_cent2->Scale(10);
		hcorpt_pbpb_cent3->Scale(100);
		hcorpt_pbpb_cent4->Scale(1000);
		hcorpt_pbpb_cent5->Scale(10000);
		hcorpt_pbpb_cent6->Scale(100000);
		
		hcorpt_pp_NoRej->Scale(0.1);
		hcorpt_pbpb_cent1_NoRej->Scale(1);
		hcorpt_pbpb_cent2_NoRej->Scale(10);
		hcorpt_pbpb_cent3_NoRej->Scale(100);
		hcorpt_pbpb_cent4_NoRej->Scale(1000);
		hcorpt_pbpb_cent5_NoRej->Scale(10000);
		hcorpt_pbpb_cent6_NoRej->Scale(100000);
		
	
		
		

		
		TCanvas *c3 = new TCanvas("c3","c3",500,800);
		c3->Divide(1,2,0,0);
		
		TH2F *htmp0 = new TH2F("htmp0","htmp0; Entries; Jet p_{T} GeV/c",NBINS-1,BOUNDARIES, 50, 10e-3,10e+11);
		
	
  			
  		 htmp0->GetYaxis()->SetNdivisions(610); 
  
 		 htmp0->GetYaxis()->SetLabelFont(43);
 		 htmp0->GetYaxis()->SetTitleFont(43);
 		 htmp0->GetYaxis()->SetLabelSize(20);
  		 htmp0->GetYaxis()->SetTitleSize(22);
 		 htmp0->GetYaxis()->SetTitleOffset(2.6);

 		 htmp0->GetXaxis()->SetLabelFont(43);
 		 htmp0->GetXaxis()->SetTitleFont(43);
 		 htmp0->GetXaxis()->SetLabelSize(20);
 		 htmp0->GetXaxis()->SetTitleSize(22);
  		 htmp0->GetXaxis()->SetTitleOffset(3.1);

  		 htmp0->GetXaxis()->SetNoExponent();
  		 htmp0->GetXaxis()->SetMoreLogLabels();

		
		c3->cd(1);
		
		gPad->SetLogy();
		
		htmp0->Draw();
		
		
		hcorpt_pbpb_cent1->SetMarkerColor(kBlue);
		hcorpt_pbpb_cent1->SetMarkerSize(0.9);
		hcorpt_pbpb_cent1->SetMarkerStyle(20);

		hcorpt_pbpb_cent1->Draw("same");
		
		hcorpt_pbpb_cent2->SetMarkerColor(kViolet+6);
		hcorpt_pbpb_cent2->SetMarkerSize(0.9);
		hcorpt_pbpb_cent2->SetMarkerStyle(21);

		hcorpt_pbpb_cent2->Draw("same");
		
		hcorpt_pbpb_cent3->SetMarkerColor(kYellow+3);
		hcorpt_pbpb_cent3->SetMarkerSize(0.9);
		hcorpt_pbpb_cent3->SetMarkerStyle(23);

		hcorpt_pbpb_cent3->Draw("same");
		
		hcorpt_pbpb_cent4->SetMarkerColor(kYellow+1);
		hcorpt_pbpb_cent4->SetMarkerSize(0.9);
		hcorpt_pbpb_cent4->SetMarkerStyle(29);

		hcorpt_pbpb_cent4->Draw("same");
		
		
		hcorpt_pbpb_cent5->SetMarkerColor(kRed+2);
		hcorpt_pbpb_cent5->SetMarkerSize(1.1);
		hcorpt_pbpb_cent5->SetMarkerStyle(33);

		hcorpt_pbpb_cent5->Draw("same");
		
		hcorpt_pbpb_cent6->SetMarkerColor(kRed+1);
		hcorpt_pbpb_cent6->SetMarkerSize(0.9);
		hcorpt_pbpb_cent6->SetMarkerStyle(34);

		hcorpt_pbpb_cent6->Draw("same");
		
		hcorpt_pp->SetMarkerColor(kBlack);
		hcorpt_pp->SetMarkerSize(0.9);
		hcorpt_pp->SetMarkerStyle(22);

		hcorpt_pp->Draw("same");
		
		
		c3->cd(2);
		
		/////////////////
		
		hcorpt_pbpb_cent1_NoRej->SetMarkerColor(kBlue);
		hcorpt_pbpb_cent1_NoRej->SetMarkerSize(0.9);
		hcorpt_pbpb_cent1_NoRej->SetMarkerStyle(24);

		hcorpt_pbpb_cent1_NoRej->Draw("same");
		
		hcorpt_pbpb_cent2_NoRej->SetMarkerColor(kViolet+6);
		hcorpt_pbpb_cent2_NoRej->SetMarkerSize(0.9);
		hcorpt_pbpb_cent2_NoRej->SetMarkerStyle(25);

		hcorpt_pbpb_cent2_NoRej->Draw("same");
		
		hcorpt_pbpb_cent3_NoRej->SetMarkerColor(kYellow+3);
		hcorpt_pbpb_cent3_NoRej->SetMarkerSize(0.9);
		hcorpt_pbpb_cent3_NoRej->SetMarkerStyle(32);

		hcorpt_pbpb_cent3_NoRej->Draw("same");
		
		hcorpt_pbpb_cent4_NoRej->SetMarkerColor(kYellow+1);
		hcorpt_pbpb_cent4_NoRej->SetMarkerSize(0.9);
		hcorpt_pbpb_cent4_NoRej->SetMarkerStyle(30);

		hcorpt_pbpb_cent4_NoRej->Draw("same");
		
		
		hcorpt_pbpb_cent5_NoRej->SetMarkerColor(kRed+2);
		hcorpt_pbpb_cent5_NoRej->SetMarkerSize(1.1);
		hcorpt_pbpb_cent5_NoRej->SetMarkerStyle(27);

		hcorpt_pbpb_cent5_NoRej->Draw("same");
		
		hcorpt_pbpb_cent6_NoRej->SetMarkerColor(kRed+1);
		hcorpt_pbpb_cent6_NoRej->SetMarkerSize(0.9);
		hcorpt_pbpb_cent6_NoRej->SetMarkerStyle(28);

		hcorpt_pbpb_cent6_NoRej->Draw("same");
		
		hcorpt_pp_NoRej->SetMarkerSize(0.9);
		hcorpt_pp_NoRej->SetMarkerStyle(26);

		hcorpt_pp_NoRej->Draw("same");
		
		
		
		 TLegend *tleg1 = new TLegend(0.25, 0.65, 0.55, 0.95);
		 tleg1->SetBorderSize(0);
		 tleg1->SetFillStyle(0);
		 tleg1->SetTextFont(42);
		 tleg1->SetTextSize(0.04);
		 tleg1->SetHeader("w/ Hcal Noise Rejection");
		 tleg1->AddEntry(hcorpt_pbpb_cent1,"0-5% ","pl");
		 tleg1->AddEntry(hcorpt_pbpb_cent2,"5-10% (x10) ","pl");
		 tleg1->AddEntry(hcorpt_pbpb_cent3,"10-30% (10^{2})","pl");
		 tleg1->AddEntry(hcorpt_pbpb_cent4,"30-50% (10^{3})","pl");
		 tleg1->AddEntry(hcorpt_pbpb_cent5,"50-70% (10^{4})","pl");
		 tleg1->AddEntry(hcorpt_pbpb_cent6,"70-90% (10^{5})","pl");
		 tleg1->AddEntry(hcorpt_pp,"pp reference (x 0.1)","pl");
		 tleg1->Draw("same");	
		 
		 TLegend *tleg2 = new TLegend(0.58, 0.65, 0.88, 0.95);
		 tleg2->SetBorderSize(0);
		 tleg2->SetFillStyle(0);
		 tleg2->SetTextFont(42);
		 tleg2->SetTextSize(0.04);
		 tleg2->SetHeader("w/o Hcal Noise Rejection");
		 tleg2->AddEntry(hcorpt_pbpb_cent1_NoRej,"0-5% ","pl");
		 tleg2->AddEntry(hcorpt_pbpb_cent2_NoRej,"5-10% (x10) ","pl");
		 tleg2->AddEntry(hcorpt_pbpb_cent3_NoRej,"10-30% (10^{2}) ","pl");
		 tleg2->AddEntry(hcorpt_pbpb_cent4_NoRej,"30-50% (10^{3}) ","pl");
		 tleg2->AddEntry(hcorpt_pbpb_cent5_NoRej,"50-70% (10^{4}) ","pl");
		 tleg2->AddEntry(hcorpt_pbpb_cent6_NoRej,"70-90% (10^{5}) ","pl");
		 tleg2->AddEntry(hcorpt_pp_NoRej,"pp reference (x 0.1)","pl");
		 tleg2->Draw("same");
		 
		 */
		 
		
		
		TCanvas *c3 = new TCanvas("c3","c3",1200,800);
		c3->Divide(3,2,0,0);
		
		TLine *line = new TLine(100.1,1,300.,1);
 		line->SetLineStyle(2), line->SetLineWidth(2);
 		
 		
		TH2F *htmp0 = new TH2F("htmp0","htmp0;Jet p_{T} GeV/c; Noise Removed / Original Data",NBINS-1,BOUNDARIES, 50, 0.7,1.2);
		
	
  			
  		 htmp0->GetYaxis()->SetNdivisions(610); 
  
 		 htmp0->GetYaxis()->SetLabelFont(43);
 		 htmp0->GetYaxis()->SetTitleFont(43);
 		 htmp0->GetYaxis()->SetLabelSize(20);
  		 htmp0->GetYaxis()->SetTitleSize(22);
 		 htmp0->GetYaxis()->SetTitleOffset(2.6);

 		 htmp0->GetXaxis()->SetLabelFont(43);
 		 htmp0->GetXaxis()->SetTitleFont(43);
 		 htmp0->GetXaxis()->SetLabelSize(20);
 		 htmp0->GetXaxis()->SetTitleSize(22);
  		 htmp0->GetXaxis()->SetTitleOffset(2.4);

  		 htmp0->GetXaxis()->SetNoExponent();
  		 htmp0->GetXaxis()->SetMoreLogLabels();
  		 
  		 htmp0->GetYaxis()->CenterTitle();
   		 htmp0->GetXaxis()->CenterTitle();
		
		c3->cd(6);
		
		
		htmp0->Draw();
		
		
		Ratio1->SetMarkerColor(kBlue);
		Ratio1->SetMarkerSize(1.1);
		Ratio1->SetMarkerStyle(33);

		Ratio1->Draw("Psame");
		drawCentTex(0);
		
		 
		 line->Draw();

		c3->cd(5);
		
		htmp0->Draw();
		
		
		Ratio2->SetMarkerColor(kBlue);
		Ratio2->SetMarkerSize(1.1);
		Ratio2->SetMarkerStyle(33);

		Ratio2->Draw("Psame");
		drawCentTex(1);
		 
		 
		 line->Draw();


		c3->cd(4);
		
		
		htmp0->Draw();
		
		
		Ratio3->SetMarkerColor(kBlue);
		Ratio3->SetMarkerSize(1.1);
		Ratio3->SetMarkerStyle(33);

		Ratio3->Draw("Psame");
		drawCentTex(2);
		
		 line->Draw();
		 
		c3->cd(3);
		
		htmp0->Draw();
		
		
		Ratio4->SetMarkerColor(kBlue);
		Ratio4->SetMarkerSize(1.1);
		Ratio4->SetMarkerStyle(33);

		Ratio4->Draw("Psame");
		drawCentTex(3);
		 
		 line->Draw();
		
		
		c3->cd(2);
		
		htmp0->Draw();
		
		
		
		Ratio5->SetMarkerColor(kBlue);
		Ratio5->SetMarkerSize(1.1);
		Ratio5->SetMarkerStyle(33);
		
		Ratio5->Draw("Psame");
		drawCentTex(4);
		
		line->Draw();
		 
		
		c3->cd(1);
		
		htmp0->Draw();
		
		
		Ratio6->SetMarkerColor(kBlue);
		Ratio6->SetMarkerSize(1.1);
		Ratio6->SetMarkerStyle(33);

		Ratio6->Draw("Psame");
		drawCentTex(5);
		 
		 line->Draw();
		
		c3->Print(Form("HcalNoiseRatio_PbPb_centbin_ak%d_%d_%d.pdf",algo,month,date));
		
		
		TCanvas *c4 = new TCanvas("c4","c4",900,450);
		
		TLine *line = new TLine(100.1,1,300.,1);
 		line->SetLineStyle(2), line->SetLineWidth(2);
 		
		c4->Divide(2,1,0,0);
		
		TH2F *htmp00 = new TH2F("htmp00","htmp00;Jet p_{T} GeV/c ;Noise Removed / Original Data",NBINS-1,BOUNDARIES, 50, 0.7,1.2);
		
	
  			
  		 htmp00->GetYaxis()->SetNdivisions(610); 
  
 		 htmp00->GetYaxis()->SetLabelFont(43);
 		 htmp00->GetYaxis()->SetTitleFont(43);
 		 htmp00->GetYaxis()->SetLabelSize(20);
  		 htmp00->GetYaxis()->SetTitleSize(22);
 		 htmp00->GetYaxis()->SetTitleOffset(1.8);

 		 htmp00->GetXaxis()->SetLabelFont(43);
 		 htmp00->GetXaxis()->SetTitleFont(43);
 		 htmp00->GetXaxis()->SetLabelSize(20);
 		 htmp00->GetXaxis()->SetTitleSize(22);
  		 htmp00->GetXaxis()->SetTitleOffset(1.7);

  		 htmp00->GetXaxis()->SetNoExponent();
  		 htmp00->GetXaxis()->SetMoreLogLabels();
  		 
   		 htmp00->GetYaxis()->CenterTitle();
   		 htmp00->GetXaxis()->CenterTitle();

  		 
		 c4->cd(1);
		
		htmp00->Draw();
		
		
		Ratio_pp->SetMarkerSize(1.1);
		Ratio_pp->SetMarkerStyle(22);

		Ratio_pp->Draw("Psame");
		drawCentTex(7);
		 
		 line->Draw();
		 
		 
		 c4->cd(2);

		htmp00->Draw();
		
		
		Ratio7->SetMarkerColor(kBlue);
		Ratio7->SetMarkerSize(1.1);
		Ratio7->SetMarkerStyle(33);

		Ratio7->Draw("Psame");
		drawCentTex(6);
		
		
		 line->Draw();
		 
		 c4->Print(Form("HcalNoiseRatio_pp_PbPb_ak%d_%d_%d.pdf",algo,month,date));
		
		
	}	
	
void drawCentTex(const int centbin){

if(centbin==0)
  TLatex *tex = new TLatex(0.7,0.8,"0-5%");
if(centbin==1)
  TLatex *tex = new TLatex(0.7,0.8,"5-10%");
if(centbin==2)
  TLatex *tex = new TLatex(0.7,0.8,"10-30%");
if(centbin==3)
  TLatex *tex = new TLatex(0.7,0.8,"30-50%");
if(centbin==4)
  TLatex *tex = new TLatex(0.7,0.8,"50-70%");
if(centbin==5)
  TLatex *tex = new TLatex(0.7,0.8,"70-90%");
if(centbin==6)
  TLatex *tex = new TLatex(0.7,0.8,"PbPb 0-90%");
if(centbin==7)
  TLatex *tex = new TLatex(0.7,0.8,"pp Reference");


  tex->SetTextFont(63);
  tex->SetTextSize(22);
  tex->SetTextColor(kBlack);
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw();
}


