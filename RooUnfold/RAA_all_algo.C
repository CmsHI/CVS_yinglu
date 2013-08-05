#include "hiForest.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TMath.h"
#include "TLegend.h"

void RAA_all_algo(int algo =2) // ic5=1;ak3=2;ak5=3;...
{	

	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();
	
		
	  const int NBINS=31;
	  Double_t BOUNDARIES[NBINS] = {100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400};
	//	const int NBINS=17;
	//	Double_t BOUNDARIES[NBINS] = {60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,250,300};
		
		float lumi=150.;
	
	HiForest *c = new HiForest("rfio:///castor/cern.ch/user/y/yinglu/hiforest_pp_276TeV_data.root","hif",1,0);
	HiForest *b = new HiForest("rfio:///castor/cern.ch/user/v/velicanu/forest/HiForestDijet_v7.root");
	

		//TFile *RAA_2011_Test = new TFile("RAA_2011_Test.root","RECREATE");
		
		
		TH1F* hcorpt_pp= new TH1F("hcorpt_pp","All jets with selection;p_{T}; 1/N dN_{Jets}/dp_{T}",NBINS-1,BOUNDARIES);

   	    TCanvas *c1 = new TCanvas("c1","");
		
	if (algo == 1)
		c->tree->Draw("icPu5.jtpt>>hcorpt_pp","hltTree.HLT_Jet60_v1 &&icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pHBHENoiseFilter","e");
		
	if (algo == 2)
		c->tree->Draw("akPu3PF.jtpt>>hcorpt_pp","hltTree.HLT_Jet60_v1&& akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2 && skim.pHBHENoiseFilter","e");
		
		
	if (algo == 3)
		c->tree->Draw("akPu5PF.jtpt>>hcorpt_pp","hltTree.HLT_Jet60_v1&& akPu5PF.jtpt>100 && abs(akPu5PF.jteta)<2 && skim.pHBHENoiseFilter","e");
		
		
		TH1F *hcorpt_pp_tmp = (TH1F*)gDirectory->Get("hcorpt_pp");
		
	
	
	// Scale by Lumi* X section -- Nevt	
	
		TH1F* hnorm_pp=(TH1F*)hcorpt_pp->Clone("hnorm_pp");
		for(int i=1; i<=hnorm_pp->GetNbinsX(); i++) {
		float width=hnorm_pp->GetBinWidth(i);
		float dN_dpt_cor_pp=hcorpt_pp->GetBinContent(i)/width/231./64./1000000; 
		float err_cor=sqrt(hcorpt_pp->GetBinContent(i))/width/231./64./1000000;
		hnorm_pp->SetBinContent(i, dN_dpt_cor_pp);
		hnorm_pp->SetBinError(i, err_cor);
		
		}
			
		
		
		TCanvas *c0 = new TCanvas("c0","");
		
		hnorm_pp->SetMarkerColor(kRed);
		hnorm_pp->SetMarkerColor(kGreen-3);
		
		hnorm_pp->SetMarkerStyle(20);
		hnorm_pp->SetMarkerStyle(20);

		hnorm_pp->Draw("");
		hnorm_pp->Draw("same");
		
		gPad->SetLogy();

		 TLegend *tleg0 = new TLegend(0.65, 0.6, 0.85, 0.85);
		 tleg0->SetBorderSize(0);
		 tleg0->SetFillStyle(0);
		 tleg0->SetTextFont(42);
		 tleg0->SetTextSize(0.04);
		 if (algo == 1)
		 tleg0->AddEntry(hnorm_pp," icpu5calo ","pl");
		 if (algo == 2)
		 tleg0->AddEntry(hnorm_pp," akpu3pf","pl");
		 if (algo == 3)
		 tleg0->AddEntry(hnorm_pp," akpu5pf","pl");
		 tleg0->Draw();		
		
		
	
		
		
		
	
    	///// HEAVY ION DATA

		// Jet spectra
		
		TH1F* hcorpt_pbpb_cent1 = new TH1F("hcorpt_pbpb_cent1","All jets with selection;Jet p_{T} (GeV/c); 1/N dN_{Jets}/dp_{T}",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent2 = new TH1F("hcorpt_pbpb_cent2","All jets with selection;Jet p_{T} (GeV/c); 1/N dN_{Jets}/dp_{T}",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent3 = new TH1F("hcorpt_pbpb_cent3","All jets with selection;Jet p_{T} (GeV/c); 1/N dN_{Jets}/dp_{T}",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent4 = new TH1F("hcorpt_pbpb_cent4","All jets with selection;Jet p_{T} (GeV/c); 1/N dN_{Jets}/dp_{T}",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent5 = new TH1F("hcorpt_pbpb_cent5","All jets with selection;Jet p_{T} (GeV/c); 1/N dN_{Jets}/dp_{T}",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent6 = new TH1F("hcorpt_pbpb_cent6","All jets with selection;Jet p_{T} (GeV/c); 1/N dN_{Jets}/dp_{T}",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_periph = new TH1F("hcorpt_pbpb_periph","All jets with selection;Jet p_{T} (GeV/c) ; 1/N dN_{Jets}/dp_{T}",NBINS-1,BOUNDARIES);
	
   		 TCanvas *c2 = new TCanvas("c2","");
		gPad->SetLogy();
	    
	    //central events as 0-10%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent1", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin<4 && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","e");
		
		if (algo == 2)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent1", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin<4 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","e");
		
		if (algo == 3)
		b->tree->Draw("akPu5PF.jtpt>>hcorpt_pbpb_cent1", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin<4 && akPu5PF.jtpt>100 && abs(akPu5PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","e");
		
		
		TH1F *hcorpt_pbpb_cent1_tmp = (TH1F*)gDirectory->Get("hcorpt_pbpb_cent1");
		
		
		
		//central events as 10-20%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent2", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>3 && evtTree.hiBin<8 && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent2", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>3 && evtTree.hiBin<8 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu5PF.jtpt>>hcorpt_pbpb_cent2", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>3 && evtTree.hiBin<8 && akPu5PF.jtpt>100 && abs(akPu5PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		
		TH1F *hcorpt_pbpb_cent2_tmp = (TH1F*)gDirectory->Get("hcorpt_pbpb_cent2");
		
		
		//central events as 20-30%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent3", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>7 && evtTree.hiBin<12 && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent3", "hltTree.HLT_HIJet80_v1 &&  evtTree.hiBin>7 && evtTree.hiBin<12  && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu5PF.jtpt>>hcorpt_pbpb_cent3", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>7 && evtTree.hiBin<12 && akPu5PF.jtpt>100 && abs(akPu5PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		
		TH1F *hcorpt_pbpb_cent3_tmp = (TH1F*)gDirectory->Get("hcorpt_pbpb_cent3");
		
		//central events as 30-50%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent4", "hltTree.HLT_HIJet80_v1 &&  evtTree.hiBin>11 && evtTree.hiBin<20  && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent4", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>11 && evtTree.hiBin<20  && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu5PF.jtpt>>hcorpt_pbpb_cent4", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>11 && evtTree.hiBin<20  && akPu5PF.jtpt>100 && abs(akPu5PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		
		TH1F *hcorpt_pbpb_cent4_tmp = (TH1F*)gDirectory->Get("hcorpt_pbpb_cent4");
		
		
		
		//central events as 50-70%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent5", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && evtTree.hiBin<28 && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent5", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && evtTree.hiBin<28  && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu5PF.jtpt>>hcorpt_pbpb_cent5", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && evtTree.hiBin<28 && akPu5PF.jtpt>100 && abs(akPu5PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		
		TH1F *hcorpt_pbpb_cent5_tmp = (TH1F*)gDirectory->Get("hcorpt_pbpb_cent5");
		
		//central events as 70-100%
	    
	    if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent6", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>27 && evtTree.hiBin<40 && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 2)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent6", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>27 && evtTree.hiBin<40 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		if (algo == 3)
		b->tree->Draw("akPu5PF.jtpt>>hcorpt_pbpb_cent6", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin>27 && evtTree.hiBin<40 && akPu5PF.jtpt>100 && abs(akPu5PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		
		TH1F *hcorpt_pbpb_cent6_tmp = (TH1F*)gDirectory->Get("hcorpt_pbpb_cent6");


		
		
		// Peripheral events as 50-100%
		if (algo == 1)
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_periph","hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		if (algo == 2)
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_periph","hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		if (algo == 3)
		b->tree->Draw("akPu5PF.jtpt>>hcorpt_pbpb_periph","hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && akPu5PF.jtpt>100 && abs(akPu5PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		
		

		
		TCanvas *c00 = new TCanvas("c00","");
		
		gPad->SetLogy();
		hcorpt_pp_tmp->SetMarkerStyle(20);
		hcorpt_pp_tmp->SetMarkerSize(0.8);
		hcorpt_pp_tmp->SetMarkerColor(kRed);
		hcorpt_pp_tmp->GetXaxis()->SetTitle("Jet E_{T} [GeV/c]");
		hcorpt_pp_tmp->GetYaxis()->SetTitle("Entries");
		hcorpt_pp_tmp->SetTitle("Inclusive Jet Spectra");
		hcorpt_pp_tmp->Draw();
		
	
				
		hcorpt_pbpb_cent1_tmp->SetMarkerStyle(20);
		hcorpt_pbpb_cent1_tmp->SetMarkerSize(0.8);
		hcorpt_pbpb_cent1_tmp->Draw("same");
		
		TLegend *tleg00 = new TLegend(0.65, 0.6, 1.00, 0.85);
		 tleg00->SetBorderSize(0);
		 tleg00->SetFillStyle(0);
		 tleg00->SetTextFont(42);
		 tleg00->AddEntry(hcorpt_pbpb_cent1_tmp," PbPb 150 #mub^{-1} ","pl");
		 tleg00->AddEntry(hcorpt_pp_tmp," pp 231 nb^{-1}","pl");
		 tleg00->SetTextSize(0.04);
		 tleg00->Draw();
		 
		TLatex *tex0 = new TLatex(100.0,0.535,"Inclusive Jets, icPu5");
		tex0->SetTextColor(1);
		tex0->SetTextFont(42);
		tex0->SetTextSize(0.04);
		tex0->Draw();
		
		TLatex *tex00 = new TLatex(100.0,0.535,"|#eta| < 2");
		tex00->SetTextColor(1);
		tex00->SetTextFont(42);
		tex00->SetTextSize(0.04);
		//tex00->Draw();
		 
		c00->Print("InclusiveJets_pT.pdf");
		
		
	
		
		
		
		
		
		// Scale by Lumi* X section -- Nevt	
		
		TH1F* hnorm_pbpb_cent1=(TH1F*)hcorpt_pbpb_cent1->Clone("hnorm_pbpb_cent1");
		for(int i=1; i<=hnorm_pbpb_cent1->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent1->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hcorpt_pbpb_cent1->GetBinContent(i)/width/lumi/7.65/1000000.; 
			float err_cor=sqrt(hcorpt_pbpb_cent1->GetBinContent(i))/width/lumi/7.65/1000000.;
			hnorm_pbpb_cent1->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent1->SetBinError(i, err_cor);
			
		}
		
	
		TH1F* hnorm_pbpb_periph=(TH1F*)hcorpt_pbpb_periph->Clone("hnorm_pbpb_periph");
		for(int i=1; i<=hnorm_pbpb_periph->GetNbinsX(); i++) {
		float width=hnorm_pbpb_periph->GetBinWidth(i);
		float dN_dpt_cor_pbpb=hcorpt_pbpb_periph->GetBinContent(i)/width/lumi/7.65/1000000.; 
		float err_cor=sqrt(hcorpt_pbpb_periph->GetBinContent(i))/width/lumi/7.65/1000000.;
		hnorm_pbpb_periph->SetBinContent(i, dN_dpt_cor_pbpb);
		hnorm_pbpb_periph->SetBinError(i, err_cor);
		
		}
	
	
	TH1F* hnorm_pbpb_cent2=(TH1F*)hcorpt_pbpb_cent2->Clone("hnorm_pbpb_cent2");
		for(int i=1; i<=hnorm_pbpb_cent2->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent2->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hcorpt_pbpb_cent2->GetBinContent(i)/width/lumi/7.65/1000000.; 
			float err_cor=sqrt(hcorpt_pbpb_cent2->GetBinContent(i))/width/lumi/7.65/1000000.;
			hnorm_pbpb_cent2->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent2->SetBinError(i, err_cor);
			
		}
		
	TH1F* hnorm_pbpb_cent3=(TH1F*)hcorpt_pbpb_cent3->Clone("hnorm_pbpb_cent3");
		for(int i=1; i<=hnorm_pbpb_cent3->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent3->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hcorpt_pbpb_cent3->GetBinContent(i)/width/lumi/7.65/1000000.; 
			float err_cor=sqrt(hcorpt_pbpb_cent3->GetBinContent(i))/width/lumi/7.65/1000000.;
			hnorm_pbpb_cent3->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent3->SetBinError(i, err_cor);
			
		}
		
	TH1F* hnorm_pbpb_cent4=(TH1F*)hcorpt_pbpb_cent4->Clone("hnorm_pbpb_cent4");
		for(int i=1; i<=hnorm_pbpb_cent4->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent4->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hcorpt_pbpb_cent4->GetBinContent(i)/width/lumi/7.65/1000000.; 
			float err_cor=sqrt(hcorpt_pbpb_cent4->GetBinContent(i))/width/lumi/7.65/1000000.;
			hnorm_pbpb_cent4->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent4->SetBinError(i, err_cor);
			
		}
		
	TH1F* hnorm_pbpb_cent5=(TH1F*)hcorpt_pbpb_cent5->Clone("hnorm_pbpb_cent5");
		for(int i=1; i<=hnorm_pbpb_cent5->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent5->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hcorpt_pbpb_cent5->GetBinContent(i)/width/lumi/7.65/1000000.; 
			float err_cor=sqrt(hcorpt_pbpb_cent5->GetBinContent(i))/width/lumi/7.65/1000000.;
			hnorm_pbpb_cent5->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent5->SetBinError(i, err_cor);
			
		}
	
	TH1F* hnorm_pbpb_cent6=(TH1F*)hcorpt_pbpb_cent6->Clone("hnorm_pbpb_cent6");
		for(int i=1; i<=hnorm_pbpb_cent6->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent6->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hcorpt_pbpb_cent6->GetBinContent(i)/width/lumi/7.65/1000000.; 
			float err_cor=sqrt(hcorpt_pbpb_cent6->GetBinContent(i))/width/lumi/7.65/1000000.;
			hnorm_pbpb_cent6->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent6->SetBinError(i, err_cor);
			
		}
		
	
		
	
	
	
		TCanvas *c3 = new TCanvas("c3","");
		
		hnorm_pbpb_cent1->SetMarkerColor(kBlue);
		hnorm_pbpb_periph->SetMarkerColor(kRed);
		hnorm_pbpb_cent1->SetMarkerSize(0.8);
		hnorm_pbpb_periph->SetMarkerSize(0.8);
		hnorm_pbpb_cent1->SetMarkerStyle(20);
		hnorm_pbpb_periph->SetMarkerStyle(20);

		hnorm_pbpb_cent1->Draw("");
		//hnorm_pbpb_periph->Draw("same");

		hnorm_pbpb_cent2->SetMarkerColor(kViolet+6);
		hnorm_pbpb_cent2->SetMarkerSize(0.8);
		hnorm_pbpb_cent2->SetMarkerStyle(20);

		hnorm_pbpb_cent2->Draw("same");
		
		hnorm_pbpb_cent3->SetMarkerColor(kYellow+3);
		hnorm_pbpb_cent3->SetMarkerSize(0.8);
		hnorm_pbpb_cent3->SetMarkerStyle(20);

		hnorm_pbpb_cent3->Draw("same");
		
		hnorm_pbpb_cent4->SetMarkerColor(kYellow+1);
		hnorm_pbpb_cent4->SetMarkerSize(0.8);
		hnorm_pbpb_cent4->SetMarkerStyle(20);

		hnorm_pbpb_cent4->Draw("same");
		
		
		hnorm_pbpb_cent5->SetMarkerColor(kRed+2);
		hnorm_pbpb_cent5->SetMarkerSize(0.8);
		hnorm_pbpb_cent5->SetMarkerStyle(20);

		hnorm_pbpb_cent5->Draw("same");
		
		hnorm_pbpb_cent6->SetMarkerColor(kRed+1);
		hnorm_pbpb_cent6->SetMarkerSize(0.8);
		hnorm_pbpb_cent6->SetMarkerStyle(20);

		hnorm_pbpb_cent6->Draw("same");
		
		


		gPad->SetLogy();
		
		
		
		 TLegend *tleg1 = new TLegend(0.65, 0.6, 0.85, 0.85);
		 tleg1->SetBorderSize(0);
		 tleg1->SetFillStyle(0);
		 tleg1->SetTextFont(42);
		 tleg1->SetTextSize(0.04);
		 tleg1->AddEntry(hnorm_pbpb_cent1," PbPb 0-10% ","pl");
		 tleg1->AddEntry(hnorm_pbpb_cent2," PbPb 10-20% ","pl");
		 tleg1->AddEntry(hnorm_pbpb_cent3," PbPb 20-30% ","pl");
		 tleg1->AddEntry(hnorm_pbpb_cent4," PbPb 30-50% ","pl");
		 tleg1->AddEntry(hnorm_pbpb_cent5," PbPb 50-70% ","pl");
		 tleg1->AddEntry(hnorm_pbpb_cent6," PbPb 70-100% ","pl");
		 //tleg1->AddEntry(hnorm_pbpb_periph," PbPb 50-100% ","pl");
		 tleg1->Draw();		 
		
		c3->Print("InclusiveJets_PbPb.pdf");
		
		TH1F* hRAA_cent1=(TH1F*)hnorm_pbpb_cent1->Clone("hRAA_cent1");
		TH1F* hRAA_periph=(TH1F*)hnorm_pbpb_periph->Clone("hRAA_periph");
		
		
		
		TH1F* hRAA_cent2=(TH1F*)hnorm_pbpb_cent2->Clone("hRAA_cent2");
		TH1F* hRAA_cent3=(TH1F*)hnorm_pbpb_cent3->Clone("hRAA_cent3");
		TH1F* hRAA_cent4=(TH1F*)hnorm_pbpb_cent4->Clone("hRAA_cent4");
		TH1F* hRAA_cent5=(TH1F*)hnorm_pbpb_cent5->Clone("hRAA_cent5");
		TH1F* hRAA_cent6=(TH1F*)hnorm_pbpb_cent6->Clone("hRAA_cent6");
		
		


		hRAA_cent1->Scale(0.0067385);     // 1/Ncoll  Ncoll is 1484 for 0-10% centrality  centrality factor *10
        hRAA_periph->Scale(0.0666666666); // 1/Ncoll  Ncoll is 30 for 50-100% centrality  centrality factor *2
		
		hRAA_cent2->Scale(0.010787487);   // 1/Ncoll  Ncoll is 927 for 10-20% centrality  centrality factor *10
		hRAA_cent3->Scale(0.017761989);   // 1/Ncoll  Ncoll is 563 for 20-30% centrality  centrality factor *10
		hRAA_cent4->Scale(0.02);          // 1/ Ncoll Ncoll is 250 for 30-50% centrality  centrality factor *10
		hRAA_cent5->Scale(0.0793650);     // 1/Ncoll  Ncoll is 63 for 50-70% centrality  centrality factor *10
		hRAA_cent6->Scale(0.375);         // 1/Ncoll  Ncoll is 8 for 70-100% centrality  centrality factor *10

		hRAA_cent2->Divide(hnorm_pp);
		hRAA_cent3->Divide(hnorm_pp);
		hRAA_cent4->Divide(hnorm_pp);
		hRAA_cent5->Divide(hnorm_pp);
		hRAA_cent6->Divide(hnorm_pp);

		
		
		//hRAA_periph->Scale(0.47619047); // 1/Ncoll  Ncoll is 7 for 70-100% centrality  centrality factor *10/3
		
		hRAA_cent1->Divide(hnorm_pp);
		hRAA_periph->Divide(hnorm_pp);
		
		
		
		
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
		hRAA_periph->SetMarkerStyle(20);
		hRAA_periph->SetMarkerSize(0.8);
		hRAA_cent1->SetMarkerColor(kBlue);
		hRAA_periph->SetMarkerColor(kRed);
		hRAA_cent1->Draw("same");
		//hRAA_periph->Draw("same");
		
		
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
		
		TLatex *tex06 = new TLatex(100.0,0.335,"           70-100%");
		tex06->SetTextColor(1);
		tex06->SetTextFont(42);
		tex06->SetTextSize(0.08);
		tex06->Draw("same");
		
		TLine * line = new TLine(100,1,400,1);
		line->SetLineStyle(3);
		line->Draw("same");
	
		
     	c4->Print("RAA__all_algo.pdf");
		 
		 
		//RAA_2011_Test->Write();
		//RAA_2011_Test->Close();
		
		}

