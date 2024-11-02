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
 * @file FluidWrapper.hpp
 * @brief Provides a wrapper class for fluid property implementations.
 *
 * This header file defines the FluidWrapper class template, which serves as a universal adapter for various fluid property backends.
 * It leverages the CRTP (Curiously Recurring Template Pattern) to provide a standardized interface for accessing fluid properties,
 * regardless of the underlying implementation. The class template forwards property requests to the encapsulated implementation,
 * handling unsupported operations gracefully and providing fallbacks where appropriate.
 */

#pragma once

#include "../Properties/Derivatives.hpp"
#include "../Protocols/FluidProtocol.hpp"
#include "../Utils/Concepts.hpp"

namespace KProps
{
    /**
     * @class FluidWrapper
     * @brief A wrapper class template for fluid property implementations.
     *
     * @details The FluidWrapper class template serves as a universal adapter for different fluid property backends,
     * leveraging the Curiously Recurring Template Pattern (CRTP) with the detail::FluidProtocol to offer a standardized
     * interface for accessing fluid properties. This design enables seamless integration and uniform access to a variety
     * of fluid property models, facilitating the development of generic fluid dynamics applications. The wrapper forwards
     * requests for fluid properties to the encapsulated implementation, handling unsupported operations gracefully and
     * providing fallback implementations where applicable.
     *
     * The FluidWrapper ensures that applications can interact with any fluid property backend through a consistent interface,
     * abstracting away the specifics of the underlying implementation. This abstraction allows for flexibility in switching
     * or upgrading fluid property models with minimal impact on the application code. The wrapper also implements checks for
     * the availability of specific property calculations in the underlying model, throwing runtime errors for unsupported
     * operations to prevent silent failures and aid in debugging.
     *
     * @tparam IMPL_T The type of the fluid property implementation being wrapped. This type must conform to the expected
     * interface of fluid property backends, including a set of core property calculation functions. The actual requirements
     * are implicitly defined by the usage within the wrapper and may include functions for setting state (e.g., setStatePT)
     * and retrieving properties (e.g., temperature, pressure).
     *
     * @note The FluidWrapper uses static polymorphism through CRTP rather than virtual functions to avoid the overhead of
     * dynamic dispatch. Therefore, it is essential that the IMPL_T type provides compile-time support for the required
     * operations.
     */
    template<typename IMPL_T>
    class FluidWrapper : public detail::FluidProtocol<FluidWrapper<IMPL_T>>
    {
        IMPL_T m_impl;
        using BASE = detail::FluidProtocol<FluidWrapper<IMPL_T>>;
        friend BASE;

    public:
        /**
         * @brief Constructs a FluidWrapper object with a copy of an existing fluid property implementation.
         *
         * @details This constructor initializes the FluidWrapper with a copy of an existing fluid property implementation,
         * encapsulating it within the wrapper to provide uniform access to its properties and functions. The passed fluid
         * property object is copied, ensuring that the wrapper has its own instance of the fluid properties, independent
         * of the original object.
         *
         * The use of this constructor is suitable when the fluid property implementation needs to be shared or reused
         * across multiple parts of an application without affecting the original instance. It provides a safe way to
         * use the capabilities of an existing fluid property model within the standardized interface of the FluidWrapper.
         *
         * @param fluid A constant reference to an instance of the fluid property implementation (IMPL_T) to be copied into
         * the wrapper. The type IMPL_T must conform to the expected interface of fluid property backends, including a set
         * of core property calculation functions.
         */
        explicit FluidWrapper(const IMPL_T& fluid) : m_impl(fluid) {}

        /**
         * @brief Constructs a FluidWrapper object by moving an existing fluid property implementation.
         *
         * @details This constructor initializes the FluidWrapper by taking ownership of an existing fluid property implementation
         * through move semantics. It effectively transfers the state of the passed fluid property object into the wrapper,
         * leaving the original object in a valid but unspecified state. This approach is efficient for initializing the wrapper
         * with fluid property models that are temporary or no longer needed in their original context.
         *
         * Utilizing move semantics minimizes overhead by avoiding unnecessary copying, making this constructor suitable for
         * situations where the fluid property implementation is dynamically created or when performance considerations are
         * paramount. It ensures that the wrapper is directly initialized with the resources of the existing model, thereby
         * optimizing resource use and initialization time.
         *
         * @param fluid An rvalue reference to an instance of the fluid property implementation (IMPL_T) to be moved into
         * the wrapper. The type IMPL_T must conform to the expected interface of fluid property backends, including a set
         * of core property calculation functions.
         */
        explicit FluidWrapper(IMPL_T&& fluid) : m_impl(std::move(fluid)) {}

