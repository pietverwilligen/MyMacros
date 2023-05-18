#include "TCanvas.h"
#include "TStyle.h"
#include "TFile.h"
#include "TH1F.h"
#include "TLegend.h"

void RECOFactorsTable() {

  int entries = 10; // !!! Aanpassen !!!
  std::string histo = "RA2SelectionHisto";

  // ===============================================
  // COMMON STUFF
  //
  // ===============================================
  
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1,0);
  gStyle->SetOptStat(000000);
  gStyle->SetOptTitle(0);
  gStyle->SetGridStyle(0);
  gROOT->UseCurrentStyle();
    
  std::string file_Q1_name = "QCD_HT-100To250_madgraph_Fall10.root";
  std::string file_Q2_name = "QCD_HT-250To500_madgraph_Fall10.root";
  std::string file_Q3_name = "QCD_HT-500To1000_madgraph_Fall10.root";
  std::string file_Q4_name = "QCD_HT-1000_madgraph_Fall10.root";
  
  std::string file_P1_name = "GJets_HT-40To100_madgraph_Fall10.root";
  std::string file_P2_name = "GJets_HT-100To200_madgraph_Fall10.root";
  std::string file_P3_name = "GJets_HT-200_madgraph_Fall10.root";
  
  std::string file_E1_name = "WJetsToLNu_madgraph-tauola_Fall10.root";
  std::string file_E2_name = "DYJetsToLL_madgraph-tauola_Fall10.root";
  std::string file_E3_name = "TTJets_madgraph-tauola_Fall10.root";
  
  // std::string file_Z_name  = "ZinvisibleJets_7TeV-madgraph_Fall10.root";
  std::string file_Z_name  = "ZinvisibleJets_7TeV-madgraph_Fall10_100GeV.root";
  std::string file_D_name  = "Photon.root";
  
  // QCD BKG MC
  TFile * file_Q1 = new TFile(file_Q1_name.c_str(),"READ");
  TFile * file_Q2 = new TFile(file_Q2_name.c_str(),"READ");
  TFile * file_Q3 = new TFile(file_Q3_name.c_str(),"READ");
  TFile * file_Q4 = new TFile(file_Q4_name.c_str(),"READ");
  // EWK BKG MC
  TFile * file_E1 = new TFile(file_E1_name.c_str(),"READ");
  TFile * file_E2 = new TFile(file_E2_name.c_str(),"READ");
  TFile * file_E3 = new TFile(file_E3_name.c_str(),"READ");
  // SGN MC
  TFile * file_P1 = new TFile(file_P1_name.c_str(),"READ");
  TFile * file_P2 = new TFile(file_P2_name.c_str(),"READ");
  TFile * file_P3 = new TFile(file_P3_name.c_str(),"READ");
  // MC Truth
  TFile * file_Z  = new TFile(file_Z_name.c_str(),"READ");  
  // DATA
  TFile * file_D  = new TFile(file_D_name.c_str(),"READ");  

  // Read Histograms
  TH1F *Z, *Q1, *Q2, *Q3, *Q4, *E1, *E2, *E3, *P1, *P2, *P3, *D;
  TH1F *Zi, *Q1i, *Q2i, *Q3i, *Q4i, *E1i, *E2i, *E3i, *P1i, *P2i, *P3i, *Di;
  int Za, Q1a, Q2a, Q3a, Q4a, E1a, E2a, E3a, P1a, P2a, P3a, *Da;
  
  // Amount of processed events (MC) :
  Q1i = ((TH1F*) file_Q1->Get("EventCounters")); Q1a = Q1i->GetBinContent(1);
  Q2i = ((TH1F*) file_Q2->Get("EventCounters")); Q2a = Q2i->GetBinContent(1);
  Q3i = ((TH1F*) file_Q3->Get("EventCounters")); Q3a = Q3i->GetBinContent(1);
  Q4i = ((TH1F*) file_Q4->Get("EventCounters")); Q4a = Q4i->GetBinContent(1);
  
  E1i = ((TH1F*) file_E1->Get("EventCounters")); E1a = E1i->GetBinContent(1);
  E2i = ((TH1F*) file_E2->Get("EventCounters")); E2a = E2i->GetBinContent(1);
  E3i = ((TH1F*) file_E3->Get("EventCounters")); E3a = E3i->GetBinContent(1);
  
  P1i = ((TH1F*) file_P1->Get("EventCounters")); P1a = P1i->GetBinContent(1);
  P2i = ((TH1F*) file_P2->Get("EventCounters")); P2a = P2i->GetBinContent(1);
  P3i = ((TH1F*) file_P3->Get("EventCounters")); P3a = P3i->GetBinContent(1);
  
  Zi = ((TH1F*)  file_Z->Get("EventCounters")); Za  = Zi->GetBinContent(1);
  Di = ((TH1F*)  file_D->Get("EventCounters")); Da  = Di->GetBinContent(1);
  
  // Cross Sections in pb
  // --------------------                                                                                                                                                                               
  std::vector<double> cross_sections; 
  // QCD cross sections
  cross_sections.push_back(7000000.00); cross_sections.push_back(171000.00); cross_sections.push_back(5200.00); cross_sections.push_back(83.00);
  // EWL cross sections
  cross_sections.push_back(31300.00); cross_sections.push_back(3100.00); cross_sections.push_back(165.00); // NNLO (24380, 2289, 95 @ LO)
  // Photon cross sections
  cross_sections.push_back(23620.00); cross_sections.push_back(3476.00); cross_sections.push_back(485.00);
  // Zinv cross section
  cross_sections.push_back(4500); // NNLO: 5760 LO: 4500
  // Luminosity in pb
  // ----------------                                                                                                                                                                                   
  double lumi = 35.30;
  // Events in MC
  // ------------                                                                                                                                                                                       
  std::vector<double> events;
 events.push_back(Q1a); events.push_back(Q2a); events.push_back(Q3a); events.push_back(Q4a);
 events.push_back(E1a); events.push_back(E2a); events.push_back(E3a);
 events.push_back(P1a); events.push_back(P2a); events.push_back(P3a);
 events.push_back(Za);
 // Scaling
 // --------
 std::vector<double> scaling;
 for(int i=0; i<cross_sections.size(); ++i) {scaling.push_back(cross_sections[i]*lumi/events[i]);}


 // ===============================================
 // HISTOGRAMS
 //
 // ===============================================

 P1 = ((TH1F*) file_P1->Get(histo.c_str()));
 P2 = ((TH1F*) file_P2->Get(histo.c_str()));
 P3 = ((TH1F*) file_P3->Get(histo.c_str()));
 
 D = ((TH1F*)  file_D->Get(histo.c_str()));
 Z = ((TH1F*)  file_Z->Get(histo.c_str()));

 P1->Sumw2(); P1->Scale(scaling[7]);
 P2->Sumw2(); P2->Scale(scaling[8]);
 P3->Sumw2(); P3->Scale(scaling[9]);
 TH1F *P;
 P = (TH1F*) P1->Clone("Sig"); int n_P = P->GetNbinsX(); for (int i=1; i<=n_P; ++i) {P->SetBinContent(i,0.0);}
 P->Add(P1); P->Add(P2); P->Add(P3); 

 Z->Sumw2(); Z->Scale(scaling[10]);
 TH1F * Z2;
 Z2 = (TH1F*) Z->Clone(); Z2->Sumw2(); Z2->Scale(5);
 // Not in Use so far: DATA
 D->Sumw2();
 TH1F * D2; 
 double scalingfactor = 0.308;
 D2 = (TH1F*) D->Clone(); D2->Sumw2(); D2->Scale(scalingfactor);




 std::vector<double> Pra2V, Pra2VE;  for (int i=3; i<=9; ++i) { if (i!=7) { Pra2V.push_back(P->GetBinContent(i)); Pra2VE.push_back(P->GetBinError(i));}}
 std::vector<double> Zra2V, Zra2VE;  for (int i=3; i<=9; ++i) { if (i!=7) { Zra2V.push_back(Z->GetBinContent(i)); Zra2VE.push_back(Z->GetBinError(i));}}

 TH1F * Ratio1 = (TH1F*) P->Clone("Merge"); int n_R1 = Ratio1->GetNbinsX(); for (int i=1; i<=n_R1; ++i) {Ratio1->SetBinContent(i,0.0);} Ratio1->Sumw2();
 Ratio1->Divide(Z,P,1);
 TH1F * Ratio2 = (TH1F*) P->Clone("Merge"); int n_R2 = Ratio2->GetNbinsX(); for (int i=1; i<=n_R2; ++i) {Ratio2->SetBinContent(i,0.0);} Ratio2->Sumw2();
 Ratio2->Divide(Z2,P,1);

 std::vector<double> R1V, R1VE;  for (int i=3; i<=9; ++i) { if (i!=7) { R1V.push_back(Ratio1->GetBinContent(i)); R1VE.push_back(Ratio1->GetBinError(i));}}
 std::vector<double> R2V, R2VE;  for (int i=3; i<=9; ++i) { if (i!=7) { R2V.push_back(Ratio2->GetBinContent(i)); R2VE.push_back(Ratio2->GetBinError(i));}}



 std::cout<<"Boson + 3 Jets           &$"<<Zra2V[0]<<" \pm "<<Zra2VE[0]<<"$ &$"<<Pra2V[0]<<" \pm "<<Pra2VE[0]<<"$ &$"<<R1V[0]<<" \pm "<<R1VE[0]<<"$ &$"<<R2V[0]<<" \pm "<<R2VE[0]<<"$"<<std::endl;
 std::cout<<"HT > 300 GeV             &$"<<Zra2V[1]<<" \pm "<<Zra2VE[1]<<"$ &$"<<Pra2V[1]<<" \pm "<<Pra2VE[1]<<"$ &$"<<R1V[1]<<" \pm "<<R1VE[1]<<"$ &$"<<R2V[1]<<" \pm "<<R2VE[1]<<"$"<<std::endl;
 std::cout<<"QCD Angular cuts         &$"<<Zra2V[2]<<" \pm "<<Zra2VE[2]<<"$ &$"<<Pra2V[2]<<" \pm "<<Pra2VE[2]<<"$ &$"<<R1V[2]<<" \pm "<<R1VE[2]<<"$ &$"<<R2V[2]<<" \pm "<<R2VE[2]<<"$"<<std::endl;
 std::cout<<"MHT > 150 GeV            &$"<<Zra2V[3]<<" \pm "<<Zra2VE[3]<<"$ &$"<<Pra2V[3]<<" \pm "<<Pra2VE[3]<<"$ &$"<<R1V[3]<<" \pm "<<R1VE[3]<<"$ &$"<<R2V[3]<<" \pm "<<R2VE[3]<<"$"<<std::endl;
 std::cout<<"High HT Search           &$"<<Zra2V[4]<<" \pm "<<Zra2VE[4]<<"$ &$"<<Pra2V[4]<<" \pm "<<Pra2VE[4]<<"$ &$"<<R1V[4]<<" \pm "<<R1VE[4]<<"$ &$"<<R2V[4]<<" \pm "<<R2VE[4]<<"$"<<std::endl;
 std::cout<<"High MHT Search          &$"<<Zra2V[5]<<" \pm "<<Zra2VE[5]<<"$ &$"<<Pra2V[5]<<" \pm "<<Pra2VE[5]<<"$ &$"<<R1V[5]<<" \pm "<<R1VE[5]<<"$ &$"<<R2V[5]<<" \pm "<<R2VE[5]<<"$"<<std::endl;

}
