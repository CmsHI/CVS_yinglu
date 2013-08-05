
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
//#include "RooUnfoldBayes.h"

//#include "RooUnfoldSvd.h"
#include "RooUnfoldBinByBin.h"


using namespace std;


#endif


int GetCentBin(int,int);


//==============================================================================
// Unfolding Ying Lu 08 07 11
//==============================================================================



void RooUnfold_InclusiveJets_hidata_June_07(int method,int algo) // algo 2 =akpu2 ; 3 =akpu3 ; 4 =akpu4 ;1 = icpu5
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
    
	
	//const int NBINS=9;
	//Double_t BOUNDARIES[NBINS] = {100,110,120,130,150,180,200,300,400};
	//const int NBINS=31;
	//Double_t BOUNDARIES[NBINS] = {100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400};
	
	const int NBINS=31;
	Double_t BOUNDARIES[NBINS] = {100.0000000, 105.5113064,111.3263577, 117.4618943, 123.9355792, 130.7660486, 137.9729661, 145.5770790, 153.6002778, 162.0656597, 170.9975947, 180.4217960, 190.3653939, 200.8570139, 211.9268593, 223.6067977, 235.9304534, 248.9333035, 262.6527804, 277.1283798, 292.4017738, 308.5169314, 325.5202446, 343.4606625, 362.3898318, 382.3622457, 403.4354004, 425.6699613, 449.1299369, 473.8828636, 500.0000000};
	
	
	const int NBINS_=31;
	Double_t BOUNDARIES_[NBINS_] = {100.0000000, 105.5113064,111.3263577, 117.4618943, 123.9355792, 130.7660486, 137.9729661, 145.5770790, 153.6002778, 162.0656597, 170.9975947, 180.4217960, 190.3653939, 200.8570139, 211.9268593, 223.6067977, 235.9304534, 248.9333035, 262.6527804, 277.1283798, 292.4017738, 308.5169314, 325.5202446, 343.4606625, 362.3898318, 382.3622457, 403.4354004, 425.6699613, 449.1299369, 473.8828636, 500.0000000};
	
	
	/*
	const int NBINS_=54;
	Double_t BOUNDARIES_[NBINS_] ={29.11541580, 30.72005556, 32.41313193, 34.19951893, 36.08435919, 
38.07307877, 40.17140278, 42.38537186, 44.72135955, 47.18609068, 
49.78666069, 52.53055609, 55.42567596, 58.48035476, 61.70338627, 
65.10404892, 68.69213250, 72.47796637, 76.47244913, 80.68708008, 
85.13399225, 89.82598738, 94.77657273, 100.0000000, 105.5113064, 
111.3263577, 117.4618943, 123.9355792, 130.7660486, 137.9729661, 
145.5770790, 153.6002778, 162.0656597, 170.9975947, 180.4217960, 
190.3653939, 200.8570139, 211.9268593, 223.6067977, 235.9304534, 
248.9333035, 262.6527804, 277.1283798, 292.4017738, 308.5169314, 
325.5202446, 343.4606625, 362.3898318, 382.3622457, 403.4354004, 
425.6699613, 449.1299369, 473.8828636, 500.0000000};
	*/

	int ncenb=6;
	
	float ptmax = 400.0;
    float ymin = 0.0001;
    float ymax = 1.7;
    
    
////*******************lumi number for the sample***************************
    
    
   // float lumi=150.;
   // float pplumi=231.;

	float lumi=103.;
	float pplumi=212.;
	
