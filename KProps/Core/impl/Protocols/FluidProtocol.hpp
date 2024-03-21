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
 * @file FluidProtocol.hpp
 * @brief Provides a template for implementing fluid dynamic protocols in derived classes.
 *
 * This file contains the FluidProtocol class template, which serves as a base class for
 * implementing fluid dynamic properties and state transition methods. It leverages the Curiously
 * Recurring Template Pattern (CRTP) to provide a static polymorphism mechanism that allows derived
 * classes to implement specific fluid dynamics algorithms, properties, and state transitions
 * without the overhead of dynamic polymorphism. The class template is designed to be used with
 * fluid properties and states such as pressure, temperature, density, enthalpy, etc., and supports
 * both molar and mass units.
 */

#pragma once

// ===== KProps Includes =====
#include <KPropsUtils.hpp>

namespace KProps::detail
{

    /**
     * @class FluidProtocol
     * @brief Template class providing a protocol for fluid state and property management.
     *
     * The FluidProtocol class template serves as a base for derived classes to implement specific
     * fluid dynamics functionalities. It employs the CRTP design pattern to enable static polymorphism,
     * allowing for efficient compile-time binding of derived class methods. This class provides
     * mechanisms to set the fluid's state using various property pairs (e.g., pressure-temperature),
     * retrieve fluid properties, and manage unit conversions. The interface enforces consistency and
     * facilitates the implementation of complex fluid dynamics calculations in derived classes.
     *
     * @tparam DERIVED The derived class that implements the specific fluid dynamics algorithms.
     */
    template<typename DERIVED>
    class FluidProtocol
    {
        friend DERIVED;

        /**
         * @brief Returns a reference to the derived class object.
         * @return A reference to the derived class object.
         *
         * This function enables access to the derived class's implementation of fluid dynamics
         * algorithms and properties from the base class context, facilitating the CRTP pattern.
         */
        DERIVED& derived() { return static_cast<DERIVED&>(*this); }

        /**
         * @brief Returns a const reference to the derived class object.
         * @return A const reference to the derived class object.
         *
         * This const variant of the derived() function allows for accessing derived class's
         * implementations in a const context, ensuring the immutability of the object when needed.
         */
        const DERIVED& derived() const { return static_cast<const DERIVED&>(*this); }

    protected:
        ~FluidProtocol() = default; /**< Destructor. Protected to prevent instantiation of base class. */

    public:
        /**
         * @brief Sets the state of the fluid using two properties.
         * @details This function determines the appropriate state transition function to call based on
         * the types of the properties provided. It supports a wide range of property pairs, including
         * pressure-temperature, pressure-enthalpy, and others. The function also handles unit
         * conversions for properties that depend on the composition of the fluid (e.g., molar vs. mass units).
         *
         * @tparam UNITS_T The units type, either MolarUnits or MassUnits, with a default of MolarUnits.
         * @tparam P1 The type of the first property.
         * @tparam P2 The type of the second property.
         * @param p1 The first property.
         * @param p2 The second property.
         *
         * @note The function employs C++20 concepts to enforce constraints on the template parameters,
         * ensuring that only valid property types and unit types are used.
         */
        template<typename UNITS_T = MolarUnits, IsProperty P1, IsProperty P2>
            requires std::same_as<UNITS_T, MolarUnits> || std::same_as<UNITS_T, MassUnits>
        void setState(P1 p1, P2 p2)
        {
            auto       spec   = std::make_pair(p1, p2);
            auto const factor = std::same_as<UNITS_T, MolarUnits> ? 1.0 : derived().molarMass();

            if constexpr (IsSpecificationPT<P1, P2>)
                derived().setStatePT(std::get<P>(spec), std::get<T>(spec));
            else if constexpr (IsSpecificationPX<P1, P2>)
                derived().setStatePX(std::get<P>(spec), std::get<X>(spec));
            else if constexpr (IsSpecificationPH<P1, P2>)
                derived().setStatePH(std::get<P>(spec), H { std::get<H>(spec) * factor });
            else if constexpr (IsSpecificationPS<P1, P2>)
                derived().setStatePS(std::get<P>(spec), S { std::get<S>(spec) * factor });
            else if constexpr (IsSpecificationPD<P1, P2>)
                derived().setStateDP(Rho { std::get<Rho>(spec) / factor }, std::get<P>(spec));
            else if constexpr (IsSpecificationTD<P1, P2>)
                derived().setStateDT(Rho { std::get<Rho>(spec) / factor }, std::get<T>(spec));
            else if constexpr (IsSpecificationDS<P1, P2>)
                derived().setStateDS(Rho { std::get<Rho>(spec) / factor }, S { std::get<S>(spec) * factor });
            else if constexpr (IsSpecificationDH<P1, P2>)
                derived().setStateDH(Rho { std::get<Rho>(spec) / factor }, H { std::get<H>(spec) * factor });
            else if constexpr (IsSpecificationDU<P1, P2>)
                derived().setStateDU(Rho { std::get<Rho>(spec) / factor }, U { std::get<U>(spec) * factor });
            else if constexpr (IsSpecificationHS<P1, P2>)
                derived().setStateHS(H { std::get<H>(spec) * factor }, S { std::get<S>(spec) * factor });
            else if constexpr (IsSpecificationPU<P1, P2>)
                derived().setStatePU(std::get<P>(spec), U { std::get<U>(spec) * factor });
            else if constexpr (IsSpecificationTS<P1, P2>)
                derived().setStateTS(std::get<T>(spec), S { std::get<S>(spec) * factor });
            else if constexpr (IsSpecificationTX<P1, P2>)
                derived().setStateTX(std::get<T>(spec), std::get<X>(spec));

            // Recursive call to setState in case one of the specifications is for Volume.
            else if constexpr (std::same_as<P1, V>)
                setState<UNITS_T>(Rho { 1.0 / p1.get() }, p2);
            else if constexpr (std::same_as<P2, V>)
                setState<UNITS_T>(p1, Rho { 1.0 / p2.get() });
            else
                std::invoke([]<bool flag = false>() { static_assert(flag, "Invalid specification"); });
        }

