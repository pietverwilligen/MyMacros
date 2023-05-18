#include "TCanvas.h"
#include "TStyle.h"
#include "TFile.h"
#include "TH1F.h"
#include "TLegend.h"

void PhotonPreSelectionPlot() {

  std::string histarray[] = {"PB_Et_B", "PB_Eta_B", "PB_TRK", "PB_ECAL", "PB_HCAL", "PB_PS", "PB_HE", "PB_SIEIE", "PB_Et_A", "PB_Eta_A", "PE_Et_B", "PE_Eta_B", "PE_TRK", "PE_ECAL", "PE_HCAL", "PE_PS", "PE_HE", "PE_SIEIE", "PE_Et_A", "PE_Eta_A"}; 
  std::string xaxisarray[] = {"Et Barrel #gamma [GeV] before #sigma_{I #eta I #eta} cut", "#eta Barrel #gamma [-] before #sigma_{I #eta I #eta} cut", "TRK Iso Barrel #gamma [GeV/c]", "ECAL Iso Barrel #gamma [GeV]", "HCAL Iso Barrel #gamma [GeV]", "Pixel Seed Barrel #gamma [-]", "H/E Barrel #gamma [-]", "#sigma_{I #eta I #eta} Barrel #gamma [-]", "Et Barrel #gamma [GeV] after #sigma_{I #eta I #eta} cut", "#eta Barrel #gamma [-] after #sigma_{I #eta I #eta} cut", "Et Endcap #gamma [GeV] before #sigma_{I #eta I #eta} cut", "#eta Endcap #gamma [-] before #sigma_{I #eta I #eta} cut", "TRK Iso Endcap #gamma [GeV/c]", "ECAL Iso Endcap #gamma [GeV]", "HCAL Iso Endcap #gamma [GeV]", "Pixel Seed Endcap #gamma [-]", "H/E Endcap #gamma [-]", "#sigma_{I #eta I #eta} Endcap #gamma [-]", "Et Endcap #gamma [GeV] after #sigma_{I #eta I #eta} cut", "#eta Endcap #gamma [-] after #sigma_{I #eta I #eta} cut"}; 
  std::string yaxisarray[] = {"#gamma candidates / 5 GeV", "#gamma candidates / 0.25", "#gamma candidates / 0.5 GeV/c", "#gamma candidates / 0.5 GeV", "#gamma candidates / 0.5 GeV",  "N #gamma's", "#gamma candidates / 0.005", "#gamma candidates / 0.0005", "#gamma candidates / 5 GeV", "#gamma candidates / 0.25", "#gamma candidates / 5 GeV", "#gamma candidates / 0.25", "#gamma candidates / 0.5 GeV/c", "#gamma candidates / 0.5 GeV", "#gamma candidates / 0.5 GeV",  "N #gamma's", "#gamma candidates / 0.005","#gamma candidates / 0.0005", "#gamma candidates / 5 GeV", "#gamma candidates / 0.25"}; 



  std::vector<std::string> Histos; for(int i=0;i<20; ++i) { Histos.push_back(histarray[i]); }
  std::vector<std::string> Xaxis;  for(int i=0;i<20; ++i) { Xaxis.push_back(xaxisarray[i]); }
  std::vector<std::string> Yaxis;  for(int i=0;i<20; ++i) { Yaxis.push_back(yaxisarray[i]); }

  for (int ii=0; ii<20; ++ii) {
    // if (ii != 6) continue;
    std::cout<<"==== i = "<<ii<<" ===="<<std::endl;
    std::string SelHisto = Histos[ii];
    std::string xaxis = Xaxis[ii];
    std::string yaxis = Yaxis[ii];

    // ==============================================
    // LUMINOSITY
    // 
    // ==============================================
    
    // lumi (34 files)
    // double lumi = 1224814.130; // ub^-1
    // lumi 2010A 
    // double lumi = 3068636.598; // ub^-1
    // lumi Proof_Run2010A
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
    
    // TCanvas * PhotonPt = new TCanvas("PhotonEt","PhotonEt",800,600);
    // PhotonPt->SetFillColor(10);
    // PhotonPt->Divide(2,2);
    
    // PhotonPt->SetLogy(1);
    // PhotonPt->SetLogx(1);
    // PhotonPt->SetGrid();
    
    std::string file_Q1_name = "PhotonPreSelectionPlots_QCD_Pt30to50_Fall10.root";
    std::string file_Q2_name = "PhotonPreSelectionPlots_QCD_Pt50to80_Fall10.root";
    std::string file_Q3_name = "PhotonPreSelectionPlots_QCD_Pt80to120_Fall10.root";
    std::string file_Q4_name = "PhotonPreSelectionPlots_QCD_Pt120to170_Fall10.root";
    std::string file_Q5_name = "PhotonPreSelectionPlots_QCD_Pt170to300_Fall10.root";
    std::string file_Q6_name = "PhotonPreSelectionPlots_QCD_Pt300to470_Fall10.root";
    std::string file_P1_name = "PhotonPreSelectionPlots_PhotonJet_Pt30_Summer10.root";
    // std::string file_P2_name = 
    // std::string file_P3_name = 
    std::string file_D_name  = "PhotonPreSelectionPlots_EGRun2010A-Nov4ReReco_v1.root";
    
    
    // BKG MC
    TFile * file_Q1 = new TFile(file_Q1_name.c_str(),"READ");
    TFile * file_Q2 = new TFile(file_Q2_name.c_str(),"READ");
    TFile * file_Q3 = new TFile(file_Q3_name.c_str(),"READ");
    TFile * file_Q4 = new TFile(file_Q4_name.c_str(),"READ");
    TFile * file_Q5 = new TFile(file_Q5_name.c_str(),"READ");
    TFile * file_Q6 = new TFile(file_Q6_name.c_str(),"READ");
    // SGN MC
    TFile * file_P1 = new TFile(file_P1_name.c_str(),"READ");
    // TFile * file_P2 = new TFile(file_P2_name.c_str(),"READ");
    // TFile * file_P3 = new TFile(file_P3_name.c_str(),"READ");
    // DATAstd::string xaxisarray[]
    TFile * file_D  = new TFile(file_D_name.c_str(),"READ");
    
    // Read Histograms
    TH1F *Z, *W, *T, *Q1, *Q2, *Q3, *Q4, *Q5, *Q6, *P1, *P2, *P3, *D;
    TH1F *Zi, *Wi, *Ti, *Q1i, *Q2i, *Q3i, *Q4i, *Q5i, *Q6i, *P1i, *P2i, *P3i, *Di;
    int Za, Wa, Ta, Q1a, Q2a, Q3a, Q4a, Q5a, Q6a, P1a, P2a, P3a, *Da;
    
    // Amount of processed events (MC) :
    /*
      Q1i = ((TH1F*) file_Q1->Get("EventCounters")); Q1a = Q1i->GetBinContent(1); if(Q1a == 0) Q1a = Q1i->GetBinContent(2);
      Q2i = ((TH1F*) file_Q2->Get("EventCounters")); Q2a = Q2i->GetBinContent(1); if(Q2a == 0) Q2a = Q2i->GetBinContent(2); 
      Q3i = ((TH1F*) file_Q3->Get("EventCounters")); Q3a = Q3i->GetBinContent(1); if(Q3a == 0) Q3a = Q3i->GetBinContent(2); 
      P1i = ((TH1F*) file_P1->Get("EventCounters")); P1a = P1i->GetBinContent(1); if(P1a == 0) P1a = P1i->GetBinContent(2); 
      P2i = ((TH1F*) file_P2->Get("EventCounters")); P2a = P2i->GetBinContent(1); if(P2a == 0) P2a = P2i->GetBinContent(2); 
      P3i = ((TH1F*) file_P3->Get("EventCounters")); P3a = P3i->GetBinContent(1); if(P3a == 0) P3a = P3i->GetBinContent(2); 
      Di = ((TH1F*)  file_D->Get("EventCounters")); Da  = Di->GetBinContent(1);  if(Da  == 0) Da  = Di->GetBinContent(2); 
    */
    // manual, because forget to implement to count all events ...
    Q1a=3264660;
    Q2a=2916546;
    Q3a=2858299;
    Q4a=2995200;
    Q5a=2850280;
    Q6a=2671240;
    P1a=1023806; // rough estimate
    
    // std::string SelHisto = "PB_Et_B";
    
    Q1 = ((TH1F*) file_Q1->Get(SelHisto.c_str()));
    Q2 = ((TH1F*) file_Q2->Get(SelHisto.c_str()));
    Q3 = ((TH1F*) file_Q3->Get(SelHisto.c_str()));
    Q4 = ((TH1F*) file_Q4->Get(SelHisto.c_str()));
    Q5 = ((TH1F*) file_Q5->Get(SelHisto.c_str()));
    Q6 = ((TH1F*) file_Q6->Get(SelHisto.c_str()));
    
    P1 = ((TH1F*) file_P1->Get(SelHisto.c_str()));
    // P2 = ((TH1F*) file_P2->Get(SelHisto.c_str()));
    // P3 = ((TH1F*) file_P3->Get(SelHisto.c_str()));
    
    D = ((TH1F*)  file_D->Get(SelHisto.c_str()));
    
    
    // Final Histograms
    TH1F *Q, *P, *A;
    Q = (TH1F*) Q1->Clone("QCD"); int n_Q = Q->GetNbinsX(); for (int i=1; i<=n_Q; ++i) {Q->SetBinContent(i,0.0);}
    P = (TH1F*) P1->Clone("Sig"); int n_P = P->GetNbinsX(); for (int i=1; i<=n_P; ++i) {P->SetBinContent(i,0.0);}
    A = (TH1F*) Q1->Clone("All"); int n_A = A->GetNbinsX(); for (int i=1; i<=n_A; ++i) {A->SetBinContent(i,0.0);}

    // Q = new TH1F("QCD_Pt","QCD MC Photon Pt Distribution", 100, 0, 500);
    // P = new TH1F("Sig_Pt","Signal MC Photon Pt Distribution", 100, 0, 500);
    // A = new TH1F("All",   "All MC Photon Pt Distribution", 100, 0, 500);
    

    // Scaling: cross section [pb] x lumi [pb^-1] / number of events before any selection
    Q1->Scale(5.312e+07 * lumi / Q1a); 
    Q2->Scale(6.359e+06 * lumi / Q2a);
    Q3->Scale(7.843e+05 * lumi / Q3a);
    Q4->Scale(1.151e+05 * lumi / Q1a); 
    Q5->Scale(2.426e+04 * lumi / Q2a);
    Q6->Scale(1.168e+03 * lumi / Q3a);
    
    P1->Scale(2.007e+04 * lumi / P1a);
    // P2->Scale(     556.5  * lumi / P1a);
    // P3->Scale(      24.37 * lumi / P1a);
    
    // QCD 
    // PhotonPt->cd(1);
    // PhotonPt->cd(1)->SetLogy(1);
    THStack *qs = new THStack("qs","Debug QCD Merge");
    Q1->SetFillColor(kOrange);  qs->Add(Q1);
    Q2->SetFillColor(kPink);    qs->Add(Q2);
    Q3->SetFillColor(kViolet);  qs->Add(Q3);
    Q4->SetFillColor(kAzure);   qs->Add(Q4);
    Q5->SetFillColor(kTeal);    qs->Add(Q5);
    Q6->SetFillColor(kSpring);  qs->Add(Q6);
    
    Q->Add(Q1); Q->Add(Q2); Q->Add(Q3); Q->Add(Q4); Q->Add(Q5); Q->Add(Q6);
    // Q->Draw();
    Q->GetYaxis()->SetTitle(yaxis.c_str());
    Q->GetYaxis()->SetRangeUser(1e-5,1e3);
    Q->GetXaxis()->SetTitle(xaxis.c_str());
    // qs->Draw("SAME");
    // Coordinates for TLegend: x1, y1, x2, y2
    TLegend *l1 = new TLegend(0.60,0.4,0.85,0.85,NULL,"brNDC");
    l1->SetLineColor(0);
    l1->SetLineStyle(0);
    l1->SetLineWidth(0);
    l1->SetFillColor(4000);
    l1->SetBorderSize(0);
    // l1->SetHeader("p_{T} all Identified Photons");
    l1->AddEntry(Q1, "QCD  30 -  50 GeV/c","F");
    l1->AddEntry(Q2, "QCD  50 -  80 GeV/c","F");
    l1->AddEntry(Q3, "QCD  80 - 120 GeV/c","F");                                                                                                                                  
    l1->AddEntry(Q4, "QCD 120 - 170 GeV/c","F");                                                                                                                                  
    l1->AddEntry(Q5, "QCD 170 - 300 GeV/c","F");                                                                                                                                  
    l1->AddEntry(Q6, "QCD 300 - 470 GeV/c","F");                                                                                                                                  
    // l1->Draw();
    
    // SGN MC
    // PhotonPt->cd(2);  
    // PhotonPt->cd(2)->SetLogy(1);
    THStack *ps = new THStack("ps","Debug SGN Merge");
    P1->SetFillColor(kOrange);  ps->Add(P1);
    // P2->SetFillColor(kPink);    ps->Add(P2);
    // P3->SetFillColor(kViolet);  ps->Add(P3);
    P->Add(P1); // P->Add(P2); P->Add(P3);  
    // P->Draw();
    P->GetYaxis()->SetTitle(yaxis.c_str());
    P->GetYaxis()->SetRangeUser(1e-5,1e3);
    P->GetXaxis()->SetTitle(xaxis.c_str());
    // ps->Draw("SAME");
    // Coordinates for TLegend: x1, y1, x2, y2
    TLegend *l2 = new TLegend(0.10,0.10,0.35,0.35,NULL,"brNDC");
    l2->SetLineColor(0);
    l2->SetLineStyle(0);
    l2->SetLineWidth(0);
    l2->SetFillColor(4000);
    l2->SetBorderSize(0);
    // l2->SetHeader("p_{T} all Identified Photons");
    l2->AddEntry(P1, "#gamma + Jet  30 GeV/c","F");
    // l2->AddEntry(P2, "#gamma + Jet  80 GeV/c","F");
    // l2->AddEntry(P3, "#gamma + Jet 170 GeV/c","F");       
    // l2->Draw();                                                                    
    
    // All MC
    // PhotonPt->cd(3);
    // PhotonPt->cd(3)->SetLogy(1);
    THStack *as = new THStack("as","All MC Merge");
    P->SetFillColor(kPink);   as->Add(P);
    Q->SetFillColor(kViolet);    as->Add(Q);
    A->Add(P); A->Add(Q);
    // A->Draw();
    A->GetYaxis()->SetTitle(yaxis.c_str());
    // A->GetYaxis()->SetRangeUser(1e-5,1e3);
    A->GetXaxis()->SetTitle(xaxis.c_str());
    // as->Draw("SAME");
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
    // l3->Draw();                                                                    
    
    // All MC + DATA
    // PhotonPt->cd(4);
    // PhotonPt->cd(4)->SetLogy(1);
    D->SetMarkerStyle(20); D->SetMarkerColor(kBlack); D->SetLineColor(kBlack);
    // A->Draw();
    A->GetYaxis()->SetTitle(yaxis.c_str());
    // A->GetYaxis()->SetRangeUser(1e-5,1e3);
    A->GetXaxis()->SetTitle(xaxis.c_str());
    // as->Draw("SAME");
    D->SetMarkerSize(0.75);
    // D->Draw("E1SAME");
    // Coordinates for TLegend: x1, y1, x2, y2
    TLegend *l4 = new TLegend(0.70,0.75,0.90,0.875,NULL,"brNDC");
    l4->SetLineColor(0);
    l4->SetLineStyle(0);
    l4->SetLineWidth(0);
    l4->SetFillColor(4000);
    l4->SetBorderSize(0);
    // l4->SetHeader("p_{T} all Identified Photons");
    l4->AddEntry(D, "DATA","pl");
    l4->AddEntry(P, "#gamma  + Jet","F");                                                                                                                                             
    l4->AddEntry(Q, "QCD","F");                                                                                                                                   
    // l4->Draw();                                                                    
    // cmsPrelim(lumi);
    
    // Again, but bigger ...
    TCanvas * PhotonPtBig = new TCanvas("PhotonPtBig","PhotonPtBig",800,600);
    PhotonPtBig->cd();
    if(ii != 5 && ii != 7 && ii != 15 && ii != 17) {
      PhotonPtBig->SetLogy(1);
      A->GetYaxis()->SetRangeUser(1e-5,1e4);
    }
    else {
      // A->GetYaxis()->SetRangeUser(0,3e3);
      if(ii == 5 || ii == 15) A->GetYaxis()->SetRangeUser(0,3e3);
      if(ii == 7)    A->GetYaxis()->SetRangeUser(0,850);
      if(ii == 17)   A->GetYaxis()->SetRangeUser(0,160);
    }
    PhotonPtBig->SetBottomMargin(0.2 + 0.8*PhotonPtBig->GetBottomMargin()-0.2*PhotonPtBig->GetTopMargin());
    A->Draw();
    A->GetYaxis()->SetTitle(yaxis.c_str());
    A->GetYaxis()->SetLabelSize(0.025);
    A->GetXaxis()->SetTicks("+");
    A->GetXaxis()->SetTitle(xaxis.c_str());
    A->GetXaxis()->SetLabelSize(0.0000025);
    A->GetXaxis()->SetTicks("+");
    as->Draw("SAME");
    D->Draw("E1SAME");
    l4->Draw();
    cmsPrelim(lumi);
    A->Draw("sameaxis");
    TPad *ratioPad = new TPad("BottomPad","",0,0,1,1);
    ratioPad->SetTopMargin(0.8 - 0.8*ratioPad->GetBottomMargin()+0.2*ratioPad->GetTopMargin());
    ratioPad->SetFillStyle(0);
    ratioPad->SetFrameFillColor(10);
    ratioPad->SetFrameBorderMode(0);
    ratioPad->Draw();
    ratioPad->cd();
    TH1* ratio = 0;
    ratio = (TH1F*)D->Clone();
    ratio->Divide(D, A, 1, 1, "b");
    // axr = (TH1F*)D->Clone();
    ratio->SetMinimum(0.0);
    ratio->SetMaximum(4.99);
    ratio->GetYaxis()->SetNdivisions(505);
    ratio->GetYaxis()->SetLabelSize(0.025);
    ratio->GetYaxis()->SetTitle("DATA / MC");
    ratio->GetXaxis()->SetTicks("+");
    ratio->GetXaxis()->SetTitle(xaxis.c_str());
    ratio->Draw("pe");
    
    savePlot(PhotonPtBig, SelHisto.c_str());
    // PhotonPtBig->Close();
  }
}



void savePlot(TCanvas * c, TString name) {
  c->SaveAs(name+".png");
  c->SaveAs(name+".eps");
  gSystem->Exec("epstopdf "+name+".eps");
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
    // latex.DrawLatex(0.90,0.82,Form("#int #font[12]{L} dt = %.1f pb^{-1}",intLumi));
    latex.DrawLatex(0.70,0.92,Form("#int #font[12]{L} dt = %.1f pb^{-1}",intLumi));
  }
  latex.SetTextAlign(11); // align left
  //  latex.DrawLatex(0.18,0.96,"CMS preliminary 2010");
  latex.DrawLatex(0.10,0.92,"CMS preliminary 2010");
  // latex.DrawLatex(0.18,0.96,"CMS 2010");

}