///*************************************************************************




	TFile *pbpb_Unfo = new TFile("pbpb_Unfo.root","RECREATE");
	
	TH1F* hResTrue_cent1= new TH1F ("Restrue_cent1", " ResTruth_cent1",    NBINS_-1, BOUNDARIES_); //Gen
	TH1F* hResMeas_cent1= new TH1F ("Resmeas_cent1", " ResMeasured_cent1", NBINS-1, BOUNDARIES); //Reco
	
	TH1F* hResTrue_cent2= new TH1F ("Restrue_cent2", " ResTruth_cent2",    NBINS_-1, BOUNDARIES_); //Gen
	TH1F* hResMeas_cent2= new TH1F ("Resmeas_cent2", " ResMeasured_cent2", NBINS-1, BOUNDARIES); //Reco
	
	TH1F* hResTrue_cent3= new TH1F ("Restrue_cent3", " ResTruth_cent3",    NBINS_-1, BOUNDARIES_); //Gen
	TH1F* hResMeas_cent3= new TH1F ("Resmeas_cent3", " ResMeasured_cent3", NBINS-1, BOUNDARIES); //Reco
	
	TH1F* hResTrue_cent4= new TH1F ("Restrue_cent4", " ResTruth_cent4",    NBINS_-1, BOUNDARIES_); //Gen
	TH1F* hResMeas_cent4= new TH1F ("Resmeas_cent4", " ResMeasured_cent4", NBINS-1, BOUNDARIES); //Reco
	
	TH1F* hResTrue_cent5= new TH1F ("Restrue_cent5", " ResTruth_cent5",    NBINS_-1, BOUNDARIES_); //Gen
	TH1F* hResMeas_cent5= new TH1F ("Resmeas_cent5", " ResMeasured_cent5", NBINS-1, BOUNDARIES); //Reco
	
	TH1F* hResTrue_cent6= new TH1F ("Restrue_cent6", " ResTruth_cent6",    NBINS_-1, BOUNDARIES_); //Gen
	TH1F* hResMeas_cent6= new TH1F ("Resmeas_cent6", " ResMeasured_cent6", NBINS-1, BOUNDARIES); //Reco
	
	
	TH2F* hMatrix_cent1= new TH2F ("hMatrix_cent1", " hMatrix_cent1;Genjet^{p_{T}};Recojet^{p_{T}}", NBINS_-1, BOUNDARIES_,NBINS-1, BOUNDARIES); //Reco
	TH2F* hMatrix_cent2= new TH2F ("hMatrix_cent2", " hMatrix_cent2;Genjet^{p_{T}};Recojet^{p_{T}}", NBINS_-1, BOUNDARIES_,NBINS-1, BOUNDARIES); //Reco
	TH2F* hMatrix_cent3= new TH2F ("hMatrix_cent3", " hMatrix_cent3;Genjet^{p_{T}};Recojet^{p_{T}}", NBINS_-1, BOUNDARIES_,NBINS-1, BOUNDARIES); //Reco
	TH2F* hMatrix_cent4= new TH2F ("hMatrix_cent4", " hMatrix_cent4;Genjet^{p_{T}};Recojet^{p_{T}}", NBINS_-1, BOUNDARIES_,NBINS-1, BOUNDARIES); //Reco
	TH2F* hMatrix_cent5= new TH2F ("hMatrix_cent5", " hMatrix_cent5;Genjet^{p_{T}};Recojet^{p_{T}}", NBINS_-1, BOUNDARIES_,NBINS-1, BOUNDARIES); //Reco
	TH2F* hMatrix_cent6= new TH2F ("hMatrix_cent6", " hMatrix_cent6;Genjet^{p_{T}};Recojet^{p_{T}}", NBINS_-1, BOUNDARIES_,NBINS-1, BOUNDARIES); //Reco

	
    RooUnfoldResponse response_cent1 (hResMeas_cent1,hResTrue_cent1);
    RooUnfoldResponse response_cent2 (hResMeas_cent2,hResTrue_cent2);
    RooUnfoldResponse response_cent3 (hResMeas_cent3,hResTrue_cent3);
    RooUnfoldResponse response_cent4 (hResMeas_cent4,hResTrue_cent4);
    RooUnfoldResponse response_cent5 (hResMeas_cent5,hResTrue_cent5);
    RooUnfoldResponse response_cent6 (hResMeas_cent6,hResTrue_cent6);
    
	
	//! Centrality reweighting function
 	 TF1* fcen = new TF1("fcen","exp(-1.0*pow(x+1.11957e+01,2)/pow(1.34120e+01,2)/2)",0,40);
 	 
 	 
 	
	
	///////// INPUT PbPb & pp  DATA FILE
	
	
	
	if (algo == 1)  TFile *f = new TFile("RAA_JetSpecta_ak3_Data_Forest2_June_13.root");
	if (algo == 2)  TFile *f = new TFile("RAA_JetSpecta_ic5_Data_Forest2_June_13.root");

	
		TH1F* hMeas_cent1=(TH1F*)f->Get("hcorpt_pbpb_cent1"); 
		TH1F* hMeas_cent2=(TH1F*)f->Get("hcorpt_pbpb_cent2"); 
		TH1F* hMeas_cent3=(TH1F*)f->Get("hcorpt_pbpb_cent3"); 
		TH1F* hMeas_cent4=(TH1F*)f->Get("hcorpt_pbpb_cent4"); 
		TH1F* hMeas_cent5=(TH1F*)f->Get("hcorpt_pbpb_cent5"); 
		TH1F* hMeas_cent6=(TH1F*)f->Get("hcorpt_pbpb_cent6");
		TH1F* hMeas_pp=(TH1F*)f->Get("hcorpt_pp");
		
		
		TH1F* hMeas_RAA_cent1=(TH1F*)f->Get("hRAA_cent1"); 
		TH1F* hMeas_RAA_cent2=(TH1F*)f->Get("hRAA_cent2"); 
		TH1F* hMeas_RAA_cent3=(TH1F*)f->Get("hRAA_cent3"); 
		TH1F* hMeas_RAA_cent4=(TH1F*)f->Get("hRAA_cent4"); 
		TH1F* hMeas_RAA_cent5=(TH1F*)f->Get("hRAA_cent5"); 
		TH1F* hMeas_RAA_cent6=(TH1F*)f->Get("hRAA_cent6");
		
		
		
		
