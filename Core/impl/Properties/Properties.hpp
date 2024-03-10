//
// Created by kenne on 18/02/2024.
//

#pragma once

#include "../Utils/Config.hpp"
#include "../Types/PropertyTypes.hpp"

#include "../Utils/Concepts.hpp"
#include "../Types/MiscTypes.hpp"

namespace pcprops
{
    namespace detail {

        /**
         * @brief Helper function to unpack a tuple and initialize a struct.
         *
         * This function template unpacks the elements of a tuple and uses them to initialize
         * a struct of type Struct.
         *
         * @tparam Struct The struct type to be initialized.
         * @tparam Tuple The tuple type from which the struct is initialized.
         * @tparam I Indices of the tuple elements.
         * @param tuple Tuple containing the values for struct initialization.
         * @return Struct An instance of Struct initialized with values from the tuple.
         */
        template<typename Struct, typename Tuple, std::size_t... I>
        Struct tupleToStructImpl(Tuple&& tuple, std::index_sequence<I...>)
        {
            return Struct { std::get<I>(std::forward<Tuple>(tuple))... };
        }

        /**
         * @brief Public function to convert a tuple to a struct.
         *
         * This function template provides a convenient way to convert a tuple into
         * a struct of type Struct.
         *
         * @tparam Struct The struct type to be initialized.
         * @tparam Tuple The tuple type from which the struct is initialized.
         * @param tuple Tuple containing the values for struct initialization.
         * @return Struct An instance of Struct initialized with values from the tuple.
         */
        template<typename Struct, typename Tuple>
        Struct tupleToStruct(Tuple&& tuple)
        {
            return tupleToStructImpl<Struct>(std::forward<Tuple>(tuple),
                                             std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>> {});
        }
    }

    template<typename PHASE_T>
    auto phase(const IFluid& fluid);

    template<typename PROPERTY_T, typename UNITS_T = MolarUnits>
    PROPERTY_T property(const IFluid& model);

    template<typename... PROPERTIES_T>
        requires(sizeof...(PROPERTIES_T) >= 1)
    auto properties(const IFluid& model);

    template<typename PROPERTY_T>
        requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
    auto saturation(const IFluid& fluid);

    template<typename PROPERTY_T>
        requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
    auto critical(const IFluid& fluid);

    template<typename PROPERTY_T>
        requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
    auto min(const IFluid& fluid);

    template<typename PROPERTY_T>
        requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
    auto max(const IFluid& fluid);

    namespace detail
    {
        template<IsProperty... PROPERTIES_T>
        class PropertyProxy
        {
            IFluid m_fluid;
            bool   m_isValid { true };

        public:
            explicit PropertyProxy(IFluid fluid, bool isValid = true) : m_fluid { std::move(fluid) }, m_isValid { isValid } {}

            PropertyProxy(const PropertyProxy&) = delete;
            PropertyProxy(PropertyProxy&&)      = delete;

            PropertyProxy& operator=(const PropertyProxy&) = delete;
            PropertyProxy& operator=(PropertyProxy&&)      = delete;

            ~PropertyProxy() = default;

            template<typename UNITS_T = MolarUnits>
                requires std::same_as<UNITS_T, MolarUnits> || std::same_as<UNITS_T, MassUnits>
            auto as() &&
            {
                if (!m_isValid) return std::make_tuple(PROPERTIES_T { std::nan("") }...);
                return std::make_tuple(m_fluid.property<PROPERTIES_T, UNITS_T>()...);
            }

            template<typename STRUCT_T, typename UNITS_T = MolarUnits>
                requires(std::same_as<UNITS_T, MolarUnits> || std::same_as<UNITS_T, MassUnits>) && (!std::same_as<STRUCT_T, MolarUnits>) &&
                        (!std::same_as<STRUCT_T, MassUnits>)
            STRUCT_T as() &&
            {
                if (!m_isValid) {
                    auto result = std::make_tuple(PROPERTIES_T { std::nan("") }...);
                    return detail::tupleToStruct<STRUCT_T>(result);
                }

                auto result = std::make_tuple(m_fluid.property<PROPERTIES_T, UNITS_T>()...);
                return detail::tupleToStruct<STRUCT_T>(result);
            }

            template<template<typename...> typename TUPLE_T, typename UNITS_T = MolarUnits>
                requires detail::IsTuple<TUPLE_T<double, double>>    // Check if container is tuple-like
            auto as() &&
            {
                if (!m_isValid) return TUPLE_T<PROPERTIES_T...> { PROPERTIES_T { std::nan("") }... };

                return TUPLE_T<PROPERTIES_T...> { m_fluid.property<PROPERTIES_T, UNITS_T>()... };
            }

            template<template<typename...> typename CONTAINER_T, typename UNITS_T = MolarUnits>    // typename VALUE_T = FLOAT>
                requires detail::IsContainer<CONTAINER_T<FLOAT>>    // Check if container is a homogeneous container
            auto as() &&
            {
                CONTAINER_T<FLOAT> container;
                container.reserve(sizeof...(PROPERTIES_T));    // Optimize for number of elements

                if (!m_isValid)
                    (container.emplace_back(PROPERTIES_T(std::nan("")).get()), ...);
                else
                    (container.emplace_back(m_fluid.property<PROPERTIES_T, UNITS_T>().get()), ...);

                return container;
            }
        };