        /**
         * @brief Returns the value of a property.
         * @details This member function of the FluidProtocol class template retrieves the value of a
         * specified fluid property. The function supports a wide range of fluid properties, including
         * fundamental properties such as molar weight (MW), temperature (T), pressure (P), vapor quality (X),
         * enthalpy (H), entropy (S), density (Rho), and internal energy (U), as well as derived properties
         * like volume (V), Gibbs energy (G), Helmholtz energy (A), and compressibility (Z). Optional properties
         * like specific heat at constant pressure (Cp), specific heat at constant volume (Cv), speed of sound (W),
         * isothermal compressibility (Kappa), and thermal expansion (Alpha) can also be retrieved, depending on
         * the implementation in the derived class.
         *
         * The function handles unit conversions for properties that depend on the fluid's composition, such as
         * converting between molar and mass units. This allows users to retrieve property values in the most
         * appropriate units for their calculations. The function employs compile-time checks and C++20 concepts
         * to ensure that only valid property types are requested, and it gracefully handles requests for unsupported
         * properties by generating compile-time errors.
         *
         * @tparam PROPERTY_T The type of the property to retrieve. Must be a valid property type.
         * @tparam UNITS_T The units type, specifying the unit system in which the property value should be returned.
         *                 Can be either MolarUnits or MassUnits. Defaults to MolarUnits.
         * @return The value of the requested property, adjusted for the specified units. The return type is dependent
         *         on the property and units requested and may vary accordingly.
         *
         * @note This function relies on the derived class's implementation to actually retrieve the property values.
         *       It only defines the interface and handling mechanism for property retrieval, including unit conversions.
         *       Derived classes must implement the logic to provide the actual values for each supported property.
         */
        template<IsProperty PROPERTY_T, typename UNITS_T = MolarUnits>
        [[nodiscard]]
        auto property() const
        {
            double const factor = std::same_as<UNITS_T, MolarUnits> ? 1.0 : derived().molarMass();

            // Required properties
            if constexpr (std::same_as<PROPERTY_T, MW>)
                return PROPERTY_T { derived().molarMass() };
            else if constexpr (std::same_as<PROPERTY_T, T>)
                return PROPERTY_T { derived().temperature() };
            else if constexpr (std::same_as<PROPERTY_T, P>)
                return PROPERTY_T { derived().pressure() };
            else if constexpr (std::same_as<PROPERTY_T, X>)
                return PROPERTY_T { derived().vaporQuality() };
            else if constexpr (std::same_as<PROPERTY_T, H>)
                return PROPERTY_T { derived().enthalpy() / factor };
            else if constexpr (std::same_as<PROPERTY_T, S>)
                return PROPERTY_T { derived().entropy() / factor };
            else if constexpr (std::same_as<PROPERTY_T, Rho>)
                return PROPERTY_T { derived().density() * factor };
            else if constexpr (std::same_as<PROPERTY_T, U>)
                return PROPERTY_T { derived().internalEnergy() / factor };

            // Derived properties
            else if constexpr (std::same_as<PROPERTY_T, V>)
                return PROPERTY_T { derived().volume() / factor };
            else if constexpr (std::same_as<PROPERTY_T, G>)
                return PROPERTY_T { derived().gibbsEnergy() / factor };
            else if constexpr (std::same_as<PROPERTY_T, A>)
                return PROPERTY_T { derived().helmholtzEnergy() / factor };
            else if constexpr (std::same_as<PROPERTY_T, Z>)
                return PROPERTY_T { derived().compressibility() };

            // Optional properties
            else if constexpr (std::same_as<PROPERTY_T, Cp>)
                return PROPERTY_T { derived().cp() / factor };
            else if constexpr (std::same_as<PROPERTY_T, Cv>)
                return PROPERTY_T { derived().cv() / factor };
            else if constexpr (std::same_as<PROPERTY_T, W>)
                return PROPERTY_T { derived().speedOfSound() };
            else if constexpr (std::same_as<PROPERTY_T, Kappa>)
                return PROPERTY_T { derived().isothermalCompressibility() };
            else if constexpr (std::same_as<PROPERTY_T, Alpha>)
                return PROPERTY_T { derived().thermalExpansion() };
            else if constexpr (std::same_as<PROPERTY_T, Phase>)
                return PROPERTY_T { derived().phase() };
            else if constexpr (std::same_as<PROPERTY_T, Undefined>)
                return PROPERTY_T { std::nan("") };
            //            else if constexpr (std::same_as<PROPERTY_T, Eta>)
            //                return PROPERTY_T { 0.0 };
            //            else if constexpr (std::same_as<PROPERTY_T, Nu>)
            //                return PROPERTY_T { 0.0 };
            //            else if constexpr (std::same_as<PROPERTY_T, TC>)
            //                return PROPERTY_T { 0.0 };
            //            else if constexpr (std::same_as<PROPERTY_T, PR>)
            //                return PROPERTY_T { 0.0 };

            else
                std::invoke([]<bool flag = false>() { static_assert(flag, "Invalid property"); });
        }

