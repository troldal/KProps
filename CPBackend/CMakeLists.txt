#==============================================================================
# Preamble
#==============================================================================
cmake_minimum_required(VERSION 3.26)
project(KProps.CPBackend VERSION 0.1.0 LANGUAGES CXX)

#==============================================================================
# Set compiler settings
#==============================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(CPBackend INTERFACE)
target_include_directories(CPBackend INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
target_link_libraries(CPBackend INTERFACE KProps CoolProp)