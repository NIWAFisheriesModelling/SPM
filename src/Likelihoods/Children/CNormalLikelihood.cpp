//============================================================================
// Name        : CNormalLikelihood.cpp
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CNormalLikelihood.h"
#include "../../Helpers/CMath.h"

//**********************************************************************
// CNormalLikelihood::CNormalLikelihood()
// Default Constructor
//**********************************************************************
CNormalLikelihood::CNormalLikelihood() {
}

//**********************************************************************
// double CNormalLikelihood::adjustErrorValue(double processError, double errorValue)
// Adjust our error value based on process error.
//**********************************************************************
double CNormalLikelihood::adjustErrorValue(double processError, double errorValue) {
  // adjust for c.v. process error
  if(processError > 0.0)
    return (sqrt(errorValue*errorValue + processError*processError));

  return errorValue;
}

//**********************************************************************
// double CNormalLikelihood::getResult(double expected, double observed, double errorValue,
//                                                            double processError, double delta)
// Get result from likelihood for our observation
//**********************************************************************
void CNormalLikelihood::getResult(vector<double> &scores, vector<double> &expected, vector<double> &observed,
    vector<double> &errorValue, vector<double> &processError, double delta) {

  // Loop through expected
  for (int i = 0; i < (int)expected.size(); ++i) {
    // Calculate score
    double dErrorValue  = adjustErrorValue(processError[i], errorValue[i]);
    double dSigma       = dErrorValue*expected[i];
    double dScore       = (observed[i]-expected[i]) / CMath::zeroFun(dErrorValue*expected[i],delta);
    dScore              = log(dSigma) + 0.5 * (dScore * dScore);

    scores.push_back(dScore);
  }
}

//**********************************************************************
// double CNormalLikelihood::simulateObserved(double expected, double errorValue, double processError, double delta)
// Simulate observed value for our observation
//**********************************************************************
void CNormalLikelihood::simulateObserved(vector<double> &observed, vector<double> &expected, vector<double> &errorValue,
    vector<double> &processError, double delta) {

  // Variables
  CRandomNumberGenerator *pRandom = CRandomNumberGenerator::Instance();

  observed.clear();

  // Loop through expected
  for (int i = 0; i < (int)expected.size(); ++i) {
    // Check expected
    if(expected[i] <= 0.0) {
      observed.push_back(0.0);
      continue;
    }

    // Calculate observed
    double dErrorValue = adjustErrorValue(processError[i], errorValue[i]);
    double dObserved   = pRandom->getRandomNormal(expected[i], (expected[i]*dErrorValue));

    observed.push_back(dObserved);
  }
}

//**********************************************************************
// CNormalLikelihood::~CNormalLikelihood()
// Destructor
//**********************************************************************
CNormalLikelihood::~CNormalLikelihood() {
}
