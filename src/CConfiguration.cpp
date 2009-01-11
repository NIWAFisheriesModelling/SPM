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
  bQuietMode                  = false;
  bPopulateWithDummyData      = false;
  sConfigFile                 = "config.spm";
  sInputValuesFile            = "";
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
    lock lk(configLock);

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
  // Thread-Safe
  lock lk(configLock);

  return vCategoryList[Index];
}

//**********************************************************************
// int CConfiguration::getCategoryIndexForName(string Name)
//
//**********************************************************************
int CConfiguration::getCategoryIndexForName(string Name) {
  try {
    lock lk(configLock);

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
  return (iMinAge+ColIndex);
}

//**********************************************************************
// int CConfiguration::getColIndexForAge(int Age)
// Get the Column Index for our Age
//**********************************************************************
int CConfiguration::getColIndexForAge(int Age) {
  return (Age-iMinAge);
}

//**********************************************************************
// void CConfiguration::addInitializationPhase(string value)
// Add label for Initialization TimeStep to our List
//**********************************************************************
void CConfiguration::addInitializationPhase(string value) {
  try {
    lock lk(configLock);

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

//**********************************************************************
//
//
//**********************************************************************
void CConfiguration::addCommandLineParameter(string value) {
  vCommandLineParameters.push_back(value);
}

//**********************************************************************
//
//
//**********************************************************************
string CConfiguration::getCommandLineParameter(int index) {
  return vCommandLineParameters[index];
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
