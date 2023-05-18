#include <stdio.h>
#include <iostream>
#include <math.h>
#include <TFile.h>
#include <TH1F.h>
#include <vector>
#include <iomanip>

void EventSelectionTable() {

  int rootfiles = 12;
  // AN-10-268 ID
  std::string RootFileNames[] = {"QCD_HT-100To250_madgraph_Fall10.root", "QCD_HT-250To500_madgraph_Fall10.root", "QCD_HT-500To1000_madgraph_Fall10.root", "QCD_HT-1000_madgraph_Fall10.root", "WJetsToLNu_madgraph-tauola_Fall10.root", "DYJetsToLL_madgraph-tauola_Fall10.root", "TTJets_madgraph-tauola_Fall10.root", "GJets_HT-40To100_madgraph_Fall10.root", "GJets_HT-100To200_madgraph_Fall10.root", "GJets_HT-200_madgraph_Fall10.root", "ZinvisibleJets_7TeV-madgraph_Fall10.root", "Photon.root"};
  // EGM ID
  // std::string RootFileNames[] = {"QCD_HT-100To250_madgraph_Fall10_EGM.root", "QCD_HT-250To500_madgraph_Fall10_EGM.root", "QCD_HT-500To1000_madgraph_Fall10_EGM.root", "QCD_HT-1000_madgraph_Fall10_EGM.root", "WJetsToLNu_madgraph-tauola_Fall10_EGM.root", "DYJetsToLL_madgraph-tauola_Fall10_EGM.root", "TTJets_madgraph-tauola_Fall10_EGM.root", "GJets_HT-40To100_madgraph_Fall10_EGM.root", "GJets_HT-100To200_madgraph_Fall10_EGM.root", "GJets_HT-200_madgraph_Fall10_EGM.root", "ZinvisibleJets_7TeV-madgraph_Fall10_100GeV.root", "Photon_EGM.root"};

  std::vector< TFile* > RootTFiles;    for(int i=0; i<rootfiles; ++i) { RootTFiles.push_back(new TFile(RootFileNames[i].c_str(),"READ")); }
  std::vector< TH1F* >  EventCounters; for(int i=0; i<rootfiles; ++i) { EventCounters.push_back((TH1F*) RootTFiles[i]->Get("EventCounters"));    EventCounters[i]->Sumw2(); }
  std::vector< TH1F* >  RA2Selection;  for(int i=0; i<rootfiles; ++i) { RA2Selection.push_back((TH1F*) RootTFiles[i]->Get("RA2SelectionHisto")); RA2Selection[i]->Sumw2();  }
  
  std::vector< TH1F* >  Book_All;        for(int i=0; i<rootfiles; ++i) { Book_All.push_back((TH1F*) RootTFiles[i]->Get("RA2SEL/0_Book_All")); Book_All[i]->Sumw2(); }
  std::vector< TH1F* >  Book_AJC;        for(int i=0; i<rootfiles; ++i) { Book_AJC.push_back((TH1F*) RootTFiles[i]->Get("RA2SEL/1_Book_AJC")); Book_AJC[i]->Sumw2(); }
  std::vector< TH1F* >  Book_AHC;        for(int i=0; i<rootfiles; ++i) { Book_AHC.push_back((TH1F*) RootTFiles[i]->Get("RA2SEL/2_Book_AHC")); Book_AHC[i]->Sumw2(); }
  std::vector< TH1F* >  Book_AAC;        for(int i=0; i<rootfiles; ++i) { Book_AAC.push_back((TH1F*) RootTFiles[i]->Get("RA2SEL/3_Book_AAC")); Book_AAC[i]->Sumw2(); }
  std::vector< TH1F* >  Book_AMC;        for(int i=0; i<rootfiles; ++i) { Book_AMC.push_back((TH1F*) RootTFiles[i]->Get("RA2SEL/4_Book_AMC")); Book_AMC[i]->Sumw2(); }
  std::vector< TH1F* >  Book_HHS;        for(int i=0; i<rootfiles; ++i) { Book_HHS.push_back((TH1F*) RootTFiles[i]->Get("RA2SEL/6_Book_HHS")); Book_HHS[i]->Sumw2(); }
  std::vector< TH1F* >  Book_HMS;        for(int i=0; i<rootfiles; ++i) { Book_HMS.push_back((TH1F*) RootTFiles[i]->Get("RA2SEL/7_Book_HMS")); Book_HMS[i]->Sumw2(); }

  std::vector< std::vector< TH1F* > > Book;
  Book.push_back(Book_All); Book.push_back(Book_AJC); Book.push_back(Book_AHC); Book.push_back(Book_AAC); Book.push_back(Book_AMC); Book.push_back(Book_HHS); Book.push_back(Book_HMS);

  std::vector< int >    Events; for(int i=0; i<rootfiles; ++i) { Events.push_back(EventCounters[i]->GetBinContent(1)); }   
  std::vector< double > CrossSections; 
  // QCD cross sections
  CrossSections.push_back(7000000.00); CrossSections.push_back(171000.00); CrossSections.push_back(5200.00); CrossSections.push_back(83.00);
  // EWL cross sections: W , DY, ttbar
  CrossSections.push_back(31300.00); CrossSections.push_back(3100.00); CrossSections.push_back(165.00); // NNLO (24380, 2289, 95 @ LO)
  // Photon cross sections
  CrossSections.push_back(23620.00); CrossSections.push_back(3476.00); CrossSections.push_back(485.00);
  // Zinv cross section
  CrossSections.push_back(4500); //LO (5760@NLO)
  // DATA
  double lumi = 36.14;
  std::vector<double> Scaling;
  for(int i=0; i<CrossSections.size(); ++i) {Scaling.push_back(CrossSections[i]*lumi/Events[i]);}
  for(int i=0; i<CrossSections.size(); ++i) {EventCounters[i]->Scale(Scaling[i]); RA2Selection[i]->Scale(Scaling[i]);}
  for(int i=0; i<CrossSections.size(); ++i) {
    std::cout<<std::setw(40)<<RootFileNames[i]<<" : x-section = "<<std::setw(9)<<CrossSections[i]<<" | lumi = "<<lumi<<" | events = "<<std::setw(9)<<Events[i];
    std::cout<<" | scaling = "<<std::setw(12)<<Scaling[i]<<" | 2 Jet Events = "<<std::setw(9)<<EventCounters[i]->GetBinContent(9);
    std::cout<<" | 3 Jet Events = "<<std::setw(9)<<EventCounters[i]->GetBinContent(10)<<" | Baseline Events = "<<std::setw(9)<<EventCounters[i]->GetBinContent(11)<<std::endl; 
  }

  std::cout<<" "<<std::endl;
  std::cout<<" "<<std::endl;

  for(int i=0; i<CrossSections.size(); ++i) {Book_All[i]->Scale(Scaling[i]); Book_AJC[i]->Scale(Scaling[i]); Book_AHC[i]->Scale(Scaling[i]); Book_AAC[i]->Scale(Scaling[i]); Book_AMC[i]->Scale(Scaling[i]); Book_HHS[i]->Scale(Scaling[i]); Book_HMS[i]->Scale(Scaling[i]);}


  // Let ROOT do the Error Calculation: 5 samples: QCD, EWK, PH, Zinv, DATA
  std::vector<TH1F*> Sample_EC, Sample_RA2;
  for(int i=0; i<5; ++i) {
    Sample_EC.push_back( (TH1F*) EventCounters[0]->Clone("Sample_EC")); 
    int n1 = Sample_EC[i]->GetNbinsX();  for (int j=1; j<=n1; ++j) {Sample_EC[i]->SetBinContent(j,0.0); Sample_EC[i]->SetBinError(j,0.0);} // Sample_EC[i]->Sumw2();
    Sample_RA2.push_back((TH1F*) RA2Selection[0]->Clone("Sample_RA2")); 
    int n2 = Sample_RA2[i]->GetNbinsX(); for (int j=1; j<=n2; ++j) {Sample_RA2[i]->SetBinContent(j,0.0); Sample_RA2[i]->SetBinError(j,0.0);} // Sample_RA2[i]->Sumw2();
  }


  // QCD
  Sample_EC[0]->Add(EventCounters[0]); Sample_EC[0]->Add(EventCounters[1]);    
  Sample_EC[0]->Add(EventCounters[2]); Sample_EC[0]->Add(EventCounters[3]); 
  Sample_RA2[0]->Add(RA2Selection[0]); Sample_RA2[0]->Add(RA2Selection[1]);
  Sample_RA2[0]->Add(RA2Selection[2]); Sample_RA2[0]->Add(RA2Selection[3]);
  // EWK
  Sample_EC[1]->Add(EventCounters[4]); Sample_EC[1]->Add(EventCounters[5]); Sample_EC[1]->Add(EventCounters[6]);
  Sample_RA2[1]->Add(RA2Selection[4]); Sample_RA2[1]->Add(RA2Selection[5]); Sample_RA2[1]->Add(RA2Selection[6]);
  // PH    
  Sample_EC[2]->Add(EventCounters[7]); Sample_EC[2]->Add(EventCounters[8]); Sample_EC[2]->Add(EventCounters[9]);
  Sample_RA2[2]->Add(RA2Selection[7]); Sample_RA2[2]->Add(RA2Selection[8]); Sample_RA2[2]->Add(RA2Selection[9]);
  // Zinv
  Sample_EC[3]->Add(EventCounters[10]);
  Sample_RA2[3]->Add(RA2Selection[10]);
  // DATA
  Sample_EC[4]->Add(EventCounters[11]);
  Sample_RA2[4]->Add(RA2Selection[11]);

  std::vector<double> DEv, DEr, ZEv, ZEr, PEv, PEr, QEv, QEr, EEv, EEr;

  // EventCounters has 11 bins:
  for(int i=1; i<12; ++i) {
    DEv.push_back(Sample_EC[4]->GetBinContent(i)); DEr.push_back(Sample_EC[4]->GetBinError(i));
    ZEv.push_back(Sample_EC[3]->GetBinContent(i)); ZEr.push_back(Sample_EC[3]->GetBinError(i)); 
    PEv.push_back(Sample_EC[2]->GetBinContent(i)); PEr.push_back(Sample_EC[2]->GetBinError(i));
    EEv.push_back(Sample_EC[1]->GetBinContent(i)); EEr.push_back(Sample_EC[1]->GetBinError(i));
    QEv.push_back(Sample_EC[0]->GetBinContent(i)); QEr.push_back(Sample_EC[0]->GetBinError(i));
  }
  // RA2Selection has 9 bins:
  for(int i=1; i<10; ++i) {
    DEv.push_back(Sample_RA2[4]->GetBinContent(i)); DEr.push_back(Sample_RA2[4]->GetBinError(i));
    ZEv.push_back(Sample_RA2[3]->GetBinContent(i)); ZEr.push_back(Sample_RA2[3]->GetBinError(i));
    PEv.push_back(Sample_RA2[2]->GetBinContent(i)); PEr.push_back(Sample_RA2[2]->GetBinError(i));
    EEv.push_back(Sample_RA2[1]->GetBinContent(i)); EEr.push_back(Sample_RA2[1]->GetBinError(i));
    QEv.push_back(Sample_RA2[0]->GetBinContent(i)); QEr.push_back(Sample_RA2[0]->GetBinError(i));
  }
 

  std::cout<<std::setw(20)<<"TABLE HEADER: "<<std::setw(18)<<" DATA "<<std::setw(26)<<"PHOTON "<<std::setw(26)<<" QCD "<<std::setw(26)<<" EWK "<<std::setw(26)<<" Zinv "<<std::endl;
  std::cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------------"<<std::endl;
  std::cout<<std::setw(20)<<"Amount of Events: "<<"| "<<std::setw(12)<<DEv[0]<<"pm"<<std::setw(12)<<DEr[0]<<"| "<<std::setw(12)<<PEv[0]<<"pm"<<std::setw(12)<<PEr[0];
  std::cout<<"| "<<std::setw(12)<<QEv[0]<<"pm"<<std::setw(12)<<QEr[0]<<"| "<<std::setw(12)<<EEv[0]<<"pm"<<std::setw(12)<<EEr[0]<<std::setw(12)<<ZEv[0]<<"pm"<<std::setw(12)<<ZEr[0]<<std::endl;

  std::cout<<std::setw(20)<<"After HLT Trigger: "<<"| "<<std::setw(12)<<DEv[1]<<"pm"<<std::setw(12)<<DEr[1]<<"| "<<std::setw(12)<<PEv[1]<<"pm"<<std::setw(12)<<PEr[1];
  std::cout<<"| "<<std::setw(12)<<QEv[1]<<"pm"<<std::setw(12)<<QEr[1]<<"| "<<std::setw(12)<<EEv[1]<<"pm"<<std::setw(12)<<EEr[1]<<std::setw(12)<<ZEv[1]<<"pm"<<std::setw(12)<<ZEr[1]<<std::endl;
  // Do not implement "after cleaning" since lepton veto was not carried out here
  std::cout<<std::setw(20)<<"Boson + 2 Jets: "<<"| "<<std::setw(12)<<DEv[7]<<"pm"<<std::setw(12)<<DEr[7]<<"| "<<std::setw(12)<<PEv[7]<<"pm"<<std::setw(12)<<PEr[7];
  std::cout<<"| "<<std::setw(12)<<QEv[7]<<"pm"<<std::setw(12)<<QEr[7]<<"| "<<std::setw(12)<<EEv[7]<<"pm"<<std::setw(12)<<EEr[7]<<std::setw(12)<<ZEv[7]<<"pm"<<std::setw(12)<<ZEr[7]<<std::endl;

  std::cout<<std::setw(20)<<"Boson + 3 Jets: "<<"| "<<std::setw(12)<<DEv[9]<<"pm"<<std::setw(12)<<DEr[9]<<"| "<<std::setw(12)<<PEv[9]<<"pm"<<std::setw(12)<<PEr[9];
  std::cout<<"| "<<std::setw(12)<<QEv[9]<<"pm"<<std::setw(12)<<QEr[9]<<"| "<<std::setw(12)<<EEv[9]<<"pm"<<std::setw(12)<<EEr[9]<<std::setw(12)<<ZEv[9]<<"pm"<<std::setw(12)<<ZEr[9]<<std::endl;
  // Check
  // std::cout<<std::setw(20)<<"Baseline Selection: "<<"| "<<std::setw(12)<<DEv[10]<<"pm"<<std::setw(12)<<DEr[10]<<"| "<<std::setw(12)<<PEv[10]<<"pm"<<std::setw(12)<<PEr[10];
  // std::cout<<"| "<<std::setw(12)<<QEv[10]<<"pm"<<std::setw(12)<<QEr[10]<<"| "<<std::setw(12)<<EEv[10]<<"pm"<<std::setw(12)<<EEr[10]<<std::endl;
  // Check
  // std::cout<<std::setw(20)<<"Boson + 3 Jets: "<<"| "<<std::setw(12)<<DEv[13]<<"pm"<<std::setw(12)<<DEr[13]<<"| "<<std::setw(12)<<PEv[13]<<"pm"<<std::setw(12)<<PEr[13];
  // std::cout<<"| "<<std::setw(12)<<QEv[13]<<"pm"<<std::setw(12)<<QEr[13]<<"| "<<std::setw(12)<<EEv[13]<<"pm"<<std::setw(12)<<EEr[13]<<std::endl;

  std::cout<<std::setw(20)<<"HT > 300: "<<"| "<<std::setw(12)<<DEv[14]<<"pm"<<std::setw(12)<<DEr[14]<<"| "<<std::setw(12)<<PEv[14]<<"pm"<<std::setw(12)<<PEr[14];
  std::cout<<"| "<<std::setw(12)<<QEv[14]<<"pm"<<std::setw(12)<<QEr[14]<<"| "<<std::setw(12)<<EEv[14]<<"pm"<<std::setw(12)<<EEr[14]<<std::setw(12)<<ZEv[14]<<"pm"<<std::setw(12)<<ZEr[14]<<std::endl;

  std::cout<<std::setw(20)<<"QCD Angular Cuts: "<<"| "<<std::setw(12)<<DEv[15]<<"pm"<<std::setw(12)<<DEr[15]<<"| "<<std::setw(12)<<PEv[15]<<"pm"<<std::setw(12)<<PEr[15];
  std::cout<<"| "<<std::setw(12)<<QEv[15]<<"pm"<<std::setw(12)<<QEr[15]<<"| "<<std::setw(12)<<EEv[15]<<"pm"<<std::setw(12)<<EEr[15]<<std::setw(12)<<ZEv[15]<<"pm"<<std::setw(12)<<ZEr[15]<<std::endl;

  std::cout<<std::setw(20)<<"Baseline Selection: "<<"| "<<std::setw(12)<<DEv[16]<<"pm"<<std::setw(12)<<DEr[16]<<"| "<<std::setw(12)<<PEv[16]<<"pm"<<std::setw(12)<<PEr[16];
  std::cout<<"| "<<std::setw(12)<<QEv[16]<<"pm"<<std::setw(12)<<QEr[16]<<"| "<<std::setw(12)<<EEv[16]<<"pm"<<std::setw(12)<<EEr[16]<<std::setw(12)<<ZEv[16]<<"pm"<<std::setw(12)<<ZEr[16]<<std::endl;

  std::cout<<std::setw(20)<<"High HT Selection: "<<"| "<<std::setw(12)<<DEv[18]<<"pm"<<std::setw(12)<<DEr[18]<<"| "<<std::setw(12)<<PEv[18]<<"pm"<<std::setw(12)<<PEr[18];
  std::cout<<"| "<<std::setw(12)<<QEv[18]<<"pm"<<std::setw(12)<<QEr[18]<<"| "<<std::setw(12)<<EEv[18]<<"pm"<<std::setw(12)<<EEr[18]<<std::setw(12)<<ZEv[18]<<"pm"<<std::setw(12)<<ZEr[18]<<std::endl;

  std::cout<<std::setw(20)<<"High MHT Selection: "<<"| "<<std::setw(12)<<DEv[19]<<"pm"<<std::setw(12)<<DEr[19]<<"| "<<std::setw(12)<<PEv[19]<<"pm"<<std::setw(12)<<PEr[19];
  std::cout<<"| "<<std::setw(12)<<QEv[19]<<"pm"<<std::setw(12)<<QEr[19]<<"| "<<std::setw(12)<<EEv[19]<<"pm"<<std::setw(12)<<EEr[19]<<std::setw(12)<<ZEv[19]<<"pm"<<std::setw(12)<<ZEr[19]<<std::endl;

  std::cout<<" "<<std::endl;
  std::cout<<" "<<std::endl;


  // For the origin in the different cuts of the selection: merge the "Book Files"
  std::vector<TH1F*> Origin_MC, Origin_ZB, Origin_DA;
  for(int i=0; i<7; ++i) {
    Origin_MC.push_back((TH1F*) Book_All[0]->Clone("Origin_MC")); 
    int n1 = Origin_MC[i]->GetNbinsX();  for (int j=1; j<=n1; ++j) {Origin_MC[i]->SetBinContent(j,0.0); Origin_MC[i]->SetBinError(j,0.0);} // Origin_MC[i]->Sumw2();
    Origin_ZB.push_back((TH1F*) Book_All[0]->Clone("Origin_ZB")); 
    int n2 = Origin_ZB[i]->GetNbinsX();  for (int j=1; j<=n2; ++j) {Origin_ZB[i]->SetBinContent(j,0.0); Origin_ZB[i]->SetBinError(j,0.0);} // Origin_ZB[i]->Sumw2();
    Origin_DA.push_back((TH1F*) Book_All[0]->Clone("Origin_DA")); 
    int n3 = Origin_DA[i]->GetNbinsX();  for (int j=1; j<=n3; ++j) {Origin_DA[i]->SetBinContent(j,0.0); Origin_DA[i]->SetBinError(j,0.0);} // Origin_DA[i]->Sumw2();
    // std::cout<<"Bins: n1 = "<<n1<<" n2 = "<< n2<<" n3 = "<<n3<<std::endl;
    for(int j=0; j<10; ++j) {
      // std::cout<<std::setw(50)<<RootFileNames[j]<<" DEC val = "<<Book[i][j]->GetBinContent(8)<<" DEC err = "<<Book[i][j]->GetBinError(8)<<std::endl;
      Origin_MC[i]->Add(Book[i][j]);
    }
    // std::cout<<"Overview of step "<<i<<" in the analysis: "<<" DEC val = "<<Origin_MC[i]->GetBinContent(8)<<" DEC err = "<<Origin_MC[i]->GetBinError(8)<<std::endl;
    // For Data the ID bins are not filled, but we can take the amount of entries
    Origin_ZB[i]->Add(Book[i][10]); // std::cout<<"Origin_ZB["<<i<<"]->Add(Book["<<i<<"][10]) Number of Bins"<<Book[i][10]->GetNbinsX()<<std::endl;
    Origin_DA[i]->Add(Book[i][11]); // std::cout<<"Origin_DA["<<i<<"]->Add(Book["<<i<<"][11]) Number of Bins"<<Book[i][11]->GetNbinsX()<<std::endl;
  }
  std::vector<double> DaEv, DaEr, ZbEv, ZbEr, PhEv, PhEr, FrEv, FrEr, DeEv, DeEr, ElEv, ElEr, OvEv, OvEr;
  for(int i=0; i<7; ++i)  {
    DaEv.push_back(Origin_DA[i]->GetBinContent(5)); DaEr.push_back(Origin_DA[i]->GetBinError(5)); // 5 = ? For Data no match is found --> 5
    ZbEv.push_back(Origin_ZB[i]->GetBinContent(5)); ZbEr.push_back(Origin_ZB[i]->GetBinError(5)); // 5 = ? For Zinv no match is found --> 5
    PhEv.push_back(Origin_MC[i]->GetBinContent(6)); PhEr.push_back(Origin_MC[i]->GetBinError(6));
    ElEv.push_back(Origin_MC[i]->GetBinContent(7)); ElEr.push_back(Origin_MC[i]->GetBinError(7));
    FrEv.push_back(Origin_MC[i]->GetBinContent(11)); FrEr.push_back(Origin_MC[i]->GetBinError(11)); // 8 = Frag | 10 = Ewk | 11 = ISR/FSR 8,10 are empty
    DeEv.push_back(Origin_MC[i]->GetBinContent(9)); DeEr.push_back(Origin_MC[i]->GetBinError(9));
    // Debug
    OvEv.push_back(Origin_MC[i]->GetBinContent(5)); OvEr.push_back(Origin_MC[i]->GetBinError(5));  // 5 = ?
  }

  std::cout<<std::setw(20)<<"TABLE HEADER: "<<std::setw(18)<<" DATA "<<std::setw(26)<<"DIRECT PHOTON "<<std::setw(26)<<" FRAGMENTATION PHOTON "<<std::setw(26)<<" SECONDARY PHOTON "<<std::setw(26)<<" MISTAGGED ELECTRON "<<std::setw(26)<<" OVERSCHOT "<<std::endl;
  std::cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------------"<<std::endl;
  int k;
  k=0;
  std::cout<<std::setw(20)<<"Boson + 2 Jets: "<<"| "<<std::setw(10)<<DaEv[k]<<"pm"<<std::setw(10)<<DaEr[k]<<"| "<<std::setw(10)<<PhEv[k]<<"pm"<<std::setw(10)<<PhEr[k]<<"| "<<std::setw(10)<<FrEv[k];
  std::cout<<"pm"<<std::setw(10)<<FrEr[k]<<"| "<<std::setw(10)<<DeEv[k]<<"pm"<<std::setw(10)<<DeEr[k]<<std::setw(10)<<ElEv[k]<<"pm"<<std::setw(10)<<ElEr[k]<<std::setw(10)<<OvEv[k]<<"pm"<<std::setw(10)<<OvEr[k]<<std::setw(10)<<ZbEv[k]<<"pm"<<std::setw(10)<<ZbEr[k]<<std::endl;
  k=1;
  std::cout<<std::setw(20)<<"Boson + 3 Jets: "<<"| "<<std::setw(10)<<DaEv[k]<<"pm"<<std::setw(10)<<DaEr[k]<<"| "<<std::setw(10)<<PhEv[k]<<"pm"<<std::setw(10)<<PhEr[k]<<"| "<<std::setw(10)<<FrEv[k];
  std::cout<<"pm"<<std::setw(10)<<FrEr[k]<<"| "<<std::setw(10)<<DeEv[k]<<"pm"<<std::setw(10)<<DeEr[k]<<std::setw(10)<<ElEv[k]<<"pm"<<std::setw(10)<<ElEr[k]<<std::setw(10)<<OvEv[k]<<"pm"<<std::setw(10)<<OvEr[k]<<std::setw(10)<<ZbEv[k]<<"pm"<<std::setw(10)<<ZbEr[k]<<std::endl;
  k=2;
  std::cout<<std::setw(20)<<"HT > 300: "<<"| "<<std::setw(10)<<DaEv[k]<<"pm"<<std::setw(10)<<DaEr[k]<<"| "<<std::setw(10)<<PhEv[k]<<"pm"<<std::setw(10)<<PhEr[k]<<"| "<<std::setw(10)<<FrEv[k];
  std::cout<<"pm"<<std::setw(10)<<FrEr[k]<<"| "<<std::setw(10)<<DeEv[k]<<"pm"<<std::setw(10)<<DeEr[k]<<std::setw(10)<<ElEv[k]<<"pm"<<std::setw(10)<<ElEr[k]<<std::setw(10)<<OvEv[k]<<"pm"<<std::setw(10)<<OvEr[k]<<std::setw(10)<<ZbEv[k]<<"pm"<<std::setw(10)<<ZbEr[k]<<std::endl;
  k=3;
  std::cout<<std::setw(20)<<"QCD Angular Cuts: "<<"| "<<std::setw(10)<<DaEv[k]<<"pm"<<std::setw(10)<<DaEr[k]<<"| "<<std::setw(10)<<PhEv[k]<<"pm"<<std::setw(10)<<PhEr[k]<<"| "<<std::setw(10)<<FrEv[k];
  std::cout<<"pm"<<std::setw(10)<<FrEr[k]<<"| "<<std::setw(10)<<DeEv[k]<<"pm"<<std::setw(10)<<DeEr[k]<<std::setw(10)<<ElEv[k]<<"pm"<<std::setw(10)<<ElEr[k]<<std::setw(10)<<OvEv[k]<<"pm"<<std::setw(10)<<OvEr[k]<<std::setw(10)<<ZbEv[k]<<"pm"<<std::setw(10)<<ZbEr[k]<<std::endl;
  k=4;
  std::cout<<std::setw(20)<<"Baseline Selection: "<<"| "<<std::setw(10)<<DaEv[k]<<"pm"<<std::setw(10)<<DaEr[k]<<"| "<<std::setw(10)<<PhEv[k]<<"pm"<<std::setw(10)<<PhEr[k]<<"| "<<std::setw(10)<<FrEv[k];
  std::cout<<"pm"<<std::setw(10)<<FrEr[k]<<"| "<<std::setw(10)<<DeEv[k]<<"pm"<<std::setw(10)<<DeEr[k]<<std::setw(10)<<ElEv[k]<<"pm"<<std::setw(10)<<ElEr[k]<<std::setw(10)<<OvEv[k]<<"pm"<<std::setw(10)<<OvEr[k]<<std::setw(10)<<ZbEv[k]<<"pm"<<std::setw(10)<<ZbEr[k]<<std::endl;
  k=5;
  std::cout<<std::setw(20)<<"High HT Selection: "<<"| "<<std::setw(10)<<DaEv[k]<<"pm"<<std::setw(10)<<DaEr[k]<<"| "<<std::setw(10)<<PhEv[k]<<"pm"<<std::setw(10)<<PhEr[k]<<"| "<<std::setw(10)<<FrEv[k];
  std::cout<<"pm"<<std::setw(10)<<FrEr[k]<<"| "<<std::setw(10)<<DeEv[k]<<"pm"<<std::setw(10)<<DeEr[k]<<std::setw(10)<<ElEv[k]<<"pm"<<std::setw(10)<<ElEr[k]<<std::setw(10)<<OvEv[k]<<"pm"<<std::setw(10)<<OvEr[k]<<std::setw(10)<<ZbEv[k]<<"pm"<<std::setw(10)<<ZbEr[k]<<std::endl;
  k=6;
  std::cout<<std::setw(20)<<"High MHT Selection: "<<"| "<<std::setw(10)<<DaEv[k]<<"pm"<<std::setw(10)<<DaEr[k]<<"| "<<std::setw(10)<<PhEv[k]<<"pm"<<std::setw(10)<<PhEr[k]<<"| "<<std::setw(10)<<FrEv[k];
  std::cout<<"pm"<<std::setw(10)<<FrEr[k]<<"| "<<std::setw(10)<<DeEv[k]<<"pm"<<std::setw(10)<<DeEr[k]<<std::setw(10)<<ElEv[k]<<"pm"<<std::setw(10)<<ElEr[k]<<std::setw(10)<<OvEv[k]<<"pm"<<std::setw(10)<<OvEr[k]<<std::setw(10)<<ZbEv[k]<<"pm"<<std::setw(10)<<ZbEr[k]<<std::endl;

  std::cout<<" "<<std::endl;
  std::cout<<" "<<std::endl;



  // PURITY & FRAG CONTR
  std::vector<double> AllEv, AllEr, DirEv, DirEr, PurEv, PurEr, FragEv, FragEr;
  for(int i=0; i<7; ++i)  {
    AllEv.push_back( PhEv[i]+FrEv[i]+DeEv[i] ); AllEr.push_back( sqrt( pow(PhEr[i]/PhEv[i],2) + pow(FrEr[i]/FrEv[i],2) + pow(DeEr[i]/DeEv[i],2) ) );
    DirEv.push_back( PhEv[i]+FrEv[i] );         DirEr.push_back( sqrt( pow(PhEr[i]/PhEv[i],2) + pow(FrEr[i]/FrEv[i],2) ) );
    PurEv.push_back( DirEv[i]/AllEv[i] );       PurEr.push_back( DirEv[i]/AllEv[i] * sqrt( pow(DirEr[i]/DirEv[i],2) + pow(AllEr[i]/AllEv[i],2) ) );
    FragEv.push_back( PhEv[i]/DirEv[i] );       FragEr.push_back( PhEv[i]/DirEv[i] * sqrt( pow(PhEr[i]/PhEv[i],2) + pow(DirEr[i]/DirEv[i],2) ) );
  }
  std::cout<<std::setw(20)<<"TABLE HEADER: "<<std::setw(18)<<" PURITY "<<std::setw(26)<<"FRAG CONTR "<<std::endl;
  std::cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------------"<<std::endl;
  k=0;
  std::cout<<std::setw(20)<<"Boson + 2 Jets: "<<"| "<<std::setw(10)<<PurEv[k]<<"pm"<<std::setw(10)<<PurEr[k]<<"| "<<std::setw(10)<<FragEv[k]<<"pm"<<std::setw(10)<<FragEr[k]<<std::endl;
  k=1;
  std::cout<<std::setw(20)<<"Boson + 3 Jets: "<<"| "<<std::setw(10)<<PurEv[k]<<"pm"<<std::setw(10)<<PurEr[k]<<"| "<<std::setw(10)<<FragEv[k]<<"pm"<<std::setw(10)<<FragEr[k]<<std::endl;
  k=2;
  std::cout<<std::setw(20)<<"HT > 300: "<<"| "<<std::setw(10)<<PurEv[k]<<"pm"<<std::setw(10)<<PurEr[k]<<"| "<<std::setw(10)<<FragEv[k]<<"pm"<<std::setw(10)<<FragEr[k]<<std::endl;
  k=3;
  std::cout<<std::setw(20)<<"QCD Anglular Cuts: "<<"| "<<std::setw(10)<<PurEv[k]<<"pm"<<std::setw(10)<<PurEr[k]<<"| "<<std::setw(10)<<FragEv[k]<<"pm"<<std::setw(10)<<FragEr[k]<<std::endl;
  k=4;
  std::cout<<std::setw(20)<<"Baseline Selection: "<<"| "<<std::setw(10)<<PurEv[k]<<"pm"<<std::setw(10)<<PurEr[k]<<"| "<<std::setw(10)<<FragEv[k]<<"pm"<<std::setw(10)<<FragEr[k]<<std::endl;
  k=5;
  std::cout<<std::setw(20)<<"High HT Selection: "<<"| "<<std::setw(10)<<PurEv[k]<<"pm"<<std::setw(10)<<PurEr[k]<<"| "<<std::setw(10)<<FragEv[k]<<"pm"<<std::setw(10)<<FragEr[k]<<std::endl;
  k=6;
  std::cout<<std::setw(20)<<"High MHT Selection: "<<"| "<<std::setw(10)<<PurEv[k]<<"pm"<<std::setw(10)<<PurEr[k]<<"| "<<std::setw(10)<<FragEv[k]<<"pm"<<std::setw(10)<<FragEr[k]<<std::endl;

  std::cout<<" "<<std::endl;
  std::cout<<" "<<std::endl;



  // Zinv FACTOR TABLE
  std::vector<double> ZP1Ev, ZP1Er, ZP2Ev, ZP2Er;
  for(int i=0; i<7; ++i)  {
    ZP1Ev.push_back(ZbEv[i]/PhEv[i]);   ZP1Er.push_back(ZbEv[i]/PhEv[i]*sqrt((pow(PhEr[i]/PhEv[i],2)+pow(ZbEr[i]/ZbEv[i],2))));
    ZP2Ev.push_back(5*ZbEv[i]/PhEv[i]); ZP2Er.push_back(5*ZbEv[i]/PhEv[i]*sqrt((pow(PhEr[i]/PhEv[i],2)+pow(ZbEr[i]/ZbEv[i],2))));
  }
  std::cout<<std::setw(20)<<"TABLE HEADER: "<<std::setw(18)<<" Z --> Invisible "<<std::setw(26)<<"DIRECT PHOTON "<<std::setw(26)<<" Zinvisible / Photon "<<std::setw(26)<<" Zboson / Photon"<<std::endl;
  std::cout<<"--------------------------------------------------------------------------------------------------------------------------------------------------------------"<<std::endl;
  k=0;
  std::cout<<std::setw(20)<<"Boson + 2 Jets: "<<"| "<<std::setw(10)<<ZbEv[k]<<"pm"<<std::setw(10)<<ZbEr[k]<<"| "<<std::setw(10)<<PhEv[k]<<"pm"<<std::setw(10)<<PhEr[k];
  std::cout<<std::setw(10)<<ZP1Ev[k]<<"pm"<<std::setw(10)<<ZP1Er[k]<<std::setw(10)<<ZP2Ev[k]<<"pm"<<std::setw(10)<<ZP2Er[k]<<std::endl;
  k=1;
  std::cout<<std::setw(20)<<"Boson + 3 Jets: "<<"| "<<std::setw(10)<<ZbEv[k]<<"pm"<<std::setw(10)<<ZbEr[k]<<"| "<<std::setw(10)<<PhEv[k]<<"pm"<<std::setw(10)<<PhEr[k];
  std::cout<<std::setw(10)<<ZP1Ev[k]<<"pm"<<std::setw(10)<<ZP1Er[k]<<std::setw(10)<<ZP2Ev[k]<<"pm"<<std::setw(10)<<ZP2Er[k]<<std::endl;
  k=2;
  std::cout<<std::setw(20)<<"HT > 300: "<<"| "<<std::setw(10)<<ZbEv[k]<<"pm"<<std::setw(10)<<ZbEr[k]<<"| "<<std::setw(10)<<PhEv[k]<<"pm"<<std::setw(10)<<PhEr[k];
  std::cout<<std::setw(10)<<ZP1Ev[k]<<"pm"<<std::setw(10)<<ZP1Er[k]<<std::setw(10)<<ZP2Ev[k]<<"pm"<<std::setw(10)<<ZP2Er[k]<<std::endl;
  k=3;
  std::cout<<std::setw(20)<<"QCD Angular Cuts: "<<"| "<<std::setw(10)<<ZbEv[k]<<"pm"<<std::setw(10)<<ZbEr[k]<<"| "<<std::setw(10)<<PhEv[k]<<"pm"<<std::setw(10)<<PhEr[k];
  std::cout<<std::setw(10)<<ZP1Ev[k]<<"pm"<<std::setw(10)<<ZP1Er[k]<<std::setw(10)<<ZP2Ev[k]<<"pm"<<std::setw(10)<<ZP2Er[k]<<std::endl;
  k=4;
  std::cout<<std::setw(20)<<"Baseline Selection: "<<"| "<<std::setw(10)<<ZbEv[k]<<"pm"<<std::setw(10)<<ZbEr[k]<<"| "<<std::setw(10)<<PhEv[k]<<"pm"<<std::setw(10)<<PhEr[k];
  std::cout<<std::setw(10)<<ZP1Ev[k]<<"pm"<<std::setw(10)<<ZP1Er[k]<<std::setw(10)<<ZP2Ev[k]<<"pm"<<std::setw(10)<<ZP2Er[k]<<std::endl;
  k=5;
  std::cout<<std::setw(20)<<"High HT Selection:: "<<"| "<<std::setw(10)<<ZbEv[k]<<"pm"<<std::setw(10)<<ZbEr[k]<<"| "<<std::setw(10)<<PhEv[k]<<"pm"<<std::setw(10)<<PhEr[k];
  std::cout<<std::setw(10)<<ZP1Ev[k]<<"pm"<<std::setw(10)<<ZP1Er[k]<<std::setw(10)<<ZP2Ev[k]<<"pm"<<std::setw(10)<<ZP2Er[k]<<std::endl;
  k=6;
  std::cout<<std::setw(20)<<"High MHT Selection: "<<"| "<<std::setw(10)<<ZbEv[k]<<"pm"<<std::setw(10)<<ZbEr[k]<<"| "<<std::setw(10)<<PhEv[k]<<"pm"<<std::setw(10)<<PhEr[k];
  std::cout<<std::setw(10)<<ZP1Ev[k]<<"pm"<<std::setw(10)<<ZP1Er[k]<<std::setw(10)<<ZP2Ev[k]<<"pm"<<std::setw(10)<<ZP2Er[k]<<std::endl;
}
