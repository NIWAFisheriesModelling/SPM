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
#include "../BaseClasses/CBaseBuildableObject.h"

// Classes
class CEstimate;

//**********************************************************************
//
//
//**********************************************************************
class CProfile : public CBaseBuildableObject {
public:
	CProfile(CProfile *Profile = 0);
	virtual                    ~CProfile();
  void                       setN(double value) { dN = value; }
  double                     getN() { return dN; }
  void                       setL(double value) { dL = value; }
  double                     getL() { return dL; }
  void                       setU(double value) { dU = value; }
  double                     getU() { return dU; }
  void                       setParameter(string value) { sParameter = value; }
  string                     getParameter() { return sParameter; }
  double                     getCurrent() { return dCurrent; }
  void                       setEnabled();
  bool                       doStep();
  CProfile*                  clone() { return (new CProfile(this)); }
  void                       validate();
  void                       build();
  void                       setEnabled(bool value);

protected:
  // Variables
  double                     dN;
  double                     dL;
  double                     dU;
  double                     dCurrent;
  string                     sParameter;
  CEstimate*                 pTarget;
};

#endif /*CPROFILE_H_*/
