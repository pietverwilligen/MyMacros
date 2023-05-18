#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>

void CalcNewPurity() {

  // -------------------
  // GENERAL INFORMATION
  // ------------------

  // Photons in Barrel and Endcap in 2Jets, 3Jets, Baseline Selection, High HT, High MHT 
  std::vector<double> barrel, endcap, barlow, barhigh, endlow, endhigh;  
  std::vector<double> bar_09_120, bar_09_200, bar_09_300, bar_14_120, bar_14_200, bar_14_300, end_21_120, end_21_200, end_21_300, end_25_120, end_25_200, end_25_300, tot, staterr;  




  // PH + 2 Jets               PH + 3 Jets                 BASELINE SEL                High HT Sel                High MHT Sel
  bar_09_120.push_back(351);   bar_09_120.push_back(37);   bar_09_120.push_back(0);    bar_09_120.push_back(0);   bar_09_120.push_back(0);
  bar_09_200.push_back(458);   bar_09_200.push_back(80);   bar_09_200.push_back(25);   bar_09_200.push_back(6);   bar_09_200.push_back(1);
  bar_09_300.push_back(97);    bar_09_300.push_back(20);   bar_09_300.push_back(14);   bar_09_300.push_back(5);   bar_09_300.push_back(10);

  bar_14_120.push_back(210);   bar_14_120.push_back(25);   bar_14_120.push_back(1);    bar_14_120.push_back(0);   bar_14_120.push_back(0);
  bar_14_200.push_back(264);   bar_14_200.push_back(43);   bar_14_200.push_back(7);    bar_14_200.push_back(1);   bar_14_200.push_back(0);
  bar_14_300.push_back(46);    bar_14_300.push_back(8);    bar_14_300.push_back(4);    bar_14_300.push_back(3);   bar_14_300.push_back(1);

  end_21_120.push_back(199);   end_21_120.push_back(30);   end_21_120.push_back(1);    end_21_120.push_back(0);   end_21_120.push_back(0);
  end_21_200.push_back(233);   end_21_200.push_back(47);   end_21_200.push_back(13);   end_21_200.push_back(4);   end_21_200.push_back(0);
  end_21_300.push_back(28);    end_21_300.push_back(7);    end_21_300.push_back(3);    end_21_300.push_back(1);   end_21_300.push_back(2);

  end_25_120.push_back(114);   end_25_120.push_back(17);   end_25_120.push_back(0);    end_25_120.push_back(0);   end_25_120.push_back(0);
  end_25_200.push_back(109);   end_25_200.push_back(20);   end_25_200.push_back(1);    end_25_200.push_back(0);   end_25_200.push_back(0);
  end_25_300.push_back(17);    end_25_300.push_back(3);    end_25_300.push_back(3);    end_25_300.push_back(2);   end_25_300.push_back(2);

  for(int i=0; i<5; ++i) { 
    barrel.push_back(bar_09_120[i] + bar_09_200[i] + bar_09_300[i] + bar_14_120[i] + bar_14_200[i] + bar_14_300[i]);
    endcap.push_back(end_21_120[i] + end_21_200[i] + end_21_300[i] + end_25_120[i] + end_25_200[i] + end_25_300[i]);
    tot.push_back(barrel[i]+endcap[i]);
    staterr.push_back(sqrt(tot[i])); 
    barlow.push_back(bar_09_120[i]+bar_14_120[i]); barhigh.push_back(bar_09_200[i]+bar_09_300[i]+bar_14_200[i]+bar_14_300[i]); 
    endlow.push_back(end_21_120[i]+end_25_120[i]); endhigh.push_back(end_21_200[i]+end_21_300[i]+end_25_200[i]+end_25_300[i]); 
  }

  std::vector< std::vector< double > > yields; 
  yields.push_back(bar_09_120); yields.push_back(bar_09_200); yields.push_back(bar_09_300); yields.push_back(bar_14_120); yields.push_back(bar_14_200); yields.push_back(bar_14_300); yields.push_back(end_21_120); yields.push_back(end_21_200); yields.push_back(end_21_300); yields.push_back(end_25_120); yields.push_back(end_25_200); yields.push_back(end_21_300);

  // DR = 0.4 ==> 70 events in baseline of which 52 in high energy barrel instead of 51
  // ID from EGamma
  /*
  double base_ph   = 68,  hht_ph   = 20,  mht_ph   = 13;
  double base_stat = 8.2, hht_stat = 4.6, mht_stat = 3.6;
  // Photons in Barrel and Endcap in the Baseline Selection, High HT, High MHT 
  std::vector<double> barrel, endcap;  
  barrel.push_back(51); barrel.push_back(15); barrel.push_back(10);
  endcap.push_back(17); endcap.push_back(5); endcap.push_back(3);
  */

  // Photon Selection (RECO, ISO, ID)
  // --------------------------------

  // Data / MC factor selection: first error is the error on the value, second one is due to pile up
  double sel_barrel_val = 1.011, sel_barrel_err = 0.019, sel_barrel_sys = 0.01;
  double sel_endcap_val = 0.997, sel_endcap_err = 0.032, sel_endcap_sys = 0.01;

  sel_barrel_err = sqrt(pow(sel_barrel_err/sel_barrel_val,2)+pow(0.01,2));
  sel_endcap_err = sqrt(pow(sel_endcap_err/sel_endcap_val,2)+pow(0.01,2));


  // No Pile Up / Pile Up
  // test: double pilehalf_barrel = 1, pilehalf_endcap = 1;
  // double pileup_barrel = 1.053, pilehalf_barrel = 1.027;
  // double pileup_endcap = 1.013, pilehalf_endcap = 1.007;


  std::vector<double> sel_val, sel_err;

  for(int i=0; i<barrel.size(); ++i) {
    double photonsel_val = 0.0;
    double photonsel_err = 0.0;
    photonsel_val = barrel[i]/(barrel[i]+endcap[i]) * sel_barrel_val /*/ pilehalf_barrel*/ + endcap[i]/(barrel[i]+endcap[i]) * sel_endcap_val /*/ pilehalf_endcap*/;
    photonsel_err = barrel[i]/(barrel[i]+endcap[i]) * sel_barrel_err /*/ pilehalf_barrel*/ + endcap[i]/(barrel[i]+endcap[i]) * sel_endcap_err /*/ pilehalf_endcap*/;
    std::cout<<" Search Region "<<i<<" SEL EFF = "<<photonsel_val<<" pm "<<photonsel_err<<" syst percentage "<<photonsel_err/photonsel_val<<std::endl;
    sel_val.push_back(photonsel_val); sel_err.push_back(photonsel_err/photonsel_val);
  }


  // Photon Purity
  // -------------

  // Data / MC factor selection:
  // Shower Shape Template
  ///*
  double bar_09_120_pur  = 0.91,  bar_09_200_pur  = 0.94,  bar_09_300_pur  = 0.97,  bar_14_120_pur  = 0.88,  bar_14_200_pur  = 0.92,  bar_14_300_pur  = 0.92; 
  double bar_09_120_stat = 0.02,  bar_09_200_stat = 0.02,  bar_09_300_stat = 0.07,  bar_14_120_stat = 0.03,  bar_14_200_stat = 0.03,  bar_14_300_stat = 0.09;
  double bar_09_120_syst = 0.064, bar_09_200_syst = 0.074, bar_09_300_syst = 0.077, bar_14_120_syst = 0.062, bar_14_200_syst = 0.074, bar_14_300_syst = 0.074;

  double end_21_120_pur  = 0.91,  end_21_200_pur  = 0.94,  end_21_300_pur  = 0.97,  end_25_120_pur  = 0.88,  end_25_200_pur  = 0.92,  end_25_300_pur  = 0.92; 
  double end_21_120_stat = 0.02,  end_21_200_stat = 0.02,  end_21_300_stat = 0.07,  end_25_120_stat = 0.03,  end_25_200_stat = 0.03,  end_25_300_stat = 0.21;
  double end_21_120_syst = 0.083, end_21_200_syst = 0.079, end_21_300_syst = 0.084, end_25_120_syst = 0.070, end_25_200_syst = 0.072, end_25_300_syst = 0.088;

  std::vector< double > pur; 
  pur.push_back(bar_09_120_pur); pur.push_back(bar_09_200_pur); pur.push_back(bar_09_300_pur); pur.push_back(bar_14_120_pur); pur.push_back(bar_14_200_pur); pur.push_back(bar_14_300_pur); pur.push_back(end_21_120_pur); pur.push_back(end_21_200_pur); pur.push_back(end_21_300_pur); pur.push_back(end_25_120_pur); pur.push_back(end_25_200_pur); pur.push_back(end_21_300_pur);
  std::vector< double > stat; 
  stat.push_back(bar_09_120_stat); stat.push_back(bar_09_200_stat); stat.push_back(bar_09_300_stat); stat.push_back(bar_14_120_stat); stat.push_back(bar_14_200_stat); stat.push_back(bar_14_300_stat); stat.push_back(end_21_120_stat); stat.push_back(end_21_200_stat); stat.push_back(end_21_300_stat); stat.push_back(end_25_120_stat); stat.push_back(end_25_200_stat); stat.push_back(end_21_300_stat);
  std::vector< double > syst; 
  syst.push_back(bar_09_120_syst); syst.push_back(bar_09_200_syst); syst.push_back(bar_09_300_syst); syst.push_back(bar_14_120_syst); syst.push_back(bar_14_200_syst); syst.push_back(bar_14_300_syst); syst.push_back(end_21_120_syst); syst.push_back(end_21_200_syst); syst.push_back(end_21_300_syst); syst.push_back(end_25_120_syst); syst.push_back(end_25_200_syst); syst.push_back(end_21_300_syst);

  std::vector< double > err;
  for(int i=0; i<stat.size(); ++i) {
    err.push_back(sqrt(pow(stat[i],2)+pow(syst[i],2)));
  }

  std::vector<double> pur_val, pur_err;

  for(int i=0; i<5; ++i) { 
    double photonpur_val = 0.0;
    double photonpur_err = 0.0;
    for(int j=0; j<pur.size(); ++j) {
      photonpur_val += yields[j][i]/tot[i] * pur[j];
      photonpur_err += yields[j][i]/tot[i] * err[j];
    }
    std::cout<<" Search Region "<<i<<" PURITY = "<<photonpur_val<<" pm "<<photonpur_err<<" syst percentage "<<photonpur_err/photonpur_val<<std::endl;
    pur_val.push_back(photonpur_val); pur_err.push_back(photonpur_err/photonpur_val);
  }

  // PHOTON FRAGMENTATION
  // --------------------
  std::vector<double> frag_val;
  double frag_low  = 0.92;
  double frag_high = 0.95;
  for(int i=0; i<5; ++i) {
    // std::cout<<"("<<barlow[i]<<"+"<<endlow[i]<<")/"<<tot[i]<<"*"<<frag_low<<" + ("<<barhigh[i]<<"+"<<endhigh[i]<<")/"<<tot[i]<<"*"<<frag_high<<std::endl;
    frag_val.push_back( (barlow[i]+endlow[i])/tot[i]*frag_low + (barhigh[i]+endhigh[i])/tot[i]*frag_high );
    std::cout<<" Search Region "<<i<<" FRAG = "<<frag_val[i]<<std::endl;
  }

  // Total Systematic Uncertainty
  // --------------------------------
  //       Constant (determined for pt > 70) <_     _> obtained from RECO factor table
  //                                           |   |
  double j2_val   = frag_val[0]*pur_val[0]*1.035*0.113*sel_val[0];
  double j3_val   = frag_val[1]*pur_val[1]*1.035*0.703*sel_val[1]; 
  double base_val = frag_val[2]*pur_val[2]*1.035*0.405*sel_val[2];
  double hht_val  = frag_val[3]*pur_val[3]*1.035*0.441*sel_val[3];
  double mht_val  = frag_val[4]*pur_val[4]*1.035*0.483*sel_val[4];




  // theoretical error is uniform 0.3 in a box: so if the value is 1, the uncertainty is limited to be inside [0.7,1.3]
  // sigma = sqrt[ (b-a)^2 / 12 ] = (b-a) / sqrt(12) = (1.3 - 0.7) / sqrt(12) = 17.32

  //                     FRAG error      PUR error         mistag     Z/G theor      Accep   Z/G stat ERR     data/mc err
  double j2_err   = sqrt(pow(0.01,2)+pow(pur_err[0],2)+pow(0.014,2)+pow(0.173,2)+pow(0.05,2)+pow(0.025,2)+pow(sel_err[0],2));
  double j3_err   = sqrt(pow(0.01,2)+pow(pur_err[0],2)+pow(0.014,2)+pow(0.173,2)+pow(0.05,2)+pow(0.026,2)+pow(sel_err[0],2));
  double base_err = sqrt(pow(0.01,2)+pow(pur_err[0],2)+pow(0.014,2)+pow(0.173,2)+pow(0.05,2)+pow(0.07,2) +pow(sel_err[0],2));
  double hht_err  = sqrt(pow(0.01,2)+pow(pur_err[1],2)+pow(0.014,2)+pow(0.173,2)+pow(0.05,2)+pow(0.13,2) +pow(sel_err[1],2));
  double mht_err  = sqrt(pow(0.01,2)+pow(pur_err[2],2)+pow(0.014,2)+pow(0.173,2)+pow(0.05,2)+pow(0.13,2) +pow(sel_err[2],2));

  double j2_syst   = j2_err   * tot[0];
  double j3_syst   = j3_err   * tot[1];
  double base_syst = base_err * tot[2];
  double hht_syst  = hht_err  * tot[3];
  double mht_syst  = mht_err  * tot[4];


  std::cout<<""<<std::endl;
  std::cout<<"Theor Uncertainty: 30% in a box"<<std::endl;
  std::cout<<""<<std::endl;

  std::cout<<" Photon + 2 Jet Sel: YIELD = "<<tot[0]<<" stat = "<<staterr[0]<<" CORR = "<<j2_val  <<" syst = "<<j2_err  <<" PRED = "<<tot[0] * j2_val  <<" stat = "<<staterr[0] * j2_val  <<" syst = "<<tot[0] * j2_val   * j2_err  <<std::endl;
  std::cout<<" Photon + 3 Jet Sel: YIELD = "<<tot[1]<<" stat = "<<staterr[1]<<" CORR = "<<j3_val  <<" syst = "<<j3_err  <<" PRED = "<<tot[1] * j3_val  <<" stat = "<<staterr[1] * j3_val  <<" syst = "<<tot[1] * j3_val   * j3_err  <<std::endl;
  std::cout<<" Baseline Selection: YIELD = "<<tot[2]<<" stat = "<<staterr[2]<<" CORR = "<<base_val<<" syst = "<<base_err<<" PRED = "<<tot[2] * base_val<<" stat = "<<staterr[2] * base_val<<" syst = "<<tot[2] * base_val * base_err<<std::endl;
  std::cout<<" High HT  Selection: YIELD = "<<tot[3]<<" stat = "<<staterr[3]<<" CORR = "<<hht_val <<" syst = "<<hht_err <<" PRED = "<<tot[3] * hht_val <<" stat = "<<staterr[3] * hht_val <<" syst = "<<tot[3]  * hht_val  * hht_err<<std::endl;
  std::cout<<" High MHT Selection: YIELD = "<<tot[4]<<" stat = "<<staterr[4]<<" CORR = "<<mht_val <<" syst = "<<mht_err <<" PRED = "<<tot[4] * mht_val <<" stat = "<<staterr[4] * mht_val <<" syst = "<<tot[4]  * mht_val  * mht_err<<std::endl;

  std::cout<<""<<std::endl;
  std::cout<<"Theor Uncerntainty: 10% RMS"<<std::endl;
  std::cout<<""<<std::endl;

  j2_err   = sqrt(pow(0.01,2)+pow(pur_err[0],2)+pow(0.014,2)+pow(0.10,2)+pow(0.05,2)+pow(0.025,2)+pow(sel_err[0],2));
  j3_err   = sqrt(pow(0.01,2)+pow(pur_err[0],2)+pow(0.014,2)+pow(0.10,2)+pow(0.05,2)+pow(0.026,2)+pow(sel_err[0],2));
  base_err = sqrt(pow(0.01,2)+pow(pur_err[0],2)+pow(0.014,2)+pow(0.10,2)+pow(0.05,2)+pow(0.07,2) +pow(sel_err[0],2));
  hht_err  = sqrt(pow(0.01,2)+pow(pur_err[1],2)+pow(0.014,2)+pow(0.10,2)+pow(0.05,2)+pow(0.13,2) +pow(sel_err[1],2));
  mht_err  = sqrt(pow(0.01,2)+pow(pur_err[2],2)+pow(0.014,2)+pow(0.10,2)+pow(0.05,2)+pow(0.13,2) +pow(sel_err[2],2));

  j2_syst   = j2_err   * tot[0];
  j3_syst   = j3_err   * tot[1];
  base_syst = base_err * tot[2];
  base_syst = hht_err  * tot[3];
  base_syst = mht_err  * tot[4];

  std::cout<<" Photon + 2 Jet Sel: YIELD = "<<tot[0]<<" stat = "<<staterr[0]<<" CORR = "<<j2_val  <<" syst = "<<j2_err  <<" PRED = "<<tot[0] * j2_val  <<" stat = "<<staterr[0] * j2_val  <<" syst = "<<tot[0] * j2_val   * j2_err  <<std::endl;
  std::cout<<" Photon + 3 Jet Sel: YIELD = "<<tot[1]<<" stat = "<<staterr[1]<<" CORR = "<<j3_val  <<" syst = "<<j3_err  <<" PRED = "<<tot[1] * j3_val  <<" stat = "<<staterr[1] * j3_val  <<" syst = "<<tot[1] * j3_val   * j3_err  <<std::endl;
  std::cout<<" Baseline Selection: YIELD = "<<tot[2]<<" stat = "<<staterr[2]<<" CORR = "<<base_val<<" syst = "<<base_err<<" PRED = "<<tot[2] * base_val<<" stat = "<<staterr[2] * base_val<<" syst = "<<tot[2] * base_val * base_err<<std::endl;
  std::cout<<" High HT  Selection: YIELD = "<<tot[3]<<" stat = "<<staterr[3]<<" CORR = "<<hht_val <<" syst = "<<hht_err <<" PRED = "<<tot[3] * hht_val <<" stat = "<<staterr[3] * hht_val <<" syst = "<<tot[3]  * hht_val  * hht_err<<std::endl;
  std::cout<<" High MHT Selection: YIELD = "<<tot[4]<<" stat = "<<staterr[4]<<" CORR = "<<mht_val <<" syst = "<<mht_err <<" PRED = "<<tot[4] * mht_val <<" stat = "<<staterr[4] * mht_val <<" syst = "<<tot[4]  * mht_val  * mht_err<<std::endl;


}




