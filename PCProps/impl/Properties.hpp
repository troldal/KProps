//
// Created by kenne on 18/02/2024.
//

#pragma once

#include "Config.hpp"
#include "PropertyTypes.hpp"

#include "Utils/Concepts.hpp"
#include "Utils/Functions.hpp"

namespace pcprops
{
    struct MolarUnits
    {
    };
    struct MassUnits
    {
    };

    template<typename PROPERTY_T, typename UNITS_T = MolarUnits>
    auto property(const IFluid& model);

    namespace detail
    {

        template<typename PROPERTY_T>
        auto convert(PROPERTY_T value)
        {
            if constexpr (std::same_as<PROPERTY_T, H>)
                return H {value / 0.01801528 };
            else if constexpr (std::same_as<PROPERTY_T, S>)
                return S { value / 0.01801528 };
            else if constexpr (std::same_as<PROPERTY_T, U>)
                return U { value / 0.01801528 };
            else if constexpr (std::same_as<PROPERTY_T, A>)
                return A { value / 0.01801528 };
            else if constexpr (std::same_as<PROPERTY_T, G>)
                return G { value / 0.01801528 };
            else if constexpr (std::same_as<PROPERTY_T, Rho>)
                return Rho { value * 0.01801528 };
            else if constexpr (std::same_as<PROPERTY_T, V>)
                return V { value / 0.01801528 };
            else if constexpr (std::same_as<PROPERTY_T, Cp>)
                return Cp { value / 0.01801528 };
            else if constexpr (std::same_as<PROPERTY_T, Cv>)
                return Cv { value / 0.01801528 };
            else return value;
        }


        template<typename Tuple, std::size_t... Indices>
        void modifyTupleElements(Tuple& t, std::index_sequence<Indices...>)
        {
            // Using a fold expression to iterate over each index and modify the tuple element.
            (..., (std::get<Indices>(t) = convert(std::get<Indices>(t))));
        }

        template<typename... Args>
        void modifyTuple(std::tuple<Args...>& t)
        {
            modifyTupleElements(t, std::index_sequence_for<Args...> {});
        }

        template<typename P1, typename P2, typename... Ps>
        auto get_tuple(const IFluid& fluid)
        {
            if constexpr (sizeof...(Ps) == 0)
                // Handle case with exactly two properties
                return std::make_tuple(property<P1>(fluid), property<P2>(fluid));

            else
                // Handle case with more than two properties
                return std::make_tuple(property<P1>(fluid), property<P2>(fluid), property<Ps>(fluid)...);
        }

        template<typename RESULT_T>
        // requires IsTuple<RESULT_T<double, double>>
        class PropertyProxy
        {
            RESULT_T m_values {};
            MW       m_mw;

        public:
            /**
             * @brief Constructor for the ResultProxy.
             *
             * Initializes the proxy with the provided tuple of values.
             *
             * @param values Tuple of property values.
             * @param mw Molar mass of the fluid.
             */
            explicit PropertyProxy(RESULT_T values, MW mw) : m_values { std::move(values) }, m_mw { std::move(mw) } {}

            PropertyProxy(const PropertyProxy&) = delete;
            PropertyProxy(PropertyProxy&&)      = delete;

            PropertyProxy& operator=(const PropertyProxy&) = delete;
            PropertyProxy& operator=(PropertyProxy&&)      = delete;

            ~PropertyProxy() = default;

            template<typename STRUCT_T, typename UNITS_T = MolarUnits>
            STRUCT_T get() &&
            {
                if constexpr (std::same_as<UNITS_T, MassUnits>)
                    modifyTuple(m_values);
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
    }    // namespace detail

    template<typename PROPERTY_T, typename UNITS_T>
    auto property(const IFluid& model)
    {
        if constexpr (std::same_as<UNITS_T, MolarUnits>)
            return model.property<PROPERTY_T>();
        else if constexpr (std::same_as<PROPERTY_T, H>)
            return H { model.property<PROPERTY_T>().get() / model.property<MW>().get() };
        else if constexpr (std::same_as<PROPERTY_T, S>)
            return S { model.property<PROPERTY_T>().get() / model.property<MW>().get() };
        else if constexpr (std::same_as<PROPERTY_T, U>)
            return U { model.property<PROPERTY_T>().get() / model.property<MW>().get() };
        else if constexpr (std::same_as<PROPERTY_T, A>)
            return A { model.property<PROPERTY_T>().get() / model.property<MW>().get() };
        else if constexpr (std::same_as<PROPERTY_T, G>)
            return G { model.property<PROPERTY_T>().get() / model.property<MW>().get() };
        else if constexpr (std::same_as<PROPERTY_T, Rho>)
            return Rho { model.property<PROPERTY_T>().get() * model.property<MW>().get() };
        else if constexpr (std::same_as<PROPERTY_T, V>)
            return V { model.property<PROPERTY_T>().get() / model.property<MW>().get() };
        else if constexpr (std::same_as<PROPERTY_T, Cp>)
            return Cp { model.property<PROPERTY_T>().get() / model.property<MW>().get() };
        else if constexpr (std::same_as<PROPERTY_T, Cv>)
            return Cv { model.property<PROPERTY_T>().get() / model.property<MW>().get() };
        else
            return model.property<PROPERTY_T>();
    }

    template<typename PROPERTY_T>
    auto properties(const IFluid& model)
    {
        using TUPLE_T = std::tuple<PROPERTY_T>;
        return detail::PropertyProxy<TUPLE_T>(std::make_tuple(property<PROPERTY_T>(model)), model.property<MW>());
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
    auto properties(const IFluid& model)
    {
        using TUPLE_T = std::tuple<P1, P2, Ps...>;
        return detail::PropertyProxy<TUPLE_T>(detail::get_tuple<P1, P2, Ps...>(model), model.property<MW>());
    }

}    // namespace pcprops