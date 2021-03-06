//============================================================================
// Name        : CEventMortalityProcess.h
// Author      : S.Rasmussen
// Date        : 9/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CEVENTMORTALITYPROCESS_H_
#define CEVENTMORTALITYPROCESS_H_

// Local Headers
#include "../CProcess.h"

// Classes
class CTimeStepManager;
class CPenalty;
class CNumericLayer;

//**********************************************************************
//
//
//**********************************************************************
class CEventMortalityProcess : public CProcess {
public:
  // Functions
  CEventMortalityProcess();
  virtual                    ~CEventMortalityProcess();
  CProcess*                  clone() { return new CEventMortalityProcess(*this); }
  double                     getUMax() { return dUMax; }
  int                        getYearsCount() { return vYearsList.size(); }
  int                        getYears(int index);
  int                        getLayersCount() { return vLayersList.size(); }
  string                     getLayers(int index);
  void                       validate();
  void                       build();
  void                       execute();

protected:
  // Variables
  double                     dUMax;
  double                     dCatch;
  double                     dVulnerable;
  double                     dExploitation;
  vector<int>                vYearsList;
  vector<string>             vLayersList;
  vector<CNumericLayer*>     vLayersIndex;
  CNumericLayer              *pLayer;
  int                        iCurrentYear;
  bool                       bYearMatch;
  CTimeStepManager           *pTimeStepManager;
  string                     sPenalty;
  CPenalty                   *pPenalty;
};

#endif /*CEVENTMORTALITYPROCESS_H_*/
