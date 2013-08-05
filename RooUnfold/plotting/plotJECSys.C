#include <TRandom.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>
#include <TLine.h>
#include <TCanvas.h>

void cleanup(TH1F *h)
{
   for (int i=1;i<=h->GetNbinsX();i++)
   {
      double val1 = h->GetBinContent(i);
      double valErr1 = h->GetBinError(i);
      //if (valErr1>=val1) {
       //  h->SetBinContent(i,0);
	 h->SetBinError(i,0);
      //}
   }   

}
void plotJECSys()
{
   // Centrality binning
   const int nbins_cent=	6;
   Double_t boundaries_cent[nbins_cent+1] = {   0,2,4,12,20,28,36   };
   Double_t ncoll[nbins_cent] = { 1660, 1310, 745, 251, 62.8, 10.8 };

   TFile *inf = new TFile("pbpb_u.root");
   
   TH1F *hRecoRAAJECSys[nbins_cent];
   TH1F *hRecoRAA[nbins_cent];
  
   TCanvas *c = new TCanvas("c","",1200,800);
   c->Divide(3,2);
   
   for (int i=0;i<nbins_cent;i++)
   {
      c->cd(6-i);
      hRecoRAA[i] = (TH1F*)inf->Get(Form("hRecoRAA_cent%d",i));
      hRecoRAAJECSys[i] = (TH1F*)inf->Get(Form("hRecoRAAJECSys_cent%d",i));
      //cleanup(hRecoRAAJECSys[i]);
      //cleanup(hRecoRAA[i]);
      hRecoRAAJECSys[i]->Divide(hRecoRAAJECSys[i],hRecoRAA[i],1,1,"B");
      hRecoRAAJECSys[i]->SetAxisRange(0.61,1.39,"Y");
      hRecoRAAJECSys[i]->Draw("p");
      hRecoRAAJECSys[i]->SetTitle(Form("PbPb %.0f-%.0f%%",2.5*boundaries_cent[i],2.5*boundaries_cent[i+1]));
      hRecoRAAJECSys[i]->SetAxisRange(100,300,"X");
      //hRecoRAA[i]->Draw("same");
      hRecoRAAJECSys[i]->Fit("pol1");
      hRecoRAAJECSys[i]->SetXTitle("Jet p_{T} (GeV/c)");
      hRecoRAAJECSys[i]->SetYTitle("Ratio");
      TLine *l = new TLine(100,1,300,1);
      l->SetLineStyle(2);
      l->Draw();
      
   }
 
}
