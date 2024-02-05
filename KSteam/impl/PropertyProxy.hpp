//
// Created by kenne on 31/01/2024.
//

#pragma once

#include "FunctionsPT.hpp"
#include "FunctionsPX.hpp"
#include "Properties.hpp"

#include <optional>
#include <tuple>

namespace KSteam::detail
{

    // Concept to check for tuple-like types
    template<typename T>
    concept TupleLike = requires { typename std::tuple_size<T>::type; };

    // Concept to check for homogeneous containers (like std::vector)
    template<typename T>
    concept HomogeneousContainer = requires(T t) {
        typename T::value_type;
        { t.emplace_back(std::declval<typename T::value_type>()) };
    };

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
    Struct tuple_to_struct_impl(Tuple&& tuple, std::index_sequence<I...>)
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
    Struct tuple_to_struct(Tuple&& tuple)
    {
        return tuple_to_struct_impl<Struct>(std::forward<Tuple>(tuple),
                                            std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>> {});
    }

    template<typename PROP, typename S1, typename S2>
        requires IsSpecification<S1, S2>
    auto callSpecFunction(S1 s1, S2 s2)
    {
        if constexpr (IsSpecificationPT<S1, S2>) {
            if constexpr (std::is_same_v<PROP, P>) return std::get<PressureCalc>(PropertyFunctionsPT)(s1, s2);
            if constexpr (std::is_same_v<PROP, T>) return std::get<TemperatureCalc>(PropertyFunctionsPT)(s1, s2);
            if constexpr (std::is_same_v<PROP, PSat>) return std::get<SaturationPressureCalc>(PropertyFunctionsPT)(s1, s2);
            if constexpr (std::is_same_v<PROP, TSat>) return std::get<SaturationTemperatureCalc>(PropertyFunctionsPT)(s1, s2);
            if constexpr (std::is_same_v<PROP, Rho>) return std::get<DensityCalc>(PropertyFunctionsPT)(s1, s2);
            if constexpr (std::is_same_v<PROP, V>) return std::get<VolumeCalc>(PropertyFunctionsPT)(s1, s2);
            if constexpr (std::is_same_v<PROP, H>) return std::get<EnthalpyCalc>(PropertyFunctionsPT)(s1, s2);
            if constexpr (std::is_same_v<PROP, S>) return std::get<EntropyCalc>(PropertyFunctionsPT)(s1, s2);
            if constexpr (std::is_same_v<PROP, U>) return std::get<InternalEnergyCalc>(PropertyFunctionsPT)(s1, s2);
            if constexpr (std::is_same_v<PROP, Cp>) return std::get<CpCalc>(PropertyFunctionsPT)(s1, s2);
            if constexpr (std::is_same_v<PROP, Cv>) return std::get<CvCalc>(PropertyFunctionsPT)(s1, s2);
            if constexpr (std::is_same_v<PROP, W>) return std::get<SpeedOfSoundCalc>(PropertyFunctionsPT)(s1, s2);
            if constexpr (std::is_same_v<PROP, Kappa>) return std::get<IsentropicExponentCalc>(PropertyFunctionsPT)(s1, s2);
            if constexpr (std::is_same_v<PROP, A>) return std::get<HelmholtzEnergyCalc>(PropertyFunctionsPT)(s1, s2);
            if constexpr (std::is_same_v<PROP, G>) return std::get<GibbsEnergyCalc>(PropertyFunctionsPT)(s1, s2);
            if constexpr (std::is_same_v<PROP, Z>) return std::get<CompressibilityFactorCalc>(PropertyFunctionsPT)(s1, s2);
            if constexpr (std::is_same_v<PROP, X>) return std::get<VaporQualityCalc>(PropertyFunctionsPT)(s1, s2);
            if constexpr (std::is_same_v<PROP, Eta>) return std::get<DynamicViscosityCalc>(PropertyFunctionsPT)(s1, s2);
            if constexpr (std::is_same_v<PROP, Nu>) return std::get<KinematicViscosityCalc>(PropertyFunctionsPT)(s1, s2);
            if constexpr (std::is_same_v<PROP, TC>) return std::get<ThermalConductivityCalc>(PropertyFunctionsPT)(s1, s2);
            if constexpr (std::is_same_v<PROP, PR>) return std::get<PrandtlNumberCalc>(PropertyFunctionsPT)(s1, s2);

            return 0.0;
        }

        if constexpr (IsSpecificationPH<S1, S2>) {
            std::cout << "PH Calc" << std::endl;
            return 0.0;
        }

        if constexpr (IsSpecificationPS<S1, S2>) {
            std::cout << "PS Calc" << std::endl;
            return 0.0;
        }

        if constexpr (IsSpecificationPU<S1, S2>) {
            std::cout << "PU Calc" << std::endl;
            return 0.0;
        }

        if constexpr (IsSpecificationPD<S1, S2>) {
            std::cout << "PD Calc" << std::endl;
            return 0.0;
        }

        if constexpr (IsSpecificationPV<S1, S2>) {
            std::cout << "PV Calc" << std::endl;
            return 0.0;
        }

        if constexpr (IsSpecificationPX<S1, S2>) {
            std::cout << "PX Calc" << std::endl;

            if constexpr (std::is_same_v<PROP, P>) return std::get<PressureCalc>(PropertyFunctionsPX)(s1, s2);
            if constexpr (std::is_same_v<PROP, T>) return std::get<TemperatureCalc>(PropertyFunctionsPX)(s1, s2);
            if constexpr (std::is_same_v<PROP, PSat>) return std::get<SaturationPressureCalc>(PropertyFunctionsPX)(s1, s2);
            if constexpr (std::is_same_v<PROP, TSat>) return std::get<SaturationTemperatureCalc>(PropertyFunctionsPX)(s1, s2);
            if constexpr (std::is_same_v<PROP, Rho>) return std::get<DensityCalc>(PropertyFunctionsPX)(s1, s2);
            if constexpr (std::is_same_v<PROP, V>) return std::get<VolumeCalc>(PropertyFunctionsPX)(s1, s2);
            if constexpr (std::is_same_v<PROP, H>) return std::get<EnthalpyCalc>(PropertyFunctionsPX)(s1, s2);
            if constexpr (std::is_same_v<PROP, S>) return std::get<EntropyCalc>(PropertyFunctionsPX)(s1, s2);
            if constexpr (std::is_same_v<PROP, U>) return std::get<InternalEnergyCalc>(PropertyFunctionsPX)(s1, s2);
            if constexpr (std::is_same_v<PROP, Cp>) return std::get<CpCalc>(PropertyFunctionsPX)(s1, s2);
            if constexpr (std::is_same_v<PROP, Cv>) return std::get<CvCalc>(PropertyFunctionsPX)(s1, s2);
            if constexpr (std::is_same_v<PROP, W>) return std::get<SpeedOfSoundCalc>(PropertyFunctionsPX)(s1, s2);
            if constexpr (std::is_same_v<PROP, Kappa>) return std::get<IsentropicExponentCalc>(PropertyFunctionsPX)(s1, s2);
            if constexpr (std::is_same_v<PROP, A>) return std::get<HelmholtzEnergyCalc>(PropertyFunctionsPX)(s1, s2);
            if constexpr (std::is_same_v<PROP, G>) return std::get<GibbsEnergyCalc>(PropertyFunctionsPX)(s1, s2);
            if constexpr (std::is_same_v<PROP, Z>) return std::get<CompressibilityFactorCalc>(PropertyFunctionsPX)(s1, s2);
            if constexpr (std::is_same_v<PROP, X>) return std::get<VaporQualityCalc>(PropertyFunctionsPX)(s1, s2);
            if constexpr (std::is_same_v<PROP, Eta>) return std::get<DynamicViscosityCalc>(PropertyFunctionsPX)(s1, s2);
            if constexpr (std::is_same_v<PROP, Nu>) return std::get<KinematicViscosityCalc>(PropertyFunctionsPX)(s1, s2);
            if constexpr (std::is_same_v<PROP, TC>) return std::get<ThermalConductivityCalc>(PropertyFunctionsPX)(s1, s2);
            if constexpr (std::is_same_v<PROP, PR>) return std::get<PrandtlNumberCalc>(PropertyFunctionsPX)(s1, s2);

            return 0.0;
        }

        if constexpr (IsSpecificationTH<S1, S2>) {
            std::cout << "TH Calc" << std::endl;
            return 0.0;
        }

        if constexpr (IsSpecificationTS<S1, S2>) {
            std::cout << "TS Calc" << std::endl;
            return 0.0;
        }

        if constexpr (IsSpecificationTU<S1, S2>) {
            std::cout << "TU Calc" << std::endl;
            return 0.0;
        }

        if constexpr (IsSpecificationTD<S1, S2>) {
            std::cout << "TD Calc" << std::endl;
            return 0.0;
        }

        if constexpr (IsSpecificationTV<S1, S2>) {
            std::cout << "TV Calc" << std::endl;
            return 0.0;
        }

        if constexpr (IsSpecificationTX<S1, S2>) {
            std::cout << "TX Calc" << std::endl;
            return 0.0;
        }

        if constexpr (IsSpecificationHS<S1, S2>) {
            std::cout << "HS Calc" << std::endl;
            return 0.0;
        }

        if constexpr (IsSpecificationUV<S1, S2>) {
            std::cout << "UV Calc" << std::endl;
            return 0.0;
        }

        if constexpr (IsSpecificationHV<S1, S2>) {
            std::cout << "HV Calc" << std::endl;
            return 0.0;
        }
    }

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
    template<typename SPEC1, typename SPEC2>
    class FlashResults
    {
        // Specification of the system
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
         * @tparam TUPLE_T Type of the tuple representing the properties.
         */
        template<typename TUPLE_T>
        class ResultProxy
        {
            TUPLE_T m_values {};

