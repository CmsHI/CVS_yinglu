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



void RooUnfold_InclusiveJets_ppdata(int method,int algo)
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
	
	
	//const int NBINS=9;
	//Double_t BOUNDARIES[NBINS] = {100,110,120,130,150,180,200,300,400};
	//const int NBINS=31;
	//Double_t BOUNDARIES[NBINS] = {100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400};
	
	const int NBINS=31;
	Double_t BOUNDARIES[NBINS] = {100.0000000, 105.5113064,111.3263577, 117.4618943, 123.9355792, 130.7660486, 137.9729661, 145.5770790, 153.6002778, 162.0656597, 170.9975947, 180.4217960, 190.3653939, 200.8570139, 211.9268593, 223.6067977, 235.9304534, 248.9333035, 262.6527804, 277.1283798, 292.4017738, 308.5169314, 325.5202446, 343.4606625, 362.3898318, 382.3622457, 403.4354004, 425.6699613, 449.1299369, 473.8828636, 500.0000000};
		
	const int NBINS_=54;
	Double_t BOUNDARIES_[NBINS_] ={29.11541580, 30.72005556, 32.41313193, 34.19951893, 36.08435919,
38.07307877, 40.17140278, 42.38537186, 44.72135955, 47.18609068, 
49.78666069, 52.53055609, 55.42567596, 58.48035476, 61.70338627,
65.10404892, 68.69213250, 72.47796637, 76.47244913, 80.68708008,
85.13399225, 89.82598738, 94.77657273, 100.0000000, 105.5113064,
111.3263577, 117.4618943, 123.9355792, 130.7660486, 137.9729661,
145.5770790, 153.6002778, 162.0656597, 170.9975947, 180.4217960,
190.3653939, 200.8570139, 211.9268593, 223.6067977, 235.9304534,
248.9333035, 262.6527804, 277.1283798, 292.4017738, 308.5169314,
325.5202446, 343.4606625, 362.3898318, 382.3622457, 403.4354004,
425.6699613, 449.1299369, 473.8828636, 500.0000000};
		
		
///////////////////// lumi information /////////////////////////////


		
	float pplumi=231.;
	
	//float pplumi=212.;

	
//////////////////////////////////////////////////////////////////
	
	
	TH1F* hResTrue= new TH1F ("Restrue", " ResTruth",    NBINS_-1, BOUNDARIES_); //Gen
	TH1F* hResMeas= new TH1F ("Resmeas", " ResMeasured", NBINS-1, BOUNDARIES); //Reco	

    RooUnfoldResponse response (hResMeas,hResTrue);



    
     // ***************** histogram for testing sample *****************
	
	// Read data file
	
	TFile *f = new TFile("RAA_JetSpecta_ak3_Data_June_13.root");
	TH1F* hMeas=(TH1F*)f->Get("hcorpt_pp");

	


     cout<<" Read Pt hat  80 - inf "<<endl;
     
    TString inname="/mnt/hadoop/cms/store/user/mnguyen/MC_Production/pythia80/merged_hiForest.root ";
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
   

 
     Long64_t nentries = tree->GetEntries();
     Long64_t nbytes = 0, nb = 0;

     for (Long64_t jentry=0; jentry<nentries;jentry++)
     {
		
		tree->GetEntry(jentry);


              for (int i= 0; i < njets; i++)
				
			  { if ( refpt[i] ==0 || refpt[i] <0 ) continue;
				if ( jteta[i] >2|| jteta[i] <-2 ) continue;
				response.Fill(jtpt[i],refpt[i]);
				}           
		

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

RooUnfoldSvd unfold (&response, hMeas, 8);
   sprintf(chmet,"Svd unfo ");
} // OR
if(method==3)
{

RooUnfoldBinByBin unfold (&response, hMeas);
 sprintf(chmet,"BinByBin unfo");
}

   TH1F* hReco= (TH1F*) unfold.Hreco();
   
  TCanvas *c1 = new TCanvas("c1","c1",600,500);
  gPad->SetLogy();

   TLegend *tleg = new TLegend(0.65, 0.6, 0.85, 0.85);
   tleg->SetBorderSize(0);
   tleg->SetFillStyle(0);
   tleg->AddEntry(hReco," Unfo pp","pl");
   tleg->AddEntry(hMeas," Data pp  ","pl");
   
   
   
   
   /////////OutPut File
   
   
   
   TFile *pp_June_06 = new TFile("pp_June_06.root","RECREATE");
   
   TH2F *htmp3 = new TH2F("htmp3","",NBINS-1, BOUNDARIES, 100, 0., hReco->GetMaximum()*1.5);
   htmp3->SetYTitle("Entries");
   htmp3->SetXTitle("p_{T} (GeV/c)");
   htmp3->Draw();
   hReco->SetMarkerColor(kRed);
   hReco->SetMarkerStyle(21);
   hReco->Draw("SAME");
   hMeas->Draw("histSAME");
   tleg->Draw("same");
   
  
 
   
   
	// Scale by Lumi* X section -- Nevt	
	
		TH1F* hnorm_pp=(TH1F*)hReco->Clone("hnorm_pp");
		for(int i=1; i<=hnorm_pp->GetNbinsX(); i++) {
		float width=hnorm_pp->GetBinWidth(i);
		float dN_dpt_cor_pp=hReco->GetBinContent(i)/width/pplumi/64./1000000; 
		float err_cor=sqrt(hReco->GetBinContent(i))/width/pplumi/64./1000000;
		hnorm_pp->SetBinContent(i, dN_dpt_cor_pp);
		hnorm_pp->SetBinError(i, err_cor);
		
		}
	
		
		
		TCanvas *c0 = new TCanvas("c0","");
		
		hnorm_pp->SetMarkerColor(kRed);
		hnorm_pp->SetMarkerStyle(20);

		hnorm_pp->Draw("");
		
		gPad->SetLogy();
		
	pp_June_06->Write();
	pp_June_06->Close();

}

#ifndef __CINT__
int main () { RooUnfold_InclusiveJets_ppdata(); return 0; }  // Main program when run stand-alone
#endif
