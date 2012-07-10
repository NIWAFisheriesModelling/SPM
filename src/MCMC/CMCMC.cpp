//============================================================================
// Name        : CMCMC.cpp
// Author      : S.Rasmussen
// Date        : 2/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Headers
#include <limits>
#include <numeric>
#include <boost/random.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>

#include "CMCMC.h"
#include "../ObjectiveFunction/CObjectiveFunction.h"
#include "../Estimates/CEstimateManager.h"
#include "../RuntimeThread/CRuntimeThread.h"
#include "../Estimates/CEstimate.h"
#include "../Minimizers/CMinimizerManager.h"
#include "../Minimizers/CMinimizer.h"
#include "../RandomNumberGenerator/CRandomNumberGenerator.h"
#include "../Helpers/ForEach.h"
#include "../Helpers/CComparer.h"
#include "../Helpers/CError.h"

// Namespaces
using namespace boost::numeric;

// Singleton Variable
CMCMC* CMCMC::clInstance = 0;

//**********************************************************************
// CMCMC::CMCMC()
// Default Constructor
//**********************************************************************
CMCMC::CMCMC() {
  // default variables
  iSuccessfulJumps = 0;
  iJumps = 0;

  pParameterList->registerAllowed(PARAM_TYPE);
  pParameterList->registerAllowed(PARAM_START);
  pParameterList->registerAllowed(PARAM_LENGTH);
  pParameterList->registerAllowed(PARAM_KEEP);
  pParameterList->registerAllowed(PARAM_MAX_CORRELATION);
  pParameterList->registerAllowed(PARAM_CORRELATION_ADJUSTMENT_METHOD);
  pParameterList->registerAllowed(PARAM_CORRELATION_ADJUSTMENT_DIFF);
  pParameterList->registerAllowed(PARAM_STEP_SIZE);
  pParameterList->registerAllowed(PARAM_PROPOSAL_DISTRIBUTION);
  pParameterList->registerAllowed(PARAM_DF);
  pParameterList->registerAllowed(PARAM_ADAPT_STEPSIZE_AT);
}

//**********************************************************************
// CMCMC* CMCMC::Instance()
// Instance Method - Singleton
//**********************************************************************
CMCMC* CMCMC::Instance() {
  if (clInstance == 0)
    clInstance = new CMCMC();
  return clInstance;
}

//**********************************************************************
// void CMCMC::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CMCMC::Destroy() {
  if (clInstance != 0) {
    delete clInstance;
    clInstance = 0;
  }
}

