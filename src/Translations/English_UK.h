//============================================================================
// Name        : English.h
// Author      : S.Rasmussen
// Date        : 18/07/2008
// Copyright   : Copyright NIWA Science ©2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

#ifndef ENGLISH_UK_H_
#define ENGLISH_UK_H_

//**********************************************************************
// ERROR CODES/STRINGS
//
//**********************************************************************
#define ERROR_BAD_CAST_WOLD_SQUARE          "Cannot convert to WorldSquare"
#define ERROR_BETWEEN_ZERO_ONE              " must be between 0.0 and 1.0"

#define ERROR_CONTAIN_QUOTES                "file_name cannot contain quotes, but must be surrounded with them"

#define ERROR_DUPLICATE_CATEGORY            "Duplicate category: "
#define ERROR_DUPLICATE_LABEL               "Duplicate label: "
#define ERROR_DUPLICATE_PARAMETER           "Duplicate parameter: "
#define ERROR_DUPLICATE_TIME_STEP           "Duplicate time_step: "

#define ERROR_EMPTY_FILE                    "Configuration file was empty"
#define ERROR_EMPTY_PARAMETER               "Parameter list was empty"

#define ERROR_ENABLED_ESTIMATES             "No enabled estimates to use"

#define ERROR_EQUAL_CATEGORY_SELECTIVITY    "Category list must be same size as Selectivity list"
#define ERROR_EQUAL_CATEGORY_PROPORTION     "Category list must be same size as proportion list"
#define ERROR_EQUAL_CATEGORY_AGES           "Category list must be same size as ages list"
#define ERROR_EQUAL_AGES_PROPORTIONS        "Ages list must be same size as proportions list"
#define ERROR_EQUAL_NOT                     " does not equal "
#define ERROR_EQUAL_TO                      " is equal to "
#define ERROR_EQUAL_VALUE_ESTIMATE          "Value list must be same size as estimate name list"
#define ERROR_EQUAL_OBS_CV                  "obs list and cv list size must be equal"
#define ERROR_EQUAL_PROPORTION_ONE          " proportions do not sum to 1.0: "
#define ERROR_EQUAL_N_OBS                   "N list must be same size as obs list"

#define ERROR_FORMAT_PARAMETER              "Invalid format, please use  type[label].variable"

#define ERROR_INVALID_BOOL                  "Invalid True/False value: "
#define ERROR_INVALID_FILE_NAME             "Invalid file name"
#define ERROR_INVALID_FORMAT                "Invalid format: "
#define ERROR_INVALID_GETLABEL_LINE         "Cannot read label, not on correct line"
#define ERROR_INVALID_IDX                   "Invalid index: "
#define ERROR_INVALID_OBS_CV_MATCH          "obs does not have a matching cv. obs: "
#define ERROR_INVALID_NUMERIC               "Value must be numeric: "
#define ERROR_INVALID_PROPORTION            "Invalid proportion: "
#define ERROR_INVALID_VALUE_NEGATIVE        "Value cannot be negative: "
#define ERROR_INVALID_WILDCARDS             "Cannot mix both wildcards ? and *"
#define ERROR_INVALID_TARGET_NULL           "Target variable is NULL"
#define ERROR_INVALID_TIME_STEP             "Invalid time_step: "
#define ERROR_INVALID_YEAR                  "Invalid year: "
#define ERROR_INVALID_LAYER_TYPE_NUMERIC    "Layer is not numeric type: "
#define ERROR_INVALID_LAYER_TYPE_STRING     "Layer is not string type: "

#define ERROR_GREATER_THAN                  " is greater than "
#define ERROR_GREATER_EQUAL_TO              " is greater than or equal to "

#define ERROR_LENGTH_METHOD                 "method is too short"

#define ERROR_LESS_THAN                     " is less than "
#define ERROR_LESS_EQUAL_TO                 " is less than or equal to "

#define ERROR_MISSING                       "Missing "
#define ERROR_MISSING_ROW_NUMBER            "Missing row number"
#define ERROR_MISSING_SECTION_METHOD        "Missing method, must directly follow new section declaration"
#define ERROR_MISSING_SECTION_TYPE          "Missing type, must directly follow new section declaration"
#define ERROR_MISSING_LAYER_SPOT            "Missing a spot on layer: "
#define ERROR_MISSING_N_OBS                 "Missing obs for n: "
#define ERROR_MISSING_QUOTES                "file_name must be surrounded by quotes"
#define ERROR_MISSING_TIME_STEP             "Missing time_step: "
#define ERROR_MISSING_YEARS_STEP            "Missing years or time_step"

