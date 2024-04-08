//
// Created by kenne on 18/02/2024.
//

#pragma once

#include <KPropsUtils.hpp>

#include "PropertyProxy.hpp"

#include "../Utils/Concepts.hpp"

namespace KProps
{
    /**
     * @brief Retrieves a specific property of the fluid in a specified unit system.
     *
     * @details This function template is designed for type-safe retrieval of a fluid property, specified at compile-time,
     * in a given unit system. It abstracts the call to the fluid model's `property` method, providing a simplified interface
     * for accessing fluid properties.
     *
     * @tparam PROPERTY_T The type representing the property to be retrieved. This should be one of the predefined property
     * types that the fluid model recognizes.
     * @tparam UNITS_T The unit system in which to retrieve the property. Defaults to MolarUnits but can be overridden to
     * specify a different unit system if required.
     *
     * @param model The fluid model from which to retrieve the property.
     *
     * @return The value of the requested property, in the units specified by `UNITS_T`. The exact return type is determined
     * by the `PROPERTY_T` template parameter.
     */
    template<typename PROPERTY_T, typename UNITS_T = MolarUnits>
    PROPERTY_T property(const IFluid& model)
    {
        return model.property<PROPERTY_T, UNITS_T>();
    }

    /**
     * @brief Retrieves a specified fluid property by enum identifier, in a given unit system.
     *
     * @details This function offers an interface for dynamically querying properties of the fluid based on an enum identifier,
     * using the unit system specified by `UNITS_T`. It simplifies accessing fluid properties, particularly when the property
     * to be queried is determined at runtime rather than compile time.
     *
     * @tparam UNITS_T The unit system in which to retrieve the property. Defaults to MolarUnits but can be overridden to
     * specify a different unit system if required.
     *
     * @param model The fluid model from which to retrieve the property.
     * @param prop The property to be retrieved, specified as an enum of type Property::Type.
     *
     * @return The value of the requested property, in the units specified by `UNITS_T`. The return type is automatically
     * deduced based on the requested property and unit system.
     */
    template<typename UNITS_T = MolarUnits>
    auto property(const IFluid& model, Property::Type prop)
    {
        return model.property<UNITS_T>(prop);
    }

    /**
     * @brief Retrieves a specified fluid property using a string identifier, in a given unit system.
     *
     * @details This function offers an interface for dynamically querying properties of the fluid based on string identifiers,
     * using the unit system specified by `UNITS_T`. It supports flexible and dynamic retrieval of fluid properties, accommodating
     * scenarios where the property to be queried is specified at runtime, such as when interpreting user input or processing data
     * from external sources.
     *
     * @tparam UNITS_T The unit system in which to retrieve the property. Defaults to MolarUnits but can be overridden to
     * specify a different unit system if required.
     *
     * @param model The fluid model from which to retrieve the property.
     * @param prop A string representing the property to be retrieved. This should match the property names expected by the
     * fluid model.
     *
     * @return The value of the requested property, in the units specified by `UNITS_T`. The return type is deduced automatically
     * based on the property and the unit system, facilitating ease of use and integration into applications.
     */
    template<typename UNITS_T = MolarUnits>
    auto property(const IFluid& model, const std::string& prop)
    {
        return model.property<UNITS_T>(prop);
    }

    /**
     * @brief Retrieves multiple static properties of the fluid.
     *
     * @details This function template queries the fluid model for multiple properties specified at compile-time. It
     * constructs a `StaticProperties` object, which encapsulates the queried properties, providing type-safe access to them.
     * This function enforces that at least one property type is specified, leveraging compile-time checks for robustness.
     *
     * @tparam PROPERTIES_T Variadic template parameter list representing the types of properties to be retrieved. Each type
     * in this list should be one of the predefined property types recognized by the fluid model. The compile-time check ensures
     * that at least one property type is specified.
     *
     * @param model The fluid model from which to retrieve the properties.
     *
     * @return An instance of `StaticProperties<PROPERTIES_T...>`, facilitating type-safe access to the specified properties.
     */
    template<typename... PROPERTIES_T>
        requires(sizeof...(PROPERTIES_T) >= 1)
    auto properties(const IFluid& model)
    {
        return detail::StaticProperties<PROPERTIES_T...>(model);
    }

    /**
     * @brief Retrieves a set of dynamic properties of the fluid specified by an initializer list of property enums.
     *
     * @param model The fluid model from which to retrieve the properties.
     * @param proplist An initializer list of `Property::Type` enums specifying the properties to be queried.
     *
     * @return An instance of `DynamicProperties`, designed for flexible access to a runtime-specified set of properties.
     */
    inline auto properties(const IFluid& model, std::initializer_list<Property::Type> proplist)    // NOLINT
    {
        return detail::DynamicProperties(model, std::vector(proplist.begin(), proplist.end()));
    }

