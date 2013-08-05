#define PP_cxx
#include "PP.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TNtuple.h"
#include <iostream>

using namespace std;





// Subroutine of Filling histograms

void PP::Fillhistos(int i) 
{


// Fill the histograms

//   Leading jet pt, eta , phi, EMF     
//   Subleading jet pt, eta, phi, EMF
    if(i==0){
	hcorpt_leading->Fill(CaloJet_corpt[0]);
	hcoreta_leading->Fill(CaloJet_coreta[0]);
	hcorphi_leading->Fill(CaloJet_corphi[0]);
	hcoremf_leading->Fill(CaloJet_emf[0]);
	hcor_etavsphi_leading->Fill(CaloJet_coreta[0],CaloJet_corphi[0]);}
					  
	if(i==1){					  
	hcorpt_trailing->Fill(CaloJet_corpt[1]);
	hcoreta_trailing->Fill(CaloJet_coreta[1]);
	hcorphi_trailing->Fill(CaloJet_corphi[1]);
	hcoremf_trailing->Fill(CaloJet_emf[1]);
	hcor_etavsphi_trailing->Fill(CaloJet_coreta[1],CaloJet_corphi[1]);}

  														 
		    hcorpt->Fill(CaloJet_corpt[i]);
			hcoreta->Fill(CaloJet_coreta[i]);
			hcorphi->Fill(CaloJet_corphi[i]);
			hcoremf->Fill(CaloJet_emf[i]);
			hcor_etavsphi->Fill(CaloJet_coreta[i],CaloJet_corphi[i]);
															   
														
	hcor_MET->Fill(CaloMET);
	hcor_SumET->Fill(CaloSumET);
	hcor_fMET->Fill(CaloMET/CaloSumET);
	
   }
						  
						  
// Subroutine of Filling normalized histograms						  

void PP::normhistos(){
	hdN_dpt_cor=(TH1F*)hcorpt->Clone("hdN_dpt_cor");
	hdN_dpt_cor->Scale(1/hdN_dpt_cor->Integral());						  
}	
						  
						  
						  
						  
	//cut booleans: HLT, eta, pt,JetID					  
						  
 bool PP::pass_HLT_Jet(int a){
	
	if(a==20){
	if(HLT_Jet20_v1_fired>0)
							  
		return true;
	}
	
    if(a==40){
	if(HLT_Jet40_v1_fired>0)
			
	    return true;
	}
		
	if(a==60){
	if(HLT_Jet60_v1_fired>0)
				
		return true;
		}	
		
	 return false;
	}
		
	// eta<2.6, 1.2; pt>30,50,70
  bool PP::pass_eta_pt(int i, float eta_cut, int pt_cut){
	  	  if(fabs(CaloJet_coreta[i])<eta_cut && CaloJet_corpt[i]>pt_cut){
		  
		  return true;
	  }
	
	  return false;
	}		
									  
  bool PP::pass_JetID(int i){
	  if(CaloJet_emf[i]>0.01 && CaloJet_fHPD[i]<0.98 && CaloJet_n90Hits[i]>1){
				return true;
	  }
			return false;
	}
		
  bool PP::pass_MET(){
			
	  if(CaloMET/CaloSumET<0.5){
			return true;
	  }
		  return false;
	}
		
		

	
				  

