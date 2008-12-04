//============================================================================
// Name        : CHessian.h
// Author      : S.Rasmussen
// Date        : 2/12/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CHESSIAN_H_
#define CHESSIAN_H_

//**********************************************************************
//
//
//**********************************************************************
class CHessian {
public:
  // Functions
  CHessian();
  virtual                     ~CHessian();
  void                        setValue(int colIndex, int rowIndex) { return; }
  double                      getValue(int colIndex, int rowIndex) { return 0.0; }
  double**                    getGrid() { return pGrid; }
  void                        constrainMagnitude(double max, double minDifference);

protected:
  // Variables
  double                      **pGrid;
  int                         iSize;
};

#endif /* CHESSIAN_H_ */
