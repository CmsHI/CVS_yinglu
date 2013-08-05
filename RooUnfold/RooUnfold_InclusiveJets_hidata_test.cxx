/*
 *  RooUnfold_InclusiveJets_hidata_test.cxx
 *  
 *
 *  Created by Ying Lu on 2/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */
 
 
#ifdef _MAKECINT_
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ class HiForest;
#pragma link C++ class Jets;

//#if !defined(__CINT__) || defined(__MAKECINT__)

#include <iostream>
#include <stdio.h>
using std::cout;
using std::endl;

#include "TRandom.h"
#include "TH1D.h"

#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"

//#include "RooUnfoldSvd.h"
//#include "RooUnfoldBinByBin.h"

//#endif

#endif

int GetCentBin(int,int);


//==============================================================================
// Unfolding Ying Lu 08 07 11
//==============================================================================



void RooUnfold_InclusiveJets_hidata_test(int method,int algo) // algo1 =akpu3 ; algo2 = icpu5
{
#ifdef __CINT__
	gSystem->Load("libRooUnfold");
#endif
	
	
	cout<<" ------------         Unfolding Ying Lu 08 07 11          ----------           "<<endl;
	cout<<" ==============================================================================="<<endl;
	
	char chmet1[100]; 
	if(method==1)
	{
		
		sprintf(chmet1,"Bayes unfo");
	} 
	if(method==2)
	{
		sprintf(chmet1,"Svd unfo ");
	}
	if(method==3)
	{
		sprintf(chmet1,"BinByBin unfo");
	}
	
	
	printf("Method : %s \n",chmet1);
	
	cout << "==================================== TRAIN ====================================" << endl;
    
	
	const int NBINS=7;
	Double_t BOUNDARIES[NBINS] = {100,120,140,160,180,200,300};
	
	float minbiasN= 1.1475e+9;
	
	int ncenb=5;
	
	
	TH1F* hResTrue_cent= new TH1F ("Restrue_cent", " ResTruth_cent",    NBINS-1, BOUNDARIES); //Gen
	TH1F* hResMeas_cent= new TH1F ("Resmeas_cent", " ResMeasured_cent", NBINS-1, BOUNDARIES); //Reco
	
	TH1F* hResTrue_periph= new TH1F ("Restrue_periph", " ResTruth_periph",    NBINS-1, BOUNDARIES); //Gen
	TH1F* hResMeas_periph= new TH1F ("Resmeas_periph", " ResMeasured_periph", NBINS-1, BOUNDARIES); //Reco
	
	
	
	
    RooUnfoldResponse response_cent (hResMeas_cent,hResTrue_cent);
    RooUnfoldResponse response_periph (hResMeas_periph,hResTrue_periph);
    
    
	
	//! Centrality reweighting function
 	 TF1* fcen = new TF1("fcen","exp(-1.0*pow(x+1.11957e+01,2)/pow(1.34120e+01,2)/2)",0,40);
	
	
    
	
	// Read data file
	
	TFile *f = new TFile("RAA_2011_Test.root");
	
	if (algo == 1)
	{
		TH1F* hMeas_cent=(TH1F*)f->Get("hcorpt_pbpb_cent1_ak3"); 
		TH1F* hMeas_periph=(TH1F*)f->Get("hcorpt_pbpb_periph_ak3"); 
		TH1F* hMeas_RAA_cent=(TH1F*)f->Get("hRAA_cent1_ak3"); 
		TH1F* hMeas_RAA_periph=(TH1F*)f->Get("hRAA_periph_ak3"); 
	}
	
	if (algo == 2)
	{	TH1F* hMeas_cent=(TH1F*)f->Get("hcorpt_pbpb_cent1_ic5"); 
		TH1F* hMeas_periph=(TH1F*)f->Get("hcorpt_pbpb_periph_ic5"); 
		TH1F* hMeas_RAA_cent=(TH1F*)f->Get("hRAA_cent1_ic5"); 
		TH1F* hMeas_RAA_periph=(TH1F*)f->Get("hRAA_periph_ic5"); 
	}
	
	

	
	
	
	cout<<" Read Pt hat  80 - inf "<<endl;
	
	float jtpt2[200];
	float refpt2[200];
	float jteta2[200];
	float pthat2;
	int njets2;
	int bin2;
	
	
    TString inname2="/mnt/hadoop/cms/store/user/mnguyen/MC_Production/Pythia80_HydjetDrum_mix01/merged_HydjetDrum.root";
	TFile* inf2 = new TFile(inname2,"read");
	
	TTree* t2 = (TTree*)inf2->Get("hiEvtAnalyzer/HiTree");

	if (algo == 1)TTree* tree2 = (TTree*)inf2->Get("akPu3PFJetAnalyzer/t");
	if (algo == 2)TTree* tree2 = (TTree*)inf2->Get("icPu5JetAnalyzer/t");
	
	
	tree2->SetBranchAddress("jtpt",jtpt2);
	tree2->SetBranchAddress("refpt",refpt2);
	tree2->SetBranchAddress("nref",&njets2);
	tree2->SetBranchAddress("jteta",&jteta2);
	tree2->SetBranchAddress("pthat",&pthat2);
	t2->SetBranchAddress("hiBin",&bin2);
	
	
	
	
	Long64_t nentries2 = t2 ->GetEntries();
	Long64_t nbytes2 = 0, nb2 = 0;
	
	float xsection2=9.913e-05;
	float scale2=xsection2/nentries2; 
	
	std::cout<<scale2<<endl; // Here scale2 =4590
	
	for (Long64_t jentry2=0; jentry2<nentries2;jentry2++)
	{
		
  		t2->GetEntry(jentry2);
		tree2->GetEntry(jentry2);
		
		
		//! Centrality bin
		
   		 if(bin2<0 || bin2>39)continue;
    	  int centb2=-1;
   		  double wcen2=1;
    
    	  centb2=GetCentBin(ncenb,bin2);
     	  wcen2 = fcen->Eval(bin2);
     	  
     	  
		if(pthat2>120. || pthat2==120.) continue;

        if(bin2< 4 && bin2 >= 0)
        {
			
			for (int i= 0; i < njets2; i++)
				
			{ if ( refpt2[i] <0. ) continue;
				if(jtpt2[i] < 80. || jteta2[i] >2. || jteta2[i] <-2. ) continue;
				response_cent.Fill(jtpt2[i],refpt2[i],scale2);
			}           
		}
		
		if(bin2 < 40 && bin2 >= 20)
        {
			
			for (int i= 0; i < njets2; i++)
				
			{ if ( refpt2[i] <0. ) continue;
				if(jtpt2[i] < 80. || jteta2[i] >2. || jteta2[i] <-2. ) continue;
				response_periph.Fill(jtpt2[i],refpt2[i],scale2);
			}             
		}
		
		
	}
	
	inf2->Close();
	
	
	cout<<" Read Pt hat  120 - inf "<<endl;
	
	float jtpt3[200];
	float refpt3[200];
	float jteta3[200];
	float pthat3;
	int njets3;
	int bin3;
	
	TString inname3="/mnt/hadoop/cms/store/user/mnguyen/MC_Production/Pythia120_HydjetDrum_mix01/merged_HydjetDrum.root";
	TFile* inf3 = new TFile(inname3,"read");
	
	TTree* t3 = (TTree*)inf3->Get("hiEvtAnalyzer/HiTree");
	
	if (algo == 1)TTree* tree3 = (TTree*)inf3->Get("akPu3PFJetAnalyzer/t");
	if (algo == 2)TTree* tree3 = (TTree*)inf3->Get("icPu5JetAnalyzer/t");
	
	
	tree3->SetBranchAddress("jtpt",jtpt3);
	tree3->SetBranchAddress("refpt",refpt3);
	tree3->SetBranchAddress("nref",&njets3);
	tree3->SetBranchAddress("jteta",&jteta3);
	tree3->SetBranchAddress("pthat",&pthat3);
	t3->SetBranchAddress("hiBin",&bin3);
	
	
	
	Long64_t nentries3 = t3 ->GetEntries();
	Long64_t nbytes3 = 0, nb3 = 0;
	
	float xsection3=1.128e-05;
	float scale3=xsection3/nentries3*minbiasN;
	
	std::cout<<scale3<<endl; //Here scale3=519
	
	for (Long64_t jentry3=0; jentry3<nentries3;jentry3++)
	{
		
  		t3->GetEntry(jentry3);
		tree3->GetEntry(jentry3);
		
		if(pthat3>170. || pthat3==170.) continue;
		
		
		//! Centrality bin
		
   		 if(bin3<0 || bin3>39)continue;
    	  int centb3=-1;
   		  double wcen3=1;
    
    	  centb3=GetCentBin(ncenb,bin3);
     	  wcen3 = fcen->Eval(bin3);
     	  

        if(bin3< 4 && bin3 >= 0)
        {
			
			for (int i= 0; i < njets3; i++)
				
			{ if ( refpt3[i] <0. ) continue;
				if(jtpt3[i] < 80. || jteta3[i] >2. || jteta3[i] <-2. ) continue;
				response_cent.Fill(jtpt3[i],refpt3[i],scale3);
			}           
		}
		
		if(bin3 < 40 && bin3 >= 20)
        {
			
			for (int i= 0; i < njets3; i++)
				
			{	if ( refpt3[i] <0. ) continue;
				if(jtpt3[i] < 80. || jteta3[i] >2. || jteta3[i] <-2. ) continue;
				response_periph.Fill(jtpt3[i],refpt3[i],scale3);
			}             
		}
		
		
	}
	
	inf3->Close();

	cout<<" Read Pt hat  170 - inf "<<endl;
	
	float jtpt4[200];
	float refpt4[200];
	float jteta4[200];
	float pthat4;
	int njets4;
	int bin4;
	
	
	TString inname4="/mnt/hadoop/cms/store/user/mnguyen/MC_Production/Pythia170_HydjetDrum_mix01/merged_HydjetDrum.root";
	TFile* inf4 = new TFile(inname4,"read");
	
	TTree* t4 = (TTree*)inf4->Get("hiEvtAnalyzer/HiTree");
	
	if (algo == 1)TTree* tree4 = (TTree*)inf4->Get("akPu3PFJetAnalyzer/t");
	if (algo == 2)TTree* tree4= (TTree*)inf4->Get("icPu5JetAnalyzer/t");
	
	
	tree4->SetBranchAddress("jtpt",jtpt4);
	tree4->SetBranchAddress("refpt",refpt4);
	tree4->SetBranchAddress("nref",&njets4);
	tree4->SetBranchAddress("jteta",&jteta4);
	tree4->SetBranchAddress("pthat",&pthat4);
	t4->SetBranchAddress("hiBin",&bin4);
	
	

	
	Long64_t nentries4 = t4 ->GetEntries();
	Long64_t nbytes4 = 0, nb4 = 0;
	
	float xsection4=1.47e-06;
	float scale4=xsection4/nentries4*minbiasN;
	
	std::cout<<scale4<<endl; // Here Scale4=16
	
	for (Long64_t jentry4=0; jentry4<nentries4;jentry4++)
	{
		
  		t4->GetEntry(jentry4);
		tree4->GetEntry(jentry4);
		
		
		//! Centrality bin
		
   		 if(bin4<0 || bin4>39)continue;
    	  int centb4=-1;
   		  double wcen4=1;
    
    	  centb4=GetCentBin(ncenb,bin4);
     	  wcen4 = fcen->Eval(bin4);
		
        if(bin4< 4 && bin4 >= 0)
        {
			
			for (int i= 0; i < njets4; i++)
				
			{ if ( refpt4[i] <0. ) continue;
				if(jtpt4[i] < 80. || jteta4[i] >2. || jteta4[i] <-2. ) continue;
				response_cent.Fill(jtpt4[i],refpt4[i],scale4);
			}           
		}
		
		if(bin4 < 40 && bin4 >= 20)
        {
			
			for (int i= 0; i < njets4; i++)
				
			{ if ( refpt4[i] <0. ) continue;
				if(jtpt4[i] < 80. || jteta4[i] >2. || jteta4[i] <-2. ) continue;
				response_periph.Fill(jtpt4[i],refpt4[i],scale4);
			}             
		}
		
		
	}
	
	inf4->Close();

		
	
	
	cout << "==================================== TEST =====================================" << endl;
	
	
	cout << "==================================== UNFOLD ===================================" << endl;
	
	char chmet[100]; 
	if(method==1)
	{
		RooUnfoldBayes unfold (&response_periph, hMeas_periph, 4); 
		TH1F* hReco_periph= (TH1F*) unfold.Hreco();
		RooUnfoldBayes unfold (&response_cent, hMeas_cent, 4);
		TH1F* hReco_cent= (TH1F*) unfold.Hreco();

		sprintf(chmet,"Bayes unfo");
	}  // OR
	if(method==2)
	{
		
		RooUnfoldSvd unfold (&response_periph, hMeas_periph, 4);
		TH1F* hReco_periph= (TH1F*) unfold.Hreco();
		RooUnfoldSvd unfold (&response_cent, hMeas_cent, 4); 
		TH1F* hReco_cent= (TH1F*) unfold.Hreco();

		sprintf(chmet,"Svd unfo ");
	} // OR
	if(method==3)
	{
		
		RooUnfoldBinByBin unfold (&response_periph, hMeas_periph,4);
		TH1F* hReco_periph= (TH1F*) unfold.Hreco();
		RooUnfoldBinByBin unfold (&response_cent, hMeas_cent,4);
		TH1F* hReco_cent= (TH1F*) unfold.Hreco();

		sprintf(chmet,"BinByBin unfo");
	}
	
		
		
	
	
	TCanvas *c1 = new TCanvas("c1","c1",600,500);
	TLegend *tleg = new TLegend(0.65, 0.6, 0.85, 0.85);
	tleg->SetBorderSize(0);
	tleg->SetFillStyle(0);
	tleg->SetTextFont(42);
	tleg->SetTextSize(0.04);
	tleg->AddEntry(hReco_cent,"0-10% Unfo","pl");
	tleg->AddEntry(hReco_periph,"70-100% Unfo","pl");
	tleg->AddEntry(hMeas_cent," 0-10% Data ","pl");
	tleg->AddEntry(hMeas_cent," 70-100% Data ","pl");
	
	TH2F *htmp3 = new TH2F("htmp3","",NBINS-1, BOUNDARIES, 100, 0., hReco_periph->GetMaximum()*1.5);
	htmp3->SetXTitle("E_{T} (GeV)");
	htmp3->SetYTitle("N");
	htmp3->Draw();
	gPad->SetLogy();
	hReco_periph->SetMarkerColor(kRed);
	hReco_periph->SetMarkerStyle(21);
	hReco_periph->SetLineColor(kRed);
	hReco_periph->Draw("SAME");
	hMeas_periph->Draw("histSAME");
	
	hReco_cent->SetMarkerColor(kBlue);
	hReco_cent->SetMarkerStyle(21);
	hReco_cent->SetLineColor(kBlue);
	hReco_cent->Draw("SAME");
	hMeas_cent->Draw("histSAME");
	tleg->Draw("same");
	
   c1->Print("JetSpec_Unfo_AllMC.eps");
   	
   	// Scale by Lumi* X section -- Nevt	
	
	
	if(algo ==1){
		
		TH1F* hnorm_pbpb_cent1_ak3=(TH1F*)hReco_cent->Clone("hnorm_pbpb_cent1_ak3");
		for(int i=1; i<=hnorm_pbpb_cent1_ak3->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent1_ak3->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hReco_cent->GetBinContent(i)/width/minbiasN;
			float err_cor=sqrt(hReco_cent->GetBinContent(i))/width/minbiasN;
			hnorm_pbpb_cent1_ak3->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent1_ak3->SetBinError(i, err_cor);
			
		}
		
		
		TH1F* hnorm_pbpb_periph_ak3=(TH1F*)hReco_periph->Clone("hnorm_pbpb_periph_ak3");
		for(int i=1; i<=hnorm_pbpb_periph_ak3->GetNbinsX(); i++) {
			float width=hnorm_pbpb_periph_ak3->GetBinWidth(i);
			float dN_dpt_cor_pbpb= hReco_periph->GetBinContent(i)/width/minbiasN;
			float err_cor=sqrt( hReco_periph->GetBinContent(i))/width/minbiasN;
			hnorm_pbpb_periph_ak3->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_periph_ak3->SetBinError(i, err_cor);
			
		}		
		
    }
    
    if(algo ==2){
		
		TH1F* hnorm_pbpb_cent1_ic5=(TH1F*)hReco_cent->Clone("hnorm_pbpb_cent1_ic5");
		for(int i=1; i<=hnorm_pbpb_cent1_ic5->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent1_ic5->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hReco_cent->GetBinContent(i)/width/minbiasN; 
			float err_cor=sqrt(hReco_cent->GetBinContent(i))/width/minbiasN;
			hnorm_pbpb_cent1_ic5->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent1_ic5->SetBinError(i, err_cor);
			
		}
		
		
		TH1F* hnorm_pbpb_periph_ic5=(TH1F*)hReco_periph->Clone("hnorm_pbpb_periph_ic5");
		for(int i=1; i<=hnorm_pbpb_periph_ic5->GetNbinsX(); i++) {
			float width=hnorm_pbpb_periph_ic5->GetBinWidth(i);
			float dN_dpt_cor_pbpb= hReco_periph->GetBinContent(i)/width/minbiasN; 
			float err_cor=sqrt(hReco_periph->GetBinContent(i))/width/minbiasN;
			hnorm_pbpb_periph_ic5->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_periph_ic5->SetBinError(i, err_cor);
			
		}
		
	}
	
   	
	
	if(algo ==1 ){	
	    TH1F* hRAA_cent1_ak3=(TH1F*)hnorm_pbpb_cent1_ak3->Clone("hRAA_cent1_ak3");
		hRAA_cent1_ak3->Scale(0.0067385); 
		TH1F* hRAA_periph_ak3=(TH1F*)hnorm_pbpb_periph_ak3->Clone("hRAA_periph_ak3");
		hRAA_periph_ak3->Scale(0.0666666666); // 1/Ncoll  Ncoll is 30 for 50-100% centrality  centrality factor *2
		
		
		
    	TFile *j = new TFile("pp_ak3_2011_Unfo_bay.root");
    	//TFile *j = new TFile("pp_ak3_2011_Unfo_svd.root");
		TH1F* hnorm_pp_ak3=(TH1F*)j->Get("hnorm_pp"); 
		
		
		hRAA_cent1_ak3->Divide(hnorm_pp_ak3);
		hRAA_periph_ak3->Divide(hnorm_pp_ak3);
		
	
	
	
		j->Close();

		TFile *pbpb_Unfo = new TFile("pbpb_Unfo.root","RECREATE");

		
		TCanvas *c4 = new TCanvas("c4","");
		TH2F *htmp1 = new TH2F("htmp1","",NBINS-1,BOUNDARIES, 100, 0.,1.5);
		
		htmp1->GetXaxis()->SetTitle("p_{T} [GeV/c]");
		htmp1->GetYaxis()->SetTitle("R_{AA}");
		htmp1->SetTitle("R_{AA}");
		htmp1->Draw();
    	hRAA_cent1_ak3->SetMarkerStyle(20);
		hRAA_cent1_ak3->SetMarkerSize(0.8);
		hRAA_periph_ak3->SetMarkerStyle(20);
		hRAA_periph_ak3->SetMarkerSize(0.8);
		hRAA_cent1_ak3->SetMarkerColor(kRed);
		hRAA_cent1_ak3->SetLineColor(kRed);
		hRAA_periph_ak3->SetMarkerColor(kBlue);
		hRAA_periph_ak3->SetLineColor(kBlue);
		hRAA_cent1_ak3->Draw("same");
		hRAA_periph_ak3->Draw("same");
		
		hMeas_RAA_cent->SetMarkerStyle(25);
		hMeas_RAA_cent->SetMarkerSize(0.8);
		hMeas_RAA_periph->SetMarkerStyle(25);
		hMeas_RAA_periph->SetMarkerSize(0.8);
		hMeas_RAA_cent->SetMarkerColor(kRed);
		hMeas_RAA_periph->SetMarkerColor(kBlue);
		hMeas_RAA_cent->SetLineColor(kRed);
		hMeas_RAA_periph->SetLineColor(kBlue);
		hMeas_RAA_cent->Draw("same");
		hMeas_RAA_periph->Draw("same");
		
		TLegend *tleg2 = new TLegend(0.65, 0.6, 0.85, 0.85);
		tleg2->SetBorderSize(0);
		tleg2->SetFillStyle(0);
		tleg2->AddEntry(hRAA_cent1_ak3," akpu3pf 0-10% Unfo","pl");
		tleg2->AddEntry(hRAA_periph_ak3," akpu3pf 70-100% Unfo","pl");
		tleg2->AddEntry(hMeas_RAA_cent," akpu3pf 0-10%","pl");
		tleg2->AddEntry(hMeas_RAA_periph," akpu3pf 70-100%","pl");
		tleg2->SetTextSize(0.04);
		tleg2->SetTextFont(42);
		tleg2->Draw();
		
		c4->Print("RAA_Unfo_AllMC_ak3.eps");
	}
	
	
	if(algo ==2){
		TH1F* hRAA_cent1_ic5=(TH1F*)hnorm_pbpb_cent1_ic5->Clone("hRAA_cent1_ic5");
		hRAA_cent1_ic5->Scale(0.0067385); // 1/Ncoll  Ncoll is 1484 for 0-10% centrality  centrality factor *10
		
		TH1F* hRAA_periph_ic5=(TH1F*)hnorm_pbpb_periph_ic5->Clone("hRAA_periph_ic5");
		hRAA_periph_ic5->Scale(0.0666666666); // 1/Ncoll  Ncoll is 30 for 50-100% centrality  centrality factor *2
		
		
		
    	//TFile *k = new TFile("pp_ic5_2011_Unfo_bay.root");
    	TFile *k = new TFile("pp_ic5_2011_Unfo_svd.root");
		TH1F* hnorm_pp_ic5=(TH1F*)k->Get("hnorm_pp"); 
		
		hRAA_cent1_ic5->Divide(hnorm_pp_ic5);
		hRAA_periph_ic5->Divide(hnorm_pp_ic5);
		
		k->Close();
	
		TFile *pbpb_Unfo = new TFile("pbpb_Unfo.root","RECREATE");

		TCanvas *c4 = new TCanvas("c4","");
		TH2F *htmp1 = new TH2F("htmp1","",NBINS-1,BOUNDARIES, 100, 0.,1.5);
		
		htmp1->GetXaxis()->SetTitle("p_{T} [GeV/c]");
		htmp1->GetYaxis()->SetTitle("R_{AA}");
		htmp1->SetTitle("R_{AA}");
		htmp1->Draw();
		hRAA_cent1_ic5->SetMarkerStyle(20);
		hRAA_cent1_ic5->SetMarkerSize(0.8);
		hRAA_periph_ic5->SetMarkerStyle(20);
		hRAA_periph_ic5->SetMarkerSize(0.8);
		hRAA_cent1_ic5->SetMarkerColor(kRed);
		hRAA_periph_ic5->SetMarkerColor(kBlue);
		hRAA_cent1_ic5->SetLineColor(kRed);
		hRAA_periph_ic5->SetLineColor(kBlue);
		hRAA_cent1_ic5->Draw("same");
		hRAA_periph_ic5->Draw("same");
		
		
	    hMeas_RAA_cent->SetMarkerStyle(25);
		hMeas_RAA_cent->SetMarkerSize(0.8);
		hMeas_RAA_periph->SetMarkerStyle(25);
		hMeas_RAA_periph->SetMarkerSize(0.8);
		hMeas_RAA_cent->SetMarkerColor(kRed);
		hMeas_RAA_periph->SetMarkerColor(kBlue);
		hMeas_RAA_cent->SetLineColor(kRed);
		hMeas_RAA_periph->SetLineColor(kBlue);
		hMeas_RAA_cent->Draw("same");
		hMeas_RAA_periph->Draw("same");
		
		
		
		TLegend *tleg2 = new TLegend(0.65, 0.6, 0.85, 0.85);
		tleg2->SetBorderSize(0);
		tleg2->SetFillStyle(0);
		tleg2->AddEntry(hRAA_cent1_ic5," icpu5 0-10% Unfo ","pl");
		tleg2->AddEntry(hRAA_periph_ic5," icpu5 70-100% Unfo","pl");
		tleg2->AddEntry(hMeas_RAA_cent," icpu5 0-10%","pl");
		tleg2->AddEntry(hMeas_RAA_periph," icpu5 70-100%","pl");
		tleg2->SetTextSize(0.04);
		tleg2->SetTextFont(42);
		tleg2->Draw();
		
		c4->Print("RAA_Unfo_AllMC_ic5.eps");
	}
	
	
	
	
	// pbpb_Unfo->Write();
	//pbpb_Unfo->Close();
	

	
	
}

