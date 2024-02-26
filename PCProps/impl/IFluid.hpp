//
// Created by kenne on 25/02/2024.
//

#pragma once

#include "Config.hpp"
#include "PropertyTypes.hpp"

#include <boost-te/te.hpp>
#include <utility>

namespace pcprops
{
    namespace detail
    {

        template<typename DERIVED>
        class FluidBase
        {
            friend DERIVED;

            DERIVED&       derived() { return static_cast<DERIVED&>(*this); }
            const DERIVED& derived() const { return static_cast<const DERIVED&>(*this); }

        protected:
            ~FluidBase() = default;

        public:
            template<IsProperty P1, IsProperty P2>
            void setState(P1 p1, P2 p2)
            {
                auto spec = std::make_pair(p1, p2);

                if constexpr (IsSpecificationPT<P1, P2>)
                    derived().setStatePT(std::get<P>(spec), std::get<T>(spec));
                else if constexpr (IsSpecificationPX<P1, P2>)
                    derived().setStatePX(std::get<P>(spec), std::get<X>(spec));
                else if constexpr (IsSpecificationPH<P1, P2>)
                    derived().setStatePH(std::get<P>(spec), std::get<H>(spec));
                else if constexpr (IsSpecificationPS<P1, P2>)
                    derived().setStatePS(std::get<P>(spec), std::get<S>(spec));
                else if constexpr (IsSpecificationPD<P1, P2>)
                    derived().setStateDP(std::get<Rho>(spec), std::get<P>(spec));
                else if constexpr (IsSpecificationTD<P1, P2>)
                    derived().setStateDT(std::get<Rho>(spec), std::get<T>(spec));
                else if constexpr (IsSpecificationDS<P1, P2>)
                    derived().setStateDS(std::get<Rho>(spec), std::get<S>(spec));
                else if constexpr (IsSpecificationDH<P1, P2>)
                    derived().setStateDH(std::get<Rho>(spec), std::get<H>(spec));
                else if constexpr (IsSpecificationDU<P1, P2>)
                    derived().setStateDU(std::get<Rho>(spec), std::get<U>(spec));
                else if constexpr (IsSpecificationHS<P1, P2>)
                    derived().setStateHS(std::get<H>(spec), std::get<S>(spec));
                else if constexpr (IsSpecificationPU<P1, P2>)
                    derived().setStatePU(std::get<P>(spec), std::get<U>(spec));
                else if constexpr (IsSpecificationTS<P1, P2>)
                    derived().setStateTS(std::get<T>(spec), std::get<S>(spec));


                else if constexpr (IsSpecificationPV<P1, P2>)
                    derived().setStateDP(Rho { 1.0 / std::get<V>(spec).get() }, std::get<P>(spec));
                else if constexpr (IsSpecificationTV<P1, P2>)
                    derived().setStateDT(Rho { 1.0 / std::get<V>(spec).get() }, std::get<T>(spec));
                else
                    []<bool flag = false>() {
                        static_assert(flag, "Invalid specification");
                    }();
            }

            template<IsProperty PROPERTY_T>
                requires std::same_as<PROPERTY_T, PCrit> || std::same_as<PROPERTY_T, TCrit>
            [[nodiscard]]
            auto property() const
            {
                if constexpr (std::same_as<PROPERTY_T, PCrit>)
                    return PROPERTY_T { derived().criticalPressure() };
                else
                    return PROPERTY_T { derived().criticalTemperature() };
            }

