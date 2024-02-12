//
// Created by kenne on 07/02/2024.
//

#pragma once

namespace KSteam
{

    template<typename MODEL_T>
    class ThermoEngine
    {
        MODEL_T m_model;

        template<typename PROPERTY_T>
        auto propertyAtPT(P pressure, T temperature) const
        {
            if constexpr (std::same_as<PROPERTY_T, P>) return pressure;
            if constexpr (std::same_as<PROPERTY_T, T>) return temperature;
            if constexpr (std::same_as<PROPERTY_T, PSat>) return m_model.template property<PSat>(temperature);
            if constexpr (std::same_as<PROPERTY_T, TSat>) return m_model.template property<TSat>(pressure);
            if constexpr (std::same_as<PROPERTY_T, H>) return m_model.template property<H>(pressure, temperature);
            if constexpr (std::same_as<PROPERTY_T, S>) return m_model.template property<S>(pressure, temperature);
            if constexpr (std::same_as<PROPERTY_T, Rho>) return m_model.template property<Rho>(pressure, temperature);
            if constexpr (std::same_as<PROPERTY_T, V>) return 1.0 / m_model.template property<Rho>(pressure, temperature);
            if constexpr (std::same_as<PROPERTY_T, U>) return m_model.template property<U>(pressure, temperature);
            if constexpr (std::same_as<PROPERTY_T, Cp>) return m_model.template property<Cp>(pressure, temperature);
            if constexpr (std::same_as<PROPERTY_T, Cv>) return m_model.template property<Cv>(pressure, temperature);
            if constexpr (std::same_as<PROPERTY_T, W>) return m_model.template property<W>(pressure, temperature);
        }

        template<typename PROPERTY_T>
        auto propertyAtPX(P pressure, X vaporQuality) const
        {
            if constexpr (std::same_as<PROPERTY_T, P>) return pressure;
            if constexpr (std::same_as<PROPERTY_T, X>) return vaporQuality;
            if constexpr (std::same_as<PROPERTY_T, T>) return m_model.template property<T>(pressure, vaporQuality);
            if constexpr (std::same_as<PROPERTY_T, PSat>) return m_model.template property<PSat>(vaporQuality);
            if constexpr (std::same_as<PROPERTY_T, TSat>) return m_model.template property<TSat>(vaporQuality);
            if constexpr (std::same_as<PROPERTY_T, H>) return m_model.template property<H>(pressure, vaporQuality);
            if constexpr (std::same_as<PROPERTY_T, S>) return m_model.template property<S>(pressure, vaporQuality);
            if constexpr (std::same_as<PROPERTY_T, Rho>) return m_model.template property<Rho>(pressure, vaporQuality);
            if constexpr (std::same_as<PROPERTY_T, V>) return 1.0 / m_model.template property<Rho>(pressure, vaporQuality);
            if constexpr (std::same_as<PROPERTY_T, U>) return m_model.template property<U>(pressure, vaporQuality);
            if constexpr (std::same_as<PROPERTY_T, Cp>) return m_model.template property<Cp>(pressure, vaporQuality);
            if constexpr (std::same_as<PROPERTY_T, Cv>) return m_model.template property<Cv>(pressure, vaporQuality);
            if constexpr (std::same_as<PROPERTY_T, W>) return m_model.template property<W>(pressure, vaporQuality);
        }

        template<typename PROPERTY_T>
        auto guessAtPH(P pressure, H enthalpy) const
        {
            if constexpr (std::same_as<PROPERTY_T, P>) return pressure;
            if constexpr (std::same_as<PROPERTY_T, T>) return m_model.template guess<T>(pressure, enthalpy);
            if constexpr (std::same_as<PROPERTY_T, Rho>) return m_model.template guess<S>(pressure, enthalpy);
        }

        template<typename PROPERTY_T>
        auto guessAtPS(P pressure, S entropy) const
        {
            if constexpr (std::same_as<PROPERTY_T, P>) return pressure;
            if constexpr (std::same_as<PROPERTY_T, T>) return m_model.template guess<T>(pressure, entropy);
            if constexpr (std::same_as<PROPERTY_T, Rho>) return m_model.template guess<S>(pressure, entropy);
        }

