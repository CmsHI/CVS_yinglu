#if !defined(__CINT__) || defined(__MAKECINT__)
#include "hiForest.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TMath.h"
#include "TLegend.h"

using namespace std;

#endif

void EventFraction()  
{
	
	
	cout<<" ------------           Event Fraction Check  7/18/2012       ----------           "<<endl;
	cout<<" ==============================================================================="<<endl;
	
	
	// *****************  Read PbPb   Data  *****************
	
	
	HiForest *c = new HiForest("/hadoop/store/user/belt/hiForest2/HiForest-ppskim-hihighpt-pt90-v1_v3_part.root","hif",1,0);
	HiForest *b = new HiForest("/hadoop/store/user/belt/hiForest2/HiForest-promptskim-hihighpt-hltjet80-pt90-v3_part.root");
	
	int nocut=0;
	int cutcent=0;
	int cutvz=0;
	int cuttrack=0;
	int cutEta=0;
	int cutpt=0;
	int cutcollision=0;
	int cutHBHE=0;
	
	int nocut        = b->tree->GetEntries("hltTree.HLT_HIJet80_v1 ");
	int cutcollision = b->tree->GetEntries("hltTree.HLT_HIJet80_v1 && skim.pcollisionEventSelection");
	int cutHBHE      = b->tree->GetEntries("hltTree.HLT_HIJet80_v1  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter");
	int cutcent      = b->tree->GetEntries("hltTree.HLT_HIJet80_v1 && evtTree.hiBin<36 && skim.pcollisionEventSelection && skim.pHBHENoiseFilter");
	int cutEta       = b->tree->GetEntries("hltTree.HLT_HIJet80_v1 && evtTree.hiBin<36 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter");
	int cutpt        = b->tree->GetEntries("hltTree.HLT_HIJet80_v1 && evtTree.hiBin<36 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter");
	int cutvz        = b->tree->GetEntries("hltTree.HLT_HIJet80_v1 && evtTree.hiBin<36 && akPu3PF.jtpt>100  && abs(evtTree.vz[1])<15 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter");
	int cuttrack     = b->tree->GetEntries("hltTree.HLT_HIJet80_v1 && evtTree.hiBin<36 && abs(evtTree.vz[1])<15 &&  akPu3PF.trackMax/akPu3PF.jtpt>0.01 && akPu3PF.jtpt>100 && abs(akPu3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter");
		
	
    cout<<" ------------          Event Fraction Result       ----------           "<<endl;
    cout<<"  Cut             "<< " Value   " << "  Percentage  " <<endl;
	cout << "  nocut =    " << nocut << endl;
	cout << "  cutcollision =    " << cutcollision << "    " <<  (float)(cutcollision/nocut) << endl;
	cout << "  cutHBHE =    " << cutHBHE  << "    " <<  (float)cutHBHE/(float)cutcollision  << endl;
	cout << "  cutcent =    " << cutcent  << "    " <<  (float)cutcent/(float)cutHBHE << endl;
	cout << "  cutEta =    " << cutEta    << "    " <<  (float)cutEta/(float)cutcent << endl;
	cout << "  cutpt =    " << cutpt      << "    " <<  (float)cutpt/(float)cutEta << endl;
	cout << "  cutvz =    " << cutvz      << "    " <<  (float)cutvz/(float)cutpt  << endl;
	cout << "  cuttrack =    " << cuttrack<< "    " <<  (float)cuttrack/(float)cutvz  << endl;
	
	
	
	
	int nocut        = c->tree->GetEntries("hltTree.HLT_Jet60_v1 ");
	int cutcollision = c->tree->GetEntries("hltTree.HLT_Jet60_v1 && skim.pcollisionEventSelection");
	int cutHBHE      = c->tree->GetEntries("hltTree.HLT_Jet60_v1 && skim.pcollisionEventSelection && skim.pHBHENoiseFilter");
	int cutEta       = c->tree->GetEntries("hltTree.HLT_Jet60_v1 && abs(ak3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter");
	int cutpt        = c->tree->GetEntries("hltTree.HLT_Jet60_v1 && ak3PF.jtpt>100 && abs(ak3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter");
	int cutvz        = c->tree->GetEntries("hltTree.HLT_Jet60_v1 && ak3PF.jtpt>100  && abs(evtTree.vz[1])<15 && abs(ak3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter");
	int cuttrack     = c->tree->GetEntries("hltTree.HLT_Jet60_v1 && abs(evtTree.vz[1])<15 &&  ak3PF.trackMax/ak3PF.jtpt>0.01 && ak3PF.jtpt>100 && abs(ak3PF.jteta)<2  && skim.pcollisionEventSelection && skim.pHBHENoiseFilter");
		
	
    cout<<" ------------          pp    Event Fraction Result       ----------           "<<endl;
    cout<<"  Cut             "<< " Value   " << "  Percentage  " <<endl;
	cout << "  nocut =    " << nocut << endl;
	cout << "  cutcollision =    " << cutcollision << "    " <<  (float)cutcollision/(float)nocut<< endl;
	cout << "  cutHBHE =    " << cutHBHE  << "    " <<   (float)cutHBHE/(float)cutcollision  << endl;
	cout << "  cutEta =    " << cutEta    << "    " <<  (float)cutEta/(float)cutHBHE << endl;
	cout << "  cutpt =    " << cutpt      << "    " <<  (float)cutpt/(float)cutEta << endl;
	cout << "  cutvz =    " << cutvz      << "    " <<  (float)cutvz/(float)cutpt  << endl;
	cout << "  cuttrack =    " << cuttrack<< "    " << (float)cuttrack/(float)cutvz  << endl;
	
	cout<<" ==============================================================="<<endl;
	
	

	
	

	
	
}


