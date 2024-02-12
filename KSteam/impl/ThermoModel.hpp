//
// Created by kenne on 06/02/2024.
//

#pragma once

#include ".utils/Properties.hpp"

namespace KSteam
{

    template<template<typename> class MODEL_T, typename FLOAT_T = FLOAT>
    class ThermoModel
    {
        MODEL_T<FLOAT_T> m_model;

    public:
         ThermoModel() = default;
        ~ThermoModel() = default;

        template<IsProperty PROPERTY_T>
            requires std::same_as<PROPERTY_T, PCrit> || std::same_as<PROPERTY_T, TCrit>
        auto property() const
        {
            if constexpr (std::same_as<PROPERTY_T, PCrit>)
                return PROPERTY_T { m_model.criticalPressure() };
            else
                return PROPERTY_T { m_model.criticalTemperature() };
        }


        template<IsProperty PROPERTY_T>
            requires std::same_as<PROPERTY_T, TSat>
        auto property(P pressure) const
        {
            return PROPERTY_T { m_model.saturationTemperatureAtP(pressure) };
        }

        template<IsProperty PROPERTY_T>
            requires std::same_as<PROPERTY_T, PSat>
        auto property(T temperature) const
        {
            return PROPERTY_T { m_model.saturationPressureAtT(temperature) };
        }

        template<IsProperty PROPERTY_T>
            requires std::same_as<PROPERTY_T, H> || std::same_as<PROPERTY_T, S> || std::same_as<PROPERTY_T, Rho> ||
                     std::same_as<PROPERTY_T, U> || std::same_as<PROPERTY_T, Cp> || std::same_as<PROPERTY_T, Cv> ||
                     std::same_as<PROPERTY_T, W>
        auto property(P pressure, T temperature) const
        {
            if constexpr (std::same_as<PROPERTY_T, H>)
                return PROPERTY_T { m_model.enthalpyAtPT(pressure, temperature) };
            else if constexpr (std::same_as<PROPERTY_T, S>)
                return PROPERTY_T { m_model.entropyAtPT(pressure, temperature) };
            else if constexpr (std::same_as<PROPERTY_T, Rho>)
                return PROPERTY_T { m_model.densityAtPT(pressure, temperature) };
            else if constexpr (std::same_as<PROPERTY_T, U>)
                return PROPERTY_T { m_model.internalEnergyAtPT(pressure, temperature) };
            else if constexpr (std::same_as<PROPERTY_T, Cp>)
                return PROPERTY_T { m_model.cpAtPT(pressure, temperature) };
            else if constexpr (std::same_as<PROPERTY_T, Cv>)
                return PROPERTY_T { m_model.cvAtPT(pressure, temperature) };
            else if constexpr (std::same_as<PROPERTY_T, W>)
                return PROPERTY_T { m_model.omegaAtPT(pressure, temperature) };
        }

        template<IsProperty PROPERTY_T>
            requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, H> || std::same_as<PROPERTY_T, S> ||
                     std::same_as<PROPERTY_T, Rho> || std::same_as<PROPERTY_T, U> || std::same_as<PROPERTY_T, Cp> ||
                     std::same_as<PROPERTY_T, Cv> || std::same_as<PROPERTY_T, W>
        auto property(P pressure, X VaporFraction) const
        {
            if constexpr (std::same_as<PROPERTY_T, T>) return PROPERTY_T { property<TSat>(pressure) };
            if constexpr (std::same_as<PROPERTY_T, H>)
                return PROPERTY_T { m_model.vaporEnthalpyAtPSat(pressure) * VaporFraction +
                                    m_model.liquidEnthalpyAtPSat(pressure) * (1 - VaporFraction) };
            else if constexpr (std::same_as<PROPERTY_T, S>)
                return PROPERTY_T { m_model.vaporEntropyAtPSat(pressure) * VaporFraction +
                                    m_model.liquidEntropyAtPSat(pressure) * (1 - VaporFraction) };
            else if constexpr (std::same_as<PROPERTY_T, Rho>)
                return PROPERTY_T { m_model.vaporDensityAtPSat(pressure) * VaporFraction +
                                    m_model.liquidDensityAtPSat(pressure) * (1 - VaporFraction) };
            else if constexpr (std::same_as<PROPERTY_T, U>)
                return PROPERTY_T { m_model.vaporInternalEnergyAtPSat(pressure) * VaporFraction +
                                    m_model.liquidInternalEnergyAtPSat(pressure) * (1 - VaporFraction) };
            else if constexpr (std::same_as<PROPERTY_T, Cp>)
                return PROPERTY_T { m_model.vaporCpAtPSat(pressure) * VaporFraction +
                                    m_model.liquidCpAtPSat(pressure) * (1 - VaporFraction) };
            else if constexpr (std::same_as<PROPERTY_T, Cv>)
                return PROPERTY_T { m_model.vaporCvAtPSat(pressure) * VaporFraction +
                                    m_model.liquidCvAtPSat(pressure) * (1 - VaporFraction) };
            else if constexpr (std::same_as<PROPERTY_T, W>)
                return PROPERTY_T { m_model.vaporOmegaAtPSat(pressure) * VaporFraction +
                                    m_model.liquidOmegaAtPSat(pressure) * (1 - VaporFraction) };
        }

