#==============================================================================
# Preamble
#==============================================================================
cmake_minimum_required(VERSION 3.24)
project(KSteam VERSION 0.1.0 LANGUAGES CXX)

#==============================================================================
# Set compiler settings
#==============================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#==============================================================================
# Import Numerixx
#==============================================================================
set(FETCHCONTENT_SOURCE_DIR_NUMERIXX ${CMAKE_CURRENT_LIST_DIR}/../Numerixx)
include(FetchContent)
FetchContent_Declare(numerixx
        GIT_REPOSITORY https://github.com/troldal/Numerixx.git
        GIT_TAG        master
        )
FetchContent_MakeAvailable(numerixx)

#==============================================================================
# Add the XLSteam Core library
#==============================================================================
add_subdirectory(KSteam)

option(KSTEAM_ENABLE_DEMOS "Enable demo programs" ${PROJECT_IS_TOP_LEVEL})
if(KSTEAM_ENABLE_DEMOS)
    add_subdirectory(demo)
endif()

option(KSTEAM_ENABLE_UNITTESTS "Enable unit tests" ${PROJECT_IS_TOP_LEVEL})
if(KSTEAM_ENABLE_UNITTESTS)
    add_subdirectory(unittest)
endif()

option(KSTEAM_ENABLE_PERFTESTS "Enable performance tests" ${PROJECT_IS_TOP_LEVEL})
if(KSTEAM_ENABLE_PERFTESTS)
    add_subdirectory(perftest)
endif()