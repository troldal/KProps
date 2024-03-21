//
// Created by kenne on 08/03/2024.
//

#pragma once

#include "../Interfaces/IFluid.hpp"

#include "PropertyProxy.hpp"

namespace KProps::detail
{

    /**
     * @brief Template struct for mapping unit types to their respective implementation types.
     * @details This template is specialized for different unit types to facilitate unit-specific operations.
     */
    template<typename...>
    struct UnitsType;

    /**
     * @brief Specialization of UnitsType for MolarUnits.
     */
    template<>
    struct UnitsType<MolarUnits>
    {
        using type = MolarUnits;
    };

    /**
     * @brief Specialization of UnitsType for MassUnits.
     */
    template<>
    struct UnitsType<MassUnits>
    {
        using type = MassUnits;
    };

    /**
     * @class FlashResults
     * @brief Manages the results of flash calculations for a given fluid.
     *
     * @details This class encapsulates the outcome of flash calculations performed on a fluid,
     * offering an interface to query various properties of the fluid post-calculation. It supports
     * querying both static and dynamic properties, with support for different units of measurement
     * through template specialization. The class is designed to work with an abstract `IFluid` interface,
     * allowing it to be used with any fluid model that conforms to this interface.
     *
     * The `FlashResults` class is versatile, offering methods to query a single property, multiple
     * properties at once, or properties specified at runtime. It also provides functionality to specify
     * the unit system for the property query, with a default of MolarUnits. This makes it a critical
     * component for applications requiring detailed and flexible post-calculation analysis of fluid properties.
     *
     * Usage of this class involves initializing it with a fluid object and the desired initial properties
     * and their units. Subsequently, the `property` or `properties` methods can be used to query the fluid's
     * properties post-flash calculation.
     *
     * Examples of use include querying the temperature, pressure, composition, and other thermodynamic
     * properties of a fluid after a flash calculation, with the ability to specify the desired unit system
     * for each query.
     *
     * @note This class assumes the fluid object passed to it supports the `IFluid` interface, which includes
     * methods for setting the fluid state and querying its properties.
     */
    class FlashResults
    {
        IFluid m_fluid;    ///< Holds the fluid object for which the flash calculation was performed.

    public:
        /**
         * @brief Constructs a FlashResults object with a specified fluid and its properties, given that the properties meet a specific
         * specification.
         *
         * @tparam P1 The type of the first property, conforming to the `IsProperty` concept and meeting the `IsSpecification<P1, P2>`
         * requirement.
         * @tparam P2 The type of the second property, conforming to the `IsProperty` concept and meeting the `IsSpecification<P1, P2>`
         * requirement.
         * @tparam UNITS_T The unit system to use for the properties, defaulting to MolarUnits.
         * @param fluid The fluid object upon which the flash calculation is based.
         * @param p1 The first property for initializing the fluid's state.
         * @param p2 The second property for initializing the fluid's state.
         * @param _ A dummy parameter used to specify the unit system for the properties.
         *
         * @details This constructor initializes the FlashResults object with a fluid, along with two properties and their units, to set the
         * fluid's state post-flash calculation. The properties `P1` and `P2` are required to satisfy the `IsSpecification<P1, P2>`
         * constraint, ensuring that they form a valid specification for setting the fluid's state. This allows for more precise control
         * over the initialization of the fluid's state, ensuring that the properties used are compatible and meet certain criteria defined
         * by `IsSpecification`.
         *
         * @note This constructor adds a compile-time check to ensure that the provided properties `P1` and `P2` meet the specified
         * requirement, offering an additional layer of type safety.
         */
        template<IsProperty P1, IsProperty P2, typename UNITS_T = MolarUnits>
            requires IsSpecification<P1, P2>
        FlashResults(IFluid fluid, P1 p1, P2 p2, UnitsType<UNITS_T> _) : m_fluid(std::move(fluid))
        {
            m_fluid.setState<UNITS_T>(p1, p2);
        }

