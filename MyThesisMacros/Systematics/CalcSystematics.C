#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector.h>

void CalcSystematics() {

  // -------------------
  // GENERAL INFORMATION
  // ------------------

  // Photons in Barrel and Endcap in 2Jets, 3Jets, Baseline Selection, High HT, High MHT 
  std::vector<double> barrel, endcap;  
  std::vector<double> barlow, barhigh, endlow, endhigh, tot, stat;  

  // PH + 2 Jets             PH + 3 Jets             BASELINE SEL           High HT Sel            High MHT Sel
  barrel.push_back(52);   barrel.push_back(16);   barrel.push_back(52);  barrel.push_back(16);  barrel.push_back(10);
  endcap.push_back(17);   endcap.push_back(5);    endcap.push_back(17);  endcap.push_back(5);   endcap.push_back(3);
  barlow.push_back(596);  barlow.push_back(65);   barlow.push_back(1);   barlow.push_back(0);   barlow.push_back(0); 
  barhigh.push_back(922); barhigh.push_back(153); barhigh.push_back(51); barhigh.push_back(16); barhigh.push_back(10);
  endlow.push_back(307);  endlow.push_back(44);   endlow.push_back(0);   endlow.push_back(0);   endlow.push_back(0);
  endhigh.push_back(401); endhigh.push_back(76);  endhigh.push_back(17); endhigh.push_back(5);  endhigh.push_back(3);
  tot.push_back(2226);    tot.push_back(338);     tot.push_back(69);     tot.push_back(21);     tot.push_back(13);
  for(int i=0; i<5; ++i) { stat.push_back(sqrt(tot[i])); }


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
  double barlow_pur  = 0.792, barhigh_pur  = 0.952, endlow_pur  = 0.779, endhigh_pur  = 0.965;
  double barlow_stat = 0.026, barhigh_stat = 0.026, endlow_stat = 0.066, endhigh_stat = 0.142;
  double barlow_syst = 0.063, barhigh_syst = 0.077, endlow_syst = 0.135, endhigh_syst = 0.167;
  //*/
  // Combined Isolation Template
  /*
  double barlow_pur  = 0.810, barhigh_pur  = 0.902, endlow_pur  = 0.614, endhigh_pur  = 0.693;
  double barlow_stat = 0.046, barhigh_stat = 0.084, endlow_stat = 0.054, endhigh_stat = 0.108;
  double barlow_syst = 0.070, barhigh_syst = 0.087, endlow_syst = 0.108, endhigh_syst = 0.103;
  */
  double barlow_err  = sqrt(pow(barlow_stat,2)+pow(barlow_syst,2));
  double barhigh_err = sqrt(pow(barhigh_stat,2)+pow(barhigh_syst,2));
  double endlow_err  = sqrt(pow(endlow_stat,2)+pow(endlow_syst,2));
  double endhigh_err = sqrt(pow(endhigh_stat,2)+pow(endhigh_syst,2));

  std::vector<double> pur_val, pur_err;

  for(int i=0; i<barlow.size(); ++i) {
    double photonpur_val = 0.0;
    double photonpur_err = 0.0;
    photonpur_val = barlow[i]/tot[i] * barlow_pur + barhigh[i]/tot[i] * barhigh_pur + endlow[i]/tot[i] * endlow_pur + endhigh[i]/tot[i] * endhigh_pur;
    photonpur_err = barlow[i]/tot[i] * barlow_err + barhigh[i]/tot[i] * barhigh_err + endlow[i]/tot[i] * endlow_err + endhigh[i]/tot[i] * endhigh_err;
    std::cout<<" Search Region "<<i<<" PURITY = "<<photonpur_val<<" pm "<<photonpur_err<<" syst percentage "<<photonpur_err/photonpur_val<<std::endl;
    pur_val.push_back(photonpur_val); pur_err.push_back(photonpur_err/photonpur_val);
  }


  // PHOTON FRAGMENTATION
  // --------------------
  std::vector<double> frag_val;
  double frag_low  = 0.92;
  double frag_high = 0.95;
  for(int i=0; i<barlow.size(); ++i) {
    // std::cout<<"("<<barlow[i]<<"+"<<endlow[i]<<")/"<<tot[i]<<"*"<<frag_low<<" + ("<<barhigh[i]<<"+"<<endhigh[i]<<")/"<<tot[i]<<"*"<<frag_high<<std::endl;
    frag_val.push_back( (barlow[i]+endlow[i])/tot[i]*frag_low + (barhigh[i]+endhigh[i])/tot[i]*frag_high );
    std::cout<<" Search Region "<<i<<" FRAG = "<<frag_val[i]<<std::endl;
  }

  // Total Systematic Uncertainty
  // --------------------------------
  //       Constant (determined for pt > 70) <_     _> obtained from RECO factor table
  //                                           |   |
  double j2_val   = frag_val[0]*pur_val[0]*1.035*0.110*sel_val[0];
  double j3_val   = frag_val[1]*pur_val[1]*1.035*0.675*sel_val[1]; 
  double base_val = frag_val[2]*pur_val[2]*1.035*0.388*sel_val[2];
  double hht_val  = frag_val[3]*pur_val[3]*1.035*0.430*sel_val[3];
  double mht_val  = frag_val[4]*pur_val[4]*1.035*0.461*sel_val[4];

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
  double base_syst = hht_err  * tot[3];
  double base_syst = mht_err  * tot[4];

  std::cout<<" Photon + 2 Jet Sel: CORR = "<<j2_val  <<" syst = "<<j2_err  <<" PRED = "<<tot[0] * j2_val  <<" stat = "<<stat[0] * j2_val  <<" syst = "<<tot[0] * j2_val   * j2_err  <<std::endl;
  std::cout<<" Photon + 3 Jet Sel: CORR = "<<j3_val  <<" syst = "<<j3_err  <<" PRED = "<<tot[1] * j3_val  <<" stat = "<<stat[1] * j3_val  <<" syst = "<<tot[1] * j3_val   * j3_err  <<std::endl;
  std::cout<<" Baseline Selection: CORR = "<<base_val<<" syst = "<<base_err<<" PRED = "<<tot[2] * base_val<<" stat = "<<stat[2] * base_val<<" syst = "<<tot[2] * base_val * base_err<<std::endl;
  std::cout<<" High HT  Selection: CORR = "<<hht_val <<" syst = "<<hht_err <<" PRED = "<<tot[3] * hht_val <<" stat = "<<stat[3] * hht_val <<" syst = "<<tot[3]  * hht_val  * hht_err<<std::endl;
  std::cout<<" High MHT Selection: CORR = "<<mht_val <<" syst = "<<mht_err <<" PRED = "<<tot[4] * mht_val <<" stat = "<<stat[4] * mht_val <<" syst = "<<tot[4]  * mht_val  * mht_err<<std::endl;
}




