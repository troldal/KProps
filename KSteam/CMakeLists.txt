#==============================================================================
# Preamble
#==============================================================================
cmake_minimum_required(VERSION 3.20)
project(KSteam)

#==============================================================================
# Set compiler settings
#==============================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(deps)


find_package(LAPACK REQUIRED)
add_library(KSteam INTERFACE IMPORTED GLOBAL)
target_include_directories(KSteam SYSTEM INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
target_link_libraries(KSteam INTERFACE dependencies numerixx LAPACK::LAPACK)