//////// INPUT  UNFOLDED  pp  Spectra
	
		//TFile *j = new TFile("pp_ak3_BinBin_Forest1_lowerpTbin_June_12.root");
		//TFile *j = new TFile(" pp_ak3_Bayes_Forest1_differentbin_June_12.root");
		TFile *j = new TFile("pp_binbin_ak3_Forest2_June_16.root");
		TH1F* hnorm_pp=(TH1F*)j->Get("hnorm_pp");
	
	
	 
	/*
	
	cout<<" Read Pt hat  50 - inf "<<endl;
	
	float jtpt1[5000];
	float refpt1[5000];
	float jteta1[5000];
	float pthat1;
	int njets1;
	int bin1;
	
	
    TString inname1="";
	
	
	TFile* inf1 = new TFile(inname1,"read");
	
	TTree* t1 = (TTree*)inf1->Get("hiEvtAnalyzer/HiTree");

	if (algo == 1)TTree* tree1 = (TTree*)inf1->Get("icPu5JetAnalyzer/t");

	if (algo == 2 )TTree* tree1 = (TTree*)inf1->Get("akPu2PFJetAnalyzer/t");
	if (algo == 3 )TTree* tree1 = (TTree*)inf1->Get("akPu3PFJetAnalyzer/t");
	if (algo == 4 )TTree* tree1 = (TTree*)inf1->Get("akPu4PFJetAnalyzer/t");
	
	
	
	
	tree1->SetBranchAddress("jtpt",jtpt1);
	tree1->SetBranchAddress("refpt",refpt1);
	tree1->SetBranchAddress("nref",&njets1);
	tree1->SetBranchAddress("jteta",&jteta1);
	tree1->SetBranchAddress("pthat",&pthat1);
	t1->SetBranchAddress("hiBin",&bin1);
	
	
	
	
	Long64_t nentries1 = t1 ->GetEntries();
	Long64_t nbytes1 = 0, nb1 = 0;
	
	float xsection1=1.021e-03;
	float scale1=xsection1/nentries1; 
	
	
	for (Long64_t jentry1=0; jentry1<nentries1;jentry1++)
	{
		
  		t1->GetEntry(jentry1);
		tree1->GetEntry(jentry1);
		
		
     	  
     	  
		if(pthat1>80. || pthat1==80.) continue;

        if(bin1< 2 && bin1 >= 0)
        {
		
   		  double wcen1=1;
          wcen1 = fcen->Eval(bin1);
     	  
     	  
			for (int i= 0; i < njets1; i++)
				
			{ if ( refpt1[i] <0. ) continue;
				if(jteta1[i] >2. || jteta1[i] <-2. ) continue;
				response_cent1.Fill(jtpt1[i],refpt1[i],scale1*wcen1);
				hMatrix_cent1->Fill(jtpt1[i],refpt1[i],scale1*wcen1);

			}           
		}
		
		if(bin1< 4 && bin1 >= 2)
        {
   		  	double wcen2=1;
     	 	wcen2 = fcen->Eval(bin1);
     	  	
			for (int i= 0; i < njets1; i++)
				
			{ if ( refpt1[i] <0. ) continue;
				if(jteta1[i] >2. || jteta1[i] <-2. ) continue;
				response_cent2.Fill(jtpt1[i],refpt1[i],scale1*wcen2);
				hMatrix_cent2->Fill(jtpt1[i],refpt1[i],scale1*wcen2);
			}           
		}
		
		if(bin1< 12 && bin1 >= 4)
        {
			double wcen3=1;
     	 	wcen3 = fcen->Eval(bin1);
				
			for (int i= 0; i < njets1; i++)
				
			{ if ( refpt1[i] <0. ) continue;
				if(jteta1[i] >2. || jteta1[i] <-2. ) continue;
				response_cent3.Fill(jtpt1[i],refpt1[i],scale1*wcen3);
				hMatrix_cent3->Fill(jtpt1[i],refpt1[i],scale1*wcen3);
			}           
		}
		
		if(bin1< 20 && bin1 >= 12)
        {
			double wcen4=1;
     	 	wcen4 = fcen->Eval(bin1);
				
			for (int i= 0; i < njets1; i++)
				
			{ if ( refpt1[i] <0. ) continue;
				if(jteta1[i] >2. || jteta1[i] <-2. ) continue;
				response_cent4.Fill(jtpt1[i],refpt1[i],scale1*wcen4);
				hMatrix_cent4->Fill(jtpt1[i],refpt1[i],scale1*wcen4);
			}           
		}
		
		if(bin1< 28 && bin1 >= 20)
        {
			double wcen5=1;
     	 	wcen5 = fcen->Eval(bin1);
				
			for (int i= 0; i < njets1; i++)
				
			{ if ( refpt1[i] <0. ) continue;
				if(jteta1[i] >2. || jteta1[i] <-2. ) continue;
				response_cent5.Fill(jtpt1[i],refpt1[i],scale1*wcen5);
				hMatrix_cent5->Fill(jtpt1[i],refpt1[i],scale1*wcen5);
			}           
		}
		
		if(bin1< 36 && bin1 >= 28)
        {
			double wcen6=1;
     	 	wcen6 = fcen->Eval(bin1);
				
			for (int i= 0; i < njets1; i++)
				
			{ if ( refpt1[i] <0. ) continue;
				if(jteta1[i] >2. || jteta1[i] <-2. ) continue;
				response_cent6.Fill(jtpt1[i],refpt1[i],scale1*wcen6);
				hMatrix_cent6->Fill(jtpt1[i],refpt1[i],scale1*wcen6);
			}             
		}
	
		
	}
	inf1->Close();
	*/
	
	
	cout<<" Read Pt hat  80 - inf "<<endl;
	
	float jtpt2[5000];
	float refpt2[5000];
	float jteta2[5000];
	float pthat2;
	int njets2;
	int bin2;
	
	
    TString inname2="/data/users/yinglu/JetRAA/Pythia80_HydjetDrum_mix01_HiForest2_v20.root";

	
	TFile* inf2 = new TFile(inname2,"read");
	
	TTree* t2 = (TTree*)inf2->Get("hiEvtAnalyzer/HiTree");

	if (algo == 1)TTree* tree2 = (TTree*)inf2->Get("icPu5JetAnalyzer/t");

	if (algo == 2 )TTree* tree2 = (TTree*)inf2->Get("akPu2PFJetAnalyzer/t");
	if (algo == 3 )TTree* tree2 = (TTree*)inf2->Get("akPu3PFJetAnalyzer/t");
	if (algo == 4 )TTree* tree2 = (TTree*)inf2->Get("akPu4PFJetAnalyzer/t");
	
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
		
		
		if(pthat2>120. || pthat2==120.) continue;

        if(bin2< 2 && bin2 >= 0)
        {
			double wcen1=1;
     	 	wcen1 = fcen->Eval(bin2);
     	 	
			for (int i= 0; i < njets2; i++)
				
			{ if ( refpt2[i] <0. ) continue;
				if(jteta2[i] >2. || jteta2[i] <-2. ) continue;
				response_cent1.Fill(jtpt2[i],refpt2[i],scale2*wcen1);
				hMatrix_cent1->Fill(jtpt2[i],refpt2[i],scale2*wcen1);
			}           
		}
		
		if(bin2< 4 && bin2 >= 2)
        {
			double wcen2=1;
     	 	wcen2 = fcen->Eval(bin2);
     	 	
			for (int i= 0; i < njets2; i++)
				
			{ if ( refpt2[i] <0. ) continue;
				if(jteta2[i] >2. || jteta2[i] <-2. ) continue;
				response_cent2.Fill(jtpt2[i],refpt2[i],scale2*wcen2);
				hMatrix_cent2->Fill(jtpt2[i],refpt2[i],scale2*wcen2);
			}           
		}
		
		if(bin2< 12 && bin2 >= 4)
        {
			
			double wcen3=1;
     	 	wcen3 = fcen->Eval(bin2);
     	 	
			for (int i= 0; i < njets2; i++)
				
			{ if ( refpt2[i] <0. ) continue;
				if(jteta2[i] >2. || jteta2[i] <-2. ) continue;
				response_cent3.Fill(jtpt2[i],refpt2[i],scale2*wcen3);
				hMatrix_cent3->Fill(jtpt2[i],refpt2[i],scale2*wcen3);
			}           
		}
		
		if(bin2< 20 && bin2 >= 12)
        {
        
        	double wcen4=1;
     	 	wcen4 = fcen->Eval(bin2);
     	 	
			
			for (int i= 0; i < njets2; i++)
				
			{ if ( refpt2[i] <0. ) continue;
				if(jteta2[i] >2. || jteta2[i] <-2. ) continue;
				response_cent4.Fill(jtpt2[i],refpt2[i],scale2*wcen4);
				hMatrix_cent4->Fill(jtpt2[i],refpt2[i],scale2*wcen4);
			}           
		}
		
		if(bin2< 28 && bin2 >= 20)
        {
			double wcen5=1;
     	 	wcen5 = fcen->Eval(bin2);
     	 	
			for (int i= 0; i < njets2; i++)
				
			{ if ( refpt2[i] <0. ) continue;
				if(jteta2[i] >2. || jteta2[i] <-2. ) continue;
				response_cent5.Fill(jtpt2[i],refpt2[i],scale2*wcen5);
				hMatrix_cent5->Fill(jtpt2[i],refpt2[i],scale2*wcen5);
			}           
		}
		
		if(bin2< 36 && bin2 >= 28)
        {
			double wcen6=1;
     	 	wcen6 = fcen->Eval(bin2);
     	 	
			for (int i= 0; i < njets2; i++)
				
			{ if ( refpt2[i] <0. ) continue;
				if(jteta2[i] >2. || jteta2[i] <-2. ) continue;
				response_cent6.Fill(jtpt2[i],refpt2[i],scale2*wcen6);
				hMatrix_cent6->Fill(jtpt2[i],refpt2[i],scale2*wcen6);
			}           
		}
	
		
	}
	
	inf2->Close();
	
	
	cout<<" Read Pt hat  120 - inf "<<endl;
	
	float jtpt3[5000];
	float refpt3[5000];
	float jteta3[5000];
	float pthat3;
	int njets3;
	int bin3;
	
	TString inname3="/data/users/yinglu/JetRAA/Pythia120_HydjetDrum_mix01_HiForest2_v19_0.root";
	
	TFile* inf3 = new TFile(inname3,"read");
	
	TTree* t3 = (TTree*)inf3->Get("hiEvtAnalyzer/HiTree");
	
	if (algo == 1)TTree* tree3 = (TTree*)inf3->Get("icPu5JetAnalyzer/t");

	if (algo == 2 )TTree* tree3 = (TTree*)inf3->Get("akPu2PFJetAnalyzer/t");
	if (algo == 3 )TTree* tree3 = (TTree*)inf3->Get("akPu3PFJetAnalyzer/t");
	if (algo == 4 )TTree* tree3 = (TTree*)inf3->Get("akPu4PFJetAnalyzer/t");
	
	tree3->SetBranchAddress("jtpt",jtpt3);
	tree3->SetBranchAddress("refpt",refpt3);
	tree3->SetBranchAddress("nref",&njets3);
	tree3->SetBranchAddress("jteta",&jteta3);
	tree3->SetBranchAddress("pthat",&pthat3);
	t3->SetBranchAddress("hiBin",&bin3);
	
	
	
	Long64_t nentries3 = t3 ->GetEntries();
	Long64_t nbytes3 = 0, nb3 = 0;
	
	float xsection3=1.128e-05;
	float scale3=xsection3/nentries3;
	
	std::cout<<scale3<<endl; //Here scale3=519
	
	for (Long64_t jentry3=0; jentry3<nentries3;jentry3++)
	{
		
  		t3->GetEntry(jentry3);
		tree3->GetEntry(jentry3);
		
		
		if(pthat3>170. || pthat3==170.) continue;
		
		
		  if(bin3< 2 && bin3 >= 0)
        {
			double wcen1=1;
     	 	wcen1 = fcen->Eval(bin3);
     	 	
			for (int i= 0; i < njets3; i++)
				
			{ if ( refpt3[i] <0. ) continue;
				if(jteta3[i] >2. || jteta3[i] <-2. ) continue;
				response_cent1.Fill(jtpt3[i],refpt3[i],scale3*wcen1);
				hMatrix_cent1->Fill(jtpt3[i],refpt3[i],scale3*wcen1);
			}           
		}
		  if(bin3< 4 && bin3 >= 2)
        {
			double wcen2=1;
     	 	wcen2 = fcen->Eval(bin3);
     	 	
			for (int i= 0; i < njets3; i++)
				
			{ if ( refpt3[i] <0. ) continue;
				if( jteta3[i] >2. || jteta3[i] <-2. ) continue;
				response_cent2.Fill(jtpt3[i],refpt3[i],scale3*wcen2);
				hMatrix_cent2->Fill(jtpt3[i],refpt3[i],scale3*wcen2);
			}           
		}
		  if(bin3< 12 && bin3 >= 4)
        {
        
        	double wcen3=1;
     	 	wcen3 = fcen->Eval(bin3);
     	 	
			
			for (int i= 0; i < njets3; i++)
				
			{ if ( refpt3[i] <0. ) continue;
				if(jteta3[i] >2. || jteta3[i] <-2. ) continue;
				response_cent3.Fill(jtpt3[i],refpt3[i],scale3*wcen3);
				hMatrix_cent3->Fill(jtpt3[i],refpt3[i],scale3*wcen3);
			}           
		}
		  if(bin3< 20 && bin3 >= 12)
        {
			double wcen4=1;
     	 	wcen4 = fcen->Eval(bin3);
     	 	
			for (int i= 0; i < njets3; i++)
				
			{ if ( refpt3[i] <0. ) continue;
				if(jteta3[i] >2. || jteta3[i] <-2. ) continue;
				response_cent4.Fill(jtpt3[i],refpt3[i],scale3*wcen4);
				hMatrix_cent4->Fill(jtpt3[i],refpt3[i],scale3*wcen4);
			}           
		}
		  if(bin3< 28 && bin3 >= 20)
        {
        
        	double wcen5=1;
     	 	wcen5 = fcen->Eval(bin3);
			
			for (int i= 0; i < njets3; i++)
				
			{ if ( refpt3[i] <0. ) continue;
				if(jteta3[i] >2. || jteta3[i] <-2. ) continue;
				response_cent5.Fill(jtpt3[i],refpt3[i],scale3*wcen5);
				hMatrix_cent5->Fill(jtpt3[i],refpt3[i],scale3*wcen5);
			}           
		}
		
		
        if(bin3< 36 && bin3 >= 28)
        {
        	double wcen6=1;
     	 	wcen6 = fcen->Eval(bin3);
			
			for (int i= 0; i < njets3; i++)
				
			{ if ( refpt3[i] <0. ) continue;
				if(jteta3[i] >2. || jteta3[i] <-2. ) continue;
				response_cent6.Fill(jtpt3[i],refpt3[i],scale3*wcen6);
				hMatrix_cent6->Fill(jtpt3[i],refpt3[i],scale3*wcen6);
			}           
		}
		
		
	}
	
	inf3->Close();

	cout<<" Read Pt hat  170 - inf "<<endl;
	
	float jtpt4[5000];
	float refpt4[5000];
	float jteta4[5000];
	float pthat4;
	int njets4;
	int bin4;
	
	
	TString inname4="/data/users/yinglu/JetRAA/Pythia170_HydjetDrum_mix01_HiForest2_v19.root";
	
	TFile* inf4 = new TFile(inname4,"read");
	
	TTree* t4 = (TTree*)inf4->Get("hiEvtAnalyzer/HiTree");
	
	if (algo == 1)TTree* tree4 = (TTree*)inf4->Get("icPu5JetAnalyzer/t");

	if (algo == 2 )TTree* tree4 = (TTree*)inf4->Get("akPu2PFJetAnalyzer/t");
	if (algo == 3 )TTree* tree4 = (TTree*)inf4->Get("akPu3PFJetAnalyzer/t");
	if (algo == 4 )TTree* tree4 = (TTree*)inf4->Get("akPu4PFJetAnalyzer/t");
	
	
	tree4->SetBranchAddress("jtpt",jtpt4);
	tree4->SetBranchAddress("refpt",refpt4);
	tree4->SetBranchAddress("nref",&njets4);
	tree4->SetBranchAddress("jteta",&jteta4);
	tree4->SetBranchAddress("pthat",&pthat4);
	t4->SetBranchAddress("hiBin",&bin4);
	
	

	
	Long64_t nentries4 = t4 ->GetEntries();
	Long64_t nbytes4 = 0, nb4 = 0;
	
	float xsection4=1.47e-06;
	float scale4=xsection4/nentries4;
	
	std::cout<<scale4<<endl; // Here Scale4=16
	
	for (Long64_t jentry4=0; jentry4<nentries4;jentry4++)
	{
		
  		t4->GetEntry(jentry4);
		tree4->GetEntry(jentry4);
		
		
		if(pthat3>200. || pthat3==200.) continue;
		
        if(bin4< 2 && bin4 >= 0)
        {
        	double wcen1=1;
     	 	wcen1 = fcen->Eval(bin4);
			
			for (int i= 0; i < njets4; i++)
				
			{ if ( refpt4[i] <0. ) continue;
				if(jteta4[i] >2. || jteta4[i] <-2. ) continue;
				response_cent1.Fill(jtpt4[i],refpt4[i],scale4*wcen1);
				hMatrix_cent1->Fill(jtpt4[i],refpt4[i],scale4*wcen1);
			}           
		}
		
		if(bin4< 4 && bin4 >= 2)
        {	
        	double wcen2=1;
     	 	wcen2 = fcen->Eval(bin4);
			
			for (int i= 0; i < njets4; i++)
				
			{ if ( refpt4[i] <0. ) continue;
				if(jteta4[i] >2. || jteta4[i] <-2. ) continue;
				response_cent2.Fill(jtpt4[i],refpt4[i],scale4*wcen2);
				hMatrix_cent2->Fill(jtpt4[i],refpt4[i],scale4*wcen2);
			}           
		}
		
		if(bin4< 12 && bin4 >= 4)
        {
			double wcen3=1;
     	 	wcen3 = fcen->Eval(bin4);
     	 	
			for (int i= 0; i < njets4; i++)
				
			{ if ( refpt4[i] <0. ) continue;
				if(jteta4[i] >2. || jteta4[i] <-2. ) continue;
				response_cent3.Fill(jtpt4[i],refpt4[i],scale4*wcen3);
				hMatrix_cent3->Fill(jtpt4[i],refpt4[i],scale4*wcen3);
			}           
		}
		
		if(bin4< 20 && bin4 >= 12)
        {
			double wcen4=1;
     	 	wcen4 = fcen->Eval(bin4);
     	 	
			for (int i= 0; i < njets4; i++)
				
			{ if ( refpt4[i] <0. ) continue;
				if(jteta4[i] >2. || jteta4[i] <-2. ) continue;
				response_cent4.Fill(jtpt4[i],refpt4[i],scale4*wcen4);
				hMatrix_cent4->Fill(jtpt4[i],refpt4[i],scale4*wcen4);
			}           
		}
		
		if(bin4< 28 && bin4 >= 20)
        {
			double wcen5=1;
     	 	wcen5 = fcen->Eval(bin4);
     	 	
			for (int i= 0; i < njets4; i++)
				
			{ if ( refpt4[i] <0. ) continue;
				if( jteta4[i] >2. || jteta4[i] <-2. ) continue;
				response_cent5.Fill(jtpt4[i],refpt4[i],scale4*wcen5);
				hMatrix_cent5->Fill(jtpt4[i],refpt4[i],scale4*wcen5);

			}           
		}
		
		if(bin4< 36 && bin4 >= 28)
        {
			double wcen3=6;
     	 	wcen6 = fcen->Eval(bin4);
     	 	
			for (int i= 0; i < njets4; i++)
				
			{ if ( refpt4[i] <0. ) continue;
				if( jteta4[i] >2. || jteta4[i] <-2. ) continue;
				response_cent6.Fill(jtpt4[i],refpt4[i],scale4*wcen6);
				hMatrix_cent6->Fill(jtpt4[i],refpt4[i],scale4*wcen6);
			}           
		}
		
		
		
		
	}
	
	inf4->Close();
	
	cout<<" Read Pt hat  200 - inf "<<endl;
	
	float jtpt5[5000];
	float refpt5[5000];
	float jteta5[5000];
	float pthat5;
	int njets5;
	int bin5;
	
	TString inname5="/data/users/yinglu/JetRAA/Pythia200_HydjetDrum_mix01_HiForest2_v19.root";
	
	TFile* inf5 = new TFile(inname5,"read");
	
	TTree* t5 = (TTree*)inf5->Get("hiEvtAnalyzer/HiTree");
	
	if (algo == 1)TTree* tree5 = (TTree*)inf5->Get("icPu5JetAnalyzer/t");

	if (algo == 2 )TTree* tree5 = (TTree*)inf5->Get("akPu2PFJetAnalyzer/t");
	if (algo == 3 )TTree* tree5 = (TTree*)inf5->Get("akPu3PFJetAnalyzer/t");
	if (algo == 4 )TTree* tree5 = (TTree*)inf5->Get("akPu4PFJetAnalyzer/t");
	
	
	tree5->SetBranchAddress("jtpt",jtpt5);
	tree5->SetBranchAddress("refpt",refpt5);
	tree5->SetBranchAddress("nref",&njets5);
	tree5->SetBranchAddress("jteta",&jteta5);
	tree5->SetBranchAddress("pthat",&pthat5);
	t5->SetBranchAddress("hiBin",&bin5);
	
	

	
	Long64_t nentries5 = t5 ->GetEntries();
	Long64_t nbytes5 = 0, nb5 = 0;
	
	float xsection5=5.310e-07;
	float scale5=xsection5/nentries5;
	
	std::cout<<scale5<<endl; 
	
	for (Long64_t jentry5=0; jentry5<nentries5;jentry5++)
	{
		
  		t5->GetEntry(jentry5);
		tree5->GetEntry(jentry5);
		
		
		
		
        if(bin5< 2 && bin5 >= 0)
        {
        	double wcen1=1;
     	 	wcen1 = fcen->Eval(bin5);
			
			for (int i= 0; i < njets5; i++)
				
			{ if ( refpt5[i] <0. ) continue;
				if(jteta5[i] >2. || jteta5[i] <-2. ) continue;
				response_cent1.Fill(jtpt5[i],refpt5[i],scale5*wcen1);
				hMatrix_cent1->Fill(jtpt5[i],refpt5[i],scale5*wcen1);
			}           
		}
		
		if(bin5< 4 && bin5 >= 2)
        {	
        	double wcen2=1;
     	 	wcen2 = fcen->Eval(bin5);
			
			for (int i= 0; i < njets5; i++)
				
			{ if ( refpt5[i] <0. ) continue;
				if(jteta5[i] >2. || jteta5[i] <-2. ) continue;
				response_cent2.Fill(jtpt5[i],refpt5[i],scale5*wcen2);
				hMatrix_cent2->Fill(jtpt5[i],refpt5[i],scale5*wcen2);
			}           
		}
		
		if(bin5< 12 && bin5 >= 4)
        {
			double wcen3=1;
     	 	wcen3 = fcen->Eval(bin5);
     	 	
			for (int i= 0; i < njets5; i++)
				
			{ if ( refpt5[i] <0. ) continue;
				if(jteta5[i] >2. || jteta5[i] <-2. ) continue;
				response_cent3.Fill(jtpt5[i],refpt5[i],scale5*wcen3);
				hMatrix_cent3->Fill(jtpt5[i],refpt5[i],scale5*wcen3);
			}           
		}
		
		if(bin5< 20 && bin5 >= 12)
        {
			double wcen4=1;
     	 	wcen4 = fcen->Eval(bin5);
     	 	
			for (int i= 0; i < njets5; i++)
				
			{ if ( refpt5[i] <0. ) continue;
				if(jteta5[i] >2. || jteta5[i] <-2. ) continue;
				response_cent4.Fill(jtpt5[i],refpt5[i],scale5*wcen4);
				hMatrix_cent4->Fill(jtpt5[i],refpt5[i],scale5*wcen4);
			}           
		}
		
		if(bin5< 28 && bin5 >= 20)
        {
			double wcen5=1;
     	 	wcen5 = fcen->Eval(bin5);
     	 	
			for (int i= 0; i < njets5; i++)
				
			{ if ( refpt5[i] <0. ) continue;
				if( jteta5[i] >2. || jteta5[i] <-2. ) continue;
				response_cent5.Fill(jtpt5[i],refpt5[i],scale5*wcen5);
				hMatrix_cent5->Fill(jtpt5[i],refpt5[i],scale5*wcen5);
			}           
		}
		
		if(bin5< 36 && bin5 >= 28)
        {
			double wcen3=6;
     	 	wcen6 = fcen->Eval(bin5);
     	 	
			for (int i= 0; i < njets5; i++)
				
			{ if ( refpt5[i] <0. ) continue;
				if( jteta5[i] >2. || jteta5[i] <-2. ) continue;
				response_cent6.Fill(jtpt5[i],refpt5[i],scale5*wcen6);
				hMatrix_cent6->Fill(jtpt5[i],refpt5[i],scale5*wcen6);
			}           
		}
		
		
		
		
	}
	
	inf5->Close();

