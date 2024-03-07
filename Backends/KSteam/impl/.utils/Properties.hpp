//
// Created by kenne on 31/01/2024.
//

#pragma once

#include "../_external.hpp"

#include "../Config.hpp"

namespace KSteam
{

    enum class Property {
        T           = 0,
        Temperature = 0,

        P        = 1,
        Pressure = 1,

        H        = 2,
        Enthalpy = 2,

        S       = 3,
        Entropy = 3,

        U              = 4,
        InternalEnergy = 4,

        A               = 5,
        HelmholtzEnergy = 5,

        G           = 6,
        GibbsEnergy = 6,

        Rho     = 7,
        Density = 7,

        V      = 8,
        Volume = 8,
        Vol    = 8,

        PSat               = 9,
        SaturationPressure = 9,

        TSat                  = 10,
        SaturationTemperature = 10,

        Cp = 11,

        Cv = 12,

        Kappa              = 13,
        IsentropicExponent = 13,

        W            = 14,
        SpeedOfSound = 14,

        Z                     = 15,
        CompressibilityFactor = 15,

        X            = 16,
        Q            = 16,
        VaporQuality = 16,

        Eta              = 17,
        DynamicViscosity = 17,

        Nu                 = 18,
        KinematicViscosity = 18,

        TC                  = 19,
        ThermalConductivity = 19,

        PR            = 20,
        PrandtlNumber = 20

    };

    using T           = fluent::NamedType<FLOAT,
                                          struct TemperatureTag,
                                          fluent::Printable,
                                          fluent::Addable,
                                          fluent::Subtractable,
                                          fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Temperature = T;

    using P        = fluent::NamedType<FLOAT,
                                       struct PressureTag,
                                       fluent::Printable,
                                       fluent::Addable,
                                       fluent::Subtractable,
                                       fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Pressure = P;

    using H        = fluent::NamedType<FLOAT,
                                       struct EnthalpyTag,
                                       fluent::Printable,
                                       fluent::Addable,
                                       fluent::Subtractable,
                                       fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Enthalpy = H;

    using S       = fluent::NamedType<FLOAT,
                                      struct EntropyTag,
                                      fluent::Printable,
                                      fluent::Addable,
                                      fluent::Subtractable,
                                      fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Entropy = S;

    using U              = fluent::NamedType<FLOAT,
                                             struct InternalEnergyTag,
                                             fluent::Printable,
                                             fluent::Addable,
                                             fluent::Subtractable,
                                             fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using InternalEnergy = U;

    using A               = fluent::NamedType<FLOAT,
                                              struct HelmholtzEnergyTag,
                                              fluent::Printable,
                                              fluent::Addable,
                                              fluent::Subtractable,
                                              fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using HelmholtzEnergy = A;

    using G           = fluent::NamedType<FLOAT,
                                          struct GibbsEnergyTag,
                                          fluent::Printable,
                                          fluent::Addable,
                                          fluent::Subtractable,
                                          fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using GibbsEnergy = G;

    using Rho     = fluent::NamedType<FLOAT,
                                      struct DensityTag,
                                      fluent::Printable,
                                      fluent::Addable,
                                      fluent::Subtractable,
                                      fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Density = Rho;

    using V      = fluent::NamedType<FLOAT,
                                     struct VolumeTag,
                                     fluent::Printable,
                                     fluent::Addable,
                                     fluent::Subtractable,
                                     fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Volume = V;
    using Vol    = V;

    using PSat               = fluent::NamedType<FLOAT,
                                                 struct PSatTag,
                                                 fluent::Printable,
                                                 fluent::Addable,
                                                 fluent::Subtractable,
                                                 fluent::ImplicitlyConvertibleTo<FLOAT>::templ,
                                                 fluent::ImplicitlyConvertibleTo<P>::templ>;
    using SaturationPressure = PSat;

    using TSat                  = fluent::NamedType<FLOAT,
                                                    struct TSatTag,
                                                    fluent::Printable,
                                                    fluent::Addable,
                                                    fluent::Subtractable,
                                                    fluent::ImplicitlyConvertibleTo<FLOAT>::templ,
                                                    fluent::ImplicitlyConvertibleTo<T>::templ>;
    using SaturationTemperature = TSat;