        /**
         * @brief Returns the value of a property specified by a Property enum value.
         * @details This overload of the property member function provides a mechanism to retrieve the value
         * of a fluid property using a strongly typed enum, `Property`, to specify the property of interest. This
         * approach simplifies the retrieval process by abstracting the specific property type behind an enum,
         * making the API easier to use and less prone to errors. The function leverages a mapping mechanism to
         * translate the enum value to the corresponding property type, after which it invokes the template-based
         * property retrieval method to obtain the property value. This design enhances type safety, reduces the
         * risk of requesting unsupported or non-existent properties, and ensures consistency across different
         * implementations of fluid dynamics algorithms in derived classes.
         *
         * The function supports the same range of properties as the template-based property retrieval method,
         * including fundamental, derived, and optional properties, subject to the capabilities of the derived
         * class. It also handles unit conversions for properties that depend on the fluid's composition, allowing
         * users to specify whether they wish to receive the property value in molar or mass units.
         *
         * @tparam UNITS_T The units type, specifying the unit system in which the property value should be returned.
         *                 Can be either MolarUnits or MassUnits, with a default of MolarUnits. This allows the user
         *                 to request the property value in the most appropriate units for their application.
         * @param prop The `Property` enum value specifying the property to retrieve. This enum should cover all
         *             properties supported by the fluid dynamics implementation in the derived class.
         * @return The value of the requested property, adjusted for the specified units. The return type is a
         *         double, representing the property value in the units specified by the `UNITS_T` template parameter.
         *
         * @note This function relies on the `mapPropertyToVariant` function to translate the `Property` enum value
         *       to a `std::variant` representing the specific property type. It then uses `std::visit` to retrieve
         *       the property value through the template-based property retrieval method. The actual retrieval and
         *       conversion logic is implemented in the derived class, with this function providing a unified interface
         *       for property retrieval.
         */
        template<typename UNITS_T = MolarUnits>
        [[nodiscard]]
        auto property(Property::Type prop) const
        {
            Property var(prop);
            std::visit(
                [&]<typename ARGUMENT>(ARGUMENT&& arg) {
                    using PROPERTY_T = std::decay_t<decltype(arg)>;
                    var = property<PROPERTY_T, UNITS_T>();
                },
                var);

            return var;
        }

