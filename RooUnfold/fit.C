#include <TRandom.h>
#include "/d102/yjlee/mpt/HiForest/hiForest.h"
#include <TH1F.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>

// Centrality binning
const int nbins_cent=	     6;
Double_t boundaries_cent[nbins_cent+1] = {   0,2,4,12,20,28,36   };
Double_t ncoll[nbins_cent] = { 1660, 1310, 745, 251, 62.8, 10.8 };

void fit(int input)
{
   HiForest *cc = new HiForest("/d102/yjlee/hiForest2PP/forest2_2760GeV_ppJet_full_July14.root");
   TH1F *h = new TH1F("h","",20,100,300);
   h->Sumw2();
   cc->tree->Draw("akPu3PF.jtpt>>h","pcollisionEventSelection&&pHBHENoiseFilter&&akPu3PF.jtpt>100&&abs(akPu3PF.jteta)<2");
   h->SetAxisRange(100,300,"X");
   TH1F *hRatio = (TH1F*)h->Clone("hRatio");
   TCanvas *c = new TCanvas("c","",600,600);
   c->SetLogy();
   h->Draw();
   TF1 *f = new TF1("f","[0]*pow(x+[2],[1])");
   f->SetParameters(1e14,-5,0);
   h->Fit("f","LL","",100,300);
   h->Fit("f","LL","",100,300);
   h->Fit("f","LL","",100,300);
   h->Fit("f","LL","",100,300);
   h->Fit("f","LL","",100,300);
   h->Fit("f","LL","",100,300);
   h->Fit("f","LL","",100,300);
   h->Fit("f","LL","",100,300);
   
   TH1F *hF = (TH1F*)h->Clone();
   for (int i=1;i<=h->GetNbinsX();i++)
   {
      double var = f->Integral(h->GetBinLowEdge(i),h->GetBinLowEdge(i+1))/h->GetBinWidth(i);
      hF->SetBinContent(i,var);
   }
   h->SetTitle("");
   h->SetXTitle("Jet p_{T} (GeV/c)");
   h->SetYTitle("Arbitrary Unit");
   f->Draw("same");
//   hF->Draw("same");
   
   TLegend *leg = new TLegend(0.3,0.3,0.5,0.5);
   leg->SetFillStyle(0);
   leg->SetBorderSize(0);
   if (input!=6) leg->AddEntry(h,Form("%.0f-%.0f%%", boundaries_cent[input]*2.5,boundaries_cent[input+1]*2.5),"");
       else  leg->AddEntry(h,Form("p+p    ", boundaries_cent[input]*2.5,boundaries_cent[input+1]*2.5),"");
   leg->Draw();
   c->SaveAs(Form("fig/spectaFit-%d.gif",input));
   c->SaveAs(Form("fig/spectaFit-%d.pdf",input));
   c->SaveAs(Form("fig/spectaFit-%d.C",input));
   
   TCanvas *c2 = new TCanvas("c2","",600,600);   
   hRatio->SetAxisRange(100,300,"X");
   hRatio->Divide(hF);
   hRatio->SetAxisRange(0.5,1.5,"Y");
   hRatio->SetTitle("");
   hRatio->SetXTitle("Jet p_{T} (GeV/c)");
   hRatio->SetYTitle("data / fit");
   hRatio->Draw();
   leg->Draw();
   TLine *l = new TLine(100,1,300,1);
   l->SetLineStyle(2);
   l->Draw();
   c2->SaveAs(Form("fig/spectaToFitRatio-%d.gif",input));
   c2->SaveAs(Form("fig/spectaToFitRatio-%d.pdf",input));
   c2->SaveAs(Form("fig/spectaToFitRatio-%d.C",input));
}
