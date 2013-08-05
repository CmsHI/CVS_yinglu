{

	const int NBINS=20;
	Double_t BOUNDARIES[NBINS] = {100,110,120,130,140,150,160,170,180,190,200,220,230,250,270,290,300,330,360,400};

	//const int NBINS=9;
	//Double_t BOUNDARIES[NBINS] = {100,110,120,130,150,180,200,300,400};
	///////// INPUT PbPb DATA FILE
	
	
	
	 TFile *f = new TFile("RAA_JetSpecta_ak3_Data_June_06.root");

	
		TH1F* hMeas_cent1=(TH1F*)f->Get("hnorm_pbpb_cent1"); 
		TH1F* hMeas_cent2=(TH1F*)f->Get("hnorm_pbpb_cent2"); 
		TH1F* hMeas_cent3=(TH1F*)f->Get("hnorm_pbpb_cent3"); 
		TH1F* hMeas_cent4=(TH1F*)f->Get("hnorm_pbpb_cent4"); 
		TH1F* hMeas_cent5=(TH1F*)f->Get("hnorm_pbpb_cent5"); 
		TH1F* hMeas_cent6=(TH1F*)f->Get("hnorm_pbpb_cent6");
		TH1F* hMeas_pp=(TH1F*)f->Get("hnorm_pp");
		
		
		TH1F* hMeas_RAA_cent1=(TH1F*)f->Get("hRAA_cent1"); 
		TH1F* hMeas_RAA_cent2=(TH1F*)f->Get("hRAA_cent2"); 
		TH1F* hMeas_RAA_cent3=(TH1F*)f->Get("hRAA_cent3"); 
		TH1F* hMeas_RAA_cent4=(TH1F*)f->Get("hRAA_cent4"); 
		TH1F* hMeas_RAA_cent5=(TH1F*)f->Get("hRAA_cent5"); 
		TH1F* hMeas_RAA_cent6=(TH1F*)f->Get("hRAA_cent6");
		

	
	///////// INPUT UNFOLDED SPECTRA
	
	  TFile *g = new TFile("pbpb_Unfo.root");
	  
	  TFile *j = new TFile("pp_ak3_BinBin_June_07.root");
		TH1F* hReco_pp=(TH1F*)j->Get("hnorm_pp"); 

		
		TH1F* hReco_cent1=(TH1F*)g->Get("hnorm_pbpb_cent1"); 
		TH1F* hReco_cent2=(TH1F*)g->Get("hnorm_pbpb_cent2"); 
		TH1F* hReco_cent3=(TH1F*)g->Get("hnorm_pbpb_cent3"); 
		TH1F* hReco_cent4=(TH1F*)g->Get("hnorm_pbpb_cent4"); 
		TH1F* hReco_cent5=(TH1F*)g->Get("hnorm_pbpb_cent5"); 
		TH1F* hReco_cent6=(TH1F*)g->Get("hnorm_pbpb_cent6");
		
		TH1F* hRAA_cent1=(TH1F*)g->Get("hRAA_cent1"); 
		TH1F* hRAA_cent2=(TH1F*)g->Get("hRAA_cent2"); 
		TH1F* hRAA_cent3=(TH1F*)g->Get("hRAA_cent3"); 
		TH1F* hRAA_cent4=(TH1F*)g->Get("hRAA_cent4"); 
		TH1F* hRAA_cent5=(TH1F*)g->Get("hRAA_cent5"); 
		TH1F* hRAA_cent6=(TH1F*)g->Get("hRAA_cent6");
		
	/*
	/////// Scaling 
	hReco_cent1->Scale(625);
	hReco_cent2->Scale(125);
	hReco_cent3->Scale(25);
	hReco_cent4->Scale(5);
	
	hMeas_cent1->Scale(625);
	hMeas_cent2->Scale(125);
	hMeas_cent3->Scale(25);
	hMeas_cent4->Scale(5);
	
	
	TCanvas *c2 = new TCanvas("c2","c2",600,500);
	
	
	TH2F *htmp3 = new TH2F("htmp3","",NBINS-1, BOUNDARIES, 100, 10e-12, 10e-4);
	htmp3->SetXTitle("Jet p_{T}(GeV/c)");
	htmp3->SetYTitle("1/N dN_{jets}/dp_{T}");
	htmp3->Draw();
	gPad->SetLogy();
	
	hReco_cent1->SetMarkerColor(kBlue);
	hReco_cent1->SetMarkerStyle(20);
	hReco_cent1->SetLineColor(kBlue);
	hReco_cent1->Draw("SAME");
	hMeas_cent1->SetMarkerColor(kBlue);
	hMeas_cent1->SetMarkerStyle(24);
	hMeas_cent1->SetLineColor(kBlue);
	hMeas_cent1->Draw("SAME");
	
	hReco_cent2->SetMarkerColor(kViolet+6);
	hReco_cent2->SetMarkerStyle(21);
	hReco_cent2->SetLineColor(kViolet+6);
	hReco_cent2->Draw("SAME");
	hMeas_cent2->SetMarkerColor(kViolet+6);
	hMeas_cent2->SetMarkerStyle(25);
	hMeas_cent2->SetLineColor(kViolet+6);
	hMeas_cent2->Draw("SAME");
	
	hReco_cent3->SetMarkerColor(kYellow+3);
	hReco_cent3->SetMarkerStyle(23);
	hReco_cent3->SetLineColor(kYellow+3);
	hReco_cent3->Draw("SAME");
	hMeas_cent3->SetMarkerColor(kYellow+3);
	hMeas_cent3->SetMarkerStyle(32);
	hMeas_cent3->SetLineColor(kYellow+3);
	hMeas_cent3->Draw("SAME");
	
	hReco_cent4->SetMarkerColor(kYellow+1);
	hReco_cent4->SetMarkerStyle(29);
	hReco_cent4->SetLineColor(kYellow+1);
	hReco_cent4->Draw("SAME");
	hMeas_cent4->SetMarkerColor(kYellow+1);
	hMeas_cent4->SetMarkerStyle(30);
	hMeas_cent4->SetLineColor(kYellow+1);
	hMeas_cent4->Draw("SAME");
	
	hReco_cent5->SetMarkerColor(kRed+2);
	hReco_cent5->SetMarkerStyle(33);
	hReco_cent5->SetLineColor(kRed+2);
	hReco_cent5->Draw("SAME");
	hMeas_cent5->SetMarkerColor(kRed+2);
	hMeas_cent5->SetMarkerStyle(27);
	hMeas_cent5->SetLineColor(kRed+2);
	hMeas_cent5->Draw("SAME");
	
	hReco_cent6->SetMarkerColor(kRed+1);
	hReco_cent6->SetMarkerStyle(34);
	hReco_cent6->SetLineColor(kRed+1);
	hReco_cent6->Draw("SAME");
	hMeas_cent6->SetMarkerColor(kRed+1);
	hMeas_cent6->SetMarkerStyle(28);
	hMeas_cent6->SetLineColor(kRed+1);
	hMeas_cent6->Draw("SAME");
	
	hReco_pp->SetMarkerColor(kBlack);
	hReco_pp->SetMarkerStyle(22);
	hReco_pp->SetLineColor(kBlack);
	hReco_pp->Draw("SAME");
	hMeas_pp->SetMarkerColor(kBlack);
	hMeas_pp->SetMarkerStyle(26);
	hMeas_pp->SetLineColor(kBlack);
	hMeas_pp->Draw("SAME");
	
	TLegend *tleg = new TLegend(0.45, 0.65, 0.60, 0.95);
	tleg->SetBorderSize(0);
	tleg->SetFillStyle(0);
	tleg->SetTextFont(42);
	tleg->SetTextSize(0.04);
	tleg->SetHeader("Unfolded");
	tleg->AddEntry(hReco_cent1," 0-5% ","pl");
	tleg->AddEntry(hReco_cent2," 5-10%","pl");
	tleg->AddEntry(hReco_cent3," 10-30%","pl");
	tleg->AddEntry(hReco_cent4," 30-50%","pl");
	tleg->AddEntry(hReco_cent5," 50-70% ","pl");
	tleg->AddEntry(hReco_cent6," 70-90% ","pl");
	tleg->AddEntry(hReco_pp," pp  ","pl");
	
	tleg->Draw("same");
	
	TLegend *tleg_ = new TLegend(0.65, 0.65, 0.80, 0.95);
	tleg_->SetBorderSize(0);
	tleg_->SetFillStyle(0);
	tleg_->SetTextFont(42);
	tleg_->SetTextSize(0.04);
	tleg_->SetHeader("Measured");
	tleg_->AddEntry(hMeas_cent1," 0-5% ","pl");
	tleg_->AddEntry(hMeas_cent2," 5-10% ","pl");
	tleg_->AddEntry(hMeas_cent3," 10-30% ","pl");
	tleg_->AddEntry(hMeas_cent4," 30-50%  ","pl");
	tleg_->AddEntry(hMeas_cent5," 50-70%  ","pl");
	tleg_->AddEntry(hMeas_cent6," 70-90%  ","pl");
	tleg_->AddEntry(hMeas_pp,"   pp    ","pl");
	
	tleg_->Draw("same");
	*/
	
	
	
	TCanvas *c1 = new TCanvas("c1","c1",900,600);
	c1->Divide(3,2,0,0);
	c1->cd(6);
	
	TH2F *htmp3 = new TH2F("htmp3","",NBINS-1, BOUNDARIES, 100,10e-13, 10e-6);
	htmp3->SetXTitle("Jet p_{T}(GeV/c)");
	htmp3->SetYTitle("1/N dN_{jets}/dp_{T}");
	htmp3->Draw();
	gPad->SetLogy();
	
	hMeas_cent1->SetMarkerStyle(24);
	hReco_cent1->Draw("SAME");
	hMeas_cent1->Draw("SAME");
	
	TLegend *tleg = new TLegend(0.45, 0.65, 0.60, 0.95);
	tleg->SetBorderSize(0);
	tleg->SetFillStyle(0);
	tleg->SetTextFont(42);
	tleg->SetTextSize(0.04);
	tleg->AddEntry(hReco_cent1," Unfolded 0-5% ","pl");
	tleg->AddEntry(hMeas_cent1," Measured 0-5% ","pl");
	tleg->Draw("same");
	
	c1->cd(5);
	
	TH2F *htmp3 = new TH2F("htmp3","",NBINS-1, BOUNDARIES, 100, 10e-13, 10e-6);
	htmp3->SetXTitle("Jet p_{T}(GeV/c)");
	htmp3->SetYTitle("1/N dN_{jets}/dp_{T}");
	htmp3->Draw();
	gPad->SetLogy();
	
	hMeas_cent2->SetMarkerStyle(24);
	hReco_cent2->Draw("SAME");
	hMeas_cent2->Draw("SAME");
	
	TLegend *tleg = new TLegend(0.45, 0.65, 0.60, 0.95);
	tleg->SetBorderSize(0);
	tleg->SetFillStyle(0);
	tleg->SetTextFont(42);
	tleg->SetTextSize(0.04);
	tleg->AddEntry(hReco_cent2," Unfolded 5-10% ","pl");
	tleg->AddEntry(hMeas_cent2," Measured 5-10% ","pl");
	tleg->Draw("same");
	
	
	c1->cd(4);
	TH2F *htmp3 = new TH2F("htmp3","",NBINS-1, BOUNDARIES, 100, 10e-13, 10e-6);
	htmp3->SetXTitle("Jet p_{T}(GeV/c)");
	htmp3->SetYTitle("1/N dN_{jets}/dp_{T}");
	htmp3->Draw();
	gPad->SetLogy();
	
	hMeas_cent3->SetMarkerStyle(24);
	hReco_cent3->Draw("SAME");
	hMeas_cent3->Draw("SAME");
	
	TLegend *tleg = new TLegend(0.45, 0.65, 0.60, 0.95);
	tleg->SetBorderSize(0);
	tleg->SetFillStyle(0);
	tleg->SetTextFont(42);
	tleg->SetTextSize(0.04);
	tleg->AddEntry(hReco_cent3," Unfolded 10-30% ","pl");
	tleg->AddEntry(hMeas_cent3," Measured 10-30% ","pl");
	tleg->Draw("same");
	
	c1->cd(3);
	TH2F *htmp3 = new TH2F("htmp3","",NBINS-1, BOUNDARIES, 100, 10e-13, 10e-6);
	htmp3->SetXTitle("Jet p_{T}(GeV/c)");
	htmp3->SetYTitle("1/N dN_{jets}/dp_{T}");
	htmp3->Draw();
	gPad->SetLogy();
	
	hMeas_cent4->SetMarkerStyle(24);
	hReco_cent4->Draw("SAME");
	hMeas_cent4->Draw("SAME");
	
	TLegend *tleg = new TLegend(0.45, 0.65, 0.60, 0.95);
	tleg->SetBorderSize(0);
	tleg->SetFillStyle(0);
	tleg->SetTextFont(42);
	tleg->SetTextSize(0.04);
	tleg->AddEntry(hReco_cent4," Unfolded 30-50% ","pl");
	tleg->AddEntry(hMeas_cent4," Measured 30-50% ","pl");
	tleg->Draw("same");
	
	c1->cd(2);
	TH2F *htmp3 = new TH2F("htmp3","",NBINS-1, BOUNDARIES, 100, 10e-13,10e-6);
	htmp3->SetXTitle("Jet p_{T}(GeV/c)");
	htmp3->SetYTitle("1/N dN_{jets}/dp_{T}");
	htmp3->Draw();
	gPad->SetLogy();
	
	hMeas_cent5->SetMarkerStyle(24);
	hReco_cent5->Draw("SAME");
	hMeas_cent5->Draw("SAME");
	
	TLegend *tleg = new TLegend(0.45, 0.65, 0.60, 0.95);
	tleg->SetBorderSize(0);
	tleg->SetFillStyle(0);
	tleg->SetTextFont(42);
	tleg->SetTextSize(0.04);
	tleg->AddEntry(hReco_cent5," Unfolded 50-70% ","pl");
	tleg->AddEntry(hMeas_cent5," Measured 50-70% ","pl");
	tleg->Draw("same");
	
	c1->cd(1);
	TH2F *htmp3 = new TH2F("htmp3","",NBINS-1, BOUNDARIES, 100,10e-13, 10e-6);
	htmp3->SetXTitle("Jet p_{T}(GeV/c)");
	htmp3->SetYTitle("1/N dN_{jets}/dp_{T}");
	htmp3->Draw();
	gPad->SetLogy();
	
	hMeas_cent6->SetMarkerStyle(24);
	hReco_cent6->Draw("SAME");
	hMeas_cent6->Draw("SAME");
	
	TLegend *tleg = new TLegend(0.45, 0.65, 0.60, 0.95);
	tleg->SetBorderSize(0);
	tleg->SetFillStyle(0);
	tleg->SetTextFont(42);
	tleg->SetTextSize(0.04);
	tleg->AddEntry(hReco_cent6," Unfolded 70-90% ","pl");
	tleg->AddEntry(hMeas_cent6," Measured 70-90% ","pl");
	tleg->Draw("same");
	
	

   c1->Print("Unfoled_PbPb_JetSpectra_June_10.pdf");
   	


	TCanvas *c0 = new TCanvas("c0","");
	gPad->SetLogy();
	
	TH2F *htmp3 = new TH2F("htmp3","",NBINS-1, BOUNDARIES, 100,hMeas_pp->GetMinimum()*0.8, hMeas_pp->GetMaximum()*1.2);
	htmp3->SetXTitle("Jet p_{T}(GeV/c)");
	htmp3->SetYTitle("1/N dN_{jets}/dp_{T}");
	htmp3->Draw();

	hReco_pp->SetMarkerColor(kBlack);
	hReco_pp->SetMarkerStyle(22);
	hReco_pp->SetLineColor(kBlack);
	hReco_pp->Draw("SAME");
	hMeas_pp->SetMarkerColor(kBlack);
	hMeas_pp->SetMarkerStyle(26);
	hMeas_pp->SetLineColor(kBlack);
	hMeas_pp->Draw("SAME");
	
	
	TLegend *tleg = new TLegend(0.65, 0.65, 0.85, 0.85);
	tleg->SetBorderSize(0);
	tleg->SetFillStyle(0);
	tleg->SetTextFont(42);
	tleg->SetTextSize(0.04);
	tleg->AddEntry(hReco_pp," Unfolded pp ","pl");
	tleg->AddEntry(hMeas_pp," Measured pp ","pl");
	tleg->Draw("same");
	
	c0->Print("Unfoled_pp_JetSpectra_June_10.pdf");
}


