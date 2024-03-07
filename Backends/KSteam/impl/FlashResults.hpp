//
// Created by kenne on 31/01/2024.
//

#pragma once

#include ".utils/Concepts.hpp"
#include ".utils/Functions.hpp"

#include ".utils/Properties.hpp"

#include <Roots.hpp>
#include <optional>
#include <tuple>

#include "ThermoEngine.hpp"

namespace KSteam::detail
{

    using oP     = std::optional<P>;
    using oT     = std::optional<T>;
    using oH     = std::optional<H>;
    using oS     = std::optional<S>;
    using oU     = std::optional<U>;
    using oA     = std::optional<A>;
    using oG     = std::optional<G>;
    using oRho   = std::optional<Rho>;
    using oV     = std::optional<V>;
    using oPSat  = std::optional<PSat>;
    using oTSat  = std::optional<TSat>;
    using oCp    = std::optional<Cp>;
    using oCv    = std::optional<Cv>;
    using oKappa = std::optional<Kappa>;
    using oW     = std::optional<W>;
    using oZ     = std::optional<Z>;
    using oX     = std::optional<X>;
    using oEta   = std::optional<Eta>;
    using oNu    = std::optional<Nu>;
    using oTC    = std::optional<TC>;
    using oPR    = std::optional<PR>;

    /**
     * @brief Represents the results of a flash calculation.
     *
     * This class encapsulates the results of a flash calculation, providing access
     * to the calculated properties in various formats.
     *
     * @tparam SPEC1 Type of the first specification.
     * @tparam SPEC2 Type of the second specification.
     */
    template<typename MODEL_T, typename SPEC1, typename SPEC2>
    class FlashResults
    {
        // Specification of the system
        MODEL_T m_thermoModel {};
        ThermoEngine<MODEL_T> m_engine;
        std::pair<SPEC1, SPEC2> m_spec;

        // Tuple of properties
        mutable std::tuple<oP, oT, oH, oS, oU, oA, oG, oRho, oV, oPSat, oTSat, oCp, oCv, oKappa, oW, oZ, oX, oEta, oNu, oTC, oPR>
            m_props {};

        /**
         * @brief Proxy class for accessing flash calculation results.
         *
         * This class acts as a proxy for accessing the results of a flash calculation,
         * allowing the results to be retrieved either as a tuple or converted to a user-defined struct.
         *
         * @tparam RESULT_T Type of the tuple representing the properties.
         */
        template<typename RESULT_T>
        // requires IsTuple<RESULT_T<double, double>>
        class ResultProxyStatic
        {
            RESULT_T m_values {};

        public:
            /**
             * @brief Constructor for the ResultProxy.
             *
             * Initializes the proxy with the provided tuple of values.
             *
             * @param values Tuple of property values.
             */
            explicit ResultProxyStatic(RESULT_T values) : m_values { std::move(values) } {}

            ResultProxyStatic(const ResultProxyStatic&) = delete;
            ResultProxyStatic(ResultProxyStatic&&)      = delete;

            ResultProxyStatic& operator=(const ResultProxyStatic&) = delete;
            ResultProxyStatic& operator=(ResultProxyStatic&&)      = delete;

            ~ResultProxyStatic() = default;

            template<typename STRUCT_T>
            STRUCT_T get() &&
            {
                return tupleToStruct<STRUCT_T>(m_values);
            }

            template<template<typename...> typename TUPLE_T>
                requires IsTuple<TUPLE_T<double, double>>    // Check if container is tuple-like
            auto get() &&
            {
                return std::apply([](auto&&... args) { return TUPLE_T<decltype(args)...> { std::forward<decltype(args)>(args)... }; },
                                  m_values);
            }

            template<template<typename...> typename CONTAINER_T, typename VALUE_T = FLOAT>
                requires IsContainer<CONTAINER_T<VALUE_T>>    // Check if container is a homogeneous container
            auto get() &&
            {
                return std::apply(
                    [](auto&&... args) -> CONTAINER_T<VALUE_T> {
                        CONTAINER_T<VALUE_T> container;
                        container.reserve(sizeof...(args));    // Optimize for number of elements
                        (container.emplace_back(static_cast<VALUE_T>(args)), ...);
                        return container;
                    },
                    m_values);
            }
        };

        class ResultProxyDynamic
        {
            std::vector<Property>  m_properties {};
            std::pair<SPEC1, SPEC2> m_spec;

