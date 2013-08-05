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
#include "/afs/cern.ch/user/y/yinglu/scratch0/CMSSW_4_4_2_patch3/src/HiForest_V2/utilities_v2.h";
#include "/afs/cern.ch/user/y/yinglu/scratch0/CMSSW_4_4_2_patch3/src/HiForest_V2/commonStyle_v2.h";

using namespace std;

#endif

void drawText(const char *text, float xp, float yp, int size);
void putCMSPrel(double x, double y, double size);
void drawText(const char *text, float xp, float yp, int size);
void drawText2(const char *text, float xp, float yp, int size);



void RAA_June_05(int algo =4) // ic5=1;ak2=2;ak3=3; ak4=4;ak5=5;...
{	


	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();
	
		
	 // const int NBINS=31;
	 // Double_t BOUNDARIES[NBINS] = {100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400};
	//	const int NBINS=17;
	//	Double_t BOUNDARIES[NBINS] = {60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,250,300};
	
	
	/////As June 13 201 new bin implemented 
	const int NBINS=31;
	Double_t BOUNDARIES[NBINS] = {100.0000000, 105.5113064,111.3263577, 117.4618943, 123.9355792, 130.7660486, 137.9729661, 145.5770790, 153.6002778, 162.0656597, 170.9975947, 180.4217960, 190.3653939, 200.8570139, 211.9268593, 223.6067977, 235.9304534, 248.9333035, 262.6527804, 277.1283798, 292.4017738, 308.5169314, 325.5202446, 343.4606625, 362.3898318, 382.3622457, 403.4354004, 425.6699613, 449.1299369, 473.8828636, 500.0000000};
	
	
	float ptmax = 400.0;
    float ymin = 0.0001;
    float ymax = 1.7;
    
    
    
	////*******************lumi number for the sample***************************
	
	
	float lumi=103.;
	float pplumi=212.;
	
	//float lumi=150.;
	//float pplumi=231.;
	
	
	////*************************************************************************
	
	
	
	/////// INPUT ROOT File
	
	//HiForest *c = new HiForest("rfio:///castor/cern.ch/user/y/yinglu/hiforest_pp_276TeV_data.root","hif",1,0);
	//HiForest *b = new HiForest("rfio:///castor/cern.ch/user/v/velicanu/forest/HiForestDijet_v7.root");
	
	
	
	HiForest *c = new HiForest("rfio:///castor/cern.ch/user/f/frankma/forest2/HiForest-ppskim-hihighpt-pt90-v1_v3_part.root","hif",1,0);
	HiForest *b = new HiForest("rfio:///castor/cern.ch/user/f/frankma/forest2/HiForest-promptskim-hihighpt-hltjet80-pt90-v2_v3_part2.root");
	
	
	/////// Output ROOT File
	
	
	

		//TFile *RAA_June_05 = new TFile("RAA_June_05.root","RECREATE");
		
		
		
		TH1F* hcorpt_pp= new TH1F("hcorpt_pp","All jets with selection;p_{T}; 1/N dN_{Jets}/dp_{T}",NBINS-1,BOUNDARIES);

   	    TCanvas *c1 = new TCanvas("c1","");
		
	if (algo == 1)
		c->tree->Draw("icPu5.jtpt>>hcorpt_pp","hltTree.HLT_Jet60_v1 &&icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pHBHENoiseFilter","e");
		
	if (algo == 2)
		c->tree->Draw("akPu2PF.jtpt>>hcorpt_pp","hltTree.HLT_Jet60_v1&& akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2 && skim.pHBHENoiseFilter","e");
		
	if (algo == 3)
		c->tree->Draw("akPu3PF.jtpt>>hcorpt_pp","hltTree.HLT_Jet60_v1&& akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2 && skim.pHBHENoiseFilter","e");
		
		
	if (algo == 4)
		c->tree->Draw("akPu4PF.jtpt>>hcorpt_pp","hltTree.HLT_Jet60_v1&& akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2 && skim.pHBHENoiseFilter","e");
	
		
	if (algo == 5)
		c->tree->Draw("akPu5PF.jtpt>>hcorpt_pp","hltTree.HLT_Jet60_v1&& akPu5PF.jtpt>100 && abs(akPu5PF.jteta)<2 && skim.pHBHENoiseFilter","e");
		
		
		
		
		
	
	
	// Scale by Lumi* X section -- Nevt	
	
		TH1F* hnorm_pp=(TH1F*)hcorpt_pp->Clone("hnorm_pp");
		for(int i=1; i<=hnorm_pp->GetNbinsX(); i++) {
		float width=hnorm_pp->GetBinWidth(i);
		float dN_dpt_cor_pp=hcorpt_pp->GetBinContent(i)/width/pplumi/64./1000000; 
		float err_cor=sqrt(hcorpt_pp->GetBinContent(i))/width/pplumi/64./1000000;
		hnorm_pp->SetBinContent(i, dN_dpt_cor_pp);
		hnorm_pp->SetBinError(i, err_cor);
		
		}
			
			
			
	////// pp plots
		
		TCanvas *c0 = new TCanvas("c0","");
		
		hnorm_pp->SetMarkerStyle(20);
		hnorm_pp->Draw("");
		
		gPad->SetLogy();

		 TLegend *tleg0 = new TLegend(0.65, 0.6, 0.85, 0.85);
		 tleg0->SetBorderSize(0);
		 tleg0->SetFillStyle(0);
		 tleg0->SetTextFont(42);
		 tleg0->SetTextSize(0.04);
		 tleg0->AddEntry(hnorm_pp," pp ","pl");
		 tleg0->Draw();		
		
		

    	///// HEAVY ION DATA

		// Jet spectra
		
		TH1F* hcorpt_pbpb_cent1 = new TH1F("hcorpt_pbpb_cent1","All jets with selection;Jet p_{T} (GeV/c); 1/N dN_{Jets}/dp_{T}",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent2 = new TH1F("hcorpt_pbpb_cent2","All jets with selection;Jet p_{T} (GeV/c); 1/N dN_{Jets}/dp_{T}",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent3 = new TH1F("hcorpt_pbpb_cent3","All jets with selection;Jet p_{T} (GeV/c); 1/N dN_{Jets}/dp_{T}",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent4 = new TH1F("hcorpt_pbpb_cent4","All jets with selection;Jet p_{T} (GeV/c); 1/N dN_{Jets}/dp_{T}",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent5 = new TH1F("hcorpt_pbpb_cent5","All jets with selection;Jet p_{T} (GeV/c); 1/N dN_{Jets}/dp_{T}",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent6 = new TH1F("hcorpt_pbpb_cent6","All jets with selection;Jet p_{T} (GeV/c); 1/N dN_{Jets}/dp_{T}",NBINS-1,BOUNDARIES);
	
   		 TCanvas *c2 = new TCanvas("c2","");
		gPad->SetLogy();
	    
	    //central events as 0-5%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent1", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin<2 && evtTree.abs(vz[1])<15 && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","e");
		
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent1", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin<2 && evtTree.abs(vz[1])<15 && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","e");
		
		if (algo == 3)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent1", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin<2 && abs(evtTree.vz[1])<15 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","e");
		
		if (algo == 4)
		b->tree->Draw("akPu4PF.jtpt>>hcorpt_pbpb_cent1", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin<2 && abs(evtTree.vz[1])<15 && akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","e");
		
		if (algo == 5)
		b->tree->Draw("akPu5PF.jtpt>>hcorpt_pbpb_cent1", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin<2 && abs(evtTree.vz[1])<15 && akPu5PF.jtpt>100 && abs(akPu5PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","e");
		
		
	
		
		//central events as 5-10%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent2", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>1  && evtTree.hiBin<4 && abs(evtTree.vz[1])<15  && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent2", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>1 &&  evtTree.hiBin<4 && abs(evtTree.vz[1])<15 && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent2", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>1 && evtTree.hiBin<4 && abs(evtTree.vz[1])<15 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 4)
		b->tree->Draw("akPu4PF.jtpt>>hcorpt_pbpb_cent2", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>1 && evtTree.hiBin<4 && abs(evtTree.vz[1])<15 && akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 5)
		b->tree->Draw("akPu5PF.jtpt>>hcorpt_pbpb_cent2", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>1 && evtTree.hiBin<4 && abs(evtTree.vz[1])<15 && akPu5PF.jtpt>100 && abs(akPu5PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		
		
		
		//central events as 10-30%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent3", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>3 && evtTree.hiBin<12  && abs(evtTree.vz[1])<15 && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent3", "hltTree.HLT_HIJet80_v1 &&  evtTree.hiBin>3 && evtTree.hiBin<12 && abs(evtTree.vz[1])<15 && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent3", "hltTree.HLT_HIJet80_v1 &&  evtTree.hiBin>3 && evtTree.hiBin<12  && abs(evtTree.vz[1])<15 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 4)
		b->tree->Draw("akPu4PF.jtpt>>hcorpt_pbpb_cent3", "hltTree.HLT_HIJet80_v1 &&  evtTree.hiBin>3 && evtTree.hiBin<12  && abs(evtTree.vz[1])<15 && akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 5)
		b->tree->Draw("akPu5PF.jtpt>>hcorpt_pbpb_cent3", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>3 && evtTree.hiBin<12 && abs(evtTree.vz[1])<15 && akPu5PF.jtpt>100 && abs(akPu5PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		
		
		//central events as 30-50%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent4", "hltTree.HLT_HIJet80_v1 &&  evtTree.hiBin>11 && evtTree.hiBin<20  && abs(evtTree.vz[1])<15 && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent4", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>11 && evtTree.hiBin<20  && abs(evtTree.vz[1])<15 && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent4", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>11 && evtTree.hiBin<20  && abs(evtTree.vz[1])<15  && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 4)
		b->tree->Draw("akPu4PF.jtpt>>hcorpt_pbpb_cent4", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>11 && evtTree.hiBin<20 && abs(evtTree.vz[1])<15  && akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 5)
		b->tree->Draw("akPu5PF.jtpt>>hcorpt_pbpb_cent4", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>11 && evtTree.hiBin<20  && abs(evtTree.vz[1])<15 && akPu5PF.jtpt>100 && abs(akPu5PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		
		
		
		//central events as 50-70%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent5", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && evtTree.hiBin<28 && abs(evtTree.vz[1])<15 && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		 
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent5", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && evtTree.hiBin<28  && abs(evtTree.vz[1])<15 && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent5", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && evtTree.hiBin<28  && abs(evtTree.vz[1])<15 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 4)
		b->tree->Draw("akPu4PF.jtpt>>hcorpt_pbpb_cent5", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && evtTree.hiBin<28  && abs(evtTree.vz[1])<15 && akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 5)
		b->tree->Draw("akPu5PF.jtpt>>hcorpt_pbpb_cent5", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && evtTree.hiBin<28 && abs(evtTree.vz[1])<15 && akPu5PF.jtpt>100 && abs(akPu5PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		
		//central events as 70-90%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent6", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>27 && evtTree.hiBin<36  && abs(evtTree.vz[1])<15 && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent6", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>27 && evtTree.hiBin<36 && abs(evtTree.vz[1])<15 && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent6", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>27 && evtTree.hiBin<36 && abs(evtTree.vz[1])<15 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 4)
		b->tree->Draw("akPu4PF.jtpt>>hcorpt_pbpb_cent6", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>27 && evtTree.hiBin<36 && abs(evtTree.vz[1])<15 && akPu4PF.jtpt>100 && abs(akPu4PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 5)
		b->tree->Draw("akPu5PF.jtpt>>hcorpt_pbpb_cent6", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>27 && evtTree.hiBin<36 && abs(evtTree.vz[1])<15 && akPu5PF.jtpt>100 && abs(akPu5PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		
		
		
	
		
		TH1F *hcorpt_pbpb_cent1_tmp = (TH1F*)gDirectory->Get("hcorpt_pbpb_cent1");
		
		/*
		
		////// PbPb 0-10% and pp Comparison plots
		
		
		TCanvas *c00 = new TCanvas("c00","");
		
		gPad->SetLogy();
		hcorpt_pp_tmp->SetMarkerStyle(20);
		hcorpt_pp_tmp->SetMarkerSize(0.8);
		hcorpt_pp_tmp->SetMarkerColor(kRed);
		hcorpt_pp_tmp->GetXaxis()->SetTitle("Jet E_{T} [GeV/c]");
		hcorpt_pp_tmp->GetYaxis()->SetTitle("Entries");
		hcorpt_pp_tmp->SetTitle("Inclusive Jet Spectra");
		hcorpt_pp_tmp->Draw();
		
	
				
		hcorpt_pbpb_cent1_tmp->SetMarkerStyle(20);
		hcorpt_pbpb_cent1_tmp->SetMarkerSize(0.8);
		hcorpt_pbpb_cent1_tmp->Draw("same");
		
		TLegend *tleg00 = new TLegend(0.65, 0.6, 1.00, 0.85);
		 tleg00->SetBorderSize(0);
		 tleg00->SetFillStyle(0);
		 tleg00->SetTextFont(42);
		 tleg00->AddEntry(hcorpt_pbpb_cent1_tmp," PbPb 150 #mub^{-1} ","pl");
		 tleg00->AddEntry(hcorpt_pp_tmp," pp 231 nb^{-1}","pl");
		 tleg00->SetTextSize(0.04);
		 tleg00->Draw();
		 
		TLatex *tex0 = new TLatex(100.0,0.535,"Inclusive Jets, icPu5");
		tex0->SetTextColor(1);
		tex0->SetTextFont(42);
		tex0->SetTextSize(0.04);
		tex0->Draw();
		
		TLatex *tex00 = new TLatex(100.0,0.535,"|#eta| < 2");
		tex00->SetTextColor(1);
		tex00->SetTextFont(42);
		tex00->SetTextSize(0.04);
		//tex00->Draw();
		 
		c00->Print("InclusiveJets_pT.pdf");
		
		*/
	
		
		
		
		
		
		// Scale by Lumi* X section -- Nevt	
		
		TH1F* hnorm_pbpb_cent1=(TH1F*)hcorpt_pbpb_cent1->Clone("hnorm_pbpb_cent1");
		for(int i=1; i<=hnorm_pbpb_cent1->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent1->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hcorpt_pbpb_cent1->GetBinContent(i)/width/lumi/7.65/1000000.; 
			float err_cor=sqrt(hcorpt_pbpb_cent1->GetBinContent(i))/width/lumi/7.65/1000000.;
			hnorm_pbpb_cent1->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent1->SetBinError(i, err_cor);
			
		}
		
	
		
	TH1F* hnorm_pbpb_cent2=(TH1F*)hcorpt_pbpb_cent2->Clone("hnorm_pbpb_cent2");
		for(int i=1; i<=hnorm_pbpb_cent2->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent2->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hcorpt_pbpb_cent2->GetBinContent(i)/width/lumi/7.65/1000000.; 
			float err_cor=sqrt(hcorpt_pbpb_cent2->GetBinContent(i))/width/lumi/7.65/1000000.;
			hnorm_pbpb_cent2->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent2->SetBinError(i, err_cor);
			
		}
		
	TH1F* hnorm_pbpb_cent3=(TH1F*)hcorpt_pbpb_cent3->Clone("hnorm_pbpb_cent3");
		for(int i=1; i<=hnorm_pbpb_cent3->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent3->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hcorpt_pbpb_cent3->GetBinContent(i)/width/lumi/7.65/1000000.; 
			float err_cor=sqrt(hcorpt_pbpb_cent3->GetBinContent(i))/width/lumi/7.65/1000000.;
			hnorm_pbpb_cent3->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent3->SetBinError(i, err_cor);
			
		}
		
	TH1F* hnorm_pbpb_cent4=(TH1F*)hcorpt_pbpb_cent4->Clone("hnorm_pbpb_cent4");
		for(int i=1; i<=hnorm_pbpb_cent4->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent4->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hcorpt_pbpb_cent4->GetBinContent(i)/width/lumi/7.65/1000000.; 
			float err_cor=sqrt(hcorpt_pbpb_cent4->GetBinContent(i))/width/lumi/7.65/1000000.;
			hnorm_pbpb_cent4->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent4->SetBinError(i, err_cor);
			
		}
		
	TH1F* hnorm_pbpb_cent5=(TH1F*)hcorpt_pbpb_cent5->Clone("hnorm_pbpb_cent5");
		for(int i=1; i<=hnorm_pbpb_cent5->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent5->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hcorpt_pbpb_cent5->GetBinContent(i)/width/lumi/7.65/1000000.; 
			float err_cor=sqrt(hcorpt_pbpb_cent5->GetBinContent(i))/width/lumi/7.65/1000000.;
			hnorm_pbpb_cent5->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent5->SetBinError(i, err_cor);
			
		}
	
	TH1F* hnorm_pbpb_cent6=(TH1F*)hcorpt_pbpb_cent6->Clone("hnorm_pbpb_cent6");
		for(int i=1; i<=hnorm_pbpb_cent6->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent6->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hcorpt_pbpb_cent6->GetBinContent(i)/width/lumi/7.65/1000000.; 
			float err_cor=sqrt(hcorpt_pbpb_cent6->GetBinContent(i))/width/lumi/7.65/1000000.;
			hnorm_pbpb_cent6->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent6->SetBinError(i, err_cor);
			
		}
		
		
		
		/////////Random Number Multiplication for Jet Spectra  & Plots
		
		TH1F *hnorm_pbpb_cent1_tmp = (TH1F*)hnorm_pbpb_cent1->Clone("hnorm_pbpb_cent1_tmp");
		
		TH1F *hnorm_pbpb_cent2_tmp = (TH1F*)hnorm_pbpb_cent2->Clone("hnorm_pbpb_cent2_tmp");
	
		TH1F *hnorm_pbpb_cent3_tmp = (TH1F*)hnorm_pbpb_cent3->Clone("hnorm_pbpb_cent3_tmp");
		
		TH1F *hnorm_pbpb_cent4_tmp = (TH1F*)hnorm_pbpb_cent4->Clone("hnorm_pbpb_cent4_tmp");
		
		TH1F *hnorm_pbpb_cent5_tmp = (TH1F*)hnorm_pbpb_cent5->Clone("hnorm_pbpb_cent5_tmp");
		
		TH1F *hnorm_pbpb_cent6_tmp = (TH1F*)hnorm_pbpb_cent6->Clone("hnorm_pbpb_cent6_tmp");
		
		TH1F *hnorm_pp_tmp = (TH1F*)hnorm_pp->Clone("hnorm_pp_tmp");

		
		hnorm_pbpb_cent1_tmp->Scale(1);
		hnorm_pbpb_cent2_tmp->Scale(10);
		hnorm_pbpb_cent3_tmp->Scale(100);
		hnorm_pbpb_cent4_tmp->Scale(1000);
		hnorm_pbpb_cent5_tmp->Scale(10000);
		hnorm_pbpb_cent6_tmp->Scale(100000);
		hnorm_pp_tmp->Scale(1);
		
		TCanvas *c2 = new TCanvas("c2","");
		
		gPad->SetLogy();
		
		
		TH2F *htmp0 = new TH2F("htmp0","",NBINS-1,BOUNDARIES, 50, 10e-12,10e-1);
		
		htmp0->GetYaxis()->SetTitle("1/N dN_{Jets}/dp_{T}");
		htmp0->GetXaxis()->SetTitle("Jet p_{T} [GeV/c]");
		htmp0->Draw();
		
		hnorm_pbpb_cent1_tmp->SetMarkerColor(kBlue);
		hnorm_pbpb_cent1_tmp->SetMarkerSize(0.9);
		hnorm_pbpb_cent1_tmp->SetMarkerStyle(20);

		hnorm_pbpb_cent1_tmp->Draw("same");
		hnorm_pbpb_cent2_tmp->SetMarkerColor(kViolet+6);
		hnorm_pbpb_cent2_tmp->SetMarkerSize(0.9);
		hnorm_pbpb_cent2_tmp->SetMarkerStyle(21);

		hnorm_pbpb_cent2_tmp->Draw("same");
		
		hnorm_pbpb_cent3_tmp->SetMarkerColor(kYellow+3);
		hnorm_pbpb_cent3_tmp->SetMarkerSize(0.9);
		hnorm_pbpb_cent3_tmp->SetMarkerStyle(23);

		hnorm_pbpb_cent3_tmp->Draw("same");
		
		hnorm_pbpb_cent4_tmp->SetMarkerColor(kYellow+1);
		hnorm_pbpb_cent4_tmp->SetMarkerSize(0.9);
		hnorm_pbpb_cent4_tmp->SetMarkerStyle(29);

		hnorm_pbpb_cent4_tmp->Draw("same");
		
		
		hnorm_pbpb_cent5_tmp->SetMarkerColor(kRed+2);
		hnorm_pbpb_cent5_tmp->SetMarkerSize(1.1);
		hnorm_pbpb_cent5_tmp->SetMarkerStyle(33);

		hnorm_pbpb_cent5_tmp->Draw("same");
		
		hnorm_pbpb_cent6_tmp->SetMarkerColor(kRed+1);
		hnorm_pbpb_cent6_tmp->SetMarkerSize(0.9);
		hnorm_pbpb_cent6_tmp->SetMarkerStyle(34);

		hnorm_pbpb_cent6_tmp->Draw("same");
		
		hnorm_pp_tmp->SetMarkerColor(kBlack);
		hnorm_pp_tmp->SetMarkerSize(0.9);
		hnorm_pp_tmp->SetMarkerStyle(22);

		hnorm_pp_tmp->Draw("same");
		
		TLegend *tleg1 = new TLegend(0.65, 0.65, 0.85, 0.90);
		tleg1->SetBorderSize(0);
		 tleg1->SetFillStyle(0);
		 tleg1->SetTextFont(42);
		 tleg1->SetTextSize(0.04);
		 tleg1->AddEntry(hnorm_pbpb_cent1_tmp," PbPb 0-5% ","pl");
		 tleg1->AddEntry(hnorm_pbpb_cent2_tmp," PbPb 5-10% (x10) ","pl");
		 tleg1->AddEntry(hnorm_pbpb_cent3_tmp," PbPb 10-30% (x10^{2}) ","pl");
		 tleg1->AddEntry(hnorm_pbpb_cent4_tmp," PbPb 30-50% (x10^{3}) ","pl");
		 tleg1->AddEntry(hnorm_pbpb_cent5_tmp," PbPb 50-70% (x10^{4}) ","pl");
		 tleg1->AddEntry(hnorm_pbpb_cent6_tmp," PbPb 70-90% (x10^{5}) ","pl");
		 tleg1->AddEntry(hnorm_pp_tmp," pp reference ","pl");
		 tleg1->Draw();		 
		
		c2->Print("InclusiveJets_PbPb_RandomN.pdf");
		
		/////////  Originial Jet Spectra Plots
	
	
		TCanvas *c3 = new TCanvas("c3","");
		
		gPad->SetLogy();
		
		hnorm_pbpb_cent1->SetMarkerColor(kBlue);
		hnorm_pbpb_cent1->SetMarkerSize(0.9);
		hnorm_pbpb_cent1->SetMarkerStyle(20);

		hnorm_pbpb_cent1->Draw("");
		hnorm_pbpb_cent2->SetMarkerColor(kViolet+6);
		hnorm_pbpb_cent2->SetMarkerSize(0.9);
		hnorm_pbpb_cent2->SetMarkerStyle(21);

		hnorm_pbpb_cent2->Draw("same");
		
		hnorm_pbpb_cent3->SetMarkerColor(kYellow+3);
		hnorm_pbpb_cent3->SetMarkerSize(0.9);
		hnorm_pbpb_cent3->SetMarkerStyle(23);

		hnorm_pbpb_cent3->Draw("same");
		
		hnorm_pbpb_cent4->SetMarkerColor(kYellow+1);
		hnorm_pbpb_cent4->SetMarkerSize(0.9);
		hnorm_pbpb_cent4->SetMarkerStyle(29);

		hnorm_pbpb_cent4->Draw("same");
		
		
		hnorm_pbpb_cent5->SetMarkerColor(kRed+2);
		hnorm_pbpb_cent5->SetMarkerSize(1.1);
		hnorm_pbpb_cent5->SetMarkerStyle(33);

		hnorm_pbpb_cent5->Draw("same");
		
		hnorm_pbpb_cent6->SetMarkerColor(kRed+1);
		hnorm_pbpb_cent6->SetMarkerSize(0.9);
		hnorm_pbpb_cent6->SetMarkerStyle(34);

		hnorm_pbpb_cent6->Draw("same");
		
		hnorm_pp->SetMarkerColor(kBlack);
		hnorm_pp->SetMarkerSize(0.9);
		hnorm_pp->SetMarkerStyle(22);

		hnorm_pp->Draw("same");
		
		
		
		
		/*
		
		////// pp reference for each centrality scaled by Ncoll
		
		
		//// Definition of pp reference
		
		TH1F* hnorm_pp1=(TH1F*)hnorm_pp->Clone("hnorm_pp1");	
		TH1F* hnorm_pp2=(TH1F*)hnorm_pp->Clone("hnorm_pp2");	
		TH1F* hnorm_pp3=(TH1F*)hnorm_pp->Clone("hnorm_pp3");	
		TH1F* hnorm_pp4=(TH1F*)hnorm_pp->Clone("hnorm_pp4");	
		TH1F* hnorm_pp5=(TH1F*)hnorm_pp->Clone("hnorm_pp5");	
		TH1F* hnorm_pp6=(TH1F*)hnorm_pp->Clone("hnorm_pp6");	
		
		
		hnorm_pp1->Scale(0.05*1658);
		hnorm_pp2->Scale(0.05*1310);
		hnorm_pp3->Scale(0.2*744);
		hnorm_pp4->Scale(0.2*250);
		hnorm_pp5->Scale(0.2*63);
		hnorm_pp6->Scale(0.3*10);
		
		hnorm_pp1->SetMarkerColor(kBlue);
		hnorm_pp2->SetMarkerColor(kViolet+6);
		hnorm_pp3->SetMarkerColor(kYellow+3);
		hnorm_pp4->SetMarkerColor(kYellow+1);
		hnorm_pp5->SetMarkerColor(kRed+2);
		hnorm_pp6->SetMarkerColor(kRed+1);
		
		hnorm_pp1->SetMarkerSize(0.5);
		hnorm_pp2->SetMarkerSize(0.5);
		hnorm_pp3->SetMarkerSize(0.5);
		hnorm_pp4->SetMarkerSize(0.5);
		hnorm_pp5->SetMarkerSize(0.5);
		hnorm_pp6->SetMarkerSize(0.5);
		
		hnorm_pp1->Draw("same");
		hnorm_pp2->Draw("same");
		hnorm_pp3->Draw("same");
		hnorm_pp4->Draw("same");
		hnorm_pp5->Draw("same");
		hnorm_pp6->Draw("same");
		

		
		*/
		
		
		 TLegend *tleg2 = new TLegend(0.65, 0.6, 0.85, 0.85);
		 tleg2->SetBorderSize(0);
		 tleg2->SetFillStyle(0);
		 tleg2->SetTextFont(42);
		 tleg2->SetTextSize(0.04);
		 tleg2->AddEntry(hnorm_pbpb_cent1," PbPb 0-5% ","pl");
		 tleg2->AddEntry(hnorm_pbpb_cent2," PbPb 5-10% ","pl");
		 tleg2->AddEntry(hnorm_pbpb_cent3," PbPb 10-30% ","pl");
		 tleg2->AddEntry(hnorm_pbpb_cent4," PbPb 30-50% ","pl");
		 tleg2->AddEntry(hnorm_pbpb_cent5," PbPb 50-70% ","pl");
		 tleg2->AddEntry(hnorm_pbpb_cent6," PbPb 70-90% ","pl");
		 tleg2->AddEntry(hnorm_pp," pp reference ","pl");
		 tleg2->Draw();		 
		
		c3->Print("InclusiveJets_PbPb.pdf");
		
		
		
		////// RAA Calculation 
		
		
		TH1F* hRAA_cent1=(TH1F*)hnorm_pbpb_cent1->Clone("hRAA_cent1");
		TH1F* hRAA_cent2=(TH1F*)hnorm_pbpb_cent2->Clone("hRAA_cent2");
		TH1F* hRAA_cent3=(TH1F*)hnorm_pbpb_cent3->Clone("hRAA_cent3");
		TH1F* hRAA_cent4=(TH1F*)hnorm_pbpb_cent4->Clone("hRAA_cent4");
		TH1F* hRAA_cent5=(TH1F*)hnorm_pbpb_cent5->Clone("hRAA_cent5");
		TH1F* hRAA_cent6=(TH1F*)hnorm_pbpb_cent6->Clone("hRAA_cent6");
		
		


		hRAA_cent1->Scale(0.0120627262);     // 1/Ncoll  Ncoll is 1658 for 0-5% centrality  centrality factor *20
		hRAA_cent2->Scale(0.0152671756);   // 1/Ncoll  Ncoll is 1310 for 5-10% centrality  centrality factor *20
		hRAA_cent3->Scale(0.0067204301);   // 1/Ncoll  Ncoll is 744 for 10-30% centrality  centrality factor *5
		hRAA_cent4->Scale(0.02);          // 1/ Ncoll Ncoll is 250 for 30-50% centrality  centrality factor *5
		hRAA_cent5->Scale(0.0793650794);     // 1/Ncoll  Ncoll is 63 for 50-70% centrality  centrality factor *5
		hRAA_cent6->Scale(0.5);         // 1/Ncoll  Ncoll is 10 for 70-90% centrality  centrality factor *5

		hRAA_cent1->Divide(hnorm_pp);
		hRAA_cent2->Divide(hnorm_pp);
		hRAA_cent3->Divide(hnorm_pp);
		hRAA_cent4->Divide(hnorm_pp);
		hRAA_cent5->Divide(hnorm_pp);
		hRAA_cent6->Divide(hnorm_pp);

		
		
		
		//// RAA Plots
		
		/*
		
		TCanvas *c4 = new TCanvas("c4","c4",500,700);
		
		c4->SetFillColor(0);
    	c4->SetBorderSize(0);
        c4->SetFrameBorderMode(0); 
   	    gStyle->SetOptStat(0); 
   	    
   	    c4->Divide(1,6,0,0);
   	    c4->cd(1);
   	    
   	    
		TH2F *htmp1 = new TH2F("htmp1","",NBINS-1,BOUNDARIES, 50, 0.,1.5);
		
		htmp1->GetYaxis()->SetTitle("R_{AA}");
		htmp1->GetXaxis()->SetTitle("Jet p_{T} [GeV/c]");
		htmp1->GetYaxis()->SetTitleOffset(1.0);
		htmp1->GetYaxis()->SetLabelSize(0.09);
		htmp1->GetXaxis()->SetLabelSize(0.09);
		htmp1->GetXaxis()->SetTitleSize(0.09);
		htmp1->GetYaxis()->SetTitleSize(0.09);
		htmp1->SetTitle("R_{AA}");
		htmp1->Draw();
		
		hRAA_cent1->SetMarkerStyle(20);
		hRAA_cent1->SetMarkerSize(0.8);
		hRAA_cent1->SetMarkerColor(kBlue);
		hRAA_cent1->Draw("same");
		
		
   	  	TLatex *tex01 = new TLatex(100.0,0.335,"        0-5%");
		tex01->SetTextColor(1);
		tex01->SetTextFont(42);
		tex01->SetTextSize(0.09);
		tex01->Draw("same");
		
		TLine * line = new TLine(100,1,400,1);
		line->SetLineStyle(3);
		line->Draw("same");
		
		
		c4->cd(2);
		  
	
		TH2F *htmp1 = new TH2F("htmp1","",NBINS-1,BOUNDARIES, 50, 0.,1.5);
		
		htmp1->GetYaxis()->SetTitle("R_{AA}");
		htmp1->GetXaxis()->SetTitle("Jet p_{T} [GeV/c]");
		htmp1->GetYaxis()->SetTitleOffset(1.0);
		htmp1->GetYaxis()->SetLabelSize(0.09);
		htmp1->GetXaxis()->SetLabelSize(0.09);
		htmp1->GetXaxis()->SetTitleSize(0.09);
		htmp1->GetYaxis()->SetTitleSize(0.09);
		htmp1->SetTitle("R_{AA}");
		htmp1->Draw();
		
		hRAA_cent2->SetMarkerStyle(20);
		hRAA_cent2->SetMarkerSize(0.8);
		hRAA_cent2->SetMarkerColor(kViolet+6);
		hRAA_cent2->Draw("same");
		
		TLatex *tex02 = new TLatex(100.0,0.335,"         5-10%");
		tex02->SetTextColor(1);
		tex02->SetTextFont(42);
		tex02->SetTextSize(0.09);
		tex02->Draw("same");
		 
		TLine * line = new TLine(100,1,400,1);
		line->SetLineStyle(3);
		line->Draw("same");
		
		c4->cd(3);
		
	
		TH2F *htmp1 = new TH2F("htmp1","",NBINS-1,BOUNDARIES, 50, 0.,1.5);
		
		htmp1->GetYaxis()->SetTitle("R_{AA}");
		htmp1->GetXaxis()->SetTitle("Jet p_{T} [GeV/c]");
		htmp1->GetYaxis()->SetTitleOffset(1.0);
		htmp1->GetYaxis()->SetLabelSize(0.09);
		htmp1->GetXaxis()->SetLabelSize(0.09);
		htmp1->GetXaxis()->SetTitleSize(0.09);
		htmp1->GetYaxis()->SetTitleSize(0.09);
		htmp1->SetTitle("R_{AA}");
		htmp1->Draw();
		
		hRAA_cent3->SetMarkerStyle(20);
		hRAA_cent3->SetMarkerSize(0.8);
		hRAA_cent3->SetMarkerColor(kYellow+3);
		hRAA_cent3->Draw("same");
		
		TLatex *tex03 = new TLatex(100.0,0.335,"          10-30%");
		tex03->SetTextColor(1);
		tex03->SetTextFont(42);
		tex03->SetTextSize(0.09);
		tex03->Draw("same");
		
		TLine * line = new TLine(100,1,400,1);
		line->SetLineStyle(3);
		line->Draw("same");
		
		c4->cd(4);
		
		
		
		TH2F *htmp1 = new TH2F("htmp1","",NBINS-1,BOUNDARIES, 50, 0.,1.5);
		
		htmp1->GetYaxis()->SetTitle("R_{AA}");
		htmp1->GetXaxis()->SetTitle("Jet p_{T} [GeV/c]");
		htmp1->GetYaxis()->SetTitleOffset(1.0);
		htmp1->GetYaxis()->SetLabelSize(0.09);
		htmp1->GetXaxis()->SetLabelSize(0.09);
		htmp1->GetXaxis()->SetTitleSize(0.09);
		htmp1->GetYaxis()->SetTitleSize(0.09);
		htmp1->SetTitle("R_{AA}");
		htmp1->Draw();
		
		hRAA_cent4->SetMarkerStyle(20);
		hRAA_cent4->SetMarkerSize(0.8);
		hRAA_cent4->SetMarkerColor(kYellow+1);
		hRAA_cent4->Draw("same");
		
		TLatex *tex04 = new TLatex(100.0,0.335,"          30-50%");
		tex04->SetTextColor(1);
		tex04->SetTextFont(42);
		tex04->SetTextSize(0.09);
		tex04->Draw("same");
		
		TLine * line = new TLine(100,1,400,1);
		line->SetLineStyle(3);
		line->Draw("same");
	
		 
		
		c4->cd(5);
			
		
		TH2F *htmp1 = new TH2F("htmp1","",NBINS-1,BOUNDARIES, 50, 0.,1.5);
		
		htmp1->GetYaxis()->SetTitle("R_{AA}");
		htmp1->GetXaxis()->SetTitle("Jet p_{T} [GeV/c]");
		htmp1->GetYaxis()->SetTitleOffset(1.0);
		htmp1->GetYaxis()->SetLabelSize(0.09);
		htmp1->GetXaxis()->SetLabelSize(0.09);
		htmp1->GetXaxis()->SetTitleSize(0.09);
		htmp1->GetYaxis()->SetTitleSize(0.09);
		htmp1->SetTitle("R_{AA}");
		htmp1->Draw();
		
		hRAA_cent5->SetMarkerStyle(20);
		hRAA_cent5->SetMarkerSize(0.8);
		hRAA_cent5->SetMarkerColor(kRed+2);
		hRAA_cent5->Draw("same");
		
		TLatex *tex05 = new TLatex(100.0,0.335,"          50-70%");
		tex05->SetTextColor(1);
		tex05->SetTextFont(42);
		tex05->SetTextSize(0.09);
		tex05->Draw("same");
		
		TLine * line = new TLine(100,1,400,1);
		line->SetLineStyle(3);
		line->Draw("same");
	
		 
		
		c4->cd(6);
		
		
		 
		TH2F *htmp1 = new TH2F("htmp1","",NBINS-1,BOUNDARIES, 50, 0.,1.5);
		
		htmp1->GetYaxis()->SetTitle("R_{AA}");
		htmp1->GetXaxis()->SetTitle("Jet p_{T} [GeV/c]");
		htmp1->GetYaxis()->SetTitleOffset(1.1);
		htmp1->GetYaxis()->SetLabelSize(0.08);
		htmp1->GetXaxis()->SetLabelSize(0.08);
		htmp1->GetXaxis()->SetTitleSize(0.08);
		htmp1->GetYaxis()->SetTitleSize(0.08);
		htmp1->SetTitle("R_{AA}");
		htmp1->Draw();
		
		
		hRAA_cent6->SetMarkerStyle(20);
		hRAA_cent6->SetMarkerSize(0.8);
		hRAA_cent6->SetMarkerColor(kRed+1);
		hRAA_cent6->Draw("same");
		
		TLatex *tex06 = new TLatex(100.0,0.335,"           70-90%");
		tex06->SetTextColor(1);
		tex06->SetTextFont(42);
		tex06->SetTextSize(0.08);
		tex06->Draw("same");
		
		TLine * line = new TLine(100,1,400,1);
		line->SetLineStyle(3);
		line->Draw("same");
	
		
     	c4->Print("RAA__all_algo.pdf");
		*/
		 
		 
		 //////Andre's Canvas setting for Charged Hadron RAA

		TCanvas *c4= new TCanvas("c4","c4",1100,770);
		 makeMultiPanelCanvasWithGap(c4,3,2,0.01,0.01,0.16,0.2,0.04,0.04); 

  		TH1D *hDum=0, *hDum_1=0, *hDum2=0, *hDum2_1=0;
  		hDum = GetDummyHist(100.0,ptmax,ymin,ymax,"Jet p_{T} (GeV/c)","R_{AA}",false);
  			
  		 hDum->GetYaxis()->SetNdivisions(610); 
  
 		 hDum->GetYaxis()->SetLabelFont(43);
 		 hDum->GetYaxis()->SetTitleFont(43);
 		 hDum->GetYaxis()->SetLabelSize(20);
  		 hDum->GetYaxis()->SetTitleSize(22);
 		 hDum->GetYaxis()->SetTitleOffset(2.6);

 		 hDum->GetXaxis()->SetLabelFont(43);
 		 hDum->GetXaxis()->SetTitleFont(43);
 		 hDum->GetXaxis()->SetLabelSize(20);
 		 hDum->GetXaxis()->SetTitleSize(22);
  		 hDum->GetXaxis()->SetTitleOffset(3.1);

  		 hDum->GetXaxis()->SetNoExponent();
  		 hDum->GetXaxis()->SetMoreLogLabels();

 		 // to show in up and down
  		 hDum->GetXaxis()->SetTitleOffset(2.4);
  		 hDum_1 = (TH1D*) hDum->Clone("hDum_1");
  		 hDum_1->SetAxisRange(0,1.2,"Y");
  		 
  		 TLine *line = new TLine(100.1,1,ptmax,1);
 		 line->SetLineStyle(2), line->SetLineWidth(2);
  		 
  		 c4->cd(1);
	     hDum->Draw("");
 		 line->Draw();
  		 drawText("70-90%",0.2,0.205,22);
 		// drawText2("T_{AA} and lumi. uncertainty",0.3,0.66,17);  
  		th1Style1(hRAA_cent6,1,20,1.2,1,1.5,1,1);    
  		//putCMSPrel(0.2,0.88,0.05);
		
		c4->cd(2);
	     hDum->Draw("");
 		 line->Draw();
  		 drawText("50-70%",0.2,0.205,22);
 		// drawText2("T_{AA} and lumi. uncertainty",0.3,0.66,17);  
  		th1Style1(hRAA_cent5,1,20,1.2,1,1.5,1,1);    
  		//putCMSPrel(0.2,0.88,0.05);
  		
  		
  		c4->cd(3);
	     hDum->Draw("");
 		 line->Draw();
  		 drawText("30-50%",0.2,0.205,22);
 		// drawText2("T_{AA} and lumi. uncertainty",0.3,0.66,17);  
  		th1Style1(hRAA_cent4,1,20,1.2,1,1.5,1,1);    
  		//putCMSPrel(0.2,0.88,0.05);
  		
  		
  		c4->cd(4);
	     hDum->Draw("");
 		 line->Draw();
  		 drawText("10-30%",0.2,0.22,22);
 		// drawText2("T_{AA} and lumi. uncertainty",0.3,0.66,17);  
  		th1Style1(hRAA_cent3,1,20,1.2,1,1.5,1,1);    
  		//putCMSPrel(0.2,0.88,0.05);
  		
  		
  		c4->cd(5);
	     hDum->Draw("");
 		 line->Draw();
  		 drawText("5-10%",0.2,0.22,22);
 		// drawText2("T_{AA} and lumi. uncertainty",0.3,0.66,17);  
  		th1Style1(hRAA_cent2,1,20,1.2,1,1.5,1,1);    
  		//putCMSPrel(0.2,0.88,0.05);
  		
  		c4->cd(6);
	     hDum->Draw("");
 		 line->Draw();
  		 drawText("0-5%",0.2,0.22,22);
 		// drawText2("T_{AA} and lumi. uncertainty",0.3,0.66,17);  
  		th1Style1(hRAA_cent1,1,20,1.2,1,1.5,1,1);    
  		//putCMSPrel(0.2,0.88,0.05);

	  c4->Print("RAA__all_algo.pdf");
         
  
		//RAA_June_05->Write();
		//RAA_June_05->Close();
		
		
		
		}
		


void putCMSPrel(double x, double y, double size){
  TLatex *tex=0;
  tex = new TLatex(x,y,"CMS Preliminary");
  tex->SetTextSize(size);
  tex->SetLineWidth(2);
  tex->SetNDC();
  tex->Draw();
}
void drawText(const char *text, float xp, float yp, int size){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(63);
  tex->SetTextSize(size);
  tex->SetTextColor(kBlack);
  tex->SetLineWidth(1);
  //tex->SetTextFont(42);
  tex->SetNDC();
  tex->Draw();
}

void drawText2(const char *text, float xp, float yp, int size){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(43);
  tex->SetTextSize(size);
  tex->SetTextColor(kBlack);
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw();
}


	
		
	
