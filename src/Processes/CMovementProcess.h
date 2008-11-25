//============================================================================
// Name        : CMovementProcess.h
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CMOVEMENTPROCESS_H_
#define CMOVEMENTPROCESS_H_

// Local Headers
#include "CProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CMovementProcess : public CProcess {
public:
  // Functions
	CMovementProcess(CMovementProcess *Process = 0);
	virtual                    ~CMovementProcess();
	void                       setHexMode(bool value) { bHexMode = value; }
	bool                       getHexMode() { return bHexMode; }
	void                       setMethod(string value);
	string                     getMethod() { return sMethod; }
	void                       setProportion(double value) { dProportion = value; }
	double                     getProportion() { return dProportion; }
	virtual CProcess*          clone() = 0;
	virtual void               validate();
	virtual void               build();
	virtual void               execute();

protected:
  // Functions
  void                       doMove(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty);
  void                       moveUp(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty);
  void                       moveDown(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty);
  void                       moveLeft(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty);
  void                       moveRight(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty);
  void                       moveLeftUp(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty);
  void                       moveLeftDown(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty);

  // Variables
  bool                       bHexMode;
  string                     sMethod;
  double                     dProportion;
  CWorldSquare               *pTargetBase;
  CWorldSquare               *pTargetDiff;
};

#endif /*CMOVEMENTPROCESS_H_*/
