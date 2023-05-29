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

#ifndef KSTEAM_FLASHPSPEC_HPP
#define KSTEAM_FLASHPSPEC_HPP

#include "Common.hpp"
#include "Config.hpp"
#include "Error.hpp"

#include <cmath>
#include <optional>

namespace KSteam
{

    /**
     * @brief Calculates the specified thermodynamic property of water/steam at given pressure and temperature using the IAPWS-IF97 model.
     * @param pressure The pressure in Pa.
     * @param temperature The temperature in K.
     * @param property The thermodynamic property to be calculated (as PropertyType enumeration).
     * @return The calculated property value.
     * @throws XLSteamError If input values are out of range.
     */
    inline FLOAT calcPropertyPT(FLOAT pressure, FLOAT temperature, Property property)
    {
        // Check for valid input
        if (temperature < 273.16 || temperature > 2273.15)
            throw KSteamError("Temperature out of range", "calcPropertyPT", { { "P", pressure }, { "T", temperature } });
        if (pressure < 0.0 || pressure > 100000000.0)
            throw KSteamError("Pressure out of range", "calcPropertyPT", { { "P", pressure }, { "T", temperature } });
        if (temperature > 1073.15 && pressure > 50000000.0)
            throw KSteamError("Pressure out of range", "calcPropertyPT", { { "P", pressure }, { "T", temperature } });

        // Call the property function
        return PropertyFunctionsPT[property].second(temperature, pressure);
    }

    /**
     * @brief Calculates the specified thermodynamic property of water/steam at given pressure and quality using the IAPWS-IF97 model.
     * @param pressure The pressure in Pa.
     * @param quality The steam quality (mass fraction of vapor phase).
     * @param property The thermodynamic property to be calculated (as PropertyType enumeration).
     * @return The calculated property value.
     * @throws XLSteamError If input values are out of range.
     */
    inline FLOAT calcPropertyPX(FLOAT pressure, FLOAT quality, Property property)
    {
        // Check for valid input
        if (pressure <= 0.0 || pressure > IF97::get_pcrit())
            throw KSteamError("Pressure out of range", "calcPropertyPX", { { "P", pressure }, { "x", quality } });
        if (quality < 0.0 || quality > 1.0)
            throw KSteamError("Quality out of range", "calcPropertyPX", { { "P", pressure }, { "x", quality } });

        // Return the property
        return PropertyFunctionsPX[property].second(pressure, quality);
    }

    namespace impl
    {

        /**
         * @brief Checks if the given pressure is within the valid range for the IAPWS-IF97 model.
         * @param pressure The pressure in Pa.
         * @return True if the pressure is within the valid range, false otherwise.
         */
        inline bool pressureIsInRange(FLOAT pressure) { return pressure >= 0.0 && pressure <= 100E6; }

        /**
         * @brief Finds the bounds for a temperature given a property function, pressure, and other specified property using the
         *        IAPWS-IF97 model.
         * @tparam OtherType The PropertyType enumeration value for the other specified property.
         * @tparam FN The type of the function to be used for the calculations.
         * @param func The function to be used for the calculations.
         * @param pressure The pressure in Pa.
         * @param otherSpec The value of the other specified property.
         * @param limits A pair containing the lower and upper limits of the temperature search range.
         * @param guess An optional initial guess for the temperature (default: nullopt).
         * @return A pair of double values representing the lower and upper bounds for the temperature.
         */
        template<Property::Type OtherType, typename FN>
        inline auto findTemperatureBounds(
            FN func, FLOAT pressure, FLOAT otherSpec, std::pair<FLOAT, FLOAT> limits, std::optional<FLOAT> guess = std::nullopt)
        {
            using namespace nxx::roots;

            // Check if the guess is within the limits
            if (guess.has_value() && *guess >= limits.first && *guess <= limits.second) {
                using namespace nxx::roots;
                return *search(BracketExpandOut(func, limits), std::make_pair(*guess - 1.0, *guess + 1.0));
            }

            // Otherwise, make an initial guess, and search for the root brackets
            else {
                auto propLower = calcPropertyPT(pressure, limits.first, OtherType);
                auto propUpper = calcPropertyPT(pressure, limits.second, OtherType);
                auto tempEst   = limits.first + (limits.second - limits.first) * (otherSpec - propLower) / (propUpper - propLower);
                return *search(nxx::roots::BracketExpandOut(func, limits), std::make_pair(tempEst - 1.0, tempEst + 1.0));
            }
        }

