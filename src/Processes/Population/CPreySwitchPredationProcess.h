//============================================================================
// Name        : CPreySwitchPredationProcess.h
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPRESWITCHPREDATIONPROCESS_H_
#define CPRESWITCHPREDATIONPROCESS_H_

// Local headers
#include "../CProcess.h"

// Forward-Dec
class CPenalty;
class CTimeStepManager;

//**********************************************************************
//
//
//**********************************************************************
class CPreySwitchPredationProcess : public CProcess {
public:
  // Functions
  CPreySwitchPredationProcess();
  virtual                     ~CPreySwitchPredationProcess();
  CProcess*                   clone() { return new CPreySwitchPredationProcess(*this); }
  void                        validate();
  void                        build();
  void                        rebuild();
  void                        execute();
  vector<int>                 getMortalityYears() { return vMortalityYears; }
  vector<vector<double> >     getMortalityRate() { return vMortalityRate; }
  vector<vector<double> >     getMortalityN() { return vMortalityN; }
  vector<vector<double> >     getMortalityBiomass() { return vMortalityBiomass; }
  vector<double>              getPredatorBiomass() { return vPredatorBiomass; }
  vector<string>              getPreyGroups() { return vPreyGroups; }
  bool                        isAbundance() { return bIsAbundance; }
  int                         getPredatorCategoryCount() { return vPredatorCategoryList.size(); }
  int                         getPredatorSelectivityCount() { return vPredatorSelectivityList.size(); }

protected:
  // Variables
  CWorldSquare                **pGrid;
  CWorldSquare                *pWorldSquare;
  bool                        bIsAbundance;
  double                      dCR;
  double                      dUMax;
  vector<double>              vMortality;
  vector<double>              vExploitation;
  vector<double>              vVulnerable;
  double                      dPredatorVulnerable;
  int                         iNPreyGroups;
  vector<double>              vElectivityList;
  vector<string>              vPreyGroups;
  vector<string>              vPreyAllocationList;
  vector<string>              vPredatorCategoryList;
  vector<int>                 vPredatorCategoryIndex;
  vector<string>              vPredatorSelectivityList;
  vector<CSelectivity*>       vPredatorSelectivityIndex;

  double                      dPredatorCurrent;
  vector<int>                 vMortalityYears;
  vector<vector<double> >     vMortalityRate;
  vector<vector<double> >     vMortalityN;
  vector<vector<double> >     vMortalityBiomass;
  vector<double>              vPredatorBiomass;
  string                      sPenalty;
  CPenalty                    *pPenalty;
  CTimeStepManager            *pTimeStepManager;

};

#endif /* CPRESWITCHPREDATIONPROCESS_H_ */
