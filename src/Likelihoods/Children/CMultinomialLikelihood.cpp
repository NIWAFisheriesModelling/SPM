//============================================================================
// Name        : CMultinomialLikelihood.cpp
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <cmath>

// Local headers
#include "CMultinomialLikelihood.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CMultinomialLikelihood::CMultinomialLikelihood()
// Default Constructor
//**********************************************************************
CMultinomialLikelihood::CMultinomialLikelihood() {
}

//**********************************************************************
// double CMultinomialLikelihood::adjustErrorValue(const double processError, const double errorValue)
// Adjust error value based on process error
//**********************************************************************
double CMultinomialLikelihood::adjustErrorValue(const double processError, const double errorValue) {
  // adjust for N process error
  if( (errorValue > 0.0) && (processError > 0.0) )
    return (1.0/(1.0/errorValue + 1.0/processError));

  return errorValue;
}
//**********************************************************************
// void CMultinomialLikelihood::getResult(vector<double> &scores, const vector<double> &expected, const vector<double> &observed,
//    const vector<double> &errorValue, const vector<double> &processError, const double delta)
// Get the result from our likelihood for the observation
//**********************************************************************
void CMultinomialLikelihood::getResult(vector<double> &scores, const vector<double> &expected, const vector<double> &observed,
    const vector<double> &errorValue, const vector<double> &processError, const double delta) {

  // Loop through expected
  for (int i = 0; i < (int)expected.size(); ++i) {
    // Calculate score
    double dErrorValue = adjustErrorValue(processError[i], errorValue[i]);
    double dScore      = CMath::lnFactorial(dErrorValue * observed[i])
                         - dErrorValue * observed[i] * log(CMath::zeroFun(expected[i],delta));

    scores.push_back(dScore);
  }
}

//**********************************************************************
// void CMultinomialLikelihood::simulateObserved(const vector<string> &keys, vector<double> &observed,
//    const vector<double> &expected, const vector<double> &errorValue, const vector<double> &processError, const double delta)
// Simulate observed value for our observation
//**********************************************************************
void CMultinomialLikelihood::simulateObserved(const vector<string> &keys, vector<double> &observed,
    const vector<double> &expected, const vector<double> &errorValue, const vector<double> &processError, const double delta) {

  // instance the random number generator
  CRandomNumberGenerator *pRandom = CRandomNumberGenerator::Instance();

  map<string, double> mTotals;

  // Loop through our expected values
  for (int i = 0; i < (int)expected.size(); ++i) {

    // Check for invalid values
    if (errorValue[i] < 0.0)
      CError::errorLessThan(PARAM_ERROR_VALUE, PARAM_ZERO);

    // Add in process error
    double dN = ceil(adjustErrorValue(processError[i], errorValue[i]));

    // Deal with zeros
    if (expected[i] <= 0.0 || dN <=0.0) {
      observed[i] = 0.0;
    } else {
    // Calculate observed number
      observed[i] = pRandom->getRandomBinomial(expected[i], dN);
      mTotals[keys[i]] += observed[i];
    }
  }

  for (unsigned i = 0; i < expected.size(); ++i)
    observed[i] /= mTotals[keys[i]];
}

//**********************************************************************
// double CMultinomialLikelihood::getInitialScore(const vector<string> &keys, const vector<double> &processError,
//    const vector<double> &errorValue) {
// Get Initial Score
//**********************************************************************
double CMultinomialLikelihood::getInitialScore(const vector<string> &keys, const vector<double> &expected, const vector<double> &observed,
                                               const vector<double> &processError, const vector<double> &errorValue, const double delta) {

  double dScore   = 0.0;
  string sLastKey = "";

  for (int i = 0; i < (int)keys.size(); ++i) {
    // Only once per key
    if (keys[i] == sLastKey)
      continue;

    dScore    += -CMath::lnFactorial(adjustErrorValue(processError[i], errorValue[i]));
    sLastKey  = keys[i];
  }

  return dScore;
}

//**********************************************************************
// CMultinomialLikelihood::~CMultinomialLikelihood()
// Destructor
//**********************************************************************
CMultinomialLikelihood::~CMultinomialLikelihood() {
}
