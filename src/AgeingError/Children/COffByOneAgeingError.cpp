//============================================================================
// Name        : COffByOneAgeingError.cpp
// Author      : S.Rasmussen
// Date        : 18/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "COffByOneAgeingError.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// COffByOneAgeingError::COffByOneAgeingError()
// Default Constructor
//**********************************************************************
COffByOneAgeingError::COffByOneAgeingError() {

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_P1);
  pParameterList->registerAllowed(PARAM_P2);
  pParameterList->registerAllowed(PARAM_K);

  // Register our variables as estimable
  registerEstimable(PARAM_P1,&dP1);
  registerEstimable(PARAM_P2,&dP2);
}

//**********************************************************************
// voidCOffByOneAgeingError::validate()
// Validate the ageing error
//**********************************************************************
void COffByOneAgeingError::validate() {
  try {
    // Base
    CAgeingError::validate();

    // Get our variables
    dP1      = pParameterList->getDouble(PARAM_P1);
    dP2      = pParameterList->getDouble(PARAM_P2);
    iK       = pParameterList->getInt(PARAM_K,true,0);

    // TODO: Complete validation - error messages need to be better phrased
    if (iK > iMaxAge)
      throw("k cannot be larger that the maximum age in the model"); //TODO: Better error message
    if ((dP1+dP2) >= 1.0)
       throw("The sum of p1 and p2 combined must be less than 1.0"); //TODO: Better error message
    if ((dP1) < 0.0)
       throw("p1 must be a non-negative number"); //TODO: Better error message
  if ((dP2) < 0.0)
       throw("p2 must be a non-negative number"); //TODO: Better error message

  } catch (string Ex) {
    Ex = "COffByOneAgeingError.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// voidCOffByOneAgeingError::build()
// Validate the ageing error
//**********************************************************************
void COffByOneAgeingError::build() {

  try {
    mMisMatrix[0][0] = 1 - dP2;
    mMisMatrix[0][1] = dP2;

    for (int i = 1; i < (iNAges-1); ++i) {
      mMisMatrix[i][i-1] = dP1;
      mMisMatrix[i][i]   = 1 - (dP1 + dP2);
      mMisMatrix[i][i+1] = dP2;
    }

    mMisMatrix[iNAges - 1][iNAges - 2] = dP1;

    if(bAgePlusGroup) {
      mMisMatrix[iNAges - 1][iNAges -1] = 1 - dP1;
    } else {
      mMisMatrix[iNAges - 1][iNAges - 1] = 1 - (dP1 + dP2);
    }

    if (iK > iMinAge) {
      for (int i = 0; i < (iK - iMinAge); ++i) {
        for(int j = 0; j < (iK - iMinAge); ++j) {
          mMisMatrix[i][j] = 0;
        }
        mMisMatrix[i][i] = 1;
      }
    }

  } catch (string Ex) {
    Ex = "COffByOneAgeingError.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void COffByOneAgeingError::getExpected(vector<double> &expected)
// Apply ageing error
//**********************************************************************
void COffByOneAgeingError::getExpected(vector<double> &expected) {
  try {
    vector<double> vResult(expected.size(),0);

    for (int i = 0; i < (int)mMisMatrix.size(); ++i) {
      for (int j = 0; j < (int)mMisMatrix[i].size(); ++j) {
        vResult[j] += expected[i] * mMisMatrix[i][j];
      }
    }

    for (int i = 0; i < (int)expected.size(); ++i)
      expected[i] = vResult[i];

  } catch (string Ex) {
    Ex = "COffByOneAgeingError.getExpected(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

}

//**********************************************************************
// COffByOneAgeingError::~COffByOneAgeingError()
// Destructor
//**********************************************************************
COffByOneAgeingError::~COffByOneAgeingError() {
}

/*
# Off By One ageing error

OffByOne<-function(min.age,max.age,dP1,dP2,iK,bAgePlusGroup=T) {
  iNAges <- max.age - min.age + 1
  mMisMatrix<-matrix(0,nrow=iNAges,ncol=iNAges)
  mMisMatrix[1,1] <- 1 - dP2
  mMisMatrix[1,2] <- dP2
  for(i in 2:(iNAges-1)) {
    mMisMatrix[i,i-1] <- dP1
    mMisMatrix[i,i]   <- 1 - (dP1 + dP2)
    mMisMatrix[i,i+1] <- dP2
  }
  mMisMatrix[iNAges,iNAges-1] <- dP1
  if(bAgePlusGroup) {
    mMisMatrix[iNAges,iNAges]<- 1 - dP1
  } else {
    mMisMatrix[iNAges,iNAges] <- 1 - (dP1 + dP2)
  }
  if((iK - min.age)>0) {
    for (i in 1:(iK - min.age)){
      for(j in 1:iNAges) {
        mMisMatrix[i,j] <- 0;
      }
      mMisMatrix[i,i]<-1
    }
  }
  return(mMisMatrix)
}

execute <- function(vExpected, mMisMatrix) {
  vResult<-rep(0,length(vExpected))
  for(i in 1:nrow(mMisMatrix)) {
    for(j in 1:ncol(mMisMatrix)) {
      vResult[j] <- vResult[j] + vExpected[i] * mMisMatrix[i,j]
    }
  }
  return(vResult)
}

Expected<-c(10,20,30,20,15,5)
mMisMatrix<-OffByOne(min.age=3,max.age=8,dP1=0.05,dP2=0.10,iK=4,bAgePlusGroup=T)
#     [,1] [,2] [,3] [,4] [,5] [,6]
#[1,] 1.00 0.00 0.00 0.00 0.00 0.00
#[2,] 0.05 0.85 0.10 0.00 0.00 0.00
#[3,] 0.00 0.05 0.85 0.10 0.00 0.00
#[4,] 0.00 0.00 0.05 0.85 0.10 0.00
#[5,] 0.00 0.00 0.00 0.05 0.85 0.10
#[6,] 0.00 0.00 0.00 0.00 0.05 0.95

execute(Expected,mMisMatrix)
#[1] 11.00 18.50 28.50 20.75 15.00  6.25


mMisMatrix<-OffByOne(min.age=3,max.age=8,dP1=0.05,dP2=0.10,iK=4,bAgePlusGroup=F)
#     [,1] [,2] [,3] [,4] [,5] [,6]
#[1,] 1.00 0.00 0.00 0.00 0.00 0.00
#[2,] 0.05 0.85 0.10 0.00 0.00 0.00
#[3,] 0.00 0.05 0.85 0.10 0.00 0.00
#[4,] 0.00 0.00 0.05 0.85 0.10 0.00
#[5,] 0.00 0.00 0.00 0.05 0.85 0.10
#[6,] 0.00 0.00 0.00 0.00 0.05 0.85

execute(Expected,mMisMatrix)
#[1] 11.00 18.50 28.50 20.75 15.00  5.75


mMisMatrix<-OffByOne(min.age=3,max.age=8,dP1=0.05,dP2=0.10,iK=0,bAgePlusGroup=T)
#     [,1] [,2] [,3] [,4] [,5] [,6]
#[1,] 0.90 0.10 0.00 0.00 0.00 0.00
#[2,] 0.05 0.85 0.10 0.00 0.00 0.00
#[3,] 0.00 0.05 0.85 0.10 0.00 0.00
#[4,] 0.00 0.00 0.05 0.85 0.10 0.00
#[5,] 0.00 0.00 0.00 0.05 0.85 0.10
#[6,] 0.00 0.00 0.00 0.00 0.05 0.95

execute(Expected,mMisMatrix)
#[1] 10.00 19.50 28.50 20.75 15.00  6.25


mMisMatrix<-OffByOne(min.age=3,max.age=8,dP1=0.05,dP2=0.10,iK=3,bAgePlusGroup=F)
#     [,1] [,2] [,3] [,4] [,5] [,6]
#[1,] 0.90 0.10 0.00 0.00 0.00 0.00
#[2,] 0.05 0.85 0.10 0.00 0.00 0.00
#[3,] 0.00 0.05 0.85 0.10 0.00 0.00
#[4,] 0.00 0.00 0.05 0.85 0.10 0.00
#[5,] 0.00 0.00 0.00 0.05 0.85 0.10
#[6,] 0.00 0.00 0.00 0.00 0.05 0.85

execute(Expected,mMisMatrix)
#[1] 10.00 19.50 28.50 20.75 15.00  5.75


*/
