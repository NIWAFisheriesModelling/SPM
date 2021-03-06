//============================================================================
// Name        : CNormalLogPrior.Test.cpp
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// headers
#include <boost/test/unit_test.hpp>
#include <string>

#include "../CEstimateManager.h"
#include "../CEstimate.h"
#include "../../TestFixtures/C1x1_Empty_Fixture.h"
#include "../../TestFixtures/Models/TwoSex_NoEstimates.h"
#include "../../ObjectiveFunction/CObjectiveFunction.h"

// strings
const std::string normal_estimate =
R"(
@estimate
parameter selectivity[FishingSel].a50
lower_bound 1
upper_bound 20
type normal_log
mu 1
sigma 2
)";


//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( NormalLogEstimate, C1x1_Empty_Fixture) {
  addToConfiguration(two_sex_no_estimates);
  addToConfiguration(normal_estimate);
  loadAndRunEnvironment();

  CObjectiveFunction* obj_func = CObjectiveFunction::Instance();
  obj_func->execute();
  BOOST_CHECK_CLOSE(obj_func->getScore(), 2562.1741691002317, 1e-9);

  CEstimate *estimate = CEstimateManager::Instance()->getEstimate("selectivity[FishingSel].a50");
  BOOST_ASSERT(estimate != 0);
  BOOST_CHECK_CLOSE(estimate->getValue(), 8.9819352509647743, 1e-5);

  // Check results
  estimate->setValue(1.0);
  BOOST_CHECK_CLOSE(estimate->getScore(), 0.125, 1e-9);
  estimate->setValue(2.0);
  BOOST_CHECK_CLOSE(estimate->getScore(), 0.70491701215973412, 1e-9);
  estimate->setValue(3.0);
  BOOST_CHECK_CLOSE(estimate->getScore(), 1.099827836602655, 1e-9);
  estimate->setValue(4.0);
  BOOST_CHECK_CLOSE(estimate->getScore(), 1.4049472777990186, 1e-9);
  estimate->setValue(5.0);
  BOOST_CHECK_CLOSE(estimate->getScore(), 1.6558647335731045, 1e-9);
}
#endif /* TEST */
