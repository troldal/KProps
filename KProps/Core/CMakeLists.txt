#==============================================================================
# Preamble
#==============================================================================
cmake_minimum_required(VERSION 3.26)
project(KProps.Core VERSION 0.1.0 LANGUAGES CXX)

#==============================================================================
# Set compiler settings
#==============================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#==============================================================================
# Create core library
#==============================================================================
# This constitutes the core KProps interface library, and is independent of any
# specific implementation. It is header-only, and contains the core classes and
# functions that are used to define and manipulate thermodynamic models, such
# as computing properties and derivatives.
# The KProps::Core library should be used in conjunction with a specific backend,
# such as one of the bundled backend implementations, or a custom backend.
add_library(KPropsCore INTERFACE)
target_include_directories(KPropsCore INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
target_link_libraries(KPropsCore INTERFACE KPropsUtils numerixx::deriv)

add_library(KProps::Core ALIAS KPropsCore)