#define ERROR_NEGATIVE_BASE_LAYER           "World layer contains a negative value"

#define ERROR_OPEN_FILE                     "Failed to open file: "

#define ERROR_QTY_LESS_PARAMETERS           "Not enough parameters: "
#define ERROR_QTY_LESS_PROPORTIONS          "Not enough proportions: "
#define ERROR_QTY_MORE_PARAMETERS           "Too many parameters: "
#define ERROR_QTY_MORE_PROPORTIONS          "Too many proportions: "
#define ERROR_QTY_ONE_PARAMETERS            "Invalid parameter count, must be 1"
#define ERROR_QTY_LESS_N                    "Not enough n's: "
#define ERROR_QTY_MORE_N                    "Too many n's: "
#define ERROR_QTY_LESS_TIME_STEPS           "Not enough time steps: "
#define ERRRO_QTY_MORE_TIME_STEPS           "Too many time_steps: "

#define ERROR_RUN_VALIDATE                  "Validation has not been run"

#define ERROR_SUPPORTED                      " not supported"
#define ERROR_SUPPORTED_FUNCTION            "function not supported"
#define ERROR_SUPPORTED_NORMALIZE           "normalise not supported"

#define ERROR_UNKNOWN_CATEGORY              "Unknown category: "
#define ERROR_UNKNOWN_ESTIMABLE             "Unknown estimable: "
#define ERROR_UNKNOWN_ESTIMATE              "Unknown estimate: "
#define ERROR_UNKNOWN_LAYER                 "Unknown layer: "
#define ERROR_UNKNOWN_METHOD                "Unknown method: "
#define ERROR_UNKNOWN_SECTION               "Unknown section: "
#define ERROR_UNKNOWN_SYNTAX                "Unknown syntax: "
#define ERROR_UNKNOWN_PARAM                 "Unknown parameter: "
#define ERROR_UNKNOWN_PENALTY               "Unknown penalty: "
#define ERROR_UNKNOWN_PRIOR                 "Unknown prior: "
#define ERROR_UNKNOWN_PROCESS               "Unknown process: "
#define ERROR_UNKNOWN_Q                     "Unknown q: "
#define ERROR_UNKNOWN_SELECTIVITY           "Unknown selectivity: "
#define ERROR_UNKNOWN_TIME_STEP             "Unknown time_step: "
#define ERROR_UNKNOWN_TYPE                  "Unknown type: "
#define ERROR_UNKNOWN_RUN_MODE              "Unknown run_mode: "

#define ERROR_VALID_SQUARES_WITH_LAYER      "No world squares are valid with layer applied"

//**********************************************************************
// BASE CONFIGURATION
//
//**********************************************************************
// Configuration File Syntax Strings
#define CONFIG_FALSE                        "false"
#define CONFIG_FALSE_SHORT                  "f"
#define CONFIG_FILE_ESTIMATE_VALUES         "values.spm"
#define CONFIG_FILE_ESTIMATION              "estimation.spm"
#define CONFIG_FILE_OUTPUT                  "output.spm"
#define CONFIG_FILE_POPULATION              "population.spm"
#define CONFIG_INCLUDE                      "@include"
#define CONFIG_SECTION_SYMBOL               "@"
#define CONFIG_SEPERATOR_ESTIMATE_VALUES    ","
#define CONFIG_TRUE                         "true"
#define CONFIG_TRUE_SHORT                   "t"
#define CONFIG_WILDCARD_SINGLE              "?"
#define CONFIG_WILDCARD_MULTIPLE            "*"
#define CONFIG_SINGLE_COMMENT               "#"
#define CONFIG_MULTI_COMMENT_START          "{"
#define CONFIG_MULTI_COMMENT_END            "}"
#define CONFIG_ARRAY_START                  "["
#define CONFIG_ARRAY_END                    "]"

//**********************************************************************
// ESTIMATION CONFIGURATION
//
//**********************************************************************
#define CONFIG_SECTION_MPD                        "@mpd"
#define CONFIG_SECTION_MINIMIZER                  "@minimiser"
#define CONFIG_SECTION_MCMC                       "@mcmc"
#define CONFIG_SECTION_PROFILE                    "@profile"
#define CONFIG_SECTION_PROP_AT_AGE                "@proportions_at_age"
#define CONFIG_SECTION_PROP_BY_CATEGORY           "@proportions_by_category"
#define CONFIG_SECTION_ABUNDANCE                  "@abundance"
#define CONFIG_SECTION_AGEING                     "@ageing_error"
#define CONFIG_SECTION_ESTIMATE                   "@estimate"
#define CONFIG_SECTION_PRIOR                      "@prior"
#define CONFIG_SECTION_PENALTY                    "@penalty"
#define CONFIG_SECTION_Q                          "@q"

