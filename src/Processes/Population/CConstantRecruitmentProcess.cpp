//============================================================================
// Name        : CConstantRecruitmentProcess.cpp
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CConstantRecruitmentProcess.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../Helpers/CComparer.h"

//**********************************************************************
// CConstantRecruitmentProcess::CConstantRecruitmentProcess(CConstantRecruitmentProcess *Process)
// Default Constructor
//**********************************************************************
CConstantRecruitmentProcess::CConstantRecruitmentProcess(CConstantRecruitmentProcess *Process)
: CProcess(Process) {

  // Vars
  dR0                         = 0.0;

  // Register allowed estimatbles
  registerEstimable(PARAM_R0, &dR0);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_R0);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_PROPORTIONS);
  pParameterList->registerAllowed(PARAM_AGES);
  pParameterList->registerAllowed(PARAM_LAYER_NAME);
}

//**********************************************************************
// void CConstantRecruitmentProcess::addProportion(double value)
// Add A Proportion To Our List
//**********************************************************************
void CConstantRecruitmentProcess::addProportion(double value) {
  vProportionList.push_back(value);

  int size = (int)vProportionList.size();
  registerEstimable(PARAM_PROPORTION, size, &vProportionList[size-1]);
}

//**********************************************************************
// double CConstantRecruitmentProcess::getProportion(int index)
// Get proportion from vector @ age
//**********************************************************************
double CConstantRecruitmentProcess::getProportion(int index) {
  try {
    if (index >= (int)vProportionList.size())
      CError::errorGreaterThanEqualTo(PARAM_INDEX, PARAM_PROPORTIONS);
    if (index < 0)
      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);

    return vProportionList[index];

  } catch (string Ex) {
    Ex = "CRecruitmentProcess.getProportion()->" + Ex;
    throw Ex;
  }

  return 0.0;
}

//**********************************************************************
// void CConstantRecruitmentProcess::addAges(int value)
// Add Ages, These Match our Categories 1-1
//**********************************************************************
void CConstantRecruitmentProcess::addAges(int value) {
  vAgesList.push_back(value);
}

//**********************************************************************
// int CConstantRecruitmentProcess::getAges(int index)
// Get an ages element from our vector @ index
//**********************************************************************
int CConstantRecruitmentProcess::getAges(int index) {
  return vAgesList[index];
}

//**********************************************************************
// void CConstantRecruitmentProcess::validate()
// Validate Our Parameters
//**********************************************************************
void CConstantRecruitmentProcess::validate() {
  try {
    // Base Validation
    CProcess::validate();

    // Populate our Variables
    dR0     = pParameterList->getDouble(PARAM_R0);

    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);
    pParameterList->fillVector(vProportionList, PARAM_PROPORTIONS);
    pParameterList->fillVector(vAgesList, PARAM_AGES);

    // TODO: Add check to ensure vector sizes are the same.

    // Loop Through Proportions. Make Sure They Equal 1.0
    double dRunningTotal = 0.0;
    foreach(double Prop, vProportionList) {
      dRunningTotal += Prop;
    }
    // See If It is close enough to 1.0
    if (!CComparer::isEqual(dRunningTotal, 1.0))
      CError::errorNotEqual(PARAM_PROPORTIONS, PARAM_ONE);

  } catch(string Ex) {
    Ex = "CRecruitmentProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CConstantRecruitmentProcess::build()
// Build Our Relationships and Indexes
//**********************************************************************
void CConstantRecruitmentProcess::build() {
  try {
    // Base Build
    CProcess::build();

    // Populate Our Ages Index
    if (vAgesIndex.size() <= 0) {
      foreach(int Age, vAgesList) {
        vAgesIndex.push_back(pWorld->getColIndexForAge(Age));
      }
    }

    // Validate our Vectors are all same size
    if (vAgesIndex.size() != vCategoryIndex.size())
      throw string(ERROR_EQUAL_CATEGORY_AGES);
    if (vAgesIndex.size() != vProportionList.size())
      throw string(ERROR_EQUAL_AGES_PROPORTIONS);

  } catch(string Ex) {
    Ex = "CRecruitmentProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CConstantRecruitmentProcess::execute()
// Execute
//**********************************************************************
void CConstantRecruitmentProcess::execute() {
#ifndef OPTIMISE
  try {
#endif
    // Base Execute
    CProcess::execute();

    // Setup Our Variables
    double        dAmountPer    = dR0;

    // Now, Divide That By The Number of WorldSquares We will be updating
    if (bDependsOnLayer)
      dAmountPer /= iNumberOfValidLayerSpots;
    else
      dAmountPer /= pWorld->getEnabledSquareCount();

    // Loop Through The World Grid (i,j)
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        // Get Current Square, and Difference Equal
        pBase       = pWorld->getBaseSquare(i, j);
        // Check if this square is enabled or not.
        if (!pBase->getEnabled())
          continue;
        if ( (bDependsOnLayer) && (!pLayer->checkSpace(i, j)) )
          continue;

        pDiff       = pWorld->getDifferenceSquare(i, j);

        // Loop Through the Categories and Ages we have and Recruit
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k)
          pDiff->addValue(vCategoryIndex[k], vAgesIndex[k], (dAmountPer * vProportionList[k]) );
      }
    }
#ifndef OPTIMISE
  } catch(string Ex) {
    Ex = "CRecruitmentProcess.execute(" + getLabel() +")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CConstantRecruitmentProcess::~CConstantRecruitmentProcess()
// Default De-Constructor
//**********************************************************************
CConstantRecruitmentProcess::~CConstantRecruitmentProcess() {
  vProportionList.clear();
  vAgesList.clear();
  vAgesIndex.clear();
}
