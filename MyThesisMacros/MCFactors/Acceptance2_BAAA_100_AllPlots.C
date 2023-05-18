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


void Acceptance2_BAAA_100_AllPlots() {

  std::string Num[] = {"Boson_0J_AA_100/Pt", "Boson_1J_AA_100/Pt", "Boson_2J_AA_100/Pt", "Boson_3J_AA_100/Pt", "Boson_0J_AA_100/Eta", "Boson_1J_AA_100/Eta", "Boson_2J_AA_100/Eta", "Boson_3J_AA_100/Eta"};
  std::string Denom[] = {"Boson_0J_BA_100/Pt", "Boson_1J_BA_100/Pt", "Boson_2J_BA_100/Pt", "Boson_3J_BA_100/Pt", "Boson_0J_BA_100/Eta", "Boson_1J_BA_100/Eta", "Boson_2J_BA_100/Eta", "Boson_3J_BA_100/Eta"};
  std::string Name[] = {"Boson_0J_BAAA_100_Pt", "Boson_1J_BAAA_100_Pt", "Boson_2J_BAAA_100_Pt", "Boson_3J_BAAA_100_Pt", "Boson_0J_BAAA_100_Eta", "Boson_1J_BAAA_100_Eta", "Boson_2J_BAAA_100_Eta", "Boson_3J_BAAA_100_Eta"};

  std::vector<std::string> NumHistos; for(int i=0;i<8; ++i) { NumHistos.push_back(Num[i]); }
  std::vector<std::string> DenomHistos; for(int i=0;i<8; ++i) { DenomHistos.push_back(Denom[i]); }
  std::vector<std::string> Names;  for(int i=0;i<8; ++i) {  Names.push_back(Name[i]); }

  std::string pt_xaxis  = "P_{T} [GeV/c]";
  std::string eta_xaxis = "#eta [-]";
  std::string pt_yaxis  = "Particles / 5 GeV [-]";
  std::string eta_yaxis = "Particles / 0.2 [-]";


  for (int ii=0; ii<8; ++ii) {
    // if(ii != 4) continue;
    std::cout<<"==== i = "<<ii<<" ===="<<std::endl;
    std::string NumHisto = NumHistos[ii];
    std::string DenomHisto = DenomHistos[ii];
    std::string NameHisto = Names[ii];
    std::string xaxis = ii<4 ? pt_xaxis : eta_xaxis;
    std::string yaxis = ii<4 ? pt_yaxis : eta_yaxis;

    // gROOT->SetStyle("Plain");
    gStyle->SetPalette(1,0);
    gStyle->SetOptStat(000000);
    gStyle->SetOptTitle(0);
    gStyle->SetGridStyle(3);
    // gROOT->UseCurrentStyle();
    
    TCanvas * PhotonPt = new TCanvas("PhotonPt","PhotonPt",800,600);
    PhotonPt->SetFillColor(10);
    
    // Read Histograms
    std::string file_P1_name = "PhotonPt40to100GenEvent.root";
    std::string file_P2_name = "PhotonPt100to200GenEvent.root";
    std::string file_P3_name = "PhotonPt200GenEvent.root";
    // std::string file_Zb_name =  "ZbosonGenEvent.root";
    TFile * file_P1 = new TFile(file_P1_name.c_str(),"READ");
    TFile * file_P2 = new TFile(file_P2_name.c_str(),"READ");
    TFile * file_P3 = new TFile(file_P3_name.c_str(),"READ");
    // TFile * file_Zb = new TFile(file_Zb_name.c_str(),"READ");
    TH1F *P1_num, *P2_num, *P3_num, *P1_denom, *P2_denom, *P3_denom;
    TH1F *P1i, *P2i, *P3i, *Zbi;
    int P1a, P2a, P3a, Zba;
    // Amount of processed events (MC) :
    P1i = ((TH1F*) file_P1->Get("NJets_AK5PT50ETA25")); P1a = P1i->GetEntries();
    P2i = ((TH1F*) file_P2->Get("NJets_AK5PT50ETA25")); P2a = P2i->GetEntries();
    P3i = ((TH1F*) file_P3->Get("NJets_AK5PT50ETA25")); P3a = P3i->GetEntries();
    // Zbi = ((TH1F*) file_Zb->Get("NJets")); Zba = Zbi->GetEntries();
    // Cross Sections in pb
    std::vector<double> cross_sections; cross_sections.push_back(23620.00); cross_sections.push_back(3476.00); cross_sections.push_back(485.00); cross_sections.push_back(4500);
    // Luminosity in pb
    double lumi = 36.14;
    // Events in MC
    std::vector<double> scaling;
    std::vector<double> events; events.push_back(P1a); events.push_back(P2a); events.push_back(P3a); events.push_back(Zba);
    // Scaling
    for(int i=0; i<cross_sections.size(); ++i) {scaling.push_back(cross_sections[i]*lumi/events[i]);}
    P1_num = ((TH1F*) file_P1->Get(NumHisto.c_str()));
    P2_num = ((TH1F*) file_P2->Get(NumHisto.c_str()));
    P3_num = ((TH1F*) file_P3->Get(NumHisto.c_str()));
    P1_denom = ((TH1F*) file_P1->Get(DenomHisto.c_str()));
    P2_denom = ((TH1F*) file_P2->Get(DenomHisto.c_str()));
    P3_denom = ((TH1F*) file_P3->Get(DenomHisto.c_str()));
    // Zb = ((TH1F*) file_Zb->Get(SelHisto.c_str()));
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
    // Zb->Sumw2(); Zb->Scale(scaling[3]); // int nZbx=Zb->GetNbinsX(); for(int j=1; j<=nZbx; ++j) {Zb->SetBinError(j,Zb->GetBinError(j)/sqrt(scaling[3]));}
    
    TH1F *PH_num, *PH_denom;
    if(ii<4) {
      // manual rebinning
      double ptbinning [] = {0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0, 90.0, 95.0, 100.0, 105.0, 110.0, 115.0, 120.0, 125.0, 130.0, 135.0, 140.0, 145.0, 150.0, 165.0, 180.0, 195.0, 210.0, 225.0, 240.0, 255.0, 270.0, 285.0, 300.0, 350.0, 400.0, 450.0, 500.0};      
      PH_num   = new TH1F("PH_num",   "PH numerator",   44, ptbinning); PH_num->Sumw2();
      PH_denom = new TH1F("PH_denom", "PH denominator", 44, ptbinning); PH_denom->Sumw2();
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
	    PH_num->SetBinError(jj,sqrt(pow(PH_num->GetBinError(jj),2)+pow(Ph_num->GetBinError(iii),2)));
            PH_denom->SetBinError(jj,sqrt(pow(PH_denom->GetBinError(jj),2)+pow(Ph_denom->GetBinError(iii),2)));
	  }
	}
      }
      // for(int j=1; j<45; ++j)  {PH_num->SetBinError(j, sqrt(Ph_num->GetBinContent(j))); PH_denom->SetBinError(j, sqrt(Ph_denom->GetBinContent(j)));}
      for(int j=31; j<41; ++j) {
	PH_num->SetBinContent(j, PH_num->GetBinContent(j)/3); PH_denom->SetBinContent(j, PH_denom->GetBinContent(j)/3);
	PH_num->SetBinError(j,   PH_num->GetBinError(j)/3);   PH_denom->SetBinError(j, PH_denom->GetBinError(j)/3);
      }
      for(int j=41; j<45; ++j) {
	PH_num->SetBinContent(j, PH_num->GetBinContent(j)/10); PH_denom->SetBinContent(j, PH_denom->GetBinContent(j)/10);
	PH_num->SetBinError(j,   PH_num->GetBinError(j)/10);   PH_denom->SetBinError(j, PH_denom->GetBinError(j)/10);
      }
    }
    else {
      PH_num = (TH1F*)Ph_num->Clone();
      PH_denom = (TH1F*)Ph_denom->Clone();
      // For Eta Plots: Do Acceptance Calculation: Sum All Events Z [-inf, inf] / All Events Photon [-2.5,2.5]
      // For Scaled Luminosity
      double NumTotal = 0, DenomTotal= 0;
      int nZbx=Ph_denom->GetNbinsX(); for(int j=1; j<=nZbx; ++j) {DenomTotal += Ph_denom->GetBinContent(j);}
      int nPhx=Ph_num->GetNbinsX(); for(int j=1; j<=nPhx; ++j)   {NumTotal += Ph_num->GetBinContent(j);}
      std::cout<<"Entries before Acceptance = "<<DenomTotal<<" | Entries after Acceptance = "<<NumTotal<<" | Acceptance efficiency = "<<NumTotal/DenomTotal;
      std::cout<<" \pm "<<sqrt(NumTotal/DenomTotal * (1 - NumTotal/DenomTotal) / DenomTotal)<<std::endl;
    }


    // Scale to full Z sample
    // PH_denom->Scale(100.00/20.00); 
    
    // Check 
    PH_num->GetYaxis()->SetTitle(yaxis.c_str());
    if(ii==0 || ii==4) PH_num->GetYaxis()->SetRangeUser(3e-3,3e6);
    if(ii==1 || ii==5) PH_num->GetYaxis()->SetRangeUser(3e-3,3e5);
    if(ii==2 || ii==6) PH_num->GetYaxis()->SetRangeUser(3e-3,3e4);
    if(ii==3 || ii==7) PH_num->GetYaxis()->SetRangeUser(3e-3,3e3);
    if(ii>=4) PH_num->GetXaxis()->SetRangeUser(-3.0,3.0);
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
    PH_num->Draw("");
    PH_denom->Draw("same");
    // Coordinates for TLegend: x1, y1, x2, y2
    TLegend *l1 = new TLegend(0.35,0.725,0.85,0.875,NULL,"brNDC");
    l1->SetLineColor(0);
    l1->SetLineStyle(0);
    l1->SetLineWidth(0);
    l1->SetFillColor(4000);
    l1->SetBorderSize(0);
    l1->AddEntry(PH_num,   "Prompt #gamma After Acceptance","l");
    l1->AddEntry(PH_denom, "Prompt #gamma Before Acceptance","l");
    l1->Draw();
    cmsPrelim(lumi, 0);
    PhotonPt->SetLogy(1);
    PhotonPt->SetBottomMargin(0.2 + 0.8*PhotonPt->GetBottomMargin()-0.2*PhotonPt->GetTopMargin());
    TPad *ratioPad = new TPad("BottomPad","",0,0,1,1);
    ratioPad->SetTopMargin(0.8 - 0.8*ratioPad->GetBottomMargin()+0.2*ratioPad->GetTopMargin());
    ratioPad->SetFillStyle(4000);
    ratioPad->SetFillColor(4000);
    ratioPad->SetFrameFillColor(4000);
    ratioPad->SetFrameFillStyle(4000);
    ratioPad->SetFrameBorderMode(0);
    ratioPad->Draw();
    ratioPad->cd();
    gStyle->SetGridStyle(3);
    ratioPad->SetGridy();
    TH1* ratio = 0;
    ratio = (TH1F*)PH_num->Clone();
    ratio->Divide(PH_num, PH_denom, 1, 1, "b");
    ratio->SetMinimum(0.0);
    ratio->SetMaximum(1.2);
    ratio->GetYaxis()->SetNdivisions(503); // N1 + 100 * N2 (small ticks and big ticks) defines the grid
    ratio->GetYaxis()->SetLabelSize(0.025);
    ratio->GetYaxis()->SetTitle("Acceptance");
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




