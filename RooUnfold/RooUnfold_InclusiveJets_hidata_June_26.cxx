#include <iostream>
#include <stdio.h>

#include <TRandom.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>
#include <TCanvas.h>

#include "src/RooUnfoldResponse.h"
#include "src/RooUnfoldBayes.h"

#include "src/RooUnfoldSvd.h"
#include "src/RooUnfoldBinByBin.h"

#include "utilities.h"
using namespace std;

//==============================================================================
// Unfolding Ying Lu 08 07 11
// Update Yen-Jie Lee 06.22.12
//==============================================================================

void RooUnfold_InclusiveJets_hidata_June_26(int method,int algo,bool useSpectraFromFile=0,char *spectraFileName = "pbpbSpectra.root", int doToy = 1, int doJECSys = 1) // algo 2 =akpu2 ; 3 =akpu3 ; 4 =akpu4 ;1 = icpu5
{
   #ifdef __CINT__
      gSystem->Load("libRooUnfold");
   #endif
	
   cout<<" ------------         Unfolding Ying Lu 08 07 11          ----------           "<<endl;
   cout<<" ==============================================================================="<<endl;
	
   char chmet1[100];
   if(method==1) {
      sprintf(chmet1,"Bayes unfo");
   } else if(method==2) {
      sprintf(chmet1,"Svd unfo ");
   } else if(method==3) {
      sprintf(chmet1,"BinByBin unfo");
   }

   printf("Method : %s \n",chmet1);
	
   cout << "==================================== TRAIN ====================================" << endl;

   // ================ Bin Size ======================================================================

   // Algos, following Ying's convension
   static const int nAlgos = 8;
   static const char *algoName[nAlgos] = { "", "icPu5", "akPu2PF", "akPu3PF", "akPu4PF", "akPu2Calo", "akPu3Calo", "akPu4Calo" };

   


   // Centrality binning
   const int nbins_cent=	6;
   Double_t boundaries_cent[nbins_cent+1] = {   0,2,4,12,20,28,36   };
   Double_t ncoll[nbins_cent] = { 1660, 1310, 745, 251, 62.8, 10.8 };

   // ================ PbPb PtBin ======================================================================
   // Pthat binning
   const int nbins_pthat = 7;
   Double_t boundaries_pthat[nbins_pthat+1];
   char *fileName_pthat[nbins_pthat+1];
   Double_t xsection[nbins_pthat+1];
   
   boundaries_pthat[0]=30;
   fileName_pthat[0]="/d102/yjlee/hiForest2MC/Pythia30_HydjetDrum_mix01_HiForest2_v19.root";   
   xsection[0]= 1.079e-02;

   boundaries_pthat[1]=50;
   fileName_pthat[1]="/d102/yjlee/hiForest2MC/Pythia50_HydjetDrum_mix01_HiForest2_v19.root";   
   xsection[1]= 1.021e-03;

   boundaries_pthat[2]=80;
   fileName_pthat[2]="/d102/yjlee/hiForest2MC/Pythia80_HydjetDrum_mix01_HiForest2_v20.root";   
   xsection[2]= 9.913e-05;

   boundaries_pthat[3]=120;
   fileName_pthat[3]="/d102/yjlee/hiForest2MC/Pythia120_HydjetDrum_mix01_HiForest2_v21_ivan.root";   
   xsection[3]= 1.128e-05;

   boundaries_pthat[4]=170;
   fileName_pthat[4]="/d102/yjlee/hiForest2MC/Pythia170_HydjetDrum_mix01_HiForest2_v19.root";   
   xsection[4]= 1.470e-06;

   boundaries_pthat[5]=200;
   fileName_pthat[5]="/d102/yjlee/hiForest2MC/Pythia200_HydjetDrum_mix01_HiForest2_v21_ivan.root";   
   xsection[5]= 5.310e-07;
//   xsection[5]= 5.310e-07;

   boundaries_pthat[6]=250;
   fileName_pthat[6]="/d102/yjlee/hiForest2MC/Pythia250_HydjetDrum_mix01_HiForest2_v21_ivan.root";   
//   xsection[6]= 6.904e-08+2.447e-8;
   xsection[6]= 9.351e-8;

//   boundaries_pthat[7]=300;
//   fileName_pthat[7]="/d102/yjlee/hiForest2MC/Pythia300_HydjetDrum_mix01_HiForest2_v21_ivan.root";   
//   xsection[7]= 2.447e-08;

   xsection[7] = 0;
   boundaries_pthat[7]=10000;
//   boundaries_pthat[6]=10000;
   

   // ================ pp PtBin ======================================================================
   const int nbinsPP_pthat = 8;
   Double_t boundariesPP_pthat[nbinsPP_pthat+1];
   char *fileNamePP_pthat[nbinsPP_pthat+1];
   Double_t xsectionPP[nbinsPP_pthat+1];
   
   boundariesPP_pthat[0]=30;
   fileNamePP_pthat[0]="/d102/yjlee/hiForest2MC/pp276Dijet30_merged.root";   
   xsectionPP[0]= 1.079e-02;

   boundariesPP_pthat[1]=50;
   fileNamePP_pthat[1]="/d102/yjlee/hiForest2MC/pp276Dijet50_merged.root";   
   xsectionPP[1]= 1.021e-03;

   boundariesPP_pthat[2]=80;
   fileNamePP_pthat[2]="/d102/yjlee/hiForest2MC/pp276Dijet80_merged.root";   
   xsectionPP[2]= 9.913e-05;

   boundariesPP_pthat[3]=120;
   fileNamePP_pthat[3]="/d102/yjlee/hiForest2MC/pp276Dijet120_merged.root";   
   xsectionPP[3]= 1.128e-05;

   boundariesPP_pthat[4]=170;
   fileNamePP_pthat[4]="/d102/yjlee/hiForest2MC/pp276Dijet170_merged.root";   
   xsectionPP[4]= 1.470e-06;

   boundariesPP_pthat[5]=200;
   fileNamePP_pthat[5]="/d102/yjlee/hiForest2MC/pp276Dijet200_merged.root";   
   xsectionPP[5]= 5.310e-07;

   boundariesPP_pthat[6]=250;
   fileNamePP_pthat[6]="/d102/yjlee/hiForest2MC/pp276Dijet250_merged.root";   
   xsectionPP[6]= 9.351e-8;

   boundariesPP_pthat[7]=300;
   fileNamePP_pthat[7]="/d102/yjlee/hiForest2MC/pp276Dijet300_merged.root";   
   xsectionPP[7]= 2.447e-08;

   xsectionPP[8] = 0;
   boundariesPP_pthat[8]=10000;
//   boundaries_pthat[6]=10000;

   //*******************lumi number for the sample***************************
   float lumi=129.;
   float pplumi=212.;
   //*************************************************************************

   // Output file
   TFile *pbpb_Unfo = new TFile("pbpb_Unfo.root","RECREATE");
	
   // Histograms used by RooUnfold
   UnfoldingHistos *uhist[nbins_cent+1];
   
   // Define RooUnfold response
   RooUnfoldResponse *response[nbins_cent+1];

   // Initialize Histograms   
   
   for (int i=0;i<=nbins_cent;i++) {
      uhist[i] = new UnfoldingHistos(i);
      response[i] = new RooUnfoldResponse(uhist[i]->hResMeas,uhist[i]->hResTrue);
   }

   // Centrality reweighting function
   TF1* fCentralityWeight = new TF1("fCentralityWeight","exp(-1.0*pow(x+1.11957e+01,2)/pow(1.34120e+01,2)/2)",0,40);
 	 
   TFile *f = 0;
	
   if (algo == 1)  f = new TFile("RAA_JetSpecta_ak3_Data_Forest2_June_13.root");
   if (algo == 2)  f = new TFile("RAA_JetSpecta_ic5_Data_Forest2_June_13.root");
		
   // INPUT UNFOLDED  pp  Spectra
	
   TFile *j = new TFile("pp_bayes_ak3_Forest2_June_16.root");
   TH1F* hnorm_pp=(TH1F*)j->Get("hnorm_pp");

   // Read data file
   TFile *infData = new TFile("/d101/yjlee/hiForest2/HiForest-promptskim-hihighpt-hltjet80-pt90-v3_part.root");
   TTree *tDataEvt = (TTree*)infData->Get("hiEvtAnalyzer/HiTree");
   TTree *tDataSkim = (TTree*)infData->Get("skimanalysis/HltTree");
   TTree *tDataHlt = (TTree*)infData->Get("hltanalysis/HltTree");
   TTree *tDataJet  = (TTree*)infData->Get(Form("%sJetAnalyzer/t",algoName[algo]));
   tDataJet->AddFriend(tDataEvt);
   tDataJet->AddFriend(tDataSkim);
   tDataJet->AddFriend(tDataHlt);

   TFile *infPP = new TFile("/d102/yjlee/hiForest2PP/HiForest-ppskim-hihighpt-pt90-v1_v3_part.root");
   TTree *tPPEvt = (TTree*)infPP->Get("hiEvtAnalyzer/HiTree");
   TTree *tPPSkim = (TTree*)infPP->Get("skimanalysis/HltTree");
   TTree *tPPHlt = (TTree*)infPP->Get("hltanalysis/HltTree");
   TTree *tPPJet  = (TTree*)infPP->Get(Form("%sJetAnalyzer/t",algoName[algo]));
   tPPJet->AddFriend(tPPEvt);
   tPPJet->AddFriend(tPPSkim);
   tPPJet->AddFriend(tPPHlt);


   // Jet data branches
   JetData *data[nbins_pthat]; 
   JetData *dataPP[nbins_pthat]; 

   for (int i=0;i<nbins_pthat;i++) data[i] = new JetData(fileName_pthat[i],Form("%sJetAnalyzer/t",algoName[algo]));	
   for (int i=0;i<nbinsPP_pthat;i++) dataPP[i] = new JetData(fileNamePP_pthat[i],Form("%sJetAnalyzer/t",algoName[algo]));	

   TFile *fSpectra(0);
   
   if (useSpectraFromFile){
      fSpectra = new TFile(spectraFileName,"read");
   }

   // Come back to the output file dir
   pbpb_Unfo->cd();

   // Get Jet spectra from data file
   cout <<"Reading data..."<<endl;

   TCanvas * cInput = new TCanvas("cInput","Input",1200,800);
   cInput->Divide(3,2);
   
   for (int i=0;i<=nbins_cent;i++){
      cInput->cd(i+1)->SetLogy();
      if (useSpectraFromFile) {
         uhist[i]->hMeas = (TH1F*)fSpectra->Get(Form("hMeas%d",i));
         uhist[i]->hMeasJECSys = (TH1F*)fSpectra->Get(Form("hMeasJECSys%d",i));
	 uhist[i]->hMeasMatch = (TH1F*)((TH2F*) fSpectra->Get(Form("hMatrix_cent%d",i)))->ProjectionY();
	 uhist[i]->hMeasMatch->Divide(uhist[i]->hMeas);
      } else {
         tDataJet->Project(Form("hMeas%d",i),"jtpt",
                        Form("abs(vz[1])<15&&pcollisionEventSelection&&pHBHENoiseFilter&&abs(jteta)<2&&hiBin<%.0f&&hiBin>=%.0f",boundaries_cent[i+1],boundaries_cent[i]));
         tDataJet->Project(Form("hMeasJECSys%d",i),Form("jtpt*%f",1.+0.02/nbins_cent*(nbins_cent-i)),
                        Form("abs(vz[1])<15&&pcollisionEventSelection&&pHBHENoiseFilter&&abs(jteta)<2&&hiBin<%.0f&&hiBin>=%.0f",boundaries_cent[i+1],boundaries_cent[i]));
         uhist[i]->hMeasMatch = 0;
      }
//      TCanvas *c =new TCanvas(Form("c%d",i),Form("c%d",i),600,600);
      uhist[i]->hMeas->Draw();
   }
   
   tPPJet->Project(Form("hMeas%d",nbins_cent),"jtpt",Form("pcollisionEventSelection&&pHBHENoiseFilter&&abs(jteta)<2"));
	
	
   TH1D *hCent = new TH1D("hCent","",nbins_cent,boundaries_cent);
   TCanvas *c = new TCanvas("c","",600,600);
   TH1D *hPtHat = new TH1D("hPtHat","",nbins_truth,boundaries_truth);
   TH1D *hPtHatPP = new TH1D("hPtHatPP","",nbins_truth,boundaries_truth);
   
   RooUnfoldResponse res(uhist[0]->hResMeas,uhist[0]->hResTrue);

   // Fill PbPb MC   
   for (int i=0;i<nbins_pthat;i++) {
      float scale=(xsection[i]-xsection[i+1])/data[i]->tJet->GetEntries(Form("pthat>%.0f&&pthat<%.0f",boundaries_pthat[i],boundaries_pthat[i+1])); 
      cout <<"Loading pthat"<<boundaries_pthat[i]
           <<" sample, cross section = "<<xsection[i]
	   << Form(" pthat>%.0f&&pthat<%.0f",boundaries_pthat[i],boundaries_pthat[i+1])<<endl;
      for (Long64_t jentry2=0; jentry2<data[i]->tJet->GetEntries();jentry2++) {
         data[i]->tEvt->GetEntry(jentry2);
         data[i]->tJet->GetEntry(jentry2);
         if(data[i]->pthat<boundaries_pthat[i] || data[i]->pthat>boundaries_pthat[i+1]) continue;
	 if(fabs(data[i]->vz)>15) continue;
         int cBin = hCent->FindBin(data[i]->bin)-1;
         double weight_cent=1;
	 double weight_pt=1;
	 if (cBin>=nbins_cent) continue;
	 if (cBin==-1) continue;
	 hPtHat->Fill(data[i]->pthat,scale*weight_cent);
         weight_cent = fCentralityWeight->Eval(data[i]->bin);
	 hCent->Fill(data[i]->bin,weight_cent);
            
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
	    if (uhist[cBin]->hMeasMatch!=0) {
	       int ptBinNumber = uhist[cBin]->hMeasMatch->FindBin(data[i]->jtpt[k]);
	       int ratio = uhist[cBin]->hMeasMatch->GetBinContent(ptBinNumber);
	       if (ratio!=0) weight_pt = 1./ratio;
	    }
   	    response[cBin]->Fill(data[i]->jtpt[k],data[i]->refpt[k],scale*weight_cent*weight_pt);
            //uhist[cBin]-> hGen->Fill(data[i]->refpt[k],scale*weight_cent);   
            //uhist[cBin]-> hMeas->Fill(data[i]->jtpt[k],scale*weight_cent);  	 
            uhist[cBin]-> hMatrix->Fill(data[i]->jtpt[k],data[i]->refpt[k],scale*weight_cent*weight_pt);
         }           
      }
   }

   // fill pp MC
   for (int i=0;i<nbinsPP_pthat;i++) {
      float scale=(xsectionPP[i]-xsectionPP[i+1])/dataPP[i]->tJet->GetEntries(Form("pthat>%.0f&&pthat<%.0f",boundariesPP_pthat[i],boundariesPP_pthat[i+1])); 
      cout <<"Loading PP pthat"<<boundariesPP_pthat[i]
           <<" sample, cross section = "<<xsectionPP[i]
	   << Form(" pthat>%.0f&&pthat<%.0f",boundariesPP_pthat[i],boundariesPP_pthat[i+1])<<endl;
      for (Long64_t jentry2=0; jentry2<dataPP[i]->tJet->GetEntries();jentry2++) {
         dataPP[i]->tEvt->GetEntry(jentry2);
         dataPP[i]->tJet->GetEntry(jentry2);
         if(dataPP[i]->pthat<boundariesPP_pthat[i] || dataPP[i]->pthat>boundariesPP_pthat[i+1]) continue;
         if(dataPP[i]->bin<=28) continue;
	 if(fabs(dataPP[i]->vz)>15) continue;
         double weight_cent=1;
	 double weight_pt=1;
	 hPtHatPP->Fill(dataPP[i]->pthat,scale*weight_cent);
            
	 for (int k= 0; k < dataPP[i]->njets; k++) { 
	    int subEvt=-1;
	    if ( dataPP[i]->refpt[k]  < 30. ) continue;
   	    if ( dataPP[i]->jteta[k]  > 2. || dataPP[i]->jteta[k] < -2. ) continue;
	    for (int l= 0; l< dataPP[i]->ngen;l++) {
	       if (dataPP[i]->refpt[k]==dataPP[i]->genpt[l]) {
	          subEvt = dataPP[i]->gensubid[l];
		  break;
	       } 
	    }
	    if (subEvt!=0) continue;
	    if (uhist[nbins_cent]->hMeasMatch!=0) {
	       int ptBinNumber = uhist[nbins_cent]->hMeasMatch->FindBin(dataPP[i]->jtpt[k]);
	       int ratio = uhist[nbins_cent]->hMeasMatch->GetBinContent(ptBinNumber);
	       if (ratio!=0) weight_pt = 1./ratio;
	    }
   	    response[nbins_cent]->Fill(dataPP[i]->jtpt[k],dataPP[i]->refpt[k],scale*weight_cent*weight_pt);
            //uhist[nbins_cent]-> hGen->Fill(dataPP[i]->refpt[k],scale*weight_cent);   
            //uhist[nbins_cent]-> hMeas->Fill(dataPP[i]->jtpt[k],scale*weight_cent);  	 
            uhist[nbins_cent]-> hMatrix->Fill(dataPP[i]->jtpt[k],dataPP[i]->refpt[k],scale*weight_cent*weight_pt);
         }           
      }
   }

   TCanvas * cMatrix = new TCanvas("cMatrix","Matrix",1200,800);
   cMatrix->Divide(3,2);
   for (int i=0;i<nbins_cent;i++){
      cMatrix->cd(i+1);
      uhist[i]->hMatrix->Draw("col");
   }

   TCanvas *cPtHat = new TCanvas("cPtHat","Pt Hat",600,600);
   cPtHat->SetLogy();
   hPtHat->Draw();
   		
   cout << "==================================== TEST =====================================" << endl;
	
   cout << "==================================== UNFOLD ===================================" << endl;
	
   char chmet[100]; 
