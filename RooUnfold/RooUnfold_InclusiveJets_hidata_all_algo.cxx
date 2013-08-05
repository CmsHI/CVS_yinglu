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



void RooUnfold_InclusiveJets_hidata_all_algo(int method,int algo) // algo1 =akpu3 ; algo2 = icpu5
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
    
	
	//const int NBINS=7;
	//Double_t BOUNDARIES[NBINS] = {100,120,140,160,180,200,300};
	const int NBINS=31;
	Double_t BOUNDARIES[NBINS] = {100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400};
	int ncenb=5;
	float minbiasN= 1.1475e+9;
	
	
	TH1F* hResTrue_cent1= new TH1F ("Restrue_cent1", " ResTruth_cent1",    NBINS-1, BOUNDARIES); //Gen
	TH1F* hResMeas_cent1= new TH1F ("Resmeas_cent1", " ResMeasured_cent1", NBINS-1, BOUNDARIES); //Reco
	
	TH1F* hResTrue_cent2= new TH1F ("Restrue_cent2", " ResTruth_cent2",    NBINS-1, BOUNDARIES); //Gen
	TH1F* hResMeas_cent2= new TH1F ("Resmeas_cent2", " ResMeasured_cent2", NBINS-1, BOUNDARIES); //Reco
	
	TH1F* hResTrue_cent3= new TH1F ("Restrue_cent3", " ResTruth_cent3",    NBINS-1, BOUNDARIES); //Gen
	TH1F* hResMeas_cent3= new TH1F ("Resmeas_cent3", " ResMeasured_cent3", NBINS-1, BOUNDARIES); //Reco
	
	TH1F* hResTrue_cent4= new TH1F ("Restrue_cent4", " ResTruth_cent4",    NBINS-1, BOUNDARIES); //Gen
	TH1F* hResMeas_cent4= new TH1F ("Resmeas_cent4", " ResMeasured_cent4", NBINS-1, BOUNDARIES); //Reco
	
	TH1F* hResTrue_cent5= new TH1F ("Restrue_cent5", " ResTruth_cent5",    NBINS-1, BOUNDARIES); //Gen
	TH1F* hResMeas_cent5= new TH1F ("Resmeas_cent5", " ResMeasured_cent5", NBINS-1, BOUNDARIES); //Reco
	
	TH1F* hResTrue_cent6= new TH1F ("Restrue_cent6", " ResTruth_cent6",    NBINS-1, BOUNDARIES); //Gen
	TH1F* hResMeas_cent6= new TH1F ("Resmeas_cent6", " ResMeasured_cent6", NBINS-1, BOUNDARIES); //Reco
	
	
	
    RooUnfoldResponse response_cent1 (hResMeas_cent1,hResTrue_cent1);
    RooUnfoldResponse response_cent2 (hResMeas_cent2,hResTrue_cent2);
    RooUnfoldResponse response_cent3 (hResMeas_cent3,hResTrue_cent3);
    RooUnfoldResponse response_cent4 (hResMeas_cent4,hResTrue_cent4);
    RooUnfoldResponse response_cent5 (hResMeas_cent5,hResTrue_cent5);
    RooUnfoldResponse response_cent6 (hResMeas_cent6,hResTrue_cent6);
    
	
	//! Centrality reweighting function
 	 TF1* fcen = new TF1("fcen","exp(-1.0*pow(x+1.11957e+01,2)/pow(1.34120e+01,2)/2)",0,40);
	
	
    
	
	///////// INPUT PbPb DATA FILE
	
	
	
	if (algo == 1)  TFile *f = new TFile("");
	if (algo == 2)  TFile *f = new TFile("");

	
		TH1F* hMeas_cent1=(TH1F*)f->Get("hcorpt_pbpb_cent1"); 
		TH1F* hMeas_cent2=(TH1F*)f->Get("hcorpt_pbpb_cent2"); 
		TH1F* hMeas_cent3=(TH1F*)f->Get("hcorpt_pbpb_cent3"); 
		TH1F* hMeas_cent4=(TH1F*)f->Get("hcorpt_pbpb_cent4"); 
		TH1F* hMeas_cent5=(TH1F*)f->Get("hcorpt_pbpb_cent5"); 
		TH1F* hMeas_cent6=(TH1F*)f->Get("hcorpt_pbpb_cent6");
		
		
		TH1F* hMeas_RAA_cent1=(TH1F*)f->Get("hRAA_cent1"); 
		TH1F* hMeas_RAA_cent2=(TH1F*)f->Get("hRAA_cent2"); 
		TH1F* hMeas_RAA_cent3=(TH1F*)f->Get("hRAA_cent3"); 
		TH1F* hMeas_RAA_cent4=(TH1F*)f->Get("hRAA_cent4"); 
		TH1F* hMeas_RAA_cent5=(TH1F*)f->Get("hRAA_cent5"); 
		TH1F* hMeas_RAA_cent6=(TH1F*)f->Get("hRAA_cent6");
		
	
	
	
	

	
	
	
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
				response_cent1.Fill(jtpt2[i],refpt2[i],scale2);
			}           
		}
		
		if(bin2< 8 && bin2 >= 4)
        {
			
			for (int i= 0; i < njets2; i++)
				
			{ if ( refpt2[i] <0. ) continue;
				if(jtpt2[i] < 80. || jteta2[i] >2. || jteta2[i] <-2. ) continue;
				response_cent2.Fill(jtpt2[i],refpt2[i],scale2);
			}           
		}
		
		if(bin2< 12 && bin2 >= 8)
        {
			
			for (int i= 0; i < njets2; i++)
				
			{ if ( refpt2[i] <0. ) continue;
				if(jtpt2[i] < 80. || jteta2[i] >2. || jteta2[i] <-2. ) continue;
				response_cent3.Fill(jtpt2[i],refpt2[i],scale2);
			}           
		}
		
		if(bin2< 20 && bin2 >= 12)
        {
			
			for (int i= 0; i < njets2; i++)
				
			{ if ( refpt2[i] <0. ) continue;
				if(jtpt2[i] < 80. || jteta2[i] >2. || jteta2[i] <-2. ) continue;
				response_cent4.Fill(jtpt2[i],refpt2[i],scale2);
			}           
		}
		
		if(bin2< 28 && bin2 >= 20)
        {
			
			for (int i= 0; i < njets2; i++)
				
			{ if ( refpt2[i] <0. ) continue;
				if(jtpt2[i] < 80. || jteta2[i] >2. || jteta2[i] <-2. ) continue;
				response_cent5.Fill(jtpt2[i],refpt2[i],scale2);
			}           
		}
		
		if(bin2< 40 && bin2 >= 28)
        {
			
			for (int i= 0; i < njets2; i++)
				
			{ if ( refpt2[i] <0. ) continue;
				if(jtpt2[i] < 80. || jteta2[i] >2. || jteta2[i] <-2. ) continue;
				response_cent6.Fill(jtpt2[i],refpt2[i],scale2);
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
				response_cent1.Fill(jtpt3[i],refpt3[i],scale3);
			}           
		}
		  if(bin3< 8 && bin3 >= 4)
        {
			
			for (int i= 0; i < njets3; i++)
				
			{ if ( refpt3[i] <0. ) continue;
				if(jtpt3[i] < 80. || jteta3[i] >2. || jteta3[i] <-2. ) continue;
				response_cent2.Fill(jtpt3[i],refpt3[i],scale3);
			}           
		}
		  if(bin3< 12 && bin3 >= 8)
        {
			
			for (int i= 0; i < njets3; i++)
				
			{ if ( refpt3[i] <0. ) continue;
				if(jtpt3[i] < 80. || jteta3[i] >2. || jteta3[i] <-2. ) continue;
				response_cent3.Fill(jtpt3[i],refpt3[i],scale3);
			}           
		}
		  if(bin3< 20 && bin3 >= 12)
        {
			
			for (int i= 0; i < njets3; i++)
				
			{ if ( refpt3[i] <0. ) continue;
				if(jtpt3[i] < 80. || jteta3[i] >2. || jteta3[i] <-2. ) continue;
				response_cent4.Fill(jtpt3[i],refpt3[i],scale3);
			}           
		}
		  if(bin3< 28 && bin3 >= 20)
        {
			
			for (int i= 0; i < njets3; i++)
				
			{ if ( refpt3[i] <0. ) continue;
				if(jtpt3[i] < 80. || jteta3[i] >2. || jteta3[i] <-2. ) continue;
				response_cent5.Fill(jtpt3[i],refpt3[i],scale3);
			}           
		}
		
		
        if(bin3< 40 && bin3 >= 28)
        {
			
			for (int i= 0; i < njets3; i++)
				
			{ if ( refpt3[i] <0. ) continue;
				if(jtpt3[i] < 80. || jteta3[i] >2. || jteta3[i] <-2. ) continue;
				response_cent6.Fill(jtpt3[i],refpt3[i],scale3);
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
				response_cent1.Fill(jtpt4[i],refpt4[i],scale4);
			}           
		}
		
		if(bin4< 8 && bin4 >= 4)
        {
			
			for (int i= 0; i < njets4; i++)
				
			{ if ( refpt4[i] <0. ) continue;
				if(jtpt4[i] < 80. || jteta4[i] >2. || jteta4[i] <-2. ) continue;
				response_cent2.Fill(jtpt4[i],refpt4[i],scale4);
			}           
		}
		
		if(bin4< 12 && bin4 >= 8)
        {
			
			for (int i= 0; i < njets4; i++)
				
			{ if ( refpt4[i] <0. ) continue;
				if(jtpt4[i] < 80. || jteta4[i] >2. || jteta4[i] <-2. ) continue;
				response_cent3.Fill(jtpt4[i],refpt4[i],scale4);
			}           
		}
		
		if(bin4< 20 && bin4 >= 12)
        {
			
			for (int i= 0; i < njets4; i++)
				
			{ if ( refpt4[i] <0. ) continue;
				if(jtpt4[i] < 80. || jteta4[i] >2. || jteta4[i] <-2. ) continue;
				response_cent4.Fill(jtpt4[i],refpt4[i],scale4);
			}           
		}
		
		if(bin4< 28 && bin4 >= 20)
        {
			
			for (int i= 0; i < njets4; i++)
				
			{ if ( refpt4[i] <0. ) continue;
				if(jtpt4[i] < 80. || jteta4[i] >2. || jteta4[i] <-2. ) continue;
				response_cent5.Fill(jtpt4[i],refpt4[i],scale4);
			}           
		}
		
		if(bin4< 40 && bin4 >= 28)
        {
			
			for (int i= 0; i < njets4; i++)
				
			{ if ( refpt4[i] <0. ) continue;
				if(jtpt4[i] < 80. || jteta4[i] >2. || jteta4[i] <-2. ) continue;
				response_cent6.Fill(jtpt4[i],refpt4[i],scale4);
			}           
		}
		
		
		
		
	}
	
	inf4->Close();

		
	
	
	cout << "==================================== TEST =====================================" << endl;
	
	
	cout << "==================================== UNFOLD ===================================" << endl;
	
	char chmet[100]; 
	if(method==1)
	{
		RooUnfoldBayes unfold (&response_cent1, hMeas_cent1, 4);
		TH1F* hReco_cent=1 (TH1F*) unfold.Hreco();
		RooUnfoldBayes unfold (&response_cent2, hMeas_cent2, 4);
		TH1F* hReco_cent2= (TH1F*) unfold.Hreco();
		RooUnfoldBayes unfold (&response_cent3, hMeas_cent3, 4);
		TH1F* hReco_cent3= (TH1F*) unfold.Hreco();
		RooUnfoldBayes unfold (&response_cent4, hMeas_cent4, 4);
		TH1F* hReco_cent4= (TH1F*) unfold.Hreco();
		RooUnfoldBayes unfold (&response_cent5, hMeas_cent5, 4);
		TH1F* hReco_cent5= (TH1F*) unfold.Hreco();
		RooUnfoldBayes unfold (&response_cent6, hMeas_cent6, 4);
		TH1F* hReco_cent6= (TH1F*) unfold.Hreco();


		sprintf(chmet,"Bayes unfo");
	}  // OR
	if(method==2)
	{
		RooUnfoldSvd unfold (&response_cent1, hMeas_cent1, 4);
		TH1F* hReco_cent=1 (TH1F*) unfold.Hreco();
		RooUnfoldSvd unfold (&response_cent2, hMeas_cent2, 4);
		TH1F* hReco_cent2= (TH1F*) unfold.Hreco();
		RooUnfoldSvd unfold (&response_cent3, hMeas_cent3, 4);
		TH1F* hReco_cent3= (TH1F*) unfold.Hreco();
		RooUnfoldSvd unfold (&response_cent4, hMeas_cent4, 4);
		TH1F* hReco_cent4= (TH1F*) unfold.Hreco();
		RooUnfoldSvd unfold (&response_cent5, hMeas_cent5, 4);
		TH1F* hReco_cent5= (TH1F*) unfold.Hreco();
		RooUnfoldSvd unfold (&response_cent6, hMeas_cent6, 4);
		TH1F* hReco_cent6= (TH1F*) unfold.Hreco();
		
		
		sprintf(chmet,"Svd unfo ");
	} // OR
	if(method==3)
	{
		RooUnfoldBinByBin unfold (&response_cent1, hMeas_cent1, 4);
		TH1F* hReco_cent=1 (TH1F*) unfold.Hreco();
		RooUnfoldBinByBin unfold (&response_cent2, hMeas_cent2, 4);
		TH1F* hReco_cent2= (TH1F*) unfold.Hreco();
		RooUnfoldBinByBin unfold (&response_cent3, hMeas_cent3, 4);
		TH1F* hReco_cent3= (TH1F*) unfold.Hreco();
		RooUnfoldBinByBin unfold (&response_cent4, hMeas_cent4, 4);
		TH1F* hReco_cent4= (TH1F*) unfold.Hreco();
		RooUnfoldBinByBin unfold (&response_cent5, hMeas_cent5, 4);
		TH1F* hReco_cent5= (TH1F*) unfold.Hreco();
		RooUnfoldBinByBin unfold (&response_cent6, hMeas_cent6, 4);
		TH1F* hReco_cent6= (TH1F*) unfold.Hreco();
		
		sprintf(chmet,"BinByBin unfo");
	}
	
		
		
	
	
	TCanvas *c1 = new TCanvas("c1","c1",600,500);
	TLegend *tleg = new TLegend(0.65, 0.6, 0.85, 0.85);
	tleg->SetBorderSize(0);
	tleg->SetFillStyle(0);
	tleg->SetTextFont(42);
	tleg->SetTextSize(0.04);
	tleg->AddEntry(hReco_cent1," 0-10% Unfold","pl");
	tleg->AddEntry(hMeas_cent1," 0-10% Measured ","pl");
	tleg->AddEntry(hReco_cent2," 10-20% Unfold","pl");
	tleg->AddEntry(hMeas_cent2," 10-20% Measured ","pl");
	tleg->AddEntry(hReco_cent3," 20-30% Unfold","pl");
	tleg->AddEntry(hMeas_cent3," 20-30% Measured ","pl");
	tleg->AddEntry(hReco_cent4," 30-50% Unfold","pl");
	tleg->AddEntry(hMeas_cent4," 30-50% Measured ","pl");
	tleg->AddEntry(hReco_cent5," 50-70% Unfold","pl");
	tleg->AddEntry(hMeas_cent5," 50-70% Measured ","pl");
	tleg->AddEntry(hReco_cent6," 70-100% Unfold","pl");
	tleg->AddEntry(hMeas_cent6," 70-100% Measured ","pl");
	
	TH2F *htmp3 = new TH2F("htmp3","",NBINS-1, BOUNDARIES, 100, 0., hReco_periph->GetMaximum()*1.5);
	htmp3->SetXTitle("Jet p_{T}(GeV/c)");
	htmp3->SetYTitle("Entries");
	htmp3->Draw();
	gPad->SetLogy();
	
	hReco_cent1->SetMarkerColor(kBlue);
	hReco_cent1->SetMarkerStyle(21);
	hReco_cent1->SetLineColor(kBlue);
	hReco_cent1->Draw("SAME");
	hMeas_cent1->Draw("histSAME");
	
	hReco_cent2->SetMarkerColor(kViolet+6);
	hReco_cent2->SetMarkerStyle(21);
	hReco_cent2->SetLineColor(kViolet+6);
	hReco_cent2->Draw("SAME");
	hMeas_cent2->Draw("histSAME");
	
	hReco_cent3->SetMarkerColor(kYellow+3);
	hReco_cent3->SetMarkerStyle(21);
	hReco_cent3->SetLineColor(kYellow+3);
	hReco_cent3->Draw("SAME");
	hMeas_cent3->Draw("histSAME");
	
	hReco_cent4->SetMarkerColor(kYellow+1);
	hReco_cent4->SetMarkerStyle(21);
	hReco_cent4->SetLineColor(kYellow+1);
	hReco_cent4->Draw("SAME");
	hMeas_cent4->Draw("histSAME");
	
	hReco_cent5->SetMarkerColor(kRed+2);
	hReco_cent5->SetMarkerStyle(21);
	hReco_cent5->SetLineColor(kRed+2);
	hReco_cent5->Draw("SAME");
	hMeas_cent5->Draw("histSAME");
	
	hReco_cent6->SetMarkerColor(kRed+1);
	hReco_cent6->SetMarkerStyle(21);
	hReco_cent6->SetLineColor(kRed+1);
	hReco_cent6->Draw("SAME");
	hMeas_cent6->Draw("histSAME");
	
	tleg->Draw("same");
	
   c1->Print("JetSpec_Unfo_AllMC.eps");
   	
   	// Scale by Lumi* X section -- Nevt	
	

		
		
		TH1F* hnorm_pbpb_cent1=(TH1F*)hReco_cent1->Clone("hnorm_pbpb_cent1");
		for(int i=1; i<=hnorm_pbpb_cent1->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent1->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hReco_cent1->GetBinContent(i)/width/minbiasN;
			float err_cor=sqrt(hReco_cent1->GetBinContent(i))/width/minbiasN;
			hnorm_pbpb_cent1->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent1->SetBinError(i, err_cor);
			
		}
		
		TH1F* hnorm_pbpb_cent2=(TH1F*)hReco_cent2->Clone("hnorm_pbpb_cent2");
		for(int i=1; i<=hnorm_pbpb_cent2->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent2->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hReco_cent2->GetBinContent(i)/width/minbiasN;
			float err_cor=sqrt(hReco_cent2->GetBinContent(i))/width/minbiasN;
			hnorm_pbpb_cent2->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent2->SetBinError(i, err_cor);
			
		}
		
		TH1F* hnorm_pbpb_cent3=(TH1F*)hReco_cent3->Clone("hnorm_pbpb_cent3");
		for(int i=1; i<=hnorm_pbpb_cent3->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent3->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hReco_cent3->GetBinContent(i)/width/minbiasN;
			float err_cor=sqrt(hReco_cent3->GetBinContent(i))/width/minbiasN;
			hnorm_pbpb_cent3->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent3->SetBinError(i, err_cor);
			
		}
		
		TH1F* hnorm_pbpb_cent4=(TH1F*)hReco_cent4->Clone("hnorm_pbpb_cent4");
		for(int i=1; i<=hnorm_pbpb_cent4->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent4->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hReco_cent4->GetBinContent(i)/width/minbiasN;
			float err_cor=sqrt(hReco_cent4->GetBinContent(i))/width/minbiasN;
			hnorm_pbpb_cent4->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent4->SetBinError(i, err_cor);
			
		}
		
		TH1F* hnorm_pbpb_cent5=(TH1F*)hReco_cent5->Clone("hnorm_pbpb_cent5");
		for(int i=1; i<=hnorm_pbpb_cent5->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent5->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hReco_cent5->GetBinContent(i)/width/minbiasN;
			float err_cor=sqrt(hReco_cent5->GetBinContent(i))/width/minbiasN;
			hnorm_pbpb_cent5->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent5->SetBinError(i, err_cor);
			
		}
		
		TH1F* hnorm_pbpb_cent6=(TH1F*)hReco_cent6->Clone("hnorm_pbpb_cent6");
		for(int i=1; i<=hnorm_pbpb_cent6->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent6->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hReco_cent6->GetBinContent(i)/width/minbiasN;
			float err_cor=sqrt(hReco_cent6->GetBinContent(i))/width/minbiasN;
			hnorm_pbpb_cent6->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent6->SetBinError(i, err_cor);
			
		}
		
		
		
	


		
		TH1F* hRAA_cent1=(TH1F*)hnorm_pbpb_cent1->Clone("hRAA_cent1");
		TH1F* hRAA_cent2=(TH1F*)hnorm_pbpb_cent2->Clone("hRAA_cent2");
		TH1F* hRAA_cent3=(TH1F*)hnorm_pbpb_cent3->Clone("hRAA_cent3");
		TH1F* hRAA_cent4=(TH1F*)hnorm_pbpb_cent4->Clone("hRAA_cent4");
		TH1F* hRAA_cent5=(TH1F*)hnorm_pbpb_cent5->Clone("hRAA_cent5");
		TH1F* hRAA_cent6=(TH1F*)hnorm_pbpb_cent6->Clone("hRAA_cent6");
		
		


		hRAA_cent1->Scale(0.0067385);     // 1/Ncoll  Ncoll is 1484 for 0-10% centrality  centrality factor *10
        //hRAA_periph->Scale(0.0666666666); // 1/Ncoll  Ncoll is 30 for 50-100% centrality  centrality factor *2
		hRAA_cent2->Scale(0.010787487);   // 1/Ncoll  Ncoll is 927 for 10-20% centrality  centrality factor *10
		hRAA_cent3->Scale(0.017761989);   // 1/Ncoll  Ncoll is 563 for 20-30% centrality  centrality factor *10
		hRAA_cent4->Scale(0.02);          // 1/ Ncoll Ncoll is 250 for 30-50% centrality  centrality factor *10
		hRAA_cent5->Scale(0.0793650);     // 1/Ncoll  Ncoll is 63 for 50-70% centrality  centrality factor *10
		hRAA_cent6->Scale(0.375);         // 1/Ncoll  Ncoll is 8 for 70-100% centrality  centrality factor *10






      ////// INPUT PP DATA FILE



		TFile *j = new TFile("pp_ak3_2011_Unfo_bay.root");
		TH1F* hnorm_pp=(TH1F*)j->Get("hnorm_pp"); 
		
		hRAA_cent2->Divide(hnorm_pp);
		hRAA_cent3->Divide(hnorm_pp);
		hRAA_cent4->Divide(hnorm_pp);
		hRAA_cent5->Divide(hnorm_pp);
		hRAA_cent6->Divide(hnorm_pp);

		
		j->Close();
		
		
		
		
		
		TFile *pbpb_Unfo = new TFile("pbpb_Unfo.root","RECREATE");
		
		
		
		
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
		
		hMeas_RAA_cent1->SetMarkerStyle(25);
		hMeas_RAA_cent1->SetMarkerSize(0.8);
		hMeas_RAA_cent1->SetMarkerColor(kBlue);
		hMeas_RAA_cent1->SetLineColor(kBlue);
		hMeas_RAA_cent1->Draw("same");
	
		
		
   	  	TLatex *tex01 = new TLatex(100.0,0.335,"        0-10%");
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
		
		hMeas_RAA_cent2->SetMarkerStyle(25);
		hMeas_RAA_cent2->SetMarkerSize(0.8);
		hMeas_RAA_cent2->SetMarkerColor(kViolet+6);
		hMeas_RAA_cent2->SetLineColor(kViolet+6);
		hMeas_RAA_cent2->Draw("same");
	
		TLatex *tex02 = new TLatex(100.0,0.335,"         10-20%");
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
		
		hMeas_RAA_cent3->SetMarkerStyle(25);
		hMeas_RAA_cent3->SetMarkerSize(0.8);
		hMeas_RAA_cent3->SetMarkerColor(kYellow+3);
		hMeas_RAA_cent3->SetLineColor(kYellow+3);
		hMeas_RAA_cent3->Draw("same");
	
		
		TLatex *tex03 = new TLatex(100.0,0.335,"          20-30%");
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
		
		hMeas_RAA_cent4->SetMarkerStyle(25);
		hMeas_RAA_cent4->SetMarkerSize(0.8);
		hMeas_RAA_cent4->SetMarkerColor(kYellow+1);
		hMeas_RAA_cent4->SetLineColor(kYellow+1);
		hMeas_RAA_cent4->Draw("same");
	
		
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
		
		hMeas_RAA_cent5->SetMarkerStyle(25);
		hMeas_RAA_cent5->SetMarkerSize(0.8);
		hMeas_RAA_cent5->SetMarkerColor(kRed+2);
		hMeas_RAA_cent5->SetLineColor(kRed+2);
		hMeas_RAA_cent5->Draw("same");
	
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
		
		hMeas_RAA_cent6->SetMarkerStyle(25);
		hMeas_RAA_cent6->SetMarkerSize(0.8);
		hMeas_RAA_cent6->SetMarkerColor(kRed+1);
		hMeas_RAA_cent6->SetLineColor(kRed+1);
		hMeas_RAA_cent6->Draw("same");
	
		TLatex *tex06 = new TLatex(100.0,0.335,"           70-100%");
		tex06->SetTextColor(1);
		tex06->SetTextFont(42);
		tex06->SetTextSize(0.08);
		tex06->Draw("same");
		
		TLine * line = new TLine(100,1,400,1);
		line->SetLineStyle(3);
		line->Draw("same");
		
		
	
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





