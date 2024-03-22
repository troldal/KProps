//
// Created by kenne on 08/03/2024.
//

#pragma once

#include <utility>

#include <KPropsUtils.hpp>

#include "../Interfaces/IFluid.hpp"

#include "../Utils/Concepts.hpp"

namespace KProps::detail
{

    /**
     * @brief Generates a default value for the specified property type.
     *
     * @tparam PROPERTY_T The type of the property for which a default value is to be generated. This function template
     * specializes the default value based on whether `PROPERTY_T` is the same as the `Phase` type or any other type.
     *
     * @return Returns a default value for the property type specified by `PROPERTY_T`. The specific value returned
     * depends on the compile-time check against the `Phase` type. For `Phase`, it returns `Phase::Unknown`; for all
     * other types, it returns a default-constructed instance of `PROPERTY_T` initialized to NaN.
     */
    template<typename PROPERTY_T>
    PROPERTY_T makeDefault()
    {
        if constexpr (std::same_as<PROPERTY_T, Phase>)
            return Phase::State::Unknown;
        else
            return PROPERTY_T { std::nan("") };
    }

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

    /**
     * @brief Base class template for fluid property classes.
     *
     * @details This class template provides a foundational implementation for fluid property classes, encapsulating
     * a fluid object and defining common behaviors and restrictions. It is designed to be inherited by specific fluid
     * property classes, which can then extend its functionality to provide access to various fluid properties.
     *
     * The class restricts copying and moving to prevent unintended duplication or transfer of the internal fluid object,
     * ensuring that fluid property classes maintain a clear and consistent relationship with the fluid they represent.
     * This design promotes safe and predictable usage patterns in client code, aligning with modern C++ best practices
     * for resource management.
     *
     * @tparam DERIVED The type of the derived class that inherits from `PropertiesBase`. This pattern allows the base
     * class to provide functionality that is accessible only to the derived class, facilitating a controlled and
     * extensible design.
     *
     * Usage of this class involves defining a derived class that inherits from `PropertiesBase`, providing specific
     * implementations or extensions as needed to support the desired fluid property interactions.
     *
     * @note This class serves as a foundational component within a larger framework for managing and accessing fluid
     * properties. It is intended for use as a base class and should not be instantiated directly in client code.
     */
    template<typename DERIVED>
    class PropertiesBase
    {
        friend DERIVED;    ///< Grants access to the derived class, allowing it to utilize protected members of this base class.

        IFluid m_fluid;    ///< Encapsulated fluid object, representing the fluid associated with this set of properties.

    protected:
        ~PropertiesBase() = default;    ///< Default destructor to ensure proper cleanup and resource management.

    public:
        /**
         * @brief Constructs a PropertiesBase instance with an associated fluid object.
         * @param fluid The fluid object to be associated with this instance, enabling property queries and manipulations.
         */
        explicit PropertiesBase(IFluid fluid) : m_fluid { std::move(fluid) } {}

        PropertiesBase(const PropertiesBase&)     = delete;    ///< Deleted copy constructor.
        PropertiesBase(PropertiesBase&&) noexcept = delete;    ///< Deleted move constructor.

        PropertiesBase& operator=(const PropertiesBase&)     = delete;    ///< Deleted copy assignment operator.
        PropertiesBase& operator=(PropertiesBase&&) noexcept = delete;    ///< Deleted move assignment operator.
    };

    /**
     * @brief Represents a collection of static properties for a fluid object.
     *
     * @details This class template extends `PropertiesBase` to enable retrieval of multiple fluid properties at once, specified
     * at compile time. It supports various forms of output, including tuples, user-defined structures, and containers, providing
     * flexibility in how properties are accessed and utilized. This class is ideal for scenarios where a fixed set of fluid properties
     * needs to be retrieved efficiently and in a type-safe manner.
     *
     * @tparam PROPERTIES_T A variadic list of property types to be retrieved. These should conform to the `IsProperty` concept, ensuring
     * that only valid property types are specified.
     */
    template<IsProperty... PROPERTIES_T>
    class StaticProperties : public PropertiesBase<StaticProperties<PROPERTIES_T...>>
    {
        using BASE = PropertiesBase<StaticProperties<PROPERTIES_T...>>;

    public:
        using BASE::BASE;    // Inherit constructor from PropertiesBase.

        /**
         * @brief Retrieves the specified properties in a tuple, using the specified unit system.
         *
         * @details This function template retrieves each specified property of the fluid and returns them in a
         * `std::tuple`, with each property converted into the specified unit system. This method is suitable
         * for when properties need to be accessed directly and possibly unpacked using structured bindings.
         *
         * @tparam UNITS_T The unit system in which to retrieve the properties. Defaults to MolarUnits, but
         * MassUnits can also be specified. This parameter allows for the specification of the unit system at
         * the point of property retrieval.
         *
         * @return A `std::tuple` containing the requested properties, each converted to the specified unit system.
         *
         * @note The unit system (`UNITS_T`) must be either `MolarUnits` or `MassUnits`.
         */
        template<typename UNITS_T = MolarUnits>
            requires std::same_as<UNITS_T, MolarUnits> || std::same_as<UNITS_T, MassUnits>
        auto get() &&
        {
            return std::make_tuple(BASE::m_fluid.template property<PROPERTIES_T, UNITS_T>()...);
        }

