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
#include <NamedType/named_type.hpp>

// ===== Standard Includes =====
#include <algorithm>
#include <array>
#include <variant>

namespace KProps
{
    /**
     * @typedef MW
     * @brief Defines a named type for Molar Weight, providing strong typing and additional functionality.
     *
     * The MW type encapsulates a FLOAT (typically a floating-point type like float or double) and associates
     * it with the concept of molar weight. It inherits behaviors from the Fluent Named Type library, including
     * arithmetic operations and implicit conversion to the underlying FLOAT type, while maintaining the
     * semantic distinction from other floating-point quantities.
     */
    using MW              = fluent::NamedType<FLOAT,
                                              struct MolarWeightTag,
                                              fluent::Printable,
                                              fluent::Addable,
                                              fluent::Subtractable,
                                              fluent::Multiplicable,
                                              fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using MolecularWeight = MW;
    using MolarMass       = MW;

    /**
     * @typedef T
     * @brief Defines a named type for Temperature, providing strong typing and additional functionality.
     *
     * The T type encapsulates a FLOAT (typically a floating-point type such as float or double) and labels
     * it as representing a temperature. It inherits several behaviors from the Fluent Named Type library,
     * including arithmetic operations and implicit conversion to FLOAT, while preserving its distinct identity
     * as a temperature value.
     */
    using T           = fluent::NamedType<FLOAT,
                                          struct TemperatureTag,
                                          fluent::Printable,
                                          fluent::Addable,
                                          fluent::Subtractable,
                                          fluent::Multiplicable,
                                          fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Temperature = T;

    /**
     * @typedef P
     * @brief Defines a named type for Pressure, enhancing type safety and code clarity.
     *
     * The P type strongly encapsulates a FLOAT (commonly a floating-point type such as float or double),
     * designating it as representing pressure. It inherits from the Fluent Named Type library, enabling
     * arithmetic operations like addition, subtraction, and multiplication, along with implicit conversion
     * to the underlying FLOAT type. These capabilities make the P type both robust and flexible for use
     * in fluid dynamics and thermodynamics calculations, where pressure is a fundamental quantity.
     */
    using P        = fluent::NamedType<FLOAT,
                                       struct PressureTag,
                                       fluent::Printable,
                                       fluent::Addable,
                                       fluent::Subtractable,
                                       fluent::Multiplicable,
                                       fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Pressure = P;

    /**
     * @typedef H
     * @brief Defines a named type for Enthalpy, incorporating additional functionality for thermodynamic calculations.
     *
     * The `H` type encapsulates a FLOAT (usually a floating-point type such as float or double), explicitly
     * representing enthalpy. It inherits from the Fluent Named Type library, which provides useful operations
     * like addition, subtraction, multiplication, and implicit conversion to the base FLOAT type. These
     * capabilities make the `H` type well-suited for use in a wide range of thermodynamic calculations, where
     * enthalpy is a key quantity.
     */
    using H        = fluent::NamedType<FLOAT,
                                       struct EnthalpyTag,
                                       fluent::Printable,
                                       fluent::Addable,
                                       fluent::Subtractable,
                                       fluent::Multiplicable,
                                       fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Enthalpy = H;

    /**
     * @typedef S
     * @brief Defines a named type for Entropy, enhancing type safety and expressiveness in thermodynamic calculations.
     *
     * The S type encapsulates a FLOAT (commonly a floating-point type such as float or double), designating
     * it as representing entropy. It inherits several behaviors from the Fluent Named Type library, including
     * arithmetic operations like addition, subtraction, and multiplication, along with implicit conversion
     * to FLOAT. These capabilities make the S type both robust and flexible for use in fluid dynamics and
     * thermodynamics, where entropy is a fundamental concept.
     */
    using S       = fluent::NamedType<FLOAT,
                                      struct EntropyTag,
                                      fluent::Printable,
                                      fluent::Addable,
                                      fluent::Subtractable,
                                      fluent::Multiplicable,
                                      fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Entropy = S;

