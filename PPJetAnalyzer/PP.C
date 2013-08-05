#define PP_cxx
#include "PP.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TNtuple.h"

void PP::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L PP.C
//      Root > PP t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
	
	
 // book histogram of pt, eta, phi:
	
	//TFile *pp_ntuple1 = new TFile("pp_ntuple1.root","RECREATE");
	
	
	TH1F *hcorpt_leading =  new TH1F("hcorpt_leading","pT Distribution of corrected leading jets",50,0,1000);
	TH1F *hcoreta_leading =  new TH1F("hcoreta_leading","Eta Distribution of corrected leading jets",50,-6,+6);
	TH2F *hcor_etavspt_leading= new TH2F("hcor_etavspt_leading","eta vs pt for corrected leading jets",50,-6,+6,50,0,1000);
	
	TH1F *hrawpt_leading =  new TH1F("hrawpt_leading","pT Distribution of raw leading jets",50,0,1000);
	TH1F *hraweta_leading =  new TH1F("hraweta_leading","Eta Distribution of raw leading jets",50,-6,+6);
	TH2F *hraw_etavspt_leading= new TH2F("hraw_etavspt_leading","eta vs pt for raw leading jets",50,-6,+6,50,0,1000);
	
	//TH1F *hjet20pt =  new TH1F("hjet20pt","hjet20pt",50,0,1000);
	//TH1F *hjet40pt =  new TH1F("hjet40pt","hjet40pt",50,0,1000);
	//TH1F *hjet60pt =  new TH1F("hjet60pt","hjet60pt",50,0,1000);
	TH1F* hdN_dpt_cor = new TH1F("hdN_dpt_cor","",50,0,1000);
	TH1F* hdN_dpt_raw = new TH1F("hdN_dpt_raw","",50,0,1000);
	//TH1D* hdN_dpt_HLT=(TH1D*)hdN_dpt_raw->Clone("hdN_dpt_HLT");
	//TH1D* hdN_dpt_jet20=(TH1D*)hjet20pt->Clone("hdN_dpt_jet20");
	//TH1D* hdN_dpt_jet40=(TH1D*)hjet40pt->Clone("hdN_dpt_jet40");
	//TH1D* hdN_dpt_jet60=(TH1D*)hjet60pt->Clone("hdN_dpt_jet60");
	
	
	hcorpt_leading->Sumw2();
	hrawpt_leading->Sumw2();
	hdN_dpt_cor->Sumw2();
	hdN_dpt_raw->Sumw2();


   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
	
