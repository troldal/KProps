//
// Created by kenne on 25/02/2024.
//

#pragma once

#include "../Protocols/FluidProtocol.hpp"

#include <memory>
#include <utility>

namespace pcprops
{
    // clang-format off
    class IFluid : public detail::FluidProtocol<IFluid>
    {
        using BASE = detail::FluidProtocol<IFluid>;
        friend BASE;

    public:
        template<typename IMPL>
        IFluid(IMPL fluid) : m_pimpl(std::make_unique<Model<IMPL>>(std::move(fluid))) {}

        IFluid(IFluid const& other) : m_pimpl(other.m_pimpl->clone()) {}

        IFluid& operator=(IFluid const& other)
        {
            if (this != &other) m_pimpl = other.m_pimpl->clone();
            return *this;
        }

        ~IFluid() = default;

        IFluid(IFluid&&) noexcept    = default;
        IFluid& operator=(IFluid&&) noexcept = default;

    private:
        void setStatePT(P pressure, T temperature) { m_pimpl->setStatePT(pressure, temperature); }
        void setStatePX(P pressure, X vaporQuality) { m_pimpl->setStatePX(pressure, vaporQuality); }
        void setStatePH(P pressure, H enthalpy) { m_pimpl->setStatePH(pressure, enthalpy); }
        void setStatePS(P pressure, S entropy) { m_pimpl->setStatePS(pressure, entropy); }
        void setStateDP(Rho density, P pressure) { m_pimpl->setStateDP(density, pressure); }
        void setStateDT(Rho density, T temperature) { m_pimpl->setStateDT(density, temperature); }
        void setStateDS(Rho density, S entropy) { m_pimpl->setStateDS(density, entropy); }
        void setStateDH(Rho density, H enthalpy) { m_pimpl->setStateDH(density, enthalpy); }
        void setStateDU(Rho density, U internalEnergy) { m_pimpl->setStateDU(density, internalEnergy); }
        void setStateHS(H enthalpy, S entropy) { m_pimpl->setStateHS(enthalpy, entropy); }
        void setStatePU(P pressure, U internalEnergy) { m_pimpl->setStatePU(pressure, internalEnergy); }
        void setStateTS(T temperature, S entropy) { m_pimpl->setStateTS(temperature, entropy); }
        void setStateTX(T temperature, X quality) { m_pimpl->setStateTX(temperature, quality); }

        // Required properties
        [[nodiscard]] MW    molarMass() const { return m_pimpl->molarMass(); }
        [[nodiscard]] T     temperature() const { return m_pimpl->temperature(); }
        [[nodiscard]] P     pressure() const { return m_pimpl->pressure(); }
        [[nodiscard]] X     vaporQuality() const { return m_pimpl->vaporQuality(); }
        [[nodiscard]] H     enthalpy() const { return m_pimpl->enthalpy(); }
        [[nodiscard]] S     entropy() const { return m_pimpl->entropy(); }
        [[nodiscard]] Rho   density() const { return m_pimpl->density(); }
        [[nodiscard]] U     internalEnergy() const { return m_pimpl->internalEnergy(); }

        // Derived properties
        [[nodiscard]] V     volume() const { return m_pimpl->volume(); }
        [[nodiscard]] G     gibbsEnergy() const { return m_pimpl->gibbsEnergy(); }
        [[nodiscard]] A     helmholtzEnergy() const { return m_pimpl->helmholtzEnergy(); }
        [[nodiscard]] Z    compressibility() const { return m_pimpl->compressibility(); }

        // Optional properties
        [[nodiscard]] Cp    cp() const { return m_pimpl->cp(); }
        [[nodiscard]] Cv    cv() const { return m_pimpl->cv(); }
        [[nodiscard]] W     speedOfSound() const { return m_pimpl->speedOfSound(); }
        [[nodiscard]] Kappa isothermalCompressibility() const { return m_pimpl->isothermalCompressibility(); }
        [[nodiscard]] Alpha thermalExpansion() const { return m_pimpl->thermalExpansion(); }
        [[nodiscard]] T     saturationTemperature() const { return m_pimpl->saturationTemperature(); }
        [[nodiscard]] P     saturationPressure() const { return m_pimpl->saturationPressure(); }
        [[nodiscard]] Phase phase_impl() const { return m_pimpl->phase_impl(); }

        // Trivial properties (required)
        [[nodiscard]] T criticalTemperature() const { return m_pimpl->criticalTemperature(); }
        [[nodiscard]] P criticalPressure() const { return m_pimpl->criticalPressure(); }
        [[nodiscard]] T     minTemperature() const { return m_pimpl->minTemperature(); }
        [[nodiscard]] T     maxTemperature() const { return m_pimpl->maxTemperature(); }
        [[nodiscard]] P     minPressure() const { return m_pimpl->minPressure(); }
        [[nodiscard]] P     maxPressure() const { return m_pimpl->maxPressure(); }



