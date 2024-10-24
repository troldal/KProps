//
// Created by kenne on 05/02/2024.
//

#pragma once

#include <KPropsUtils.hpp>

#include <tuple>

namespace KProps::detail
{

    // Concept to check for tuple-like types
    template<typename T>
    concept IsTuple = requires { typename std::tuple_size<T>::type; };

    // Concept to check for homogeneous containers (like std::vector)
    template<typename T>
    concept IsContainer = requires(T t) {
        typename T::value_type;
        {
            t.emplace_back(std::declval<typename T::value_type>())
        };
    };

    template<typename T>
    concept HasVolume = requires(T t) {
        {
            t.volume()
        } -> std::convertible_to<FLOAT>;    // Adjust the return type as needed
    };

    template<typename T>
    concept HasGibbsEnergy = requires(T t) {
        {
            t.gibbsEnergy()
        } -> std::convertible_to<FLOAT>;    // Adjust the return type as needed
    };

    template<typename T>
    concept HasHelmholtzEnergy = requires(T t) {
        {
            t.helmholtzEnergy()
        } -> std::convertible_to<FLOAT>;    // Adjust the return type as needed
    };

    template<typename T>
    concept HasSpeedOfSound = requires(T t) {
        {
            t.speedOfSound()
        } -> std::convertible_to<FLOAT>;    // Adjust the return type as needed
    };

    template<typename T>
    concept HasIsothermalCompressibility = requires(T t) {
        {
            t.isothermalCompressibility()
        } -> std::convertible_to<FLOAT>;    // Adjust the return type as needed
    };

    template<typename T>
    concept HasThermalExpansion = requires(T t) {
        {
            t.thermalExpansion()
        } -> std::convertible_to<FLOAT>;    // Adjust the return type as needed
    };

    template<typename T>
    concept HasCp = requires(T t) {
        {
            t.cp()
        } -> std::convertible_to<FLOAT>;    // Adjust the return type as needed
    };

    template<typename T>
    concept HasCv = requires(T t) {
        {
            t.cv()
        } -> std::convertible_to<FLOAT>;    // Adjust the return type as needed
    };

    template<typename T>
    concept HasSatP = requires(T t) {
        {
            t.saturationPressure()
        } -> std::convertible_to<FLOAT>;    // Adjust the return type as needed
    };

    template<typename T>
    concept HasSatT = requires(T t) {
        {
            t.saturationTemperature()
        } -> std::convertible_to<FLOAT>;    // Adjust the return type as needed
    };

    template<typename T>
    concept HasPhase = requires(T t) {
        {
            t.phase()
        } -> std::same_as<Phase>;    // Adjust the return type as needed
    };

    template<typename T>
    concept HasDynViscosity = requires(T t) {
        {
            t.dynamicViscosity()
        } -> std::convertible_to<FLOAT>;    // Adjust the return type as needed
    };

    template<typename T>
    concept HasKinViscosity = requires(T t) {
        {
            t.kinematicViscosity()
        } -> std::convertible_to<FLOAT>;    // Adjust the return type as needed
    };

    template<typename T>
    concept HasThermalConductivity = requires(T t) {
        {
            t.thermalConductivity()
        } -> std::convertible_to<FLOAT>;    // Adjust the return type as needed
    };

    template<typename T>
    concept HasPrandtlNumber = requires(T t) {
        {
            t.prandtlNumber()
        } -> std::convertible_to<FLOAT>;    // Adjust the return type as needed
    };

    template<typename T>
    concept HasZ = requires(T t) {
        {
            t.compressibility()
        } -> std::convertible_to<FLOAT>;    // Adjust the return type as needed
    };

    template<typename TYPE>
    concept SupportsSpecPT = requires(TYPE type, P p, T t) {
        {
            type.setStatePT(p, t)
        };
    };

    template<typename TYPE>
    concept SupportsSpecPX = requires(TYPE type, P p, X x) {
        {
            type.setStatePX(p, x)
        };
    };

    template<typename TYPE>
    concept SupportsSpecPH = requires(TYPE type, P p, H h) {
        {
            type.setStatePH(p, h)
        };
    };

    template<typename TYPE>
    concept SupportsSpecPS = requires(TYPE type, P p, S s) {
        {
            type.setStatePS(p, s)
        };
    };

    template<typename TYPE>
    concept SupportsSpecDP = requires(TYPE type, Rho rho, P p) {
        {
            type.setStateDP(rho, p)
        };
    };

    template<typename TYPE>
    concept SupportsSpecDT = requires(TYPE type, Rho rho, T t) {
        {
            type.setStateDT(rho, t)
        };
    };

    template<typename TYPE>
    concept SupportsSpecDS = requires(TYPE type, Rho rho, S s) {
        {
            type.setStateDS(rho, s)
        };
    };

    template<typename TYPE>
    concept SupportsSpecDH = requires(TYPE type, Rho rho, H h) {
        {
            type.setStateDH(rho, h)
        };
    };

    template<typename TYPE>
    concept SupportsSpecDU = requires(TYPE type, Rho rho, U u) {
        {
            type.setStateDU(rho, u)
        };
    };

    template<typename TYPE>
    concept SupportsSpecHS = requires(TYPE type, H h, S s) {
        {
            type.setStateHS(h, s)
        };
    };

    template<typename TYPE>
    concept SupportsSpecPU = requires(TYPE type, P p, U u) {
        {
            type.setStatePU(p, u)
        };
    };

    template<typename TYPE>
    concept SupportsSpecTS = requires(TYPE type, T t, S s) {
        {
            type.setStateTS(t, s)
        };
    };

    template<typename TYPE>
    concept SupportsSpecTX = requires(TYPE type, T t, X x) {
        {
            type.setStateTX(t, x)
        };
    };

}    // namespace KProps::detail