        FluidWrapper(const FluidWrapper& other) = default; /**< Copy constructor. */
        FluidWrapper(FluidWrapper&&) noexcept   = default; /**< Move constructor. */

        FluidWrapper& operator=(const FluidWrapper& other) = default; /**< Copy assignment operator. */
        FluidWrapper& operator=(FluidWrapper&&) noexcept   = default; /**< Move assignment operator. */

        /**
         * @brief Provides non-const access to the encapsulated fluid property implementation.
         *
         * @details This member function returns a reference to the encapsulated fluid property implementation (IMPL_T),
         * allowing for non-const operations on the underlying model. It enables direct manipulation and access to the
         * specific functionalities of the fluid property backend that might not be exposed through the FluidWrapper's
         * interface. This function is useful when needing to perform operations specific to the underlying implementation
         * or when the FluidWrapper interface does not provide the required functionality.
         *
         * It is important to use this access carefully, as modifications to the underlying implementation can affect the
         * state and behavior of the FluidWrapper object. Direct access should be used judiciously and with an understanding
         * of the underlying fluid property model's behavior.
         *
         * @return A non-const reference to the encapsulated fluid property implementation (IMPL_T).
         */
        auto& impl() { return m_impl; }

        /**
         * @brief Provides const access to the encapsulated fluid property implementation.
         *
         * @details This member function returns a const reference to the encapsulated fluid property implementation (IMPL_T),
         * allowing for read-only operations on the underlying model. It enables access to the specific functionalities and
         * properties of the fluid property backend without allowing modifications to its state. This function is particularly
         * useful for querying information or performing calculations that do not alter the state of the fluid property model.
         *
         * Utilizing this const access ensures that the integrity of the underlying implementation is maintained while still
         * providing the flexibility to inspect and use its properties and functionalities. It is a safe way to interact with
         * the underlying model when only read operations are required.
         *
         * @return A const reference to the encapsulated fluid property implementation (IMPL_T).
         */
        const auto& impl() const { return m_impl; }

    private:
        /**
         * @brief Sets the state of the fluid using pressure and temperature.
         * @param pressure The pressure of the fluid.
         * @param temperature The temperature of the fluid.
         * @throws std::runtime_error If setting state by pressure and temperature is not supported.
         */
        void setStatePT(P pressure, T temperature)
        {
            if constexpr (detail::SupportsSpecPT<IMPL_T>)
                m_impl.setStatePT(pressure, temperature);
            else
                throw std::runtime_error("setStatePT not supported by this backend");
        }

        /**
         * @brief Sets the state of the fluid using pressure and vapor quality.
         * @param pressure The pressure of the fluid.
         * @param vaporQuality The vapor quality of the fluid.
         * @throws std::runtime_error If setting state by pressure and vapor quality is not supported.
         */
        void setStatePX(P pressure, X vaporQuality)
        {
            if constexpr (detail::SupportsSpecPX<IMPL_T>)
                m_impl.setStatePX(pressure, vaporQuality);
            else
                throw std::runtime_error("setStatePX not supported by this backend");
        }

        /**
         * @brief Sets the state of the fluid using pressure and enthalpy.
         * @param pressure The pressure of the fluid.
         * @param enthalpy The enthalpy of the fluid.
         * @throws std::runtime_error If setting state by pressure and enthalpy is not supported.
         */
        void setStatePH(P pressure, H enthalpy)
        {
            if constexpr (detail::SupportsSpecPH<IMPL_T>)
                m_impl.setStatePH(pressure, enthalpy);
            else
                throw std::runtime_error("setStatePH not supported by this backend");
        }

