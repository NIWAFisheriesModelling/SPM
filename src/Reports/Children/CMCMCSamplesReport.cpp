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
  bWrittenHeader  = false;

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
    if (pRuntimeController->getRunMode() != RUN_MODE_MONTE_CARLO_MARKOV_CHAIN)
      return;

    vChain = pMCMC->getMCMCChain();

    this->start();

    // Print Out
    if(!bWrittenHeader) {
      cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
      cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";

      cout << PARAM_MCMC_SAMPLES << CONFIG_RATIO_SEPARATOR << "\n";
      vector<string> vEstimateNames = pMCMC->getEstimateNames();
      for (int i =0; i < (int)vEstimateNames.size(); ++i ) {
        cout << vEstimateNames[i] << ((i<(int)vEstimateNames.size()-1) ? CONFIG_SEPERATOR_ESTIMATE_VALUES : "\n");
      }
      bWrittenHeader = true;
    }

    //Print out the most recent set of numbers
    int iN = vChain.size()-1;
    for(int j=0; j < (int)vChain[iN].vValues.size(); ++j) {
      cout << vChain[iN].vValues[j] << ((j<(int)vChain[iN].vValues.size()-1) ? CONFIG_SEPERATOR_ESTIMATE_VALUES : "\n");
    }

    if( iN == pMCMC->getNSamples() ) {
      cout << CONFIG_END_REPORT << "\n" << endl;
    }

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
