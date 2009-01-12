//============================================================================
// Name        : CProportionsAtAgeObservation.cpp
// Author      : S.Rasmussen
// Date        : 17/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CProportionsAtAgeObservation.h"
#include "../../Layers/String/CStringLayer.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/CComparer.h"

//**********************************************************************
// CProportionsAtAgeObservation::CProportionsAtAgeObservation(CProportionsAtAgeObservation *Observation)
// Default Constructor
//**********************************************************************
CProportionsAtAgeObservation::CProportionsAtAgeObservation(CProportionsAtAgeObservation *Observation)
: CObservation(Observation) {

  // Vars
  iMinAge             = -1;
  iMaxAge             = -1;
  bAgePlus            = false;
  bRescale            = false;
  dR                  = DELTA;
  pAgeResults         = 0;
  dNProcessError      = -1;

  // Copy Construct
  if (Observation != 0) {
    iMinAge         = Observation->getMinAge();
    iMaxAge         = Observation->getMaxAge();
    bAgePlus        = Observation->getAgePlus();
    bRescale        = Observation->getRescale();
    dR              = Observation->getR();
    dNProcessError  = Observation->getNProcessError();

    // Clone our N Map
    for (int i = 0; i < Observation->getNCount(); ++i) {
      string key = Observation->getNKey(i);
      mN[key] = Observation->getNValue(key);
    }

    // CLone our Proportion Matrix (Map of Vectors)
    for (int i = 0; i < Observation->getProportionCount(); ++i) {
      string key = Observation->getProportionKey(i);
      for (int j = 0; j < Observation->getProportionKeyValueCount(key); ++j) {
        mvProportionMatrix[key].push_back(Observation->getProportionValue(key, j));
      }
    }

  }
}

//**********************************************************************
// void CProportionsAtAgeObservation::addProportion(string Group, double Proportion)
// Add Observation to our Map/Vector.
//**********************************************************************
void CProportionsAtAgeObservation::addProportion(string Group, double Proportion) {
  mvProportionMatrix[Group].push_back(Proportion);
}

//**********************************************************************
// string CProportionsAtAgeObservation::getProportionKey(int index)
// Get key from our matrix for the index
//**********************************************************************
string CProportionsAtAgeObservation::getProportionKey(int index) {

  map<string, vector<double> >::iterator ptr = mvProportionMatrix.begin();
  for (int i = 0; i < index; ++i)
    ptr++;
  return (*ptr).first;
}

//**********************************************************************
// int CProportionsAtAgeObservation::getProportionKeyValueCount(string key)
// Get the number of elements for our key in the vector
//**********************************************************************
int CProportionsAtAgeObservation::getProportionKeyValueCount(string key) {
  return (int)mvProportionMatrix[key].size();
}

//**********************************************************************
// double CProportionsAtAgeObservation::getProportionValue(string key, int index)
// Return value from the vector in the map at key
//**********************************************************************
double CProportionsAtAgeObservation::getProportionValue(string key, int index) {
  return mvProportionMatrix[key][index];
}

//**********************************************************************
// void CProportionsAtAgeObservation::addN(string key, double value)
// Add N to our Map
//**********************************************************************
void CProportionsAtAgeObservation::addN(string key, double value) {
  mN[key] = value;
}

//**********************************************************************
// string CProportionsAtAgeObservation::getNKey(int index)
// Get key for Index
//**********************************************************************
string CProportionsAtAgeObservation::getNKey(int index) {

  map<string, double>::iterator ptr = mN.begin();
  for (int i = 0; i < index; ++i)
    ptr++;
  return (*ptr).first;
}

//**********************************************************************
// double CProportionsAtAgeObservation::getNValue(string key)
// Return Double For Key
//**********************************************************************
double CProportionsAtAgeObservation::getNValue(string key) {
  return mN[key];
}

