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


void Acceptance3_OA_AllPlots() {

  int entries = 8;
  std::string SelHistos1[] = {"Boson_0J_AA/Pt", "Boson_1J_AA/Pt", "Boson_2J_AA/Pt", "Boson_3J_AA/Pt", "Boson_0J_AA/Eta", "Boson_1J_AA/Eta", "Boson_2J_AA/Eta", "Boson_3J_AA/Eta"};
  std::string SelHistos2[] = {"Boson_0J_BA/Pt", "Boson_1J_BA/Pt", "Boson_2J_BA/Pt", "Boson_3J_BA/Pt", "Boson_0J_BA/Eta", "Boson_1J_BA/Eta", "Boson_2J_BA/Eta", "Boson_3J_BA/Eta"};
  std::string NameHistos[] = {"Boson_0J_OA_Pt", "Boson_1J_OA_Pt", "Boson_2J_OA_Pt", "Boson_3J_OA_Pt", "Boson_0J_OA_Eta", "Boson_1J_OA_Eta", "Boson_2J_OA_Eta", "Boson_3J_OA_Eta"};

  std::vector<std::string> Histos1; for(int i=0;i<entries; ++i) { Histos1.push_back(SelHistos1[i]); }
  std::vector<std::string> Histos2; for(int i=0;i<entries; ++i) { Histos2.push_back(SelHistos2[i]); }
  std::vector<std::string> Names;   for(int i=0;i<entries; ++i) { Names.push_back(NameHistos[i]); }

  std::string pt_xaxis  = "P_{T} [GeV/c]";
  std::string eta_xaxis = "#eta [-]";
  std::string pt_yaxis  = "Particles / 5 GeV [-]";
  std::string eta_yaxis = "Particles / 0.2 [-]";


  for (int ii=0; ii<entries; ++ii) {
    // if(ii>3) continue;
    std::cout<<"==== i = "<<ii<<" ===="<<std::endl;
    std::string SelHisto1 = Histos1[ii];
    std::string SelHisto2 = Histos2[ii];
    std::string NameHisto = Names[ii];
    std::string xaxis = ii<4 ? pt_xaxis : eta_xaxis;
    std::string yaxis = ii<4 ? pt_yaxis : eta_yaxis;

    gROOT->SetStyle("Plain");
    gStyle->SetPalette(1,0);
    gStyle->SetOptStat(000000);
    gStyle->SetOptTitle(0);
    gStyle->SetGridStyle(3);
    gROOT->UseCurrentStyle();
    
    TCanvas * PhotonPt = new TCanvas("PhotonPt","PhotonPt",800,600);
    PhotonPt->SetFillColor(10);
    
    // Read Histograms
    std::string file_P1_name = "PhotonPt40to100GenEvent.root";
    std::string file_P2_name = "PhotonPt100to200GenEvent.root";
    std::string file_P3_name = "PhotonPt200GenEvent.root";
    std::string file_Zb_name =  "ZbosonGenEvent.root";
    TFile * file_P1 = new TFile(file_P1_name.c_str(),"READ");
    TFile * file_P2 = new TFile(file_P2_name.c_str(),"READ");
    TFile * file_P3 = new TFile(file_P3_name.c_str(),"READ");
    TFile * file_Zb = new TFile(file_Zb_name.c_str(),"READ");
    TH1F *P1, *P2, *P3, *Zb, *P1_, *P2_, *P3_, *Zb_;
    TH1F *P1i, *P2i, *P3i, *Zbi;
    int P1a, P2a, P3a, Zba;
    // Amount of processed events (MC) :
    P1i = ((TH1F*) file_P1->Get("NJets_AK5PT50ETA25")); P1a = P1i->GetEntries();
    P2i = ((TH1F*) file_P2->Get("NJets_AK5PT50ETA25")); P2a = P2i->GetEntries();
    P3i = ((TH1F*) file_P3->Get("NJets_AK5PT50ETA25")); P3a = P3i->GetEntries();
    Zbi = ((TH1F*) file_Zb->Get("NJets_AK5PT50ETA25")); Zba = Zbi->GetEntries();
    // Cross Sections in pb
    std::vector<double> cross_sections; cross_sections.push_back(23620.00); cross_sections.push_back(3476.00); cross_sections.push_back(485.00); cross_sections.push_back(4500);
    // Luminosity in pb
    double lumi = 36.14;
    // Events in MC
    std::vector<double> scaling;
    std::vector<double> events; events.push_back(P1a); events.push_back(P2a); events.push_back(P3a); events.push_back(Zba);
    // Scaling
    for(int i=0; i<cross_sections.size(); ++i) {scaling.push_back(cross_sections[i]*lumi/events[i]);}
    P1 = ((TH1F*) file_P1->Get(SelHisto2.c_str()));
    P2 = ((TH1F*) file_P2->Get(SelHisto2.c_str()));
    P3 = ((TH1F*) file_P3->Get(SelHisto2.c_str()));
    Zb = ((TH1F*) file_Zb->Get(SelHisto2.c_str()));
    P1_ = ((TH1F*) file_P1->Get(SelHisto1.c_str()));
    P2_ = ((TH1F*) file_P2->Get(SelHisto1.c_str()));
    P3_ = ((TH1F*) file_P3->Get(SelHisto1.c_str()));
    Zb_ = ((TH1F*) file_Zb->Get(SelHisto1.c_str()));
    P1->Add(P1_,-1);
    P2->Add(P2_,-1);
    P3->Add(P3_,-1);
    Zb->Add(Zb_,-1);
    // Final Histograms
    TH1F *Ph = (TH1F*) P1->Clone("Merge"); int n_P = Ph->GetNbinsX(); for (int j=1; j<=n_P; ++j) {Ph->SetBinContent(j,0.0);} Ph->Sumw2();
    // Scaling: cross section [pb] x lumi [pb^-1] / number of events before any selection
    P1->Sumw2(); P1->Scale(scaling[0]); // int nP1x=P1->GetNbinsX(); for(int j=1; j<=nP1x; ++j) {P1->SetBinError(j,P1->GetBinError(j)/sqrt(scaling[0]));}
    P2->Sumw2(); P2->Scale(scaling[1]); // int nP2x=P2->GetNbinsX(); for(int j=1; j<=nP2x; ++j) {P2->SetBinError(j,P2->GetBinError(j)/sqrt(scaling[1]));}
    P3->Sumw2(); P3->Scale(scaling[2]); // int nP3x=P3->GetNbinsX(); for(int j=1; j<=nP3x; ++j) {P3->SetBinError(j,P3->GetBinError(j)/sqrt(scaling[2]));}
    Ph->Add(P1); Ph->Add(P2); Ph->Add(P3);
    Zb->Sumw2(); Zb->Scale(scaling[3]); // int nZbx=Zb->GetNbinsX(); for(int j=1; j<=nZbx; ++j) {Zb->SetBinError(j,Zb->GetBinError(j)/sqrt(scaling[3]));}
    
    TH1F * PH, *ZB;
    if(ii<4) {
      // manual rebinning
      // Rebin Scheme 1: 30 bins of 5 Gev | 10 bins of 15 GeV | 4 bins of 50 GeV
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
      double Ztotal = 0, Ptotal = 0;
      int nZbx=Zb->GetNbinsX(); for(int j=21; j<=nZbx; ++j) {Ztotal += Zb->GetBinContent(j);}
      int nPhx=Ph->GetNbinsX(); for(int j=21; j<=nPhx; ++j) {Ptotal += Ph->GetBinContent(j);}
      std::cout<<"Entries in Z(inv) histo = "<<Ztotal<<" | Entries in P histo = "<<Ptotal<<" | Z(inv)/P = "<<Ztotal/Ptotal<<" | Z(all)/P = "<<5.0*Ztotal/Ptotal<<std::endl;
      // Rebin Scheme 2: 25 bins of 5 GeV | 1 bin of 25 GeV | 1 bin of 50 GeV | 1 bin of 100 GeV | 1 bin of 200 GeV
      /*
      double ptbinning [] = {0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0, 90.0, 95.0, 100.0, 105.0, 110.0, 115.0, 120.0, 125.0, 150.0, 200.0, 300.0, 500.0};
      int ptbins = 29;
      PH = new TH1F("PH", "PH", ptbins, ptbinning); PH->Sumw2();
      ZB = new TH1F("ZB", "ZB", ptbins, ptbinning); ZB->Sumw2();
      int bins = Ph->GetNbinsX();
      double binwidth = 500.0/bins;
      double photons = 0.0, zbosons = 0.0;
      for(int iii=1; iii<=bins; ++iii) {
        double bin_lvalue = (0.0 + (iii-1)*binwidth);
        double bin_rvalue = (0.0 + (iii)*binwidth);
        for(int jj=1; jj<=ptbins; ++jj) {
          if (bin_lvalue >=  ptbinning[jj-1] && bin_rvalue <= ptbinning[jj]) {
            PH->AddBinContent(jj,Ph->GetBinContent(iii));
            ZB->AddBinContent(jj,Zb->GetBinContent(iii));
          }
        }
      }
      for(int j=1;  j<bins+1; ++j)  {PH->SetBinError(j, sqrt(Ph->GetBinContent(j))); ZB->SetBinError(j, sqrt(Zb->GetBinContent(j)));}
      for(int j=26; j<27; ++j) {
        PH->SetBinContent(j, PH->GetBinContent(j)/5); ZB->SetBinContent(j, ZB->GetBinContent(j)/5);
        PH->SetBinError(j,   PH->GetBinError(j)/5);   ZB->SetBinError(j, ZB->GetBinError(j)/5);
      }
      for(int j=27; j<28; ++j) {
        PH->SetBinContent(j, PH->GetBinContent(j)/10); ZB->SetBinContent(j, ZB->GetBinContent(j)/10);
        PH->SetBinError(j,   PH->GetBinError(j)/10);   ZB->SetBinError(j, ZB->GetBinError(j)/10);
      }
      for(int j=28; j<29; ++j) {
        PH->SetBinContent(j, PH->GetBinContent(j)/20); ZB->SetBinContent(j, ZB->GetBinContent(j)/20);
        PH->SetBinError(j,   PH->GetBinError(j)/20);   ZB->SetBinError(j, ZB->GetBinError(j)/20);
      }
      for(int j=29; j<30; ++j) {
        PH->SetBinContent(j, PH->GetBinContent(j)/40); ZB->SetBinContent(j, ZB->GetBinContent(j)/40);
        PH->SetBinError(j,   PH->GetBinError(j)/40);   ZB->SetBinError(j, ZB->GetBinError(j)/40);
      }
      */
      // No rebinning
      /*
      PH = (TH1F*)Ph->Clone();
      ZB = (TH1F*)Zb->Clone();
      */
    }
    else {
      PH = (TH1F*)Ph->Clone();
      ZB = (TH1F*)Zb->Clone();
      // For Eta Plots: Do Acceptance Calculation: Sum All Events Z [-inf, inf] / All Events Photon [-2.5,2.5]
      // For Scaled Luminosity
      double Ztotal = 0, Ptotal = 0, Ptotal1 = 0, Ptotal2 = 0;
      double lb = 0, rb=0;
      int nZbx=Zb->GetNbinsX(); for(int j=1; j<=nZbx; ++j) {Ztotal += Zb->GetBinContent(j);}
      int nPhx=Ph->GetNbinsX(); for(int j=1; j<=nPhx; ++j) {Ptotal += Ph->GetBinContent(j);}
	/*
	lb = (-5.0 + j*10.0/nPhx); rb = (-5.0 + (j+1)*10.0/nPhx); 
	if(lb >= -2.4 && rb <= 2.4) {Ptotal1 += Ph->GetBinContent(j);}
	if(lb >= -2.6 && rb <= 2.6) {Ptotal2 += Ph->GetBinContent(j);}
      }
      std::cout<<"Entries in Z (inv) histo = "<<Ztotal<<" | Entries in P histo in ecal range [-2.4,2.4] = "<<Ptotal1<<" | Z(inv) full range / P ecal range = "<<Ztotal/Ptotal1;
      std::cout<<" | Z(all) full range / P ecal range = "<<5.0*Ztotal/Ptotal1<<std::endl;
      std::cout<<"Entries in Z (inv) histo = "<<Ztotal<<" | Entries in P histo in ecal range [-2.6,2.6] = "<<Ptotal2<<" | Z(inv) full range / P ecal range = "<<Ztotal/Ptotal2;
      std::cout<<" | Z(all) full range / P ecal range = "<<5.0*Ztotal/Ptotal2<<std::endl;
      */
      std::cout<<"Entries in Z histo = "<<Ztotal<<" | Entries in P histo = "<<Ptotal<<" | Z(inv)/P = "<<Ztotal/Ptotal<<" | Z(all)/P = "<<5.0*Ztotal/Ptotal<<std::endl;
    }


    // Scale to full Z sample
    ZB->Scale(100.00/20.00); 
   
    // Check 
    PH->GetYaxis()->SetTitle(yaxis.c_str());
    if(ii==0 || ii==4) PH->GetYaxis()->SetRangeUser(3e-3,3e7);
    if(ii==1 || ii==5) PH->GetYaxis()->SetRangeUser(3e-3,3e6);
    if(ii==2 || ii==6) PH->GetYaxis()->SetRangeUser(3e-3,3e5);
    if(ii==3 || ii==7) PH->GetYaxis()->SetRangeUser(3e-3,3e4);

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
    ratioPad->SetGridy();
    TH1* ratio = 0;
    ratio = (TH1F*)PH->Clone();
    ratio->Divide(ZB, PH, 1, 1, "b");
    if(ii<4) {
      ratio->SetMinimum(0.0);
      ratio->SetMaximum(2.0);
    }
    else {
      ratio->SetMinimum(0.0);
      ratio->SetMaximum(0.4);
    }
    ratio->GetYaxis()->SetNdivisions(503); // N1 + 100 * N2 (small ticks and big ticks) defines the grid
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




