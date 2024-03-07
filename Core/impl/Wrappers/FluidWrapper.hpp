//
// Created by kenne on 03/03/2024.
//

#pragma once

#include "../Properties/Derivatives.hpp"
#include "../Protocols/FluidProtocol.hpp"
#include "../Utils/Concepts.hpp"

namespace pcprops
{

    template<typename IMPL_T>
    class FluidWrapper : public detail::FluidProtocol<FluidWrapper<IMPL_T>>
    {
        IMPL_T m_impl;
        using BASE = detail::FluidProtocol<FluidWrapper<IMPL_T>>;
        friend BASE;

    public:
        explicit FluidWrapper(const IMPL_T& fluid) : m_impl(fluid) {}
        explicit FluidWrapper(IMPL_T&& fluid) : m_impl(std::move(fluid)) {}

        FluidWrapper(const FluidWrapper& other) = default;
        FluidWrapper(FluidWrapper&&) noexcept   = default;

        FluidWrapper& operator=(const FluidWrapper& other) = default;
        FluidWrapper& operator=(FluidWrapper&&) noexcept   = default;

        auto&       impl() { return m_impl; }
        const auto& impl() const { return m_impl; }

    private:
        void setStatePT(P pressure, T temperature) {
            if constexpr (detail::SupportsSpecPT<IMPL_T>)
                m_impl.setStatePT(pressure, temperature);
            else
                throw std::runtime_error("setStatePT not supported by this backend");
        }
        void setStatePX(P pressure, X vaporQuality) {
            if constexpr (detail::SupportsSpecPX<IMPL_T>)
                m_impl.setStatePX(pressure, vaporQuality);
            else
                throw std::runtime_error("setStatePX not supported by this backend");
        }
        void setStatePH(P pressure, H enthalpy) {
            if constexpr (detail::SupportsSpecPH<IMPL_T>)
                m_impl.setStatePH(pressure, enthalpy);
            else
                throw std::runtime_error("setStatePH not supported by this backend");
        }
        void setStatePS(P pressure, S entropy) {
            if constexpr (detail::SupportsSpecPS<IMPL_T>)
                m_impl.setStatePS(pressure, entropy);
            else
                throw std::runtime_error("setStatePS not supported by this backend");
        }
        void setStateDP(Rho density, P pressure) {
            if constexpr (detail::SupportsSpecDP<IMPL_T>)
                m_impl.setStateDP(density, pressure);
            else
                throw std::runtime_error("setStateDP not supported by this backend");
        }
        void setStateDT(Rho density, T temperature) {
            if constexpr (detail::SupportsSpecDT<IMPL_T>)
                m_impl.setStateDT(density, temperature);
            else
                throw std::runtime_error("setStateDT not supported by this backend");
        }
        void setStateDS(Rho density, S entropy) {
            if constexpr (detail::SupportsSpecDS<IMPL_T>)
                m_impl.setStateDS(density, entropy);
            else
                throw std::runtime_error("setStateDS not supported by this backend");
        }
        void setStateDH(Rho density, H enthalpy) {
            if constexpr (detail::SupportsSpecDH<IMPL_T>)
                m_impl.setStateDH(density, enthalpy);
            else
                throw std::runtime_error("setStateDH not supported by this backend");
        }
        void setStateDU(Rho density, U internalEnergy) {
            if constexpr (detail::SupportsSpecDU<IMPL_T>)
                m_impl.setStateDU(density, internalEnergy);
            else
                throw std::runtime_error("setStateDU not supported by this backend");
        }
        void setStateHS(H enthalpy, S entropy) {
            if constexpr (detail::SupportsSpecHS<IMPL_T>)
                m_impl.setStateHS(enthalpy, entropy);
            else
                throw std::runtime_error("setStateHS not supported by this backend");
        }
        void setStatePU(P pressure, U internalEnergy) {
            if constexpr (detail::SupportsSpecPU<IMPL_T>)
                m_impl.setStatePU(pressure, internalEnergy);
            else
                throw std::runtime_error("setStatePU not supported by this backend");
        }
        void setStateTS(T temperature, S entropy) {
            if constexpr (detail::SupportsSpecTS<IMPL_T>)
                m_impl.setStateTS(temperature, entropy);
            else
                throw std::runtime_error("setStateTS not supported by this backend");
        }
        void setStateTX(T temperature, X quality) {
            if constexpr (detail::SupportsSpecTX<IMPL_T>)
                m_impl.setStateTX(temperature, quality);
            else
                throw std::runtime_error("setStateTX not supported by this backend");
        }

