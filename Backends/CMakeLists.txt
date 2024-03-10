#==============================================================================
# Preamble
#==============================================================================
cmake_minimum_required(VERSION 3.26)
project(KProps.Backends VERSION 0.1.0 LANGUAGES CXX)

#==============================================================================
# Set compiler settings
#==============================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
#set(CMAKE_CXX_VISIBILITY_PRESET hidden)
#set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
#include(GenerateExportHeader)

#==============================================================================
# Create HEOS backend library
#==============================================================================
#
add_library(KPropsHEOS SHARED)
target_sources(KPropsHEOS PUBLIC HEOS/impl/HEOS.cpp)
target_include_directories(KPropsHEOS PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/HEOS)
target_link_libraries(KPropsHEOS PUBLIC CoolProp KProps::Types)

add_library(KProps::HEOS ALIAS KPropsHEOS)

#==============================================================================
# Create IF97 backend library
#==============================================================================
add_library(KPropsIF97 INTERFACE)
target_include_directories(KPropsIF97 INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/IF97)
target_link_libraries(KPropsIF97 INTERFACE KProps::Types CoolProp)

add_library(KProps::IF97 ALIAS KPropsIF97)