        /**
         * @brief Sets the state of the fluid using pressure and entropy.
         * @param pressure The pressure of the fluid.
         * @param entropy The entropy of the fluid.
         * @throws std::runtime_error If setting state by pressure and entropy is not supported.
         */
        void setStatePS(P pressure, S entropy)
        {
            if constexpr (detail::SupportsSpecPS<IMPL_T>)
                m_impl.setStatePS(pressure, entropy);
            else
                throw std::runtime_error("setStatePS not supported by this backend");
        }

        /**
         * @brief Sets the state of the fluid using density and pressure.
         * @param density The density of the fluid.
         * @param pressure The pressure of the fluid.
         * @throws std::runtime_error If setting state by density and pressure is not supported.
         */
        void setStateDP(Rho density, P pressure)
        {
            if constexpr (detail::SupportsSpecDP<IMPL_T>)
                m_impl.setStateDP(density, pressure);
            else
                throw std::runtime_error("setStateDP not supported by this backend");
        }

        /**
         * @brief Sets the state of the fluid using density and temperature.
         * @param density The density of the fluid.
         * @param temperature The temperature of the fluid.
         * @throws std::runtime_error If setting state by density and temperature is not supported.
         */
        void setStateDT(Rho density, T temperature)
        {
            if constexpr (detail::SupportsSpecDT<IMPL_T>)
                m_impl.setStateDT(density, temperature);
            else
                throw std::runtime_error("setStateDT not supported by this backend");
        }

        /**
         * @brief Sets the state of the fluid using density and entropy.
         * @param density The density of the fluid.
         * @param entropy The entropy of the fluid.
         * @throws std::runtime_error If setting state by density and entropy is not supported.
         */
        void setStateDS(Rho density, S entropy)
        {
            if constexpr (detail::SupportsSpecDS<IMPL_T>)
                m_impl.setStateDS(density, entropy);
            else
                throw std::runtime_error("setStateDS not supported by this backend");
        }

        /**
         * @brief Sets the state of the fluid using density and enthalpy.
         * @param density The density of the fluid.
         * @param enthalpy The enthalpy of the fluid.
         * @throws std::runtime_error If setting state by density and enthalpy is not supported.
         */
        void setStateDH(Rho density, H enthalpy)
        {
            if constexpr (detail::SupportsSpecDH<IMPL_T>)
                m_impl.setStateDH(density, enthalpy);
            else
                throw std::runtime_error("setStateDH not supported by this backend");
        }

        /**
         * @brief Sets the state of the fluid using density and internal energy.
         * @param density The density of the fluid.
         * @param internalEnergy The internal energy of the fluid.
         * @throws std::runtime_error If setting state by density and internal energy is not supported.
         */
        void setStateDU(Rho density, U internalEnergy)
        {
            if constexpr (detail::SupportsSpecDU<IMPL_T>)
                m_impl.setStateDU(density, internalEnergy);
            else
                throw std::runtime_error("setStateDU not supported by this backend");
        }

        /**
         * @brief Sets the state of the fluid using enthalpy and entropy.
         * @param enthalpy The enthalpy of the fluid.
         * @param entropy The entropy of the fluid.
         * @throws std::runtime_error If setting state by enthalpy and entropy is not supported.
         */
        void setStateHS(H enthalpy, S entropy)
        {
            if constexpr (detail::SupportsSpecHS<IMPL_T>)
                m_impl.setStateHS(enthalpy, entropy);
            else
                throw std::runtime_error("setStateHS not supported by this backend");
        }

        /**
         * @brief Sets the state of the fluid using pressure and internal energy.
         * @param pressure The pressure of the fluid.
         * @param internalEnergy The internal energy of the fluid.
         * @throws std::runtime_error If setting state by pressure and internal energy is not supported.
         */
        void setStatePU(P pressure, U internalEnergy)
        {
            if constexpr (detail::SupportsSpecPU<IMPL_T>)
                m_impl.setStatePU(pressure, internalEnergy);
            else
                throw std::runtime_error("setStatePU not supported by this backend");
        }

        /**
         * @brief Sets the state of the fluid using temperature and entropy.
         * @param temperature The temperature of the fluid.
         * @param entropy The entropy of the fluid.
         * @throws std::runtime_error If setting state by temperature and entropy is not supported.
         */
        void setStateTS(T temperature, S entropy)
        {
            if constexpr (detail::SupportsSpecTS<IMPL_T>)
                m_impl.setStateTS(temperature, entropy);
            else
                throw std::runtime_error("setStateTS not supported by this backend");
        }

