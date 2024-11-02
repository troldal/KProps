#==============================================================================
# Preamble
#==============================================================================
cmake_minimum_required(VERSION 3.26)
project(KProps.Utils VERSION 0.1.0 LANGUAGES CXX)

#==============================================================================
# Set compiler settings
#==============================================================================
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(units CONFIG REQUIRED)
find_package(strong_type CONFIG REQUIRED)
find_package(fixed_string CONFIG REQUIRED)

add_subdirectory(_external)

add_library(KPropsUtils INTERFACE)
target_include_directories(KPropsUtils INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
target_link_libraries(KPropsUtils INTERFACE units::units strong_type::strong_type external)

add_library(KProps::Utils ALIAS KPropsUtils)