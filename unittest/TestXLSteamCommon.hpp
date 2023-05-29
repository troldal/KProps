//
// Created by Kenneth Balslev on 05/05/2023.
//

#ifndef XLSTEAM_TESTXLSTEAMCOMMON_HPP
#define XLSTEAM_TESTXLSTEAMCOMMON_HPP

#include <KSteam.hpp>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <random>
#include <tuple>

using namespace Catch;

enum Property { P, T, V, RHO, H, S, U, X };

using Properties = std::tuple<double, double, double, double, double, double, double, double>;

inline void checkProps(const auto& props, const auto& refProps)
{
    CHECK_THAT(std::get<P>(props),
               Catch::Matchers::WithinRel(std::get<P>(refProps), 0.001) || Catch::Matchers::WithinAbs(std::get<P>(refProps), 0.001));

    CHECK_THAT(std::get<T>(props),
               Catch::Matchers::WithinRel(std::get<T>(refProps), 0.001) || Catch::Matchers::WithinAbs(std::get<T>(refProps), 0.001));

    CHECK_THAT(std::get<H>(props),
               Catch::Matchers::WithinRel(std::get<H>(refProps), 0.001) || Catch::Matchers::WithinAbs(std::get<H>(refProps), 0.001));

    CHECK_THAT(std::get<S>(props),
               Catch::Matchers::WithinRel(std::get<S>(refProps), 0.001) || Catch::Matchers::WithinAbs(std::get<S>(refProps), 0.001));

    CHECK_THAT(std::get<U>(props),
               Catch::Matchers::WithinRel(std::get<U>(refProps), 0.001) || Catch::Matchers::WithinAbs(std::get<U>(refProps), 0.001));

    CHECK_THAT(std::get<V>(props),
               Catch::Matchers::WithinRel(std::get<V>(refProps), 0.001) || Catch::Matchers::WithinAbs(std::get<V>(refProps), 0.001));

    CHECK_THAT(std::get<RHO>(props),
               Catch::Matchers::WithinRel(std::get<RHO>(refProps), 0.001) || Catch::Matchers::WithinAbs(std::get<RHO>(refProps), 0.001));

    CHECK_THAT(std::get<X>(props),
               Catch::Matchers::WithinRel(std::get<X>(refProps), 0.001) || Catch::Matchers::WithinAbs(std::get<X>(refProps), 0.001));
}

// The fundamental function for computing properties. This is used as the reference.
inline auto computePropsPT(double pressure, double temperature)
{
    Properties props {};

    std::get<P>(props)   = KSteam::calcPropertyPT(pressure, temperature, "P");
    std::get<T>(props)   = KSteam::calcPropertyPT(pressure, temperature, "T");
    std::get<V>(props)   = KSteam::calcPropertyPT(pressure, temperature, "V");
    std::get<RHO>(props) = KSteam::calcPropertyPT(pressure, temperature, "RHO");
    std::get<H>(props)   = KSteam::calcPropertyPT(pressure, temperature, "H");
    std::get<S>(props)   = KSteam::calcPropertyPT(pressure, temperature, "S");
    std::get<U>(props)   = KSteam::calcPropertyPT(pressure, temperature, "U");
    std::get<X>(props)   = KSteam::calcPropertyPT(pressure, temperature, "X");

    return props;
}

// Functions for computing properties using the pressure as one of the inputs
inline auto computePropsPX(double pressure, double quality)
{
    Properties props {};

    std::get<P>(props)   = KSteam::calcPropertyPX(pressure, quality, "P");
    std::get<T>(props)   = KSteam::calcPropertyPX(pressure, quality, "T");
    std::get<V>(props)   = KSteam::calcPropertyPX(pressure, quality, "V");
    std::get<RHO>(props) = KSteam::calcPropertyPX(pressure, quality, "RHO");
    std::get<H>(props)   = KSteam::calcPropertyPX(pressure, quality, "H");
    std::get<S>(props)   = KSteam::calcPropertyPX(pressure, quality, "S");
    std::get<U>(props)   = KSteam::calcPropertyPX(pressure, quality, "U");
    std::get<X>(props)   = KSteam::calcPropertyPX(pressure, quality, "X");

    return props;
}