        /**
         * @brief Calculates the specified thermodynamic property of water/steam at given pressure and another known property
         *        in the supercritical region using the IAPWS-IF97 model.
         * @tparam OtherType The type of the other known property (as PropertyType enumeration).
         * @param pressure The pressure in Pa.
         * @param otherSpec The value of the other known property.
         * @param property The thermodynamic property to be calculated (as PropertyType enumeration).
         * @param guess Optional initial temperature guess for the solver (in K).
         * @return The calculated property value.
         * @throws XLSteamError If input values are out of range.
         */
        template<Property::Type OtherType>
        inline FLOAT calcPSpecSupercritical(FLOAT pressure, FLOAT otherSpec, Property property, std::optional<FLOAT> guess = std::nullopt)
        {
            using namespace nxx::roots;

            // Define the function to solve.
            auto func = [&](FLOAT t) { return calcPropertyPT(pressure, t, OtherType) - otherSpec; };

            // Determine the limits for the temperature for the given pressure
            auto limits = TemperatureLimits(pressure);

            // Find the bounds for the temperature
            auto bounds = findTemperatureBounds<OtherType>(func, pressure, otherSpec, limits, guess);

            // Solve the function
            auto temperature = fsolve(Bisection(func), bounds, EPS);
            return calcPropertyPT(pressure, checkResult(temperature), property);
        }

        /**
         * @brief Calculates the specified thermodynamic property of water/steam at given pressure and another known property
         *        in the saturation region using the IAPWS-IF97 model.
         * @tparam OtherType The type of the other known property (as PropertyType enumeration).
         * @param pressure The pressure in Pa.
         * @param otherSpec The value of the other known property.
         * @param property The thermodynamic property to be calculated (as PropertyType enumeration).
         * @return The calculated property value.
         * @throws XLSteamError If input values are out of range.
         */
        template<Property::Type OtherType>
        inline FLOAT calcPSpecSaturation(FLOAT pressure, FLOAT otherSpec, Property property)
        {
            using namespace nxx::roots;

            // Define the function to solve.
            auto func = [&](FLOAT x) { return calcPropertyPX(pressure, x, OtherType) - otherSpec; };

            // Solve the function
            auto quality = fsolve(Bisection(func), { 0.0, 1.0 }, EPS);
            return calcPropertyPX(pressure, checkResult(quality), property);
        }

        /**
         * @brief Calculates the specified thermodynamic property of water/steam at given pressure and another known property
         *        in the liquid region using the IAPWS-IF97 model.
         * @tparam OtherType The type of the other known property (as PropertyType enumeration).
         * @param pressure The pressure in Pa.
         * @param otherSpec The value of the other known property.
         * @param property The thermodynamic property to be calculated (as PropertyType enumeration).
         * @param guess Optional initial temperature guess for the solver (in K).
         * @return The calculated property value.
         * @throws XLSteamError If input values are out of range.
         */
        template<Property::Type OtherType>
        inline FLOAT calcPSpecLiquid(FLOAT pressure, FLOAT otherSpec, Property property, std::optional<FLOAT> guess = std::nullopt)
        {
            using namespace nxx::roots;

            // Define the function to solve.
            auto func = [&](FLOAT t) { return calcPropertyPT(pressure, t, OtherType) - otherSpec; };

            // Determine the limits for the temperature for the given pressure.
            // The upper limit is the saturation temperature at the given pressure, minus EPS to ensure
            // that the solver does not fail due to the saturation curve being discontinuous.
            auto limits = std::make_pair(TemperatureLimits(pressure).first, IF97::Tsat97(pressure) - EPS);

            // Define the bounds for the temperature
            auto bounds = findTemperatureBounds<OtherType>(func, pressure, otherSpec, limits, guess);

            // Solve the function
            auto temperature = fsolve(Bisection(func), bounds, EPS);
            return calcPropertyPT(pressure, checkResult(temperature), property);
        }

