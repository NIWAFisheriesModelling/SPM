//============================================================================
// Name        : CMCMC.cpp
// Author      : S.Rasmussen
// Date        : 2/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Global Headers
#include <boost/random.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>

// Local Headers
#include "CMCMC.h"
#include "../ObjectiveFunction/CObjectiveFunction.h"
#include "../CEstimateManager.h"
#include "../RuntimeThread/CRuntimeThread.h"
#include "../Estimates/CEstimate.h"
#include "../CMinimizerManager.h"
#include "../Minimizers/CMinimizer.h"

// Namespaces
using namespace boost::numeric;

// Singleton Variable
CMCMC* CMCMC::clInstance = 0;

//**********************************************************************
// CMCMC::CMCMC()
// Default Constructor
//**********************************************************************
CMCMC::CMCMC() {
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
// void CMCMC::addThread(CRuntimeThread *Thread)
// Add Thread
//**********************************************************************
void CMCMC::addThread(CRuntimeThread *Thread) {
  lock lk(mutThread);
  vThreadList.push_back(Thread);
}

//**********************************************************************
// void CMCMC::addAdaptAt(int value)
// Add AdaptAt
//**********************************************************************
void CMCMC::addAdaptAt(int value) {
  vAdaptAtList.push_back(value);
}

//**********************************************************************
// void CMCMC::validate()
// Validate our MCMC
//**********************************************************************
void CMCMC::validate() {
  try {

  } catch (string Ex) {
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

  } catch (string Ex) {
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
    // Variables
    int iEstimateCount      = CEstimateManager::Instance()->getEnabledEstimateCount();
    int iThreadCount        = pConfig->getNumberOfThreads();
    int iThreadListSize     = 0;

    // Build the Covariance Matrix
    buildCovarianceMatrix();

    // Wait until all threads have subscribed.
    while (iThreadListSize != iThreadCount) {
      if (true) {
        lock lk(mutThread);
        iThreadListSize = (int)vThreadList.size();
      }
      sleep(1);
    }

    // Resize Vector for Generating our estimates
    vCandidates.resize(iEstimateCount);

    // Start MCMC
    for (int i = 0; i < iLength; ++i) {

      foreach(CRuntimeThread *Thread, vThreadList) {
        // Get Handle to target thread's estimate manager
        CEstimateManager *pEstimateManager = Thread->getEstimateManager();

        // Generate new Vars
        generateEstimates();

        for (int j = 0; j < iEstimateCount; ++j)
          pEstimateManager->getEstimate(j)->setValue(vCandidates[i]);

        // Un-"Wait" thread
        Thread->setWaiting(false);
      }

      // Wait until all threads are "Waiting"
      foreach(CRuntimeThread *Thread, vThreadList) {
        while(!Thread->getWaiting())
          sleep(1);
      }

      // Work Through and Look For our Match
      /*foreach(CRuntimeThread *Thread, vThreadList) {
        // Print Thread to PrintState
        PrintState->print(thread);
        // Check if We want
        if ( ((Thread->getScore() < dBestScore) || (Thread->getScore() < randomScore)) && (i < iLength) ) {
          bestScore = Thread->getVariables();
          break;
        } else if (i >= iLength)
          break;

        ++i;
      }*/
    }

    // Terminate Threads
    foreach(CRuntimeThread *Thread, vThreadList) {
      Thread->setTerminate(true);
    }

  } catch (string Ex) {
   Ex = "CMCMC.execute()->" + Ex;
   throw Ex;
  }
}


//**********************************************************************
// bool CMCMC::generateEstimates()
// Generate some estimate values
//**********************************************************************
bool CMCMC::generateEstimates() {

  int iSize = mxCovariance.size1();

  ublas::matrix<double> mxCovarianceTemp(mxCovariance);
  vector<int> vZeros(iSize);

  for (int i = 0; i < iSize; ++i)
    vZeros[i] = 0;

  // Make the 0 Covariances because they cause
  // The cholesky to fail.
  for (int i = 0; i < iSize; ++i)
    if (isZero(mxCovariance(i,i))) {
      mxCovarianceTemp(i,i) = 1.0;
      vZeros[i] = 1;
    }

  // generate the standard normal random numbers
  //fill_randn(s);
  if (!choleskyDecomposition())
    return false;

  //for (int i = 0; i < iSize; ++i)
    //vCandidates *= mxCovarianceLT(i,i) + dMean;

  // Reset our 0 Co-Variances
  for (int i = 0; i < iSize; ++i)
    if (vZeros[i] == 1)
      vCandidates[i] = 0.0; // mean[i]

  return true;
}

//**********************************************************************
//
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
// void CMCMC::buildCovarianceMatrix()
// Build the Co-Variance Matrix
//**********************************************************************
void CMCMC::buildCovarianceMatrix() {
  // Variables
  int iEstimateCount      = CEstimateManager::Instance()->getEnabledEstimateCount();

  // Get handle to our Minimizer and Hessian
  CMinimizerManager *pMinimizerManager = CMinimizerManager::Instance();
  CMinimizer *pMinimizer  = pMinimizerManager->getMinimizer();

  ublas::matrix<double> mxHessian(iEstimateCount, iEstimateCount);
  for (int i = 0; i < iEstimateCount; ++i)
    for (int j = 0; j < iEstimateCount; ++j)
      mxHessian(i,j) = pMinimizer->getHessianValue(i, j);

  // Convert Hessian to Covariance
  ublas::permutation_matrix<> pm(mxHessian.size1());
  ublas::matrix<double> copiedMatrix = ublas::matrix<double>(mxHessian);
  ublas::lu_factorize(copiedMatrix,pm);

  ublas::matrix<double> identityMatrix(ublas::identity_matrix<double>(copiedMatrix.size1()));
  ublas::lu_substitute(copiedMatrix,pm,identityMatrix);

  mxCovariance.swap(identityMatrix);
}

//**********************************************************************
// void CMCMC::sleep(int time)
// Platform-Independent Sleep
//**********************************************************************
void CMCMC::sleep(int milliseconds) {
#ifdef __MINGW32__
  Sleep(milliseconds);
#else
  usleep( milliseconds * 1000);
#endif
}

//**********************************************************************
// CMCMC::~CMCMC()
// Default De-Constructor
//**********************************************************************
CMCMC::~CMCMC() {
  vThreadList.clear();
}
