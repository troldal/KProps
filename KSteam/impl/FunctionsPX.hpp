//
// Created by kenne on 01/02/2024.
//

#pragma once

#include <tuple>

namespace KSteam::detail {

    constexpr auto PropertyFunctionsPX = std::make_tuple(

        // Pressure:
        [](FLOAT P, FLOAT x) {
            if (!std::isfinite(P)) throw KSteamError("Invalid pressure", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return P;
        },

        // Temperature:
        [](FLOAT P, FLOAT x) {
            auto result = IF97::Tsat97(P);
            if (!std::isfinite(result)) throw KSteamError("Invalid temperature", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return result;
        },

        // Saturation pressure:
        [](FLOAT P, FLOAT x) {
            if (!std::isfinite(P)) throw KSteamError("Invalid saturation pressure", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return P;
        },

        // Saturation temperature:
        [](FLOAT P, FLOAT x) {
            auto result = IF97::Tsat97(P);
            if (!std::isfinite(result))
                throw KSteamError("Invalid saturation temperature", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return result;
        },

        // Density:
        [](FLOAT P, FLOAT x) {
            auto result = IF97::rhomass_pQ(P, x);
            if (!std::isfinite(result)) throw KSteamError("Invalid density", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return result;
        },

        // Volume:
        [](FLOAT P, FLOAT x) {
            auto result = 1.0 / IF97::rhomass_pQ(P, x);
            if (!std::isfinite(result)) throw KSteamError("Invalid volume", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return result;
        },

        // Enthalpy:
        [](FLOAT P, FLOAT x) {
            auto result = IF97::hmass_pQ(P, x);
            if (!std::isfinite(result)) throw KSteamError("Invalid enthalpy", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return result;
        },

        // Entropy:
        [](FLOAT P, FLOAT x) {
            auto result = IF97::smass_pQ(P, x);
            if (!std::isfinite(result)) throw KSteamError("Invalid entropy", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return result;
        },

        // Internal energy:
        [](FLOAT P, FLOAT x) {
            auto result = IF97::umass_pQ(P, x);
            if (!std::isfinite(result))
                throw KSteamError("Invalid internal energy", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return result;
        },

        // Cp:
        [](FLOAT P, FLOAT x) {
            auto result = IF97::cpvap_p(P) * x + IF97::cpliq_p(P) * (1 - x);
            if (!std::isfinite(result))
                throw KSteamError("Invalid specific heat at constant pressure", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return result;
        },

        // Cv:
        [](FLOAT P, FLOAT x) {
            auto result = IF97::cvvap_p(P) * x + IF97::cvliq_p(P) * (1 - x);
            if (!std::isfinite(result))
                throw KSteamError("Invalid specific heat at constant volume", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return result;
        },

        // Speed of sound:
        [](FLOAT P, FLOAT x) {
            FLOAT result;
            if (x == 1.0)
                result = IF97::speed_soundvap_p(P);
            else if (x == 0.0)
                result = IF97::speed_soundliq_p(P);
            else
                result = std::nan("");
                //throw KSteamError("Invalid speed of sound", "PropertyFunctionsPX", { { "P", P }, { "x", x } });

            //if (!std::isfinite(result))
              //  throw KSteamError("Invalid speed of sound", "PropertyFunctionsPX", { { "P", P }, { "x", x } });

            return result;
        },

        // Isentropic exponent:
        [](FLOAT P, FLOAT x) {
            auto result = IF97::cpvap_p(P) * x + IF97::cpliq_p(P) * (1 - x) / IF97::cvvap_p(P) * x + IF97::cvliq_p(P) * (1 - x);
            if (!std::isfinite(result))
                throw KSteamError("Invalid isentropic exponent", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return result;
        },

        // Helmholtz energy:
        [](FLOAT P, FLOAT x) {
            auto result = IF97::umass_pQ(P, x) - IF97::Tsat97(P) * IF97::smass_pQ(P, x);
            if (!std::isfinite(result))
                throw KSteamError("Invalid Helmholtz energy", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return result;
        },

        // Gibbs energy:
        [](FLOAT P, FLOAT x) {
            auto result = IF97::hmass_pQ(P, x) - IF97::Tsat97(P) * IF97::smass_pQ(P, x);
            if (!std::isfinite(result)) throw KSteamError("Invalid Gibbs energy", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return result;
        },

        // Compressibility factor:
        [](FLOAT P, FLOAT x) {
            auto result = P * (1.0 / IF97::rhomass_pQ(P, x)) * IF97::get_MW() / (IF97::Tsat97(P) * 8.31446261815324);
            if (!std::isfinite(result))
                throw KSteamError("Invalid compressibility factor", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return result;
        },

        // Vapor quality:
        [](FLOAT P, FLOAT x) {
            if (!std::isfinite(x)) throw KSteamError("Invalid vapor quality", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return x;
        },

        // Dynamic viscosity:
        [](FLOAT P, FLOAT x) {
            FLOAT result;
            if (x == 1.0)
                result = IF97::viscvap_p(P);
            else if (x == 0.0)
                result = IF97::viscliq_p(P);
            else
                result = std::nan("");
                //throw KSteamError("Invalid dynamic viscosity", "PropertyFunctionsPX", { { "P", P }, { "x", x } });

            //if (!std::isfinite(result))
                //throw KSteamError("Invalid dynamic viscosity", "PropertyFunctionsPX", { { "P", P }, { "x", x } });

            return result;
        },

        // Kinematic viscosity:
        [](FLOAT P, FLOAT x) {
            FLOAT result;
            if (x == 1.0)
                result = IF97::viscvap_p(P) / IF97::rhomass_pQ(P, x);
            else if (x == 0.0)
                result = IF97::viscliq_p(P) / IF97::rhomass_pQ(P, x);
            else
                result = std::nan("");
                //throw KSteamError("Invalid kinematic viscosity", "PropertyFunctionsPX", { { "P", P }, { "x", x } });

            //if (!std::isfinite(result))
                //throw KSteamError("Invalid kinematic viscosity", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return result;
        },

        // Thermal conductivity:
        [](FLOAT P, FLOAT x) {
            FLOAT result;
            if (x == 1.0)
                result = IF97::tcondvap_p(P);
            else if (x == 0.0)
                result = IF97::tcondliq_p(P);
            else
                result = std::nan("");
                //throw KSteamError("Invalid thermal conductivity", "PropertyFunctionsPX", { { "P", P }, { "x", x } });

            //if (!std::isfinite(result))
                //throw KSteamError("Invalid thermal conductivity", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return result;
        },

        // Prandtl number:
        [](FLOAT P, FLOAT x) {
            FLOAT result;
            if (x == 1.0)
                result = IF97::prandtlvap_p(P);
            else if (x == 0.0)
                result = IF97::prandtlliq_p(P);
            else
                result = std::nan("");
                //throw KSteamError("Invalid Prandtl number", "PropertyFunctionsPX", { { "P", P }, { "x", x } });

            //if (!std::isfinite(result)) throw KSteamError("Invalid Prandtl number", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return result;
        });

}