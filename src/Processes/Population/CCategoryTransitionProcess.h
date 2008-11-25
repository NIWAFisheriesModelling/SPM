//============================================================================
// Name        : CCategoryTransitionProcess.h
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CCATEGORYTRANSITIONPROCESS_H_
#define CCATEGORYTRANSITIONPROCESS_H_

// Local Headers
#include "../CProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CCategoryTransitionProcess : public CProcess {
public:
  // Functions
	CCategoryTransitionProcess(CCategoryTransitionProcess *Process = 0);
	virtual ~CCategoryTransitionProcess();
	void                       setFrom(string value) { sFrom = value; }
	string                     getFrom() { return sFrom; }
	void                       setTo(string value) { sTo = value; }
	string                     getTo() { return sTo; }
	void                       setProportion(double value) { dProportion = value; }
	double                     getProportion() { return dProportion; }
	CProcess*                  clone() { return (new CCategoryTransitionProcess(this)); }
	void                       validate();
	void                       build();
	void                       execute();

protected:
  // Variables
  string                     sFrom;
  string                     sTo;
  double                     dProportion;
  int                        iFromIndex;
  int                        iToIndex;
};

#endif /*CCATEGORYTRANSITIONPROCESS_H_*/