        /**
         * @brief Converts the retrieved properties into a user-defined structure.
         *
         * @details Retrieves the specified properties, converts them to the specified unit system, and then
         * converts the result into a user-defined structure `STRUCT_T`, facilitating easy access to properties
         * within custom data structures.
         *
         * @tparam STRUCT_T The type of the user-defined structure to which the properties will be converted.
         * @tparam UNITS_T The unit system in which to retrieve the properties. Defaults to MolarUnits, but
         * MassUnits can also be specified.
         *
         * @return An instance of `STRUCT_T` containing the requested properties, each converted to the specified
         * unit system.
         *
         * @note The function enforces that `UNITS_T` must be either `MolarUnits` or `MassUnits`, and `STRUCT_T`
         * cannot be `MolarUnits` or `MassUnits`.
         */
        template<typename STRUCT_T, typename UNITS_T = MolarUnits>
            requires(std::same_as<UNITS_T, MolarUnits> || std::same_as<UNITS_T, MassUnits>) && (!std::same_as<STRUCT_T, MolarUnits>) &&
                    (!std::same_as<STRUCT_T, MassUnits>)
        STRUCT_T get() &&
        {
            return tupleToStruct<STRUCT_T>(std::make_tuple(BASE::m_fluid.template property<PROPERTIES_T, UNITS_T>()...));
        }

        /**
         * @brief Retrieves specified properties in a user-defined, tuple-like container, using a specified unit system.
         *
         * @details This member function template provides the capability to query and retrieve multiple fluid properties,
         * specified at compile-time, and store them in a user-defined tuple-like container. It utilizes template template parameters
         * and compile-time checks to ensure that the specified container is tuple-like. The properties are retrieved in the unit
         * system specified by `UNITS_T` and returned in an instance of the user-defined tuple-like container `TUPLE_T`.
         *
         * The function demonstrates the use of advanced C++ template and type traits techniques to offer flexible and type-safe
         * retrieval of fluid properties. It is particularly useful in scenarios where custom data structures are preferred over
         * standard library containers for holding fluid properties, allowing for integration with application-specific type systems
         * or data handling paradigms.
         *
         * @tparam TUPLE_T The user-defined tuple-like container template to use for holding the properties. This container must
         * adhere to the tuple-like interface and structure. The requirement is checked at compile time using a concept or requires
         * clause, ensuring that only suitable types are used.
         * @tparam UNITS_T The unit system in which to retrieve the properties. Defaults to MolarUnits, but can be overridden to
         * specify a different unit system as needed.
         *
         * @return An instance of `TUPLE_T` containing the requested properties, each converted to the specified unit system. The
         * types of the properties within `TUPLE_T` are determined by `PROPERTIES_T...`, ensuring that the return type accurately
         * reflects the queried properties in a type-safe manner.
         *
         * @note This function relies on a compile-time check to verify that `TUPLE_T` is tuple-like, using the `detail::IsTuple`
         * utility. This check ensures that the function template is only instantiated with compatible container types, promoting
         * type safety and preventing misuse.
         */
        template<template<typename...> typename TUPLE_T, typename UNITS_T = MolarUnits>
            requires detail::IsTuple<TUPLE_T<double, int>>    // Check if container is tuple-like
        auto get() &&
        {
            return TUPLE_T<PROPERTIES_T...> { BASE::m_fluid.template property<PROPERTIES_T, UNITS_T>()... };
        }