//**********************************************************************
// OUTPUT CONFIGURATION
//
//**********************************************************************
#define CONFIG_SECTION_PRINT_STATE                "@print_state"

//**********************************************************************
// POPULATION CONFIGURATION
//
//**********************************************************************
#define CONFIG_SECTION_SPATIAL_STRUCT             "@spatial_structure"
#define CONFIG_SECTION_POPULATION_STRUCT          "@population_structure"
#define CONFIG_SECTION_INITIALIZATION             "@initialisation"
#define CONFIG_SECTION_ANNUAL_CYCLE               "@annual_cycle"
#define CONFIG_SECTION_TIME_STEP                  "@time_step"
#define CONFIG_SECTION_INITIALIZATION_PHASE       "@initialisation_phase"
#define CONFIG_SECTION_POPULATION_PROCESS         "@population_process"
#define CONFIG_SECTION_MOVEMENT_PROCESS           "@movement_process"
#define CONFIG_SECTION_LAYER                      "@layer"
#define CONFIG_SECTION_SELECTIVITY                "@selectivity"
#define CONFIG_SECTION_DIRECTED_PROCESS           "@directed_process"

//**********************************************************************
// RUN MODES
//
//**********************************************************************
#define MODE_BASIC_RUN                        "basic_run"
#define MODE_ESTIMATION                       "estimation"
#define MODE_PROFILE                          "profile"
#define MODE_MCMC                             "mcmc"
#define MODE_FORWARD_PROJECTION               "forward_projection"

//**********************************************************************
// FMM
//
//**********************************************************************
#define FMM_MANY_FUNCTION_EVALUATIONS             "FMM: Too many function evaluations"
#define FMM_MANY_LOOPS_LINEAR_SEARCH              "FMM: Too many loops in this linear search"
#define FMM_SMALL_LINEAR_STEP_SIZE                "FMM: Linear step size too small"
#define FMM_MANY_QUASI_NEWTON_ITERATIONS          "FMM: Too many quasi-newton iterations"
#define FMM_ITERATION                             "FMM: Iteration = "
#define FMM_FUNCTION_VALUE                        "FMM: Function value = "
#define FMM_CURRENT_PARAMETER_ESTIMATES           "FMM: Current parameter estimates = "
#define FMM_MAX_NEWTON_STEP_FIVE                  "FMM: The max newton step has been taken 5 times, see D&S p 348"
#define FMM_CONVERGENCE_CHECK                     "FMM: Convergence check value = "
#define FMM_CONVERGENCE_THRESHOLD                 "FMM: Convergence threshold = "
#define FMM_CONVERGENCE                           "FMM: Convergence = "
#define FMM_FUNCTION_SCORE                        "FMM: Function score = "
#define FMM_GRADIENT_VALUE                        "FMM: Gradient value = "
#define FMM_SMALL_STEP_SIZE_CONVERGENCE           "FMM: Step size too small. Indicates successful convergence"
#define FMM_CONVERGENCE_NOT_TEXTBOOK              "FMM: This is not a textbook ideal convergence"

//**********************************************************************
// GAMMADIFF
//
//**********************************************************************
#define GAMMADIFF_SIZE_LOWER_BOUND_START_VALUE    "GammaDiff: Lower bound vector is not same size as start value"
#define GAMMADIFF_SIZE_UPPER_BOUND_START_VALUE    "GammaDiff: Upper bound vector is not same size as start value"
#define GAMMADIFF_CONVERGENCE_UNCLEAR             "GammaDiff: Unclear convergence, maybe local minimum"
#define GAMMADIFF_EVALUATIONS_MAX                 "GammaDiff: Maximum evaluations/iterations with no convergence"
#define GAMMADIFF_CONVERGENCE                     "GammaDiff: Successful convergence"
#define GAMMADIFF_RETURN_VALUE_UNKNOWN            "GammaDiff: Fatal error, unknown return value = "
#define GAMMADIFF_LESS_START_LOWER_BOUND          "GammaDiff: Start value is less than lower bound"
#define GAMMADIFF_GREATER_START_UPPER_BOUND       "GammaDiff: Start value is greater than upper bound"

