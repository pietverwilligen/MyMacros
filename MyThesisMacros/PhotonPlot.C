#include "TCanvas.h"
#include "TStyle.h"
#include "TFile.h"
#include "TH1F.h"
#include "TLegend.h"

void PhotonPlot() {

  int entries = 11; // !!! Aanpassen !!!
  // std::string dir = "RECO/RECO_3Jets_Egamma/";
  std::string dir = "RECO/RECO_Egamma/";
  std::string histarray[] = {"Et", "Eta", "Phi", "HE", "HolTrkIso", "EcalIso", "HcalIso", "PixelSeeds", "SigmaIEtaIEta", "SigmaIPhiIPhi", "V_PoverE"};
  std::string xaxisarray[] = {"Et #gamma [GeV]", "#eta #gamma [-]", "#phi #gamma [-]", "H/E #gamma [-]", "TRK Iso #gamma [GeV/c]", "ECAL Iso #gamma [GeV]", "HCAL Iso #gamma [GeV]", "Pixel Seed #gamma [-]", "#sigma_{I #eta I #eta} #gamma [-]", "#sigma_{I #phi I #phi} #gamma [-]", "Conversion #gamma: Pair p  over SC E [-]"};
  std::string yaxisarray[] = {"#gamma candidates / 5 GeV", "#gamma candidates / 0.20", "#gamma candidates / #frac{2 #pi}{18}", "#gamma candidates / 0.005", "#gamma candidates / 0.25 GeV/c", "#gamma candidates / 0.25 GeV", "#gamma candidates / 0.25 GeV",  "#gamma candidates", "#gamma candidates / 0.0005", "#gamma candidates / 0.0005", "#gamma candiates [A.U.]"};
  std::string namearray[] = {"PhotonEt","PhotonEta", "PhotonPhi", "PhotonHE", "PhotonTrkIso", "PhotonEcalIso", "PhotonHcalIso", "PhotonPS", "PhotonSIEIE", "PhotonSIPIP", "PhotonPoverE"};

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
    
  std::string file_Q1_name = "QCD_HT-100To250_madgraph_Fall10_v0.root";
  std::string file_Q2_name = "QCD_HT-250To500_madgraph_Fall10_v0.root";
  std::string file_Q3_name = "QCD_HT-500To1000_madgraph_Fall10_v0.root";
  std::string file_Q4_name = "QCD_HT-1000_madgraph_Fall10_v0.root";
  
  std::string file_P1_name = "GJets_HT-40To100_madgraph_Fall10_v0.root";
  std::string file_P2_name = "GJets_HT-100To200_madgraph_Fall10_v0.root";
  std::string file_P3_name = "GJets_HT-200_madgraph_Fall10_v0.root";
  
  std::string file_E1_name = "WJetsToLNu_madgraph-tauola_Fall10_v0.root";
  std::string file_E2_name = "DYJetsToLL_madgraph-tauola_Fall10_v0.root";
  std::string file_E3_name = "TTJets_madgraph-tauola_Fall10_v0.root";
  
  std::string file_Z_name  = "ZinvisibleJets_7TeV-madgraph_Fall10_v0.root";
  std::string file_D_name  = "Photon_v0.root";
  
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
  cross_sections.push_back(31000.00); cross_sections.push_back(3100.00); cross_sections.push_back(165.00); // NNLO (24380, 2289, 95 @ LO)
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
    Q1->Scale(scaling[0]); 
    Q2->Scale(scaling[1]);
    Q3->Scale(scaling[2]);
    Q4->Scale(scaling[3]);

    E1->Scale(scaling[4]);
    E2->Scale(scaling[5]);
    E3->Scale(scaling[6]);
    
    P1->Scale(scaling[7]);
    P2->Scale(scaling[8]);
    P3->Scale(scaling[9]);
    
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

    // All MC + DATA
    TCanvas * c1 = new TCanvas("c","canvas",800,600);
    c1->cd();
    c1->SetLogy(1);
    A->GetYaxis()->SetRangeUser(3e-4,1e4);
    /*
    if(ii != 5 && ii != 7 && ii != 15 && ii != 17) {
      c1->SetLogy(1);
      A->GetYaxis()->SetRangeUser(3e-4,1e8);
    }
    else {
      // A->GetYaxis()->SetRangeUser(0,3e3);
      if(ii == 5 || ii == 15) A->GetYaxis()->SetRangeUser(0,3e5);
      if(ii == 7)    A->GetYaxis()->SetRangeUser(0,1e5);
      if(ii == 17)   A->GetYaxis()->SetRangeUser(0,2e4);
    }
    */
    D->SetMarkerStyle(20); D->SetMarkerColor(kBlack); D->SetLineColor(kBlack); D->SetMarkerSize(0.75);
    A->GetYaxis()->SetTitle(yaxis.c_str());
    A->GetYaxis()->SetLabelSize(0.025);
    // A->GetYaxis()->SetTicks("+");
    // A->GetXaxis()->SetTitle(xaxis.c_str())
    A->GetXaxis()->SetLabelSize(0.0000025);
    A->GetXaxis()->SetTicks("+-");
    A->Draw();
    as->Draw("same");
    D->Draw("sameE");
    gPad->RedrawAxis();
    gStyle->SetGridStyle(3);
    // Coordinates for TLegend: x1, y1, x2, y2
    TLegend *l1 = new TLegend(0.60,0.75,0.85,0.85,NULL,"brNDC");
    l1->SetLineColor(0);
    l1->SetLineStyle(0);
    l1->SetLineWidth(0);
    l1->SetFillColor(4000);
    l1->SetBorderSize(0);
    l1->AddEntry(E, "EWK: W,Z,t#bar{t}","f");
    l1->AddEntry(Q, "QCD: prompt, frag & decay","f");
    l1->AddEntry(P, "Photon: prompt","f");
    l1->AddEntry(D, "Data","pel");
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
    ratio = (TH1F*)D->Clone();
    ratio->Divide(D, A, 1, 1, "b");
    ratio->SetMinimum(0.0);                                                                                                                                                                             
    ratio->SetMaximum(4.0);   
    ratio->GetYaxis()->SetNdivisions(505); // N1 + 100 * N2 (small ticks and big ticks) defines the grid
    ratio->GetYaxis()->SetLabelSize(0.025);
    ratio->GetYaxis()->SetTitle("Data / MC");
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