    using PCrit            = fluent::NamedType<FLOAT,
                                               struct PCritTag,
                                               fluent::Printable,
                                               fluent::Addable,
                                               fluent::Subtractable,
                                               fluent::ImplicitlyConvertibleTo<FLOAT>::templ,
                                               fluent::ImplicitlyConvertibleTo<P>::templ>;
    using CriticalPressure = PCrit;

    using TCrit               = fluent::NamedType<FLOAT,
                                                  struct TCritTag,
                                                  fluent::Printable,
                                                  fluent::Addable,
                                                  fluent::Subtractable,
                                                  fluent::ImplicitlyConvertibleTo<FLOAT>::templ,
                                                  fluent::ImplicitlyConvertibleTo<T>::templ>;
    using CriticalTemperature = TCrit;

    using Cp = fluent::NamedType<FLOAT,
                                 struct CpTag,
                                 fluent::Printable,
                                 fluent::Addable,
                                 fluent::Subtractable,
                                 fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;

    using Cv = fluent::NamedType<FLOAT,
                                 struct CvTag,
                                 fluent::Printable,
                                 fluent::Addable,
                                 fluent::Subtractable,
                                 fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;

    using Kappa              = fluent::NamedType<FLOAT,
                                                 struct KappaTag,
                                                 fluent::Printable,
                                                 fluent::Addable,
                                                 fluent::Subtractable,
                                                 fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using IsentropicExponent = Kappa;

    using W            = fluent::NamedType<FLOAT,
                                           struct SpeedOfSoundTag,
                                           fluent::Printable,
                                           fluent::Addable,
                                           fluent::Subtractable,
                                           fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using SpeedOfSound = W;

    using Z                     = fluent::NamedType<FLOAT,
                                                    struct CompressibilityFactorTag,
                                                    fluent::Printable,
                                                    fluent::Addable,
                                                    fluent::Subtractable,
                                                    fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using CompressibilityFactor = Z;

    using X            = fluent::NamedType<FLOAT,
                                           struct VaporQualityTag,
                                           fluent::Printable,
                                           fluent::Addable,
                                           fluent::Subtractable,
                                           fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Q            = X;
    using VaporQuality = X;

    using Eta              = fluent::NamedType<FLOAT,
                                               struct DynamicViscosityTag,
                                               fluent::Printable,
                                               fluent::Addable,
                                               fluent::Subtractable,
                                               fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using DynamicViscosity = Eta;

    using Nu                 = fluent::NamedType<FLOAT,
                                                 struct KinematicViscosityTag,
                                                 fluent::Printable,
                                                 fluent::Addable,
                                                 fluent::Subtractable,
                                                 fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using KinematicViscosity = Nu;

    using TC                  = fluent::NamedType<FLOAT,
                                                  struct ThermalConductivityTag,
                                                  fluent::Printable,
                                                  fluent::Addable,
                                                  fluent::Subtractable,
                                                  fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using ThermalConductivity = TC;

    using PR            = fluent::NamedType<FLOAT,
                                            struct PrandtlNumberTag,
                                            fluent::Printable,
                                            fluent::Addable,
                                            fluent::Subtractable,
                                            fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using PrandtlNumber = PR;

    template<typename PROPERTY>
    concept IsProperty =
        std::same_as<PROPERTY, T> || std::same_as<PROPERTY, P> || std::same_as<PROPERTY, H> || std::same_as<PROPERTY, S> ||
        std::same_as<PROPERTY, U> || std::same_as<PROPERTY, A> || std::same_as<PROPERTY, G> || std::same_as<PROPERTY, Rho> ||
        std::same_as<PROPERTY, V> || std::same_as<PROPERTY, PSat> || std::same_as<PROPERTY, TSat> || std::same_as<PROPERTY, Cp> ||
        std::same_as<PROPERTY, Cv> || std::same_as<PROPERTY, Kappa> || std::same_as<PROPERTY, W> || std::same_as<PROPERTY, Z> ||
        std::same_as<PROPERTY, X> || std::same_as<PROPERTY, Eta> || std::same_as<PROPERTY, Nu> || std::same_as<PROPERTY, TC> ||
        std::same_as<PROPERTY, PR> || std::same_as<PROPERTY, PCrit> || std::same_as<PROPERTY, TCrit>;