        struct Concept
        {
            virtual ~Concept() = default;

            virtual void setStatePT(P pressure, T temperature)     = 0;
            virtual void setStatePX(P pressure, X vaporQuality)    = 0;
            virtual void setStatePH(P pressure, H enthalpy)        = 0;
            virtual void setStatePS(P pressure, S entropy)         = 0;
            virtual void setStateDP(Rho density, P pressure)       = 0;
            virtual void setStateDT(Rho density, T temperature)    = 0;
            virtual void setStateDS(Rho density, S entropy)        = 0;
            virtual void setStateDH(Rho density, H enthalpy)       = 0;
            virtual void setStateDU(Rho density, U internalEnergy) = 0;
            virtual void setStateHS(H enthalpy, S entropy)         = 0;
            virtual void setStatePU(P pressure, U internalEnergy)  = 0;
            virtual void setStateTS(T temperature, S entropy)      = 0;
            virtual void setStateTX(T temperature, X quality)      = 0;

            // Required properties
            [[nodiscard]] virtual MW    molarMass() const                 = 0;
            [[nodiscard]] virtual T     temperature() const               = 0;
            [[nodiscard]] virtual P     pressure() const                  = 0;
            [[nodiscard]] virtual X     vaporQuality() const              = 0;
            [[nodiscard]] virtual H     enthalpy() const                  = 0;
            [[nodiscard]] virtual S     entropy() const                   = 0;
            [[nodiscard]] virtual Rho   density() const                   = 0;
            [[nodiscard]] virtual U     internalEnergy() const            = 0;

            // Derived properties
            [[nodiscard]] virtual V     volume() const                    = 0;
            [[nodiscard]] virtual G     gibbsEnergy() const               = 0;
            [[nodiscard]] virtual A     helmholtzEnergy() const           = 0;
            [[nodiscard]] virtual Z    compressibility() const            = 0;

            // Optional properties
            [[nodiscard]] virtual Cp    cp() const                        = 0;
            [[nodiscard]] virtual Cv    cv() const                        = 0;
            [[nodiscard]] virtual W     speedOfSound() const              = 0;
            [[nodiscard]] virtual Kappa isothermalCompressibility() const = 0;
            [[nodiscard]] virtual Alpha thermalExpansion() const          = 0;
            [[nodiscard]] virtual T saturationTemperature() const         = 0;
            [[nodiscard]] virtual P saturationPressure() const            = 0;
            [[nodiscard]] virtual Phase phase_impl() const                = 0;

            // Trivial properties
            [[nodiscard]] virtual T criticalTemperature() const     = 0;
            [[nodiscard]] virtual P criticalPressure() const        = 0;
            [[nodiscard]] virtual T     minTemperature() const      = 0;
            [[nodiscard]] virtual T     maxTemperature() const      = 0;
            [[nodiscard]] virtual P     minPressure() const         = 0;
            [[nodiscard]] virtual P     maxPressure() const         = 0;

            [[nodiscard]] virtual std::unique_ptr<Concept> clone() const = 0;
        };

        template<typename IMPL>
        struct Model final : Concept
        {
            IMPL m_fluid;

            explicit Model(IMPL const& fluid) : m_fluid(fluid) {}
            explicit Model(IMPL&& fluid) : m_fluid(std::move(fluid)) {}

            void setStatePT(P pressure, T temperature) override { m_fluid.setState(pressure, temperature); }
            void setStatePX(P pressure, X vaporQuality) override { m_fluid.setState(pressure, vaporQuality); }
            void setStatePH(P pressure, H enthalpy) override { m_fluid.setState(pressure, enthalpy); }
            void setStatePS(P pressure, S entropy) override { m_fluid.setState(pressure, entropy); }
            void setStateDP(Rho density, P pressure) override { m_fluid.setState(density, pressure); }
            void setStateDT(Rho density, T temperature) override { m_fluid.setState(density, temperature); }
            void setStateDS(Rho density, S entropy) override { m_fluid.setState(density, entropy); }
            void setStateDH(Rho density, H enthalpy) override { m_fluid.setState(density, enthalpy); }
            void setStateDU(Rho density, U internalEnergy) override { m_fluid.setState(density, internalEnergy); }
            void setStateHS(H enthalpy, S entropy) override { m_fluid.setState(enthalpy, entropy); }
            void setStatePU(P pressure, U internalEnergy) override { m_fluid.setState(pressure, internalEnergy); }
            void setStateTS(T temperature, S entropy) override { m_fluid.setState(temperature, entropy); }
            void setStateTX(T temperature, X quality) override { m_fluid.setState(temperature, quality); }

