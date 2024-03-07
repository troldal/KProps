//
// Created by kenne on 06/03/2024.
//

#include "../HEOS.hpp"

#include <AbstractState.h>
#include <CoolProp.h>

namespace pcprops
{

    struct HEOS::impl
    {
        enum class Specification { None, PT, PH, PS, PX, DP, DT, DS, DH, DU, HS, PU, TS, TX };

        std::unique_ptr<CoolProp::AbstractState> m_state { nullptr };
        std::string                              m_fluidName {};
        Specification                            m_spec { Specification::None };

        template<IsProperty S1, IsProperty S2>
        void setState(S1 state1, S2 state2)
        {
            auto spec = std::make_pair(state1, state2);

            m_state->clear();
            m_state.reset(CoolProp::AbstractState::factory("HEOS", m_fluidName));

            // TODO: Consider special case for critical point

            if constexpr (IsSpecificationPT<S1, S2>) {
                m_state->update(CoolProp::PT_INPUTS, std::get<P>(spec), std::get<T>(spec));
                m_spec = Specification::PT;
            }

            else if constexpr (IsSpecificationPX<S1, S2>) {
                m_state->update(CoolProp::PQ_INPUTS, std::get<P>(spec), std::get<X>(spec));
                m_spec = Specification::PX;
            }

            else if constexpr (IsSpecificationPH<S1, S2>) {
                m_state->update(CoolProp::HmolarP_INPUTS, std::get<H>(spec), std::get<P>(spec));
                m_spec = Specification::PH;
            }

            else if constexpr (IsSpecificationPS<S1, S2>) {
                m_state->update(CoolProp::PSmolar_INPUTS, std::get<P>(spec), std::get<S>(spec));
                m_spec = Specification::PS;
            }

            else if constexpr (IsSpecificationPD<S1, S2>) {
                m_state->update(CoolProp::DmolarP_INPUTS, std::get<Rho>(spec), std::get<P>(spec));
                m_spec = Specification::DP;
            }

            else if constexpr (IsSpecificationTD<S1, S2>) {
                m_state->update(CoolProp::DmolarT_INPUTS, std::get<Rho>(spec), std::get<T>(spec));
                m_spec = Specification::DT;
            }

            else if constexpr (IsSpecificationDS<S1, S2>) {
                m_state->update(CoolProp::DmolarSmolar_INPUTS, std::get<Rho>(spec), std::get<S>(spec));
                m_spec = Specification::DS;
            }

            else if constexpr (IsSpecificationDH<S1, S2>) {
                m_state->update(CoolProp::DmolarHmolar_INPUTS, std::get<Rho>(spec), std::get<H>(spec));
                m_spec = Specification::DH;
            }

            else if constexpr (IsSpecificationDU<S1, S2>) {
                m_state->update(CoolProp::DmolarUmolar_INPUTS, std::get<Rho>(spec), std::get<U>(spec));
                m_spec = Specification::DU;
            }

            else if constexpr (IsSpecificationHS<S1, S2>) {
                m_state->update(CoolProp::HmolarSmolar_INPUTS, std::get<H>(spec), std::get<S>(spec));
                m_spec = Specification::HS;
            }

            else if constexpr (IsSpecificationPU<S1, S2>) {
                m_state->update(CoolProp::PUmolar_INPUTS, std::get<P>(spec), std::get<U>(spec));
                m_spec = Specification::PU;
            }

            else if constexpr (IsSpecificationTS<S1, S2>) {
                m_state->update(CoolProp::SmolarT_INPUTS, std::get<S>(spec), std::get<T>(spec));
                m_spec = Specification::TS;
            }

            else if constexpr (IsSpecificationTX<S1, S2>) {
                m_state->update(CoolProp::QT_INPUTS, std::get<X>(spec), std::get<T>(spec));
                m_spec = Specification::TX;
            }
            else
                []<bool flag = false> { static_assert(flag, "Invalid specification pair."); }();
        }

        double twoPhaseProperty(auto func) const
        {
            auto q = vaporQuality();
            auto p = pressure();

            m_state->update(CoolProp::PQ_INPUTS, p, 0.0);
            auto valL = func();

            m_state->update(CoolProp::PQ_INPUTS, p, 1.0);
            auto valV = func();

            m_state->update(CoolProp::PQ_INPUTS, p, q);

            return valL + q * (valV - valL);
        }

    public:
        // The setState functions (required)
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
        void setStateTX(T temperature, X quality) { setState(temperature, quality); }

        // Trivial properties (required)
        double molarMass() const { return m_state->molar_mass(); }
        double criticalPressure() const { return m_state->p_critical(); }
        double criticalTemperature() const { return m_state->T_critical(); }
        double minTemperature() const { return m_state->Tmin(); }
        double minPressure() const { return m_state->p_triple(); }
        double maxTemperature() const { return m_state->Tmax(); }
        double maxPressure() const { return m_state->pmax(); }

