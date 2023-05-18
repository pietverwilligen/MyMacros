#include "TCanvas.h"
#include "TStyle.h"
#include "TFile.h"
#include "TH1F.h"
#include "TLegend.h"

void PhotonPreSelectionPlot() {

  std::string Dir1 = "PHOTON";
  std::string Dir2 = "PSPIKE";

  int entries = 24; // !!! Aanpassen !!!

  std::string histarray[] = {"PB_Et_B", "PB_Eta_B", "PB_TRK", "PB_ECAL", "PB_HCAL", "PB_PS", "PB_HE", "PB_SIEIE", "PB_Et_A", "PB_Eta_A", "PE_Et_B", "PE_Eta_B", "PE_TRK", "PE_ECAL", "PE_HCAL", "PE_PS", "PE_HE", "PE_SIEIE", "PE_Et_A", "PE_Eta_A", "P_Et_B", "P_Eta_B", "P_Et_A", "P_Eta_A"}; 


  std::string xaxisarray[] = {"Et Barrel #gamma [GeV] before #sigma_{I #eta I #eta} cut", "#eta Barrel #gamma [-] before #sigma_{I #eta I #eta} cut", "TRK Iso Barrel #gamma [GeV/c]", "ECAL Iso Barrel #gamma [GeV]", "HCAL Iso Barrel #gamma [GeV]", "Pixel Seed Barrel #gamma [-]", "H/E Barrel #gamma [-]", "#sigma_{I #eta I #eta} Barrel #gamma [-]", "Et Barrel #gamma [GeV] after #sigma_{I #eta I #eta} cut", "#eta Barrel #gamma [-] after #sigma_{I #eta I #eta} cut", "Et Endcap #gamma [GeV] before #sigma_{I #eta I #eta} cut", "#eta Endcap #gamma [-] before #sigma_{I #eta I #eta} cut", "TRK Iso Endcap #gamma [GeV/c]", "ECAL Iso Endcap #gamma [GeV]", "HCAL Iso Endcap #gamma [GeV]", "Pixel Seed Endcap #gamma [-]", "H/E Endcap #gamma [-]", "#sigma_{I #eta I #eta} Endcap #gamma [-]", "Et Endcap #gamma [GeV] after #sigma_{I #eta I #eta} cut", "#eta Endcap #gamma [-] after #sigma_{I #eta I #eta} cut", "Et #gamma [GeV] before #sigma_{I #eta I #eta} cut", "#eta #gamma [-] before #sigma_{I #eta I #eta} cut", "Et #gamma [GeV] after #sigma_{I #eta I #eta} cut", "#eta #gamma [-] after #sigma_{I #eta I #eta} cut"}; 

  std::string yaxisarray[] = {"#gamma candidates / 5 GeV", "#gamma candidates / 0.20", "#gamma candidates / 0.5 GeV/c", "#gamma candidates / 0.5 GeV", "#gamma candidates / 0.5 GeV",  "N #gamma's", "#gamma candidates / 0.005", "#gamma candidates / 0.0005", "#gamma candidates / 5 GeV", "#gamma candidates / 0.20", "#gamma candidates / 5 GeV", "#gamma candidates / 0.20", "#gamma candidates / 0.5 GeV/c", "#gamma candidates / 0.5 GeV", "#gamma candidates / 0.5 GeV",  "N #gamma's", "#gamma candidates / 0.005","#gamma candidates / 0.0005", "#gamma candidates / 5 GeV", "#gamma candidates / 0.20", "#gamma candidates / 5 GeV", "#gamma candidates / 0.20", "#gamma candidates / 5 GeV", "#gamma candidates / 0.20"}; 



  std::vector<std::string> Histos; for(int i=0;i<entries; ++i) { Histos.push_back(histarray[i]); }
  std::vector<std::string> Xaxis;  for(int i=0;i<entries; ++i) { Xaxis.push_back(xaxisarray[i]); }
  std::vector<std::string> Yaxis;  for(int i=0;i<entries; ++i) { Yaxis.push_back(yaxisarray[i]); }
  int Rebin = 0;
  for (int ii=0; ii<entries; ++ii) {
    // Debug modus for only 1 plot
    if (ii != 0) continue;
    // 
    if( ii==0 || ii==8 || ii==10 || ii==18 || ii==20 || ii==22 ) Rebin = 1;
    else Rebin = 0;
    std::cout<<"==== i = "<<ii<<" ==== "<<Histos[ii]<<" ==== "<<Xaxis[ii]<<" ==== "<<Yaxis[ii]<<" ==== "<<std::endl;

    std::string SelHisto = Histos[ii];
    std::string xaxis = Xaxis[ii];
    std::string yaxis = Yaxis[ii];

    // ==============================================
    // LUMINOSITY
    // 
    // ==============================================

    // lumi 2010A 
    // double lumi = 3068636.598; // ub^-1
    // lumi 2010A & 2010B
    double lumi = 36140000; // ub^-1
    
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
    
 std::string file_Q1_name = "QCD_HT-100To250_madgraph_Fall10_PreSelectionPlots.root";
 std::string file_Q2_name = "QCD_HT-250To500_madgraph_Fall10_PreSelectionPlots.root";
 std::string file_Q3_name = "QCD_HT-500To1000_madgraph_Fall10_PreSelectionPlots.root";
 std::string file_Q4_name = "QCD_HT-1000_madgraph_Fall10_PreSelectionPlots.root";

 std::string file_P1_name = "GJets_HT-40To100_madgraph_Fall10_PreSelectionPlots.root";
 std::string file_P2_name = "GJets_HT-100To200_madgraph_PreSelectionPlots.root";
 std::string file_P3_name = "GJets_HT-200_madgraph_PreSelectionPlots.root";

 std::string file_E1_name = "WJetsToLNu_madgraph-tauola_Fall10_PreSelectionPlots.root";
 std::string file_E2_name = "DYJetsToLL_madgraph-tauola_Fall10_PreSelectionPlots.root";
 std::string file_E3_name = "TTJets_madgraph-tauola_Fall10_PreSelectionPlots.root";

 std::string file_D_name  = "PhotonPreSelectionPlots.root";
    
    
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
    // DATA std::string xaxisarray[]
    TFile * file_D  = new TFile(file_D_name.c_str(),"READ");
    
    // Read Histograms
    TH1F *Z, *W, *T, *Q1, *Q2, *Q3, *Q4, *E1, *E2, *E3, *P1, *P2, *P3, *D;
    TH1F *Zi, *Wi, *Ti, *Q1i, *Q2i, *Q3i, *Q4i, *E1i, *E2i, *E3i, *P1i, *P2i, *P3i, *Di;
    int Za, Wa, Ta, Q1a, Q2a, Q3a, Q4a, E1a, E2a, E3a, P1a, P2a, P3a, *Da;
    
    // Amount of processed events (MC) :
    // manual, because forget to implement to count all events ...
    Q1a=10022600;
    Q2a=4675070;
    Q3a=7351210;
    Q4a=1713320;
    E1a=14818200;
    E2a=2543740;
    E3a=1394550;
    P1a=2217100;
    P2a=1061600;
    P3a=1142170;
    
    // std::string SelHisto = "PB_Et_B";
    
    Q1 = ((TH1F*) file_Q1->Get((Dir1+"/"+SelHisto).c_str())); Q1->Sumw2();
    Q2 = ((TH1F*) file_Q2->Get((Dir1+"/"+SelHisto).c_str())); Q2->Sumw2();
    Q3 = ((TH1F*) file_Q3->Get((Dir1+"/"+SelHisto).c_str())); Q3->Sumw2();
    Q4 = ((TH1F*) file_Q4->Get((Dir1+"/"+SelHisto).c_str())); Q4->Sumw2();
    E1 = ((TH1F*) file_E1->Get((Dir1+"/"+SelHisto).c_str())); E1->Sumw2();
    E2 = ((TH1F*) file_E2->Get((Dir1+"/"+SelHisto).c_str())); E2->Sumw2();
    E3 = ((TH1F*) file_E3->Get((Dir1+"/"+SelHisto).c_str())); E3->Sumw2();
    P1 = ((TH1F*) file_P1->Get((Dir1+"/"+SelHisto).c_str())); P1->Sumw2();
    P2 = ((TH1F*) file_P2->Get((Dir1+"/"+SelHisto).c_str())); P2->Sumw2();
    P3 = ((TH1F*) file_P3->Get((Dir1+"/"+SelHisto).c_str())); P3->Sumw2();
    
    // Scaling: cross section [pb] x lumi [pb^-1] / number of events before any selection
    Q1->Scale(7e+06  * lumi / Q1a); 
    Q2->Scale(171+03 * lumi / Q2a);
    Q3->Scale(5200   * lumi / Q3a);
    Q4->Scale(83     * lumi / Q1a); 

    E1->Scale(31000  * lumi / E1a);
    E2->Scale( 3100  * lumi / E2a);
    E3->Scale(  165  * lumi / E3a);
    
    P1->Scale(23620  * lumi / P1a);
    P2->Scale( 3476  * lumi / P1a);
    P3->Scale(  485  * lumi / P1a);


    TH1F *Q, *P, *A, *E;
    TH1F *Qq, *Pp, *Aq, *Ee, *Dd;
    THStack *as = new THStack("as","All Merge");
    if(!Rebin) {
      D = ((TH1F*)  file_D->Get((Dir1+"/"+SelHisto).c_str())); D->Sumw2();
      // Final Histograms
      Q = (TH1F*) Q1->Clone("QCD"); int n_Q = Q->GetNbinsX(); for (int i=1; i<=n_Q; ++i) {Q->SetBinContent(i,0.0); Q->SetBinError(i,0,0);}
      P = (TH1F*) P1->Clone("Sig"); int n_P = P->GetNbinsX(); for (int i=1; i<=n_P; ++i) {P->SetBinContent(i,0.0); P->SetBinError(i,0,0);}
      E = (TH1F*) E1->Clone("All"); int n_E = E->GetNbinsX(); for (int i=1; i<=n_E; ++i) {E->SetBinContent(i,0.0); E->SetBinError(i,0,0);}
      A = (TH1F*) Q1->Clone("All"); int n_A = A->GetNbinsX(); for (int i=1; i<=n_A; ++i) {A->SetBinContent(i,0.0); A->SetBinError(i,0,0);}
      // Add
      Q->Add(Q1); Q->Add(Q2); Q->Add(Q3); Q->Add(Q4); 
      P->Add(P1); P->Add(P2); P->Add(P3); 
      E->Add(E1); E->Add(E2); E->Add(E3);
    }
    else {
      Dd = ((TH1F*)  file_D->Get((Dir1+"/"+SelHisto).c_str())); Dd->Sumw2();

      Qq = (TH1F*) Q1->Clone("QCD"); int n_Q = Qq->GetNbinsX(); for (int i=1; i<=n_Q; ++i) {Qq->SetBinContent(i,0.0); Qq->SetBinError(i,0,0);}
      Pp = (TH1F*) P1->Clone("Sig"); int n_P = Pp->GetNbinsX(); for (int i=1; i<=n_P; ++i) {Pp->SetBinContent(i,0.0); Pp->SetBinError(i,0,0);}
      Ee = (TH1F*) E1->Clone("All"); int n_E = Ee->GetNbinsX(); for (int i=1; i<=n_E; ++i) {Ee->SetBinContent(i,0.0); Ee->SetBinError(i,0,0);}
      Aa = (TH1F*) Q1->Clone("All"); int n_A = Aa->GetNbinsX(); for (int i=1; i<=n_A; ++i) {Aa->SetBinContent(i,0.0); Aa->SetBinError(i,0,0);}

      Qq->Add(Q1); Qq->Add(Q2); Qq->Add(Q3); Qq->Add(Q4); 
      Pp->Add(P1); Pp->Add(P2); Pp->Add(P3); 
      Ee->Add(E1); Ee->Add(E2); Ee->Add(E3);
      Aa->Add(Ee); Aa->Add(Qq); Aa->Add(Pp);

      double ptbinning [] = {0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0, 90.0, 95.0, 100.0, 105.0, 110.0, 115.0, 120.0, 125.0, 130.0, 135.0, 140.0, 145.0, 150.0, 165.0, 180.0, 195.0, 210.0, 225.0, 240.0, 255.0, 270.0, 285.0, 300.0, 350.0, 400.0, 450.0, 500.0};
      P = new TH1F("P", "P", 44, ptbinning); P->Sumw2();
      Q = new TH1F("Q", "Q", 44, ptbinning); Q->Sumw2();
      E = new TH1F("E", "E", 44, ptbinning); E->Sumw2();
      D = new TH1F("D", "D", 44, ptbinning); D->Sumw2();
      A = new TH1F("A", "A", 44, ptbinning); A->Sumw2();
      int bins = P->GetNbinsX();
      double binwidth = 500.0/bins;
      double photons = 0.0, zbosons = 0.0;
      for(int iii=1; iii<=bins; ++iii) {
        double bin_lvalue = (0.0 + (iii-1)*binwidth);
        double bin_rvalue = (0.0 + (iii)*binwidth);
        for(int jj=1; jj<45; ++jj) {
          if (bin_lvalue >=  ptbinning[jj-1] && bin_rvalue <= ptbinning[jj]) {
            P->AddBinContent(jj,Pp->GetBinContent(iii));
            Q->AddBinContent(jj,Qq->GetBinContent(iii));
            E->AddBinContent(jj,Ee->GetBinContent(iii));
            D->AddBinContent(jj,Dd->GetBinContent(iii));
            A->AddBinContent(jj,Aa->GetBinContent(iii));
            P->SetBinError(jj,sqrt(pow(P->GetBinError(jj),2)+pow(Pp->GetBinError(iii),2)));
            Q->SetBinError(jj,sqrt(pow(Q->GetBinError(jj),2)+pow(Qq->GetBinError(iii),2)));
            E->SetBinError(jj,sqrt(pow(E->GetBinError(jj),2)+pow(Ee->GetBinError(iii),2)));
            D->SetBinError(jj,sqrt(pow(D->GetBinError(jj),2)+pow(Dd->GetBinError(iii),2)));
            A->SetBinError(jj,sqrt(pow(A->GetBinError(jj),2)+pow(Aa->GetBinError(iii),2)));
          }
	}
      }
      for(int j=31; j<41; ++j) {
        P->SetBinContent(j, P->GetBinContent(j)/3); P->SetBinError(j, P->GetBinError(j)/3);
        Q->SetBinContent(j, Q->GetBinContent(j)/3); Q->SetBinError(j, Q->GetBinError(j)/3);
        E->SetBinContent(j, E->GetBinContent(j)/3); E->SetBinError(j, E->GetBinError(j)/3);
        D->SetBinContent(j, D->GetBinContent(j)/3); D->SetBinError(j, D->GetBinError(j)/3);
        A->SetBinContent(j, A->GetBinContent(j)/3); A->SetBinError(j, A->GetBinError(j)/3);
      }
      for(int j=41; j<45; ++j) {
        P->SetBinContent(j, P->GetBinContent(j)/10); P->SetBinError(j, P->GetBinError(j)/10);
        Q->SetBinContent(j, Q->GetBinContent(j)/10); Q->SetBinError(j, Q->GetBinError(j)/10);
        E->SetBinContent(j, E->GetBinContent(j)/10); E->SetBinError(j, E->GetBinError(j)/10);
        D->SetBinContent(j, D->GetBinContent(j)/10); D->SetBinError(j, D->GetBinError(j)/10);
        A->SetBinContent(j, A->GetBinContent(j)/10); A->SetBinError(j, A->GetBinError(j)/10);
      }
    }

    E->SetFillColor(kYellow); as->Add(E);
    Q->SetFillColor(kGreen);  as->Add(Q);
    P->SetFillColor(kRed);    as->Add(P);
    A->Add(E); A->Add(Q); A->Add(P);

    // All MC + DATA
    TCanvas * c1 = new TCanvas("c","canvas",800,600);
    c1->cd();
    c1->SetLogy(1);
    A->GetYaxis()->SetRangeUser(3e-4,1e8);
    D->SetMarkerStyle(20); D->SetMarkerColor(kBlack); D->SetLineColor(kBlack); D->SetMarkerSize(0.75);
    A->GetYaxis()->SetTitle(yaxis.c_str());
    A->GetYaxis()->SetLabelSize(0.025);
    A->GetXaxis()->SetLabelSize(0.0000025);
    A->GetXaxis()->SetTicks("+-");
    A->Draw("HIST");
    as->Draw("HISTsame");
    D->Draw("sameEP");
    gPad->RedrawAxis();
    gStyle->SetGridStyle(3);
    // Coordinates for TLegend: x1, y1, x2, y2
    TLegend *l1 = new TLegend(0.60,0.75,0.85,0.85,NULL,"brNDC");
    l1->SetLineColor(0);
    l1->SetLineStyle(0);
    l1->SetLineWidth(0);
    l1->SetFillColor(4000);
    l1->SetBorderSize(0);
    l1->AddEntry(D, "Data","lp");
    l1->AddEntry(P, "Photon: prompt","f");
    l1->AddEntry(Q, "QCD: prompt, frag & decay","f");
    l1->AddEntry(E, "EWK: W,Z,t#bar{t}","f");
    l1->Draw();
    cmsPrelim(lumi, 0);
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
    ratio->SetMaximum(1.0);   
    ratio->GetYaxis()->SetNdivisions(503); // N1 + 100 * N2 (small ticks and big ticks) defines the grid
    ratio->GetYaxis()->SetLabelSize(0.025);
    ratio->GetYaxis()->SetTitle("Data / MC");
    ratio->GetXaxis()->SetTicks("+");
    ratio->GetXaxis()->SetTitle(xaxis.c_str());
    ratio->GetXaxis()->SetLabelSize(0.025);
    ratio->Draw("pe");
    savePlot(c1, SelHisto.c_str());
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
