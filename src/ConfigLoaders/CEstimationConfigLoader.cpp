//============================================================================
// Name        : CEstimationConfigLoader.cpp
// Author      : S.Rasmussen
// Date        : 17/02/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CEstimationConfigLoader.h"
#include "../Estimates/CEstimate.h"
#include "../Minimizers/DESolver/CDESolverInterface.h"
#include "../Minimizers/GammaDiff/CGammaDiffInterface.h"
#include "../Observations/Children/CProportionsAtAgeObservation.h"
#include "../Observations/Children/CProportionsByCategoryObservation.h"
#include "../Observations/Children/CAbundanceObservation.h"
#include "../Priors/Children/CUniformPrior.h"
#include "../Priors/Children/CNormalPrior.h"
#include "../Priors/Children/CNormalByStdevPrior.h"
#include "../Priors/Children/CLogNormalPrior.h"
#include "../Priors/Children/CUniformLogPrior.h"
#include "../Priors/Children/CNormalLogPrior.h"
#include "../Priors/Children/CBetaPrior.h"
#include "../Penalties/CPenalty.h"
#include "../Qs/CQ.h"
#include "../Profiles/CProfile.h"

//**********************************************************************
// CEstimationConfigLoader::CEstimationConfigLoader()
// Default Constructor
//**********************************************************************
CEstimationConfigLoader::CEstimationConfigLoader(string Directory) {
  // Set File Name and Load The File
  setDirectory(Directory);
  setFileName(CONFIG_FILE_ESTIMATION);
  loadConfigFile();

  // Vars
  pWorld                     = CWorld::Instance();
  pMinimizerManager          = CMinimizerManager::Instance();
  pEstimateManager           = CEstimateManager::Instance();
  pMCMC                      = CMCMC::Instance();
  pProfileManager            = CProfileManager::Instance();
  pObservationManager        = CObservationManager::Instance();
  pPriorManager              = CPriorManager::Instance();
  pPenaltyManager            = CPenaltyManager::Instance();
  pQManager                  = CQManager::Instance();
}

