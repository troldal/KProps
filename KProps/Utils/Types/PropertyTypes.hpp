/*
    888    d8P  8888888b.
    888   d8P   888   Y88b
    888  d8P    888    888
    888d88K     888   d88P 888d888 .d88b.  88888b.  .d8888b
    8888888b    8888888P"  888P"  d88""88b 888 "88b 88K
    888  Y88b   888        888    888  888 888  888 "Y8888b.
    888   Y88b  888        888    Y88..88P 888 d88P      X88
    888    Y88b 888        888     "Y88P"  88888P"   88888P'
                                           888
                                           888
                                           888

    MIT License

    Copyright (c) 2024 Kenneth Troldal Balslev

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

/**
 * @file PropertyTypes.hpp
 * @brief Defines named types for various physical and thermodynamic properties of fluids.
 *
 * This file provides a set of named types for representing physical and thermodynamic properties of fluids.
 * The named types are defined using the Fluent Named Type library, which enhances type safety and code
 * expressiveness by associating a specific FLOAT type with each property. The named types are used to
 * encapsulate the underlying FLOAT values, providing a semantic distinction between different properties
 * and enabling arithmetic operations and implicit conversions to the base FLOAT type.
 */

#pragma once

// ===== External Includes =====

// ===== Standard Includes =====
#include <algorithm>
#include <array>
#include <optional>
#include <ranges>
#include <variant>
#include "../Quantities/Phase.hpp"
#include "../Quantities/Temperature.hpp"
#include "../Quantities/MolecularWeight.hpp"
#include "../Quantities/CriticalTemperature.hpp"
#include "../Quantities/Pressure.hpp"
#include "../Quantities/Enthalpy.hpp"
#include "../Quantities/Entropy.hpp"
#include "../Quantities/InternalEnergy.hpp"
#include "../Quantities/HelmholtzEnergy.hpp"
#include "../Quantities/GibbsEnergy.hpp"
#include "../Quantities/Density.hpp"
#include "../Quantities/Volume.hpp"
#include "../Quantities/IsobaricHeatCapacity.hpp"
#include "../Quantities/IsochoricHeatCapacity.hpp"
#include "../Quantities/IsothermalCompressibility.hpp"
#include "../Quantities/ThermalExpansionCoefficient.hpp"
#include "../Quantities/SpeedOfSound.hpp"
#include "../Quantities/CompressibilityFactor.hpp"
#include "../Quantities/VaporQuality.hpp"
#include "../Quantities/DynamicViscosity.hpp"
#include "../Quantities/KinematicViscosity.hpp"
#include "../Quantities/ThermalConductivity.hpp"
#include "../Quantities/PrandtlNumber.hpp"
#include "../Quantities/Undefined.hpp"
#include "../Quantities/Unknown.hpp"


namespace KProps
{


    /**
     * @concept IsProperty
     * @brief Ensures that a type is a valid property type.
     *
     * The IsProperty concept is a compile-time constraint that checks if the given PROPERTY type is one of the valid
     * property types defined using the Fluent Named Type idiom. This includes properties such as temperature (T), pressure (P),
     * enthalpy (H), and others, each represented by a strong type alias to prevent mixing of incompatible types in calculations
     * and operations. The concept facilitates the creation of generic functions, templates, and classes that are constrained to
     * work with valid property types, thereby preventing misuse and enhancing type safety.
     *
     * @tparam PROPERTY The type to check against the list of valid property types.
     */
    template<typename PROPERTY>
    concept IsProperty =
        std::same_as<PROPERTY, T> || std::same_as<PROPERTY, P> || std::same_as<PROPERTY, H> || std::same_as<PROPERTY, S> ||
        std::same_as<PROPERTY, U> || std::same_as<PROPERTY, A> || std::same_as<PROPERTY, G> || std::same_as<PROPERTY, Rho> ||
        std::same_as<PROPERTY, V> || std::same_as<PROPERTY, Cp> || std::same_as<PROPERTY, Cv> || std::same_as<PROPERTY, Kappa> ||
        std::same_as<PROPERTY, W> || std::same_as<PROPERTY, Z> || std::same_as<PROPERTY, X> || std::same_as<PROPERTY, Eta> ||
        std::same_as<PROPERTY, Nu> || std::same_as<PROPERTY, TC> || std::same_as<PROPERTY, PR> || std::same_as<PROPERTY, MW> ||
        std::same_as<PROPERTY, Alpha> || std::same_as<PROPERTY, Phase> || std::same_as<PROPERTY, Undefined> ||
        std::same_as<PROPERTY, Unknown> || std::same_as<PROPERTY, Phase::BASE>;