        /**
         * @brief Returns the value of a property specified by a string.
         * @details This overload of the property() member function offers a flexible way to retrieve fluid
         * property values using a string identifier for the property. It is designed to facilitate interaction
         * with systems where property identifiers might be dynamically specified at runtime, such as in scripting
         * languages or through user input in a graphical interface. The function maps the input string to the
         * corresponding `Property` enum value, leveraging the existing property retrieval mechanisms to obtain
         * and return the property value.
         *
         * This approach maintains the benefits of type safety and compile-time checks where possible, by
         * translating the runtime string input into a compile-time type. It also provides a convenient interface
         * for accessing fluid properties without requiring direct usage of property types or enum values,
         * simplifying the API for dynamic use cases.
         *
         * @tparam UNITS_T The units type, indicating whether the property value should be returned in MolarUnits
         *                 or MassUnits. Defaults to MolarUnits. This template parameter allows the user to
         *                 specify the unit system for the returned property value, catering to different
         *                 calculation needs.
         * @param propertyString The string specifying the property. This string is mapped to a corresponding
         *                       `Property` enum value, which is then used to retrieve the property value. The
         *                       mapping is dependent on the implementation in the derived class and requires a
         *                       comprehensive mapping function to cover all supported properties.
         * @return The value of the requested property, adjusted for the specified units. The return type is a
         *         double, representing the property value in the specified unit system. This ensures that the
         *         function can be used flexibly in various contexts where the specific property type might not
         *         be known at compile time.
         *
         * @note This function relies on the derived class implementing a `mapStringToProperty` function that
         *       translates a property name string to a `Property` enum value. The actual property value retrieval
         *       is then performed using the existing property retrieval mechanisms, ensuring consistency in
         *       property handling and unit conversion across different interfaces.
         */
        template<typename UNITS_T = MolarUnits>
        [[nodiscard]]
        auto property(std::string propertyString) const
        {
            std::transform(propertyString.begin(), propertyString.end(), propertyString.begin(), ::toupper);
            return property<UNITS_T>(Property::typeFromString(propertyString));
        }

        /**
         * @brief Returns the saturation temperature or pressure.
         * @details The saturation() member function provides the saturation temperature or pressure of the
         * fluid, depending on the property type specified by the template parameter. Saturation properties
         * are fundamental in thermodynamics and fluid dynamics, characterizing the transition between phases
         * under equilibrium conditions. This function allows for an intuitive and direct query of these critical
         * properties, enhancing the usability and flexibility of the fluid dynamics model implemented by the
         * derived class.
         *
         * The function employs template metaprogramming to enforce that only valid property types, specifically
         * temperature (T) or pressure (P), can be used to instantiate it. This design ensures type safety and
         * correctness by leveraging compile-time checks, thus preventing misuse of the API.
         *
         * @tparam PROPERTY_T The type of the saturation property to retrieve. Must be either T (temperature)
         *                    or P (pressure), representing the desired saturation condition to query.
         * @return The saturation property value, encapsulated in the PROPERTY_T type. This design ensures that
         *         the return type conveys both the value and the semantic meaning of the property being retrieved,
         *         enhancing code readability and maintainability.
         *
         * @note This function relies on the derived class to provide the actual implementation of the saturation
         *       temperature and pressure retrieval. It defines the interface and enforces the contract between
         *       the base and derived classes, ensuring that derived classes adhere to the expected behavior.
         */
        template<IsProperty PROPERTY_T>
            requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
        [[nodiscard]]
        auto saturation() const
        {
            if constexpr (std::same_as<PROPERTY_T, T>)
                return PROPERTY_T { derived().saturationTemperature() };
            else
                return PROPERTY_T { derived().saturationPressure() };
        }