/*

//// Response Matrix Check

	TCanvas *c0 = new TCanvas("c0","");
c0->Divide(3,2,0,0);
c0->cd(1);
hMatrix_cent1->Draw("colz");
c0->cd(2);
hMatrix_cent2->Draw("colz");
c0->cd(3);
hMatrix_cent3->Draw("colz");
c0->cd(4);
hMatrix_cent4->Draw("colz");
c0->cd(5);
hMatrix_cent5->Draw("colz");
c0->cd(6);
hMatrix_cent6->Draw("colz");
*/

	pbpb_Unfo->cd();
		
	
	
	cout << "==================================== TEST =====================================" << endl;
	
	
	cout << "==================================== UNFOLD ===================================" << endl;
	
	char chmet[100]; 
	if(method==1)
	{
		RooUnfoldBayes unfold1 (&response_cent1, hMeas_cent1, 4);
		TH1F* hReco_cent1= (TH1F*) unfold1.Hreco();
		RooUnfoldBayes unfold2 (&response_cent2, hMeas_cent2, 4);
		TH1F* hReco_cent2= (TH1F*) unfold2.Hreco();
		RooUnfoldBayes unfold3 (&response_cent3, hMeas_cent3, 4);
		TH1F* hReco_cent3= (TH1F*) unfold3.Hreco();
		RooUnfoldBayes unfold4 (&response_cent4, hMeas_cent4, 4);
		TH1F* hReco_cent4= (TH1F*) unfold4.Hreco();
		RooUnfoldBayes unfold5 (&response_cent5, hMeas_cent5, 4);
		TH1F* hReco_cent5= (TH1F*) unfold5.Hreco();
		RooUnfoldBayes unfold6 (&response_cent6, hMeas_cent6, 4);
		TH1F* hReco_cent6= (TH1F*) unfold6.Hreco();


		sprintf(chmet,"Bayes unfo");
	}  // OR
	if(method==2)
	{
		RooUnfoldSvd unfold (&response_cent1, hMeas_cent1, 8);
		TH1F* hReco_cent1= (TH1F*) unfold.Hreco();
		RooUnfoldSvd unfold (&response_cent2, hMeas_cent2, 8);
		TH1F* hReco_cent2= (TH1F*) unfold.Hreco();
		RooUnfoldSvd unfold (&response_cent3, hMeas_cent3, 8);
		TH1F* hReco_cent3= (TH1F*) unfold.Hreco();
		RooUnfoldSvd unfold (&response_cent4, hMeas_cent4, 8);
		TH1F* hReco_cent4= (TH1F*) unfold.Hreco();
		RooUnfoldSvd unfold (&response_cent5, hMeas_cent5, 8);
		TH1F* hReco_cent5= (TH1F*) unfold.Hreco();
		RooUnfoldSvd unfold (&response_cent6, hMeas_cent6, 8);
		TH1F* hReco_cent6= (TH1F*) unfold.Hreco();
		
		
		sprintf(chmet,"Svd unfo ");
	} // OR
	if(method==3)
	{
		RooUnfoldBinByBin unfold (&response_cent1, hMeas_cent1);
		TH1F* hReco_cent1= (TH1F*) unfold.Hreco();
		RooUnfoldBinByBin unfold (&response_cent2, hMeas_cent2);
		TH1F* hReco_cent2= (TH1F*) unfold.Hreco();
		RooUnfoldBinByBin unfold (&response_cent3, hMeas_cent3);
		TH1F* hReco_cent3= (TH1F*) unfold.Hreco();
		RooUnfoldBinByBin unfold (&response_cent4, hMeas_cent4);
		TH1F* hReco_cent4= (TH1F*) unfold.Hreco();
		RooUnfoldBinByBin unfold (&response_cent5, hMeas_cent5);
		TH1F* hReco_cent5= (TH1F*) unfold.Hreco();
		RooUnfoldBinByBin unfold (&response_cent6, hMeas_cent6);
		TH1F* hReco_cent6= (TH1F*) unfold.Hreco();
		
		sprintf(chmet,"BinByBin unfo");
	}
	
		
	
	

   	
   	// Scale by Lumi* X section -- Nevt	
	

		
		
		TH1F* hnorm_pbpb_cent1=(TH1F*)hReco_cent1->Clone("hnorm_pbpb_cent1");
		for(int i=1; i<=hnorm_pbpb_cent1->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent1->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hReco_cent1->GetBinContent(i)/width/lumi/7.65/1000000.;
			float err_cor=sqrt(hReco_cent1->GetBinContent(i))/width/lumi/7.65/1000000.;
			hnorm_pbpb_cent1->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent1->SetBinError(i, err_cor);
			
		}
		
		TH1F* hnorm_pbpb_cent2=(TH1F*)hReco_cent2->Clone("hnorm_pbpb_cent2");
		for(int i=1; i<=hnorm_pbpb_cent2->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent2->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hReco_cent2->GetBinContent(i)/width/lumi/7.65/1000000.;
			float err_cor=sqrt(hReco_cent2->GetBinContent(i))/width/lumi/7.65/1000000.;
			hnorm_pbpb_cent2->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent2->SetBinError(i, err_cor);
			
		}
		
		TH1F* hnorm_pbpb_cent3=(TH1F*)hReco_cent3->Clone("hnorm_pbpb_cent3");
		for(int i=1; i<=hnorm_pbpb_cent3->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent3->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hReco_cent3->GetBinContent(i)/width/lumi/7.65/1000000.;
			float err_cor=sqrt(hReco_cent3->GetBinContent(i))/width/lumi/7.65/1000000.;
			hnorm_pbpb_cent3->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent3->SetBinError(i, err_cor);
			
		}
		
		TH1F* hnorm_pbpb_cent4=(TH1F*)hReco_cent4->Clone("hnorm_pbpb_cent4");
		for(int i=1; i<=hnorm_pbpb_cent4->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent4->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hReco_cent4->GetBinContent(i)/width/lumi/7.65/1000000.;
			float err_cor=sqrt(hReco_cent4->GetBinContent(i))/width/lumi/7.65/1000000.;
			hnorm_pbpb_cent4->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent4->SetBinError(i, err_cor);
			
		}
		
		TH1F* hnorm_pbpb_cent5=(TH1F*)hReco_cent5->Clone("hnorm_pbpb_cent5");
		for(int i=1; i<=hnorm_pbpb_cent5->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent5->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hReco_cent5->GetBinContent(i)/width/lumi/7.65/1000000.;
			float err_cor=sqrt(hReco_cent5->GetBinContent(i))/width/lumi/7.65/1000000.;
			hnorm_pbpb_cent5->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent5->SetBinError(i, err_cor);
			
		}
		
		TH1F* hnorm_pbpb_cent6=(TH1F*)hReco_cent6->Clone("hnorm_pbpb_cent6");
		for(int i=1; i<=hnorm_pbpb_cent6->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent6->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hReco_cent6->GetBinContent(i)/width/lumi/7.65/1000000.;
			float err_cor=sqrt(hReco_cent6->GetBinContent(i))/width/lumi/7.65/1000000.;
			hnorm_pbpb_cent6->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent6->SetBinError(i, err_cor);
			
		}
		
		
		
	


		
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
	
		
		
 pbpb_Unfo->Write();
 pbpb_Unfo->Close();
	

	
	
}

	
int GetCentBin(int ncen,int bin)
{
  int ibin=-1;
  //! centrality is defined as 2.5% bins of cross section
  //! in 0-39 bins

  if(ncen==6){
    if(bin<2)ibin=0; //! 0-5%
    else if(bin>=2 && bin<4)ibin=1;    //! 5-10%
    else if(bin>=4 && bin<12)ibin=2;   //! 10-30%
    else if(bin>=12 && bin<20)ibin=3;  //! 30-50%
    else if(bin>=20 && bin<28)ibin=4;  //! 50-70%
    else if(bin>=28 && bin<36)ibin=5;  //! 70-90%

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