/*
   // ======================= Reconstructed PP spectra =========================================================
   RooUnfoldBayes unfold (response[nbins_cent], uhist[nbins_cent]->hMeas,2);
   uhist[nbins_cent]->hReco = (TH1F*) unfold.Hreco();
   divideBinWidth(uhist[nbins_cent]->hReco);
//   uhist[nbins_cent]->hReco->Scale(1./pplumi/64/1000000);
//   uhist[nbins_cent]->hMeas->Scale(1./pplumi/64/1000000);
   cleanup(uhist[nbins_cent]->hReco);
   uhist[nbins_cent]->hRecoRebin = rebin(uhist[nbins_cent]->hReco);
  */ 
   // ======================= Reconstructed PbPb spectra =========================================================
   TCanvas * cPbPb = new TCanvas("cPbPb","PbPb",1200,800);
   cPbPb->Divide(3,3); 
   cPbPb->cd(1);


   for (int i=0;i<=nbins_cent;i++) {
      cPbPb->cd(i+1)->SetLogy();
      RooUnfoldBayes unfold       (response[i], uhist[i]->hMeas,2);
      RooUnfoldBayes unfoldJECSys (response[i], uhist[i]->hMeasJECSys,2);
      RooUnfoldBinByBin unfold2      (response[i], uhist[i]->hMeas);
      uhist[i]->hReco         = (TH1F*) unfold.Hreco();
      uhist[i]->hRecoJECSys   = (TH1F*) unfoldJECSys.Hreco();
      uhist[i]->hRecoBinByBin = (TH1F*) unfold2.Hreco();
      //divideBinWidth(uhist[i]->hMeas);
      if (doToy) {
         TCanvas *cToy = new TCanvas("cToy","toy",600,600);
   	 int nExp=1000;
   	 TH1F *hTmp[nbins_truth+1];
   	 TH1F *hTmp2[nbins_truth+1];
   	 for (int j=1;j<=nbins_truth;j++) {
     	    hTmp[j] = new TH1F(Form("hTmp%d",j),"",100,0,10.+uhist[i]->hReco->GetBinContent(j)*2);
     	    hTmp2[j] = new TH1F(Form("hTmp2%d",j),"",100,0,10.+uhist[i]->hRecoBinByBin->GetBinContent(j)*2);
   	 }
     	 for (int exp =0; exp<nExp; exp++) {
   	    TH1F *hToy = (TH1F*)uhist[i]->hMeas->Clone();   
     	    hToy->SetName("hToy");
     	    if (exp%10==0) cout <<"Pseudo-experiment "<<exp<<endl;
     	    for (int j=1;j<=hToy->GetNbinsX();j++) {
   	       double value = gRandom->Poisson(uhist[i]->hMeas->GetBinContent(j));
     	       hToy->SetBinContent(j,value);
   	    }

     	    RooUnfoldBayes unfoldToy(response[i],hToy,2);
     	    RooUnfoldBinByBin unfoldToy2(response[i],hToy);
     	    TH1F *hRecoTmp = (TH1F*) unfoldToy.Hreco();
     	    TH1F *hRecoTmp2 = (TH1F*) unfoldToy2.Hreco();
   	    
     	    for (int j=1;j<=hRecoTmp->GetNbinsX();j++) {
     	       hTmp[j]->Fill(hRecoTmp->GetBinContent(j));
     	       hTmp2[j]->Fill(hRecoTmp2->GetBinContent(j));
     	    }
     	    delete hToy;
     	    delete hRecoTmp;
     	    delete hRecoTmp2;
     	 }
   	 TF1 *f = new TF1("f","[0]*TMath::Gaus(x,[1],[2])");
     	 for (int j=1;j<nbins_truth;j++)
     	 {
            f->SetParameters(hTmp[j]->GetMaximum(),hTmp[j]->GetMean(),hTmp[j]->GetRMS());
     	    if (hTmp[j]->GetMean()>0) {
       	       hTmp[j]->Fit("f","Q ");
       	       hTmp[j]->Fit("f","LL Q ");
//	       cToy->SaveAs(Form("toy/cent-%d-pt-%.0f.gif",i,uhist[i]->hReco->GetBinCenter(j)));
//     	       cout <<j<<" "<<f->GetParameter(2)<<endl;
     	       uhist[i]->hReco->SetBinError(j,f->GetParameter(2));
     	    }	       
            f->SetParameters(hTmp2[j]->GetMaximum(),hTmp2[j]->GetMean(),hTmp2[j]->GetRMS());
     	    if (hTmp2[j]->GetMean()>0) {
       	       hTmp2[j]->Fit("f","Q ");
       	       hTmp2[j]->Fit("f","LL Q ");
//	       cToy->SaveAs(Form("toy/cent2-%d-pt-%.0f.gif",i,uhist[i]->hReco->GetBinCenter(j)));
//     	       cout <<j<<" "<<f->GetParameter(2)<<endl;
//     	       uhist[i]->hRecoBinByBin->SetBinError(j,f->GetParameter(2));
     	    }	       
     	    delete hTmp[j];
     	    delete hTmp2[j];
     	 }
	 cPbPb->cd(i+1);
      }
      cleanup(uhist[i]->hReco);
      divideBinWidth(uhist[i]->hReco);
      divideBinWidth(uhist[i]->hRecoJECSys);
      uhist[i]->hMeas->SetMarkerStyle(24);
      uhist[i]->hMeas->Draw();    
      uhist[i]->hReco->Draw("same");    
  }	      

  // Calculate RAA
  TH1F *hRebinPP = rebin(uhist[nbins_cent]->hReco);
  hRebinPP->SetName("hRebinPP");
  TH1F *hRebinBinByBinPP = rebin(uhist[nbins_cent]->hRecoBinByBin);
  hRebinBinByBinPP->SetName("hRebinBinByBinPP");
  TH1F *hRecoPP  = (TH1F*)uhist[nbins_cent]->hReco->Clone("hRecoPP");
  TH1F *hMeasPP  = (TH1F*)uhist[nbins_cent]->hMeas->Clone("hMeasPP");
  hRebinPP         ->Scale(1./pplumi/64/1000000);
  hRecoPP          ->Scale(1./pplumi/64/1000000);
  hRebinBinByBinPP ->Scale(1./pplumi/64/1000000);
  hMeasPP          ->Scale(1./pplumi/64/1000000);
  
  TCanvas * cRAA = new TCanvas("cRAA","RAA",1200,800);
  cRAA->Divide(3,2); 
  for (int i=0;i<nbins_cent;i++) {
     cRAA->cd(nbins_cent-i);
     TH1F *hRebinRAA = rebin(uhist[i]->hReco);
     TH1F *hRebinBinByBinRAA = rebin(uhist[i]->hRecoBinByBin);
     hRebinRAA->SetName(Form("hRebinRAA_cent%d",i));
     hRebinBinByBinRAA->SetName(Form("hRebinBinByBinRAA_cent%d",i));
     TH1F *hRecoRAA         = (TH1F*)uhist[i]->hReco->Clone(Form("hRecoRAA_cent%d",i));
     TH1F *hMeasRAA         = (TH1F*)uhist[i]->hMeas->Clone(Form("hMeasRAA_cent%d",i));
     TH1F *hRecoRAAJECSys   = (TH1F*)uhist[i]->hRecoJECSys->Clone(Form("hRecoRAAJECSys_cent%d",i));
     hRebinRAA        ->Scale(1./lumi/7.65/1000000/0.025/(boundaries_cent[i+1]-boundaries_cent[i])/ncoll[i]);
     hRebinBinByBinRAA->Scale(1./lumi/7.65/1000000/0.025/(boundaries_cent[i+1]-boundaries_cent[i])/ncoll[i]);
     hRecoRAA         ->Scale(1./lumi/7.65/1000000/0.025/(boundaries_cent[i+1]-boundaries_cent[i])/ncoll[i]);
     hMeasRAA         ->Scale(1./lumi/7.65/1000000/0.025/(boundaries_cent[i+1]-boundaries_cent[i])/ncoll[i]);
     hRecoRAAJECSys   ->Scale(1./lumi/7.65/1000000/0.025/(boundaries_cent[i+1]-boundaries_cent[i])/ncoll[i]);
     hRebinRAA->Divide(hRebinPP);
     hRecoRAA->Divide(hRecoPP);
     hRebinBinByBinRAA->Divide(hRebinBinByBinPP);
     hMeasRAA->Divide(hMeasPP);
     hRecoRAAJECSys->Divide(hRecoPP);
     hRebinRAA->SetAxisRange(100,300,"X");
     hRebinRAA->SetAxisRange(0,2,"Y");
     hMeasRAA ->SetMarkerStyle(24);
     hMeasRAA ->SetLineColor(2);
     hMeasRAA ->SetMarkerColor(2);
     hRecoRAA->SetMarkerStyle(24);
     hRecoRAA->SetLineColor(4);
     hRecoRAA->SetMarkerColor(4);
     hRebinBinByBinRAA->SetMarkerStyle(20);
     hRebinBinByBinRAA->SetLineColor(2);
     hRebinBinByBinRAA->SetMarkerColor(2);

     hRebinRAA->SetTitle(Form("PbPb %.0f-%.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]));
     hRebinRAA->SetXTitle("Jet p_{T} (GeV/c)");
     hRebinRAA->SetYTitle("R_{AA}");      
     hRebinRAA->Draw();
//     hMeasRAA->Draw("same");
//     hRecoRAA->Draw("same");
     hRebinBinByBinRAA->Draw("same");
     hRebinRAA->Draw("same");
     //uhist[i]->hMeas->Write();
  }
   
   
   
  divideBinWidth(hCent);
  pbpb_Unfo->Write();
//  pbpb_Unfo->Close();
}
