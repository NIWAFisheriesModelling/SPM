//============================================================================
// Name        : CLocalBHRecruitmentProcess.h
// Author      : S.Rasmussen
// Date        : 13/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description : This is a Beverton-Hold stock recruitment
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CLOCALBHRECRUITMENTPROCESS_H_
#define CLOCALBHRECRUITMENTPROCESS_H_

// Local Headers
#include "../CProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CLocalBHRecruitmentProcess : public CProcess {
public:
  CLocalBHRecruitmentProcess();
  virtual                     ~CLocalBHRecruitmentProcess();
  CProcess*                   clone() { return new CLocalBHRecruitmentProcess(*this); }
  void                        validate();
  void                        build();
  void                        execute();

protected:
  // Variables
  vector<double>              vProportionList;
  double                      dR0;
  vector<int>                 vAgesList;
  vector<int>                 vAgesIndex;
  double                      dSteepness;
  double                      dSigmaR;
  double                      dRho;
  vector<double>              vYCSValues;
  vector<int>                 vYCSYears;
  vector<int>                 vStandardiseYCSYearRange;
  int                         iSSBOffset;
  string                      sR0Layer;
  string                      sSSBLayer;
  CNumericLayer               *pR0Layer;
  CNumericLayer               *pSSBLayer;
};

#endif /* CLOCALBHRECRUITMENTPROCESS_H_ */
