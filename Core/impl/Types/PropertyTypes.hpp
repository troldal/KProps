//
// Created by kenne on 31/01/2024.
//

#pragma once

// #include "../_external.hpp"

#include <variant>

#include <NamedType/named_type.hpp>

#include "../Utils/Config.hpp"

namespace pcprops
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

        Cp = 9,

        Cv = 10,

        Kappa              = 11,
        IsothermalCompressibility = 11,

        W            = 12,
        SpeedOfSound = 12,

        Z                     = 13,
        CompressibilityFactor = 13,

        X            = 14,
        Q            = 14,
        VaporQuality = 14,

        Eta              = 15,
        DynamicViscosity = 15,

        Nu                 = 16,
        KinematicViscosity = 16,

        TC                  = 17,
        ThermalConductivity = 17,

        PR            = 18,
        PrandtlNumber = 18,

        MW              = 19,
        MolecularWeight = 19,
        MolarMass       = 19

    };

    using MW = fluent::NamedType<FLOAT,
                                 struct MolarWeightTag,
                                 fluent::Printable,
                                 fluent::Addable,
                                 fluent::Subtractable,
                                 fluent::Multiplicable,
                                 fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;

    using MolecularWeight = MW;
    using MolarMass       = MW;

    using T           = fluent::NamedType<FLOAT,
                                          struct TemperatureTag,
                                          fluent::Printable,
                                          fluent::Addable,
                                          fluent::Subtractable,
                                          fluent::Multiplicable,
                                          fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Temperature = T;

    using P        = fluent::NamedType<FLOAT,
                                       struct PressureTag,
                                       fluent::Printable,
                                       fluent::Addable,
                                       fluent::Subtractable,
                                       fluent::Multiplicable,
                                       fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Pressure = P;

    using H        = fluent::NamedType<FLOAT,
                                       struct EnthalpyTag,
                                       fluent::Printable,
                                       fluent::Addable,
                                       fluent::Subtractable,
                                       fluent::Multiplicable,
                                       fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Enthalpy = H;

    using S       = fluent::NamedType<FLOAT,
                                      struct EntropyTag,
                                      fluent::Printable,
                                      fluent::Addable,
                                      fluent::Subtractable,
                                      fluent::Multiplicable,
                                      fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Entropy = S;

    using U              = fluent::NamedType<FLOAT,
                                             struct InternalEnergyTag,
                                             fluent::Printable,
                                             fluent::Addable,
                                             fluent::Subtractable,
                                             fluent::Multiplicable,
                                             fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using InternalEnergy = U;

    using A               = fluent::NamedType<FLOAT,
                                              struct HelmholtzEnergyTag,
                                              fluent::Printable,
                                              fluent::Addable,
                                              fluent::Subtractable,
                                              fluent::Multiplicable,
                                              fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using HelmholtzEnergy = A;

    using G           = fluent::NamedType<FLOAT,
                                          struct GibbsEnergyTag,
                                          fluent::Printable,
                                          fluent::Addable,
                                          fluent::Subtractable,
                                          fluent::Multiplicable,
                                          fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using GibbsEnergy = G;

    using Rho     = fluent::NamedType<FLOAT,
                                      struct DensityTag,
                                      fluent::Printable,
                                      fluent::Addable,
                                      fluent::Subtractable,
                                      fluent::Multiplicable,
                                      fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Density = Rho;

    using V      = fluent::NamedType<FLOAT,
                                     struct VolumeTag,
                                     fluent::Printable,
                                     fluent::Addable,
                                     fluent::Subtractable,
                                     fluent::Multiplicable,
                                     fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Volume = V;
    using Vol    = V;

    using Cp = fluent::NamedType<FLOAT,
                                 struct CpTag,
                                 fluent::Printable,
                                 fluent::Addable,
                                 fluent::Subtractable,
                                 fluent::Multiplicable,
                                 fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;

    using Cv = fluent::NamedType<FLOAT,
                                 struct CvTag,
                                 fluent::Printable,
                                 fluent::Addable,
                                 fluent::Subtractable,
                                 fluent::Multiplicable,
                                 fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;

    using Kappa              = fluent::NamedType<FLOAT,
                                                 struct KappaTag,
                                                 fluent::Printable,
                                                 fluent::Addable,
                                                 fluent::Subtractable,
                                                 fluent::Multiplicable,
                                                 fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using IsothermalCompressibility = Kappa;

    using Alpha              = fluent::NamedType<FLOAT,
                                                        struct AlphaTag,
                                                        fluent::Printable,
                                                        fluent::Addable,
                                                        fluent::Subtractable,
                                                        fluent::Multiplicable,
                                                        fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using ThermalExpansion = Kappa;

    using W            = fluent::NamedType<FLOAT,
                                           struct SpeedOfSoundTag,
                                           fluent::Printable,
                                           fluent::Addable,
                                           fluent::Subtractable,
                                           fluent::Multiplicable,
                                           fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using SpeedOfSound = W;

    using Z                     = fluent::NamedType<FLOAT,
                                                    struct CompressibilityFactorTag,
                                                    fluent::Printable,
                                                    fluent::Addable,
                                                    fluent::Subtractable,
                                                    fluent::Multiplicable,
                                                    fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using CompressibilityFactor = Z;

    using X            = fluent::NamedType<FLOAT,
                                           struct VaporQualityTag,
                                           fluent::Printable,
                                           fluent::Addable,
                                           fluent::Subtractable,
                                           fluent::Multiplicable,
                                           fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using Q            = X;
    using VaporQuality = X;

    using Eta              = fluent::NamedType<FLOAT,
                                               struct DynamicViscosityTag,
                                               fluent::Printable,
                                               fluent::Addable,
                                               fluent::Subtractable,
                                               fluent::Multiplicable,
                                               fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using DynamicViscosity = Eta;

    using Nu                 = fluent::NamedType<FLOAT,
                                                 struct KinematicViscosityTag,
                                                 fluent::Printable,
                                                 fluent::Addable,
                                                 fluent::Subtractable,
                                                 fluent::Multiplicable,
                                                 fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using KinematicViscosity = Nu;

    using TC                  = fluent::NamedType<FLOAT,
                                                  struct ThermalConductivityTag,
                                                  fluent::Printable,
                                                  fluent::Addable,
                                                  fluent::Subtractable,
                                                  fluent::Multiplicable,
                                                  fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using ThermalConductivity = TC;

    using PR            = fluent::NamedType<FLOAT,
                                            struct PrandtlNumberTag,
                                            fluent::Printable,
                                            fluent::Addable,
                                            fluent::Subtractable,
                                            fluent::Multiplicable,
                                            fluent::ImplicitlyConvertibleTo<FLOAT>::templ>;
    using PrandtlNumber = PR;

    template<typename PROPERTY>
    concept IsProperty =
        std::same_as<PROPERTY, T> || std::same_as<PROPERTY, P> || std::same_as<PROPERTY, H> || std::same_as<PROPERTY, S> ||
        std::same_as<PROPERTY, U> || std::same_as<PROPERTY, A> || std::same_as<PROPERTY, G> || std::same_as<PROPERTY, Rho> ||
        std::same_as<PROPERTY, V>   || std::same_as<PROPERTY, Cp> ||
        std::same_as<PROPERTY, Cv> || std::same_as<PROPERTY, Kappa> || std::same_as<PROPERTY, W> || std::same_as<PROPERTY, Z> ||
        std::same_as<PROPERTY, X> || std::same_as<PROPERTY, Eta> || std::same_as<PROPERTY, Nu> || std::same_as<PROPERTY, TC> ||
        std::same_as<PROPERTY, PR>  || std::same_as<PROPERTY, MW> || std::same_as<PROPERTY, Alpha>;

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
    concept IsSpecificationDS = (std::same_as<S1, S> && std::same_as<S2, Density>) || (std::same_as<S1, Density> && std::same_as<S2, S>);

    template<typename S1, typename S2>
    concept IsSpecificationDH = (std::same_as<S1, H> && std::same_as<S2, Density>) || (std::same_as<S1, Density> && std::same_as<S2, H>);

    template<typename S1, typename S2>
    concept IsSpecificationDU = (std::same_as<S1, U> && std::same_as<S2, Density>) || (std::same_as<S1, Density> && std::same_as<S2, U>);

    template<typename S1, typename S2>
    concept IsSpecificationSU = (std::same_as<S1, U> && std::same_as<S2, S>) || (std::same_as<S1, S> && std::same_as<S2, U>);

    template<typename S1, typename S2>
    concept IsSpecification =
        IsSpecificationPT<S1, S2> || IsSpecificationPH<S1, S2> || IsSpecificationPS<S1, S2> || IsSpecificationPU<S1, S2> ||
        IsSpecificationPD<S1, S2> || IsSpecificationPV<S1, S2> || IsSpecificationPX<S1, S2> || IsSpecificationTH<S1, S2> ||
        IsSpecificationTS<S1, S2> || IsSpecificationTU<S1, S2> || IsSpecificationTD<S1, S2> || IsSpecificationTV<S1, S2> ||
        IsSpecificationTX<S1, S2> || IsSpecificationHS<S1, S2> || IsSpecificationUV<S1, S2> || IsSpecificationHV<S1, S2>;

    using PropertyVariant = std::variant<MW, P, T, H, S, U, A, G, Rho, V, Cp, Cv, Kappa, W, Z, X, Eta, Nu, TC, PR>;

}    // namespace pcprops