        /**
         * @brief Retrieves specified properties in a user-defined, homogeneous container, using a specified unit system.
         *
         * @details This function template queries multiple fluid properties, specified at compile-time, and stores them in a
         * user-defined container that conforms to homogeneous container semantics. The properties are retrieved in the unit system
         * specified by `UNITS_T` and are added to the container, which is then returned. This approach allows for flexible and
         * efficient collection of fluid properties, facilitating integration with custom data handling or storage mechanisms.
         *
         * The function employs compile-time checks to ensure that the specified container is suitable for holding the queried
         * properties, enhancing type safety and preventing misuse. This is achieved through the use of template template parameters,
         * fold expressions, and concepts or requires clauses, showcasing modern C++ template programming techniques.
         *
         * @tparam CONTAINER_T The user-defined container template to use for holding the properties. The container must support
         * the `emplace_back` method and be capable of holding elements of type `FLOAT`. The suitability of the container is
         * verified at compile time using a custom check.
         * @tparam UNITS_T The unit system in which to retrieve the properties. Defaults to MolarUnits but can be overridden to
         * specify a different unit system, providing flexibility in how properties are represented.
         *
         * @return A `CONTAINER_T<FLOAT>` instance containing the requested properties, each converted to the specified unit system
         * and stored as `FLOAT`. The container is dynamically populated with the property values, allowing for efficient and
         * flexible property collection.
         *
         * @note The function relies on the `detail::IsContainer` utility to verify at compile time that `CONTAINER_T` adheres to
         * the expected container interface, specifically ensuring that it can hold elements of type `FLOAT` and supports the
         * `emplace_back` method. This compile-time check promotes type safety and ensures compatibility with the function's
         * requirements.
         */
        template<template<typename...> typename CONTAINER_T, typename UNITS_T = MolarUnits>    // typename VALUE_T = FLOAT>
            requires detail::IsContainer<CONTAINER_T<Property>>    // Check if container is a homogeneous container
        auto get() &&
        {
            CONTAINER_T<Property> container;
            // Adjust the container's size upfront, which might lead to default initialization of elements
            container.resize(sizeof...(PROPERTIES_T), T { std::nan("") });

            // Since direct emplacement is not ideal after resize (due to default initialization),
            // we should assign the values. Assuming we can iterate and assign:
            auto it = container.begin();
            ((*(it++) = BASE::m_fluid.template property<PROPERTIES_T, UNITS_T>()), ...);

            return container;
        }
    };

    /**
     * @brief Manages dynamic retrieval of fluid properties specified at runtime.
     *
     * @details This class extends `PropertiesBase` to facilitate dynamic querying of fluid properties. It is designed to
     * accommodate scenarios where the set of properties to be retrieved cannot be known at compile time and must be
     * specified at runtime. The class stores a collection of property identifiers and provides a method to retrieve their
     * values in a specified unit system, encapsulated in a user-defined container.
     *
     * @tparam TYPE The type of property identifiers stored in this class, typically a variant or enumeration that represents
     * different possible fluid properties.
     */
    // template<typename TYPE>
    // requires std::same_as<TYPE, Property::Type> || std::same_as<TYPE, std::string>
    class DynamicProperties : public PropertiesBase<DynamicProperties>
    {
        using BASE = PropertiesBase<DynamicProperties>;

        std::vector<Property::Type> m_properties {};    ///< A vector of property identifiers for dynamic querying.

    public:
        /**
         * @brief Constructs a `DynamicProperties` instance with an associated fluid object and a collection of property identifiers.
         *
         * @param fluid The fluid object to which the dynamic properties pertain.
         * @param properties A vector of property identifiers specifying which properties are to be dynamically queried.
         */

        DynamicProperties(IFluid fluid, std::vector<Property::Type> properties)
            : BASE(std::move(fluid)),
              m_properties { std::move(properties) }
        {}

        DynamicProperties(IFluid fluid, std::vector<std::string> properties)
            : BASE(std::move(fluid)),
              m_properties { [&] {
                  std::vector<Property::Type> result;
                  result.reserve(properties.size());
                  for (const auto& prop : properties) result.emplace_back(Property::typeFromString(prop));
                  return result;
              }() }
        {}

        /**
         * @brief Retrieves the specified properties in a user-defined, homogeneous container.
         *
         * @details Queries the fluid object for the properties specified at runtime and stores them in a
         * user-defined container. This method allows for flexible and efficient retrieval of a dynamic set of
         * properties, supporting a wide range of application requirements and user scenarios.
         *
         * @tparam CONTAINER_T The user-defined container template to use for holding the properties. This container
         * must support the `emplace_back` method and be capable of holding elements of type `PropertyVariant`.
         * @tparam UNITS_T The unit system in which to retrieve the properties. Defaults to MolarUnits but can be
         * overridden to specify a different unit system, offering flexibility in property representation.
         *
         * @return A `CONTAINER_T<PropertyVariant>` instance containing the requested properties, each converted to
         * the specified unit system and stored as `PropertyVariant`. The container is dynamically populated with the
         * property values, allowing for flexible property collection.
         *
         * @note The function relies on a compile-time check, using the `detail::IsContainer` utility, to verify that
         * `CONTAINER_T` adheres to the expected container interface, specifically ensuring that it can hold elements
         * of type `PropertyVariant` and supports the `emplace_back` method.
         */
        template<template<typename...> typename CONTAINER_T, typename UNITS_T = MolarUnits>    // typename VALUE_T = FLOAT>
            requires detail::IsContainer<CONTAINER_T<Property>>    // Check if container is a homogeneous container
        auto get() &&
        {
            CONTAINER_T<Property> container;
            container.resize(m_properties.size(), T { std::nan("") });    // Optimize for number of elements

            std::transform(m_properties.begin(), m_properties.end(), container.begin(), [this](auto prop) {
                return m_fluid.property<UNITS_T>(prop);
            });

            return container;
        }
    };

}    // namespace KProps::detail
