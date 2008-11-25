//============================================================================
// Name        : CDirectedProcess.h
// Author      : S.Rasmussen
// Date        : 28/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
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
class CDirectedProcess : public CBaseExecutableObject {
public:
	CDirectedProcess(CDirectedProcess *Process = 0);
	virtual                    ~CDirectedProcess();
	void                       setType(string value) { sType = value; }
	string                     getType() { return sType; }
	void                       setAlpha(double value) { dAlpha = value; }
	double                     getAlpha() { return dAlpha; }
	void                       setLayerName(string value) { sLayerName = value; }
	string                     getLayerName() { return sLayerName; }
	virtual double             getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) = 0;
	virtual CDirectedProcess*  clone() = 0;
	virtual void               validate() = 0;
	void                       build();
	void                       execute();

protected:
  // Variables
  string                     sType;
  double                     dAlpha;
  string                     sLayerName;
  double                     dLayerValue;
  CNumericLayer              *pLayer;
  bool                       bIsStaticLookup;
  double                     dRet;
};

#endif /*CDIRECTEDPROCESS_H_*/
