#include "TCanvas.h"
#include "TStyle.h"
#include "TFile.h"
#include "TH1F.h"
#include "TLegend.h"

void PhotonPreSelectionPlotOnlyData() {

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
    // if (ii != 0) continue;
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
    gStyle->SetGridStyle(1);
    gROOT->UseCurrentStyle();
   
    std::string file_D_name  = "PhotonPreSelectionPlots.root";
    TFile * file_D  = new TFile(file_D_name.c_str(),"READ");
    TH1F *D, *D1;
    if(!Rebin) {
      D = ((TH1F*)  file_D->Get((Dir1+"/"+SelHisto).c_str())); D->Sumw2();
    }
    else {
      D1 = ((TH1F*)  file_D->Get((Dir1+"/"+SelHisto).c_str())); D1->Sumw2();
      double ptbinning [] = {0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0, 90.0, 95.0, 100.0, 105.0, 110.0, 115.0, 120.0, 125.0, 130.0, 135.0, 140.0, 145.0, 150.0, 165.0, 180.0, 195.0, 210.0, 225.0, 240.0, 255.0, 270.0, 285.0, 300.0, 350.0, 400.0, 450.0, 500.0};
      D = new TH1F("D", "D", 44, ptbinning); D->Sumw2();
      int bins = D1->GetNbinsX();
      double binwidth = 500.0/bins;
      double photons = 0.0, zbosons = 0.0;
      for(int iii=1; iii<=bins; ++iii) {
        double bin_lvalue = (0.0 + (iii-1)*binwidth);
        double bin_rvalue = (0.0 + (iii)*binwidth);
        for(int jj=1; jj<45; ++jj) {
          if (bin_lvalue >=  ptbinning[jj-1] && bin_rvalue <= ptbinning[jj]) {
	    D->AddBinContent(jj,D1->GetBinContent(iii));
            D->SetBinError(jj,sqrt(pow(D->GetBinError(jj),2)+pow(D1->GetBinError(iii),2)));
          }
	}
      }
      for(int j=31; j<41; ++j) {
        D->SetBinContent(j, D->GetBinContent(j)/3); D->SetBinError(j, D->GetBinError(j)/3);
      }
      for(int j=41; j<45; ++j) {
        D->SetBinContent(j, D->GetBinContent(j)/10); D->SetBinError(j, D->GetBinError(j)/10);
      }
    }
    // All MC + DATA
    TCanvas * c1 = new TCanvas("c","canvas",800,600);
    c1->cd();
    c1->SetLogy(1);
    D->GetYaxis()->SetRangeUser(3e-4,1e8);
    D->SetMarkerStyle(20); D->SetMarkerColor(kBlack); D->SetLineColor(kBlack); D->SetMarkerSize(0.75);
    D->GetYaxis()->SetTitle(yaxis.c_str());
    D->GetYaxis()->SetLabelSize(0.025);
    D->GetXaxis()->SetTitle(xaxis.c_str());
    D->GetXaxis()->SetLabelSize(0.025);
    D->Draw("EPH");
    gPad->RedrawAxis();
    gStyle->SetGridStyle(3);
    // Coordinates for TLegend: x1, y1, x2, y2
    /*
    TLegend *l1 = new TLegend(0.60,0.75,0.85,0.85,NULL,"brNDC");
    l1->SetLineColor(0);
    l1->SetLineStyle(0);
    l1->SetLineWidth(0);
    l1->SetFillColor(4000);
    l1->SetBorderSize(0);
    l1->AddEntry(D, "Data","lp");
    l1->Draw();
    */
    cmsPrelim(lumi, 0);
    c1->SetLogy(1);
    c1->SetGridx();
    c1->SetGridy();
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
