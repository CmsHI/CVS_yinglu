#include "hiForest.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TMath.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include "TFitResultPtr.h"


using namespace std;


void ppJet60TriggerEff(const int algo=1){
	
	//Initiation 
	
	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();
	const int NBINS=17;
	Float_t BOUNDARIES[NBINS] = {10.,20.,30.,40.,50.,60.,70.,80.,90.,100.,110.,120.,140.,160.,180.,200.,300.};
	TH1F* jetptnum_ic5 = new TH1F("jetptnum_ic5","All jets with selection;p_{T}; N_{jets} ",NBINS-1,BOUNDARIES);
	TH1F* jetptnum_ak3 = new TH1F("jetptnum_ak3","All jets with selection;p_{T}; N_{jets}",NBINS-1,BOUNDARIES);
	TH1F *jetptdenom_ic5 = new TH1F("jetptdenom_ic5","All jets with selection;p_{T}; N_{jets} ",NBINS-1,BOUNDARIES);
	TH1F *jetptdenom_ak3 = new TH1F("jetptdenom_ak3","All jets with selection;p_{T}; N_{jets} ",NBINS-1,BOUNDARIES);
	
	
	
	float cutEtaJet = 2;
	
	float cutPtJet = 30;

	float jtpt_ic5[1000];
	float jteta_ic5[1000];
	int njets_ic5;
	
	float jtpt_ak3[1000];
	float jteta_ak3[1000];
	int njets_ak3;
	
	int mb;
	int jet60;
	int prescale;
	int HBHEFilter;
	
	TFile *inf = TFile::Open("rfio:///castor/cern.ch/user/y/yinglu/hiforest_pp_276TeV_data.root");	
	
	
	TTree* ic5t = (TTree*)inf->Get("icPu5JetAnalyzer/t");
	TTree* t = (TTree*)inf->Get("hltanalysis/HltTree");
	TTree* skimt = (TTree*)inf->Get("skimanalysis/HltTree");
	
	
	ic5t->SetBranchAddress("jtpt",jtpt_ic5);
	ic5t->SetBranchAddress("jteta",jteta_ic5);
	ic5t->SetBranchAddress("nref",&njets_ic5);
	
	TTree* ak3t = (TTree*)inf->Get("akPu3PFJetAnalyzer/t");
	
	ak3t->SetBranchAddress("jtpt",jtpt_ak3);
	ak3t->SetBranchAddress("jteta",jteta_ak3);
	ak3t->SetBranchAddress("nref",&njets_ak3);
	
	
	t->SetBranchAddress("HLT_L1BscMinBiasORBptxPlusANDMinus_v1",&mb);
	t->SetBranchAddress("HLT_Jet60_v1",&jet60);
	t->SetBranchAddress("HLT_L1BscMinBiasORBptxPlusANDMinus_v1_Prescl",&prescale);
	
	skimt->SetBranchAddress("pHBHENoiseFilter",&HBHEFilter);		

	
	int Nevents = t->GetEntries();
	for(int iev = 0; iev < Nevents; ++iev){
		t->GetEntry(iev);
		ic5t->GetEntry(iev);
				
			if(jtpt_ic5[0] < cutPtJet) continue;
			if(fabs(jteta_ic5[0]) > cutEtaJet) continue;
			if(!HBHEFilter) continue;
			if(mb) jetptdenom_ic5->Fill(jtpt_ic5[0]);
			if(mb&&jet60) jetptnum_ic5->Fill(jtpt_ic5[0]);
		
		
	}
	
	
	
	for(int iev = 0; iev < Nevents; ++iev){
		t->GetEntry(iev);
		ak3t->GetEntry(iev);
		
		
		
			if(jtpt_ak3[0] < cutPtJet) continue;
			if(fabs(jteta_ak3[0]) > cutEtaJet) continue;
			if(!HBHEFilter) continue;
			if(mb) jetptdenom_ak3->Fill(jtpt_ak3[0]);
			if(mb&&jet60) jetptnum_ak3->Fill(jtpt_ak3[0]);
		
		
	}	
		
	
     

		
		TCanvas *c1 = new TCanvas("c1", "");
		c1->Divide(2,1);
		
		
		
		gROOT->LoadMacro("erf.C");
		
		
		
		
		TGraphAsymmErrors *dividedthingy1= new TGraphAsymmErrors;
		dividedthingy1->BayesDivide(jetptnum_ic5,jetptdenom_ic5);
		
		TGraphAsymmErrors *dividedthingy2= new TGraphAsymmErrors;
		dividedthingy2->BayesDivide(jetptnum_ak3,jetptdenom_ak3);
		
		/*
		float xstart=20.0;
		float xend=300.0;
		
		
		TF1 *fitfcn = new TF1("fitfcn",erf,xstart,xend,2); //<============
		fitfcn->SetParameter(0,40); //<============= 
		TFitResultPtr results =dividedthingy->Fit("fitfcn","VSR");
		
		cout << "Chi2: " << results->Chi2() << " / " << results->Ndf() << " NDF" << endl;
		
		float turnon=fitfcn->GetX(0.99,10,300);
		cout << "99% at: " << turnon << endl;
		char turnontext[50]="";
		sprintf(turnontext,"HLT60 at %4.1f GeV",turnon);
		
		
		
		dividedthingy->GetFunction("fitfcn")->SetLineColor(1);
		*/
		
		c1->cd(1);
		dividedthingy1->SetLineColor(1);
		dividedthingy1->GetXaxis()->SetTitle("p_{T}^{leading jet} [GeV/c]");
		dividedthingy1->GetYaxis()->SetTitle("pp HLT_Jet60 Trigger Eff");
		dividedthingy1->Draw("Ap");
				
		c1->cd(2);
		dividedthingy2->SetLineColor(1);		
		dividedthingy2->GetXaxis()->SetTitle("p_{T}^{leading jet} [GeV/c]");
		dividedthingy2->GetYaxis()->SetTitle("pp HLT_Jet60 Trigger Eff");
		dividedthingy2->Draw("Ap");
		
		
		
		
		
		
	 
	
	
}