    /**
     * @brief Retrieves a set of dynamic properties of the fluid specified by a container of property enums.
     *
     * @tparam CONTAINER_T The type of the container holding the property enums. This container type must meet the
     * requirement that its `value_type` is `Property::Type`, ensuring that the properties can be correctly identified
     * and queried.
     *
     * @param model The fluid model from which to retrieve the properties.
     * @param proplist A container of `Property::Type` enums specifying the properties to be queried.
     *
     * @return An instance of `DynamicProperties`, designed for accessing a dynamically specified set of properties.
     */
    template<typename CONTAINER_T>
        requires std::same_as<typename CONTAINER_T::value_type, Property::Type>
    auto properties(const IFluid& model, const CONTAINER_T& proplist)
    {
        return detail::DynamicProperties(model, std::vector(proplist.begin(), proplist.end()));
    }

    /**
     * @brief Retrieves a set of dynamic properties of the fluid specified by an initializer list of string identifiers.
     *
     * @param model The fluid model from which to retrieve the properties.
     * @param proplist An initializer list of strings, where each string represents a property identifier.
     *
     * @return An instance of `DynamicProperties`, enabling flexible access to properties specified by string identifiers.
     */
    inline auto properties(const IFluid& model, std::initializer_list<std::string> proplist)    // NOLINT
    {
        return detail::DynamicProperties(model, std::vector(proplist.begin(), proplist.end()));
    }

    /**
     * @brief Retrieves a set of dynamic properties of the fluid specified by a container of string identifiers.
     *
     * @tparam CONTAINER_T The type of the container holding the string identifiers. This container type must meet the
     * requirement that its `value_type` is `std::string`, ensuring compatibility with property identification mechanisms.
     *
     * @param model The fluid model from which to retrieve the properties.
     * @param proplist A container of strings specifying the properties to be queried.
     *
     * @return An instance of `DynamicProperties`, designed for accessing properties identified by strings dynamically.
     */
    template<typename CONTAINER_T>
        requires std::same_as<typename CONTAINER_T::value_type, std::string>
    auto properties(const IFluid& model, const CONTAINER_T& proplist)
    {
        return detail::DynamicProperties(model, std::vector(proplist.begin(), proplist.end()));
    }

    /**
     * @brief Retrieves the saturation property (either temperature or pressure) of the fluid.
     *
     * @details This function template queries the fluid object for its saturation property, which can be either
     * temperature (`T`) or pressure (`P`), as specified by the template parameter `PROPERTY_T`. It demonstrates
     * the use of concepts to enforce compile-time type constraints, ensuring that the property type requested is
     * supported by the fluid model.
     *
     * @tparam PROPERTY_T The property type to be retrieved. Must be either `T` (temperature) or `P` (pressure),
     * as enforced by a compile-time constraint.
     *
     * @param fluid The fluid object from which to retrieve the saturation property.
     *
     * @return The saturation value of the specified property type from the fluid object.
     */
    template<typename PROPERTY_T>
        requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
    PROPERTY_T saturation(const IFluid& fluid)
    {
        if constexpr (std::same_as<PROPERTY_T, T>)
            return fluid.saturation<T>();
        else
            return fluid.saturation<P>();
    }

    /**
     * @brief Retrieves the critical property (either temperature or pressure) of the fluid.
     *
     * @tparam PROPERTY_T The property type to be retrieved, constrained to `T` (temperature) or `P` (pressure).
     *
     * @param fluid The fluid object from which to retrieve the critical property.
     *
     * @return The critical value of the specified property type from the fluid object.
     */
    template<typename PROPERTY_T>
        requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
    PROPERTY_T critical(const IFluid& fluid)
    {
        if constexpr (std::same_as<PROPERTY_T, T>)
            return fluid.critical<T>();
        else
            return fluid.critical<P>();
    }

    /**
     * @brief Retrieves the minimum value of the specified property (temperature or pressure) of the fluid.
     *
     * @tparam PROPERTY_T The property type for which the minimum value is to be retrieved, limited to `T` or `P`.
     *
     * @param fluid The fluid object from which to retrieve the minimum property value.
     *
     * @return The minimum value of the specified property type from the fluid object.
     */
    template<typename PROPERTY_T>
        requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
    PROPERTY_T min(const IFluid& fluid)
    {
        if constexpr (std::same_as<PROPERTY_T, T>)
            return fluid.min<T>();
        else
            return fluid.min<P>();
    }

    /**
     * @brief Retrieves the maximum value of the specified property (temperature or pressure) of the fluid.
     *
     * @tparam PROPERTY_T The property type for which the maximum value is to be retrieved, limited to `T` or `P`.
     *
     * @param fluid The fluid object from which to retrieve the maximum property value.
     *
     * @return The maximum value of the specified property type from the fluid object.
     */
    template<typename PROPERTY_T>
        requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
    PROPERTY_T max(const IFluid& fluid)
    {
        if constexpr (std::same_as<PROPERTY_T, T>)
            return fluid.max<T>();
        else
            return fluid.max<P>();
    }

}    // namespace KProps