    /**
     * @typedef U
     * @brief Defines a named type for Internal Energy, enhancing type safety and code expressiveness.
     *
     * The U type encapsulates a FLOAT (typically a floating-point type such as float or double), and labels
     * it as representing internal energy. It inherits from the Fluent Named Type library, which adds useful
     * operations like addition, subtraction, multiplication, and implicit conversion to FLOAT. These capabilities
     * make the U type robust and adaptable for use across a wide range of thermodynamic calculations and fluid dynamics
     * scenarios where internal energy is a key concept.
     */
    using U              = fluent::NamedType<FLOAT,
                                             struct InternalEnergyTag,
                                             fluent::Printable,
                                             fluent::Addable,
                                             fluent::Subtractable,
                                             fluent::Multiplicable,
                                             fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using InternalEnergy = U;

    /**
     * @typedef A
     * @brief Defines a named type for Helmholtz Energy, enhancing type safety and expressiveness in thermodynamic calculations.
     *
     * The A type encapsulates a FLOAT (commonly a floating-point type such as float or double), and is specifically tagged
     * to represent Helmholtz energy. It inherits from the Fluent Named Type library, gaining useful operations like addition,
     * subtraction, multiplication, and implicit conversion to FLOAT. These features make the A type robust and adaptable
     * for a broad spectrum of thermodynamic calculations where Helmholtz energy is a crucial concept, particularly in the
     * analysis of systems in equilibrium at constant temperature and volume.
     */
    using A               = fluent::NamedType<FLOAT,
                                              struct HelmholtzEnergyTag,
                                              fluent::Printable,
                                              fluent::Addable,
                                              fluent::Subtractable,
                                              fluent::Multiplicable,
                                              fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using HelmholtzEnergy = A;

    /**
     * @typedef G
     * @brief Defines a named type for Gibbs Energy, enriching type safety and expressiveness in thermodynamic and chemical calculations.
     *
     * The G type strongly encapsulates a FLOAT (typically a floating-point type such as float or double), designating it
     * as representing Gibbs energy. It benefits from the Fluent Named Type library traits, enabling operations like addition,
     * subtraction, multiplication, and implicit conversion to FLOAT. These features make the G type both robust and flexible
     * for use across various scenarios in thermodynamics and chemical thermodynamics, where Gibbs energy plays a pivotal role
     * in determining the spontaneity of reactions and the equilibrium of phases.
     */
    using G           = fluent::NamedType<FLOAT,
                                          struct GibbsEnergyTag,
                                          fluent::Printable,
                                          fluent::Addable,
                                          fluent::Subtractable,
                                          fluent::Multiplicable,
                                          fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using GibbsEnergy = G;

    /**
     * @typedef Rho
     * @brief Defines a named type for Density, enhancing type safety and expressiveness in calculations involving mass and volume.
     *
     * The Rho type wraps a FLOAT (typically a floating-point type like float or double), explicitly marking it as representing
     * density. It inherits useful operations from the Fluent Named Type library, such as addition, subtraction, multiplication,
     * and implicit conversion to FLOAT. These capabilities make the Rho type robust and versatile for use in various scientific
     * and engineering contexts where density is a key property.
     */
    using Rho     = fluent::NamedType<FLOAT,
                                      struct DensityTag,
                                      fluent::Printable,
                                      fluent::Addable,
                                      fluent::Subtractable,
                                      fluent::Multiplicable,
                                      fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Density = Rho;

    /**
     * @typedef V
     * @brief Defines a named type for Volume, increasing type safety and expressiveness in volume calculations.
     *
     * The V type encapsulates a FLOAT (commonly a floating-point type such as float or double), specifically
     * labeling it as representing volume. It benefits from the Fluent Named Type library traits, enabling
     * arithmetic operations such as addition, subtraction, multiplication, and implicit conversion to FLOAT.
     * These features make the V type both robust and flexible for use in a wide array of applications where
     * volume is a critical property.
     */
    using V      = fluent::NamedType<FLOAT,
                                     struct VolumeTag,
                                     fluent::Printable,
                                     fluent::Addable,
                                     fluent::Subtractable,
                                     fluent::Multiplicable,
                                     fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Volume = V;
    using Vol    = V;

