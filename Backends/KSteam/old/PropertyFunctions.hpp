//
// Created by kenne on 01/02/2024.
//

#pragma once

#include <tuple>

#include ".utils/Error.hpp"
#include ".utils/Properties.hpp"

#include <Deriv.hpp>

#include "Water.hpp"

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

    template<typename FLUID_T>
    class PropertyFunctions
    {

        static constexpr FLUID_T m_fluid {};
    public:
        static constexpr auto PropertyFunctionsPT = std::make_tuple(

            // Pressure:
            [](P Pressure, T Temperature) {
                if (!std::isfinite(Pressure)) throw KSteamError("Invalid pressure", "PropertyFunctionsPT", { { "T", Temperature }, { "P", Pressure } });
                return Pressure;
            },

            // Temperature:
            [](P Pressure, T Temperature) {
                if (!std::isfinite(Temperature)) throw KSteamError("Invalid temperature", "PropertyFunctionsPT", { { "T", Temperature }, { "P", Pressure } });
                return Temperature;
            },

            // Saturation pressure:
            [](P Pressure, T Temperature) {
                auto result = PSat {IF97::psat97(Temperature)};
                if (!std::isfinite(result)) throw KSteamError("Invalid saturation pressure", "PropertyFunctionsPT", { { "T", Temperature }, { "P", Pressure } });
                return result;
            },

            // Saturation temperature:
            [](P Pressure, T Temperature) {
                auto result = TSat{IF97::Tsat97(Pressure)};
                if (!std::isfinite(result))
                    throw KSteamError("Invalid saturation temperature", "PropertyFunctionsPT", { { "T", Temperature }, { "P", Pressure } });
                return result;
            },

            // Density:
            [](P Pressure, T Temperature) {
                auto result = Rho{IF97::rhomass_Tp(Temperature, Pressure)};
                if (!std::isfinite(result)) throw KSteamError("Invalid density", "PropertyFunctionsPT", { { "T", Temperature }, { "P", Pressure } });
                return result;
            },

            // Volume:
            [](P Pressure, T Temperature) {
                auto result = V{1.0 / IF97::rhomass_Tp(Temperature, Pressure)};
                if (!std::isfinite(result)) throw KSteamError("Invalid volume", "PropertyFunctionsPT", { { "T", Temperature }, { "P", Pressure } });
                return result;
            },

            // Enthalpy:
            [](P Pressure, T Temperature) {
                if (Temperature < IF97::Tmin) {
                    auto slope = *nxx::deriv::forward([Pressure](FLOAT t){return IF97::hmass_Tp(t, Pressure);}, IF97::Tmin);
                    return H{IF97::hmass_Tp(IF97::Tmin, Pressure) + slope * (Temperature - IF97::Tmin)};
                }

                if (Temperature > IF97::Tmax) {
                    auto slope = *nxx::deriv::backward([Pressure](FLOAT t){return IF97::hmass_Tp(t, Pressure);}, IF97::Tmax);
                    return H{IF97::hmass_Tp(IF97::Tmax, Pressure) + slope * (Temperature - IF97::Tmax)};
                }


                // auto result = H{IF97::hmass_Tp(Temperature, Pressure)};
                auto result = H{m_fluid.enthalpyAtPT(Pressure, Temperature)};
                if (!std::isfinite(result)) throw KSteamError("Invalid enthalpy", "PropertyFunctionsPT", { { "T", Temperature }, { "P", Pressure } });
                return result;
            },

            // Entropy:
            [](P Pressure, T Temperature) {
                auto result = S{IF97::smass_Tp(Temperature, Pressure)};
                if (!std::isfinite(result)) throw KSteamError("Invalid entropy", "PropertyFunctionsPT", { { "T", Temperature }, { "P", Pressure } });
                return result;
            },

            // Internal energy:
            [](P Pressure, T Temperature) {
                auto result = U{IF97::umass_Tp(Temperature, Pressure)};
                if (!std::isfinite(result)) throw KSteamError("Invalid internal energy", "PropertyFunctionsPT", { { "T", Temperature }, { "P", Pressure } });
                return result;
            },

            // Cp:
            [](P Pressure, T Temperature) {
                auto result = Cp{IF97::cpmass_Tp(Temperature, Pressure)};
                if (!std::isfinite(result))
                    throw KSteamError("Invalid specific heat capacity (Cp)", "PropertyFunctionsPT", { { "T", Temperature }, { "P", Pressure } });
                return result;
            },

            // Cv:
            [](P Pressure, T Temperature) {
                auto result = Cv{IF97::cvmass_Tp(Temperature, Pressure)};
                if (!std::isfinite(result))
                    throw KSteamError("Invalid specific heat capacity (Cv)", "PropertyFunctionsPT", { { "T", Temperature }, { "P", Pressure } });
                return IF97::cvmass_Tp(Temperature, Pressure);
            },

            // Speed of sound:
            [](P Pressure, T Temperature) {
                auto result = W{IF97::speed_sound_Tp(Temperature, Pressure)};
                if (!std::isfinite(result)) throw KSteamError("Invalid speed of sound", "PropertyFunctionsPT", { { "T", Temperature }, { "P", Pressure } });
                return result;
            },

            // Isentropic exponent:
            [](P Pressure, T Temperature) {
                auto result = Kappa{IF97::cpmass_Tp(Temperature, Pressure) / IF97::cvmass_Tp(Temperature, Pressure)};
                if (!std::isfinite(result)) throw KSteamError("Invalid isentropic exponent", "PropertyFunctionsPT", { { "T", Temperature }, { "P", Pressure } });
                return result;
            },

            // Helmholtz energy:
            [](P Pressure, T Temperature) {
                auto result = A{IF97::umass_Tp(Temperature, Pressure) - Temperature * IF97::smass_Tp(Temperature, Pressure)};
                if (!std::isfinite(result)) throw KSteamError("Invalid Helmholtz energy", "PropertyFunctionsPT", { { "T", Temperature }, { "P", Pressure } });
                return result;
            },

            // Gibbs energy:
            [](P Pressure, T Temperature) {
                auto result = G{IF97::hmass_Tp(Temperature, Pressure) - Temperature * IF97::smass_Tp(Temperature, Pressure)};
                if (!std::isfinite(result)) throw KSteamError("Invalid Gibbs energy", "PropertyFunctionsPT", { { "T", Temperature }, { "P", Pressure } });
                return result;
            },

            // Compressibility factor:
            [](P Pressure, T Temperature) {
                auto result = Z{Pressure * IF97::rhomass_Tp(Temperature, Pressure) / (Temperature * 8.31446261815324)};
                if (!std::isfinite(result))
                    throw KSteamError("Invalid compressibility factor", "PropertyFunctionsPT", { { "T", Temperature }, { "P", Pressure } });
                return result;
            },

            // Vapor quality:
            [](P Pressure, T Temperature) {
                if (Temperature > IF97::get_Tcrit() && Pressure > IF97::get_pcrit()) return X{-1.0};
                //                    throw XLSteamError("Vapor quality undefined for T > Tcrit and P > Pcrit",
                //                                       "VaporQuality(P, T)",
                //                                       { { "P", P }, { "T", T } });
                if (Temperature <= IF97::get_Tcrit() && Pressure > IF97::psat97(Temperature)) return X{0.0};
                if (Pressure <= IF97::get_pcrit() && Temperature > IF97::Tsat97(Pressure))
                    return X{1.0};
                else
                    return X{-1.0};
            },

            // Dynamic viscosity:
            [](P Pressure, T Temperature) {
                auto result = Eta{IF97::visc_Tp(Temperature, Pressure)};
                if (!std::isfinite(result)) throw KSteamError("Invalid dynamic viscosity", "PropertyFunctionsPT", { { "T", Temperature }, { "P", Pressure } });
                return result;
            },

            // Kinematic viscosity:
            [](P Pressure, T Temperature) {
                auto result = Nu{IF97::visc_Tp(Temperature, Pressure) / IF97::rhomass_Tp(Temperature, Pressure)};
                if (!std::isfinite(result)) throw KSteamError("Invalid kinematic viscosity", "PropertyFunctionsPT", { { "T", Temperature }, { "P", Pressure } });
                return result;
            },

            // Thermal conductivity:
            [](P Pressure, T Temperature) {
                auto result = TC{IF97::tcond_Tp(Temperature, Pressure)};
                if (!std::isfinite(result))
                    throw KSteamError("Invalid thermal conductivity", "PropertyFunctionsPT", { { "T", Temperature }, { "P", Pressure } });
                return result;
            },

            // Prandtl number:
            [](P Pressure, T Temperature) {
                auto result = PR{IF97::prandtl_Tp(Temperature, Pressure)};
                if (!std::isfinite(result)) throw KSteamError("Invalid Prandtl number", "PropertyFunctionsPT", { { "T", Temperature }, { "P", Pressure } });
                return result;
            });



        static constexpr auto PropertyFunctionsPX = std::make_tuple(

        // Pressure:
        [](P Pressure, X VaporFraction) {
            if (!std::isfinite(Pressure)) throw KSteamError("Invalid pressure", "PropertyFunctionsPX", { { "P", Pressure }, { "x", VaporFraction } });
            return Pressure;
        },

        // Temperature:
        [](P Pressure, X VaporFraction) {
            auto result = T{IF97::Tsat97(Pressure)};
            if (!std::isfinite(result)) throw KSteamError("Invalid temperature", "PropertyFunctionsPX", { { "P", Pressure }, { "x", VaporFraction } });
            return result;
        },

        // Saturation pressure:
        [](P Pressure, X VaporFraction) {
            if (!std::isfinite(Pressure)) throw KSteamError("Invalid saturation pressure", "PropertyFunctionsPX", { { "P", Pressure }, { "x", VaporFraction } });
            return Pressure;
        },

        // Saturation temperature:
        [](P Pressure, X VaporFraction) {
            auto result = TSat{IF97::Tsat97(Pressure)};
            if (!std::isfinite(result))
                throw KSteamError("Invalid saturation temperature", "PropertyFunctionsPX", { { "P", Pressure }, { "x", VaporFraction } });
            return result;
        },

        // Density:
        [](P Pressure, X VaporFraction) {
            auto result = Rho{IF97::rhomass_pQ(Pressure, VaporFraction)};
            if (!std::isfinite(result)) throw KSteamError("Invalid density", "PropertyFunctionsPX", { { "P", Pressure }, { "x", VaporFraction } });
            return result;
        },

        // Volume:
        [](P Pressure, X VaporFraction) {
            auto result = V{1.0 / IF97::rhomass_pQ(Pressure, VaporFraction)};
            if (!std::isfinite(result)) throw KSteamError("Invalid volume", "PropertyFunctionsPX", { { "P", Pressure }, { "x", VaporFraction } });
            return result;
        },

        // Enthalpy:
        [](P Pressure, X VaporFraction) {
            auto result = H{IF97::hmass_pQ(Pressure, VaporFraction)};
            if (!std::isfinite(result)) throw KSteamError("Invalid enthalpy", "PropertyFunctionsPX", { { "P", Pressure }, { "x", VaporFraction } });
            return result;
        },

        // Entropy:
        [](P Pressure, X VaporFraction) {
            auto result = S{IF97::smass_pQ(Pressure, VaporFraction)};
            if (!std::isfinite(result)) throw KSteamError("Invalid entropy", "PropertyFunctionsPX", { { "P", Pressure }, { "x", VaporFraction } });
            return result;
        },

        // Internal energy:
        [](P Pressure, X VaporFraction) {
            auto result = U{IF97::umass_pQ(Pressure, VaporFraction)};
            if (!std::isfinite(result))
                throw KSteamError("Invalid internal energy", "PropertyFunctionsPX", { { "P", Pressure }, { "x", VaporFraction } });
            return result;
        },

        // Cp:
        [](P Pressure, X VaporFraction) {
            auto result = Cp{IF97::cpvap_p(Pressure) * VaporFraction + IF97::cpliq_p(Pressure) * (1 - VaporFraction)};
            if (!std::isfinite(result))
                throw KSteamError("Invalid specific heat at constant pressure", "PropertyFunctionsPX", { { "P", Pressure }, { "x", VaporFraction } });
            return result;
        },

        // Cv:
        [](P Pressure, X VaporFraction) {
            auto result = Cv{IF97::cvvap_p(Pressure) * VaporFraction + IF97::cvliq_p(Pressure) * (1 - VaporFraction)};
            if (!std::isfinite(result))
                throw KSteamError("Invalid specific heat at constant volume", "PropertyFunctionsPX", { { "P", Pressure }, { "x", VaporFraction } });
            return result;
        },

        // Speed of sound:
        [](P Pressure, X VaporFraction) {
            W result{0.0};
            if (VaporFraction == 1.0)
                result = W{IF97::speed_soundvap_p(Pressure)};
            else if (VaporFraction == 0.0)
                result = W{IF97::speed_soundliq_p(Pressure)};
            else
                result = W{std::nan("")};
                //throw KSteamError("Invalid speed of sound", "PropertyFunctionsPX", { { "P", P }, { "x", x } });

            //if (!std::isfinite(result))
              //  throw KSteamError("Invalid speed of sound", "PropertyFunctionsPX", { { "P", P }, { "x", x } });

            return result;
        },

        // Isentropic exponent:
        [](P Pressure, X VaporFraction) {
            auto result = Kappa{IF97::cpvap_p(Pressure) * VaporFraction + IF97::cpliq_p(Pressure) * (1 - VaporFraction) / IF97::cvvap_p(Pressure) * VaporFraction + IF97::cvliq_p(Pressure) * (1 - VaporFraction)};
            if (!std::isfinite(result))
                throw KSteamError("Invalid isentropic exponent", "PropertyFunctionsPX", { { "P", Pressure }, { "x", VaporFraction } });
            return result;
        },

        // Helmholtz energy:
        [](P Pressure, X VaporFraction) {
            auto result = A{IF97::umass_pQ(Pressure, VaporFraction) - IF97::Tsat97(Pressure) * IF97::smass_pQ(Pressure, VaporFraction)};
            if (!std::isfinite(result))
                throw KSteamError("Invalid Helmholtz energy", "PropertyFunctionsPX", { { "P", Pressure }, { "x", VaporFraction } });
            return result;
        },

        // Gibbs energy:
        [](P Pressure, X VaporFraction) {
            auto result = G{IF97::hmass_pQ(Pressure, VaporFraction) - IF97::Tsat97(Pressure) * IF97::smass_pQ(Pressure, VaporFraction)};
            if (!std::isfinite(result)) throw KSteamError("Invalid Gibbs energy", "PropertyFunctionsPX", { { "P", Pressure }, { "x", VaporFraction } });
            return result;
        },

        // Compressibility factor:
        [](P Pressure, X VaporFraction) {
            auto result = Z{Pressure * (1.0 / IF97::rhomass_pQ(Pressure, VaporFraction)) * IF97::get_MW() / (IF97::Tsat97(Pressure) * 8.31446261815324)};
            if (!std::isfinite(result))
                throw KSteamError("Invalid compressibility factor", "PropertyFunctionsPX", { { "P", Pressure }, { "x", VaporFraction } });
            return result;
        },

        // Vapor quality:
        [](P Pressure, X VaporFraction) {
            if (!std::isfinite(VaporFraction)) throw KSteamError("Invalid vapor quality", "PropertyFunctionsPX", { { "P", Pressure }, { "x", VaporFraction } });
            return VaporFraction;
        },

        // Dynamic viscosity:
        [](P Pressure, X VaporFraction) {
            Eta result{0.0};
            if (VaporFraction == 1.0)
                result = Eta{IF97::viscvap_p(Pressure)};
            else if (VaporFraction == 0.0)
                result = Eta{IF97::viscliq_p(Pressure)};
            else
                result = Eta{std::nan("")};
                //throw KSteamError("Invalid dynamic viscosity", "PropertyFunctionsPX", { { "P", P }, { "x", x } });

            //if (!std::isfinite(result))
                //throw KSteamError("Invalid dynamic viscosity", "PropertyFunctionsPX", { { "P", P }, { "x", x } });

            return result;
        },

        // Kinematic viscosity:
        [](P Pressure, X VaporFraction) {
            Nu result{0.0};
            if (VaporFraction == 1.0)
                result = Nu{IF97::viscvap_p(Pressure) / IF97::rhomass_pQ(Pressure, VaporFraction)};
            else if (VaporFraction == 0.0)
                result = Nu{IF97::viscliq_p(Pressure) / IF97::rhomass_pQ(Pressure, VaporFraction)};
            else
                result = Nu{std::nan("")};
                //throw KSteamError("Invalid kinematic viscosity", "PropertyFunctionsPX", { { "P", P }, { "x", x } });

            //if (!std::isfinite(result))
                //throw KSteamError("Invalid kinematic viscosity", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return result;
        },

        // Thermal conductivity:
        [](P Pressure, X VaporFraction) {
            TC result{0.0};
            if (VaporFraction == 1.0)
                result = TC{IF97::tcondvap_p(Pressure)};
            else if (VaporFraction == 0.0)
                result = TC{IF97::tcondliq_p(Pressure)};
            else
                result = TC{std::nan("")};
                //throw KSteamError("Invalid thermal conductivity", "PropertyFunctionsPX", { { "P", P }, { "x", x } });

            //if (!std::isfinite(result))
                //throw KSteamError("Invalid thermal conductivity", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return result;
        },

        // Prandtl number:
        [](P Pressure, X VaporFraction) {
            PR result{0.0};
            if (VaporFraction == 1.0)
                result = PR{IF97::prandtlvap_p(Pressure)};
            else if (VaporFraction == 0.0)
                result = PR{IF97::prandtlliq_p(Pressure)};
            else
                result = PR{std::nan("")};
                //throw KSteamError("Invalid Prandtl number", "PropertyFunctionsPX", { { "P", P }, { "x", x } });

            //if (!std::isfinite(result)) throw KSteamError("Invalid Prandtl number", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
            return result;
        });
    };

}    // namespace KSteam::detail