//============================================================================
// Name        : CBHRecruitmentProcess.h
// Author      : S.Rasmussen
// Date        : 13/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description : This is a Beverton-Hold stock recruitment
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CBHRECRUITMENTPROCESS_H_
#define CBHRECRUITMENTPROCESS_H_

// Local Headers
#include "../CProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CBHRecruitmentProcess : public CProcess {
public:
  CBHRecruitmentProcess();
  virtual                     ~CBHRecruitmentProcess();
  CProcess*                   clone() { return new CBHRecruitmentProcess(*this); }
  void                        validate();
  void                        build();
  void                        execute();

protected:
  // Variables
  double                      dR0;
  vector<double>              vProportions;
  int                         iAge;
  int                         iAgeIndex;
  double                      dSteepness;
  double                      dSigmaR;
  double                      dRho;
  string                      sSSB;
  vector<double>              vYCSValues;
  vector<int>                 vYCSYears;
  vector<int>                 vStandardiseYCSYearRange;
  int                         iSSBOffset;
  string                      sLayer;
  CNumericLayer               *pLayer;
};

#endif /* CBHRECRUITMENTPROCESS_H_ */