        /**
         * @brief Returns the critical temperature or pressure.
         * @details The critical() member function retrieves the critical temperature or pressure of the fluid,
         * which are key thermodynamic properties defining the conditions at which the liquid and gas phases of
         * a substance have the same density, marking the end of the phase envelope. This function facilitates
         * access to these critical properties, which are essential for the analysis and calculation of fluid
         * behavior under various conditions, especially near critical points where fluid properties experience
         * significant changes.
         *
         * Similar to other specialized property retrieval functions, critical() employs template metaprogramming
         * techniques to ensure that it can only be instantiated for property types representing temperature (T)
         * or pressure (P). This restriction is enforced at compile-time, enhancing the safety and predictability
         * of the function by preventing the retrieval of unrelated properties through its interface.
         *
         * @tparam PROPERTY_T The type of the critical property to retrieve. Must be constrained to T (temperature)
         *                    or P (pressure), corresponding to the critical temperature and critical pressure,
         *                    respectively.
         * @return The critical property value, wrapped in the specified PROPERTY_T type. This ensures that the
         *         returned value is immediately identifiable as a temperature or pressure, depending on the
         *         property type requested, thereby improving the clarity and expressiveness of the function's usage.
         *
         * @note The implementation of this function is expected to be provided by the derived class, which must
         *       define the mechanisms for calculating or retrieving the critical temperature and pressure values.
         *       This design delegates the responsibility for implementing these critical property calculations to
         *       the derived class, allowing for flexibility in the choice of methods and data sources.
         */
        template<IsProperty PROPERTY_T>
            requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
        [[nodiscard]]
        auto critical() const
        {
            if constexpr (std::same_as<PROPERTY_T, T>)
                return PROPERTY_T { derived().criticalTemperature() };
            else
                return PROPERTY_T { derived().criticalPressure() };
        }

        /**
         * @brief Returns the minimum temperature or pressure.
         * @details The min() member function retrieves the minimum allowable temperature or pressure for the
         * fluid model implemented by the derived class. These minimum values are crucial for defining the valid
         * operational or study range of the fluid, beyond which the physical models or empirical correlations
         * may not provide reliable results. Access to these limits ensures that simulations and calculations
         * remain within the boundaries where the fluid's behavior is well-defined and predictable.
         *
         * Leveraging template metaprogramming, this function enforces at compile-time that it can only be called
         * with property types representing temperature (T) or pressure (P). This design decision reinforces type
         * safety and API correctness, preventing misuse and ensuring that the function's intent is clear.
         *
         * @tparam PROPERTY_T The type of the minimum property to retrieve. This is constrained to T (temperature)
         *                    or P (pressure) to specify whether the minimum temperature or pressure is being
         *                    requested.
         * @return The minimum value of the requested property, encapsulated within the PROPERTY_T type. This
         *         encapsulation facilitates clear, self-documenting code by making the property type explicit
         *         in the function's return value, enhancing readability and maintainability.
         *
         * @note Implementation of this function must be provided by the derived class, which is responsible for
         *       defining the minimum temperature and pressure based on the fluid model or database being used.
         *       This requirement allows for customized definitions of these limits to fit specific fluids and
         *       applications.
         */
        template<IsProperty PROPERTY_T>
            requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
        [[nodiscard]]
        auto min() const
        {
            if constexpr (std::same_as<PROPERTY_T, T>)
                return PROPERTY_T { derived().minTemperature() };
            else
                return PROPERTY_T { derived().minPressure() };
        }

        /**
         * @brief Returns the maximum temperature or pressure.
         * @details The max() member function retrieves the maximum allowable temperature or pressure for the
         * fluid model implemented by the derived class. Identifying the maximum limits is essential for
         * understanding the range within which the fluid's behavior is accurately described by the model or
         * empirical data. This information is particularly valuable for ensuring that simulations and analytical
         * studies do not exceed the conditions where the fluid model remains valid and reliable.
         *
         * By employing template metaprogramming, max() is designed to accept only property types representing
         * temperature (T) or pressure (P), reinforcing the function's usage specificity and correctness through
         * compile-time checks. This approach effectively prevents misuse and maintains the integrity of the
         * fluid model's operational boundaries.
         *
         * @tparam PROPERTY_T The type of the maximum property to retrieve, constrained to either T (temperature)
         *                    or P (pressure). This specification determines whether the function returns the
         *                    maximum temperature or pressure that the fluid model supports.
         * @return The maximum value of the specified property, encapsulated within the PROPERTY_T type. Encapsulating
         *         the return value in this manner promotes type safety and clarity, making the returned property's
         *         nature immediately apparent and ensuring consistency in how property values are handled.
         *
         * @note The implementation of this function is the responsibility of the derived class, which must define
         *       the maximum temperature and pressure according to the specific fluid model or dataset in use. This
         *       requirement facilitates adaptability and precision in representing the upper limits of the fluid's
         *       operational range.
         */
        template<IsProperty PROPERTY_T>
            requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
        [[nodiscard]]
        auto max() const
        {
            if constexpr (std::same_as<PROPERTY_T, T>)
                return PROPERTY_T { derived().maxTemperature() };
            else
                return PROPERTY_T { derived().maxPressure() };
        }
    };

}    // namespace pcprops::detail