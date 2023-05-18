#include "TFile.h"
#include "TH1F.h"
#include "math.h"

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>


void ExtractSignalContamination() {
  // input

  // ==========
  // ROOT Files 
  // ==========

  int entries = 8;
  double lumi = 36.14; // pb inv
  std::vector<std::string> FileInfo;
  std::vector<std::string> FileName;

  // tan(beta) = 10 (Christian Auterman)
  // -----------------------------------
  FileInfo.push_back("tan(b) = 10 | m0 = 200 | m1/2 = 280 | reco_703_2_do2.root");
  FileName.push_back("Photon_autermann_reco_703_2_do2.root");
  FileInfo.push_back("tan(b) = 10 | m0 = 200 | m1/2 = 290 | reco_704_2_9cc.root");
  FileName.push_back("Photon_autermann_reco_704_2_9cc.root");
  FileInfo.push_back("tan(b) = 10 | m0 = 500 | m1/2 = 170 | reco_1772_1_IhJ.root");
  FileName.push_back("Photon_autermann_reco_1772_1_IhJ.root");
  FileInfo.push_back("tan(b) = 10 | m0 = 800 | m1/2 = 230 | reco_2858_1_aHC.root");
  FileName.push_back("Photon_autermann_reco_2858_1_aHC.root");

  // tan(beta) = 3 (Jim Lungu)
  // -------------------------
  FileInfo.push_back("tan(b) = 3 | m0 = 200 | m1/2 = 280 | reco_513_1_lpU.root");
  FileName.push_back("Photon_lungu_reco_513_1_lpU.root");
  FileInfo.push_back("tan(b) = 3 | m0 = 200 | m1/2 = 290 | reco_514_1_wwr.root");
  FileName.push_back("Photon_lungu_reco_514_1_wwr.root");
  FileInfo.push_back("tan(b) = 3 | m0 = 400 | m1/2 = 300 | reco_1035_2_8gy.root");
  FileName.push_back("Photon_lungu_reco_1035_2_8gy.root");
  FileInfo.push_back("tan(b) = 3 | m0 = 400 | m1/2 = 310 | reco_1036_2_CQL.root");
  FileName.push_back("Photon_lungu_reco_1036_2_CQL.root");
 
  std::vector< TFile* > RootFile;
  for(int i=0; i<entries; ++i) {
    RootFile.push_back(new TFile(FileName[i].c_str(),"READ"));
  }
  std::vector< TH1F* > HistFile;
  for(int i=0; i<entries; ++i) {
    HistFile.push_back(((TH1F*)  (RootFile[i])->Get("RA2SelectionHisto")));
  }

  std::vector<int> Entries;
  std::vector<int> Baseline;
  std::vector<int> HighHT;
  std::vector<int> HighMHT;
  for(int i=0; i<entries; ++i) {
    Entries.push_back((HistFile[i])->GetBinContent(1));
    Baseline.push_back((HistFile[i])->GetBinContent(6));
    HighHT.push_back((HistFile[i])->GetBinContent(8));
    HighMHT.push_back((HistFile[i])->GetBinContent(9));
  }
  std::vector<double> Xsection;
  std::vector<double> Scaling;
  Xsection.push_back(1.952); Xsection.push_back(1.611); Xsection.push_back(10.38); Xsection.push_back(1.572);
  Xsection.push_back(1.973); Xsection.push_back(1.633); Xsection.push_back(0.855); Xsection.push_back(0.736);

  for(int i=0; i<entries; ++i) {
    Scaling.push_back(Xsection[i]*lumi/Entries[i]);
  }
  std::vector<double> BaselineSc;
  std::vector<double> HighHTSc;
  std::vector<double> HighMHTSc;
  for(int i=0; i<entries; ++i) {
    BaselineSc.push_back(((HistFile[i])->GetBinContent(6))*Scaling[i]);
    HighHTSc.push_back(((HistFile[i])->GetBinContent(8))*Scaling[i]);
    HighMHTSc.push_back(((HistFile[i])->GetBinContent(9))*Scaling[i]);
  }
  // All events
  for(int i=0; i<entries; ++i) {
    std::cout<<std::setw(60)<<FileInfo[i]<<" | Processed Evts: "<<std::setw(6)<<Entries[i]<<" | Baseline SEL: "<<std::setw(3)<<Baseline[i];
    std::cout<<" | High HT: "<<std::setw(3)<<HighHT[i]<<" | High MHT: "<<std::setw(3)<<HighMHT[i]<<std::endl;
  }
  std::cout<<" "<<std::endl;
  // Scaled events
  for(int i=0; i<entries; ++i) {
    std::cout<<std::setw(60)<<FileInfo[i]<<" | Baseline SEL: "<<std::setw(3)<<BaselineSc[i];
    std::cout<<" | High HT: "<<std::setw(3)<<HighHTSc[i]<<" | High MHT: "<<std::setw(3)<<HighMHTSc[i]<<std::endl;
  }

  // ===========
  // Corrections
  // =========== 

  double corr_base = 0.373; double syst_base = 0.23;
  double corr_hht  = 0.414; double syst_hht  = 0.26;
  double corr_mht  = 0.448; double syst_mht  = 0.25;
  /*
  D1->Scale(corr_base);
  D2->Scale(corr_hht);
  D3->Scale(corr_mht);

  for(int i=1; i<=D1->GetNbinsX(); ++i) { D1->SetBinError(i,sqrt(pow(D1->GetBinError(i),2) + pow(D1->GetBinContent(i)*syst_base,2))); }
  for(int i=1; i<=D2->GetNbinsX(); ++i) { D2->SetBinError(i,sqrt(pow(D2->GetBinError(i),2) + pow(D2->GetBinContent(i)*syst_hht,2))); }
  for(int i=1; i<=D3->GetNbinsX(); ++i) { D3->SetBinError(i,sqrt(pow(D3->GetBinError(i),2) + pow(D3->GetBinContent(i)*syst_mht,2))); }
  */
}
