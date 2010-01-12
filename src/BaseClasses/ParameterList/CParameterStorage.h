//============================================================================
// Name        : CParameterStorage.h
// Author      : R.Bian
// Date        : 23/12/2009
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPARAMETERSTORAGE_H_
#define CPARAMETERSTORAGE_H_

// Global Headers
#include <vector>
#include <string>

// Using
using std::vector;
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CParameterStorage {
public:
  // Functions
  CParameterStorage();
  virtual                     ~CParameterStorage();
  vector<string> operator[](int i);
  vector<string> operator[](string str);
  int find(string str);
  int size(){return (int)mParameters.size();}
  void push_in(vector<string> strList){mParameters.push_back(strList);}
  void push_in(string str, int i);

protected:
  // Variables
  vector<vector<string> >     mParameters;
};

#endif /* CPARAMETERSTORAGE_H_ */