//**********************************************************************
// void CMCMC::validate()
// Validate our MCMC
//**********************************************************************
void CMCMC::validate() {
  try {
    // Populate the variables from parameter list
    dStart                  = pParameterList->getDouble(PARAM_START, true, 0.0);
    iLength                 = pParameterList->getInt(PARAM_LENGTH);
    iKeep                   = pParameterList->getInt(PARAM_KEEP, true, 1);
    dMaxCorrelation         = pParameterList->getDouble(PARAM_MAX_CORRELATION, true, 0.8);
    sCorrelationMethod      = pParameterList->getString(PARAM_CORRELATION_ADJUSTMENT_METHOD, true, PARAM_COVARIANCE);
    dCorrelationDiff        = pParameterList->getDouble(PARAM_CORRELATION_ADJUSTMENT_DIFF, true, 0.0001);
    dStepSize               = pParameterList->getDouble(PARAM_STEP_SIZE, true, 0.0);
    sProposalDistribution   = pParameterList->getString(PARAM_PROPOSAL_DISTRIBUTION, true, PARAM_T);
    iDF                     = pParameterList->getInt(PARAM_DF, true, 4);

    if (pParameterList->hasParameter(PARAM_STEP_SIZE)) {
      pParameterList->fillVector(vAdaptStepSize, PARAM_ADAPT_STEPSIZE_AT);
    } else {
      vAdaptStepSize.resize(1);
      vAdaptStepSize[0] = 1;
    }

    // Validate the parameters
    if (iLength < 0)
      CError::errorLessThan(PARAM_LENGTH, PARAM_ZERO);
    if (iKeep < 0)
      CError::errorLessThan(PARAM_KEEP, PARAM_ZERO);
    if (sCorrelationMethod != PARAM_CORRELATION && sCorrelationMethod != PARAM_COVARIANCE)
      CError::errorUnknown(PARAM_CORRELATION_ADJUSTMENT_METHOD, sCorrelationMethod);
    if (sProposalDistribution != PARAM_T && sProposalDistribution != PARAM_NORMAL)
      CError::errorUnknown(PARAM_PROPOSAL_DISTRIBUTION, sProposalDistribution);
    if (dMaxCorrelation <= 0)
      CError::errorLessThan(PARAM_MAX_CORRELATION, PARAM_ZERO);
    if (dMaxCorrelation > 1)
      CError::errorGreaterThan(PARAM_MAX_CORRELATION, PARAM_ONE);
    if (iDF <= 0)
      CError::errorLessThan(PARAM_DF, PARAM_ZERO);
    for(int i = 0; i < (int)vAdaptStepSize.size(); ++i) {
      if (vAdaptStepSize[i] < 1)
        CError::errorLessThan(PARAM_ADAPT_STEPSIZE_AT, PARAM_ONE);
      if (vAdaptStepSize[i] > iLength )
        CError::errorGreaterThan(PARAM_ADAPT_STEPSIZE_AT, PARAM_LENGTH);
    }

  } catch (string &Ex) {
    Ex = "CMCMC.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMC::build()
// Build our MCMC
//**********************************************************************
void CMCMC::build() {
  try {

    // Link to our minimiser
    pMinimizer = CMinimizerManager::Instance()->getMinimizer();

    // Build default step size
    iEstimateCount = CEstimateManager::Instance()->getEnabledEstimateCount();

    if (!pParameterList->hasParameter(PARAM_STEP_SIZE)) {
      dStepSize = 2.4 * pow( (double)iEstimateCount, -0.5);
    } else if ( dStepSize==0.0 ) {
      dStepSize = 2.4 * pow( (double)iEstimateCount, -0.5);
    }

  } catch (string &Ex) {
    Ex = "CMCMC.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMC::execute()
// Execute our MCMC
//**********************************************************************
void CMCMC::execute() {
  try {

    // Build initial covariance matrix
    buildCovarianceMatrix();

    // Setup initial candidate vector
    vCandidates.resize(iEstimateCount);

    for(int i=0; i < iEstimateCount; ++i) {
      vCandidates[i] = CEstimateManager::Instance()->getEnabledEstimate(i)->getValue();
    }

    // Get MCMC starting values
    if (dStart > 0.0 ) {
      generateRandomStart();
      for (int i = 0; i < iEstimateCount; ++i) {
        CEstimateManager::Instance()->getEnabledEstimate(i)->setValue(vCandidates[i]);
      }
    }

    // Get the initial objective function value -> we need to set the value of the estimates here calculated in the lines above
//    CRuntimeThread *pThread = pRuntimeController->getCurrentThread();
//    pThread->rebuild();
//    pThread->startModel();

    // Workout our objective function value
    CObjectiveFunction *pObjectiveFunction = CObjectiveFunction::Instance();
//    pObjectiveFunction->execute();
    double dScore = pObjectiveFunction->getScore();

    //===============================================================
    // Now, do our MCMC
    //===============================================================

    // Iterate over length of MCMC
    for (int i =0; i < iLength; ++i) {
    // Generate a candidate value
      vector<double> vOldCandidates = vCandidates;

      updateStepSize(i);

      generateNewCandidate();
      for (int j = 0; j < iEstimateCount; ++j) {
        CEstimateManager::Instance()->getEnabledEstimate(j)->setValue(vCandidates[j]);
      }

      // Run model with these parameters to get objective function score
      CRuntimeThread *pThread = pRuntimeController->getCurrentThread();
      pThread->rebuild();
      pThread->startModel();
      // Workout our Objective Score
      CObjectiveFunction *pObjectiveFunction = CObjectiveFunction::Instance();
      pObjectiveFunction->execute();

      // Preserve our score for later
      double dOldScore = dScore;
      dScore = pObjectiveFunction->getScore();
      double dRatio = 1.0;

      // Evaluate if the new value is better, and decide whether to jump
      if (dScore >= dOldScore) {
        dRatio = exp(dOldScore - dScore);
      }
      if (CRandomNumberGenerator::Instance()->getRandomUniform_01() < dRatio) {
        // accept the candidate point
        // keep the score, and its compontent parts
        SChainItem newItem;
        newItem.dPenalty    = pObjectiveFunction->getPenalties();
        newItem.dScore      = pObjectiveFunction->getScore();
        newItem.dPrior      = pObjectiveFunction->getPriors();
        newItem.dLikelihood = pObjectiveFunction->getLikelihoods();;
        newItem.vValues     = vCandidates;

        vChain.push_back(newItem);

        iJumps++;
        iSuccessfulJumps++;
      } else {
        // reject the candidate point and reset our Candidate back to what they were
        dScore = dOldScore;
        vCandidates = vOldCandidates;
        iJumps++;
      }
    }
    // Alistair TODO: now we've finished, we need to thin the results so as to keep only 1 in every iKeep value
    //                vMCMC vValues, vPriors, vPenalties, vLikelihoodsvScore

  } catch (string &Ex) {
    Ex = "CMCMC.execute()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMC::generateRandomStart()
// generateRandomStart for our MCMC
//**********************************************************************
void CMCMC::generateRandomStart() {
  try {

    vector<double> vOldCandidates = vCandidates;

    fillMVnorm(dStart);

    int iAttempts = 0;
    bool bCandidatesOk;
    int iEnabledEstimateCount = CEstimateManager::Instance()->getEnabledEstimateCount();

    // Sanity check
    if ((int)vCandidates.size() != iEnabledEstimateCount)
      THROW_EXCEPTION("Candidate vector size d")


    do {
      bCandidatesOk = true;

      iAttempts++;
      if (iAttempts >= 1000)
        CError::errorEqualTo("MCMC start attempts", "1000");
      vCandidates = vOldCandidates;
      fillMVnorm(dStart);

      // Check bounds and regenerate candidates if
      // they are not within the bounds.
      for (int i = 0; i < iEnabledEstimateCount; ++i) {
        CEstimate *estimate = CEstimateManager::Instance()->getEnabledEstimate(i);
        if (estimate->getLowerBound() > vCandidates[i] || estimate->getUpperBound() < vCandidates[i]) {
          bCandidatesOk = false;
          break;
        }
      }

    } while (!bCandidatesOk);

  } catch (string &Ex) {
    Ex = "CMCMC.generateRandomStart()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// bool CMCMC::generateEstimates()
// Generate some estimate values
//**********************************************************************
void CMCMC::generateNewCandidate() {

  try {

    vector<double> vOldCandidates = vCandidates;

    if (sProposalDistribution == PARAM_NORMAL) {
      fillMVnorm(dStepSize);
      int iAttempts = 0;
    // Scott TODO: check that out randomly generated candiates are still within the upper and lower bounds defined by the @estimate blocks
      //while (!vCandidates ! within_bounds() ){  // we need a within_bounds function for our minimiser to carry out this test
        iAttempts++;
        if (iAttempts >= 1000)
          CError::errorEqualTo("MCMC MVNorm attempts", "1000");
        vCandidates = vOldCandidates;
        fillMVnorm(dStepSize);
      //}
    } else {
      fillMVt(dStepSize);
      int iAttempts = 0;
      // Scott TODO: check that out randomly generated candiates are still within the upper and lower bounds defined by the @estimate blocks
      //while (!vCandidates ! within_bounds() ){  // we need a within_bounds function for our minimiser to carry out this test
        iAttempts++;
        if (iAttempts >= 1000)
          CError::errorEqualTo("MCMC MVNorm attempts", "1000");
        vCandidates = vOldCandidates;
        fillMVt(dStepSize);
      //}
    }

  } catch (string &Ex) {
    Ex = "CMCMC.generateRandomStart()->" + Ex;
    throw Ex;
  }
}


//**********************************************************************
// void CMCMC::updateStepSize(int iLength)
// Ypdate stepsize if required
//**********************************************************************
void CMCMC::updateStepSize(int iteration) {

  if(iJumps > 0) {
    for(int i = 0; i < (int)vAdaptStepSize.size(); ++i) {
      if(vAdaptStepSize[i] == iteration ) {
        double dAcceptanceRate = (double)iSuccessfulJumps / (double)iJumps ;
        if (dAcceptanceRate > 0.5) {
          dStepSize *= 2;
          iSuccessfulJumps = 0;
          iJumps = 0;
          break;
        } else if (dAcceptanceRate < 0.2) {
          dStepSize /= 2;
          iSuccessfulJumps = 0;
          iJumps = 0;
          break;
        }
      }
    }
  }
}

//**********************************************************************
// void CMCMC::buildCovarianceMatrix()
// build our Covariance Matrix
//**********************************************************************
void CMCMC::buildCovarianceMatrix() {
  try {

    // Obtain the covariance matrix to use for the proposal distribution
    mxCovariance = pMinimizer->getCovarianceMatrix();

    // Adjust the covariance matrix for the proposal distribution
    for (int i=0; i < (int)mxCovariance.size1(); ++i) {
      for (int j=i+1; j < (int)mxCovariance.size2(); ++j) {
        if (mxCovariance(i,j) / sqrt(mxCovariance(i,j) * mxCovariance(j,j)) > dMaxCorrelation) {
          mxCovariance(i,j) = dMaxCorrelation * sqrt(mxCovariance(i,i) * mxCovariance(j,j));
          mxCovariance(j,i) = mxCovariance(i,j);
        }
        if (mxCovariance(i,j) / sqrt(mxCovariance(i,i) * mxCovariance(j,j)) < -dMaxCorrelation){
          mxCovariance(i,j) = -dMaxCorrelation * sqrt(mxCovariance(i,i) * mxCovariance(j,j));
          mxCovariance(j,i) = mxCovariance(i,j);
        }
      }
    }

    // Adjust any nonzero variances less than min_diff x the difference between the bounds on the parameter.
    // Obtain the estimation bounds to use to modify the covariance matrix
    vector<double> vDiffBounds;
    for (int i = 0; i < CEstimateManager::Instance()->getEnabledEstimateCount(); ++i) {
      CEstimate *estimate = CEstimateManager::Instance()->getEnabledEstimate(i);
      vDiffBounds.push_back( estimate->getUpperBound() - estimate->getLowerBound() );
    }

    //for (int i=0; i < (int)mxCovariance.size1(); ++i) {
    //  if (mxCovariance(i,i) < dCorrelationDiff * vDiffBounds[i] && mxCovariance(i,i) != 0) {
          if (sCorrelationMethod == PARAM_COVARIANCE) {
            //double dMultiplyCovariance = (sqrt(dCorrelationDiff) * vDiffBounds[i]) / sqrt(mxCovariance(i,i));
            //for (int j=0 ; j < (int)mxCovariance.size1(); ++j) {
              //mxCovariance(i,j) = mxCovariance(i,j) * dMultiplyCovariance;
              //mxCovariance(j,i) = mxCovariance(j,i) * dMultiplyCovariance;
            //}
           } else if(sCorrelationMethod == PARAM_CORRELATION) {
             //mxCovariance(i,i) = dCorrelationDiff * vDiffBounds[i];
           }
    //   }
    // }

  } catch (string &Ex) {
    Ex = "CMCMC.buildCovarianceMatrix()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CMCMC:fillMVnorm(double stepsize)
//
//**********************************************************************
void CMCMC::fillMVnorm(double stepsize) {

  // set zero variances to 1 as above
  ublas::matrix<double>  mxTemp = mxCovariance;

  vector<bool> bHasZeroVariances;
  bHasZeroVariances.resize(mxTemp.size1());
  for (int i = 0; i <= (int)mxTemp.size1(); ++i) {
    if ( mxTemp(i,i) == 0 ) {
      mxTemp(i,i) = 1;
      bHasZeroVariances[i] = true;
    } else{
      bHasZeroVariances[i] = false;
    }
  }
  // generate the standard normal random numbers

//  fill_randn(s);
  // get lower triangular part of choleski decomposition of covar
//  dmatrix L(1,n,1,n);
//  if (!chol(covar,L)){
//    error("Failed choleski decomposition in fill_mvnorm");}
//  (*this) = L*(*this) + mean;
  // find the elements with 0 variances and set them to their means
//  for (int i=covar.rowmin(); i<=covar.rowmax(); i++){
//    if (zero_variances[i]){
//      (*this)[i] = mean[i];
//    }
//  }

//+++++++++++++++++++++++++++++++++++++
// Copied from CASAL: Needs work
//+++++++++++++++++++++++++++++++++++++

/*
  // Found a problem here for the case where some variances (and hence the corresponding
  // rows and columns of covar) are 0. The cholesky decomposition does not work in these
  // cases. I thought of this kludge: Set the 0 variances to 1, leaving the covariances at 0.
  // When finished, set the corresponding deviations from the mean to 0.

  // set zero variances to 1 as above
  dvector zero_variances(covar.rowmin(),covar.rowmax());
  zero_variances = 0;
  for (int i=covar.rowmin(); i<=covar.rowmax(); i++){
    if (covar[i][i]==0){
      covar[i][i] = 1;
      zero_variances[i] = 1;
    }
  }
  // generate the standard normal random numbers
  fill_randn(s);
  // get lower triangular part of choleski decomposition of covar
  dmatrix L(1,n,1,n);
  if (!chol(covar,L)){
    error("Failed choleski decomposition in fill_mvnorm");}
  (*this) = L*(*this) + mean;
  // find the elements with 0 variances and set them to their means
  for (int i=covar.rowmin(); i<=covar.rowmax(); i++){
    if (zero_variances[i]){
      (*this)[i] = mean[i];
    }
  }
*/
}

//**********************************************************************
// CMCMC:fillMVt()
//
//**********************************************************************
void CMCMC::fillMVt(double stepsize) {

//+++++++++++++++++++++++++++++++++++++
// Copied from CASAL: Needs work
//+++++++++++++++++++++++++++++++++++++

  // Result is mean + 1/sqrt(y/df) * x,
  // where x ~ multivariate normal(0,_covar)
  // and y ~ chi-square(df).
  // See fill_mvnorm for treatment of zero variances.

//  dvector zeros(mean * 0);
//  fill_mvnorm(s,zeros,_covar);
//  dvector y(1,1);
//  y.fill_chisq(s,df);
//  (*this) *= (1/sqrt(y[1]/df));
//  (*this) += mean;

}

//**********************************************************************
// bool CMCMC::choleskyDecomposition()
//
//**********************************************************************
bool CMCMC::choleskyDecomposition() {

  int n = mxCovariance.size1();

  for (unsigned int i = 0; i < mxCovariance.size1(); ++i)
    for (unsigned int j = 0; j < mxCovariance.size2(); ++j)
      mxCovarianceLT(i,j) = 0.0;

  for (int i = 0; i < n; ++i)
    mxCovarianceLT(i, i) = 1.0;

  if (mxCovariance(0,0) < 0)
    return false;

  double dSum = 0.0;

  mxCovarianceLT(0,0) = sqrt(mxCovariance(0,0));
  for (int i = 1; i < n; ++i) {
    dSum = 0.0;

    for (int j = 0; j < i; ++j)
      dSum += mxCovarianceLT(i,j) * mxCovarianceLT(i,j);

    if (mxCovariance(i,i) <= dSum)
      return false;

    mxCovarianceLT(i,i) = sqrt(mxCovariance(i,i)-dSum);
    for (int j = i+1; j < n; ++j) {
      dSum = 0.0;
      for (int k = 0; k < i; ++k)
        dSum += mxCovarianceLT(j,k) * mxCovarianceLT(i,k);
      mxCovarianceLT(j,i) = (mxCovariance(j,i)-dSum)/mxCovarianceLT(i,i);
    }
  }

  dSum = 0.0;
  for (int i = 0; i < (n-1); ++i)
    dSum += mxCovarianceLT(n,i) * mxCovarianceLT(n,i);
  if (mxCovariance(n,n) <= dSum)
    return false;
  mxCovarianceLT(n,n) = sqrt(mxCovariance(n,n) - dSum);

  return true;
}

//**********************************************************************
// CMCMC::~CMCMC()
// Default De-Constructor
//**********************************************************************
CMCMC::~CMCMC() {
}