        /**
         * @brief Retrieves a specific property of the fluid in a specified unit system.
         *
         * @details This template function queries the fluid object for a specific property, specified by the
         * template parameter `PROPERTY_T`, using the unit system specified by `UNITS_T`. The function provides
         * flexibility in accessing fluid properties, allowing the caller to specify both the property and the
         * unit system at compile time. This is particularly useful for applications that need to retrieve various
         * properties of the fluid under different units without having to manually convert between unit systems.
         *
         * @tparam PROPERTY_T The type representing the property to be retrieved. This type should be one of the
         * predefined property types that the fluid object recognizes.
         * @tparam UNITS_T The unit system in which to retrieve the property. This template parameter defaults to
         * MolarUnits but can be overridden to specify a different unit system if required.
         *
         * @return The value of the requested property, in the units specified by `UNITS_T`. The exact return type
         * is determined by the `PROPERTY_T` template parameter.
         *
         * @note The fluid object must support the `property<PROPERTY_T, UNITS_T>()` method for this function to work.
         * This implies that the fluid object should be designed to handle queries for properties in various unit systems,
         * and have the necessary logic to return the correct value for the requested property and unit system.
         */
        template<typename PROPERTY_T, typename UNITS_T = MolarUnits>
        PROPERTY_T property() const
        {
            return m_fluid.property<PROPERTY_T, UNITS_T>();
        }

        /**
         * @brief Retrieves a specified property of the fluid in a given unit system, based on a runtime property identifier.
         *
         * @details This function template is designed to query the fluid object for a property specified at runtime through an enum
         * identifier, using the unit system specified by `UNITS_T`. It allows for flexible and dynamic retrieval of fluid properties,
         * accommodating cases where the property to be queried is determined at runtime rather than compile time. The function leverages
         * the templating system to ensure that property values are retrieved in the correct unit system, facilitating ease of use in varied
         * scientific and engineering applications where multiple unit systems are in use.
         *
         * @tparam UNITS_T The unit system in which to retrieve the property. This template parameter defaults to MolarUnits but can be
         * overridden to specify a different unit system if required. This allows for the querying of properties in units appropriate to the
         * context of the application.
         *
         * @param prop The property to be retrieved, specified as an enum of type Property. This parameter determines which property of the
         * fluid is queried.
         *
         * @return Returns the value of the requested property, in the units specified by `UNITS_T`. The return type is automatically
         * deduced based on the requested property and unit system. This design ensures that the function can be used flexibly for any
         * property type supported by the fluid object.
         *
         * @note This function requires that the fluid object's `property<UNITS_T>(Property)` method is capable of interpreting the property
         * enum and returning the corresponding property value in the requested unit system. It implies a level of dynamic flexibility in
         * the fluid object's implementation, allowing for property queries based on runtime decisions.
         */
        template<typename UNITS_T = MolarUnits>
        auto property(Property::Type prop) const
        {
            return m_fluid.property<UNITS_T>(prop);
        }

        /**
         * @brief Retrieves a specified property of the fluid using a string identifier, in a given unit system.
         *
         * @details This function template offers an interface for dynamically querying properties of the fluid based on string identifiers,
         * using the unit system specified by `UNITS_T`. It is particularly useful in contexts where the property to be queried is
         * determined at runtime, such as when interpreting user input or processing data from external sources. The function supports
         * flexible retrieval of properties, adapting to various unit systems as required by the application. By leveraging template and
         * function overloading, it provides a consistent and user-friendly mechanism for accessing fluid properties without the need for
         * manual conversion between different unit systems or property naming conventions.
         *
         * @tparam UNITS_T The unit system in which to retrieve the property. Defaults to MolarUnits, but can be overridden to specify a
         * different unit system, accommodating diverse application requirements. This flexibility ensures that properties can be queried in
         * units that are most relevant or convenient for the specific context of use.
         *
         * @param propString A string representing the property to be retrieved. This parameter allows for the specification of the property
         * in a flexible and dynamic manner, accommodating a wide range of property identifiers that may not be known until runtime.
         *
         * @return The value of the requested property, in the units specified by `UNITS_T`. The return type is deduced automatically based
         * on the property and the unit system, facilitating ease of use and integration into applications. This design supports a broad
         * range of property types and values, ensuring the function's applicability across various domains and use cases.
         *
         * @note The fluid object must implement a `property<UNITS_T>(const std::string&)` method capable of understanding the string-based
         * property identifiers and returning the corresponding property value in the specified unit system. This requirement underscores
         * the necessity for a flexible and extensible fluid model capable of accommodating dynamic property queries.
         */
        template<typename UNITS_T = MolarUnits>
        auto property(const std::string& propString) const
        {
            return m_fluid.property<UNITS_T>(propString);
        }

