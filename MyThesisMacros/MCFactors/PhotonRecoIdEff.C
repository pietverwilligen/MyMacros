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
void PhotonRecoIdEff() {

  int entries = 9;
  std::string Dir = "ExtraPlots";
  std::string SelHistos [] = {"Pt_All_BaS", "Pt_All_HHS", "Pt_All_HMS", "Pt_R05_BaS", "Pt_R05_HHS", "Pt_R05_HMS", "Pt_R09_BaS", "Pt_R09_HHS", "Pt_R09_HMS"};
  std::string NameHistos[] = {"Pt_All_BaS", "Pt_All_HHS", "Pt_All_HMS", "Pt_R05_BaS", "Pt_R05_HHS", "Pt_R05_HMS", "Pt_R09_BaS", "Pt_R09_HHS", "Pt_R09_HMS"};

  std::vector<std::string> Histos; for(int i=0;i<entries; ++i) { Histos.push_back(SelHistos[i]); }
  std::vector<std::string> Names;  for(int i=0;i<entries; ++i) {  Names.push_back(NameHistos[i]); }

  std::string xaxis  = "P_{T} [GeV/c]";
  std::string yaxis  = "Particles / 5 GeV [-]";


  for (int ii=0; ii<entries; ++ii) {
    // if(ii != 8) continue;
    int Rebin = 1;
    std::string SelHisto = Histos[ii];
    std::string NameHisto = Names[ii];
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

    // Check 
    GE->GetYaxis()->SetTitle(yaxis.c_str());
    if(Rebin) GE->GetYaxis()->SetRangeUser(3e-3,3e3);
    else      GE->GetYaxis()->SetRangeUser(3e-3,3e2);
    GE->GetYaxis()->SetLabelSize(0.025);
    // GE->GetYaxis()->SetTicks("+");
    GE->GetXaxis()->SetLabelSize(0.0000025);
    GE->GetXaxis()->SetTicks("+-");
    
    GE->SetLineColor(1);
    GE->SetLineStyle(1);
    GE->SetLineWidth(2);
    RE->SetLineColor(2);
    RE->SetLineStyle(2);
    RE->SetLineWidth(2);
    GE->Draw();
    RE->Draw("same");
    // Coordinates for TLegend: x1, y1, x2, y2
    TLegend *l1 = new TLegend(0.55,0.575,0.85,0.675,NULL,"brNDC");
    l1->SetLineColor(0);
    l1->SetLineStyle(0);
    l1->SetLineWidth(0);
    l1->SetFillColor(4000);
    l1->SetBorderSize(0);
    l1->AddEntry(GE, "Generatorlevel","l");
    l1->AddEntry(RE, "Reconstruction","l");
    l1->Draw();
    cmsPrelim(lumi, 0);
    PhotonPt->SetLogy(1);
    double padsize = 0.5;
    PhotonPt->SetBottomMargin(padsize + (1-padsize)*PhotonPt->GetBottomMargin()-padsize*PhotonPt->GetTopMargin());
    TPad *ratioPad = new TPad("BottomPad","",0,0,1,1);
    ratioPad->SetTopMargin((1-padsize) - (1-padsize)*ratioPad->GetBottomMargin()+padsize*ratioPad->GetTopMargin());
    ratioPad->SetFillStyle(4000);
    ratioPad->SetFillColor(4000);
    ratioPad->SetFrameFillColor(4000);
    ratioPad->SetFrameFillStyle(4000);
    ratioPad->SetFrameBorderMode(0);
    ratioPad->Draw();
    ratioPad->cd();
    ratioPad->SetGridy();
    TH1* ratio = 0;
    ratio = (TH1F*)GE->Clone();
    ratio->Divide(RE, GE, 1, 1, "b");
    ratio->SetMinimum(-0.1);
    ratio->SetMaximum(1.1);
    ratio->GetYaxis()->SetNdivisions(510); // N1 + 100 * N2 (small ticks and big ticks) defines the grid
    ratio->GetYaxis()->SetLabelSize(0.025);
    ratio->GetYaxis()->SetTitle("Efficiency     ");
    ratio->GetXaxis()->SetTicks("+");
    ratio->GetXaxis()->SetTitle(xaxis.c_str());
    ratio->GetXaxis()->SetLabelSize(0.025);
    ratio->Draw("pe");
    savePlot(PhotonPt, NameHisto.c_str());
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