inline auto computePropsPH(double pressure, double enthalpy)
{
    Properties props {};

    std::get<P>(props)   = KSteam::calcPropertyPH(pressure, enthalpy, "P");
    std::get<T>(props)   = KSteam::calcPropertyPH(pressure, enthalpy, "T");
    std::get<V>(props)   = KSteam::calcPropertyPH(pressure, enthalpy, "V");
    std::get<RHO>(props) = KSteam::calcPropertyPH(pressure, enthalpy, "RHO");
    std::get<H>(props)   = KSteam::calcPropertyPH(pressure, enthalpy, "H");
    std::get<S>(props)   = KSteam::calcPropertyPH(pressure, enthalpy, "S");
    std::get<U>(props)   = KSteam::calcPropertyPH(pressure, enthalpy, "U");
    std::get<X>(props)   = KSteam::calcPropertyPH(pressure, enthalpy, "X");

    return props;
}

inline auto computePropsPS(double pressure, double entropy)
{
    Properties props {};

    std::get<P>(props)   = KSteam::calcPropertyPS(pressure, entropy, "P");
    std::get<T>(props)   = KSteam::calcPropertyPS(pressure, entropy, "T");
    std::get<V>(props)   = KSteam::calcPropertyPS(pressure, entropy, "V");
    std::get<RHO>(props) = KSteam::calcPropertyPS(pressure, entropy, "RHO");
    std::get<H>(props)   = KSteam::calcPropertyPS(pressure, entropy, "H");
    std::get<S>(props)   = KSteam::calcPropertyPS(pressure, entropy, "S");
    std::get<U>(props)   = KSteam::calcPropertyPS(pressure, entropy, "U");
    std::get<X>(props)   = KSteam::calcPropertyPS(pressure, entropy, "X");

    return props;
}

inline auto computePropsPV(double pressure, double volume, double TGuess)
{
    Properties props {};

    std::get<P>(props)   = KSteam::calcPropertyPV(pressure, volume, "P", TGuess);
    std::get<T>(props)   = KSteam::calcPropertyPV(pressure, volume, "T", TGuess);
    std::get<V>(props)   = KSteam::calcPropertyPV(pressure, volume, "V", TGuess);
    std::get<RHO>(props) = KSteam::calcPropertyPV(pressure, volume, "RHO", TGuess);
    std::get<H>(props)   = KSteam::calcPropertyPV(pressure, volume, "H", TGuess);
    std::get<S>(props)   = KSteam::calcPropertyPV(pressure, volume, "S", TGuess);
    std::get<U>(props)   = KSteam::calcPropertyPV(pressure, volume, "U", TGuess);
    std::get<X>(props)   = KSteam::calcPropertyPV(pressure, volume, "X", TGuess);

    return props;
}

inline auto computePropsPRHO(double pressure, double density, double TGuess)
{
    Properties props {};

    std::get<P>(props)   = KSteam::calcPropertyPRHO(pressure, density, "P", TGuess);
    std::get<T>(props)   = KSteam::calcPropertyPRHO(pressure, density, "T", TGuess);
    std::get<V>(props)   = KSteam::calcPropertyPRHO(pressure, density, "V", TGuess);
    std::get<RHO>(props) = KSteam::calcPropertyPRHO(pressure, density, "RHO", TGuess);
    std::get<H>(props)   = KSteam::calcPropertyPRHO(pressure, density, "H", TGuess);
    std::get<S>(props)   = KSteam::calcPropertyPRHO(pressure, density, "S", TGuess);
    std::get<U>(props)   = KSteam::calcPropertyPRHO(pressure, density, "U", TGuess);
    std::get<X>(props)   = KSteam::calcPropertyPRHO(pressure, density, "X", TGuess);

    return props;
}

inline auto computePropsPU(double pressure, double internalEnergy)
{
    Properties props {};

    std::get<P>(props)   = KSteam::calcPropertyPU(pressure, internalEnergy, "P");
    std::get<T>(props)   = KSteam::calcPropertyPU(pressure, internalEnergy, "T");
    std::get<V>(props)   = KSteam::calcPropertyPU(pressure, internalEnergy, "V");
    std::get<RHO>(props) = KSteam::calcPropertyPU(pressure, internalEnergy, "RHO");
    std::get<H>(props)   = KSteam::calcPropertyPU(pressure, internalEnergy, "H");
    std::get<S>(props)   = KSteam::calcPropertyPU(pressure, internalEnergy, "S");
    std::get<U>(props)   = KSteam::calcPropertyPU(pressure, internalEnergy, "U");
    std::get<X>(props)   = KSteam::calcPropertyPU(pressure, internalEnergy, "X");

    return props;
}

