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


void PTurnOn() {

  int entries = 3;
  std::string dir = "RA2SEL/";
  std::string NumHisto []   = {"4_PT_AMC", "6_PT_HHS", "7_PT_HMS"};
  std::string DenomHisto [] = {"3_PT_AAC", "3_PT_AAC", "3_PT_AAC"};
  std::string XaxisHisto    = "Photon PT [GeV/c]";
  std::string YaxisHisto    = "Events / 5 GeV/c";
  std::string NameHistos[]  = {"MC_P_AMC_Efficiency", "MC_P_HHS_Efficiency", "MC_P_HMS_Efficiency"};

  std::vector<std::string> NumHistos;   for(int i=0;i<entries; ++i) { NumHistos.push_back(NumHisto[i]); }
  std::vector<std::string> DenomHistos; for(int i=0;i<entries; ++i) { DenomHistos.push_back(DenomHisto[i]); }
  std::vector<std::string> Xaxis;  for(int i=0;i<entries; ++i) {  Xaxis.push_back(XaxisHisto); }
  std::vector<std::string> Yaxis;  for(int i=0;i<entries; ++i) {  Yaxis.push_back(YaxisHisto); }
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
  std::string file_Zb_name = "ZinvisibleJets_7TeV-madgraph_Fall10.root";

  TFile * file_P1 = new TFile(file_P1_name.c_str(),"READ");
  TFile * file_P2 = new TFile(file_P2_name.c_str(),"READ");
  TFile * file_P3 = new TFile(file_P3_name.c_str(),"READ");
  TFile * file_Zb = new TFile(file_Zb_name.c_str(),"READ");

  TH1F * P1i = ((TH1F*) file_P1->Get("EventCounters")); int P1a = P1i->GetBinContent(1);
  TH1F * P2i = ((TH1F*) file_P2->Get("EventCounters")); int P2a = P2i->GetBinContent(1);
  TH1F * P3i = ((TH1F*) file_P3->Get("EventCounters")); int P3a = P3i->GetBinContent(1);
  TH1F * Zbi = ((TH1F*) file_Zb->Get("EventCounters")); int Zba = Zbi->GetBinContent(1);

  // Cross Sections in pb
  // --------------------
  std::vector<double> cross_sections;
  // Photon cross sections
  cross_sections.push_back(23620.00); cross_sections.push_back(3476.00); cross_sections.push_back(485.00);
  // Zinv cross section
  cross_sections.push_back(5760); // NNLO (4500@LO)
  // Luminosity in pb
  // ----------------
  double lumi = 36.14;
  // double lumi = 500.00;
  // double lumi = 300.00;
  // Events in MC
  // ------------
  std::vector<double> events;
  events.push_back(P1a); events.push_back(P2a); events.push_back(P3a);  events.push_back(Zba);
  // Scaling
  // -------
  std::vector<double> scaling;
  for(int i=0; i<cross_sections.size(); ++i) {scaling.push_back(cross_sections[i]*lumi/events[i]);}


  for (int ii=0; ii<entries; ++ii) {
    // if(ii != 0) continue;
    std::cout<<"==== i = "<<ii<<" ===="<<std::endl;
    std::string NumHisto = NumHistos[ii];
    std::string DenomHisto = DenomHistos[ii];
    std::string NameHisto = Names[ii];
    std::string xaxis = Xaxis[ii];
    std::string yaxis = Yaxis[ii];

    TCanvas * PhotonPt = new TCanvas("PhotonPt","PhotonPt",800,600);
    PhotonPt->SetFillColor(10);
    
    TH1F * P1_num = ((TH1F*) file_P1->Get((dir+NumHisto).c_str())); P1_num->Sumw2();
    TH1F * P2_num = ((TH1F*) file_P2->Get((dir+NumHisto).c_str())); P2_num->Sumw2();
    TH1F * P3_num = ((TH1F*) file_P3->Get((dir+NumHisto).c_str())); P3_num->Sumw2();
    TH1F * Zb_num = ((TH1F*) file_Zb->Get((dir+NumHisto).c_str())); Zb_num->Sumw2();
    TH1F * P1_denom = ((TH1F*) file_P1->Get((dir+DenomHisto).c_str())); P1_denom->Sumw2();
    TH1F * P2_denom = ((TH1F*) file_P2->Get((dir+DenomHisto).c_str())); P2_denom->Sumw2();
    TH1F * P3_denom = ((TH1F*) file_P3->Get((dir+DenomHisto).c_str())); P3_denom->Sumw2();
    TH1F * Zb_denom = ((TH1F*) file_Zb->Get((dir+DenomHisto).c_str())); Zb_denom->Sumw2();

    // Final Histograms
    TH1F *Ph_num = (TH1F*) P1_num->Clone("Merge"); int n_P = Ph_num->GetNbinsX(); for (int j=1; j<=n_P; ++j) {Ph_num->SetBinContent(j,0.0);} Ph_num->Sumw2();
    // Scaling: cross section [pb] x lumi [pb^-1] / number of events before any selection
    P1_num->Sumw2(); P1_num->Scale(scaling[0]); // int nP1x=P1_num->GetNbinsX(); for(int j=1; j<=nP1x; ++j) {P1_num->SetBinError(j,P1_num->GetBinError(j)/sqrt(scaling[0]));}
    P2_num->Sumw2(); P2_num->Scale(scaling[1]); // int nP2x=P2_num->GetNbinsX(); for(int j=1; j<=nP2x; ++j) {P2_num->SetBinError(j,P2_num->GetBinError(j)/sqrt(scaling[1]));}
    P3_num->Sumw2(); P3_num->Scale(scaling[2]); // int nP3x=P3_num->GetNbinsX(); for(int j=1; j<=nP3x; ++j) {P3_num->SetBinError(j,P3_num->GetBinError(j)/sqrt(scaling[2]));}
    Ph_num->Add(P1_num); Ph_num->Add(P2_num); Ph_num->Add(P3_num);
    TH1F *Ph_denom = (TH1F*) P1_denom->Clone("Merge"); for (int j=1; j<=n_P; ++j) {Ph_denom->SetBinContent(j,0.0);} Ph_denom->Sumw2();
    // Scaling: cross section [pb] x lumi [pb^-1] / denomber of events before any selection
    P1_denom->Sumw2(); P1_denom->Scale(scaling[0]); // for(int j=1; j<=nP1x; ++j) {P1_denom->SetBinError(j,P1_denom->GetBinError(j)/sqrt(scaling[0]));}
    P2_denom->Sumw2(); P2_denom->Scale(scaling[1]); // for(int j=1; j<=nP2x; ++j) {P2_denom->SetBinError(j,P2_denom->GetBinError(j)/sqrt(scaling[1]));}
    P3_denom->Sumw2(); P3_denom->Scale(scaling[2]); // for(int j=1; j<=nP3x; ++j) {P3_denom->SetBinError(j,P3_denom->GetBinError(j)/sqrt(scaling[2]));}
    Ph_denom->Add(P1_denom); Ph_denom->Add(P2_denom); Ph_denom->Add(P3_denom);

    // Zb_num->Sumw2(); Zb_num->Scale(scaling[3]); int nZbx=Zb_num->GetNbinsX(); for(int j=1; j<=nZbx; ++j) {Zb_num->SetBinError(j,Zb->GetBinError(j)/sqrt(scaling[3]));}
    // Zb_denom->Sumw2(); Zb_denom->Scale(scaling[3]);                           for(int j=1; j<=nZbx; ++j) {Zb_denom->SetBinError(j,Zb->GetBinError(j)/sqrt(scaling[3]));}
    
    TH1F *PH_num, *PH_denom, *ZB_num, *ZB_denom;
    bool man_rebin = 0;
    if(man_rebin) {
      // manual rebinning
      double ptbinning [] = {0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0, 90.0, 95.0, 100.0, 105.0, 110.0, 115.0, 120.0, 125.0, 130.0, 135.0, 140.0, 145.0, 150.0, 165.0, 180.0, 195.0, 210.0, 225.0, 240.0, 255.0, 270.0, 285.0, 300.0, 350.0, 400.0, 450.0, 500.0};      
      PH_num   = new TH1F("PH_num",   "PH numerator",   44, ptbinning); PH_num->Sumw2();
      PH_denom = new TH1F("PH_denom", "PH denominator", 44, ptbinning); PH_denom->Sumw2();
      ZB_num   = new TH1F("ZB_num",   "ZB numerator",   44, ptbinning); ZB_num->Sumw2();
      ZB_denom = new TH1F("ZB_denom", "ZB denominator", 44, ptbinning); ZB_denom->Sumw2();
      int bins = Ph_num->GetNbinsX();
      double binwidth = 500.0/bins;
      double photons = 0.0, zbosons = 0.0;
      for(int iii=1; iii<=bins; ++iii) {
	double bin_lvalue = (0.0 + (iii-1)*binwidth);
	double bin_rvalue = (0.0 + (iii)*binwidth);
	for(int jj=1; jj<45; ++jj) {
	  if (bin_lvalue >=  ptbinning[jj-1] && bin_rvalue <= ptbinning[jj]) {
	    PH_num->AddBinContent(jj,Ph_num->GetBinContent(iii));
	    PH_denom->AddBinContent(jj,Ph_denom->GetBinContent(iii));
	    ZB_num->AddBinContent(jj,Zb_num->GetBinContent(iii));
	    ZB_denom->AddBinContent(jj,Zb_denom->GetBinContent(iii));
	  }
	}
      }
      for(int j=1; j<45; ++j)  {
	PH_num->SetBinError(j, sqrt(PH_num->GetBinContent(j))); PH_denom->SetBinError(j, sqrt(PH_denom->GetBinContent(j)));
	ZB_num->SetBinError(j, sqrt(ZB_num->GetBinContent(j))); ZB_denom->SetBinError(j, sqrt(ZB_denom->GetBinContent(j)));
      }
      for(int j=31; j<41; ++j) {
	PH_num->SetBinContent(j, PH_num->GetBinContent(j)/3); PH_denom->SetBinContent(j, PH_denom->GetBinContent(j)/3);
	PH_num->SetBinError(j,   PH_num->GetBinError(j)/3);   PH_denom->SetBinError(j, PH_denom->GetBinError(j)/3);
	ZB_num->SetBinContent(j, ZB_num->GetBinContent(j)/3); ZB_denom->SetBinContent(j, ZB_denom->GetBinContent(j)/3);
	ZB_num->SetBinError(j,   ZB_num->GetBinError(j)/3);   ZB_denom->SetBinError(j, ZB_denom->GetBinError(j)/3);
      }
      for(int j=41; j<45; ++j) {
	PH_num->SetBinContent(j, PH_num->GetBinContent(j)/10); PH_denom->SetBinContent(j, PH_denom->GetBinContent(j)/10);
	PH_num->SetBinError(j,   PH_num->GetBinError(j)/10);   PH_denom->SetBinError(j, PH_denom->GetBinError(j)/10);
	ZB_num->SetBinContent(j, ZB_num->GetBinContent(j)/10); ZB_denom->SetBinContent(j, ZB_denom->GetBinContent(j)/10);
	ZB_num->SetBinError(j,   ZB_num->GetBinError(j)/10);   ZB_denom->SetBinError(j, ZB_denom->GetBinError(j)/10);
      }
    }
    else {
      PH_num = (TH1F*)Ph_num->Clone();
      PH_denom = (TH1F*)Ph_denom->Clone();
      ZB_num = (TH1F*)Zb_num->Clone();
      ZB_denom = (TH1F*)Zb_denom->Clone();
    }

    // Check 
    PH_num->GetYaxis()->SetTitle(yaxis.c_str());
    PH_num->GetYaxis()->SetRangeUser(3e-4,1e4);
    PH_num->GetYaxis()->SetLabelSize(0.025);
    // PH_num->GetYaxis()->SetTicks("+");
    PH_num->GetXaxis()->SetLabelSize(0.0000025);
    PH_num->GetXaxis()->SetTicks("+-");
    
    PH_num->SetLineColor(1);
    PH_num->SetLineStyle(1);
    PH_num->SetLineWidth(2);
    PH_denom->SetLineColor(2);
    PH_denom->SetLineStyle(2);
    PH_denom->SetLineWidth(2);
    PH_num->Draw("HIST");
    PH_denom->Draw("HISTsame");
    // Coordinates for TLegend: x1, y1, x2, y2
    TLegend *l1 = new TLegend(0.35,0.725,0.85,0.875,NULL,"brNDC");
    l1->SetLineColor(0);
    l1->SetLineStyle(0);
    l1->SetLineWidth(0);
    l1->SetFillColor(4000);
    l1->SetBorderSize(0);
    l1->AddEntry(PH_denom, "Photon PT Before MHT Cut","l");
    l1->AddEntry(PH_num,   "Photon PT After MHT Cut","l");
    l1->Draw();
    cmsPrelim(lumi,-1);
    PhotonPt->SetLogy(1);
    PhotonPt->SetBottomMargin(0.4 + 0.6*PhotonPt->GetBottomMargin()-0.4*PhotonPt->GetTopMargin());
    TPad *ratioPad = new TPad("BottomPad","",0,0,1,1);
    ratioPad->SetTopMargin(0.6 - 0.6*ratioPad->GetBottomMargin()+0.4*ratioPad->GetTopMargin());
    ratioPad->SetFillStyle(4000);
    ratioPad->SetFillColor(4000);
    ratioPad->SetFrameFillColor(4000);
    ratioPad->SetFrameFillStyle(4000);
    ratioPad->SetFrameBorderMode(0);
    ratioPad->Draw();
    ratioPad->cd();
    ratioPad->SetGridy();
    TH1* ratio = 0;
    ratio = (TH1F*)PH_num->Clone();
    ratio->Divide(PH_num, PH_denom, 1, 1, "b"); 
    // b for binomial error calculation does not work fine
    /*
    int n_R = ratio->GetNbinsX(); 
    for (int j=1; j<=n_R; ++j) {
      if(ratio->GetBinContent(j)==0) ratio->SetBinError(j,0);
      else ratio->SetBinError(j,sqrt((ratio->GetBinContent(j)*(1-ratio->GetBinContent(j)))/PH_num->GetBinContent(j)));
    }
    */
    gStyle->SetGridStyle(3);
    ratio->SetMinimum(-0.2);
    ratio->SetMaximum(1.2);
    ratio->GetYaxis()->SetNdivisions(503); // N1 + 100 * N2 (small ticks and big ticks) defines the grid
    ratio->GetYaxis()->SetLabelSize(0.025);
    ratio->GetYaxis()->SetTitle("Efficiency");
    ratio->GetXaxis()->SetTicks("+");
    ratio->GetXaxis()->SetTitle(xaxis.c_str());
    ratio->GetXaxis()->SetLabelSize(0.025);
    ratio->Draw("e");
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
  if (intLumi > 0.) {
    latex.SetTextAlign(31); // align right
    // latex.DrawLatex(0.85,0.84,Form("#int #font[12]{L} dt = %.1f pb^{-1}",intLumi));
    if(Data==-2) latex.DrawLatex(0.70,0.92,"All MC, not rescaled");
    else if(Data==-1) latex.DrawLatex(0.70,0.92,Form("Max L = %.1f pb^{-1}", intLumi));
    else latex.DrawLatex(0.70,0.92,Form("L = %.1f pb^{-1}",intLumi));

  }
  latex.SetTextAlign(11); // align left
  //  latex.DrawLatex(0.18,0.96,"CMS preliminary 2010");
  if(Data== 1) latex.DrawLatex(0.10,0.92,"CMS preliminary 2010");
  if(Data== 0) latex.DrawLatex(0.10,0.92,"CMS Monte-Carlo 2010");
  if(Data==-1) latex.DrawLatex(0.10,0.92,"CMS Monte-Carlo 2010");
  if(Data==-2) latex.DrawLatex(0.10,0.92,"CMS Monte-Carlo 2010");
  // latex.DrawLatex(0.18,0.96,"CMS 2010");
}

void savePlot(TCanvas * c, TString name) {
   c->SaveAs(name+".png");
   c->SaveAs(name+".eps");
   gSystem->Exec("epstopdf "+name+".eps");
   std::cout<<"Plots saved"<<std::endl;
}




