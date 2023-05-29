//
// Created by Kenneth Balslev on 16/05/2023.
//

#include "TestXLSteamCommon.hpp"

TEST_CASE("KSteam Fuzzing")
{
    std::random_device rd;
    std::mt19937       mt_generator(rd());
    int                count = 1000;

    SECTION("T or P Specifications")
    {
        for (int i = 0; i <= count; ++i) {
            std::uniform_real_distribution<double> distT(273.16, 2273.15);
            auto                                   temperature = distT(mt_generator);

            auto p_range = KSteam::PressureLimits(temperature);

            std::uniform_real_distribution<double> distP(p_range.first, p_range.second);
            auto                                   pressure = distP(mt_generator);

            checkCalcTV(pressure, temperature);
            checkCalcTRHO(pressure, temperature);
            checkCalcTS(pressure, temperature);
            checkCalcTU(pressure, temperature);
            checkCalcTH(pressure, temperature);

            checkCalcPV(pressure, temperature);
            checkCalcPRHO(pressure, temperature);
            checkCalcPS(pressure, temperature);
            checkCalcPU(pressure, temperature);
            checkCalcPH(pressure, temperature);
        }
    }

    SECTION("Quality Specifications")
    {
        for (int i = 0; i <= count; ++i) {
            std::uniform_real_distribution<double> distP(611.657, 22064000.0);
            std::uniform_real_distribution<double> distX(0.0, 1.0);

            auto pressure    = distP(mt_generator);
            auto quality     = distX(mt_generator);
            auto temperature = IF97::Tsat97(pressure);

            checkCalcSatPV(pressure, quality);
            checkCalcSatPRHO(pressure, quality);
            checkCalcSatPS(pressure, quality);
            checkCalcSatPU(pressure, quality);
            checkCalcSatPH(pressure, quality);

            checkCalcSatTV(temperature, quality);
            checkCalcSatTRHO(temperature, quality);
            checkCalcSatTS(temperature, quality);
            checkCalcSatTU(temperature, quality);
            checkCalcSatTH(temperature, quality);
        }
    }
}