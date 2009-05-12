//============================================================================
// Name        : CLogNormalLikelihood.cpp
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CLogNormalLikelihood.h"
#include "../../Helpers/CMath.h"

//**********************************************************************
// CLogNormalLikelihood::CLogNormalLikelihood()
// Default Constructor
//**********************************************************************
CLogNormalLikelihood::CLogNormalLikelihood() {

}

//**********************************************************************
// double CLogNormalLikelihood::adjustErrorValue(double processError, double errorValue)
// Adjust our error value based on process error
//**********************************************************************
double CLogNormalLikelihood::adjustErrorValue(double processError, double errorValue) {
  // adjust for c.v. process error
  if(processError > 0.0)
    return (sqrt(errorValue*errorValue + processError*processError));

  return errorValue;
}

//**********************************************************************
// void CLogNormalLikelihood::getResult(vector<double> &scores, vector<double> &expected, vector<double> &observed,
//     vector<double> &errorValue, vector<double> &processError, double delta)
// Get the result from our likelihood for the observation
//**********************************************************************
void CLogNormalLikelihood::getResult(vector<double> &scores, vector<double> &expected, vector<double> &observed,
    vector<double> &errorValue, vector<double> &processError, double delta) {

  // Loop through expected
  for (int i = 0; i < (int)expected.size(); ++i) {
    // Calculate Result
    double dErrorValue = adjustErrorValue(processError[i], errorValue[i]);
    double dSigma = sqrt(log(1+ dErrorValue*dErrorValue));
    double dScore = log(observed[i] / CMath::zeroFun(expected[i],delta)) / dSigma + 0.5*dSigma;
    dScore        = log(dSigma) + 0.5 * dScore * dScore;

    scores.push_back(dScore);
  }
}

//**********************************************************************
// void CLogNormalLikelihood::simulateObserved(vector<double> &observed, vector<double> &expected, vector<double> &errorValue,
//     vector<double> &processError, double delta)
// Simulate an observed value from our expected
//**********************************************************************
void CLogNormalLikelihood::simulateObserved(vector<double> &observed, vector<double> &expected, vector<double> &errorValue,
    vector<double> &processError, double delta) {

  // Variables
  CRandomNumberGenerator *pRandom = CRandomNumberGenerator::Instance();

  observed.clear();

  // Loop through expected
  for (int i = 0; i < (int)expected.size(); ++i) {

    // Should never happen ...
    if (expected[i] <= 0.0) {
      observed.push_back(0.0);
      continue;
    }

    // Calculate Score
    double dErrorValue  = adjustErrorValue(processError[i], errorValue[i]);
    double dObserved    = pRandom->getRandomLogNormal(expected[i], dErrorValue);

    observed.push_back(dObserved);
  }
}

//**********************************************************************
// CLogNormalLikelihood::~CLogNormalLikelihood()
// Destructor
//**********************************************************************
CLogNormalLikelihood::~CLogNormalLikelihood() {
}
