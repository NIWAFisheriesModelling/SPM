//============================================================================
// Name        : CConfiguration.cpp
// Author      : S.Rasmussen
// Date        : 30/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CConfiguration.h"
#include "Translations/Translations.h"

// Singleton Variable
CConfiguration* CConfiguration::clInstance = 0;

//**********************************************************************
// CConfiguration::CConfiguration()
// Default Constructor
//**********************************************************************
CConfiguration::CConfiguration() {
  // Variables
  bVerboseMode                = false;
  bPopulateWithDummyData      = false;
  sConfigPath                 = "";
  iNumberOfYearsToRun         = 0;
  iNumberOfYearsToProject     = 0;
  iNumberOfTimeSteps          = 0;
  iMinAge                     = -1;
  iMaxAge                     = -1;
  bUseAgePlus                 = false;
  iHumanStartYear             = 2000;
  iNumberOfThreads            = 1;
  bUseEstimateValues          = false;
}

//**********************************************************************
// CConfiguration* CConfiguration::Instance()
// Instance Method - Singleton
//**********************************************************************
CConfiguration* CConfiguration::Instance() {
  if (clInstance == 0)
    clInstance = new CConfiguration();
  return clInstance;
}

//**********************************************************************
// void CConfiguration::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CConfiguration::Destroy() {
  if (clInstance != 0) {
    delete clInstance;
    clInstance = 0;
  }
}

//**********************************************************************
// void CConfiguration::addCategory(string value)
// Add Category to our List
//**********************************************************************
void CConfiguration::addCategory(string value) {
  try {
    // Validate
    if (value == "")
      throw string(ERROR_MISSING + string(PARAM_PARAMETER));

    // Check for duplicates
    for (int i = 0; i < (int)vCategoryList.size(); ++i) {
      if (vCategoryList[i] == value)
        throw string(ERROR_DUPLICATE_CATEGORY + vCategoryList[i]);
    }

    // All good.
    vCategoryList.push_back(value);

  } catch (string Ex) {
    Ex = "CRuntimeController.addCategory()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// string CConfiguration::getCategoryNameForIndex(int Index)
// Get Category Name for Index
//**********************************************************************
string CConfiguration::getCategoryNameForIndex(int Index) {
#ifndef OPTIMISE
  try {
    // Validate
    if (Index < 0)
      throw string(PARAM_INDEX + string(ERROR_LESS_THAN) + string(PARAM_ZERO));
    if (Index >= (int)vCategoryList.size())
      throw string(PARAM_INDEX + string(ERROR_GREATER_EQUAL_TO) + string(PARAM_CATEGORIES));

  } catch (string Ex) {
    Ex = "CRuntimeController.getCategoryNameForIndex()->" + Ex;
    throw Ex;
  }
#endif

  return vCategoryList[Index];
}

//**********************************************************************
// int CConfiguration::getCategoryIndexForName(string Name)
//
//**********************************************************************
int CConfiguration::getCategoryIndexForName(string Name) {
  try {
    // Validate
    for (int i = 0; i < (int)vCategoryList.size(); ++i) {
      if (vCategoryList[i] == Name)
        return i;
    }

    throw string(ERROR_UNKNOWN_CATEGORY + Name);

  } catch (string Ex) {
    Ex = "CRuntimeController.getCategoryNameForIndex()->" + Ex;
    throw Ex;
  }

  return -1;
}

//**********************************************************************
// int CConfiguration::getAgeForColIndex(int ColIndex)
// Get the Age for our Column Index
//**********************************************************************
int CConfiguration::getAgeForColIndex(int ColIndex) {
#ifndef OPTIMISE
  try {
    if ((ColIndex+iMinAge) > iMaxAge)
      throw string(PARAM_COLUMN + string(ERROR_GREATER_THAN) + string(PARAM_MAX_AGE));
    if (ColIndex < 0)
      throw string(PARAM_COLUMN_INDEX + string(ERROR_LESS_THAN) + string(PARAM_ZERO));
#endif

    return (iMinAge+ColIndex);

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CConfiguration.getAgeForColIndex()->" + Ex;
    throw Ex;
  }

  return -1;
#endif
}

//**********************************************************************
// int CConfiguration::getColIndexForAge(int Age)
// Get the Column Index for our Age
//**********************************************************************
int CConfiguration::getColIndexForAge(int Age) {
#ifndef OPTIMISE
  try {
    if (Age < iMinAge)
      throw string(PARAM_AGE + string(ERROR_LESS_THAN) + string(PARAM_MIN_AGE));
    if (Age > iMaxAge)
      throw string(PARAM_AGE + string(ERROR_GREATER_THAN) + string(PARAM_MAX_AGE));
#endif

    return (Age-iMinAge);

#ifndef OPTIMISE
  } catch (string Ex) {
    Ex = "CConfiguration.getColIndexForAge()->" + Ex;
    throw Ex;
  }

  return -1;
#endif
}

//**********************************************************************
// void CConfiguration::addInitializationPhase(string value)
// Add label for Initialization TimeStep to our List
//**********************************************************************
void CConfiguration::addInitializationPhase(string value) {
  try {
    vInitializationList.push_back(value);
  } catch (string Ex) {
    Ex = "CConfiguration.addInitializationPhase()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// string CConfiguration::getInitializationPhase(int index)
//
//**********************************************************************
string CConfiguration::getInitializationPhase(int index) {
  try {
    lock lk(configLock);
    return vInitializationList[index];

  } catch (string Ex) {
    Ex = "CConfiguration.getInitializationPhase()->" + Ex;
    throw Ex;
  }

  return "";
}

//****************\******************************************************
// void CConfiguration::validate()
// Validate our Configuration
//**********************************************************************
void CConfiguration::validate() {
  try {
    // Validate our Local Variables
    if (getCategoryCount() <= 0)
      throw string(ERROR_MISSING + string(PARAM_CATEGORIES));
    if (getMinAge() < 0)
      throw string(ERROR_MISSING + string(PARAM_MIN_AGE));
    if (getMaxAge() < 0)
      throw string(ERROR_MISSING + string(PARAM_MAX_AGE));
    if (getMinAge() > getMaxAge())
      throw string(PARAM_MIN_AGE + string(ERROR_GREATER_THAN) + string(PARAM_MAX_AGE));
    if (getNumberOfYearsToRun() == 0)
      throw string(ERROR_MISSING + string(PARAM_RUN_YEARS));
    if (getNumberOfTimeSteps() == 0)
      throw string(ERROR_MISSING + string(PARAM_TIME_STEP));

  } catch (string Ex) {
    Ex = "CConfiguration.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CConfiguration::~CConfiguration()
// Default De-Constructor
//**********************************************************************
CConfiguration::~CConfiguration() {
}
