#include "hiForest.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TMath.h"
#include "TLegend.h"


using namespace std;


void HIJet80TriggerEff(const int algo=1){
	
	//Initiation 
	
	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();
	const int NBINS=15;
	Float_t BOUNDARIES[NBINS] = {30.,40.,50.,60.,70.,80.,90.,100.,110.,120.,140.,160.,180.,200.,300.};
	TH1F* hjetptnum_tmp = new TH1F("hjetptnum","All jets with selection;p_{T}; N_{jets} ",NBINS-1,BOUNDARIES);
	TH1F* hjetptdenom_tmp = new TH1F("hjetptdenom","All jets with selection;p_{T}; N_{jets}",NBINS-1,BOUNDARIES);
	
	// Heavy Ion Data
	
	HiForest *c = new HiForest("rfio:///castor/cern.ch/user/v/velicanu/forest/HiForestMinBias_v2.root"); 
	TCanvas *c0 = new TCanvas("c0","");
	
	// icpu5 jets
	if (algo==1)
	{
	c->tree->Draw("icPu5.jtpt[0]>>hjetptnum_tmp", "hltTree.HLT_HIJet80_v1 && hltTree.HLT_HIMinBiasHfOrBSC_v1 && icPu5.jtpt[0] >30 &&abs(icPu5.jteta[0])<2&& skim.pcollisionEventSelection && skim.pHBHENoiseFilter");
    TH1F *hjetptnum = (TH1F*)gDirectory->Get("hjetptnum_tmp");
	c->tree->Draw("icPu5.jtpt[0]>>hjetptdenom_tmp", "hltTree.HLT_HIMinBiasHfOrBSC_v1 && icPu5.jtpt[0] >30 && abs(icPu5.jteta[0])<2 && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
	TH1F* hjetptdenom = (TH1F*)gDirectory->Get("hjetptdenom_tmp");
	}
//	cout<<"hjetptdenom->Mean"<<hjetptdenom->GetMean()<<endl;
//  cout<<"hjetptnum->Mean"<<hjetptnum->GetMean()<<endl;


    // akpupf3 jets
    if (algo==2)
	{
    c->tree->Draw("akPu3PF.jtpt[0]>>hjetptnum_tmp", "hltTree.HLT_HIJet80_v1 && hltTree.HLT_HIMinBiasHfOrBSC_v1 && akPu3PF.jtpt[0] >30 && abs(akPu3PF.jteta[0])<2 && skim.pcollisionEventSelection && skim.pHBHENoiseFilter");
    TH1F *hjetptnum = (TH1F*)gDirectory->Get("hjetptnum_tmp");
	c->tree->Draw("akPu3PF.jtpt[0]>>hjetptdenom_tmp", "hltTree.HLT_HIMinBiasHfOrBSC_v1 && akPu3PF.jtpt[0] >30 && abs(akPu3PF.jteta[0])<2&& skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
	TH1F* hjetptdenom = (TH1F*)gDirectory->Get("hjetptdenom_tmp");
     }
     
	c0->Clear();	
	TCanvas *c2 = new TCanvas("c2","");
	c2->cd();

	hjetptnum->Draw("ep");
	hjetptdenom->Draw("epsame");
	
//        c0->SaveAs("test.gif");
		
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
		dividedthingy->BayesDivide(hjetptnum,hjetptdenom);
		
		
		float xstart=20.0;
		float xend=300.0;
		
		
		/*TF1 *fitfcn = new TF1("fitfcn",erf,xstart,xend,2); //<============
		fitfcn->SetParameter(0,40); //<============= 
		TFitResultPtr results =dividedthingy->Fit("fitfcn","VSR");
		
		cout << "Chi2: " << results->Chi2() << " / " << results->Ndf() << " NDF" << endl;
		
		float turnon=fitfcn->GetX(0.99,10,300);
		cout << "99% at: " << turnon << endl;
		char turnontext[50]="";
		sprintf(turnontext,"HLT80 at %4.1f GeV",turnon);
		
		
		
		dividedthingy->GetFunction("fitfcn")->SetLineColor(1);
		dividedthingy->SetLineColor(1);
		*/
		dividedthingy->GetXaxis()->SetTitle("p_{T}^{leading jet} [GeV/c]");
		dividedthingy->GetYaxis()->SetTitle("HLT_Jet80 Trigger Eff");
		dividedthingy->Draw("Ap");
		
		
		
		
		
		
	 
	
	
}
