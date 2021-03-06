//============================================================================
// Name        : CProportionsAtAgeObservation.cpp
// Author      : S.Rasmussen
// Date        : 17/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Global Headers
#include <iostream>
#include <boost/lexical_cast.hpp>

// Local Headers
#include "CProportionsAtAgeObservation.h"
#include "../../AgeingError/CAgeingError.h"
#include "../../AgeingError/CAgeingErrorManager.h"
#include "../../Helpers/CComparer.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CCompoundCategories.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Selectivities/CSelectivity.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CProportionsAtAgeObservation::CProportionsAtAgeObservation()
// Default Constructor
//**********************************************************************
CProportionsAtAgeObservation::CProportionsAtAgeObservation() {

  // Default Values
  pAgeResults         = 0;
  iMinAge             = -1;
  iMaxAge             = -1;
  bAgePlus            = false;
  bRescale            = false;
  pAgeingError        = 0;
  pCategories         = 0;

  // Register estimables
  registerEstimable(PARAM_PROCESS_ERROR, &dProcessError);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_MIN_AGE);
  pParameterList->registerAllowed(PARAM_MAX_AGE);
  pParameterList->registerAllowed(PARAM_AGE_PLUS_GROUP);
  pParameterList->registerAllowed(PARAM_TOLERANCE);
  pParameterList->registerAllowed(PARAM_OBS);
  pParameterList->registerAllowed(PARAM_DELTA);
  pParameterList->registerAllowed(PARAM_ERROR_VALUE);
  pParameterList->registerAllowed(PARAM_PROCESS_ERROR);
  pParameterList->registerAllowed(PARAM_AGEING_ERROR);
}

