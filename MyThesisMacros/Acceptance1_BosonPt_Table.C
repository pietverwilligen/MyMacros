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

void Acceptance1_BosonPt_Table() {

  int entries = 8; // !!! Aanpassen !!!
  std::string SelHistos [] = {"Boson_0J_BA/Eta", "Boson_1J_BA/Eta", "Boson_2J_BA/Eta", "Boson_3J_BA/Eta", "Boson_0J_BA_100/Eta", "Boson_1J_BA_100/Eta", "Boson_2J_BA_100/Eta", "Boson_3J_BA_100/Eta"};
  std::string NameHistos[] = {"Boson_0J_BA_Eta", "Boson_1J_BA_Eta", "Boson_2J_BA_Eta", "Boson_3J_BA_Eta", "Boson_0J_BA_100_Eta", "Boson_1J_BA_100_Eta", "Boson_2J_BA_100_Eta", "Boson_3J_BA_100_Eta"};

  std::vector<std::string> Histos; for(int i=0;i<entries; ++i) { Histos.push_back(SelHistos[i]); }
  std::vector<std::string> Names;  for(int i=0;i<entries; ++i) {  Names.push_back(NameHistos[i]); }

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
    std::string file_Zb_name =  "ZbosonGenEvent.root";
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
    std::vector<double> cross_sections; cross_sections.push_back(23620.00); cross_sections.push_back(3476.00); cross_sections.push_back(485.00); cross_sections.push_back(5760);
    // Luminosity in pb
    double lumi = 35.30;
    // Events in MC
    std::vector<double> scaling;
    std::vector<double> events; events.push_back(P1a); events.push_back(P2a); events.push_back(P3a); events.push_back(Zba);
    // Scaling
    for(int i=0; i<cross_sections.size(); ++i) {scaling.push_back(cross_sections[i]*lumi/events[i]);}
    std::cout<<"Z scaling : x-section = "<<cross_sections[3]<<" | lumi = "<<lumi<<" | events = "<<events[3]<<" | scaling = "<<scaling[3]<<std::endl;

  for (int ii=0; ii<entries; ++ii) {
    // std::cout<<"==== i = "<<ii<<" ===="<<std::endl;
    std::string SelHisto = Histos[ii];
    std::string NameHisto = Names[ii];

    P1 = ((TH1F*) file_P1->Get(SelHisto.c_str())); TH1F *P1_ = (TH1F*) P1->Clone();
    P2 = ((TH1F*) file_P2->Get(SelHisto.c_str())); TH1F *P2_ = (TH1F*) P2->Clone();
    P3 = ((TH1F*) file_P3->Get(SelHisto.c_str())); TH1F *P3_ = (TH1F*) P3->Clone();
    Zb = ((TH1F*) file_Zb->Get(SelHisto.c_str())); TH1F *Zb_ = (TH1F*) Zb->Clone();
    // Final Histograms
    TH1F *Ph = (TH1F*) P1->Clone("Merge"); int n_P = Ph->GetNbinsX(); for (int j=1; j<=n_P; ++j) {Ph->SetBinContent(j,0.0);} Ph->Sumw2();
    // Scaling: cross section [pb] x lumi [pb^-1] / number of events before any selection
    P1->Sumw2(); P1->Scale(scaling[0]); // int nP1x=P1->GetNbinsX(); for(int j=1; j<=nP1x; ++j) {P1->SetBinError(j,P1->GetBinError(j)/sqrt(scaling[0]));}
    P2->Sumw2(); P2->Scale(scaling[1]); // int nP2x=P2->GetNbinsX(); for(int j=1; j<=nP2x; ++j) {P2->SetBinError(j,P2->GetBinError(j)/sqrt(scaling[1]));}
    P3->Sumw2(); P3->Scale(scaling[2]); // int nP3x=P3->GetNbinsX(); for(int j=1; j<=nP3x; ++j) {P3->SetBinError(j,P3->GetBinError(j)/sqrt(scaling[2]));}
    Ph->Add(P1); Ph->Add(P2); Ph->Add(P3);
    // for (int j=1; j<=n_P; ++j) {
    // Ph->SetBinError(j,sqrt(P1_->GetBinContent(j)+P2_->GetBinContent(j)+P3_->GetBinContent(j)));
    // Ph->SetBinError(j,sqrt(P1_->GetBinContent(j)/sqrt(scaling[0])+P2_->GetBinContent(j)/sqrt(scaling[1])+P3_->GetBinContent(j)/sqrt(scaling[2])));
    // }
    Zb->Sumw2(); Zb->Scale(scaling[3]);
    // Scale to full Z sample
    // <<Zb->Scale(100.00/20.00);
    // int nZbx=Zb->GetNbinsX();
    // for(int j=1; j<=nZbx; ++j) {
    // Zb->SetBinError(j,sqrt(Zb_->GetBinContent(j)));
    // Zb->SetBinError(j,Zb->GetBinError(j)/sqrt(scaling[3]));
    // }
    
    TH1F * PH, *ZB;
    PH = (TH1F*)Ph->Clone();
    ZB = (TH1F*)Zb->Clone();
    // For Eta Plots: Do Acceptance Calculation: Sum All Events Z [-inf, inf] / All Events Photon [-2.5,2.5]
    // For Scaled Luminosity
    double Ztotal = 0, Ptotal1 = 0, Ptotal2 = 0;
    double lb = 0, rb=0;
    int nZbx=Zb->GetNbinsX(); for(int j=1; j<=nZbx; ++j) {Ztotal += Zb->GetBinContent(j);}
    int nPhx=Ph->GetNbinsX(); for(int j=1; j<=nPhx; ++j) {
      lb = (-5.0 + j*10.0/nPhx); rb = (-5.0 + (j+1)*10.0/nPhx); 
      if(lb >= -2.4 && rb <= 2.4) {Ptotal1 += Ph->GetBinContent(j);}
      if(lb >= -2.6 && rb <= 2.6) {Ptotal2 += Ph->GetBinContent(j);}
    }
    // std::cout<<"Entries in Z histo = "<<Ztotal<<" | Entries in P histo in ecal range [-2.4,2.4] = "<<Ptotal1<<" | Z full range / P ecal range = "<<Ztotal/Ptotal1<<std::endl;
    // std::cout<<"Entries in Z histo = "<<Ztotal<<" | Entries in P histo in ecal range [-2.6,2.6] = "<<Ptotal2<<" | Z full range / P ecal range = "<<Ztotal/Ptotal2<<std::endl;
    std::cout<<NameHisto<<" | # Photons in [-2.4, 2.4] = "<<Ptotal1<<" | # Z events = "<<Ztotal<<" | & "<<Ztotal/Ptotal1<<" \pm "<<sqrt(Ztotal*(1-Ztotal/Ptotal1))/Ptotal1<<" &"<<Ztotal/Ptotal2<<" \pm "<<sqrt(Ztotal*(1-Ztotal/Ptotal2))/Ptotal2<<std::endl;

  }

}
