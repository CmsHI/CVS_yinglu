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
	const int NBINS=10;
	Double_t BOUNDARIES[NBINS] = {100,120,140,160,180,200,220,240,280,350};


//Read Central Unfo pbpb jet spectra	
TFile *f = new TFile("pbpb_Unfo_central.root");
//TFile *f = new TFile("pbpb_Unfo_periph.root");
//TFile *f = new TFile("pbpb_Unfo_mid.root");
TH1F *hpbpb_unfospectra1 =(TH1F*)f->Get("Resmeas_Restrue");

	// compute the differential yield (bin content/bin width)
	for(int i=1; i<=hpbpb_unfospectra1->GetNbinsX(); i++) {
		float width=hpbpb_unfospectra1->GetBinWidth(i);
		float dN_dpt_cor_pbpb1=hpbpb_unfospectra1->GetBinContent(i)/width/7.2/7.65/1000000.; //20743 total events
		float err_cor1=sqrt(hpbpb_unfospectra1->GetBinContent(i))/width/7.2/7.65/1000000.;
		//float dN_dpt_cor_pbpb1=hpbpb_unfospectra1->GetBinContent(i)/width*7650/4001; //20743 total events
		//float err_cor1=sqrt(hpbpb_unfospectra1->GetBinContent(i))/width*7650/4001;
		hpbpb_unfospectra1->SetBinContent(i, dN_dpt_cor_pbpb1);
		hpbpb_unfospectra1->SetBinError(i, err_cor1);
		
	}
	
	
	
// Read Periph Unfo pbpb jet spectra	
  TFile *k = new TFile("pbpb_Unfo_periph.root");
//TFile *g = new TFile("pbpb_Unfo_mid.root");
TH1F *hpbpb_unfospectra2 =(TH1F*)k->Get("Resmeas_Restrue");

	// compute the differential yield (bin content/bin width)
	for(int i=1; i<=hpbpb_unfospectra2->GetNbinsX(); i++) {
		float width=hpbpb_unfospectra2->GetBinWidth(i);
		float dN_dpt_cor_pbpb2=hpbpb_unfospectra2->GetBinContent(i)/width/7.2/7.65/1000000.; //20743 total events
		float err_cor2=sqrt(hpbpb_unfospectra2->GetBinContent(i))/width/7.2/7.65/1000000.;
		//float dN_dpt_cor_pbpb2=hpbpb_unfospectra2->GetBinContent(i)/width*7650/4001; //20743 total events
		//float err_cor2=sqrt(hpbpb_unfospectra2->GetBinContent(i))/width*7650/4001;
		hpbpb_unfospectra2->SetBinContent(i, dN_dpt_cor_pbpb2);
		hpbpb_unfospectra2->SetBinError(i, err_cor2);
		
	}
		
// Read unfo pp jet spectra

TFile *g = new TFile("pp_Unfo.root");
TH1F *hpp_unfospectra =(TH1F*)g->Get("Resmeas_Restrue");

	// compute the differential yield (bin content/bin width)
	for(int i=1; i<=hpp_unfospectra->GetNbinsX(); i++) {
	float width=hpp_unfospectra->GetBinWidth(i);
	float dN_dpt_cor_pp=hpp_unfospectra->GetBinContent(i)/width/231./56./1000000; //4617960 total events
	float err_cor=sqrt(hpp_unfospectra->GetBinContent(i))/width/231./56./1000000;
	//float dN_dpt_cor_pp=hpp_unfospectra->GetBinContent(i)/width*56./23131; //4617960 total events
	//float err_cor=sqrt(hpp_unfospectra->GetBinContent(i))/width*56./23131;
	hpp_unfospectra->SetBinContent(i, dN_dpt_cor_pp);
	hpp_unfospectra->SetBinError(i, err_cor);
}


