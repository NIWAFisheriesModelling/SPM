//============================================================================
// Name        : CSelectivityManager.cpp
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description : << See CSelectivityManager.h >>
// $Date$
//============================================================================

// Local Headers
#include "CSelectivityManager.h"
#include "CSelectivity.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"

// Single Static variable
boost::thread_specific_ptr<CSelectivityManager> CSelectivityManager::clInstance;

//**********************************************************************
// CSelectivityManager::CSelectivityManager()
// Default Constructor
//**********************************************************************
CSelectivityManager::CSelectivityManager() {
}

//**********************************************************************
// CSelectivityManager* CSelectivityManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CSelectivityManager* CSelectivityManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CSelectivityManager());
  return clInstance.get();
}

//**********************************************************************
// void CSelectivityManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CSelectivityManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CSelectivityManager::addSelectivity(CSelectivity* Selectivity)
// Add Selectivity
//**********************************************************************
void CSelectivityManager::addSelectivity(CSelectivity* Selectivity) {
  vSelectivityList.push_back(Selectivity);
}

//**********************************************************************
// int CSelectivityManager::getSelectivityIndex(string Label)
// get The selectivity Index
//**********************************************************************
int CSelectivityManager::getSelectivityIndex(string Label) {
  try {
    vector<CSelectivity*>::iterator vPtr = vSelectivityList.begin();
    int iCount = 0;
    while (vPtr != vSelectivityList.end()) {
       if ((*vPtr)->getLabel() == Label)
         return iCount;
      iCount++;
      vPtr++;
    }

    throw string(ERROR_UNKNOWN_SELECTIVITY + Label);

  } catch (string Ex) {
    Ex = "CSelectivityManager.getSelectivityIndex()->" + Ex;
    throw Ex;
  }

  return -1;
}

//**********************************************************************
// CSelectivity* CSelectivityManager::getSelectivity(string Label)
// Get our Selectivity
//**********************************************************************
CSelectivity* CSelectivityManager::getSelectivity(string Label) {
  try {
    vector<CSelectivity*>::iterator vPtr = vSelectivityList.begin();
    while (vPtr != vSelectivityList.end()) {
       if ((*vPtr)->getLabel() == Label)
         return (*vPtr);
      vPtr++;
    }

    throw string(ERROR_UNKNOWN_SELECTIVITY + Label);

  } catch (string Ex) {
    Ex = "CSelectivityManager.getSelectivity()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// CSelectivity* CSelectivityManager::getSelectivity(int index)
// Get the selectivity from our vector @ index
//**********************************************************************
CSelectivity* CSelectivityManager::getSelectivity(int index) {
  try {
    if (index >= (int)vSelectivityList.size())
      CError::errorGreaterThanEqualTo(PARAM_INDEX, PARAM_SELECTIVITIES);
    if (index < 0)
      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);

    return vSelectivityList[index];

  } catch (string Ex) {
    Ex = "CSelectivityManaget.getSelectivity()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CSelectivityManager::clone(CSelectivityManager *Manager)
// Clone
//**********************************************************************
void CSelectivityManager::clone(CSelectivityManager *Manager) {
  try {

//    for (int i = 0; i < Manager->getSelectivityCount(); ++i) {
//      CSelectivity *pSelectivity = Manager->getSelectivity(i);
//      vSelectivityList.push_back(pSelectivity->clone());
//    }
    // TODO: Fix Clones
  } catch (string Ex) {
    Ex = "CSelectivityManager.clone()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSelectivityManager::Validate()
// Validate Selectivities
//**********************************************************************
void CSelectivityManager::validate() {
  try {
    // Validate
    foreach(CSelectivity *Selectivity, vSelectivityList) {
      Selectivity->validate();
    }

    // Check For duplicate labels
    map<string, int>                  mSelectivityList;
    foreach(CSelectivity *Selectivity, vSelectivityList) {
      mSelectivityList[Selectivity->getLabel()] += 1;

      if (mSelectivityList[Selectivity->getLabel()] > 1)
        throw string(ERROR_DUPLICATE_LABEL + Selectivity->getLabel());
    }
  } catch(string Ex) {
    Ex  = "CSelectivityManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSelectivityManager::build()
// build
//**********************************************************************
void CSelectivityManager::build() {
#ifndef OPTIMISE
  try {
#endif

    // build Selectivities
    foreach(CSelectivity *Selectivity, vSelectivityList) {
      Selectivity->build();
    }

#ifndef OPTIMISE
  } catch(string Ex) {
    Ex  = "CSelectivityManager.build()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CSelectivityManager::rebuild()
// rebuild
//**********************************************************************
void CSelectivityManager::rebuild() {
#ifndef OPTIMISE
  try {
#endif

    // build Selectivities
    foreach(CSelectivity *Selectivity, vSelectivityList) {
      Selectivity->rebuild();
    }

#ifndef OPTIMISE
  } catch(string Ex) {
    Ex  = "CSelectivityManager.rebuild()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CSelectivityManager::~CSelectivityManager()
// Default De-Constructor
//**********************************************************************
CSelectivityManager::~CSelectivityManager() {
  vector<CSelectivity*>::iterator vPtr;
  vPtr = vSelectivityList.begin();
  while (vPtr != vSelectivityList.end()) {
    delete (*vPtr);
    vPtr++;
  }
  vSelectivityList.clear();
}