        public:
            /**
             * @brief Constructor for the ResultProxy.
             *
             * Initializes the proxy with the provided tuple of values.
             *
             * @param values Tuple of property values.
             */
            explicit ResultProxyDynamic(std::vector<Property> properties, std::pair<SPEC1, SPEC2> spec)
                : m_properties { std::move(properties) },
                  m_spec { std::move(spec) }
            {}

            ResultProxyDynamic(const ResultProxyDynamic&) = delete;
            ResultProxyDynamic(ResultProxyDynamic&&)      = delete;

            ResultProxyDynamic& operator=(const ResultProxyDynamic&) = delete;
            ResultProxyDynamic& operator=(ResultProxyDynamic&&)      = delete;

            ~ResultProxyDynamic() = default;

            template<template<typename...> typename CONTAINER_T, typename VALUE_T = PropertyVariant>
                requires IsContainer<CONTAINER_T<VALUE_T>>    // Check if container is a homogeneous container
            auto get() &&
            {
                CONTAINER_T<VALUE_T> container;
                for (const auto& prop : m_properties) {
                    switch (prop) {
                        case Property::P:
                            container.emplace_back(callSpecFunction<P>(m_spec.first, m_spec.second));
                            break;
                        case Property::T:
                            container.emplace_back(callSpecFunction<T>(m_spec.first, m_spec.second));
                            break;
                        case Property::H:
                            container.emplace_back(callSpecFunction<H>(m_spec.first, m_spec.second));
                            break;
                        case Property::S:
                            container.emplace_back(callSpecFunction<S>(m_spec.first, m_spec.second));
                            break;
                        case Property::U:
                            container.emplace_back(callSpecFunction<U>(m_spec.first, m_spec.second));
                            break;
                        case Property::A:
                            container.emplace_back(callSpecFunction<A>(m_spec.first, m_spec.second));
                            break;
                        case Property::G:
                            container.emplace_back(callSpecFunction<G>(m_spec.first, m_spec.second));
                            break;
                        case Property::Rho:
                            container.emplace_back(callSpecFunction<Rho>(m_spec.first, m_spec.second));
                            break;
                        case Property::V:
                            container.emplace_back(callSpecFunction<V>(m_spec.first, m_spec.second));
                            break;
                        case Property::PSat:
                            container.emplace_back(callSpecFunction<PSat>(m_spec.first, m_spec.second));
                            break;
                        case Property::TSat:
                            container.emplace_back(callSpecFunction<TSat>(m_spec.first, m_spec.second));
                            break;
                        case Property::Cp:
                            container.emplace_back(callSpecFunction<Cp>(m_spec.first, m_spec.second));
                            break;
                        case Property::Cv:
                            container.emplace_back(callSpecFunction<Cv>(m_spec.first, m_spec.second));
                            break;
                        case Property::Kappa:
                            container.emplace_back(callSpecFunction<Kappa>(m_spec.first, m_spec.second));
                            break;
                        case Property::W:
                            container.emplace_back(callSpecFunction<W>(m_spec.first, m_spec.second));
                            break;
                        case Property::Z:
                            container.emplace_back(callSpecFunction<Z>(m_spec.first, m_spec.second));
                            break;
                        case Property::X:
                            container.emplace_back(callSpecFunction<X>(m_spec.first, m_spec.second));
                            break;
                        case Property::Eta:
                            container.emplace_back(callSpecFunction<Eta>(m_spec.first, m_spec.second));
                            break;
                        case Property::Nu:
                            container.emplace_back(callSpecFunction<Nu>(m_spec.first, m_spec.second));
                            break;
                        case Property::TC:
                            container.emplace_back(callSpecFunction<TC>(m_spec.first, m_spec.second));
                            break;
                        case Property::PR:
                            container.emplace_back(callSpecFunction<PR>(m_spec.first, m_spec.second));
                            break;
                    }
                }

                return container;
            }
        };

        /**
         * @brief Get the properties as a tuple.
         *
         * Returns the properties encapsulated by this proxy as a tuple.
         *
         * @return TUPLE_T A tuple containing the property values.
         */
        template<typename P1, typename P2, typename... Ps>
        auto get_tuple() const
        {
            if constexpr (sizeof...(Ps) == 0)
                // Handle case with exactly two properties
                return std::make_tuple(property<P1>(), property<P2>());

            else
                // Handle case with more than two properties
                return std::make_tuple(property<P1>(), property<P2>(), property<Ps>()...);
        }

