//============================================================================
// Name        : ConstantRecruitment.h
// Author      : S.Rasmussen
// Date        : 20/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST
#ifndef CONSTANTRECRUITMENT_H_
#define CONSTANTRECRUITMENT_H_

const string constant_recruitment =
  "@process constant_recruitment\n"
  "type constant_recruitment\n"
  "categories immature\n"
  "proportions 1.0\n"
  "R0 100\n"
  "ages 1\n";

const string constant_recruitment_all_ages =
  "@process constant_recruitment_all_ages\n"
  "type constant_recruitment\n"
  "categories immature\n"
  "proportions 1.0\n"
  "R0 10000\n"
  "ages 1 2 3 4 5 6 7 8 9 0\n";

#endif /* CONSTANTRECRUITMENT_H_ */
#endif /* TEST */