        // Required property functions
        double temperature() const { return m_state->T(); }
        double pressure() const { return m_state->p(); }
        double vaporQuality() const
        {
            if (m_state->phase() == CoolProp::iphase_gas) return 1.0;
            if (m_state->phase() == CoolProp::iphase_liquid) return 0.0;
            return std::clamp(m_state->Q(), 0.0, 1.0);
        }
        double enthalpy() const
        {
            if (m_state->phase() != CoolProp::iphase_twophase) return m_state->hmolar();
            return twoPhaseProperty([&] { return m_state->hmolar(); });
        }
        double entropy() const
        {
            if (m_state->phase() != CoolProp::iphase_twophase) return m_state->smolar();
            return twoPhaseProperty([&] { return m_state->smolar(); });
        }
        double density() const
        {
            if (m_state->phase() != CoolProp::iphase_twophase) return m_state->rhomolar();
            return 1.0 / twoPhaseProperty([&] { return 1.0 / m_state->rhomolar(); });
        }
        double internalEnergy() const
        {
            if (m_state->phase() != CoolProp::iphase_twophase) return m_state->umolar();
            return twoPhaseProperty([&] { return m_state->umolar(); });
        }

        // Derived properties
        double volume() const { return 1.0 / density(); }
        double gibbsEnergy() const { return m_state->gibbsmolar(); }
        double helmholtzEnergy() const { return m_state->helmholtzmolar(); }
        double compressibility() const { return m_state->compressibility_factor(); }

        // Optional properties
        double cp() const
        {
            if (m_state->phase() != CoolProp::iphase_twophase) return m_state->cpmolar();

            auto fluid = *this;

            fluid.setStatePX(P { pressure() }, X { 0.0 });
            auto cpL = fluid.m_state->cpmolar();

            fluid.setStatePX(P { pressure() }, X { 1.0 });
            auto cpV = fluid.m_state->cpmolar();

            return cpV * vaporQuality() + cpL * (1 - vaporQuality());
        }
        double cv() const
        {
            if (m_state->phase() != CoolProp::iphase_twophase) return m_state->cvmolar();

            auto fluid = *this;

            fluid.setStatePX(P { pressure() }, X { 0.0 });
            auto cvL = fluid.m_state->cvmolar();

            fluid.setStatePX(P { pressure() }, X { 1.0 });
            auto cvV = fluid.m_state->cvmolar();

            return cvV * vaporQuality() + cvL * (1 - vaporQuality());
        }
        double speedOfSound() const { return m_state->speed_sound(); }
        double isothermalCompressibility() const { return m_state->isothermal_compressibility(); }
        double thermalExpansion() const { return m_state->isobaric_expansion_coefficient(); }
        double saturationTemperature() const
        {
            auto fluid = *this;
            fluid.setStatePX(P { pressure() }, X { 0.0 });
            return fluid.temperature();
        }
        double saturationPressure() const
        {
            auto fluid = *this;
            fluid.setStateTX(T { temperature() }, X { 0.0 });
            return fluid.pressure();
        }
        Phase phase() const
        {
            switch (m_state->phase()) {
                case CoolProp::iphase_liquid:
                case CoolProp::iphase_supercritical_liquid:
                    return Phase::Liquid;
                case CoolProp::iphase_gas:
                case CoolProp::iphase_supercritical_gas:
                    return Phase::Gas;
                case CoolProp::iphase_twophase:
                    return Phase::TwoPhase;
                case CoolProp::iphase_critical_point:
                    return Phase::Critical;
                case CoolProp::iphase_supercritical:
                    return Phase::Supercritical;
                default:
                    return Phase::Unknown;
            }
        }

        explicit impl(const std::string& fluidName)
            : m_state(CoolProp::AbstractState::factory("HEOS", fluidName)),
              m_fluidName(fluidName),
              m_spec(Specification::None)
        {}

        template<typename S1, typename S2>
            requires IsSpecificationPT<S1, S2> || IsSpecificationPX<S1, S2> || IsSpecificationPH<S1, S2>
        impl(const std::string& fluidName, S1 state1, S2 state2) : impl(fluidName)
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

        ~impl() = default;

