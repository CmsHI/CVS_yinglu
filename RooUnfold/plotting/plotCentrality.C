#include <TRandom.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>
#include <TLine.h>
#include <TCanvas.h>
#include <utilities.h>

void plotCentrality()
{
   // Centrality binning
   TFile *inf = new TFile("pbpbSpectra.root");
   TH1F *hData = (TH1F*)inf->Get("hCentData");   
   TH1F *hMC = (TH1F*)inf->Get("hCentMC");
   
   hMC->SetLineColor(2);
   hMC->SetMarkerColor(2);
   hData->Scale(1./hData->Integral());
   hMC->Scale(1./hMC->Integral());
   makeHistTitle(hMC,""," Centrality","Event Fraction");

   TCanvas *c = new TCanvas("c","",600,600);
   hMC->Draw();
   hData->Draw("same");
   //hMC->SetAxisRange(0,36,"X");
   
   TLegend *leg = myLegend(0.5,0.7,0.9,0.9);
   leg->AddEntry(hMC,"Reweighted MC","pl");
   leg->AddEntry(hData,"Data","pl");
   leg->Draw();
   c->SaveAs("fig/Centrality.C");
   c->SaveAs("fig/Centrality.pdf");
   c->SaveAs("fig/Centrality.gif");
}
