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

void plotVertex()
{
   // Centrality binning
   TFile *inf = new TFile("pbpbSpectra.root");
   TH1F *hData = (TH1F*)inf->Get("hVzData");   
   TH1F *hMC = (TH1F*)inf->Get("hVzMC");
   
   hMC->SetLineColor(2);
   hMC->SetMarkerColor(2);
   hData->Scale(1./hData->Integral());
   hMC->Scale(1./hMC->Integral());
   makeHistTitle(hMC,"","Primary Vertex Z (cm)","Event Fraction");

   TCanvas *c = new TCanvas("c","",600,600);
   hMC->Draw();
   hData->Draw("same");
   
   TLegend *leg = myLegend(0.37,0.22,0.78,0.41);
   leg->AddEntry(hMC,"Reweighted MC","pl");
   leg->AddEntry(hData,"Data","pl");
   leg->Draw();
   c->SaveAs("fig/PrimaryVertex.C");
   c->SaveAs("fig/PrimaryVertex.pdf");
   c->SaveAs("fig/PrimaryVertex.gif");
}
