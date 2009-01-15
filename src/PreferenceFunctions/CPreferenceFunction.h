//============================================================================
// Name        : CPreferenceFunction.h
// Author      : S.Rasmussen
// Date        : 28/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2009-01-12 11:44:49 +1300 (Mon, 12 Jan 2009) $
//============================================================================
#ifndef CDIRECTEDPROCESS_H_
#define CDIRECTEDPROCESS_H_

// Local Headers
#include "../BaseClasses/CBaseExecutableObject.h"

// Classes
class CNumericLayer;

//**********************************************************************
//
//
//**********************************************************************
class CPreferenceFunction : public CBaseExecutableObject {
public:
	CPreferenceFunction(CPreferenceFunction *Process = 0);
	virtual                    ~CPreferenceFunction();
	virtual CPreferenceFunction*  clone() = 0;
	string                     getLayerName() { return sLayerName; }
	double                     getAlpha() { return dAlpha; }
	virtual double             getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) = 0;
	virtual void               validate() = 0;
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

#endif /*CDIRECTEDPROCESS_H_*/