    /**
     * @typedef Cp
     * @brief Defines a named type for Specific Heat Capacity at Constant Pressure, increasing type safety and expressiveness.
     *
     * The Cp type wraps a FLOAT (typically a floating-point type such as float or double), explicitly marking it as representing
     * specific heat capacity at constant pressure. It inherits useful operations from the Fluent Named Type library, such as
     * addition, subtraction, multiplication, and implicit conversion to FLOAT. These features make the Cp type robust and
     * adaptable for use in various scientific and engineering contexts where specific heat capacity is a key property.
     */
    using Cp = fluent::NamedType<FLOAT,
                                 struct CpTag,
                                 fluent::Printable,
                                 fluent::Addable,
                                 fluent::Subtractable,
                                 fluent::Multiplicable,
                                 fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;

    /**
     * @typedef Cv
     * @brief Defines a named type for Specific Heat Capacity at Constant Volume, enhancing type safety and code expressiveness.
     *
     * The Cv type wraps a FLOAT (usually a floating-point type such as float or double), and marks it as representing specific
     * heat capacity at constant volume. It inherits various operations from the Fluent Named Type library, including addition,
     * subtraction, multiplication, and implicit conversion to FLOAT. These functionalities make the Cv type both robust and
     * versatile for use in a wide range of scientific and engineering applications where specific heat capacity is a crucial property.
     */
    using Cv = fluent::NamedType<FLOAT,
                                 struct CvTag,
                                 fluent::Printable,
                                 fluent::Addable,
                                 fluent::Subtractable,
                                 fluent::Multiplicable,
                                 fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;

    /**
     * @typedef Kappa
     * @brief Defines a named type for Isothermal Compressibility, increasing type safety and expressiveness in material and fluid
     * calculations.
     *
     * The Kappa type wraps a FLOAT (typically a floating-point type such as float or double), explicitly marking it as representing
     * isothermal compressibility. It benefits from the Fluent Named Type library traits, enabling arithmetic operations like addition,
     * subtraction, multiplication, and implicit conversion to FLOAT. These features make the Kappa type both robust and versatile for use
     * in various scientific and engineering contexts where isothermal compressibility is a key property in understanding material and fluid
     * behavior under pressure changes.
     */
    using Kappa                     = fluent::NamedType<FLOAT,
                                                        struct KappaTag,
                                                        fluent::Printable,
                                                        fluent::Addable,
                                                        fluent::Subtractable,
                                                        fluent::Multiplicable,
                                                        fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using IsothermalCompressibility = Kappa;

    /**
     * @typedef Alpha
     * @brief Defines a named type for Thermal Expansion, increasing type safety and expressiveness in thermal analysis.
     *
     * The Alpha type wraps a FLOAT (commonly a floating-point type such as float or double), and marks it as representing
     * the coefficient of thermal expansion. It inherits useful operations from the Fluent Named Type library, including
     * addition, subtraction, multiplication, and implicit conversion to FLOAT. These features make Alpha both robust and
     * adaptable for use in a wide range of applications where understanding material behavior in response to temperature
     * changes is critical.
     */
    using Alpha            = fluent::NamedType<FLOAT,
                                               struct AlphaTag,
                                               fluent::Printable,
                                               fluent::Addable,
                                               fluent::Subtractable,
                                               fluent::Multiplicable,
                                               fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using ThermalExpansion = Alpha;

    /**
     * @typedef W
     * @brief Defines a named type for Speed of Sound, increasing type safety and expressiveness in acoustics and fluid dynamics.
     *
     * The W type wraps a FLOAT (typically a floating-point type such as float or double), clearly indicating it as representing
     * the speed of sound. It benefits from the Fluent Named Type library traits, enabling arithmetic operations such as addition,
     * subtraction, multiplication, and implicit conversion to FLOAT. These features make the W type both robust and adaptable for
     * use in a wide range of applications where the speed of sound is a critical parameter, including acoustics, aerodynamics,
     * and material science.
     */
    using W            = fluent::NamedType<FLOAT,
                                           struct SpeedOfSoundTag,
                                           fluent::Printable,
                                           fluent::Addable,
                                           fluent::Subtractable,
                                           fluent::Multiplicable,
                                           fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using SpeedOfSound = W;

