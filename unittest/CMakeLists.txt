#=======================================================================================================================
# Preamble
#=======================================================================================================================
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(XLSteam.Tests)


include(FetchContent)
FetchContent_Declare(Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        3f0283d
        )

FetchContent_MakeAvailable(Catch2)


#=======================================================================================================================
# Define TEST target
#=======================================================================================================================
add_executable(XLSteamTests EXCLUDE_FROM_ALL "")
target_sources(XLSteamTests
        PRIVATE
        TestXLSteamPSpec.cpp
        )

target_link_libraries(XLSteamTests
        PRIVATE
        KSteam
        Catch2WithMain
        )

add_executable(TestTSpec EXCLUDE_FROM_ALL "")
target_sources(TestTSpec
        PRIVATE
        TestXLSteamTSpec.cpp
        )

target_link_libraries(TestTSpec
        PRIVATE
        KSteam
        Catch2WithMain
        )

add_executable(TestKSteamFuzzing EXCLUDE_FROM_ALL "")
target_sources(TestKSteamFuzzing
        PRIVATE
        TestKSteamFuzzing.cpp
        )

target_link_libraries(TestKSteamFuzzing
        PRIVATE
        KSteam
        Catch2WithMain
        )