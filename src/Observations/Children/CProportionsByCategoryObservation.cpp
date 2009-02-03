//============================================================================
// Name        : CProportionsByCategoryObservation.cpp
// Author      : S.Rasmussen
// Date        : 1/05/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CProportionsByCategoryObservation.h"
#include "../../Layers/String/CStringLayer.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/CComparer.h"

//**********************************************************************
// CProportionsByCategoryObservation::CProportionsByCategoryObservation()
// Default Constructor
//**********************************************************************
CProportionsByCategoryObservation::CProportionsByCategoryObservation() {
  // TODO: Implement
}

//**********************************************************************
// string CProportionsByCategoryObservation::getProportionKey(int index)
// Return key by index into the map
//**********************************************************************
string CProportionsByCategoryObservation::getProportionKey(int index) {

  map<string, vector<double> >::iterator ptr = mvProportionMatrix.begin();
  for (int i = 0; i < index; ++i)
    ptr++;
  return (*ptr).first;
}

//**********************************************************************
// int CProportionsByCategoryObservation::getProportionKeyCount(string key)
// Return number of elements in vector by key
//**********************************************************************
int CProportionsByCategoryObservation::getProportionKeyCount(string key) {
  return (int)mvProportionMatrix[key].size();
}

//**********************************************************************
// double CProportionsByCategoryObservation::getProportionValue(string key, int index)
// Return value by key (map) and index (vector)
//**********************************************************************
double CProportionsByCategoryObservation::getProportionValue(string key, int index) {
  return mvProportionMatrix[key][index];
}

//**********************************************************************
// string CProportionsByCategoryObservation::getNKey(int index)
// Get Key from N by index
//**********************************************************************
string CProportionsByCategoryObservation::getNKey(int index) {

  map<string, vector<double> >::iterator ptr = mvN.begin();
  for (int i = 0; i < index; ++i)
    ptr++;
  return (*ptr).first;
}

//**********************************************************************
// int CProportionsByCategoryObservation::getNKeyValueCount(string key)
// Get number of values in vector from matrix by key
//**********************************************************************
int CProportionsByCategoryObservation::getNKeyValueCount(string key) {
  return (int)mvN[key].size();
}

//**********************************************************************
// double CProportionsByCategoryObservation::getNValue(string key, int index)
// Get the Value from mvN
//**********************************************************************
double CProportionsByCategoryObservation::getNValue(string key, int index) {
  return mvN[key][index];
}

//**********************************************************************
// string CProportionsByCategoryObservation::getPopulationCategory(int index)
// Return the population category by index
//**********************************************************************
string CProportionsByCategoryObservation::getPopulationCategory(int index) {
  return vPopulationCategoryNames[index];
}

//**********************************************************************
// string CProportionsByCategoryObservation::getPopulationSelectivity(int index)
// Get selectivity by index
//**********************************************************************
string CProportionsByCategoryObservation::getPopulationSelectivity(int index) {
  return vPopulationSelectivityNames[index];
}

