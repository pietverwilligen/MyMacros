#include <TROOT.h>
#include "TString.h"
#include "TSystem.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include "TIterator.h"
#include "TKey.h"

#include "TFile.h"
#include "TCanvas.h"


#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <iomanip>
#include <iostream>
#include <fstream>

// -----------------------------------------------
// 
// Macro to extract all Fit Canvasses
// from a CMS Standard TnP ROOT File
// Adapted version of ROOT macro of Hugues Brun
//
// ------------------------------------------------

void ExtractFitCanvas(){

  TString outputDir = "fitPlots";            // directory that will contain the fit plots
  TString thePlotToDraw[1] = {"PF"};         // name of the ID in the TnP trees
  // TString theName[1] = {"Loose_ID"};         // name of the ID that will appear on the plot ...
  // int nbOfIds = 1;                           // number of IDs
  TString thePath = "DIRPATH";
  // TString thePath = "/home/piet/Work/TagAndProbe/HZZ4l_Final_Analysis/HZZ4l_TnP_PPM_53ABCD/PFdBIso_from_SIP_and_ID/";
  TString kind;
  TString candle;
  // TDirectory *theDr = (TDirectory*) myFile->Get("eleIDdir");///denom_pt/fit_eff_plots");
  // theDr->ls();
  int myIndex;
  // int theIndex;

  // Binnings
  double all_eta_binning[] = {-2.4, -2.1, -1.6, -1.2, -0.9, -0.6, -0.3, -0.2, 0.2, 0.3, 0.6, 0.9, 1.2, 1.6, 2.1, 2.4};
  double all_vtx_binning[] = {0.5, 2.5, 4.5, 6.5, 8.5, 10.5, 12.5, 14.5, 16.5, 18.5, 20.5, 22.5, 24.5, 26.5, 28.5, 30.5, 50.5};
  double mid_pte_binning[] = {2, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.5, 5.0, 5.5, 6.0, 7.0, 8.0, 9.0, 10, 12.5, 15, 20, 30, 40, 100, 200, 1000};
  double sip_pte_binning[] = {5.0, 5.5, 6.0, 7.0, 8.0, 9.0, 10, 12.5, 15, 20, 30, 40, 100, 200, 1000};
  double iso_pte_binning[] = {5.0, 10, 12.5, 15, 20, 30, 40, 100, 200, 1000};

  TSystemDirectory dir(thePath, thePath);
  TSystemFile *file;
  TString fname;
  TIter next(dir.GetListOfFiles());
  while ((file=(TSystemFile*)next())) {
    fname = file->GetName();
    if (fname.BeginsWith("TnP")) {
      std::cout<<"Processing File :: "<<fname<<std::endl;
      if (fname.Contains("data") || fname.Contains("DATA")) kind = "data";
      else kind = "mc";
      if (fname.Contains("jpsi") || fname.Contains("JPsi")) candle = "JPsi";
      else candle = "Z";
      /*
      bool pass = false;
      for (int p = 0 ; p< nbOfIds ; p++){
	if (fname.Contains(thePlotToDraw[p])) {
	  pass = true;
	  theIndex = p;
	  break;
	}
      }
      if (!(pass)) continue;
      */
      TFile *myFile = new TFile(fname);
      TIter nextkey(myFile->GetListOfKeys());
      TKey *key;
      
      while (key = (TKey*)nextkey()) {
	TString theTypeClasse = key->GetClassName();
	TString theNomClasse = key->GetTitle();
	if ( theTypeClasse == "TDirectoryFile"){
	  TDirectory *theDr = (TDirectory*) myFile->Get(theNomClasse);
	  TIter nextkey2(theDr->GetListOfKeys());
	  TKey *key2;
	  while (key2 = (TKey*)nextkey2()) {
	    TString theTypeClasse2 = key2->GetClassName();
	    TString theNomClasse2 = key2->GetTitle();
	    if ( theTypeClasse == "TDirectoryFile"){
	      TDirectory *theDr2 = (TDirectory*) myFile->Get(theNomClasse+"/"+theNomClasse2);
	      TIter nextkey3(theDr2->GetListOfKeys());
	      TKey *key3;
	      while (key3 = (TKey*)nextkey3()) {
		TString theTypeClasse3 = key3->GetClassName();
		TString theNomClasse3 = key3->GetTitle();
		if (((theNomClasse3.Contains("vpvPlusExpo"))||(theNomClasse3.Contains("gaussPlusExpo")))&&(!(theNomClasse3.Contains("all")))) {
		  TCanvas *theCanvas = (TCanvas*) myFile->Get(theNomClasse+"/"+theNomClasse2+"/"+theNomClasse3+"/fit_canvas");
		  // theCanvas->Print(outputDir+"/"+kind+"_"+theName[theIndex]+"__"+theNomClasse3+".png");
		  if(theCanvas!=0) {
                    // theCanvas->cd();
		    theCanvas->Print(outputDir+"/"+kind+"_"+candle+"_"+theNomClasse2+"__"+theNomClasse3+".png");
		  }
		}
	      }
	    }
	  }
	}
      }
      
      delete myFile;
    }
  }
}
