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

void cmsPrelim(double, int);
void savePlot(TCanvas*, TString);
void PhotonRecoIdEffCompare() {

  int selections = 3;
  int plots = 3;
  int entries = selections * plots;
  std::string Dir = "ExtraPlots";
  std::string SelHistos [] = {"Pt_All_BaS", "Pt_All_HHS", "Pt_All_HMS", "Pt_R05_BaS", "Pt_R05_HHS", "Pt_R05_HMS", "Pt_R09_BaS", "Pt_R09_HHS", "Pt_R09_HMS"};
  std::string NameHistos[] = {"Pt_All", "Pt_ R05", "Pt_R09"};

  std::vector<std::string> Histos; for(int i=0;i<entries; ++i) { Histos.push_back(SelHistos[i]); }
  std::vector<std::string> Names;  for(int i=0;i<plots; ++i)   {  Names.push_back(NameHistos[i]); }

  std::string xaxis  = "P_{T} [GeV/c]";
  std::string yaxis  = "Particles / 5 GeV [-]";

  std::vector< TH1F* > GenHist;
  std::vector< TH1F* > RecoHist;

  for (int ii=0; ii<entries; ++ii) {
    // if(ii != 8) continue;
    int Rebin = 1;
    std::string SelHisto = Histos[ii];
    std::cout<<"==== i = "<<ii<<" ==== "<<SelHisto<<" ===="<<std::endl;

    gROOT->SetStyle("Plain");
    gStyle->SetPalette(1,0);
    gStyle->SetOptStat(000000);
    gStyle->SetOptTitle(0);
    gStyle->SetGridStyle(3);
    gROOT->UseCurrentStyle();
    
    TCanvas * PhotonPt = new TCanvas("PhotonPt","PhotonPt",800,600);
    PhotonPt->SetFillColor(10);
    
    // Read Histograms
    // GJets_HT-100To200_madgraph_Fall10.root
    // GJets_HT-200_madgraph_Fall10.root
    // GJets_HT-40To100_madgraph_Fall10.root
    // PhotonGenEvent_100To200.root
    // PhotonGenEvent_200.root
    // PhotonGenEvent_40To100.root
    double lumi = 2355;
    std::string file_Gen_name  = "PhotonGenEvent_200.root";
    std::string file_Reco_name = "GJets_HT-200_madgraph_Fall10.root";

    TFile * file_Gen  = new TFile(file_Gen_name.c_str(),"READ");
    TFile * file_Reco = new TFile(file_Reco_name.c_str(),"READ");

    TH1F *G, *R;

    G = ((TH1F*) file_Gen->Get((Dir+"/"+SelHisto).c_str()));  G->Sumw2();
    R = ((TH1F*) file_Reco->Get((Dir+"/"+SelHisto).c_str())); R->Sumw2();
    // std::cout<<"Gen  Histo: "<<G<<std::endl;
    // std::cout<<"Reco Histo: "<<R<<std::endl;
    TH1F * GE, *RE;
    if(Rebin) {
      // manual rebinning
      // Rebin Scheme 1: 30 bins of 5 Gev | 10 bins of 15 GeV | 4 bins of 50 GeV
      double ptbinning [] = {0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0, 90.0, 95.0, 100.0, 105.0, 110.0, 115.0, 120.0, 125.0, 130.0, 135.0, 140.0, 145.0, 150.0, 165.0, 180.0, 195.0, 210.0, 225.0, 240.0, 255.0, 270.0, 285.0, 300.0, 350.0, 400.0, 450.0, 500.0};      
      GE = new TH1F("PH", "GE", 44, ptbinning); GE->Sumw2();
      RE = new TH1F("RE", "RE", 44, ptbinning); RE->Sumw2();
      int bins = G->GetNbinsX();
      double binwidth = 500.0/bins;
      double photons = 0.0, zbosons = 0.0;
      for(int iii=1; iii<=bins; ++iii) {
	double bin_lvalue = (0.0 + (iii-1)*binwidth);
	double bin_rvalue = (0.0 + (iii)*binwidth);
	for(int jj=1; jj<45; ++jj) {
	  if (bin_lvalue >=  ptbinning[jj-1] && bin_rvalue <= ptbinning[jj]) {
	    GE->AddBinContent(jj,G->GetBinContent(iii));
	    RE->AddBinContent(jj,R->GetBinContent(iii));
	    GE->SetBinError(jj,sqrt(pow(GE->GetBinError(jj),2)+pow(G->GetBinError(iii),2)));
	    RE->SetBinError(jj,sqrt(pow(RE->GetBinError(jj),2)+pow(R->GetBinError(iii),2)));
	  }
	}
      }
      for(int j=31; j<41; ++j) {
	GE->SetBinContent(j, GE->GetBinContent(j)/3); RE->SetBinContent(j, RE->GetBinContent(j)/3);
	GE->SetBinError(j,   GE->GetBinError(j)/3);   RE->SetBinError(j, RE->GetBinError(j)/3);
      }
      for(int j=41; j<45; ++j) {
	GE->SetBinContent(j, GE->GetBinContent(j)/10); RE->SetBinContent(j, RE->GetBinContent(j)/10);
	GE->SetBinError(j,   GE->GetBinError(j)/10);   RE->SetBinError(j, RE->GetBinError(j)/10);
      }
      double Gentotal = 0, Recototal = 0;
      int nGbx=GE->GetNbinsX(); for(int j=1; j<=nGbx; ++j) {Gentotal  += GE->GetBinContent(j);}
      int nRhx=RE->GetNbinsX(); for(int j=1; j<=nRhx; ++j) {Recototal += RE->GetBinContent(j);}
      std::cout<<"Entries in Reco histo = "<<Recototal<<" | Entries in Gen histo = "<<Gentotal<<" | Eff = "<<Recototal/Gentotal<<std::endl;
    }
    else {
      GE = (TH1F*)G->Clone();
      RE = (TH1F*)R->Clone();
    }
    GenHist.push_back(GE);
    RecoHist.push_back(RE);
  }
  for(int i=0; i<selections; ++i) {
    TCanvas * c1 = new TCanvas("c1","c1",800,600);
    c1->SetFillStyle(4000);
    c1->SetFillColor(4000);
    c1->SetFrameFillColor(4000);
    c1->SetFrameFillStyle(4000);
    c1->SetFrameBorderMode(0);
    c1->SetGridy();
    TH1 *R1 = 0, *R2 = 0, *R3 = 0;
    R1 = (TH1F*)GenHist[i]->Clone();
    R1->Divide(RecoHist[i], GenHist[i], 1, 1, "b");
    R2 = (TH1F*)GenHist[i+3]->Clone();
    R2->Divide(RecoHist[i+3], GenHist[i+3], 1, 1, "b");
    R3 = (TH1F*)GenHist[i+6]->Clone();
    R3->Divide(RecoHist[i+6], GenHist[i+6], 1, 1, "b");

    R1->SetLineColor(kBlue);   R2->SetLineColor(kMagenta);   R3->SetLineColor(kRed);
    R1->SetLineWidth(2);       R2->SetLineWidth(2);          R3->SetLineWidth(2);
    // R1->SetMarkerSize(2);      R2->SetMarkerSize(2);         R3->SetMarkerSize(2);
    R1->SetMarkerColor(kBlue); R2->SetMarkerColor(kMagenta); R3->SetMarkerColor(kRed);
    R1->SetMarkerStyle(20);    R2->SetMarkerStyle(21);       R3->SetMarkerStyle(34);

    R1->SetMinimum(-0.1);
    R1->SetMaximum(1.1);
    R1->GetYaxis()->SetNdivisions(510); // N1 + 100 * N2 (small ticks and big ticks) defines the grid
    R1->GetYaxis()->SetLabelSize(0.025);
    R1->GetYaxis()->SetTitle("Efficiency");
    R1->GetXaxis()->SetTicks("+");
    R1->GetXaxis()->SetTitle(xaxis.c_str());
    R1->GetXaxis()->SetLabelSize(0.025);
    R1->Draw("pe");
    R2->Draw("pesame");
    R3->Draw("pesame");

    // Coordinates for TLegend: x1, y1, x2, y2
    TLegend *l1 = new TLegend(0.55,0.575,0.85,0.675,NULL,"brNDC");
    l1->SetLineColor(0);
    l1->SetLineStyle(0);
    l1->SetLineWidth(0);
    l1->SetFillColor(4000);
    l1->SetBorderSize(0);
    l1->AddEntry(R1, "#Delta (#gamma - jet) > 0.0","lp");
    l1->AddEntry(R2, "#Delta (#gamma - jet) > 0.5","lp");
    l1->AddEntry(R3, "#Delta (#gamma - jet) > 0.9","lp");
    l1->Draw();
    double lumi = 0.0; // do not plot
    cmsPrelim(lumi, 0);
    std::string NameHisto = Names[i];
    savePlot(c1, NameHisto.c_str());
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
  // if (intLumi > 0.) {
  //   latex.SetTextAlign(31); // align right
  //   // latex.DrawLatex(0.85,0.84,Form("#int #font[12]{L} dt = %.1f pb^{-1}",intLumi));
  //   latex.DrawLatex(0.70,0.92,Form("L = %.1f pb^{-1}",intLumi));
  // }
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