        /**
         * @brief Calculates the specified thermodynamic property of water/steam at given pressure and another known property
         *        in the vapor region using the IAPWS-IF97 model.
         * @tparam OtherType The type of the other known property (as PropertyType enumeration).
         * @param pressure The pressure in Pa.
         * @param otherSpec The value of the other known property.
         * @param property The thermodynamic property to be calculated (as PropertyType enumeration).
         * @param guess Optional initial temperature guess for the solver (in K).
         * @return The calculated property value.
         * @throws XLSteamError If input values are out of range.
         */
        template<Property::Type OtherType>
        inline FLOAT calcPSpecVapor(FLOAT pressure, FLOAT otherSpec, Property property, std::optional<FLOAT> guess = std::nullopt)
        {
            using namespace nxx::roots;

            // Define the function to solve.
            auto func = [&](FLOAT t) { return calcPropertyPT(pressure, t, OtherType) - otherSpec; };

            // Determine the limits for the temperature for the given pressure.
            // The lower limit is the saturation temperature at the given pressure, plus EPS to ensure
            // that the solver does not fail due to the saturation curve being discontinuous.
            auto limits = std::make_pair(IF97::Tsat97(pressure) + EPS, TemperatureLimits(pressure).second);

            // Define the bounds for the temperature
            auto bounds = findTemperatureBounds<OtherType>(func, pressure, otherSpec, limits, guess);

            // Solve the function
            auto temperature = fsolve(Bisection(func), bounds, EPS);
            return calcPropertyPT(pressure, checkResult(temperature), property);
        }

        /**
         * @brief Calculates the specified thermodynamic property of water/steam at given pressure and another known property
         *        using the IAPWS-IF97 model.
         * @tparam OtherType The type of the other known property (as PropertyType enumeration).
         * @param pressure The pressure in Pa.
         * @param otherSpec The value of the other known property.
         * @param property The thermodynamic property to be calculated (as PropertyType enumeration).
         * @param guess Optional initial temperature guess for the solver (in K).
         * @return The calculated property value.
         * @throws XLSteamError If input values are out of range or an error occurs during the calculation.
         */
        template<Property::Type OtherType>
        inline FLOAT calcPSpec(FLOAT pressure, FLOAT otherSpec, Property property, std::optional<FLOAT> guess = std::nullopt)
        {
            // Look up the string representation of the other property
            auto specString = Property(OtherType).asString();
                //std::find_if(PropertyList.begin(), PropertyList.end(), [&](const auto& s) { return s.second == OtherType; })->first;

            // Check if pressure is within range
            if (!pressureIsInRange(pressure))
                throw KSteamError("Pressure out of range", "calcPropertyPH", { { "P", pressure }, { specString, otherSpec } });

            // Check if pressure is supercritical (dense phase) and use the appropriate solver
            if (pressure > IF97::get_pcrit()) return calcPSpecSupercritical<OtherType>(pressure, otherSpec, property, guess);

            // Determine the enthalpy of the saturated liquid and saturated vapor
            auto propLiq = calcPropertyPX(pressure, 0.0, OtherType);
            auto propVap = calcPropertyPX(pressure, 1.0, OtherType);

            // Check if enthalpy is within the saturation curve and use the appropriate solver
            if (otherSpec >= propLiq && otherSpec <= propVap) {
                return calcPSpecSaturation<OtherType>(pressure, otherSpec, property);
            }

            // Check if enthalpy is in the liquid region and use the appropriate solver
            if (otherSpec < propLiq) return calcPSpecLiquid<OtherType>(pressure, otherSpec, property, guess);

            // Check if enthalpy is in the vapor region and use the appropriate solver
            if (otherSpec > propVap) return calcPSpecVapor<OtherType>(pressure, otherSpec, property, guess);

            // If we get here, something went wrong
            throw KSteamError("PH flash calculation error", "calcPropertyPH", { { "P", pressure }, { specString, otherSpec } });
        }
    }    // namespace impl

