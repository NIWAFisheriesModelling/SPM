//============================================================================
// Name        : CObservation.h
// Author      : S.Rasmussen
// Date        : 19/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef COBSERVATION_H_
#define COBSERVATION_H_

// Local Headers
#include "../BaseClasses/CBaseExecute.h"
#include "../World/WorldView/CLayerDerivedWorldView.h"
#include "../Likelihoods/CLikelihood.h"

// structures
struct SComparison {
  string sKey;
  double dExpectedValue;
  double dObservedValue;
  double dErrorValue;
  double dScore;
};

// Classes
class CStringLayer;
class CSelectivity;

//**********************************************************************
//
//
//**********************************************************************
class CObservation : public CBaseExecute {
public:
  // Functions
  CObservation();
  virtual                    ~CObservation();
  virtual CObservation*      clone() = 0;
  int                        getYear() { return iYear; }
  int                        getTimeStep() { return iTimeStep; }
  string                     getLayer() { return sLayer; }
  string                     getCategory(int index);
  string                     getSelectivity(int index);
  double                     getScore() { return dScore; }
  void                       fillComparisons(vector<SComparison*> &comparisons);
  virtual void               validate();
  virtual void               build();
  virtual void               execute();

protected:
  // Functions
  void                       saveComparison(string key, double expected, double observed, double errorValue, double score);

  // Variables
  double                     dScore;
  int                        iYear;
  string                     sTimeStep;
  int                        iTimeStep;
  string                     sLayer;
  CStringLayer               *pLayer;
  vector<string>             vCategoryNames;
  vector<int>                vCategories;
  vector<string>             vSelectivityNames;
  vector<CSelectivity*>      vSelectivities;
  vector<SComparison*>       vComparisons;
  CLayerDerivedWorldView     *pWorldView;
  string                     sLikelihood;
  string                     sSimulationLikelihood;
  CLikelihood                *pLikelihood;
  bool                       bSimulationRunMode;

};

#endif /*COBSERVATION_H_*/
