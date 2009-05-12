//============================================================================
// Name        : CBinomialLikelihood.cpp
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <cmath>

// Local headers
#include "CBinomialLikelihood.h"
#include "../../Helpers/CMath.h"

//**********************************************************************
// CBinomialLikelihood::CBinomialLikelihood()
// Default Constructor
//**********************************************************************
CBinomialLikelihood::CBinomialLikelihood() {
}

//**********************************************************************
// double CBinomialLikelihood::adjustErrorValue(double processError, double errorValue)
// Adjust our ErrorValue based on process error
//**********************************************************************
double CBinomialLikelihood::adjustErrorValue(double processError, double errorValue) {
  // adjust for N process error
  if( (errorValue > 0.0) && (processError > 0.0) )
    return (1.0/(1.0/errorValue + 1.0/processError));

  return errorValue;
}

//**********************************************************************
// void CBinomialLikelihood::getResult(vector<double> &scores, vector<double> &expected, vector<double> &observed,
//     vector<double> &errorValue, vector<double> &processError, double delta)
// Calculate the Result of this Likelihood
//**********************************************************************
void CBinomialLikelihood::getResult(vector<double> &scores, vector<double> &expected, vector<double> &observed,
    vector<double> &errorValue, vector<double> &processError, double delta) {

  // Loop through expected values
  for (int i = 0; i < (int)expected.size(); ++i) {
    // Calculate Result
    double dErrorValue  = adjustErrorValue(processError[i], errorValue[i]);
    double dScore       = CMath::lnFactorial(dErrorValue)
                           - CMath::lnFactorial(dErrorValue * (1.0 - observed[i]))
                           - CMath::lnFactorial(dErrorValue * observed[i])
                           + dErrorValue * observed[i] * log(CMath::zeroFun(expected[i], delta))
                           + dErrorValue * (1.0 - observed[i]) * log(CMath::zeroFun(1.0 - expected[i], delta));

    scores.push_back(-dScore);
  }
}

//**********************************************************************
// void CBinomialLikelihood::simulateObserved(vector<double> &observed, vector<double> &expected, vector<double> &errorValue,
//     vector<double> &processError, double delta)
// Simulate our Observed values
//**********************************************************************
void CBinomialLikelihood::simulateObserved(vector<double> &observed, vector<double> &expected, vector<double> &errorValue,
    vector<double> &processError, double delta) {

  // Variables
  CRandomNumberGenerator *pRandom = CRandomNumberGenerator::Instance();

  observed.clear();

  // Loop through expected
  for (int i = 0; i < (int)expected.size(); ++i) {
    // Check for valid expected
    if (expected[i] < 0.0) {
      observed.push_back(0.0);
      continue;
    }

    // Calculate Result
    errorValue[i] = adjustErrorValue(processError[i], errorValue[i]);
    double dObserved    = pRandom->getRandomBinomial(expected[i], errorValue[i]);

    observed.push_back(dObserved);
  }
}

//**********************************************************************
// CBinomialLikelihood::~CBinomialLikelihood()
// Destructor
//**********************************************************************
CBinomialLikelihood::~CBinomialLikelihood() {
}
