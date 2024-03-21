// //
// // Created by kenne on 18/02/2024.
// //
//
// #pragma once
//
// #include <KPropsUtils.hpp>
//
// #include "../Utils/Concepts.hpp"
//
//
// namespace KProps
// {
//     namespace detail {
//
//         /**
//          * @brief Helper function to unpack a tuple and initialize a struct.
//          *
//          * This function template unpacks the elements of a tuple and uses them to initialize
//          * a struct of type Struct.
//          *
//          * @tparam Struct The struct type to be initialized.
//          * @tparam Tuple The tuple type from which the struct is initialized.
//          * @tparam I Indices of the tuple elements.
//          * @param tuple Tuple containing the values for struct initialization.
//          * @return Struct An instance of Struct initialized with values from the tuple.
//          */
//         template<typename Struct, typename Tuple, std::size_t... I>
//         Struct tupleToStructImpl(Tuple&& tuple, std::index_sequence<I...>)
//         {
//             return Struct { std::get<I>(std::forward<Tuple>(tuple))... };
//         }
//
//         /**
//          * @brief Public function to convert a tuple to a struct.
//          *
//          * This function template provides a convenient way to convert a tuple into
//          * a struct of type Struct.
//          *
//          * @tparam Struct The struct type to be initialized.
//          * @tparam Tuple The tuple type from which the struct is initialized.
//          * @param tuple Tuple containing the values for struct initialization.
//          * @return Struct An instance of Struct initialized with values from the tuple.
//          */
//         template<typename Struct, typename Tuple>
//         Struct tupleToStruct(Tuple&& tuple)
//         {
//             return tupleToStructImpl<Struct>(std::forward<Tuple>(tuple),
//                                              std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>> {});
//         }
//     }
//
//     template<typename PROPERTY_T, typename UNITS_T = MolarUnits>
//     PROPERTY_T property(const IFluid& model);
//
//     template<typename... PROPERTIES_T>
//         requires(sizeof...(PROPERTIES_T) >= 1)
//     auto properties(const IFluid& model);
//
//     template<typename PROPERTY_T>
//         requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
//     PROPERTY_T saturation(const IFluid& fluid);
//
//     template<typename PROPERTY_T>
//         requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
//     PROPERTY_T critical(const IFluid& fluid);
//
//     template<typename PROPERTY_T>
//         requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
//     PROPERTY_T min(const IFluid& fluid);
//
//     template<typename PROPERTY_T>
//         requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
//     PROPERTY_T max(const IFluid& fluid);
//
//     namespace detail
//     {
//
//         /**
//          * @class PropertyProxy
//          * @brief A proxy class for efficiently fetching multiple properties from a fluid in various formats.
//          *
//          * @details PropertyProxy is designed to provide a flexible and efficient way to retrieve multiple fluid properties
//          * at once, supporting conversion to tuples, structs, or containers. It leverages template metaprogramming to allow
//          * users to specify the desired properties and units at compile time, offering strong type safety and reducing runtime
//          * overhead. The class also supports handling invalid states, returning NaN values for all requested properties if the
//          * proxy is marked as invalid.
//          *
//          * @tparam PROPERTIES_T A parameter pack of property types, indicating which properties to retrieve from the fluid.
//          */
//         template<IsProperty... PROPERTIES_T>
//         class PropertyProxy
//         {
//             IFluid m_fluid;
//             bool   m_isValid { true };
//
//         public:
//
//             /**
//              * @brief Constructor for PropertyProxy.
//              * @details Initializes the proxy with a fluid and an optional validity flag.
//              * @param fluid The fluid from which properties will be retrieved.
//              * @param isValid Optional flag indicating whether the proxy is valid. Defaults to true.
//              */
//             explicit PropertyProxy(IFluid fluid, bool isValid = true) : m_fluid { std::move(fluid) }, m_isValid { isValid } {}
//
//             PropertyProxy(const PropertyProxy&) = delete; /**< Deleted copy constructor. */
//             PropertyProxy(PropertyProxy&&)      = delete; /**< Deleted move constructor. */
//
//             PropertyProxy& operator=(const PropertyProxy&) = delete; /**< Deleted copy assignment operator. */
//             PropertyProxy& operator=(PropertyProxy&&)      = delete; /**< Deleted move assignment operator. */
//
//             ~PropertyProxy() = default; /**< Default destructor. */
//
//             /**
//              * @brief Retrieves the specified properties as a tuple in the requested units.
//              *
//              * @details This function template fetches the specified properties from the fluid and returns them as a tuple.
//              * If the PropertyProxy is marked as invalid, it returns a tuple filled with NaN values for each property. This
//              * approach allows for efficient, type-safe retrieval of multiple properties in a single call, supporting both
//              * MolarUnits and MassUnits through template specialization.
//              *
//              * Usage of this function is limited to contexts where the PropertyProxy object can be moved, ensuring that property
//              * retrieval is performed only once in a safe and controlled manner.
//              *
//              * @tparam UNITS_T The unit system in which to retrieve the properties. Must be either MolarUnits or MassUnits.
//              * Defaults to MolarUnits if not specified.
//              *
//              * @return A std::tuple containing the requested properties in the specified units. Each property is strongly typed
//              * according to the PROPERTIES_T template parameters, ensuring type safety.
//              *
//              * @note This function can only be called on rvalue references of PropertyProxy, i.e., temporary objects or objects
//              * explicitly moved. This ensures that the proxy's state is accessed in a controlled manner, preventing multiple
//              * retrievals that could lead to inconsistencies.
//              */
//             template<typename UNITS_T = MolarUnits>
//                 requires std::same_as<UNITS_T, MolarUnits> || std::same_as<UNITS_T, MassUnits>
//             auto get() &&
//             {
//                 if (!m_isValid) return std::make_tuple(PROPERTIES_T { std::nan("") }...);
//                 return std::make_tuple(m_fluid.property<PROPERTIES_T, UNITS_T>()...);
//             }
//
//             /**
//              * @brief Retrieves the specified properties, converting them to a user-defined struct in the requested units.
//              *
//              * @details This function template fetches the specified properties from the fluid and returns them converted into
//              * a user-defined struct. This allows for direct mapping of fluid properties into a struct, facilitating easy access
//              * to multiple properties within user code. If the PropertyProxy is marked as invalid, it returns a struct with NaN
//              * values for each field corresponding to the properties.
//              *
//              * The conversion relies on the `detail::tupleToStruct` utility, which maps a tuple of properties to the corresponding
//              * fields in the STRUCT_T type. This mechanism requires STRUCT_T to be structured in a way that matches the order and
//              * types of properties specified in PROPERTIES_T.
//              *
//              * @tparam STRUCT_T The struct type into which the properties should be converted. This type should not be one of the
//              * unit types (MolarUnits or MassUnits) to avoid template specialization conflicts.
//              * @tparam UNITS_T The unit system in which to retrieve the properties. Must be either MolarUnits or MassUnits. Defaults
//              * to MolarUnits if not specified.
//              *
//              * @return An instance of STRUCT_T containing the requested properties in the specified units.
//              *
//              * @note This function can only be called on rvalue references of PropertyProxy, i.e., temporary objects or objects
//              * explicitly moved. This constraint ensures that the proxy's state is accessed in a controlled manner, promoting
//              * safe and consistent use of the proxy.
//              */
//             template<typename STRUCT_T, typename UNITS_T = MolarUnits>
//                 requires(std::same_as<UNITS_T, MolarUnits> || std::same_as<UNITS_T, MassUnits>) && (!std::same_as<STRUCT_T, MolarUnits>) &&
//                         (!std::same_as<STRUCT_T, MassUnits>)
//             STRUCT_T get() &&
//             {
//                 if (!m_isValid) {
//                     auto result = std::make_tuple(PROPERTIES_T { std::nan("") }...);
//                     return detail::tupleToStruct<STRUCT_T>(result);
//                 }
//
//                 auto result = std::make_tuple(m_fluid.property<PROPERTIES_T, UNITS_T>()...);
//                 return detail::tupleToStruct<STRUCT_T>(result);
//             }
//
//             /**
//              * @brief Retrieves the specified properties as a tuple-like container in the requested units.
//              *
//              * @details This function template fetches the specified properties from the fluid and returns them in a tuple-like
//              * container specified by the user. It supports a generic way to gather multiple properties into a single, custom
//              * tuple-like structure, enhancing flexibility and integration with user-defined types or third-party tuple libraries.
//              * If the PropertyProxy is marked as invalid, it returns a container filled with NaN values for each property. This
//              * method allows for efficient and type-safe retrieval of properties, suitable for scenarios where custom tuple types
//              * are preferred over the standard std::tuple.
//              *
//              * @tparam TUPLE_T The template of the tuple-like container into which the properties should be aggregated. This
//              * template must be compatible with a tuple-like interface.
//              * @tparam UNITS_T The unit system in which to retrieve the properties. Must be either MolarUnits or MassUnits.
//              * Defaults to MolarUnits if not specified.
//              *
//              * @return A TUPLE_T container instance containing the requested properties in the specified units.
//              *
//              * @note The requirement `detail::IsTuple<TUPLE_T<double, double>>` checks if TUPLE_T is tuple-like, ensuring
//              * compatibility with the intended usage of this function. This function can only be called on rvalue references
//              * of PropertyProxy, i.e., temporary objects or objects explicitly moved, to ensure controlled access to the proxy's
//              * state and prevent inconsistent usage.
//              */
//             template<template<typename...> typename TUPLE_T, typename UNITS_T = MolarUnits>
//                 requires detail::IsTuple<TUPLE_T<double, double>>    // Check if container is tuple-like
//             auto get() &&
//             {
//                 if (!m_isValid) return TUPLE_T<PROPERTIES_T...> { PROPERTIES_T { std::nan("") }... };
//
//                 return TUPLE_T<PROPERTIES_T...> { m_fluid.property<PROPERTIES_T, UNITS_T>()... };
//             }
//
//             /**
//              * @brief Retrieves the specified properties as a homogeneous container of floats in the requested units.
//              *
//              * @details This function template fetches the specified properties from the fluid and stores them in a user-defined
//              * homogeneous container. It allows for the aggregation of multiple fluid properties into a single container, making it
//              * easier to handle and process these properties collectively. If the PropertyProxy is marked as invalid, the container
//              * is filled with NaN values for each property. This method is particularly useful for scenarios where properties need to
//              * be stored or processed in a dynamic or non-tuple format, offering flexibility in how properties are represented.
//              *
//              * The function also optimizes container storage by reserving space based on the number of properties being retrieved,
//              * minimizing potential reallocations.
//              *
//              * @tparam CONTAINER_T The template of the homogeneous container into which the properties should be aggregated. This
//              * template must support emplace_back or similar methods for adding elements. Examples include std::vector, std::list, etc.
//              * @tparam UNITS_T The unit system in which to retrieve the properties. Must be either MolarUnits or MassUnits.
//              * Defaults to MolarUnits if not specified.
//              *
//              * @return A CONTAINER_T instance containing the requested properties in the specified units.
//              *
//              * @note The requirement `detail::IsContainer<CONTAINER_T<FLOAT>>` ensures that CONTAINER_T is a container type
//              * compatible with storing float (or similar) types, enhancing the function's applicability to a wide range of
//              * standard and custom container types. This function can only be called on rvalue references of PropertyProxy,
//              * i.e., temporary objects or objects explicitly moved, promoting controlled and consistent access to the proxy's state.
//              */
//             template<template<typename...> typename CONTAINER_T, typename UNITS_T = MolarUnits>    // typename VALUE_T = FLOAT>
//                 requires detail::IsContainer<CONTAINER_T<FLOAT>>    // Check if container is a homogeneous container
//             auto get() &&
//             {
//                 CONTAINER_T<FLOAT> container;
//                 container.reserve(sizeof...(PROPERTIES_T));    // Optimize for number of elements
//
//                 if (!m_isValid)
//                     (container.emplace_back(PROPERTIES_T(std::nan("")).get()), ...);
//                 else
//                     (container.emplace_back(m_fluid.property<PROPERTIES_T, UNITS_T>().get()), ...);
//
//                 return container;
//             }
//         };
//
//     }    // namespace detail
//
//     template<typename PROPERTY_T, typename UNITS_T>
//     PROPERTY_T property(const IFluid& model)
//     {
//         return model.property<PROPERTY_T, UNITS_T>();
//     }
//
//     template<typename... PROPERTIES_T>
//         requires(sizeof...(PROPERTIES_T) >= 1)
//     auto properties(const IFluid& model)
//     {
//         return detail::PropertyProxy<PROPERTIES_T...>(model);
//     }
//
//     template<typename PROPERTY_T>
//         requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
//     PROPERTY_T saturation(const IFluid& fluid)
//     {
//         if constexpr (std::same_as<PROPERTY_T, T>)
//             return fluid.saturation<T>();
//         else
//             return fluid.saturation<P>();
//     }
//
//     template<typename PROPERTY_T>
//         requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
//     PROPERTY_T critical(const IFluid& fluid)
//     {
//         if constexpr (std::same_as<PROPERTY_T, T>)
//             return fluid.critical<T>();
//         else
//             return fluid.critical<P>();
//     }
//
//     template<typename PROPERTY_T>
//         requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
//     PROPERTY_T min(const IFluid& fluid)
//     {
//         if constexpr (std::same_as<PROPERTY_T, T>)
//             return fluid.min<T>();
//         else
//             return fluid.min<P>();
//     }
//
//     template<typename PROPERTY_T>
//         requires std::same_as<PROPERTY_T, T> || std::same_as<PROPERTY_T, P>
//     PROPERTY_T max(const IFluid& fluid)
//     {
//         if constexpr (std::same_as<PROPERTY_T, T>)
//             return fluid.max<T>();
//         else
//             return fluid.max<P>();
//     }
//
// }    // namespace pcprops