            template<IsProperty PROPERTY_T>
                requires std::same_as<PROPERTY_T, H> || std::same_as<PROPERTY_T, S> || std::same_as<PROPERTY_T, Rho> ||
                         std::same_as<PROPERTY_T, U> || std::same_as<PROPERTY_T, Cp> || std::same_as<PROPERTY_T, Cv> ||
                         std::same_as<PROPERTY_T, W> || std::same_as<PROPERTY_T, X> || std::same_as<PROPERTY_T, T> ||
                         std::same_as<PROPERTY_T, P> || std::same_as<PROPERTY_T, V> || std::same_as<PROPERTY_T, A> ||
                         std::same_as<PROPERTY_T, G> || std::same_as<PROPERTY_T, Kappa> || std::same_as<PROPERTY_T, MW>
            [[nodiscard]]
            auto property() const
            {
                if constexpr (std::same_as<PROPERTY_T, MW>)
                    return PROPERTY_T { derived().molarMass() };
                else if constexpr (std::same_as<PROPERTY_T, T>)
                    return PROPERTY_T { derived().temperature() };
                else if constexpr (std::same_as<PROPERTY_T, P>)
                    return PROPERTY_T { derived().pressure() };
                else if constexpr (std::same_as<PROPERTY_T, H>)
                    return PROPERTY_T { derived().enthalpy() };
                else if constexpr (std::same_as<PROPERTY_T, S>)
                    return PROPERTY_T { derived().entropy() };
                else if constexpr (std::same_as<PROPERTY_T, Rho>)
                    return PROPERTY_T { derived().density() };
                else if constexpr (std::same_as<PROPERTY_T, U>)
                    return PROPERTY_T { derived().internalEnergy() };
                else if constexpr (std::same_as<PROPERTY_T, Cp>)
                    return PROPERTY_T { derived().cp() };
                else if constexpr (std::same_as<PROPERTY_T, Cv>)
                    return PROPERTY_T { derived().cv() };
                else if constexpr (std::same_as<PROPERTY_T, W>)
                    return PROPERTY_T { derived().speedOfSound() };
                else if constexpr (std::same_as<PROPERTY_T, X>)
                    return PROPERTY_T { derived().vaporQuality() };
                else if constexpr (std::same_as<PROPERTY_T, V>)
                    return PROPERTY_T { 1.0 / derived().density() };
                else if constexpr (std::same_as<PROPERTY_T, A>)
                    return PROPERTY_T { derived().internalEnergy() - derived().temperature() * derived().entropy() };
                else if constexpr (std::same_as<PROPERTY_T, G>)
                    return PROPERTY_T { derived().enthalpy() - derived().temperature() * derived().entropy() };
                else if constexpr (std::same_as<PROPERTY_T, Kappa>)
                    return PROPERTY_T { derived().isothermalCompressibility() };
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
        };

    }    // namespace detail

    template<typename IMPL_T>
    class Fluid : public detail::FluidBase<Fluid<IMPL_T>>
    {
        IMPL_T m_impl;
        using BASE = detail::FluidBase<Fluid<IMPL_T>>;
        friend BASE;

    public:
        explicit Fluid(const IMPL_T& fluid) : m_impl(fluid) {}
        explicit Fluid(IMPL_T&& fluid) : m_impl(std::move(fluid)) {}

    private:
        void setStatePT(P pressure, T temperature) { m_impl.setStatePT(pressure, temperature); }
        void setStatePX(P pressure, X vaporQuality) { m_impl.setStatePX(pressure, vaporQuality); }
        void setStatePH(P pressure, H enthalpy) { m_impl.setStatePH(pressure, enthalpy); }
        void setStatePS(P pressure, S entropy) { m_impl.setStatePS(pressure, entropy); }
        void setStateDP(Rho density, P pressure) { m_impl.setStateDP(density, pressure); }
        void setStateDT(Rho density, T temperature) { m_impl.setStateDT(density, temperature); }
        void setStateDS(Rho density, S entropy) { m_impl.setStateDS(density, entropy); }
        void setStateDH(Rho density, H enthalpy) { m_impl.setStateDH(density, enthalpy); }
        void setStateDU(Rho density, U internalEnergy) { m_impl.setStateDU(density, internalEnergy); }
        void setStateHS(H enthalpy, S entropy) { m_impl.setStateHS(enthalpy, entropy); }
        void setStatePU(P pressure, U internalEnergy) { m_impl.setStatePU(pressure, internalEnergy); }
        void setStateTS(T temperature, S entropy) { m_impl.setStateTS(temperature, entropy); }