            // Required properties
            [[nodiscard]] MW    molarMass() const override { return m_fluid.template property<MW>(); }
            [[nodiscard]] T     temperature() const override { return m_fluid.template property<T>(); }
            [[nodiscard]] P     pressure() const override { return m_fluid.template property<P>(); }
            [[nodiscard]] X     vaporQuality() const override { return m_fluid.template property<X>(); }
            [[nodiscard]] H     enthalpy() const override { return m_fluid.template property<H>(); }
            [[nodiscard]] S     entropy() const override { return m_fluid.template property<S>(); }
            [[nodiscard]] Rho   density() const override { return m_fluid.template property<Rho>(); }
            [[nodiscard]] U     internalEnergy() const override { return m_fluid.template property<U>(); }

            // Derived properties
            [[nodiscard]] V     volume() const override { return m_fluid.template property<V>(); }
            [[nodiscard]] G     gibbsEnergy() const override { return m_fluid.template property<G>(); }
            [[nodiscard]] A     helmholtzEnergy() const override { return m_fluid.template property<A>(); }
            [[nodiscard]] Z    compressibility() const override { return m_fluid.template property<Z>(); }

            // Optional properties
            [[nodiscard]] Cp    cp() const override { return m_fluid.template property<Cp>(); }
            [[nodiscard]] Cv    cv() const override { return m_fluid.template property<Cv>(); }
            [[nodiscard]] W     speedOfSound() const override { return m_fluid.template property<W>(); }
            [[nodiscard]] Kappa isothermalCompressibility() const override { return m_fluid.template property<Kappa>(); }
            [[nodiscard]] Alpha thermalExpansion() const override { return m_fluid.template property<Alpha>(); }
            [[nodiscard]] T saturationTemperature() const override { return m_fluid.template saturation<T>(); }
            [[nodiscard]] P saturationPressure() const override { return m_fluid.template saturation<P>(); }
            [[nodiscard]] Phase phase_impl() const override { return m_fluid.phase(); }

            // Trivial properties
            [[nodiscard]] T criticalTemperature() const override { return m_fluid.template critical<T>(); }
            [[nodiscard]] P criticalPressure() const override { return m_fluid.template critical<P>(); }
            [[nodiscard]] T     minTemperature() const override { return m_fluid.template min<T>(); }
            [[nodiscard]] T     maxTemperature() const override { return m_fluid.template max<T>(); }
            [[nodiscard]] P     minPressure() const override { return m_fluid.template min<P>(); }
            [[nodiscard]] P     maxPressure() const override { return m_fluid.template max<P>(); }

            [[nodiscard]] std::unique_ptr<Concept> clone() const override { return std::make_unique<Model<IMPL>>(*this); }
        };

        std::unique_ptr<Concept> m_pimpl;
    };

    // clang-format on

