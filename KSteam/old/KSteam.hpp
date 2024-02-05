//
// Created by Kenneth Balslev on 23/04/2023.
//

#ifndef KSTEAM_KSTEAM_HPP
#define KSTEAM_KSTEAM_HPP

#include "KSteamError.hpp"
#include "Properties.hpp"
#include "impl/_external.hpp"

#include <concepts>
#include <functional>

namespace KSteam
{

    template<std::floating_point TYPE = double>
    class KSteam
    {
        using JSONString = std::string;

        enum class PropertyType {
            Pressure,
            Temperature,
            SaturationPressure,
            SaturationTemperature,
            Density,
            Volume,
            Enthalpy,
            Entropy,
            InternalEnergy,
            Cp,
            Cv,
            SpeedOfSound,
            IsentropicExponent,
            HelmholtzEnergy,
            GibbsEnergy,
            CompressibilityFactor,
            VaporQuality,
            DynamicViscosity,
            KinematicViscosity,
            ThermalConductivity,
            PrandtlNumber
        };

        const std::vector<std::pair<PropertyType, std::function<double(double, double)>>> PropertyFunctionsPT = {
            { PropertyType::Pressure,
              [](double T, double P) {
                  if (!std::isfinite(P)) throw KSteamError("Invalid pressure", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                  return P;
              } },
            { PropertyType::Temperature,
              [](double T, double P) {
                  if (!std::isfinite(T)) throw KSteamError("Invalid temperature", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                  return T;
              } },
            { PropertyType::SaturationPressure,
              [](double T, double P) {
                  auto result = IF97::psat97(T);
                  if (!std::isfinite(result))
                      throw KSteamError("Invalid saturation pressure", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                  return result;
              } },
            { PropertyType::SaturationTemperature,
              [](double T, double P) {
                  auto result = IF97::Tsat97(P);
                  if (!std::isfinite(result))
                      throw KSteamError("Invalid saturation temperature", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                  return result;
              } },
            { PropertyType::Density,
              [](double T, double P) {
                  auto result = IF97::rhomass_Tp(T, P);
                  if (!std::isfinite(result)) throw KSteamError("Invalid density", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                  return result;
              } },
            { PropertyType::Volume,
              [](double T, double P) {
                  auto result = 1.0 / IF97::rhomass_Tp(T, P);
                  if (!std::isfinite(result)) throw KSteamError("Invalid volume", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                  return result;
              } },
            { PropertyType::Enthalpy,
              [](double T, double P) {
                  auto result = IF97::hmass_Tp(T, P);
                  if (!std::isfinite(result)) throw KSteamError("Invalid enthalpy", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                  return result;
              } },
            { PropertyType::Entropy,
              [](double T, double P) {
                  auto result = IF97::smass_Tp(T, P);
                  if (!std::isfinite(result)) throw KSteamError("Invalid entropy", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                  return result;
              } },
            { PropertyType::InternalEnergy,
              [](double T, double P) {
                  auto result = IF97::umass_Tp(T, P);
                  if (!std::isfinite(result))
                      throw KSteamError("Invalid internal energy", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                  return result;
              } },
            { PropertyType::Cp,
              [](double T, double P) {
                  auto result = IF97::cpmass_Tp(T, P);
                  if (!std::isfinite(result))
                      throw KSteamError("Invalid specific heat capacity (Cp)", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                  return result;
              } },
            { PropertyType::Cv,
              [](double T, double P) {
                  auto result = IF97::cvmass_Tp(T, P);
                  if (!std::isfinite(result))
                      throw KSteamError("Invalid specific heat capacity (Cv)", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                  return IF97::cvmass_Tp(T, P);
              } },
            { PropertyType::SpeedOfSound,
              [](double T, double P) {
                  auto result = IF97::speed_sound_Tp(T, P);
                  if (!std::isfinite(result))
                      throw KSteamError("Invalid speed of sound", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                  return result;
              } },
            { PropertyType::IsentropicExponent,
              [](double T, double P) {
                  auto result = IF97::cpmass_Tp(T, P) / IF97::cvmass_Tp(T, P);
                  if (!std::isfinite(result))
                      throw KSteamError("Invalid isentropic exponent", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                  return result;
              } },
            { PropertyType::HelmholtzEnergy,
              [](double T, double P) {
                  auto result = IF97::umass_Tp(T, P) - T * IF97::smass_Tp(T, P);
                  if (!std::isfinite(result))
                      throw KSteamError("Invalid Helmholtz energy", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                  return result;
              } },
            { PropertyType::GibbsEnergy,
              [](double T, double P) {
                  auto result = IF97::hmass_Tp(T, P) - T * IF97::smass_Tp(T, P);
                  if (!std::isfinite(result)) throw KSteamError("Invalid Gibbs energy", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                  return result;
              } },
            { PropertyType::CompressibilityFactor,
              [](double T, double P) {
                  auto result = P / (IF97::rhomass_Tp(T, P) / IF97::get_MW() * T * 8.31446261815324);
                  if (!std::isfinite(result))
                      throw KSteamError("Invalid compressibility factor", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                  return result;
              } },
            { PropertyType::VaporQuality,
              [](double T, double P) {
                  if (T > IF97::get_Tcrit() && P > IF97::get_pcrit())
                      throw KSteamError("Vapor quality undefined for T > Tcrit and P > Pcrit",
                                        "VaporQuality(P, T)",
                                        { { "P", P }, { "T", T } });
                  if (T <= IF97::get_Tcrit() && P > IF97::psat97(T)) return 0.0;
                  if (P <= IF97::get_pcrit() && T > IF97::Tsat97(P))
                      return 1.0;
                  else
                      throw KSteamError("Vapor quality undefined for given P and T", "VaporQuality(P, T)", { { "P", P }, { "T", T } });
              } },
            { PropertyType::DynamicViscosity,
              [](double T, double P) {
                  auto result = IF97::visc_Tp(T, P);
                  if (!std::isfinite(result))
                      throw KSteamError("Invalid dynamic viscosity", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                  return result;
              } },
            { PropertyType::KinematicViscosity,
              [](double T, double P) {
                  auto result = IF97::visc_Tp(T, P) / IF97::rhomass_Tp(T, P);
                  if (!std::isfinite(result))
                      throw KSteamError("Invalid kinematic viscosity", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                  return result;
              } },
            { PropertyType::ThermalConductivity,
              [](double T, double P) {
                  auto result = IF97::tcond_Tp(T, P);
                  if (!std::isfinite(result))
                      throw KSteamError("Invalid thermal conductivity", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                  return result;
              } },
            { PropertyType::PrandtlNumber,
              [](double T, double P) {
                  auto result = IF97::prandtl_Tp(T, P);
                  if (!std::isfinite(result))
                      throw KSteamError("Invalid Prandtl number", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                  return result;
              } }
        };

        const std::vector<std::pair<PropertyType, std::function<double(double, double)>>> PropertyFunctionsPX = {
            { PropertyType::Pressure,
              [](double P, double x) {
                  if (!std::isfinite(P)) throw KSteamError("Invalid pressure", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  return P;
              } },
            { PropertyType::Temperature,
              [](double P, double x) {
                  auto result = IF97::Tsat97(P);
                  if (!std::isfinite(result)) throw KSteamError("Invalid temperature", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  return result;
              } },
            { PropertyType::SaturationPressure,
              [](double P, double x) {
                  if (!std::isfinite(P))
                      throw KSteamError("Invalid saturation pressure", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  return P;
              } },
            { PropertyType::SaturationTemperature,
              [](double P, double x) {
                  auto result = IF97::Tsat97(P);
                  if (!std::isfinite(result))
                      throw KSteamError("Invalid saturation temperature", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  return result;
              } },
            { PropertyType::Density,
              [](double P, double x) {
                  auto result = IF97::rhomass_pQ(P, x);
                  if (!std::isfinite(result)) throw KSteamError("Invalid density", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  return result;
              } },
            { PropertyType::Volume,
              [](double P, double x) {
                  auto result = 1.0 / IF97::rhomass_pQ(P, x);
                  if (!std::isfinite(result)) throw KSteamError("Invalid volume", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  return result;
              } },
            { PropertyType::Enthalpy,
              [](double P, double x) {
                  auto result = IF97::hmass_pQ(P, x);
                  if (!std::isfinite(result)) throw KSteamError("Invalid enthalpy", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  return result;
              } },
            { PropertyType::Entropy,
              [](double P, double x) {
                  auto result = IF97::smass_pQ(P, x);
                  if (!std::isfinite(result)) throw KSteamError("Invalid entropy", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  return result;
              } },
            { PropertyType::InternalEnergy,
              [](double P, double x) {
                  auto result = IF97::umass_pQ(P, x);
                  if (!std::isfinite(result))
                      throw KSteamError("Invalid internal energy", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  return result;
              } },
            { PropertyType::Cp,
              [](double P, double x) {
                  auto result = IF97::cpvap_p(P) * x + IF97::cpliq_p(P) * (1 - x);
                  if (!std::isfinite(result))
                      throw KSteamError("Invalid specific heat at constant pressure", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  return result;
              } },
            { PropertyType::Cv,
              [](double P, double x) {
                  auto result = IF97::cvvap_p(P) * x + IF97::cvliq_p(P) * (1 - x);
                  if (!std::isfinite(result))
                      throw KSteamError("Invalid specific heat at constant volume", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  return result;
              } },
            { PropertyType::SpeedOfSound,
              [](double P, double x) {
                  double result;
                  if (x == 1.0)
                      result = IF97::speed_soundvap_p(P);
                  else if (x == 0.0)
                      result = IF97::speed_soundliq_p(P);
                  else
                      throw KSteamError("Invalid speed of sound", "PropertyFunctionsPX", { { "P", P }, { "x", x } });

                  if (!std::isfinite(result))
                      throw KSteamError("Invalid speed of sound", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  else
                      return result;
              } },
            { PropertyType::IsentropicExponent,
              [](double P, double x) {
                  auto result = IF97::cpvap_p(P) * x + IF97::cpliq_p(P) * (1 - x) / IF97::cvvap_p(P) * x + IF97::cvliq_p(P) * (1 - x);
                  if (!std::isfinite(result))
                      throw KSteamError("Invalid isentropic exponent", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  return result;
              } },
            { PropertyType::HelmholtzEnergy,
              [](double P, double x) {
                  auto result = IF97::umass_pQ(P, x) - IF97::Tsat97(P) * IF97::smass_pQ(P, x);
                  if (!std::isfinite(result))
                      throw KSteamError("Invalid Helmholtz energy", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  return result;
              } },
            { PropertyType::GibbsEnergy,
              [](double P, double x) {
                  auto result = IF97::hmass_pQ(P, x) - IF97::Tsat97(P) * IF97::smass_pQ(P, x);
                  if (!std::isfinite(result)) throw KSteamError("Invalid Gibbs energy", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  return result;
              } },
            { PropertyType::CompressibilityFactor,
              [](double P, double x) {
                  auto result = P * (1.0 / IF97::rhomass_pQ(P, x)) * IF97::get_MW() / (IF97::Tsat97(P) * 8.31446261815324);
                  if (!std::isfinite(result))
                      throw KSteamError("Invalid compressibility factor", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  return result;
              } },
            { PropertyType::VaporQuality,
              [](double P, double x) {
                  if (!std::isfinite(x)) throw KSteamError("Invalid vapor quality", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  return x;
              } },
            { PropertyType::DynamicViscosity,
              [](double P, double x) {
                  double result;
                  if (x == 1.0)
                      result = IF97::viscvap_p(P);
                  else if (x == 0.0)
                      result = IF97::viscliq_p(P);
                  else
                      throw KSteamError("Invalid dynamic viscosity", "PropertyFunctionsPX", { { "P", P }, { "x", x } });

                  if (!std::isfinite(result))
                      throw KSteamError("Invalid dynamic viscosity", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  else
                      return result;
              } },
            { PropertyType::KinematicViscosity,
              [](double P, double x) {
                  double result;
                  if (x == 1.0)
                      result = IF97::viscvap_p(P) / IF97::rhomass_pQ(P, x);
                  else if (x == 0.0)
                      result = IF97::viscliq_p(P) / IF97::rhomass_pQ(P, x);
                  else
                      throw KSteamError("Invalid kinematic viscosity", "PropertyFunctionsPX", { { "P", P }, { "x", x } });

                  if (!std::isfinite(result))
                      throw KSteamError("Invalid kinematic viscosity", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  return result;
              } },
            { PropertyType::ThermalConductivity,
              [](double P, double x) {
                  double result;
                  if (x == 1.0)
                      result = IF97::tcondvap_p(P);
                  else if (x == 0.0)
                      result = IF97::tcondliq_p(P);
                  else
                      throw KSteamError("Invalid thermal conductivity", "PropertyFunctionsPX", { { "P", P }, { "x", x } });

                  if (!std::isfinite(result))
                      throw KSteamError("Invalid thermal conductivity", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  return result;
              } },
            { PropertyType::PrandtlNumber,
              [](double P, double x) {
                  double result;
                  if (x == 1.0)
                      result = IF97::prandtlvap_p(P);
                  else if (x == 0.0)
                      result = IF97::prandtlliq_p(P);
                  else
                      throw KSteamError("Invalid Prandtl number", "PropertyFunctionsPX", { { "P", P }, { "x", x } });

                  if (!std::isfinite(result))
                      throw KSteamError("Invalid Prandtl number", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                  return result;
              } }
        };

        using PropertyFunction = std::function<double(double, double)>;

        auto getFunctionPT(PropertyType PropID)
        {
            // Find the property function
            auto func =
                std::find_if(PropertyFunctionsPT.begin(),
                             PropertyFunctionsPT.end(),
                             [PropID](const std::pair<PropertyType, PropertyFunction>& element) { return element.first == PropID; });
            if (func == PropertyFunctionsPT.end()) throw KSteamError("Invalid property ID");
            return func->second;
        };

        auto getFunctionPX(PropertyType PropID)
        {
            // Find the property function
            auto func =
                std::find_if(PropertyFunctionsPX.begin(),
                             PropertyFunctionsPX.end(),
                             [PropID](const std::pair<PropertyType, PropertyFunction>& element) { return element.first == PropID; });
            if (func == PropertyFunctionsPX.end()) throw KSteamError("Invalid property ID");
            return func->second;
        };




    public:
        TYPE satP(TYPE temperature) { return IF97::psat97(temperature); }

        TYPE satT(TYPE pressure) { return IF97::Tsat97(pressure); }

        FluidProperties<TYPE> flashPT(TYPE pressure, TYPE temperature)
        {
            // Check for valid input
            if (temperature < 273.16 || temperature > 2273.15)
                throw KSteamError("Temperature out of range", "XLSteamPT", { { "P", pressure }, { "T", temperature } });
            if (pressure < 0.0 || pressure > 100000000.0)
                throw KSteamError("Pressure out of range", "XLSteamPT", { { "P", pressure }, { "T", temperature } });
            if (temperature > 1073.15 && pressure > 50000000.0)
                throw KSteamError("Pressure out of range", "XLSteamPT", { { "P", pressure }, { "T", temperature } });

            PhaseProperties<TYPE> phaseProperties;

            phaseProperties.Pressure                = getFunctionPT(PropertyType::Pressure)(temperature, pressure);
            phaseProperties.Temperature             = getFunctionPT(PropertyType::Temperature)(temperature, pressure);
            phaseProperties.Quality                 = getFunctionPT(PropertyType::VaporQuality)(temperature, pressure);
            phaseProperties.Compressibility         = getFunctionPT(PropertyType::CompressibilityFactor)(temperature, pressure);
            phaseProperties.SaturationPressure      = getFunctionPT(PropertyType::SaturationPressure)(temperature, pressure);
            phaseProperties.SaturationTemperature   = getFunctionPT(PropertyType::SaturationTemperature)(temperature, pressure);
            phaseProperties.Density                 = getFunctionPT(PropertyType::Density)(temperature, pressure);
            phaseProperties.SpecificVolume          = getFunctionPT(PropertyType::Volume)(temperature, pressure);
            phaseProperties.SpecificEnthalpy        = getFunctionPT(PropertyType::Enthalpy)(temperature, pressure);
            phaseProperties.SpecificEntropy         = getFunctionPT(PropertyType::Entropy)(temperature, pressure);
            phaseProperties.SpecificInternalEnergy  = getFunctionPT(PropertyType::InternalEnergy)(temperature, pressure);
            phaseProperties.SpecificGibbsEnergy     = getFunctionPT(PropertyType::GibbsEnergy)(temperature, pressure);
            phaseProperties.SpecificHelmholtzEnergy = getFunctionPT(PropertyType::HelmholtzEnergy)(temperature, pressure);
            phaseProperties.Cp                      = getFunctionPT(PropertyType::Cp)(temperature, pressure);
            phaseProperties.Cv                      = getFunctionPT(PropertyType::Cv)(temperature, pressure);
            phaseProperties.SpeedOfSound            = getFunctionPT(PropertyType::SpeedOfSound)(temperature, pressure);
            phaseProperties.ThermalConductivity     = getFunctionPT(PropertyType::ThermalConductivity)(temperature, pressure);
            phaseProperties.DynamicViscosity        = getFunctionPT(PropertyType::DynamicViscosity)(temperature, pressure);
            phaseProperties.KinematicViscosity      = getFunctionPT(PropertyType::KinematicViscosity)(temperature, pressure);
            phaseProperties.PrandtlNumber           = getFunctionPT(PropertyType::PrandtlNumber)(temperature, pressure);

            return { phaseProperties };
        }

        FluidProperties<TYPE> flashPX(TYPE pressure, TYPE quality)
        {
            // Check for valid input
            if (pressure <= 0.0 || pressure > IF97::get_pcrit())
                throw KSteamError("Pressure out of range", "XLSteamPX", { { "P", pressure }, { "x", quality } });
            if (quality < 0.0 || quality > 1.0)
                throw KSteamError("Quality out of range", "XLSteamPX", { { "P", pressure }, { "x", quality } });

            TYPE temperature = IF97::Tsat97(pressure);

            PhaseProperties<TYPE> vaporProperties;
            PhaseProperties<TYPE> liquidProperties;

            vaporProperties.Pressure                = getFunctionPX(PropertyType::Pressure)(pressure, 1.0);
            vaporProperties.Temperature             = getFunctionPX(PropertyType::Temperature)(pressure, 1.0);
            vaporProperties.Quality                 = quality;
            vaporProperties.Compressibility         = getFunctionPX(PropertyType::CompressibilityFactor)(pressure, 1.0);
            vaporProperties.SaturationPressure      = getFunctionPX(PropertyType::SaturationPressure)(pressure, 1.0);
            vaporProperties.SaturationTemperature   = getFunctionPX(PropertyType::SaturationTemperature)(pressure, 1.0);
            vaporProperties.Density                 = getFunctionPX(PropertyType::Density)(pressure, 1.0);
            vaporProperties.SpecificVolume          = getFunctionPX(PropertyType::Volume)(pressure, 1.0);
            vaporProperties.SpecificEnthalpy        = getFunctionPX(PropertyType::Enthalpy)(pressure, 1.0);
            vaporProperties.SpecificEntropy         = getFunctionPX(PropertyType::Entropy)(pressure, 1.0);
            vaporProperties.SpecificInternalEnergy  = getFunctionPX(PropertyType::InternalEnergy)(pressure, 1.0);
            vaporProperties.SpecificGibbsEnergy     = getFunctionPX(PropertyType::GibbsEnergy)(pressure, 1.0);
            vaporProperties.SpecificHelmholtzEnergy = getFunctionPX(PropertyType::HelmholtzEnergy)(pressure, 1.0);
            vaporProperties.Cp                      = getFunctionPX(PropertyType::Cp)(pressure, 1.0);
            vaporProperties.Cv                      = getFunctionPX(PropertyType::Cv)(pressure, 1.0);
            vaporProperties.SpeedOfSound            = getFunctionPX(PropertyType::SpeedOfSound)(pressure, 1.0);
            vaporProperties.ThermalConductivity     = getFunctionPX(PropertyType::ThermalConductivity)(pressure, 1.0);
            vaporProperties.DynamicViscosity        = getFunctionPX(PropertyType::DynamicViscosity)(pressure, 1.0);
            vaporProperties.KinematicViscosity      = getFunctionPX(PropertyType::KinematicViscosity)(pressure, 1.0);
            vaporProperties.PrandtlNumber           = getFunctionPX(PropertyType::PrandtlNumber)(pressure, 1.0);

            liquidProperties.Pressure                = getFunctionPX(PropertyType::Pressure)(pressure, 0.0);
            liquidProperties.Temperature             = getFunctionPX(PropertyType::Temperature)(pressure, 0.0);
            liquidProperties.Quality                 = 1.0 - quality;
            liquidProperties.Compressibility         = getFunctionPX(PropertyType::CompressibilityFactor)(pressure, 0.0);
            liquidProperties.SaturationPressure      = getFunctionPX(PropertyType::SaturationPressure)(pressure, 0.0);
            liquidProperties.SaturationTemperature   = getFunctionPX(PropertyType::SaturationTemperature)(pressure, 0.0);
            liquidProperties.Density                 = getFunctionPX(PropertyType::Density)(pressure, 0.0);
            liquidProperties.SpecificVolume          = getFunctionPX(PropertyType::Volume)(pressure, 0.0);
            liquidProperties.SpecificEnthalpy        = getFunctionPX(PropertyType::Enthalpy)(pressure, 0.0);
            liquidProperties.SpecificEntropy         = getFunctionPX(PropertyType::Entropy)(pressure, 0.0);
            liquidProperties.SpecificInternalEnergy  = getFunctionPX(PropertyType::InternalEnergy)(pressure, 0.0);
            liquidProperties.SpecificGibbsEnergy     = getFunctionPX(PropertyType::GibbsEnergy)(pressure, 0.0);
            liquidProperties.SpecificHelmholtzEnergy = getFunctionPX(PropertyType::HelmholtzEnergy)(pressure, 0.0);
            liquidProperties.Cp                      = getFunctionPX(PropertyType::Cp)(pressure, 0.0);
            liquidProperties.Cv                      = getFunctionPX(PropertyType::Cv)(pressure, 0.0);
            liquidProperties.SpeedOfSound            = getFunctionPX(PropertyType::SpeedOfSound)(pressure, 0.0);
            liquidProperties.ThermalConductivity     = getFunctionPX(PropertyType::ThermalConductivity)(pressure, 0.0);
            liquidProperties.DynamicViscosity        = getFunctionPX(PropertyType::DynamicViscosity)(pressure, 0.0);
            liquidProperties.KinematicViscosity      = getFunctionPX(PropertyType::KinematicViscosity)(pressure, 0.0);
            liquidProperties.PrandtlNumber           = getFunctionPX(PropertyType::PrandtlNumber)(pressure, 0.0);

            return { liquidProperties, vaporProperties };
        }

        FluidProperties<TYPE> flashTX(TYPE temperature, TYPE quality) {
            return flashPX(IF97::psat97(temperature), quality);
        }
    };

}    // namespace KSteam

#endif    // KSTEAM_KSTEAM_HPP
