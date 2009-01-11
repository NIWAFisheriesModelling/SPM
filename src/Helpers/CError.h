//============================================================================
// Name        : CError.h
// Author      : S.Rasmussen
// Date        : 6/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CERROR_H_
#define CERROR_H_

// Global Headers
#include <string>

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CError {
public:
  // Functions
  static void           error(string value);
  static void           errorMissing(string value);
  static void           errorLessThan(string less, string more);
  static void           errorLessThanEqualTo(string less, string more);
  static void           errorGreaterThan(string more, string less);
  static void           errorGreaterThanEqualTo(string more, string less);
  static void           errorNotEqual(string value1, string value2);
  static void           errorEqualTo(string value1, string value2);
  static void           errorSupported(string value);
private:
  // Functions
  CError() { }
  virtual ~CError() { }
};

#endif /* CERROR_H_ */
