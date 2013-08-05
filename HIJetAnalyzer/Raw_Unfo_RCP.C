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
	

//Read Central Unfo pbpb jet spectra	
TFile *f = new TFile("/home/yinglu/RooUnfold/CMSSW_4_1_3_patch2/src/RooUnfold-1.0.3/RCP_pbpb_Unfo/RCP_pbpb_Unfo1.root");
TFile *g = new TFile("/home/yinglu/RooUnfold/CMSSW_4_1_3_patch2/src/RooUnfold-1.0.3/RCP_pbpb_Unfo/RCP_pbpb_Unfo2.root");
TFile *h = new TFile("/home/yinglu/RooUnfold/CMSSW_4_1_3_patch2/src/RooUnfold-1.0.3/RCP_pbpb_Unfo/RCP_pbpb_Unfo3.root");
TFile *k = new TFile("/home/yinglu/RooUnfold/CMSSW_4_1_3_patch2/src/RooUnfold-1.0.3/RCP_pbpb_Unfo/RCP_pbpb_Unfo4.root");
TFile *l = new TFile("/home/yinglu/RooUnfold/CMSSW_4_1_3_patch2/src/RooUnfold-1.0.3/RCP_pbpb_Unfo/RCP_pbpb_Unfo5.root");
TFile *m = new TFile("/home/yinglu/RooUnfold/CMSSW_4_1_3_patch2/src/RooUnfold-1.0.3/RCP_pbpb_Unfo/RCP_pbpb_Unfo6.root");
TFile *n = new TFile("/home/yinglu/RooUnfold/CMSSW_4_1_3_patch2/src/RooUnfold-1.0.3/RCP_pbpb_Unfo/RCP_pbpb_Unfo7.root");

TH1F *hcorpt_pbpb_cent1 =(TH1F*)f->Get("Resmeas_Restrue");
TH1F *hcorpt_pbpb_cent2 =(TH1F*)g->Get("Resmeas_Restrue");
TH1F *hcorpt_pbpb_cent3 =(TH1F*)h->Get("Resmeas_Restrue");
TH1F *hcorpt_pbpb_cent4 =(TH1F*)k->Get("Resmeas_Restrue");
TH1F *hcorpt_pbpb_cent5 =(TH1F*)l->Get("Resmeas_Restrue");
TH1F *hcorpt_pbpb_cent6 =(TH1F*)m->Get("Resmeas_Restrue");
TH1F *hcorpt_pbpb_cent7 =(TH1F*)n->Get("Resmeas_Restrue");