        /**
         * @brief Sets the state of the fluid using temperature and vapor quality.
         * @param temperature The temperature of the fluid.
         * @param quality The vapor quality of the fluid.
         * @throws std::runtime_error If setting state by temperature and vapor quality is not supported.
         */
        void setStateTX(T temperature, X quality)
        {
            if constexpr (detail::SupportsSpecTX<IMPL_T>)
                m_impl.setStateTX(temperature, quality);
            else
                throw std::runtime_error("setStateTX not supported by this backend");
        }

        // Required properties

        /**
         * @brief Retrieves the molar mass of the fluid.
         * @return The molar mass of the fluid.
         */
        [[nodiscard]]
        MW molarMass() const
        {
            return MW { m_impl.molarMass() };
        }

        /**
         * @brief Retrieves the current temperature of the fluid.
         * @return The temperature of the fluid.
         */
        [[nodiscard]]
        T temperature() const
        {
            return T { m_impl.temperature() };
        }

        /**
         * @brief Retrieves the current pressure of the fluid.
         * @return The pressure of the fluid.
         */
        [[nodiscard]]
        P pressure() const
        {
            return P { m_impl.pressure() };
        }

        /**
         * @brief Retrieves the vapor quality of the fluid.
         * @details Vapor quality is defined as the mass fraction of vapor in a liquid-vapor mixture.
         * @return The vapor quality of the fluid.
         */
        [[nodiscard]]
        X vaporQuality() const
        {
            if (pressure() >= criticalPressure() && temperature() >= criticalTemperature()) return X { std::nan("") };
            return X { m_impl.vaporQuality() };
        }

        /**
         * @brief Retrieves the enthalpy of the fluid.
         * @return The enthalpy of the fluid.
         */
        [[nodiscard]]
        H enthalpy() const
        {
            return H { m_impl.enthalpy() };
        }

        /**
         * @brief Retrieves the entropy of the fluid.
         * @return The entropy of the fluid.
         */
        [[nodiscard]]
        S entropy() const
        {
            return S { m_impl.entropy() };
        }

        /**
         * @brief Retrieves the density of the fluid.
         * @return The density of the fluid.
         */
        [[nodiscard]]
        Rho density() const
        {
            return Rho { m_impl.density() };
        }

        /**
         * @brief Retrieves the internal energy of the fluid.
         * @return The internal energy of the fluid.
         */
        [[nodiscard]]
        U internalEnergy() const
        {
            return U { m_impl.internalEnergy() };
        }

        // Derived properties

        /**
         * @brief Retrieves the volume of the fluid.
         * @details If the underlying implementation supports direct volume calculation, it is used. Otherwise, volume is calculated as the
         * inverse of density.
         * @return The volume of the fluid.
         */
        [[nodiscard]]
        V volume() const
        {
            if constexpr (detail::HasVolume<IMPL_T>)
                return V { m_impl.volume() };
            else
                return V { 1.0 / density() };
        }

        /**
         * @brief Retrieves the Gibbs energy of the fluid.
         * @details If the underlying implementation supports direct Gibbs energy calculation, it is used. Otherwise, Gibbs energy is
         * calculated using the relation G = H - T*S.
         * @return The Gibbs energy of the fluid.
         */
        [[nodiscard]]
        G gibbsEnergy() const
        {
            if constexpr (detail::HasGibbsEnergy<IMPL_T>)
                return G { m_impl.gibbsEnergy() };
            else
                return G { m_impl.enthalpy() - m_impl.temperature() * m_impl.entropy() };
        }

        /**
         * @brief Retrieves the Helmholtz energy of the fluid.
         * @details If the underlying implementation supports direct Helmholtz energy calculation, it is used. Otherwise, Helmholtz energy
         * is calculated using the relation A = U - T*S.
         * @return The Helmholtz energy of the fluid.
         */
        [[nodiscard]]
        A helmholtzEnergy() const
        {
            if constexpr (detail::HasHelmholtzEnergy<IMPL_T>)
                return A { m_impl.helmholtzEnergy() };
            else
                return A { m_impl.internalEnergy() - m_impl.temperature() * m_impl.entropy() };
        }