    /**
     * @concept IsSpecificationPT
     * @brief Ensures that a pair of types represent a valid Pressure-Temperature specification.
     *
     * The IsSpecificationPT concept checks whether the given pair of types (S1 and S2) corresponds to
     * a Pressure (P) and Temperature (T) pair, in any order. This specification is common in fluid dynamics
     * and thermodynamics for defining states or processes where both pressure and temperature are known or
     * targeted parameters.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecificationPT = (std::same_as<S1, P> && std::same_as<S2, T>) || (std::same_as<S1, T> && std::same_as<S2, P>);

    /**
     * @concept IsSpecificationPH
     * @brief Ensures that a pair of types represent a valid Pressure-Enthalpy specification.
     *
     * The IsSpecificationPH concept checks whether the given pair of types (S1 and S2) matches a Pressure (P)
     * and Enthalpy (H) pair, in any order. This specification is particularly useful in processes such as boiling,
     * condensation, or other phase change processes where pressure and enthalpy define the system's state.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecificationPH = (std::same_as<S1, P> && std::same_as<S2, H>) || (std::same_as<S1, H> && std::same_as<S2, P>);

    /**
     * @concept IsSpecificationPS
     * @brief Ensures that a pair of types represent a valid Pressure-Entropy specification.
     *
     * The IsSpecificationPS concept verifies if the given pair of types (S1 and S2) forms a Pressure (P)
     * and Entropy (S) pair, in any order. This specification is essential for describing states or processes
     * in thermodynamic cycles where entropy changes play a significant role, alongside pressure.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecificationPS = (std::same_as<S1, P> && std::same_as<S2, S>) || (std::same_as<S1, S> && std::same_as<S2, P>);

    /**
     * @concept IsSpecificationPU
     * @brief Ensures that a pair of types represent a valid Pressure-Internal Energy specification.
     *
     * The IsSpecificationPU concept checks if the given pair of types (S1 and S2) aligns with a Pressure (P)
     * and Internal Energy (U) pair, in any order. Such a specification is vital for detailed energy analysis
     * in thermodynamic systems where internal energy, alongside pressure, defines the state or transformation
     * of the system.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecificationPU = (std::same_as<S1, P> && std::same_as<S2, U>) || (std::same_as<S1, U> && std::same_as<S2, P>);

    /**
     * @concept IsSpecificationPD
     * @brief Ensures that a pair of types represent a valid Pressure-Density specification.
     *
     * The IsSpecificationPD concept verifies whether the given pair of types (S1 and S2) matches a Pressure (P)
     * and Density (Density) pair, in any order. This specification is crucial for studies involving fluid statics,
     * dynamics, and where the relationship between pressure and density is fundamental to the analysis.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecificationPD = (std::same_as<S1, P> && std::same_as<S2, Density>) || (std::same_as<S1, Density> && std::same_as<S2, P>);

    /**
     * @concept IsSpecificationPV
     * @brief Ensures that a pair of types represent a valid Pressure-Volume specification.
     *
     * The IsSpecificationPV concept checks if the given pair of types (S1 and S2) forms a Pressure (P)
     * and Volume (V) pair, in any order. This specification is essential for describing states or processes
     * in thermodynamic cycles, particularly in the context of Boyle's law and other volume-related phenomena.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecificationPV = (std::same_as<S1, P> && std::same_as<S2, V>) || (std::same_as<S1, V> && std::same_as<S2, P>);

    /**
     * @concept IsSpecificationPX
     * @brief Ensures that a pair of types represent a valid Pressure-Vapor Quality specification.
     *
     * The IsSpecificationPX concept verifies whether the given pair of types (S1 and S2) aligns with a Pressure (P)
     * and Vapor Quality (X) pair, in any order. Such a specification is vital for detailed analysis in phase change processes,
     * boiling, and condensation studies where pressure and vapor quality define the system's state.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecificationPX = (std::same_as<S1, P> && std::same_as<S2, X>) || (std::same_as<S1, X> && std::same_as<S2, P>);

    /**
     * @concept IsSpecificationTH
     * @brief Ensures that a pair of types represent a valid Temperature-Enthalpy specification.
     *
     * The IsSpecificationTH concept checks if the given pair of types (S1 and S2) corresponds to
     * a Temperature (T) and Enthalpy (H) pair, in any order. This specification is commonly used in
     * processes such as heating, cooling, or other thermal transformations where both temperature and
     * enthalpy are known or targeted parameters.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecificationTH = (std::same_as<S1, T> && std::same_as<S2, H>) || (std::same_as<S1, H> && std::same_as<S2, T>);

    /**
     * @concept IsSpecificationTS
     * @brief Ensures that a pair of types represent a valid Temperature-Entropy specification.
     *
     * The IsSpecificationTS concept checks if the given pair of types (S1 and S2) forms a Temperature (T)
     * and Entropy (S) pair, in any order. This specification is crucial for describing thermodynamic states
     * or processes where both temperature and entropy are known or targeted parameters, especially in
     * analyses involving entropy changes and thermal efficiency.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecificationTS = (std::same_as<S1, T> && std::same_as<S2, S>) || (std::same_as<S1, S> && std::same_as<S2, T>);

    /**
     * @concept IsSpecificationTU
     * @brief Ensures that a pair of types represent a valid Temperature-Internal Energy specification.
     *
     * The IsSpecificationTU concept verifies whether the given pair of types (S1 and S2) aligns with a Temperature (T)
     * and Internal Energy (U) pair, in any order. This specification is vital for energy analysis and thermodynamic
     * studies where temperature and internal energy define the system's state or transformation, particularly in
     * heat transfer and energy conversion processes.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecificationTU = (std::same_as<S1, T> && std::same_as<S2, U>) || (std::same_as<S1, U> && std::same_as<S2, T>);

    /**
     * @concept IsSpecificationTD
     * @brief Ensures that a pair of types represent a valid Temperature-Density specification.
     *
     * The IsSpecificationTD concept checks if the given pair of types (S1 and S2) corresponds to a Temperature (T)
     * and Density (Density) pair, in any order. Such a specification is essential in fluid dynamics and material science
     * for studying the thermal expansion of substances and the effects of temperature on material density.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecificationTD = (std::same_as<S1, T> && std::same_as<S2, Density>) || (std::same_as<S1, Density> && std::same_as<S2, T>);

    /**
     * @concept IsSpecificationTV
     * @brief Ensures that a pair of types represent a valid Temperature-Volume specification.
     *
     * The IsSpecificationTV concept verifies whether the given pair of types (S1 and S2) matches a Temperature (T)
     * and Volume (V) pair, in any order. This specification is particularly useful for examining the effects of
     * temperature on the volume of gases and liquids, following principles such as Charles's law in gas dynamics
     * and thermal expansion in liquids and solids.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecificationTV = (std::same_as<S1, T> && std::same_as<S2, V>) || (std::same_as<S1, V> && std::same_as<S2, T>);

    /**
     * @concept IsSpecificationTX
     * @brief Ensures that a pair of types represent a valid Temperature-Vapor Quality specification.
     *
     * The IsSpecificationTX concept checks whether the given pair of types (S1 and S2) corresponds to a Temperature (T)
     * and Vapor Quality (X) pair, in any order. This specification is crucial in phase change studies and boiling or condensation
     * processes where temperature and vapor quality together define the state of the system.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecificationTX = (std::same_as<S1, T> && std::same_as<S2, X>) || (std::same_as<S1, X> && std::same_as<S2, T>);

    /**
     * @concept IsSpecificationHS
     * @brief Ensures that a pair of types represent a valid Enthalpy-Entropy specification.
     *
     * The IsSpecificationHS concept verifies if the given pair of types (S1 and S2) forms an Enthalpy (H) and Entropy (S) pair,
     * in any order. This specification is essential for thermodynamic cycle analysis and understanding energy transformations
     * and efficiency, particularly in heat engines and refrigeration cycles.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecificationHS = (std::same_as<S1, H> && std::same_as<S2, S>) || (std::same_as<S1, S> && std::same_as<S2, H>);

    /**
     * @concept IsSpecificationUV
     * @brief Ensures that a pair of types represent a valid Internal Energy-Volume specification.
     *
     * The IsSpecificationUV concept checks if the given pair of types (S1 and S2) aligns with an Internal Energy (U) and Volume (V)
     * pair, in any order. Such a specification is vital for detailed energy analysis in systems where volume changes accompany
     * energy transformations, affecting the internal energy.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecificationUV = (std::same_as<S1, U> && std::same_as<S2, V>) || (std::same_as<S1, V> && std::same_as<S2, U>);

    /**
     * @concept IsSpecificationHV
     * @brief Ensures that a pair of types represent a valid Enthalpy-Volume specification.
     *
     * The IsSpecificationHV concept verifies whether the given pair of types (S1 and S2) matches an Enthalpy (H) and Volume (V) pair,
     * in any order. This specification is particularly useful in processes involving heat addition or removal in systems experiencing
     * volume changes, such as in expansion or compression work scenarios.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecificationHV = (std::same_as<S1, H> && std::same_as<S2, V>) || (std::same_as<S1, V> && std::same_as<S2, H>);

    /**
     * @concept IsSpecificationDS
     * @brief Ensures that a pair of types represent a valid Density-Entropy specification.
     *
     * The IsSpecificationDS concept checks if the given pair of types (S1 and S2) forms a Density (Density) and
     * Entropy (S) pair, in any order. This specification is critical in analyses where density and entropy variations
     * play a significant role, such as in compressible flow and thermodynamic efficiency calculations.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecificationDS = (std::same_as<S1, S> && std::same_as<S2, Density>) || (std::same_as<S1, Density> && std::same_as<S2, S>);

    /**
     * @concept IsSpecificationDH
     * @brief Ensures that a pair of types represent a valid Density-Enthalpy specification.
     *
     * The IsSpecificationDH concept verifies whether the given pair of types (S1 and S2) matches a Density (Density)
     * and Enthalpy (H) pair, in any order. Such a specification is vital in heat transfer and phase change studies
     * where both density and enthalpy are key factors determining material and fluid behavior.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecificationDH = (std::same_as<S1, H> && std::same_as<S2, Density>) || (std::same_as<S1, Density> && std::same_as<S2, H>);

    /**
     * @concept IsSpecificationDU
     * @brief Ensures that a pair of types represent a valid Density-Internal Energy specification.
     *
     * The IsSpecificationDU concept checks if the given pair of types (S1 and S2) aligns with a Density (Density)
     * and Internal Energy (U) pair, in any order. This specification is essential for detailed energy analyses
     * in systems where changes in density and internal energy are closely related, such as in compressible flows
     * and energy conversion processes.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecificationDU = (std::same_as<S1, U> && std::same_as<S2, Density>) || (std::same_as<S1, Density> && std::same_as<S2, U>);

    /**
     * @concept IsSpecificationSU
     * @brief Ensures that a pair of types represent a valid Entropy-Internal Energy specification.
     *
     * The IsSpecificationSU concept verifies whether the given pair of types (S1 and S2) forms an Entropy (S)
     * and Internal Energy (U) pair, in any order. This specification is crucial for thermodynamic studies focusing
     * on the relationship between entropy and internal energy, especially in analyses of thermal efficiency and
     * energy dissipation.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecificationSU = (std::same_as<S1, U> && std::same_as<S2, S>) || (std::same_as<S1, S> && std::same_as<S2, U>);

    /**
     * @concept IsSpecification
     * @brief Ensures that a pair of types represent any valid specification.
     *
     * The IsSpecification concept checks if the given pair of types (S1 and S2) forms any of the valid specification pairs defined
     * by individual concepts. This includes combinations of pressure, temperature, enthalpy, entropy, internal energy, density, volume,
     * vapor quality, and other properties. This broad validation is essential for implementing generic thermodynamic and fluid dynamic
     * models and analyses that require flexibility in specifying state or process parameters.
     *
     * @tparam S1 The first type in the pair to check.
     * @tparam S2 The second type in the pair to check.
     */
    template<typename S1, typename S2>
    concept IsSpecification =
        IsSpecificationPT<S1, S2> || IsSpecificationPH<S1, S2> || IsSpecificationPS<S1, S2> || IsSpecificationPU<S1, S2> ||
        IsSpecificationPD<S1, S2> || IsSpecificationPV<S1, S2> || IsSpecificationPX<S1, S2> || IsSpecificationTH<S1, S2> ||
        IsSpecificationTS<S1, S2> || IsSpecificationTU<S1, S2> || IsSpecificationTD<S1, S2> || IsSpecificationTV<S1, S2> ||
        IsSpecificationTX<S1, S2> || IsSpecificationHS<S1, S2> || IsSpecificationUV<S1, S2> || IsSpecificationHV<S1, S2>;

}    // namespace KProps