//**********************************************************************
// void CProportionsAtAgeObservation::Validate()
// Validate
//**********************************************************************
void CProportionsAtAgeObservation::validate() {
  try {
    // Base
    CObservation::validate();

    // We must have some proportions
    if (mvProportionMatrix.size() == 0)
      CError::errorMissing(PARAM_OBS);
    if (iMinAge < pWorld->getMinAge())
      CError::errorLessThan(PARAM_MIN_AGE, PARAM_MIN_AGE);
    if (iMaxAge > pWorld->getMaxAge())
      CError::errorGreaterThan(PARAM_MAX_AGE, PARAM_MAX_AGE);
    if (CComparer::isEqual(dR, -1.0))
      CError::errorMissing(PARAM_R);

    // Find out the Spread in Ages
    int iAgeSpread = (iMaxAge+1) - iMinAge;

    // Loop Through our Partitions
    map<string, vector<double> >::iterator vPropPtr = mvProportionMatrix.begin();
    while (vPropPtr != mvProportionMatrix.end()) {
      // Validate Sizes
      if (iAgeSpread > (int)((*vPropPtr).second).size())
        throw string(ERROR_QTY_LESS_PROPORTIONS + (*vPropPtr).first);
      if (iAgeSpread < (int)((*vPropPtr).second).size())
        throw string(ERROR_QTY_MORE_PROPORTIONS + (*vPropPtr).first);

      // If bRescale=True, loop through proportions and rescale so sum equals one
      if (bRescale) {
        double dRunningTotal = 0.0;
        vector<double>::iterator vPtr3 = ((*vPropPtr).second).begin();
        while (vPtr3 != ((*vPropPtr).second).end()) {
          dRunningTotal += (*vPtr3);
          vPtr3++;
        }
        vector<double>::iterator vPtr4 = ((*vPropPtr).second).begin();
        while (vPtr4 != ((*vPropPtr).second).end()) {
          (*vPtr4) /= dRunningTotal;
          vPtr4++;
        }
      } else {
        // Loop Through Proportions, Ensuring they approximately Equal 1.0
        double dRunningTotal = 0.0;
        vector<double>::iterator vPtr2 = ((*vPropPtr).second).begin();
        while (vPtr2 != ((*vPropPtr).second).end()) {
          dRunningTotal += (*vPtr2);
          vPtr2++;
        }
        if (fabs(1.0-dRunningTotal)> 0.001) {
          throw string((*vPropPtr).first + ERROR_EQUAL_PROPORTION_ONE + CConvertor::doubleToString(dRunningTotal));
        }
      }

      vPropPtr++;
    }
    // Must be same size
    if (vCategoryList.size() != vSelectivityList.size())
      throw string(ERROR_EQUAL_CATEGORY_SELECTIVITY);

    // Number of N's must be equal to number of Proportions
    if (mN.size() != mvProportionMatrix.size())
      throw string(ERROR_EQUAL_N_OBS);

    // Validate our N's against the OBS
    // They have to have a 1-to-1 relationship
    bool bMatch = false;
    map<string, double>::iterator vNPtr = mN.begin();

    while (vNPtr != mN.end()) {
      bMatch = false;
      // Loop Props Looking For Match;
      vPropPtr = mvProportionMatrix.begin();
      while (vPropPtr != mvProportionMatrix.end()) {
        if ((*vPropPtr).first == (*vNPtr).first) {
          bMatch = true;
          break;
          }
      vPropPtr++;
      }

      if (!bMatch)
        throw string(ERROR_MISSING_N_OBS + (*vNPtr).first);

      vNPtr++;
    }
  } catch (string Ex) {
    Ex = "CProportionsAtAgeObservation.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProportionsAtAgeObservation::build()
// Build
//**********************************************************************
void CProportionsAtAgeObservation::build() {
  try {
    // Base Build
    CObservation::build();

    // Create Array of Age Results
    iArraySize = (iMaxAge+1) - iMinAge;

    if (pAgeResults == 0)
      pAgeResults = new double[iArraySize];
    for (int i = 0; i < iArraySize; ++i)
      pAgeResults[i] = 0.0;

  } catch (string Ex) {
    Ex = "CProportionsAtAgeObservation.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProportionsAtAgeObservation::execute()
// Execute
//**********************************************************************
void CProportionsAtAgeObservation::execute() {
#ifndef OPTIMISE
  try {
#endif
    // Variables
    int    iSquareAgeOffset   = iMinAge - pWorld->getMinAge();
           dScore             = 0.0;
    double dRunningTotal      = 0.0;
    double dCurrentProp       = 0.0;

    // Loop Through Observations
    map<string, vector<double> >::iterator vPropPtr = mvProportionMatrix.begin();
    while (vPropPtr != mvProportionMatrix.end()) {
      // For this Key, Populate our Age Results For Each Age
      // Loop Through Each Square In Layer
      for (int i = 0; i < pLayer->getHeight(); ++i) {
        for (int j = 0; j < pLayer->getWidth(); ++j) {
          // Check if this matches the key
          if (pLayer->getValue(i, j) == (*vPropPtr).first) {
            // Get our Square and check if it's enabled
            pBase = pWorld->getBaseSquare(i, j);
            if (!pBase->getEnabled())
              continue;

            // Loop Through Ages in that square and add them to count
            for (int k = iSquareAgeOffset; k < (iArraySize+iSquareAgeOffset); ++k) {
              // Loop Through Categories
              for (int l = 0; l < (int)vCategoryIndex.size(); ++l) {
                double dSelectResult = vSelectivityIndex[l]->getResult(k);
                pAgeResults[k] += dSelectResult * pBase->getPopulationInCategoryForAge(k, l);
              }
            }
            // And if the observation has a plus group
            if(bAgePlus) {
              // Loop Through Plus Group Ages in that square and add them to count for the Plus group
              for (int k = (iArraySize+iSquareAgeOffset); k < pWorld->getMaxAge(); ++k) {
                // Loop Through Categories
                for (int l = 0; l < (int)vCategoryIndex.size(); ++l) {
                  double dSelectResult = vSelectivityIndex[l]->getResult(k);
                  pAgeResults[iArraySize+iSquareAgeOffset-1] += dSelectResult * pBase->getPopulationInCategoryForAge(k, l);
                }
              }
            }
          }
        }
      }

      // Populate our Running Total
      dRunningTotal = 0.0;

      for (int i = 0; i < iArraySize; ++i)
        dRunningTotal += pAgeResults[i];

      // If we have a running total, do a comparison against
      // Our AgeResults

      double dN = mN[(*vPropPtr).first];
      //Add in Process Error if defined
      if(dNProcessError>=0) dN = 1.0/(1.0/dN + 1.0/dNProcessError);

      dScore = -CMath::lnFactorial(dN);

      for (int i = 0; i < iArraySize; ++i) {

        // Get our Proportion
        if(!CComparer::isZero(dRunningTotal))
          dCurrentProp = pAgeResults[i] / dRunningTotal;
        else
          dCurrentProp = 0.0;
        dScore += CMath::lnFactorial(dN * ((*vPropPtr).second)[i]) - dN * ((*vPropPtr).second)[i] * log(CMath::zeroFun(dCurrentProp,dR));
      }

      // Clear Our Age Results
      for (int i = 0; i < iArraySize; ++i)
        pAgeResults[i] = 0.0;

      vPropPtr++;
    }

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CProportionsAtAgeObservation.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CProportionsAtAgeObservation::~CProportionsAtAgeObservation()
// Default De-Constructor
//**********************************************************************
CProportionsAtAgeObservation::~CProportionsAtAgeObservation() {
  // Clear Age Results
  delete [] pAgeResults;
}
