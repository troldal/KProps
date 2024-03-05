#==============================================================================
# Preamble
#==============================================================================
cmake_minimum_required(VERSION 3.26)
project(KProps VERSION 0.1.0 LANGUAGES CXX)

#==============================================================================
# Set compiler settings
#==============================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(external)

add_library(KProps INTERFACE)
target_include_directories(KProps INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
target_link_libraries(KProps INTERFACE external numerixx::deriv)