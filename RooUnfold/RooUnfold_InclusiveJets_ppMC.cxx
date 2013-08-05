//=====================================================================-*-C++-*-
// File and Version Information:
//      $Id: RooUnfoldData_v1.cxx,v 1.3 2011/07/05 17:42:55 yunju Exp $
//
// Description:
//      Simple example usage of the RooUnfold package using toy MC.
//
// Authors: Tim Adye <T.J.Adye@rl.ac.uk> and Fergus Wilson <fwilson@slac.stanford.edu>
//
//==============================================================================

#if !defined(__CINT__) || defined(__MAKECINT__)

#include <iostream>
#include <stdio.h>
using std::cout;
using std::endl;

#include "TRandom.h"
#include "TH1D.h"

#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"

//#include "RooUnfoldSvd.h"
//#include "RooUnfoldBinByBin.h"

#endif

//==============================================================================
// Unfolding Ying Lu 08 07 11
//==============================================================================



void RooUnfold_InclusiveJets_ppMC(int method,int algo)
{
#ifdef __CINT__
  gSystem->Load("libRooUnfold");
#endif

 
 
cout<<" ------------         Unfolding Ying Lu 08 07 11          ----------           "<<endl;
cout<<" ==============================================================================="<<endl;

char chmet1[100]; 
if(method==1)
{

  sprintf(chmet1,"Bayes unfo");
} 
if(method==2)
{
   sprintf(chmet1,"Svd unfo ");
}
if(method==3)
{
 sprintf(chmet1,"BinByBin unfo");
}

printf("Method : %s \n",chmet1);


  cout << "==================================== TRAIN ====================================" << endl;
    
    
    TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();
	
	
	const int NBINS=17;
	Double_t BOUNDARIES[NBINS] = {60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,250,300};
	
	
	
	TH1F* hResTrue= new TH1F ("Restrue", " ResTruth",    NBINS-1, BOUNDARIES); //Gen
	TH1F* hResMeas= new TH1F ("Resmeas", " ResMeasured", NBINS-1, BOUNDARIES); //Reco
	

    RooUnfoldResponse response (hResMeas,hResTrue);



    
     // ***************** histogram for testing sample *****************
	 TH1F* hTrue= new TH1F ("true", "Test Truth",   NBINS-1, BOUNDARIES); //Gen
     TH1F* hMeas= new TH1F ("meas", "Test Measured", NBINS-1, BOUNDARIES); //Reco
	


     cout<<" Read Pt hat  80 - inf "<<endl;
     
   // TString inname="/mnt/hadoop/cms/store/user/mnguyen/MC_Production/pythia80/merged_hiForest.root ";
    TString inname="/net/hisrv0001/home/icali/hadoop/Pythia/Z2/ppDijet_merged/pp276Dijet80_merged.root";
	TFile* inf = new TFile(inname,"read");
	
	
	
     
     float jtpt[200];
     float jteta[200];
     float refpt[200];
     int njets;
     
	if (algo == 1) TTree* tree = (TTree*)inf->Get("akPu3PFJetAnalyzer/t");
	if (algo == 2) TTree* tree = (TTree*)inf->Get("icPu5JetAnalyzer/t");

	
	tree->SetBranchAddress("jtpt",jtpt);
	tree->SetBranchAddress("jteta",jteta);
	tree->SetBranchAddress("refpt",refpt);
	tree->SetBranchAddress("nref",&njets);
   

 
     Long64_t nentries = tree->GetEntriesFast();
     Long64_t nbytes = 0, nb = 0;

	cout<<nentries << endl;
	
     for (Long64_t jentry=0; jentry<nentries;jentry++)
     {
		
		tree->GetEntry(jentry);

		if(jentry%2==1)
             { for (int i= 0; i < njets; i++)
				
			  { if ( refpt[i] ==0 || refpt[i] <0 ) continue;
				if ( jtpt[i] < 80 ||jteta[i] >2 ||jteta[i] <-2  ) continue;
				response.Fill(jtpt[i],refpt[i]);
				}           
			 }
			
			else
			{
			for (int i= 0; i < njets; i++)
				{
				if ( refpt[i] ==0 || refpt[i] <0 ) continue;
				if ( jtpt[i] < 80 ||jteta[i] >2 ||jteta[i] <-2 ) continue;
				hMeas->Fill(jtpt[i]);
				hTrue->Fill(refpt[i]);
				}
			}
/*	
	
				
             for (int i= 0; i < njets; i++)
				
			  { 
				if ( jtpt[i] < 80. ||jteta[i] >2. ||jteta[i] <-2.  ) continue;
				hMeas->Fill(jtpt[i]);
				
				if ( refpt[i] <0. ) continue;
				response.Fill(jtpt[i],refpt[i]);
				hTrue->Fill(refpt[i]);
				}
			
*/
		
		
		
     }




  cout << "==================================== TEST =====================================" << endl;


  cout << "==================================== UNFOLD ===================================" << endl;

char chmet[100]; 
if(method==1)
{
  RooUnfoldBayes unfold (&response, hMeas, 4); 
  sprintf(chmet,"Bayes unfo");
}  // OR
if(method==2)
{

RooUnfoldSvd unfold (&response, hMeas, 4);
   sprintf(chmet,"Svd unfo ");
} // OR
if(method==3)
{

RooUnfoldBinByBin unfold (&response, hMeas,4);
 sprintf(chmet,"BinByBin unfo");
}

   TH1F* hReco= (TH1F*) unfold.Hreco();
   
   
   TH1F* hRatio1= (TH1F*)hReco->Clone("hRatio1");
   hRatio1->Divide(hTrue);
  
   TH1F* hRatio2= (TH1F*)hMeas->Clone("hRatio2");
   hRatio2->Divide(hTrue);
   
  TCanvas *c1 = new TCanvas("c1","c1",600,500);
  c1->Divide(1,2);
  c1->cd(1);
  gPad->SetLogy();

   TLegend *tleg = new TLegend(0.65, 0.6, 0.85, 0.85);
   tleg->SetBorderSize(0);
   tleg->SetFillStyle(0);
   tleg->SetTextFont(42);
   tleg->AddEntry(hReco," pp unfo","pl");
   tleg->AddEntry(hMeas," pp reco  ","l");
   tleg->AddEntry(hTrue," pp gen  ","pl");
   
   
 //  TFile *pp_MC_Unfo = new TFile("pp_MC_Unfo.root","RECREATE");
   
   TH2F *htmp3 = new TH2F("htmp3","",NBINS-1, BOUNDARIES, 100, 0., hReco->GetMaximum()*1.5);
   htmp3->SetYTitle("Entries");
   htmp3->SetXTitle("p_{T} (GeV/c)");
   htmp3->Draw();
   hReco->SetMarkerColor(kRed);
   hReco->SetMarkerStyle(21);
   hReco->Draw("SAME");
   hMeas->Draw("histSAME");
   hTrue->SetMarkerColor(1);
   hTrue->SetMarkerStyle(25);
   hTrue->Draw("SAME");
   tleg->Draw("same");
   
  c1->cd(2);
  
  TLegend *tleg = new TLegend(0.65, 0.6, 0.90, 0.90);
  tleg->SetBorderSize(0);
  tleg->SetFillStyle(0);
  tleg->SetTextFont(42);
  tleg->SetTextSize(0.05);
  tleg->AddEntry(hRatio1," Unfolded / Truth ","pl");
  tleg->AddEntry(hRatio2," Measured / Truth  ","pl");
  
  TH2F *htmp4 = new TH2F("htmp4","",NBINS-1, BOUNDARIES, 20, 0.6,1.5);
  htmp4->SetXTitle("p_{T} (GeV/c)");
  htmp4->SetYTitle("Ratio");
  htmp4->Draw("");
  hRatio1->SetMarkerColor(kRed);
  hRatio2->SetMarkerColor(1);
  hRatio1->Draw("esame");
  hRatio2->Draw("esame");
  tleg->Draw("same");
   
 
   
   
	// Scale by Nevt	
	
		TH1F* hnorm_pp=(TH1F*)hReco->Clone("hnorm_pp");
		for(int i=1; i<=hnorm_pp->GetNbinsX(); i++) {
		float width=hnorm_pp->GetBinWidth(i);
		float dN_dpt_cor_pp=hReco->GetBinContent(i)/width/159807; // matt's nentries is 1896300
		float err_cor=sqrt(hReco->GetBinContent(i))/width/159807;
		hnorm_pp->SetBinContent(i, dN_dpt_cor_pp);
		hnorm_pp->SetBinError(i, err_cor);
		
		}
	
		TH1F* hgen_norm_pp=(TH1F*)hTrue->Clone("hgen_norm_pp");
		for(int i=1; i<=hgen_norm_pp->GetNbinsX(); i++) {
		float width=hgen_norm_pp->GetBinWidth(i);
		float dN_dpt_cor_pp=hTrue->GetBinContent(i)/width/159807; 
		float err_cor=sqrt(hTrue->GetBinContent(i))/width/159807;
		hgen_norm_pp->SetBinContent(i, dN_dpt_cor_pp);
		hgen_norm_pp->SetBinError(i, err_cor);
		
		}
		
		TCanvas *c0 = new TCanvas("c0","");
		
		hnorm_pp->SetMarkerColor(kRed);
		hnorm_pp->SetMarkerStyle(20);

		hnorm_pp->Draw("");
		
		gPad->SetLogy();
		
	//pp_MC_Unfo->Write();
	//pp_MC_Unfo->Close();

}

#ifndef __CINT__
int main () { RooUnfold_InclusiveJets_ppdata(); return 0; }  // Main program when run stand-alone
#endif