        /**
         * @brief Retrieves the compressibility factor (Z) of the fluid.
         * @details If the underlying implementation supports direct calculation of the compressibility factor, it is used. Otherwise,
         * compressibility factor is estimated from the ideal gas law.
         * @return The compressibility factor of the fluid.
         */
        [[nodiscard]]
        Z compressibility() const
        {
            if constexpr (detail::HasZ<IMPL_T>)
                return Z { m_impl.compressibility() };
            else
                return Z { m_impl.pressure() / (m_impl.density() * m_impl.temperature() * R) };
        }

        // Optional properties

        /**
         * @brief Retrieves the specific heat at constant pressure (Cp) of the fluid.
         * @return The specific heat at constant pressure.
         */
        [[nodiscard]]
        Cp cp() const
        {
            if constexpr (detail::HasCp<IMPL_T>)
                return Cp { m_impl.cp() };
            else
                return Cp { derivative<Of<H>, Wrt<T>, AtConst<P>>(*this) };
        }

        /**
         * @brief Retrieves the specific heat at constant volume (Cv) of the fluid.
         * @return The specific heat at constant volume.
         */
        [[nodiscard]]
        Cv cv() const
        {
            if constexpr (detail::HasCv<IMPL_T>)
                return Cv { m_impl.cv() };
            else
                return Cv { derivative<Of<U>, Wrt<T>, AtConst<V>>(*this) };
        }

        /**
         * @brief Retrieves the speed of sound in the fluid.
         * @details If not directly available, calculates based on the thermodynamic properties.
         * @return The speed of sound in the fluid.
         */
        [[nodiscard]]
        W speedOfSound() const
        {
            if constexpr (detail::HasSpeedOfSound<IMPL_T>)
                return W { m_impl.speedOfSound() };
            else {
                auto v     = 1.0 / density();
                auto _beta = -(1.0 / v) * (cv() / cp()) / derivative<Of<P>, Wrt<V>, AtConst<T>>(*this);
                auto temp  = v / (_beta * molarMass());
                return W { std::sqrt(temp) };
            }
        }

        /**
         * @brief Retrieves the isothermal compressibility of the fluid.
         * @details If not directly available, calculates based on the thermodynamic properties.
         * @return The isothermal compressibility of the fluid.
         */
        [[nodiscard]]
        Kappa isothermalCompressibility() const
        {
            if constexpr (detail::HasIsothermalCompressibility<IMPL_T>)
                return Kappa { m_impl.isothermalCompressibility() };
            else {
                auto result = -density() * derivative<Of<V>, Wrt<P>, AtConst<T>>(*this);
                return Kappa { result };
            }
        }

        /**
         * @brief Retrieves the thermal expansion coefficient (Alpha) of the fluid.
         * @details If not directly available, calculates based on the thermodynamic properties.
         * @return The thermal expansion coefficient.
         */
        [[nodiscard]]
        Alpha thermalExpansion() const
        {
            if constexpr (detail::HasThermalExpansion<IMPL_T>)
                return Alpha { m_impl.thermalExpansion() };
            else {
                auto result = density() * derivative<Of<V>, Wrt<T>, AtConst<P>>(*this);
                return Alpha { result };
            }
        }

        /**
         * @brief Retrieves the saturation temperature of the fluid for its current pressure.
         * @details Returns NaN if the current state is above the critical pressure.
         * @return The saturation temperature, or NaN if not applicable.
         */
        [[nodiscard]]
        T saturationTemperature() const
        {
            if constexpr (detail::HasSatT<IMPL_T>)
                return T { m_impl.saturationTemperature() };
            else {
                if (m_impl.pressure() > m_impl.criticalPressure()) return T { std::nan("") };
                IMPL_T fluid = m_impl;
                fluid.setStatePX(P { m_impl.pressure() }, X { 0.5 });
                return T { fluid.temperature() };
            }
        }

        /**
         * @brief Retrieves the saturation pressure of the fluid for its current temperature.
         * @details Returns NaN if the current state is above the critical temperature.
         * @return The saturation pressure, or NaN if not applicable.
         */
        [[nodiscard]]
        P saturationPressure() const
        {
            if constexpr (detail::HasSatP<IMPL_T>)
                return P { m_impl.saturationPressure() };
            else {
                if (m_impl.temperature() > m_impl.criticalTemperature()) return P { std::nan("") };
                IMPL_T fluid = m_impl;
                fluid.setStateTX(T { m_impl.temperature() }, X { 0.5 });
                return P { fluid.pressure() };
            }
        }