    /**
     * @brief Calculates the specified thermodynamic property of water/steam at given pressure and enthalpy
     *        using the IAPWS-IF97 model.
     * @param pressure The pressure in Pa.
     * @param enthalpy The enthalpy in J/kg.
     * @param property The thermodynamic property to be calculated (as PropertyType enumeration).
     * @return The calculated property value.
     * @throws XLSteamError If input values are out of range or an error occurs during the calculation.
     */
    inline FLOAT calcPropertyPH(FLOAT pressure, FLOAT enthalpy, Property property)
    {
        // Use the backward equation for the temperature guess
        auto TGuess = IF97::T_phmass(pressure, enthalpy);

        // Call the implementation
        return impl::calcPSpec<Property::Enthalpy>(pressure, enthalpy, property, TGuess);
    }

    /**
     * @brief Calculates the specified thermodynamic property of water/steam at given pressure and entropy
     *        using the IAPWS-IF97 model.
     * @param pressure The pressure in Pa.
     * @param entropy The entropy in J/(kg·K).
     * @param property The thermodynamic property to be calculated (as PropertyType enumeration).
     * @return The calculated property value.
     * @throws XLSteamError If input values are out of range or an error occurs during the calculation.
     */
    inline FLOAT calcPropertyPS(FLOAT pressure, FLOAT entropy, Property property)
    {
        // Use the backward equation for the temperature guess
        auto TGuess = IF97::T_psmass(pressure, entropy);

        // Call the implementation
        return impl::calcPSpec<Property::Entropy>(pressure, entropy, property, TGuess);
    }

    /**
     * @brief Calculates the specified thermodynamic property of water/steam at given pressure and internal energy
     *        using the IAPWS-IF97 model.
     * @param pressure The pressure in Pa.
     * @param internalEnergy The internal energy in J/kg.
     * @param property The thermodynamic property to be calculated (as PropertyType enumeration).
     * @return The calculated property value.
     * @throws XLSteamError If input values are out of range or an error occurs during the calculation.
     */
    inline FLOAT calcPropertyPU(FLOAT pressure, FLOAT internalEnergy, Property property)
    {
        // As there is no backward equation for the temperature guess, we let the solver determine the initial guess
        return impl::calcPSpec<Property::InternalEnergy>(pressure, internalEnergy, property);
    }

    // =================================================================================================================
    // Get property from specification of pressure and volume
    // =================================================================================================================

