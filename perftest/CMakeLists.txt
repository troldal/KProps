#==================================================================================================================
# Preamble
#==================================================================================================================
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(XLSteam.Benchmark)

#==============================================================================
# Set compiler settings
#==============================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(gbench)


add_executable(XLSteamBenchmark)
target_sources(XLSteamBenchmark
        PRIVATE
        benchmark.cpp
        )

target_link_libraries(XLSteamBenchmark PRIVATE benchmark::benchmark benchmark::benchmark_main KSteam)