//**********************************************************************
// PARAMETERS
//
//**********************************************************************
#define PARAM_A                                   "a"
#define PARAM_ABUNDANCE                           "abundance"
#define PARAM_ADAPT_AT                            "adapt_at"
#define PARAM_ADAPTIVE_STEP_SIZE                  "adaptive_stepsize"
#define PARAM_AGE                                 "age"
#define PARAM_AGE_INDEX                           "age_index"
#define PARAM_AGE_PLUS_GROUP                      "age_plus_group"
#define PARAM_AGEING                              "ageing"
#define PARAM_AGES                                "ages"
#define PARAM_ALPHA                               "alpha"
#define PARAM_A50                                 "a50"
#define PARAM_ATO95                               "ato95"
#define PARAM_B                                   "b"
#define PARAM_BETA                                "beta"
#define PARAM_C                                   "c"
#define PARAM_CATEGORIES                          "categories"
#define PARAM_CATEGORY                            "category"
#define PARAM_CATEGORY_INDEX                      "category_index"
#define PARAM_CATEGORY_TRANSITION                 "category_transition"
#define PARAM_COLUMN                              "column"
#define PARAM_COLUMN_INDEX                        "column_index"
#define PARAM_CONSTANT                            "constant"
#define PARAM_CURRENT                             "current"
#define PARAM_CV                                  "cv"
#define PARAM_CV_PROCESS_ERROR                    "cv_process_error"
#define PARAM_DESOLVER                            "desolver"
#define PARAM_DF                                  "df"
#define PARAM_DIRECTED                            "directed"
#define PARAM_DIRECTED_PROCESS                    "directed_process"
#define PARAM_DIRECTED_PROCESSES                  "directed_processes"
#define PARAM_DIST                                "dist"
#define PARAM_DISTANCE                            "distance"
#define PARAM_DOUBLE                              "double"
#define PARAM_DOUBLE_NORMAL                       "double_normal"
#define PARAM_ENABLED_ESTIMATES                   "enabled_estimates"
#define PARAM_ESTIMATE                            "estimate"
#define PARAM_ESTIMATES                           "estimates"
#define PARAM_ESTIMATE_VALUE                      "estimate_value"
#define PARAM_EVENT_MORTALITY                     "event_mortality"
#define PARAM_EXPONENTIAL                         "exponential"
#define PARAM_FILE_NAME                           "file_name"
#define PARAM_FINAL                               "final"
#define PARAM_FLAGGED_PENALTIES                   "flagged_penalties"
#define PARAM_FROM                                "from"
#define PARAM_GAMMADIFF                           "gammadiff"
#define PARAM_GRAD_TOL                            "grad_tol"
#define PARAM_H                                   "h"
#define PARAM_HEIGHT                              "height"
#define PARAM_HEX                                 "hex"
#define PARAM_HEX_UNIFORM                         "hex_uniform"
#define PARAM_INDEX                               "index"
#define PARAM_INITIAL                             "initial"
#define PARAM_INITIALIZATION_PHASES               "initialisation_phases"
#define PARAM_INVERSE_LOGISTIC                    "inverse_logistic"
#define PARAM_KEEP                                "keep"
#define PARAM_KNIFE_EDGE                          "knife_edge"
#define PARAM_L                                   "l"
#define PARAM_LABEL                               "label"
#define PARAM_LAMBDA                              "lambda"
#define PARAM_LAYER_CATEGORIES                    "layer_categories"
#define PARAM_LAYER_HEIGHT                        "layer_height"
#define PARAM_LAYER_MAX                           "layer_max"
#define PARAM_LAYER_MIN                           "layer_min"
#define PARAM_LAYER_NAME                          "layer_name"
#define PARAM_LAYER_TYPE                          "layer_type"
#define PARAM_LAYER_WIDTH                         "layer_width"
#define PARAM_LAYERS                              "layers"
#define PARAM_LENGTH                              "length"
#define PARAM_LOG_SCALE                           "log_scale"
#define PARAM_LOGISTIC                            "logistic"
#define PARAM_LOGISTIC_PRODUCING                  "logistic_producing"
#define PARAM_LOG_NORMAL                          "log_normal"
#define PARAM_LOWER_BOUND                         "lower_bound"
#define PARAM_M                                   "m"
#define PARAM_MAX_AGE                             "max_age"
#define PARAM_MAX_EVALS                           "max_evals"
#define PARAM_MAX_ITERS                           "max_iters"
#define PARAM_METHOD                              "method"
#define PARAM_MIN_AGE                             "min_age"
#define PARAM_MINIMIZER                           "minimiser"
#define PARAM_MOVEMENT_PROCESS                    "movement_process"
#define PARAM_MOVEMENT_PROCESSES                  "movement_processes"
#define PARAM_MU                                  "mu"
#define PARAM_MULTIPLIER                          "multiplier"
#define PARAM_N                                   "n"
#define PARAM_N_PROCESS_ERROR                     "n_process_error"
#define PARAM_NATURAL_MORTALITY                   "natural_mortality"
#define PARAM_NCOLS                               "ncols"
#define PARAM_NORMAL                              "normal"
#define PARAM_NORMAL_BY_STDEV                     "normal_by_stdev"
#define PARAM_NORMAL_LOG                          "normal_log"
#define PARAM_NORMALIZE                           "normalise"
#define PARAM_NROWS                               "nrows"
#define PARAM_NUMERIC                             "numeric"
#define PARAM_OBJECTIVE                           "objective"
#define PARAM_OBS                                 "obs"
#define PARAM_OBSERVATIONS                        "observations"
#define PARAM_ONE                                 "1 (one)"
#define PARAM_ONE_THOUSAND                        "1,000"
#define PARAM_OVERWRITE                           "overwrite"
#define PARAM_PARAMETER                           "parameter"
#define PARAM_PENALTY                             "penalty"
#define PARAM_POPULATION_CATEGORIES               "population_categories"
#define PARAM_POPULATION_PROCESS                  "population_process"
#define PARAM_POPULATION_PROCESSES                "population_processes"
#define PARAM_POPULATION_SELECTIVITIES            "population_selectivities"
#define PARAM_PRIOR                               "prior"
#define PARAM_PROCESSES                           "processes"
#define PARAM_PROFILES                            "profiles"
#define PARAM_PROJECTION_YEARS                    "projection_years"
#define PARAM_PROPORTION                          "proportion"
#define PARAM_PROPORTIONS                         "proportions"
#define PARAM_PROPORTIONS_AT_AGE                  "proportions_at_age"
#define PARAM_PROPORTIONS_BY_CATEGORY             "proportions_by_category"
#define PARAM_PROPOSAL_T                          "proposal_t"
#define PARAM_Q                                   "q"
#define PARAM_R                                   "r"
#define PARAM_R0                                  "r0"
#define PARAM_RECRUITMENT                         "recruitment"
#define PARAM_RESCALE                             "rescale"
#define PARAM_RHO                                 "rho"
#define PARAM_ROW                                 "row"
#define PARAM_ROW_INDEX                           "row_index"
#define PARAM_RUN_YEARS                           "run_years"
#define PARAM_SAME                                "same"
#define PARAM_SCORES_INDEX                        "scores_index"
#define PARAM_SELECTIVITIES                       "selectivities"
#define PARAM_SELECTIVITY                         "selectivity"
#define PARAM_SIGMA                               "sigma"
#define PARAM_SIGMA_L                             "sigma_l"
#define PARAM_SIGMA_R                             "sigma_r"
#define PARAM_SQUARE                              "square"
#define PARAM_SQUARE_UNIFORM                      "square_uniform"
#define PARAM_START                               "start"
#define PARAM_STEP                                "step"
#define PARAM_STEP_SIZE                           "step_size"
#define PARAM_START_YEAR                          "start_year"
#define PARAM_STEEPNESS                           "steepness"
#define PARAM_THRESHOLD                           "threshold"
#define PARAM_TIME_STEP                           "time_step"
#define PARAM_TIME_STEPS                          "time_steps"
#define PARAM_TO                                  "to"
#define PARAM_TOTAL_SCORE                         "total_score"
#define PARAM_TYPE                                "type"
#define PARAM_U                                   "u"
#define PARAM_UMAX                                "umax"
#define PARAM_UNIFORM                             "uniform"
#define PARAM_UNIFORM_LOG                         "uniform_log"
#define PARAM_UPPER_BOUND                         "upper_bound"
#define PARAM_VALUE                               "value"
#define PARAM_WIDTH                               "width"
#define PARAM_YEAR                                "year"
#define PARAM_YEARS                               "years"
#define PARAM_ZERO                                "0 (zero)"


#endif /* ENGLISH_H_ */
