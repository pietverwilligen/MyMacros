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

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>

void cmsPrelim(double, int);
void savePlot(TCanvas*, TString);

void RA2PlotNewBinning() {

  bool fullaxis = false;
  int plots = 4;
  int categories = 7;
  int entries = plots * categories; // = 28 !!! Aanpassen !!!
  std::string dir = "RA2SEL/";
  std::string histarray[] = {"0_HT_All", "0_MHT_All", "0_PH_JCl_All", "0_PH_RJC_All", "1_HT_AJC", "1_MHT_AJC", "1_PH_JCl_AJC", "1_PH_RJC_AJC", 
			     "2_HT_AHC", "2_MHT_AHC", "2_PH_JCl_AHC", "2_PH_RJC_AHC", "3_HT_AAC", "3_MHT_AAC", "3_PH_JCl_AAC", "3_PH_RJC_AAC", 
			     "4_HT_AMC", "4_MHT_AMC", "4_PH_JCl_AMC", "4_PH_RJC_AMC", "6_HT_HHS", "6_MHT_HHS", "6_PH_JCl_HHS", "6_PH_RJC_HHS",
			     "7_HT_HMS", "7_MHT_HMS", "7_PH_JCl_HMS", "7_PH_RJC_HMS"};
  std::string xaxisarray[] = {"HT [GeV/c]", "MHT [GeV/c]", "#Delta #varphi_{#gamma - jet} [-]", "#Delta R_{#gamma - jet} [-]"};
  /*
  std::string yaxisarray[] = {"All Events / 5 GeV/c", "All Events / 5 GeV/c", "All Events / 0.101", "All Events / 0.10",
			      "Events after Jet cut / 5 GeV/c", "Events after Jet cut / 5 GeV/c", "Events after Jet cut / 0.101", "Events after Jet cut / 0.10",
			      "Events after HT cut / 5 GeV/c", "Events after HT cut / 5 GeV/c", "Events after HT cut / 0.101", "Events after HT cut / 0.10",
			      "Events after Angular cut / 5 GeV/c", "Events after Angular cut / 5 GeV/c", "Events after Angular cut / 0.101", "Events after Angular cut / 0.10",
			      "Events after MHT cut / 5 GeV/c", "Events after MHT cut / 5 GeV/c", "Events after MHT cut / 0.101", "Events after MHT cut / 0.10",
			      "Events after HHS cut / 5 GeV/c", "Events after HHS cut / 5 GeV/c", "Events after HHS cut / 0.101", "Events after HHS cut / 0.10",
			      "Events after HMS cut / 5 GeV/c", "Events after HMS cut / 5 GeV/c", "Events after HMS cut / 0.101", "Events after HMS cut / 0.10"};
  */
  std::string yaxisarray[] = {"All / 5 GeV/c", "All / 5 GeV/c", "All / 0.101", "All / 0.10",
			      "# 3 Jets / 5 GeV/c", "# 3 Jets / 5 GeV/c", "# 3 Jets / 0.101", "# 3 Jets / 0.10",
			      "# HT > 300 / 5 GeV/c", "# HT > 300 / 5 GeV/c", "# HT > 300 / 0.101", "# HT > 300 / 0.10",
			      "# Angular / 5 GeV/c", "# Angular / 5 GeV/c", "# Angular / 0.101", "# Angular / 0.10",
			      "# Baseline / 5 GeV/c", "# Baseline / 5 GeV/c", "# Baseline / 0.101", "# Baseline / 0.10",
			      "# High HT / 5 GeV/c", "# High HT / 5 GeV/c", "# High HT / 0.101", "# High HT / 0.10",
			      "# High MHT / 5 GeV/c", "# High MHT / 5 GeV/c", "# High MHT / 0.101", "# High MHT / 0.10"};

  std::string namearray[] = {"HT_All", "MHT_All", "DPHI_All", "DR_All", "HT_AJC", "MHT_AJC", "DPHI_AJC", "DR_AJC", "HT_AHC", "MHT_AHC", "DPHI_AHC", "DR_AHC", "HT_AAC", "MHT_AAC", "DPHI_AAC", "DR_AAC", "HT_AMC", "MHT_AMC", "DPHI_AMC", "DR_AMC", "HT_HHS", "MHT_HHS", "DPHI_HHS", "DR_HHS", "HT_HMS", "MHT_HMS", "DPHI_HMS", "DR_HMS"};

  std::vector<std::string> Histos; for(int i=0;i<entries; ++i) { Histos.push_back(histarray[i]); }
  std::vector<std::string> Xaxis;  for(int i=0;i<categories; ++i) { for(int j=0;j<plots; ++j) { Xaxis.push_back(xaxisarray[j]); } }
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
  // cross_sections.push_back(5760); // NNLO (4500@LO)
  cross_sections.push_back(4500); // NNLO (4500@LO)
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
    // if (ii != 19) continue;
    // if (ii > 7) continue;
    // 
    std::cout<<"==== i = "<<ii<<" ==== "<<Histos[ii]<<" ==== "<<Xaxis[ii]<<" ==== "<<Yaxis[ii]<<" ==== "<<std::endl;

    std::string SelHisto = Histos[ii];
    std::string xaxis = Xaxis[ii];
    std::string yaxis = Yaxis[ii];
    std::string NameHisto = Names[ii];
    
    Q1 = ((TH1F*) file_Q1->Get((dir+SelHisto).c_str()));
    Q2 = ((TH1F*) file_Q2->Get((dir+SelHisto).c_str()));
    Q3 = ((TH1F*) file_Q3->Get((dir+SelHisto).c_str()));
    Q4 = ((TH1F*) file_Q4->Get((dir+SelHisto).c_str()));
    E1 = ((TH1F*) file_E1->Get((dir+SelHisto).c_str()));
    E2 = ((TH1F*) file_E2->Get((dir+SelHisto).c_str()));
    E3 = ((TH1F*) file_E3->Get((dir+SelHisto).c_str()));
    P1 = ((TH1F*) file_P1->Get((dir+SelHisto).c_str()));
    P2 = ((TH1F*) file_P2->Get((dir+SelHisto).c_str()));
    P3 = ((TH1F*) file_P3->Get((dir+SelHisto).c_str()));
    
    D = ((TH1F*)  file_D->Get((dir+SelHisto).c_str()));
    Z = ((TH1F*)  file_Z->Get((dir+SelHisto).c_str()));
    
    // Final Histograms
    TH1F *Q, *P, *A, *E;
    Q = (TH1F*) Q1->Clone("QCD"); int n_Q = Q->GetNbinsX(); for (int i=1; i<=n_Q; ++i) {Q->SetBinContent(i,0.0); Q->SetBinError(i,0,0);}
    P = (TH1F*) P1->Clone("Sig"); int n_P = P->GetNbinsX(); for (int i=1; i<=n_P; ++i) {P->SetBinContent(i,0.0); P->SetBinError(i,0,0);}
    E = (TH1F*) E1->Clone("All"); int n_E = E->GetNbinsX(); for (int i=1; i<=n_E; ++i) {E->SetBinContent(i,0.0); E->SetBinError(i,0,0);}
    A = (TH1F*) Q1->Clone("All"); int n_A = A->GetNbinsX(); for (int i=1; i<=n_A; ++i) {A->SetBinContent(i,0.0); A->SetBinError(i,0,0);}

    // Q = new TH1F("QCD_Pt","QCD MC Photon Pt Distribution", 100, 0, 500);
    // P = new TH1F("Sig_Pt","Signal MC Photon Pt Distribution", 100, 0, 500);
    // A = new TH1F("All",   "All MC Photon Pt Distribution", 100, 0, 500);
    

    // Scaling: cross section [pb] x lumi [pb^-1] / number of events before any selection
    Q1->Sumw2(); Q1->Scale(scaling[0]); 
    Q2->Sumw2(); Q2->Scale(scaling[1]);
    Q3->Sumw2(); Q3->Scale(scaling[2]);
    Q4->Sumw2(); Q4->Scale(scaling[3]);

    E1->Sumw2(); E1->Scale(scaling[4]);
    E2->Sumw2(); E2->Scale(scaling[5]);
    E3->Sumw2(); E3->Scale(scaling[6]);
    
    P1->Sumw2(); P1->Scale(scaling[7]);
    P2->Sumw2(); P2->Scale(scaling[8]);
    P3->Sumw2(); P3->Scale(scaling[9]);

    Z->Sumw2(); Z->Scale(scaling[10]*5);
    D->Sumw2(); 

    Q->Add(Q1); Q->Add(Q2); Q->Add(Q3); Q->Add(Q4); 
    P->Add(P1); P->Add(P2); P->Add(P3); 
    E->Add(E1); E->Add(E2); E->Add(E3);

    THStack *as = new THStack("as","All Merge");
    E->SetFillColor(kYellow); as->Add(E);
    Q->SetFillColor(kGreen);  as->Add(Q);
    P->SetFillColor(kRed);    as->Add(P);
    A->Add(E); A->Add(Q); A->Add(P);

    TH1F *QC, *PH, *EW, *AA, *ZB, *DA;
    if(ii%4==2 || ii%4==3) { // NO REBIN
      QC = (TH1F*) Q->Clone("QCD"); // int n_Q = Q->GetNbinsX(); for (int i=1; i<=n_Q; ++i) {QC->SetBinContent(i,0.0); QC->SetBinError(i,0,0);}
      PH = (TH1F*) P->Clone("Sig"); // int n_P = P->GetNbinsX(); for (int i=1; i<=n_P; ++i) {PH->SetBinContent(i,0.0); PH->SetBinError(i,0,0);}
      EW = (TH1F*) E->Clone("All"); // int n_E = E->GetNbinsX(); for (int i=1; i<=n_E; ++i) {EW->SetBinContent(i,0.0); EW->SetBinError(i,0,0);}
      AA = (TH1F*) A->Clone("All"); // int n_A = A->GetNbinsX(); for (int i=1; i<=n_A; ++i) {AA->SetBinContent(i,0.0); AA->SetBinError(i,0,0);}
      ZB = (TH1F*) Z->Clone("All"); // int n_Z = Z->GetNbinsX(); for (int i=1; i<=n_Z; ++i) {ZB->SetBinContent(i,0.0); ZB->SetBinError(i,0,0);}
      DA = (TH1F*) D->Clone("All"); // int n_D = D->GetNbinsX(); for (int i=1; i<=n_D; ++i) {DA->SetBinContent(i,0.0); DA->SetBinError(i,0,0);}
    }
    else { // REBIN
      // manual rebinning
      // Rebin Scheme 1: 30 bins of 5 Gev | 10 bins of 15 GeV | 4 bins of 50 GeV + 10 bins of 50 GeV for HT plots = 54 bins
      int newbins = 0;
      // if(ii%4 == 0) newbins = 54;
      // else          newbins = 44;
      if(ii%2 == 0) newbins = 28; // HT up to 1500
      else          newbins = 16; // MHT up to 500       
      // std::cout<<"Counter: "<<ii<<" mod 4 : "<<ii%4<<" Amount of bins: "<<newbins<<std::endl;
      // double ptbinning [] = {0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0, 90.0, 95.0, 100.0, 105.0, 110.0, 115.0, 120.0, 125.0, 130.0, 135.0, 140.0, 145.0, 150.0, 165.0, 180.0, 195.0, 210.0, 225.0, 240.0, 255.0, 270.0, 285.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0, 850.0, 900.0, 950.0, 1000.0};
      double ptbinning [] = {0.0, 25.0, 50.0, 75.0, 100.0, 125.0, 150.0, 175.0, 200.0, 225.0, 250.0, 275.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0, 850.0, 900.0, 950.0, 1000.0, 1250.0, 1500.0, 1750.0, 2000.0, 2250.0, 2500.0};
      PH = new TH1F("PH", "PH", newbins, ptbinning); PH->Sumw2();
      QC = new TH1F("QC", "QC", newbins, ptbinning); QC->Sumw2();
      EW = new TH1F("EW", "EW", newbins, ptbinning); EW->Sumw2();
      DA = new TH1F("DA", "DA", newbins, ptbinning); DA->Sumw2();
      AA = new TH1F("DA", "DA", newbins, ptbinning); DA->Sumw2();
      ZB = new TH1F("ZB", "ZB", newbins, ptbinning); ZB->Sumw2();
      int bins = P->GetNbinsX();    // old binning
      double binwidth = 0.0;        // shouldnot make a difference
      // if (newbins == 54) binwidth = 1000/bins;
      // if (newbins == 44) binwidth = 500.0/bins; 
      if(fullaxis) {
        if (ii%2 == 0) binwidth = 1000.0/bins; // HT  !!! Binwidth of original file !!! do not touch
        if (ii%2 == 1) binwidth = 500.0/bins;  // MHT !!! Binwidth of original file !!! do not touch
      }
      else {
	if (ii%2 == 0) binwidth = 2500.0/bins;  // HT  !!! Binwidth of original file !!! do not touch
        if (ii%2 == 1) binwidth = 1000.0/bins;  // MHT !!! Binwidth of original file !!! do not touch
      }
      double photons = 0.0, zbosons = 0.0;
      for(int iii=1; iii<=bins; ++iii) {
	double bin_lvalue = (0.0 + (iii-1)*binwidth);
	double bin_rvalue = (0.0 + (iii)*binwidth);
	for(int jj=1; jj<newbins+1; ++jj) {
	  if (bin_lvalue >=  ptbinning[jj-1] && bin_rvalue <= ptbinning[jj]) {
	    PH->AddBinContent(jj,P->GetBinContent(iii));
	    QC->AddBinContent(jj,Q->GetBinContent(iii));
	    EW->AddBinContent(jj,E->GetBinContent(iii));
	    DA->AddBinContent(jj,D->GetBinContent(iii));
	    AA->AddBinContent(jj,A->GetBinContent(iii));
	    ZB->AddBinContent(jj,Z->GetBinContent(iii));
	    PH->SetBinError(jj,sqrt(pow(PH->GetBinError(jj),2)+pow(P->GetBinError(iii),2)));
	    QC->SetBinError(jj,sqrt(pow(QC->GetBinError(jj),2)+pow(Q->GetBinError(iii),2)));
	    EW->SetBinError(jj,sqrt(pow(EW->GetBinError(jj),2)+pow(E->GetBinError(iii),2)));
	    DA->SetBinError(jj,sqrt(pow(DA->GetBinError(jj),2)+pow(D->GetBinError(iii),2)));
	    AA->SetBinError(jj,sqrt(pow(AA->GetBinError(jj),2)+pow(A->GetBinError(iii),2)));
	    ZB->SetBinError(jj,sqrt(pow(ZB->GetBinError(jj),2)+pow(Z->GetBinError(iii),2)));
	  }
	}
      }
      // for(int j=31; j<41; ++j) { // 15 GeV binning
      for(int j=1; j<13; ++j) { // 25 GeV binning
	PH->SetBinContent(j, PH->GetBinContent(j)/5); PH->SetBinError(j, PH->GetBinError(j)/5);
	QC->SetBinContent(j, QC->GetBinContent(j)/5); QC->SetBinError(j, QC->GetBinError(j)/5);
	EW->SetBinContent(j, EW->GetBinContent(j)/5); EW->SetBinError(j, EW->GetBinError(j)/5);
	DA->SetBinContent(j, DA->GetBinContent(j)/5); DA->SetBinError(j, DA->GetBinError(j)/5);
	AA->SetBinContent(j, AA->GetBinContent(j)/5); AA->SetBinError(j, AA->GetBinError(j)/5);
	ZB->SetBinContent(j, ZB->GetBinContent(j)/5); ZB->SetBinError(j, ZB->GetBinError(j)/5);
      }
      // for(int j=41; j<newbins+1; ++j) { // 50 GeV binning
      for(int j=13; j<std::min(newbins+1,27); ++j) { // 50 GeV binning
	PH->SetBinContent(j, PH->GetBinContent(j)/10); PH->SetBinError(j, PH->GetBinError(j)/10);   
	QC->SetBinContent(j, QC->GetBinContent(j)/10); QC->SetBinError(j, QC->GetBinError(j)/10);   
	EW->SetBinContent(j, EW->GetBinContent(j)/10); EW->SetBinError(j, EW->GetBinError(j)/10);   
	DA->SetBinContent(j, DA->GetBinContent(j)/10); DA->SetBinError(j, DA->GetBinError(j)/10);   
	AA->SetBinContent(j, AA->GetBinContent(j)/10); AA->SetBinError(j, AA->GetBinError(j)/10);   
	ZB->SetBinContent(j, ZB->GetBinContent(j)/10); ZB->SetBinError(j, ZB->GetBinError(j)/10);
      }
      for(int j=27; j<newbins+1; ++j) { // 250 GeV binning
	PH->SetBinContent(j, PH->GetBinContent(j)/50); PH->SetBinError(j, PH->GetBinError(j)/50);   
	QC->SetBinContent(j, QC->GetBinContent(j)/50); QC->SetBinError(j, QC->GetBinError(j)/50);   
	EW->SetBinContent(j, EW->GetBinContent(j)/50); EW->SetBinError(j, EW->GetBinError(j)/50);   
	DA->SetBinContent(j, DA->GetBinContent(j)/50); DA->SetBinError(j, DA->GetBinError(j)/50);   
	AA->SetBinContent(j, AA->GetBinContent(j)/50); AA->SetBinError(j, AA->GetBinError(j)/50);   
	ZB->SetBinContent(j, ZB->GetBinContent(j)/50); ZB->SetBinError(j, ZB->GetBinError(j)/50);
      }
    }
     
    THStack *AS = new THStack("AS","All Merge");
    EW->SetFillColor(kYellow); AS->Add(EW);
    QC->SetFillColor(kGreen);  AS->Add(QC);
    PH->SetFillColor(kRed);    AS->Add(PH);
    ZB->SetLineColor(kBlue); ZB->SetLineWidth(2);
    
    // All MC + DATA
    TCanvas * c1 = new TCanvas("c","canvas",800,600);
    c1->cd();
    c1->SetLogy(1);
    AA->GetYaxis()->SetRangeUser(3e-4,1e5);
    // Request: how much entries in Delta R plot in 0.5 - 1.5
    if(ii%4==3) {
      double amount = AA->Integral(6,15);
      std::cout<<"Events in MC in 0.5 - 1.5 (bins 6 - 15): "<<AA->Integral(6,15)<<std::endl;
    }
    DA->SetMarkerStyle(20); DA->SetMarkerColor(kBlack); DA->SetLineColor(kBlack); DA->SetMarkerSize(0.75);
    AA->GetYaxis()->SetTitle(yaxis.c_str());
    AA->GetYaxis()->SetLabelSize(0.025);
    // A->GetYaxis()->SetTicks("+");
    // A->GetXaxis()->SetTitle(xaxis.c_str())
    AA->GetXaxis()->SetLabelSize(0.00);
    // AA->GetXaxis()->SetLabelSize(0.0000025);
    AA->GetXaxis()->SetTicks("+-");
    AA->Draw("HIST");
    AS->Draw("HISTsame");
    DA->Draw("sameE");
    ZB->Draw("sameH");
    gPad->RedrawAxis();
    gStyle->SetGridStyle(3);
    // Coordinates for TLegend: x1, y1, x2, y2
    double l_x1 = 0.60, l_x2 = 0.85, l_y1 = 0.75, l_y2 = 0.85; 
    if(ii%4==0 ||ii%4==1)       {l_x1 = 0.675; l_x2 = 0.875; l_y1 = 0.695; l_y2 = 0.895;}
    else if(ii%4==2 || ii%4==3) {l_x1 = 0.125; l_x2 = 0.325; l_y1 = 0.745; l_y2 = 0.895;}
    else {} //                  {l_x1 = 0.125; l_x2 = 0.325; l_y1 = 0.675; l_y2 = 0.875;}
    TLegend *l1 = new TLegend(l_x1,l_y1,l_x2,l_y2,NULL,"brNDC");
    l1->SetLineColor(0);
    l1->SetLineStyle(0);
    l1->SetLineWidth(0);
    l1->SetFillColor(4000);
    l1->SetBorderSize(0);
    l1->AddEntry(DA, "Data","pel");
    l1->AddEntry(ZB, "invisible Z x 5","l");
    l1->AddEntry(PH, "Photon: prompt","f");
    l1->AddEntry(QC, "QCD: prompt, frag & decay","f");
    l1->AddEntry(EW, "EWK: W,Z,t#bar{t}","f");
    l1->Draw();
    cmsPrelim(lumi, 1);
    c1->SetLogy(1);
    // Ratio Pads
    // ratio big : 2 ratio pads: 0.6 | 0.4
    double frst = 0.6;
    // ratio ratio1 : ratio2: 0.5 | 0.5
    double secd = 0.5;
    // std::cout<<"c1->GetTopMargin() = "<<c1->GetTopMargin()<<" | c1->GetBottomMargin() = "<<c1->GetBottomMargin()<<std::endl;
    c1->SetBottomMargin((1-frst) + frst*c1->GetBottomMargin()-(1-frst)*c1->GetTopMargin());
    TPad *ratioPad = new TPad("BottomPad","",0,0,1,1);
    ratioPad->SetTopMargin(frst - frst*ratioPad->GetBottomMargin()+(1-frst)*ratioPad->GetTopMargin());
    ratioPad->SetBottomMargin((1-secd) + secd*ratioPad->GetBottomMargin()-(1-secd)*ratioPad->GetTopMargin());
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
    std::cout<<"PH: bins = "<<PH->GetNbinsX()<<std::endl;
    std::cout<<"ZB: bins = "<<ZB->GetNbinsX()<<std::endl;
    ratio->Divide(DA, AA, 1, 1, "b");
    ratio->SetMinimum(-0.4);                                                                                                                                        
    ratio->SetMaximum(2.4);   
    ratio->GetYaxis()->SetNdivisions(505); // N1 + 100 * N2 (small ticks and big ticks) defines the grid
    ratio->GetYaxis()->SetLabelSize(0.025);
    //ratio->GetYaxis()->SetTitleSize(0.025);
    ratio->GetYaxis()->SetTitle("Data / MC");
    // ratio->GetYaxis()->SetTitleOffset(1.3);
    ratio->GetXaxis()->SetTicks("+-");
    ratio->GetXaxis()->SetLabelSize(0.00);
    // ratio->GetXaxis()->SetLabelSize(0.0000025);
    //ratio->GetXaxis()->SetTitle(xaxis.c_str());
    // ratio->GetXaxis()->SetLabelSize(0.025);
    ratio->Draw("pe");

    TPad *ratioPad2 = new TPad("BottomPad2","",0,0,1,1);

    ratioPad2->SetTopMargin((frst+secd*(1-frst)) - (frst+secd*(1-frst))*ratioPad2->GetBottomMargin()+(secd*(1-frst))*ratioPad2->GetTopMargin());
    ratioPad2->SetFillStyle(4000);
    ratioPad2->SetFillColor(4000);
    ratioPad2->SetFrameFillColor(4000);
    ratioPad2->SetFrameFillStyle(4000);
    ratioPad2->SetFrameBorderMode(0);
    ratioPad2->Draw();
    ratioPad2->cd();
    ratioPad2->SetGridy();
    TH1* ratio2 = 0;
    ratio2 = (TH1F*)ZB->Clone();
    // std::cout<<"PH: bins = "<<PH->GetNbinsX()<<std::endl;
    // std::cout<<"ZB: bins = "<<ZB->GetNbinsX()<<std::endl;
    ratio2->Divide(PH, ZB, 1, 1, "b");
    ratio2->SetMinimum(-0.4); 
    ratio2->SetMaximum(2.4);   
    ratio2->GetYaxis()->SetNdivisions(505); // N1 + 100 * N2 (small ticks and big ticks) defines the grid
    ratio2->GetYaxis()->SetLabelSize(0.025);
    // ratio2->GetYaxis()->SetTitleSize(0.025);    
    ratio2->GetYaxis()->SetTitle("#gamma / Z     ");
    // ratio2->GetYaxis()->SetTitleOffset(1.3);
    ratio2->GetXaxis()->SetTicks("+");
    ratio2->GetXaxis()->SetTitle(xaxis.c_str());
    ratio2->GetXaxis()->SetLabelSize(0.025);
    ratio2->Draw("pe");

    savePlot(c1, NameHisto.c_str());    
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
