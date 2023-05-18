#include "TStyle.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TFile.h"
#include "TH1F.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TString.h"
#include "TGaxis.h"

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
#include <algorithm>

void cmsPrelim(double, int);
void savePlot(TCanvas*, TString);

void RA2Prediction() {

  bool norebin = false;
  bool fullaxis = false;
  int plots = 2;
  int categories = 3;
  int entries = plots * categories; // = 6 !!! Aanpassen !!!
  std::string dir = "RA2SEL/";
  std::string histarray[] = {"4_HT_AMC", "4_MHT_AMC","6_HT_HHS", "6_MHT_HHS", "7_HT_HMS", "7_MHT_HMS"};
  std::string xaxisarray[] = {"HT [GeV/c]", "MHT [GeV/c]"};
  std::string yaxisarray[] = {"# Baseline / 5 GeV/c", "# Baseline / 5 GeV/c", "# High HT / 5 GeV/c", "# High HT / 5 GeV/c", "# High MHT / 5 GeV/c", "# High MHT / 5 GeV/c"} ;
  std::vector<std::string> name;
  std::string namearray1[] = {"HTPred_AMC_fullaxis", "MHTPred_AMC_fullaxis", "HTPred_HHS_fullaxis", "MHTPred_HHS_fullaxis", "HTPred_HMS_fullaxis", "MHTPred_HMS_fullaxis"};
  std::string namearray2[] = {"HTPred_AMC", "MHTPred_AMC", "HTPred_HHS", "MHTPred_HHS", "HTPred_HMS", "MHTPred_HMS"};
  
  std::vector<std::string> Histos; for(int i=0;i<entries; ++i) { Histos.push_back(histarray[i]); }
  std::vector<std::string> Xaxis;  for(int i=0;i<categories; ++i) { for(int j=0;j<plots; ++j) { Xaxis.push_back(xaxisarray[j]); } }
  std::vector<std::string> Yaxis;  for(int i=0;i<entries; ++i) { Yaxis.push_back(yaxisarray[i]); }
  std::vector<std::string> Names;  for(int i=0;i<entries; ++i) { if(fullaxis) { Names.push_back(namearray1[i]); } else { Names.push_back(namearray2[i]); } }

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
  
  std::string file_Z_name  = "ZinvisibleJets_7TeV-madgraph_Fall10.root";
  std::string file_D_name  = "Photon.root";
  
  // MC Truth
  TFile * file_Z  = new TFile(file_Z_name.c_str(),"READ");  
  // DATA
  TFile * file_D  = new TFile(file_D_name.c_str(),"READ");  

  // Read Histograms
  TH1F *Z, *D;
  TH1F *Zi, *Di;
  int Za, Da;
  
  // Amount of processed events (MC) :
  
  Zi = ((TH1F*)  file_Z->Get("EventCounters")); Za  = Zi->GetBinContent(1);
  Di = ((TH1F*)  file_D->Get("EventCounters")); Da  = Di->GetBinContent(1);
  
  // Cross Sections in pb
  // --------------------                                                                                                                                                                               
  std::vector<double> cross_sections; 
  // Zinv cross section
  cross_sections.push_back(5760); //   LO (4500@LO)
  // cross_sections.push_back(4500); // NNLO (5760@LO)
  // Luminosity in pb
  // ----------------                                                                                                                                                                                   
  double lumi = 36.14;
  // Events in MC
  // ------------                                                                                                                                                                                       
  std::vector<double> events;
  events.push_back(Za);
  // Scaling
  // --------
  std::vector<double> scaling;
  for(int i=0; i<cross_sections.size(); ++i) {scaling.push_back(cross_sections[i]*lumi/events[i]);}


 // ===============================================
 // HISTOGRAMS
 //
 // ===============================================
 
 for (int ii=0; ii<entries; ++ii) {
   // Debug modus for only 1 plo
   // if (ii != 0) continue;
   // if (ii != 2) continue;  // HT All
   // if (ii != 1) continue;  // MHT All
   // if (ii != 16) continue; // HT Baseline
   // if (ii != 17) continue; // MHT Baseline
   // if (ii > 7) continue;

    // 
    std::cout<<"==== i = "<<ii<<" ==== "<<Histos[ii]<<" ==== "<<Xaxis[ii]<<" ==== "<<Yaxis[ii]<<" ==== "<<std::endl;

    std::string SelHisto = Histos[ii];
    std::string xaxis = Xaxis[ii];
    std::string yaxis = Yaxis[ii];
    std::string NameHisto = Names[ii];
        
    D = ((TH1F*)  file_D->Get((dir+SelHisto).c_str()));
    Z = ((TH1F*)  file_Z->Get((dir+SelHisto).c_str()));
    
    // Final Histograms
    Z->Sumw2(); Z->Scale(scaling[0]);
    D->Sumw2(); 
    if( ii==0 || ii==1) D->Scale(0.358610);
    if( ii==2 || ii==3) D->Scale(0.398383);
    if( ii==4 || ii==5) D->Scale(0.430566);

    TH1F *ZB, *DA;
    if(norebin) { // NO REBIN
      ZB = (TH1F*) Z->Clone("All"); // int n_Z = Z->GetNbinsX(); for (int i=1; i<=n_Z; ++i) {ZB->SetBinContent(i,0.0); ZB->SetBinError(i,0,0);}
      DA = (TH1F*) D->Clone("All"); // int n_D = D->GetNbinsX(); for (int i=1; i<=n_D; ++i) {DA->SetBinContent(i,0.0); DA->SetBinError(i,0,0);}
    }
    else { // REBIN
      // manual rebinning
      // Rebin Scheme 1: 30 bins of 5 Gev | 10 bins of 15 GeV | 4 bins of 50 GeV + 10 bins of 50 GeV for HT plots = 54 bins
      int newbins = 0;
      // if(ii%2 == 0) newbins = 50; // HT plots max supported
      // else          newbins = 40; // MHT plots max supported
      // if(ii%2 == 0) newbins = 32; // HT plots max supported (2500)
      // else          newbins = 26; // MHT plots max supported (1000)
      if(ii%2 == 0) newbins = 28; // HT up to 1500
      else          newbins = 16; // MHT up to 500
      // std::cout<<"Counter: "<<ii<<" mod 4 : "<<ii%2<<" Amount of bins: "<<newbins<<std::endl;
      // double ptbinning [] = {0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0, 90.0, 95.0, 100.0, 105.0, 110.0, 115.0, 120.0, 125.0, 130.0, 135.0, 140.0, 145.0, 150.0, 175.0, 200.0, 225.0, 250.0, 275.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0, 850.0, 900.0, 950.0, 1000.0};
      double ptbinning [] = {0.0, 25.0, 50.0, 75.0, 100.0, 125.0, 150.0, 175.0, 200.0, 225.0, 250.0, 275.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0, 850.0, 900.0, 950.0, 1000.0, 1250.0, 1500.0, 1750.0, 2000.0, 2250.0, 2500.0};
      DA = new TH1F("DA", "DA", newbins, ptbinning); DA->Sumw2();
      ZB = new TH1F("ZB", "ZB", newbins, ptbinning); ZB->Sumw2();
      int bins = D->GetNbinsX();    // old binning
      double binwidth = 0.0;        // should not make a difference
      if(fullaxis) {
	if (ii%2 == 0) binwidth = 1000.0/bins; // HT  !!! Binwidth of original file !!! do not touch
	if (ii%2 == 1) binwidth = 500.0/bins;  // MHT !!! Binwidth of original file !!! do not touch
      }
      else {
	if (ii%2 == 0) binwidth = 2500.0/bins;  // HT  !!! Binwidth of original file !!! do not touch
	if (ii%2 == 1) binwidth = 1000.0/bins;  // MHT !!! Binwidth of original file !!! do not touch
      }
      double photons = 0.0, zbosons = 0.0;
      for(int iii=1; iii<=bins; ++iii) {
	double bin_lvalue = (0.0 + (iii-1)*binwidth);
	double bin_rvalue = (0.0 + (iii)*binwidth);
	for(int jj=1; jj<newbins+1; ++jj) {
	  if (bin_lvalue >=  ptbinning[jj-1] && bin_rvalue <= ptbinning[jj]) {
	    /* // DEBUG
	    if(D->GetBinContent(iii) != 0) {
	      std::cout<<"bin_lvalue ["<<bin_lvalue<<"] >=  ptbinning["<<jj-1<<"] ["<<ptbinning[jj-1]<<"] && bin_rvalue ["<<bin_rvalue<<"] <= ptbinning["<<jj<<"] ["<<ptbinning[jj]<<"]"<<std::endl;
	      std::cout<<"bin ["<<bin_lvalue<<", "<<bin_rvalue<<"] added in bin ["<<ptbinning[jj-1]<<", "<<ptbinning[jj]<<"] "<<std::endl;
	      std::cout<<" original counter: "<<iii<<" new counter: "<<jj<<" bincontent: "<<D->GetBinContent(iii)<<std::endl;
	    }
	    */
	    DA->AddBinContent(jj,D->GetBinContent(iii));
	    ZB->AddBinContent(jj,Z->GetBinContent(iii));
	    DA->SetBinError(jj,sqrt(pow(DA->GetBinError(jj),2)+pow(D->GetBinError(iii),2)));
	    ZB->SetBinError(jj,sqrt(pow(ZB->GetBinError(jj),2)+pow(Z->GetBinError(iii),2)));
	  }
	}
      }
      // for(int j=31; j<37; ++j) { // 25 GeV binning
      for(int j=1; j<13; ++j) { // 25 GeV binning
	DA->SetBinContent(j, DA->GetBinContent(j)/5); DA->SetBinError(j, DA->GetBinError(j)/5);
	ZB->SetBinContent(j, ZB->GetBinContent(j)/5); ZB->SetBinError(j, ZB->GetBinError(j)/5);
      }
      // for(int j=37; j<std::min(newbins+1,51); ++j) { // 50 GeV binning
      for(int j=13; j<std::min(newbins+1,27); ++j) { // 50 GeV binning
	DA->SetBinContent(j, DA->GetBinContent(j)/10); DA->SetBinError(j, DA->GetBinError(j)/10);   
	ZB->SetBinContent(j, ZB->GetBinContent(j)/10); ZB->SetBinError(j, ZB->GetBinError(j)/10);
      }
      for(int j=27; j<newbins+1; ++j) { // 250 GeV binning
	DA->SetBinContent(j, DA->GetBinContent(j)/50); DA->SetBinError(j, DA->GetBinError(j)/50);   
	ZB->SetBinContent(j, ZB->GetBinContent(j)/50); ZB->SetBinError(j, ZB->GetBinError(j)/50);
      }
    }
     
    // Upper and Lower (Stat + Syst)
    TH1F* DA_up  = (TH1F*) DA->Clone("DA_up");
    TH1F* DA_dn  = (TH1F*) DA->Clone("DA_dn");
    TH1F* DA_all = (TH1F*) DA->Clone("DA_all");
    double syst = 0.0;
    if( ii==0 || ii==1) {syst = 0.233167;}
    if( ii==2 || ii==3) {syst = 0.260001;}
    if( ii==4 || ii==5) {syst = 0.255502;}
    int n_DA = DA->GetNbinsX(); for (int i=1; i<=n_DA; ++i) {
      DA_up->SetBinContent(i,DA->GetBinContent(i)+sqrt(pow(DA->GetBinError(i),2)+pow(DA->GetBinContent(i)*syst,2))); 
      DA_dn->SetBinContent(i,DA->GetBinContent(i)-sqrt(pow(DA->GetBinError(i),2)+pow(DA->GetBinContent(i)*syst,2))); 
      DA_up->SetBinError(i,0,0);
      DA_dn->SetBinError(i,0,0);
      DA_all->SetBinError(i,sqrt(pow(DA->GetBinError(i),2)+pow(DA->GetBinContent(i)*syst,2)));
    }

    // All MC + DATA
    TCanvas * c1 = new TCanvas("c","canvas",800,600);
    TPad *plotPad = new TPad("TopPad","",0,0,1,1);
    plotPad->SetFillStyle(4000);
    plotPad->SetFillColor(4000);
    plotPad->SetFrameFillColor(4000);
    plotPad->SetFrameFillStyle(4000);
    plotPad->SetFrameBorderMode(0);
    plotPad->Draw();
    plotPad->cd();
    plotPad->SetLogy(1);
    // FH = Pointer to First Histogram 
    // TH1F * FH = &(*DA_up);
    TH1F * FH = &(*DA);

    FH->GetYaxis()->SetRangeUser(3e-3,3e0);
    // FH->GetYaxis()->SetRangeUser(0,2);

    DA->SetMarkerStyle(8);      DA->SetMarkerColor(kBlack); 
    DA->SetLineColor(kBlack);   DA->SetMarkerSize(1.10);
    ZB->SetLineColor(kBlue);    ZB->SetLineWidth(2);
    DA_up->SetLineStyle(9);     DA_dn->SetLineStyle(9); 
    DA_up->SetLineWidth(2);     DA_dn->SetLineWidth(2);
    DA_up->SetLineColor(kGray+1); DA_dn->SetLineColor(kGray+1);
    DA_up->SetFillStyle(3004);  
    DA_up->SetFillColor(kGray+1);
    DA_dn->SetFillStyle(1001);  DA_dn->SetFillColor(10); // 0,4100 are not working, 1001 is solid and is default| kWhite and 0 are also not working
    DA_all->SetLineColor(kGray+1); /*DA_all->SetFillStyle(3004);*/  DA_all->SetFillColor(kGray);
    // hack
    DA_hack2= (TH1F*) DA_dn->Clone();
    for (int i=1; i<=n_DA; ++i) {
      if((DA_dn->GetBinContent(i-1) > 0) && (DA_dn->GetBinContent(i) <= 0)) {
	std::cout<<"Hack 2: Bincontent ["<<i-1<<"] = "<<DA_dn->GetBinContent(i-1)<<" && Bincontent ["<<i<<"] = "<<DA_dn->GetBinContent(i)<<std::endl;
	DA_hack2->SetBinContent(i,3E-4);
	DA_hack2->SetBinError(i,0);
      }
    }
    DA_hack2->SetLineColor(kGray+1);
    DA_hack2->SetLineStyle(9);
    DA_hack2->SetLineWidth(2);
    DA_hack2->SetFillColor(10);
    DA_hack2->SetFillStyle(1001);

    FH->GetYaxis()->SetTitle(yaxis.c_str());
    FH->GetYaxis()->SetLabelSize(0.025);
    // FH->GetYaxis()->SetTicks("+");
    // FH->GetXaxis()->SetTitle(xaxis.c_str())
    FH->GetXaxis()->SetLabelSize(0.00);
    // FH->GetXaxis()->SetLabelSize(0.0000025);
    FH->GetXaxis()->SetTicks("+-");
    // DA_up->Draw("HF][");
    // DA_dn->Draw("HF][same");
    // DA_hack2->Draw("H][same");
    FH->Draw("E");
    DA_all->Draw("E2same");
    ZB->Draw("][sameH");
    DA->Draw("Esame");
    gPad->Update();
    gStyle->SetGridStyle(3);
    gPad->RedrawAxis("g");
    FH->Draw("sameaxis");
    gPad->Update();
    // Coordinates for TLegend: x1, y1, x2, y2
    double l_x1 = 0.60, l_x2 = 0.85, l_y1 = 0.75, l_y2 = 0.85; 
    // if(fullaxis) {l_x1 = 0.60;  l_x2 = 0.85;  l_y1 = 0.75;  l_y2 = 0.85; }
    // else         {l_x1 = 0.125; l_x2 = 0.325; l_y1 = 0.425; l_y2 = 0.625;}
    if(ii%2==0)       {l_x1 = 0.575; l_x2 = 0.850; l_y1 = 0.695; l_y2 = 0.895;}
    else if(ii%2==1)  {l_x1 = 0.125; l_x2 = 0.400; l_y1 = 0.425; l_y2 = 0.625;}
    else {} //                  {l_x1 = 0.125; l_x2 = 0.325; l_y1 = 0.675; l_y2 = 0.875;}
    TLegend *l1 = new TLegend(l_x1,l_y1,l_x2,l_y2,NULL,"brNDC");
    l1->SetLineColor(0);
    l1->SetLineStyle(0);
    l1->SetLineWidth(0);
    l1->SetFillColor(4000);
    l1->SetBorderSize(0);
    DA->SetFillStyle(3004);  DA->SetFillColor(kGray+1);
    l1->AddEntry(DA, "Pred. from Data","pel");
    // l1->AddEntry(DA_up, "Stat.+Syst. Uncert.","lf");
    l1->AddEntry(DA_all, "Stat.+Syst. Uncert.","f");
    l1->AddEntry(ZB, "invisible Z (NLO MC)","l");
    l1->Draw();
    cmsPrelim(lumi, 1);
    // Ratio Pads
    // ratio big : 2 ratio pads: 0.6 | 0.4
    double frst = 0.6;
    // ratio ratio1 : ratio2: 0.5 | 0.5
    // in case of only one ratio pad: set to 1
    double secd = 1;
    // std::cout<<"c1->GetTopMargin() = "<<c1->GetTopMargin()<<" | c1->GetBottomMargin() = "<<c1->GetBottomMargin()<<std::endl;
    // c1->SetBottomMargin((1-frst) + frst*c1->GetBottomMargin()-(1-frst)*c1->GetTopMargin());
    plotPad->SetBottomMargin((1-frst) + frst*c1->GetBottomMargin()-(1-frst)*c1->GetTopMargin());
    TPad *ratioPad = new TPad("BottomPad","",0,0,1,1);
    ratioPad->SetTopMargin(frst - frst*ratioPad->GetBottomMargin()+(1-frst)*ratioPad->GetTopMargin());
    // ratioPad->SetBottomMargin((1-secd) + secd*ratioPad->GetBottomMargin()-(1-secd)*ratioPad->GetTopMargin());
    ratioPad->SetFillStyle(4000);
    ratioPad->SetFillColor(4000);
    ratioPad->SetFrameFillColor(4000);
    ratioPad->SetFrameFillStyle(4000);
    ratioPad->SetFrameBorderMode(0);
    ratioPad->Draw();
    ratioPad->cd();
    ratioPad->SetGridy();
    TH1 *ratio = 0, *ratio_up = 0, *ratio_dn = 0, *ratio_all = 0;
    ratio     = (TH1F*)DA->Clone();
    ratio_up  = (TH1F*)DA_up->Clone();
    ratio_dn  = (TH1F*)DA_dn->Clone();
    ratio_all = (TH1F*)DA_all->Clone("ratio");
    //    std::cout<<"PH: bins = "<<PH->GetNbinsX()<<std::endl;
    //    std::cout<<"ZB: bins = "<<ZB->GetNbinsX()<<std::endl;
    // ratio->Divide(DA, ZB, 1, 1); // !!! no binomial error !!!

    int n_ra = ratio->GetNbinsX(); 
    for (int i=1; i<=n_ra; ++i) {
      double a  = DA->GetBinContent(i); double b  = ZB->GetBinContent(i);
      double ae = DA->GetBinError(i);   double be = ZB->GetBinError(i);
      if(a!=0 && b!=0) {
	ratio->SetBinContent(i,a/b);
	ratio->SetBinError(i,(a/b)*sqrt(pow(ae/a,2)+pow(be/b,2)));
      }
    }
    ratio_up = (TH1*) ratio->Clone("up");
    ratio_dn = (TH1*) ratio->Clone("dn");
    for (int i=1; i<=n_ra; ++i) {
      if(ratio->GetBinContent(i) > 0) {
	ratio_up->SetBinContent(i,ratio->GetBinContent(i)+sqrt(pow(ratio->GetBinError(i),2)+pow(ratio->GetBinContent(i)*syst,2))); 
	ratio_dn->SetBinContent(i,ratio->GetBinContent(i)-sqrt(pow(ratio->GetBinError(i),2)+pow(ratio->GetBinContent(i)*syst,2)));
	ratio_up->SetBinError(i,0);
	ratio_dn->SetBinError(i,0);
	ratio_all->SetBinContent(i,ratio->GetBinContent(i));
	ratio_all->SetBinError(i,sqrt(pow(ratio->GetBinError(i),2)+pow(ratio->GetBinContent(i)*syst,2))); 
      }
    }
    ratio_up->SetLineStyle(9);     ratio_dn->SetLineStyle(9); 
    ratio_up->SetLineWidth(2);     ratio_dn->SetLineWidth(2);
    ratio_up->SetLineColor(kGray+1); ratio_dn->SetLineColor(kGray+1);
    ratio_up->SetFillStyle(3004);  ratio_up->SetFillColor(kGray+1);
    ratio_dn->SetFillStyle(1001);  ratio_dn->SetFillColor(10); 
    ratio_hack1= (TH1F*)ratio_dn->Clone();
    ratio_hack2= (TH1F*)ratio_dn->Clone();
    // cosmetic issue: shade negative bins only
    for(int i=2; i<=n_ra; ++i) {
      if(ratio_dn->GetBinContent(i) > 0) {
	ratio_hack1->SetBinContent(i,0);
	ratio_hack1->SetBinError(i,0);
      }
      if((ratio_dn->GetBinContent(i-1) > 0) && (ratio_dn->GetBinContent(i) <= 0)) {
	ratio_hack2->SetBinContent(i,0.1);
	ratio_hack2->SetBinError(i,0);
	// std::cout<<"Hack 2: Bincontent ["<<i-1<<"] = "<<ratio_dn->GetBinContent(i-1)<<" && Bincontent ["<<i<<"] = "<<ratio_dn->GetBinContent(i)<<std::endl;
      }
    }
    ratio_hack1->SetLineColor(1001);
    ratio_hack1->SetLineStyle(1);
    ratio_hack1->SetLineWidth(0);
    ratio_hack1->SetFillColor(kGray+1);
    ratio_hack1->SetFillStyle(3004);
    ratio_hack2->SetLineColor(kGray+1);
    ratio_hack2->SetLineStyle(9);
    ratio_hack2->SetLineWidth(2);
    ratio_hack2->SetFillColor(10);
    ratio_hack2->SetFillStyle(1001);
    // FHR = Pointer to First Histogram Ratio
    // TH1 * FHR = &(*ratio_up);
    TH1 * FHR = &(*ratio);
    // FHR->SetMinimum(-0.4);                                                                                                                                        
    FHR->SetMinimum(0.01);                                                                                                                                        
    FHR->SetMaximum(5.4);   
    FHR->GetYaxis()->SetNdivisions(510); // N1 + 100 * N2 (small ticks and big ticks) defines the grid
    FHR->GetYaxis()->SetLabelSize(0.025);
    //FHR->GetYaxis()->SetTitleSize(0.025);
    FHR->GetYaxis()->SetTitle("Data / MC");
    // FHR->GetYaxis()->SetTitleOffset(1.3);
    // FHR->GetXaxis()->SetTicks("+-");
    // FHR->GetXaxis()->SetLabelSize(0.00);
    FHR->GetXaxis()->SetTicks("+");
    FHR->GetXaxis()->SetTitle(xaxis.c_str());
    FHR->GetXaxis()->SetLabelSize(0.025);
    // ratio_up->Draw("FH][");
    // ratio_dn->Draw("FH][same");
    // ratio_hack1->Draw("Fsame");
    // ratio_hack2->Draw("H][same");
    ratio->Draw("pe");
    ratio_all->Draw("E2same");
    ratio->Draw("pesame");
    ratioPad->Update();
    ratioPad->RedrawAxis("g");
    FHR->Draw("sameaxis");
    // Redraw Axis
    // Apparently axis coordinates follow existing axis coordinates:
    // x_min, y_min, x_max, y_max, value_start, value_stop, ndiv=510, options=+-, U
    double val_start = 0.0, val_stop = 0.0;
    if (ii%2 == 0) val_stop = 1500.0;
    if (ii%2 == 1) val_stop = 500.0;
    TGaxis * axis = new TGaxis(val_start,5.4,val_stop,5.4,val_start,val_stop,510,"-+");
    axis->SetLabelSize(0.00);
    // axis->SetTicks("+-");
    axis->Draw("same");


    ratioPad->Update();
    
    plotPad->cd();
    plotPad->Update();
    plotPad->RedrawAxis("g");
    FH->Draw("Esame");
    FH->Draw("sameaxis");
    plotPad->Update();
    c1->Update();    
    /*
    TPad *ratioPad2 = new TPad("BottomPad2","",0,0,1,1);
    ratioPad2->SetTopMargin((frst+secd*(1-frst)) - (frst+secd*(1-frst))*ratioPad2->GetBottomMargin()+(secd*(1-frst))*ratioPad2->GetTopMargin());
    ratioPad2->SetFillStyle(4000);
    ratioPad2->SetFillColor(4000);
    ratioPad2->SetFrameFillColor(4000);
    ratioPad2->SetFrameFillStyle(4000);
    ratioPad2->SetFrameBorderMode(0);
    ratioPad2->Draw();
    ratioPad2->cd();
    ratioPad2->SetGridy();
    TH1* ratio2 = 0;
    ratio2 = (TH1F*)ZB->Clone();
    // std::cout<<"PH: bins = "<<PH->GetNbinsX()<<std::endl;
    // std::cout<<"ZB: bins = "<<ZB->GetNbinsX()<<std::endl;
    ratio2->Divide(PH, ZB, 1, 1, "b");
    ratio2->SetMinimum(-0.4); 
    ratio2->SetMaximum(2.4);   
    ratio2->GetYaxis()->SetNdivisions(505); // N1 + 100 * N2 (small ticks and big ticks) defines the grid
    ratio2->GetYaxis()->SetLabelSize(0.025);
    // ratio2->GetYaxis()->SetTitleSize(0.025);    
    ratio2->GetYaxis()->SetTitle("#gamma / Z     ");
    // ratio2->GetYaxis()->SetTitleOffset(1.3);
    ratio2->GetXaxis()->SetTicks("+");
    ratio2->GetXaxis()->SetTitle(xaxis.c_str());
    ratio2->GetXaxis()->SetLabelSize(0.025);
    ratio2->Draw("pe");
    */
    savePlot(c1, NameHisto.c_str());    
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
    latex.DrawLatex(0.70,0.92,Form("L = %.1f pb^{-1}",intLumi));
  }
  latex.SetTextAlign(11); // align left
  if(Data==1) latex.DrawLatex(0.10,0.92,"CMS preliminary 2010");
  if(Data==0) latex.DrawLatex(0.10,0.92,"CMS Monte-Carlo 2010");
}

void savePlot(TCanvas * c, TString name) {
  c->SaveAs(name+".png");
  c->SaveAs(name+".eps");
  gSystem->Exec("epstopdf "+name+".eps");
}
