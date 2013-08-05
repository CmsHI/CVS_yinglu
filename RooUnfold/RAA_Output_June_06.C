#if !defined(__CINT__) || defined(__MAKECINT__)

#include <iostream>
#include <stdio.h>

#include "hiForest.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TMath.h"
#include "TLegend.h"


using namespace std;

#endif

/*

void dumpDatatoTxt(const char *centbin,TH1F *h,const char *txtfile);

void dumpDatatoTxt(const char *centbin,TH1F *h,const char *txtfile)
{
ofstream outf(txtfile,ios::out);
for(int ix=1;ix<=h->GetNbinsX();ix++){
double pt = h->GetBinLowEdge(ix);
double val = h->GetBinContent(ix);
double err = h->GetBinError(ix);

outf<<pt<<"\t"<<val<<"\t"<<err<<"\t"<<0<<"\t"<<0<<"\t"<<0<<"\t"<<centbin<<endl;
}
outf.close();
}
*/


void RAA_Output_June_06(int algo =4) // ic5=1;ak2=2;ak3=3;ak4=4;ak5=5;...
{	

	float ptmax = 400.0;
    float ymin = 0.0001;
    float ymax = 1.7;

	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();
	
	//const int NBINS=9;
	//Double_t BOUNDARIES[NBINS] = {100,110,120,130,150,180,200,300,400};
		
	 // const int NBINS=31;
	 // Double_t BOUNDARIES[NBINS] = {100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400};
	//	const int NBINS=17;
	//	Double_t BOUNDARIES[NBINS] = {60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,250,300};
	// const int NBINS=20;
	// Double_t BOUNDARIES[NBINS] = {100,110,120,130,140,150,160,170,180,190,200,220,230,250,270,290,300,330,360,400};
	
	const int NBINS=31;
	Double_t BOUNDARIES[NBINS] = {100.0000000, 105.5113064,111.3263577, 117.4618943, 123.9355792, 130.7660486, 137.9729661, 145.5770790, 153.6002778, 162.0656597, 170.9975947, 180.4217960, 190.3653939, 200.8570139, 211.9268593, 223.6067977, 235.9304534, 248.9333035, 262.6527804, 277.1283798, 292.4017738, 308.5169314, 325.5202446, 343.4606625, 362.3898318, 382.3622457, 403.4354004, 425.6699613, 449.1299369, 473.8828636, 500.0000000};

///*******************lumi number for the sample***************************

	
	//float lumi=150.;
	//float pplumi=231.;

	float lumi=103.;
	float pplumi=212.;
	
///*************************************************************************




 /////// INPUT File 
 

	//HiForest *c = new HiForest("rfio:///castor/cern.ch/user/y/yinglu/hiforest_pp_276TeV_data.root","hif",1,0);
	//HiForest *b = new HiForest("rfio:///castor/cern.ch/user/v/velicanu/forest/HiForestDijet_v7.root");
	
	
	HiForest *c = new HiForest("rfio:///castor/cern.ch/user/f/frankma/forest2/HiForest-ppskim-hihighpt-pt90-v1_v3_part.root","hif",1,0);
	HiForest *b = new HiForest("rfio:///castor/cern.ch/user/f/frankma/forest2/HiForest-promptskim-hihighpt-hltjet80-pt90-v2_v3_part2.root");
	
	
	
	/////// Output ROOT File
	
	
	

		TFile *RAA_Output_June_06 = new TFile("RAA_Output_June_06.root","RECREATE");
		
		
		////// pp spectra 
		
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
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent1", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin<2 && abs(evtTree.vz[1])<15 && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","e");
		
		if (algo == 2)
		b->tree->Draw("akPu2PF.jtpt>>hcorpt_pbpb_cent1", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin<2 && abs(evtTree.vz[1])<15 && akPu2PF.jtpt>100 && abs(akPu2PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","e");
		
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

		
		/*
		dumpDatatoTxt("0-5%", hcorpt_pbpb_cent1,"0_5_PbPb_JetSpectra.txt");
		dumpDatatoTxt("5-10%", hcorpt_pbpb_cent2,"5_10_PbPb_JetSpectra.txt");
		dumpDatatoTxt("10-30%", hcorpt_pbpb_cent3,"10_30_PbPb_JetSpectra.txt");
		dumpDatatoTxt("30-50%", hcorpt_pbpb_cent4,"30_50_PbPb_JetSpectra.txt");
		dumpDatatoTxt("50-70%", hcorpt_pbpb_cent5,"50_70_PbPb_JetSpectra.txt");
		dumpDatatoTxt("70-90%", hcorpt_pbpb_cent6,"70_90_PbPb_JetSpectra.txt");
		dumpDatatoTxt("0%", hcorpt_pp,"pp_JetSpectra.txt");
		*/
	
		RAA_Output_June_06->Write();
		RAA_Output_June_06->Close();
		
		
		
		}
		