    namespace impl
    {
        /**
         * @brief Calculates the specified thermodynamic property of water/steam at given pressure and density using the
         *        IAPWS-IF97 model.
         *
         *        The pressure/density specification cannot use the generic solver, as the density is not a monotonic
         *        function of temperature, with the maximum density being reached at the inflection temperature (4 deg. C at
         *        1 bar). Therefore, a specialized solver is used, that takes an initial guess to determine on which
         *        side of the inflection temperature the solution lies.
         *
         * @param pressure The pressure in Pa.
         * @param density The density in kg/m³.
         * @param property The thermodynamic property to be calculated (as PropertyType enumeration).
         * @param guess An initial guess for the temperature (optional).
         * @return The calculated property value.
         * @throws XLSteamError If input values are out of range or an error occurs during the calculation.
         */
        inline FLOAT computeFlashPRHO(FLOAT pressure, FLOAT density, Property property, std::optional<FLOAT> guess = 273.16)
        {
            using namespace nxx::roots;

            // Determine the temperature limits and inflection temperature (where the density is maximum)
            auto limits         = TemperatureLimits(pressure);
            auto inflectionTemp = InflectionTemperature(pressure);

            // Determine the density limits
            auto rhoZero = calcPropertyPT(pressure, limits.first, Property::Density);
            auto rhoMin  = calcPropertyPT(pressure, limits.second, Property::Density);
            auto rhoMax  = calcPropertyPT(pressure, inflectionTemp, Property::Density);

            // Due to potential rounding errors, we will allow a small deviation from the limits (the square root of EPS)
            if ((density - rhoMax > 0.0) && (density - rhoMax) < std::sqrt(EPS)) density = rhoMax;
            if ((rhoMin - density > 0.0) && (rhoMin - density) < std::sqrt(EPS)) density = rhoMin;

            // Check if density is within range
            if (density < rhoMin || density > rhoMax)
                throw KSteamError("Density out of range", "XLSteamPD", { { "P", pressure }, { "RHO", density } });

            // Check if pressure is within range
            if (!impl::pressureIsInRange(pressure))
                throw KSteamError("Pressure out of range", "XLSteamPD", { { "P", pressure }, { "RHO", density } });

            // Check if density is in the vicinity of the inflection point
            if (inflectionTemp > limits.first && density >= (rhoZero - std::sqrt(EPS)) && density <= (rhoMax) && *guess <= inflectionTemp) {
                // Due to potential rounding errors, we will allow a small deviation from the density at the minimum temperature
                if (std::abs(rhoZero - density) <= EPS) density = rhoZero;

                // Define the function to be solved
                auto func = [&](FLOAT t) { return calcPropertyPT(pressure, t, Property::Density) - density; };

                // Solve the function
                auto temperature = fsolve(Bisection(func), { limits.first, inflectionTemp }, EPS);
                return calcPropertyPT(pressure, checkResult(temperature), property);
            }

            // Check if pressure is supercritical, and if so, use the supercritical solver
            if (pressure > IF97::get_pcrit()) return impl::calcPSpecSupercritical<Property::Density>(pressure, density, property);

            // Determine the volume of the saturated liquid and saturated vapor
            auto rhoSatLiq = calcPropertyPX(pressure, 0.0, Property::Density);
            auto rhoSatVap = calcPropertyPX(pressure, 1.0, Property::Density);

            // Check if we are in the liquid region, and if so, use the liquid solver
            if (density > rhoSatLiq) {
                // Define the function to be solved
                auto func = [&](FLOAT t) { return calcPropertyPT(pressure, t, Property::Density) - density; };

                // Solve the function.
                // The upper limit is set to the saturation temperature minus EPS, to ensure that the solver does not
                // return a temperature that is in the vapor region.
                auto temperature = fsolve(Bisection(func), { inflectionTemp, IF97::Tsat97(pressure) - EPS }, EPS);
                return calcPropertyPT(pressure, checkResult(temperature), property);
            }

            // Check if volume is within the saturation curve, and if so, use the saturation solver
            if (density <= rhoSatLiq && density >= rhoSatVap) {
                return impl::calcPSpecSaturation<Property::Density>(pressure, density, property);
            }

            // Check if we are in the vapor region and if so, use the vapor solver
            if (density < rhoSatVap) return impl::calcPSpecVapor<Property::Density>(pressure, density, property);

            // If we get here, something went wrong
            throw KSteamError("PV flash calculation error", "XLSteamPD", { { "P", pressure }, { "RHO", density } });
        }