// Functions for computing properties using the temperature as one of the inputs
inline auto computePropsTX(double temperature, double quality)
{
    Properties props {};

    std::get<P>(props)   = KSteam::calcPropertyTX(temperature, quality, "P");
    std::get<T>(props)   = KSteam::calcPropertyTX(temperature, quality, "T");
    std::get<V>(props)   = KSteam::calcPropertyTX(temperature, quality, "V");
    std::get<RHO>(props) = KSteam::calcPropertyTX(temperature, quality, "RHO");
    std::get<H>(props)   = KSteam::calcPropertyTX(temperature, quality, "H");
    std::get<S>(props)   = KSteam::calcPropertyTX(temperature, quality, "S");
    std::get<U>(props)   = KSteam::calcPropertyTX(temperature, quality, "U");
    std::get<X>(props)   = KSteam::calcPropertyTX(temperature, quality, "X");

    return props;
}

inline auto computePropsTV(double temperature, double volume)
{
    Properties props {};

    std::get<P>(props)   = KSteam::calcPropertyTV(temperature, volume, "P");
    std::get<T>(props)   = KSteam::calcPropertyTV(temperature, volume, "T");
    std::get<V>(props)   = KSteam::calcPropertyTV(temperature, volume, "V");
    std::get<RHO>(props) = KSteam::calcPropertyTV(temperature, volume, "RHO");
    std::get<H>(props)   = KSteam::calcPropertyTV(temperature, volume, "H");
    std::get<S>(props)   = KSteam::calcPropertyTV(temperature, volume, "S");
    std::get<U>(props)   = KSteam::calcPropertyTV(temperature, volume, "U");
    std::get<X>(props)   = KSteam::calcPropertyTV(temperature, volume, "X");

    return props;
}

inline auto computePropsTRHO(double temperature, double density)
{
    Properties props {};

    std::get<P>(props)   = KSteam::calcPropertyTRHO(temperature, density, "P");
    std::get<T>(props)   = KSteam::calcPropertyTRHO(temperature, density, "T");
    std::get<V>(props)   = KSteam::calcPropertyTRHO(temperature, density, "V");
    std::get<RHO>(props) = KSteam::calcPropertyTRHO(temperature, density, "RHO");
    std::get<H>(props)   = KSteam::calcPropertyTRHO(temperature, density, "H");
    std::get<S>(props)   = KSteam::calcPropertyTRHO(temperature, density, "S");
    std::get<U>(props)   = KSteam::calcPropertyTRHO(temperature, density, "U");
    std::get<X>(props)   = KSteam::calcPropertyTRHO(temperature, density, "X");

    return props;
}

inline auto computePropsTH(double temperature, double enthalpy, double PGuess)
{
    Properties props {};

    std::get<P>(props)   = KSteam::calcPropertyTH(temperature, enthalpy, "P", PGuess);
    std::get<T>(props)   = KSteam::calcPropertyTH(temperature, enthalpy, "T", PGuess);
    std::get<V>(props)   = KSteam::calcPropertyTH(temperature, enthalpy, "V", PGuess);
    std::get<RHO>(props) = KSteam::calcPropertyTH(temperature, enthalpy, "RHO", PGuess);
    std::get<H>(props)   = KSteam::calcPropertyTH(temperature, enthalpy, "H", PGuess);
    std::get<S>(props)   = KSteam::calcPropertyTH(temperature, enthalpy, "S", PGuess);
    std::get<U>(props)   = KSteam::calcPropertyTH(temperature, enthalpy, "U", PGuess);
    std::get<X>(props)   = KSteam::calcPropertyTH(temperature, enthalpy, "X", PGuess);

    return props;
}

inline auto computePropsTS(double temperature, double entropy, double PGuess)
{
    Properties props {};

    std::get<P>(props)   = KSteam::calcPropertyTS(temperature, entropy, "P", PGuess);
    std::get<T>(props)   = KSteam::calcPropertyTS(temperature, entropy, "T", PGuess);
    std::get<V>(props)   = KSteam::calcPropertyTS(temperature, entropy, "V", PGuess);
    std::get<RHO>(props) = KSteam::calcPropertyTS(temperature, entropy, "RHO", PGuess);
    std::get<H>(props)   = KSteam::calcPropertyTS(temperature, entropy, "H", PGuess);
    std::get<S>(props)   = KSteam::calcPropertyTS(temperature, entropy, "S", PGuess);
    std::get<U>(props)   = KSteam::calcPropertyTS(temperature, entropy, "U", PGuess);
    std::get<X>(props)   = KSteam::calcPropertyTS(temperature, entropy, "X", PGuess);

    return props;
}