        template<typename PROPERTY_T>
        auto guessAtHS(H enthalpy, S entropy) const
        {
            if constexpr (std::same_as<PROPERTY_T, P>) return m_model.template guess<P>(enthalpy, entropy);
            if constexpr (std::same_as<PROPERTY_T, T>) return m_model.template guess<T>(enthalpy, entropy);
            if constexpr (std::same_as<PROPERTY_T, Rho>) return m_model.template guess<S>(enthalpy, entropy);
        }

        template<typename PROPERTY_T>
        auto guessAtPU(P pressure, U internalEnergy) const
        {
            if constexpr (std::same_as<PROPERTY_T, P>) return pressure;

            if constexpr (std::same_as<PROPERTY_T, T>) {
                auto lower = T { 0.0 };
                auto upper = T { 0.0 };

                if (pressure < P { m_model.template property<PCrit>() } &&
                    internalEnergy >= m_model.template property<U>(pressure, m_model.template min<T>()) &&
                    internalEnergy <= m_model.template property<U>(pressure, T { m_model.template property<TSat>(pressure) }))
                {
                    lower = m_model.template min<T>();
                    upper = T { m_model.template property<TSat>(pressure) };
                }
                else if (pressure < P { m_model.template property<PCrit>() } &&
                         internalEnergy >= m_model.template property<U>(pressure, T { m_model.template property<TSat>(pressure) }) &&
                         internalEnergy <= m_model.template property<U>(pressure, m_model.template max<T>()))
                {
                    lower = T { m_model.template property<TSat>(pressure) };
                    upper = m_model.template max<T>();
                }
                else if (pressure < P { m_model.template property<PCrit>() }) {
                    return T { m_model.template property<TSat>(pressure) };
                }
                else if (pressure == P { m_model.template property<PCrit>() }) {
                    return T { m_model.template property<TCrit>() };
                }
                else {
                    lower = m_model.template min<T>();
                    upper = m_model.template max<T>();
                }

                using namespace nxx::roots;
                return fsolve<Bisection>(
                           [&](FLOAT t) { return m_model.template property<U>(pressure, T { t }).get() - internalEnergy.get(); },
                           { lower.get(), upper.get() },
                           1e-3,
                           100)
                    .template result<T>();
            }

            if constexpr (std::same_as<PROPERTY_T, Rho>) {
                auto t = guessAtPU<T>(pressure, internalEnergy);
                return m_model.template property<Rho>(pressure, t);
            }
        }

        template<typename PROPERTY_T>
        auto guessAtTD(T temperature, Rho density) const
        {
            if constexpr (std::same_as<PROPERTY_T, T>) return temperature;
            if constexpr (std::same_as<PROPERTY_T, Rho>) return density;
            if constexpr (std::same_as<PROPERTY_T, P>) {
                auto lower = P { 0.0 };
                auto upper = P { 0.0 };

                if (temperature < m_model.template property<TCrit>() &&
                    density >= m_model.template property<Rho>(m_model.template min<P>(), temperature) &&
                    density < m_model.template property<Rho>(m_model.template property<PSat>(temperature), X { 0.0 }))
                {
                    lower = m_model.template min<P>();
                    upper = m_model.template property<PSat>(temperature);
                }
                else if (temperature < m_model.template property<TCrit>() &&
                         density > m_model.template property<Rho>(m_model.template property<PSat>(temperature), X { 1.0 }) &&
                         density <= m_model.template property<Rho>(m_model.template max<P>(), temperature))
                {
                    lower = m_model.template property<PSat>(temperature) + PSat { std::sqrt(std::numeric_limits<FLOAT>::epsilon()) };
                    upper = m_model.template max<P>();
                }
                else if (temperature < m_model.template property<TCrit>()) {
                    return P { m_model.template property<PSat>(temperature) };
                }
                else if (temperature == m_model.template property<TCrit>()) {
                    return P { m_model.template property<PCrit>() };
                }
                else {
                    lower = m_model.template min<P>();
                    upper = m_model.template max<P>();
                }

                using namespace nxx::roots;
                return fsolve<Bisection>(
                           [&](FLOAT p) { return m_model.template property<Rho>(P { p }, temperature).get() - density.get(); },
                           { lower.get(), upper.get() },
                           1e-3,
                           100)
                    .template result<P>();
            }
        }

        template<typename PROPERTY_T>
        auto guessAtTV(T temperature, V volume) const
        {
            return guessAtTD<PROPERTY_T>(temperature, 1.0 / volume);
        }