    // class IFluid : public detail::FluidBase<IFluid>, public te::poly<IFluid>
    // {
    // public:
    //     using te::poly<IFluid>::poly;
    //     using BASE = detail::FluidBase<IFluid>;
    //     friend BASE;
    //
    //     // IFluid(const IFluid&) = default;
    //     // IFluid(IFluid&&)      = default;
    //     // IFluid& operator=(const IFluid&) = default;
    //     // IFluid& operator=(IFluid&&) = default;
    //
    //
    //     void setStatePT(P pressure, T temperature)
    //     {
    //         te::call([](auto& self, P p, T t) { self.setState(p, t); }, *this, pressure, temperature);
    //     }
    //
    //     void setStatePX(P pressure, X vaporQuality)
    //     {
    //         te::call([](auto& self, P p, X x) { self.setState(p, x); }, *this, pressure, vaporQuality);
    //     }
    //
    //     void setStatePH(P pressure, H enthalpy)
    //     {
    //         te::call([](auto& self, P p, H h) { self.setState(p, h); }, *this, pressure, enthalpy);
    //     }
    //
    //     void setStatePS(P pressure, S entropy)
    //     {
    //         te::call([](auto& self, P p, S s) { self.setState(p, s); }, *this, pressure, entropy);
    //     }
    //
    //     void setStateDP(Rho density, P pressure)
    //     {
    //         te::call([](auto& self, Rho rho, P p) { self.setState(rho, p); }, *this, density, pressure);
    //     }
    //
    //     void setStateDT(Rho density, T temperature)
    //     {
    //         te::call([](auto& self, Rho rho, T t) { self.setState(rho, t); }, *this, density, temperature);
    //     }
    //
    //     void setStateDS(Rho density, S entropy)
    //     {
    //         te::call([](auto& self, Rho rho, S s) { self.setState(rho, s); }, *this, density, entropy);
    //     }
    //
    //     void setStateDH(Rho density, H enthalpy)
    //     {
    //         te::call([](auto& self, Rho rho, H h) { self.setState(rho, h); }, *this, density, enthalpy);
    //     }
    //
    //     void setStateDU(Rho density, U internalEnergy)
    //     {
    //         te::call([](auto& self, Rho rho, U u) { self.setState(rho, u); }, *this, density, internalEnergy);
    //     }
    //
    //     void setStateHS(H enthalpy, S entropy)
    //     {
    //         te::call([](auto& self, H h, S s) { self.setState(h, s); }, *this, enthalpy, entropy);
    //     }
    //
    //     void setStatePU(P pressure, U internalEnergy)
    //     {
    //         te::call([](auto& self, P p, U u) { self.setState(p, u); }, *this, pressure, internalEnergy);
    //     }
    //
    //     void setStateTS(T temperature, S entropy)
    //     {
    //         te::call([](auto& self, T t, S s) { self.setState(t, s); }, *this, temperature, entropy);
    //     }
    //
    //     void setStateTX(T temperature, X quality)
    //     {
    //         te::call([](auto& self, T t, X x) { self.setState(t, x); }, *this, temperature, quality);
    //     }
    //
    //     [[nodiscard]]
    //     MW molarMass() const
    //     {
    //         return te::call<MW>([](auto const& self) { self.template property<MW>(); }, *this);
    //     }
    //     [[nodiscard]]
    //     T temperature() const
    //     {
    //         return te::call<T>([](auto const& self) { self.template property<T>(); }, *this);
    //     }
    //     [[nodiscard]]
    //     P pressure() const
    //     {
    //         return te::call<P>([](auto const& self) { self.template property<P>(); }, *this);
    //     }
    //     [[nodiscard]]
    //     H enthalpy() const
    //     {
    //         return te::call<H>([](auto const& self) { self.template property<H>(); }, *this);
    //     }
    //     [[nodiscard]]
    //     S entropy() const
    //     {
    //         return te::call<S>([](auto const& self) { self.template property<S>(); }, *this);
    //     }
    //     [[nodiscard]]
    //     Rho density() const
    //     {
    //         return te::call<Rho>([](auto const& self) { self.template property<Rho>(); }, *this);
    //     }
    //     [[nodiscard]]
    //     U internalEnergy() const
    //     {
    //         return te::call<U>([](auto const& self) { self.template property<U>(); }, *this);
    //     }
    //     [[nodiscard]]
    //     Cp cp() const
    //     {
    //         return te::call<Cp>([](auto const& self) { self.template property<Cp>(); }, *this);
    //     }
    //     [[nodiscard]]
    //     Cv cv() const
    //     {
    //         return te::call<Cv>([](auto const& self) { self.template property<Cv>(); }, *this);
    //     }
    //     [[nodiscard]]
    //     W speedOfSound() const
    //     {
    //         return te::call<W>([](auto const& self) { self.template property<W>(); }, *this);
    //     }
    //     [[nodiscard]]
    //     X vaporQuality() const
    //     {
    //         return te::call<X>([](auto const& self) { self.template property<X>(); }, *this);
    //     }
    //     [[nodiscard]]
    //     V volume() const
    //     {
    //         return te::call<V>([](auto const& self) { self.template property<V>(); }, *this);
    //     }
    //     [[nodiscard]]
    //     A helmholtzEnergy() const
    //     {
    //         return te::call<A>([](auto const& self) { self.template property<A>(); }, *this);
    //     }
    //     [[nodiscard]]
    //     G gibbsEnergy() const
    //     {
    //         return te::call<G>([](auto const& self) { self.template property<G>(); }, *this);
    //     }
    //     [[nodiscard]]
    //     Kappa isothermalCompressibility() const
    //     {
    //         return te::call<Kappa>([](auto const& self) { self.template property<Kappa>(); }, *this);
    //     }
    //
    //     [[nodiscard]]
    //     TCrit criticalTemperature() const
    //     {
    //         return te::call<TCrit>([](auto const& self) { self.template property<TCrit>(); }, *this);
    //     }
    //     [[nodiscard]]
    //     PCrit criticalPressure() const
    //     {
    //         return te::call<PCrit>([](auto const& self) { self.template property<PCrit>(); }, *this);
    //     }
    //     [[nodiscard]]
    //     T minTemperature() const
    //     {
    //         return te::call<T>([](auto const& self) { self.template min<T>(); }, *this);
    //     }
    //     [[nodiscard]]
    //     T maxTemperature() const
    //     {
    //         return te::call<T>([](auto const& self) { self.template max<T>(); }, *this);
    //     }
    //     [[nodiscard]]
    //     P minPressure() const
    //     {
    //         return te::call<P>([](auto const& self) { self.template min<P>(); }, *this);
    //     }
    //     [[nodiscard]]
    //     P maxPressure() const
    //     {
    //         return te::call<P>([](auto const& self) { self.template max<P>(); }, *this);
    //     }
    // };


}    // namespace pcprops