        template<typename PHASE_T>
        class PhaseProxy
        {
            IFluid m_fluid;

        public:
            explicit PhaseProxy(IFluid fluid) : m_fluid { std::move(fluid) } {}

            template<typename PROPERTY_T, typename UNITS_T = MolarUnits>
            auto property()
            {
                auto ph = m_fluid.phase();

                if (std::is_same_v<PHASE_T, Liquid> && ph == Phase::Liquid) return pcprops::property<PROPERTY_T, UNITS_T>(m_fluid);

                if (std::is_same_v<PHASE_T, Liquid> && ph == Phase::TwoPhase) {
                    m_fluid.setState(pcprops::property<P>(m_fluid), X { 0.0 });
                    return pcprops::property<PROPERTY_T, UNITS_T>(m_fluid);
                }

                if (std::is_same_v<PHASE_T, Liquid> && ph != Phase::Liquid && ph != Phase::TwoPhase) {
                    return PROPERTY_T { std::nan("") };
                }

                if (std::is_same_v<PHASE_T, Gas> && ph == Phase::Gas) return pcprops::property<PROPERTY_T, UNITS_T>(m_fluid);

                if (std::is_same_v<PHASE_T, Gas> && ph == Phase::TwoPhase) {
                    m_fluid.setState(pcprops::property<P>(m_fluid), X { 1.0 });
                    return pcprops::property<PROPERTY_T, UNITS_T>(m_fluid);
                }

                if (std::is_same_v<PHASE_T, Gas> && ph != Phase::Gas && ph != Phase::TwoPhase) {
                    return PROPERTY_T { std::nan("") };
                }

                return pcprops::property<PROPERTY_T, UNITS_T>(m_fluid);
            }

            template<typename... PROPERTIES_T>
            auto properties()
            {
                auto ph = m_fluid.phase();

                if (std::is_same_v<PHASE_T, Liquid> && ph == Phase::Liquid) return pcprops::properties<PROPERTIES_T...>(m_fluid);

                if (std::is_same_v<PHASE_T, Liquid> && ph == Phase::TwoPhase) {
                    m_fluid.setState(pcprops::property<P>(m_fluid), X { 0.0 });
                    return pcprops::properties<PROPERTIES_T...>(m_fluid);
                }

                if (std::is_same_v<PHASE_T, Liquid> && ph != Phase::Liquid && ph != Phase::TwoPhase) {
                    return detail::PropertyProxy<PROPERTIES_T...>(m_fluid, false);
                }

                if (std::is_same_v<PHASE_T, Gas> && ph == Phase::Gas) return pcprops::properties<PROPERTIES_T...>(m_fluid);

                if (std::is_same_v<PHASE_T, Gas> && ph == Phase::TwoPhase) {
                    m_fluid.setState(pcprops::property<P>(m_fluid), X { 1.0 });
                    return pcprops::properties<PROPERTIES_T...>(m_fluid);
                }

                if (std::is_same_v<PHASE_T, Gas> && ph != Phase::Gas && ph != Phase::TwoPhase) {
                    return detail::PropertyProxy<PROPERTIES_T...>(m_fluid, false);
                }

                return pcprops::properties<PROPERTIES_T...>(m_fluid);
            }
        };

    }    // namespace detail

    template<typename PHASE_T>
    auto phase(const IFluid& fluid)
    {
        return detail::PhaseProxy<PHASE_T>(fluid);
    }

    template<typename PROPERTY_T, typename UNITS_T>
    PROPERTY_T property(const IFluid& model)
    {
        return model.property<PROPERTY_T, UNITS_T>();
    }

    template<typename... PROPERTIES_T>
        requires(sizeof...(PROPERTIES_T) >= 1)
    auto properties(const IFluid& model)
    {
        return detail::PropertyProxy<PROPERTIES_T...>(model);
    }

    template<typename PROPERTY_T>
        requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
    auto saturation(const IFluid& fluid)
    {
        if constexpr (std::same_as<PROPERTY_T, T>)
            return fluid.saturation<T>();
        else
            return fluid.saturation<P>();
    }

    template<typename PROPERTY_T>
        requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
    auto critical(const IFluid& fluid)
    {
        if constexpr (std::same_as<PROPERTY_T, T>)
            return fluid.critical<T>();
        else
            return fluid.critical<P>();
    }

    template<typename PROPERTY_T>
        requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
    auto min(const IFluid& fluid)
    {
        if constexpr (std::same_as<PROPERTY_T, T>)
            return fluid.min<T>();
        else
            return fluid.min<P>();
    }

    template<typename PROPERTY_T>
        requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
    auto max(const IFluid& fluid)
    {
        if constexpr (std::same_as<PROPERTY_T, T>)
            return fluid.max<T>();
        else
            return fluid.max<P>();
    }

}    // namespace pcprops
