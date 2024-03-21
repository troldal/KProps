//
// Created by kenne on 16/02/2024.
//

#pragma once

#include <KPropsUtils.hpp>

#include <memory>

namespace KProps
{

    class HEOS
    {
        struct impl;
        std::unique_ptr<impl> m_impl;
    public:

        // The setState functions (required)
        void setStatePT(P pressure, T temperature);
        void setStatePX(P pressure, X quality);
        void setStatePH(P pressure, H enthalpy);
        void setStatePS(P pressure, S entropy);
        void setStateDP(Rho density, P pressure);
        void setStateDT(Rho density, T temperature);
        void setStateDS(Rho density, S entropy);
        void setStateDH(Rho density, H enthalpy);
        void setStateDU(Rho density, U internalEnergy);
        void setStateHS(H enthalpy, S entropy);
        void setStatePU(P pressure, U internalEnergy);
        void setStateTS(T temperature, S entropy);
        void setStateTX(T temperature, X quality);

        // Trivial properties (required)
        [[nodiscard]] double molarMass() const;
        [[nodiscard]] double criticalPressure() const;
        [[nodiscard]] double criticalTemperature() const;
        [[nodiscard]] double minTemperature() const;
        [[nodiscard]] double minPressure() const;
        [[nodiscard]] double maxTemperature() const;
        [[nodiscard]] double maxPressure() const;

        // Required property functions
        [[nodiscard]] double temperature() const;
        [[nodiscard]] double pressure() const;
        [[nodiscard]] double vaporQuality() const;
        [[nodiscard]] double enthalpy() const;
        [[nodiscard]] double entropy() const;
        [[nodiscard]] double density() const;
        [[nodiscard]] double internalEnergy() const;

        // Derived properties
        [[nodiscard]] double volume() const;
        [[nodiscard]] double gibbsEnergy() const;
        [[nodiscard]] double helmholtzEnergy() const;
        [[nodiscard]] double compressibility() const;

        // Optional properties
        [[nodiscard]] double cp() const;
        [[nodiscard]] double cv() const;
        [[nodiscard]] double speedOfSound() const;
        [[nodiscard]] double isothermalCompressibility() const;
        [[nodiscard]] double thermalExpansion() const;
        [[nodiscard]] double saturationTemperature() const;
        [[nodiscard]] double saturationPressure() const;
        [[nodiscard]] Phase phase() const;

        explicit HEOS(const std::string& fluidName);

//        template<typename S1, typename S2>
//            requires IsSpecificationPT<S1, S2> || IsSpecificationPX<S1, S2> || IsSpecificationPH<S1, S2>
//        CoolPropBackend(const std::string& fluidName, S1 state1, S2 state2) : CoolPropBackend(fluidName)
//        {
//            auto spec = std::make_pair(state1, state2);
//
//            if constexpr (IsSpecificationPT<S1, S2>)
//                setStatePT(std::get<P>(spec), std::get<T>(spec));
//            else if constexpr (IsSpecificationPX<S1, S2>)
//                setStatePX(std::get<P>(spec), std::get<X>(spec));
//            else if constexpr (IsSpecificationPH<S1, S2>)
//                setStatePH(std::get<P>(spec), std::get<H>(spec));
//            else if constexpr (IsSpecificationPD<S1, S2>)
//                setStateDP(std::get<Rho>(spec), std::get<P>(spec));
//            else if constexpr (IsSpecificationTD<S1, S2>)
//                setStateDT(std::get<Rho>(spec), std::get<T>(spec));
//        }

        HEOS(const HEOS& other);
        HEOS(HEOS&& other) noexcept;
        ~HEOS();
    };
}    // namespace pcprops
