//============================================================================
// Name        : CError.cpp
// Author      : S.Rasmussen
// Date        : 6/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CError.h"
#include "../Translations/Translations.h"

//**********************************************************************
// void CError::error(string value)
// Throw a basic error
//**********************************************************************
void CError::error(string value) {
  throw value;
}

//**********************************************************************
// void CError::errorMissing(string value)
// Throw an error parameter missing
//**********************************************************************
void CError::errorMissing(string value) {
  string sException = ERROR_MISSING;
  sException += value;
  throw sException;
}

//**********************************************************************
// void CError::errorLessThan(string less, string more)
// Throw an error less than
//**********************************************************************
void CError::errorLessThan(string less, string more) {
  string sException = less;
  sException += ERROR_LESS_THAN;
  sException += more;
  throw sException;
}

//**********************************************************************
// void CError::errorLessThanEqualTo(string less, string more)
// Throw error less than or equal to
//**********************************************************************
void CError::errorLessThanEqualTo(string less, string more) {
  string sException = less;
  sException += ERROR_LESS_EQUAL_TO;
  sException += more;
  throw sException;
}

//**********************************************************************
// void CError::errorGreaterThan(string more, string less)
// Throw error greater than
//**********************************************************************
void CError::errorGreaterThan(string more, string less) {
  string sException = more;
  sException += ERROR_GREATER_THAN;
  sException += less;
  throw sException;
}

//**********************************************************************
// void CError::errorGreaterThanEqualTo(string more, string less)
// Throw error greater than or equal to
//**********************************************************************
void CError::errorGreaterThanEqualTo(string more, string less) {
  string sException = more;
  sException += ERROR_GREATER_EQUAL_TO;
  sException += less;
  throw sException;
}

//**********************************************************************
// void CError::errorNotEqual(string value1, string value2)
// Throw error not equal
//**********************************************************************
void CError::errorNotEqual(string value1, string value2) {
  string sException = value1;
  sException += ERROR_EQUAL_NOT;
  sException += value1;
  throw sException;
}

//**********************************************************************
// void CError::errorEqualTo(string value1, string value2)
// Throw error equal to
//**********************************************************************
void CError::errorEqualTo(string value1, string value2) {
  string sException = value1;
  sException += ERROR_EQUAL_TO;
  sException += value1;
  throw sException;
}

//**********************************************************************
// void CError::errorSupported(string value)
// Throw error not supported
//**********************************************************************
void CError::errorSupported(string value) {
  string sException = value;
  sException += ERROR_SUPPORTED;
  throw sException;
}
