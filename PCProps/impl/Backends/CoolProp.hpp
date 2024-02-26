//
// Created by kenne on 16/02/2024.
//

#pragma once

#include <AbstractState.h>
#include <CoolProp.h>
#include <memory>

namespace pcprops
{

    class CoolPropBackend
    {
        std::unique_ptr<CoolProp::AbstractState> m_state { nullptr };


        // void setState(CoolProp::input_pairs inputPair, double value1, double value2)
        // {
        //     m_state->clear();
        //     m_state.reset(CoolProp::AbstractState::factory("HEOS", m_state->fluid_names().front()));
        //     m_state->update(inputPair, value1, value2);
        // }

        template<IsProperty S1, IsProperty S2>
        void setState(S1 state1, S2 state2)
        {
            auto spec = std::make_pair(state1, state2);

            m_state->clear();
            m_state.reset(CoolProp::AbstractState::factory("HEOS", m_state->fluid_names().front()));

            if constexpr (IsSpecificationPT<S1, S2>)
                m_state->update(CoolProp::PT_INPUTS, std::get<P>(spec), std::get<T>(spec));
            else if constexpr (IsSpecificationPX<S1, S2>)
                m_state->update(CoolProp::PQ_INPUTS, std::get<P>(spec), std::get<X>(spec));
            else if constexpr (IsSpecificationPH<S1, S2>)
                m_state->update(CoolProp::HmolarP_INPUTS, std::get<H>(spec), std::get<P>(spec));
            else if constexpr (IsSpecificationPS<S1, S2>)
                m_state->update(CoolProp::PSmolar_INPUTS, std::get<P>(spec), std::get<S>(spec));
            else if constexpr (IsSpecificationPD<S1, S2>)
                m_state->update(CoolProp::DmolarP_INPUTS, std::get<Rho>(spec), std::get<P>(spec));
            else if constexpr (IsSpecificationTD<S1, S2>)
                m_state->update(CoolProp::DmolarT_INPUTS, std::get<Rho>(spec), std::get<T>(spec));
            else if constexpr (IsSpecificationDS<S1, S2>)
                m_state->update(CoolProp::DmolarSmolar_INPUTS, std::get<Rho>(spec), std::get<S>(spec));
            else if constexpr (IsSpecificationDH<S1, S2>)
                m_state->update(CoolProp::DmolarHmolar_INPUTS, std::get<Rho>(spec), std::get<H>(spec));
            else if constexpr (IsSpecificationDU<S1, S2>)
                m_state->update(CoolProp::DmolarUmolar_INPUTS, std::get<Rho>(spec), std::get<U>(spec));
            else if constexpr (IsSpecificationHS<S1, S2>)
                m_state->update(CoolProp::HmolarSmolar_INPUTS, std::get<H>(spec), std::get<S>(spec));
            else if constexpr (IsSpecificationPU<S1, S2>)
                m_state->update(CoolProp::PUmolar_INPUTS, std::get<P>(spec), std::get<U>(spec));
            else if constexpr (IsSpecificationTS<S1, S2>)
                m_state->update(CoolProp::SmolarT_INPUTS, std::get<S>(spec), std::get<T>(spec));
            else
                []<bool flag = false> { static_assert(flag, "Invalid specification pair."); }();
        }

    public:
        void setStatePT(P pressure, T temperature) { setState(pressure, temperature); }
        void setStatePX(P pressure, X quality) { setState(pressure, quality); }
        void setStatePH(P pressure, H enthalpy) { setState(enthalpy, pressure); }
        void setStatePS(P pressure, S entropy) { setState(pressure, entropy); }
        void setStateDP(Rho density, P pressure) { setState(density, pressure); }
        void setStateDT(Rho density, T temperature) { setState(density, temperature); }
        void setStateDS(Rho density, S entropy) { setState(density, entropy); }
        void setStateDH(Rho density, H enthalpy) { setState(density, enthalpy); }
        void setStateDU(Rho density, U internalEnergy) { setState(density, internalEnergy); }
        void setStateHS(H enthalpy, S entropy) { setState(enthalpy, entropy); }
        void setStatePU(P pressure, U internalEnergy) { setState(pressure, internalEnergy); }
        void setStateTS(T temperature, S entropy) { setState(temperature, entropy); }


        auto molarMass() const { return m_state->molar_mass(); }

        auto criticalPressure() const { return m_state->p_critical(); }
        auto criticalTemperature() const { return m_state->T_critical(); }
        auto temperature() const { return m_state->T(); }
        auto pressure() const { return m_state->p(); }
        auto speedOfSound() const { return m_state->speed_sound(); }
        auto vaporQuality() const { return m_state->Q(); }
        auto minTemperature() const { return m_state->Tmin(); }
        auto minPressure() const { return m_state->p_triple(); }
        auto maxTemperature() const { return m_state->Tmax(); }
        auto maxPressure() const { return m_state->pmax(); }
        auto isothermalCompressibility() const { return m_state->isothermal_compressibility(); }

        auto enthalpy() const { return m_state->hmolar(); }
        auto entropy() const { return m_state->smolar(); }
        auto density() const { return m_state->rhomolar(); }
        auto internalEnergy() const { return m_state->umolar(); }
        auto cp() const { return m_state->cpmolar(); }
        auto cv() const { return m_state->cvmolar(); }

        explicit CoolPropBackend(const std::string& fluidName) : m_state(CoolProp::AbstractState::factory("HEOS", fluidName)) {}

        template<typename S1, typename S2>
            requires IsSpecificationPT<S1, S2> || IsSpecificationPX<S1, S2> || IsSpecificationPH<S1, S2>
        CoolPropBackend(const std::string& fluidName, S1 state1, S2 state2) : CoolPropBackend(fluidName)
        {
            auto spec = std::make_pair(state1, state2);

            if constexpr (IsSpecificationPT<S1, S2>)
                setStatePT(std::get<P>(spec), std::get<T>(spec));
            else if constexpr (IsSpecificationPX<S1, S2>)
                setStatePX(std::get<P>(spec), std::get<X>(spec));
            else if constexpr (IsSpecificationPH<S1, S2>)
                setStatePH(std::get<P>(spec), std::get<H>(spec));
            else if constexpr (IsSpecificationPD<S1, S2>)
                setStateDP(std::get<Rho>(spec), std::get<P>(spec));
            else if constexpr (IsSpecificationTD<S1, S2>)
                setStateDT(std::get<Rho>(spec), std::get<T>(spec));
        }

        ~CoolPropBackend() = default;

        CoolPropBackend(const CoolPropBackend& other) : CoolPropBackend(other.m_state->fluid_names().front()) { *m_state = *other.m_state; }
    };

}    // namespace pcprops
