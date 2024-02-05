//
// Created by kenne on 01/02/2024.
//

#pragma once

#include <tuple>

namespace KSteam::detail
{

    enum Calculation : size_t {
        PressureCalc = 0,
        TemperatureCalc,
        SaturationPressureCalc,
        SaturationTemperatureCalc,
        DensityCalc,
        VolumeCalc,
        EnthalpyCalc,
        EntropyCalc,
        InternalEnergyCalc,
        CpCalc,
        CvCalc,
        SpeedOfSoundCalc,
        IsentropicExponentCalc,
        HelmholtzEnergyCalc,
        GibbsEnergyCalc,
        CompressibilityFactorCalc,
        VaporQualityCalc,
        DynamicViscosityCalc,
        KinematicViscosityCalc,
        ThermalConductivityCalc,
        PrandtlNumberCalc
    };

    constexpr auto PropertyFunctionsPT = std::make_tuple(

        // Pressure:
        [](FLOAT P, FLOAT T) {
            if (!std::isfinite(P)) throw KSteamError("Invalid pressure", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
            return P;
        },

        // Temperature:
        [](FLOAT P, FLOAT T) {
            if (!std::isfinite(T)) throw KSteamError("Invalid temperature", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
            return T;
        },

        // Saturation pressure:
        [](FLOAT P, FLOAT T) {
            auto result = IF97::psat97(T);
            if (!std::isfinite(result)) throw KSteamError("Invalid saturation pressure", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
            return result;
        },

        // Saturation temperature:
        [](FLOAT P, FLOAT T) {
            auto result = IF97::Tsat97(P);
            if (!std::isfinite(result))
                throw KSteamError("Invalid saturation temperature", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
            return result;
        },

        // Density:
        [](FLOAT P, FLOAT T) {
            auto result = IF97::rhomass_Tp(T, P);
            if (!std::isfinite(result)) throw KSteamError("Invalid density", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
            return result;
        },

        // Volume:
        [](FLOAT P, FLOAT T) {
            auto result = 1.0 / IF97::rhomass_Tp(T, P);
            if (!std::isfinite(result)) throw KSteamError("Invalid volume", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
            return result;
        },

        // Enthalpy:
        [](FLOAT P, FLOAT T) {
            auto result = IF97::hmass_Tp(T, P);
            if (!std::isfinite(result)) throw KSteamError("Invalid enthalpy", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
            return result;
        },

        // Entropy:
        [](FLOAT P, FLOAT T) {
            auto result = IF97::smass_Tp(T, P);
            if (!std::isfinite(result)) throw KSteamError("Invalid entropy", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
            return result;
        },

        // Internal energy:
        [](FLOAT P, FLOAT T) {
            auto result = IF97::umass_Tp(T, P);
            if (!std::isfinite(result)) throw KSteamError("Invalid internal energy", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
            return result;
        },

        // Cp:
        [](FLOAT P, FLOAT T) {
            auto result = IF97::cpmass_Tp(T, P);
            if (!std::isfinite(result))
                throw KSteamError("Invalid specific heat capacity (Cp)", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
            return result;
        },

        // Cv:
        [](FLOAT P, FLOAT T) {
            auto result = IF97::cvmass_Tp(T, P);
            if (!std::isfinite(result))
                throw KSteamError("Invalid specific heat capacity (Cv)", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
            return IF97::cvmass_Tp(T, P);
        },

        // Speed of sound:
        [](FLOAT P, FLOAT T) {
            auto result = IF97::speed_sound_Tp(T, P);
            if (!std::isfinite(result)) throw KSteamError("Invalid speed of sound", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
            return result;
        },

        // Isentropic exponent:
        [](FLOAT P, FLOAT T) {
            auto result = IF97::cpmass_Tp(T, P) / IF97::cvmass_Tp(T, P);
            if (!std::isfinite(result)) throw KSteamError("Invalid isentropic exponent", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
            return result;
        },

        // Helmholtz energy:
        [](FLOAT P, FLOAT T) {
            auto result = IF97::umass_Tp(T, P) - T * IF97::smass_Tp(T, P);
            if (!std::isfinite(result)) throw KSteamError("Invalid Helmholtz energy", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
            return result;
        },

        // Gibbs energy:
        [](FLOAT P, FLOAT T) {
            auto result = IF97::hmass_Tp(T, P) - T * IF97::smass_Tp(T, P);
            if (!std::isfinite(result)) throw KSteamError("Invalid Gibbs energy", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
            return result;
        },

        // Compressibility factor:
        [](FLOAT P, FLOAT T) {
            auto result = P * IF97::rhomass_Tp(T, P) / (T * 8.31446261815324);
            if (!std::isfinite(result))
                throw KSteamError("Invalid compressibility factor", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
            return result;
        },

        // Vapor quality:
        [](FLOAT P, FLOAT T) {
            if (T > IF97::get_Tcrit() && P > IF97::get_pcrit()) return -1.0;
            //                    throw XLSteamError("Vapor quality undefined for T > Tcrit and P > Pcrit",
            //                                       "VaporQuality(P, T)",
            //                                       { { "P", P }, { "T", T } });
            if (T <= IF97::get_Tcrit() && P > IF97::psat97(T)) return 0.0;
            if (P <= IF97::get_pcrit() && T > IF97::Tsat97(P))
                return 1.0;
            else
                return -1.0;
        },

        // Dynamic viscosity:
        [](FLOAT P, FLOAT T) {
            auto result = IF97::visc_Tp(T, P);
            if (!std::isfinite(result)) throw KSteamError("Invalid dynamic viscosity", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
            return result;
        },

        // Kinematic viscosity:
        [](FLOAT P, FLOAT T) {
            auto result = IF97::visc_Tp(T, P) / IF97::rhomass_Tp(T, P);
            if (!std::isfinite(result)) throw KSteamError("Invalid kinematic viscosity", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
            return result;
        },

        // Thermal conductivity:
        [](FLOAT P, FLOAT T) {
            auto result = IF97::tcond_Tp(T, P);
            if (!std::isfinite(result))
                throw KSteamError("Invalid thermal conductivity", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
            return result;
        },

        // Prandtl number:
        [](FLOAT P, FLOAT T) {
            auto result = IF97::prandtl_Tp(T, P);
            if (!std::isfinite(result)) throw KSteamError("Invalid Prandtl number", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
            return result;
        });

}    // namespace KSteam::detail