        template<IsProperty PROPERTY_T, IsProperty SPEC1, IsProperty SPEC2>
            requires(std::same_as<PROPERTY_T, P> || std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, Rho>) &&
                    (IsSpecificationPH<SPEC1, SPEC2> || IsSpecificationPS<SPEC1, SPEC2> || IsSpecificationHS<SPEC1, SPEC2>)
        auto guess(SPEC1 s1, SPEC2 s2) const
        {
            auto specification = std::make_pair(s1, s2);

            if constexpr (IsSpecificationPH<SPEC1, SPEC2>) {
                if constexpr (std::same_as<PROPERTY_T, T>) {
                    return PROPERTY_T { m_model.temperatureGuessAtPH(std::get<P>(specification), std::get<H>(specification)) };
                }
                else if constexpr (std::same_as<PROPERTY_T, Rho>) {
                    return PROPERTY_T { m_model.densityGuessAtPH(std::get<P>(specification), std::get<H>(specification)) };
                }
                else {
                    return std::get<P>(specification);
                }
            }
            else if constexpr (IsSpecificationPS<SPEC1, SPEC2>) {
                if constexpr (std::same_as<PROPERTY_T, T>) {
                    return PROPERTY_T { m_model.temperatureGuessAtPS(std::get<P>(specification), std::get<S>(specification)) };
                }
                else if constexpr (std::same_as<PROPERTY_T, Rho>) {
                    return PROPERTY_T { m_model.densityGuessAtPS(std::get<P>(specification), std::get<S>(specification)) };
                }
                else {
                    return std::get<P>(specification);
                }
            }
            else if constexpr (IsSpecificationHS<SPEC1, SPEC2>) {
                if constexpr (std::same_as<PROPERTY_T, T>) {
                    return PROPERTY_T { m_model.temperatureGuessAtHS(std::get<H>(specification), std::get<S>(specification)) };
                }
                else if constexpr (std::same_as<PROPERTY_T, P>) {
                    return PROPERTY_T { m_model.pressureGuessAtHS(std::get<H>(specification), std::get<S>(specification)) };
                }
                else {
                    return PROPERTY_T { m_model.densityGuessAtPS(
                        m_model.pressureGuessAtHS(std::get<H>(specification), std::get<S>(specification)),
                        std::get<S>(specification)) };
                }
            }
        }

        template<IsProperty PROPERTY_T>
            requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
        auto min() const
        {
            if constexpr (std::same_as<PROPERTY_T, T>)
                return PROPERTY_T { m_model.minTemperature() };
            else
                return PROPERTY_T { m_model.minPressure() };
        }

        template<IsProperty PROPERTY_T>
            requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
        auto max() const
        {
            if constexpr (std::same_as<PROPERTY_T, T>)
                return PROPERTY_T { m_model.maxTemperature() };
            else
                return PROPERTY_T { m_model.maxPressure() };
        }
    };

}    // namespace KSteam