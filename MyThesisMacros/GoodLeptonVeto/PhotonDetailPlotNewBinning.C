#include "TStyle.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TFile.h"
#include "TH1F.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TString.h"
#include "TGaxis.h"

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
#include <algorithm>

void PhotonDetailPlotNewBinning() {

  int entries = 11; // !!! Aanpassen !!!

  std::string dir_all = "RECO/RECO_Egamma/";
  std::string dir_dir = "RECO/RECO_Direct_Egamma/";
  std::string dir_fra = "RECO/RECO_Fragment_Egamma/";
  std::string dir_dec = "RECO/RECO_Decay_Egamma/";
  std::string dir_mis = "RECO/RECO_Electron_Egamma/";

  std::string histarray[] = {"Et", "Eta", "Phi", "HE", "HolTrkIso", "EcalIso", "HcalIso", "PixelSeeds", "SigmaIEtaIEta", "SigmaIPhiIPhi", "V_PoverE"};
  std::string xaxisarray[] = {"Pt #gamma [GeV]", "#eta #gamma [-]", "#phi #gamma [-]", "H/E #gamma [-]", "TRK Iso #gamma [GeV/c]", "ECAL Iso #gamma [GeV]", "HCAL Iso #gamma [GeV]", "Pixel Seed #gamma [-]", "#sigma_{I #eta I #eta} #gamma [-]", "#sigma_{I #phi I #phi} #gamma [-]", "Conversion #gamma: Pair p  over SC E [-]"};
  std::string yaxisarray[] = {"#gamma candidates / 5 GeV", "#gamma candidates / 0.20", "#gamma candidates / #frac{2 #pi}{18}", "#gamma candidates / 0.005", "#gamma candidates / 0.25 GeV/c", "#gamma candidates / 0.25 GeV", "#gamma candidates / 0.25 GeV",  "#gamma candidates", "#gamma candidates / 0.0005", "#gamma candidates / 0.0005", "#gamma candiates [A.U.]"};
  std::string namearray[] = {"PhotonEt","PhotonEta", "PhotonPhi", "PhotonHE", "PhotonTrkIso", "PhotonEcalIso", "PhotonHcalIso", "PhotonPS", "PhotonSIEIE", "PhotonSIPIP", "PhotonPoverE"};

  std::vector<std::string> Histos; for(int i=0;i<entries; ++i) { Histos.push_back(histarray[i]); }
  std::vector<std::string> Xaxis;  for(int i=0;i<entries; ++i) { Xaxis.push_back(xaxisarray[i]); }
  std::vector<std::string> Yaxis;  for(int i=0;i<entries; ++i) { Yaxis.push_back(yaxisarray[i]); }
  std::vector<std::string> Names;  for(int i=0;i<entries; ++i) { Names.push_back(namearray[i]); }

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
  
  std::string file_Z_name  = "ZinvisibleJets_7TeV-madgraph_Fall10.root";
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
  int Za, Q1a, Q2a, Q3a, Q4a, E1a, E2a, E3a, P1a, P2a, P3a, Da;
  
  TH1F *Q1_fra, *Q2_fra, *Q3_fra, *Q4_fra;
  TH1F *Q1_dec, *Q2_dec, *Q3_dec, *Q4_dec;
  TH1F *Q1_mis, *Q2_mis, *Q3_mis, *Q4_mis;

  TH1F *E1_fra, *E2_fra, *E3_fra;
  TH1F *E1_dec, *E2_dec, *E3_dec;
  TH1F *E1_mis, *E2_mis, *E3_mis;

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
  cross_sections.push_back(31000.00); cross_sections.push_back(3100.00); cross_sections.push_back(165.00); // NNLO (24380, 2289, 95 @ LO)
  // Photon cross sections
  cross_sections.push_back(23620.00); cross_sections.push_back(3476.00); cross_sections.push_back(485.00);
  // Zinv cross section
  cross_sections.push_back(5760); // NNLO (4500@LO)
  // Luminosity in pb
  // ----------------                                                                                                                                                                                   
  double lumi = 36.14;
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
 
 for (int ii=0; ii<entries; ++ii) {
    // Debug modus for only 1 plot
    if (ii != 0) continue;
    // 
    int rebin = 0;
    if(ii == 0) rebin = 1;

    std::cout<<"==== i = "<<ii<<" ==== "<<Histos[ii]<<" ==== "<<Xaxis[ii]<<" ==== "<<Yaxis[ii]<<" ==== "<<std::endl;

    std::string SelHisto = Histos[ii];
    std::string xaxis = Xaxis[ii];
    std::string yaxis = Yaxis[ii];
    std::string NameHisto = Names[ii];
    
    Q1 = ((TH1F*) file_Q1->Get((dir_all+SelHisto).c_str())); Q1->Sumw2();
    Q2 = ((TH1F*) file_Q2->Get((dir_all+SelHisto).c_str())); Q2->Sumw2();
    Q3 = ((TH1F*) file_Q3->Get((dir_all+SelHisto).c_str())); Q3->Sumw2();
    Q4 = ((TH1F*) file_Q4->Get((dir_all+SelHisto).c_str())); Q4->Sumw2();
    Q1_fra = ((TH1F*) file_Q1->Get((dir_fra+SelHisto).c_str())); Q1_fra->Sumw2();
    Q2_fra = ((TH1F*) file_Q2->Get((dir_fra+SelHisto).c_str())); Q2_fra->Sumw2();
    Q3_fra = ((TH1F*) file_Q3->Get((dir_fra+SelHisto).c_str())); Q3_fra->Sumw2();
    Q4_fra = ((TH1F*) file_Q4->Get((dir_fra+SelHisto).c_str())); Q4_fra->Sumw2();
    Q1_dec = ((TH1F*) file_Q1->Get((dir_dec+SelHisto).c_str())); Q1_dec->Sumw2();
    Q2_dec = ((TH1F*) file_Q2->Get((dir_dec+SelHisto).c_str())); Q2_dec->Sumw2();
    Q3_dec = ((TH1F*) file_Q3->Get((dir_dec+SelHisto).c_str())); Q3_dec->Sumw2();
    Q4_dec = ((TH1F*) file_Q4->Get((dir_dec+SelHisto).c_str())); Q4_dec->Sumw2();
    Q1_mis = ((TH1F*) file_Q1->Get((dir_mis+SelHisto).c_str())); Q1_mis->Sumw2(); std::cout<<"Mistagged Electrons: Q1_mis: Entries"<<Q1_mis->GetEntries()<<std::endl;
    Q2_mis = ((TH1F*) file_Q2->Get((dir_mis+SelHisto).c_str())); Q2_mis->Sumw2(); std::cout<<"Mistagged Electrons: Q2_mis: Entries"<<Q2_mis->GetEntries()<<std::endl;
    Q3_mis = ((TH1F*) file_Q3->Get((dir_mis+SelHisto).c_str())); Q3_mis->Sumw2(); std::cout<<"Mistagged Electrons: Q3_mis: Entries"<<Q3_mis->GetEntries()<<std::endl;
    Q4_mis = ((TH1F*) file_Q4->Get((dir_mis+SelHisto).c_str())); Q4_mis->Sumw2(); std::cout<<"Mistagged Electrons: Q4_mis: Entries"<<Q4_mis->GetEntries()<<std::endl;
    E1_fra = ((TH1F*) file_E1->Get((dir_fra+SelHisto).c_str())); E1_fra->Sumw2();
    E2_fra = ((TH1F*) file_E2->Get((dir_fra+SelHisto).c_str())); E2_fra->Sumw2();
    E3_fra = ((TH1F*) file_E3->Get((dir_fra+SelHisto).c_str())); E3_fra->Sumw2();
    E1_dec = ((TH1F*) file_E1->Get((dir_dec+SelHisto).c_str())); E1_dec->Sumw2();
    E2_dec = ((TH1F*) file_E2->Get((dir_dec+SelHisto).c_str())); E2_dec->Sumw2();
    E3_dec = ((TH1F*) file_E3->Get((dir_dec+SelHisto).c_str())); E3_dec->Sumw2();
    E1_mis = ((TH1F*) file_E1->Get((dir_mis+SelHisto).c_str())); E1_mis->Sumw2(); std::cout<<"Mistagged Electrons: E1_mis: Entries"<<E1_mis->GetEntries()<<std::endl;
    E2_mis = ((TH1F*) file_E2->Get((dir_mis+SelHisto).c_str())); E2_mis->Sumw2(); std::cout<<"Mistagged Electrons: E2_mis: Entries"<<E2_mis->GetEntries()<<std::endl;
    E3_mis = ((TH1F*) file_E3->Get((dir_mis+SelHisto).c_str())); E3_mis->Sumw2(); std::cout<<"Mistagged Electrons: E3_mis: Entries"<<E3_mis->GetEntries()<<std::endl;

    P1 = ((TH1F*) file_P1->Get((dir_all+SelHisto).c_str())); P1->Sumw2();
    P2 = ((TH1F*) file_P2->Get((dir_all+SelHisto).c_str())); P2->Sumw2();
    P3 = ((TH1F*) file_P3->Get((dir_all+SelHisto).c_str())); P3->Sumw2();
    
    D = ((TH1F*)  file_D->Get((dir_all+SelHisto).c_str())); D->Sumw2();
    
    // Final Histograms
    TH1F *Q, * Q_dir, *Q_fra, *Q_dec, *Q_all, *P, *A, *E;

    Q = (TH1F*) Q1->Clone("QCD"); int n_Q = Q->GetNbinsX(); for (int i=1; i<=n_Q; ++i) {Q->SetBinContent(i,0.0); Q->SetBinError(i,0.0);}
    Q_fra = (TH1F*) Q1->Clone("QCD"); for (int i=1; i<=n_Q; ++i) {Q_fra->SetBinContent(i,0.0); Q_fra->SetBinError(i,0.0);}
    Q_dec = (TH1F*) Q1->Clone("QCD"); for (int i=1; i<=n_Q; ++i) {Q_dec->SetBinContent(i,0.0); Q_dec->SetBinError(i,0.0);}
    Q_mis = (TH1F*) Q1->Clone("QCD"); for (int i=1; i<=n_Q; ++i) {Q_mis->SetBinContent(i,0.0); Q_mis->SetBinError(i,0.0);}
    Q_all = (TH1F*) Q1->Clone("QCD"); for (int i=1; i<=n_Q; ++i) {Q_all->SetBinContent(i,0.0); Q_all->SetBinError(i,0.0);}
    P = (TH1F*) P1->Clone("Sig"); int n_P = P->GetNbinsX(); for (int i=1; i<=n_P; ++i) {P->SetBinContent(i,0.0); P->SetBinError(i,0.0);}
    E_fra = (TH1F*) E1_fra->Clone("EWK"); int n_E = E_fra->GetNbinsX(); for (int i=1; i<=n_E; ++i) {E_fra->SetBinContent(i,0.0); E_fra->SetBinError(i,0.0);}
    E_dec = (TH1F*) E1_fra->Clone("EWK"); for (int i=1; i<=n_E; ++i) {E_dec->SetBinContent(i,0.0); E_dec->SetBinError(i,0.0);}
    E_mis = (TH1F*) E1_fra->Clone("EWK"); for (int i=1; i<=n_E; ++i) {E_mis->SetBinContent(i,0.0); E_mis->SetBinError(i,0.0);}
    A = (TH1F*) Q1->Clone("All"); int n_A = A->GetNbinsX(); for (int i=1; i<=n_A; ++i) {A->SetBinContent(i,0.0); A->SetBinError(i,0.0);}

    // Q = new TH1F("QCD_Pt","QCD MC Photon Pt Distribution", 100, 0, 500);
    // P = new TH1F("Sig_Pt","Signal MC Photon Pt Distribution", 100, 0, 500);
    // A = new TH1F("All",   "All MC Photon Pt Distribution", 100, 0, 500);
    

    // Scaling: cross section [pb] x lumi [pb^-1] / number of events before any selection
    Q1->Scale(scaling[0]); 
    Q2->Scale(scaling[1]);
    Q3->Scale(scaling[2]);
    Q4->Scale(scaling[3]);

    Q1_fra->Scale(scaling[0]); 
    Q2_fra->Scale(scaling[1]);
    Q3_fra->Scale(scaling[2]);
    Q4_fra->Scale(scaling[3]);
    Q1_dec->Scale(scaling[0]); 
    Q2_dec->Scale(scaling[1]);
    Q3_dec->Scale(scaling[2]);
    Q4_dec->Scale(scaling[3]);
    Q1_mis->Scale(scaling[0]); 
    Q2_mis->Scale(scaling[1]);
    Q3_mis->Scale(scaling[2]);
    Q4_mis->Scale(scaling[3]);

    E1_fra->Scale(scaling[4]);
    E2_fra->Scale(scaling[5]);
    E3_fra->Scale(scaling[6]);
    E1_dec->Scale(scaling[4]);
    E2_dec->Scale(scaling[5]);
    E3_dec->Scale(scaling[6]);
    E1_mis->Scale(scaling[4]);
    E2_mis->Scale(scaling[5]);
    E3_mis->Scale(scaling[6]);
    
    P1->Scale(scaling[7]);
    P2->Scale(scaling[8]);
    P3->Scale(scaling[9]);
    

    Q->Add(Q1); Q->Add(Q2); Q->Add(Q3); Q->Add(Q4); 
    Q_fra->Add(Q1_fra); Q_fra->Add(Q2_fra); Q_fra->Add(Q3_fra); Q_fra->Add(Q4_fra); Q_fra->Add(E1_fra); Q_fra->Add(E2_fra); Q_fra->Add(E3_fra);
    Q_dec->Add(Q1_dec); Q_dec->Add(Q2_dec); Q_dec->Add(Q3_dec); Q_dec->Add(Q4_dec); Q_dec->Add(E1_dec); Q_dec->Add(E2_dec); Q_dec->Add(E3_dec);
    Q_mis->Add(Q1_mis); Q_mis->Add(Q2_mis); Q_mis->Add(Q3_mis); Q_mis->Add(Q4_mis); Q_mis->Add(E1_mis); Q_mis->Add(E2_mis); Q_mis->Add(E3_mis);
    Q_all->Add(Q_dec); Q_all->Add(Q_fra); Q->Add(Q_dir); 
    P->Add(P1); P->Add(P2); P->Add(P3); 
    THStack *as = new THStack("as","All Merge");
    Q_mis->SetFillColor(kYellow);   as->Add(Q_mis);
    Q_dec->SetFillColor(kGreen);    as->Add(Q_dec);
    Q_fra->SetFillColor(kMagenta);  as->Add(Q_fra);
    P->SetFillColor(kRed);          as->Add(P);
    A->Add(Q_mis); A->Add(Q_dec); A->Add(Q_fra); A->Add(P);

    if(!rebin) {
      // All MC + DATA
      TCanvas * c1 = new TCanvas("c","canvas",800,600);
      c1->cd();
      c1->SetLogy(1);
      if(ii == 4 || ii == 5 || ii == 6) { A->GetYaxis()->SetRangeUser(3e-4,1e6); }
      else { 	                          A->GetYaxis()->SetRangeUser(3e-4,1e4); }
      D->SetMarkerStyle(20); D->SetMarkerColor(kBlack); D->SetLineColor(kBlack); D->SetMarkerSize(0.75);
      A->GetYaxis()->SetTitle(yaxis.c_str());
      A->GetYaxis()->SetLabelSize(0.025);
      if(ii == 4 || ii == 5 || ii == 6) {A->GetXaxis()->SetRangeUser(-1,6); D->GetXaxis()->SetRangeUser(-1,6);}
      // A->GetYaxis()->SetTicks("+");
      // A->GetXaxis()->SetTitle(xaxis.c_str())
      A->GetXaxis()->SetLabelSize(0.0000025);
      A->GetXaxis()->SetTicks("+-");
      A->Draw("HIST");
      as->Draw("HISTsame");
      D->Draw("sameE");
      gPad->RedrawAxis();
      gStyle->SetGridStyle(3);
      // Coordinates for TLegend: x1, y1, x2, y2
      double x1,y1,x2,y2;
      if(ii == 4 || ii == 5 || ii == 6) { x1=0.70; y1=0.575; x2=0.85; y2=0.875; }
      else {                              x1=0.70; y1=0.725; x2=0.85; y2=0.875; }
      TLegend *l1 = new TLegend(x1,y1,x2,y2,NULL,"brNDC");
      l1->SetLineColor(0);
      l1->SetLineStyle(0);
      l1->SetLineWidth(0);
      l1->SetFillColor(4000);
      l1->SetBorderSize(0);
      l1->AddEntry(D, "Data","pel");
      l1->AddEntry(P, "Prompt #gamma","f");
      l1->AddEntry(Q_fra, "Fragmentation #gamma","f");
      l1->AddEntry(Q_dec, "Meson decay #gamma","f");
      l1->AddEntry(Q_mis, "Mistagged e^{#pm}","f");
      l1->Draw();
      cmsPrelim(lumi, 1);
      c1->SetLogy(1);
      c1->SetBottomMargin(0.2 + 0.8*c1->GetBottomMargin()-0.2*c1->GetTopMargin());
      TPad *ratioPad = new TPad("BottomPad","",0,0,1,1);
      ratioPad->SetTopMargin(0.8 - 0.8*ratioPad->GetBottomMargin()+0.2*ratioPad->GetTopMargin());
      ratioPad->SetFillStyle(4000);
      ratioPad->SetFillColor(4000);
      ratioPad->SetFrameFillColor(4000);
      ratioPad->SetFrameFillStyle(4000);
      ratioPad->SetFrameBorderMode(0);
      ratioPad->Draw();
      ratioPad->cd();
      ratioPad->SetGridy();
      TH1* ratio = 0;
      ratio = (TH1F*)D->Clone();
      ratio->Divide(D, A, 1, 1, "b");
      ratio->SetMinimum(0.0);                                                                                                                                                                             
      ratio->SetMaximum(4.0);   
      ratio->GetYaxis()->SetNdivisions(505); // N1 + 100 * N2 (small ticks and big ticks) defines the grid
      ratio->GetYaxis()->SetLabelSize(0.025);
      ratio->GetYaxis()->SetTitle("Data / MC");
      ratio->GetXaxis()->SetTicks("+");
      ratio->GetXaxis()->SetTitle(xaxis.c_str());
      ratio->GetXaxis()->SetLabelSize(0.025);
      ratio->Draw("pe");
      savePlot(c1, NameHisto.c_str());
    } 
    else {
      // manual rebinning
      // Rebin Scheme 1: 30 bins of 5 Gev | 10 bins of 15 GeV | 4 bins of 50 GeV
      // double ptbinning [] = {0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0, 90.0, 95.0, 100.0, 105.0, 110.0, 115.0, 120.0, 125.0, 130.0, 135.0, 140.0, 145.0, 150.0, 165.0, 180.0, 195.0, 210.0, 225.0, 240.0, 255.0, 270.0, 285.0, 300.0, 350.0, 400.0, 450.0, 500.0};
      double ptbinning [] = {0.0, 25.0, 50.0, 75.0, 100.0, 125.0, 150.0, 175.0, 200.0, 225.0, 250.0, 275.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0, 850.0, 900.0, 950.0, 1000.0, 1250.0, 1500.0, 1750.0, 2000.0, 2250.0, 2500.0};
      int newbins = 16;
      // if(ii%2 == 0) newbins = 28; // HT up to 1500
      // else          newbins = 16; // MHT up to 500
      PH = new TH1F("PH", "PH", newbins, ptbinning); PH->Sumw2();
      QF = new TH1F("QF", "QF", newbins, ptbinning); QF->Sumw2();
      QD = new TH1F("QD", "QD", newbins, ptbinning); QD->Sumw2();
      EW = new TH1F("EW", "EW", newbins, ptbinning); EW->Sumw2();
      DA = new TH1F("DA", "DA", newbins, ptbinning); DA->Sumw2();
      AA = new TH1F("AA", "AA", newbins, ptbinning); AA->Sumw2();
      int bins = P->GetNbinsX();
      // double binwidth = 500.0/bins;
      double binwidth = 1000.0/bins;
      double photons = 0.0, zbosons = 0.0;
      for(int iii=1; iii<=bins; ++iii) {
        double bin_lvalue = (0.0 + (iii-1)*binwidth);
        double bin_rvalue = (0.0 + (iii)*binwidth);
        for(int jj=1; jj<newbins+1; ++jj) {
          if (bin_lvalue >=  ptbinning[jj-1] && bin_rvalue <= ptbinning[jj]) {
            PH->AddBinContent(jj,P->GetBinContent(iii));
            QF->AddBinContent(jj,Q_fra->GetBinContent(iii));
            QD->AddBinContent(jj,Q_dec->GetBinContent(iii));
            EW->AddBinContent(jj,Q_mis->GetBinContent(iii));
            DA->AddBinContent(jj,D->GetBinContent(iii));
            AA->AddBinContent(jj,A->GetBinContent(iii));
            PH->SetBinError(jj,sqrt(pow(PH->GetBinError(jj),2)+pow(P->GetBinError(iii),2)));
            QF->SetBinError(jj,sqrt(pow(QF->GetBinError(jj),2)+pow(Q_fra->GetBinError(iii),2)));
            QD->SetBinError(jj,sqrt(pow(QD->GetBinError(jj),2)+pow(Q_dec->GetBinError(iii),2)));
            EW->SetBinError(jj,sqrt(pow(EW->GetBinError(jj),2)+pow(Q_mis->GetBinError(iii),2)));
            DA->SetBinError(jj,sqrt(pow(DA->GetBinError(jj),2)+pow(D->GetBinError(iii),2)));
            AA->SetBinError(jj,sqrt(pow(AA->GetBinError(jj),2)+pow(A->GetBinError(iii),2)));
          }
        }
      }
      // for(int j=31; j<41; ++j) { // 15 GeV binning
      for(int j=1; j<13; ++j) { // 25 GeV binning
        PH->SetBinContent(j, PH->GetBinContent(j)/5); PH->SetBinError(j, PH->GetBinError(j)/5);
        QF->SetBinContent(j, QF->GetBinContent(j)/5); QF->SetBinError(j, QF->GetBinError(j)/5);
        QD->SetBinContent(j, QD->GetBinContent(j)/5); QD->SetBinError(j, QD->GetBinError(j)/5);
        EW->SetBinContent(j, EW->GetBinContent(j)/5); EW->SetBinError(j, EW->GetBinError(j)/5);
        DA->SetBinContent(j, DA->GetBinContent(j)/5); DA->SetBinError(j, DA->GetBinError(j)/5);
        AA->SetBinContent(j, AA->GetBinContent(j)/5); AA->SetBinError(j, AA->GetBinError(j)/5);
      }
      // for(int j=41; j<45; ++j) {
      for(int j=13; j<std::min(newbins+1,27); ++j) { // 50 GeV binning
        PH->SetBinContent(j, PH->GetBinContent(j)/10); PH->SetBinError(j, PH->GetBinError(j)/10);
        QF->SetBinContent(j, QF->GetBinContent(j)/10); QF->SetBinError(j, QF->GetBinError(j)/10);
        QD->SetBinContent(j, QD->GetBinContent(j)/10); QD->SetBinError(j, QD->GetBinError(j)/10);
        EW->SetBinContent(j, EW->GetBinContent(j)/10); EW->SetBinError(j, EW->GetBinError(j)/10);
        DA->SetBinContent(j, DA->GetBinContent(j)/10); DA->SetBinError(j, DA->GetBinError(j)/10);
        AA->SetBinContent(j, AA->GetBinContent(j)/10); AA->SetBinError(j, AA->GetBinError(j)/10);
      }
      for(int j=27; j<newbins+1; ++j) { // 250 GeV binning
        PH->SetBinContent(j, PH->GetBinContent(j)/10); PH->SetBinError(j, PH->GetBinError(j)/10);
        QF->SetBinContent(j, QF->GetBinContent(j)/10); QF->SetBinError(j, QF->GetBinError(j)/10);
        QD->SetBinContent(j, QD->GetBinContent(j)/10); QD->SetBinError(j, QD->GetBinError(j)/10);
        EW->SetBinContent(j, EW->GetBinContent(j)/10); EW->SetBinError(j, EW->GetBinError(j)/10);
        DA->SetBinContent(j, DA->GetBinContent(j)/10); DA->SetBinError(j, DA->GetBinError(j)/10);
        AA->SetBinContent(j, AA->GetBinContent(j)/10); AA->SetBinError(j, AA->GetBinError(j)/10);
      }
      THStack *AS = new THStack("AS","All Merge");
      EW->SetFillColor(kYellow); AS->Add(EW);
      QD->SetFillColor(kGreen);  AS->Add(QD);
      QF->SetFillColor(kMagenta);AS->Add(QF);
      PH->SetFillColor(kRed);    AS->Add(PH);

      // All MC + DATA
      TCanvas * c1 = new TCanvas("c","canvas",800,600);
      c1->cd();
      c1->SetLogy(1);
      AA->GetYaxis()->SetRangeUser(3e-4,1e4);
      DA->SetMarkerStyle(20); D->SetMarkerColor(kBlack); D->SetLineColor(kBlack); D->SetMarkerSize(0.75);
      AA->GetYaxis()->SetTitle(yaxis.c_str());
      AA->GetYaxis()->SetLabelSize(0.025);
      AA->GetXaxis()->SetLabelSize(0.0000025);
      AA->GetXaxis()->SetTicks("+-");
      if(ii==4 || ii==5 || ii==6) { A->GetXaxis()->SetRangeUser(-1,6); D->GetXaxis()->SetRangeUser(-1,6);}
      if(ii==8) { A->GetXaxis()->SetRangeUser(0,0.035); D->GetXaxis()->SetRangeUser(0,0.035);}
      AA->Draw("HIST");
      AS->Draw("HISTsame");
      DA->Draw("sameE");
      gPad->RedrawAxis();
      gStyle->SetGridStyle(3);
      // Coordinates for TLegend: x1, y1, x2, y2
      TLegend *l1 = new TLegend(0.70,0.725,0.85,0.875,NULL,"brNDC");
      l1->SetLineColor(0);
      l1->SetLineStyle(0);
      l1->SetLineWidth(0);
      l1->SetFillColor(4000);
      l1->SetBorderSize(0);
      l1->AddEntry(DA, "Data","pel");
      l1->AddEntry(PH, "Prompt #gamma","f");
      l1->AddEntry(QF, "Fragmentation #gamma","f");
      l1->AddEntry(QD, "Meson decay #gamma","f");
      l1->AddEntry(EW, "Mistagged e^{#pm}","f");
      l1->Draw();
      cmsPrelim(lumi, 1);
      c1->SetLogy(1);
      c1->SetBottomMargin(0.2 + 0.8*c1->GetBottomMargin()-0.2*c1->GetTopMargin());
      TPad *ratioPad = new TPad("BottomPad","",0,0,1,1);
      ratioPad->SetTopMargin(0.8 - 0.8*ratioPad->GetBottomMargin()+0.2*ratioPad->GetTopMargin());
      ratioPad->SetFillStyle(4000);
      ratioPad->SetFillColor(4000);
      ratioPad->SetFrameFillColor(4000);
      ratioPad->SetFrameFillStyle(4000);
      ratioPad->SetFrameBorderMode(0);
      ratioPad->Draw();
      ratioPad->cd();
      ratioPad->SetGridy();
      TH1* ratio = 0;
      ratio = (TH1F*)DA->Clone();
      ratio->Divide(DA, AA, 1, 1, "b");
      ratio->SetMinimum(0.0);
      ratio->SetMaximum(4.0);
      ratio->GetYaxis()->SetNdivisions(505); // N1 + 100 * N2 (small ticks and big ticks) defines the grid
      ratio->GetYaxis()->SetLabelSize(0.025);
      ratio->GetYaxis()->SetTitle("Data / MC");
      ratio->GetXaxis()->SetTicks("+");
      ratio->GetXaxis()->SetTitle(xaxis.c_str());
      ratio->GetXaxis()->SetLabelSize(0.025);
      ratio->Draw("pe");
      savePlot(c1, NameHisto.c_str());
    }
  }
}

void cmsPrelim( double intLumi, int Data)
{
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.90,0.92,"#sqrt{s} = 7 TeV");
  if (intLumi > 0.) {
    latex.SetTextAlign(31); // align right
    latex.DrawLatex(0.70,0.92,Form("L = %.1f pb^{-1}",intLumi));
  }
  latex.SetTextAlign(11); // align left
  if(Data==1) latex.DrawLatex(0.10,0.92,"CMS preliminary 2010");
  if(Data==0) latex.DrawLatex(0.10,0.92,"CMS Monte-Carlo 2010");
}

void savePlot(TCanvas * c, TString name) {
  c->SaveAs(name+".png");
  c->SaveAs(name+".eps");
  gSystem->Exec("epstopdf "+name+".eps");
}
