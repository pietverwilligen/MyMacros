#include "TCanvas.h"
#include "TStyle.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "THStack.h"
#include "TGraph.h"
#include "TGraph2D.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TList.h"
#include "TGaxis.h"
#include "TPaletteAxis.h"
#include <stdio.h>
#include <TROOT.h>
#include "TSystem.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <algorithm>


void savePlot(TCanvas*, TString);

void ElectronicsComparison() {

  // double ATLAS_HVPoints[] = {7000, 7500, 8000, 8100, 8200, 8300, 8400, 8500, 8600, 8700, 8800, 8900, 9000, 9100, 9200, 9300, 9400, 9500, 9600, 9700};
  // double ATLAS_Triggers[] = { 300,  305,  300,  301,  300,  300,  300,  310,  300,  300,  320,  300,  300,  300,  300,  300,  300,  300,  300,  300};
  // double ATLAS_Events[]   = {   2,    5,    4,    5,    9,   17,   27,   64,  128,  183,  261,  265,  286,  290,  298,  295,  293,  297,  297,  297};

  // double CMS_HVPoints[] = {7500, 8000, 8500, 8800, 9000, 9200, 9400, 9600, 9800};
  // double CMS_Triggers[] = { 300,  341,  317,  300,  325,  300,  303,  300,  303};  
  // double CMS_Events[]   = {   2,    2,    4,    5,   33,  190,  276,  287,  294};

  double ATLAS_HVPoints[] = {8000, 8100, 8200, 8300, 8400, 8500, 8600, 8700, 8800, 8900, 9000, 9100, 9200, 9300, 9400, 9500, 9600, 9700};
  double ATLAS_Triggers[] = { 300,  301,  300,  300,  300,  310,  300,  300,  320,  300,  300,  300,  300,  300,  300,  300,  300,  300};
  double ATLAS_Events[]   = {   4,    5,    9,   17,   27,   64,  128,  183,  261,  265,  286,  290,  298,  295,  293,  297,  297,  297};

  double CMS_HVPoints[] = {8000, 8500, 8800, 9000, 9200, 9400, 9600, 9800};
  double CMS_Triggers[] = { 341,  317,  300,  325,  300,  303,  300,  303};  
  double CMS_Events[]   = {   2,    4,    5,   33,  190,  276,  287,  294};

  // Sigmoid Function to fit:
  //                                1
  // f(HV) = Eff_max * ---------------------------- , where lambda and HV50 are fitparameters.
  //                    1 + exp[-lambda*(HV-HV50)]
  // 
  //                 d Eff     lambda * Eff_max
  // Slope at HV50 = -----  =  ----------------
  //                 d HV            4
  // 
  const int ATLAS_num = 18; // 20 
  const int CMS_num = 8;    //  9

  double ATLAS_eff[ATLAS_num], ATLAS_err[ATLAS_num], ATLAS_HVerr[ATLAS_num];
  double CMS_eff[CMS_num],     CMS_err[CMS_num],     CMS_HVerr[CMS_num];

  for(int i=0; i<ATLAS_num; ++i) {
    ATLAS_eff[i] = ATLAS_Events[i] * 1.0 / ATLAS_Triggers[i];
    ATLAS_err[i] = sqrt( ATLAS_eff[i] * (1.0 - ATLAS_eff[i]) / ATLAS_Triggers[i] );
    ATLAS_HVerr[i] = 0.0;
  } 

  for(int i=0; i<CMS_num; ++i) {
    CMS_eff[i] = CMS_Events[i] * 1.0 / CMS_Triggers[i];
    CMS_err[i] = sqrt( CMS_eff[i] * (1.0 - CMS_eff[i]) / CMS_Triggers[i] );
    CMS_HVerr[i] = 0.0;
  }

  TStyle *plain = new TStyle("Plain","Plain Style (no colours/fill areas)");
  plain->cd();
  gStyle->SetOptStat(0);   // 10
  gStyle->SetOptFit(0); // 1011
  gStyle->SetOptTitle(0);


  TGraphErrors * ATLAS_points = new TGraphErrors(ATLAS_num, ATLAS_HVPoints, ATLAS_eff, ATLAS_HVerr, ATLAS_err);
  TGraphErrors * CMS_points   = new TGraphErrors(CMS_num,   CMS_HVPoints,   CMS_eff,   CMS_HVerr,   CMS_err);

  TF1 * sig1 = new TF1("sig1","[0]*1.0/(1.0+exp(-[1]*(x-[2])))",8000,10000);
  TF1 * sig2 = new TF1("sig2","[0]*1.0/(1.0+exp(-[1]*(x-[2])))",8000,10000);

  sig1->SetParameter(0, 0.98); // efficiency
  sig1->SetParameter(1,  0.5); // lambda
  sig1->SetParameter(2, 8700); // HV50

  sig1->SetLineWidth(2);
  sig1->SetLineColor(kRed);

  sig2->SetParameter(0, 0.98); // efficiency
  sig2->SetParameter(1,  0.5); // lambda
  sig2->SetParameter(2, 8700); // HV50

  sig2->SetLineWidth(2);
  sig2->SetLineColor(kBlack);

  TCanvas * c = new TCanvas("", "", 800, 600);
  c->cd();
  c->SetTicks(1,1);
  c->SetTitle("");
  // MarkerStyle :: 20 full circle :: 24 open circle
  ATLAS_points->SetMarkerStyle(20); ATLAS_points->SetMarkerSize(1.00); ATLAS_points->SetMarkerColor(kRed); ATLAS_points->SetLineWidth(2.25); ATLAS_points->SetLineColor(kRed);
  CMS_points->SetMarkerStyle(20);   CMS_points->SetMarkerSize(1.00);   CMS_points->SetMarkerColor(kBlack); CMS_points->SetLineWidth(2.25);   CMS_points->SetLineColor(kBlack);
  // ATLAS_points->Draw("AP");
  // CMS_points->Draw("PSame");
  // ATLAS_points->Fit("sig1", "V+", "ep");
  ATLAS_points->Draw("APE");
  ATLAS_points->Fit(sig1, "R");
  ATLAS_points->Draw("PESameS");
  c->Update();
  CMS_points->Draw("PESame");
  CMS_points->Fit(sig2, "R+", "SameS");
  CMS_points->Draw("PESameS");
  c->Update();
  ATLAS_points->GetXaxis()->SetTitle("HV (V)");
  ATLAS_points->GetYaxis()->SetTitle("Efficiency");
  double leg_x1 = 0.15, leg_x2 = 0.45, leg_y1 = 0.700, leg_y2 = 0.850;
  TLegend * l1 = new TLegend(leg_x1, leg_y1, leg_x2, leg_y2, NULL,"brNDC"); l1->SetLineColor(1);    l1->SetLineStyle(1);  l1->SetLineWidth(1);  l1->SetFillColor(4000); l1->SetBorderSize(1);
  l1->AddEntry(ATLAS_points, "new electronics", "lep");
  l1->AddEntry(CMS_points,   "CMS electronics", "lep");
  l1->Draw();
  c->Update();
  savePlot(c, "Marcello");
}

void savePlot(TCanvas * c, TString name) {
  c->SaveAs(name+".root");
  c->SaveAs(name+".png");
  c->SaveAs(name+".eps");
  gSystem->Exec("epstopdf "+name+".eps");
  std::cout<<"Plot "<<name<<" saved"<<std::endl;
}
