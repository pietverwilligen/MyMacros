#include "TCanvas.h"
#include "TStyle.h"
#include "TFile.h"
#include "TH1F.h"
#include "TLegend.h"

void RA2Plot() {

  int entries = 10; // !!! Aanpassen !!!
  std::string dir = "RA2SEL/";
  std::string histarray[] = {"0_HT_All", "0_MHT_All", "1_HT_AJC", "1_MHT_AJC", "2_HT_AHC", "2_MHT_AHC", "3_HT_AAC", "3_MHT_AAC", "4_HT_AMC", "4_MHT_AMC"};
  std::string xaxisarray[] = {"HT [GeV/c]", "MHT [GeV/c]","HT [GeV/c]", "MHT [GeV/c]","HT [GeV/c]", "MHT [GeV/c]","HT [GeV/c]", "MHT [GeV/c]","HT [GeV/c]", "MHT [GeV/c]"}; 
  std::string yaxisarray[] = {"All Events / 5 GeV/c", "All Events / 5 GeV/c","Events after Jet cut / 5 GeV/c", "Events after Jet cut / 5 GeV/c","Events after HT cut / 5 GeV/c", "Events after HT cut / 5 GeV/c","Events after Angular cut / 5 GeV/c", "Events after Angular cut / 5 GeV/c","Events after MHT cut / 5 GeV/c", "Events after MHT cut / 5 GeV/c"};
  std::string namearray[] = {"HT_All", "MHT_All", "HT_AJC", "MHT_AJC", "HT_AHC", "MHT_AHC", "HT_AAC", "MHT_AAC", "HT_AMC", "MHT_AMC"};

  std::vector<std::string> Histos; for(int i=0;i<entries; ++i) { Histos.push_back(histarray[i]); }
  std::vector<std::string> Xaxis;  for(int i=0;i<entries; ++i) { Xaxis.push_back(xaxisarray[i]); }
  std::vector<std::string> Yaxis;  for(int i=0;i<entries; ++i) { Yaxis.push_back(yaxisarray[i]); }
  std::vector<std::string> Names;  for(int i=0;i<entries; ++i) { Names.push_back(namearray[i]); }

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
    
  std::string file_Q1_name = "QCD_HT-100To250_madgraph_Fall10.root";
  std::string file_Q2_name = "QCD_HT-250To500_madgraph_Fall10.root";
  std::string file_Q3_name = "QCD_HT-500To1000_madgraph_Fall10.root";
  std::string file_Q4_name = "QCD_HT-1000_madgraph_Fall10.root";
  
  std::string file_P1_name = "GJets_HT-40To100_madgraph_Fall10.root";
  std::string file_P2_name = "GJets_HT-100To200_madgraph_Fall10.root";
  std::string file_P3_name = "GJets_HT-200_madgraph_Fall10.root";
  
  std::string file_E1_name = "WJetsToLNu_madgraph-tauola_Fall10.root";
  std::string file_E2_name = "DYJetsToLL_madgraph-tauola_Fall10.root";
  std::string file_E3_name = "TTJets_madgraph-tauola_Fall10.root";
  
  std::string file_Z_name  = "ZinvisibleJets_7TeV-madgraph_Fall10.root";
  std::string file_D_name  = "Photon.root";
  
  // QCD BKG MC
  TFile * file_Q1 = new TFile(file_Q1_name.c_str(),"READ");
  TFile * file_Q2 = new TFile(file_Q2_name.c_str(),"READ");
  TFile * file_Q3 = new TFile(file_Q3_name.c_str(),"READ");
  TFile * file_Q4 = new TFile(file_Q4_name.c_str(),"READ");
  // EWK BKG MC
  TFile * file_E1 = new TFile(file_E1_name.c_str(),"READ");
  TFile * file_E2 = new TFile(file_E2_name.c_str(),"READ");
  TFile * file_E3 = new TFile(file_E3_name.c_str(),"READ");
  // SGN MC
  TFile * file_P1 = new TFile(file_P1_name.c_str(),"READ");
  TFile * file_P2 = new TFile(file_P2_name.c_str(),"READ");
  TFile * file_P3 = new TFile(file_P3_name.c_str(),"READ");
  // MC Truth
  TFile * file_Z  = new TFile(file_Z_name.c_str(),"READ");  
  // DATA
  TFile * file_D  = new TFile(file_D_name.c_str(),"READ");  

  // Read Histograms
  TH1F *Z, *Q1, *Q2, *Q3, *Q4, *E1, *E2, *E3, *P1, *P2, *P3, *D;
  TH1F *Zi, *Q1i, *Q2i, *Q3i, *Q4i, *E1i, *E2i, *E3i, *P1i, *P2i, *P3i, *Di;
  int Za, Q1a, Q2a, Q3a, Q4a, E1a, E2a, E3a, P1a, P2a, P3a, *Da;
  
  // Amount of processed events (MC) :
  Q1i = ((TH1F*) file_Q1->Get("EventCounters")); Q1a = Q1i->GetBinContent(1);
  Q2i = ((TH1F*) file_Q2->Get("EventCounters")); Q2a = Q2i->GetBinContent(1);
  Q3i = ((TH1F*) file_Q3->Get("EventCounters")); Q3a = Q3i->GetBinContent(1);
  Q4i = ((TH1F*) file_Q4->Get("EventCounters")); Q4a = Q4i->GetBinContent(1);
  
  E1i = ((TH1F*) file_E1->Get("EventCounters")); E1a = E1i->GetBinContent(1);
  E2i = ((TH1F*) file_E2->Get("EventCounters")); E2a = E2i->GetBinContent(1);
  E3i = ((TH1F*) file_E3->Get("EventCounters")); E3a = E3i->GetBinContent(1);
  
  P1i = ((TH1F*) file_P1->Get("EventCounters")); P1a = P1i->GetBinContent(1);
  P2i = ((TH1F*) file_P2->Get("EventCounters")); P2a = P2i->GetBinContent(1);
  P3i = ((TH1F*) file_P3->Get("EventCounters")); P3a = P3i->GetBinContent(1);
  
  Zi = ((TH1F*)  file_Z->Get("EventCounters")); Za  = Zi->GetBinContent(1);
  Di = ((TH1F*)  file_D->Get("EventCounters")); Da  = Di->GetBinContent(1);
  
  // Cross Sections in pb
  // --------------------                                                                                                                                                                               
  std::vector<double> cross_sections; 
  // QCD cross sections
  cross_sections.push_back(7000000.00); cross_sections.push_back(171000.00); cross_sections.push_back(5200.00); cross_sections.push_back(83.00);
  // EWL cross sections
  cross_sections.push_back(31300.00); cross_sections.push_back(3100.00); cross_sections.push_back(165.00); // NNLO (24380, 2289, 95 @ LO)
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
 events.push_back(Q1a); events.push_back(Q2a); events.push_back(Q3a); events.push_back(Q4a);
 events.push_back(E1a); events.push_back(E2a); events.push_back(E3a);
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
 
 for (int ii=0; ii<entries; ++ii) {
    // Debug modus for only 1 plot
    // if (ii != 0) continue;
    // 
    std::cout<<"==== i = "<<ii<<" ==== "<<Histos[ii]<<" ==== "<<Xaxis[ii]<<" ==== "<<Yaxis[ii]<<" ==== "<<std::endl;

    std::string SelHisto = Histos[ii];
    std::string xaxis = Xaxis[ii];
    std::string yaxis = Yaxis[ii];
    std::string NameHisto = Names[ii];
    
    Q1 = ((TH1F*) file_Q1->Get((dir+SelHisto).c_str()));
    Q2 = ((TH1F*) file_Q2->Get((dir+SelHisto).c_str()));
    Q3 = ((TH1F*) file_Q3->Get((dir+SelHisto).c_str()));
    Q4 = ((TH1F*) file_Q4->Get((dir+SelHisto).c_str()));
    E1 = ((TH1F*) file_E1->Get((dir+SelHisto).c_str()));
    E2 = ((TH1F*) file_E2->Get((dir+SelHisto).c_str()));
    E3 = ((TH1F*) file_E3->Get((dir+SelHisto).c_str()));
    P1 = ((TH1F*) file_P1->Get((dir+SelHisto).c_str()));
    P2 = ((TH1F*) file_P2->Get((dir+SelHisto).c_str()));
    P3 = ((TH1F*) file_P3->Get((dir+SelHisto).c_str()));
    
    D = ((TH1F*)  file_D->Get((dir+SelHisto).c_str()));
    Z = ((TH1F*)  file_Z->Get((dir+SelHisto).c_str()));
    
    // Final Histograms
    TH1F *Q, *P, *A, *E;
    Q = (TH1F*) Q1->Clone("QCD"); int n_Q = Q->GetNbinsX(); for (int i=1; i<=n_Q; ++i) {Q->SetBinContent(i,0.0);}
    P = (TH1F*) P1->Clone("Sig"); int n_P = P->GetNbinsX(); for (int i=1; i<=n_P; ++i) {P->SetBinContent(i,0.0);}
    E = (TH1F*) E1->Clone("All"); int n_E = E->GetNbinsX(); for (int i=1; i<=n_E; ++i) {E->SetBinContent(i,0.0);}
    A = (TH1F*) Q1->Clone("All"); int n_A = A->GetNbinsX(); for (int i=1; i<=n_A; ++i) {A->SetBinContent(i,0.0);}

    // Q = new TH1F("QCD_Pt","QCD MC Photon Pt Distribution", 100, 0, 500);
    // P = new TH1F("Sig_Pt","Signal MC Photon Pt Distribution", 100, 0, 500);
    // A = new TH1F("All",   "All MC Photon Pt Distribution", 100, 0, 500);
    

    // Scaling: cross section [pb] x lumi [pb^-1] / number of events before any selection
    Q1->Sumw2(); Q1->Scale(scaling[0]); 
    Q2->Sumw2(); Q2->Scale(scaling[1]);
    Q3->Sumw2(); Q3->Scale(scaling[2]);
    Q4->Sumw2(); Q4->Scale(scaling[3]);

    E1->Sumw2(); E1->Scale(scaling[4]);
    E2->Sumw2(); E2->Scale(scaling[5]);
    E3->Sumw2(); E3->Scale(scaling[6]);
    
    P1->Sumw2(); P1->Scale(scaling[7]);
    P2->Sumw2(); P2->Scale(scaling[8]);
    P3->Sumw2(); P3->Scale(scaling[9]);

    Z->Sumw2(); Z->Scale(scaling[10]*5);
    D->Sumw2(); 

    // Merge QCD and Photon and EWK samples 
    THStack *qs = new THStack("qs","Debug QCD Merge");
    Q1->SetFillColor(kOrange);  qs->Add(Q1);
    Q2->SetFillColor(kPink);    qs->Add(Q2);
    Q3->SetFillColor(kViolet);  qs->Add(Q3);
    Q4->SetFillColor(kAzure);   qs->Add(Q4);
    Q->Add(Q1); Q->Add(Q2); Q->Add(Q3); Q->Add(Q4); 
    // Debug: Test
    // TCanvas * t1 = new TCanvas("t1","QCD",800,600);
    // t1->cd(); Q->Draw(); qs->Draw("same");
    //
    THStack *ps = new THStack("ps","Debug Gam Merge");
    P1->SetFillColor(kOrange);  ps->Add(P1);
    P2->SetFillColor(kPink);    ps->Add(P2);
    P3->SetFillColor(kViolet);  ps->Add(P3);
    P->Add(P1); P->Add(P2); P->Add(P3); 
    // Debug: Test
    // TCanvas * t2 = new TCanvas("t2","Photon",800,600);
    // t2->cd(); P->Draw(); ps->Draw("same");
    // 
    THStack *es = new THStack("es","Debug EWK Merge");
    E3->SetFillColor(kOrange);    es->Add(E3);
    E2->SetFillColor(kPink);      es->Add(E2);
    E1->SetFillColor(kViolet);    es->Add(E1);
    E->Add(E1); E->Add(E2); E->Add(E3);
    // Debug: Test
    // TCanvas * t3 = new TCanvas("t3","EWK",800,600);
    // t3->cd(); E->Draw(); es->Draw("same");
    // Def Merge
    THStack *as = new THStack("as","All Merge");
    E->SetFillColor(kYellow); as->Add(E);
    Q->SetFillColor(kGreen);  as->Add(Q);
    P->SetFillColor(kRed);    as->Add(P);
    A->Add(E); A->Add(Q); A->Add(P);



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
    ratio->SetMinimum(0.2);                                                                                                                                                                             
    ratio->SetMaximum(1.2);   
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
