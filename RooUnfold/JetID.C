#if !defined(__CINT__) || defined(__MAKECINT__)

#include <iostream>
#include <stdio.h>

#include "TRandom.h"
#include "TH1D.h"

#include <TROOT.h>
#include <TStyle.h>
#include "TError.h"

#include "TFile.h"
#include "TCanvas.h"

#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TH2D.h"


#include "TDirectory.h"
#include "TDirectoryFile.h"

#include "TGraph.h"
#include "TColor.h"
#include "TLatex.h"
#include "TLine.h"
#include "TTree.h"
#include "TF1.h"
#include "TLegend.h"



#endif


int GetCentBin(int bin);
void drawCentTex(const int centbin);
void drawText(const char *text, float xp, float yp, int size);

void JetID(int algo,int month, int date)  ///  algo1= icpu5, 2=ak2pupf, 3=ak3pupf, 4=ak4pupf ;    input for month and date for saving plots' sake
{
	
	
	cout<<" ------------         JetID Ying Lu 06 28 12          ----------           "<<endl;
	cout<<" ==============================================================================="<<endl;
	
	
	
	//// OutPut file
	
	
	
	//  TFile *f = new TFile("pbpb_Unfo.root","RECREATE");
	
	
	const int NBINS=21;
	Double_t BOUNDARIES[NBINS] = {100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250 ,260, 270, 280, 290, 300};
	
	const int NBINS_=26;
	Double_t BOUNDARIES_[NBINS_] = {50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250 ,260, 270, 280, 290, 300};
	
	const int ncen=6;
	
	
	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();
	
	
	//! Centrality reweighting function
	TF1* fcen= new TF1("fcen","[0]*exp([1]+[2]*x+[3]*x*x+[4]*x*x*x)",0,40);
	fcen->SetParameters(2.10653e-02,5.61607,-1.41493e-01,1.00586e-03,-1.32625e-04);
	
	//! Centrality reweighting function
 	// TF1* fcen = new TF1("fcen","exp(-1.0*pow(x+1.11957e+01,2)/pow(1.34120e+01,2)/2)",0,40); 
	
	//! Primary Vertex reweighting function
	TF1 *fVz = new TF1("fVz","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x");
	fVz->SetParameters(7.62788e-01,-1.13228e-02,5.85199e-03,-3.04550e-04,4.43440e-05);
	
	
    
	// ***************** MC_histogram  *****************
	TH1F* hphotonMax[6];
	TH1F* htrackMax[6];
	TH1F* htrackSum[6];
	TH1F* hneutralMax[6];
	TH1F* hneutralSum[6];
	TH1F* hphotonSum[6];
	TH1F* hpT[6];
	TH1F* heta[6];
	TH1F* hphi[6];
	TH2F* heta_pT[6];
	TH2F* heta_phi[6];
	
	TH1F* hpthat[6];
	
	
	
	for(int icen=0;icen<ncen;icen++)
	{ hphotonMax[icen] = new TH1F (Form("hphotonMax_%d",icen), Form("photonMax%d; Max photon p_{T} / Jet p_{T}; Event Fraction",icen), 20, 0.,1. );
		htrackMax[icen]= new TH1F (Form("htrackMax_%d",icen), Form("trackMax%d; Max track p_{T} / Jet p_{T}; Event Fraction ",icen),   20, 0.,1.); 
		htrackSum[icen]= new TH1F (Form("htrackSum_%d",icen), Form("trackSum%d; Sum track p_{T} / Jet p_{T}; Event Fraction",icen),   20, 0.,1.); 
		hneutralMax[icen]= new TH1F (Form("hneutralMax_%d",icen), Form("neutralMax%d; Max neutral p_{T} / Jet p_{T};Event Fraction ",icen),  20, 0.,1.); 
		hneutralSum[icen]= new TH1F (Form("hneutralSum_%d",icen), Form("neutralSum%d; Sum neutral p_{T} / Jet p_{T}; Event Fraction ",icen),   20, 0.,1.); 
		hphotonSum[icen]= new TH1F (Form("hphotonSum_%d",icen), Form("photonSum%d; Sum photon p_{T} / Jet p_{T}; Event Fraction ",icen),   20, 0.,1.);
		hpT[icen]= new TH1F (Form("hpT_%d",icen), Form("hpT%d; Jet p_{T}; Event Fraction ",icen),   NBINS-1,BOUNDARIES);
		heta[icen]= new TH1F (Form("heta_%d",icen), Form("heta%d; Jet #eta; Event Fraction",icen), 20,-2,+2);
		hphi[icen]= new TH1F (Form("hphi_%d",icen), Form("hphi%d; Jet #phi; Event Fraction",icen), 20, -3.14,+3.14);
		heta_phi[icen]= new TH2F (Form("heta_phi_%d",icen), Form("eta_phi%d; Jet #eta; Jet #phi",icen),20,-2,+2, 20, -3.14,+3.14);
		heta_pT[icen]= new TH2F (Form("heta_pT_%d",icen), Form("eta_phi%d; Jet #eta; Jet p_{T} ",icen),20,-2,+2, 20, 90,500);
		hpthat[icen]= new TH1F (Form("hpthat_%d",icen), Form("hpthat%d; pthat; Event Fraction ",icen),   NBINS_-1,BOUNDARIES_);
	}
	
	
	// *****************Data_histogram  *****************
	
	TH1F* hphotonMax_[6];
	TH1F* htrackMax_[6];
	TH1F* htrackSum_[6];
	TH1F* hneutralMax_[6];
	TH1F* hneutralSum_[6];
	TH1F* hphotonSum_[6];
	TH1F* hpT_[6];
	TH1F* heta_[6];
	TH1F* hphi_[6];
	TH2F* heta_pT_[6];
	TH2F* heta_phi_[6];
	
	
	for(int icen=0;icen<ncen;icen++)
	{ hphotonMax_[icen] = new TH1F (Form("hphotonMaxD_%d",icen), Form("photonMax%d; Max photon p_{T}/ Jet p_{T}; Event Fraction",icen), 20, 0.,1. );
		htrackMax_[icen]= new TH1F (Form("htrackMaxD_%d",icen), Form("trackMax%d; Max track p_{T}/ Jet p_{T}; Event Fraction ",icen),   20, 0.,1.); 
		htrackSum_[icen]= new TH1F (Form("htrackSumD_%d",icen), Form("trackSum%d; Sum track p_{T} / Jet p_{T}; Event Fraction ",icen),   20, 0.,1.); 
		hneutralMax_[icen]= new TH1F (Form("hneutralMaxD_%d",icen), Form("neutralMax%d; Max neutral p_{T} / Jet p_{T};Event Fraction ",icen),  20, 0.,1.); 
		hneutralSum_[icen]= new TH1F (Form("hneutralSumD_%d",icen), Form("neutralSum%d; Sum neutral p_{T}/ Jet p_{T}; Event Fraction ",icen),   20, 0.,1.); 
		hphotonSum_[icen]= new TH1F (Form("hphotonSumD_%d",icen), Form("photonSum%d; Sum photon p_{T}/ Jet p_{T}; Event Fraction ",icen),   20, 0.,1.);
		hpT_[icen]= new TH1F (Form("hpTD_%d",icen), Form("hpT%d; Jet p_{T}; Event Fraction ",icen),   NBINS-1,BOUNDARIES);
		heta_[icen]= new TH1F (Form("hetaD_%d",icen), Form("heta%d; Jet #eta; Event Fraction ",icen), 20,-2,+2);
		hphi_[icen]= new TH1F (Form("hphiD_%d",icen), Form("hphi%d; Jet #phi; Event Fraction",icen), 20, -3.14,+3.14);
		heta_phi_[icen]= new TH2F (Form("heta_phiD_%d",icen), Form("eta_phi%d; Jet #eta; Jet #phi ",icen),20,-2,+2, 20, -3.14,+3.14);
		heta_pT_[icen]= new TH2F (Form("heta_pTD_%d",icen), Form("eta_phi%d; Jet #eta; Jet p_{T} ",icen),20,-2,+2, NBINS-1,BOUNDARIES);
	}
	
	
	
	
	// *****************  Ratio Plots *****************
	
	
	TH1F* hphotonMax_Ratio[6];
	TH1F* htrackMax_Ratio[6];
	TH1F* htrackSum_Ratio[6];
	TH1F* hneutralMax_Ratio[6];
	TH1F* hneutralSum_Ratio[6];
	TH1F* hphotonSum_Ratio[6];
	TH1F* hpT_Ratio[6];
	TH1F* heta_Ratio[6];
	TH1F* hphi_Ratio[6];
	
	
	for(int icen=0;icen<ncen;icen++)
	{   hphotonMax_Ratio[icen] = new TH1F (Form("hphotonMax_Ratio%d",icen), Form("photonMax%d; Max photon p_{T} / Jet p_{T}; Data / MC Ratio",icen), 20, 0.,1. );
		htrackMax_Ratio[icen]= new TH1F (Form("htrackMax_Ratio%d",icen), Form("trackMax%d; Max track p_{T} / Jet p_{T}; Data / MC Ratio ",icen),   20, 0.,1.); 
		htrackSum_Ratio[icen]= new TH1F (Form("htrackSum_Ratio%d",icen), Form("trackSum%d; Sum track p_{T} / Jet p_{T};  Data / MC Ratio ",icen),   20, 0.,1.); 
		hneutralMax_Ratio[icen]= new TH1F (Form("hneutralMax_Ratio%d",icen), Form("neutralMax%d; Max neutral p_{T} / Jet p_{T}; Data / MC Ratio ",icen),  20, 0.,1.); 
		hneutralSum_Ratio[icen]= new TH1F (Form("hneutralSum_Ratio%d",icen), Form("neutralSum%d; Sum neutral p_{T} / Jet p_{T};  Data / MC Ratio ",icen),   20, 0.,1.); 
		hphotonSum_Ratio[icen]= new TH1F (Form("hphotonSum_Ratio%d",icen), Form("photonSum%d; Sum photon p_{T} / Jet p_{T};  Data / MC Ratio ",icen),   20, 0.,1.);
		hpT_Ratio[icen]= new TH1F (Form("hpT_Ratio%d",icen), Form("hpT%d; Jet p_{T};  Data / MC Ration ",icen),   NBINS-1,BOUNDARIES);
		heta_Ratio[icen]= new TH1F (Form("heta_Ratio%d",icen), Form("heta%d; Jet #eta;  Data / MC Ratio ",icen), 20,-2,+2);
		hphi_Ratio[icen]= new TH1F (Form("hphi_Ratio%d",icen), Form("hphi%d; Jet #phi;  Data / MC Ratio",icen), 20, -3.14,+3.14);
		
	}
	
	
	// *****************  Read Data  *****************
	
	
	cout<<" Read Data "<<endl;
	
	TString inname0="/hadoop/store/user/belt/hiForest2/HiForest-promptskim-hihighpt-hltjet80-pt90-v3_part.root";
	TFile* inf0 = new TFile(inname0,"read");
	
	float jtpt0[1000];
	float jteta0[1000];
	float jtphi0[1000];
	float photonMax0[1000];
	float trackMax0[1000];
	float trackSum0[1000];
	float neutralMax0[1000];
	float neutralSum0[1000];
	float photonSum0[1000];
	float vz0;
	int pHBHENoiseFilter0;
	int pcollisionEventSelection0;
	int njets0;
	int bin0;
	
	TTree* tree0=0;
	
    if (algo == 4) tree0 = (TTree*)inf0->Get("akPu4PFJetAnalyzer/t");
    if (algo == 3) tree0 = (TTree*)inf0->Get("akPu3PFJetAnalyzer/t");
	if (algo == 2) tree0 = (TTree*)inf0->Get("akPu2PFJetAnalyzer/t");
	if (algo == 1) tree0 = (TTree*)inf0->Get("icPu5JetAnalyzer/t");
	TTree* t0 = (TTree*)inf0->Get("hiEvtAnalyzer/HiTree");
	TTree* t_0 = (TTree*)inf0->Get("skimanalysis/HltTree");
	
	tree0->SetBranchAddress("jtpt",jtpt0);
	tree0->SetBranchAddress("jtphi",jtphi0);
	
	tree0->SetBranchAddress("trackMax",trackMax0);
	tree0->SetBranchAddress("photonMax",photonMax0);
	tree0->SetBranchAddress("trackSum",trackSum0);
	tree0->SetBranchAddress("neutralMax",neutralMax0);
	tree0->SetBranchAddress("neutralSum",neutralSum0);
	tree0->SetBranchAddress("photonSum",photonSum0);
	
	tree0->SetBranchAddress("jteta",jteta0);
	tree0->SetBranchAddress("nref",&njets0);
    t0->SetBranchAddress("hiBin",&bin0);
    t0->SetBranchAddress("vz",&vz0);
	t_0->SetBranchAddress("pcollisionEventSelection",&pcollisionEventSelection0);
	t_0->SetBranchAddress("pHBHENoiseFilter",&pHBHENoiseFilter0);
	
	Long64_t nentries0= tree0->GetEntriesFast();
	
	
	for (Long64_t jentry0=0; jentry0<nentries0;jentry0++)
	{
		
  		t0->GetEntry(jentry0);
		tree0->GetEntry(jentry0);
		t_0->GetEntry(jentry0);
		
		
		if(pcollisionEventSelection0!=1 || pHBHENoiseFilter0!=1 ||fabs(vz0)>15 ) continue; 
		
		for (int i= 0; i < njets0; i++)
			
		{if(jtpt0[i]<100 || jteta0[i] >2. || jteta0[i] <-2.) continue;
		 
			
		if(bin0<0 || bin0>39)continue;
		int centb0=-1;
		
		  centb0=GetCentBin(bin0);
		  
		
		if (centb0 == -1) continue;
		
			htrackMax_[centb0]->Fill(trackMax0[i]/jtpt0[i]);
			htrackSum_[centb0]->Fill(trackSum0[i]/jtpt0[i]);
			hneutralMax_[centb0]->Fill(neutralMax0[i]/jtpt0[i]);
			hneutralSum_[centb0]->Fill(neutralSum0[i]/jtpt0[i]);
			hphotonSum_[centb0]->Fill(photonSum0[i]/jtpt0[i]);
			hphotonMax_[centb0]->Fill(photonMax0[i]/jtpt0[i]);
			
			
			if((trackMax0[i]/jtpt0[i])<0.01 ) continue;
			
			hpT_[centb0]->Fill(jtpt0[i]);
			hphi_[centb0]->Fill(jtphi0[i]);
			heta_[centb0]->Fill(jteta0[i]);
			heta_pT_[centb0]->Fill(jteta0[i],jtpt0[i]);
			heta_phi_[centb0]->Fill(jteta0[i],jtphi0[i]);
			
			
		}
		
	}
	
	inf0->Close();
	
	
	
	// *****************Read MC *****************//
	
	cout<<" Read Pt hat  50 - inf "<<endl;
	
	TString inname1="/hadoop/store/user/belt/hiForest2/Pythia50_HydjetDrum_mix01_HiForest2_v19.root";
	TFile* inf1 = new TFile(inname1,"read");
	
	float jtpt1[1000];
	float jteta1[1000];
	float jtphi1[1000];
	float photonMax1[1000];
	float trackMax1[1000];
	float trackSum1[1000];
	float neutralMax1[1000];
	float neutralSum1[1000];
	float photonSum1[1000];
	float vz1;
	int njets1;
	float pthat1;
	int bin1;
	int pcollisionEventSelection1;
	
	TTree* tree1=0;
	 
	if (algo == 4) tree1 = (TTree*)inf1->Get("akPu4PFJetAnalyzer/t");
    if (algo == 3) tree1 = (TTree*)inf1->Get("akPu3PFJetAnalyzer/t");
	if (algo == 2) tree1 = (TTree*)inf1->Get("akPu2PFJetAnalyzer/t");
	if (algo == 1) tree1 = (TTree*)inf1->Get("icPu5JetAnalyzer/t");
	TTree* t1 = (TTree*)inf1->Get("hiEvtAnalyzer/HiTree");
	TTree* t_1 = (TTree*)inf1->Get("skimanalysis/HltTree");
	
	tree1->SetBranchAddress("jtpt",jtpt1);
	tree1->SetBranchAddress("jtphi",jtphi1);
	
	tree1->SetBranchAddress("trackMax",trackMax1);
	tree1->SetBranchAddress("photonMax",photonMax1);
	tree1->SetBranchAddress("trackSum",trackSum1);
	tree1->SetBranchAddress("neutralMax",neutralMax1);
	tree1->SetBranchAddress("neutralSum",neutralSum1);
	tree1->SetBranchAddress("photonSum",photonSum1);
	
	tree1->SetBranchAddress("jteta",jteta1);
	tree1->SetBranchAddress("nref",&njets1);
	tree1->SetBranchAddress("pthat",&pthat1);
    t1->SetBranchAddress("hiBin",&bin1);
    t1->SetBranchAddress("vz",&vz1);
    t_1->SetBranchAddress("pcollisionEventSelection",&pcollisionEventSelection1);
	
	
	Long64_t nentries1_= tree1->GetEntries("pthat>50&& pthat<80");
	Long64_t nentries1= tree1->GetEntries();
	
	float xsection1=(1.021e-03)-(9.913e-05);
	float scale1=xsection1/nentries1_;
	
	cout<< nentries1 << endl; //117816
	
	for (Long64_t jentry1=0; jentry1<nentries1;jentry1++)
	{
		
  		t1->GetEntry(jentry1);
		tree1->GetEntry(jentry1);
		t_1->GetEntry(jentry1);
		
		if(pthat1<50 || pthat1>80. ) continue;
		if(pcollisionEventSelection1!=1 || fabs(vz1)>15  ) continue; 
		
		//! Centrality Bin Weighting Factor
		
		if(bin1<0 || bin1>36)continue;
		int centb1=-1;
		double wcen1=1;
		double weight_vz1=1;
		
		centb1=GetCentBin(bin1);
		wcen1 = fcen->Eval(bin1);
		weight_vz1 = fVz->Eval(vz1);
		
		if (centb1 == -1) continue;
		
		//!  Jet Loop
		
		for (int i= 0; i < njets1; i++)
			
		{if( jtpt1[i]<100 || jteta1[i] >2. || jteta1[i] <-2.) continue;
		
			
			htrackMax[centb1]->Fill(trackMax1[i]/jtpt1[i],scale1*wcen1*weight_vz1);
			htrackSum[centb1]->Fill(trackSum1[i]/jtpt1[i],scale1*wcen1*weight_vz1);
			hneutralMax[centb1]->Fill(neutralMax1[i]/jtpt1[i],scale1*wcen1*weight_vz1);
			hneutralSum[centb1]->Fill(neutralSum1[i]/jtpt1[i],scale1*wcen1*weight_vz1);
			hphotonSum[centb1]->Fill(photonSum1[i]/jtpt1[i],scale1*wcen1*weight_vz1);
			hphotonMax[centb1]->Fill(photonMax1[i]/jtpt1[i],scale1*wcen1*weight_vz1);
			
			
			if((trackMax1[i]/jtpt1[i])<0.01 ) continue;
			
			hpT[centb1]->Fill(jtpt1[i],scale1*wcen1*weight_vz1);
			hphi[centb1]->Fill(jtphi1[i],scale1*wcen1*weight_vz1);
			heta[centb1]->Fill(jteta1[i],scale1*wcen1*weight_vz1);
			heta_pT[centb1]->Fill(jteta1[i],jtpt1[i],scale1*wcen1*weight_vz1);
			heta_phi[centb1]->Fill(jteta1[i],jtphi1[i],scale1*wcen1*weight_vz1);
			
			
		}
		
		
			hpthat[centb1]->Fill(pthat1,scale1*wcen1*weight_vz1);
		
	}
	
	inf1->Close();
	
	
	
	cout<<" Read Pt hat  80 - inf "<<endl;
	
	
	float jtpt2[1000];
	float jtphi2[1000];
	float jteta2[1000];
	float photonMax2[1000];
	float trackMax2[1000];
    float trackSum2[1000];
    float neutralMax2[1000];
    float neutralSum2[1000];
    float photonSum2[1000];
    float vz2;
	float pthat2;
	int njets2;
	int bin2;
	int pcollisionEventSelection2;
	
	TString inname2="/data/users/yinglu/JetRAA/Pythia80_HydjetDrum_mix01_HiForest2_v20.root";
	TFile* inf2 = new TFile(inname2,"read");
	
	TTree* tree2=0;
	
	TTree* t2 = (TTree*)inf2->Get("hiEvtAnalyzer/HiTree");
	if (algo == 4) tree2 = (TTree*)inf2->Get("akPu4PFJetAnalyzer/t");
    if (algo == 3) tree2 = (TTree*)inf2->Get("akPu3PFJetAnalyzer/t");
	if (algo == 2) tree2 = (TTree*)inf2->Get("akPu2PFJetAnalyzer/t");
	if (algo == 1) tree2 = (TTree*)inf2->Get("icPu5JetAnalyzer/t");
	TTree* t_2 = (TTree*)inf2->Get("skimanalysis/HltTree");
	
	
	tree2->SetBranchAddress("jtpt",jtpt2);
	tree2->SetBranchAddress("jtphi",jtphi2);
	
	tree2->SetBranchAddress("trackMax",trackMax2);
	tree2->SetBranchAddress("photonMax",photonMax2);
	tree2->SetBranchAddress("trackSum",trackSum2);
	tree2->SetBranchAddress("neutralMax",neutralMax2);
	tree2->SetBranchAddress("neutralSum",neutralSum2);
	tree2->SetBranchAddress("photonSum",photonSum2);
	
	tree2->SetBranchAddress("nref",&njets2);
	tree2->SetBranchAddress("jteta",&jteta2);
	tree2->SetBranchAddress("pthat",&pthat2);
	t2->SetBranchAddress("hiBin",&bin2);
	t2->SetBranchAddress("vz",&vz2);
	t_2->SetBranchAddress("pcollisionEventSelection",&pcollisionEventSelection2);
	
	Long64_t nentries2_ = tree2 ->GetEntries("pthat>80 && pthat<120");
	Long64_t nentries2 = tree2 ->GetEntries();
	
	float xsection2=(9.913e-05)-(1.128e-05);
	float scale2=xsection2/nentries2_;
	
	std::cout<<nentries2<<endl; //78549
	
	for (Long64_t jentry2=0; jentry2<nentries2;jentry2++)
	{
		
  		t2->GetEntry(jentry2);
		tree2->GetEntry(jentry2);
		t_2->GetEntry(jentry2);
		
		if(pthat2<80 || pthat2>120. ) continue;
		if(pcollisionEventSelection2!=1|| fabs(vz2)>15  ) continue; 
		
		//! Centrality Bin Weighting Factor
		
		if(bin2<0 || bin2>36)continue;
		int centb2=-1;
		double wcen2=1;
		double weight_vz2=1;
		
		centb2=GetCentBin(bin2);
		wcen2 = fcen->Eval(bin2);
		weight_vz2 = fVz->Eval(vz2);
		
		if (centb2 == -1) continue;
		
		//!  Jet Loop
		
		for (int i= 0; i < njets2; i++)
			
		{if(jtpt2[i]<100 || jteta2[i] >2. || jteta2[i] <-2. ) continue;
		
			
			htrackMax[centb2]->Fill(trackMax2[i]/jtpt2[i],scale2*wcen2*weight_vz2);
			htrackSum[centb2]->Fill(trackSum2[i]/jtpt2[i],scale2*wcen2*weight_vz2);
			hneutralMax[centb2]->Fill(neutralMax2[i]/jtpt2[i],scale2*wcen2*weight_vz2);
			hneutralSum[centb2]->Fill(neutralSum2[i]/jtpt2[i],scale2*wcen2*weight_vz2);
			hphotonSum[centb2]->Fill(photonSum2[i]/jtpt2[i],scale2*wcen2*weight_vz2);
			hphotonMax[centb2]->Fill(photonMax2[i]/jtpt2[i],scale2*wcen2*weight_vz2);
			
			
			if((trackMax2[i]/jtpt2[i])<0.01 ) continue;
			
			hpT[centb2]->Fill(jtpt2[i],scale2*wcen2*weight_vz2);
			hphi[centb2]->Fill(jtphi2[i],scale2*wcen2*weight_vz2);
			heta[centb2]->Fill(jteta2[i],scale2*wcen2*weight_vz2);
			heta_pT[centb2]->Fill(jteta2[i],jtpt2[i],scale2*wcen2*weight_vz2);
			heta_phi[centb2]->Fill(jteta2[i],jtphi2[i],scale2*wcen2*weight_vz2);
			
		}
		
		hpthat[centb2]->Fill(pthat2,scale2*wcen2*weight_vz2);
		
	}
	
	inf2->Close();
	
	
	
	
	cout<<" Read Pt hat  120 - inf "<<endl;
	
	float jtpt3[1000];
	float jtphi3[1000];
	float photonMax3[1000];
	float trackMax3[1000];
    float trackSum3[1000];
    float neutralMax3[1000];
    float neutralSum3[1000];
    float photonSum3[1000];
    float jteta3[1000];
    float vz3;
	float pthat3;
	int njets3;
	int bin3;
	int pcollisionEventSelection3;
	
	TString inname3="/data/users/yinglu/JetRAA/Pythia120_HydjetDrum_mix01_HiForest2_v19_0.root";
	TFile* inf3 = new TFile(inname3,"read");
	
	TTree* tree3 =0;
	
	TTree* t3 = (TTree*)inf3->Get("hiEvtAnalyzer/HiTree");
	if (algo == 4)  tree3 = (TTree*)inf3->Get("akPu4PFJetAnalyzer/t");
    if (algo == 3)  tree3 = (TTree*)inf3->Get("akPu3PFJetAnalyzer/t");
	if (algo == 2)  tree3 = (TTree*)inf3->Get("akPu2PFJetAnalyzer/t");
	if (algo == 1)  tree3 = (TTree*)inf3->Get("icPu5JetAnalyzer/t");
	TTree* t_3 = (TTree*)inf3->Get("skimanalysis/HltTree");
	
	
	tree3->SetBranchAddress("jtpt",jtpt3);
	tree3->SetBranchAddress("jtphi",jtphi3);
	
	tree3->SetBranchAddress("trackMax",trackMax3);
	tree3->SetBranchAddress("photonMax",photonMax3);
	tree3->SetBranchAddress("trackSum",trackSum3);
	tree3->SetBranchAddress("neutralMax",neutralMax3);
	tree3->SetBranchAddress("neutralSum",neutralSum3);
	tree3->SetBranchAddress("photonSum",photonSum3);	
	
	tree3->SetBranchAddress("nref",&njets3);
	tree3->SetBranchAddress("jteta",&jteta3);
	tree3->SetBranchAddress("pthat",&pthat3);
	t3->SetBranchAddress("hiBin",&bin3);
	t3->SetBranchAddress("vz",&vz3);
	t_3->SetBranchAddress("pcollisionEventSelection",&pcollisionEventSelection3);
	
	
	Long64_t nentries3_ = tree3 ->GetEntries("pthat>120 && pthat<170");
	Long64_t nentries3 = tree3 ->GetEntries();
	
	float xsection3=(1.128e-05)-(1.47e-06);
	float scale3=xsection3/nentries3_;
	
	std::cout<<nentries3<<endl; //19629
	
	for (Long64_t jentry3=0; jentry3<nentries3;jentry3++)
	{
		
  		t3->GetEntry(jentry3);
		tree3->GetEntry(jentry3);
		t_3->GetEntry(jentry3);
		
		if(pthat3<120 || pthat3>170.) continue;
		if(pcollisionEventSelection3!=1 || fabs(vz3)>15  ) continue;
		
		//! Centrality Bin Weighting Factor
		
		if(bin3<0 || bin3>36)continue;
		int centb3=-1;
		double wcen3=1;
		double weight_vz3=1;
		
		centb3=GetCentBin(bin3);
		wcen3 = fcen->Eval(bin3);
		weight_vz3 = fVz->Eval(vz3);
		
		if (centb3 == -1) continue;
		
		//! Jet loop
		
		for (int i= 0; i < njets3; i++)
			
		{if( jtpt3[i]<100 || jteta3[i] >2. || jteta3[i] <-2. ) continue;
	
			
			
			htrackMax[centb3]->Fill(trackMax3[i]/jtpt3[i],scale3*wcen3*weight_vz3);
			htrackSum[centb3]->Fill(trackSum3[i]/jtpt3[i],scale3*wcen3*weight_vz3);
			hneutralMax[centb3]->Fill(neutralMax3[i]/jtpt3[i],scale3*wcen3*weight_vz3);
			hneutralSum[centb3]->Fill(neutralSum3[i]/jtpt3[i],scale3*wcen3*weight_vz3);
			hphotonSum[centb3]->Fill(photonSum3[i]/jtpt3[i],scale3*wcen3*weight_vz3);
			hphotonMax[centb3]->Fill(photonMax3[i]/jtpt3[i],scale3*wcen3*weight_vz3);
			
			if((trackMax3[i]/jtpt3[i])<0.01 ) continue;
			
			hpT[centb3]->Fill(jtpt3[i],scale3*wcen3*weight_vz3);
			hphi[centb3]->Fill(jtphi3[i],scale3*wcen3*weight_vz3);
			heta[centb3]->Fill(jteta3[i],scale3*wcen3*weight_vz3);
			heta_pT[centb3]->Fill(jteta3[i],jtpt3[i],scale3*wcen3*weight_vz3);
			heta_phi[centb3]->Fill(jteta3[i],jtphi3[i],scale3*wcen3*weight_vz3);
			
			
		}
		
		
		hpthat[centb3]->Fill(pthat3,scale3*wcen3*weight_vz3);
	}
	
	
	inf3->Close();
	
	
	
	cout<<" Read Pt hat  170 - inf "<<endl;
	
	
	float jtpt4[1000];
	float jteta4[1000];
	float jtphi4[1000];
	float photonMax4[1000];
 	float trackMax4[1000];
    float trackSum4[1000];
    float neutralMax4[1000];
    float neutralSum4[1000];
    float photonSum4[1000];
    float vz4;
	float pthat4;
	int njets4;
	int bin4;
	int pcollisionEventSelection4;
	
	
	
	TString inname4="/data/users/yinglu/JetRAA/Pythia170_HydjetDrum_mix01_HiForest2_v19.root";
	TFile* inf4 = new TFile(inname4,"read");
	
	
	TTree* tree4=0;
	 
	TTree* t4 = (TTree*)inf4->Get("hiEvtAnalyzer/HiTree");
	if (algo == 4) tree4 = (TTree*)inf4->Get("akPu4PFJetAnalyzer/t");
    if (algo == 3) tree4 = (TTree*)inf4->Get("akPu3PFJetAnalyzer/t");
	if (algo == 2) tree4 = (TTree*)inf4->Get("akPu2PFJetAnalyzer/t");
	if (algo == 1) tree4 = (TTree*)inf4->Get("icPu5JetAnalyzer/t");
	TTree* t_4 = (TTree*)inf4->Get("skimanalysis/HltTree");
	
	
	tree4->SetBranchAddress("jtpt",jtpt4);
	tree4->SetBranchAddress("jtphi",jtphi4);
	
	tree4->SetBranchAddress("trackMax",trackMax4);
	tree4->SetBranchAddress("photonMax",photonMax4);
	tree4->SetBranchAddress("trackSum",trackSum4);
	tree4->SetBranchAddress("neutralMax",neutralMax4);
	tree4->SetBranchAddress("neutralSum",neutralSum4);
	tree4->SetBranchAddress("photonSum",photonSum4);
	
	tree4->SetBranchAddress("nref",&njets4);
	tree4->SetBranchAddress("jteta",&jteta4);
	tree4->SetBranchAddress("pthat",&pthat4);
	t4->SetBranchAddress("hiBin",&bin4);
	t4->SetBranchAddress("vz",&vz4);
	t_4->SetBranchAddress("pcollisionEventSelection",&pcollisionEventSelection4);
	
	
	
	Long64_t nentries4_ = tree4 ->GetEntries("pthat>170 && pthat<200");
	Long64_t nentries4 = tree4 ->GetEntries();
	//Long64_t nentries4 = tree4 ->GetEntries("pthat<250");
	
	float xsection4=(1.47e-06)-(5.310e-07);
	//float xsection4=(1.47e-06)-(1.192e-7);
	float scale4=xsection4/nentries4_;
	
	std::cout<<nentries4<<endl; //67585
	
	for (Long64_t jentry4=0; jentry4<nentries4;jentry4++)
	{
		
  		t4->GetEntry(jentry4);
		tree4->GetEntry(jentry4);
		t_4->GetEntry(jentry4);
		
		if(pthat4<170 || pthat4>200.) continue;
		
		//if(pthat4>250.) continue;
		
		if(pcollisionEventSelection4!=1 || fabs(vz4)>15 ) continue;
		
		//! Centrality Bin Weighting Factor
		
		if(bin4<0 || bin4>36)continue;
		int centb4=-1;
		double wcen4=1;
		double weight_vz4=1;
		
		centb4=GetCentBin(bin4);
		wcen4 = fcen->Eval(bin4);
		weight_vz4 = fVz->Eval(vz4);
		
		if (centb4 == -1) continue;
		
		
		//! Jet Loop
		
		for (int i= 0; i < njets4; i++)
			
		{if(jtpt4[i]<100 || jteta4[i] >2. || jteta4[i] <-2.) continue;
		
			
			htrackMax[centb4]->Fill(trackMax4[i]/jtpt4[i],scale4*wcen4*weight_vz4);
			htrackSum[centb4]->Fill(trackSum4[i]/jtpt4[i],scale4*wcen4*weight_vz4);
			hneutralMax[centb4]->Fill(neutralMax4[i]/jtpt4[i],scale4*wcen4*weight_vz4);
			hneutralSum[centb4]->Fill(neutralSum4[i]/jtpt4[i],scale4*wcen4*weight_vz4);
			hphotonSum[centb4]->Fill(photonSum4[i]/jtpt4[i],scale4*wcen4*weight_vz4);
			hphotonMax[centb4]->Fill(photonMax4[i]/jtpt4[i],scale4*wcen4*weight_vz4);
			
			
			if((trackMax4[i]/jtpt4[i])<0.01 ) continue;
			
			hpT[centb4]->Fill(jtpt4[i],scale4*wcen4*weight_vz4);
			hphi[centb4]->Fill(jtphi4[i],scale4*wcen4*weight_vz4);
			heta[centb4]->Fill(jteta4[i],scale4*wcen4*weight_vz4);
			heta_pT[centb4]->Fill(jteta4[i],jtpt4[i],scale4*wcen4*weight_vz4);
			heta_phi[centb4]->Fill(jteta4[i],jtphi4[i],scale4*wcen4*weight_vz4);
			
		}
		
		hpthat[centb4]->Fill(pthat4,scale4*wcen4*weight_vz4);
		
		
	}
	
	inf4->Close();
	
	
	
	cout<<" Read Pt hat  200 - inf "<<endl;
	
	
	
	float jtpt5[1000];
	float jteta5[1000];
	float jtphi5[1000];
	float photonMax5[1000];
	float trackMax5[1000];
    float trackSum5[1000];
    float neutralMax5[1000];
    float neutralSum5[1000];
    float photonSum5[1000];
    float vz5;
	float pthat5;
	int njets5;
	int bin5;
	int pcollisionEventSelection5;
	
	
	TString inname5="/data/users/yinglu/JetRAA/Pythia200_HydjetDrum_mix01_HiForest2_v19.root";
	TFile* inf5 = new TFile(inname5,"read");
	
	
	TTree* tree5 =0;
	 
	TTree* t5 = (TTree*)inf5->Get("hiEvtAnalyzer/HiTree");
	if (algo == 4)  tree5 = (TTree*)inf5->Get("akPu4PFJetAnalyzer/t");
    if (algo == 3)  tree5 = (TTree*)inf5->Get("akPu3PFJetAnalyzer/t");
	if (algo == 2)  tree5 = (TTree*)inf5->Get("akPu2PFJetAnalyzer/t");
	if (algo == 1)  tree5 = (TTree*)inf5->Get("icPu5JetAnalyzer/t");
	TTree* t_5 = (TTree*)inf5->Get("skimanalysis/HltTree");
	
	
	tree5->SetBranchAddress("jtpt",jtpt5);
	tree5->SetBranchAddress("jtphi",jtphi5);
	
	tree5->SetBranchAddress("trackMax",trackMax5);
	tree5->SetBranchAddress("photonMax",photonMax5);
	tree5->SetBranchAddress("trackSum",trackSum5);
	tree5->SetBranchAddress("neutralMax",neutralMax5);
	tree5->SetBranchAddress("neutralSum",neutralSum5);
	tree5->SetBranchAddress("photonSum",photonSum5);
	
	tree5->SetBranchAddress("nref",&njets5);
	tree5->SetBranchAddress("jteta",&jteta5);
	tree5->SetBranchAddress("pthat",&pthat5);
	t5->SetBranchAddress("hiBin",&bin5);
	t5->SetBranchAddress("vz",&vz5);
	t_5->SetBranchAddress("pcollisionEventSelection",&pcollisionEventSelection5);
	
	Long64_t nentries5_ = tree5 ->GetEntries("pthat>200 && pthat<250");
	Long64_t nentries5 = tree5 ->GetEntries();
	//Long64_t nentries5 = tree5 ->GetEntries("");
	
	//float xsection5=5.310e-07;
	float xsection5=(5.310e-07)-(1.192e-7);
	float scale5=xsection5/nentries5_;
	
	std::cout<<nentries5<<endl; //23400
	
	for (Long64_t jentry5=0; jentry5<nentries5;jentry5++)
	{
		
  		t5->GetEntry(jentry5);
		tree5->GetEntry(jentry5);
		t_5->GetEntry(jentry5);
				
				
		if(pthat5<200 || pthat5>250.) continue;
		if(pcollisionEventSelection5!=1|| fabs(vz5)>15 ) continue;
		
		
		//! Centrality Bin Weighting Factor
		
		if(bin5<0 || bin5>36)continue;
		int centb5=-1;
		double wcen5=1;
		double weight_vz5=1;
		
		centb5=GetCentBin(bin5);
		wcen5 = fcen->Eval(bin5);
		weight_vz5 = fVz->Eval(vz5);
		
		if (centb5 == -1) continue;
		
		//!  Jet Loop
		
		
		for (int i= 0; i < njets5; i++)
			
		{if( jtpt5[i]<100 || jteta5[i] >2. || jteta5[i] <-2. ) continue;
		
			
			htrackMax[centb5]->Fill(trackMax5[i]/jtpt5[i],scale5*wcen5*weight_vz5);
			htrackSum[centb5]->Fill(trackSum5[i]/jtpt5[i],scale5*wcen5*weight_vz5);
			hneutralMax[centb5]->Fill(neutralMax5[i]/jtpt5[i],scale5*wcen5*weight_vz5);
			hneutralSum[centb5]->Fill(neutralSum5[i]/jtpt5[i],scale5*wcen5*weight_vz5);
			hphotonSum[centb5]->Fill(photonSum5[i]/jtpt5[i],scale5*wcen5*weight_vz5);
			hphotonMax[centb5]->Fill(photonMax5[i]/jtpt5[i],scale5*wcen5*weight_vz5);
			
			if((trackMax5[i]/jtpt5[i])<0.01 ) continue;
			
			hpT[centb5]->Fill(jtpt5[i],scale5*wcen5*weight_vz5);
			hphi[centb5]->Fill(jtphi5[i],scale5*wcen5*weight_vz5);
			heta[centb5]->Fill(jteta5[i],scale5*wcen5*weight_vz5);
			heta_pT[centb5]->Fill(jteta5[i],jtpt5[i],scale5*wcen5*weight_vz5);
			heta_phi[centb5]->Fill(jteta5[i],jtphi5[i],scale5*wcen5*weight_vz5);
			
		}
		
		hpthat[centb5]->Fill(pthat5,scale5*wcen5*weight_vz5);
		
	}
	
	inf5->Close();
	
	
	cout<<" Read Pt hat  250 - inf "<<endl;
	
	
	float jtpt6[1000];
	float jteta6[1000];
	float jtphi6[1000];
	float photonMax6[1000];
	float trackMax6[1000];
    float trackSum6[1000];
    float neutralMax6[1000];
    float neutralSum6[1000];
    float photonSum6[1000];
    float vz6;
	float pthat6;
	int njets6;
	int bin6;
	int pcollisionEventSelection6;
	
	
	
	TString inname6="/hadoop/store/user/belt/hiForest2/Pythia250_HydjetDrum_mix01_HiForest2_v21_ivan.root";
	TFile* inf6 = new TFile(inname6,"read");
	
	TTree* tree6=0;
	
	TTree* t6 = (TTree*)inf6->Get("hiEvtAnalyzer/HiTree");
	if (algo == 4) tree6 = (TTree*)inf6->Get("akPu4PFJetAnalyzer/t");
    if (algo == 3) tree6 = (TTree*)inf6->Get("akPu3PFJetAnalyzer/t");
	if (algo == 2) tree6 = (TTree*)inf6->Get("akPu2PFJetAnalyzer/t");
	if (algo == 1) tree6 = (TTree*)inf6->Get("icPu5JetAnalyzer/t");
	TTree* t_6 = (TTree*)inf6->Get("skimanalysis/HltTree");
	
	
	tree6->SetBranchAddress("jtpt",jtpt6);
	tree6->SetBranchAddress("jtphi",jtphi6);
	
	tree6->SetBranchAddress("trackMax",trackMax6);
	tree6->SetBranchAddress("photonMax",photonMax6);
	tree6->SetBranchAddress("trackSum",trackSum6);
	tree6->SetBranchAddress("neutralMax",neutralMax6);
	tree6->SetBranchAddress("neutralSum",neutralSum6);
	tree6->SetBranchAddress("photonSum",photonSum6);
	
	tree6->SetBranchAddress("nref",&njets6);
	tree6->SetBranchAddress("jteta",&jteta6);
	tree6->SetBranchAddress("pthat",&pthat6);
	t6->SetBranchAddress("hiBin",&bin6);
	t6->SetBranchAddress("vz",&vz6);
	t_6->SetBranchAddress("pcollisionEventSelection",&pcollisionEventSelection6);
	
	
	Long64_t nentries6_ = tree6 ->GetEntries("pthat>250. && pthat<1000.");
	Long64_t nentries6 = tree6 ->GetEntries();
	
	float xsection6=1.192e-7;
	float scale6=xsection6/nentries6_;
	
	std::cout<<nentries6<<endl; 
	
	for (Long64_t jentry6=0; jentry6<nentries6;jentry6++)
	{
		
  		t6->GetEntry(jentry6);
		tree6->GetEntry(jentry6);
		t_6->GetEntry(jentry6);
		
		if(pthat6<250. || pthat6>1000.) continue;
				
		if(pcollisionEventSelection6!=1 || fabs(vz6)>15 ) continue;
		
		
		//! Centrality Bin Weighting Factor
		
		if(bin6<0 || bin6>36)continue;
		int centb6=-1;
		double wcen6=1;
		double weight_vz6=1;
		
		centb6=GetCentBin(bin6);
		wcen6 = fcen->Eval(bin6);
		weight_vz6 = fVz->Eval(vz6);
		
		if (centb6 == -1) continue;
		
		//!  Jet Loop
		
		
		for (int i= 0; i < njets6; i++)
			
		{if( jtpt6[i]<100 || jteta6[i] >2. || jteta6[i] <-2.) continue;
		
			
			htrackMax[centb6]->Fill(trackMax6[i]/jtpt6[i],scale6*wcen6*weight_vz6);
			htrackSum[centb6]->Fill(trackSum6[i]/jtpt6[i],scale6*wcen6*weight_vz6);
			hneutralMax[centb6]->Fill(neutralMax6[i]/jtpt6[i],scale6*wcen6*weight_vz6);
			hneutralSum[centb6]->Fill(neutralSum6[i]/jtpt6[i],scale6*wcen6*weight_vz6);
			hphotonSum[centb6]->Fill(photonSum6[i]/jtpt6[i],scale6*wcen6*weight_vz6);
			hphotonMax[centb6]->Fill(photonMax6[i]/jtpt6[i],scale6*wcen6*weight_vz6);
			
			if((trackMax6[i]/jtpt6[i])<0.01 ) continue;
			
			hpT[centb6]->Fill(jtpt6[i],scale6*wcen6*weight_vz6);
			hphi[centb6]->Fill(jtphi6[i],scale6*wcen6*weight_vz6);
			heta[centb6]->Fill(jteta6[i],scale6*wcen6*weight_vz6);
			heta_pT[centb6]->Fill(jteta6[i],jtpt6[i],scale6*wcen6*weight_vz6);
			heta_phi[centb6]->Fill(jteta6[i],jtphi6[i],scale6*wcen6*weight_vz6);
			
		}
		
		hpthat[centb6]->Fill(pthat6,scale6*wcen6*weight_vz6);
		
	}
	
	inf6->Close();
	
	
	
	
	
	
	
	
	//********************     Normalization    ****************************************//
	
	
	for(int icen=0;icen<ncen;icen++)
		
	{
	htrackMax[icen]->Scale(1/htrackMax[icen]->Integral());
	htrackSum[icen]->Scale(1/htrackSum[icen]->Integral());
	hneutralMax[icen]->Scale(1/hneutralMax[icen]->Integral());
	hneutralSum[icen]->Scale(1/hneutralSum[icen]->Integral());
	hphotonMax[icen]->Scale(1/hphotonMax[icen]->Integral());
	hphotonSum[icen]->Scale(1/hphotonSum[icen]->Integral());
	
	
	hpT[icen]->Scale(1/hpT[icen]->Integral());
	hphi[icen]->Scale(1/hphi[icen]->Integral());
	heta[icen]->Scale(1/heta[icen]->Integral());
	//heta_pT[icen]->Scale(1/heta_pT[icen]->Integral());
	//heta_phi[icen]->Scale(1/heta_phi[icen]->Integral());
	
	
	htrackMax_[icen]->Scale(1/htrackMax_[icen]->Integral());
	htrackSum_[icen]->Scale(1/htrackSum_[icen]->Integral());
	hneutralMax_[icen]->Scale(1/hneutralMax_[icen]->Integral());
	hneutralSum_[icen]->Scale(1/hneutralSum_[icen]->Integral());
	hphotonMax_[icen]->Scale(1/hphotonMax_[icen]->Integral());
	hphotonSum_[icen]->Scale(1/hphotonSum_[icen]->Integral());
	
	
	hpT_[icen]->Scale(1/hpT_[icen]->Integral());
	hphi_[icen]->Scale(1/hphi_[icen]->Integral());
	heta_[icen]->Scale(1/heta_[icen]->Integral());
	//heta_pT_[icen]->Scale(1/heta_pT_[icen]->Integral());
	//heta_phi_[icen]->Scale(1/heta_phi_[icen]->Integral());
	}
	
	
	
	//********************    Ratio Plots   ****************************************//
	for(int icen=0;icen<ncen;icen++)
	
	{
	
	hphotonMax_Ratio[icen]->Divide(hphotonMax_[icen],hphotonMax[icen]);
    htrackMax_Ratio[icen]->Divide(htrackMax_[icen], htrackMax[icen]);
    htrackSum_Ratio[icen]->Divide(htrackSum_[icen],htrackSum[icen]);
	hneutralMax_Ratio[icen]->Divide(hneutralMax_[icen],hneutralMax[icen]);
	hneutralSum_Ratio[icen]->Divide(hneutralSum_[icen],hneutralSum[icen]);
	hphotonSum_Ratio[icen]->Divide(hphotonSum_[icen],hphotonSum[icen]);
	hpT_Ratio[icen]->Divide(hpT_[icen],hpT[icen]);
	heta_Ratio[icen]->Divide(heta_[icen],heta[icen]);
	hphi_Ratio[icen]->Divide(hphi_[icen],hphi[icen]);
	
	
	
	}
	
	
	for(int icen=0;icen<ncen;icen++)
	
	{
	
	hphotonMax_Ratio[icen]->SetAxisRange(0.1,10,"Y");
    htrackMax_Ratio[icen]->SetAxisRange(0.1,10,"Y");
    htrackSum_Ratio[icen]->SetAxisRange(0.1,10,"Y");
	hneutralMax_Ratio[icen]->SetAxisRange(0.1,10,"Y");
	hneutralSum_Ratio[icen]->SetAxisRange(0.1,10,"Y");
	hphotonSum_Ratio[icen]->SetAxisRange(0.1,10,"Y");
	hpT_Ratio[icen]->SetAxisRange(0.1,10,"Y");
	heta_Ratio[icen]->SetAxisRange(0.1,10,"Y");
	hphi_Ratio[icen]->SetAxisRange(0.1,10,"Y");
	

	

	
	hpT[icen]->SetAxisRange(0.0001,1.,"Y");
	heta[icen]->SetAxisRange(0.01,0.1,"Y");
	hphi[icen]->SetAxisRange(0.01,0.1,"Y");
	

	
	}
	
	//********************    Plots   ****************************************//
	
	
gStyle->SetHistFillStyle(3004);
gStyle->SetHistFillColor(30);
gStyle->SetHistLineColor(30);


TCanvas *c1 = new TCanvas("c1","c1",900,600);
c1->Divide(3,2,0,0);

c1->cd(1);
gPad->SetLogy();

hphotonMax[0]->UseCurrentStyle();
hphotonMax[0]->Draw("l hist");
hphotonMax_[0]->Draw("esame");
drawCentTex(0);

TLegend *tleg = new TLegend(0.35, 0.08, 0.80, 0.35);
tleg->SetBorderSize(0);
tleg->SetFillStyle(0);
tleg->SetTextFont(42);
tleg->SetTextSize(0.06);
tleg->AddEntry(hphotonMax[0]," MC ","f");
tleg->AddEntry(hphotonMax_[0]," Data ","pl");
tleg->Draw();

c1->cd(2);
gPad->SetLogy();

hphotonMax[1]->UseCurrentStyle();
hphotonMax[1]->Draw("l hist");
hphotonMax_[1]->Draw("esame");
drawCentTex(1);

c1->cd(3);
gPad->SetLogy();

hphotonMax[2]->UseCurrentStyle();
hphotonMax[2]->Draw("l hist");
hphotonMax_[2]->Draw("esame");
drawCentTex(2);

c1->cd(4);
gPad->SetLogy();

hphotonMax[3]->UseCurrentStyle();
hphotonMax[3]->Draw("l hist");
hphotonMax_[3]->Draw("esame");
drawCentTex(3);

c1->cd(5);
gPad->SetLogy();

hphotonMax[4]->UseCurrentStyle();
hphotonMax[4]->Draw("l hist");
hphotonMax_[4]->Draw("esame");
drawCentTex(4);

c1->cd(6);
gPad->SetLogy();

hphotonMax[5]->UseCurrentStyle();
hphotonMax[5]->Draw("l hist");
hphotonMax_[5]->Draw("esame");
drawCentTex(5);


c1->SaveAs(Form("JetID_photonMax_ak%dPuPF_%d_%d.pdf",algo,month,date));


TCanvas *c2 = new TCanvas("c2","c2",900,600);
c2->Divide(3,2,0,0);

c2->cd(1);
gPad->SetLogy();


htrackSum[0]->UseCurrentStyle();
htrackSum[0]->Draw("l hist");
htrackSum_[0]->Draw("esame");
drawCentTex(0);

tleg->Draw();

c2->cd(2);
gPad->SetLogy();

htrackSum[1]->UseCurrentStyle();
htrackSum[1]->Draw("l hist");
htrackSum_[1]->Draw("esame");
drawCentTex(1);

c2->cd(3);
gPad->SetLogy();

htrackSum[2]->UseCurrentStyle();
htrackSum[2]->Draw("l hist");
htrackSum_[2]->Draw("esame");
drawCentTex(2);

c2->cd(4);
gPad->SetLogy();

htrackSum[3]->UseCurrentStyle();
htrackSum[3]->Draw("l hist");
htrackSum_[3]->Draw("esame");
drawCentTex(3);

c2->cd(5);
gPad->SetLogy();

htrackSum[4]->UseCurrentStyle();
htrackSum[4]->Draw("l hist");
htrackSum_[4]->Draw("esame");
drawCentTex(4);

c2->cd(6);
gPad->SetLogy();

htrackSum[5]->UseCurrentStyle();
htrackSum[5]->Draw("l hist");
htrackSum_[5]->Draw("esame");
drawCentTex(5);

c2->SaveAs(Form("JetID_trackSum_ak%dPuPF_%d_%d.pdf",algo,month,date));

TCanvas *c3 = new TCanvas("c3","c3",900,600);
c3->Divide(3,2,0,0);

c3->cd(1);
gPad->SetLogy();

hneutralMax[0]->UseCurrentStyle();
hneutralMax[0]->Draw("l hist");
hneutralMax_[0]->Draw("esame");
drawCentTex(0);

tleg->Draw();

c3->cd(2);
gPad->SetLogy();

hneutralMax[1]->UseCurrentStyle();
hneutralMax[1]->Draw("l hist");
hneutralMax_[1]->Draw("esame");
drawCentTex(1);

c3->cd(3);
gPad->SetLogy();

hneutralMax[2]->UseCurrentStyle();
hneutralMax[2]->Draw("l hist");
hneutralMax_[2]->Draw("esame");
drawCentTex(2);

c3->cd(4);
gPad->SetLogy();

hneutralMax[3]->UseCurrentStyle();
hneutralMax[3]->Draw("l hist");
hneutralMax_[3]->Draw("esame");
drawCentTex(3);

c3->cd(5);
gPad->SetLogy();

hneutralMax[4]->UseCurrentStyle();
hneutralMax[4]->Draw("l hist");
hneutralMax_[4]->Draw("esame");
drawCentTex(4);

c3->cd(6);
gPad->SetLogy();

hneutralMax[5]->UseCurrentStyle();
hneutralMax[5]->Draw("l hist");
hneutralMax_[5]->Draw("esame");
drawCentTex(5);

c3->SaveAs(Form("JetID_neutralMax_ak%dPuPF_%d_%d.pdf",algo,month,date));


TCanvas *c4 = new TCanvas("c4","c4",900,600);
c4->Divide(3,2,0,0);

c4->cd(1);
gPad->SetLogy();

hneutralSum[0]->UseCurrentStyle();
hneutralSum[0]->Draw("l hist");
hneutralSum_[0]->Draw("esame");
drawCentTex(0);

tleg->Draw();

c4->cd(2);
gPad->SetLogy();

hneutralSum[1]->UseCurrentStyle();
hneutralSum[1]->Draw("l hist");
hneutralSum_[1]->Draw("esame");
drawCentTex(1);

c4->cd(3);
gPad->SetLogy();

hneutralSum[2]->UseCurrentStyle();
hneutralSum[2]->Draw("l hist");
hneutralSum_[2]->Draw("esame");
drawCentTex(2);

c4->cd(4);
gPad->SetLogy();

hneutralSum[3]->UseCurrentStyle();
hneutralSum[3]->Draw("l hist");
hneutralSum_[3]->Draw("esame");
drawCentTex(3);

c4->cd(5);
gPad->SetLogy();

hneutralSum[4]->UseCurrentStyle();
hneutralSum[4]->Draw("l hist");
hneutralSum_[4]->Draw("esame");
drawCentTex(4);

c4->cd(6);
gPad->SetLogy();

hneutralSum[5]->UseCurrentStyle();
hneutralSum[5]->Draw("l hist");
hneutralSum_[5]->Draw("esame");
drawCentTex(5);

c4->SaveAs(Form("JetID_neutralSum_ak%dPuPF_%d_%d.pdf",algo,month,date));

TCanvas *c5 = new TCanvas("c5","c5",900,600);
c5->Divide(3,2,0,0);


c5->cd(1);
gPad->SetLogy();

hphotonSum[0]->UseCurrentStyle();
hphotonSum[0]->Draw("l hist");
hphotonSum_[0]->Draw("esame");
drawCentTex(0);

tleg->Draw();

c5->cd(2);
gPad->SetLogy();

hphotonSum[1]->UseCurrentStyle();
hphotonSum[1]->Draw("l hist");
hphotonSum_[1]->Draw("esame");
drawCentTex(1);

c5->cd(3);
gPad->SetLogy();

hphotonSum[2]->UseCurrentStyle();
hphotonSum[2]->Draw("l hist");
hphotonSum_[2]->Draw("esame");
drawCentTex(2);

c5->cd(4);
gPad->SetLogy();

hphotonSum[3]->UseCurrentStyle();
hphotonSum[3]->Draw("l hist");
hphotonSum_[3]->Draw("esame");
drawCentTex(3);

c5->cd(5);
gPad->SetLogy();

hphotonSum[4]->UseCurrentStyle();
hphotonSum[4]->Draw("l hist");
hphotonSum_[4]->Draw("esame");
drawCentTex(4);

c5->cd(6);
gPad->SetLogy();

hphotonSum[5]->UseCurrentStyle();
hphotonSum[5]->Draw("l hist");
hphotonSum_[5]->Draw("esame");
drawCentTex(5);

c5->SaveAs(Form("JetID_photonSum_ak%dPuPF_%d_%d.pdf",algo,month,date));


TCanvas *c6 = new TCanvas("c6","c6",900,600);
c6->Divide(3,2,0,0);

c6->cd(1);
gPad->SetLogy();

htrackMax[0]->UseCurrentStyle();
htrackMax[0]->Draw("l hist");
htrackMax_[0]->Draw("esame");
drawCentTex(0);

tleg->Draw();



c6->cd(2);
gPad->SetLogy();

htrackMax[1]->UseCurrentStyle();
htrackMax[1]->Draw("l hist");
htrackMax_[1]->Draw("esame");
drawCentTex(1);

c6->cd(3);
gPad->SetLogy();

htrackMax[2]->UseCurrentStyle();
htrackMax[2]->Draw("l hist");
htrackMax_[2]->Draw("esame");
drawCentTex(2);

c6->cd(4);
gPad->SetLogy();

htrackMax[3]->UseCurrentStyle();
htrackMax[3]->Draw("l hist");
htrackMax_[3]->Draw("esame");
drawCentTex(3);

c6->cd(5);
gPad->SetLogy();

htrackMax[4]->UseCurrentStyle();
htrackMax[4]->Draw("l hist");
htrackMax_[4]->Draw("esame");
drawCentTex(4);

c6->cd(6);
gPad->SetLogy();

htrackMax[5]->UseCurrentStyle();
htrackMax[5]->Draw("l hist");
htrackMax_[5]->Draw("esame");
drawCentTex(5);


c6->SaveAs(Form("JetID_trackMax_ak%dPuPF_%d_%d.pdf",algo,month,date));




TCanvas *c7 = new TCanvas("c7","c7",900,600);

c7->Divide(3,2,0,0);

c7->cd(1);
gPad->SetLogy();


hpT[0]->UseCurrentStyle();
hpT[0]->Draw("l hist");
hpT_[0]->Draw("esame");
drawCentTex(0);

tleg->Draw();

c7->cd(2);
gPad->SetLogy();


hpT[1]->UseCurrentStyle();
hpT[1]->Draw("l hist");
hpT_[1]->Draw("esame");
drawCentTex(1);

c7->cd(3);
gPad->SetLogy();


hpT[2]->UseCurrentStyle();
hpT[2]->Draw("l hist");
hpT_[2]->Draw("esame");
drawCentTex(2);

c7->cd(4);
gPad->SetLogy();


hpT[3]->UseCurrentStyle();
hpT[3]->Draw("l hist");
hpT_[3]->Draw("esame");
drawCentTex(3);

c7->cd(5);
gPad->SetLogy();


hpT[4]->UseCurrentStyle();
hpT[4]->Draw("l hist");
hpT_[4]->Draw("esame");
drawCentTex(4);

c7->cd(6);
gPad->SetLogy();


hpT[5]->UseCurrentStyle();
hpT[5]->Draw("l hist");
hpT_[5]->Draw("esame");
drawCentTex(5);


c7->SaveAs(Form("JetQuality_pT_ak%dPuPF_%d_%d.pdf",algo,month,date));



TCanvas *c8 = new TCanvas("c8","c8",900,600);

c8->Divide(3,2,0,0);

c8->cd(1);

hphi[0]->UseCurrentStyle();
hphi[0]->Draw("l hist");
hphi_[0]->Draw("esame");
drawCentTex(0);

tleg->Draw();

c8->cd(2);

hphi[1]->UseCurrentStyle();
hphi[1]->Draw("l hist");
hphi_[1]->Draw("esame");
drawCentTex(1);

c8->cd(3);


hphi[2]->UseCurrentStyle();
hphi[2]->Draw("l hist");
hphi_[2]->Draw("esame");
drawCentTex(2);

c8->cd(4);


hphi[3]->UseCurrentStyle();
hphi[3]->Draw("l hist");
hphi_[3]->Draw("esame");
drawCentTex(3);

c8->cd(5);


hphi[4]->UseCurrentStyle();
hphi[4]->Draw("l hist");
hphi_[4]->Draw("esame");
drawCentTex(4);

c8->cd(6);

hphi[5]->UseCurrentStyle();
hphi[5]->Draw("l hist");
hphi_[5]->Draw("esame");
drawCentTex(5);

c8->SaveAs(Form("JetQuality_Phi_ak%dPuPF_%d_%d.pdf",algo,month,date));

TCanvas *c9 = new TCanvas("c9","c9",900,600);

c9->Divide(3,2,0,0);

c9->cd(1);

heta[0]->UseCurrentStyle();
heta[0]->Draw("l hist");
heta_[0]->Draw("esame");
drawCentTex(0);

tleg->Draw();

c9->cd(2);	

heta[1]->UseCurrentStyle();
heta[1]->Draw("l hist");
heta_[1]->Draw("esame");
drawCentTex(1);

c9->cd(3);

heta[2]->UseCurrentStyle();
heta[2]->Draw("l hist");
heta_[2]->Draw("esame");
drawCentTex(2);

c9->cd(4);

heta[3]->UseCurrentStyle();
heta[3]->Draw("l hist");
heta_[3]->Draw("esame");
drawCentTex(3);

c9->cd(5);	

heta[4]->UseCurrentStyle();
heta[4]->Draw("l hist");
heta_[4]->Draw("esame");
drawCentTex(4);

c9->cd(6);	

heta[5]->UseCurrentStyle();
heta[5]->Draw("l hist");
heta_[5]->Draw("esame");
drawCentTex(5);


c9->SaveAs(Form("JetQuality_Eta_ak%dPuPF_%d_%d.pdf",algo,month,date));




    TCanvas *c10 = new TCanvas("c10","c10",900,600);
	
    c10->Divide(3,2,0,0);
	
    c10->cd(1);

    heta_phi[0]->Draw("colz");
    drawCentTex(0);
    drawText("MC",0.7,0.65,22);
    
    c10->cd(2);
  
    heta_phi[1]->Draw("colz");
    drawCentTex(1);
    
    
    c10->cd(3);
    
    heta_phi[2]->Draw("colz");
    drawCentTex(2);
    
    c10->cd(4);
   
    heta_phi[3]->Draw("colz");
    drawCentTex(3);
    
     c10->cd(5);
    
    heta_phi[4]->Draw("colz");
    drawCentTex(4);
    
     c10->cd(6);
   
    heta_phi[5]->Draw("colz");
    drawCentTex(5);
    
    c10->SaveAs(Form("JetQuality_MC_Eta_Phi_ak%dPuPF_%d_%d.pdf",algo,month,date));
     
     
      TCanvas *c11 = new TCanvas("c11","c11",900,600);
	
    c11->Divide(3,2,0,0);
	
    c11->cd(1);

    heta_phi_[0]->Draw("colz");
    drawCentTex(0);
    drawText("Data",0.7,0.65,22);
    
    c11->cd(2);
  
	
    heta_phi_[1]->Draw("colz");
    drawCentTex(1);
    
    
    c11->cd(3);
    
    heta_phi_[2]->Draw("colz");
    drawCentTex(2);
    
    c11->cd(4);
   
    heta_phi_[3]->Draw("colz");
    drawCentTex(3);
    
     c11->cd(5);
    
    heta_phi_[4]->Draw("colz");
    drawCentTex(4);
    
     c11->cd(6);
   
    heta_phi_[5]->Draw("colz");
    drawCentTex(5);
    
     c11->SaveAs(Form("JetQuality_Data_Eta_Phi_ak%dPuPF_%d_%d.pdf",algo,month,date));
    
    TCanvas *c12 = new TCanvas("c12","c12",900,600);
	
    c12->Divide(3,2,0,0);
	
    c12->cd(1);

    heta_pT[0]->Draw("colz");
    drawCentTex(0);
    drawText("MC",0.7,0.65,22);
    
    c12->cd(2);
    
    heta_pT[1]->Draw("colz");
    drawCentTex(1);
    
    
    c12->cd(3);
    
    heta_pT[2]->Draw("colz");
    drawCentTex(2);
    
    c12->cd(4);
   
    heta_pT[3]->Draw("colz");
    drawCentTex(3);
    
     c12->cd(5);
    
    heta_pT[4]->Draw("colz");
    drawCentTex(4);
    
     c12->cd(6);
   
    heta_pT[5]->Draw("colz");
    drawCentTex(5);
    
     c12->SaveAs(Form("JetQuality_MC_Eta_pT_ak%dPuPF_%d_%d.pdf",algo,month,date));
      
    TCanvas *c13 = new TCanvas("c13","c13",900,600);
	
    c13->Divide(3,2,0,0);
	
    c13->cd(1);

    heta_pT_[0]->Draw("colz");
    drawCentTex(0);
    drawText("Data",0.7,0.65,22);
    
    c13->cd(2);
    
    heta_pT_[1]->Draw("colz");
    drawCentTex(1);
    
    
    c13->cd(3);
    
    heta_pT_[2]->Draw("colz");
    drawCentTex(2);
    
    c13->cd(4);
   
    heta_pT_[3]->Draw("colz");
    drawCentTex(3);
    
     c13->cd(5);
    
    heta_pT_[4]->Draw("colz");
    drawCentTex(4);
    
     c13->cd(6);
   
    heta_pT_[5]->Draw("colz");
    drawCentTex(5);
    
    c13->SaveAs(Form("JetQuality_Data_Eta_pT__ak%dPuPF_%d_%d.pdf",algo,month,date));
    
    
    
    
    TCanvas *c14 = new TCanvas("c14","c14",900,600);
	
    c14->Divide(3,2,0,0);
	
    c14->cd(1);
    gPad->SetLogy();
    

    hpthat[0]->Draw("e");
    drawCentTex(0);
    
    c14->cd(2);
    gPad->SetLogy();
	    
    hpthat[1]->Draw("e");
 	drawCentTex(1);
    
    
    c14->cd(3);
    gPad->SetLogy();
    
    hpthat[2]->Draw("e");
    drawCentTex(2);
    
    c14->cd(4);
    gPad->SetLogy();
   
    hpthat[3]->Draw("e");
    drawCentTex(3);
    
     c14->cd(5);
     gPad->SetLogy();
    
    hpthat[4]->Draw("e");
    drawCentTex(4);
    
     c14->cd(6);
     gPad->SetLogy();
   
    hpthat[5]->Draw("e");
    drawCentTex(5);
    
    c14->SaveAs(Form("JetQuality_pthat_MC__ak%dPuPF_%d_%d.pdf",algo,month,date));
    
	
	
	TCanvas *c15 = new TCanvas("c15","c15",900,600);
	c15->Divide(3,2,0,0);
	
	TLine *line = new TLine(0.,1,1.,1);
 	line->SetLineStyle(2), line->SetLineWidth(2);
	
	c15->cd(1);
	gPad->SetLogy();
	
    hphotonMax_Ratio[0]->Draw("");
    drawCentTex(0);
    line->Draw();
    
    
    c15->cd(2);
	gPad->SetLogy();
	
    hphotonMax_Ratio[1]->Draw("profile");
    drawCentTex(1);
    line->Draw();

    c15->cd(3);
	gPad->SetLogy();
	
    hphotonMax_Ratio[2]->Draw("profile");
    drawCentTex(2);
    line->Draw();
    
    c15->cd(4);
	gPad->SetLogy();
	
    hphotonMax_Ratio[3]->Draw("profile");
    drawCentTex(3);
    line->Draw();
    
    
    c15->cd(5);
	gPad->SetLogy();
	
    hphotonMax_Ratio[4]->Draw("profile");
    drawCentTex(4);
    line->Draw();
    
    c15->cd(6);
	gPad->SetLogy();
	
    hphotonMax_Ratio[5]->Draw("profile");
    drawCentTex(5);
    line->Draw();
   
   c15->SaveAs(Form("JetID_photonMax_Ratio_ak%dPuPF_%d_%d.pdf",algo,month,date));
	
    
	TCanvas *c16 = new TCanvas("c16","c16",900,600);
	c16->Divide(3,2,0,0);
	

	c16->cd(1);
    gPad->SetLogy();
	
    htrackSum_Ratio[0]->Draw("profile");
    drawCentTex(0);
    line->Draw();
    
    
    c16->cd(2);
    gPad->SetLogy();
	
    htrackSum_Ratio[1]->Draw("profile");
    drawCentTex(1);
    line->Draw();
    
    c16->cd(3);
    gPad->SetLogy();
	
    htrackSum_Ratio[2]->Draw("profile");
    drawCentTex(2);
    line->Draw();
    
    c16->cd(4);
    gPad->SetLogy();
	
    htrackSum_Ratio[3]->Draw("profile");
    drawCentTex(3);
    line->Draw();
    
    c16->cd(5);
    gPad->SetLogy();
	
    htrackSum_Ratio[4]->Draw("profile");
    drawCentTex(4);
    line->Draw();
    
    c16->cd(6);
    gPad->SetLogy();
	
    htrackSum_Ratio[5]->Draw("profile");
    drawCentTex(5);
 	line->Draw();
 	
	c16->SaveAs(Form("JetID_trackSum_Ratio_ak%dPuPF_%d_%d.pdf",algo,month,date));
	
	TCanvas *c17 = new TCanvas("c17","c17",900,600);
	c17->Divide(3,2,0,0);

 		 
	c17->cd(1);
    gPad->SetLogy();
	
    hneutralMax_Ratio[0]->Draw("profile");
    drawCentTex(0);
    line->Draw();
    
    
    c17->cd(2);
    gPad->SetLogy();
	
    hneutralMax_Ratio[1]->Draw("profile");
    drawCentTex(1);
    line->Draw();
    
    c17->cd(3);
    gPad->SetLogy();
	
    hneutralMax_Ratio[2]->Draw("profile");
    drawCentTex(2);
    line->Draw();
    
    c17->cd(4);
    gPad->SetLogy();
	
    hneutralMax_Ratio[3]->Draw("profile");
    drawCentTex(3);
    line->Draw();
    
    c17->cd(5);
    gPad->SetLogy();
	
    hneutralMax_Ratio[4]->Draw("profile");
    drawCentTex(4);
    line->Draw();
    
    c17->cd(6);
    gPad->SetLogy();
	
    hneutralMax_Ratio[5]->Draw("profile");
    drawCentTex(5);
    line->Draw();
   
	c17->SaveAs(Form("JetID_neutralMax_Ratio_ak%dPuPF_%d_%d.pdf",algo,month,date));
	 
	 
	TCanvas *c18 = new TCanvas("c18","c18",900,600);
	c18->Divide(3,2,0,0);

	
	c18->cd(1);
    gPad->SetLogy();
	
    hneutralSum_Ratio[0]->Draw("profile");
    drawCentTex(0);
    line->Draw();
    
    
    c18->cd(2);
    gPad->SetLogy();
	
    hneutralSum_Ratio[1]->Draw("profile");
    drawCentTex(1);
    line->Draw();
    
    c18->cd(3);
    gPad->SetLogy();
	
    hneutralSum_Ratio[2]->Draw("profile");
    drawCentTex(2);
    line->Draw();
    
    c18->cd(4);
    gPad->SetLogy();
	
    hneutralSum_Ratio[3]->Draw("profile");
    drawCentTex(3);
    line->Draw();
    
    c18->cd(5);
    gPad->SetLogy();
	
    hneutralSum_Ratio[4]->Draw("profile");
    drawCentTex(4);
    line->Draw();
    
    c18->cd(6);
    gPad->SetLogy();
	
    hneutralSum_Ratio[5]->Draw("profile");
    drawCentTex(5);
    line->Draw();
	
    c18->SaveAs(Form("JetID_neutralSum_Ratio_ak%dPuPF_%d_%d.pdf",algo,month,date));
	
	TCanvas *c19 = new TCanvas("c19","c19",900,600);
	c19->Divide(3,2,0,0);
	
	
	c19->cd(1);
    gPad->SetLogy();
	
    hphotonSum_Ratio[0]->Draw("profile");
    drawCentTex(0);
    line->Draw();
    
    
    c19->cd(2);
    gPad->SetLogy();
	
    hphotonSum_Ratio[1]->Draw("profile");
    drawCentTex(1);
    line->Draw();
    
    c19->cd(3);
    gPad->SetLogy();
	
    hphotonSum_Ratio[2]->Draw("profile");
    drawCentTex(2);
    line->Draw();
    
    c19->cd(4);
    gPad->SetLogy();
	
    hphotonSum_Ratio[3]->Draw("profile");
    drawCentTex(3);
    line->Draw();
    
    c19->cd(5);
    gPad->SetLogy();
	
    hphotonSum_Ratio[4]->Draw("profile");
    drawCentTex(4);
    line->Draw();
    
    c19->cd(6);
    gPad->SetLogy();
	
    hphotonSum_Ratio[5]->Draw("profile");
    drawCentTex(5);
    line->Draw();
   
   c19->SaveAs(Form("JetID_photonSum_Ratio_ak%dPuPF_%d_%d.pdf",algo,month,date));
		
		
	TCanvas *c20 = new TCanvas("c20","c20",900,600);
	c20->Divide(3,2,0,0);
	
	
    c20->cd(1);
    gPad->SetLogy();
	
    htrackMax_Ratio[0]->Draw("profile");
    drawCentTex(0);
    line->Draw();
    
    
     c20->cd(2);
    gPad->SetLogy();
	
    htrackMax_Ratio[1]->Draw("profile");
    drawCentTex(1);
    line->Draw();
    
     c20->cd(3);
    gPad->SetLogy();
	
    htrackMax_Ratio[2]->Draw("profile");
    drawCentTex(2);
    line->Draw();
    
     c20->cd(4);
    gPad->SetLogy();
	
    htrackMax_Ratio[3]->Draw("profile");
    drawCentTex(3);
    line->Draw();
    
     c20->cd(5);
    gPad->SetLogy();
	
    htrackMax_Ratio[4]->Draw("profile");
    drawCentTex(4);
    line->Draw();
    
     c20->cd(6);
    gPad->SetLogy();
	
    htrackMax_Ratio[5]->Draw("profile");
    drawCentTex(5);
    line->Draw();
    
 
 	c20->SaveAs(Form("JetID_trackMax_Ratio_ak%dPuPF_%d_%d.pdf",algo,month,date));
	
	
    
    
	
}


