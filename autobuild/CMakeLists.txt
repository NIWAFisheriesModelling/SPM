cmake_minimum_required(VERSION 2.8)
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

# Change the output folders for our build to something cleaner and platform dependent
SET(CMAKE_ROOT   bin/cmake)

STRING(REPLACE "autobuild" "" SPM_HOME_DIRECTORY ${CMAKE_HOME_DIRECTORY})
MESSAGE("Home: ${SPM_HOME_DIRECTORY}")

IF (WIN32)
  INCLUDE_DIRECTORIES("C:/Work/Boost/boost_1_55_0/")
  INCLUDE_DIRECTORIES("D:/Programming/Boost/boost_1_55_0")
  LINK_DIRECTORIES("${SPM_HOME_DIRECTORY}/libs/windows_gcc_4_8/")
  
  # Generic Build Settings
  SET(LINK_OPTIONS "-static")
  SET(COMPILE_OPTIONS_MAIN "-O0 -g3 -Wall -Werror -fmessage-length=0 -DBOOST_THREAD_USE_LIB=1 -Wno-unused-local-typedefs -DBOOST_THREAD_PROVIDES_GENERIC_SHARED_MUTEX_ON_WIN -fopenmp -static")
  SET(COMPILE_OPTIONS_OPTI "-O2 -g0 -Wall -Werror -fmessage-length=0 -DBOOST_THREAD_USE_LIB=1 -Wno-unused-local-typedefs -DBOOST_THREAD_PROVIDES_GENERIC_SHARED_MUTEX_ON_WIN -fopenmp -static -DOPTIMIZE")
  SET(COMPILE_OPTIONS_TEST "-O0 -g3 -Wall -Werror -fmessage-length=0 -DBOOST_THREAD_USE_LIB=1 -Wno-unused-local-typedefs -DBOOST_THREAD_PROVIDES_GENERIC_SHARED_MUTEX_ON_WIN -fopenmp -static -DTEST")
  SET(MAIN_LIBRARIES
    gomp
    pthread
    boost_system-mgw48-mt-s-1_55
    boost_filesystem-mgw48-mt-s-1_55
    boost_thread-mgw48-mt-s-1_55
    boost_program_options-mgw48-mt-s-1_55
    boost_chrono-mgw48-mt-s-1_55
  )
  SET(TEST_LIBRARIES boost_unit_test_framework-mgw48-mt-s-1_55)
  
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

# To build the list below I used MSYS
# By executing the following command I could store the names of all
# .cpp files in a txt file. Then use a simple find/replace from .cpp to ""
# find src | grep ".cpp" | grep -v "svn" | grep -v ".Test." | grep -v "UnitTest" | grep -v "TestFixtures" > cpps.txt
# To get Unit Test only Files

FILE(GLOB_RECURSE SOURCE_FILES ${SPM_HOME_DIRECTORY}/src/*.cpp)
FILE(GLOB_RECURSE TEST_FILES ${SPM_HOME_DIRECTORY}/src/*.Test.cpp)
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