inline auto computePropsTU(double temperature, double intEnergy, double PGuess)
{
    Properties props {};

    std::get<P>(props)   = KSteam::calcPropertyTU(temperature, intEnergy, "P", PGuess);
    std::get<T>(props)   = KSteam::calcPropertyTU(temperature, intEnergy, "T", PGuess);
    std::get<V>(props)   = KSteam::calcPropertyTU(temperature, intEnergy, "V", PGuess);
    std::get<RHO>(props) = KSteam::calcPropertyTU(temperature, intEnergy, "RHO", PGuess);
    std::get<H>(props)   = KSteam::calcPropertyTU(temperature, intEnergy, "H", PGuess);
    std::get<S>(props)   = KSteam::calcPropertyTU(temperature, intEnergy, "S", PGuess);
    std::get<U>(props)   = KSteam::calcPropertyTU(temperature, intEnergy, "U", PGuess);
    std::get<X>(props)   = KSteam::calcPropertyTU(temperature, intEnergy, "X", PGuess);

    return props;
}

// Check calculations using pressure in the saturation region
inline void checkCalcSatPH(double pressure, double quality)
{
    INFO("Pressure: " << pressure << ", Quality: " << quality);

    auto refProps = computePropsPX(pressure, quality);
    auto props    = computePropsPH(pressure, std::get<H>(refProps));

    checkProps(props, refProps);
}

inline void checkCalcSatPS(double pressure, double quality)
{
    INFO("Pressure: " << pressure << ", Quality: " << quality);

    auto refProps = computePropsPX(pressure, quality);
    auto props    = computePropsPS(pressure, std::get<S>(refProps));

    checkProps(props, refProps);
}

inline void checkCalcSatPV(double pressure, double quality)
{
    INFO("Pressure: " << pressure << ", Quality: " << quality);

    auto refProps = computePropsPX(pressure, quality);
    auto props    = computePropsPV(pressure, std::get<V>(refProps), std::get<T>(refProps));

    checkProps(props, refProps);
}

inline void checkCalcSatPRHO(double pressure, double quality)
{
    INFO("Pressure: " << pressure << ", Quality: " << quality);

    auto refProps = computePropsPX(pressure, quality);
    auto props    = computePropsPRHO(pressure, std::get<RHO>(refProps), std::get<T>(refProps));

    checkProps(props, refProps);
}

inline void checkCalcSatPU(double pressure, double quality)
{
    INFO("Pressure: " << pressure << ", Quality: " << quality);

    auto refProps = computePropsPX(pressure, quality);
    auto props    = computePropsPU(pressure, std::get<U>(refProps));

    checkProps(props, refProps);
}

// Check calculations using temperature in the saturation region
inline void checkCalcSatTH(double temperature, double quality)
{
    INFO("Temperature: " << temperature << ", Quality: " << quality);

    auto refProps = computePropsTX(temperature, quality);
    auto props    = computePropsTH(temperature, std::get<H>(refProps), std::get<P>(refProps));

    checkProps(props, refProps);
}

inline void checkCalcSatTS(double temperature, double quality)
{
    INFO("Temperature: " << temperature << ", Quality: " << quality);

    auto refProps = computePropsTX(temperature, quality);
    auto props    = computePropsTS(temperature, std::get<S>(refProps), std::get<P>(refProps));

    checkProps(props, refProps);
}

inline void checkCalcSatTV(double temperature, double quality)
{
    INFO("Temperature: " << temperature << ", Quality: " << quality);

    auto refProps = computePropsTX(temperature, quality);
    auto props    = computePropsTV(temperature, std::get<V>(refProps));

    checkProps(props, refProps);
}

inline void checkCalcSatTRHO(double temperature, double quality)
{
    INFO("Temperature: " << temperature << ", Quality: " << quality);

    auto refProps = computePropsTX(temperature, quality);
    auto props    = computePropsTRHO(temperature, std::get<RHO>(refProps));

    checkProps(props, refProps);
}

