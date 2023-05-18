#include "TCanvas.h"
#include "TStyle.h"
#include "TFile.h"
#include "TH1F.h"
#include "TLegend.h"


void DY(){

  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1,0);
  gStyle->SetOptStat(000000);
  gStyle->SetOptTitle(0);
  gStyle->SetGridStyle(0);
  gROOT->UseCurrentStyle();

  TH1F * A = new TH1F("A", "DiMuonInvariantMass_DiMuonPt150ToInf",16,0,160);

  A->SetBinContent(1,0);
  A->SetBinContent(2,0);
  A->SetBinContent(3,12);
  A->SetBinContent(4,14);
  A->SetBinContent(5,18);
  A->SetBinContent(6,9);
  A->SetBinContent(7,20);
  A->SetBinContent(8,43);
  A->SetBinContent(9,418);
  A->SetBinContent(10,1020);
  A->SetBinContent(11,53);
  A->SetBinContent(12,23);
  A->SetBinContent(13,14);
  A->SetBinContent(14,10);
  A->SetBinContent(15,7);
  A->SetBinContent(16,32);


  A->GetXaxis()->SetTitle("DiMuonInvariantMass [GeV/c^{2}]");
  A->GetYaxis()->SetTitle("Entries in DiMuonPt150ToInf / 10 GeV/c^{2}");

  A->Draw();


}