        [[nodiscard]] MW    molarMass() const { return MW {m_impl.molarMass()}; }
        [[nodiscard]] T     temperature() const { return T {m_impl.temperature()}; }
        [[nodiscard]] P     pressure() const { return P {m_impl.pressure()}; }
        [[nodiscard]] H     enthalpy() const { return H {m_impl.enthalpy()}; }
        [[nodiscard]] S     entropy() const { return S {m_impl.entropy()}; }
        [[nodiscard]] Rho   density() const { return Rho {m_impl.density()}; }
        [[nodiscard]] U     internalEnergy() const { return U {m_impl.internalEnergy()}; }
        [[nodiscard]] Cp    cp() const { return Cp {m_impl.cp()}; }
        [[nodiscard]] Cv    cv() const { return Cv {m_impl.cv()}; }
        [[nodiscard]] W     speedOfSound() const { return W {m_impl.speedOfSound()}; }
        [[nodiscard]] X     vaporQuality() const { return X {m_impl.vaporQuality()}; }
        [[nodiscard]] Kappa isothermalCompressibility() const { return Kappa {m_impl.isothermalCompressibility()}; }

        [[nodiscard]] TCrit criticalTemperature() const { return TCrit {m_impl.criticalTemperature()}; }
        [[nodiscard]] PCrit criticalPressure() const { return PCrit {m_impl.criticalPressure()}; }
        [[nodiscard]] T     minTemperature() const { return T {m_impl.minTemperature()}; }
        [[nodiscard]] T     maxTemperature() const { return T {m_impl.maxTemperature()}; }
        [[nodiscard]] P     minPressure() const { return P {m_impl.minPressure()}; }
        [[nodiscard]] P     maxPressure() const { return P {m_impl.maxPressure()}; }
    };

    // clang-format off
    class IFluid : public detail::FluidBase<IFluid>
    {
        using BASE = detail::FluidBase<IFluid>;
        friend BASE;

    public:
        template<typename IMPL>
        IFluid(IMPL fluid) : m_pimpl(std::make_unique<Model<IMPL>>(std::move(fluid)))
        {}

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

        [[nodiscard]] MW    molarMass() const { return m_pimpl->molarMass(); }
        [[nodiscard]] T     temperature() const { return m_pimpl->temperature(); }
        [[nodiscard]] P     pressure() const { return m_pimpl->pressure(); }
        [[nodiscard]] H     enthalpy() const { return m_pimpl->enthalpy(); }
        [[nodiscard]] S     entropy() const { return m_pimpl->entropy(); }
        [[nodiscard]] Rho   density() const { return m_pimpl->density(); }
        [[nodiscard]] U     internalEnergy() const { return m_pimpl->internalEnergy(); }
        [[nodiscard]] Cp    cp() const { return m_pimpl->cp(); }
        [[nodiscard]] Cv    cv() const { return m_pimpl->cv(); }
        [[nodiscard]] W     speedOfSound() const { return m_pimpl->speedOfSound(); }
        [[nodiscard]] X     vaporQuality() const { return m_pimpl->vaporQuality(); }
        [[nodiscard]] Kappa isothermalCompressibility() const { return m_pimpl->isothermalCompressibility(); }

        [[nodiscard]] TCrit criticalTemperature() const { return m_pimpl->criticalTemperature(); }
        [[nodiscard]] PCrit criticalPressure() const { return m_pimpl->criticalPressure(); }
        [[nodiscard]] T     minTemperature() const { return m_pimpl->minTemperature(); }
        [[nodiscard]] T     maxTemperature() const { return m_pimpl->maxTemperature(); }
        [[nodiscard]] P     minPressure() const { return m_pimpl->minPressure(); }
        [[nodiscard]] P     maxPressure() const { return m_pimpl->maxPressure(); }

        struct Concept
        {
            virtual ~Concept() = default;

