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


void MCFactors_BosonPT_AllPlots() {

  int entries = 4; // !!! Aanpassen !!!
  std::string dir = "RA2SEL/";
  std::string SelHistos[]   = {"1_PT_AJC", "2_PT_AHC", "3_PT_AAC", "4_PT_AMC"};
  std::string XaxisHisto[] = {"Boson PT [GeV/c]", "Boson PT [GeV/c]", "Boson PT [GeV/c]", "Boson PT [GeV/c]"};
  std::string YaxisHisto[] = {"Events after Jet cut / 5 GeV/c", "Events after HT cut / 5 GeV/c", "Events after Angular cut / 5 GeV/c","Events after MHT cut / 5 GeV/c"};
  std::string NameHistos[]  = {"Boson_PT_AJC", "Boson_PT_AHC", "Boson_PT_AAC", "Boson_PT_AMC"};

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
  // std::string file_Z_name  = "ZinvisibleJets_7TeV-madgraph_Fall10.root";
  std::string file_Z_name  = "ZinvisibleJets_7TeV-madgraph_Fall10_100GeV.root";

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
  cross_sections.push_back(4500); // NNLO (4500@LO)
  // Luminosity in pb
  // ----------------
  double lumi = 36.14;
  // Events in MC
  // ------------
  std::vector<double> events;
  events.push_back(P1a); events.push_back(P2a); events.push_back(P3a);  events.push_back(Za);
  // Scaling
  // --------
  std::vector<double> scaling;
  for(int i=0; i<cross_sections.size(); ++i) {scaling.push_back(cross_sections[i]*lumi/events[i]);}


  // ===============================================
  // HISTOGRAMS                                     
  //                                                
  // ===============================================

  for (int ii=0; ii<entries; ++ii) {
    // if(ii != 0) continue; 
    std::cout<<"==== i = "<<ii<<" ===="<<std::endl;
    std::cout<<Names[ii]<<std::endl;
    std::string SelHisto = Histos[ii];
    std::string NameHisto = Names[ii];
    std::string xaxis = Xaxis[ii];
    std::string yaxis = Yaxis[ii];


    
    TCanvas * PhotonPt = new TCanvas("PhotonPt","PhotonPt",800,600);
    PhotonPt->SetFillColor(10);
    
    TH1F * P1 = ((TH1F*) file_P1->Get((dir+SelHisto).c_str())); P1->Sumw2();
    TH1F * P2 = ((TH1F*) file_P2->Get((dir+SelHisto).c_str())); P2->Sumw2();
    TH1F * P3 = ((TH1F*) file_P3->Get((dir+SelHisto).c_str())); P3->Sumw2();
    TH1F * Zb = ((TH1F*)  file_Z->Get((dir+SelHisto).c_str())); Zb->Sumw2();

    // Final Histograms
    TH1F *Ph = (TH1F*) P1->Clone("Merge"); int n_P = Ph->GetNbinsX(); for (int j=1; j<=n_P; ++j) {Ph->SetBinContent(j,0.0);} Ph->Sumw2();
    // Scaling: cross section [pb] x lumi [pb^-1] / number of events before any selection
    P1->Sumw2(); P1->Scale(scaling[0]); // int nP1x=P1->GetNbinsX(); for(int j=1; j<=nP1x; ++j) {P1->SetBinError(j,P1->GetBinError(j)/sqrt(scaling[0]));}
    P2->Sumw2(); P2->Scale(scaling[1]); // int nP2x=P2->GetNbinsX(); for(int j=1; j<=nP2x; ++j) {P2->SetBinError(j,P2->GetBinError(j)/sqrt(scaling[1]));}
    P3->Sumw2(); P3->Scale(scaling[2]); // int nP3x=P3->GetNbinsX(); for(int j=1; j<=nP3x; ++j) {P3->SetBinError(j,P3->GetBinError(j)/sqrt(scaling[2]));}
    Ph->Add(P1); Ph->Add(P2); Ph->Add(P3);
    Zb->Sumw2(); Zb->Scale(scaling[3]); // int nZbx=Zb->GetNbinsX(); for(int j=1; j<=nZbx; ++j) {Zb->SetBinError(j,Zb->GetBinError(j)/sqrt(scaling[3]));}
    
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
	  PH->SetBinError(jj,sqrt(pow(PH->GetBinError(jj),2)+pow(Ph->GetBinError(iii),2)));
	  ZB->SetBinError(jj,sqrt(pow(ZB->GetBinError(jj),2)+pow(Zb->GetBinError(iii),2)));
	}
      }
    }
    // for(int j=1; j<45; ++j)  {PH->SetBinError(j, sqrt(Ph->GetBinContent(j))); ZB->SetBinError(j, sqrt(Zb->GetBinContent(j)));}                                                                              
    for(int j=31; j<41; ++j) {
      PH->SetBinContent(j, PH->GetBinContent(j)/3); ZB->SetBinContent(j, ZB->GetBinContent(j)/3);
      PH->SetBinError(j,   PH->GetBinError(j)/3);   ZB->SetBinError(j, ZB->GetBinError(j)/3);
    }
    for(int j=41; j<45; ++j) {
      PH->SetBinContent(j, PH->GetBinContent(j)/10); ZB->SetBinContent(j, ZB->GetBinContent(j)/10);
      PH->SetBinError(j,   PH->GetBinError(j)/10);   ZB->SetBinError(j, ZB->GetBinError(j)/10);
    }
    // manual pt cut @ 100 GeV/c
    for(int j=1; j<=20; ++j) {ZB->SetBinContent(j,0); ZB->SetBinError(j,0);}
    for(int j=1; j<=20; ++j) {PH->SetBinContent(j,0); PH->SetBinError(j,0);}
    double Ztotal = 0, Ptotal = 0;
    int nZbx=Zb->GetNbinsX(); for(int j=21; j<=nZbx; ++j) {Ztotal += Zb->GetBinContent(j);}
    int nPhx=Ph->GetNbinsX(); for(int j=21; j<=nPhx; ++j) {Ptotal += Ph->GetBinContent(j);}
    std::cout<<"Entries in Z(inv) histo = "<<Ztotal<<" | Entries in P histo = "<<Ptotal<<" | Z(inv)/P = "<<Ztotal/Ptotal<<" | Z(all)/P = "<<5.0*Ztotal/Ptotal<<std::endl;

  
    // Scale to full Z sample
    ZB->Scale(100.00/20.00);             // Scaling to whole Z sample 
    // if(ii=1) ZB->Scale(1.0/0.0465222);   // Scale to MHT-like for boson pt > 100, 0-... jets
    // if(ii=1) ZB->Scale(5.0/0.364348);    // scale to MHT-like for all RA2 Selection cuts
    // if(ii=1) ZB->Scale(1.0/0.15424);     // Scaling to whole Eta range 

    // Check 
    PH->GetYaxis()->SetTitle(yaxis.c_str());
    PH->GetYaxis()->SetRangeUser(3e-4,1e4);
    PH->GetYaxis()->SetLabelSize(0.025);
    // PH->GetYaxis()->SetTicks("+");
    PH->GetXaxis()->SetLabelSize(0.0000025);
    PH->GetXaxis()->SetTicks("+-");
    
    PH->SetLineColor(1);
    PH->SetLineStyle(1);
    PH->SetLineWidth(2);
    ZB->SetLineColor(2);
    ZB->SetLineStyle(2);
    ZB->SetLineWidth(2);
    PH->Draw("");
    ZB->Draw("same");
    // Coordinates for TLegend: x1, y1, x2, y2
    // TLegend *l1 = new TLegend(0.60,0.75,0.85,0.85,NULL,"brNDC");
    TLegend *l1 = new TLegend(0.35,0.725,0.85,0.875,NULL,"brNDC");
    l1->SetLineColor(0);
    l1->SetLineStyle(0);
    l1->SetLineWidth(0);
    l1->SetFillColor(4000);
    l1->SetBorderSize(0);
    l1->AddEntry(PH, "Prompt  #gamma Prod","l");
    l1->AddEntry(ZB, "Inclusive Z Prod","l");
    l1->Draw();
    cmsPrelim(lumi, 0);
    PhotonPt->SetLogy(1);
    // ratio of bottom ratio plot wrt whole plot
    double r = 0.3;
    PhotonPt->SetBottomMargin(r + (1-r)*PhotonPt->GetBottomMargin()-r*PhotonPt->GetTopMargin());
    TPad *ratioPad = new TPad("BottomPad","",0,0,1,1);
    ratioPad->SetTopMargin((1-r) - (1-r)*ratioPad->GetBottomMargin()+r*ratioPad->GetTopMargin());
    ratioPad->SetFillStyle(4000);
    ratioPad->SetFillColor(4000);
    ratioPad->SetFrameFillColor(4000);
    ratioPad->SetFrameFillStyle(4000);
    ratioPad->SetFrameBorderMode(0);
    ratioPad->Draw();
    ratioPad->cd();
    ratioPad->SetGridy();
    TH1* ratio = 0;
    ratio = (TH1F*)PH->Clone();
    ratio->Divide(ZB, PH, 1, 1, "b");
    ratio->SetMinimum(0.0);
    ratio->SetMaximum(5.0);
    gStyle->SetGridStyle(3);
    ratio->GetYaxis()->SetNdivisions(505); // N1 + 100 * N2 (small ticks and big ticks) defines the grid
    ratio->GetYaxis()->SetLabelSize(0.025);
    ratio->GetYaxis()->SetTitle("Z / #gamma");
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




