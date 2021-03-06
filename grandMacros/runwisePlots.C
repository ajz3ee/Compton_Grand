#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TString.h"
#include "TMath.h"
#include "TF1.h"
#include "THStack.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "../buildGrandRootfile.h"
#include "makePlots.h"

#include <vector>
#include <string>
#include <fstream>
#include <istream>

using namespace std;

void runwisePlots(Int_t prexOrCrex){
  TString expt = experimentCode(prexOrCrex);
  TString fname = Form("%sGrandCompton.root", expt.Data());
  const Int_t nPolVars = 6;
  const Int_t nDataVars = 22;
  const Int_t nOthVars = 8;
  TString polVars[nPolVars] = {"Pol0", "Asym0", "Asym0LasOff", "Pol0", "Asym0", "Asym0LasOff"};
  TString dataVars[nDataVars] = {"Acc0LasOn", "Acc0LasOff", "Acc0BeamOff", "Acc4LasOn", "Acc4LasOff", "Acc4BeamOff",
                                 "LaserPower", "BeamCurrent", "bpmAx", "bpmAy", "bpmBx", "bpmBy", 
                                 "CentralRateLasOn", "CentralRateLasOff", "USbg1", "USbg2", "DSbg1", "DSbg2",
                                 "HFingerLasOn", "HFingerLasOff", "VFingerLasOn", "VFingerLasOff"};
  TString othVars[nOthVars] = {"runTime", "numCycles", "tablePosX", "tablePosY",
                               "qw1", "hw1", "qw2", "targetPos"};
  Float_t polYmins[nPolVars] = {0.99, 0.99, 0.99, 0.9, 0.9, 0.9};
  Float_t polYmaxs[nPolVars] = {1.01, 1.01, 1.01, 1.1, 1.1, 1.1};
  Bool_t polSign[nPolVars] = {true, true, true, false, false, false};
  Bool_t othFloat[nOthVars] = {true, false, true, true, true, true, true, true};

  Int_t msmtNum = 0;
  for(Int_t i = 0; i < nPolVars; i++){
    plotPolRun(fname.Data(), polVars[i].Data(), msmtNum++, polYmins[i], polYmaxs[i], polSign[i]);
  }
  plotPolRun(fname.Data(), "Pol0", msmtNum++, 0.0, 1.1, false, true);
  plotPolRun(fname.Data(), "Asym0LasOff", msmtNum++, 0.0, 1.1, false, true);
  for(Int_t i = 0; i < nDataVars; i++){
    plotStandardRun(fname.Data(), dataVars[i].Data(), msmtNum++, 0.9, 1.1, true);
  }
  for(Int_t i = 0; i < nOthVars; i++){
    plotStandardRun(fname.Data(), othVars[i].Data(), msmtNum++, 0.9, 1.1, othFloat[i]);
  }

  gSystem->Exec(Form("pdfunite %s/plots/msmt*.pdf %s/aggregates/%sGrandRunwise.pdf", 
                getenv("COMPMON_GRAND"), getenv("COMPMON_WEB"), expt.Data()));
  gSystem->Exec(Form("rm -f %s/plots/msmt*.pdf", getenv("COMPMON_GRAND")));
}