        /**
         * @brief Retrieves multiple static properties of the fluid simultaneously.
         *
         * @details This template function is designed to query the fluid object for multiple properties at once, leveraging
         * variadic templates to allow the caller to specify any number of property types. The function enforces a compile-time
         * requirement that at least one property type must be specified, ensuring that the call is meaningful. It is particularly
         * useful for scenarios where multiple related properties need to be retrieved in a single operation, improving performance
         * and reducing verbosity compared to querying each property individually.
         *
         * @tparam PROPERTIES_T Variadic template parameter list representing the types of properties to be retrieved. Each type
         * in this list should be one of the predefined property types recognized by the fluid object. The constraint ensures that
         * at least one property type is specified, leveraging the power of modern C++ to enhance type safety and intention clarity.
         *
         * @return Returns an instance of `StaticProperties<PROPERTIES_T...>`, a templated structure designed to hold the requested
         * properties in a type-safe manner. The `StaticProperties` structure provides access to the values of the specified properties,
         * each in their respective type as determined by the template parameters. This design allows for efficient and convenient
         * access to multiple fluid properties with minimal overhead.
         *
         * @note This function assumes the existence of a `StaticProperties<PROPERTIES_T...>` template that is capable of aggregating
         * and providing access to the specified properties. The fluid object must support querying for each of the properties specified
         * by `PROPERTIES_T` types, ensuring compatibility between the fluid model and this function's requirements.
         */
        template<typename... PROPERTIES_T>
            requires(sizeof...(PROPERTIES_T) >= 1)
        auto properties() const
        {
            return StaticProperties<PROPERTIES_T...>(m_fluid);
        }

        /**
         * @brief Retrieves a set of dynamic properties of the fluid specified at runtime.
         *
         * @details This function provides the capability to query the fluid object for a set of properties
         * specified by an initializer list of property enums at runtime. It is designed for scenarios where
         * the properties to be queried cannot be known at compile time and must be determined based on runtime
         * conditions or user inputs. This flexibility allows for a highly adaptable interface to fluid property
         * retrieval, accommodating a wide range of use cases and application requirements.
         *
         * The function constructs a `DynamicProperties` object, which encapsulates the queried properties and
         * offers an interface for accessing their values. This approach enables efficient and convenient access
         * to multiple properties with minimal overhead and supports dynamic adjustment of the queried properties
         * based on application logic or user interaction.
         *
         * @param proplist An initializer list of `Property` enums specifying the properties to be queried. Each
         * element in this list represents a property identifier that the fluid object understands and can retrieve.
         *
         * @return Returns an instance of `DynamicProperties`, a structure designed to hold and provide access to
         * the values of dynamically specified properties. This object offers methods to access each queried property,
         * with the specific interface depending on the implementation of `DynamicProperties`.
         *
         * @note The implementation of `DynamicProperties` and the fluid object must support the concept of dynamically
         * querying properties based on runtime-specified identifiers. This requirement ensures that the function can
         * be effectively used to adapt to various application scenarios where fixed property queries are insufficient.
         */
        auto properties(std::initializer_list<Property::Type> proplist) const    // NOLINT
        {
            return DynamicProperties(m_fluid, std::vector(proplist.begin(), proplist.end()));
        }

        /**
         * @brief Retrieves a set of dynamic properties of the fluid specified by a container of property enums.
         *
         * @details This function template extends the flexibility of querying fluid properties dynamically by allowing
         * the caller to specify a container of property enums. It leverages template constraints to ensure that the
         * function is only instantiated with containers whose value type is `Property`, thereby maintaining type safety
         * and clarity of intent. This approach is particularly useful in scenarios where the properties to be queried
         * are determined at runtime and may be stored or managed in standard container types, such as vectors or lists.
         *
         * The function constructs a `DynamicProperties` object, encapsulating the queried properties and offering an
         * interface for accessing their values. This design facilitates efficient and convenient access to a dynamic
         * set of properties, supporting a wide range of application requirements and user scenarios.
         *
         * @tparam CONTAINER_T The type of the container holding the property enums. This type must meet the requirement
         * that its `value_type` is `Property`, ensuring compatibility and correctness in the queried properties.
         *
         * @param proplist A constant reference to a container of `Property` enums specifying the properties to be queried.
         * Each element in this container represents a property identifier understood by the fluid object.
         *
         * @return Returns an instance of `DynamicProperties`, designed to hold and provide access to the values of the
         * properties specified by the `proplist` container. The interface of `DynamicProperties` enables access to each
         * queried property's value, with specifics depending on its implementation.
         *
         * @note The fluid object and the implementation of `DynamicProperties` must support dynamic property queries based
         * on the identifiers provided in the `proplist` container. This requirement ensures that the function can be used
         * effectively in various dynamic and flexible application scenarios.
         */
        template<typename CONTAINER_T>
            requires std::same_as<typename CONTAINER_T::value_type, Property::Type>
        auto properties(const CONTAINER_T& proplist) const
        {
            return DynamicProperties(m_fluid, std::vector(proplist.begin(), proplist.end()));
        }

