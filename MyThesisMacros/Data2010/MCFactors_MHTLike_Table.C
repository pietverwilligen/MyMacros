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

void MCFactors_MHTLike_Table() {

  int entries = 10; // !!! Aanpassen !!!
  std::string dir = "RA2SEL/";
  std::string SelHistos[]   = {"HT_All", "MHT_All", "HT_AJC", "MHT_AJC", "HT_AHC", "MHT_AHC", "HT_AAC", "MHT_AAC", "HT_AMC", "MHT_AMC"};
  std::string XaxisHisto[] = {"HT [GeV/c]", "MHT [GeV/c]","HT [GeV/c]", "MHT [GeV/c]","HT [GeV/c]", "MHT [GeV/c]","HT [GeV/c]", "MHT [GeV/c]","HT [GeV/c]", "MHT [GeV/c]"};
  std::string YaxisHisto[] = {"All Events / 5 GeV/c", "All Events / 5 GeV/c","Events after Jet cut / 5 GeV/c", "Events after Jet cut / 5 GeV/c","Events after HT cut / 5 GeV/c", "Events after HT cut / 5GeV/c","Events after Angular cut / 5 GeV/c", "Events after Angular cut / 5 GeV/c","Events after MHT cut / 5 GeV/c", "Events after MHT cut / 5 GeV/c"};
  std::string NameHistos[]  = {"HT_All", "MHT_All", "HT_AJC", "MHT_AJC", "HT_AHC", "MHT_AHC", "HT_AAC", "MHT_AAC", "HT_AMC", "MHT_AMC"};

  std::vector<std::string> Histos; for(int i=0;i<entries; ++i) {  Histos.push_back(SelHistos[i]); }
  std::vector<std::string> Xaxis;  for(int i=0;i<entries; ++i) {  Xaxis.push_back(XaxisHisto[i]); }
  std::vector<std::string> Yaxis;  for(int i=0;i<entries; ++i) {  Yaxis.push_back(YaxisHisto[i]); }
  std::vector<std::string> Names;  for(int i=0;i<entries; ++i) {  Names.push_back(NameHistos[i]); }

  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1,0);
  gStyle->SetOptStat(000000);
  gStyle->SetOptTitle(0);
  gStyle->SetGridStyle(0);
  gROOT->UseCurrentStyle();

  std::string file_P1_name = "GJets_HT-40To100_madgraph_Fall10.root";
  std::string file_P2_name = "GJets_HT-100To200_madgraph_Fall10.root";
  std::string file_P3_name = "GJets_HT-200_madgraph_Fall10.root";
  std::string file_Z_name  = "ZinvisibleJets_7TeV-madgraph_Fall10.root";

  TFile * file_P1 = new TFile(file_P1_name.c_str(),"READ");
  TFile * file_P2 = new TFile(file_P2_name.c_str(),"READ");
  TFile * file_P3 = new TFile(file_P3_name.c_str(),"READ");
  TFile * file_Z  = new TFile(file_Z_name.c_str(),"READ");

  TH1F * P1i = ((TH1F*) file_P1->Get("EventCounters")); int P1a = P1i->GetBinContent(1);
  TH1F * P2i = ((TH1F*) file_P2->Get("EventCounters")); int P2a = P2i->GetBinContent(1);
  TH1F * P3i = ((TH1F*) file_P3->Get("EventCounters")); int P3a = P3i->GetBinContent(1);
  TH1F * Zi = ((TH1F*)  file_Z->Get("EventCounters"));  int  Za  = Zi->GetBinContent(1);

  // Cross Sections in pb
  // --------------------                                                                                                                                                                               
  std::vector<double> cross_sections;
  // Photon cross sections
  cross_sections.push_back(23620.00); cross_sections.push_back(3476.00); cross_sections.push_back(485.00);
  // Zinv cross section
  cross_sections.push_back(5760); // NNLO (4500@LO)
  // Luminosity in pb
  // ----------------
  double lumi = 35.30;
  // Events in MC
  // ------------
  std::vector<double> events;
  events.push_back(P1a); events.push_back(P2a); events.push_back(P3a);  events.push_back(Za);
  // Scaling
  // --------
  std::vector<double> scaling;
  for(int i=0; i<cross_sections.size(); ++i) {scaling.push_back(cross_sections[i]*lumi/events[i]);}

  std::cout<<"Z scaling : x-section = "<<cross_sections[3]<<" | lumi = "<<lumi<<" | events = "<<events[3]<<" | scaling = "<<scaling[3]<<std::endl;

  // ===============================================
  // HISTOGRAMS                                     
  //                                                
  // ===============================================


  for (int ii=0; ii<entries; ++ii) {
    // if(ii != 0) continue;
    // std::cout<<"==== i = "<<ii<<" ===="<<std::endl;
    std::string SelHisto = Histos[ii];
    std::string NameHisto = Names[ii];
    std::string xaxis = Xaxis[ii];
    std::string yaxis = Yaxis[ii];
    
    TH1F * P1 = ((TH1F*) file_P1->Get((dir+SelHisto).c_str()));
    TH1F * P2 = ((TH1F*) file_P2->Get((dir+SelHisto).c_str()));
    TH1F * P3 = ((TH1F*) file_P3->Get((dir+SelHisto).c_str()));
    TH1F * Zb = ((TH1F*)  file_Z->Get((dir+SelHisto).c_str()));

    // Final Histograms
    TH1F *Ph, *PH, *ZB;
    Ph = (TH1F*) P1->Clone("Merge"); int n_P = Ph->GetNbinsX(); for (int j=1; j<=n_P; ++j) {Ph->SetBinContent(j,0.0);} Ph->Sumw2();
    // Scaling: cross section [pb] x lumi [pb^-1] / number of events before any selection
    P1->Sumw2(); P1->Scale(scaling[0]); int nP1x=P1->GetNbinsX(); for(int j=1; j<=nP1x; ++j) {P1->SetBinError(j,P1->GetBinError(j)/sqrt(scaling[0]));}
    P2->Sumw2(); P2->Scale(scaling[1]); int nP2x=P2->GetNbinsX(); for(int j=1; j<=nP2x; ++j) {P2->SetBinError(j,P2->GetBinError(j)/sqrt(scaling[1]));}
    P3->Sumw2(); P3->Scale(scaling[2]); int nP3x=P3->GetNbinsX(); for(int j=1; j<=nP3x; ++j) {P3->SetBinError(j,P3->GetBinError(j)/sqrt(scaling[2]));}
    Ph->Add(P1); Ph->Add(P2); Ph->Add(P3);
    Zb->Sumw2(); Zb->Scale(scaling[3]); int nZbx=Zb->GetNbinsX(); for(int j=1; j<=nZbx; ++j) {Zb->SetBinError(j,Zb->GetBinError(j)/sqrt(scaling[3]));}
    

    // manual rebinning
    double ptbinning [] = {0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0, 90.0, 95.0, 100.0, 105.0, 110.0, 115.0, 120.0, 125.0, 130.0, 135.0, 140.0, 145.0, 150.0, 165.0, 180.0, 195.0, 210.0, 225.0, 240.0, 255.0, 270.0, 285.0, 300.0, 350.0, 400.0, 450.0, 500.0};      
    PH = new TH1F("PH", "PH", 44, ptbinning); PH->Sumw2();
    ZB = new TH1F("ZB", "ZB", 44, ptbinning); ZB->Sumw2();
    int bins = Ph->GetNbinsX();
    double binwidth = 500.0/bins;
    double photons = 0.0, zbosons = 0.0;
    for(int iii=1; iii<=bins; ++iii) {
      double bin_lvalue = (0.0 + (iii-1)*binwidth);
      double bin_rvalue = (0.0 + (iii)*binwidth);
      for(int jj=1; jj<45; ++jj) {
	if (bin_lvalue >=  ptbinning[jj-1] && bin_rvalue <= ptbinning[jj]) {
	  PH->AddBinContent(jj,Ph->GetBinContent(iii));
	  ZB->AddBinContent(jj,Zb->GetBinContent(iii));
	}
      }
    }
    for(int j=1; j<45; ++j)  {PH->SetBinError(j, sqrt(PH->GetBinContent(j))); ZB->SetBinError(j, sqrt(ZB->GetBinContent(j)));}
    for(int j=31; j<41; ++j) {
      PH->SetBinContent(j, PH->GetBinContent(j)/3); ZB->SetBinContent(j, ZB->GetBinContent(j)/3);
      PH->SetBinError(j,   PH->GetBinError(j)/3);   ZB->SetBinError(j, ZB->GetBinError(j)/3);
    }
    for(int j=41; j<45; ++j) {
      PH->SetBinContent(j, PH->GetBinContent(j)/10); ZB->SetBinContent(j, ZB->GetBinContent(j)/10);
      PH->SetBinError(j,   PH->GetBinError(j)/10);   ZB->SetBinError(j, ZB->GetBinError(j)/10);
    }

    // Scale to full Z sample
    // ZB->Scale(100.00/20.00); 
    // TH1F *ZP = (TH1F*) ZB->Clone("Ratio"); int n_ZP = ZB->GetNbinsX(); for (int j=1; j<=n_ZP; ++j) {ZP->SetBinContent(j,0.0);} ZP->Sumw2();
    // ZP->Divide(ZB,PH,1,1);
    // ZP->Draw();   
    // Vanaf Z/G > 100 GeV
    double Ztotal = 0.0, Gtotal = 0.0, Rtotal = 0.0; 
    double Zerr = 0.0, Gerr = 0.0, Rerr = 0.0;
    for(int i=21; i<45; ++i) {
      Gtotal += PH->GetBinContent(i);
      Ztotal += ZB->GetBinContent(i);
      // Rtotal += ZP->GetBinContent(i);
      // std::cout<<"Bin "<<i<<" PH = "<<PH->GetBinContent(i)<<" sqrt = "<<sqrt(PH->GetBinContent(i))<<" err = "<<PH->GetBinError(i)<<std::endl;
      // std::cout<<"Bin "<<i<<" ZB = "<<ZB->GetBinContent(i)<<" sqrt = "<<sqrt(ZB->GetBinContent(i))<<" err = "<<ZB->GetBinError(i)<<std::endl;
      // std::cout<<"Bin "<<i<<" ZP = "<<ZP->GetBinContent(i)<<" sqrt = "<<sqrt(ZP->GetBinContent(i))<<" err = "<<ZP->GetBinError(i)<<std::endl;
      Gerr += (PH->GetBinContent(i))*(PH->GetBinContent(i));
      Zerr += (ZB->GetBinContent(i))*(ZB->GetBinContent(i));
      // Rerr += (ZP->GetBinContent(i))*(ZP->GetBinContent(i));
    }
    Gerr = sqrt(Gerr);
    Zerr = sqrt(Zerr);
    // Rerr = sqrt(Rerr);
    double value = Ztotal/Gtotal;
    double err1 = value*(Zerr/Ztotal + Gerr/Gtotal);
    std::cout<<NameHisto<<"| # Z bosons = "<<Ztotal<<" | # Photons = "<<Gtotal<<" | Z/P = "<<value<<" err = "<<err1<<std::endl; //" R = "<<Rtotal/24<<" Rerr = "<<Rerr/24<<std::endl;
    delete Ph;
    delete PH;
    delete ZB;
  }
}
