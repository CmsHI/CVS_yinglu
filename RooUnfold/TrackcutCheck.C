#include <iostream>
#include <stdio.h>

#include <TRandom.h>
#include <TH1F.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include "utilities.h"

using namespace std;


void TrackcutCheck(int algo=3)
{

	//gStyle->SetOptStat(11);
	
	// ================ PbPb PtBin ======================================================================
	
	
	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();
	
	
	
	// Pthat binning
	const int nbins_pthat = 8;
	Double_t boundaries_pthat[nbins_pthat+1];
	char *fileName_pthat[nbins_pthat+1];
	Double_t xsection[nbins_pthat+1];
	
	boundaries_pthat[0]=30;
	fileName_pthat[0]="/hadoop/store/user/belt/hiForest2/Pythia30_HydjetDrum_mix01_HiForest2_v19.root";   
	xsection[0]= 1.079e-02;
	
	boundaries_pthat[1]=50;
	fileName_pthat[1]="/hadoop/store/user/belt/hiForest2/Pythia50_HydjetDrum_mix01_HiForest2_v19.root";   
	xsection[1]= 1.021e-03;
	
	boundaries_pthat[2]=80;
	fileName_pthat[2]="/hadoop/store/user/belt/hiForest2/Pythia80_HydjetDrum_mix01_HiForest2_v20.root";   
	xsection[2]= 9.913e-05;
	
	boundaries_pthat[3]=120;
	fileName_pthat[3]="/hadoop/store/user/belt/hiForest2/Pythia120_HydjetDrum_mix01_HiForest2_v21_ivan.root";   
	xsection[3]= 1.128e-05;
	
	boundaries_pthat[4]=170;
	fileName_pthat[4]="/hadoop/store/user/belt/hiForest2/Pythia170_HydjetDrum_mix01_HiForest2_v19.root";   
	xsection[4]= 1.470e-06;
	
	boundaries_pthat[5]=200;
	fileName_pthat[5]="/hadoop/store/user/belt/hiForest2/Pythia200_HydjetDrum_mix01_HiForest2_v21_ivan.root";   
	xsection[5]= 5.310e-07;
	
	boundaries_pthat[6]=250;
	fileName_pthat[6]="/hadoop/store/user/belt/hiForest2/Pythia250_HydjetDrum_mix01_HiForest2_v21_ivan.root";   
	xsection[6]= 1.192e-7;
	
	boundaries_pthat[7]=300;
	fileName_pthat[7]="/hadoop/store/user/belt/hiForest2/Pythia300_HydjetDrum_mix01_HiForest2_v21_ivan.root";   
	xsection[7]= 3.176e-08;
	
	xsection[8] = 0;
	boundaries_pthat[8]=1000;
	
	
	// ================ pp PtBin ======================================================================
	const int nbinsPP_pthat = 8;
	Double_t boundariesPP_pthat[nbinsPP_pthat+1];
	char *fileNamePP_pthat[nbinsPP_pthat+1];
	Double_t xsectionPP[nbinsPP_pthat+1];
	
	boundariesPP_pthat[0]=30;
	fileNamePP_pthat[0]="/hadoop/store/user/belt/hiForest2/pp276Dijet30_merged.root";   
	xsectionPP[0]= 1.079e-02;
	
	boundariesPP_pthat[1]=50;
	fileNamePP_pthat[1]="/hadoop/store/user/belt/hiForest2/pp276Dijet50_merged.root";   
	xsectionPP[1]= 1.021e-03;
	
	boundariesPP_pthat[2]=80;
	fileNamePP_pthat[2]="/hadoop/store/user/belt/hiForest2/pp276Dijet80_merged.root";   
	xsectionPP[2]= 9.913e-05;
	
	boundariesPP_pthat[3]=120;
	fileNamePP_pthat[3]="/hadoop/store/user/belt/hiForest2/pp276Dijet120_merged.root";   
	xsectionPP[3]= 1.128e-05;
	
	boundariesPP_pthat[4]=170;
	fileNamePP_pthat[4]="/hadoop/store/user/belt/hiForest2/pp276Dijet170_merged.root";   
	xsectionPP[4]= 1.470e-06;
	
	boundariesPP_pthat[5]=200;
	fileNamePP_pthat[5]="/hadoop/store/user/belt/hiForest2/pp276Dijet200_merged.root";   
	xsectionPP[5]= 5.310e-07;
	
	boundariesPP_pthat[6]=250;
	fileNamePP_pthat[6]="/hadoop/store/user/belt/hiForest2/pp276Dijet250_merged.root";   
	xsectionPP[6]= 1.192e-7;
	
	boundariesPP_pthat[7]=300;
	fileNamePP_pthat[7]="/hadoop/store/user/belt/hiForest2/pp276Dijet300_merged.root";   
	xsectionPP[7]= 3.176e-08;
	
	xsectionPP[8] = 0;
	boundariesPP_pthat[8]=1000;
	//   boundaries_pthat[6]=10000;
	
	//*******************lumi number for the sample***************************
	float lumi=129.;
	float pplumi=212.;
   //************************************************************************
	int evtPbPb = 0;
	int evtPP = 0;
	
	//*************************************************************************
	TH1F *hMeas1           = new TH1F("SpecPbPb", "; Jet p_{T} (GeV/c); 1/N dN_{jets}/dp_{T}" ,nbins_rec,boundaries_rec);
	TH1F *hMeas2           = new TH1F("SpecPbPb", "; Jet p_{T} (GeV/c); 1/N dN_{jets}/dp_{T}",nbins_rec,boundaries_rec);
	
	TH1F *hMeasPP1         = new TH1F("SpecPP", "; Jet p_{T} (GeV/c); 1/N dN_{jets}/dp_{T}",nbins_rec,boundaries_rec);
	TH1F *hMeasPP2         = new TH1F("SpecPP","; Jet p_{T} (GeV/c); 1/N dN_{jets}/dp_{T}" ,nbins_rec,boundaries_rec);



	// Initialize reweighting functions
	
	// Vertex & centrality reweighting for PbPb
	TF1 *fVz;
	TF1* fCentralityWeight;
	
	
		fVz = new TF1("fVz","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x");
		fVz->SetParameters(7.62788e-01,-1.13228e-02,5.85199e-03,-3.04550e-04,4.43440e-05);
		fCentralityWeight = new TF1("fCentralityWeight","[0]*exp([1]+[2]*x+[3]*x*x+[4]*x*x*x)",0,40);
		fCentralityWeight->SetParameters(2.10653e-02,5.61607,-1.41493e-01,1.00586e-03,-1.32625e-04);
	
	// Vertex reweighting for pp
	TF1 *fVzPP = new TF1("fVzPP","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x");
	fVzPP->SetParameters(8.41684e-01,-2.58609e-02,4.86550e-03,-3.10581e-04,2.07918e-05);
	
   	
	
	
	// Setup jet data branches
	JetData *data[nbins_pthat]; 
	JetData *dataPP[nbins_pthat]; 
	
	for (int i=0;i<nbins_pthat;i++) data[i] = new JetData(fileName_pthat[i],Form("%sJetAnalyzer/t",algoName[algo]),Form("%sJetAnalyzer/t",algoNameGen[algo]));	
	for (int i=0;i<nbinsPP_pthat;i++) dataPP[i] = new JetData(fileNamePP_pthat[i],Form("%sJetAnalyzer/t",algoNamePP[algo]),Form("%sJetAnalyzer/t",algoNameGen[algo]));	
	
	
	TH1F *hCent = new TH1F("hCent","",nbins_cent,boundaries_cent);
	
	TCanvas *c = new TCanvas("c","",600,600);
	TH1F *hPtHat = new TH1F("hPtHat","",nbins_pthat,boundaries_pthat);
	TH1F *hPtHatRaw = new TH1F("hPtHatRaw","",nbins_pthat,boundaries_pthat);
	TH1F *hPtHatPP = new TH1F("hPtHatPP","",nbinsPP_pthat,boundariesPP_pthat);
	TH1F *hPtHatRawPP = new TH1F("hPtHatRawPP","",nbinsPP_pthat,boundariesPP_pthat);
	
		
	for (int i=0;i<nbins_pthat;i++) {
		TH1F *hPtHatTmp = new TH1F("hPtHatTmp","",nbins_pthat,boundaries_pthat);
		data[i]->tJet->Project("hPtHatTmp","pthat");
		hPtHatRaw->Add(hPtHatTmp);
		delete hPtHatTmp;
	}
	
	for (int i=0;i<nbinsPP_pthat;i++) {
		TH1F *hPtHatTmp = new TH1F("hPtHatTmp","",nbinsPP_pthat,boundariesPP_pthat);
		dataPP[i]->tJet->Project("hPtHatTmp","pthat","abs(vz)<15");
		hPtHatRawPP->Add(hPtHatTmp);
		delete hPtHatTmp;
	}
	
	
		// Fill PbPb MC   
		cout <<"Loading PbPb MC"<<endl;

		for (int i=0;i<nbins_pthat;i++) {
			if (xsection[i]==0) continue;
			for (Long64_t jentry2=0; jentry2<data[i]->tJet->GetEntries();jentry2++) {
				data[i]->tEvt->GetEntry(jentry2);
				data[i]->tJet->GetEntry(jentry2);
				data[i]->tGenJet->GetEntry(jentry2);
				int pthatBin = hPtHat->FindBin(data[i]->pthat);
				float scale = (xsection[pthatBin-1]-xsection[pthatBin])/hPtHatRaw->GetBinContent(pthatBin);
				if(fabs(data[i]->vz)>15) continue;
				double weight_pt=1;
				double weight_vz=1;
				
				weight_vz = fVz->Eval(data[i]->vz);
				
				for (int k= 0; k < data[i]->njets; k++) { 
					int subEvt=-1;
					if ( data[i]->refpt[k]  < 30. ) continue;
					if ( data[i]->jteta[k]  > 2. || data[i]->jteta[k] < -2. ) continue;
					
						for (int l= 0; l< data[i]->ngen;l++) {
						if (data[i]->refpt[k]==data[i]->genpt[l]) {
							subEvt = data[i]->gensubid[l];
							break;
						} 
					}
					if (subEvt!=0) continue;
				
						if (data[i]->jtpt[k] <100) continue;
						
					hMeas1->Fill(data[i]->jtpt[k],scale*weight_pt*weight_vz); 
					
					if ( data[i]->trackMax[k]/data[i]->jtpt[k]<0.01) continue;
					
					hMeas2->Fill(data[i]->jtpt[k],scale*weight_pt*weight_vz);  	
				}
				evtPbPb++;
			}
			
			
			
		}	
		
		cout <<"Loading PP MC"<<endl;
		
		// fill pp MC
		for (int i=0;i<nbinsPP_pthat;i++) {
			if (xsectionPP[i]==0) continue;			
			for (Long64_t jentry2=0; jentry2<dataPP[i]->tJet->GetEntries();jentry2++) {
				dataPP[i]->tEvt->GetEntry(jentry2);
				dataPP[i]->tJet->GetEntry(jentry2);
				dataPP[i]->tGenJet->GetEntry(jentry2);
				if(dataPP[i]->pthat<boundariesPP_pthat[i] || dataPP[i]->pthat>boundariesPP_pthat[i+1]) continue;
				if(dataPP[i]->bin<=28) continue;
				int pthatBin = hPtHatPP->FindBin(dataPP[i]->pthat);
				float scale = (xsectionPP[pthatBin-1]-xsectionPP[pthatBin])/hPtHatRawPP->GetBinContent(pthatBin);
				if(fabs(dataPP[i]->vz)>15) continue;
				double weight_cent=1;
				double weight_pt=1;
				double weight_vz=1;
				
				weight_vz = fVzPP->Eval(dataPP[i]->vz);
			
				for (int k= 0; k < dataPP[i]->njets; k++) { 
					if ( dataPP[i]->refpt[k]  < 30. ) continue;
					if ( dataPP[i]->jteta[k]  > 2. || dataPP[i]->jteta[k] < -2. ) continue;
					
					if (dataPP[i]->jtpt[k] <100) continue;
					
					hMeasPP1->Fill(dataPP[i]->jtpt[k],scale*weight_vz);  
					if ( dataPP[i]->trackMax[k]/dataPP[i]->jtpt[k]<0.01) continue;
					hMeasPP2->Fill(dataPP[i]->jtpt[k],scale*weight_vz);  
										
				} 
				evtPP++;
			}
			
			
		}
	
	

	
	
	TH1F *hRatio =(TH1F*)hMeas1->Clone("hRatio");
	hRatio->Divide(hMeas2);
	
	TH1F *hRatioPP =(TH1F*)hMeasPP1->Clone("hRatioPP");
	hRatioPP->Divide(hMeasPP2);
	
	cout <<"**********************************Track Cut Check Result**************************************"<<endl;
	cout << "PbPb Event =  " << evtPbPb << "    PP event =  " << evtPP  <<  endl;
	float perc1= (hMeas1->GetEntries()-hMeas2->GetEntries())/hMeas1->GetEntries();
	float perc2= (hMeasPP1->GetEntries()-hMeasPP2->GetEntries())/hMeasPP1->GetEntries();
	cout << "PbPb before track cut =  " <<hMeas1->GetEntries() << "   PbPb after track cut =    "  << hMeas2->GetEntries() << "    PP before track cut =  " << hMeasPP1->GetEntries() <<  "   PP afer track cut = "<< hMeasPP2->GetEntries() << "   PbPb removed jet percentage =  " << perc1  << "   PP removed jet percentage =  " << perc2 << endl;
	
	TCanvas *c1 = new TCanvas("c1","",900,700);
	
	TLine *line = new TLine(100,1,500,1);
	line->SetLineStyle(2);
	line->SetLineWidth(2);
	
	c1->Divide(2,2);
	c1->cd(1);
	gPad->SetLogy();
	hMeas1->SetAxisRange(100,300,"X");
	hMeas1->Draw();
	hMeas2->SetMarkerStyle(24);
	hMeas2->Draw("same");
	drawText("PbPb",0.3,0.23,25);
	
	TLegend *leg = myLegend(0.6,0.65,0.95,0.9);
			leg->AddEntry(hMeas1,"Before Track cut","pl");
			leg->AddEntry(hMeas2,"After Track cut","pl");
			leg->Draw();
			
	
	c1->cd(2);
	gPad->SetLogy();
	hMeasPP1->SetAxisRange(100,300,"X");
	hMeasPP1->Draw();
	hMeasPP2->SetMarkerStyle(24);
	hMeasPP2->Draw("same");
	drawText("pp",0.3,0.23,25);
	
	c1->cd(3);
	hRatio->GetYaxis()->SetTitle("Ratio");
	hRatio->SetAxisRange(0.8,1.5,"Y");
	hRatio->SetAxisRange(100,300,"X");
	hRatio->Draw();
	line->Draw();
	
	c1->cd(4);
	hRatioPP->GetYaxis()->SetTitle("Ratio");
	hRatioPP->SetAxisRange(0.8,1.5,"Y");
	hRatioPP->SetAxisRange(100,300,"X");
	hRatioPP->Draw();
	line->Draw();
	
	c1->Update();
    c1->SaveAs(Form("TrackCutCheck_ak%dPuPF.pdf",algo));
    c1->SaveAs(Form("TrackCutCheck_ak%dPuPF.C",algo));
    c1->SaveAs(Form("TrackCutCheck_ak%dPuPF.gif",algo));
	
	}
