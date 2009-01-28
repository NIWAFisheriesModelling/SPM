//============================================================================
// Name        : CParameterList.cpp
// Author      : S.Rasmussen
// Date        : 8/01/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <map>
#include <vector>
#include <string>
#include <iostream>

// Local headers
#include "CParameterList.h"
#include "../../Helpers/ForEach.h"
#include "../../Helpers/CComparer.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CError.h"
#include "../../Translations/Translations.h"

// Using
using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;

//**********************************************************************
// CParameterList::CParameterList(CParameterList *Object = 0)
// Constructor
//**********************************************************************
CParameterList::CParameterList(CParameterList *Object) {

  // Copy Construct
  if (Object != 0) {
  }
}

//**********************************************************************
// void CParameterList::registerAllowed(string name)
// Register an allowed parameter
//**********************************************************************
void CParameterList::registerAllowed(string name) {
  vAllowedParameters.push_back(name);
}

//**********************************************************************
// void CParameterList::addParameter(string name, string value)
// Add a parameter
//**********************************************************************
void CParameterList::addParameter(string name, string value) {
  mParameters[name].push_back(value);
}

//**********************************************************************
//
//
//**********************************************************************
void CParameterList::checkInvalidParameters() {

  map<string, vector<string> >::iterator mvPtr = mParameters.begin();
  while (mvPtr != mParameters.end()) {
    bool bMatch = false;

    foreach(string Parameter, vAllowedParameters) {
      if (Parameter == (*mvPtr).first) {
        bMatch = true;
        break;
      }
    }

    if (!bMatch)
      throw string("Parameter " + (*mvPtr).first + " is not supported");

    mvPtr++;
  }

}

//**********************************************************************
// string CParameterList::getString(string name)
// Return the value of the parameter
//**********************************************************************
string CParameterList::getString(string name, bool optional, string defaultValue) {
  if (!hasParameter(name))
    if (optional)
      return defaultValue;
    else
      CError::errorMissing(name);

  if ((int)mParameters[name].size() == 0)
    throw string("No value defined for " + name); // TODO: Add CError
  if ((int)mParameters[name].size() > 1)
    throw string("Too many parameters for " + name); // TODO: ADD Cerror

  return mParameters[name][0];
}

//**********************************************************************
// double CParameterList::getDouble(string name)
// Return the double for the parameter
//**********************************************************************
double CParameterList::getDouble(string name, bool optional, double defaultValue) {

  double dReturn = defaultValue;

  // Get the string
  string sValue = getString(name, optional);
  // If we have one
  if (sValue != "")
    dReturn = CConvertor::stringToDouble(sValue);

  return dReturn;
}

//**********************************************************************
// int CParameterList::getInt(string name)
// Return the int for the parameter
//**********************************************************************
int CParameterList::getInt(string name) {
  return CConvertor::stringToInt(getString(name));
}

//**********************************************************************
// bool CParameterList::getBool(string name, bool optional, bool defaultValue)
// Return the bool for the parameter
//**********************************************************************
bool CParameterList::getBool(string name, bool optional, bool defaultValue) {

  string value = getString(name, optional);

  // Check for non-existent optional value. If so, return default
  if ( (value == "") && (optional) )
    return defaultValue;

  // Check for False/F match
  if ( (value == CONFIG_FALSE) || (value == CONFIG_FALSE_SHORT) )
    return false;
  // Check for true/T match
  if ( (value == CONFIG_TRUE) || (value == CONFIG_TRUE_SHORT) )
    return true;

  throw string("value not valid true/false for :" + name); // TODO: Add CError for this
}

//**********************************************************************
// void CParameterList::fillVector(vector<string> &list, string name, int offset)
// Fill the vector with strings from our parameter list
//**********************************************************************
void CParameterList::fillVector(vector<string> &list, string name, int offset) {
  if (!hasParameter(name))
    throw string ("Missing parameter " + name); // TODO: FIX THIS

  vector<string>::iterator vPtr = mParameters[name].begin();
  vPtr+= offset; // Move to Offset

  while (vPtr != mParameters[name].end()) {
    list.push_back((*vPtr));
    vPtr++;
  }
}

