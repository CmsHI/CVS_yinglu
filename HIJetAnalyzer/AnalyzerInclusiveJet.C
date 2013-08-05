#include <TRandom.h>

#include <TNtuple.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>

#define PI 3.14159



/*class Trigger{
 int mb;
 int jet35u;
 int jet35uc;
 int jet50u;
 
 };
 
 */

class Jet{
public:
	
	Jet(){
		njets=0;
		pt = 0;
		eta = 0;
		phi = 0;
		run = 0;
		evt = 0;
		bin = 0;
	}
	int njets;
	float pt;
	float eta;
	float phi;
	int run ;
	int evt;
	int bin;
	
};


void analyzeInclusivejet(){
	
	float cutEtaJet = 2;
	
	float cutPtJet = 85;
	
	
	// Tree variables
	
	//Trigger trigger;
	float jtpt_ic5[1000];
	float jteta_ic5[1000];
	float jtphi_ic5[1000];
	int njets_ic5;
	
	float jtpt_ak3[1000];
	float jteta_ak3[1000];
	float jtphi_ak3[1000];
	int njets_ak3;
	
	int run;
	int evt;
	int bin;
	
	TString inname="yenjie_merged.root";
	TFile* inf = new TFile(inname,"read");
	
	TTree* ic5t = (TTree*)inf->Get("icPu5JetAnalyzer/t");
	TTree* t = (TTree*)inf->Get("hltanalysis/HltTree");
	
	ic5t->SetBranchAddress("jtpt",jtpt_ic5);
	ic5t->SetBranchAddress("jteta",jteta_ic5);
	ic5t->SetBranchAddress("jtphi",jtphi_ic5);
	ic5t->SetBranchAddress("nref",&njets_ic5);
	
	TTree* ak3t = (TTree*)inf->Get("akPu3PFJetAnalyzer/t");
	
	ak3t->SetBranchAddress("jtpt",jtpt_ak3);
	ak3t->SetBranchAddress("jteta",jteta_ak3);
	ak3t->SetBranchAddress("jtphi",jtphi_ak3);
	ak3t->SetBranchAddress("nref",&njets_ak3);
	
	/*
	 t->SetBranchAddress("HLT_HIMinBiasHfOrBSC",&evt.mb);
	 t->SetBranchAddress("HLT_HIJet35U",&trigger.jet35u);
	 t->SetBranchAddress("HLT_HIJet35U_Core",&trigger.jet35uc);
	 t->SetBranchAddress("HLT_HIJet50U",&trigger.jet50u);
	 */
	t->SetBranchAddress("Run",&run);
	t->SetBranchAddress("Event",&evt);
	t->SetBranchAddress("hiBin",&bin);
	
	TString outname = "JetSkimTree.root";
	TFile* outf = new TFile(outname,"recreate");
	
	//TNtuple* nt_ic5 = new TNtuple("nt_ic5","","njets:jtpt:jteta:jtphi:bin:trigger.mb:trigger.jet35u:trigger.jet50u:trigger.jet35uc:run:evt");
	//TNtuple* nt_ak3 = new TNtuple("nt_ak3","","njets:jtpt:jteta:jtphi:bin:trigger.mb:trigger.jet35u:trigger.jet50u:trigger.jet35uc:run:evt");
	TNtuple* nt_ic5 = new TNtuple("nt_ic5","","njets:pt:eta:phi:run:evt:bin");
	TNtuple* nt_ak3 = new TNtuple("nt_ak3","","njets:pt:eta:phi:run:evt:bin");
	
	int Nevents = t->GetEntries();
	for(int iev = 0; iev < Nevents; ++iev){
		t->GetEntry(iev);
		ic5t->GetEntry(iev);
		
		Jet ic5;
		
		for(int i = 0; i < njets_ic5; ++i){
			if(jtpt_ic5[i] < cutPtJet) continue;
			if(fabs(jteta_ic5[i]) > cutEtaJet) continue;
			ic.njets =njets_ic5[0];
			ic5.pt =jtpt_ic5[i];
			ic5.eta=jteta_ic5[i];
			ic5.phi = jtphi_ic5[i];
			ic5.run = run;
			ic5.evt = evt;
			ic5.bin = bin;
			
			nt_ic5->Fill(ic.njets,ic5.pt,ic5.eta,ic5.phi,ic5.run,ic5.evt,ic5.bin);
			
		}
		//nt_ic5->Fill(njets_ic5,jtpt_ic5[i],jteta_ic5[i],jtphi_ic5[i],bin,run,evt);
		
		
	}
	nt_ic5->Write();	
	
	
	
	for(int iev = 0; iev < Nevents; ++iev){
		t->GetEntry(iev);
		ak3t->GetEntry(iev);
		
		Jet ak3;
		
		for(int i = 0; i < njets_ak3; ++i){
			if(jtpt_ak3[i] < cutPtJet) continue;
			if(fabs(jteta_ak3[i]) > cutEtaJet) continue;
			ak3.pt =jtpt_ak3[i];
			ak3.eta=jteta_ak3[i];
			ak3.phi = jtphi_ak3[i];
			ak3.run = run;
			ak3.evt = evt;
			ak3.bin = bin;
			
			nt_ak3->Fill(ak.njets,ak3.pt,ak3.eta,ak3.phi,ak3.run,ak3.evt,ak3.bin);
			
		}
		//nt_ak3->Fill(njets_ak3,jtpt_ak3[i],jteta_ak3[i],jtphi_ak3[i],bin,run,evt);
		
		
	}
	
	nt_ak3->Write();
	
	outf->Write();
	outf->Close();
}

