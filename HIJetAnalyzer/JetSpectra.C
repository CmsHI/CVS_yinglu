#if !defined(__CINT__) || defined(__MAKECINT__)

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TMath.h"


#endif



{	 


	// pp data, Fetch the tree 
	TFile * f= new TFile("Matt_JetTrees_pp.root");
	TTree * t =(TTree*)gDirectory->Get("t");
	
	TFile *JetSpectra = new TFile("JetSpectra.root","RECREATE");
	
	// Jet spectra
	//const int NBINS=17;
	//Double_t BOUNDARIES[NBINS] = {85,95,105,115,125,135,145,155,165,175,185,195,215,235,260,300,350};
	
	const int NBINS=10;
	Double_t BOUNDARIES[NBINS] = {100,120,140,160,180,200,220,240,280,350};
	
	
	TH1F* hcorpt_pp_cent1 = new TH1F("hcorpt_pp_cent1","All jets with selection;p_{T}; # of Events",NBINS-1,BOUNDARIES);
	hcorpt_pp_cent1->Sumw2();
	
    TCanvas *c1 = new TCanvas("c1","");
	c1.Divide(1,2);
	c1->cd(1);
	t->Draw("corrpt_j4>>hcorpt_pp_cent1","corrpt_j4[0]>85 && abs(jteta_j4)<2","");
	
	hcorpt_pp_cent1->Write();
	
		// Scale by Lumi* X section -- Nevt	

	//hdN_dpt_cor_pp=(TH1F*)hcorpt_pp->Clone("hdN_dpt_cor_pp");
	//hdN_dpt_cor_pp->Scale(1/(hdN_dpt_cor_pp->Integral()*(231*56*1000000)));
	
	
	  // Scale by Lumi* X section -- Nevt	
	
	  TH1F* hdN_dpt_cor_pp=(TH1F*)hcorpt_pp_cent1->Clone("hdN_dpt_cor_pp");
	// compute the differential yield (bin content/bin width)
	for(int i=1; i<=hdN_dpt_cor_pp->GetNbinsX(); i++) {
		float width=hdN_dpt_cor_pp->GetBinWidth(i);
		
		cout << width << endl;
		//float dN_dpt_cor_pp=hcorpt_pp_cent1->GetBinContent(i)/width*56/23131; //4617960 total events
		//float err_cor=sqrt(hcorpt_pp_cent1->GetBinContent(i))/width*56/23131;
		float dN_dpt_cor_pp=hcorpt_pp_cent1->GetBinContent(i)/width/231./56./1000000; //4617960 total events
		float err_cor=sqrt(hcorpt_pp_cent1->GetBinContent(i))/width/231./56./1000000;
		hdN_dpt_cor_pp->SetBinContent(i, dN_dpt_cor_pp);
		hdN_dpt_cor_pp->SetBinError(i, err_cor);
		
	}
		//float scale = 1/(231*56*1000000);
		//hdN_dpt_cor_pp->Scale(0.0000000000773036);


	c1->cd(2);
	hdN_dpt_cor_pp->SetMarkerStyle(20);
	hdN_dpt_cor_pp->SetMarkerSize(0.8);
	hdN_dpt_cor_pp->SetMarkerColor(2);
	hdN_dpt_cor_pp->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	hdN_dpt_cor_pp->GetYaxis()->SetTitle("1/N_{evt} dN/dp_{T} [GeV^{-1}]");
	hdN_dpt_cor_pp->SetTitle("Jet Spectra of pp in Matt's Tree");
	hdN_dpt_cor_pp->Draw();
	gPad->SetLogy();	
	hdN_dpt_cor_pp->Write();
	
	
	
	
	// HI data, Fetch the tree 
	TChain * chain= new TChain("t","");
	chain->Add("Set1.root");
	chain->Add("Set2.root");
	chain->Add("Set3.root");
	chain->Add("Set4_FIX.root");
	
	
	// Jet spectra
	//const int NBINS=17;
	//Double_t BOUNDARIES[NBINS] = {85,95,105,115,125,135,145,155,165,175,185,195,215,235,260,300,350};
	
	const int NBINS=10;
	Double_t BOUNDARIES[NBINS] = {100,120,140,160,180,200,220,240,280,350};
	
	
	TH1F* hcorpt_pbpb_cent1 = new TH1F("hcorpt_pbpb_cent1","All jets with selection;p_{T}; # of Events",NBINS-1,BOUNDARIES);
	hcorpt_pbpb_cent1->Sumw2();
	
	c1->cd(1);
	//chain->Draw("corrpt_j4>>hcorpt_pbpb_cent1","corrpt_j4[0]>85 && abs(jteta_j4)<2 && bin>19","same");
   chain->Draw("corrpt_j4>>hcorpt_pbpb_cent1","corrpt_j4[0]>85 && abs(jteta_j4)<2 && bin<4","same");
	hcorpt_pbpb_cent1->Write();
		// Scale by Lumi* X section -- Nevt	

	//hdN_dpt_cor_pbpb=(TH1F*)hcorpt_pp->Clone("hdN_dpt_cor_pbpb");
	//hdN_dpt_cor_pbpb->Scale(1/(hdN_dpt_cor_pbpb->Integral()*(231*56*1000000)));
	
	
	  // Scale by Lumi* X section -- Nevt	
	
	  TH1F* hdN_dpt_cor_pbpb=(TH1F*)hcorpt_pbpb_cent1->Clone("hdN_dpt_cor_pbpb");
	// compute the differential yield (bin content/bin width)
	for(int i=1; i<=hdN_dpt_cor_pbpb->GetNbinsX(); i++) {
		float width=hdN_dpt_cor_pbpb->GetBinWidth(i);
		//float dN_dpt_cor_pbpb=hcorpt_pbpb_cent1->GetBinContent(i)/width*7650./4001; //20743 total events
		//float err_cor=sqrt(hcorpt_pbpb_cent1->GetBinContent(i))/width*7650./4001;
		float dN_dpt_cor_pbpb=hcorpt_pbpb_cent1->GetBinContent(i)/width/7.2/7.65/1000000.; //20743 total events
		float err_cor=sqrt(hcorpt_pbpb_cent1->GetBinContent(i))/width/7.2/7.65/1000000.;
		hdN_dpt_cor_pbpb->SetBinContent(i, dN_dpt_cor_pbpb);
		hdN_dpt_cor_pbpb->SetBinError(i, err_cor);
		
	}
		
		//float scale = 1/(7.2*7.65*1000000)   
	    // Ncoll = 1484 for central events  0-10%
	   // hdN_dpt_cor_pbpb->Scale(0.000000018155);
	
	
	c1->cd(2);
	hdN_dpt_cor_pbpb->SetMarkerStyle(20);
	hdN_dpt_cor_pbpb->SetMarkerSize(0.8);
	hdN_dpt_cor_pbpb->SetMarkerColor(9);
	hdN_dpt_cor_pbpb->Draw("same");
	hdN_dpt_cor_pbpb->Write();
	
	
  /* TLegend *tleg = new TLegend(0.65, 0.6, 0.85, 0.85);
   tleg->SetBorderSize(0);
   TLatex *la1 = new TLatex(120, hdN_dpt_cor_pp->GetMaximum()*1.55);
   tleg->AddEntry(hdN_dpt_cor_pp," pp ","pl");
   tleg->AddEntry(hdN_dpt_cor_pbpb," PbPb","pl");
   tleg->Draw("same");
   la1->Draw();
*/
	 
	 TCanvas *c2 = new TCanvas("c2","");
	 TH2F *htmp1 = new TH2F("htmp1","",NBINS-1,BOUNDARIES, 100, 0., hdN_dpt_cor_pbpb->GetMaximum()*1.5);
	 TH1F* hRAA=(TH1F*)hdN_dpt_cor_pbpb->Clone("hRAA");
	 hRAA->Scale(0.0067385); // 1/Ncoll  Ncoll is 1484 for 0-10% centrality  centrality factor *10
	 //hRAA->Scale(0.0666666666); // 1/Ncoll  Ncoll is 30 for 50-100% centrality  centrality factor *2
	 hRAA->Divide(hdN_dpt_cor_pp);
	 hRAA->SetMarkerStyle(20);
	 hRAA->SetMarkerSize(0.8);
	 hRAA->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	 hRAA->GetYaxis()->SetTitle("R_{AA}");
	 hRAA->SetTitle("R_{AA}");
	 hRAA->SetMarkerColor(4);
	 hRAA->Draw("");
	
	JetSpectra->Write();
	JetSpectra->Close();
		
}


