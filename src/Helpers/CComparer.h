//============================================================================
// Name        : CComparer.h
// Author      : S.Rasmussen
// Date        : 7/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCOMPARER_H_
#define CCOMPARER_H_

// Global Headers
#include <string>

// Local Headers
#include "DefinedValues.h"

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CComparer {
public:
  // Functions
  static bool     isSame(string one, string two, bool useWildCards = true);

  // Inline Functions
  static bool     isZero(double A) { return ( (A < ZERO) && (A > -ZERO) ); }
  static bool     isTrueZero(double A) { return ( (A < TRUE_ZERO) && (A > -TRUE_ZERO) ); }
  static bool     isNonNegative(double A) { return ( 0.0 <= A ); }
  static bool     isPositive(double A) { return ( 0.0 < A ); }
  static bool     isSmall(double A) { return ( (A < SMALL) && (A > -SMALL) ); }
  static bool     isEqual(double A, double B) { return ( ((A-B) < ZERO) && ((A-B) > -ZERO) ); }
  static bool     isSimilar(double A, double B) { return ( ((A-B) < SMALL) && ((A-B) > -SMALL) ); }
  static bool     isBetween(double A, double B, double C) {
    return ( ((A-B) > -ZERO) && ((A-C) < ZERO) );
  }

private:
  // Functions
  CComparer();
  virtual ~CComparer();
};

#endif /* CCOMPARER_H_ */