inline void checkCalcSatTU(double temperature, double quality)
{
    INFO("Temperature: " << temperature << ", Quality: " << quality);

    auto refProps = computePropsTX(temperature, quality);
    auto props    = computePropsTU(temperature, std::get<U>(refProps), std::get<P>(refProps));

    checkProps(props, refProps);
}

// Check calculations using pressure outside the saturation region
inline void checkCalcTV(double pressure, double temperature)
{
    INFO("Pressure: " << pressure << ", Temperature: " << temperature);

    auto refProps = computePropsPT(pressure, temperature);
    auto props    = computePropsTV(temperature, std::get<V>(refProps));

    checkProps(props, refProps);
}

inline void checkCalcTRHO(double pressure, double temperature)
{
    INFO("Pressure: " << pressure << ", Temperature: " << temperature);

    auto refProps = computePropsPT(pressure, temperature);
    auto props    = computePropsTRHO(temperature, std::get<RHO>(refProps));

    checkProps(props, refProps);
}

inline void checkCalcTH(double pressure, double temperature)
{
    INFO("Pressure: " << pressure << ", Temperature: " << temperature);

    auto refProps = computePropsPT(pressure, temperature);
    auto props    = computePropsTH(temperature, std::get<H>(refProps), pressure);

    checkProps(props, refProps);
}

inline void checkCalcTS(double pressure, double temperature)
{
    INFO("Pressure: " << pressure << ", Temperature: " << temperature);

    auto refProps = computePropsPT(pressure, temperature);
    auto props    = computePropsTS(temperature, std::get<S>(refProps), pressure);

    checkProps(props, refProps);
}

inline void checkCalcTU(double pressure, double temperature)
{
    INFO("Pressure: " << pressure << ", Temperature: " << temperature);

    auto refProps = computePropsPT(pressure, temperature);
    auto props    = computePropsTU(temperature, std::get<U>(refProps), pressure);

    checkProps(props, refProps);
}

// Check calculations using pressure outside the saturation region
inline void checkCalcPH(double pressure, double temperature)
{
    INFO("Pressure: " << pressure << ", Temperature: " << temperature);

    auto refProps = computePropsPT(pressure, temperature);
    auto props    = computePropsPH(pressure, std::get<H>(refProps));

    checkProps(props, refProps);
}

inline void checkCalcPS(double pressure, double temperature)
{
    INFO("Pressure: " << pressure << ", Temperature: " << temperature);

    auto refProps = computePropsPT(pressure, temperature);
    auto props    = computePropsPS(pressure, std::get<S>(refProps));

    checkProps(props, refProps);
}

inline void checkCalcPV(double pressure, double temperature)
{
    INFO("Pressure: " << pressure << ", Temperature: " << temperature);

    auto refProps = computePropsPT(pressure, temperature);
    auto props    = computePropsPV(pressure, std::get<V>(refProps), temperature);

    checkProps(props, refProps);
}

inline void checkCalcPRHO(double pressure, double temperature)
{
    INFO("Pressure: " << pressure << ", Temperature: " << temperature);

    auto refProps = computePropsPT(pressure, temperature);
    auto props    = computePropsPRHO(pressure, std::get<RHO>(refProps), temperature);

    checkProps(props, refProps);
}

inline void checkCalcPU(double pressure, double temperature)
{
    INFO("Pressure: " << pressure << ", Temperature: " << temperature);

    auto refProps = computePropsPT(pressure, temperature);
    auto props    = computePropsPU(pressure, std::get<U>(refProps));

    checkProps(props, refProps);
}

// inline double newTemperature(double temperature, std::pair<double, double> range)
//{
//     if (temperature < range.first + 100.0)
//         temperature += 1.0;
//     else if (temperature >= range.first + 100.0 && temperature < range.first + 400.0)
//         temperature += 5.0;
//     temperature += 10.0;
//
//     return temperature;
// }
//
// inline double newPressure(double pressure)
//{
//     if (pressure < 10000.0)
//         pressure += 1000.0;
//     else if (pressure >= 10000.0 && pressure < 1000000.0)
//         pressure += 10000.0;
//     else
//         pressure += 100000.0;
//
//     return pressure;
// }

#endif    // XLSTEAM_TESTXLSTEAMCOMMON_HPP