        // Required properties
        [[nodiscard]]
        MW molarMass() const
        {
            return MW { m_impl.molarMass() };
        }
        [[nodiscard]]
        T temperature() const
        {
            return T { m_impl.temperature() };
        }
        [[nodiscard]]
        P pressure() const
        {
            return P { m_impl.pressure() };
        }
        [[nodiscard]]
        X vaporQuality() const
        {
            return X { m_impl.vaporQuality() };
        }
        [[nodiscard]]
        H enthalpy() const
        {
            return H { m_impl.enthalpy() };
        }
        [[nodiscard]]
        S entropy() const
        {
            return S { m_impl.entropy() };
        }
        [[nodiscard]]
        Rho density() const
        {
            return Rho { m_impl.density() };
        }
        [[nodiscard]]
        U internalEnergy() const
        {
            return U { m_impl.internalEnergy() };
        }

        // Derived properties
        [[nodiscard]]
        V volume() const
        {
            if constexpr (detail::HasVolume<IMPL_T>)
                return V { m_impl.volume() };
            else
                return V { 1.0 / density() };
        }
        [[nodiscard]]
        G gibbsEnergy() const
        {
            if constexpr (detail::HasGibbsEnergy<IMPL_T>)
                return G { m_impl.gibbsEnergy() };
            else
                return G { m_impl.enthalpy() - m_impl.temperature() * m_impl.entropy() };
        }
        [[nodiscard]]
        A helmholtzEnergy() const
        {
            if constexpr (detail::HasHelmholtzEnergy<IMPL_T>)
                return A { m_impl.helmholtzEnergy() };
            else
                return A { m_impl.internalEnergy() - m_impl.temperature() * m_impl.entropy() };
        }
        [[nodiscard]]
        Z compressibility() const
        {
            if constexpr (detail::HasZ<IMPL_T>)
                return Z { m_impl.compressibility() };
            else
                return Z { m_impl.pressure() / (m_impl.density() * m_impl.temperature() * R) };
        }

        // Optional properties
        [[nodiscard]]
        Cp cp() const
        {
            if constexpr (detail::HasCp<IMPL_T>)
                return Cp { m_impl.cp() };
            else
                return Cp { derivative<Of<H>, Wrt<T>, AtConst<P>>(*this) };
        }
        [[nodiscard]]
        Cv cv() const
        {
            if constexpr (detail::HasCv<IMPL_T>)
                return Cv { m_impl.cv() };
            else
                return Cv { derivative<Of<U>, Wrt<T>, AtConst<V>>(*this) };
        }
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
        [[nodiscard]]
        T saturationTemperature() const
        {
            if constexpr (detail::HasSatT<IMPL_T>)
                return T { m_impl.saturationTemperature() };
            else {
                if (m_impl.pressure() > m_impl.criticalPressure()) return T {std::nan("")};
                IMPL_T fluid = m_impl;
                fluid.setStatePX(P { m_impl.pressure() }, X { 0.5 });
                return T { fluid.temperature() };
            }
        }
        [[nodiscard]]
        P saturationPressure() const
        {
            if constexpr (detail::HasSatP<IMPL_T>)
                return P { m_impl.saturationPressure() };
            else {
                if (m_impl.temperature() > m_impl.criticalTemperature()) return P {std::nan("")};
                IMPL_T fluid = m_impl;
                fluid.setStateTX(T { m_impl.temperature() }, X { 0.5 });
                return P { fluid.pressure() };
            }
        }
        [[nodiscard]]
        Phase phase_impl() const
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

        // Trivial properties
        [[nodiscard]]
        T criticalTemperature() const
        {
            return T { m_impl.criticalTemperature() };
        }
        [[nodiscard]]
        P criticalPressure() const
        {
            return P { m_impl.criticalPressure() };
        }
        [[nodiscard]]
        T minTemperature() const
        {
            return T { m_impl.minTemperature() };
        }
        [[nodiscard]]
        T maxTemperature() const
        {
            return T { m_impl.maxTemperature() };
        }
        [[nodiscard]]
        P minPressure() const
        {
            return P { m_impl.minPressure() };
        }
        [[nodiscard]]
        P maxPressure() const
        {
            return P { m_impl.maxPressure() };
        }


    };
}    // namespace pcprops