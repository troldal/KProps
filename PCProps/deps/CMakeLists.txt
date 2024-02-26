#=======================================================================================================================
# EXTERNAL LIBRARIES
#   Define external libraries used by KSteam. The libraries are header-only, so
#   INTERFACE libraries should be defined.
#=======================================================================================================================
add_library(pcprops_deps INTERFACE)
target_include_directories(pcprops_deps SYSTEM INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
