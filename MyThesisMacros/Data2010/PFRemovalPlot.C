#include "TCanvas.h"
#include "TStyle.h"
#include "TFile.h"
#include "TH1F.h"
#include "TLegend.h"
#include "/home/piet/setTDRStyle.C"


void PFRemovalPlot() {

  int entries = 6; // !!! Aanpassen !!!
  // std::string dir = "RECO/RECO_3Jets_Egamma/";
  std::string dir = "RECO/Event/";
  std::string histarray[] = {"PtJet_GenPtPhoton_All","PtJet_GenPtPhoton_DeltaR01","PtJet_GenPtPhoton_DeltaR04","PtJet_PtPhoton_All","PtJet_PtPhoton_DeltaR01","PtJet_PtPhoton_DeltaR04"};
  std::string title[] = {"All Events", "Events with PFJet in #Delta R < 0.1", "Events with PFJet in 0.1 < #Delta R < 0.4"}; 
  std::string xaxis1 = "Gen Photon p_{T} [GeV/c]";
  std::string xaxis2 = "Reco Photon p_{T} [GeV/c]";
  std::string yaxis = "Closesth PF Jet p_{T}";

  std::vector<std::string> Histos; for(int i=0;i<entries; ++i) { Histos.push_back(histarray[i]); }

  // ===============================================
  // COMMON STUFF
  //
  // ===============================================

  //
  // setTDRStyle();
  //tdrStyle->SetOptStat(0000000);
  //tdrStyle->SetTitleSize(0.05, "XYZ");

  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1,0);
  gStyle->SetOptStat(000000);
  // gStyle->SetOptStat(111111);
  gStyle->SetOptTitle(0);
  // gStyle->SetGridStyle(0);
  gROOT->UseCurrentStyle();
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.15);

  std::string file_name = "GJets_HT-200_madgraph_Fall10_PLOT.root";
  TFile * file = new TFile(file_name.c_str(),"READ");

  // TCanvas * c1 = new TCanvas("c","canvas",1000,600);
  TCanvas * c1 = new TCanvas("c","canvas",900,300);
  //   c1->Divide(3,2);
  c1->Divide(3,1);
  for(int i=0; i<6; ++i) {
    if(i<3) continue;
    // c1->cd(i+1);
    c1->cd(i-2);
    H = ((TH2F*) file->Get((dir+histarray[i]).c_str()));   
    H->Draw("colz");
    H->GetYaxis()->SetTitle(yaxis.c_str());
    if(i<3) H->GetXaxis()->SetTitle(xaxis1.c_str());
    else H->GetXaxis()->SetTitle(xaxis2.c_str());
    H->GetYaxis()->SetTitle(yaxis.c_str());
    H->GetYaxis()->SetTitleOffset(1.5);
    if(i<3) H->SetTitle((title[i]).c_str());
    else H->SetTitle((title[i-3]).c_str());
  }
  savePlot(c1, "PFJetRemoval");
}

void savePlot(TCanvas * c, TString name) {
  c->SaveAs(name+".png");
  c->SaveAs(name+".eps");
  gSystem->Exec("epstopdf "+name+".eps");
}