//**********************************************************************
// void CProportionsAtAgeObservation::Validate()
// Validate
//**********************************************************************
void CProportionsAtAgeObservation::validate() {
  try {
    // Base

    CObservation::validate();

    // Populate our Parameters
    iMinAge             = pParameterList->getInt(PARAM_MIN_AGE);
    iMaxAge             = pParameterList->getInt(PARAM_MAX_AGE);
    bAgePlus            = pParameterList->getBool(PARAM_AGE_PLUS_GROUP,true,true);
    dDelta              = pParameterList->getDouble(PARAM_DELTA,true,DELTA);
    dTolerance          = pParameterList->getDouble(PARAM_TOLERANCE,true,0.001);
    dProcessError       = pParameterList->getDouble(PARAM_PROCESS_ERROR,true,0);
    sAgeingError        = pParameterList->getString(PARAM_AGEING_ERROR, true, "");

    // Read in categories, and construct the vector<vector>> of categories and selectivities
    // rows = sets of proportions: columns are the categories to aggregate
    pCategories = new CCompoundCategories;
    pCategories->setCategories(vCategoryNames,getLabel());

    // Validate
    //Check length of categories and selectivites are equal
    unsigned iCategoryNamesSize = pCategories->getNCategories();
    unsigned iSelectivityNamesSize = vSelectivityNames.size();
    if (iCategoryNamesSize != iSelectivityNamesSize)
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_SELECTIVITIES);

    if (dDelta < 0)
      CError::errorLessThan(PARAM_DELTA, PARAM_ZERO);

    if (iMinAge < pWorld->getMinAge())
      CError::errorLessThan(PARAM_MIN_AGE, PARAM_MIN_AGE);
    if (iMaxAge > pWorld->getMaxAge())
      CError::errorGreaterThan(PARAM_MAX_AGE, PARAM_MAX_AGE);
    if (dProcessError < 0)
      CError::errorLessThan(PARAM_PROCESS_ERROR, PARAM_ZERO);
    if(sLikelihood == PARAM_DIRICHLET && dProcessError > 1)
      CError::errorGreaterThan(PARAM_PROCESS_ERROR, PARAM_ONE);

    // Find out the Spread in Ages
    iAgeSpread = (iMaxAge+1) - iMinAge;
    int iNGroups = pCategories->getNRows();

    // Get our OBS
    vector<string> vOBS;
    pParameterList->fillVector(vOBS, PARAM_OBS);

    if ((vOBS.size() % (iNGroups * iAgeSpread + 1)) !=0)
      CError::errorListNotSize(PARAM_OBS, iAgeSpread * iNGroups);

    for (int i = 0; i < (int)vOBS.size(); i+=(iNGroups * iAgeSpread + 1)) {
      for (int j = 0; j < (iNGroups * iAgeSpread); ++j) {
        try {
          mvObservationMatrix[vOBS[i]].push_back(boost::lexical_cast<double>(vOBS[i+j+1]));
        } catch (boost::bad_lexical_cast) {
          string Ex = string("Non-numeric value in ") + PARAM_OBS + string(" for ") + PARAM_OBSERVATION + string(" ") + getLabel();
          throw Ex;
        }

        // Check for non-positive or negative values in our observations  - depends on likelihood
        if(sLikelihood == PARAM_LOGNORMAL) {
          if ((*mvObservationMatrix[vOBS[i]].rbegin()) <= 0.0 ) {
            CError::errorLessThanEqualTo(PARAM_OBS, PARAM_ZERO);
          }
        } else if(sLikelihood == PARAM_MULTINOMIAL || sLikelihood == PARAM_DIRICHLET ) {
          if(boost::lexical_cast<double>(vOBS[i+j+1]) < 0.0) {
            CError::errorLessThan(PARAM_OBS, PARAM_ZERO);
          }
        }
      }
    }

    // Get our Error Value
    vector<string> vErrorValues;
    pParameterList->fillVector(vErrorValues, PARAM_ERROR_VALUE);

    string sThisLikelihood = sLikelihood;
    if(sLikelihood == PARAM_PSEUDO) {
      sThisLikelihood = pParameterList->getString(PARAM_SIMULATION_LIKELIHOOD);
    }

    if(sThisLikelihood == PARAM_LOGNORMAL) {
      if ((vErrorValues.size() % (iNGroups * iAgeSpread + 1)) !=0)
        CError::errorListNotSize(PARAM_ERROR_VALUE, iAgeSpread * iNGroups);
      for (int i = 0; i < (int)vErrorValues.size(); i+=(iNGroups * iAgeSpread + 1)) {
        for (int j = 0; j < (iNGroups * iAgeSpread); ++j) {
          try {
            mvErrorMatrix[vErrorValues[i]].push_back(boost::lexical_cast<double>(vErrorValues[i+j+1]));
          } catch (boost::bad_lexical_cast) {
            string Ex = string("Non-numeric value in ") + PARAM_ERROR_VALUE + string(" for ") + PARAM_OBSERVATION + string(" ") + getLabel();
            throw Ex;
          }
          // Check for non-positive or negative values in the error - depends on likelihood
          if (boost::lexical_cast<double>(vErrorValues[i+j+1]) <= 0.0 ) {
            CError::errorLessThanEqualTo(PARAM_ERROR_VALUE, PARAM_ZERO);
          }
        }
      }
    } else if(sThisLikelihood == PARAM_MULTINOMIAL || sThisLikelihood == PARAM_DIRICHLET) {
      if ((vErrorValues.size() % 2) != 0)
        throw string(PARAM_ERROR_VALUE + string(ERROR_NOT_CONTAIN_EVEN_ELEMENTS));
      for (int i = 0; i < (int)vErrorValues.size(); i+=2) {
        for (int j = 0; j < (iNGroups * iAgeSpread); ++j) {
          try {
            mvErrorMatrix[vErrorValues[i]].push_back(boost::lexical_cast<double>(vErrorValues[i+1]));
            //mvErrorMatrix[vErrorValues[i]] = boost::lexical_cast<double>(vErrorValues[i+1]);
          } catch (boost::bad_lexical_cast) {
            string Ex = string("Non-numeric value in ") + PARAM_ERROR_VALUE + string(" for ") + PARAM_OBSERVATION + string(" ") + getLabel();
            throw Ex;
          }
          // Check for non-positive or negative values in the error - depends on likelihood
          if (boost::lexical_cast<double>(vErrorValues[i+1]) < 0.0 ) {
            CError::errorLessThan(PARAM_ERROR_VALUE, PARAM_ZERO);
          }
        }
      }
    }

    // Declare maps for later use
    map<string, vector<double> >::iterator vObsPtr = mvObservationMatrix.begin();
    map<string, vector<double> >::iterator vErrPtr = mvErrorMatrix.begin();

    // Loop Through our Partitions
    while (vObsPtr != mvObservationMatrix.end()) {
      // Validate Sizes
      if ((iAgeSpread * iNGroups) > (int)((*vObsPtr).second).size())
        throw string(ERROR_QTY_LESS_PROPORTIONS + (*vObsPtr).first);
      if ((iAgeSpread * iNGroups) < (int)((*vObsPtr).second).size())
        throw string(ERROR_QTY_MORE_PROPORTIONS + (*vObsPtr).first);

        // Rescale if Tolerance is exceeded
        double dRunningTotal = 0.0;
        vector<double>::iterator vPtr3 = ((*vObsPtr).second).begin();
        while (vPtr3 != ((*vObsPtr).second).end()) {
          dRunningTotal += (*vPtr3);
          vPtr3++;
        }

        if (fabs(1.0-dRunningTotal) > dTolerance) {
          vector<double>::iterator vPtr4 = ((*vObsPtr).second).begin();
          while (vPtr4 != ((*vObsPtr).second).end()) {
            (*vPtr4) /= dRunningTotal;
            vPtr4++;
          }
        }
      vObsPtr++;
    }

    // Number of N's must be equal to number of Proportions
    if (mvErrorMatrix.size() != mvObservationMatrix.size()) {
      CError::errorListSameSize(PARAM_N, PARAM_OBS);
    }

    // Validate our N's against the OBS
    // They have to have a 1-to-1 relationship
    bool bMatch = false;

    while (vErrPtr != mvErrorMatrix.end()) {
      bMatch = false;
      // Loop Props Looking For Match;
      vObsPtr = mvObservationMatrix.begin();
      while (vObsPtr != mvObservationMatrix.end()) {
        if ((*vObsPtr).first == (*vErrPtr).first) {
          bMatch = true;
          break;
        }
        vObsPtr++;
      }

      if (!bMatch)
        throw string(ERROR_MISSING_N_OBS + (*vErrPtr).first);

      vErrPtr++;
    }
  } catch (string &Ex) {
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

    // Ageing Error
    if (sAgeingError != "")
      pAgeingError = CAgeingErrorManager::Instance()->getAgeingError(sAgeingError);

    // Create Array of Age Results
    if (pAgeResults == 0)
      pAgeResults = new double[iAgeSpread * pCategories->getNRows()];
    for (int i = 0; i < (iAgeSpread * pCategories->getNRows()); ++i)
      pAgeResults[i] = 0.0;

  } catch (string &Ex) {
    Ex = "CProportionsAtAgeObservation.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProportionsAtAgeObservation::execute()
// Execute
//**********************************************************************
void CProportionsAtAgeObservation::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // Variables
    int                 iSquareAgeOffset   = iMinAge - pWorld->getMinAge();
                        dScore             = 0.0;
    double              dRunningTotal      = 0.0;
    double              dCurrentProp       = 0.0;
    vector<string>      vKeys;
    vector<int>         vAges;
    vector<string>      vGroup;
    vector<double>      vExpected;
    vector<double>      vObserved;
    vector<double>      vProcessError;
    vector<double>      vErrorValue;
    vector<double>      vScores;

    // Base
    CObservation::execute();

    pWorldView->execute();

    // Loop Through Observations
    map<string, vector<double> >::iterator mvObsPtr = mvObservationMatrix.begin();
    map<string, vector<double> >::iterator mvErrPtr = mvErrorMatrix.begin();

    while (mvObsPtr != mvObservationMatrix.end()) {
      // Get Square for this Area
      CWorldSquare *pStartSquare = pStartWorldView->getSquare((*mvObsPtr).first);
      CWorldSquare *pSquare      = pWorldView->getSquare((*mvObsPtr).first);

      //apply ageing error & calculate proportion time_step
      vector<double> vTemp(pSquare->getWidth(),0);
      for (int i = 0; i < (int)pSquare->getHeight(); ++i) {
        for (int j = 0; j < (int)pSquare->getWidth(); ++j) {
          double dStartValue  = pStartSquare->getValue(i, j);
          double dEndValue    = pSquare->getValue(i, j);
          if(sProportionMethod == PARAM_MEAN) {
            vTemp[j] = dStartValue + ((dEndValue - dStartValue) * dProportionTimeStep);
          } else {
            vTemp[j] = std::abs(dStartValue - dEndValue) * dProportionTimeStep;
          }
        }
        if (pAgeingError != 0)
          pAgeingError->getExpected(vTemp);
        for (int j = 0; j < (int)pSquare->getWidth(); ++j) {
          pSquare->setValue(i,j,vTemp[j]);
        }
      }
      // Loop Through Ages in that square and add them to count
      for (int i = 0; i < iAgeSpread; ++i) {
        // Loop Through Category Groups
        for (int j = 0; j < pCategories->getNRows(); ++j) {
          for (int k = 0; k < pCategories->getNElements(j); ++k) {
            double dSelectResult = vSelectivities[pCategories->getIndex(j,k)]->getResult((i+iSquareAgeOffset));
            pAgeResults[i + (j * iAgeSpread)] += dSelectResult * pSquare->getAbundanceInCategoryForAge((i+iSquareAgeOffset), pCategories->getCategoryIndex(j,k));
          }
        }
      }
      // And if the observation has a plus group
      if(bAgePlus) {
        // Loop Through Plus Group Ages in that square and add them to count for the Plus group
        for (int i = iAgeSpread+iSquareAgeOffset; i < pWorld->getAgeSpread(); ++i) {
          // Loop Through Categories
          for (int j = 0; j < pCategories->getNRows(); ++j) {
            for (int k = 0; k < pCategories->getNElements(j); ++k) {
              double dSelectResult = vSelectivities[pCategories->getIndex(j,k)]->getResult(i);
              pAgeResults[(iAgeSpread-1) + (j * iAgeSpread)] += dSelectResult * pSquare->getAbundanceInCategoryForAge(i, pCategories->getCategoryIndex(j,k));
            }
          }
        }
      }
      // Populate our Running Total
      dRunningTotal = 0.0;

      for (int i = 0; i < (iAgeSpread * pCategories->getNRows()); ++i)
        dRunningTotal += pAgeResults[i];

      for (int i = 0; i < (pCategories->getNRows()); ++i) {
        for (int j = 0; j < iAgeSpread; ++j) {
          // Get our Proportion
          if(!CComparer::isZero(dRunningTotal))
            dCurrentProp = pAgeResults[(iAgeSpread * i) + j] / dRunningTotal;
          else
            dCurrentProp = 0.0;

          // Store the items we want to calculate scores for
          vKeys.push_back((*mvObsPtr).first);
          vGroup.push_back(pCategories->getGroup(i));
          vAges.push_back(j+iMinAge);
          vExpected.push_back(dCurrentProp);
          vObserved.push_back(((*mvObsPtr).second)[(iAgeSpread * i) + j]);
          vProcessError.push_back(dProcessError);
          //indentify the correct row of error values and extract the correct error value
          while (mvErrPtr != mvErrorMatrix.end()) {
            if ((*mvErrPtr).first == (*mvObsPtr).first) {
              vErrorValue.push_back(((*mvErrPtr).second)[(iAgeSpread * i) + j]);
              break;
            }
            mvErrPtr++;
          }
        }
      }

      // Clear Our Age Results
      for (int i = 0; i < (iAgeSpread * pCategories->getNRows()); ++i)
        pAgeResults[i] = 0.0;

      mvObsPtr++;
    }

    // Simulate or Generate Result?
    if (pRuntimeController->getRunMode() == RUN_MODE_SIMULATION) {
      // Simulate our values, then save them
      pLikelihood->simulateObserved(vKeys, vObserved, vExpected, vErrorValue, vProcessError, dDelta);
      for (int i = 0; i < (int)vObserved.size(); ++i)
        saveComparison(vKeys[i], vAges[i], vGroup[i], vExpected[i], vObserved[i], vErrorValue[i], vProcessError[i], pLikelihood->adjustErrorValue(vProcessError[i], vErrorValue[i]), 0.0);

    } else { // Generate Score
      dScore = pLikelihood->getInitialScore(vKeys, vExpected, vObserved, vProcessError, vErrorValue, dDelta);

      // Generate Results and save them
      pLikelihood->getResult(vScores, vExpected, vObserved, vErrorValue, vProcessError, dDelta);
      for (int i = 0; i < (int)vScores.size(); ++i) {
        dScore += vScores[i];
        saveComparison(vKeys[i], vAges[i], vGroup[i], vExpected[i], vObserved[i], vErrorValue[i], vProcessError[i], pLikelihood->adjustErrorValue(vProcessError[i], vErrorValue[i]), vScores[i]);
      }
    }

#ifndef OPTIMIZE
  } catch (string &Ex) {
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
  if (pAgeResults != 0)
    delete [] pAgeResults;
}
