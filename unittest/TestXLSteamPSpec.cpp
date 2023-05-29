//
// Created by Troldal on 25/09/2022.
//

#include "TestXLSteamCommon.hpp"

//TEST_CASE("Rigorous Test")
//{
//    double pressureFirst = 1000.0;
//    double pressureLast  = 100000000.0;
//
//    SECTION("PH Specification")
//    {
//        auto pressure = pressureFirst;
//        while (pressure < pressureLast) {
//            auto temp_range  = XLSteam::TemperatureLimits(pressure);
//            auto temperature = temp_range.first;
//            while (temperature < temp_range.second) {
//                checkCalcPH(pressure, temperature);
//                temperature = newTemperature(temperature, temp_range);
//            }
//            pressure = newPressure(pressure);
//        }
//    }
//
//    SECTION("PS Specification")
//    {
//        auto pressure = pressureFirst;
//        while (pressure < pressureLast) {
//            auto temp_range  = XLSteam::TemperatureLimits(pressure);
//            auto temperature = temp_range.first;
//            while (temperature < temp_range.second) {
//                checkCalcPS(pressure, temperature);
//                temperature = newTemperature(temperature, temp_range);
//            }
//            pressure = newPressure(pressure);
//        }
//    }
//
//    SECTION("PV Specification")
//    {
//        auto pressure = pressureFirst;
//        while (pressure < pressureLast) {
//            auto temp_range  = XLSteam::TemperatureLimits(pressure);
//            auto temperature = temp_range.first;
//            while (temperature < temp_range.second) {
//                checkCalcPV(pressure, temperature);
//                temperature = newTemperature(temperature, temp_range);
//            }
//
//            pressure = newPressure(pressure);
//        }
//    }
//
//    SECTION("PRHO Specification")
//    {
//        auto pressure = pressureFirst;
//        while (pressure < pressureLast) {
//            auto temp_range  = XLSteam::TemperatureLimits(pressure);
//            auto temperature = temp_range.first;
//            while (temperature < temp_range.second) {
//                checkCalcPRHO(pressure, temperature);
//                temperature = newTemperature(temperature, temp_range);
//            }
//
//            pressure = newPressure(pressure);
//        }
//    }
//
//    SECTION("PU Specification")
//    {
//        auto pressure = pressureFirst;
//        while (pressure < pressureLast) {
//            auto temp_range  = XLSteam::TemperatureLimits(pressure);
//            auto temperature = temp_range.first;
//            while (temperature < temp_range.second) {
//                checkCalcPU(pressure, temperature);
//                temperature = newTemperature(temperature, temp_range);
//            }
//
//            pressure = newPressure(pressure);
//        }
//    }
//}


//TEST_CASE("Edge Test")
//{
//    SECTION("PH Specification")
//    {
//        checkCalcPH(611.657, 273.16);
//        checkCalcPH(611.657, 647.096);
//        checkCalcPH(100000000.0, 273.16);
//        checkCalcPH(100000000.0, 647.096);
//    }
//
//    SECTION("PS Specification")
//    {
//        checkCalcPS(611.657, 273.16);
//        checkCalcPS(611.657, 647.096);
//        checkCalcPS(100000000.0, 273.16);
//        checkCalcPS(100000000.0, 647.096);
//    }
//
//    SECTION("PV Specification")
//    {
//        checkCalcPV(611.657, 273.16);
//        checkCalcPV(611.657, 647.096);
//        checkCalcPV(100000000.0, 273.16);
//        checkCalcPV(100000000.0, 647.096);
//    }
//
//    SECTION("PRHO Specification")
//    {
//        checkCalcPRHO(611.657, 273.16);
//        checkCalcPRHO(611.657, 647.096);
//        checkCalcPRHO(100000000.0, 273.16);
//        checkCalcPRHO(100000000.0, 647.096);
//    }
//
//    SECTION("PU Specification")
//    {
//        checkCalcPU(611.657, 273.16);
//        checkCalcPU(611.657, 647.096);
//        checkCalcPU(100000000.0, 273.16);
//        checkCalcPU(100000000.0, 647.096);
//    }
//}