void PP::Loop()
{
	

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   
	cout<<"entries"<<nentries<<endl;

	Long64_t nbytes = 0, nb = 0;
	
	// initialize the histograms
	
	hcorpt_leading=  new TH1F("hcorpt_leading","pT Distribution of Leading jets",50,0,1000);
	hcoreta_leading =  new TH1F("hcoreta_leading","Eta Distribution of Leading jets",50,-6,+6);
	hcorphi_leading =  new TH1F("hcorphi_leading","Phi Distribution of Leading jets",50,-3.3,+3.3);
	hcoremf_leading =  new TH1F("hcoremf_leading","EMF of Leading jets",50,-2,+2);
	hcor_etavsphi_leading= new TH2F("hcor_etavsphi_leading","eta vs pt for Leading jets",50,-6,+6,50,-3.3,+3.3);
	
	hcorpt_trailing =  new TH1F("hcorpt_trailing","pT Distribution of Trailing jets",50,0,1000);
	hcoreta_trailing =  new TH1F("hcoreta_trailing","Eta Distribution of Trailing jets",50,-6,+6);
	hcorphi_trailing =  new TH1F("hcorphi_trailing","Phi Distribution of Trailing jets",50,-3.3,+3.3);
	hcoremf_trailing=  new TH1F("hcoremf_trailing","EMF of Trailing jets",50,-2,+2);
	hcor_etavsphi_trailing= new TH2F("hcor_etavsphi_trailing","eta vs pt for Trailing jets",50,-6,+6,50,-3.3,+3.3);
	
	hcorpt =  new TH1F("hcorpt","pT Distribution of All jets",50,0,1000);
	hcoreta =  new TH1F("hcoreta","Eta Distribution of All jets",50,-6,+6);
	hcorphi =  new TH1F("hcorphi","Phi Distribution of All jets",50,-3.3,+3.3);
	hcoremf =  new TH1F("hcoremf","EMF of All jets",50,-2,+2);
	hcor_etavsphi= new TH2F("hcor_etavsphi","eta vs pt for All jets",50,-6,+6,50,-3.3,+3.3);
	
	hdN_dpt_cor = new TH1F("hdN_dpt_cor","",50,0,1000);
	hcor_MET = new TH1F("hcor_MET", "",50,0,200);
	hcor_SumET = new TH1F("hcor_SumET","",50,0,1000);
	hcor_fMET = new TH1F("hcor_fMET","",50,0,1);

	
	hcorpt_leading->Sumw2();
	hcorpt_trailing->Sumw2();
	hdN_dpt_cor->Sumw2();
	hcorpt->Sumw2();
	
	
	
	//  Event Loop start
	
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
       if(jentry%1000==0) cout<<"entries"<<jentry<<endl;
	   Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);
	   nbytes += nb;
	   
	   
	  	   
		
	//No Cuts
	   for (int i=0;i<nCaloJets;i++){
		
	       
      //Cut Eta<2.6
	  // if (pass_eta_pt(i,2.6,0)) 
		 
	  //Cut Eta<2.6,HLTJet20,pT>30 
	  // if (pass_eta_pt(i,2.6,30) && pass_HLT_Jet(20)) 
			
		   
	   //Cut Eta<2.6,HLTJet20,pT>30,JetID
	//	if (pass_eta_pt(i,2.6,30) && pass_HLT_Jet(20) && pass_JetID(i)) 
			   
		  
    //Cut Eta<2.6,HLTJet20,pT>30,JetID,fraction of MET<0.5
	 //  if (pass_eta_pt(i,2.6,30) && pass_HLT_Jet(20) && pass_JetID(i) && pass_MET())
	
		
    //Cut Eta<2.6,HLTJet40,pT>50,JetID,fraction of MET<0.5
	 //  if (pass_eta_pt(i,2.6,50) && pass_HLT_Jet(40) && pass_JetID(i) && pass_MET())
		 
	 //Cut Eta<2.6,HLTJet60,pT>70,JetID,fraction of MET<0.5
	  // if (pass_eta_pt(i,2.6,70) && pass_HLT_Jet(60) && pass_JetID(i) && pass_MET())
		  		   
	//Cut Eta<1.2,HLTJet20,pT>30,JetID,fraction of MET<0.5
	 //  if (pass_eta_pt(i,1.2,30) && pass_HLT_Jet(20) && pass_JetID(i) && pass_MET())
		  
	   
		   
    //Cut Eta<1.2,HLTJet40,pT>50,JetID,fraction of MET<0.5
	   if (pass_eta_pt(i,1.2,50) && pass_HLT_Jet(40) && pass_JetID(i) && pass_MET())
		   Fillhistos(i);
	   }
	   
		  
	//Cut Eta<1.2,HLTJet60,pT>70,JetID,fraction of MET<0.5
	 //  if (pass_eta_pt(i,1.2,70) && pass_HLT_Jet(60) && pass_JetID(i) && pass_MET())
		   
	  
	
		
	   
		   
   }  //Event Loop ends
	
	

	
	normhistos();
	drawhistos();
	
	//pp_ntuple->Write();
	//pp_ntuple->Close();
} // End of void:pp function
		
		

		
//Subroutine of Draw Histogram
		