// Scale by Lumi* X section -- Nevt	
		
		TH1F* hdN_dpt_cor_pbpb1=(TH1F*)hcorpt_pbpb_cent1->Clone("hdN_dpt_cor_pbpb1");
	
		// compute the differential yield (bin content/bin width)
		for(int i=1; i<=hdN_dpt_cor_pbpb1->GetNbinsX(); i++) {
			float width=hdN_dpt_cor_pbpb1->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hcorpt_pbpb_cent1->GetBinContent(i)/width/7.2/7.65/1000000.; 
			float err_cor=sqrt(hcorpt_pbpb_cent1->GetBinContent(i))/width/7.2/7.65/1000000.;
			hdN_dpt_cor_pbpb1->SetBinContent(i, dN_dpt_cor_pbpb);
			hdN_dpt_cor_pbpb1->SetBinError(i, err_cor);
			
		}
	
	
		TH1F* hdN_dpt_cor_pbpb2=(TH1F*)hcorpt_pbpb_cent2->Clone("hdN_dpt_cor_pbpb2");
	
		// compute the differential yield (bin content/bin width)
		for(int i=1; i<=hdN_dpt_cor_pbpb2->GetNbinsX(); i++) {
		float width=hdN_dpt_cor_pbpb2->GetBinWidth(i);
		float dN_dpt_cor_pbpb=hcorpt_pbpb_cent2->GetBinContent(i)/width/7.2/7.65/1000000.; 
		float err_cor=sqrt(hcorpt_pbpb_cent2->GetBinContent(i))/width/7.2/7.65/1000000.;
		hdN_dpt_cor_pbpb2->SetBinContent(i, dN_dpt_cor_pbpb);
		hdN_dpt_cor_pbpb2->SetBinError(i, err_cor);
		
	}
	
		TH1F* hdN_dpt_cor_pbpb3=(TH1F*)hcorpt_pbpb_cent3->Clone("hdN_dpt_cor_pbpb3");
	
	// compute the differential yield (bin content/bin width)
	for(int i=1; i<=hdN_dpt_cor_pbpb3->GetNbinsX(); i++) {
		float width=hdN_dpt_cor_pbpb3->GetBinWidth(i);
		float dN_dpt_cor_pbpb=hcorpt_pbpb_cent3->GetBinContent(i)/width/7.2/7.65/1000000.; 
		float err_cor=sqrt(hcorpt_pbpb_cent3->GetBinContent(i))/width/7.2/7.65/1000000.;
		hdN_dpt_cor_pbpb3->SetBinContent(i, dN_dpt_cor_pbpb);
		hdN_dpt_cor_pbpb3->SetBinError(i, err_cor);
		
	}
	
	TH1F* hdN_dpt_cor_pbpb4=(TH1F*)hcorpt_pbpb_cent4->Clone("hdN_dpt_cor_pbpb4");
	
	// compute the differential yield (bin content/bin width)
	for(int i=1; i<=hdN_dpt_cor_pbpb4->GetNbinsX(); i++) {
		float width=hdN_dpt_cor_pbpb4->GetBinWidth(i);
		float dN_dpt_cor_pbpb=hcorpt_pbpb_cent4->GetBinContent(i)/width/7.2/7.65/1000000.; 
		float err_cor=sqrt(hcorpt_pbpb_cent4->GetBinContent(i))/width/7.2/7.65/1000000.;
		hdN_dpt_cor_pbpb4->SetBinContent(i, dN_dpt_cor_pbpb);
		hdN_dpt_cor_pbpb4->SetBinError(i, err_cor);
		
	}
	
	TH1F* hdN_dpt_cor_pbpb5=(TH1F*)hcorpt_pbpb_cent5->Clone("hdN_dpt_cor_pbpb5");
	
	// compute the differential yield (bin content/bin width)
	for(int i=1; i<=hdN_dpt_cor_pbpb5->GetNbinsX(); i++) {
		float width=hdN_dpt_cor_pbpb5->GetBinWidth(i);
		float dN_dpt_cor_pbpb=hcorpt_pbpb_cent5->GetBinContent(i)/width/7.2/7.65/1000000.; 
		float err_cor=sqrt(hcorpt_pbpb_cent5->GetBinContent(i))/width/7.2/7.65/1000000.;
		hdN_dpt_cor_pbpb5->SetBinContent(i, dN_dpt_cor_pbpb);
		hdN_dpt_cor_pbpb5->SetBinError(i, err_cor);
		
	}
	
	TH1F* hdN_dpt_cor_pbpb6=(TH1F*)hcorpt_pbpb_cent6->Clone("hdN_dpt_cor_pbpb6");
	
	// compute the differential yield (bin content/bin width)
	for(int i=1; i<=hdN_dpt_cor_pbpb6->GetNbinsX(); i++) {
		float width=hdN_dpt_cor_pbpb6->GetBinWidth(i);
		float dN_dpt_cor_pbpb=hcorpt_pbpb_cent6->GetBinContent(i)/width/7.2/7.65/1000000.; 
		float err_cor=sqrt(hcorpt_pbpb_cent6->GetBinContent(i))/width/7.2/7.65/1000000.;
		hdN_dpt_cor_pbpb6->SetBinContent(i, dN_dpt_cor_pbpb);
		hdN_dpt_cor_pbpb6->SetBinError(i, err_cor);
		
	}
	
	TH1F* hdN_dpt_cor_pbpb7=(TH1F*)hcorpt_pbpb_cent7->Clone("hdN_dpt_cor_pbpb7");
	
	// compute the differential yield (bin content/bin width)
	for(int i=1; i<=hdN_dpt_cor_pbpb7->GetNbinsX(); i++) {
		float width=hdN_dpt_cor_pbpb7->GetBinWidth(i);
		float dN_dpt_cor_pbpb=hcorpt_pbpb_cent7->GetBinContent(i)/width/7.2/7.65/1000000.; 
		float err_cor=sqrt(hcorpt_pbpb_cent7->GetBinContent(i))/width/7.2/7.65/1000000.;
		hdN_dpt_cor_pbpb7->SetBinContent(i, dN_dpt_cor_pbpb);
		hdN_dpt_cor_pbpb7->SetBinError(i, err_cor);
		
	}
	
			