    /**
     * @typedef Z
     * @brief Defines a named type for Compressibility Factor, enhancing type safety and expressiveness in gas behavior calculations.
     *
     * The Z type wraps a FLOAT (typically a floating-point type such as float or double), and marks it as representing the
     * compressibility factor. It inherits from the Fluent Named Type library traits, enabling arithmetic operations like addition,
     * subtraction, multiplication, and implicit conversion to FLOAT. These features make the Z type both robust and adaptable for
     * use in a broad range of applications where the compressibility factor is a critical parameter for describing the deviation
     * of real gas behavior from ideal gas law predictions.
     */
    using Z                     = fluent::NamedType<FLOAT,
                                                    struct CompressibilityFactorTag,
                                                    fluent::Printable,
                                                    fluent::Addable,
                                                    fluent::Subtractable,
                                                    fluent::Multiplicable,
                                                    fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using CompressibilityFactor = Z;

    /**
     * @typedef X
     * @brief Defines a named type for Vapor Quality, increasing type safety and expressiveness in two-phase flow and heat transfer.
     *
     * The X type wraps a FLOAT (typically a floating-point type such as float or double), and marks it as representing vapor quality,
     * the ratio of the mass of vapor to the total mass of the mixture. It inherits from the Fluent Named Type library traits, enabling
     * arithmetic operations such as addition, subtraction, multiplication, and implicit conversion to FLOAT. These features make the X
     * type both robust and adaptable for use in various applications where vapor quality is a critical parameter, including refrigeration,
     * boiling, and condensation processes.
     */
    using X            = fluent::NamedType<FLOAT,
                                           struct VaporQualityTag,
                                           fluent::Printable,
                                           fluent::Addable,
                                           fluent::Subtractable,
                                           fluent::Multiplicable,
                                           fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Q            = X;
    using VaporQuality = X;

    /**
     * @typedef Eta
     * @brief Defines a named type for Dynamic Viscosity, increasing type safety and expressiveness in fluid dynamics calculations.
     *
     * The Eta type wraps a FLOAT (typically a floating-point type such as float or double), and labels it as representing dynamic
     * viscosity. It inherits from the Fluent Named Type library traits, enabling arithmetic operations like addition, subtraction,
     * multiplication, and implicit conversion to FLOAT. These features make the Eta type both robust and versatile for use in various
     * scientific and engineering contexts where dynamic viscosity is a crucial fluid property for characterizing flow behavior and
     * resistance.
     */
    using Eta              = fluent::NamedType<FLOAT,
                                               struct DynamicViscosityTag,
                                               fluent::Printable,
                                               fluent::Addable,
                                               fluent::Subtractable,
                                               fluent::Multiplicable,
                                               fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using DynamicViscosity = Eta;

    /**
     * @typedef Nu
     * @brief Defines a named type for Kinematic Viscosity, increasing type safety and expressiveness in fluid dynamics.
     *
     * The Nu type wraps a FLOAT (typically a floating-point type such as float or double), and labels it as representing
     * kinematic viscosity. It benefits from the Fluent Named Type library traits, enabling arithmetic operations like
     * addition, subtraction, multiplication, and implicit conversion to FLOAT. These features make the Nu type both
     * robust and adaptable for use in a wide range of scientific and engineering contexts where kinematic viscosity is
     * a key parameter for describing the ratio of dynamic viscosity to fluid density, affecting flow and diffusion.
     */
    using Nu                 = fluent::NamedType<FLOAT,
                                                 struct KinematicViscosityTag,
                                                 fluent::Printable,
                                                 fluent::Addable,
                                                 fluent::Subtractable,
                                                 fluent::Multiplicable,
                                                 fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using KinematicViscosity = Nu;

