//============================================================================
// Name        : CHollingMortalityRateProcess.h
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CHOLLINGMORTALITYRATEPROCESS_H_
#define CHOLLINGMORTALITYRATEPROCESS_H_

// Local headers
#include "../CProcess.h"

// Forward-Dec
class CNumericLayer;
class CPenalty;

//**********************************************************************
//
//
//**********************************************************************
class CHollingMortalityRateProcess : public CProcess {
public:
  // Functions
  CHollingMortalityRateProcess();
  virtual                     ~CHollingMortalityRateProcess();
  CProcess*                   clone() { return new CHollingMortalityRateProcess(*this); }
  void                        validate();
  void                        build();
  void                        rebuild();
  void                        execute();
  vector<double>              getMortalityRate() { return vMortalityRate; }
  vector<double>              getMortalityN() { return vMortalityN; }
  vector<double>              getMortalityBiomass() { return vMortalityBiomass; }
  bool                        isAbundance() { return bIsAbundance; }

protected:
  // Variables
  CWorldSquare               **pGrid;
  CNumericLayer              *pLayer;
  string                     sLayer;
  bool                       bIsAbundance;
  bool                       bHollingType2;
  double                     dA;
  double                     dB;
  double                     dBSquared;
  double                     dUMax;
  double                     dMortality;
  vector<double>             vMortalityRate;
  vector<double>             vMortalityN;
  vector<double>             vMortalityBiomass;
  string                     sPenalty;
  CPenalty                   *pPenalty;
};

#endif /* CHOLLINGMORTALITYRATEPROCESS_H_ */
