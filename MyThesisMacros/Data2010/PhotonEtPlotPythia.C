#include "TCanvas.h"
#include "TStyle.h"
#include "TFile.h"
#include "TH1F.h"
#include "TLegend.h"

void PhotonEtPlotPythia(void) {


  // ==============================================
  // Important Variables that Change for each plot:
  //
  // Name of DIR (Run/Configuration/Data)
  // Histo to plot
  // X and Y axis names
  //
  // ==============================================

  // Dir
  // std::string DataDir = "D_Run_FirstProd";
  // std::string DataDir = "D_Run_PythiaLoose";
  std::string DataDir = "";
  // Histogram String
  string sel       = "RECO/RECO_Barrel_Egamma/";

  string histo = "Et";
  string SelHisto = sel+histo;


  // string yaxis = "Events / 5 GeV/c";
  string yaxis = "Events / 5 GeV";
  // string xaxis = "p_{T} #gamma (GeV/c)";
  string xaxis = "E_{T} #gamma (GeV)";
  // string xaxis = "#eta #gamma (GeV/c)";
  // string xaxis = "#phi #gamma (GeV/c)";


  // ==============================================
  // LUMINOSITY
  // 
  // ==============================================

  // lumi (34 files)
  // double lumi = 1224814.130; // ub^-1

  // lumi 2010A 
  // double lumi = 3068636.598; // ub^-1
  double lumi = 1333777.395; // ub^-1

  // Scale luminosity to inverse picobarns
  lumi = lumi / 1000000;     // pb^-1


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

  TCanvas * PhotonPt = new TCanvas("PhotonPt","PhotonPt",800,600);
  PhotonPt->SetFillColor(10);
  PhotonPt->Divide(2,2);

  // PhotonPt->SetLogy(1);
  // PhotonPt->SetLogx(1);
  // PhotonPt->SetGrid();

  std::string file_Q1_name = "QCD_Pt30to50_Fall10.root";
  std::string file_Q2_name = "QCD_Pt50to80_Fall10.root";
  std::string file_Q3_name = "QCD_Pt80to120_Fall10.root";
  std::string file_Q4_name = "QCD_Pt120to170_Fall10.root";
  std::string file_Q5_name = "QCD_Pt170to300_Fall10.root";
  std::string file_Q6_name = "QCD_Pt300to470_Fall10.root";

  std::string file_P1_name = "PhotonJet_Pt30_Summer10.root";
  // std::string file_P2_name = DataDir+"/"+"Loose_PhotonJet_Pt80_Spring10.root";
  // std::string file_P3_name = DataDir+"/"+"Loose_PhotonJet_Pt170_Spring10.root";

  std::string file_D_name  = "EGRun2010A-Nov4ReReco_v1.root";


  // BKG MC
  TFile * file_Q1 = new TFile(file_Q1_name.c_str(),"READ");
  TFile * file_Q2 = new TFile(file_Q2_name.c_str(),"READ");
  TFile * file_Q3 = new TFile(file_Q3_name.c_str(),"READ");

  // SGN MC
  TFile * file_P1 = new TFile(file_P1_name.c_str(),"READ");
  TFile * file_P2 = new TFile(file_P2_name.c_str(),"READ");
  TFile * file_P3 = new TFile(file_P3_name.c_str(),"READ");
  // DATA
  TFile * file_D  = new TFile(file_D_name.c_str(),"READ");

  // Read Histograms
  TH1F *Z, *W, *T, *Q1, *Q2, *Q3, *Q4, *Q5, *P1, *P2, *P3, *D;
  TH1F *Zi, *Wi, *Ti, *Q1i, *Q2i, *Q3i, *Q4i, *Q5i, *P1i, *P2i, *P3i, *Di;
  int Za, Wa, Ta, Q1a, Q2a, Q3a, Q4a, Q5a, P1a, P2a, P3a, *Da;


  Q1 = ((TH1F*) file_Q1->Get(SelHisto.c_str()));
  Q2 = ((TH1F*) file_Q2->Get(SelHisto.c_str()));
  Q3 = ((TH1F*) file_Q3->Get(SelHisto.c_str()));

  P1 = ((TH1F*) file_P1->Get(SelHisto.c_str()));
  P2 = ((TH1F*) file_P2->Get(SelHisto.c_str()));
  P3 = ((TH1F*) file_P3->Get(SelHisto.c_str()));

   D = ((TH1F*)  file_D->Get(SelHisto.c_str()));

  Q1i = ((TH1F*) file_Q1->Get("EventCounters")); Q1a = Q1i->GetBinContent(1); if(Q1a == 0) Q1a = Q1i->GetBinContent(2);
  Q2i = ((TH1F*) file_Q2->Get("EventCounters")); Q2a = Q2i->GetBinContent(1); if(Q2a == 0) Q2a = Q2i->GetBinContent(2); 
  Q3i = ((TH1F*) file_Q3->Get("EventCounters")); Q3a = Q3i->GetBinContent(1); if(Q3a == 0) Q3a = Q3i->GetBinContent(2); 

  P1i = ((TH1F*) file_P1->Get("EventCounters")); P1a = P1i->GetBinContent(1); if(P1a == 0) P1a = P1i->GetBinContent(2); 
  P2i = ((TH1F*) file_P2->Get("EventCounters")); P2a = P2i->GetBinContent(1); if(P2a == 0) P2a = P2i->GetBinContent(2); 
  P3i = ((TH1F*) file_P3->Get("EventCounters")); P3a = P3i->GetBinContent(1); if(P3a == 0) P3a = P3i->GetBinContent(2); 

   Di = ((TH1F*)  file_D->Get("EventCounters")); Da  = Di->GetBinContent(1);  if(Da  == 0) Da  = Di->GetBinContent(2); 

  // Final Histograms
  TH1F *Q, *P;
  Q = new TH1F("QCD_Pt","QCD MC Photon Pt Distribution", 100, 0, 500);
  P = new TH1F("Sig_Pt","Signal MC Photon Pt Distribution", 100, 0, 500);
  A = new TH1F("All",   "All MC Photon Pt Distribution", 100, 0, 500);

  // Scaling: cross section [pb] x lumi [pb^-1] / number of events before any selection
  Q1->Scale(60410000 * lumi / Q1a); 
  Q2->Scale(  923800 * lumi / Q2a);
  Q3->Scale(   25470 * lumi / Q3a);

  P1->Scale(   20070    * lumi / P1a);
  P2->Scale(     556.5  * lumi / P1a);
  P3->Scale(      24.37 * lumi / P1a);

  // QCD 
  PhotonPt->cd(1);
  PhotonPt->cd(1)->SetLogy(1);
  THStack *qs = new THStack("qs","Debug QCD Merge");
  Q1->SetFillColor(kOrange);  qs->Add(Q1);
  Q2->SetFillColor(kPink);    qs->Add(Q2);
  Q3->SetFillColor(kViolet);  qs->Add(Q3);
  Q->Add(Q1); Q->Add(Q2); Q->Add(Q3); 
  Q->Draw();
  Q->GetYaxis()->SetTitle(yaxis.c_str());
  Q->GetYaxis()->SetRangeUser(1e-5,1e3);
  Q->GetXaxis()->SetTitle(xaxis.c_str());
  qs->Draw("SAME");
  // Coordinates for TLegend: x1, y1, x2, y2
  TLegend *l1 = new TLegend(0.60,0.4,0.85,0.85,NULL,"brNDC");
  l1->SetLineColor(0);
  l1->SetLineStyle(0);
  l1->SetLineWidth(0);
  l1->SetFillColor(4000);
  l1->SetBorderSize(0);
  // l1->SetHeader("p_{T} all Identified Photons");
  l1->AddEntry(Q1, "QCD  30 GeV/c","F");                                                                                                                                                      
  l1->AddEntry(Q2, "QCD  80 GeV/c","F");                                                                                                                                             
  l1->AddEntry(Q3, "QCD 170 GeV/c","F");                                                                                                                                   
  l1->Draw();
                                                                    
  // SGN MC
  PhotonPt->cd(2);  
  PhotonPt->cd(2)->SetLogy(1);
  THStack *ps = new THStack("ps","Debug SGN Merge");
  P1->SetFillColor(kOrange);  ps->Add(P1);
  P2->SetFillColor(kPink);    ps->Add(P2);
  P3->SetFillColor(kViolet);  ps->Add(P3);
  P->Add(P1); P->Add(P2); P->Add(P3);  
  P->Draw();
  P->GetYaxis()->SetTitle(yaxis.c_str());
  P->GetYaxis()->SetRangeUser(1e-5,1e3);
  P->GetXaxis()->SetTitle(xaxis.c_str());
  ps->Draw("SAME");
  // Coordinates for TLegend: x1, y1, x2, y2
  TLegend *l2 = new TLegend(0.60,0.6,0.85,0.85,NULL,"brNDC");
  l2->SetLineColor(0);
  l2->SetLineStyle(0);
  l2->SetLineWidth(0);
  l2->SetFillColor(4000);
  l2->SetBorderSize(0);
  // l2->SetHeader("p_{T} all Identified Photons");
  l2->AddEntry(P1, "#gamma + Jet  30 GeV/c","F");                                                                                                                                                      
  l2->AddEntry(P2, "#gamma + Jet  80 GeV/c","F");                                                                                                                                             
  l2->AddEntry(P3, "#gamma + Jet 170 GeV/c","F");                                                                                                                                   
  l2->Draw();                                                                    

  // All MC
  PhotonPt->cd(3);
  PhotonPt->cd(3)->SetLogy(1);
  THStack *as = new THStack("as","All MC Merge");
  P->SetFillColor(kAzure);   as->Add(P);
  Q->SetFillColor(kTeal);    as->Add(Q);
   A->Add(P); A->Add(Q);
   A->Draw();
   A->GetYaxis()->SetTitle(yaxis.c_str());
   A->GetYaxis()->SetRangeUser(1e-5,1e3);
   A->GetXaxis()->SetTitle(xaxis.c_str());
   as->Draw("SAME");
   // Coordinates for TLegend: x1, y1, x2, y2
   TLegend *l3 = new TLegend(0.70,0.4,0.85,0.85,NULL,"brNDC");
   l3->SetLineColor(0);
   l3->SetLineStyle(0);
   l3->SetLineWidth(0);
   l3->SetFillColor(4000);
   l3->SetBorderSize(0);
   // l3->SetHeader("p_{T} all Identified Photons");
   l3->AddEntry(P, "#gamma  + Jet","F");                                                                                                                                             
   l3->AddEntry(Q, "QCD","F");                                                                                                                                   
   l3->Draw();                                                                    

   // All MC + DATA
   PhotonPt->cd(4);
   PhotonPt->cd(4)->SetLogy(1);
   D->SetMarkerStyle(20); D->SetMarkerColor(kBlack); D->SetLineColor(kBlack);
   A->Draw();
   A->GetYaxis()->SetTitle(yaxis.c_str());
   A->GetYaxis()->SetRangeUser(1e-5,1e3);
   A->GetXaxis()->SetTitle(xaxis.c_str());
   as->Draw("SAME");
   D->SetMarkerSize(0.75);
   D->Draw("E1SAME");
   // Coordinates for TLegend: x1, y1, x2, y2
   TLegend *l4 = new TLegend(0.70,0.4,0.85,0.80,NULL,"brNDC");
   l4->SetLineColor(0);
   l4->SetLineStyle(0);
   l4->SetLineWidth(0);
   l4->SetFillColor(4000);
   l4->SetBorderSize(0);
   // l4->SetHeader("p_{T} all Identified Photons");
   l4->AddEntry(D, "DATA","pl");
   l4->AddEntry(P, "#gamma  + Jet","F");                                                                                                                                             
   l4->AddEntry(Q, "QCD","F");                                                                                                                                   
   l4->Draw();                                                                    
   cmsPrelim(lumi);

   // Again, but bigger ...
   TCanvas * PhotonPtBig = new TCanvas("PhotonPtBig","PhotonPtBig",800,600);
   PhotonPtBig->cd();
   PhotonPtBig->SetLogy(1);
   A->Draw();
   A->GetYaxis()->SetTitle(yaxis.c_str());
   A->GetYaxis()->SetRangeUser(1e-5,1e3);
   A->GetXaxis()->SetTitle(xaxis.c_str());
   as->Draw("SAME");
   D->Draw("E1SAME");
   l4->Draw();
   cmsPrelim(lumi);

}

