//============================================================================
// Name        : CLogNormalLikelihood.Test.cpp
// Author      : S.Rasmussen
// Date        : 29/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../Factory/CLikelihoodFactory.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(LogNormalLikelihood ) {
  // Get Likelihood
  CLikelihood *pLikelihood = CLikelihoodFactory::buildLikelihood(PARAM_PROPORTIONS_AT_AGE, PARAM_LOGNORMAL);


  // Check results

  // clear memory
  delete pLikelihood;
}

#endif /* TEST */
