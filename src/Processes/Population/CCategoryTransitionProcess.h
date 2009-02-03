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
	CCategoryTransitionProcess();
	virtual                    ~CCategoryTransitionProcess();
	CProcess*                  clone() { return new CCategoryTransitionProcess(*this); }
	void                       validate();
	void                       build();
	void                       execute();

protected:
  // Variables
  string                     sFrom;
  string                     sTo;
  double                     dN;
  int                        iFromIndex;
  int                        iToIndex;
  string                     sSelectivity;
  CSelectivity*              pSelectivity;
};

#endif /*CCATEGORYTRANSITIONPROCESS_H_*/