void cmsPrelim( double intLumi )
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
    latex.DrawLatex(0.90,0.82,Form("#int #font[12]{L} dt = %.1f pb^{-1}",intLumi));
  }
  latex.SetTextAlign(11); // align left
  //  latex.DrawLatex(0.18,0.96,"CMS preliminary 2010");
  latex.DrawLatex(0.10,0.92,"CMS preliminary 2010");
  // latex.DrawLatex(0.18,0.96,"CMS 2010");

}



  /*
  Frix_EffFakeScatter_n->SetMarkerSize(1);
  Frix_EffFakeScatter_n->SetMarkerStyle(29);
  Frix_EffFakeScatter_n->SetMarkerColor(1);
  Frix_EffFakeScatter_n->GetXaxis()->SetTitle("Fake Rate");
  // Frix_EffFakeScatter_n->GetXaxis()->SetTitleOffset(1.2);
  Frix_EffFakeScatter_n->GetYaxis()->SetTitle("Isolation Efficiency");
  Frix_EffFakeScatter_n->GetYaxis()->SetTitleOffset(1.2);
  Frix_EffFakeScatter_n->GetXaxis()->SetRangeUser(0.50,1.00);
  Frix_EffFakeScatter_n->GetYaxis()->SetRangeUser(0.88,1.000);
  Frix_EffFakeScatter_n->SetTitle("Isolation Efficiency of hard #gamma's vs Fake Rate due to Isolation of all #gamma's");
  Frix_EffFakeScatter_n->Draw();

  Frix_EffFakeScatter_d->SetMarkerSize(1);
  Frix_EffFakeScatter_d->SetMarkerStyle(20);
  Frix_EffFakeScatter_d->SetMarkerColor(2);
  Frix_EffFakeScatter_d->Draw("SAME");

  Frix_EffFakeScatter_e->SetMarkerSize(1);
  Frix_EffFakeScatter_e->SetMarkerStyle(21);
  Frix_EffFakeScatter_e->SetMarkerColor(3);
  Frix_EffFakeScatter_e->Draw("SAME");

  Trad_EffFakeScatter_d->SetMarkerSize(1);
  Trad_EffFakeScatter_d->SetMarkerStyle(24);
  Trad_EffFakeScatter_d->SetMarkerColor(4);
  Trad_EffFakeScatter_d->Draw("SAME");

  Trad_EffFakeScatter_e->SetMarkerSize(1);
  Trad_EffFakeScatter_e->SetMarkerStyle(25);
  Trad_EffFakeScatter_e->SetMarkerColor(6);
  Trad_EffFakeScatter_e->Draw("SAME");



  // Legend

  // For a horizontal Legend
  // TLegend* leg = new TLegend(0.09770115,0.9173729,0.8994253,0.9830508,NULL,"brNDC");
  // leg->SetNColumns(5);
  // For a normal one
  // Coordinates for TLegend: x1, y1, x2, y2
  TLegend *leg = new TLegend(0.35,0.15,0.63,0.40,NULL,"brNDC");
  leg->SetLineColor(1);
  leg->SetLineStyle(0);
  leg->SetLineWidth(1);
  leg->SetFillColor(18);
  leg->SetBorderSize(0);
  leg->SetHeader("All Photons: No pt cut");
  // leg->SetHeader("Photons: pt cut @ 2GeV/c");
  leg->AddEntry(Frix_EffFakeScatter_n, "Frix Iso (n)","P");
  leg->AddEntry(Frix_EffFakeScatter_d, "Frix Iso (#delta_{0})","P");
  leg->AddEntry(Frix_EffFakeScatter_e, "Frix Iso (#varepsilon_{#gamma})","P");
  leg->AddEntry(Trad_EffFakeScatter_d, "Trad Iso (#delta_{0})","P");
  leg->AddEntry(Trad_EffFakeScatter_e, "Trad Iso (#varepsilon_{#gamma})","P");
  leg->Draw();

  // Efkes Zot Doen
  // Coordinates for TPad: x1, y1, x2, y2
  TPad *pad = new TPad("pad", "pad",0.65,0.10,0.90,0.825);
  // pad->SetFillColor(0);
  pad->SetFillStyle(4000);
  pad->SetBorderMode(0);
  pad->SetBorderSize(0);
  //pad->SetLineColor(1);
  //pad->SetLineWidth(2);
  pad->SetTopMargin(0.025);
  pad->SetBottomMargin(0.05);
  pad->SetLeftMargin(0.075);
  pad->SetRightMargin(0.025);
  // pad->SetLogx(1);
  // pad->SetLogy(1);
  pad->Draw();
  pad->cd();
  TH2F * s2_Frix_EffFakeScatter_n = new TH2F(*Frix_EffFakeScatter_n);
  TH2F * s2_Frix_EffFakeScatter_d = new TH2F(*Frix_EffFakeScatter_d);
  TH2F * s2_Frix_EffFakeScatter_e = new TH2F(*Frix_EffFakeScatter_e);
  TH2F * s2_Trad_EffFakeScatter_d = new TH2F(*Trad_EffFakeScatter_d);
  TH2F * s2_Trad_EffFakeScatter_e = new TH2F(*Trad_EffFakeScatter_e);
  TAxis * s2_Xaxis = s2_Frix_EffFakeScatter_n->GetXaxis();
  TAxis * s2_Yaxis = s2_Frix_EffFakeScatter_n->GetYaxis();
  s2_Xaxis->SetDrawOption("-");
  s2_Xaxis->SetDrawOption("-");
  s2_Xaxis->SetLabelOffset(-0.1);
  s2_Xaxis->SetLabelOffset(-0.1);
  s2_Xaxis->SetRangeUser(0.83725,0.83850);
  s2_Xaxis->SetTitle("");
  s2_Yaxis->SetRangeUser(0.960,1.000);
  s2_Yaxis->SetTitle("");
  s2_Frix_EffFakeScatter_n->SetTitle(0);
  s2_Frix_EffFakeScatter_n->Draw();
  // s2_Frix_EffFakeScatter_n->SetMaximum(10000);
  s2_Frix_EffFakeScatter_d->Draw("SAME");
  s2_Frix_EffFakeScatter_e->Draw("SAME");
  s2_Trad_EffFakeScatter_d->Draw("SAME");
  s2_Trad_EffFakeScatter_e->Draw("SAME");
  //pad->Update();
  //pad->RedrawAxis();
  pad->Modified();

  */