        template<typename PROPERTY_T, typename S1, typename S2>
        auto find(S1 s1, S2 s2) const
        {
            auto spec = std::make_pair(s1, s2);

            if constexpr (IsSpecificationPH<S1, S2>) {
                auto p     = std::get<P>(spec);
                auto h     = std::get<H>(spec);
                auto guess = T { 0.0 };

                if (h <= propertyAtPT<H>(p, m_model.template min<T>()))
                    guess = m_model.template min<T>();
                else if (h >= propertyAtPT<H>(p, m_model.template max<T>()))
                    guess = m_model.template max<T>();
                else
                    guess = guessAtPH<T>(p, h);

                auto objective = [&](FLOAT t) {
                    if (t < m_model.template min<T>()) {
                        auto slope = m_model.template property<Cp>(p, m_model.template min<T>());
                        return propertyAtPT<H>(p, m_model.template min<T>()) + slope * (t - m_model.template min<T>()) - h;
                    }

                    if (t > m_model.template max<T>()) {
                        auto slope = m_model.template property<Cp>(p, m_model.template max<T>());
                        return propertyAtPT<H>(p, m_model.template max<T>()) + slope * (t - m_model.template max<T>()) - h;
                    }
                    return (m_model.template property<H>(p, T { t }) - h).get();
                };

                auto outputter = [&](const nxx::roots::PolishingIterData<size_t, FLOAT>& iterData) {
                    const auto& [iter, guess, previous] = iterData;
                    if (guess < m_model.template min<T>()) return m_model.template min<T>();
                    if (guess > m_model.template max<T>()) return m_model.template max<T>();
                    return T { guess };
                };

                guess = nxx::roots::fdfsolve<nxx::roots::Secant>(objective, guess.get()).result(outputter);
                return property<PROPERTY_T>(p, guess);
            }

            if constexpr (IsSpecificationPS<S1, S2>) {
                auto p     = std::get<P>(spec);
                auto s     = std::get<S>(spec);
                auto guess = T { 0.0 };

                if (s <= propertyAtPT<S>(p, m_model.template min<T>()))
                    guess = m_model.template min<T>();
                else if (s >= propertyAtPT<S>(p, m_model.template max<T>()))
                    guess = m_model.template max<T>();
                else
                    guess = guessAtPS<T>(p, s);

                auto objective = [&](FLOAT t) {
                    if (t < m_model.template min<T>()) {
                        auto slope = m_model.template property<Cp>(p, m_model.template min<T>()) / m_model.template min<T>();
                        return propertyAtPT<S>(p, m_model.template min<T>()) + slope * (t - m_model.template min<T>()) - s;
                    }

                    if (t > m_model.template max<T>()) {
                        auto slope = m_model.template property<Cp>(p, m_model.template max<T>()) / m_model.template max<T>();
                        return propertyAtPT<S>(p, m_model.template max<T>()) + slope * (t - m_model.template max<T>()) - s;
                    }
                    return (m_model.template property<S>(p, T { t }) - s).get();
                };

                auto outputter = [&](const nxx::roots::PolishingIterData<size_t, FLOAT>& iterData) {
                    const auto& [iter, guess, previous] = iterData;
                    if (guess < m_model.template min<T>()) return m_model.template min<T>();
                    if (guess > m_model.template max<T>()) return m_model.template max<T>();
                    return T { guess };
                };

                guess = nxx::roots::fdfsolve<nxx::roots::Secant>(objective, guess.get()).result(outputter);
                return property<PROPERTY_T>(p, guess);
            }

            if constexpr (IsSpecificationPU<S1, S2>) {
                auto p     = std::get<P>(spec);
                auto u     = std::get<U>(spec);
                auto guess = T { 0.0 };

                if (u <= propertyAtPT<U>(p, m_model.template min<T>()))
                    guess = m_model.template min<T>();
                else if (u >= propertyAtPT<U>(p, m_model.template max<T>()))
                    guess = m_model.template max<T>();
                else
                    guess = guessAtPU<T>(p, u);

                auto objective = [&](FLOAT t) {
                    if (t < m_model.template min<T>()) {
                        auto slope = m_model.template property<Cv>(p, m_model.template min<T>());
                        return propertyAtPT<U>(p, m_model.template min<T>()) + slope * (t - m_model.template min<T>()) - u;
                    }

                    if (t > m_model.template max<T>()) {
                        auto slope = m_model.template property<Cv>(p, m_model.template max<T>());
                        return propertyAtPT<U>(p, m_model.template max<T>()) + slope * (t - m_model.template max<T>()) - u;
                    }
                    return (m_model.template property<U>(p, T { t }) - u).get();
                };

                auto outputter = [&](const nxx::roots::PolishingIterData<size_t, FLOAT>& iterData) {
                    const auto& [iter, guess, previous] = iterData;
                    if (guess < m_model.template min<T>()) return m_model.template min<T>();
                    if (guess > m_model.template max<T>()) return m_model.template max<T>();
                    return T { guess };
                };

                guess = nxx::roots::fdfsolve<nxx::roots::Secant>(objective, guess.get()).result(outputter);
                return property<PROPERTY_T>(p, guess);
            }

            if constexpr (IsSpecificationTD<S1, S2>) {
                auto t     = std::get<T>(spec);
                auto rho   = std::get<Rho>(spec);
                auto guess = P { 0.0 };

                if (rho <= propertyAtPT<Rho>(m_model.template min<P>(), t))
                    guess = m_model.template min<P>();
                else if (rho >= propertyAtPT<Rho>(m_model.template max<P>(), t))
                    guess = m_model.template max<P>();
                else
                    guess = guessAtTD<P>(t, rho);

                auto objective = [&](FLOAT p) {
                    if (p < m_model.template min<P>()) {
                        // auto slope = m_model.template property<Cv>(p, m_model.template min<T>()) / m_model.template min<T>();
                        auto slope = *nxx::deriv::forward([&](FLOAT pr) { return m_model.template property<Rho>(P { pr }, t).get(); },
                                                          m_model.template min<P>());
                        return propertyAtPT<Rho>(m_model.template min<P>(), t) + slope * (p - m_model.template min<P>()) - rho;
                    }

                    if (p > m_model.template max<P>()) {
                        // auto slope = m_model.template property<Cv>(p, m_model.template max<T>()) / m_model.template max<T>();
                        auto slope = *nxx::deriv::backward([&](FLOAT pr) { return m_model.template property<Rho>(P { pr }, t).get(); },
                                                           m_model.template max<P>());
                        return propertyAtPT<Rho>(m_model.template max<P>(), t) + slope * (p - m_model.template max<P>()) - rho;
                    }
                    return (m_model.template property<Rho>(P { p }, t) - rho).get();
                };

                guess = nxx::roots::fdfsolve<nxx::roots::Secant>(objective, guess.get()).template result<P>();

                // TODO: Implement a better guess for pressure:
                if (guess > m_model.template max<P>()) guess = m_model.template max<P>();
                return property<PROPERTY_T>(guess, t);
            }

            if constexpr (IsSpecificationTV<S1, S2>) {
                return find<PROPERTY_T>(std::get<T>(spec), Rho{1.0 / std::get<V>(spec).get()});
            }
        }