        public:
            /**
             * @brief Constructor for the ResultProxy.
             *
             * Initializes the proxy with the provided tuple of values.
             *
             * @param values Tuple of property values.
             */
            explicit ResultProxy(TUPLE_T values) : m_values { std::move(values) } {}

            // // Implicit conversion to user-defined struct
            // template<typename STRUCT_T>
            // operator STRUCT_T() const    // NOLINT
            // {
            //     return tuple_to_struct<STRUCT_T>(m_values);
            // }


            template<typename STRUCT_T>
            STRUCT_T get() const
            {
                return tuple_to_struct<STRUCT_T>(m_values);
            }

            template<template<typename...> typename STRUCT_T>
            auto get() const {
                return std::apply([](auto&&... args) {
                    return STRUCT_T<decltype(args)...>{std::forward<decltype(args)>(args)...};
                }, m_values);
            }

            // TUPLE_T get() const { return m_values; }
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
            if (!prop) prop = PROPERTY_T { callSpecFunction<PROPERTY_T>(m_spec.first, m_spec.second) };
            return prop.value();
        }

        template<typename PROPERTY_T>
        auto properties() const
        {
            using TUPLE_T = std::tuple<PROPERTY_T>;
            return ResultProxy<TUPLE_T>(std::make_tuple(property<PROPERTY_T>()));
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
            return ResultProxy<TUPLE_T>(get_tuple<P1, P2, Ps...>());
        }

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
            return tuple_to_struct<STRUCT_T>(get_tuple<P, T, H, S, U, A, G, Rho, V, PSat, TSat, Cp, Cv, Kappa, W, Z, X, Eta, Nu, TC, PR>());
        }

        template<template<typename...> typename STRUCT_T>
        requires TupleLike<STRUCT_T<double, double>>  // Check if ContainerType is tuple-like
        auto get() const
        {
            return std::apply([](auto&&... args) { return STRUCT_T<decltype(args)...> { std::forward<decltype(args)>(args)... }; },
                              get_tuple<P, T, H, S, U, A, G, Rho, V, PSat, TSat, Cp, Cv, Kappa, W, Z, X, Eta, Nu, TC, PR>());
        }

        template<template<typename...> typename ContainerType, typename VALUE_T = FLOAT>
        requires HomogeneousContainer<ContainerType<VALUE_T>>  // Check if ContainerType is a homogeneous container
        auto get() const {
            return std::apply([](auto&&... args) -> ContainerType<VALUE_T> {
                ContainerType<VALUE_T> container;
                container.reserve(sizeof...(args)); // Optimize for number of elements
                (container.emplace_back(static_cast<VALUE_T>(args)), ...);
                //(container.emplace_back(args), ...);
                return container;
            }, get_tuple<P, T, H, S, U, A, G, Rho, V, PSat, TSat, Cp, Cv, Kappa, W, Z, X, Eta, Nu, TC, PR>());
        }
    };

}    // namespace KSteam::detail
