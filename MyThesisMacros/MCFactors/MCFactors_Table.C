#include "TCanvas.h"
#include "TStyle.h"
#include "TFile.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TLatex.h"
#include <stdio.h>
#include <iostream>
#include <TROOT.h> 
#include "TSystem.h"
#include <stdio.h>
#include <math.h>

void MCFactors_Table() {

  int entries = 10; // !!! Aanpassen !!!

  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1,0);
  gStyle->SetOptStat(000000);
  gStyle->SetOptTitle(0);
  gStyle->SetGridStyle(0);
  gROOT->UseCurrentStyle();
  
  // Read Histograms
  std::string file_P1_name = "PhotonPt40to100GenEvent.root";
  std::string file_P2_name = "PhotonPt100to200GenEvent.root";
  std::string file_P3_name = "PhotonPt200GenEvent.root";
  std::string file_Zb_name = "ZbosonGenEvent.root";
  TFile * file_P1 = new TFile(file_P1_name.c_str(),"READ");
  TFile * file_P2 = new TFile(file_P2_name.c_str(),"READ");
  TFile * file_P3 = new TFile(file_P3_name.c_str(),"READ");
  TFile * file_Zb = new TFile(file_Zb_name.c_str(),"READ");
  TH1F *P1, *P2, *P3, *Zb;
  TH1F *P1i, *P2i, *P3i, *Zbi;
  int P1a, P2a, P3a, Zba;
  // Amount of processed events (MC) :
  P1i = ((TH1F*) file_P1->Get("NJets_AK5PT50ETA25")); P1a = P1i->GetEntries();
  P2i = ((TH1F*) file_P2->Get("NJets_AK5PT50ETA25")); P2a = P2i->GetEntries();
  P3i = ((TH1F*) file_P3->Get("NJets_AK5PT50ETA25")); P3a = P3i->GetEntries();
  Zbi = ((TH1F*) file_Zb->Get("NJets_AK5PT50ETA25")); Zba = Zbi->GetEntries();
  // Cross Sections in pb
  std::vector<double> cross_sections; cross_sections.push_back(23620.00); cross_sections.push_back(3476.00); cross_sections.push_back(485.00); cross_sections.push_back(4500);
  // Luminosity in pb
  double lumi = 36.14;
  // Events in MC
  std::vector<double> scaling;
  std::vector<double> events; events.push_back(P1a); events.push_back(P2a); events.push_back(P3a); events.push_back(Zba);
  // Scaling
  for(int i=0; i<cross_sections.size(); ++i) {scaling.push_back(cross_sections[i]*lumi/events[i]);}
  // std::cout<<"Z scaling : x-section = "<<cross_sections[3]<<" | lumi = "<<lumi<<" | events = "<<events[3]<<" | scaling = "<<scaling[3]<<std::endl;
  
  // Histo relevant for RA2 Selection: Bins: | 1 = Total Events | 3 = Iso Photon + 3 Jets | 4 = HT | 5 = Angular | 6 = MHT |                                                                              

  TH1F * P1ra2 = ((TH1F*) file_P1->Get("EventCounters_B100")); P1ra2->Sumw2(); P1ra2->Scale(scaling[0]); 
  TH1F * P2ra2 = ((TH1F*) file_P2->Get("EventCounters_B100")); P2ra2->Sumw2(); P2ra2->Scale(scaling[1]); 
  TH1F * P3ra2 = ((TH1F*) file_P3->Get("EventCounters_B100")); P3ra2->Sumw2(); P3ra2->Scale(scaling[2]);
  TH1F * Pbra2 = (TH1F*) P1ra2->Clone("Merge"); int n_P = Pbra2->GetNbinsX(); for (int i=1; i<=n_P; ++i) {Pbra2->SetBinContent(i,0.0);} Pbra2->Sumw2();
  Pbra2->Add(P1ra2); Pbra2->Add(P2ra2); Pbra2->Add(P3ra2);
  // Chnge this to B100 or B000 if you do or do not want a pt cut of 100 GeV o the bosons 
  Zbra2 = ((TH1F*) file_Zb->Get("EventCounters_B100"));
  TH1F * Zara2  = (TH1F*) Zbra2->Clone("Inclusive");
  // Debug
  std::cout<<"Cutflow on Z before scaling: ";
  for(int i=1; i<8; ++i) {
    std::cout<<Zbra2->GetBinContent(i)<<" | ";
  }
  std::cout<<std::endl; 
  // end Debug
  Zbra2->Sumw2(); Zbra2->Scale(scaling[3]); 
  // Debug
  std::cout<<"Cutflow on Z after scaling: ";
  for(int i=1; i<8; ++i) {
    std::cout<<Zbra2->GetBinContent(i)<<" | ";
  }
  std::cout<<std::endl; 
  // end Debug

  Zara2->Sumw2(); Zara2->Scale(scaling[3]*5.0); 
  
  std::vector<double> Pra2V, Pra2VE;  for (int i=1; i<=entries; ++i) { Pra2V.push_back(Pbra2->GetBinContent(i)); Pra2VE.push_back(Pbra2->GetBinError(i));}
  std::vector<double> Zra2V, Zra2VE;  for (int i=1; i<=entries; ++i) { Zra2V.push_back(Zbra2->GetBinContent(i)); Zra2VE.push_back(Zbra2->GetBinError(i));}
    
  TH1F * Ratio1 = (TH1F*) Pbra2->Clone("Merge"); int n_R1 = Ratio1->GetNbinsX(); for (int i=1; i<=n_R1; ++i) {Ratio1->SetBinContent(i,0.0);} Ratio1->Sumw2();
  Ratio1->Divide(Zbra2,Pbra2,1);
  TH1F * Ratio2 = (TH1F*) Pbra2->Clone("Merge"); int n_R2 = Ratio2->GetNbinsX(); for (int i=1; i<=n_R2; ++i) {Ratio2->SetBinContent(i,0.0);} Ratio2->Sumw2();
  Ratio2->Divide(Zara2,Pbra2,1);
  
  std::vector<double> R1V, R1VE;  for (int i=1; i<=entries; ++i) { R1V.push_back(Ratio1->GetBinContent(i)); R1VE.push_back(Ratio1->GetBinError(i));}
  std::vector<double> R2V, R2VE;  for (int i=1; i<=entries; ++i) { R2V.push_back(Ratio2->GetBinContent(i)); R2VE.push_back(Ratio2->GetBinError(i));}

  
  // ===============================================
  // TABLE MC Event
  // ===============================================  
  std::cout<<"\hline"<<std::endl;
  std::cout<<"\hline"<<std::endl;
  std::cout<<"Selection Cuts         &\#  Zinv   &\#  Photon  & Zinv/Photon & Z/Photon"<<std::endl;
  std::cout<<"\hline"<<std::endl;
  std::cout<<"All Events             &$"<<Zra2V[0]<<" \pm "<<Zra2VE[0]<<"$ &$"<<Pra2V[0]<<" \pm "<<Pra2VE[0]<<"$ &$"<<R1V[0]<<" \pm "<<R1VE[0]<<"$ &$"<<R2V[0]<<" \pm "<<R2VE[0]<<"$"<<std::endl;
  std::cout<<"1 $gamma > 100 GeV/c$  &$"<<Zra2V[1]<<" \pm "<<Zra2VE[1]<<"$ &$"<<Pra2V[1]<<" \pm "<<Pra2VE[1]<<"$ &$"<<R1V[1]<<" \pm "<<R1VE[1]<<"$ &$"<<R2V[1]<<" \pm "<<R2VE[1]<<"$"<<std::endl;
  std::cout<<"+ 1 Jet                &$"<<Zra2V[2]<<" \pm "<<Zra2VE[2]<<"$ &$"<<Pra2V[2]<<" \pm "<<Pra2VE[2]<<"$ &$"<<R1V[2]<<" \pm "<<R1VE[2]<<"$ &$"<<R2V[2]<<" \pm "<<R2VE[2]<<"$"<<std::endl;
  std::cout<<"+ 2 Jets               &$"<<Zra2V[3]<<" \pm "<<Zra2VE[3]<<"$ &$"<<Pra2V[3]<<" \pm "<<Pra2VE[3]<<"$ &$"<<R1V[3]<<" \pm "<<R1VE[3]<<"$ &$"<<R2V[3]<<" \pm "<<R2VE[3]<<"$"<<std::endl;
  std::cout<<"+ 3 Jets               &$"<<Zra2V[4]<<" \pm "<<Zra2VE[4]<<"$ &$"<<Pra2V[4]<<" \pm "<<Pra2VE[4]<<"$ &$"<<R1V[4]<<" \pm "<<R1VE[4]<<"$ &$"<<R2V[4]<<" \pm "<<R2VE[4]<<"$"<<std::endl;
  std::cout<<"\hline"<<std::endl;
  std::cout<<"HT > 300 GeV             &$"<<Zra2V[5]<<" \pm "<<Zra2VE[5]<<"$ &$"<<Pra2V[5]<<" \pm "<<Pra2VE[5]<<"$ &$"<<R1V[5]<<" \pm "<<R1VE[5]<<"$ &$"<<R2V[5]<<" \pm "<<R2VE[5]<<"$"<<std::endl;
  std::cout<<"QCD Angular cuts         &$"<<Zra2V[6]<<" \pm "<<Zra2VE[6]<<"$ &$"<<Pra2V[6]<<" \pm "<<Pra2VE[6]<<"$ &$"<<R1V[6]<<" \pm "<<R1VE[6]<<"$ &$"<<R2V[6]<<" \pm "<<R2VE[6]<<"$"<<std::endl;
  std::cout<<"MHT > 150 GeV            &$"<<Zra2V[7]<<" \pm "<<Zra2VE[7]<<"$ &$"<<Pra2V[7]<<" \pm "<<Pra2VE[7]<<"$ &$"<<R1V[7]<<" \pm "<<R1VE[7]<<"$ &$"<<R2V[7]<<" \pm "<<R2VE[7]<<"$"<<std::endl;
  std::cout<<"\hline"<<std::endl;
  std::cout<<"High HT Search:          &$"<<Zra2V[8]<<" \pm "<<Zra2VE[8]<<"$ &$"<<Pra2V[8]<<" \pm "<<Pra2VE[8]<<"$ &$"<<R1V[8]<<" \pm "<<R1VE[8]<<"$ &$"<<R2V[8]<<" \pm "<<R2VE[8]<<"$"<<std::endl;
  std::cout<<"\hline"<<std::endl;
  std::cout<<"High MHT Search:         &$"<<Zra2V[9]<<" \pm "<<Zra2VE[9]<<"$ &$"<<Pra2V[9]<<" \pm "<<Pra2VE[9]<<"$ &$"<<R1V[9]<<" \pm "<<R1VE[9]<<"$ &$"<<R2V[9]<<" \pm "<<R2VE[9]<<"$"<<std::endl;
  std::cout<<"\hline"<<std::endl;
  std::cout<<"\hline"<<std::endl;

}