    public:
         ThermoEngine() = default;
        ~ThermoEngine() = default;

        template<typename PROPERTY_T, typename S1, typename S2>
            requires IsSpecification<S1, S2> && IsProperty<PROPERTY_T>
        auto property(S1 s1, S2 s2) const
        {
            auto spec = std::make_pair(s1, s2);

            if constexpr (IsSpecificationPT<S1, S2>) return propertyAtPT<PROPERTY_T>(std::get<P>(spec), std::get<T>(spec));
            if constexpr (IsSpecificationPH<S1, S2>) return find<PROPERTY_T>(std::get<P>(spec), std::get<H>(spec));
            if constexpr (IsSpecificationPS<S1, S2>) return find<PROPERTY_T>(std::get<P>(spec), std::get<S>(spec));
            if constexpr (IsSpecificationPU<S1, S2>) return find<PROPERTY_T>(std::get<P>(spec), std::get<U>(spec));

            if constexpr (IsSpecificationPX<S1, S2>) return propertyAtPX<PROPERTY_T>(std::get<P>(spec), std::get<X>(spec));

            if constexpr (IsSpecificationTD<S1, S2>) return find<PROPERTY_T>(std::get<T>(spec), std::get<Rho>(spec));
            if constexpr (IsSpecificationTV<S1, S2>) return find<PROPERTY_T>(std::get<T>(spec), std::get<V>(spec));
        }
    };

}    // namespace KSteam