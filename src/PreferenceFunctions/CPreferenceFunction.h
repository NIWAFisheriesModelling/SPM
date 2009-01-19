//============================================================================
// Name        : CPreferenceFunction.h
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPREFERENCEFUNCTION_H_
#define CPREFERENCEFUNCTION_H_

// Local Includes
#include "../BaseClasses/CBaseExecutableObject.h"

// Forward Decs
class CNumericLayer;

//**********************************************************************
//
//
//**********************************************************************
class CPreferenceFunction : public CBaseExecutableObject {
public:
  CPreferenceFunction(CPreferenceFunction *Process = 0);
  virtual                     ~CPreferenceFunction();
  virtual CPreferenceFunction*  clone() = 0;
  string                     getLayerName() { return sLayerName; }
  double                     getAlpha() { return dAlpha; }
  virtual double             getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) = 0;
  virtual void               validate();
  void                       build();
  void                       execute();

protected:
  // Variables
  double                     dAlpha;
  string                     sLayerName;
  double                     dLayerValue;
  CNumericLayer              *pLayer;
  bool                       bIsStaticLookup;
  double                     dRet;
};

#endif /* CPREFERENCEFUNCTION_H_ */