//**********************************************************************
// void CParameterList::fillVector(vector<double> &list, string name, int offset = 0)
// Fill Vector with Doubles
//**********************************************************************
void CParameterList::fillVector(vector<double> &list, string name, int offset) {
  if (!hasParameter(name))
    throw string ("Missing parameter " + name); // TODO: FIX THIS

  vector<string>::iterator vPtr = mParameters[name].begin();
  vPtr+= offset; // Move to Offset

  while (vPtr != mParameters[name].end()) {
    list.push_back(CConvertor::stringToDouble((*vPtr)));
    vPtr++;
  }
}

//**********************************************************************
// void CParameterList::fillVector(vector<int> &list, string name, int offset)
// Fill Vector with Ints
//**********************************************************************
void CParameterList::fillVector(vector<int> &list, string name, int offset) {
  if (!hasParameter(name))
    throw string ("Missing parameter " + name); // TODO: FIX THIS

  vector<string>::iterator vPtr = mParameters[name].begin();
  vPtr+= offset; // Move to Offset

  while (vPtr != mParameters[name].end()) {
    list.push_back(CConvertor::stringToInt((*vPtr)));
    vPtr++;
  }

}

//**********************************************************************
// void CParameterList::fillArray(double *array, string name, int offset)
//
//**********************************************************************
void CParameterList::fillArray(double *array, int length, string name, int offset) {
  if (!hasParameter(name))
    throw string ("Missing parameter " + name); // TODO: FIX THIS

  if (((int)mParameters[name].size()-offset) != length)
    throw string("Cannot fill array. Number of parameters doesn't match length");

  for (int i = offset; i < (int)mParameters[name].size(); ++i)
    array[i-offset] = CConvertor::stringToDouble(mParameters[name][i]);
}

//**********************************************************************
// void CParameterList::fillArray(string *array, string name, int offset)
//
//**********************************************************************
void CParameterList::fillArray(string *array, int length, string name, int offset) {
  if (!hasParameter(name))
    throw string ("Missing parameter " + name); // TODO: FIX THIS

  if (((int)mParameters[name].size()-offset) != length)
    throw string("Cannot fill array. Number of parameters doesn't match length");

  for (int i = offset; i < (int)mParameters[name].size(); ++i)
    array[i-offset] = mParameters[name][i];
}

//**********************************************************************
// bool CParameterList::hasParameter(string name)
// Do we have this parameter?
//**********************************************************************
bool CParameterList::hasParameter(string name) {
  map<string, vector<string> >::iterator mPtr = mParameters.begin();
  while (mPtr != mParameters.end()) {
    if (CComparer::isSame(name, (*mPtr).first, true))
      return true;

    mPtr++;
  }

  return false;
}

//**********************************************************************
// int CParameterList::countMatches(string name)
// Count how many defined parameters match the name (Wildcards allowed)
//**********************************************************************
int CParameterList::countMatches(string name) {
  int iMatch = 0;

  map<string, vector<string> >::iterator mPtr = mParameters.begin();
  while (mPtr != mParameters.end()) {
    if (CComparer::isSame(name, (*mPtr).first, true))
      iMatch++;
    mPtr++;
  }

  return iMatch;
}

//**********************************************************************
// int CParameterList::countParameterValues(string name)
// Count how many values are assigned to this parameter
//**********************************************************************
int CParameterList::countParameterValues(string name) {
  if (!hasParameter(name))
    throw string ("Missing parameter " + name); // TODO: FIX THIS

  return (int)mParameters[name].size();
}

//**********************************************************************
// string CParameterList::getMatchFullName(string name, int matchNumber = 1)
// Get the Match full (absolute) name
//**********************************************************************
string CParameterList::getMatchFullName(string name, int matchNumber = 1) {
  map<string, vector<string> >::iterator mPtr = mParameters.begin();
  while (mPtr != mParameters.end()) {
    if (CComparer::isSame(name, (*mPtr).first, true)) {
      matchNumber--;

      if (matchNumber == 0)
        return (*mPtr).first;
    }

    mPtr++;
  }

  throw string("Not enough matches for " + name); // TODO: Add CError
}

//**********************************************************************
// CParameterList::~CParameterList()
// Destructor
//**********************************************************************
CParameterList::~CParameterList() {
}