    public:
        /**
         * @brief Constructor for FlashResults.
         *
         * Initializes the flash results with the specified system specifications.
         *
         * @param p1 First specification of the system.
         * @param p2 Second specification of the system.
         */
        FlashResults(SPEC1 p1, SPEC2 p2) : m_spec { p1, p2 }
        {
            std::get<std::optional<SPEC1>>(m_props) = p1;
            std::get<std::optional<SPEC2>>(m_props) = p2;
        }

        /**
         * @brief Get a single property.
         *
         * Retrieves a single property of type PROPERTY_T from the flash results.
         * If the property is not set, it initializes it with a default value.
         *
         * @tparam PROPERTY_T The type of the property to retrieve.
         * @return The value of the requested property.
         */
        template<typename PROPERTY_T>
        auto property() const
        {
            auto& prop = std::get<std::optional<PROPERTY_T>>(m_props);
            // if (!prop) prop = PROPERTY_T { callSpecFunction<MODEL_T, PROPERTY_T>(m_spec.first, m_spec.second) };
            if (!prop) prop = PROPERTY_T { m_engine.template property<PROPERTY_T>(m_spec.first, m_spec.second) };
            return prop.value();
            // return callSpecFunction<MODEL_T, PROPERTY_T>(m_spec.first, m_spec.second);
        }

        template<typename PROPERTY_T>
        auto properties() const
        {
            using TUPLE_T = std::tuple<PROPERTY_T>;
            return ResultProxyStatic<TUPLE_T>(std::make_tuple(property<PROPERTY_T>()));
        }

        /**
         * @brief Get selected properties as a proxy object.
         *
         * Retrieves selected properties and returns them as a ResultProxy object.
         * The ResultProxy object can be implicitly converted to a user-defined struct
         * or used to access the properties as a tuple.
         *
         * @tparam P1, P2, Ps Types of the properties to retrieve.
         * @return A ResultProxy object encapsulating the selected properties.
         */
        template<typename P1, typename P2, typename... Ps>
        auto properties() const
        {
            using TUPLE_T = std::tuple<P1, P2, Ps...>;
            return ResultProxyStatic<TUPLE_T>(get_tuple<P1, P2, Ps...>());
        }

        auto properties(std::initializer_list<Property> props) { return ResultProxyDynamic(props, m_spec); }

        /**
         * @brief Get all properties as a struct.
         *
         * Converts all the properties stored in the FlashResults instance to a user-defined struct.
         * The STRUCT_T parameter should be a struct type that can be initialized with the properties
         * stored in the FlashResults instance.
         *
         * @tparam STRUCT_T The struct type to which the properties will be converted.
         * @return STRUCT_T An instance of STRUCT_T initialized with the property values.
         */
        template<typename STRUCT_T>
        STRUCT_T get() const
        {
            return tupleToStruct<STRUCT_T>(get_tuple<P, T, H, S, U, A, G, Rho, V, PSat, TSat, Cp, Cv, Kappa, W, Z, X, Eta, Nu, TC, PR>());
        }

        template<template<typename...> typename TUPLE_T>
            requires IsTuple<TUPLE_T<double, double>>    // Check if container is tuple-like
        auto get() const
        {
            return std::apply([](auto&&... args) { return TUPLE_T<decltype(args)...> { std::forward<decltype(args)>(args)... }; },
                              get_tuple<P, T, H, S, U, A, G, Rho, V, PSat, TSat, Cp, Cv, Kappa, W, Z, X, Eta, Nu, TC, PR>());
        }

        template<template<typename...> typename CONTAINER_T, typename VALUE_T = PropertyVariant>
            requires IsContainer<CONTAINER_T<VALUE_T>>    // Check if container is a homogeneous container
        auto get() const
        {
            return std::apply(
                [](auto&&... args) -> CONTAINER_T<VALUE_T> {
                    CONTAINER_T<VALUE_T> container;
                    container.reserve(sizeof...(args));    // Optimize for number of elements
                    (container.emplace_back(static_cast<VALUE_T>(args)), ...);
                    return container;
                },
                get_tuple<P, T, H, S, U, A, G, Rho, V, PSat, TSat, Cp, Cv, Kappa, W, Z, X, Eta, Nu, TC, PR>());
        }
    };

}    // namespace KSteam::detail
