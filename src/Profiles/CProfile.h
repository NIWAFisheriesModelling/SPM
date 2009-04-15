//============================================================================
// Name        : CProfile.h
// Author      : S.Rasmussen
// Date        : 2/03/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CPROFILE_H_
#define CPROFILE_H_

// Local Headers
#include "../BaseClasses/CBaseBuild.h"

// Classes
class CEstimate;

//**********************************************************************
//
//
//**********************************************************************
class CProfile : public CBaseBuild {
public:
  CProfile();
  virtual                    ~CProfile();
  CProfile*                  clone() { return (new CProfile(*this)); }
  double                     getStep() { return dStep; }
  double                     getL() { return dL; }
  double                     getU() { return dU; }
  string                     getParameter() { return sParameter; }
  double                     getCurrent() { return dCurrent; }
  void                       setEnabled();
  bool                       doStep();
  void                       validate();
  void                       build();
  void                       setEnabled(bool value);

protected:
  // Variables
  int                        iN;
  double                     dStep;
  double                     dL;
  double                     dU;
  double                     dCurrent;
  string                     sParameter;
  CEstimate*                 pTarget;
};

#endif /*CPROFILE_H_*/