        /**
         * @brief Determines the phase of the fluid based on its current state.
         * @details Determines phase using critical points and saturation properties if not directly available.
         * @return The phase of the fluid.
         */
        [[nodiscard]]
        Phase phase() const
        {
            if constexpr (detail::HasPhase<IMPL_T>)
                return m_impl.phase();
            else {
                auto p = m_impl.pressure();
                auto t = m_impl.temperature();

                if (p > m_impl.criticalPressure() && t > m_impl.criticalTemperature()) return Phase::Supercritical;
                if (p > m_impl.criticalPressure() - EPS && t > m_impl.criticalTemperature() - EPS) return Phase::Critical;

                auto satP = saturationPressure().get();
                auto satT = saturationTemperature().get();

                if (p < satP + EPS && p > satP - EPS) return Phase::TwoPhase;
                if (t < satT + EPS && t > satT - EPS) return Phase::TwoPhase;

                if (p >= satP + EPS) return Phase::Liquid;
                if (t >= satT + EPS) return Phase::Gas;

                return Phase::Unknown;
            }
        }

        [[nodiscard]]
        Eta dynamicViscosity() const
        {
            if constexpr (detail::HasDynViscosity<IMPL_T>)
                return Eta { m_impl.dynamicViscosity() };
            else {
                return Eta { std::nan("") };
            }
        }

        [[nodiscard]]
        Nu kinematicViscosity() const
        {
            if constexpr (detail::HasKinViscosity<IMPL_T>)
                return Nu { m_impl.kinematicViscosity() };
            else {
                return Nu { std::nan("") };
            }
        }

        [[nodiscard]]
        TC thermalConductivity() const
        {
            if constexpr (detail::HasThermalConductivity<IMPL_T>)
                return TC { m_impl.thermalConductivity() };
            else {
                return TC { std::nan("") };
            }
        }

        [[nodiscard]]
        PR prandtlNumber() const
        {
            if constexpr (detail::HasPrandtlNumber<IMPL_T>)
                return PR { m_impl.prandtlNumber() };
            else {
                return PR { std::nan("") };
            }
        }

        // Trivial properties

        /**
         * @brief Retrieves the critical temperature of the fluid.
         * @details The critical temperature is the temperature above which distinct liquid and gas phases do not exist.
         * @return The critical temperature of the fluid.
         */
        [[nodiscard]]
        T criticalTemperature() const
        {
            return T { m_impl.criticalTemperature() };
        }

        /**
         * @brief Retrieves the critical pressure of the fluid.
         * @details The critical pressure is the pressure above which distinct liquid and gas phases do not exist.
         * @return The critical pressure of the fluid.
         */
        [[nodiscard]]
        P criticalPressure() const
        {
            return P { m_impl.criticalPressure() };
        }

        /**
         * @brief Retrieves the minimum temperature for which the fluid's properties are defined.
         * @return The minimum temperature of the fluid.
         */
        [[nodiscard]]
        T minTemperature() const
        {
            return T { m_impl.minTemperature() };
        }

        /**
         * @brief Retrieves the maximum temperature for which the fluid's properties are defined.
         * @return The maximum temperature of the fluid.
         */
        [[nodiscard]]
        T maxTemperature() const
        {
            return T { m_impl.maxTemperature() };
        }

        /**
         * @brief Retrieves the minimum pressure for which the fluid's properties are defined.
         * @return The minimum pressure of the fluid.
         */
        [[nodiscard]]
        P minPressure() const
        {
            return P { m_impl.minPressure() };
        }

        /**
         * @brief Retrieves the maximum pressure for which the fluid's properties are defined.
         * @return The maximum pressure of the fluid.
         */
        [[nodiscard]]
        P maxPressure() const
        {
            return P { m_impl.maxPressure() };
        }

        [[nodiscard]]
        T tripleTemperature() const
        {
            return T { m_impl.tripleTemperature() };
        }

        [[nodiscard]]
        P triplePressure() const
        {
            return P { m_impl.triplePressure() };
        }
    };
}    // namespace KProps