        impl(const impl& other) : impl(other.m_fluidName)
        {
            switch (other.m_spec) {
                case Specification::PT:
                    setState(P { other.pressure() }, T { other.temperature() });
                    break;
                case Specification::PX:
                    setState(P { other.pressure() }, X { other.vaporQuality() });
                    break;
                case Specification::PH:
                    setState(P { other.pressure() }, H { other.enthalpy() });
                    break;
                case Specification::PS:
                    setState(P { other.pressure() }, S { other.entropy() });
                    break;
                case Specification::DP:
                    setState(Rho { other.density() }, P { other.pressure() });
                    break;
                case Specification::DT:
                    setState(Rho { other.density() }, T { other.temperature() });
                    break;
                case Specification::DS:
                    setState(Rho { other.density() }, S { other.entropy() });
                    break;
                case Specification::DH:
                    setState(Rho { other.density() }, H { other.enthalpy() });
                    break;
                case Specification::DU:
                    setState(Rho { other.density() }, U { other.internalEnergy() });
                    break;
                case Specification::HS:
                    setState(H { other.enthalpy() }, S { other.entropy() });
                    break;
                case Specification::PU:
                    setState(P { other.pressure() }, U { other.internalEnergy() });
                    break;
                case Specification::TS:
                    setState(T { other.temperature() }, S { other.entropy() });
                    break;
                case Specification::TX:
                    setState(T { other.temperature() }, X { other.vaporQuality() });
                    break;
                default:
                    break;
            }
        }

        impl(impl&& other) noexcept = default;
    };

    void   HEOS::setStatePT(P pressure, T temperature) { m_impl->setStatePT(pressure, temperature); }
    void   HEOS::setStatePX(P pressure, X quality) { m_impl->setStatePX(pressure, quality); }
    void   HEOS::setStatePH(P pressure, H enthalpy) { m_impl->setStatePH(pressure, enthalpy); }
    void   HEOS::setStatePS(P pressure, S entropy) { m_impl->setStatePS(pressure, entropy); }
    void   HEOS::setStateDP(Rho density, P pressure) { m_impl->setStateDP(density, pressure); }
    void   HEOS::setStateDT(Rho density, T temperature) { m_impl->setStateDT(density, temperature); }
    void   HEOS::setStateDS(Rho density, S entropy) { m_impl->setStateDS(density, entropy); }
    void   HEOS::setStateDH(Rho density, H enthalpy) { m_impl->setStateDH(density, enthalpy); }
    void   HEOS::setStateDU(Rho density, U internalEnergy) { m_impl->setStateDU(density, internalEnergy); }
    void   HEOS::setStateHS(H enthalpy, S entropy) { m_impl->setStateHS(enthalpy, entropy); }
    void   HEOS::setStatePU(P pressure, U internalEnergy) { m_impl->setStatePU(pressure, internalEnergy);}
    void   HEOS::setStateTS(T temperature, S entropy) { m_impl->setStateTS(temperature, entropy); }
    void   HEOS::setStateTX(T temperature, X quality) { m_impl->setStateTX(temperature, quality); }

    double HEOS::molarMass() const { return m_impl->molarMass(); }
    double HEOS::criticalPressure() const { return m_impl->criticalPressure(); }
    double HEOS::criticalTemperature() const { return m_impl->criticalTemperature(); }
    double HEOS::minTemperature() const { return m_impl->minTemperature(); }
    double HEOS::minPressure() const { return m_impl->minPressure(); }
    double HEOS::maxTemperature() const { return m_impl->maxTemperature(); }
    double HEOS::maxPressure() const { return m_impl->maxPressure();}
    double HEOS::temperature() const { return m_impl->temperature(); }
    double HEOS::pressure() const { return m_impl->pressure();}
    double HEOS::vaporQuality() const { return m_impl->vaporQuality(); }
    double HEOS::enthalpy() const { return m_impl->enthalpy(); }
    double HEOS::entropy() const { return m_impl->entropy(); }
    double HEOS::density() const { return m_impl->density(); }
    double HEOS::internalEnergy() const { return m_impl->internalEnergy();}
    double HEOS::volume() const { return m_impl->volume(); }
    double HEOS::gibbsEnergy() const { return m_impl->gibbsEnergy(); }
    double HEOS::helmholtzEnergy() const { return m_impl->helmholtzEnergy(); }
    double HEOS::compressibility() const { return m_impl->compressibility(); }
    double HEOS::cp() const { return m_impl->cp(); }
    double HEOS::cv() const { return m_impl->cv(); }
    double HEOS::speedOfSound() const { return m_impl->speedOfSound(); }
    double HEOS::isothermalCompressibility() const { return m_impl->isothermalCompressibility();}
    double HEOS::thermalExpansion() const { return m_impl->thermalExpansion();}
    double HEOS::saturationTemperature() const { return m_impl->saturationTemperature(); }
    double HEOS::saturationPressure() const { return m_impl->saturationPressure();}
    Phase  HEOS::phase() const { return m_impl->phase(); }

    HEOS::HEOS(const std::string& fluidName) : m_impl {std::make_unique<impl>(fluidName)} {}
    HEOS::HEOS(const HEOS& other) : m_impl(std::make_unique<impl>(*other.m_impl)) {}
    HEOS::HEOS(HEOS&& other) noexcept = default;
    HEOS::~HEOS() = default;

}    // namespace pcprops