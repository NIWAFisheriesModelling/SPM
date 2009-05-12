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

//**********************************************************************
// CMultinomialLikelihood::CMultinomialLikelihood()
// Default Constructor
//**********************************************************************
CMultinomialLikelihood::CMultinomialLikelihood() {
}

//**********************************************************************
// double CMultinomialLikelihood::adjustErrorValue(double processError, double errorValue)
// Adjust error value based on process error
//**********************************************************************
double CMultinomialLikelihood::adjustErrorValue(double processError, double errorValue) {
  // adjust for N process error
  if( (errorValue > 0.0) && (processError > 0.0) )
    return (1.0/(1.0/errorValue + 1.0/processError));

  return errorValue;
}
//**********************************************************************
// void CMultinomialLikelihood::getResult(vector<double> &scores, vector<double> &expected, vector<double> &observed,
//     vector<double> &errorValue, vector<double> &processError, double delta)
// Get the result from our likelihood for the observation
//**********************************************************************
void CMultinomialLikelihood::getResult(vector<double> &scores, vector<double> &expected, vector<double> &observed,
    vector<double> &errorValue, vector<double> &processError, double delta) {

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
// void CMultinomialLikelihood::simulateObserved(vector<double> &observed, vector<double> &expected, vector<double> &errorValue,
//     vector<double> &processError, double delta)
// Simulate observed value for our observation
//**********************************************************************
void CMultinomialLikelihood::simulateObserved(vector<double> &observed, vector<double> &expected, vector<double> &errorValue,
    vector<double> &processError, double delta) {

  observed.clear();

  // Loop through expected
  for (int i = 0; i < (int)expected.size(); ++i) {
    observed.push_back(expected[i]);
  }
  /*
   *                                                          // this section should just rescale any returned values to sum to 1?
        // instance the random number generator
        CRandomNumberGenerator *pRandom = CRandomNumberGenerator::Instance();
        // get the multinomial N value
        double dN = std::ceil(pLikelihood->adjustErrorValue(dProcessError, dErrorValue));
        //declare a vector to hold vector of results (simulated observed values)
        std::vector<double> vObserved(iArraySize, 0.0);
        //declare a vector to hold vector of expected values
        std::vector<double> vExpected(iArraySize, 0.0);
        // iteratate through errorvalue numbers
        for(int i = 0; i< (int)dN; i++) {
          // get a random uniform
          double dRandomNumber = pRandom -> getRandomUniform_01();
          // create a holder for the cumulative sum of expected values
          double dCumulativeSumExpected = 0.0;
          // iterate through the proportions..
          for (int j = 0; j < iArraySize; ++j) {
            if(!CComparer::isZero(dRunningTotal))
              vExpected[j] = pAgeResults[j] / dRunningTotal;
            else
              vExpected[j] = 0.0;
            // update the running total
            dCumulativeSumExpected = dCumulativeSumExpected + vExpected[j];
            // compare with random number
            if(dRandomNumber  <= dCumulativeSumExpected) {
              vObserved[j]++;
              break;
            }
          }
        }
   */
}

//**********************************************************************
// double CMultinomialLikelihood::getInitialScore(vector<string> &keys, vector<double> &processError, vector<double> &errorValue)
// Get Initial Score
//**********************************************************************
double CMultinomialLikelihood::getInitialScore(vector<string> &keys, vector<double> &processError, vector<double> &errorValue) {

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