//**********************************************************************
// void CEstimationConfigLoader::processConfigFile()
// Process our Config File
//**********************************************************************
void CEstimationConfigLoader::processConfigFile() {
  try {
    if (vConfigList.size() == 0)
      throw string(ERROR_EMPTY_FILE);

    // Loop Through Our Lines
    vConfigPtr = vConfigList.begin();
    while(vConfigPtr != vConfigList.end()) {
      if ((int)(*vConfigPtr).find(CONFIG_SECTION_SYMBOL) >= 0) {

        // Populate Our Parameters
        populateParameters();
        if (vParameterList.size() == 0)
          throw string(ERROR_EMPTY_PARAMETER);

        // Check What Section we are in
        if (vParameterList[0] == CONFIG_SECTION_MPD)
          loadMPD();
        else if (vParameterList[0] == CONFIG_SECTION_MINIMIZER)
          loadMinimizer();
        else if (vParameterList[0] == CONFIG_SECTION_MCMC)
          loadMCMC();
        else if (vParameterList[0] == CONFIG_SECTION_PROFILE)
          loadProfile();
        else if (vParameterList[0] == CONFIG_SECTION_PROP_AT_AGE)
          loadProportionsAtAge();
        else if (vParameterList[0] == CONFIG_SECTION_PROP_BY_CATEGORY)
          loadProportionsByCategory();
        else if (vParameterList[0] == CONFIG_SECTION_ABUNDANCE)
          loadAbundance();
        else if (vParameterList[0] == CONFIG_SECTION_AGEING)
          loadAgeingError();
        else if (vParameterList[0] == CONFIG_SECTION_ESTIMATE)
          loadEstimate();
        else if (vParameterList[0] == CONFIG_SECTION_PRIOR)
          loadPrior();
        else if (vParameterList[0] == CONFIG_SECTION_PENALTY)
          loadPenalty();
        else if (vParameterList[0] == CONFIG_SECTION_Q)
          loadQ();
        else
          throw string(ERROR_UNKNOWN_SECTION + vParameterList[0]);

        continue; // We Incremented Elsewhere
      } else
        throw string(ERROR_UNKNOWN_SYNTAX + (*vConfigPtr));

      vConfigPtr++;
    }
  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.processConfigFile()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimationConfigLoader::loadMPD()
// Load @mpd
//**********************************************************************
void CEstimationConfigLoader::loadMPD() {
  try {
    // @simulation should have no extra parameters
    if (vParameterList.size() != 1)
      throw string(ERROR_QTY_MORE_PARAMETERS);

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_MINIMIZER))
          pMinimizerManager->setActiveMinimizer(vParameterList[1]);
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadMPD()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimationConfigLoader::loadMinimizer()
// Load our @minimizer
//**********************************************************************
void CEstimationConfigLoader::loadMinimizer() {
  try {
    // Should have 1 parameter (Label)
    if (vParameterList.size() != 2)
      throw string(ERROR_QTY_ONE_PARAMETERS);

    // Inc
    vConfigPtr++;
    // Populate Parameters
    populateParameters();

    if (vParameterList.size() == 0)
      throw string(ERROR_EMPTY_PARAMETER);
    if (vParameterList.size() != 2)
      throw string(ERROR_QTY_ONE_PARAMETERS);

    // Must Be Type
    if (vParameterList[0] != PARAM_TYPE)
      throw string(ERROR_QTY_ONE_PARAMETERS);
    if (vParameterList.size() != 2)
      throw string(ERROR_QTY_ONE_PARAMETERS);

    if (vParameterList[1] == PARAM_DESOLVER)
      loadMinimizer_DeSolver();
    else if (vParameterList[1] == PARAM_GAMMADIFF)
      loadMinimizer_GammaDiff();
    else
      throw string(ERROR_UNKNOWN_PARAM + vParameterList[1]);

  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadMinimizer()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimationConfigLoader::loadMinimizer_DeSolver()
//
//**********************************************************************
void CEstimationConfigLoader::loadMinimizer_DeSolver() {
  try {
    CDESolverInterface *pMinimizer = new CDESolverInterface();
    pMinimizer->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++; // Skip type =
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (!loadBaseMinimizerAttributes(pMinimizer)) {
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
        }
      }
      vConfigPtr++;
    }
    pMinimizerManager->addMinimizer(pMinimizer);

  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadMinimizer_DeSolver()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimationConfigLoader::loadMinimizer_GammaDiff()
//
//**********************************************************************
void CEstimationConfigLoader::loadMinimizer_GammaDiff() {
  try {
    CGammaDiffInterface *pMinimizer = new CGammaDiffInterface();
    pMinimizer->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++; // Skip type =
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (!loadBaseMinimizerAttributes(pMinimizer)) {
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
        }
      }
      vConfigPtr++;
    }
    pMinimizerManager->addMinimizer(pMinimizer);


  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadMinimizer_GammaDiff()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimationConfigLoader::loadMCMC()
// load @mcmc
//**********************************************************************
void CEstimationConfigLoader::loadMCMC() {
  try {
    // @MCMC should have no extra parameters
      if (vParameterList.size() != 1)
        throw string(ERROR_QTY_MORE_PARAMETERS);

      // Load Next Line
      vConfigPtr++;
      while(vConfigPtr != vConfigList.end()) {
        populateParameters();

        if (vParameterList.size() > 0) {
          if (newSection())
            break;

          // Check Section
          if (checkLine(PARAM_START))
            pMCMC->setStart(getIntValue(1));
          else if (checkLine(PARAM_LENGTH))
            pMCMC->setLength(getIntValue(1));
          else if (checkLine(PARAM_KEEP))
            pMCMC->setKeep(getIntValue(1));
          else if (checkLine(PARAM_ADAPTIVE_STEP_SIZE))
            pMCMC->setAdaptiveStepsize(getBoolValue(1));
          else if (checkLine(PARAM_ADAPT_AT, 1, MAX_PARAMS))
            for (int i = 1; i < (int)vParameterList.size(); ++i)
              pMCMC->addAdaptAt(getIntValue(i));
          else if (checkLine(PARAM_PROPOSAL_T))
            pMCMC->setProposalT(getBoolValue(1));
          else if (checkLine(PARAM_DF))
            pMCMC->setDf(getIntValue(1));
          else
            throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
        }
        vConfigPtr++;
      }

  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadMCMC()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimationConfigLoader::loadProfile()
// Load @profile
//**********************************************************************
void CEstimationConfigLoader::loadProfile() {
  try {
    // @MCMC should have no extra parameters
      if (vParameterList.size() != 1)
        throw string(ERROR_QTY_MORE_PARAMETERS);

      CProfile *pProfile = new CProfile();

      // Load Next Line
      vConfigPtr++;
      while(vConfigPtr != vConfigList.end()) {
        populateParameters();

        if (vParameterList.size() > 0) {
          if (newSection())
            break;

          // Check Section
          if (checkLine(PARAM_PARAMETER))
            pProfile->setParameter(vParameterList[1]);
          else if (checkLine(PARAM_N))
            pProfile->setN(getDoubleValue(1));
          else if (checkLine(PARAM_L))
            pProfile->setL(getDoubleValue(1));
          else if (checkLine(PARAM_U))
            pProfile->setU(getDoubleValue(1));
          else
            throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
        }
        vConfigPtr++;
      }

      pProfileManager->addProfile(pProfile);
  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadProfile()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimationConfigLoader::loadProportionsAtAge()
// Load @Proportions-at-age
//**********************************************************************
void CEstimationConfigLoader::loadProportionsAtAge() {
  try {
    // Get Label
    CProportionsAtAgeObservation *pObservation = new CProportionsAtAgeObservation();
    pObservation->setLabel(getLabel());

    // Load Next Line
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_YEAR))
          pObservation->setYear(getIntValue(1));
        else if (checkLine(PARAM_TIME_STEP))
          pObservation->setTimeStep(getIntValue(1));
        else if (checkLine(PARAM_CATEGORIES, 1, MAX_PARAMS))
          for (int i = 1; i < (int)vParameterList.size(); ++i)
            pObservation->addCategory(vParameterList[i]);
        else if (checkLine(PARAM_LAYER_NAME))
          pObservation->setLayer(vParameterList[1]);
        else if (checkLine(PARAM_SELECTIVITIES, 1, MAX_PARAMS))
          for (int i = 1; i < (int)vParameterList.size(); ++i)
            pObservation->addSelectivity(vParameterList[i]);
        else if (checkLine(PARAM_MIN_AGE))
          pObservation->setMinAge(getIntValue(1));
        else if (checkLine(PARAM_MAX_AGE))
          pObservation->setMaxAge(getIntValue(1));
        else if (checkLine(PARAM_AGE_PLUS_GROUP))
          pObservation->setAgePlus(getBoolValue(1));
        else if (checkLine(PARAM_RESCALE))
          pObservation->setRescale(getBoolValue(1));
        else if (checkLine(PARAM_DIST))
          pObservation->setDist(vParameterList[1]);
        else if (checkLine(PARAM_N_PROCESS_ERROR))
          pObservation->setNProcessError(getDoubleValue(1));
        else if (checkLine(PARAM_OBS, 2, MAX_PARAMS))
          for (int i = 2; i < (int)vParameterList.size(); ++i)
            pObservation->addProportion(vParameterList[1], getDoubleValue(i, true));
        else if (checkLine(PARAM_R))
          pObservation->setR(getDoubleValue(1));
        else if (checkLine(PARAM_N, 1, MAX_PARAMS))
          for(int i = 2; i < (int)vParameterList.size(); ++i)
            pObservation->addN(vParameterList[1], getDoubleValue(i, true));
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
    pObservationManager->addObservation(pObservation);

  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadProportionsAtAge()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
//
//
//**********************************************************************
void CEstimationConfigLoader::loadProportionsByCategory() {
  try {
    // Get Label
    CProportionsByCategoryObservation *pObservation = new CProportionsByCategoryObservation();
    pObservation->setLabel(getLabel());

    // Load Next Line
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_YEAR))
          pObservation->setYear(getIntValue(1));
        else if (checkLine(PARAM_TIME_STEP))
          pObservation->setTimeStep(getIntValue(1));
        else if (checkLine(PARAM_CATEGORIES, 1, MAX_PARAMS))
          for (int i = 1; i < (int)vParameterList.size(); ++i)
            pObservation->addCategory(vParameterList[i]);
        else if (checkLine(PARAM_POPULATION_CATEGORIES, 1, MAX_PARAMS))
          for (int i = 1; i < (int)vParameterList.size(); ++i)
            pObservation->addPopulationCategory(vParameterList[i]);
        else if (checkLine(PARAM_LAYER_NAME))
          pObservation->setLayer(vParameterList[1]);
        else if (checkLine(PARAM_SELECTIVITIES, 1, MAX_PARAMS))
          for (int i = 1; i < (int)vParameterList.size(); ++i)
            pObservation->addSelectivity(vParameterList[i]);
        else if (checkLine(PARAM_POPULATION_SELECTIVITIES, 1, MAX_PARAMS))
          for (int i = 1; i < (int)vParameterList.size(); ++i)
            pObservation->addPopulationSelectivity(vParameterList[i]);
        else if (checkLine(PARAM_MIN_AGE))
          pObservation->setMinAge(getIntValue(1));
        else if (checkLine(PARAM_MAX_AGE))
          pObservation->setMaxAge(getIntValue(1));
        else if (checkLine(PARAM_AGE_PLUS_GROUP))
          pObservation->setAgePlus(getBoolValue(1));
        else if (checkLine(PARAM_DIST))
          pObservation->setDist(vParameterList[1]);
        else if (checkLine(PARAM_OBS, 2, MAX_PARAMS))
          for (int i = 2; i < (int)vParameterList.size(); ++i)
            pObservation->addProportion(vParameterList[1], getDoubleValue(i, true));
        else if (checkLine(PARAM_R))
          pObservation->setR(getDoubleValue(1));
        else if (checkLine(PARAM_N, 1, MAX_PARAMS))
          for(int i = 2; i < (int)vParameterList.size(); ++i)
            pObservation->addN(vParameterList[1], getDoubleValue(i, true));
        else if (checkLine(PARAM_N_PROCESS_ERROR))
          pObservation->setNProcessError(getDoubleValue(1));
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
    pObservationManager->addObservation(pObservation);
  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadProportionsByCategory()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimationConfigLoader::loadAbundance()
// @abundance Observation
//**********************************************************************
void CEstimationConfigLoader::loadAbundance() {
  try {
    // Get Label
    CAbundanceObservation *pObservation = new CAbundanceObservation();
    pObservation->setLabel(getLabel());

    // Load Next Line
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_YEAR))
          pObservation->setYear(getIntValue(1));
        else if (checkLine(PARAM_TIME_STEP))
          pObservation->setTimeStep(getIntValue(1));
        else if (checkLine(PARAM_CATEGORIES, 1, MAX_PARAMS))
          for (int i = 1; i < (int)vParameterList.size(); ++i)
            pObservation->addCategory(vParameterList[i]);
        else if (checkLine(PARAM_LAYER_NAME))
          pObservation->setLayer(vParameterList[1]);
        else if (checkLine(PARAM_SELECTIVITIES, 1, MAX_PARAMS))
          for (int i = 1; i < (int)vParameterList.size(); ++i)
            pObservation->addSelectivity(vParameterList[i]);
        else if (checkLine(PARAM_DIST))
          pObservation->setDist(vParameterList[1]);
        else if (checkLine(PARAM_OBS, 2, 2))
          pObservation->addProportion(vParameterList[1], getDoubleValue(2, true));
        else if (checkLine(PARAM_CV, 2, 2))
          pObservation->addCV(vParameterList[1], getDoubleValue(2, true));
        else if (checkLine(PARAM_Q))
          pObservation->setQ(vParameterList[1]);
        else if (checkLine(PARAM_CV_PROCESS_ERROR))
          pObservation->setCVProcessError(getDoubleValue(1));
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
    pObservationManager->addObservation(pObservation);

  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadAbundance()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimationConfigLoader::loadAgeingError()
// @ageing_error
//**********************************************************************
void CEstimationConfigLoader::loadAgeingError() {
  try {
    // @ageing_erro should have no extra parameters
    if (vParameterList.size() != 1)
      throw string(ERROR_QTY_MORE_PARAMETERS);

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Load Parameters Up
       }
      vConfigPtr++;
    }

  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadAgeingError()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimationConfigLoader::loadEstimate()
// Load @estimate
//**********************************************************************
void CEstimationConfigLoader::loadEstimate() {
  try {
    // @estimate should have no extra parameters
    if (vParameterList.size() != 1)
      throw string(ERROR_QTY_MORE_PARAMETERS);

    // Create Var
    CEstimate *pEstimate = new CEstimate();

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_PARAMETER))
          pEstimate->setParameter(vParameterList[1]);
        else if (checkLine(PARAM_LOWER_BOUND))
          pEstimate->setLowerBound(getDoubleValue(1));
        else if (checkLine(PARAM_UPPER_BOUND))
          pEstimate->setUpperBound(getDoubleValue(1));
        else if (checkLine(PARAM_PRIOR))
          pEstimate->setPrior(vParameterList[1]);
        else if (checkLine(PARAM_SAME))
          for (int i = 1; i < (int)vParameterList.size(); ++i)
            pEstimate->addSame(vParameterList[i]);
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }

    pEstimateManager->addEstimate(pEstimate);

  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadEstimate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimationConfigLoader::loadPrior()
// load @prior
//**********************************************************************
void CEstimationConfigLoader::loadPrior() {
  try {
  // @prior should have 1 parameter (Label)
    if (vParameterList.size() != 2)
      throw string(ERROR_QTY_ONE_PARAMETERS);

    // Inc
    vConfigPtr++;
    // Populate Parameters
    populateParameters();

    if (vParameterList.size() == 0)
      throw string(ERROR_EMPTY_PARAMETER);

    // Must Be Type
    if (vParameterList[0] != PARAM_TYPE)
      throw string(ERROR_MISSING_SECTION_TYPE);
    if (vParameterList.size() != 2)
      throw string(ERROR_QTY_ONE_PARAMETERS);

    if (vParameterList[1] == PARAM_UNIFORM)
      loadPrior_Uniform();
    else if (vParameterList[1] == PARAM_NORMAL)
      loadPrior_Normal();
    else if (vParameterList[1] == PARAM_NORMAL_BY_STDEV)
      loadPrior_NormalByStdev();
    else if (vParameterList[1] == PARAM_LOG_NORMAL)
      loadPrior_LogNormal();
    else if (vParameterList[1] == PARAM_UNIFORM_LOG)
      loadPrior_UniformLog();
    else if (vParameterList[1] == PARAM_NORMAL_LOG)
      loadPrior_NormalLog();
    else if (vParameterList[1] == PARAM_BETA)
      loadPrior_Beta();
    else
      throw string(ERROR_UNKNOWN_TYPE + vParameterList[1]);

  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadPrior()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimationConfigLoader::loadPrior_Uniform()
// type = uniform
//**********************************************************************
void CEstimationConfigLoader::loadPrior_Uniform() {
  try {
    CUniformPrior *pPrior = new CUniformPrior();
    pPrior->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_C))
          pPrior->setC(getDoubleValue(1));
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
    pPriorManager->addPrior(pPrior);

  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadPrior_Uniform()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimationConfigLoader::loadPrior_UniformLog()
// type = uniform_log
//**********************************************************************
void CEstimationConfigLoader::loadPrior_UniformLog() {
  try {
    CUniformLogPrior *pPrior = new CUniformLogPrior();
    pPrior->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_C))
          pPrior->setC(getDoubleValue(1));
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
    pPriorManager->addPrior(pPrior);

  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadPrior_UniformLog()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimationConfigLoader::loadPrior_NormalLog()
// type = normal_log
//**********************************************************************
void CEstimationConfigLoader::loadPrior_NormalLog() {
  try {
    CNormalLogPrior *pPrior = new CNormalLogPrior();
    pPrior->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_MU))
          pPrior->setMu(getDoubleValue(1));
        else if (checkLine(PARAM_SIGMA))
          pPrior->setSigma(getDoubleValue(1));
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
    pPriorManager->addPrior(pPrior);

  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadPrior_NormalLog()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimationConfigLoader::loadPrior_Normal()
// type = normal
//**********************************************************************
void CEstimationConfigLoader::loadPrior_Normal() {
  try {
    CNormalPrior *pPrior = new CNormalPrior();
    pPrior->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_MU))
          pPrior->setMu(getDoubleValue(1));
        else if (checkLine(PARAM_CV))
          pPrior->setCv(getDoubleValue(1));
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
    pPriorManager->addPrior(pPrior);

  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadPrior_Normal()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimationConfigLoader::loadPrior_NormalByStdev()
// type = normal_by_stdev
//**********************************************************************
void CEstimationConfigLoader::loadPrior_NormalByStdev() {
  try {
    CNormalByStdevPrior *pPrior = new CNormalByStdevPrior();
    pPrior->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_MU))
          pPrior->setMu(getDoubleValue(1));
        else if (checkLine(PARAM_SIGMA))
          pPrior->setSigma(getDoubleValue(1));
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
    pPriorManager->addPrior(pPrior);

  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadPrior_LogNormal()->" + Ex;
    throw Ex;
  }
}
//**********************************************************************
// void CEstimationConfigLoader::loadPrior_LogNormal()
// type = lognormal
//**********************************************************************
void CEstimationConfigLoader::loadPrior_LogNormal() {
  try {
    CLogNormalPrior *pPrior = new CLogNormalPrior();
    pPrior->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_MU))
          pPrior->setMu(getDoubleValue(1));
        else if (checkLine(PARAM_CV))
          pPrior->setCv(getDoubleValue(1));
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
    pPriorManager->addPrior(pPrior);

  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadPrior_LogNormal()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimationConfigLoader::loadPrior_Beta()
// type = Beta
//**********************************************************************
void CEstimationConfigLoader::loadPrior_Beta() {
  try {
    CBetaPrior *pPrior = new CBetaPrior();
    pPrior->setLabel(getLabel());

    // Load Next Line
    vConfigPtr++;
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_MU))
          pPrior->setMu(getDoubleValue(1));
        else if (checkLine(PARAM_SIGMA))
          pPrior->setSigma(getDoubleValue(1));
        else if (checkLine(PARAM_A))
          pPrior->setA(getDoubleValue(1));
        else if (checkLine(PARAM_B))
          pPrior->setB(getDoubleValue(1));
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
    pPriorManager->addPrior(pPrior);

  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadPrior_Beta()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimationConfigLoader::loadPenalty()
// @penalty
//**********************************************************************
void CEstimationConfigLoader::loadPenalty() {
  try {
    CPenalty *pPenalty = new CPenalty();
    pPenalty->setLabel(getLabel());

    // Load Next Line
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_LOG_SCALE))
          pPenalty->setLogScale(getBoolValue(1));
        else if (checkLine(PARAM_MULTIPLIER))
          pPenalty->setMultiplier(getDoubleValue(1));
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
    pPenaltyManager->addPenalty(pPenalty);

  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadPenalty()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimationConfigLoader::loadQ()
// Load the Q Parameter
//**********************************************************************
void CEstimationConfigLoader::loadQ() {
  try {
    CQ *pQ = new CQ();
    pQ->setLabel(getLabel());

    // Load Next Line
    while(vConfigPtr != vConfigList.end()) {
      populateParameters();

      if (vParameterList.size() > 0) {
        if (newSection())
          break;

        // Check Section
        if (checkLine(PARAM_TYPE))
          pQ->setType(vParameterList[1]);
        else if (checkLine(PARAM_Q))
          pQ->setQ(getDoubleValue(1));
        else
          throw string(ERROR_UNKNOWN_PARAM + vParameterList[0]);
      }
      vConfigPtr++;
    }
    pQManager->addQ(pQ);

  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadPenalty()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// bool CEstimationConfigLoader::loadBaseMinimizerAttributes(CMinimizer *pMinimizer)
//
//**********************************************************************
bool CEstimationConfigLoader::loadBaseMinimizerAttributes(CMinimizer *pMinimizer) {
  try {
    if (checkLine(PARAM_MAX_ITERS))
      pMinimizer->setMaxIterations(getIntValue(1));
    else if (checkLine(PARAM_MAX_EVALS))
      pMinimizer->setMaxEvaluations(getIntValue(1));
    else if (checkLine(PARAM_GRAD_TOL))
      pMinimizer->setGradientTolerance(getDoubleValue(1));
    else if (checkLine(PARAM_STEP_SIZE))
      pMinimizer->setStepSize(getDoubleValue(1));
    else
      return false;

  } catch (string Ex) {
    Ex = "CEstimationConfigLoader.loadBaseMinimizerAttributes()->" + Ex;
    throw Ex;
  }
  return true;
}

//**********************************************************************
// CEstimationConfigLoader::~CEstimationConfigLoader()
// Default De-Constructor
//**********************************************************************
CEstimationConfigLoader::~CEstimationConfigLoader() {
}
