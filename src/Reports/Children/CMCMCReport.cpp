//============================================================================
// Name        : CMCMCReport.cpp
// Author      : S.Rasmussen
// Date        : 26/05/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Headers
#include <boost/lexical_cast.hpp>

#include "CMCMCReport.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "../../MCMC/CMCMC.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"

//**********************************************************************
// CMCMCReport::CMCMCReport()
// Default Constructor
//**********************************************************************
CMCMCReport::CMCMCReport() {
  // Variables
  eExecutionState     = STATE_FINALIZATION;

}

//**********************************************************************
// void CMCMCReport::validate()
// Validate this reporter
//**********************************************************************
void CMCMCReport::validate() {
  try {

    // Validate parent
    CFileReport::validate();

  } catch (string &Ex) {
    Ex = "CMCMCReport.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMCReport::build()
// Build this reporter
//**********************************************************************
void CMCMCReport::build() {
  try {
    // Base
    CFileReport::build();

    pMCMC = CMCMC::Instance();

  } catch (string &Ex) {
    Ex = "CMCMCReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMCReport::execute()
// Execute reporter
//**********************************************************************
void CMCMCReport::execute() {
  try {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_MARKOV_CHAIN_MONTE_CARLO)
      return;

    vChain = pMCMC->getMCMCChain();
    ublas::matrix<double> mxCovariance = pMCMC->getCovariance();
    ublas::matrix<double> mxOriginalCovariance = pMCMC->getOriginalCovariance();
    vector<string> vEstimateNames = pMCMC->getEstimateNames();

    this->start();

    // Print Out
    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";

    cout << "Original " << PARAM_COVARIANCE << " matrix:\n";
    for(int i=0; i < (int)mxOriginalCovariance.size1(); ++i) {
      for(int j=0; j < (int)mxOriginalCovariance.size2(); ++j) {
        cout << mxOriginalCovariance(i,j) << ",";
      }
      cout << "\n";
    }
    cout << "Proposal distribution " PARAM_COVARIANCE << " matrix:\n";
    for(int i=0; i < (int)mxCovariance.size1(); ++i) {
      for(int j=0; j < (int)mxCovariance.size2(); ++j) {
        cout << mxCovariance(i,j) << ",";
      }
      cout << "\n";
    }

    cout << "MCMC objective function values:\n";
    cout << "iteration, score, penalty, prior, likelihood, acceptance_rate, step_size\n";
    for(int i=0; i<(int)vChain.size(); ++i) {
      cout << vChain[i].iIteration << ", " << vChain[i].dScore << ", " << vChain[i].dPenalty << ", " << vChain[i].dPrior << ", " << vChain[i].dLikelihood << ", " << vChain[i].dAcceptanceRate << ", " << vChain[i].dStepSize << "\n";
    }
    cout << "MCMC samples:\n";
    for (int i =0; i < (int)vEstimateNames.size(); ++i ) {
      cout << vEstimateNames[i] << ", ";
    }
    cout << "\n";
    for(int i=0; i<(int)vChain.size(); ++i) {
      for(int j=0; j < (int)vChain[i].vValues.size(); ++j) {
        cout << vChain[i].vValues[j] << ", ";
      }
      cout << "\n";
    }

    cout << CONFIG_END_REPORT << "\n" << endl;

    this->end();

  } catch (string &Ex) {
    Ex = "CMCMCReport.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}


//**********************************************************************
// CMCMCReport::~CMCMCReport()
// Destructor
//**********************************************************************
CMCMCReport::~CMCMCReport() {
}
