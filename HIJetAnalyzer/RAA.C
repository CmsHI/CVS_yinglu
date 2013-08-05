{
TCanvas *c1=new TCanvas("c1","");
TFile *f = new TFile("JetSpectra_central.root");
TH1F *hPbPb_cent = (TH1F*)f->Get("hRAA");
TFile *g = new TFile("JetSpectra_periph.root");
TH1F *hpp_cent = (TH1F*)g->Get("hRAA");






TCanvas *c2=new TCanvas("c2",""); 
TFile *f = new TFile("JetSpectra_central.root");
TH1F *hRAA_cent = (TH1F*)f->Get("hRAA");
TFile *g = new TFile("JetSpectra_periph.root");
TH1F *hRAA_periph = (TH1F*)g->Get("hRAA");
hRAA_cent->SetMarkerColor(2);
hRAA_cent->Draw();
hRAA_periph->SetMarkerColor(4);
hRAA_periph->Draw("same");
TLine * line = new TLine(80,1,350,1);
line->Draw("same");
TLegend *tleg = new TLegend(0.65, 0.6, 0.85, 0.85);
tleg->SetBorderSize(0);
tleg->AddEntry(hRAA_cent," central ","pl");
tleg->AddEntry(hRAA_periph," peripheral ","pl");
tleg->Draw();

}

