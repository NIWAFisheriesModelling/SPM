//============================================================================
// Name        : CNumericLayer.h
// Author      : S.Rasmussen
// Date        : 1/04/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CNUMERICLAYER_H_
#define CNUMERICLAYER_H_

// Local Headers
#include "../../CLayer.h"

//**********************************************************************
//
//
//**********************************************************************
class CNumericLayer : public CLayer {
public:
  // Functions
	CNumericLayer();
	virtual                  ~CNumericLayer();
  void                      setMin(double value) { dMin = value; }
  double                    getMin() { return dMin; }
  void                      setMax(double value) { dMax = value; }
  double                    getMax() { return dMax; }
  void                      setMinMax(double Min, double Max) { dMin = Min, dMax = Max; }
  void                      defaultMinMax() { dMin = -1.0; dMax = -1.0; }
  virtual void              setValue(int Row, int Col, double Value);
  virtual double            getValue(int RowIndex, int ColIndex, int TargetRow=0, int TargetCol=0)=0;
  virtual bool              checkSpace(int RowIndex, int ColIndex);
  virtual int               countValidSpaces();
  virtual void              validate();
  virtual void              build() = 0;

protected:
  // Variables
  double                     **pGrid;
  double                    dMin;
  double                    dMax;
};

#endif /*CNUMERICLAYER_H_*/
