//============================================================================
// Name        : CMCMCObjectivesReport.cpp
// Author      : A. Dunn
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
//============================================================================

// Headers
#include <boost/lexical_cast.hpp>

#include "CMCMCObjectivesReport.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "../../MCMC/CMCMC.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"

//**********************************************************************
// CMCMCObjectivesReport::CMCMCObjectivesReport()
// Default Constructor
//**********************************************************************
CMCMCObjectivesReport::CMCMCObjectivesReport() {
  // Variables
  eExecutionState     = STATE_FINALIZATION;

}

//**********************************************************************
// void CMCMCObjectivesReport::validate()
// Validate this reporter
//**********************************************************************
void CMCMCObjectivesReport::validate() {
  try {

    // Validate parent
    CFileReport::validate();

    sFileName   = pParameterList->getString(PARAM_FILE_NAME);

  } catch (string &Ex) {
    Ex = "CMCMCObjectivesReport.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMCObjectivesReport::build()
// Build this reporter
//**********************************************************************
void CMCMCObjectivesReport::build() {
  try {
    // Base
    CFileReport::build();

    pMCMC = CMCMC::Instance();

  } catch (string &Ex) {
    Ex = "CMCMCObjectivesReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMCObjectivesReport::execute()
// Execute reporter
//**********************************************************************
void CMCMCObjectivesReport::execute() {
  try {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_MARKOV_CHAIN_MONTE_CARLO)
      return;

    vChain = pMCMC->getMCMCChain();
    ublas::matrix<double> mxCovariance = pMCMC->getCovariance();
    ublas::matrix<double> mxOriginalCovariance = pMCMC->getOriginalCovariance();
    ublas::matrix<double> mxCovarianceLT = pMCMC->getCovarianceLT();
    vector<string> vEstimateNames = pMCMC->getEstimateNames();

    this->start();

    // Print Out
    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";

    cout << "Original " << PARAM_COVARIANCE << " " << PARAM_MATRIX << CONFIG_RATIO_SEPARATOR << endl;
    for(int i=0; i < (int)mxOriginalCovariance.size1(); ++i) {
      for(int j=0; j < (int)mxOriginalCovariance.size2(); ++j) {
        cout << mxOriginalCovariance(i,j) << ((j<(int)mxOriginalCovariance.size2()-1) ? CONFIG_SEPERATOR_ESTIMATE_VALUES : "\n");
      }
    }
    cout << "Proposal distribution " PARAM_COVARIANCE << " " << PARAM_MATRIX << CONFIG_RATIO_SEPARATOR << endl;
    for(int i=0; i < (int)mxCovariance.size1(); ++i) {
      for(int j=0; j < (int)mxCovariance.size2(); ++j) {
        cout << mxCovariance(i,j) << ((j<(int)mxCovariance.size2()-1) ? CONFIG_SEPERATOR_ESTIMATE_VALUES : "\n");
      }
    }
    cout << "Cholesky decomposition " << PARAM_MATRIX << CONFIG_RATIO_SEPARATOR << endl;
    for(int i=0; i < (int)mxCovarianceLT.size1(); ++i) {
      for(int j=0; j < (int)mxCovarianceLT.size2(); ++j) {
        cout << mxCovarianceLT(i,j) << ((j<(int)mxCovarianceLT.size2()-1) ? CONFIG_SEPERATOR_ESTIMATE_VALUES : "\n");
      }
    }

    cout << "MCMC objective function values:\n";
    cout << "iteration, score, penalty, prior, likelihood, acceptance_rate, acceptance_rate_since_adapt, step_size\n";
    for(int i=0; i<(int)vChain.size(); ++i) {
      cout << vChain[i].iIteration << CONFIG_SEPERATOR_ESTIMATE_VALUES << vChain[i].dScore;
      cout << CONFIG_SEPERATOR_ESTIMATE_VALUES << vChain[i].dPenalty << CONFIG_SEPERATOR_ESTIMATE_VALUES;
      cout << vChain[i].dPrior << CONFIG_SEPERATOR_ESTIMATE_VALUES << vChain[i].dLikelihood;
      cout << CONFIG_SEPERATOR_ESTIMATE_VALUES << vChain[i].dAcceptanceRate << CONFIG_SEPERATOR_ESTIMATE_VALUES;
      cout << vChain[i].dAcceptanceRateSinceAdapt << CONFIG_SEPERATOR_ESTIMATE_VALUES << vChain[i].dStepSize << "\n";
    }
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
    Ex = "CMCMCObjectivesReport.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CMCMCObjectivesReport::~CMCMCObjectivesReport()
// Destructor
//**********************************************************************
CMCMCObjectivesReport::~CMCMCObjectivesReport() {
}