const int NBINS2=7;
	Double_t BOUNDARIES2[NBINS2] = {0,10,20,30,40,50,60};

	TH1F* hR_CP1 = new TH1F("hR_CP1","R_{CP};Centrality;R_{CP}",NBINS2-1,BOUNDARIES2); // 100-125GeV
	TH1F* hR_CP2 = new TH1F("hR_CP2","R_{CP};Centrality;R_{CP}",NBINS2-1,BOUNDARIES2); // 125-150GeV
	TH1F* hR_CP3 = new TH1F("hR_CP3","R_{CP};Centrality;R_{CP}",NBINS2-1,BOUNDARIES2); // 150-200GeV
	
	
		TCanvas *c4 = new TCanvas("c4","");
		c4.Divide(1,3);
		c4->cd(1);
	
		TH2F *htmp1 = new TH2F("htmp1","R_{CP};Centrality;R_{CP}",NBINS2-1,BOUNDARIES2, 1, 0, 1.5);
		htmp1->Draw();

		float bin_content1 = hdN_dpt_cor_pbpb1->GetBinContent(1)/(hdN_dpt_cor_pbpb7->GetBinContent(1));
		bin_content1 = bin_content1*10*28/1484/5;
		hR_CP1->SetBinContent(1, bin_content1);
	
		//float err_cor=(hdN_dpt_cor_pbpb1->GetBinError(1)/hdN_dpt_cor_pbpb7->GetBinError(1))*10*30/1484/2;
		//hR_CP1->SetBinError(1, err_cor);
	
		float bin_content2 = hdN_dpt_cor_pbpb2->GetBinContent(1)/(hdN_dpt_cor_pbpb7->GetBinContent(1));
		bin_content2 = bin_content2*10*28/927/5;
		hR_CP1->SetBinContent(2, bin_content2);
	
		//float err_cor=(sqrt(hdN_dpt_cor_pbpb2->GetBinContent(1))/sqrt(hdN_dpt_cor_pbpb7->GetBinContent(1)))*10*30/927/2;
		//hR_CP1->SetBinError(2, err_cor);

	
		float bin_content3 = hdN_dpt_cor_pbpb3->GetBinContent(1)/(hdN_dpt_cor_pbpb7->GetBinContent(1));
		bin_content3 = bin_content3*10*28/562/5;
		hR_CP1->SetBinContent(3, bin_content3);
	
		//float err_cor=(sqrt(hdN_dpt_cor_pbpb3->GetBinContent(1))/sqrt(hdN_dpt_cor_pbpb7->GetBinContent(1)))*10*30/562/2;
		//hR_CP1->SetBinError(3, err_cor);

		
		float bin_content4 = hdN_dpt_cor_pbpb4->GetBinContent(1)/(hdN_dpt_cor_pbpb7->GetBinContent(1));
		bin_content4 = bin_content4*10*28/323/5;
		hR_CP1->SetBinContent(4, bin_content4);
	
		//float err_cor=(sqrt(hdN_dpt_cor_pbpb4->GetBinContent(1))/sqrt(hdN_dpt_cor_pbpb7->GetBinContent(1)))*5*30/251/2;
		//hR_CP1->SetBinError(4, err_cor);

	
		float bin_content5 = hdN_dpt_cor_pbpb5->GetBinContent(1)/(hdN_dpt_cor_pbpb7->GetBinContent(1));
		bin_content5 = bin_content5*10*28/175/5;
		hR_CP1->SetBinContent(5, bin_content5);
	
		float bin_content6 = hdN_dpt_cor_pbpb6->GetBinContent(1)/(hdN_dpt_cor_pbpb7->GetBinContent(1));
		bin_content6 = bin_content6*10*28/87/5;
		hR_CP1->SetBinContent(6, bin_content6);
	
		hR_CP1->SetMarkerColor(2);
		hR_CP1->SetMarkerStyle(20);
		hR_CP1->Draw("same");
	
		TLegend *tleg = new TLegend(0.65, 0.6, 0.85, 0.85);
		tleg->SetBorderSize(0);
		tleg->AddEntry(hR_CP1," 100-125GeV ","");
		tleg->Draw("same");
	
		TLine * line = new TLine(0,1,60,1);
		line->Draw("same");


	
	
		c4->cd(2);
		
		TH2F *htmp2 = new TH2F("htmp2","R_{CP};Centrality;R_{CP}",NBINS2-1,BOUNDARIES2, 1, 0, 1.5);
		htmp2->Draw();

		float bin_content1 = hdN_dpt_cor_pbpb1->GetBinContent(2)/(hdN_dpt_cor_pbpb7->GetBinContent(2));
		bin_content1 = bin_content1*10*28/1484/5;
		hR_CP2->SetBinContent(1, bin_content1);
	
		float bin_content2 = hdN_dpt_cor_pbpb2->GetBinContent(2)/(hdN_dpt_cor_pbpb7->GetBinContent(2));
		bin_content2 = bin_content2*10*28/927/5;
		hR_CP2->SetBinContent(2, bin_content2);
	
		float bin_content3 = hdN_dpt_cor_pbpb3->GetBinContent(2)/(hdN_dpt_cor_pbpb7->GetBinContent(2));
		bin_content3 = bin_content3*10*28/562/5;
		hR_CP2->SetBinContent(3, bin_content3);
	
		float bin_content4 = hdN_dpt_cor_pbpb4->GetBinContent(2)/(hdN_dpt_cor_pbpb7->GetBinContent(2));
		bin_content4 = bin_content4*10*28/323/5;
		hR_CP2->SetBinContent(4, bin_content4);
	
		float bin_content5 = hdN_dpt_cor_pbpb5->GetBinContent(2)/(hdN_dpt_cor_pbpb7->GetBinContent(2));
		bin_content5 = bin_content5*10*28/175/5;
		hR_CP2->SetBinContent(5, bin_content5);
	
		float bin_content6 = hdN_dpt_cor_pbpb6->GetBinContent(2)/(hdN_dpt_cor_pbpb7->GetBinContent(2));
		bin_content6 = bin_content6*10*28/87/5;
		hR_CP2->SetBinContent(6, bin_content6);
	
		hR_CP2->SetMarkerColor(3);
		hR_CP2->SetMarkerStyle(20);
		hR_CP2->Draw("same");
	
		TLegend *tleg = new TLegend(0.65, 0.6, 0.85, 0.85);
		tleg->SetBorderSize(0);
		tleg->AddEntry(hR_CP2," 125-150GeV ","");
		tleg->Draw("same");
	
		TLine * line = new TLine(0,1,60,1);
		line->Draw("same");
		

	
		
		c4->cd(3);
	
		TH2F *htmp3 = new TH2F("htmp3","R_{CP};Centrality;R_{CP}",NBINS2-1,BOUNDARIES2, 1, 0, 1.5);
		htmp3->Draw();
	
		float bin_content1 = hdN_dpt_cor_pbpb1->GetBinContent(3)/(hdN_dpt_cor_pbpb7->GetBinContent(3));
		bin_content1 = bin_content1*10*28/1484/5;
		hR_CP3->SetBinContent(1, bin_content1);
	
		float bin_content2 = hdN_dpt_cor_pbpb2->GetBinContent(3)/(hdN_dpt_cor_pbpb7->GetBinContent(3));
		bin_content2 = bin_content2*10*28/927/5;
		hR_CP3->SetBinContent(2, bin_content2);
	
		float bin_content3 = hdN_dpt_cor_pbpb3->GetBinContent(3)/(hdN_dpt_cor_pbpb7->GetBinContent(3));
		bin_content3 = bin_content3*10*28/562/5;
		hR_CP3->SetBinContent(3, bin_content3);
	
		float bin_content4 = hdN_dpt_cor_pbpb4->GetBinContent(3)/(hdN_dpt_cor_pbpb7->GetBinContent(3));
		bin_content4 = bin_content4*10*28/323/5;
		hR_CP3->SetBinContent(4, bin_content4);
	
	
		float bin_content5 = hdN_dpt_cor_pbpb5->GetBinContent(3)/(hdN_dpt_cor_pbpb7->GetBinContent(3));
		bin_content5 = bin_content5*10*28/175/5;
		hR_CP3->SetBinContent(5, bin_content5);
	
		float bin_content6 = hdN_dpt_cor_pbpb6->GetBinContent(3)/(hdN_dpt_cor_pbpb7->GetBinContent(3));
		bin_content6 = bin_content6*10*28/87/5;
		hR_CP3->SetBinContent(6, bin_content6);
	
		hR_CP3->SetMarkerColor(5);
		hR_CP3->SetMarkerStyle(20);	
		hR_CP3->Draw("same");
	
		TLegend *tleg = new TLegend(0.65, 0.6, 0.85, 0.85);
		tleg->SetBorderSize(0);
		tleg->AddEntry(hR_CP3," 150-200GeV ","");
		tleg->Draw("same");
	
		TLine * line = new TLine(0,1,60,1);
		line->Draw("same");
	
	
		
	
	
	
	 



}