//**********************************************************************
// void CProportionsByCategoryObservation::validate()
// Validate the Observation Parameters
//**********************************************************************
void CProportionsByCategoryObservation::validate() {
  try {
    // Base Validation
    CObservation::validate();

    // Find out the Spread in Ages
    int iAgeSpread = (iMaxAge+1) - iMinAge;

    // Loop Through our Partitions
    map<string, vector<double> >::iterator vPropPtr = mvProportionMatrix.begin();
    while (vPropPtr != mvProportionMatrix.end()) {
      // Validate Sizes of proportions
      if (iAgeSpread > (int)((*vPropPtr).second).size())
        throw string(ERROR_QTY_LESS_PROPORTIONS + (*vPropPtr).first);
      if (iAgeSpread < (int)((*vPropPtr).second).size())
        throw string(ERROR_QTY_MORE_PROPORTIONS + (*vPropPtr).first);

      // Loop Through Proportions, Ensuring they lie between 0.0 and 1.0
      vector<double>::iterator vPtr2 = ((*vPropPtr).second).begin();
      while (vPtr2 != ((*vPropPtr).second).end()) {
        if(!CComparer::isBetween((*vPtr2),0.0,1.0))
          throw string((*vPropPtr).first + ERROR_BETWEEN_ZERO_ONE);
        vPtr2++;
      }
      vPropPtr++;
    }

    // Loop Through our Partitions
    map<string, vector<double> >::iterator vNPtr = mvN.begin();
    while (vNPtr != mvN.end()) {
      // Validate Sizes of Ns
      if (iAgeSpread > (int)((*vNPtr).second).size())
        throw string(ERROR_QTY_LESS_N + (*vNPtr).first);
      if (iAgeSpread < (int)((*vNPtr).second).size())
        throw string(ERROR_QTY_MORE_N + (*vNPtr).first);

      vNPtr++;
    }

  } catch (string Ex) {
    Ex = "CProportionsByCategoryObservation.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProportionsByCategoryObservation::build()
// Build our Observation Objects and Relationships
//**********************************************************************
void CProportionsByCategoryObservation::build() {
  try {
    // Base Build
    CObservation::build();

    // Create Array of Age Results
    iArraySize = (iMaxAge+1) - iMinAge;

    if (pAgeResults == 0)
      pAgeResults = new double[iArraySize];
    for (int i = 0; i < iArraySize; ++i)
      pAgeResults[i] = 0.0;

    if (pCombinedAgeResults == 0)
      pCombinedAgeResults = new double[iArraySize];
    for (int i = 0; i < iArraySize; ++i)
      pCombinedAgeResults[i] = 0.0;

    // Validate our N's against the OBS
    // They have to have a 1-to-1 relationship
    bool bMatch = false;
    map<string, vector<double> >::iterator vNPtr = mvN.begin();
    map<string, vector<double> >::iterator vPropPtr = mvProportionMatrix.begin();

    while (vNPtr != mvN.end()) {
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
    Ex = "CProportionsByCategoryObservation.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProportionsByCategoryObservation::execute()
// Execute our Observation to generate a score
//**********************************************************************
void CProportionsByCategoryObservation::execute() {
#ifndef OPTIMISE
  try {
#endif
    // Variables
    int    iSquareAgeOffset   = iMinAge - pWorld->getMinAge();

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
            pBaseSquare = pWorld->getBaseSquare(i, j);
            if (!pBaseSquare->getEnabled())
              continue;

            // Loop Through Ages in that square and add them to count
            for (int k = iSquareAgeOffset; k < (iArraySize+iSquareAgeOffset); ++k) {
              // Loop Through Categories
              for (int l = 0; l < (int)vCategories.size(); ++l) {
                double dSelectResult = vSelectivities[l]->getResult(k);
                pAgeResults[k] += dSelectResult * pBaseSquare->getPopulationInCategoryForAge(k, l);
              }
              for (int l = 0; l < (int)vPopulationCategories.size(); ++l) {
                double dSelectResult = vPopulationSelectivities[l]->getResult(k);
                pCombinedAgeResults[k] += dSelectResult * pBaseSquare->getPopulationInCategoryForAge(k, l);
              }
            }
            // And if the observation has a plus group
            if(bAgePlus) {
              // Loop Through Plus Group Ages in that square and add them to count for the Plus group
              for (int k = (iArraySize+iSquareAgeOffset); k < pWorld->getMaxAge(); ++k) {
                // Loop Through Categories
                for (int l = 0; l < (int)vCategories.size(); ++l) {
                  double dSelectResult = vSelectivities[l]->getResult(k);
                  pAgeResults[iArraySize+iSquareAgeOffset-1] += dSelectResult * pBaseSquare->getPopulationInCategoryForAge(k, l);
                }
                for (int l = 0; l < (int)vPopulationCategories.size(); ++l) {
                  double dSelectResult = vPopulationSelectivities[l]->getResult(k);
                  pCombinedAgeResults[iArraySize+iSquareAgeOffset-1] += dSelectResult * pBaseSquare->getPopulationInCategoryForAge(k, l);
                }
              }
            }
          }
        }
      }

      // If we have a running total, do a comparison against
      // Our AgeResults

      dScore = 0.0;

      map<string, vector<double> >::iterator mNPtr = mvN.begin();
      while (mNPtr != mvN.end()) {
        if ((*mNPtr).first == (*vPropPtr).first)
          break;
        mNPtr++;
      }

      for (int i = 0; i < iArraySize; ++i) {
        double dExp = pAgeResults[i]/pCombinedAgeResults[i];
        double dObs  = (*vPropPtr).second[i] ;
        double dN  = (*mNPtr).second[i];
        if(dNProcessError>=0) dN = 1.0/(1.0/dN + 1.0/dNProcessError);
        dScore -= CMath::lnFactorial(dN) - CMath::lnFactorial(dN-(1-dObs)) -
            CMath::lnFactorial(dN*dObs) + dN * dObs * log(CMath::zeroFun(dExp,dR)) + dN *(1-dObs)
            * log(CMath::zeroFun(1-dExp,dR));
      }

      // Clear Our Age Results
      for (int i = 0; i < iArraySize; ++i) {
        pAgeResults[i] = 0.0;
        pCombinedAgeResults[i] = 0.0;
      }
      vPropPtr++;
    }

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CProportionsByCategoryObservation.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CProportionsByCategoryObservation::~CProportionsByCategoryObservation()
// Default De-Constructor
//**********************************************************************
CProportionsByCategoryObservation::~CProportionsByCategoryObservation() {
  delete [] pAgeResults;
  delete [] pCombinedAgeResults;
}