void PP::drawhistos(){
	
	
	//Leading Jets
	
	TCanvas *a=new TCanvas("a","a",1);
	
	hcorpt_leading->SetMarkerStyle(20);
	hcorpt_leading->SetMarkerSize(0.8);
	hcorpt_leading->Draw();
	hcorpt_leading->GetXaxis()->SetTitle("pT [GeV]");
	hcorpt_leading->GetYaxis()->SetTitle("# of Events");
	hcorpt_leading->SetTitle("# of Events vs pT For Leading Jets");
	gPad->SetLogy();
	a->Print("# of Events vs pT For Leading Jets.eps");
	
	
	TCanvas *b=new TCanvas("b","b",1);
	
	hcoreta_leading->SetMarkerStyle(20);
	hcoreta_leading->SetMarkerSize(0.8);
	hcoreta_leading->Draw("e");
	hcoreta_leading->GetXaxis()->SetTitle("#eta [GeV]");
	hcoreta_leading->GetYaxis()->SetTitle("# of Events");
	hcoreta_leading->SetTitle("# of Events vs #eta For Leading Jets");
	gPad->SetLogy();
	b->Print("# of Events vs eta For Leading Jets.eps");
	
	
	TCanvas *h=new TCanvas("h","h",1);
	hcorphi_leading->SetMarkerStyle(20);
	hcorphi_leading->SetMarkerSize(0.8);
	hcorphi_leading->Draw("e");
	hcorphi_leading->GetXaxis()->SetTitle("#phi");
	hcorphi_leading->GetYaxis()->SetTitle("# of Events");
	hcorphi_leading->SetTitle("# of Events vs #phi For Leading Jets");
	h->Print("Phi For Leading Jets.eps");
	
    TCanvas *k=new TCanvas("k","k",1);
	
	hcoremf_leading->SetMarkerStyle(20);
	hcoremf_leading->SetMarkerSize(0.8);
	hcoremf_leading->Draw();
	hcoremf_leading->GetXaxis()->SetTitle("emf");
	hcoremf_leading->GetYaxis()->SetTitle("# of Events");
	hcoremf_leading->SetTitle("# of Events vs EMF For Leading Jets");
	gPad->SetLogy();
	k->Print("# of Events vs emf For Leading Jets.eps");
	
	TCanvas *c=new TCanvas("c","c",1);
	
	hcor_etavsphi_leading->SetMarkerStyle(20);
	hcor_etavsphi_leading->SetMarkerSize(0.8);
	hcor_etavsphi_leading->Draw("CONTZ");
	hcor_etavsphi_leading->GetXaxis()->SetTitle("#eta ");
	hcor_etavsphi_leading->GetYaxis()->SetTitle("#phi");
	hcor_etavsphi_leading->SetTitle("#phi vs #eta For Leading Jets");
	c->Print("Phi vs eta For Leading Jets.eps");
	
	
	
	
	
	
	//Subleading Jets
	
	TCanvas *e=new TCanvas("e","e",1);
	
	hcorpt_trailing->SetMarkerStyle(20);
	hcorpt_trailing->SetMarkerSize(0.8);
	hcorpt_trailing->Draw();
	hcorpt_trailing->GetXaxis()->SetTitle("pT [GeV]");
	hcorpt_trailing->GetYaxis()->SetTitle("# of Events");
	hcorpt_trailing->SetTitle("# of Events vs pT For trailing Jets");
	gPad->SetLogy();
	e->Print("# of Events vs pT For trailing Jets.eps");
	
	
	TCanvas *f=new TCanvas("f","f",1);
	
	hcoreta_trailing->SetMarkerStyle(20);
	hcoreta_trailing->SetMarkerSize(0.8);
	hcoreta_trailing->Draw("e");
	hcoreta_trailing->GetXaxis()->SetTitle("#eta [GeV]");
	hcoreta_trailing->GetYaxis()->SetTitle("# of Events");
	hcoreta_trailing->SetTitle("# of Events vs #eta For trailing Jets");
	gPad->SetLogy();
	f->Print("# of Events vs eta For trailing Jets.eps");
	
	TCanvas *l=new TCanvas("l","l",1);
	hcorphi_trailing->SetMarkerStyle(20);
	hcorphi_trailing->SetMarkerSize(0.8);
	hcorphi_trailing->Draw("e");
	hcorphi_trailing->GetXaxis()->SetTitle("#phi");
	hcorphi_trailing->GetYaxis()->SetTitle("# of Events");
	hcorphi_trailing->SetTitle("# of Events vs #phi For trailing Jets");
	l->Print("Phi For trailing Jets.eps");
	
    TCanvas *m=new TCanvas("m","m",1);
	
	hcoremf_trailing->SetMarkerStyle(20);
	hcoremf_trailing->SetMarkerSize(0.8);
	hcoremf_trailing->Draw();
	hcoremf_trailing->GetXaxis()->SetTitle("emf");
	hcoremf_trailing->GetYaxis()->SetTitle("# of Events");
	hcoremf_trailing->SetTitle("# of Events vs EMF For trailing Jets");
	gPad->SetLogy();
	m->Print("# of Events vs emf For trailing Jets.eps");
	
	
	//All Jets
	
	TCanvas *n=new TCanvas("n","n",1);
	
	hcorpt->SetMarkerStyle(20);
	hcorpt->SetMarkerSize(0.8);
	hcorpt->Draw();
	hcorpt->GetXaxis()->SetTitle("pT [GeV]");
	hcorpt->GetYaxis()->SetTitle("# of Events");
	hcorpt->SetTitle("# of Events vs pT For All Jets");
	gPad->SetLogy();
	n->Print("# of Events vs pT For All Jets.eps");
	
	
	TCanvas *p=new TCanvas("p","p",1);
	
	hcoreta->SetMarkerStyle(20);
	hcoreta->SetMarkerSize(0.8);
	hcoreta->Draw("e");
	hcoreta->GetXaxis()->SetTitle("#eta [GeV]");
	hcoreta->GetYaxis()->SetTitle("# of Events");
	hcoreta->SetTitle("# of Events vs #eta For All Jets");
	gPad->SetLogy();
	p->Print("# of Events vs eta For All Jets.eps");
	
	
	TCanvas *r=new TCanvas("r","r",1);
	hcorphi->SetMarkerStyle(20);
	hcorphi->SetMarkerSize(0.8);
	hcorphi->Draw("e");
	hcorphi->GetXaxis()->SetTitle("#phi");
	hcorphi->GetYaxis()->SetTitle("# of Events");
	hcorphi->SetTitle("# of Events vs #phi For All Jets");
	r->Print("Phi For All Jets.eps");
	
    TCanvas *s=new TCanvas("s","s",1);
	
	hcoremf->SetMarkerStyle(20);
	hcoremf->SetMarkerSize(0.8);
	hcoremf->Draw();
	hcoremf->GetXaxis()->SetTitle("emf");
	hcoremf->GetYaxis()->SetTitle("# of Events");
	hcoremf->SetTitle("# of Events vs EMF For All Jets");
	gPad->SetLogy();
	s->Print("# of Events vs emf For All Jets.eps");
	
	TCanvas *t=new TCanvas("t","t",1);
	
	hcor_etavsphi->SetMarkerStyle(20);
	hcor_etavsphi->SetMarkerSize(0.8);
	hcor_etavsphi->Draw("CONTZ");
	hcor_etavsphi->GetXaxis()->SetTitle("#eta ");
	hcor_etavsphi->GetYaxis()->SetTitle("#phi");
	hcor_etavsphi->SetTitle("#phi vs #eta For All Jets");
	t->Print("Phi vs eta For All Jets.eps");
	
	//MET
	
	TCanvas *v=new TCanvas("v","v",1);
	
	hcor_MET->SetMarkerStyle(20);
	hcor_MET->SetMarkerSize(0.8);
	hcor_MET->Draw();
	hcor_MET->GetXaxis()->SetTitle("MET [GeV]");
	hcor_MET->GetYaxis()->SetTitle("# of Events");
	hcor_MET->SetTitle("# of Events vs MET For All Jets");
	gPad->SetLogy();
	v->Print("# of Events vs MET For All Jets.eps");
	
	TCanvas *w=new TCanvas("w","w",1);
	
	hcor_fMET->SetMarkerStyle(20);
	hcor_fMET->SetMarkerSize(0.8);
	hcor_fMET->Draw();
	hcor_fMET->GetXaxis()->SetTitle("fMET [GeV]");
	hcor_fMET->GetYaxis()->SetTitle("# of Events");
	hcor_fMET->SetTitle("# of Events vs MET/SumET For All Jets");
	gPad->SetLogy();
	w->Print("# of Events vs MET/SumET For All Jets.eps");
	
	TCanvas *y=new TCanvas("y","y",1);
	
	hcor_SumET->SetMarkerStyle(20);
	hcor_SumET->SetMarkerSize(0.8);
	hcor_SumET->Draw();
	hcor_SumET->GetXaxis()->SetTitle("SumET [GeV]");
	hcor_SumET->GetYaxis()->SetTitle("# of Events");
	hcor_SumET->SetTitle("# of Events vs SumET For All Jets");
	gPad->SetLogy();
	y->Print("# of Events vs SumET For All Jets.eps");
	
	
}	
	
	
