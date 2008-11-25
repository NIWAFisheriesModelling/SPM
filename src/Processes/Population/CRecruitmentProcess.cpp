//============================================================================
// Name        : CRecruitmentProcess.cpp
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CRecruitmentProcess.h"
#include "../../Layers/CNumericLayer.h"

//**********************************************************************
// CRecruitmentProcess::CRecruitmentProcess(CRecruitmentProcess *Process)
// Default Constructor
//**********************************************************************
CRecruitmentProcess::CRecruitmentProcess(CRecruitmentProcess *Process)
: CProcess(Process) {

  // Vars
  dR0                         = 0.0;
  dSteepness                  = 0.0;
  dSigmaR                     = 0.0;
  dRho                        = 0.0;
  sMethod                     = "";
  eMethod                     = METHOD_UNKNOWN;

  registerEstimable(PARAM_R0, &dR0);
  registerEstimable(PARAM_STEEPNESS, &dSteepness);
  registerEstimable(PARAM_SIGMA_R, &dSigmaR);
  registerEstimable(PARAM_RHO, &dRho);

  // Copy Construct
  if (Process != 0) {
    dR0           = Process->getR0();
    dSteepness    = Process->getSteepness();
    dSigmaR       = Process->getSigmaR();
    dRho          = Process->getRho();
    sMethod       = Process->getMethod();

    // Copy vectors
    for (int i = 0; i < Process->getAgesCount(); ++i)
      addAges(Process->getAges(i));
    for (int i = 0; i < Process->getProportionCount(); ++i)
      addProportion(Process->getProportion(i));
  }
}

//**********************************************************************
// void CRecruitmentProcess::addProportion(double value)
// Add A Proportion To Our List
//**********************************************************************
void CRecruitmentProcess::addProportion(double value) {
  vProportionList.push_back(value);

  int size = (int)vProportionList.size();
  registerEstimable(PARAM_PROPORTION, size, &vProportionList[size-1]);
}

//**********************************************************************
// double CRecruitmentProcess::getProportion(int index)
// Get proportion from vector @ age
//**********************************************************************
double CRecruitmentProcess::getProportion(int index) {
  try {
    if (index >= (int)vProportionList.size())
      errorGreaterThanEqualTo(PARAM_INDEX, PARAM_PROPORTIONS);
    if (index < 0)
      errorLessThan(PARAM_INDEX, PARAM_ZERO);

    return vProportionList[index];

  } catch (string Ex) {
    Ex = "CRecruitmentProcess.getProportion()->" + Ex;
    throw Ex;
  }

  return 0.0;
}

//**********************************************************************
// void CRecruitmentProcess::addAges(int value)
// Add Ages, These Match our Categories 1-1
//**********************************************************************
void CRecruitmentProcess::addAges(int value) {
  vAgesList.push_back(value);
}

//**********************************************************************
// int CRecruitmentProcess::getAges(int index)
// Get an ages element from our vector @ index
//**********************************************************************
int CRecruitmentProcess::getAges(int index) {
  return vAgesList[index];
}

//**********************************************************************
// void CRecruitmentProcess::validate()
// Validate Our Parameters
//**********************************************************************
void CRecruitmentProcess::validate() {
  try {
    // Base Validation
    CProcess::validate();

    // Local Validation
    if (getCategoryCount() == 0)
      errorMissing(PARAM_CATEGORIES);
    if (getProportionCount() == 0)
      errorMissing(PARAM_PROPORTIONS);
    if (getProportionCount() != getCategoryCount())
      throw string(ERROR_EQUAL_CATEGORY_PROPORTION);
    if (getAgesCount() == 0)
      errorMissing(PARAM_AGES);
    if (getAgesCount() != getCategoryCount())
      throw string(ERROR_EQUAL_CATEGORY_AGES);
    if (isZero(dR0))
      errorMissing(PARAM_R0);
    if (sMethod == "")
      errorMissing(PARAM_METHOD);
    if (vSelectivityList.size() > 0)
      errorSupported(PARAM_SELECTIVITIES);
    if (vLayerCategoryList.size() > 0)
      errorSupported(PARAM_LAYERS);
    if (sPenalty != "")
      errorSupported(PARAM_PENALTY);

    if (sMethod != PARAM_UNIFORM)
      throw string(ERROR_UNKNOWN_METHOD + sMethod);
    else
      eMethod = METHOD_UNIFORM;

    // Loop Through Proportions. Make Sure They Equal 1.0
    double dRunningTotal = 0.0;
    foreach(double Prop, vProportionList) {
      dRunningTotal += Prop;
    }
    // See If It is close enough to 1.0
    if (!isSame(dRunningTotal, 1.0))
      errorNotEqual(PARAM_PROPORTIONS, PARAM_ONE);

  } catch(string Ex) {
    Ex = "CRecruitmentProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CRecruitmentProcess::build()
// Build Our Relationships and Indexes
//**********************************************************************
void CRecruitmentProcess::build() {
  try {
    // Base Build
    CProcess::build();

    // Populate Our Ages Index
    if (vAgesIndex.size() <= 0) {
      foreach(int Age, vAgesList) {
        vAgesIndex.push_back(pConfig->getColIndexForAge(Age));
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
// void CRecruitmentProcess::execute()
// Execute
//**********************************************************************
void CRecruitmentProcess::execute() {
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
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          if (eMethod == METHOD_UNIFORM)
            pDiff->addValue(vCategoryIndex[k], vAgesIndex[k], (dAmountPer * vProportionList[k]) );
        }
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
// CRecruitmentProcess::~CRecruitmentProcess()
// Default De-Constructor
//**********************************************************************
CRecruitmentProcess::~CRecruitmentProcess() {
  vProportionList.clear();
  vAgesList.clear();
  vAgesIndex.clear();
}
