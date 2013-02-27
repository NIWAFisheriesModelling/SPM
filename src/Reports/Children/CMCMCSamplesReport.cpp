//============================================================================
// Name        : CMCMCSamplesReport.cpp
// Author      : A. Dunn
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
//============================================================================

// Headers
#include <boost/lexical_cast.hpp>

#include "CMCMCSamplesReport.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "../../MCMC/CMCMC.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"

//**********************************************************************
// CMCMCSamplesReport::CMCMCSamplesReport()
// Default Constructor
//**********************************************************************
CMCMCSamplesReport::CMCMCSamplesReport() {
  // Variables
  eExecutionState     = STATE_FINALIZATION;
  //bWrittenHeader  = false;

}

//**********************************************************************
// void CMCMCSamplesReport::validate()
// Validate this reporter
//**********************************************************************
void CMCMCSamplesReport::validate() {
  try {

    // Validate parent
    CFileReport::validate();

  } catch (string &Ex) {
    Ex = "CMCMCSamplesReport.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMCSamplesReport::build()
// Build this reporter
//**********************************************************************
void CMCMCSamplesReport::build() {
  try {
    // Base
    CFileReport::build();

    pMCMC = CMCMC::Instance();

  } catch (string &Ex) {
    Ex = "CMCMCSamplesReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMCSamplesReport::execute()
// Execute reporter
//**********************************************************************
void CMCMCSamplesReport::execute() {
  try {

    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_MARKOV_CHAIN_MONTE_CARLO)
      return;

//    if ( (sFileName != "") && (!bOverwrite) ) {
//      struct stat stFileInfo;
//      int intStat = stat(sFileName.c_str(),&stFileInfo);
//
//      if (intStat == 0) // File Exists
//        bWrittenHeader = true; // Don't write the header
//    }



    vChain = pMCMC->getMCMCChain();
    ublas::matrix<double> mxCovariance = pMCMC->getCovariance();
    ublas::matrix<double> mxOriginalCovariance = pMCMC->getOriginalCovariance();
    ublas::matrix<double> mxCovarianceLT = pMCMC->getCovarianceLT();
    vector<string> vEstimateNames = pMCMC->getEstimateNames();

    this->start();

    // Print Out
    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";

    cout << "MCMC samples:\n";
    for (int i =0; i < (int)vEstimateNames.size(); ++i ) {
      cout << vEstimateNames[i] << ((i<(int)vEstimateNames.size()-1) ? CONFIG_SEPERATOR_ESTIMATE_VALUES : "\n");
    }
    for(int i=0; i<(int)vChain.size(); ++i) {
      for(int j=0; j < (int)vChain[i].vValues.size(); ++j) {
        cout << vChain[i].vValues[j] << ((j<(int)vChain[i].vValues.size()-1) ? CONFIG_SEPERATOR_ESTIMATE_VALUES : "\n");
      }
    }

    cout << CONFIG_END_REPORT << "\n" << endl;

    this->end();

  } catch (string &Ex) {
    Ex = "CMCMCSamplesReport.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CMCMCSamplesReport::~CMCMCSamplesReport()
// Destructor
//**********************************************************************
CMCMCSamplesReport::~CMCMCSamplesReport() {
}