    /**
     * @typedef TC
     * @brief Defines a named type for Thermal Conductivity, increasing type safety and expressiveness in heat transfer analysis.
     *
     * The TC type wraps a FLOAT (commonly a floating-point type such as float or double), and marks it as representing thermal
     * conductivity. It inherits from the Fluent Named Type library traits, enabling arithmetic operations like addition,
     * subtraction, multiplication, and implicit conversion to FLOAT. These features make the TC type robust and adaptable for
     * use in a wide range of applications where thermal conductivity is a critical property for analyzing and predicting heat
     * transfer in materials.
     */
    using TC                  = fluent::NamedType<FLOAT,
                                                  struct ThermalConductivityTag,
                                                  fluent::Printable,
                                                  fluent::Addable,
                                                  fluent::Subtractable,
                                                  fluent::Multiplicable,
                                                  fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using ThermalConductivity = TC;

    /**
     * @typedef PR
     * @brief Defines a named type for Prandtl Number, increasing type safety and expressiveness in fluid dynamics and heat transfer
     * analysis.
     *
     * The PR type wraps a FLOAT (typically a floating-point type such as float or double), and labels it as representing the Prandtl
     * number, a dimensionless number that characterizes the relative thickness of the momentum and thermal boundary layers in fluid flow.
     * It inherits from the Fluent Named Type library traits, enabling arithmetic operations like addition, subtraction, multiplication, and
     * implicit conversion to FLOAT. These features make the PR type both robust and adaptable for use in a wide range of scientific and
     * engineering contexts where the Prandtl number is a key parameter for analyzing heat transfer in fluid flows.
     */
    using PR            = fluent::NamedType<FLOAT,
                                            struct PrandtlNumberTag,
                                            fluent::Printable,
                                            fluent::Addable,
                                            fluent::Subtractable,
                                            fluent::Multiplicable,
                                            fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using PrandtlNumber = PR;

    /**
     * @enum Phase
     * @brief Enumerates the possible phases of matter in the context of thermodynamics.
     *
     * The Phase enum class provides a list of possible states or phases of matter that are commonly used
     * in thermodynamics and fluid dynamics calculations. It includes Liquid, Gas, TwoPhase (representing a mixture of liquid and gas),
     * Critical (representing the critical point at which the liquid and gas phases become indistinguishable),
     * Supercritical (representing a state of matter beyond the critical point), and Unknown (representing an undefined or unknown phase).
     *
     * The use of this enum within the fluid dynamics framework ensures a standardized approach to phase
     * specification, enhancing code readability, maintainability, and interoperability among different
     * components and derived class implementations.
     */
    enum class Phase { Liquid, Gas, TwoPhase, Critical, Supercritical, Unknown };

    /**
     * @fn std::string phaseToString(Phase phase)
     * @brief Converts a Phase enum value to a corresponding string representation.
     *
     * This function takes a Phase enum value as input and returns a string that represents the same phase.
     * It supports all possible phases of matter defined in the Phase enum, including Liquid, Gas, TwoPhase,
     * Critical, and Supercritical. If the input phase does not match any of these, the function returns "UNKNOWN".
     *
     * @param phase The Phase enum value to be converted to a string.
     * @return A string representing the input phase. If the input phase does not correspond to a known phase, the function returns
     * "UNKNOWN".
     */
    inline std::string phaseToString(Phase phase)
    {
        switch (phase) {
            case Phase::Liquid:
                return "LIQUID";
            case Phase::Gas:
                return "GAS";
            case Phase::TwoPhase:
                return "TWOPHASE";
            case Phase::Critical:
                return "CRITICAL";
            case Phase::Supercritical:
                return "SUPERCRITICAL";
            default:
                return "UNKNOWN";
        }
    }

    /**
     * @fn std::ostream& operator<<(std::ostream& os, Phase phase)
     * @brief Overloads the stream insertion operator for the Phase enum.
     *
     * This function overloads the stream insertion operator (<<) to enable direct output of Phase enum values
     * to an output stream (such as std::cout or an std::ofstream). It uses the phaseToString function to convert
     * the Phase enum value to a string representation, which is then inserted into the output stream.
     *
     * @param os The output stream where the Phase string representation will be inserted.
     * @param phase The Phase enum value to be output.
     * @return The same output stream passed as input, allowing for chaining of output operations.
     */
    inline std::ostream& operator<<(std::ostream& os, Phase phase)
    {
        os << phaseToString(phase);
        return os;
    }

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
        std::same_as<PROPERTY, Alpha> || std::same_as<PROPERTY, Phase>;

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
