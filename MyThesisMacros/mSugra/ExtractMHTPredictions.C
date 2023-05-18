#include "TFile.h"
#include "TH1F.h"
#include "math.h"

void ExtractMHTPredictions() {
  // input
  std::string file_D_name  = "Photon.root";
  TFile * file_D  = new TFile(file_D_name.c_str(),"READ");
  //output
  TFile * outputfile = new TFile("PhotonMHTPrediction.root","RECREATE");


  TH1F * D1 = ((TH1F*)  file_D->Get("RA2SEL/4_MHT_AMC"));
  TH1F * D2 = ((TH1F*)  file_D->Get("RA2SEL/6_MHT_HHS"));
  TH1F * D3 = ((TH1F*)  file_D->Get("RA2SEL/7_MHT_HMS"));

  double corr_base = 0.373; double syst_base = 0.23;
  double corr_hht  = 0.414; double syst_hht  = 0.26;
  double corr_mht  = 0.448; double syst_mht  = 0.25;

  D1->Scale(corr_base);
  D2->Scale(corr_hht);
  D3->Scale(corr_mht);

  for(int i=1; i<=D1->GetNbinsX(); ++i) { D1->SetBinError(i,sqrt(pow(D1->GetBinError(i),2) + pow(D1->GetBinContent(i)*syst_base,2))); }
  for(int i=1; i<=D2->GetNbinsX(); ++i) { D2->SetBinError(i,sqrt(pow(D2->GetBinError(i),2) + pow(D2->GetBinContent(i)*syst_hht,2))); }
  for(int i=1; i<=D3->GetNbinsX(); ++i) { D3->SetBinError(i,sqrt(pow(D3->GetBinError(i),2) + pow(D3->GetBinContent(i)*syst_mht,2))); }


  outputfile->cd();
  D1->Write();
  D2->Write();
  D3->Write();


}
