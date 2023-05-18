#include "TCanvas.h"
#include "TStyle.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TLatex.h"
#include <stdio.h>
#include <iostream>
#include <TROOT.h> 
#include "TSystem.h"
#include <stdio.h>
#include <math.h>

void cmsPrelim(double, int);
void savePlot(TCanvas*, TString);


void DrellYan() {

    gROOT->SetStyle("Plain");
    gStyle->SetPalette(1,0);
    gStyle->SetOptStat(000000);
    gStyle->SetOptTitle(0);
    gStyle->SetGridStyle(3);
    gROOT->UseCurrentStyle();
    gStyle->SetOptStat(1111111);     

    // TCanvas * DrellYan = new TCanvas("Drell-Yan","Drell-Yan",800,600);
    // DrellYan->SetFillColor(10);
    
    // Read Histograms
    std::string file_DY_name = "histosZ_M_qt.root";
    TFile * file_DY = new TFile(file_DY_name.c_str(),"READ");
    TH2F *diMass, *ZMass;
    // Amount of processed events (MC) :
    diMass = ((TH2F*) file_DY->Get("h_diMass_vs_qt")); 
    ZMass  = ((TH2F*) file_DY->Get("h_Zmass_vs_qt")); 
    diMass->UseCurrentStyle();
    // diMass->Draw();


    // bin 0          = underflowbin
    // bin 1          = first bin
    // bin NbinsX     = last bin
    // bin NbinsX + 1 = overflowbin

    // Find Out the binning
    std::cout<<"X-axis: amount of bins = "<<diMass->GetNbinsX()<<" | Y-axis: amount of bins = "<<diMass->GetNbinsY()<<std::endl;
    double x1 = 0, x2 = 150, y1 = 20, y2 = 150;
    int ix0 = 1, ix150 = 150, iy20 = 1, iy150 = 130;
    int ix100 = 101, iy70 = 50;
    double err_20to70 = 0.0;  double i20to70  = diMass->IntegralAndError(ix100, ix150+1,  1 , 50,  err_20to70);
    double err_70to110 = 0.0; double i70to110 = diMass->IntegralAndError(ix100, ix150+1, 51 , 90,  err_70to110);
    double err_110 = 0.0;     double i110     = diMass->IntegralAndError(ix100, ix150+1, 91 , 131, err_110);
    std::cout<<"--------------------------------------------------------------------------"<<std::endl;
    std::cout<<" Events  100 < PT & 20 < M < 70  : "<<i20to70<<" pm "<<err_20to70 <<std::endl;
    std::cout<<" Events  100 < PT & 70 < M < 110 : "<<i70to110<<" pm "<<err_70to110<<std::endl;
    std::cout<<" Events  100 < PT & 110 < M      : "<<i110    <<" pm "<<err_110    <<std::endl;
    
    std::cout<<"Ratio 20to70 / 70to110  = "<<i20to70/i70to110        <<" pm "<<sqrt(pow(err_20to70/i20to70,2) + pow(err_70to110/i70to110, 2))<<std::endl;
    std::cout<<"Ratio 20to70 / 110to... = "<<i20to70/(i70to110+i110) <<" pm "<<i20to70/(i70to110+i110)*sqrt(pow(err_20to70/i20to70,2) + pow(err_70to110/i70to110, 2) + pow(err_110/i110, 2))<<std::endl;
    

    diMass->Sumw2();
    // Scale factors from Zinv with pt> 100 passing Baseling, High HT, High MHT
    double BS = 18.2/1722;
    double HS = 5.01/1722;
    double MS = 6.21/1722;
    // Scale to X-section
    double crosssection = 1300;
    double events = diMass->GetEntries();
    double lumi = 36.1;
    // diMass->Scale(crosssection*lumi/events);

    std::cout<<"--------------------------------------------------------------------------"<<std::endl;
    std::cout<<"Switch on scaling if you want this to work"<<std::endl;
    // Integral(Int_t binx1, Int_t binx2, Int_t biny1, Int_t biny2, Option_t* option = "")
    double err_all = 0.0; double all = diMass->IntegralAndError(ix100, ix150+1, iy20 , iy70, err_all);
    // in slices of 10 starting 
    double err_1 = 0.0; double i20to30 = diMass->IntegralAndError(ix100, ix150+1,  1 , 10, err_1);
    double err_2 = 0.0; double i30to40 = diMass->IntegralAndError(ix100, ix150+1, 11 , 20, err_2);
    double err_3 = 0.0; double i40to50 = diMass->IntegralAndError(ix100, ix150+1, 21 , 30, err_3);
    double err_4 = 0.0; double i50to60 = diMass->IntegralAndError(ix100, ix150+1, 31 , 40, err_4);
    double err_5 = 0.0; double i60to70 = diMass->IntegralAndError(ix100, ix150+1, 41 , 50, err_5);
    std::cout<<" Events  100 < PT & 20 < M < 70 : "<<all<<" pm "<<err_all<<"| Scaled to Baseline : "<<all*BS<<" | High HT : "<<all*HS<<" | High MHT : "<<all*MS<<std::endl;
    std::cout<<" "<<std::endl;
    std::cout<<" Events  100 < PT & 20 < M < 30 : "<<i20to30<<" pm "<<err_1<<"| Scaled to Baseline : "<<i20to30*BS<<" | High HT : "<<i20to30*HS<<" | High MHT : "<<i20to30*MS<<std::endl;
    std::cout<<" Events  100 < PT & 30 < M < 40 : "<<i30to40<<" pm "<<err_2<<"| Scaled to Baseline : "<<i30to40*BS<<" | High HT : "<<i30to40*HS<<" | High MHT : "<<i30to40*MS<<std::endl;
    std::cout<<" Events  100 < PT & 40 < M < 50 : "<<i40to50<<" pm "<<err_3<<"| Scaled to Baseline : "<<i40to50*BS<<" | High HT : "<<i40to50*HS<<" | High MHT : "<<i40to50*MS<<std::endl;
    std::cout<<" Events  100 < PT & 50 < M < 60 : "<<i50to60<<" pm "<<err_4<<"| Scaled to Baseline : "<<i50to60*BS<<" | High HT : "<<i50to60*HS<<" | High MHT : "<<i50to60*MS<<std::endl;
    std::cout<<" Events  100 < PT & 60 < M < 70 : "<<i60to70<<" pm "<<err_5<<"| Scaled to Baseline : "<<i60to70*BS<<" | High HT : "<<i60to70*HS<<" | High MHT : "<<i60to70*MS<<std::endl;

    // Vanaf 100
    if(1==1) {
      std::cout<<"--------------------------------------------------------------------------"<<std::endl;
      // Integral(Int_t binx1, Int_t binx2, Int_t biny1, Int_t biny2, Option_t* option = "")
      double err_all = 0.0; double all = diMass->IntegralAndError(ix100, ix150+1, iy20 , iy70, err_all);
      // in slices of 10 starting 
      double err_1 = 0.0; double i20to30 = diMass->IntegralAndError(ix100, ix150+1,  1 , 10, err_1);
      double err_2 = 0.0; double i30to40 = diMass->IntegralAndError(ix100, ix150+1, 11 , 20, err_2);
      double err_3 = 0.0; double i40to50 = diMass->IntegralAndError(ix100, ix150+1, 21 , 30, err_3);
      double err_4 = 0.0; double i50to60 = diMass->IntegralAndError(ix100, ix150+1, 31 , 40, err_4);
      double err_5 = 0.0; double i60to70 = diMass->IntegralAndError(ix100, ix150+1, 41 , 50, err_5);
      std::cout<<" Events  100 < PT & 20 < M < 70 : "<<all<<" pm "<<err_all<<std::endl;
      std::cout<<" "<<std::endl;
      std::cout<<" Events  100 < PT & 20 < M < 30 : "<<i20to30<<" pm "<<err_1<<std::endl;
      std::cout<<" Events  100 < PT & 30 < M < 40 : "<<i30to40<<" pm "<<err_2<<std::endl;
      std::cout<<" Events  100 < PT & 40 < M < 50 : "<<i40to50<<" pm "<<err_3<<std::endl;
      std::cout<<" Events  100 < PT & 50 < M < 60 : "<<i50to60<<" pm "<<err_4<<std::endl;
      std::cout<<" Events  100 < PT & 60 < M < 70 : "<<i60to70<<" pm "<<err_5<<std::endl;
      std::cout<<" "<<std::endl;
      double err_20to70 = 0.0;  double i20to70  = diMass->IntegralAndError(ix100, ix150+1,  1 , 50,  err_20to70);
      double err_70to110 = 0.0; double i70to110 = diMass->IntegralAndError(ix100, ix150+1, 51 , 90,  err_70to110);
      double err_110 = 0.0;     double i110     = diMass->IntegralAndError(ix100, ix150+1, 91 , 131, err_110);
      std::cout<<" Events  150 < PT & 20 < M < 70  : "<<i20to70<<" pm "<<err_20to70 <<std::endl;
      std::cout<<" Events  150 < PT & 70 < M < 110 : "<<i70to110<<" pm "<<err_70to110<<std::endl;
      std::cout<<" Events  150 < PT & 110 < M      : "<<i110    <<" pm "<<err_110    <<std::endl;
      std::cout<<" "<<std::endl;
      std::cout<<"Ratio 20to70 / 70to110 = "<<i20to70/i70to110        <<" pm "<<sqrt(pow(err_20to70/i20to70,2) + pow(err_70to110/i70to110, 2))<<std::endl;
      std::cout<<"Ratio 20to70 / 70to... = "<<i20to70/(i70to110+i110) <<" pm "<<i20to70/(i70to110+i110)*sqrt(pow(err_20to70/i20to70,2) + pow(err_70to110/i70to110, 2) + pow(err_110/i110, 2))<<std::endl;

    }
    // Vanaf 150
    if(2==2) {
      std::cout<<"--------------------------------------------------------------------------"<<std::endl;
      // Integral(Int_t binx1, Int_t binx2, Int_t biny1, Int_t biny2, Option_t* option = "")
      double err_all = 0.0; double all = diMass->IntegralAndError(ix150, ix150+1, iy20 , iy70, err_all);
      // in slices of 10 starting 
      double err_1 = 0.0; double i20to30 = diMass->IntegralAndError(ix150+1, ix150+1,  1 , 10, err_1);
      double err_2 = 0.0; double i30to40 = diMass->IntegralAndError(ix150+1, ix150+1, 11 , 20, err_2);
      double err_3 = 0.0; double i40to50 = diMass->IntegralAndError(ix150+1, ix150+1, 21 , 30, err_3);
      double err_4 = 0.0; double i50to60 = diMass->IntegralAndError(ix150+1, ix150+1, 31 , 40, err_4);
      double err_5 = 0.0; double i60to70 = diMass->IntegralAndError(ix150+1, ix150+1, 41 , 50, err_5);
      std::cout<<" Events  150 < PT & 20 < M < 70 : "<<all<<" pm "<<err_all<<std::endl;
      std::cout<<" "<<std::endl;
      std::cout<<" Events  150 < PT & 20 < M < 30 : "<<i20to30<<" pm "<<err_1<<std::endl;
      std::cout<<" Events  150 < PT & 30 < M < 40 : "<<i30to40<<" pm "<<err_2<<std::endl;
      std::cout<<" Events  150 < PT & 40 < M < 50 : "<<i40to50<<" pm "<<err_3<<std::endl;
      std::cout<<" Events  150 < PT & 50 < M < 60 : "<<i50to60<<" pm "<<err_4<<std::endl;
      std::cout<<" Events  150 < PT & 60 < M < 70 : "<<i60to70<<" pm "<<err_5<<std::endl;
      std::cout<<" "<<std::endl;
      double err_20to70 = 0.0;  double i20to70  = diMass->IntegralAndError(ix150, ix150+1,  1 , 50,  err_20to70);
      double err_70to110 = 0.0; double i70to110 = diMass->IntegralAndError(ix150, ix150+1, 51 , 90,  err_70to110);
      double err_110 = 0.0;     double i110     = diMass->IntegralAndError(ix150, ix150+1, 91 , 131, err_110);
      std::cout<<" Events  150 < PT & 20 < M < 70  : "<<i20to70<<" pm "<<err_20to70 <<std::endl;
      std::cout<<" Events  150 < PT & 70 < M < 110 : "<<i70to110<<" pm "<<err_70to110<<std::endl;
      std::cout<<" Events  150 < PT & 110 < M      : "<<i110    <<" pm "<<err_110    <<std::endl;
      std::cout<<" "<<std::endl;
      std::cout<<"Ratio 20to70 / 70to110 = "<<i20to70/i70to110        <<" pm "<<sqrt(pow(err_20to70/i20to70,2) + pow(err_70to110/i70to110, 2))<<std::endl;
      std::cout<<"Ratio 20to70 / 70to... = "<<i20to70/(i70to110+i110) <<" pm "<<i20to70/(i70to110+i110)*sqrt(pow(err_20to70/i20to70,2) + pow(err_70to110/i70to110, 2) + pow(err_110/i110, 2))<<std::endl;


    }
}

void cmsPrelim( double intLumi, int Data)
{
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  latex.SetTextAlign(31); // align right
  // latex.DrawLatex(0.90,0.96,"#sqrt{s} = 7 TeV");
  latex.DrawLatex(0.90,0.92,"#sqrt{s} = 7 TeV");
  if (intLumi > 0.) {
    latex.SetTextAlign(31); // align right
    // latex.DrawLatex(0.85,0.84,Form("#int #font[12]{L} dt = %.1f pb^{-1}",intLumi));
    latex.DrawLatex(0.70,0.92,Form("L = %.1f pb^{-1}",intLumi));
  }
  latex.SetTextAlign(11); // align left
  //  latex.DrawLatex(0.18,0.96,"CMS preliminary 2010");
  if(Data==1) latex.DrawLatex(0.10,0.92,"CMS preliminary 2010");
  if(Data==0) latex.DrawLatex(0.10,0.92,"CMS Monte-Carlo 2010");
  // latex.DrawLatex(0.18,0.96,"CMS 2010");
}

void savePlot(TCanvas * c, TString name) {
   c->SaveAs(name+".png");
   c->SaveAs(name+".eps");
   gSystem->Exec("epstopdf "+name+".eps");
   std::cout<<"Plots saved"<<std::endl;
}




