#=======================================================================================================================
# EXTERNAL LIBRARIES
#   Define external libraries used by KSteam. The libraries are header-only, so
#   INTERFACE libraries should be defined.
#=======================================================================================================================
add_library(external INTERFACE)
target_include_directories(external SYSTEM INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