        /**
         * @brief Retrieves a set of dynamic properties of the fluid specified by string identifiers at runtime.
         *
         * @details This function offers a flexible way to query the fluid object for a set of properties identified
         * by strings. It is designed to accommodate scenarios where the properties to be queried are specified at runtime,
         * potentially based on user input or external data sources. By accepting an initializer list of string identifiers,
         * this function allows for a high degree of flexibility and dynamism in accessing fluid properties, making it suitable
         * for applications that require runtime determination of property queries.
         *
         * Upon invocation, the function constructs a `DynamicProperties` object that encapsulates the requested properties
         * and provides an interface for accessing their values. This approach ensures efficient and convenient access to a
         * dynamically specified set of properties, supporting varied and flexible application requirements.
         *
         * @param proplist An initializer list of strings, where each string represents a property identifier. These identifiers
         * are used to query the corresponding properties of the fluid, and thus must match the property names expected by the
         * fluid object.
         *
         * @return Returns an instance of `DynamicProperties`, a structure designed to hold and provide access to the values of
         * the dynamically specified properties. The `DynamicProperties` object offers methods for accessing the value of each
         * queried property, with the specifics of this interface depending on its implementation.
         *
         * @note The fluid object and the `DynamicProperties` implementation must support property queries based on string
         * identifiers, including the ability to interpret these identifiers and retrieve the corresponding property values.
         * This requirement underscores the need for a flexible and extensible fluid model capable of handling dynamic property
         * queries.
         */
        auto properties(std::initializer_list<std::string> proplist) const    // NOLINT
        {
            return DynamicProperties(m_fluid, std::vector(proplist.begin(), proplist.end()));
        }

        /**
         * @brief Retrieves a set of dynamic properties of the fluid specified by a container of string identifiers.
         *
         * @details This function template provides a powerful and flexible mechanism for querying properties of the fluid object
         * based on a set of string identifiers contained within any container conforming to the requirement that its `value_type`
         * is `std::string`. This design allows for dynamic property queries that are determined at runtime, making it ideal for
         * applications requiring the ability to adapt to varying property requirements, such as those specified by user input or
         * derived from external data sources.
         *
         * The function utilizes a template constraint to ensure type safety, only allowing instantiation with containers whose
         * elements are strings. Upon invocation, it constructs a `DynamicProperties` object, which encapsulates the queried
         * properties and offers an interface for accessing their values. This approach ensures efficient and convenient access
         * to a dynamically specified set of properties, enhancing the adaptability and flexibility of the application.
         *
         * @tparam CONTAINER_T The type of the container holding the string identifiers for the properties. This container type
         * must meet the requirement that its `value_type` is `std::string`, ensuring that the properties can be correctly
         * identified and queried.
         *
         * @param proplist A constant reference to a container of strings, where each string represents a property identifier.
         * These identifiers are used to query the corresponding properties of the fluid, and thus must match the property names
         * expected by the fluid object.
         *
         * @return Returns an instance of `DynamicProperties`, a structure designed to hold and provide access to the values of
         * the properties specified by the `proplist` container. This object provides methods for accessing the value of each
         * queried property, with the specifics of this interface depending on its implementation.
         *
         * @note The implementation of both the fluid object and the `DynamicProperties` structure must support dynamic property
         * queries based on string identifiers. This includes the ability to interpret the identifiers provided in the `proplist`
         * container and to retrieve the corresponding property values, ensuring that the function can be effectively used across
         * a wide range of dynamic and flexible application scenarios.
         */
        template<typename CONTAINER_T>
            requires std::same_as<typename CONTAINER_T::value_type, std::string>
        auto properties(const CONTAINER_T& proplist) const
        {
            return DynamicProperties(m_fluid, std::vector(proplist.begin(), proplist.end()));
        }
    };

}    // namespace KProps::detail