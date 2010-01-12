//============================================================================
// Name        : CParameterStorage.cpp
// Author      : R.Bian
// Date        : 5/01/2010
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <vector>
#include <string>
#include <iostream>

// Local headers
//#include "../Translations/Translations.h"
//#include "../RandomStation/Helper.h"
#include "CParameterStorage.h"

// Using
using std::vector;
using std::string;
using std::cout;
using std::endl;

//**********************************************************************
// CParameterStorage::CParameterStorage()
// Constructor
//**********************************************************************
CParameterStorage::CParameterStorage() {
}

// Operator [] with integer index, return the whole string vector
vector<string> CParameterStorage::operator [](int i){
   if (i<(int)mParameters.size()) return mParameters[i];
	else {
		cout<<"Index out of range"<<endl;
		vector<string> strList;
		return strList;
	}
}

// Operator [] with string index, return the vector [2:end]
vector<string> CParameterStorage::operator [](string str){
	int i=find(str);
	vector<string> strList;
	if (i>=0) {
	   strList=mParameters[i];
		strList.erase(strList.begin());
	}
	return strList;
}

// Look for the string and return integer index
int CParameterStorage::find(string str){
	for (int i=0;i<(int)mParameters.size();i++){
		if (str==mParameters[i][0]) return i;
	}
	return -1;
}

// Add a string to mParameters[i]
void CParameterStorage::push_in(string str,int i) {
	while (i>=(int)mParameters.size()){
		vector<string> strList;
		mParameters.push_back(strList);
	   //mParameters[i].push_back(str);
	}
	mParameters[i].push_back(str);
}

//**********************************************************************
// CParameterStorage::~CParameterStorage()
// Destructor
//**********************************************************************
CParameterStorage::~CParameterStorage() {
}
