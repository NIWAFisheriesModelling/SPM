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
#include <iostream>

// Local Headers
#include "CConvertor.h"

// Namespace
using std::ostringstream;
using std::stringstream;
using std::cout;
using std::endl;

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
  if (!(myStream >> dRet) || ((int)myStream.peek() != (int)std::string::npos))
    throw string("Invalid double: " + value);

  return dRet;
}

//**********************************************************************
// int CConvertor::stringToInt(string value)
// Convert from string to int
//**********************************************************************
int CConvertor::stringToInt(string value) {
  int iRet = 0;
  stringstream myStream(value);
  if (!(myStream >> iRet) || myStream.peek()!= (int)std::string::npos)
    throw string("Invalid integer: " + value);

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
    throw string("Unknown boolean (true/false): " + value);

  return bRet;
}

//**********************************************************************
// void CConvertor::stringToVectorByNewline(string value, vector<string> &lines)
// Convert a string to a vector, split by \n
//**********************************************************************
void CConvertor::stringToVectorByNewline(string value, vector<string> &lines) {
  // Variables
  string  sLine         = value;
  int     iFirstSpace   = -1;

  // Lowercase sline
  for (unsigned i = 0; i < sLine.length(); ++i)
    sLine[i] = tolower(sLine[i]);

  iFirstSpace = sLine.find_first_of('\n');
  if (iFirstSpace == -1) {
    lines.push_back( sLine );
    return;
  }

  while (iFirstSpace >= 0) {
    // Check Difference Between Our Spaces
    if (iFirstSpace > 0)
      lines.push_back( sLine.substr(0, iFirstSpace));

    sLine = sLine.erase(0, iFirstSpace+1);
    iFirstSpace = sLine.find_first_of('\n', 0);
  }
  // If anything is remaining, add it to the list
  if (sLine.length() > 0)
    lines.push_back(sLine);
}

