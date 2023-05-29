/*
KKKKKKKKK    KKKKKKK   SSSSSSSSSSSSSSS      tttt
K:::::::K    K:::::K SS:::::::::::::::S  ttt:::t
K:::::::K    K:::::KS:::::SSSSSS::::::S  t:::::t
K:::::::K   K::::::KS:::::S     SSSSSSS  t:::::t
KK::::::K  K:::::KKKS:::::S        ttttttt:::::ttttttt        eeeeeeeeeeee    aaaaaaaaaaaaa      mmmmmmm    mmmmmmm
  K:::::K K:::::K   S:::::S        t:::::::::::::::::t      ee::::::::::::ee  a::::::::::::a   mm:::::::m  m:::::::mm
  K::::::K:::::K     S::::SSSS     t:::::::::::::::::t     e::::::eeeee:::::eeaaaaaaaaa:::::a m::::::::::mm::::::::::m
  K:::::::::::K       SS::::::SSSSStttttt:::::::tttttt    e::::::e     e:::::e         a::::a m::::::::::::::::::::::m
  K:::::::::::K         SSS::::::::SS    t:::::t          e:::::::eeeee::::::e  aaaaaaa:::::a m:::::mmm::::::mmm:::::m
  K::::::K:::::K           SSSSSS::::S   t:::::t          e:::::::::::::::::e aa::::::::::::a m::::m   m::::m   m::::m
  K:::::K K:::::K               S:::::S  t:::::t          e::::::eeeeeeeeeee a::::aaaa::::::a m::::m   m::::m   m::::m
KK::::::K  K:::::KKK            S:::::S  t:::::t    tttttte:::::::e         a::::a    a:::::a m::::m   m::::m   m::::m
K:::::::K   K::::::KSSSSSSS     S:::::S  t::::::tttt:::::te::::::::e        a::::a    a:::::a m::::m   m::::m   m::::m
K:::::::K    K:::::KS::::::SSSSSS:::::S  tt::::::::::::::t e::::::::eeeeeeeea:::::aaaa::::::a m::::m   m::::m   m::::m
K:::::::K    K:::::KS:::::::::::::::SS     tt:::::::::::tt  ee:::::::::::::e a::::::::::aa:::am::::m   m::::m   m::::m
KKKKKKKKK    KKKKKKK SSSSSSSSSSSSSSS         ttttttttttt      eeeeeeeeeeeeee  aaaaaaaaaa  aaaammmmmm   mmmmmm   mmmmmm

MIT License

Copyright (c) 2023 Kenneth Troldal Balslev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef KSTEAM_COMMON_HPP
#define KSTEAM_COMMON_HPP

#include "impl/Config.hpp"
#include "impl/Error.hpp"
//#include "impl/IF97/IF97.h"
#include <deps/IF97/IF97.h>

#include <numerixx.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <compare>
#include <functional>
#include <string>
#include <vector>

namespace KSteam
{
    /**
     * @brief Checks if a given std::expected object contains a valid temperature value, and if not, throws an appropriate error.
     *
     * @tparam T The type of the std::expected object.
     * @param temperature A std::expected object containing a temperature value or an error.
     * @return The temperature value if the std::expected object is valid.
     * @throws RootError The error object from the std::expected if it is invalid and does not contain a valid temperature value.
     */
    inline auto checkResult(auto result)
    {
        using namespace nxx::roots;

        if (result.has_value()) return *result;

        if (!result.has_value() && result.error().type() == RootErrorType::MaxIterationsExceeded) return result.error().value();

        throw result.error();    // NOLINT
    }

    inline auto TemperatureLimits(FLOAT pressure)
    {
        if (pressure >= 0.0 && pressure <= 50000000.0) return std::make_pair<FLOAT, FLOAT>(273.16, 2273.15);

        if (pressure > 50000000.0 && pressure <= 100000000.0) return std::make_pair<FLOAT, FLOAT>(273.16, 1073.15);

        throw KSteamError("Pressure out of range", "TemperatureLimits", { { "P", pressure } });
    }

    inline auto PressureLimits(FLOAT temperature)
    {
        if (temperature >= 273.16 && temperature <= 1073.15) return std::make_pair<FLOAT, FLOAT>(611.657, 100000000.0);

        if (temperature > 1073.15 && temperature <= 2273.15) return std::make_pair<FLOAT, FLOAT>(611.657, 50000000.0);

        throw KSteamError("Temperature out of range", "PressureLimits", { { "T", temperature } });
    }

    inline auto InflectionTemperature(FLOAT pressure)
    {
        if (pressure > 10000.0) return std::max(273.16, -2.103006E-7 * pressure + 2.771633E2);
        if (pressure < 813.0) return -1.23606E-05 * pressure * pressure + 3.73348E-02 * pressure + 2.54948E+02;

        return 277.13;
    }

    /**
     * @class Property
     * @brief Encapsulates the concept of a thermodynamic property.
     *
     * This class represents a thermodynamic property and provides several ways
     * to instantiate a property, either directly from its Type or from a string ID.
     */
    class Property
    {
    public:
        /**
         * @enum Type
         * @brief Enumeration of the possible thermodynamic properties.
         */
        enum Type : size_t {
            Pressure = 0,
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

    private:
        /**
         * @var PropertyArray
         * @brief Map from string identifiers to property types.
         */
        constexpr static const std::array<std::pair<std::string_view, Type>, 40> PropertyArray = {
            { { "P", Type::Pressure },
              { "PRESSURE", Type::Pressure },
              { "T", Type::Temperature },
              { "TEMPERATURE", Type::Temperature },
              { "PSAT", Type::SaturationPressure },
              { "TSAT", Type::SaturationTemperature },
              { "RHO", Type::Density },
              { "DENSITY", Type::Density },
              { "V", Type::Volume },
              { "VOL", Type::Volume },
              { "VOLUME", Type::Volume },
              { "H", Type::Enthalpy },
              { "ENTHALPY", Type::Enthalpy },
              { "S", Type::Entropy },
              { "ENTROPY", Type::Entropy },
              { "U", Type::InternalEnergy },
              { "INTERNAL ENERGY", Type::InternalEnergy },
              { "CP", Type::Cp },
              { "CV", Type::Cv },
              { "W", Type::SpeedOfSound },
              { "SPEED OF SOUND", Type::SpeedOfSound },
              { "KAPPA", Type::IsentropicExponent },
              { "ISENTROPIC EXPONENT", Type::IsentropicExponent },
              { "A", Type::HelmholtzEnergy },
              { "F", Type::HelmholtzEnergy },
              { "HELMHOLTZ ENERGY", Type::HelmholtzEnergy },
              { "G", Type::GibbsEnergy },
              { "GIBBS ENERGY", Type::GibbsEnergy },
              { "Z", Type::CompressibilityFactor },
              { "COMPRESSIBILITY FACTOR", Type::CompressibilityFactor },
              { "X", Type::VaporQuality },
              { "QUALITY", Type::VaporQuality },
              { "ETA", Type::DynamicViscosity },
              { "DYNAMIC VISCOSITY", Type::DynamicViscosity },
              { "NU", Type::KinematicViscosity },
              { "KINEMATIC VISCOSITY", Type::KinematicViscosity },
              { "TC", Type::ThermalConductivity },
              { "THERMAL CONDUCTIVITY", Type::ThermalConductivity },
              { "PR", Type::PrandtlNumber },
              { "PRANDTL NUMBER", Type::PrandtlNumber } }
        };

    public:
        /**
         * @brief Construct a Property object from a Type.
         * @param propertyType Type of the property.
         */
        constexpr Property(Type propertyType) : m_propertyType(propertyType) {}    // NOLINT

        /**
         * @brief Construct a Property object from a string-like ID.
         *
         * This constructor is templated to accept any type that can be converted to
         * std::string_view. It converts the string-like ID to upper case, then
         * searches for the ID in PropertyArray. If found, it sets the property type
         * accordingly; otherwise, it throws an exception.
         *
         * @tparam T A string-like type that can be converted to std::string_view.
         * @param propertyID The string-like identifier of the property.
         * @throws XLSteamError If the string-like ID is not recognized.
         */
        template<typename T>
        // clang-format off
            requires requires(T t) {{std::string_view(t)} -> std::same_as<std::string_view>;}
        // clang-format on
        Property(T&& propertyID)    // NOLINT
        {
            std::string propID = propertyID;
            std::transform(propID.begin(), propID.end(), propID.begin(), [](unsigned char c) { return std::toupper(c); });

            auto result = std::find_if(PropertyArray.begin(),
                                       PropertyArray.end(),
                                       [&propID](const std::pair<std::string_view, Type>& element) { return element.first == propID; });

            if (result != PropertyArray.end())
                m_propertyType = result->second;
            else
                throw KSteamError("Invalid property ID");
        }

        /**
         * @brief Assigns a new property type to the Property object.
         *
         * This function assigns a new property type to the Property object and
         * returns a reference to the object for possible chaining of operations.
         *
         * @param other The new property type to assign to the Property object.
         * @return A reference to the Property object after the assignment.
         */
        Property& operator=(const Type other) { m_propertyType = other; return *this; }

        /**
         * @brief Get the Type of the property.
         * @return The Type of the property.
         */
        [[nodiscard]] Type type() const { return m_propertyType; }

        /**
         * @brief Implicit conversion to Type.
         * @return The Type of the property.
         */
        [[nodiscard]] operator Type() const { return type(); }    // NOLINT

        /**
         * @brief Get a string representation of the property.
         * @return A string representation of the property.
         * @throws XLSteamError If the Type of the property is not recognized.
         */
        [[nodiscard]] std::string asString() const
        {
            auto result =
                std::find_if(PropertyArray.begin(), PropertyArray.end(), [this](const std::pair<std::string_view, Type>& element) {
                    return element.second == m_propertyType;
                });

            if (result != PropertyArray.end())
                return std::string(result->first);
            else
                throw KSteamError("Invalid property type");
        }

        /**
         * @brief Compare this Property with another for ordering.
         * @param other The other Property to compare to.
         * @return A standard comparison result (-1 for less than, 0 for equal, 1 for greater than).
         */
        auto operator<=>(const Property&) const = default;

    private:
        Type m_propertyType; /*< Type of the property. */
    };

    // The following functions are used to calculate the properties of steam from pressure and temperature.
    // The functions are implemented as lambda functions in an array of pairs, where the first element is the
    // property type and the second element is the lambda function. The lambda functions take two arguments,
    // pressure and temperature, and return the requested property. The functions are called from the
    // XLSteamPT() function below.
    static const std::array<std::pair<Property, std::function<FLOAT(FLOAT, FLOAT)>>, 21> PropertyFunctionsPT = {
        { { Property::Pressure,
            [](FLOAT T, FLOAT P) {
                if (!std::isfinite(P)) throw KSteamError("Invalid pressure", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                return P;
            } },
          { Property::Temperature,
            [](FLOAT T, FLOAT P) {
                if (!std::isfinite(T)) throw KSteamError("Invalid temperature", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                return T;
            } },
          { Property::SaturationPressure,
            [](FLOAT T, FLOAT P) {
                auto result = IF97::psat97(T);
                if (!std::isfinite(result))
                    throw KSteamError("Invalid saturation pressure", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                return result;
            } },
          { Property::SaturationTemperature,
            [](FLOAT T, FLOAT P) {
                auto result = IF97::Tsat97(P);
                if (!std::isfinite(result))
                    throw KSteamError("Invalid saturation temperature", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                return result;
            } },
          { Property::Density,
            [](FLOAT T, FLOAT P) {
                auto result = IF97::rhomass_Tp(T, P);
                if (!std::isfinite(result)) throw KSteamError("Invalid density", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                return result;
            } },
          { Property::Volume,
            [](FLOAT T, FLOAT P) {
                auto result = 1.0 / IF97::rhomass_Tp(T, P);
                if (!std::isfinite(result)) throw KSteamError("Invalid volume", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                return result;
            } },
          { Property::Enthalpy,
            [](FLOAT T, FLOAT P) {
                auto result = IF97::hmass_Tp(T, P);
                if (!std::isfinite(result)) throw KSteamError("Invalid enthalpy", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                return result;
            } },
          { Property::Entropy,
            [](FLOAT T, FLOAT P) {
                auto result = IF97::smass_Tp(T, P);
                if (!std::isfinite(result)) throw KSteamError("Invalid entropy", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                return result;
            } },
          { Property::InternalEnergy,
            [](FLOAT T, FLOAT P) {
                auto result = IF97::umass_Tp(T, P);
                if (!std::isfinite(result))
                    throw KSteamError("Invalid internal energy", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                return result;
            } },
          { Property::Cp,
            [](FLOAT T, FLOAT P) {
                auto result = IF97::cpmass_Tp(T, P);
                if (!std::isfinite(result))
                    throw KSteamError("Invalid specific heat capacity (Cp)", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                return result;
            } },
          { Property::Cv,
            [](FLOAT T, FLOAT P) {
                auto result = IF97::cvmass_Tp(T, P);
                if (!std::isfinite(result))
                    throw KSteamError("Invalid specific heat capacity (Cv)", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                return IF97::cvmass_Tp(T, P);
            } },
          { Property::SpeedOfSound,
            [](FLOAT T, FLOAT P) {
                auto result = IF97::speed_sound_Tp(T, P);
                if (!std::isfinite(result)) throw KSteamError("Invalid speed of sound", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                return result;
            } },
          { Property::IsentropicExponent,
            [](FLOAT T, FLOAT P) {
                auto result = IF97::cpmass_Tp(T, P) / IF97::cvmass_Tp(T, P);
                if (!std::isfinite(result))
                    throw KSteamError("Invalid isentropic exponent", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                return result;
            } },
          { Property::HelmholtzEnergy,
            [](FLOAT T, FLOAT P) {
                auto result = IF97::umass_Tp(T, P) - T * IF97::smass_Tp(T, P);
                if (!std::isfinite(result))
                    throw KSteamError("Invalid Helmholtz energy", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                return result;
            } },
          { Property::GibbsEnergy,
            [](FLOAT T, FLOAT P) {
                auto result = IF97::hmass_Tp(T, P) - T * IF97::smass_Tp(T, P);
                if (!std::isfinite(result)) throw KSteamError("Invalid Gibbs energy", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                return result;
            } },
          { Property::CompressibilityFactor,
            [](FLOAT T, FLOAT P) {
                auto result = P * IF97::rhomass_Tp(T, P) / (T * 8.31446261815324);
                if (!std::isfinite(result))
                    throw KSteamError("Invalid compressibility factor", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                return result;
            } },
          { Property::VaporQuality,
            [](FLOAT T, FLOAT P) {
                if (T > IF97::get_Tcrit() && P > IF97::get_pcrit()) return -1.0;
                //                    throw XLSteamError("Vapor quality undefined for T > Tcrit and P > Pcrit",
                //                                       "VaporQuality(P, T)",
                //                                       { { "P", P }, { "T", T } });
                if (T <= IF97::get_Tcrit() && P > IF97::psat97(T)) return 0.0;
                if (P <= IF97::get_pcrit() && T > IF97::Tsat97(P))
                    return 1.0;
                else
                    return -1.0;
                //                    throw XLSteamError("Vapor quality undefined for given P and T", "VaporQuality(P, T)", { { "P", P }, {
                //                    "T", T } });
            } },
          { Property::DynamicViscosity,
            [](FLOAT T, FLOAT P) {
                auto result = IF97::visc_Tp(T, P);
                if (!std::isfinite(result))
                    throw KSteamError("Invalid dynamic viscosity", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                return result;
            } },
          { Property::KinematicViscosity,
            [](FLOAT T, FLOAT P) {
                auto result = IF97::visc_Tp(T, P) / IF97::rhomass_Tp(T, P);
                if (!std::isfinite(result))
                    throw KSteamError("Invalid kinematic viscosity", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                return result;
            } },
          { Property::ThermalConductivity,
            [](FLOAT T, FLOAT P) {
                auto result = IF97::tcond_Tp(T, P);
                if (!std::isfinite(result))
                    throw KSteamError("Invalid thermal conductivity", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                return result;
            } },
          { Property::PrandtlNumber,
            [](FLOAT T, FLOAT P) {
                auto result = IF97::prandtl_Tp(T, P);
                if (!std::isfinite(result)) throw KSteamError("Invalid Prandtl number", "PropertyFunctionsPT", { { "T", T }, { "P", P } });
                return result;
            } } }
    };

    // The following functions are used to calculate the properties of steam from pressure and quality.
    // The functions are implemented as lambda functions in an array of pairs, where the first element is the
    // property type and the second element is the lambda function. The lambda functions take two arguments,
    // pressure and quality, and return the requested property. The functions are called from the
    // XLSteamPX() function below.
    static const std::array<std::pair<Property, std::function<FLOAT(FLOAT, FLOAT)>>, 21> PropertyFunctionsPX = {
        { { Property::Pressure,
            [](FLOAT P, FLOAT x) {
                if (!std::isfinite(P)) throw KSteamError("Invalid pressure", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                return P;
            } },
          { Property::Temperature,
            [](FLOAT P, FLOAT x) {
                auto result = IF97::Tsat97(P);
                if (!std::isfinite(result)) throw KSteamError("Invalid temperature", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                return result;
            } },
          { Property::SaturationPressure,
            [](FLOAT P, FLOAT x) {
                if (!std::isfinite(P)) throw KSteamError("Invalid saturation pressure", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                return P;
            } },
          { Property::SaturationTemperature,
            [](FLOAT P, FLOAT x) {
                auto result = IF97::Tsat97(P);
                if (!std::isfinite(result))
                    throw KSteamError("Invalid saturation temperature", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                return result;
            } },
          { Property::Density,
            [](FLOAT P, FLOAT x) {
                auto result = IF97::rhomass_pQ(P, x);
                if (!std::isfinite(result)) throw KSteamError("Invalid density", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                return result;
            } },
          { Property::Volume,
            [](FLOAT P, FLOAT x) {
                auto result = 1.0 / IF97::rhomass_pQ(P, x);
                if (!std::isfinite(result)) throw KSteamError("Invalid volume", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                return result;
            } },
          { Property::Enthalpy,
            [](FLOAT P, FLOAT x) {
                auto result = IF97::hmass_pQ(P, x);
                if (!std::isfinite(result)) throw KSteamError("Invalid enthalpy", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                return result;
            } },
          { Property::Entropy,
            [](FLOAT P, FLOAT x) {
                auto result = IF97::smass_pQ(P, x);
                if (!std::isfinite(result)) throw KSteamError("Invalid entropy", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                return result;
            } },
          { Property::InternalEnergy,
            [](FLOAT P, FLOAT x) {
                auto result = IF97::umass_pQ(P, x);
                if (!std::isfinite(result))
                    throw KSteamError("Invalid internal energy", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                return result;
            } },
          { Property::Cp,
            [](FLOAT P, FLOAT x) {
                auto result = IF97::cpvap_p(P) * x + IF97::cpliq_p(P) * (1 - x);
                if (!std::isfinite(result))
                    throw KSteamError("Invalid specific heat at constant pressure", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                return result;
            } },
          { Property::Cv,
            [](FLOAT P, FLOAT x) {
                auto result = IF97::cvvap_p(P) * x + IF97::cvliq_p(P) * (1 - x);
                if (!std::isfinite(result))
                    throw KSteamError("Invalid specific heat at constant volume", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                return result;
            } },
          { Property::SpeedOfSound,
            [](FLOAT P, FLOAT x) {
                FLOAT result;
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
          { Property::IsentropicExponent,
            [](FLOAT P, FLOAT x) {
                auto result = IF97::cpvap_p(P) * x + IF97::cpliq_p(P) * (1 - x) / IF97::cvvap_p(P) * x + IF97::cvliq_p(P) * (1 - x);
                if (!std::isfinite(result))
                    throw KSteamError("Invalid isentropic exponent", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                return result;
            } },
          { Property::HelmholtzEnergy,
            [](FLOAT P, FLOAT x) {
                auto result = IF97::umass_pQ(P, x) - IF97::Tsat97(P) * IF97::smass_pQ(P, x);
                if (!std::isfinite(result))
                    throw KSteamError("Invalid Helmholtz energy", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                return result;
            } },
          { Property::GibbsEnergy,
            [](FLOAT P, FLOAT x) {
                auto result = IF97::hmass_pQ(P, x) - IF97::Tsat97(P) * IF97::smass_pQ(P, x);
                if (!std::isfinite(result)) throw KSteamError("Invalid Gibbs energy", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                return result;
            } },
          { Property::CompressibilityFactor,
            [](FLOAT P, FLOAT x) {
                auto result = P * (1.0 / IF97::rhomass_pQ(P, x)) * IF97::get_MW() / (IF97::Tsat97(P) * 8.31446261815324);
                if (!std::isfinite(result))
                    throw KSteamError("Invalid compressibility factor", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                return result;
            } },
          { Property::VaporQuality,
            [](FLOAT P, FLOAT x) {
                if (!std::isfinite(x)) throw KSteamError("Invalid vapor quality", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                return x;
            } },
          { Property::DynamicViscosity,
            [](FLOAT P, FLOAT x) {
                FLOAT result;
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
          { Property::KinematicViscosity,
            [](FLOAT P, FLOAT x) {
                FLOAT result;
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
          { Property::ThermalConductivity,
            [](FLOAT P, FLOAT x) {
                FLOAT result;
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
          { Property::PrandtlNumber,
            [](FLOAT P, FLOAT x) {
                FLOAT result;
                if (x == 1.0)
                    result = IF97::prandtlvap_p(P);
                else if (x == 0.0)
                    result = IF97::prandtlliq_p(P);
                else
                    throw KSteamError("Invalid Prandtl number", "PropertyFunctionsPX", { { "P", P }, { "x", x } });

                if (!std::isfinite(result)) throw KSteamError("Invalid Prandtl number", "PropertyFunctionsPX", { { "P", P }, { "x", x } });
                return result;
            } } }
    };

}    // namespace XLSteam

#endif    // KSTEAM_COMMON_HPP