/*TFile *k = new TFile("/home/yinglu/RooUnfold/CMSSW_4_1_3_patch2/src/RooUnfold-1.0.3/Data/JetSpectra_central.root");
TH1F* hpbpb_rawspectra=(TH1F*)k->Get("hcorpt_pbpb_cent1"); //Reco
TH1F* hpp_rawspectra=(TH1F*)k->Get("hcorpt_pp_cent1"); //Reco
*/


// Unfo Normalized jet spectra
 TCanvas *c1 = new TCanvas("c1","");
 //TH2F *htmp = new TH2F("htmp","",NBINS-1, BOUNDARIES, 100, 0., hpbpb_unfospectra2->GetMaximum()*1.5);
 //htmp->SetXTitle("E_{T} (GeV)");
 //htmp->Draw();
 hpbpb_unfospectra1->SetMarkerColor(2);
 hpbpb_unfospectra1->Draw("");
 hpbpb_unfospectra2->SetMarkerColor(5);
 hpbpb_unfospectra2->Draw("same");
 hpp_unfospectra->SetMarkerColor(9);
 hpp_unfospectra->Draw("same");
// hpbpb_rawspectra->SetMarkerColor(3);
// hpbpb_rawspectra->Draw("SAME");
// hpp_rawspectra->SetMarkerColor(5);
// hpp_rawspectra->Draw("SAME");


 //Unfolded	Jet RAA 

	 TH1F* hRAA1=(TH1F*) hpbpb_unfospectra1->Clone("hRAA1");
	 TH1F* hRAA2=(TH1F*) hpbpb_unfospectra2->Clone("hRAA2");
	 hRAA1->Scale(0.0067385); // 1/Ncoll  Ncoll is 1484 for 0-10% centrality  centrality factor *10
	 hRAA2->Scale(0.0666666666); // 1/Ncoll  Ncoll is 30 for 50-100% centrality  centrality factor *2
	 hRAA1->Divide(hpp_unfospectra);
	 hRAA2->Divide(hpp_unfospectra);

    TCanvas *c2 = new TCanvas("c2","");

    TH2F *htmp1 = new TH2F("htmp1","",NBINS-1, BOUNDARIES, 100, 0., hRAA2->GetMaximum()*2.);
	 htmp1->GetXaxis()->SetTitle("p_{T} [GeV/c]");
	 htmp1->GetYaxis()->SetTitle("R_{AA}");
	 htmp1->SetTitle("R_{AA}");
	 htmp1->Draw();
	 hRAA1->SetMarkerColor(2);
	 hRAA1->Draw("same");
	 hRAA2->SetMarkerColor(9);
	 hRAA2->Draw("same");
	 hRAA1->SetMarkerStyle(20);
	 hRAA1->SetMarkerSize(0.8);
	 hRAA2->SetMarkerSize(0.8);
	
	 


// Without Unfolding Jet RAA for central and periph
TFile *j = new TFile("/home/yinglu/RooUnfold/CMSSW_4_1_3_patch2/src/RooUnfold-1.0.3/Data/JetSpectra_central.root");
TH1F *hRAA_cent = (TH1F*)j->Get("hRAA");
TFile *m = new TFile("/home/yinglu/RooUnfold/CMSSW_4_1_3_patch2/src/RooUnfold-1.0.3/Data/JetSpectra_periph.root");
TH1F *hRAA_periph = (TH1F*)m->Get("hRAA");
hRAA_cent->SetMarkerColor(6);
hRAA_cent->Draw("same");
hRAA_periph->SetMarkerColor(8);
hRAA_periph->Draw("same");
TLine * line = new TLine(100,1,350,1);
line->Draw("same");
TLegend *tleg = new TLegend(0.65, 0.6, 0.85, 0.85);
tleg->SetBorderSize(0);
tleg->AddEntry(hRAA_cent," central ","pl");
tleg->AddEntry(hRAA_periph," peripheral ","pl");
tleg->AddEntry(hRAA1," central unfo ","pl");
tleg->AddEntry(hRAA2," periph unfo ","pl");
tleg->Draw("same");

	
	
	 



}