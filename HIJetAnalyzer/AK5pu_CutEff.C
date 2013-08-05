/*
 *  AK5pu_CutEff.C
 *  
 *
 *  Created by Ying Lu on 10/3/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#include <TRandom.h>

#include <TNtuple.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>

void analyzeInclusivejet(){
	
	float cutEtaJet = 2;
	
	float cutPtJet =100;
	
	
	// Tree variables
	
	//Trigger trigger;
	float jtpt_ic5[1000];
	float jteta_ic5[1000];
	float jtphi_ic5[1000];
	int njets_ic5;
	
	float jtpt_ak3[1000];
	float jteta_ak3[1000];
	float jtphi_ak3[1000];
	int njets_ak3;
	
	int run;
	int evt;
	int bin;
	
	
	const int NBINS=15;
	Double_t BOUNDARIES[NBINS] = {60,65,72,80,90,100,120,140,160,180,200,220,240,280,350};
	
	
	TH1F* hak3pujet_cut = new TH1F("hak3pujet_cut","AK3PU Jet Spectra with cut;p_{T}; # of Events",NBINS-1,BOUNDARIES);
	TH1F* hak3pujet = new TH1F("hak3pujet","AK3PU Jet Spectra;p_{T}; # of Events",NBINS-1,BOUNDARIES);
	hak3pujet_cut->Sumw2();
	hak3pujet->Sumw2();
	
	
	TString inname="merged.root";
	TFile* inf = new TFile(inname,"read");
	
	TTree* ic5t = (TTree*)inf->Get("icPu5JetAnalyzer/t");
	TTree* t = (TTree*)inf->Get("hltanalysis/HltTree");
	
	ic5t->SetBranchAddress("jtpt",jtpt_ic5);
	ic5t->SetBranchAddress("jteta",jteta_ic5);
	ic5t->SetBranchAddress("jtphi",jtphi_ic5);
	ic5t->SetBranchAddress("nref",&njets_ic5);
	
	TTree* ak3t = (TTree*)inf->Get("akPu3PFJetAnalyzer/t");
	
	ak3t->SetBranchAddress("jtpt",jtpt_ak3);
	ak3t->SetBranchAddress("jteta",jteta_ak3);
	ak3t->SetBranchAddress("jtphi",jtphi_ak3);
	ak3t->SetBranchAddress("nref",&njets_ak3);
	
	t->SetBranchAddress("Run",&run);
	t->SetBranchAddress("Event",&evt);
	t->SetBranchAddress("hiBin",&bin);
	
	TString outname = "JetSkimTree.root";
			
	int Nevents = t->GetEntries();
	for(int iev = 0; iev < Nevents; ++iev){
		t->GetEntry(iev);
		ic5t->GetEntry(iev);
		ak3t->GetEntry(iev);
		
		for(int i = 0; i < njets_ak3; ++i){
			//if(jtpt_ak3[i] < cutPtJet) continue;
			if(fabs(jteta_ak3[i]) > cutEtaJet) continue;
			hak3pujet->Fill(jtpt_ak3[i]);
							}//1st for loop
		
		int id=0;
		for(int i = 0; i < njets_ak3; ++i){
			if(fabs(jteta_ic5[i]) < cutEtaJet)
				id =1;
			
		}// 2nd for loop
		if(id == 1){
				for(int i = 0; i < njets_ak3; ++i){
					if(jtpt_ic5[i] < cutPtJet) continue;
					//if(jtpt_ak3[i] < cutPtJet) continue;
					if(fabs(jteta_ak3[i]) > cutEtaJet) continue;
					hak3pujet_cut->Fill(jtpt_ak3[i]);
				}
			
	}// if loop
	}//evt loop
	
	
	TCanvas *c1 = new TCanvas("c1", "",46,477,700,509);
	c1->Range(-125,-11.1492,1125,3.24528);
	c1->SetBorderSize(0);
	c1->SetBorderMode(0);
	c1->SetLeftMargin(0.16);
	c1->SetTopMargin(0.06);
	c1->SetBottomMargin(0.17);
	c1->SetTicks(1,1);
	
	
	
	gROOT->LoadMacro("erf.C");
		
	TGraphAsymmErrors *dividedthingy= new TGraphAsymmErrors;
	dividedthingy->BayesDivide(hak3pujet_cut,hak3pujet);
	
	
	float xstart=20.0;
	float xend=300.0;
	
	
	TF1 *fitfcn = new TF1("fitfcn",erf,xstart,xend,2); //<============
	fitfcn->SetParameter(0,40); //<============= 
	TFitResultPtr results =dividedthingy->Fit("fitfcn","VSR");
	
	cout << "Chi2: " << results->Chi2() << " / " << results->Ndf() << " NDF" << endl;
	
	float turnon=fitfcn->GetX(0.99,10,300);
	cout << "99% at: " << turnon << endl;
	char turnontext[50]="";
	sprintf(turnontext," ak5pu at %4.1f",turnon);
	
	
	
	dividedthingy->GetFunction("fitfcn")->SetLineColor(3);
	dividedthingy->SetLineColor(1);
	dividedthingy->Draw("Ap");
	
	
	
	TText *t2 = new TText(95,0.08,turnontext);
	t2->SetTextSize(0.055);
	t2->SetTextColor(1);
	t2->Draw();
		
		
	
}

