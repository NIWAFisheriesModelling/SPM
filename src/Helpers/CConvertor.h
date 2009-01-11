//============================================================================
// Name        : CConvertor.h
// Author      : S.Rasmussen
// Date        : 6/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCONVERTOR_H_
#define CCONVERTOR_H_

// Global Headers
#include <string>

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CConvertor {
public:
  // Functions
  static string         doubleToString(double value);
  static string         intToString(int value);
  static double         stringToDouble(string value);
  static int            stringToInt(string value);
  static bool           stringToBool(string value);

private:
  // Functions
  CConvertor() { }
  virtual ~CConvertor() { }
};

#endif /* CCONVERTOR_H_ */