    template<typename S1, typename S2>
    concept IsSpecificationPT = (std::same_as<S1, P> && std::same_as<S2, T>) || (std::same_as<S1, T> && std::same_as<S2, P>);

    template<typename S1, typename S2>
    concept IsSpecificationPH = (std::same_as<S1, P> && std::same_as<S2, H>) || (std::same_as<S1, H> && std::same_as<S2, P>);

    template<typename S1, typename S2>
    concept IsSpecificationPS = (std::same_as<S1, P> && std::same_as<S2, S>) || (std::same_as<S1, S> && std::same_as<S2, P>);

    template<typename S1, typename S2>
    concept IsSpecificationPU = (std::same_as<S1, P> && std::same_as<S2, U>) || (std::same_as<S1, U> && std::same_as<S2, P>);

    template<typename S1, typename S2>
    concept IsSpecificationPD = (std::same_as<S1, P> && std::same_as<S2, Density>) || (std::same_as<S1, Density> && std::same_as<S2, P>);

    template<typename S1, typename S2>
    concept IsSpecificationPV = (std::same_as<S1, P> && std::same_as<S2, V>) || (std::same_as<S1, V> && std::same_as<S2, P>);

    template<typename S1, typename S2>
    concept IsSpecificationPX = (std::same_as<S1, P> && std::same_as<S2, X>) || (std::same_as<S1, X> && std::same_as<S2, P>);

    template<typename S1, typename S2>
    concept IsSpecificationTH = (std::same_as<S1, T> && std::same_as<S2, H>) || (std::same_as<S1, H> && std::same_as<S2, T>);

    template<typename S1, typename S2>
    concept IsSpecificationTS = (std::same_as<S1, T> && std::same_as<S2, S>) || (std::same_as<S1, S> && std::same_as<S2, T>);

    template<typename S1, typename S2>
    concept IsSpecificationTU = (std::same_as<S1, T> && std::same_as<S2, U>) || (std::same_as<S1, U> && std::same_as<S2, T>);

    template<typename S1, typename S2>
    concept IsSpecificationTD = (std::same_as<S1, T> && std::same_as<S2, Density>) || (std::same_as<S1, Density> && std::same_as<S2, T>);

    template<typename S1, typename S2>
    concept IsSpecificationTV = (std::same_as<S1, T> && std::same_as<S2, V>) || (std::same_as<S1, V> && std::same_as<S2, T>);

    template<typename S1, typename S2>
    concept IsSpecificationTX = (std::same_as<S1, T> && std::same_as<S2, X>) || (std::same_as<S1, X> && std::same_as<S2, T>);

    template<typename S1, typename S2>
    concept IsSpecificationHS = (std::same_as<S1, H> && std::same_as<S2, S>) || (std::same_as<S1, S> && std::same_as<S2, H>);

    template<typename S1, typename S2>
    concept IsSpecificationUV = (std::same_as<S1, U> && std::same_as<S2, V>) || (std::same_as<S1, V> && std::same_as<S2, U>);

    template<typename S1, typename S2>
    concept IsSpecificationHV = (std::same_as<S1, H> && std::same_as<S2, V>) || (std::same_as<S1, V> && std::same_as<S2, H>);

    template<typename S1, typename S2>
    concept IsSpecification =
        IsSpecificationPT<S1, S2> || IsSpecificationPH<S1, S2> || IsSpecificationPS<S1, S2> || IsSpecificationPU<S1, S2> ||
        IsSpecificationPD<S1, S2> || IsSpecificationPV<S1, S2> || IsSpecificationPX<S1, S2> || IsSpecificationTH<S1, S2> ||
        IsSpecificationTS<S1, S2> || IsSpecificationTU<S1, S2> || IsSpecificationTD<S1, S2> || IsSpecificationTV<S1, S2> ||
        IsSpecificationTX<S1, S2> || IsSpecificationHS<S1, S2> || IsSpecificationUV<S1, S2> || IsSpecificationHV<S1, S2>;

    using PropertyVariant = std::variant<P, T, H, S, U, A, G, Rho, V, PSat, TSat, Cp, Cv, Kappa, W, Z, X, Eta, Nu, TC, PR>;

}    // namespace KSteam