        /**
         * @brief Calculates the specified thermodynamic property of water/steam at given pressure and volume using the
         *        IAPWS-IF97 model.
         *
         *        The pressure/volume specification cannot use the generic solver, as the volume is not a monotonic
         *        function of temperature, with the minimum volume being reached at the inflection temperature (4 deg. C at
         *        1 bar). Therefore, a specialized solver is used, that takes an initial guess to determine on which
         *        side of the inflection temperature the solution lies.
         *
         * @param pressure The pressure in Pa.
         * @param volume The volume in m³/kg.
         * @param property The thermodynamic property to be calculated (as PropertyType enumeration).
         * @param guess An initial guess for the temperature (optional).
         * @return The calculated property value.
         * @throws XLSteamError If input values are out of range or an error occurs during the calculation.
         */
        inline FLOAT computeFlashPV(FLOAT pressure, FLOAT volume, Property property, std::optional<FLOAT> guess = 273.16)
        {
            using namespace nxx::roots;

            // Determine the temperature limits and inflection temperature (where the density is maximum)
            auto limits         = TemperatureLimits(pressure);
            auto inflectionTemp = InflectionTemperature(pressure);

            // Determine the volume limits
            auto volZero = calcPropertyPT(pressure, limits.first, Property::Volume);
            auto volMin  = calcPropertyPT(pressure, inflectionTemp, Property::Volume);
            auto volMax  = calcPropertyPT(pressure, limits.second, Property::Volume);

            // Due to potential rounding errors, we will allow a small deviation from the limits (the square root of EPS)
            if ((volMin - volume > 0.0) && (volMin - volume) < std::sqrt(EPS)) volume = volMin;
            if ((volume - volMax > 0.0) && (volume - volMax) < std::sqrt(EPS)) volume = volMax;

            // Check if density is within range
            if (volume < volMin || volume > volMax)
                throw KSteamError("Density out of range", "calcPropertyPV", { { "P", pressure }, { "V", volume } });

            // Check if pressure is within range
            if (!impl::pressureIsInRange(pressure))
                throw KSteamError("Pressure out of range", "calcPropertyPV", { { "P", pressure }, { "V", volume } });

            // Check if density is in the vicinity of the inflection point
            if (inflectionTemp > limits.first && volume <= (volZero + std::sqrt(EPS)) && volume >= volMax && *guess <= inflectionTemp) {
                // Due to potential rounding errors, we will allow a small deviation from the volume at the minimum temperature
                if (std::abs(volume - volZero) <= EPS) volume = volZero;

                // Define the function to be solved
                auto func = [&](FLOAT t) { return calcPropertyPT(pressure, t, Property::Volume) - volume; };

                // Solve the function.
                auto temperature = fsolve(Bisection(func), { limits.first, inflectionTemp }, EPS);
                return calcPropertyPT(pressure, checkResult(temperature), property);
            }

            // Check if pressure is supercritical and if so, use the supercritical solver
            if (pressure > IF97::get_pcrit()) return impl::calcPSpecSupercritical<Property::Volume>(pressure, volume, property);

            // Determine the volume of the saturated liquid and saturated vapor
            auto volSatLiq = calcPropertyPX(pressure, 0.0, Property::Volume);
            auto volSatVap = calcPropertyPX(pressure, 1.0, Property::Volume);

            // Check if we are in the liquid region and if so, use the liquid solver
            if (volume < volSatLiq) {
                // Define the function to be solved
                auto func = [&](FLOAT t) { return calcPropertyPT(pressure, t, Property::Volume) - volume; };

                // Solve the function. The upper limit is set to the saturation temperature minus EPS, to ensure that the
                // solver does not return a temperature that is in the vapor region.
                auto temperature = fsolve(Bisection(func), { inflectionTemp, IF97::Tsat97(pressure) - EPS }, EPS);
                return calcPropertyPT(pressure, checkResult(temperature), property);
            }

            // Check if volume is within the saturation curve and if so, use the saturation solver
            if (volume >= volSatLiq && volume <= volSatVap) {
                return impl::calcPSpecSaturation<Property::Volume>(pressure, volume, property);
            }

            // Check if we are in the vapor region and if so, use the vapor solver
            if (volume > volSatVap) return impl::calcPSpecVapor<Property::Volume>(pressure, volume, property);

            // If we get here, something went wrong
            throw KSteamError("PV flash calculation error", "calcPropertyPV", { { "P", pressure }, { "V", volume } });
        }
    }    // namespace impl

    /**
     * @brief Calculates the specified thermodynamic property of water/steam at given pressure and density using the
     *        IAPWS-IF97 model.
     * @param pressure The pressure in Pa.
     * @param density The density in kg/m³.
     * @param property The thermodynamic property to be calculated (as PropertyType enumeration).
     * @param guess An initial guess for the temperature (default: 273.16 K).
     * @return The calculated property value.
     */
    inline FLOAT calcPropertyPRHO(FLOAT pressure, FLOAT density, Property property, std::optional<FLOAT> guess = std::nullopt)
    {
        if (density > 1.0)
            return impl::computeFlashPRHO(pressure, density, property, guess);
        else
            return impl::computeFlashPV(pressure, 1.0 / density, property, guess);
    }

    /**
     * @brief Calculates the specified thermodynamic property of water/steam at given pressure and volume using the
     *        IAPWS-IF97 model.
     * @param pressure The pressure in Pa.
     * @param volume The volume in m³/kg.
     * @param property The thermodynamic property to be calculated (as PropertyType enumeration).
     * @param guess An initial guess for the temperature (default: 273.16 K).
     * @return The calculated property value.
     */
    inline FLOAT calcPropertyPV(FLOAT pressure, FLOAT volume, Property property, std::optional<FLOAT> guess = std::nullopt)
    {
        if (volume > 1.0)
            return impl::computeFlashPV(pressure, volume, property, guess);
        else
            return impl::computeFlashPRHO(pressure, 1.0 / volume, property, guess);
    }
}    // namespace XLSteam

#endif    // KSTEAM_FLASHPSPEC_HPP