int GetCentBin(int ncen,int bin)
{
  int ibin=-1;
  //! centrality is defined as 2.5% bins of cross section
  //! in 0-39 bins

  if(ncen==6){
    if(bin<4)ibin=0; //! 0-10%
    else if(bin>=4 && bin<8)ibin=1;    //! 10-20%
    else if(bin>=8 && bin<12)ibin=2;   //! 20-30%
    else if(bin>=12 && bin<20)ibin=3;  //! 30-50%
    else if(bin>=20 && bin<28)ibin=4;  //! 50-70%
    else if(bin>=28 && bin<40)ibin=5;  //! 70-100%

  } else if(ncen==5){
    if(bin<4)ibin=0; //! 0-10% 
    else if(bin>=4  && bin<8)ibin=1;  //! 10-20%
    else if(bin>=8  && bin<12)ibin=2; //! 20-30%
    else if(bin>=12 && bin<20)ibin=3; //! 30-50%
    else if(bin>=20 && bin<40)ibin=4; //! 50-100%

  }else if(ncen==7){
    if(bin<4)ibin=0; //! 0-10%
    else if(bin>=4 && bin<8)ibin=1;    //! 10-20%
    else if(bin>=8 && bin<12)ibin=2;   //! 20-30%
    else if(bin>=12 && bin<16)ibin=3;  //! 30-40%
    else if(bin>=16 && bin<20)ibin=4;  //! 40-50%
    else if(bin>=20 && bin<24)ibin=5;  //! 50-60%
    else if(bin>=24 && bin<32)ibin=6;  //! 60-80%
    //else if(bin>=32)ibin=7; //! 80-100%
  }
  return ibin;
}
#ifndef __CINT__
int main () { RooUnfoldPhoJ(); return 0; }  // Main program when run stand-alone
#endif
