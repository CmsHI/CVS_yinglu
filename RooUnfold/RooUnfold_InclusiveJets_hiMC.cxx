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



void RooUnfold_InclusiveJets_hiMC(int method,int algo)
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
	
	
	//! Centrality reweighting function
 	 TF1* fcen = new TF1("fcen","exp(-1.0*pow(x+1.11957e+01,2)/pow(1.34120e+01,2)/2)",0,40); 
  
    
    
     // Reading trees from histograms
  
 	float jtpt2[200];
	float refpt2[200];
	float jteta2[200];
	float pthat2;
	int njets2;
	int bin2;
	
	float jtpt3[200];
	float refpt3[200];
	float jteta3[200];
	float pthat3;
	int njets3;
	int bin3;
	
	
	float jtpt4[200];
	float refpt4[200];
	float jteta4[200];
	float pthat4;
	int njets4;
	int bin4;
	
	
	
	
	
	
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
	
	
	
	
	//// OutPut file

	
	
	//  TFile *f = new TFile("pbpb_Unfo.root","RECREATE");
	  
	  
	  
	  
	  cout << "==================================== TRAIN ====================================" << endl;
    
  
	
	//const int NBINS=7;
	//Double_t BOUNDARIES[NBINS] = {100,120,140,160,180,200,300};
	const int NBINS=17;
	Double_t BOUNDARIES[NBINS] = {60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,250,300};
	
	int n1=0;
	int n2=0;
	int ncenb=5;
	
	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();
	
	
	TH1F* hResTrue_cent= new TH1F ("Restrue_cent", " ResTruth_cent",    NBINS-1, BOUNDARIES); //Gen
	TH1F* hResMeas_cent= new TH1F ("Resmeas_cent", " ResMeasured_cent", NBINS-1, BOUNDARIES); //Reco
	
	TH1F* hResTrue_periph= new TH1F ("Restrue_periph", " ResTruth_periph",    NBINS-1, BOUNDARIES); //Gen
	TH1F* hResMeas_periph= new TH1F ("Resmeas_periph", " ResMeasured_periph", NBINS-1, BOUNDARIES); //Reco
	
	
	
	
    RooUnfoldResponse response_cent (hResMeas_cent,hResTrue_cent);
    RooUnfoldResponse response_periph (hResMeas_periph,hResTrue_periph);
	
	
	
    
	// ***************** histogram for testing sample *****************
	
	 
	
	
		TH1F* hMeas_cent= new TH1F ("hMeas_cent", "Test Measured cent",   NBINS-1, BOUNDARIES); //Gen
		TH1F* hMeas_periph= new TH1F ("hMeas_periph", "Test Measured periph",   NBINS-1, BOUNDARIES); //Gen
		TH1F* hTrue_cent= new TH1F ("hTrue_cent", "Test Truth cent",   NBINS-1, BOUNDARIES); //Gen
		TH1F* hTrue_periph= new TH1F ("hTrue_periph", "Test Truth periph",   NBINS-1, BOUNDARIES); //Gen
		TH1F* hRAA_cent= new TH1F ("hRAA_cent", "Test RAA measured cent",   NBINS-1, BOUNDARIES); //Gen
		TH1F* hRAA_periph= new TH1F ("hRAA_periph", "Test RAA measured periph",   NBINS-1, BOUNDARIES); //Gen
	
	
	
	
	
	cout<<" Read Pt hat  80 - inf "<<endl;
	
	
	
	Long64_t nentries2 = t2 ->GetEntries();
	Long64_t nbytes2 = 0, nb2 = 0;
	
	float xsection2=9.913e-05;
	float scale2=xsection2/nentries2;
	
	std::cout<<nentries2<<endl;
	std::cout<<scale2<<endl; 
	
	for (Long64_t jentry2=0; jentry2<nentries2;jentry2++)
	{
		
  		t2->GetEntry(jentry2);
		tree2->GetEntry(jentry2);
		
		if(pthat2>120. ) continue;
		
		//! Centrality bin
		
   		 if(bin2<0 || bin2>39)continue;
    	  int centb2=-1;
   		  double wcen2=1;
    
    	  centb2=GetCentBin(ncenb,bin2);
     	  wcen2 = fcen->Eval(bin2);
    


        if(bin2< 4 && bin2 >= 0)
        {
		 if(jentry2%2==1)
		 {
			for (int i= 0; i < njets2; i++)
				
			{ if ( refpt2[i] <0. ) continue;
				if(jtpt2[i] < 80. || jteta2[i] >2. || jteta2[i] <-2. ) continue;
				//for(int n2=0;n2<scale2;n2++)
				response_cent.Fill(jtpt2[i],refpt2[i],scale2);
			} 
		 }
		 
		 else
			{
			for (int i= 0; i < njets2; i++)
				{
				if ( refpt2[i] <0. ) continue;
				if(jtpt2[i] < 80. || jteta2[i] >2. || jteta2[i] <-2. ) continue;
				//for(int n2=0;n2<scale2;n2++)
				{hMeas_cent->Fill(jtpt2[i],scale2);
				hTrue_cent->Fill(refpt2[i],scale2);}
				}
				n1++;
			}
		 
		 
		}// bin if end
		
		if(bin2 < 40 && bin2 >= 20)
        {
			if(jentry2%2==1)
			{
			for (int i= 0; i < njets2; i++)
				
				{ if ( refpt2[i] <0. ) continue;
				if(jtpt2[i] < 80. || jteta2[i] >2. || jteta2[i] <-2. ) continue;
				//for(int n2=0;n2<scale2;n2++)
				response_periph.Fill(jtpt2[i],refpt2[i],scale2);
				}  
			}
		
		else
			{
			for (int i= 0; i < njets2; i++)
				{
				if ( refpt2[i] <0. ) continue;
				if(jtpt2[i] < 80. || jteta2[i] >2. || jteta2[i] <-2. ) continue;
				//for(int n2=0;n2<scale2;n2++)
				{hMeas_periph->Fill(jtpt2[i],scale2);
				hTrue_periph->Fill(refpt2[i],scale2);}
				}
				n2++;
			}
		
		
		}// bin if end
		
		
		
		
	}
	
	
	
	
	cout<<" Read Pt hat  120 - inf "<<endl;
	
	
	
	Long64_t nentries3 = t3 ->GetEntries();
	Long64_t nbytes3 = 0, nb3 = 0;
	
	float xsection3=1.128e-05;
	float scale3=xsection3/nentries3;
	
	std::cout<<scale3<<endl; 
	
	for (Long64_t jentry3=0; jentry3<nentries3;jentry3++)
	{
		
  		t3->GetEntry(jentry3);
		tree3->GetEntry(jentry3);
		
		if(pthat3>170.) continue;
		
		//! Centrality bin
		
   		 if(bin3<0 || bin3>39)continue;
    	  int centb3=-1;
   		  double wcen3=1;
    
    	  centb3=GetCentBin(ncenb,bin3);
     	  wcen3 = fcen->Eval(bin3);

		
		
        if(bin3< 4 && bin3 >= 0)
        {
			if(jentry3%2==1)
			{
			for (int i= 0; i < njets3; i++)
			{ if ( refpt3[i] <0. ) continue;
				if(jtpt3[i] < 80. || jteta3[i] >2. || jteta3[i] <-2. ) continue;
				//for(int n3=0;n3<scale3;n3++)
				response_cent.Fill(jtpt3[i],refpt3[i],scale3);
			}  
		}
			
			else
			{
			for (int i= 0; i < njets3; i++)
				{
				 if ( refpt3[i] <0. ) continue;
				if(jtpt3[i] < 80. || jteta3[i] >2. || jteta3[i] <-2. ) continue;
				//for(int n3=0;n3<scale3;n3++)
				{hMeas_cent->Fill(jtpt3[i],scale3);
				hTrue_cent->Fill(refpt3[i],scale3);}
				}
				n1++;
			}
			
		} //bin if end
		
		if(bin3 < 40 && bin3 >= 20)
        {
			if(jentry3%2==1)
			{
			for (int i= 0; i < njets3; i++)
				
			{  if ( refpt3[i] <0. ) continue;
				if(jtpt3[i] < 80. || jteta3[i] >2. || jteta3[i] <-2. ) continue;
				//for(int n3=0;n3<scale3;n3++)
				response_periph.Fill(jtpt3[i],refpt3[i],scale3);
			} 
			
			}
			
			
			else
			{
			for (int i= 0; i < njets3; i++)
				{
				 if ( refpt3[i] <0. ) continue;
				if(jtpt3[i] < 80. || jteta3[i] >2. || jteta3[i] <-2. ) continue;
				//for(int n3=0;n3<scale3;n3++)
				{hMeas_periph->Fill(jtpt3[i],scale3);
				hTrue_periph->Fill(refpt3[i],scale3);}
				}
				n2++;
			}
		} // bin if end
		
		
	}
	

	cout<<" Read Pt hat  170 - inf "<<endl;
	
	
	Long64_t nentries4 = t4 ->GetEntries();
	Long64_t nbytes4 = 0, nb4 = 0;
	
	float xsection4=1.47e-06;
	float scale4=xsection4/nentries4;
	
	std::cout<<scale4<<endl; 
	
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
			if(jentry4%2==1)
			{for (int i= 0; i < njets4; i++)
				
			{ if ( refpt4[i] <0. ) continue;
				if(jtpt4[i] < 80. || jteta4[i] >2. || jteta4[i] <-2. ) continue;
				//for(int n4=0;n4<scale4;n4++)
				response_cent.Fill(jtpt4[i],refpt4[i],scale4);
			} 
			}
			else
			{
			for (int i= 0; i < njets4; i++)
				{
				if ( refpt4[i] <0. ) continue;
				if(jtpt4[i] < 80. || jteta4[i] >2. || jteta4[i] <-2. ) continue;
				//for(int n4=0;n4<scale4;n4++)
				{hMeas_cent->Fill(jtpt4[i],scale4);
				hTrue_cent->Fill(refpt4[i],scale4);}
				}
				n1++;
			}
		}// bin if end
		
		if(bin4 < 40 && bin4 >= 20)
        {
        	if(jentry4%2==1)
			
			{for (int i= 0; i < njets4; i++)
				
			 { if ( refpt4[i] <0. ) continue;
				if(jtpt4[i] < 80. || jteta4[i] >2. || jteta4[i] <-2. ) continue;
				//for(int n4=0;n4<scale4;n4++)
				response_periph.Fill(jtpt4[i],refpt4[i],scale4);
			 }   
			}
			
			else
			{
			for (int i= 0; i < njets4; i++)
				{
				if ( refpt4[i] <0. ) continue;
				if(jtpt4[i] < 80. || jteta4[i] >2. || jteta4[i] <-2. ) continue;
				//for(int n4=0;n4<scale4;n4++)
				{hMeas_periph->Fill(jtpt4[i],scale4);
				hTrue_periph->Fill(refpt4[i],scale4);}
				}
				n2++;
			}
			
		}// bin if end
		
		
	}
	
	

	
    
    
	
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
	
	
	 
	TH1F* hRatio1_cent= (TH1F*)hReco_cent->Clone("hRatio1_cent1");
   	hRatio1_cent->Divide(hTrue_cent);
   	
   	TH1F* hRatio1_periph= (TH1F*)hReco_periph->Clone("hRatio1_periph1");
   	hRatio1_periph->Divide(hTrue_periph);
   	
   	TH1F* hRatio2_cent= (TH1F*)hMeas_cent->Clone("hRatio2_cent");
   	hRatio2_cent->Divide(hTrue_cent);
   	
   	TH1F* hRatio2_periph= (TH1F*)hMeas_periph->Clone("hRatio2_periph");
   	hRatio2_periph->Divide(hTrue_periph);
   

   
	TCanvas *c1 = new TCanvas("c1","c1",600,900);
	c1->Divide(1,3);
	c1->cd(1);
	
	
	TLegend *tleg = new TLegend(0.65, 0.6, 0.95, 0.95);
	tleg->SetBorderSize(0);
	tleg->SetFillStyle(0);
	tleg->SetTextFont(42);
	tleg->SetTextSize(0.04);
	tleg->AddEntry(hReco_cent,"PbPb 0-10% unfo","pl");
	tleg->AddEntry(hReco_periph,"PbPb 50-100% unfo","pl");
	tleg->AddEntry(hMeas_cent," PbPb 0-10% reco","l");
	tleg->AddEntry(hMeas_cent," PbPb 50-100% reco ","l");
	tleg->AddEntry(hTrue_cent," PbPb 0-10% gen ","pl");
	tleg->AddEntry(hTrue_periph,"PbPb 50-100% gen ","pl");
	
	TH2F *htmp3 = new TH2F("htmp3","",NBINS-1, BOUNDARIES, 100, 0., hReco_periph->GetMaximum()*1.5);
	htmp3->SetXTitle("p_{T} (GeV)");
	htmp3->SetYTitle("Entries");
	htmp3->Draw();
	gPad->SetLogy();
	hReco_periph->SetMarkerColor(kRed);
	hReco_periph->SetMarkerStyle(21);
	hReco_periph->SetLineColor(kRed);
	hReco_periph->Draw("SAME");
	hTrue_periph->SetMarkerStyle(21);
	hMeas_periph->Draw("histSAME");
	
	hReco_cent->SetMarkerColor(kBlue);
	hReco_cent->SetMarkerStyle(21);
	hReco_cent->SetLineColor(kBlue);
	hReco_cent->Draw("SAME");
	hTrue_cent->SetMarkerStyle(21);
	hMeas_cent->Draw("histSAME");
	hTrue_cent->SetMarkerColor(1);
    hTrue_cent->SetMarkerStyle(25);
    hTrue_periph->SetMarkerColor(1);
    hTrue_periph->SetMarkerStyle(25);
    hTrue_cent->Draw("eSAME");
    hTrue_periph->Draw("eSAME");
	tleg->Draw("same");
	
	
	c1->cd(2);
	
	TLegend *tleg = new TLegend(0.65, 0.6, 0.90, 0.90);
	tleg->SetBorderSize(0);
	tleg->SetFillStyle(0);
	tleg->SetTextFont(42);
	tleg->SetTextSize(0.04);
	tleg->AddEntry(hRatio1_cent,"0-10% Unfolded / Truth ","pl");
	//tleg->AddEntry(hRatio1_periph,"50-100% Unfolded/ Truth","pl");
	tleg->AddEntry(hRatio2_cent,"0-10% Measured / Truth ","pl");
	//tleg->AddEntry(hRatio2_periph,"50-100% Measured/ Truth","pl");
	
	TH2F *htmp4 = new TH2F("htmp4","",NBINS-1, BOUNDARIES, 100, 0., 2.);
	htmp4->SetXTitle("p_{T} (GeV)");
	htmp4->SetYTitle("Ratio");
	htmp4->Draw();
	hRatio1_cent->SetMarkerColor(kBlue);
	//hRatio1_periph->SetMarkerColor(kRed);
	hRatio1_cent->Draw("esame");
	//hRatio1_periph->Draw("esame");
	
	hRatio2_cent->SetMarkerStyle(24);
	//hRatio2_periph->SetMarkerStyle(24);
	hRatio2_cent->SetMarkerColor(kBlue);
	//hRatio2_periph->SetMarkerColor(kRed);
	hRatio2_cent->Draw("esame");
	//hRatio2_periph->Draw("esame");
	tleg->Draw("same");
	
	c1->cd(3);
	
	TLegend *tleg = new TLegend(0.55, 0.5, 1.0, 0.90);
	tleg->SetBorderSize(0);
	tleg->SetFillStyle(0);
	tleg->SetTextFont(42);
	tleg->SetTextSize(0.04);
	tleg->AddEntry(hRatio1_periph,"50-100% Unfolded/ Truth","pl");
	tleg->AddEntry(hRatio2_periph,"50-100% Measured/ Truth","pl");
	
	TH2F *htmp5 = new TH2F("htmp5","",NBINS-1, BOUNDARIES, 100, 0., 2.);
	htmp5->SetXTitle("p_{T} (GeV)");
	htmp5->SetYTitle("Ratio");
	htmp5->Draw();
	hRatio1_periph->SetMarkerColor(kRed);
	hRatio1_periph->Draw("esame");
	
	hRatio2_periph->SetMarkerStyle(24);
	hRatio2_periph->SetMarkerColor(kRed);
	hRatio2_periph->Draw("esame");
	tleg->Draw("same");
	
  // c1->Print("JetSpec_Unfo_AllMC.eps");
  
 
   	
  	// Scale by Lumi* X section -- Nevt	 nentries of pp MC =1896300
	
			
		TH1F* hnorm_pbpb_cent1=(TH1F*)hReco_cent->Clone("hnorm_pbpb_cent1");
		for(int i=1; i<=hnorm_pbpb_cent1->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent1->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hReco_cent->GetBinContent(i)/width;
			float err_cor=sqrt(hReco_cent->GetBinContent(i))/width;
			hnorm_pbpb_cent1->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent1->SetBinError(i, err_cor);
			
		}
		
		
		TH1F* hnorm_pbpb_periph=(TH1F*)hReco_periph->Clone("hnorm_pbpb_periph");
		for(int i=1; i<=hnorm_pbpb_periph->GetNbinsX(); i++) {
			float width=hnorm_pbpb_periph->GetBinWidth(i);
			float dN_dpt_cor_pbpb= hReco_periph->GetBinContent(i)/width;
			float err_cor=sqrt( hReco_periph->GetBinContent(i))/width;
			hnorm_pbpb_periph->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_periph->SetBinError(i, err_cor);
			
		}		
		
		
		 TH1F* hgen_norm_pbpb_cent1=(TH1F*)hTrue_cent->Clone("hgen_norm_pbpb_cent1");
		for(int i=1; i<=hgen_norm_pbpb_cent1->GetNbinsX(); i++) {
			float width=hgen_norm_pbpb_cent1->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hTrue_cent->GetBinContent(i)/width/24783;
			float err_cor=sqrt(hTrue_cent->GetBinContent(i))/width/24783;
			hgen_norm_pbpb_cent1->SetBinContent(i, dN_dpt_cor_pbpb);
			hgen_norm_pbpb_cent1->SetBinError(i, err_cor);
			
		}
		
		
		
		TH1F* hgen_norm_pbpb_periph=(TH1F*)hTrue_periph->Clone("hgen_norm_pbpb_periph");
		for(int i=1; i<=hgen_norm_pbpb_periph->GetNbinsX(); i++) {
			float width=hgen_norm_pbpb_periph->GetBinWidth(i);
			float dN_dpt_cor_pbpb= hTrue_periph->GetBinContent(i)/width/24783;
			float err_cor=sqrt( hTrue_periph->GetBinContent(i))/width/24783;
			hgen_norm_pbpb_periph->SetBinContent(i, dN_dpt_cor_pbpb);
			hgen_norm_pbpb_periph->SetBinError(i, err_cor);
			
		}		
   
		
	
	
   
    
       // nentries of pp MC =1896300, 159807 ;  xsec of pp = 9.91e-5 ;
	
   	    float ScaleF= 1/9.91e-5;
	
	    TH1F* hRAA_cent1=(TH1F*)hnorm_pbpb_cent1->Clone("hRAA_cent1");
		TH1F* hRAA_periph=(TH1F*)hnorm_pbpb_periph->Clone("hRAA_periph");
		
		TH1F* hgen_RAA_cent1=(TH1F*)hgen_norm_pbpb_cent1->Clone("hgen_RAA_cent1");
		TH1F* hgen_RAA_periph=(TH1F*)hgen_norm_pbpb_periph->Clone("hgen_RAA_periph");
		
		
		hRAA_cent1->Scale(ScaleF*10);
		hRAA_periph->Scale(ScaleF*2);
		
		hgen_RAA_cent1->Scale(10);
	    hgen_RAA_periph->Scale(2);
		
    	TFile *j = new TFile("pp_ak3_MC_Unfo_bay.root");
    	//TFile *j = new TFile("pp_ic5_MC_Unfo_bay.root");
		TH1F* hnorm_pp=(TH1F*)j->Get("hnorm_pp"); 
		
		
		hRAA_cent1->Divide(hnorm_pp);
		hRAA_periph->Divide(hnorm_pp);
		
		hgen_RAA_cent1->Divide(hgen_norm_pp);
		hgen_RAA_periph->Divide(hgen_norm_pp);
		
	
	
	
		j->Close();


		
		TCanvas *c4 = new TCanvas("c4","");
		TH2F *htmp1 = new TH2F("htmp1","",NBINS-1,BOUNDARIES, 100, 0.,hRAA_cent1->GetMaximum()*1.5);
		
		htmp1->GetXaxis()->SetTitle("p_{T} [GeV/c]");
		htmp1->GetYaxis()->SetTitle("R_{AA}");
		htmp1->SetTitle("R_{AA}");
		htmp1->Draw();
    	hRAA_cent1->SetMarkerStyle(20);
		hRAA_cent1->SetMarkerSize(0.8);
		hRAA_periph->SetMarkerStyle(20);
		hRAA_periph->SetMarkerSize(0.8);
		hRAA_cent1->SetMarkerColor(kRed);
		hRAA_cent1->SetLineColor(kRed);
		hRAA_periph->SetMarkerColor(kBlue);
		hRAA_periph->SetLineColor(kBlue);
		hRAA_cent1->Draw("same");
		hRAA_periph->Draw("same");
		
		hgen_RAA_cent1->SetMarkerStyle(25);
		hgen_RAA_periph->SetMarkerStyle(25);
		hgen_RAA_cent1->SetMarkerSize(0.8);
		hgen_RAA_periph->SetMarkerSize(0.8);
		hgen_RAA_cent1->SetMarkerColor(kBlue);
		hgen_RAA_periph->SetMarkerColor(kRed);
		
		hgen_RAA_cent1->Draw("same");
		hgen_RAA_periph->Draw("same");
		
		
		TLegend *tleg2 = new TLegend(0.65, 0.6, 1.00, 0.85);
		tleg2->SetBorderSize(0);
		tleg2->SetFillStyle(0);
		tleg2->SetTextFont(42);
		tleg2->AddEntry(hRAA_cent1,"PbPb 0-10% Unfo / pp Unfo","pl");
		tleg2->AddEntry(hRAA_periph,"PbPb 50-100% Unfo / pp Unfo","pl");
		tleg2->AddEntry(hgen_RAA_cent1,"PbPb 0-10% Truth / pp Truth","pl");
		tleg2->AddEntry(hgen_RAA_periph,"PbPb 50-100% Truth / pp Truth","pl");
		tleg2->SetTextSize(0.03);
		tleg2->Draw();
		
		//c4->Print("RAA_Unfo_AllMC_ak3.eps");
	
	
	// f->Write();
	// f->Close();
	
	
	
	
	
	

	
	
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


//#ifndef __CINT__
//int main () { RooUnfoldPhoJ(); return 0; }  // Main program when run stand-alone
//#endif





