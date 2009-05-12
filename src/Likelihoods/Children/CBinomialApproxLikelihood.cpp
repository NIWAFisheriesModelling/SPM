//============================================================================
// Name        : CBinomialApproxLikelihood.cpp
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CBinomialApproxLikelihood.h"
#include "../../Helpers/CMath.h"

//**********************************************************************
// CBinomialApproxLikelihood::CBinomialApproxLikelihood()
// Default Constructor
//**********************************************************************
CBinomialApproxLikelihood::CBinomialApproxLikelihood() {
}

//**********************************************************************
// double CBinomialApproxLikelihood::adjustErrorValue(double processError, double errorValue)
// Adjust our error value based on process error
//**********************************************************************
double CBinomialApproxLikelihood::adjustErrorValue(double processError, double errorValue) {
  // adjust for N process error
  if( (errorValue > 0.0) && (processError > 0.0) )
    return (1.0/(1.0/errorValue + 1.0/processError));

  return errorValue;
}

//**********************************************************************
// void CBinomialApproxLikelihood::getResult(vector<double> &scores, vector<double> &expected, vector<double> &observed,
//    vector<double> &errorValue, vector<double> &processError, double delta)
// Get the result from our likelihood
//**********************************************************************
void CBinomialApproxLikelihood::getResult(vector<double> &scores, vector<double> &expected, vector<double> &observed,
    vector<double> &errorValue, vector<double> &processError, double delta) {

  // Loop through expected values
  for (int i = 0; i < (int)expected.size(); ++i) {
    // Calculate Scores
    double dErrorValue  = adjustErrorValue(processError[i], errorValue[i]);
    double dStdError    = sqrt((CMath::zeroFun(expected[i],delta) * CMath::zeroFun(1.0-expected[i],delta))/dErrorValue);
    double dScore       = log(dStdError) + 0.5 * pow((observed[i] - expected[i])/dStdError,2.0);

    scores.push_back(dScore);
  }
}

//**********************************************************************
// double CBinomialApproxLikelihood::simulateObserved(double expected, double errorValue, double processError, double delta)
// Simulate observed value from our observation
//**********************************************************************
void CBinomialApproxLikelihood::simulateObserved(vector<double> &observed, vector<double> &expected, vector<double> &errorValue,
    vector<double> &processError, double delta) {

  // Variables
  CRandomNumberGenerator *pRandom = CRandomNumberGenerator::Instance();

  observed.clear();

  // Loop through our expected values
  for (int i = 0; i < (int)expected.size(); ++i) {
    // Check for invalid values
    if (expected[i] < 0.0) {
      observed.push_back(0.0);
      continue;
    }

    // Calculate Observed
    double dErrorValue = adjustErrorValue(processError[i], errorValue[i]);
    double dObserved = pRandom->getRandomBinomial(expected[i], dErrorValue);

    observed.push_back(dObserved);
  }
}

//**********************************************************************
// CBinomialApproxLikelihood::~CBinomialApproxLikelihood()
// Destructor
//**********************************************************************
CBinomialApproxLikelihood::~CBinomialApproxLikelihood() {
}