            virtual void setStatePT(P pressure, T temperature)  = 0;
            virtual void setStatePX(P pressure, X vaporQuality) = 0;
            virtual void setStatePH(P pressure, H enthalpy)     = 0;
            virtual void setStatePS(P pressure, S entropy)     = 0;
            virtual void setStateDP(Rho density, P pressure)    = 0;
            virtual void setStateDT(Rho density, T temperature) = 0;
            virtual void setStateDS(Rho density, S entropy) = 0;
            virtual void setStateDH(Rho density, H enthalpy) = 0;
            virtual void setStateDU(Rho density, U internalEnergy) = 0;
            virtual void setStateHS(H enthalpy, S entropy) = 0;
            virtual void setStatePU(P pressure, U internalEnergy) = 0;
            virtual void setStateTS(T temperature, S entropy) = 0;

            [[nodiscard]] virtual MW    molarMass() const                 = 0;
            [[nodiscard]] virtual T     temperature() const               = 0;
            [[nodiscard]] virtual P     pressure() const                  = 0;
            [[nodiscard]] virtual H     enthalpy() const                  = 0;
            [[nodiscard]] virtual S     entropy() const                   = 0;
            [[nodiscard]] virtual Rho   density() const                   = 0;
            [[nodiscard]] virtual U     internalEnergy() const            = 0;
            [[nodiscard]] virtual Cp    cp() const                        = 0;
            [[nodiscard]] virtual Cv    cv() const                        = 0;
            [[nodiscard]] virtual W     speedOfSound() const              = 0;
            [[nodiscard]] virtual X     vaporQuality() const              = 0;
            [[nodiscard]] virtual V     volume() const                    = 0;
            [[nodiscard]] virtual A     helmholtzEnergy() const           = 0;
            [[nodiscard]] virtual G     gibbsEnergy() const               = 0;
            [[nodiscard]] virtual Kappa isothermalCompressibility() const = 0;

            [[nodiscard]] virtual TCrit criticalTemperature() const = 0;
            [[nodiscard]] virtual PCrit criticalPressure() const    = 0;
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

            [[nodiscard]] MW    molarMass() const override { return m_fluid.template property<MW>(); }
            [[nodiscard]] T     temperature() const override { return m_fluid.template property<T>(); }
            [[nodiscard]] P     pressure() const override { return m_fluid.template property<P>(); }
            [[nodiscard]] H     enthalpy() const override { return m_fluid.template property<H>(); }
            [[nodiscard]] S     entropy() const override { return m_fluid.template property<S>(); }
            [[nodiscard]] Rho   density() const override { return m_fluid.template property<Rho>(); }
            [[nodiscard]] U     internalEnergy() const override { return m_fluid.template property<U>(); }
            [[nodiscard]] Cp    cp() const override { return m_fluid.template property<Cp>(); }
            [[nodiscard]] Cv    cv() const override { return m_fluid.template property<Cv>(); }
            [[nodiscard]] W     speedOfSound() const override { return m_fluid.template property<W>(); }
            [[nodiscard]] X     vaporQuality() const override { return m_fluid.template property<X>(); }
            [[nodiscard]] V     volume() const override { return m_fluid.template property<V>(); }
            [[nodiscard]] A     helmholtzEnergy() const override { return m_fluid.template property<A>(); }
            [[nodiscard]] G     gibbsEnergy() const override { return m_fluid.template property<G>(); }
            [[nodiscard]] Kappa isothermalCompressibility() const override { return m_fluid.template property<Kappa>(); }

            [[nodiscard]] TCrit criticalTemperature() const override { return m_fluid.template property<TCrit>(); }
            [[nodiscard]] PCrit criticalPressure() const override { return m_fluid.template property<PCrit>(); }
            [[nodiscard]] T     minTemperature() const override { return m_fluid.template min<T>(); }
            [[nodiscard]] T     maxTemperature() const override { return m_fluid.template max<T>(); }
            [[nodiscard]] P     minPressure() const override { return m_fluid.template min<P>(); }
            [[nodiscard]] P     maxPressure() const override { return m_fluid.template max<P>(); }

            [[nodiscard]] std::unique_ptr<Concept> clone() const override { return std::make_unique<Model<IMPL>>(*this); }
        };

        std::unique_ptr<Concept> m_pimpl;
    };
    // clang-format on

}    // namespace pcprops