int GetCentBin(int bin)
{
	int ibin=-1;
	//! centrality is defined as 2.5% bins of cross section
	//! in 0-39 bins
	
    if(bin<2)ibin=0; //! 0-5%
    else if(bin>=2 && bin<4)ibin=1;    //! 5-10%
    else if(bin>=4 && bin<12)ibin=2;   //! 10-30%
    else if(bin>=12 && bin<20)ibin=3;  //! 30-50%
    else if(bin>=20 && bin<28)ibin=4;  //! 50-70%
    else if(bin>=28 && bin<36)ibin=5;  //! 70-90%
	return ibin;
}

void drawCentTex(const int centbin){
 TLatex *tex=0;
 
if(centbin==0)
  tex = new TLatex(0.7,0.8,"0-5%");
if(centbin==1)
  tex = new TLatex(0.7,0.8,"5-10%");
if(centbin==2)
  tex = new TLatex(0.7,0.8,"10-30%");
if(centbin==3)
  tex = new TLatex(0.7,0.8,"30-50%");
if(centbin==4)
  tex = new TLatex(0.7,0.8,"50-70%");
if(centbin==5)
  tex = new TLatex(0.7,0.8,"70-90%");


  tex->SetTextFont(63);
  tex->SetTextSize(22);
  tex->SetTextColor(kBlack);
  tex->SetLineWidth(1);
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





