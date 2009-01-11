//============================================================================
// Name        : CConvertor.cpp
// Author      : S.Rasmussen
// Date        : 6/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <sstream>

// Local Headers
#include "CConvertor.h"

// Namespace
using std::ostringstream;
using std::stringstream;

//**********************************************************************
// string CConvertor::doubleToString(double value)
// Convert from double to string
//**********************************************************************
string CConvertor::doubleToString(double value) {
  ostringstream o;
  if (!(o << value))
    return "";
  return o.str();
}

//**********************************************************************
// string CConvertor::intToString(int value)
// Convert from int to string
//**********************************************************************
string CConvertor::intToString(int value) {
  ostringstream o;
  if (!(o << value))
    return "";
  return o.str();
}

//**********************************************************************
// double CConvertor::stringToDouble(string value)
// Convert from string to double
//**********************************************************************
double CConvertor::stringToDouble(string value) {
  double dRet = 0.0;
  stringstream myStream(value);
  if (!(myStream >> dRet))
    throw string("Invalid double");

  return dRet;
}

//**********************************************************************
// int CConvertor::stringToInt(string value)
// Convert from string to int
//**********************************************************************
int CConvertor::stringToInt(string value) {
  int iRet = 0;
  stringstream myStream(value);
  if (!(myStream >> iRet))
    throw string("Invalid integer");

  return iRet;
}

//**********************************************************************
//
//
//**********************************************************************
bool CConvertor::stringToBool(string value) {
  bool bRet = false;

  if ( (value == "true") || (value == "t") )
    bRet = true;
  else if ( (value == "false") || (value == "f"))
    bRet = false;
  else
    throw string("Unknown bool: " + value);

  return bRet;
}

