//
// Created by kenne on 03/03/2024.
//

#pragma once

#include "../Types/MiscTypes.hpp"
#include "../Types/PropertyTypes.hpp"

namespace pcprops::detail {

    template<typename DERIVED>
    class FluidProtocol
    {
        friend DERIVED;

        DERIVED&       derived() { return static_cast<DERIVED&>(*this); }
        const DERIVED& derived() const { return static_cast<const DERIVED&>(*this); }

    protected:
        ~FluidProtocol() = default;

    public:
        template<typename UNITS_T = MolarUnits, IsProperty P1, IsProperty P2>
            requires std::same_as<UNITS_T, MolarUnits> || std::same_as<UNITS_T, MassUnits>
        void setState(P1 p1, P2 p2)
        {
            auto spec = std::make_pair(p1, p2);
            auto const factor = std::same_as<UNITS_T, MolarUnits> ? 1.0 : derived().molarMass();

            if constexpr (IsSpecificationPT<P1, P2>)
                derived().setStatePT(std::get<P>(spec), std::get<T>(spec));
            else if constexpr (IsSpecificationPX<P1, P2>)
                derived().setStatePX(std::get<P>(spec), std::get<X>(spec));
            else if constexpr (IsSpecificationPH<P1, P2>)
                derived().setStatePH(std::get<P>(spec), H{std::get<H>(spec) * factor});
            else if constexpr (IsSpecificationPS<P1, P2>)
                derived().setStatePS(std::get<P>(spec), S{std::get<S>(spec) * factor});
            else if constexpr (IsSpecificationPD<P1, P2>)
                derived().setStateDP(Rho{std::get<Rho>(spec) / factor}, std::get<P>(spec));
            else if constexpr (IsSpecificationTD<P1, P2>)
                derived().setStateDT(Rho{std::get<Rho>(spec) / factor}, std::get<T>(spec));
            else if constexpr (IsSpecificationDS<P1, P2>)
                derived().setStateDS(Rho{std::get<Rho>(spec) / factor}, S{std::get<S>(spec) * factor});
            else if constexpr (IsSpecificationDH<P1, P2>)
                derived().setStateDH(Rho{std::get<Rho>(spec) / factor}, H{std::get<H>(spec) * factor});
            else if constexpr (IsSpecificationDU<P1, P2>)
                derived().setStateDU(Rho{std::get<Rho>(spec) / factor}, U{std::get<U>(spec) * factor});
            else if constexpr (IsSpecificationHS<P1, P2>)
                derived().setStateHS(H{std::get<H>(spec) * factor}, S{std::get<S>(spec) * factor});
            else if constexpr (IsSpecificationPU<P1, P2>)
                derived().setStatePU(std::get<P>(spec), U{std::get<U>(spec) * factor});
            else if constexpr (IsSpecificationTS<P1, P2>)
                derived().setStateTS(std::get<T>(spec), S{std::get<S>(spec) * factor});
            else if constexpr (IsSpecificationTX<P1, P2>)
                derived().setStateTX(std::get<T>(spec), std::get<X>(spec));

            // Recursive call to setState in case one of the specifications is for Volume.
            else if constexpr (std::same_as<P1, V>)
                setState<UNITS_T>(Rho{1.0 / p1.get()}, p2);
            else if constexpr (std::same_as<P2, V>)
                setState<UNITS_T>(p1, Rho{1.0 / p2.get()});
            else
                std::invoke([]<bool flag = false>() { static_assert(flag, "Invalid specification"); });
        }

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
                return PROPERTY_T { derived().density() * factor};
            else if constexpr (std::same_as<PROPERTY_T, U>)
                return PROPERTY_T { derived().internalEnergy() / factor};

                // Derived properties
            else if constexpr (std::same_as<PROPERTY_T, V>)
                return PROPERTY_T { derived().volume() / factor };
            else if constexpr (std::same_as<PROPERTY_T, G>)
                return PROPERTY_T { derived().gibbsEnergy() / factor };
            else if constexpr (std::same_as<PROPERTY_T, A>)
                return PROPERTY_T { derived().helmholtzEnergy() / factor };
            else if constexpr (std::same_as<PROPERTY_T, Z>)
                return PROPERTY_T { derived().compressibility()};

                // Optional properties
            else if constexpr (std::same_as<PROPERTY_T, Cp>)
                return PROPERTY_T { derived().cp() / factor };
            else if constexpr (std::same_as<PROPERTY_T, Cv>)
                return PROPERTY_T { derived().cv() / factor};
            else if constexpr (std::same_as<PROPERTY_T, W>)
                return PROPERTY_T { derived().speedOfSound() };
            else if constexpr (std::same_as<PROPERTY_T, Kappa>)
                return PROPERTY_T { derived().isothermalCompressibility() };
            else if constexpr (std::same_as<PROPERTY_T, Alpha>)
                return PROPERTY_T { derived().thermalExpansion() };
            else
                std::invoke([]<bool flag = false>() { static_assert(flag, "Invalid property"); });
        }

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

        Phase phase() const
        {
            return derived().phase_impl();
        }
    };


}