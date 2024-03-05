#=======================================================================================================================
# Preamble
#=======================================================================================================================
cmake_minimum_required(VERSION 3.24 FATAL_ERROR)
project(KSteam.Demo)



#=======================================================================================================================
# Include the fmt library
#=======================================================================================================================
#add_subdirectory(fmt SYSTEM)

add_library(FastCSV INTERFACE IMPORTED)
target_include_directories(FastCSV SYSTEM INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/FastCSV/>)

find_package(sciplot CONFIG REQUIRED)

#=======================================================================================================================
# Define demo target
#=======================================================================================================================
#add_executable(SinglePhase EXCLUDE_FROM_ALL "")
#target_sources(SinglePhase
#        PRIVATE
#        SinglePhase.cpp
#        )
#target_link_libraries(SinglePhase
#        PRIVATE
#        KSteam fmt FastCSV
#        )
#
#add_executable(HighTemperature EXCLUDE_FROM_ALL "")
#target_sources(HighTemperature
#        PRIVATE
#        HighTemperature.cpp
#)
#target_link_libraries(HighTemperature
#        PRIVATE
#        KSteam fmt FastCSV
#)
#
#add_executable(PropertyPlotter EXCLUDE_FROM_ALL "")
#target_sources(PropertyPlotter
#        PRIVATE
#        PropertyPlotter.cpp
#)
#target_link_libraries(PropertyPlotter
#        PRIVATE
#        KSteam fmt FastCSV sciplot::sciplot
#)

add_executable(NewInterface EXCLUDE_FROM_ALL "")
target_sources(NewInterface
        PRIVATE
        NewInterface.cpp
)
target_link_libraries(NewInterface
        PRIVATE
        KProps CPBackend FastCSV sciplot::sciplot CoolProp
)

add_executable(PropertyPX EXCLUDE_FROM_ALL "")
target_sources(PropertyPX
        PRIVATE
        PropertyPX.cpp
)
target_link_libraries(PropertyPX
        PRIVATE
        KProps CPBackend FastCSV sciplot::sciplot CoolProp
)

add_executable(PropertyTX EXCLUDE_FROM_ALL "")
target_sources(PropertyTX
        PRIVATE
        PropertyTX.cpp
)
target_link_libraries(PropertyTX
        PRIVATE
        KProps CPBackend FastCSV sciplot::sciplot CoolProp
)

add_executable(PropertyPT EXCLUDE_FROM_ALL "")
target_sources(PropertyPT
        PRIVATE
        PropertyPT.cpp
)
target_link_libraries(PropertyPT
        PRIVATE
        KProps CPBackend FastCSV sciplot::sciplot CoolProp
)