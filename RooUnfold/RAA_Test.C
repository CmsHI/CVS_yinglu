#include "hiForest.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TMath.h"
#include "TLegend.h"

void RAA_Test(){	

	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();
	
		//const int NBINS=7;
		//Double_t BOUNDARIES[NBINS] = {100,120,140,160,180,200,300};
	    const int NBINS=31;
	   Double_t BOUNDARIES[NBINS] = {100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400};
		
		float lumi=150.;
	
	 //   HiForest *c = new HiForest("rfio:///castor/cern.ch/user/p/pkurt/dijet/hiforest_Collision_pp_276_dijet.root","hif",1,0);
	HiForest *c = new HiForest("rfio:///castor/cern.ch/user/y/yinglu/hiforest_pp_276TeV_data.root","hif",1,0);
	HiForest *b = new HiForest("rfio:///castor/cern.ch/user/v/velicanu/forest/HiForestDijet_v7.root");
	

		TFile *RAA_2011_Test = new TFile("RAA_2011_Test.root","RECREATE");
		
		
		TH1F* hcorpt_pp_ic5= new TH1F("hcorpt_pp_ic5","All jets with selection;p_{T}; 1/N_{Minbias} dN_{jets}/dp_{T}",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pp_ak3= new TH1F("hcorpt_pp_ak3","All jets with selection;p_{T}; 1/N_{Minbias} dN_{jets}/dp_{T}",NBINS-1,BOUNDARIES);

   	    TCanvas *c1 = new TCanvas("c1","");
		
	
		c->tree->Draw("icPu5.jtpt>>hcorpt_pp_ic5","hltTree.HLT_Jet60_v1 &&icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pHBHENoiseFilter","e");
		c->tree->Draw("akPu3PF.jtpt>>hcorpt_pp_ak3","hltTree.HLT_Jet60_v1&& akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2 && skim.pHBHENoiseFilter","esame");
	
	TH1F *hcorpt_pp_ic5_tmp = (TH1F*)gDirectory->Get("hcorpt_pp_ic5");
	TH1F *hcorpt_pp_ak3_tmp = (TH1F*)gDirectory->Get("hcorpt_pp_ak3");
	
	/*
	// Scale by Lumi* X section -- Nevt	
	
		TH1F* hnorm_pp_ic5=(TH1F*)hcorpt_pp_ic5->Clone("hnorm_pp_ic5");
		for(int i=1; i<=hnorm_pp_ic5->GetNbinsX(); i++) {
		float width=hnorm_pp_ic5->GetBinWidth(i);
		float dN_dpt_cor_pp=hcorpt_pp_ic5->GetBinContent(i)/width/231./64./1000000; 
		float err_cor=sqrt(hcorpt_pp_ic5->GetBinContent(i))/width/231./64./1000000;
		hnorm_pp_ic5->SetBinContent(i, dN_dpt_cor_pp);
		hnorm_pp_ic5->SetBinError(i, err_cor);
		
		}
			
		TH1F* hnorm_pp_ak3=(TH1F*)hcorpt_pp_ak3->Clone("hnorm_pp_ak3");
		for(int i=1; i<=hnorm_pp_ak3->GetNbinsX(); i++) {
		float width=hnorm_pp_ic5->GetBinWidth(i);
		float dN_dpt_cor_pp=hcorpt_pp_ak3->GetBinContent(i)/width/231./64./1000000; 
		float err_cor=sqrt(hcorpt_pp_ak3->GetBinContent(i))/width/231./64./1000000;
		hnorm_pp_ak3->SetBinContent(i, dN_dpt_cor_pp);
		hnorm_pp_ak3->SetBinError(i, err_cor);
		
	
		}
		
		
		TCanvas *c0 = new TCanvas("c0","");
		
		hnorm_pp_ic5->SetMarkerColor(kRed);
		hnorm_pp_ak3->SetMarkerColor(kGreen-3);
		
		hnorm_pp_ic5->SetMarkerStyle(20);
		hnorm_pp_ak3->SetMarkerStyle(20);

		hnorm_pp_ic5->Draw("");
		hnorm_pp_ak3->Draw("same");
		
		gPad->SetLogy();

		 TLegend *tleg0 = new TLegend(0.65, 0.6, 0.85, 0.85);
		 tleg0->SetBorderSize(0);
		 tleg0->SetFillStyle(0);
		 tleg0->AddEntry(hnorm_pp_ic5," icpu5 ","pl");
		 tleg0->AddEntry(hnorm_pp_ak3," akpu3pf","pl");
		 tleg0->Draw();		
		*/
		
	
		
		
		
	
    	///// HEAVY ION DATA

		// Jet spectra
		
		TH1F* hcorpt_pbpb_cent1_ic5 = new TH1F("hcorpt_pbpb_cent1_ic5","All jets with selection;p_{T}; 1/N_{Minbias} dN_{jets}/dp_{T}",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_cent1_ak3 = new TH1F("hcorpt_pbpb_cent1_ak3","All jets with selection;p_{T}; 1/N_{Minbias} dN_{jets}/dp_{T}",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_periph_ic5 = new TH1F("hcorpt_pbpb_periph_ic5","All jets with selection;p_{T}; 1/N_{Minbias} dN_{jets}/dp_{T}",NBINS-1,BOUNDARIES);
		TH1F* hcorpt_pbpb_periph_ak3 = new TH1F("hcorpt_pbpb_periph_ak3","All jets with selection;p_{T}; 1/N_{Minbias} dN_{jets}/dp_{T}",NBINS-1,BOUNDARIES);
	
   		 TCanvas *c2 = new TCanvas("c2","");
		gPad->SetLogy();
	    
	    //central events as 0-10%
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_cent1_ic5", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin<4 && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","e");
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_cent1_ak3", "hltTree.HLT_HIJet80_v1 && evtTree.hiBin<4 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
	TH1F *hcorpt_pbpb_cent1_ic5_tmp = (TH1F*)gDirectory->Get("hcorpt_pbpb_cent1_ic5");
	TH1F *hcorpt_pbpb_cent1_ak3_tmp = (TH1F*)gDirectory->Get("hcorpt_pbpb_cent1_ak3");

		
		// Peripheral events as 50-100%
		b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_periph_ic5","hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && icPu5.jtpt>100 && abs(icPu5.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","e");
		b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_periph_ak3","hltTree.HLT_HIJet80_v1 && evtTree.hiBin>19 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");

		
		// peripheral events as 70-100%
		// b->tree->Draw("icPu5.jtpt>>hcorpt_pbpb_periph_ic5","hltTree.HLT_HIJet80_v1 && evtTree.hiBin>27 && icPu5.jtpt>100 && abs(icPu5.jteta)<2 && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");
		// b->tree->Draw("akPu3PF.jtpt>>hcorpt_pbpb_periph_ak3","hltTree.HLT_HIJet80_v1 && evtTree.hiBin>27 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2 && skim.pcollisionEventSelection && skim.pHBHENoiseFilter","esame");

		
		TCanvas *c00 = new TCanvas("c00","");
		
		gPad->SetLogy();
		hcorpt_pp_ic5_tmp->SetMarkerStyle(20);
		hcorpt_pp_ic5_tmp->SetMarkerSize(0.8);
		hcorpt_pp_ic5_tmp->SetMarkerColor(kRed);
		hcorpt_pp_ic5_tmp->GetXaxis()->SetTitle("Jet E_{T} [GeV/c]");
		hcorpt_pp_ic5_tmp->GetYaxis()->SetTitle("Entries");
		hcorpt_pp_ic5_tmp->SetTitle("Inclusive Jet Spectra");
		hcorpt_pp_ic5_tmp->Draw();
		
	
				
		hcorpt_pbpb_cent1_ic5_tmp->SetMarkerStyle(20);
		hcorpt_pbpb_cent1_ic5_tmp->SetMarkerSize(0.8);
		hcorpt_pbpb_cent1_ic5_tmp->Draw("same");
		
		TLegend *tleg00 = new TLegend(0.65, 0.6, 1.00, 0.85);
		 tleg00->SetBorderSize(0);
		 tleg00->SetFillStyle(0);
		 tleg00->AddEntry(hcorpt_pbpb_cent1_ic5_tmp," PbPb 150 #mub^{-1} ","pl");
		 tleg00->AddEntry(hcorpt_pp_ic5_tmp," pp 231 nb^{-1}","pl");
		 tleg00->SetTextSize(0.04);
		 tleg00->Draw();
		 
		TLatex *tex0 = new TLatex(100.0,0.535,"Inclusive Jets, icPu5");
		tex0->SetTextColor(1);
		tex0->SetTextFont(42);
		tex0->SetTextSize(0.045);
		tex0->Draw();
		
		TLatex *tex00 = new TLatex(100.0,0.535,"|#eta| < 2");
		tex00->SetTextColor(1);
		tex00->SetTextFont(42);
		tex00->SetTextSize(0.045);
		tex00->Draw();
		 
		c00->Print("InclusiveJetForYenJie_icPu5.pdf");
		
		
		TCanvas *c01 = new TCanvas("c01","");

		gPad->SetLogy();
		hcorpt_pp_ak3_tmp->SetMarkerStyle(20);
		hcorpt_pp_ak3_tmp->SetMarkerSize(0.8);
		hcorpt_pp_ak3_tmp->SetMarkerColor(kRed);
		hcorpt_pp_ak3_tmp->GetXaxis()->SetTitle("Jet E_{T} [GeV/c]");
		hcorpt_pp_ak3_tmp->GetYaxis()->SetTitle("Entries");
		hcorpt_pp_ak3_tmp->SetTitle("Inclusive Jet Spectra");
		hcorpt_pp_ak3_tmp->Draw();
		
		
		
		
		hcorpt_pbpb_cent1_ak3_tmp->SetMarkerStyle(20);
		hcorpt_pbpb_cent1_ak3_tmp->SetMarkerSize(0.8);
		hcorpt_pbpb_cent1_ak3_tmp->Draw("same");
		
		TLegend *tleg01 = new TLegend(0.65, 0.6, 1.00, 0.85);
		 tleg01->SetBorderSize(0);
		 tleg01->SetFillStyle(0);
		 tleg01->AddEntry(hcorpt_pbpb_cent1_ak3_tmp," PbPb 150 #mub^{-1}","pl");
		 tleg01->AddEntry(hcorpt_pp_ak3_tmp," pp 231 nb^{-1}","pl");
		 tleg01->SetTextSize(0.04);
		 tleg01->Draw();	
		 
	 TLatex *tex1 = new TLatex(100.0,0.535,"Inclusive Jets, akPu3PF");
		tex1->SetTextColor(1);
		tex1->SetTextFont(42);
		tex1->SetTextSize(0.045);
		tex1->Draw();
		
		 TLatex *tex11 = new TLatex(100.0,0.535,"|#eta| < 2");
		tex11->SetTextColor(1);
		tex11->SetTextFont(42);
		tex11->SetTextSize(0.045);
		tex11->Draw();
		
		c01->Print("InclusiveJetForYenJie_akPu3PF.pdf");
		
		
		
		/*
		
		// Scale by Lumi* X section -- Nevt	
		
		TH1F* hnorm_pbpb_cent1_ic5=(TH1F*)hcorpt_pbpb_cent1_ic5->Clone("hnorm_pbpb_cent1_ic5");
		for(int i=1; i<=hnorm_pbpb_cent1_ic5->GetNbinsX(); i++) {
			float width=hnorm_pbpb_cent1_ic5->GetBinWidth(i);
			float dN_dpt_cor_pbpb=hcorpt_pbpb_cent1_ic5->GetBinContent(i)/width/lumi/7.65/1000000.; 
			float err_cor=sqrt(hcorpt_pbpb_cent1_ic5->GetBinContent(i))/width/lumi/7.65/1000000.;
			hnorm_pbpb_cent1_ic5->SetBinContent(i, dN_dpt_cor_pbpb);
			hnorm_pbpb_cent1_ic5->SetBinError(i, err_cor);
			
		}
		
	
		TH1F* hnorm_pbpb_periph_ic5=(TH1F*)hcorpt_pbpb_periph_ic5->Clone("hnorm_pbpb_periph_ic5");
		for(int i=1; i<=hnorm_pbpb_periph_ic5->GetNbinsX(); i++) {
		float width=hnorm_pbpb_periph_ic5->GetBinWidth(i);
		float dN_dpt_cor_pbpb=hcorpt_pbpb_periph_ic5->GetBinContent(i)/width/lumi/7.65/1000000.; 
		float err_cor=sqrt(hcorpt_pbpb_periph_ic5->GetBinContent(i))/width/lumi/7.65/1000000.;
		hnorm_pbpb_periph_ic5->SetBinContent(i, dN_dpt_cor_pbpb);
		hnorm_pbpb_periph_ic5->SetBinError(i, err_cor);
		
		}
	
	TH1F* hnorm_pbpb_cent1_ak3=(TH1F*)hcorpt_pbpb_cent1_ak3->Clone("hnorm_pbpb_cent1_ak3");
	for(int i=1; i<=hnorm_pbpb_cent1_ak3->GetNbinsX(); i++) {
		float width=hnorm_pbpb_cent1_ak3->GetBinWidth(i);
		float dN_dpt_cor_pbpb=hcorpt_pbpb_cent1_ak3->GetBinContent(i)/width/lumi/7.65/1000000.;
		float err_cor=sqrt(hcorpt_pbpb_cent1_ak3->GetBinContent(i))/width/lumi/7.65/1000000.;
		hnorm_pbpb_cent1_ak3->SetBinContent(i, dN_dpt_cor_pbpb);
		hnorm_pbpb_cent1_ak3->SetBinError(i, err_cor);
		
		}
	
	
	TH1F* hnorm_pbpb_periph_ak3=(TH1F*)hcorpt_pbpb_periph_ak3->Clone("hnorm_pbpb_periph_ak3");
	for(int i=1; i<=hnorm_pbpb_periph_ak3->GetNbinsX(); i++) {
		float width=hnorm_pbpb_periph_ak3->GetBinWidth(i);
		float dN_dpt_cor_pbpb=hcorpt_pbpb_periph_ak3->GetBinContent(i)/width/lumi/7.65/1000000.;
		float err_cor=sqrt(hcorpt_pbpb_periph_ak3->GetBinContent(i))/width/lumi/7.65/1000000.;
		hnorm_pbpb_periph_ak3->SetBinContent(i, dN_dpt_cor_pbpb);
		hnorm_pbpb_periph_ak3->SetBinError(i, err_cor);
		
	  }		

		TCanvas *c3 = new TCanvas("c3","");
		
		hnorm_pbpb_cent1_ic5->SetMarkerColor(kBlue);
		hnorm_pbpb_cent1_ak3->SetMarkerColor(kBlue);
		hnorm_pbpb_periph_ak3->SetMarkerColor(kRed);
		hnorm_pbpb_periph_ic5->SetMarkerColor(kRed);
		
		hnorm_pbpb_cent1_ic5->SetMarkerStyle(25);
		hnorm_pbpb_cent1_ak3->SetMarkerStyle(20);
		hnorm_pbpb_periph_ak3->SetMarkerStyle(20);
		hnorm_pbpb_periph_ic5->SetMarkerStyle(25);

		hnorm_pbpb_cent1_ic5->Draw("");
		hnorm_pbpb_cent1_ak3->Draw("same");
		hnorm_pbpb_periph_ak3->Draw("same");
		hnorm_pbpb_periph_ic5->Draw("same");

		gPad->SetLogy();
		
		
		 TLegend *tleg1 = new TLegend(0.65, 0.6, 0.85, 0.85);
		 tleg1->SetBorderSize(0);
		 tleg1->SetFillStyle(0);
		 tleg1->AddEntry(hnorm_pbpb_cent1_ic5," icpu5 cent1 ","pl");
		 tleg1->AddEntry(hnorm_pbpb_cent1_ak3," akpu3pf cent1","pl");
		 tleg1->AddEntry(hnorm_pbpb_periph_ak3," akpu3pf periph","pl");
		 tleg1->AddEntry(hnorm_pbpb_periph_ic5,"icpu5 periph ","pl");
		 tleg1->Draw();		 
		
		
		
		TH1F* hRAA_cent1_ic5=(TH1F*)hnorm_pbpb_cent1_ic5->Clone("hRAA_cent1_ic5");
		TH1F* hRAA_cent1_ak3=(TH1F*)hnorm_pbpb_cent1_ak3->Clone("hRAA_cent1_ak3");
		TH1F* hRAA_periph_ak3=(TH1F*)hnorm_pbpb_periph_ak3->Clone("hRAA_periph_ak3");
		TH1F* hRAA_periph_ic5=(TH1F*)hnorm_pbpb_periph_ic5->Clone("hRAA_periph_ic5");


		hRAA_cent1_ic5->Scale(0.0067385); // 1/Ncoll  Ncoll is 1484 for 0-10% centrality  centrality factor *10
		hRAA_cent1_ak3->Scale(0.0067385); // 1/Ncoll  Ncoll is 1484 for 0-10% centrality  centrality factor *10
		
		hRAA_periph_ak3->Scale(0.0666666666); // 1/Ncoll  Ncoll is 30 for 50-100% centrality  centrality factor *2
        hRAA_periph_ic5->Scale(0.0666666666); // 1/Ncoll  Ncoll is 30 for 50-100% centrality  centrality factor *2
		
		
		//hRAA_periph_ak3->Scale(0.47619047); // 1/Ncoll  Ncoll is 7 for 70-100% centrality  centrality factor *10/3
		//hRAA_periph_ic5->Scale(0.47619047); // 1/Ncoll  Ncoll is 7 for 70-100% centrality  centrality factor *10/3
		
		hRAA_cent1_ic5->Divide(hnorm_pp_ic5);
		hRAA_cent1_ak3->Divide(hnorm_pp_ak3);
		hRAA_periph_ic5->Divide(hnorm_pp_ic5);
		hRAA_periph_ak3->Divide(hnorm_pp_ak3);
		
		c3->Print("InclusiveJets_pbpb_test.eps");
		
		
		TCanvas *c4 = new TCanvas("c4","");
		TH2F *htmp1 = new TH2F("htmp1","",NBINS-1,BOUNDARIES, 100, 0.,1.5);
		
		htmp1->GetXaxis()->SetTitle("p_{T} [GeV/c]");
		htmp1->GetYaxis()->SetTitle("R_{AA}");
		htmp1->SetTitle("R_{AA}");
		htmp1->Draw();
		hRAA_cent1_ic5->SetMarkerStyle(20);
		hRAA_cent1_ic5->SetMarkerSize(0.8);
		hRAA_periph_ic5->SetMarkerStyle(20);
		hRAA_periph_ic5->SetMarkerSize(0.8);
		hRAA_cent1_ic5->SetMarkerColor(kRed);
		hRAA_periph_ic5->SetMarkerColor(kBlue);
		hRAA_cent1_ic5->Draw("same");
		hRAA_periph_ic5->Draw("same");
		
		TLegend *tleg2 = new TLegend(0.65, 0.6, 1.00, 0.85);
		 tleg2->SetBorderSize(0);
		 tleg2->SetFillStyle(0);
		 tleg2->AddEntry(hRAA_cent1_ic5," icpu5 cent1 ","pl");
		 tleg2->AddEntry(hRAA_periph_ic5," icpu5 periph","pl");
		 tleg2->SetTextSize(0.04);
		 tleg2->Draw();	
		 
     	c4->Print("RAA_Test_ic5.eps");
		 
		TCanvas *c5 = new TCanvas("c5","");
		TH2F *htmp1 = new TH2F("htmp1","",NBINS-1,BOUNDARIES, 100, 0.,1.5);
		
		htmp1->GetXaxis()->SetTitle("p_{T} [GeV/c]");
		htmp1->GetYaxis()->SetTitle("R_{AA}");
		htmp1->SetTitle("R_{AA}");
		htmp1->Draw();
		
		hRAA_cent1_ak3->SetMarkerStyle(20);
		hRAA_cent1_ak3->SetMarkerSize(0.8);
		hRAA_periph_ak3->SetMarkerStyle(20);
		hRAA_periph_ak3->SetMarkerSize(0.8);
		hRAA_cent1_ak3->SetMarkerColor(kRed);
		hRAA_periph_ak3->SetMarkerColor(kBlue);
		hRAA_cent1_ak3->Draw("same");
		hRAA_periph_ak3->Draw("same");
		
		TLegend *tleg3 = new TLegend(0.65, 0.6, 1.00, 0.85);
		 tleg3->SetBorderSize(0);
		 tleg3->SetFillStyle(0);
		 tleg3->AddEntry(hRAA_cent1_ak3," akpu3pf cent1","pl");
		 tleg3->AddEntry(hRAA_periph_ak3," akpu3pf periph","pl");
		 tleg3->SetTextSize(0.04);
		 tleg3->Draw();	
		 
		c5->Print("RAA_Test_ak3.eps");
		 
		RAA_2011_Test->Write();
		RAA_2011_Test->Close();
		*/
		
		}

