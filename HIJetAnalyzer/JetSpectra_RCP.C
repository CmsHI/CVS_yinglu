 

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
	TFile *RCP_pbpb_Spectra = new TFile("RCP_pbpb_Spectra.root","RECREATE");
		
	const int NBINS1=5;
	Double_t BOUNDARIES1[NBINS1] = {100,125,150,200,350};
	
		
		
		TH1F* hcorpt_pbpb_cent1 = new TH1F("hcorpt_pbpb_cent1","All jets with selection;p_{T}; # of Events",NBINS1-1,BOUNDARIES1);
		TH1F* hcorpt_pbpb_cent2 = new TH1F("hcorpt_pbpb_cent2","All jets with selection;p_{T}; # of Events",NBINS1-1,BOUNDARIES1);
		TH1F* hcorpt_pbpb_cent3 = new TH1F("hcorpt_pbpb_cent3","All jets with selection;p_{T}; # of Events",NBINS1-1,BOUNDARIES1);
		TH1F* hcorpt_pbpb_cent4 = new TH1F("hcorpt_pbpb_cent4","All jets with selection;p_{T}; # of Events",NBINS1-1,BOUNDARIES1);
		TH1F* hcorpt_pbpb_cent5 = new TH1F("hcorpt_pbpb_cent5","All jets with selection;p_{T}; # of Events",NBINS1-1,BOUNDARIES1);
		TH1F* hcorpt_pbpb_cent6 = new TH1F("hcorpt_pbpb_cent6","All jets with selection;p_{T}; # of Events",NBINS1-1,BOUNDARIES1);
		TH1F* hcorpt_pbpb_cent7 = new TH1F("hcorpt_pbpb_cent7","All jets with selection;p_{T}; # of Events",NBINS1-1,BOUNDARIES1);




		hcorpt_pbpb_cent1->Sumw2();
		hcorpt_pbpb_cent2->Sumw2();
		hcorpt_pbpb_cent3->Sumw2();
		hcorpt_pbpb_cent4->Sumw2();
		hcorpt_pbpb_cent5->Sumw2();
		hcorpt_pbpb_cent6->Sumw2();
		hcorpt_pbpb_cent7->Sumw2();

		
	     
	   
		
		// HI data, Fetch the tree 
		TChain * chain= new TChain("t","");
		chain->Add("Set1.root");
		chain->Add("Set2.root");
		chain->Add("Set3.root");
		chain->Add("Set4_FIX.root");
	
		
		chain->Draw("corrpt_j4>>hcorpt_pbpb_cent1","corrpt_j4[0]>85 && abs(jteta_j4)<2 && bin<4","same"); // 0-10%
		chain->Draw("corrpt_j4>>hcorpt_pbpb_cent2","corrpt_j4[0]>85 && abs(jteta_j4)<2 && bin>3 && bin<8","same"); //10-20%
		chain->Draw("corrpt_j4>>hcorpt_pbpb_cent3","corrpt_j4[0]>85 && abs(jteta_j4)<2 && bin>7 && bin<12","same");  //20-30%
		chain->Draw("corrpt_j4>>hcorpt_pbpb_cent4","corrpt_j4[0]>85 && abs(jteta_j4)<2 && bin>11 && bin<16","same"); //30-40%
		chain->Draw("corrpt_j4>>hcorpt_pbpb_cent5","corrpt_j4[0]>85 && abs(jteta_j4)<2 && bin>15 && bin<20","same"); //40-50%
		//chain->Draw("corrpt_j4>>hcorpt_pbpb_cent4","corrpt_j4[0]>85 && abs(jteta_j4)<2 && bin>11 && bin<20","same");
		chain->Draw("corrpt_j4>>hcorpt_pbpb_cent6","corrpt_j4[0]>85 && abs(jteta_j4)<2 && bin>19 && bin<24","same"); //50-60%
		chain->Draw("corrpt_j4>>hcorpt_pbpb_cent7","corrpt_j4[0]>85 && abs(jteta_j4)<2 && bin>23 && bin<32","same"); //60-80%

		hcorpt_pbpb_cent1->SetMarkerColor(2);
		hcorpt_pbpb_cent2->SetMarkerColor(3);
		hcorpt_pbpb_cent3->SetMarkerColor(4);
		hcorpt_pbpb_cent4->SetMarkerColor(5);
		hcorpt_pbpb_cent5->SetMarkerColor(6);
		hcorpt_pbpb_cent6->SetMarkerColor(7);
		hcorpt_pbpb_cent7->SetMarkerColor(7);

	

	
	    TCanvas *c2 = new TCanvas("c2","");
			
		hcorpt_pbpb_cent1->Draw();
		hcorpt_pbpb_cent2->Draw("same");
		hcorpt_pbpb_cent3->Draw("same");
		hcorpt_pbpb_cent4->Draw("same");
		hcorpt_pbpb_cent5->Draw("same");
		hcorpt_pbpb_cent6->Draw("same");
		hcorpt_pbpb_cent7->Draw("same");

	
		
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
	
			
	    		
	TCanvas *c3 = new TCanvas("c3","");

	hdN_dpt_cor_pbpb1->SetMarkerStyle(20);
	hdN_dpt_cor_pbpb1->SetMarkerSize(0.8);
	hdN_dpt_cor_pbpb1->SetMarkerColor(2);
	hdN_dpt_cor_pbpb1->Draw("");
	
	hdN_dpt_cor_pbpb2->SetMarkerStyle(20);
	hdN_dpt_cor_pbpb2->SetMarkerSize(0.8);
	hdN_dpt_cor_pbpb2->SetMarkerColor(3);
	hdN_dpt_cor_pbpb2->Draw("same");
	
	hdN_dpt_cor_pbpb3->SetMarkerStyle(20);
	hdN_dpt_cor_pbpb3->SetMarkerSize(0.8);
	hdN_dpt_cor_pbpb3->SetMarkerColor(4);
	hdN_dpt_cor_pbpb3->Draw("same");
	
	hdN_dpt_cor_pbpb4->SetMarkerStyle(20);
	hdN_dpt_cor_pbpb4->SetMarkerSize(0.8);
	hdN_dpt_cor_pbpb4->SetMarkerColor(5);
	hdN_dpt_cor_pbpb4->Draw("same");
	
	hdN_dpt_cor_pbpb5->SetMarkerStyle(20);
	hdN_dpt_cor_pbpb5->SetMarkerSize(0.8);
	hdN_dpt_cor_pbpb5->SetMarkerColor(6);
	hdN_dpt_cor_pbpb5->Draw("same");
	
	hdN_dpt_cor_pbpb6->SetMarkerStyle(20);
	hdN_dpt_cor_pbpb6->SetMarkerSize(0.8);
	hdN_dpt_cor_pbpb6->SetMarkerColor(7);
	hdN_dpt_cor_pbpb6->Draw("same");
	
	hdN_dpt_cor_pbpb7->SetMarkerStyle(20);
	hdN_dpt_cor_pbpb7->SetMarkerSize(0.8);
	hdN_dpt_cor_pbpb7->SetMarkerColor(8);
	hdN_dpt_cor_pbpb7->Draw("same");
	
	
			
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
	
		TLine * line = new TLine(0,1,50,1);
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
	
		TLine * line = new TLine(0,1,50,1);
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
	
		TLine * line = new TLine(0,1,50,1);
		line->Draw("same");
	
	RCP_pbpb_Spectra->Write();
	RCP_pbpb_Spectra->Close();
		
		}
		