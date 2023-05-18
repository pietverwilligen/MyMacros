#include "TCanvas.h"
#include "TStyle.h"
#include "TFile.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TString.h"

void DataTurnOn() {
  bool rebin = 0;
  int entries = 3; // !!! Aanpassen !!!
  // std::string dir = "RA2SEL/";
  std::string XaxisHisto    = "Photon PT [GeV/c]";
  std::string YaxisHisto    = "Events / 5 GeV/c";
  std::string NameHistos[]  = {"DATA_AMC_Efficiency", "DATA_HHS_Efficiency", "DATA_HMS_Efficiency"};


  std::vector<TString> NumHistos; NumHistos.push_back("RA2SEL/4_PT_AMC"); NumHistos.push_back("RA2SEL/6_PT_HHS"); NumHistos.push_back("RA2SEL/7_PT_HMS");
  std::vector<TString> DenHistos; DenHistos.push_back("RA2SEL/3_PT_AAC"); DenHistos.push_back("RA2SEL/3_PT_AAC"); DenHistos.push_back("RA2SEL/3_PT_AAC");
  std::vector<std::string> Xaxis;  for(int i=0;i<entries; ++i) { Xaxis.push_back(XaxisHisto); }
  std::vector<std::string> Yaxis;  for(int i=0;i<entries; ++i) { Yaxis.push_back(YaxisHisto); }
  std::vector<std::string> Names;  for(int i=0;i<entries; ++i) { Names.push_back(NameHistos[i]); }

  // ===============================================
  // COMMON STUFF
  //
  // ===============================================
  
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1,0);
  gStyle->SetOptStat(000000);
  gStyle->SetOptTitle(0);
  gStyle->SetGridStyle(0);
  gROOT->UseCurrentStyle();
    
  std::string file_P1_name = "GJets_HT-40To100_madgraph_Fall10.root";
  std::string file_P2_name = "GJets_HT-100To200_madgraph_Fall10.root";
  std::string file_P3_name = "GJets_HT-200_madgraph_Fall10.root";
  
  std::string file_Z_name  = "ZinvisibleJets_7TeV-madgraph_Fall10.root";
  std::string file_D_name  = "Photon.root";
  
  // SGN MC
  TFile * file_P1 = new TFile(file_P1_name.c_str(),"READ");
  TFile * file_P2 = new TFile(file_P2_name.c_str(),"READ");
  TFile * file_P3 = new TFile(file_P3_name.c_str(),"READ");
  // MC Truth
  TFile * file_Z  = new TFile(file_Z_name.c_str(),"READ");  
  // DATA
  TFile * file_D  = new TFile(file_D_name.c_str(),"READ");  

  // Read Histograms
  TH1F *Z_num, *P1_num, *P2_num, *P3_num, *D_num, *Z_den, *P1_den, *P2_den, *P3_den, *D_den;
  TH1F *Zi, *P1i, *P2i, *P3i, *Di;
  int Za, P1a, P2a, P3a, *Da;
  
  // Amount of processed events (MC) :
  P1i = ((TH1F*) file_P1->Get("EventCounters")); P1a = P1i->GetBinContent(1);
  P2i = ((TH1F*) file_P2->Get("EventCounters")); P2a = P2i->GetBinContent(1);
  P3i = ((TH1F*) file_P3->Get("EventCounters")); P3a = P3i->GetBinContent(1);
  
  Zi = ((TH1F*)  file_Z->Get("EventCounters")); Za  = Zi->GetBinContent(1);
  Di = ((TH1F*)  file_D->Get("EventCounters")); Da  = Di->GetBinContent(1);
  
  // Cross Sections in pb
  // --------------------                                                                                                                                                                               
  std::vector<double> cross_sections; 
  // Photon cross sections
  cross_sections.push_back(23620.00); cross_sections.push_back(3476.00); cross_sections.push_back(485.00);
  // Zinv cross section
  cross_sections.push_back(5760); // NNLO (4500@LO)
  // Luminosity in pb
  // ----------------                                                                                                                                                                                   
  double lumi = 35.30;
  // Events in MC
  // ------------                                                                                                                                                                                       
  std::vector<double> events;
 events.push_back(P1a); events.push_back(P2a); events.push_back(P3a);
 events.push_back(Za);
 // Scaling
 // --------
 std::vector<double> scaling;
 for(int i=0; i<cross_sections.size(); ++i) {scaling.push_back(cross_sections[i]*lumi/events[i]);}


 // ===============================================
 // HISTOGRAMS
 //
 // ===============================================
 TString DenHisto = DenHistos[0];
 P1_den = ((TH1F*) file_P1->Get(DenHisto.Data()));
 P2_den = ((TH1F*) file_P2->Get(DenHisto.Data()));
 P3_den = ((TH1F*) file_P3->Get(DenHisto.Data()));
 D_den = ((TH1F*)  file_D->Get(DenHisto.Data()));
 Z_den = ((TH1F*)  file_Z->Get(DenHisto.Data()));
   P1_den->Sumw2(); P1_den->Scale(scaling[0]);
   P2_den->Sumw2(); P2_den->Scale(scaling[1]);
   P3_den->Sumw2(); P3_den->Scale(scaling[2]);
   Z_den->Sumw2(); Z_den->Scale(scaling[3]*5);
   D_den->Sumw2(); 
   TH1F* P_den;
   P_den = (TH1F*) P1_den->Clone("Den"); int n_P_den = P_den->GetNbinsX(); for (int i=1; i<=n_P_den; ++i) {P_den->SetBinContent(i,0.0);}
   P_den->Add(P1_den); P_den->Add(P2_den); P_den->Add(P3_den); 
 
 for (int ii=0; ii<entries; ++ii) {
   // Debug modus for only 1 plot
   // if (ii != 2) continue;
   std::cout<<"==== i = "<<ii<<" ==== "<<NumHistos[ii]<<" ==== "<<DenHistos[ii]<<" ==== "<<Xaxis[ii]<<" ==== "<<Yaxis[ii]<<" ==== "<<std::endl;
   TString NumHisto = NumHistos[ii];
   TString DenHisto = DenHistos[ii];
   std::string NameHisto = Names[ii];
   std::string xaxis = Xaxis[ii];
   std::string yaxis = Yaxis[ii];
    
   P1_num = ((TH1F*) file_P1->Get(NumHisto.Data()));
   P2_num = ((TH1F*) file_P2->Get(NumHisto.Data()));
   P3_num = ((TH1F*) file_P3->Get(NumHisto.Data()));
    
   D_num = ((TH1F*)  file_D->Get(NumHisto.Data()));
   Z_num = ((TH1F*)  file_Z->Get(NumHisto.Data()));

    
   // Final Histograms
   TH1F *P_num, *P_den;

   P_num = (TH1F*) P1_num->Clone("Num"); int n_P_num = P_num->GetNbinsX(); for (int i=1; i<=n_P_num; ++i) {P_num->SetBinContent(i,0.0);}


   // Scaling: cross section [pb] x lumi [pb^-1] / number of events before any selection
   P1_num->Sumw2(); P1_num->Scale(scaling[0]);
   P2_num->Sumw2(); P2_num->Scale(scaling[1]);
   P3_num->Sumw2(); P3_num->Scale(scaling[2]);
   
   Z_num->Sumw2(); Z_num->Scale(scaling[3]*5);
   D_num->Sumw2(); 

   P_num->Add(P1_num); P_num->Add(P2_num); P_num->Add(P3_num); 


   D_num->SetLineColor(1);
   D_num->SetLineStyle(1);
   D_num->SetLineWidth(2);
   D_den->SetLineColor(2);
   D_den->SetLineStyle(2);
   D_den->SetLineWidth(2);

    if(!rebin) {
      // Make Plot
      TCanvas * c1 = new TCanvas("c","canvas",800,600);
      c1->cd();
      c1->SetLogy(1);
      D_den->GetYaxis()->SetRangeUser(3e-4,1e4);      
      // Z->SetLineColor(kMagenta); Z->SetLineWidth(2);
      // D->SetMarkerStyle(20); D->SetMarkerColor(kBlack); D->SetLineColor(kBlack); D->SetMarkerSize(0.75);
      D_den->GetYaxis()->SetTitle(yaxis.c_str());
      D_den->GetYaxis()->SetLabelSize(0.025);
      // A->GetYaxis()->SetTicks("+");
      // A->GetXaxis()->SetTitle(xaxis.c_str())
      D_den->GetXaxis()->SetLabelSize(0.0000025);
      D_den->GetXaxis()->SetTicks("+-");
      D_den->Draw("HIST");
      D_num->Draw("HISTsame");
      // D->Draw("sameE");
      // Z->Draw("sameH");
      gPad->RedrawAxis();
      gStyle->SetGridStyle(3);
      // Coordinates for TLegend: x1, y1, x2, y2
      TLegend *l1 = new TLegend(0.35,0.725,0.85,0.875,NULL,"brNDC");
      l1->SetLineColor(0);
      l1->SetLineStyle(0);
      l1->SetLineWidth(0);
      l1->SetFillColor(4000);
      l1->SetBorderSize(0);
      l1->AddEntry(D_den, "Photon PT Before MHT Cut","l");
      l1->AddEntry(D_num, "Photon PT After MHT Cut","l");
      l1->Draw();
      cmsPrelim(lumi,1);
      c1->SetLogy(1);
      double r = 0.4;
      c1->SetBottomMargin(r + (1-r)*c1->GetBottomMargin()-r*c1->GetTopMargin());
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
      ratio = (TH1F*)D_num->Clone();
      ratio->Divide(D_num, D_den, 1, 1, "b");
      ratio->SetMinimum(-0.2);
      ratio->SetMaximum(1.2);   
      ratio->GetYaxis()->SetNdivisions(505); // N1 + 100 * N2 (small ticks and big ticks) defines the grid
      ratio->GetYaxis()->SetLabelSize(0.025);
      ratio->GetYaxis()->SetTitle("Efficiency");
      ratio->GetXaxis()->SetTicks("+");
      ratio->GetXaxis()->SetTitle(xaxis.c_str());
      ratio->GetXaxis()->SetLabelSize(0.025);
      ratio->Draw("pe");
      savePlot(c1, NameHisto.c_str());
      
    }
    else {
    // manual rebinning                                                                                                                                                                                 
    // Rebin Scheme 1: 30 bins of 5 Gev | 10 bins of 15 GeV | 4 bins of 50 GeV                                                                                                                          
    double ptbinning [] = {0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0, 90.0, 95.0, 100.0, 105.0, 110.0, 115.0, 120.0, 125.0, 130.0, 135.0\
			   , 140.0, 145.0, 150.0, 165.0, 180.0, 195.0, 210.0, 225.0, 240.0, 255.0, 270.0, 285.0, 300.0, 350.0, 400.0, 450.0, 500.0};
    PH = new TH1F("PH", "PH", 44, ptbinning); PH->Sumw2();
    QC = new TH1F("QC", "QC", 44, ptbinning); QC->Sumw2();
    EW = new TH1F("EW", "EW", 44, ptbinning); EW->Sumw2();
    DA = new TH1F("DA", "DA", 44, ptbinning); DA->Sumw2();
    AA = new TH1F("DA", "DA", 44, ptbinning); DA->Sumw2();
    ZB = new TH1F("ZB", "ZB", 44, ptbinning); ZB->Sumw2();
    int bins = P->GetNbinsX();
    double binwidth = 500.0/bins;
    double photons = 0.0, zbosons = 0.0;
    for(int iii=1; iii<=bins; ++iii) {
      double bin_lvalue = (0.0 + (iii-1)*binwidth);
      double bin_rvalue = (0.0 + (iii)*binwidth);
      for(int jj=1; jj<45; ++jj) {
	if (bin_lvalue >=  ptbinning[jj-1] && bin_rvalue <= ptbinning[jj]) {
	  PH->AddBinContent(jj,P->GetBinContent(iii));
	  QC->AddBinContent(jj,Q->GetBinContent(iii));
	  EW->AddBinContent(jj,E->GetBinContent(iii));
	  DA->AddBinContent(jj,D->GetBinContent(iii));
	  AA->AddBinContent(jj,A->GetBinContent(iii));
	  ZB->AddBinContent(jj,Z->GetBinContent(iii));
	  PH->SetBinError(jj,sqrt(pow(PH->GetBinError(jj),2)+pow(P->GetBinError(iii),2)));
	  QC->SetBinError(jj,sqrt(pow(QC->GetBinError(jj),2)+pow(Q->GetBinError(iii),2)));
	  EW->SetBinError(jj,sqrt(pow(EW->GetBinError(jj),2)+pow(E->GetBinError(iii),2)));
	  DA->SetBinError(jj,sqrt(pow(DA->GetBinError(jj),2)+pow(D->GetBinError(iii),2)));
	  AA->SetBinError(jj,sqrt(pow(AA->GetBinError(jj),2)+pow(A->GetBinError(iii),2)));
	  ZB->SetBinError(jj,sqrt(pow(ZB->GetBinError(jj),2)+pow(Z->GetBinError(iii),2)));
	}
      }
    }
    // for(int j=1; j<45; ++j)  {PH->SetBinError(j, sqrt(Ph->GetBinContent(j))); ZB->SetBinError(j, sqrt(Zb->GetBinContent(j)));}                                                                       
    for(int j=31; j<41; ++j) {
      PH->SetBinContent(j, PH->GetBinContent(j)/3); PH->SetBinError(j, PH->GetBinError(j)/3);
      QC->SetBinContent(j, QC->GetBinContent(j)/3); QC->SetBinError(j, QC->GetBinError(j)/3);
      EW->SetBinContent(j, EW->GetBinContent(j)/3); EW->SetBinError(j, EW->GetBinError(j)/3);
      DA->SetBinContent(j, DA->GetBinContent(j)/3); DA->SetBinError(j, DA->GetBinError(j)/3);
      AA->SetBinContent(j, AA->GetBinContent(j)/3); AA->SetBinError(j, AA->GetBinError(j)/3);
      ZB->SetBinContent(j, ZB->GetBinContent(j)/3); ZB->SetBinError(j, ZB->GetBinError(j)/3);
    }
    for(int j=41; j<45; ++j) {
      PH->SetBinContent(j, PH->GetBinContent(j)/10); PH->SetBinError(j, PH->GetBinError(j)/10);   
      QC->SetBinContent(j, QC->GetBinContent(j)/10); QC->SetBinError(j, QC->GetBinError(j)/10);   
      EW->SetBinContent(j, EW->GetBinContent(j)/10); EW->SetBinError(j, EW->GetBinError(j)/10);   
      DA->SetBinContent(j, DA->GetBinContent(j)/10); DA->SetBinError(j, DA->GetBinError(j)/10);   
      AA->SetBinContent(j, AA->GetBinContent(j)/10); AA->SetBinError(j, AA->GetBinError(j)/10);   
      ZB->SetBinContent(j, ZB->GetBinContent(j)/10); ZB->SetBinError(j, ZB->GetBinError(j)/10);
    }
    THStack *AS = new THStack("AS","All Merge");
    EW->SetFillColor(kYellow); AS->Add(EW);
    QC->SetFillColor(kGreen);  AS->Add(QC);
    PH->SetFillColor(kRed);    AS->Add(PH);

    // All MC + DATA
    TCanvas * c1 = new TCanvas("c","canvas",800,600);
    c1->cd();
    c1->SetLogy(1);
    AA->GetYaxis()->SetRangeUser(3e-4,1e4);

    ZB->SetLineColor(kMagenta); ZB->SetLineWidth(2);
    DA->SetMarkerStyle(20); DA->SetMarkerColor(kBlack); DA->SetLineColor(kBlack); DA->SetMarkerSize(0.75);
    AA->GetYaxis()->SetTitle(yaxis.c_str());
    AA->GetYaxis()->SetLabelSize(0.025);
    // A->GetYaxis()->SetTicks("+");
    // A->GetXaxis()->SetTitle(xaxis.c_str())
    AA->GetXaxis()->SetLabelSize(0.0000025);
    AA->GetXaxis()->SetTicks("+-");
    AA->Draw("HIST");
    AS->Draw("HISTsame");
    DA->Draw("sameE");
    ZB->Draw("sameH");
    gPad->RedrawAxis();
    gStyle->SetGridStyle(3);
    // Coordinates for TLegend: x1, y1, x2, y2
    TLegend *l1 = new TLegend(0.60,0.75,0.85,0.85,NULL,"brNDC");
    l1->SetLineColor(0);
    l1->SetLineStyle(0);
    l1->SetLineWidth(0);
    l1->SetFillColor(4000);
    l1->SetBorderSize(0);
    l1->AddEntry(DA, "Data","pel");
    l1->AddEntry(ZB, "invisible Z","l");
    l1->AddEntry(PH, "Photon: prompt","f");
    l1->AddEntry(QC, "QCD: prompt, frag & decay","f");
    l1->AddEntry(EW, "EWK: W,Z,t#bar{t}","f");
    l1->Draw();
    cmsPrelim(lumi, 1);
    c1->SetLogy(1);
    c1->SetBottomMargin(0.2 + 0.8*c1->GetBottomMargin()-0.2*c1->GetTopMargin());
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
    ratio = (TH1F*)DA->Clone();
    ratio->Divide(DA, ZB, 1, 1, "b");
    ratio->SetMinimum(0.0);                                                                                                                                                                             
    ratio->SetMaximum(1.5);   
    ratio->GetYaxis()->SetNdivisions(505); // N1 + 100 * N2 (small ticks and big ticks) defines the grid
    ratio->GetYaxis()->SetLabelSize(0.025);
    ratio->GetYaxis()->SetTitle("Data / Zinv");
    ratio->GetXaxis()->SetTicks("+");
    ratio->GetXaxis()->SetTitle(xaxis.c_str());
    ratio->GetXaxis()->SetLabelSize(0.025);
    ratio->Draw("pe");
    savePlot(c1, NameHisto.c_str());
  }
  }

}

void cmsPrelim( double intLumi, int Data)
{
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.90,0.92,"#sqrt{s} = 7 TeV");
  if (intLumi > 0.) {
    latex.SetTextAlign(31); // align right
    if(Data==-2) latex.DrawLatex(0.70,0.92,"All MC, not rescaled");
    else if(Data==-1) latex.DrawLatex(0.70,0.92,Form("Max L = %.1f pb^{-1}", intLumi));
    else              latex.DrawLatex(0.70,0.92,Form("L = %.1f pb^{-1}",intLumi));
  }
  latex.SetTextAlign(11); // align left
  if(Data==1) latex.DrawLatex(0.10,0.92,"CMS preliminary 2010");
  if(Data==0) latex.DrawLatex(0.10,0.92,"CMS Monte-Carlo 2010");
  if(Data <0) latex.DrawLatex(0.10,0.92,"CMS Monte-Carlo 2010");

}

void savePlot(TCanvas * c, TString name) {
  c->SaveAs(name+".png");
  c->SaveAs(name+".eps");
  gSystem->Exec("epstopdf "+name+".eps");
}
