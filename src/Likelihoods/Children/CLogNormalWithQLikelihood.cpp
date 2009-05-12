//============================================================================
// Name        : CLogNormalWithQLikelihood.cpp
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <cmath>

// Local headers
#include "CLogNormalWithQLikelihood.h"
#include "../../Helpers/CMath.h"

//**********************************************************************
// CLogNormalWithQLikelihood::CLogNormalWithQLikelihood()
// Default Constructor
//**********************************************************************
CLogNormalWithQLikelihood::CLogNormalWithQLikelihood() {
}

//**********************************************************************
// double CLogNormalWithQLikelihood::adjustErrorValue(double processError, double errorValue)
// Adjust our ErrorValue based on Process Error
//**********************************************************************
double CLogNormalWithQLikelihood::adjustErrorValue(double processError, double errorValue) {
  // adjust for c.v. process error
  if(processError > 0.0)
    return (sqrt(errorValue*errorValue + processError*processError));

  return errorValue;
}

//**********************************************************************
// void CLogNormalWithQLikelihood::getResult(vector<double> &scores, vector<double> &expected, vector<double> &observed,
//     vector<double> &errorValue, vector<double> &processError, double delta)
// Get the result from our likelihood for the observation
//**********************************************************************
void CLogNormalWithQLikelihood::getResult(vector<double> &scores, vector<double> &expected, vector<double> &observed,
    vector<double> &errorValue, vector<double> &processError, double delta) {

  // Loop through expected
  for (int i = 0; i < (int)expected.size(); ++i) {
    // Calculate score
    double dErrorValue  = adjustErrorValue(processError[i], errorValue[i]);
    double dSigma       = sqrt(log(1+ dErrorValue*dErrorValue));
    double dScore       = log(observed[i] / CMath::zeroFun(expected[i],delta)) / dSigma + 0.5*dSigma;
    dScore              = log(dSigma) + 0.5 * (dScore * dScore);

    scores.push_back(dScore);
  }
}

//**********************************************************************
// void CLogNormalWithQLikelihood::simulateObserved(vector<double> &observed, vector<double> &expected, vector<double> &errorValue,
//     vector<double> &processError, double delta)
// Simulate our observed values
//**********************************************************************
void CLogNormalWithQLikelihood::simulateObserved(vector<double> &observed, vector<double> &expected, vector<double> &errorValue,
    vector<double> &processError, double delta) {

  // Variables
  CRandomNumberGenerator *pRandom = CRandomNumberGenerator::Instance();

  observed.clear();

  // Loop through expected
  for (int i = 0; i < (int)expected.size(); ++i) {
    // Should never happen ...
    if(expected[i] <= 0.0) {
      observed.push_back(0.0);
      continue;
    }

    // Calculate observed
    double dErrorValue  = adjustErrorValue(processError[i], errorValue[i]);
    double dObserved    = pRandom->getRandomLogNormal(expected[i], dErrorValue);

    observed.push_back(dObserved);
  }
}

//**********************************************************************
// CLogNormalWithQLikelihood::~CLogNormalWithQLikelihood()
// Destructor
//**********************************************************************
CLogNormalWithQLikelihood::~CLogNormalWithQLikelihood() {
}
