
#ifdef _MAKECINT_
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ class HiForest;
#pragma link C++ class Jets;

//#if !defined(__CINT__) || defined(__MAKECINT__)

#include <iostream>
#include <stdio.h>

#include "TRandom.h"
#include "TH1D.h"

#include <TROOT.h>
#include <TStyle.h>
#include "TError.h"

#include "TFile.h"
#include "TCanvas.h"

#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TH2D.h"

#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"


#include "TDirectory.h"
#include "TDirectoryFile.h"

#include "TChain.h"
#include "TGraph.h"
#include "TColor.h"


#include "/data/users/yinglu/JetRAA/CMSSW_4_4_2_patch3/src/RooUnfold-1.1.1/utilities_v2.h";
#include "/data/users/yinglu/JetRAA/CMSSW_4_4_2_patch3/src/RooUnfold-1.1.1/commonStyle_v2.h";

using namespace std;


#endif

void drawText(const char *text, float xp, float yp, int size);
void putCMSPrel(double x, double y, double size);
void drawText(const char *text, float xp, float yp, int size);
void drawText2(const char *text, float xp, float yp, int size);



void Unfolding_RAA_Plotting_June_07(int algo=1) // algo1 =akpu3 ; algo2 = icpu5
{
	
	
	
	float ptmax = 400.0;
    float ymin = 0.0001;
    float ymax = 1.7;
    
   
	
    
	///////// INPUT PbPb DATA FILE
	
	/*
	
	if (algo == 1)  TFile *f = new TFile("RAA_JetSpecta_ak3_Data_June_06.root");
	//if (algo == 2)  TFile *f = new TFile("RAA_JetSpecta_ic5_Data_June_08.root");

	
		
		TH1F* hMeas_RAA_cent1=(TH1F*)f->Get("hRAA_cent1"); 
		TH1F* hMeas_RAA_cent2=(TH1F*)f->Get("hRAA_cent2"); 
		TH1F* hMeas_RAA_cent3=(TH1F*)f->Get("hRAA_cent3"); 
		TH1F* hMeas_RAA_cent4=(TH1F*)f->Get("hRAA_cent4"); 
		TH1F* hMeas_RAA_cent5=(TH1F*)f->Get("hRAA_cent5"); 
		TH1F* hMeas_RAA_cent6=(TH1F*)f->Get("hRAA_cent6");
		
	f->Close();
	*/
	
	///////// INPUT UNFOLDED SPECTRA
	
	if (algo == 1)  TFile *g = new TFile("pbpb_Unfo.root");
	//if (algo == 2)  TFile *g = new TFile("pbpb_Unfo.root");

		
		TH1F* hRAA_cent1=(TH1F*)g->Get("hRAA_cent1"); 
		TH1F* hRAA_cent2=(TH1F*)g->Get("hRAA_cent2"); 
		TH1F* hRAA_cent3=(TH1F*)g->Get("hRAA_cent3"); 
		TH1F* hRAA_cent4=(TH1F*)g->Get("hRAA_cent4"); 
		TH1F* hRAA_cent5=(TH1F*)g->Get("hRAA_cent5"); 
		TH1F* hRAA_cent6=(TH1F*)g->Get("hRAA_cent6");
		

	
		/*
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
		hRAA_cent1->SetMarkerColor(kBlue);
		hRAA_cent1->Draw("same");
		
		hMeas_RAA_cent1->SetMarkerStyle(25);
		hMeas_RAA_cent1->SetMarkerSize(0.8);
		hMeas_RAA_cent1->SetMarkerColor(kBlue);
		hMeas_RAA_cent1->SetLineColor(kBlue);
		hMeas_RAA_cent1->Draw("same");
	
		
		
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
		
		hMeas_RAA_cent2->SetMarkerStyle(25);
		hMeas_RAA_cent2->SetMarkerSize(0.8);
		hMeas_RAA_cent2->SetMarkerColor(kViolet+6);
		hMeas_RAA_cent2->SetLineColor(kViolet+6);
		hMeas_RAA_cent2->Draw("same");
	
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
		
		hMeas_RAA_cent3->SetMarkerStyle(25);
		hMeas_RAA_cent3->SetMarkerSize(0.8);
		hMeas_RAA_cent3->SetMarkerColor(kYellow+3);
		hMeas_RAA_cent3->SetLineColor(kYellow+3);
		hMeas_RAA_cent3->Draw("same");
	
		
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
		
		hMeas_RAA_cent4->SetMarkerStyle(25);
		hMeas_RAA_cent4->SetMarkerSize(0.8);
		hMeas_RAA_cent4->SetMarkerColor(kYellow+1);
		hMeas_RAA_cent4->SetLineColor(kYellow+1);
		hMeas_RAA_cent4->Draw("same");
	
		
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
		
		hMeas_RAA_cent5->SetMarkerStyle(25);
		hMeas_RAA_cent5->SetMarkerSize(0.8);
		hMeas_RAA_cent5->SetMarkerColor(kRed+2);
		hMeas_RAA_cent5->SetLineColor(kRed+2);
		hMeas_RAA_cent5->Draw("same");
	
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
		
		hMeas_RAA_cent6->SetMarkerStyle(25);
		hMeas_RAA_cent6->SetMarkerSize(0.8);
		hMeas_RAA_cent6->SetMarkerColor(kRed+1);
		hMeas_RAA_cent6->SetLineColor(kRed+1);
		hMeas_RAA_cent6->Draw("same");
	
		TLatex *tex06 = new TLatex(100.0,0.335,"           70-100%");
		tex06->SetTextColor(1);
		tex06->SetTextFont(42);
		tex06->SetTextSize(0.08);
		tex06->Draw("same");
		
		TLine * line = new TLine(100,1,400,1);
		line->SetLineStyle(3);
		line->Draw("same");
		*/
		
		
		
		 /////setting for Charged Hadron RAA

		TCanvas *c4= new TCanvas("c4","c4",1100,770);
		 makeMultiPanelCanvasWithGap(c4,3,2,0.01,0.01,0.16,0.2,0.04,0.04); 

  		TH1D *hDum=0, *hDum_1=0, *hDum2=0, *hDum2_1=0;
  		hDum = GetDummyHist(100.0,ptmax,ymin,ymax,"Jet p_{T} (GeV/c)","R_{AA}",false);
  			
  		 hDum->GetYaxis()->SetNdivisions(610); 
  
 		 hDum->GetYaxis()->SetLabelFont(43);
 		 hDum->GetYaxis()->SetTitleFont(43);
 		 hDum->GetYaxis()->SetLabelSize(20);
  		 hDum->GetYaxis()->SetTitleSize(22);
 		 hDum->GetYaxis()->SetTitleOffset(2.6);

 		 hDum->GetXaxis()->SetLabelFont(43);
 		 hDum->GetXaxis()->SetTitleFont(43);
 		 hDum->GetXaxis()->SetLabelSize(20);
 		 hDum->GetXaxis()->SetTitleSize(22);
  		 hDum->GetXaxis()->SetTitleOffset(3.1);

  		 hDum->GetXaxis()->SetNoExponent();
  		 hDum->GetXaxis()->SetMoreLogLabels();

 		 // to show in up and down
  		 hDum->GetXaxis()->SetTitleOffset(2.4);
  		 hDum_1 = (TH1D*) hDum->Clone("hDum_1");
  		 hDum_1->SetAxisRange(0,1.2,"Y");
  		 
  		 TLine *line = new TLine(100.1,1,ptmax,1);
 		 line->SetLineStyle(2), line->SetLineWidth(2);
  		 
  		 c4->cd(1);
	     hDum->Draw("");
 		 line->Draw();
  		 drawText("70-90%",0.2,0.205,22);
 		// drawText2("T_{AA} and lumi. uncertainty",0.3,0.66,17);  
  		th1Style1(hRAA_cent6,1,20,1.2,1,1.5,1,1);    
  		//putCMSPrel(0.2,0.88,0.05);
		
		c4->cd(2);
	     hDum->Draw("");
 		 line->Draw();
  		 drawText("50-70%",0.2,0.205,22);
 		// drawText2("T_{AA} and lumi. uncertainty",0.3,0.66,17);  
  		th1Style1(hRAA_cent5,1,20,1.2,1,1.5,1,1);    
  		//putCMSPrel(0.2,0.88,0.05);
  		
  		
  		c4->cd(3);
	     hDum->Draw("");
 		 line->Draw();
  		 drawText("30-50%",0.2,0.205,22);
 		// drawText2("T_{AA} and lumi. uncertainty",0.3,0.66,17);  
  		th1Style1(hRAA_cent4,1,20,1.2,1,1.5,1,1);    
  		//putCMSPrel(0.2,0.88,0.05);
  		
  		
  		c4->cd(4);
	     hDum->Draw("");
 		 line->Draw();
  		 drawText("10-30%",0.2,0.22,22);
 		// drawText2("T_{AA} and lumi. uncertainty",0.3,0.66,17);  
  		th1Style1(hRAA_cent3,1,20,1.2,1,1.5,1,1);    
  		//putCMSPrel(0.2,0.88,0.05);
  		
  		
  		c4->cd(5);
	     hDum->Draw("");
 		 line->Draw();
  		 drawText("5-10%",0.2,0.22,22);
 		// drawText2("T_{AA} and lumi. uncertainty",0.3,0.66,17);  
  		th1Style1(hRAA_cent2,1,20,1.2,1,1.5,1,1);    
  		//putCMSPrel(0.2,0.88,0.05);
  		
  		c4->cd(6);
	     hDum->Draw("");
 		 line->Draw();
  		 drawText("0-5%",0.2,0.22,22);
 		// drawText2("T_{AA} and lumi. uncertainty",0.3,0.66,17);  
  		th1Style1(hRAA_cent1,1,20,1.2,1,1.5,1,1);    
  		//putCMSPrel(0.2,0.88,0.05);

	c4->Print("Unfolded_RAA_June_14.pdf");
	
	
}


void putCMSPrel(double x, double y, double size){
  TLatex *tex=0;
  tex = new TLatex(x,y,"CMS Preliminary");
  tex->SetTextSize(size);
  tex->SetLineWidth(2);
  tex->SetNDC();
  tex->Draw();
}
void drawText(const char *text, float xp, float yp, int size){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(63);
  tex->SetTextSize(size);
  tex->SetTextColor(kBlack);
  tex->SetLineWidth(1);
  //tex->SetTextFont(42);
  tex->SetNDC();
  tex->Draw();
}

void drawText2(const char *text, float xp, float yp, int size){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(43);
  tex->SetTextSize(size);
  tex->SetTextColor(kBlack);
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw();
}


	
		
	