/*	//Only read certain branches

	fChain->SetBranchStatus("*",0);  // disable all branches
	fChain->SetBranchStatus("CaloJet_rawpt",1);  // activate branchname
	fChain->SetBranchStatus("CaloJet_corpt",1);  // activate branchname
	fChain->SetBranchStatus("CaloJet_coreta",1);  // activate branchname
	fChain->SetBranchStatus("CaloJet_raweta",1);  // activate branchname

*/
	
	cout<<"entries"<<nentries<<endl;

   Long64_t nbytes = 0, nb = 0;
	
	  //  Event Loop start
	
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
       if(jentry%1000==0) cout<<"entries"<<jentry<<endl;
	   Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);
	   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	   
	  
	   
  // Fill the Min Bias histograms pt eta , First Corrected, Then Raw
	   
	   
	   hcorpt_leading->Fill(CaloJet_corpt[0]);
	   hcoreta_leading->Fill(CaloJet_coreta[0]);
	   hcor_etavspt_leading->Fill(CaloJet_coreta[0],CaloJet_corpt[0]);
	   
	   
	   
	   hrawpt_leading->Fill(CaloJet_rawpt[0]);
	   hraweta_leading->Fill(CaloJet_raweta[0]);
	   hraw_etavspt_leading->Fill(CaloJet_raweta[0],CaloJet_rawpt[0]);
	
	   	   
	  /*   const int NBINS=24;
	   Double_t BOUNDARIES[NBINS] = {5,15,18,25,28,35,38,48,55,61,70,80,90,100,120,140,180,200,300,400,600,740,800,1000};
	   
	   	   
	    //Book pT spectra for corrected and raw jets
	   
	   TH1D* hdN_dpt_cor=(TH1D*)hcorpt_leading->Clone("hdN_dpt_cor");

	   
	    // compute the differential yield (bin content/bin width)
		for(int i=1; i<=hdN_dpt_cor->GetNbinsX(); i++) {
		   double width=hdN_dpt_cor->GetBinWidth(i);
		   double dN_dpt_cor=hcorpt_leading->GetBinContent(i)/width;
		   double err_cor=sqrt(hcorpt_leading->GetBinContent(i))/width;
		   hdN_dpt_cor->SetBinContent(i, dN_dpt_cor);
		   hdN_dpt_cor->SetBinError(i, err_cor);
		
		}
	   

	   
       TH1D* hdN_dpt_raw=(TH1D*)hrawpt_leading->Clone("hdN_dpt_raw");
	   
	    // compute the differential yield (bin content/bin width)
	   for(int i=1; i<=hdN_dpt_raw->GetNbinsX(); i++) {
		   double width=hdN_dpt_raw->GetBinWidth(i);
		   double dN_dpt_raw=hrawpt_leading->GetBinContent(i)/width;
		   double err_raw=sqrt(hrawpt_leading->GetBinContent(i))/width;
		   hdN_dpt_raw->SetBinContent(i, dN_dpt_raw);
		   hdN_dpt_raw->SetBinError(i, err_raw);
		   
	   }
	   

	   
	    // Book and fill various HLT histrograms
	   
	     TH1D* hdN_dpt_HLT=(TH1D*)hdN_dpt_raw->Clone("hdN_dpt_HLT");
	  
	   if(HLT_Jet20_v1_fired>0) continue;
	   hjet20pt->Fill(CaloJet_rawpt[0]);
	   
	   TH1D* hdN_dpt_jet20=(TH1D*)hjet20pt->Clone("hdN_dpt_jet20");
	   	   for(int i=1; i<=hdN_dpt_jet20->GetNbinsX(); i++) {
		   double width=hdN_dpt_jet20->GetBinWidth(i);
		   double dN_dpt_jet20=hjet20pt->GetBinContent(i)/width;
		   double err_jet20=sqrt(hjet20pt->GetBinContent(i))/width;
		   hdN_dpt_jet20->SetBinContent(i, dN_dpt_jet20);
		   hdN_dpt_jet20->SetBinError(i, err_jet20);
		   } 
	   
	   if(HLT_Jet40_v1_fired>0) continue;
	   hjet40pt->Fill(CaloJet_rawpt[0]);
			   TH1D* hdN_dpt_jet40=(TH1D*)hjet40pt->Clone("hdN_dpt_jet40");
			   for(int i=1; i<=hdN_dpt_jet40->GetNbinsX(); i++) {
				   double width=hdN_dpt_jet40->GetBinWidth(i);
				   double dN_dpt_jet40=hjet40pt->GetBinContent(i)/width;
				   double err_jet40=sqrt(hjet40pt->GetBinContent(i))/width;
				   hdN_dpt_jet40->SetBinContent(i, dN_dpt_jet40);
				   hdN_dpt_jet40->SetBinError(i, err_jet40);
			   }
	   
	   if(HLT_Jet60_v1_fired>0) continue;
	   hjet60pt->Fill(CaloJet_rawpt[0]);
				 TH1D* hdN_dpt_jet60=(TH1D*)hjet60pt->Clone("hdN_dpt_jet60");
				   for(int i=1; i<=hdN_dpt_jet60->GetNbinsX(); i++) {
					   double width=hdN_dpt_jet60->GetBinWidth(i);
					   double dN_dpt_jet60=hjet60pt->GetBinContent(i)/width;
					   double err_jet60=sqrt(hjet60pt->GetBinContent(i))/width;
					   hdN_dpt_jet60->SetBinContent(i, dN_dpt_jet60);
					   hdN_dpt_jet60->SetBinError(i, err_jet60);
				   }
	   
	   
	   

	   
	   TNtuple *nt = new TNtuple("nt","","corpt:coreta:rawpt:raweta:lumi:run:event:HLT20:HLT40:HLT60");

	   // Fill mini-ntuple
	   Float_t var[10];
	   var[0]=CaloJet_corpt[0];
	   var[1]=CaloJet_coreta[0];
	   var[2]=CaloJet_rawpt[0];
	   var[3]=CaloJet_raweta[0];
	   var[4]=Lumi;
	   var[5]=Run;
	   var[6]=Event;
	   var[7]=HLT_Jet20_v1_fired;
	   var[8]=HLT_Jet40_v1_fired;
	   var[9]=HLT_Jet60_v1_fired;
	   nt->Fill(var);
	   */
	   
   }  //Event Loop ends
	
	
	//****************  Normalized pT spectra for raw, corrected and various HLT jets *********************
	
	
	TH1F *hdN_dpt_cor=(TH1F*)hcorpt_leading->Clone("hdN_dpt_cor");
	hdN_dpt_cor->Scale(1/hdN_dpt_cor->Integral());
	
	TH1F *hdN_dpt_raw=(TH1F*)hrawpt_leading->Clone("hdN_dpt_raw");
	hdN_dpt_raw->Scale(1/hdN_dpt_raw->Integral());
	
	
	
	
	//Draw Histogram
	
	//Corrected Jets
	
	TCanvas *a=new TCanvas("a","a",1);
	
	hcorpt_leading->SetMarkerStyle(20);
	hcorpt_leading->SetMarkerSize(0.8);
	hcorpt_leading->Draw();
	hcorpt_leading->GetXaxis()->SetTitle("pT [GeV]");
	hcorpt_leading->GetYaxis()->SetTitle("# of Events");
	hcorpt_leading->SetTitle("# of Events vs pT For Corrected Jets");
	gPad->SetLogy();
	a->Print("# of Events vs pT For Corrected Jets.eps");
	
	
	TCanvas *b=new TCanvas("b","b",1);
	
	hcoreta_leading->SetMarkerStyle(20);
	hcoreta_leading->SetMarkerSize(0.8);
	hcoreta_leading->Draw("e");
	hcoreta_leading->GetXaxis()->SetTitle("#eta [GeV]");
	hcoreta_leading->GetYaxis()->SetTitle("# of Events");
	hcoreta_leading->SetTitle("# of Events vs #eta For Corrected Jets");
	gPad->SetLogy();
	b->Print("# of Events vs eta For Corrected Jets.eps");
	
	TCanvas *c=new TCanvas("c","c",1);

	hcor_etavspt_leading->SetMarkerStyle(20);
	hcor_etavspt_leading->SetMarkerSize(0.8);
	hcor_etavspt_leading->Draw("CONTZ");
	hcor_etavspt_leading->GetXaxis()->SetTitle("#eta [GeV]");
	hcor_etavspt_leading->GetYaxis()->SetTitle("pT");
	hcor_etavspt_leading->SetTitle("pT vs #eta For Corrected Jets");
	gPad->SetLogy();
	c->Print("pT vs eta For Corrected Jets.eps");
	
	TCanvas *d=new TCanvas("d","d",1);

	
	hdN_dpt_cor->SetMarkerStyle(20);
	hdN_dpt_cor->SetMarkerSize(0.8);
	hdN_dpt_cor->SetMarkerColor(2);
	hdN_dpt_cor->Draw();
	hdN_dpt_cor->GetXaxis()->SetTitle("pT [GeV]");
	hdN_dpt_cor->GetYaxis()->SetTitle("dN/dpT [GeV]^(-1)");
	hdN_dpt_cor->SetTitle("Corrected Jets pT spectra");
	gPad->SetLogy();
	d->Print("Corrected Jets pT spectra.eps");
	
	
	//Raw Jets
	
	TCanvas *e=new TCanvas("e","e",1);

	
	hrawpt_leading->SetMarkerStyle(20);
	hrawpt_leading->SetMarkerSize(0.8);
	hrawpt_leading->Draw();
	hrawpt_leading->GetXaxis()->SetTitle("pT [GeV]");
	hrawpt_leading->GetYaxis()->SetTitle("# of Events");
	hrawpt_leading->SetTitle("# of Events vs pT For Raw Jets");
	gPad->SetLogy();
	e->Print("# of Events vs pT For Raw Jets.eps");
	
	TCanvas *f=new TCanvas("f","f",1);

	
	hraweta_leading->SetMarkerStyle(20);
	hraweta_leading->SetMarkerSize(0.8);
	hraweta_leading->Draw("e");
	hraweta_leading->GetXaxis()->SetTitle("#eta [GeV]");
	hraweta_leading->GetYaxis()->SetTitle("# of Events");
	hraweta_leading->SetTitle("# of Events vs #eta For Raw Jets");
	gPad->SetLogy();
	f->Print("# of Events vs eta For Raw Jets.eps");
	
	TCanvas *g=new TCanvas("g","g",1);

	
	hraw_etavspt_leading->SetMarkerStyle(20);
	hraw_etavspt_leading->SetMarkerSize(0.8);
	hraw_etavspt_leading->Draw("CONTZ");
	hraw_etavspt_leading->GetXaxis()->SetTitle("#eta [GeV]");
	hraw_etavspt_leading->GetYaxis()->SetTitle("pT");
	hraw_etavspt_leading->SetTitle("pT vs #eta For Raw Jets");
	gPad->SetLogy();
	g->Print("pT vs eta For Raw Jets.eps");
	
	TCanvas *h=new TCanvas("h","h",1);

	
	hdN_dpt_raw->SetMarkerStyle(20);
	hdN_dpt_raw->SetMarkerSize(0.8);
	hdN_dpt_raw->SetMarkerColor(2);
    hdN_dpt_raw->Draw();
	hdN_dpt_raw->GetXaxis()->SetTitle("pT [GeV]");
	hdN_dpt_raw->GetYaxis()->SetTitle("dN/dpT [GeV]^(-1)");
	hdN_dpt_raw->SetTitle("Raw Jets pT spectra");
	gPad->SetLogy();
	h->Print("Raw Jets pT spectra.eps");
	
	
	/*//HLT Trigger
	TCanvas *k=new TCanvas("j","j",1);

	hdN_dpt_HLT->SetMarkerStyle(20);
	hdN_dpt_HLT->SetMarkerSize(0.8);
	hdN_dpt_HLT->Draw();
	hdN_dpt_jet20->SetMarkerStyle(20);
	hdN_dpt_jet20->SetMarkerSize(0.8);
	hdN_dpt_jet20->SetMarkerColor(2);
	hdN_dpt_jet20->Draw("same");
	hdN_dpt_jet40->SetMarkerStyle(20);
	hdN_dpt_jet40->SetMarkerSize(0.8);
	hdN_dpt_jet40->SetMarkerColor(3);
	hdN_dpt_jet40->Draw("same");
	hdN_dpt_jet60->SetMarkerStyle(20);
	hdN_dpt_jet60->SetMarkerSize(0.8);
	hdN_dpt_jet60->SetMarkerColor(4);
	hdN_dpt_jet60->Draw("same");
	hdN_dpt_HLT->GetXaxis()->SetTitle("pT [GeV]");
	hdN_dpt_HLT->GetYaxis()->SetTitle("dN/dpT [GeV]^(-1)");
	hdN_dpt_HLT->SetTitle("HLT");
	gPad->SetLogy();
	//k->Print("HLT Trigger Jets.eps");
	
	*/

	//pp_ntuple->Write();
	//pp_ntuple->Close();
} // End of void:pp function
