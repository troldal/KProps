//
// Created by kenne on 08/03/2024.
//

#pragma once

#include <utility>

#include "../interfaces/IFluid.hpp"

#include "../Types/PropertyTypes.hpp"
#include "../Utils/Config.hpp"

#include "../Types/MiscTypes.hpp"
#include "../Utils/Concepts.hpp"

#include "FlashResults.hpp"

namespace pcprops
{

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

    template<typename DERIVED>
    class PropertiesBase
    {
        friend DERIVED;

        IFluid m_fluid;
        bool   m_isValid { true };

    protected:
        ~PropertiesBase() = default;

    public:
        explicit PropertiesBase(IFluid fluid, bool isValid = true) : m_fluid { std::move(fluid) }, m_isValid { isValid } {}

        PropertiesBase(const PropertiesBase&)     = delete;
        PropertiesBase(PropertiesBase&&) noexcept = delete;

        PropertiesBase& operator=(const PropertiesBase&)     = delete;
        PropertiesBase& operator=(PropertiesBase&&) noexcept = delete;
    };

    template<IsProperty... PROPERTIES_T>
    class StaticProperties : public PropertiesBase<StaticProperties<PROPERTIES_T...>>
    {
        using BASE = PropertiesBase<StaticProperties<PROPERTIES_T...>>;

    public:
        using BASE::BASE;

        template<typename UNITS_T = MolarUnits>
            requires std::same_as<UNITS_T, MolarUnits> || std::same_as<UNITS_T, MassUnits>
        auto get() &&
        {
            if (!BASE::m_isValid) return std::make_tuple(PROPERTIES_T { std::nan("") }...);
            return std::make_tuple(BASE::m_fluid.template property<PROPERTIES_T, UNITS_T>()...);
        }

        template<typename STRUCT_T, typename UNITS_T = MolarUnits>
            requires(std::same_as<UNITS_T, MolarUnits> || std::same_as<UNITS_T, MassUnits>) && (!std::same_as<STRUCT_T, MolarUnits>) &&
                    (!std::same_as<STRUCT_T, MassUnits>)
        STRUCT_T get() &&
        {
            if (!BASE::m_isValid) {
                auto result = std::make_tuple(PROPERTIES_T { std::nan("") }...);
                return tupleToStruct<STRUCT_T>(result);
            }

            auto result = std::make_tuple(BASE::m_fluid.template property<PROPERTIES_T, UNITS_T>()...);
            return tupleToStruct<STRUCT_T>(result);
        }

        template<template<typename...> typename TUPLE_T, typename UNITS_T = MolarUnits>
            requires detail::IsTuple<TUPLE_T<double, double>>    // Check if container is tuple-like
        auto get() &&
        {
            if (!BASE::m_isValid) return TUPLE_T<PROPERTIES_T...> { PROPERTIES_T { std::nan("") }... };

            return TUPLE_T<PROPERTIES_T...> { BASE::m_fluid.template property<PROPERTIES_T, UNITS_T>()... };
        }

        template<template<typename...> typename CONTAINER_T, typename UNITS_T = MolarUnits>    // typename VALUE_T = FLOAT>
            requires detail::IsContainer<CONTAINER_T<FLOAT>>    // Check if container is a homogeneous container
        auto get() &&
        {
            CONTAINER_T<FLOAT> container;
            container.reserve(sizeof...(PROPERTIES_T));    // Optimize for number of elements

            if (!BASE::m_isValid)
                (container.emplace_back(PROPERTIES_T(std::nan("")).get()), ...);
            else
                (container.emplace_back(BASE::m_fluid.template property<PROPERTIES_T, UNITS_T>().get()), ...);

            return container;
        }
    };

    class DynamicProperties : public PropertiesBase<DynamicProperties>
    {
        using BASE = PropertiesBase<DynamicProperties>;

        std::vector<Property> m_properties { };

    public:
        explicit DynamicProperties(IFluid fluid, std::vector<Property> properties, bool isValid = true)
            : BASE (std::move(fluid), isValid) , m_properties {std::move( properties )} {}

        template<template<typename...> typename CONTAINER_T, typename UNITS_T = MolarUnits>    // typename VALUE_T = FLOAT>
            requires detail::IsContainer<CONTAINER_T<FLOAT>>    // Check if container is a homogeneous container
        auto get() &&
        {
            CONTAINER_T<FLOAT> container;
            //container.reserve(m_properties.size());    // Optimize for number of elements

            for (auto prop : m_properties) { // Assuming propertiesVector is std::vector<Property>
                PropertyVariant var = mapPropertyToVariant(prop); // Convert enum to corresponding variant

                std::visit([&](auto&& arg) {
                    using TYPE = std::decay_t<decltype(arg)>; // Deduce the type held by variant
                    container.emplace_back(BASE::m_fluid.template property<TYPE, UNITS_T>().get());
                }, var);
            }

            return container;
        }
    };

}    // namespace pcprops
