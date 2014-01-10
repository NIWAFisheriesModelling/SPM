cmake_minimum_required(VERSION 2.6)
project(SPM)

# to run (Windows, Mingw32-gcc)
#   cmake -G "MinGW Makefiles"
#   mingw32-make all
# or Linux
#   cmake -G "Unix Makefiles"
#   make all

SET(MAIN_NAME spm_unoptimised)
SET(TEST_NAME spm_unittests)
SET(OPTI_NAME spm)

# Assumptions
# Compiled with MinGW under Windows, where,
#   MinGW is in c:\Program Files
#   Boost libraries are located in C:/Progra~2/MingW/boost_libs
#   Boost header files are located in C:/Progra~2/MinGW/include/boost/

IF (WIN32)
  # Scott's Build Environment Variables
  #INCLUDE_DIRECTORIES("D:/Programming/Boost/boost_1_53_0/")
  #LINK_DIRECTORIES("D:/Programming/Boost/boost_1_53_0/stage/lib")
  
  # Alistair's Build Environment
  LINK_DIRECTORIES("C:/Progra~1/boost/boost_1_54_0/stage/lib")
  
  # Generic Build Settings
  SET(LINK_OPTIONS "-static icon.o")
  #SET(COMPILE_OPTIONS_LIBR "-DBOOST_THREAD_USE_LIB=1 -DDBOOST_THREAD_PROVIDES_GENERIC_SHARED_MUTEX_ON_WIN -O0 -g3 -ggdb -Wall -fmessage-length=0")
  SET(COMPILE_OPTIONS_MAIN "-DBOOST_THREAD_USE_LIB=1 -DBOOST_THREAD_PROVIDES_GENERIC_SHARED_MUTEX_ON_WIN -O0 -g3 -Wall -fmessage-length=0 -fopenmp -static")
  SET(COMPILE_OPTIONS_OPTI "-DBOOST_THREAD_USE_LIB=1 -DBOOST_THREAD_PROVIDES_GENERIC_SHARED_MUTEX_ON_WIN -DOPTIMIZE -O2 -g0 -Wall -fmessage-length=0 -fopenmp -static")
  SET(COMPILE_OPTIONS_TEST "-DBOOST_THREAD_USE_LIB=1 -DBOOST_THREAD_PROVIDES_GENERIC_SHARED_MUTEX_ON_WIN -DTEST -O0 -g3 -Wall -fmessage-length=0 -fopenmp -static")
  ADD_CUSTOM_TARGET(icon ALL
    COMMAND windres --output ${PROJECT_SOURCE_DIR}/icon.o --input ${PROJECT_SOURCE_DIR}/src/spm.rc
  )
  SET(MAIN_LIBRARIES
    gomp
    pthread
    boost_system-mgw47-mt-s-1_54
    boost_filesystem-mgw47-mt-s-1_54
    boost_thread-mgw47-mt-s-1_54
    boost_program_options-mgw47-mt-s-1_54
    boost_chrono-mgw47-mt-s-1_54
  )
  SET(TEST_LIBRARIES boost_unit_test_framework-mgw47-mt-sd-1_54)
  
ELSE (WIN32)
  # wellopensuse131 link directories
  SET(BOOST_LIBS "/opt/boost155/lib/")
  SET(BOOST_HEADERS "/opt/boost155/include/boost/")
  SET(LINK_OPTIONS "-static -L ${BOOST_LIBS}")
  #SET(LINK_OPTIONS "-L ${BOOST_LIBS}")
  SET(COMPILE_OPTIONS_LIBR "-DBOOST_THREAD_USE_LIB=1 -O0 -g3 -ggdb -Wall -fmessage-length=0 -fopenmp -Wno-unused-local-typedefs -I ${BOOST_HEADERS}")
  SET(COMPILE_OPTIONS_MAIN "-DBOOST_THREAD_USE_LIB=1 -O0 -g3 -Wall -fmessage-length=0 -fopenmp -Wno-unused-local-typedefs -I ${BOOST_HEADERS}")
  SET(COMPILE_OPTIONS_OPTI "-DBOOST_THREAD_USE_LIB=1 -DOPTIMIZE -O3 -g0 -Wall -fmessage-length=0 -fopenmp -Wno-unused-local-typedefs -I ${BOOST_HEADERS}")
  SET(COMPILE_OPTIONS_TEST "-DBOOST_THREAD_USE_LIB=1 -DTEST -O0 -g3 -Wall -fmessage-length=0 -fopenmp -Wno-unused-local-typedefs -I ${BOOST_HEADERS}")
  SET(MAIN_LIBRARIES
    boost_system
    boost_filesystem
    boost_thread
    boost_program_options    
    gomp
    pthread
    )
  SET(TEST_LIBRARIES boost_unit_test_framework)
ENDIF (WIN32)


# Autogeneration of Version.h file in src directory (backing up current ('NULL') version
ADD_CUSTOM_TARGET(version ALL
  COMMAND cp ${PROJECT_SOURCE_DIR}/src/Version.h ${PROJECT_SOURCE_DIR}/src/Version.h.old
  COMMAND svn_version --quiet --format c++ m--path ${PROJECT_SOURCE_DIR} --recursive --output ${PROJECT_SOURCE_DIR}/src/Version.h
)

# To build the list below I used MSYS
# By executing the following command I could store the names of all
# .cpp files in a txt file. Then use a simple find/replace from .cpp to ""
# find src | grep ".cpp" | grep -v "svn" | grep -v ".Test." | grep -v "UnitTest" | grep -v "TestFixtures" > cpps.txt
# To get Unit Test only Files

FILE(GLOB_RECURSE SOURCE_FILES src/*.cpp)
FILE(GLOB_RECURSE TEST_FILES src/*.Test.cpp)
list(REMOVE_ITEM SOURCE_FILES ${TEST_FILES})

# Build SPM unoptimised
ADD_EXECUTABLE(${MAIN_NAME} ${SOURCE_FILES})
SET_TARGET_PROPERTIES(${MAIN_NAME} PROPERTIES COMPILE_FLAGS ${COMPILE_OPTIONS_MAIN} LINK_FLAGS ${LINK_OPTIONS})
TARGET_LINK_LIBRARIES(${MAIN_NAME} ${MAIN_LIBRARIES})

# Build SPM unit tests
ADD_EXECUTABLE(${TEST_NAME} ${SOURCE_FILES} ${TEST_FILES})
SET_TARGET_PROPERTIES(${TEST_NAME} PROPERTIES COMPILE_FLAGS ${COMPILE_OPTIONS_TEST} LINK_FLAGS ${LINK_OPTIONS})
TARGET_LINK_LIBRARIES(${TEST_NAME} ${MAIN_LIBRARIES} ${TEST_LIBRARIES})

# Build SPM optimised
ADD_EXECUTABLE(${OPTI_NAME} ${SOURCE_FILES})
SET_TARGET_PROPERTIES(${OPTI_NAME} PROPERTIES COMPILE_FLAGS ${COMPILE_OPTIONS_OPTI} LINK_FLAGS ${LINK_OPTIONS})
TARGET_LINK_LIBRARIES(${OPTI_NAME} ${MAIN_LIBRARIES})

ADD_DEPENDENCIES(${MAIN_NAME} version icon)
ADD_DEPENDENCIES(${TEST_NAME} version icon)
#ADD_DEPENDENCIES(${LIBRARY_NAME} version)
ADD_DEPENDENCIES(${OPTI_NAME} version icon)
